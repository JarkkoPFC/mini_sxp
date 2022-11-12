//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// mp_free_list
//============================================================================
usize_t mp_free_list::capacity() const
{
  return m_capacity;
}
//----

usize_t mp_free_list::num_pending_allocs() const
{
  return m_num_allocs;
}
//----

void *mp_free_list::alloc_block()
{
  while(true)
  {
    // allocate item from free list
    if(item *i=m_queue.pop())
    {
      atom_inc(m_num_allocs);
      return i;
    }
    reserve(m_num_allocs+1);
  }
}
//----

void mp_free_list::free_block(void *p_)
{
  // release item back to the free list
  PFC_ASSERT_PEDANTIC(p_!=0);
  m_queue.push(*reinterpret_cast<item*>(p_));
  atom_dec(m_num_allocs);
}
//----------------------------------------------------------------------------
