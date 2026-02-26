//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MP_MSG_QUEUE_H
#define PFC_CORE_MP_MSG_QUEUE_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "mp_memory.h"
namespace pfc
{

// new
class message_base;
class mp_message_queue;
//----------------------------------------------------------------------------


//============================================================================
// message_base
//============================================================================
class message_base
{
public:
  // construction
  PFC_INLINE message_base();
  PFC_INLINE virtual ~message_base()=0;
  //--------------------------------------------------------------------------

private:
  friend class mp_message_queue;
  message_base *m_next;
};
//----------------------------------------------------------------------------


//============================================================================
// mp_message_queue
//============================================================================
class mp_message_queue
{
public:
  // construction
  mp_message_queue();
  ~mp_message_queue();
  //--------------------------------------------------------------------------

  // message handling
  template<class T, typename... Params> void queue_message(Params&&...);
  void exec_messages();
  //--------------------------------------------------------------------------

private:
  mp_message_queue(const mp_message_queue&); // not implemented
  void operator=(const mp_message_queue&); // not implemented
  //--------------------------------------------------------------------------

  volatile unsigned m_active_allocator_idx;
  volatile unsigned m_num_queuing;
  mp_sequential_memory_allocator m_allocator[2];
  mp_fifo_queue<message_base, &message_base::m_next> m_messages;
};
//----------------------------------------------------------------------------

//============================================================================
#include "mp_msg_queue.inl"
} // namespace pfc
#endif
