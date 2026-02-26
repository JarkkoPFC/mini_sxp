//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// message_base
//============================================================================
message_base::message_base()
{
  m_next=0;
}
//----------------------------------------------------------------------------

message_base::~message_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// mp_message_queue
//============================================================================
template<class T, typename... Params>
void mp_message_queue::queue_message(Params&&... params_)
{
  // queue message using currently active allocator
  atom_inc(m_num_queuing);
  unsigned alloc_idx=atom_read(m_active_allocator_idx);
  T *msg=(T*)m_allocator[alloc_idx].alloc(sizeof(T), meta_alignof<T>::res);
  PFC_PNEW(msg)T(static_cast<Params&&>(params_)...);
  m_messages.push(*msg);
  atom_dec(m_num_queuing);
}
//----------------------------------------------------------------------------
