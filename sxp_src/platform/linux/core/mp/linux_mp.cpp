//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core/mp/mp.h"
#include "sxp_src/core/math/bit_math.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// mp_thread
//============================================================================
static void thread_cleanup_proc(void *thread_)
{
  *(bool*)thread_=false;
}
//----

void *mp_thread::thread_proc(void *thread_)
{
  mp_thread *t=static_cast<mp_thread*>(thread_);
  usize_t res;
  pthread_cleanup_push(&thread_cleanup_proc, &t->m_handle.is_running);
  res=t->m_func();
  pthread_cleanup_pop(0);
  pthread_exit((void*)res);
}
//----------------------------------------------------------------------------

mp_thread::mp_thread()
{
  m_handle.thread_id=0;
  m_handle.is_running=false;
  PFC_VERIFY_MSG(pthread_attr_init(&m_handle.thread_attr)==0, ("Unable to initialize thread attributes"));
}
//----

mp_thread::mp_thread(const functor<int()> &f_, bool suspended_, int hw_thread_idx_, usize_t stack_size_)
{
  m_handle.thread_id=0;
  m_handle.is_running=false;
  PFC_VERIFY_MSG(pthread_attr_init(&m_handle.thread_attr)==0, ("Unable to initialize thread attributes"));
  init(f_, suspended_, hw_thread_idx_, stack_size_);
}
//----

void mp_thread::init(const functor<int()> &f_, bool suspended_, int hw_thread_idx_, usize_t stack_size_)
{
  // setup thread attributes
  PFC_ASSERT_MSG(!m_handle.thread_id, ("Thread has already been initialized"));
  if(stack_size_)
    PFC_VERIFY_MSG(pthread_attr_setstacksize(&m_handle.thread_attr, stack_size_)==0, ("Unable to set thread stack size to %i bytes", stack_size_));
  if(hw_thread_idx_!=-1)
  {
    // assign thread to run on given HW thread
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(hw_thread_idx_, &cpuset);
    PFC_VERIFY_MSG(pthread_attr_setaffinity_np(&m_handle.thread_attr, sizeof(cpu_set_t), &cpuset)==0, ("Unable to assign thread to CPU HW thread %i", hw_thread_idx_));
  }

  // start thread if not requested in suspended state
  m_func=f_;
  if(!suspended_)
    start();
}
//----

mp_thread::~mp_thread()
{
  // join thread and get result
  pthread_join(m_handle.thread_id, 0);
  PFC_VERIFY_MSG(pthread_attr_destroy(&m_handle.thread_attr)==0, ("Destroying thread attributes failed"));
}
//----

void mp_thread::start()
{
  // start the thread
  PFC_ASSERT_MSG(m_handle.thread_id==0, ("Thread is already running"));
  m_handle.is_running=true;
  PFC_VERIFY_MSG(pthread_create(&m_handle.thread_id, &m_handle.thread_attr, &thread_proc, this)==0, ("Thread creation failed"));
}
//----------------------------------------------------------------------------

bool mp_thread::is_terminated() const
{
  if(!m_handle.thread_id || m_handle.is_running)
    return false;
  pthread_join(m_handle.thread_id, 0);
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// mp_event
//============================================================================
mp_event::mp_event()
{
  PFC_VERIFY_MSG(pthread_cond_init(&m_handle.cond, 0)==0, ("Condition variable creation for the event failed"));
  PFC_VERIFY_MSG(pthread_mutex_init(&m_handle.mutex, 0)==0, ("Mutex creation for the event failed"));
  PFC_VERIFY_MSG(pthread_mutex_lock(&m_handle.mutex)==0, ("Mutex locking upon the event creation failed"));
}
//----

mp_event::~mp_event()
{
  PFC_VERIFY_MSG(pthread_cond_destroy(&m_handle.cond)==0, ("Condition variable destruction for the event failed"));
  PFC_VERIFY_MSG(pthread_mutex_destroy(&m_handle.mutex)==0, ("Mutex destruction for the event failed"));
}
//----------------------------------------------------------------------------


//============================================================================
// mp_gate
//============================================================================
mp_gate::mp_gate()
{
  PFC_VERIFY_MSG(pthread_cond_init(&m_handle.cond, 0)==0, ("Condition variable creation for the gate failed"));
  PFC_VERIFY_MSG(pthread_mutex_init(&m_handle.mutex, 0)==0, ("Mutex creation for the gate failed"));
  m_handle.is_open=false;
}
//----

mp_gate::~mp_gate()
{
  PFC_VERIFY_MSG(pthread_cond_destroy(&m_handle.cond)==0, ("Condition variable destruction for the gate failed"));
  PFC_VERIFY_MSG(pthread_mutex_destroy(&m_handle.mutex)==0, ("Mutex destruction for the gate failed"));
}
//----------------------------------------------------------------------------


//============================================================================
// mp_critical_section
//============================================================================
mp_critical_section::mp_critical_section()
{
  PFC_VERIFY_MSG(pthread_mutex_init(&m_handle, 0)==0, ("Critical section creation failed"));
}
//----

mp_critical_section::~mp_critical_section()
{
  PFC_VERIFY_MSG(pthread_mutex_destroy(&m_handle)==0, ("Critical section destruction failed"));
}
//----------------------------------------------------------------------------


//============================================================================
// misc
//============================================================================
void pfc::set_hardware_thread(unsigned hw_thread_idx_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
}
//----

unsigned pfc::num_hardware_threads()
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----------------------------------------------------------------------------
