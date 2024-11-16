//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "memory.h"
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
// free_list
//============================================================================
free_list::free_list()
  :m_block_size(0)
  ,m_block_align(0)
  ,m_num_items_per_stride(0)
  ,m_capacity(0)
  ,m_num_allocs(0)
  ,m_head(0)
{
}
//----

free_list::free_list(void *buffer_, usize_t buffer_size_, usize_t item_size_, usize_t item_byte_align_)
  :m_block_size(0)
  ,m_block_align(0)
  ,m_num_items_per_stride(0)
  ,m_capacity(0)
  ,m_num_allocs(0)
  ,m_head(0)
{
  init(buffer_, buffer_size_, item_size_, item_byte_align_);
}
//----

free_list::free_list(usize_t item_size_, usize_t capacity_, usize_t item_byte_align_)
  :m_block_size(0)
  ,m_block_align(0)
  ,m_num_items_per_stride(0)
  ,m_capacity(0)
  ,m_num_allocs(0)
  ,m_head(0)
{
  init(item_size_, capacity_, item_byte_align_);
}
//----

free_list::~free_list()
{
  release();
}
//----

void free_list::init(void *buffer_, usize_t buffer_size_, usize_t item_size_, usize_t item_byte_align_)
{
  // calculate capacity
  PFC_ASSERT_MSG(!m_block_size, ("free_list has already been initialized\r\n"));
  PFC_ASSERT(item_size_);
  PFC_ASSERT_MSG(item_byte_align_>=ptr_size && is_pow2(item_byte_align_),
                 ("free_list item byte alignment (%i) must be at least %i and power-of-2\r\n", item_byte_align_, ptr_size));
  m_block_size=item_byte_align_*((item_size_+item_byte_align_-1)/item_byte_align_);
  m_block_align=item_byte_align_;
  usize_t align_offset=(item_byte_align_-usize_t(buffer_))&(item_byte_align_-1);
  buffer_size_=buffer_size_>align_offset?buffer_size_-align_offset:0;
  (uint8_t*&)buffer_+=align_offset;
  m_capacity=buffer_size_/m_block_size;

  // build free-list
  item *it=(item*)buffer_;
  m_head=it;
  for(usize_t i=0; i<m_capacity-1; ++i)
  {
    item *next_it=(item*)(((uint8_t*&)it)+m_block_size);
    it->next=next_it;
    it=next_it;
  }
  it->next=0;
}
//----

void free_list::init(usize_t item_size_, usize_t capacity_, usize_t item_byte_align_)
{
  PFC_ASSERT_MSG(!m_block_size, ("free_list has already been initialized\r\n"));
  PFC_ASSERT(item_size_);
  PFC_ASSERT_MSG(item_byte_align_>=ptr_size && is_pow2(item_byte_align_),
                 ("free_list item byte alignment (%i) must be at least %i and power-of-2\r\n", item_byte_align_, ptr_size));
  m_block_size=item_byte_align_*((item_size_+item_byte_align_-1)/(item_byte_align_?item_byte_align_:1));
  m_block_align=item_byte_align_;
  m_num_items_per_stride=max<usize_t>(min_stride_items, m_block_size?stride_size/m_block_size:0);
  reserve(capacity_);
}
//----

void free_list::check_allocator(usize_t num_bytes_, usize_t mem_align_)
{
  PFC_CHECK_MSG(num_bytes_<=m_block_size, ("free_list allocates %u byte memory blocks (requesting %u bytes)\r\n", m_block_size, num_bytes_));
  PFC_CHECK_MSG(mem_align_ && mem_align_<=m_block_align && (mem_align_&(mem_align_-1))==0,
                ("free_list memory alignment must be power-of-2 and in range [1, %u] (requesting %u byte alignment)\r\n", m_block_align, mem_align_));
}
//----

void free_list::reserve(usize_t capacity_)
{
  // check for free-list expansion
  if(capacity_<=m_capacity)
    return;
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
      stride->next=m_head;
      m_head=stride;
      ((uint8_t*&)stride)+=m_block_size;
    }
  }
  m_capacity+=num_new_strides*m_num_items_per_stride;
}
//----

void free_list::release()
{
  PFC_ASSERT(!m_num_allocs);
  m_capacity=0;
  m_head=0;
  m_strides.clear();
}
//----

void free_list::force_release()
{
  m_capacity=0;
  m_num_allocs=0;
  m_head=0;
  m_strides.clear();
}
//----------------------------------------------------------------------------

