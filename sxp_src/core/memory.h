//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MEMORY_H
#define PFC_CORE_MEMORY_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "containers.h"
namespace pfc
{

// new
class free_list;
class sequential_memory_allocator;
class buddy_memory_manager;
class atlas_memory_manager;
template<typename> class lru_index_cache;
//----------------------------------------------------------------------------


//============================================================================
// free_list
//============================================================================
class free_list: public memory_allocator_base
{
public:
  // construction
  free_list();
  free_list(void *buffer_, usize_t buffer_size_, usize_t item_size_, usize_t item_byte_align_=ptr_size);
  free_list(usize_t item_size_, usize_t capacity_=0, usize_t item_byte_align_=ptr_size);
  ~free_list();
  void init(void *buffer_, usize_t buffer_size_, usize_t item_size_, usize_t item_byte_align_=ptr_size);
  void init(usize_t item_size_, usize_t capacity_=0, usize_t item_byte_align_=ptr_size);
  virtual void check_allocator(usize_t num_bytes_, usize_t mem_align_);
  void reserve(usize_t capacity_);
  void release();
  void force_release();
  //--------------------------------------------------------------------------

  // accessors and alloc/dealloc
  PFC_INLINE usize_t capacity() const;
  PFC_INLINE usize_t num_allocs() const;
  PFC_INLINE void *alloc_block();
  PFC_INLINE void free_block(void*);
  virtual void *alloc(usize_t num_bytes_, usize_t mem_align_=memory_align);
  virtual void free(void*);
  //--------------------------------------------------------------------------

private:
  //==========================================================================
  // free_list::item
  //==========================================================================
  struct item
  {
    item *next;
  };
  PFC_STATIC_ASSERT(sizeof(item)==ptr_size);
  //--------------------------------------------------------------------------

  usize_t m_block_size;
  usize_t m_block_align;
  usize_t m_num_items_per_stride;
  usize_t m_capacity;
  usize_t m_num_allocs;
  item *m_head;
  array<owner_data> m_strides;
};
//----------------------------------------------------------------------------


//============================================================================
// sequential_memory_allocator
//============================================================================
class sequential_memory_allocator: public memory_allocator_base
{
public:
  // construction
  sequential_memory_allocator(usize_t stride_size_=65536, usize_t max_stride_alloc_size_=1024, bool support_free_blocks_=false);
  ~sequential_memory_allocator();
  void release();
  void force_release();
  //--------------------------------------------------------------------------

  // memory management
  virtual void *alloc(usize_t num_bytes_, usize_t mem_align_=memory_align);
  virtual void free(void*);
  //--------------------------------------------------------------------------

private:
  const usize_t m_stride_size;
  const usize_t m_max_stride_alloc_size;
  const bool m_support_free_blocks;
  usize_t m_num_allocs;
  usize_t m_cur_stride_pos;
  void *m_cur_stride;
  list<owner_data> m_strides;
  list<owner_data> m_free_blocks;
};
//----------------------------------------------------------------------------


//============================================================================
// buddy_memory_manager
//============================================================================
typedef void *buddy_mem_handle_t;
//----

class buddy_memory_manager
{
public:
  // construction
  buddy_memory_manager();
  buddy_memory_manager(usize_t pool_size_);
  ~buddy_memory_manager();
  void init(usize_t pool_size_);
  void uninit();
  void force_release();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE usize_t pool_size() const;
  PFC_INLINE usize_t num_allocs() const;
  //--------------------------------------------------------------------------

  // memory management
  buddy_mem_handle_t alloc(usize_t num_items_);
  void free(buddy_mem_handle_t);
  PFC_INLINE usize_t data_offset(buddy_mem_handle_t) const;
  //--------------------------------------------------------------------------

private:
  buddy_memory_manager(const buddy_memory_manager&); // not implemented
  void operator=(const buddy_memory_manager&); // not implemented
  PFC_INLINE unsigned alloc_block();
  PFC_INLINE void free_block(unsigned);
  void reserve();
  //--------------------------------------------------------------------------

