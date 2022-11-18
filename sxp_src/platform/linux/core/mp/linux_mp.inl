//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// include compiler specific inline implementations
//============================================================================
#include PFC_STR(PFC_CAT2(linux_mp__,PFC_COMPILER_SRC_STR.inl))
//----------------------------------------------------------------------------


//============================================================================
// mp_event
//============================================================================
void mp_event::trigger()
{
  PFC_VERIFY_MSG(pthread_cond_signal(&m_handle.cond)==0,
                 ("Condition variable signaling for the event trigger failed"));
}
//----------------------------------------------------------------------------


//============================================================================
// mp_gate
//============================================================================
void mp_gate::open()
{
  m_handle.is_open=true;
  PFC_VERIFY_MSG(pthread_cond_broadcast(&m_handle.cond)==0,
                 ("Condition variable broadcast for the gate open failed"));
}
//----

void mp_gate::close()
{
  m_handle.is_open=false;
}
//----------------------------------------------------------------------------


//============================================================================
// mp_critical_section
//============================================================================
void mp_critical_section::enter()
{
  PFC_VERIFY_MSG(pthread_mutex_lock(&m_handle)==0, ("Entering critical section failed"));
}
//----

void mp_critical_section::leave()
{
  PFC_VERIFY_MSG(pthread_mutex_unlock(&m_handle)==0, ("Leaving critical section failed"));
}
//----------------------------------------------------------------------------


//============================================================================
// synchronization functions
//============================================================================
PFC_INLINE int wait_thread(mp_thread &thread_)
{
  void *res;
  PFC_VERIFY_MSG(pthread_join(thread_.m_handle.thread_id, &res)==0,
                 ("Thread join while waiting for the thread failed"));
  return res!=PTHREAD_CANCELED?*(int*)res:0;
}
//----

PFC_INLINE void wait_event(mp_event &event_)
{
  PFC_VERIFY_MSG(pthread_cond_wait(&event_.m_handle.cond, &event_.m_handle.mutex)==0,
                 ("Waiting for the event failed"));
}
//----

PFC_INLINE void wait_gate(mp_gate &gate_)
{
  if(!gate_.m_handle.is_open)
  {
    PFC_VERIFY_MSG(pthread_mutex_lock(&gate_.m_handle.mutex)==0,
                   ("Mutex lock for waiting for the gate failed"));
    PFC_VERIFY_MSG(pthread_cond_wait(&gate_.m_handle.cond, &gate_.m_handle.mutex)==0,
                   ("Waiting for the gate failed"));
    PFC_VERIFY_MSG(pthread_mutex_unlock(&gate_.m_handle.mutex)==0,
                   ("Mutex unlock for waiting for the gate failed"));
  }
}
//----------------------------------------------------------------------------