void *free_list::alloc(usize_t num_bytes_, usize_t mem_align_)
{
  PFC_ASSERT_PEDANTIC_MSG(num_bytes_<=m_block_size, ("free_list allocates %u byte memory blocks (requesting %u bytes)\r\n", m_block_size, num_bytes_));
  PFC_ASSERT_PEDANTIC_MSG(mem_align_ && mem_align_<=m_block_align && (mem_align_&(mem_align_-1))==0,
                          ("free_list memory alignment must be power-of-2 and in range [1, %u] (requesting %u byte alignment)\r\n", m_block_align, mem_align_));
  return alloc_block();
}
//----

void free_list::free(void *p_)
{
  if(p_)
    free_block(p_);
}
//----------------------------------------------------------------------------


//============================================================================
// sequential_memory_allocator
//============================================================================
sequential_memory_allocator::sequential_memory_allocator(usize_t stride_size_, usize_t max_stride_alloc_size_, bool support_free_blocks_)
  :m_stride_size(stride_size_)
  ,m_max_stride_alloc_size(max_stride_alloc_size_)
  ,m_support_free_blocks(support_free_blocks_)
{
  // init allocator
  PFC_ASSERT(max_stride_alloc_size_<=stride_size_);
  m_num_allocs=0;
  m_cur_stride_pos=stride_size_;
  m_cur_stride=0;
}
//----

sequential_memory_allocator::~sequential_memory_allocator()
{
  release();
}
//----

void sequential_memory_allocator::release()
{
  // check for no allocations and release memory resources
  PFC_ASSERT(!m_num_allocs);
  m_cur_stride_pos=m_stride_size;
  m_cur_stride=0;
  m_strides.clear();
  m_free_blocks.clear();
}
//----

void sequential_memory_allocator::force_release()
{
  // release memory resources
  m_num_allocs=0;
  m_cur_stride_pos=m_stride_size;
  m_cur_stride=0;
  m_strides.clear();
  m_free_blocks.clear();
}
//----------------------------------------------------------------------------

void *sequential_memory_allocator::alloc(usize_t num_bytes_, usize_t mem_align_)
{
  // check for free block allocation
  PFC_ASSERT_PEDANTIC_MSG(mem_align_ && mem_align_<=memory_align && (mem_align_&(mem_align_-1))==0, ("Memory alignment (%i) must be power-of-2 and in range [1, %i]\r\n", mem_align_, memory_align));
  ++m_num_allocs;
  if(num_bytes_>m_max_stride_alloc_size)
  {
    PFC_ASSERT_MSG(m_support_free_blocks, ("Free block allocations are disabled for the allocator (max stride alloc size is %i bytes). Trying to allocate %i bytes\r\n", m_max_stride_alloc_size, num_bytes_));
    void *data=PFC_MEM_ALLOC(num_bytes_);
    m_free_blocks.push_back(data);
    return data;
  }

  // get aligned position and check for new stride allocation
  usize_t aligned_stride_pos=(m_cur_stride_pos+(mem_align_-1))&(0-mem_align_);
  m_cur_stride_pos=aligned_stride_pos+num_bytes_;
  if(m_cur_stride_pos>m_stride_size)
  {
    // add new stride
    aligned_stride_pos=0;
    m_cur_stride_pos=num_bytes_;
    m_cur_stride=PFC_MEM_ALLOC(m_stride_size);
    m_strides.push_back(m_cur_stride);
  }

  // return memory block address
  return ((char*)m_cur_stride)+aligned_stride_pos;
}
//----

void sequential_memory_allocator::free(void*)
{
  --m_num_allocs;
}
//----------------------------------------------------------------------------


//============================================================================
// buddy_memory_manager
//============================================================================
buddy_memory_manager::buddy_memory_manager()
{
  m_pool_size=0;
  m_num_allocs=0;
  m_free_list=0;
}
//----

buddy_memory_manager::buddy_memory_manager(usize_t pool_size_)
{
  m_pool_size=0;
  m_num_allocs=0;
  m_free_list=0;
  init(pool_size_);
}
//----

buddy_memory_manager::~buddy_memory_manager()
{
  uninit();
}
//----

