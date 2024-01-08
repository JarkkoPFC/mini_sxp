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
{
}
//----

mp_message_queue::~mp_message_queue()
{
}
//----

void mp_message_queue::force_clear()
{
  m_messages.force_clear();
  m_allocator.force_release();
}
//----------------------------------------------------------------------------

void mp_message_queue::exec_messages()
{
  // execute all messages in the queue
  while(message_base *msg=m_messages.pop())
    msg->exec();
  m_allocator.force_release();
}
//----------------------------------------------------------------------------
