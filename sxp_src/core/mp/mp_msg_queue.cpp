//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "mp_msg_queue.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// mp_message_queue
//============================================================================
mp_message_queue::mp_message_queue()
  :m_active_allocator_idx(0)
  ,m_num_queuing(0)
{
}
//----

mp_message_queue::~mp_message_queue()
{
}
//----------------------------------------------------------------------------

void mp_message_queue::exec_messages()
{
  // execute all queued messages and release allocator for retired epoch
  unsigned alloc_idx=m_active_allocator_idx;
  atom_xor(m_active_allocator_idx, 1u);
  do 
  {
    while(message_base *msg=m_messages.pop())
      msg->~message_base();
  } while(atom_read(m_num_queuing));
  while(message_base *msg=m_messages.pop())
    msg->~message_base();
  m_allocator[alloc_idx].force_release();
}
//----------------------------------------------------------------------------