void buddy_memory_manager::init(usize_t pool_size_)
{
  // setup null block (0) and pool blocks (1..num_pools)
  PFC_ASSERT_MSG(m_blocks.size()==0, ("Buddy memory manager has already been initialized\r\n"));
  PFC_ASSERT_MSG(pool_size_, ("Pool size for buddy memory manager not specified\r\n"));
  m_blocks.insert_back(num_pools+1);
  m_pool_size=pool_size_;

  // add initial memory blocks for the pool size
  usize_t data_offset=0;
  while(pool_size_)
  {
    unsigned pool_idx=msb_pos(pool_size_)+1;
    PFC_ASSERT(pool_idx<=num_pools);
    unsigned block_idx=alloc_block();
    buddy_block &block=m_blocks[block_idx];
    block.data_offset=data_offset;
    block.prev_idx[0]=pool_idx;
    block.next_idx[0]=0;
    m_blocks[pool_idx].next_idx[0]=block_idx;
    usize_t pool_size=usize_t(1)<<(pool_idx-1);
    pool_size_&=~pool_size;
    data_offset+=pool_size;
  }
}
//----

void buddy_memory_manager::uninit()
{
  PFC_ASSERT_MSG(!m_num_allocs, ("Buddy memory manager has %i pending memory allocations\r\n", m_num_allocs));
  m_blocks.clear();
  m_pool_size=0;
  m_free_list=0;
}
//----

void buddy_memory_manager::force_release()
{
  // force-release all pending memory allocations
  m_num_allocs=0;
  init(m_pool_size);
}
//----------------------------------------------------------------------------

buddy_mem_handle_t buddy_memory_manager::alloc(usize_t num_items_)
{
  // search for free block from pools for given number of items
  PFC_ASSERT_MSG(m_blocks.size(), ("Buddy memory manager not initialized\r\n"));
  PFC_ASSERT(num_items_);
  unsigned required_pool_idx=msb_pos(num_items_*2-1)+1;
  unsigned pool_idx=required_pool_idx;
  while(pool_idx<=num_pools)
  {
    // check if found a free block
    if(unsigned block_idx=m_blocks[pool_idx].next_idx[0])
    {
      // remove the block from the pool
      buddy_block *block=&m_blocks[block_idx];
      unsigned buddy_idx=block->prev_idx[0]==0;
      m_blocks[pool_idx].next_idx[0]=block->next_idx[buddy_idx];
      block->prev_idx[buddy_idx]=0;

      // trim block to the closest matching size
      while(pool_idx>required_pool_idx)
      {
        // add new block to the smaller block list
        --pool_idx;
        unsigned new_block_idx=alloc_block();
        buddy_block &new_block=m_blocks[new_block_idx];
        new_block.data_offset=block->data_offset+(buddy_idx?1<<pool_idx:0);
        new_block.prev_idx[0]=0;
        new_block.prev_idx[1]=pool_idx;
        new_block.next_idx[0]=0;
        new_block.next_idx[1]=0;
        new_block.parent_idx=(block_idx<<1)|buddy_idx;
        m_blocks[pool_idx].next_idx[0]=new_block_idx;
        block_idx=new_block_idx;
        block=&new_block;
        buddy_idx=0;
      }
      ++m_num_allocs;
      return (void*)((usize_t(block_idx)<<block_idx_shift)|((pool_idx-1)<<1)|buddy_idx);
    }
    ++pool_idx;
  }
  PFC_ERRORF("Out of memory while trying to allocate %i items\r\n", num_items_);
  return 0;
}
//----

void buddy_memory_manager::free(buddy_mem_handle_t handle_)
{
  // coalesce free buddy blocks
  usize_t handle=(usize_t)handle_;
  unsigned pool_idx=((handle>>1)&order_mask)+1;
  unsigned buddy_idx=(handle&1)^1;
  unsigned block_idx=(unsigned)(handle>>block_idx_shift);
  buddy_block *block=&m_blocks[block_idx];
  while(unsigned buddy_prev_idx=block->prev_idx[buddy_idx])
  {
    // remove block from buddy free-list and free the block
    unsigned buddy_next_idx=block->next_idx[buddy_idx];
    buddy_block &prev_block=m_blocks[buddy_prev_idx];
    prev_block.next_idx[prev_block.next_idx[0]!=block_idx]=buddy_next_idx;
    if(buddy_next_idx)
    {
      buddy_block &next_block=m_blocks[buddy_next_idx];
      next_block.prev_idx[next_block.prev_idx[0]!=block_idx]=buddy_prev_idx;
    }
    free_block(block_idx);

    // proceed to the parent block
    buddy_idx=(block->parent_idx&1)^1;
    block_idx=block->parent_idx>>1;
    block=&m_blocks[block_idx];
    ++pool_idx;
  }

  // push free block to the proper pool
  block->prev_idx[buddy_idx^1]=pool_idx;
  unsigned next_block=m_blocks[pool_idx].next_idx[0];
  block->next_idx[buddy_idx^1]=next_block;
  m_blocks[next_block].prev_idx[m_blocks[next_block].prev_idx[0]==0]=block_idx;
  m_blocks[pool_idx].next_idx[0]=block_idx;
  --m_num_allocs;
}
//----------------------------------------------------------------------------

