//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "mp_memory.h"
#include "sxp_src/core/math/bit_math.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// config
//============================================================================
enum
{
  min_stride_items=4,
  stride_size=4096
};
//----------------------------------------------------------------------------


//============================================================================
// mp_free_list
//============================================================================
mp_free_list::mp_free_list(void *buffer_, usize_t buffer_size_, usize_t item_size_, usize_t item_byte_align_)
  :m_block_size(item_byte_align_*((item_size_+item_byte_align_-1)/item_byte_align_))
  ,m_block_align(item_byte_align_)
  ,m_num_items_per_stride(0)
  ,m_num_allocs(0)
{
  // calculate capacity
  PFC_ASSERT(item_size_);
  PFC_ASSERT_MSG(item_byte_align_>=ptr_size && is_pow2(item_byte_align_), ("free_list item byte alignment (%i) must be at least %i and power-of-2\r\n", item_byte_align_, ptr_size));
  usize_t align_offset=((item_byte_align_-usize_t(buffer_))&(item_byte_align_-1));
  buffer_size_=buffer_size_>align_offset?buffer_size_-align_offset:0;
  (uint8_t*&)buffer_+=align_offset;
  m_capacity=buffer_size_/m_block_size;

  // build free-list
  item *it=(item*)buffer_;
  for(usize_t i=0; i<m_capacity-1; ++i)
  {
    item *next_it=(item*)(((uint8_t*&)it)+m_block_size);
    m_queue.push(*it);
    it=next_it;
  }
}
//----

mp_free_list::mp_free_list(usize_t item_size_, usize_t capacity_, usize_t item_byte_align_)
  :m_block_size(item_byte_align_*((item_size_+item_byte_align_-1)/(item_byte_align_?item_byte_align_:1)))
  ,m_block_align(item_byte_align_)
  ,m_num_items_per_stride(max<usize_t>(min_stride_items, m_block_size?stride_size/m_block_size:0))
  ,m_capacity(0)
  ,m_num_allocs(0)
{
  PFC_ASSERT(item_size_);
  PFC_ASSERT_MSG(item_byte_align_>=ptr_size && is_pow2(item_byte_align_), ("free_list item byte alignment (%i) must be at least %i and power-of-2\r\n", item_byte_align_, ptr_size));
  reserve(capacity_);
}
//----

mp_free_list::~mp_free_list()
{
  release();
}
//----

void mp_free_list::check_allocator(usize_t num_bytes_, usize_t mem_align_)
{
  PFC_CHECK_MSG(num_bytes_<=m_block_size, ("mp_free_list allocates %u byte memory blocks (requesting %u bytes)\r\n", m_block_size, num_bytes_));
  PFC_CHECK_MSG(mem_align_ && mem_align_<=m_block_align && (mem_align_&(mem_align_-1))==0,
                ("mp_free_list memory alignment must be power-of-2 and in range [1, %u] (requesting %u byte alignment)\r\n", m_block_align, mem_align_));
}
//----

void mp_free_list::reserve(usize_t capacity_)
{
  // check for free-list expansion
  m_reserve_csect.enter();
  if(capacity_<=m_capacity)
  {
    m_reserve_csect.leave();
    return;
  }
  PFC_ASSERT_MSG(m_num_items_per_stride, ("Fixed size free_list out of capacity\r\n"));

  // allocate new strides and construct free list
  usize_t num_new_strides=((capacity_-m_capacity)+m_num_items_per_stride-1)/m_num_items_per_stride;
  usize_t ssize=m_num_items_per_stride*m_block_size;
  m_strides.reserve(m_strides.size()+num_new_strides);
  for(usize_t si=0; si<num_new_strides; ++si)
  {
    // allocate stride and add elements to the free list
    item *stride=(item*)PFC_MEM_ALLOC(ssize);
    m_strides.push_back(stride);
    usize_t align_offset=(m_block_align-usize_t(stride))&(m_block_align-1);
    (uint8_t*&)stride+=align_offset;
    usize_t num_items=m_num_items_per_stride-(align_offset?1:0);
    for(usize_t i=0; i<num_items; ++i)
    {
      item *next_it=(item*)(((uint8_t*&)stride)+m_block_size);
      m_queue.push(*stride);
      stride=next_it;
    }
  }
  m_capacity+=num_new_strides*m_num_items_per_stride;
  m_reserve_csect.leave();
}
//----

void mp_free_list::release()
{
  // release free list queue items
  PFC_ASSERT(!m_num_allocs);
  m_capacity=0;
  m_strides.clear();
  m_queue.force_clear();
}
//----------------------------------------------------------------------------

void *mp_free_list::alloc(usize_t num_bytes_, usize_t mem_align_)
{
  PFC_ASSERT_PEDANTIC_MSG(num_bytes_<=m_block_size, ("mp_free_list allocates %u byte memory blocks (requesting %u bytes)\r\n", m_block_size, num_bytes_));
  PFC_ASSERT_PEDANTIC_MSG(mem_align_ && mem_align_<=m_block_align && (mem_align_&(mem_align_-1))==0,
                          ("mp_free_list memory alignment must be power-of-2 and in range [1, %u] (requesting %u byte alignment)\r\n", m_block_align, mem_align_));
  return alloc_block();
}
//----