  //==========================================================================
  // buddy_block
  //==========================================================================
  struct buddy_block
  {
    buddy_block()
    {
      data_offset=0;
      prev_idx[0]=prev_idx[1]=0;
      next_idx[0]=next_idx[1]=0;
      parent_idx=0;
    }
    //------------------------------------------------------------------------

    usize_t data_offset;
    unsigned prev_idx[2], next_idx[2], parent_idx;
  };
  //--------------------------------------------------------------------------

  enum {max_order=5};
  enum {num_pools=1<<max_order};
  enum {block_idx_shift=max_order+1};
  enum {order_mask=(1<<max_order)-1};
  deque<buddy_block> m_blocks;
  usize_t m_pool_size;
  usize_t m_num_allocs;
  unsigned m_free_list;
};
//----------------------------------------------------------------------------


//============================================================================
// atlas_memory_manager
//============================================================================
typedef uint32_t atlas_mem_handle_t;
struct atlas_coords {unsigned x, y;};
//----

class atlas_memory_manager
{
public:
  // construction
  atlas_memory_manager();
  atlas_memory_manager(unsigned width_, unsigned height_);
  ~atlas_memory_manager();
  void init(unsigned width_, unsigned height_);
  void uninit();
  void force_release();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE unsigned atlas_width() const;
  PFC_INLINE unsigned atlas_height() const;
  PFC_INLINE unsigned num_allocs() const;
  //--------------------------------------------------------------------------

  // memory management
  atlas_mem_handle_t alloc(unsigned size_);
  void free(atlas_mem_handle_t);
  PFC_INLINE atlas_coords coords(atlas_mem_handle_t) const;
  //--------------------------------------------------------------------------

private:
  atlas_memory_manager(const atlas_memory_manager&); // not implemented
  void operator=(const atlas_memory_manager&); // not implemented
  PFC_INLINE unsigned alloc_block();
  PFC_INLINE void free_block(unsigned);
  void reserve_blocks();
  //--------------------------------------------------------------------------

  //==========================================================================
  // buddy_block
  //==========================================================================
  struct buddy_block
  {
    PFC_INLINE buddy_block()
    {
      coords.x=0;
      coords.y=0;
      free_buddy_mask=0;
      prev_idx=0;
      next_idx=0;
      parent_idx=0;
    }
    //------------------------------------------------------------------------

    atlas_coords coords;
    uint8_t free_buddy_mask;
    unsigned prev_idx, next_idx, parent_idx;
  };
  //--------------------------------------------------------------------------

  enum {max_order=4};
  enum {num_pools=1<<max_order};
  enum {block_idx_shift=max_order+2};
  enum {order_mask=(1<<max_order)-1};
  deque<buddy_block> m_blocks;
  unsigned m_atlas_width;
  unsigned m_atlas_height;
  unsigned m_num_allocs;
  unsigned m_block_free_list;
};
//----------------------------------------------------------------------------


//============================================================================
// lru_index_cache
//============================================================================
template<typename IndexType>
class lru_index_cache
{
public:
  // construction
  lru_index_cache();
  lru_index_cache(unsigned num_indices_);
  ~lru_index_cache();
  void init(unsigned num_indices_);
  void uninit();
  //--------------------------------------------------------------------------

  // cache access and refresh
  PFC_INLINE usize_t size() const;
  PFC_INLINE const IndexType *lru_indices();
  void refresh(const IndexType *indices_, unsigned num_indices_);
  //--------------------------------------------------------------------------

private:
  lru_index_cache(const lru_index_cache&); // not implemented
  void operator=(const lru_index_cache&); // not implemented
  //--------------------------------------------------------------------------

  typedef uint32_t index_flag_type_t;
  enum {num_index_flag_element_bits=sizeof(index_flag_type_t)*8};
  enum {index_flag_element_mask=num_index_flag_element_bits-1};
  enum {index_flag_element_shift=meta_log2<num_index_flag_element_bits>::res};
  array<IndexType> m_index_cache;
  array<index_flag_type_t> m_active_index_flags;
};
//----------------------------------------------------------------------------

//============================================================================
#include "memory.inl"
} // namespace pfc
#endif