unsigned buddy_memory_manager::alloc_block()
{
  // pop new block from the free-list
  if(!m_free_list)
    reserve();
  unsigned new_block_idx=m_free_list;
  m_free_list=m_blocks[new_block_idx].next_idx[0];
  return new_block_idx;
}
//----

void buddy_memory_manager::free_block(unsigned block_idx_)
{
  // push block to the free-list
  m_blocks[block_idx_].next_idx[0]=m_free_list;
  m_free_list=block_idx_;
}
//----

void buddy_memory_manager::reserve()
{
  // insert new items to the free-list
  enum {num_reserve_blocks=deque_traits<buddy_block>::ssize};
  unsigned start_block_idx=(unsigned)m_blocks.size();
  m_blocks.insert_back(num_reserve_blocks);
  for(unsigned i=0; i<num_reserve_blocks; ++i)
  {
    m_blocks[start_block_idx+i].next_idx[0]=m_free_list;
    m_free_list=start_block_idx+i;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// atlas_memory_manager
//============================================================================
atlas_memory_manager::atlas_memory_manager()
{
  m_atlas_width=0;
  m_atlas_height=0;
  m_num_allocs=0;
  m_block_free_list=0;
}
//----

atlas_memory_manager::atlas_memory_manager(unsigned width_, unsigned height_)
{
  m_atlas_width=0;
  m_atlas_height=0; 
  m_num_allocs=0;
  m_block_free_list=0;
  init(width_, height_);
}
//----

atlas_memory_manager::~atlas_memory_manager()
{
  uninit();
}
//----

void atlas_memory_manager::init(unsigned width_, unsigned height_)
{
  // setup null block (0) and pool blocks (1..num_pools)
  PFC_ASSERT_MSG(m_blocks.size()==0, ("Atlas memory manager has already been initialized\r\n"));
  PFC_ASSERT_MSG(width_ && height_, ("Atlas size for atlas memory manager not specified\r\n"));
  PFC_ASSERT_MSG(is_pow2(width_) && is_pow2(height_), ("Atlas width and height must be power-of-two\r\n"));
  m_blocks.insert_back(num_pools+1);
  m_atlas_width=width_;
  m_atlas_height=height_;

  // add initial blocks for the atlas
  unsigned min_dim=min(width_, height_);
  unsigned max_dim=max(width_, height_);
  unsigned pool_idx=bitpos(min_dim)+1;
  atlas_coords coords={0, 0};
  for(unsigned i=0; i<max_dim; i+=min_dim)
  {
    unsigned block_idx=alloc_block();
    buddy_block &block=m_blocks[block_idx];
    block.coords=coords;
    block.free_buddy_mask=0x1;
    block.next_idx=0;
    block.prev_idx=pool_idx;
    if(unsigned pool_next_idx=m_blocks[pool_idx].next_idx)
      m_blocks[pool_next_idx].prev_idx=block_idx;
    m_blocks[pool_idx].next_idx=block_idx;
    coords.x+=width_>height_?min_dim:0;
    coords.y+=height_>width_?min_dim:0;
  }
}
//----

void atlas_memory_manager::uninit()
{
  PFC_ASSERT_MSG(!m_num_allocs, ("Atlas memory manager has %i pending memory allocations\r\n", m_num_allocs));
  m_blocks.clear();
  m_atlas_width=0;
  m_atlas_height=0;
  m_block_free_list=0;
}
//----

void atlas_memory_manager::force_release()
{
  m_num_allocs=0;
  init(m_atlas_width, m_atlas_height);
}
//----------------------------------------------------------------------------

atlas_mem_handle_t atlas_memory_manager::alloc(unsigned size_)
{
  PFC_ASSERT_MSG(m_blocks.size(), ("Atlas memory manager not initialized\r\n"));
  PFC_ASSERT(size_);
  unsigned required_pool_idx=msb_pos(size_*2-1)+1;
  unsigned pool_idx=required_pool_idx;
  while(pool_idx<=num_pools)
  {
    // check for a free block
    if(unsigned block_idx=m_blocks[pool_idx].next_idx)
    {
      // get buddy index and check if all block buddies are allocated
      buddy_block *block=&m_blocks[block_idx];
      uint8_t free_buddy_mask=block->free_buddy_mask;
      unsigned buddy_idx=lsb_pos(free_buddy_mask);
      block->free_buddy_mask&=~lsb(free_buddy_mask);
      if(!block->free_buddy_mask)
      {
        // remove the block from the pool
        m_blocks[pool_idx].next_idx=block->next_idx;
        block->prev_idx=0;
      }

      // trim block to the closest matching size
      while(pool_idx>required_pool_idx)
      {
        // add new block to the smaller block list
        --pool_idx;
        unsigned new_block_idx=alloc_block();
        buddy_block &new_block=m_blocks[new_block_idx];
        new_block.free_buddy_mask=0xe;
        new_block.coords.x=block->coords.x+((buddy_idx&1)<<pool_idx);
        new_block.coords.y=block->coords.y+((buddy_idx&2)<<(pool_idx-1));
        new_block.prev_idx=pool_idx;
        new_block.next_idx=0;
        new_block.parent_idx=(block_idx<<2)|buddy_idx;
        m_blocks[pool_idx].next_idx=new_block_idx;
        block_idx=new_block_idx;
        block=&new_block;
        buddy_idx=0;
      }
      ++m_num_allocs;
      return atlas_mem_handle_t((block_idx<<block_idx_shift)|((pool_idx-1)<<2)|buddy_idx);
    }
    ++pool_idx;
  }
  PFC_ERRORF("Out of memory while trying to allocate %ix%i rect from %ix%i atlas\r\n", size_, size_, m_atlas_width, m_atlas_height);
  return 0;
}
//----

void atlas_memory_manager::free(atlas_mem_handle_t handle_)
{
  // coalesce free buddy blocks
  unsigned pool_idx=((handle_>>2)&order_mask)+1;
  unsigned buddy_idx=handle_&3;
  unsigned block_idx=handle_>>block_idx_shift;
  buddy_block *block=&m_blocks[block_idx];
  while((block->free_buddy_mask|=1<<buddy_idx)==0xf && block->parent_idx)
  {
    // free block
    unsigned block_prev_idx=block->prev_idx;
    unsigned block_next_idx=block->next_idx;
    m_blocks[block_prev_idx].next_idx=block_next_idx;
    if(block_next_idx)
      m_blocks[block_next_idx].prev_idx=block_prev_idx;
    free_block(block_idx);

    // proceed to the parent block
    buddy_idx=(block->parent_idx&3);
    block_idx=block->parent_idx>>2;
    block=&m_blocks[block_idx];
    ++pool_idx;
  }

  // check if block is already in a free list
  if(!block->prev_idx)
  {
    // add block to the free list of the pool
    block->prev_idx=pool_idx;
    m_blocks[pool_idx].next_idx=block_idx;
  }
  --m_num_allocs;
}
//----------------------------------------------------------------------------

unsigned atlas_memory_manager::alloc_block()
{
  // pop new block from the free-list
  if(!m_block_free_list)
    reserve_blocks();
  unsigned new_block_idx=m_block_free_list;
  m_block_free_list=m_blocks[new_block_idx].next_idx;
  return new_block_idx;
}
//----

void atlas_memory_manager::free_block(unsigned block_idx_)
{
  // push block to the free-list
  m_blocks[block_idx_].next_idx=m_block_free_list;
  m_block_free_list=block_idx_;
}
//----

void atlas_memory_manager::reserve_blocks()
{
  // insert new items to the free-list
  enum {num_reserve_blocks=deque_traits<buddy_block>::ssize};
  unsigned start_block_idx=(unsigned)m_blocks.size();
  m_blocks.insert_back(num_reserve_blocks);
  for(unsigned i=0; i<num_reserve_blocks; ++i)
  {
    m_blocks[start_block_idx+i].next_idx=m_block_free_list;
    m_block_free_list=start_block_idx+i;
  }
}
//----------------------------------------------------------------------------