void mp_free_list::free(void *p_)
{
  if(p_)
    free_block(p_);
}
//----------------------------------------------------------------------------


//============================================================================
// mp_sequential_memory_allocator
//============================================================================
mp_sequential_memory_allocator::mp_sequential_memory_allocator(usize_t stride_size_, usize_t max_stride_alloc_size_, bool support_free_blocks_)
  :m_stride_size(stride_size_)
  ,m_max_stride_alloc_size(max_stride_alloc_size_)
  ,m_support_free_blocks(support_free_blocks_)
{
  // init allocator
  PFC_ASSERT(max_stride_alloc_size_<=stride_size_);
  m_num_allocs=0;
  m_stride_state.state_data.stride_pos=stride_size_;
  m_stride_state.state_data.stride=0;
}
//----

mp_sequential_memory_allocator::~mp_sequential_memory_allocator()
{
  release();
}
//----

void mp_sequential_memory_allocator::check_allocator(usize_t num_bytes_, usize_t mem_align_)
{
  PFC_CHECK_MSG(m_support_free_blocks || num_bytes_<=m_max_stride_alloc_size,
                ("mp_sequential_memory_allocator maximum memory block size is %u bytes (requesting %u bytes)\r\n", m_max_stride_alloc_size, num_bytes_));
  PFC_CHECK_MSG(mem_align_ && mem_align_<=memory_align && (mem_align_&(mem_align_-1))==0,
                ("mp_sequential_memory_allocator memory alignment must be power-of-2 and in range [1, %u] (requesting %u byte alignment)\r\n", memory_align, mem_align_));
}
//----

void mp_sequential_memory_allocator::release()
{
  // check for no allocations and release memory resources
  PFC_ASSERT(!m_num_allocs);
  force_release();
}
//----

void mp_sequential_memory_allocator::force_release()
{
  // release memory resources
  m_num_allocs=0;
  m_stride_state.state_data.stride_pos=m_stride_size;
  m_stride_state.state_data.stride=0;
  m_stride_csect.enter();
  m_strides.clear();
  m_free_blocks.clear();
  m_stride_csect.leave();
}
//----------------------------------------------------------------------------

void *mp_sequential_memory_allocator::alloc(usize_t num_bytes_, usize_t mem_align_)
{
  // check for free block allocation
  PFC_ASSERT_PEDANTIC_MSG(mem_align_ && mem_align_<=memory_align && (mem_align_&(mem_align_-1))==0,
                          ("mp_sequential_memory_allocator memory alignment must be power-of-2 and in range [1, %u] (requesting %u byte alignment)\r\n", memory_align, mem_align_));
  atom_inc(m_num_allocs);
  if(num_bytes_>m_max_stride_alloc_size)
  {
    PFC_ASSERT_MSG(m_support_free_blocks, ("Free block allocations are disabled for the allocator (max stride alloc size is %i bytes). Trying to allocate %i bytes\r\n", m_max_stride_alloc_size, num_bytes_));
    void *data=PFC_MEM_ALLOC(num_bytes_);
    m_free_block_csect.enter();
    m_free_blocks.push_back(data);
    m_free_block_csect.leave();
    return data;
  }

  stride_state cur_state, new_state;
  do 
  {
    // get aligned position and check for new stride allocation
    cur_state.data=atom_read(m_stride_state.data);
    usize_t aligned_stride_pos=(cur_state.state_data.stride_pos+(mem_align_-1))&(0-mem_align_);
    new_state.state_data.stride_pos=aligned_stride_pos+num_bytes_;
    new_state.state_data.stride=cur_state.state_data.stride;
    if(new_state.state_data.stride_pos>m_stride_size)
    {
      // enter stride critical section and check if a stride is already added
      m_stride_csect.enter();
      if(m_stride_state.state_data.stride==cur_state.state_data.stride)
      {
        // add new memory stride
        new_state.state_data.stride_pos=num_bytes_;
        new_state.state_data.stride=PFC_MEM_ALLOC(m_stride_size);
        atom_write(m_stride_state.data, new_state.data);
        m_strides.push_back(new_state.state_data.stride);
        m_stride_csect.leave();
        return new_state.state_data.stride;
      }
      m_stride_csect.leave();
    }
  } while(atom_cmov_eq(m_stride_state.data, new_state.data, cur_state.data)!=cur_state.data);

  // return memory block address
  return ((char*)new_state.state_data.stride)+new_state.state_data.stride_pos-num_bytes_;
}
//----

void mp_sequential_memory_allocator::free(void*)
{
  atom_dec(m_num_allocs);
}
//----------------------------------------------------------------------------
