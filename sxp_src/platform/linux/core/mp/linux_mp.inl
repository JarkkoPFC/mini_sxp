//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
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
  // store one pending auto-reset wake before signaling a waiter
  PFC_VERIFY_MSG(pthread_mutex_lock(&m_handle.mutex)==0,
                 ("Mutex lock for the event trigger failed"));
  m_handle.is_triggered=true;
  PFC_VERIFY_MSG(pthread_cond_signal(&m_handle.cond)==0,
                 ("Condition variable signaling for the event trigger failed"));
  PFC_VERIFY_MSG(pthread_mutex_unlock(&m_handle.mutex)==0,
                 ("Mutex unlock for the event trigger failed"));
}
//----------------------------------------------------------------------------


//============================================================================
// mp_gate
//============================================================================
void mp_gate::open()
{
  // publish the open state under the gate mutex before waking waiters
  PFC_VERIFY_MSG(pthread_mutex_lock(&m_handle.mutex)==0,
                 ("Mutex lock for the gate open failed"));
  m_handle.is_open=true;
  PFC_VERIFY_MSG(pthread_cond_broadcast(&m_handle.cond)==0,
                 ("Condition variable broadcast for the gate open failed"));
  PFC_VERIFY_MSG(pthread_mutex_unlock(&m_handle.mutex)==0,
                 ("Mutex unlock for the gate open failed"));
}
//----

void mp_gate::close()
{
  // publish the closed state under the same mutex used by waiters
  PFC_VERIFY_MSG(pthread_mutex_lock(&m_handle.mutex)==0,
                 ("Mutex lock for the gate close failed"));
  m_handle.is_open=false;
  PFC_VERIFY_MSG(pthread_mutex_unlock(&m_handle.mutex)==0,
                 ("Mutex unlock for the gate close failed"));
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

PFC_INLINE bool wait_event(mp_event &event_, float timeout_secs_)
{
  PFC_ASSERT(timeout_secs_>=0.0f);

  // wait until one pending event trigger is available and consume it before returning
  PFC_VERIFY_MSG(pthread_mutex_lock(&event_.m_handle.mutex)==0,
                 ("Mutex lock for waiting for the event failed"));
  if(timeout_secs_>0.0f)
  {
    struct timespec ts;
    PFC_VERIFY_MSG(clock_gettime(CLOCK_MONOTONIC, &ts)==0,
                   ("Monotonic clock query for the event wait failed"));
    int64_t timeout_ns=int64_t(timeout_secs_*1000000000.0+0.5);
    ts.tv_sec+=time_t(timeout_ns/1000000000ll);
    ts.tv_nsec+=long(timeout_ns%1000000000ll);
    if(ts.tv_nsec>=1000000000) {ts.tv_sec++; ts.tv_nsec-=1000000000;}
    while(!event_.m_handle.is_triggered)
    {
      int wait_res=pthread_cond_timedwait(&event_.m_handle.cond, &event_.m_handle.mutex, &ts);
      if(wait_res==ETIMEDOUT)
      {
        PFC_VERIFY_MSG(pthread_mutex_unlock(&event_.m_handle.mutex)==0,
                       ("Mutex unlock after timed out event wait failed"));
        return false;
      }
      PFC_VERIFY_MSG(wait_res==0, ("Timed wait for the event failed"));
    }
  }
  else
  {
    while(!event_.m_handle.is_triggered)
      PFC_VERIFY_MSG(pthread_cond_wait(&event_.m_handle.cond, &event_.m_handle.mutex)==0,
                     ("Waiting for the event failed"));
  }
  event_.m_handle.is_triggered=false;
  PFC_VERIFY_MSG(pthread_mutex_unlock(&event_.m_handle.mutex)==0,
                 ("Mutex unlock for the event wait failed"));
  return true;
}
//----

PFC_INLINE bool wait_gate(mp_gate &gate_, float timeout_secs_)
{
  PFC_ASSERT(timeout_secs_>=0.0f);

  // wait until the manual-reset gate state becomes open
  PFC_VERIFY_MSG(pthread_mutex_lock(&gate_.m_handle.mutex)==0,
                 ("Mutex lock for waiting for the gate failed"));
  if(timeout_secs_>0.0f)
  {
    struct timespec ts;
    PFC_VERIFY_MSG(clock_gettime(CLOCK_MONOTONIC, &ts)==0,
                   ("Monotonic clock query for the gate wait failed"));
    int64_t timeout_ns=int64_t(timeout_secs_*1000000000.0+0.5);
    ts.tv_sec+=time_t(timeout_ns/1000000000ll);
    ts.tv_nsec+=long(timeout_ns%1000000000ll);
    if(ts.tv_nsec>=1000000000) {ts.tv_sec++; ts.tv_nsec-=1000000000;}
    while(!gate_.m_handle.is_open)
    {
      int wait_res=pthread_cond_timedwait(&gate_.m_handle.cond, &gate_.m_handle.mutex, &ts);
      if(wait_res==ETIMEDOUT)
      {
        PFC_VERIFY_MSG(pthread_mutex_unlock(&gate_.m_handle.mutex)==0,
                       ("Mutex unlock after timed out gate wait failed"));
        return false;
      }
      PFC_VERIFY_MSG(wait_res==0, ("Timed wait for the gate failed"));
    }
  }
  else
  {
    while(!gate_.m_handle.is_open)
      PFC_VERIFY_MSG(pthread_cond_wait(&gate_.m_handle.cond, &gate_.m_handle.mutex)==0,
                     ("Waiting for the gate failed"));
  }
  PFC_VERIFY_MSG(pthread_mutex_unlock(&gate_.m_handle.mutex)==0,
                 ("Mutex unlock for waiting for the gate failed"));
  return true;
}
//----------------------------------------------------------------------------
