//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MP_MEMORY_H
#define PFC_CORE_MP_MEMORY_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "mp.h"
#include "sxp_src/core/containers.h"
namespace pfc
{

// new
class mp_free_list;
class mp_sequential_memory_allocator;
//----------------------------------------------------------------------------


//============================================================================
// mp_free_list
//============================================================================
class mp_free_list: public memory_allocator_base
{
public:
  // construction
  mp_free_list(void *buffer_, usize_t buffer_size_, usize_t item_size_, usize_t item_byte_align_=ptr_size);
  mp_free_list(usize_t item_size_, usize_t capacity_=0, usize_t item_byte_align_=ptr_size);
  ~mp_free_list();
  virtual void check_allocator(usize_t num_bytes_, usize_t mem_align_);
  void reserve(usize_t capacity_);
  void release();
  //--------------------------------------------------------------------------

  // accessors and alloc/dealloc
  PFC_INLINE usize_t capacity() const;
  PFC_INLINE usize_t num_pending_allocs() const;
  PFC_INLINE void *alloc_block();
  PFC_INLINE void free_block(void*);
  virtual void *alloc(usize_t num_bytes_, usize_t mem_align_=memory_align);
  virtual void free(void*);
  //--------------------------------------------------------------------------

private:
  //==========================================================================
  // mp_free_list::item
  //==========================================================================
  struct item
  {
    item *next;
  };
  PFC_CTC_ASSERT(sizeof(item)==ptr_size);
  //--------------------------------------------------------------------------

  const usize_t m_block_size;
  const usize_t m_block_align;
  const usize_t m_num_items_per_stride;
  usize_t m_capacity;
  usize_t m_num_allocs;
  mp_lifo_queue<item> m_queue;
  mp_critical_section m_reserve_csect;
  array<owner_data> m_strides;
};
//----------------------------------------------------------------------------


//============================================================================
// mp_sequential_memory_allocator
//============================================================================
class mp_sequential_memory_allocator: public memory_allocator_base
{
public:
  // construction
  mp_sequential_memory_allocator(usize_t stride_size_=65536, usize_t max_stride_alloc_size_=1024, bool support_free_blocks_=false);
  ~mp_sequential_memory_allocator();
  virtual void check_allocator(usize_t num_bytes_, usize_t mem_align_);
  void release();
  void force_release();
  //--------------------------------------------------------------------------

  // memory management
  virtual void *alloc(usize_t num_bytes_, usize_t mem_align_=memory_align);
  virtual void free(void*);
  //--------------------------------------------------------------------------

private:
  //==========================================================================
  // stride_state
  //==========================================================================
  union stride_state
  {
    struct stride_state_struct
    {
      usize_t stride_pos;
      void * stride;
    } state_data;
    usize2_t data;
  };
  //--------------------------------------------------------------------------

  const usize_t m_stride_size;
  const usize_t m_max_stride_alloc_size;
  const bool m_support_free_blocks;
  usize_t m_num_allocs;
  stride_state m_stride_state;
  list<owner_data> m_strides;
  list<owner_data> m_free_blocks;
  mp_critical_section m_stride_csect;
  mp_critical_section m_free_block_csect;
};
//----------------------------------------------------------------------------

//============================================================================
#include "mp_memory.inl"
} // namespace pfc
#endif
