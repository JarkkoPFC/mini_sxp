//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// free_list
//============================================================================
usize_t free_list::capacity() const
{
  return m_capacity;
}
//----

usize_t free_list::num_allocs() const
{
  return m_num_allocs;
}
//----

void *free_list::alloc_block()
{
  // allocate item from the list
  if(!m_head)
    reserve(m_capacity+1);
  void *p=m_head;
  m_head=m_head->next;
  ++m_num_allocs;
  return p;
}
//----

void free_list::free_block(void *p_)
{
  // release item back to the free list
  PFC_ASSERT_PEDANTIC(p_!=0);
  item *p=reinterpret_cast<item*>(p_);
  p->next=m_head;
  m_head=p;
  --m_num_allocs;
}
//----------------------------------------------------------------------------


//============================================================================
// buddy_memory_manager
//============================================================================
usize_t buddy_memory_manager::pool_size() const
{
  return m_pool_size;
}
//----

usize_t buddy_memory_manager::num_allocs() const
{
  return m_num_allocs;
}
//----------------------------------------------------------------------------

usize_t buddy_memory_manager::data_offset(buddy_mem_handle_t handle_) const
{
  // return data offset for the memory handle
  usize_t handle=(usize_t)handle_;
  const buddy_block &block=m_blocks[handle>>block_idx_shift];
  return block.data_offset+(handle&1?1<<((handle>>1)&order_mask):0);
}
//----------------------------------------------------------------------------


//============================================================================
// atlas_memory_manager
//============================================================================
unsigned atlas_memory_manager::atlas_width() const
{
  return m_atlas_width;
}
//----

unsigned atlas_memory_manager::atlas_height() const
{
  return m_atlas_height;
}
//----

unsigned atlas_memory_manager::num_allocs() const
{
  return m_num_allocs;
}
//----------------------------------------------------------------------------

atlas_coords atlas_memory_manager::coords(atlas_mem_handle_t handle_) const
{
  // return coordinates for the memory handle
  const buddy_block &block=m_blocks[handle_>>block_idx_shift];
  atlas_coords coords=block.coords;
  unsigned order=(handle_>>2)&order_mask;
  coords.x+=(handle_&1)<<order;
  coords.y+=(handle_&2)<<(order-1);
  return coords;
}
//----------------------------------------------------------------------------


//============================================================================
// lru_index_cache
//============================================================================
template<typename IndexType>
lru_index_cache<IndexType>::lru_index_cache()
{
}
//----

template<typename IndexType>
lru_index_cache<IndexType>::lru_index_cache(unsigned num_indices_)
{
  init(num_indices_);
}
//----

template<typename IndexType>
lru_index_cache<IndexType>::~lru_index_cache()
{
}
//----

template<typename IndexType>
void lru_index_cache<IndexType>::init(unsigned num_indices_)
{
  // initialize the cache with given number of indices
  PFC_ASSERT_MSG(m_index_cache.size()==0, ("LRU index cache has already been initialized\r\n"));
  PFC_ASSERT_MSG(num_indices_, ("Number of indices not specified\r\n"));
  m_index_cache.resize(num_indices_);
  m_active_index_flags.resize((num_indices_+index_flag_element_mask)/num_index_flag_element_bits);
  IndexType *index_cache=m_index_cache.data();
  for(unsigned i=0; i<num_indices_; ++i)
    index_cache[i]=IndexType(i);
}
//----

template<typename IndexType>
void lru_index_cache<IndexType>::uninit()
{
  m_index_cache.clear();
  m_active_index_flags.clear();
}
//----------------------------------------------------------------------------

template<typename IndexType>
usize_t lru_index_cache<IndexType>::size() const
{
  return m_index_cache.size();
}
//----

template<typename IndexType>
const IndexType *lru_index_cache<IndexType>::lru_indices()
{
  return m_index_cache.data();
}
//----

template<typename IndexType>
void lru_index_cache<IndexType>::refresh(const IndexType *indices_, unsigned num_indices_)
{
  // flag active indices
  unsigned num_cache_indices=unsigned(m_index_cache.size());
  IndexType *index_cache=m_index_cache.data();
  PFC_ASSERT_MSG(num_indices_<num_cache_indices, ("Trying to refresh more LRU cache indices than are available in the cache\r\n"));
  PFC_ASSERT_MSG(indices_+num_indices_<=index_cache || indices_>=index_cache+num_cache_indices, ("LRU cache refresh indices can't refer to the cache\r\n"));
  index_flag_type_t *active_index_flags=m_active_index_flags.data();
  mem_zero(active_index_flags, m_active_index_flags.size()*sizeof(*active_index_flags));
  for(unsigned i=0; i<num_indices_; ++i)
  {
    uint16_t idx=indices_[i];
    PFC_ASSERT_PEDANTIC(idx<num_cache_indices);
    unsigned offs=idx>>index_flag_element_shift;
    index_flag_type_t bitmask=1<<(idx&index_flag_element_mask);
    PFC_ASSERT_PEDANTIC_MSG(!(active_index_flags[offs]&bitmask), ("Duplicate index entry (%i) for LRU cache update\r\n", idx));
    active_index_flags[offs]|=bitmask;
  }

  // move unused indices to the head and used indices to the tail of the cache
  unsigned inactive_index_offs=0;
  for(unsigned i=0; i<num_cache_indices; ++i)
  {
    IndexType idx=index_cache[i];
    if(!(active_index_flags[idx>>index_flag_element_shift]&(1<<(idx&index_flag_element_mask))))
      index_cache[inactive_index_offs++]=idx;
  }
  mem_copy(index_cache+num_cache_indices-num_indices_, indices_, num_indices_*sizeof(*index_cache));
}
//----------------------------------------------------------------------------
