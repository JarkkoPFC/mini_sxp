//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
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
DWORD WINAPI mp_thread::thread_proc(void *thread_)
{
  mp_thread *t=static_cast<mp_thread*>(thread_);
  int res=t->m_func();
  ExitThread(res);
}
//----------------------------------------------------------------------------

mp_thread::mp_thread()
{
  m_handle=0;
}
//----

mp_thread::mp_thread(const functor<int()> &f_, bool suspended_, int hw_thread_idx_, usize_t stack_size_)
{
  m_handle=0;
  init(f_, suspended_, hw_thread_idx_, stack_size_);
}
//----

void mp_thread::init(const functor<int()> &f_, bool suspended_, int hw_thread_idx_, usize_t stack_size_)
{
  PFC_ASSERT_MSG(!m_handle, ("Thread has already been initialized\r\n"));
  m_func=f_;
  m_handle=CreateThread(NULL, stack_size_, &thread_proc, this, suspended_?CREATE_SUSPENDED:0, NULL);
  PFC_CHECK_MSG(m_handle, ("Thread creation failed\r\n"));
  if(hw_thread_idx_>=0)
    SetThreadIdealProcessor(m_handle, hw_thread_idx_);
}
//----

mp_thread::~mp_thread()
{
  WaitForSingleObjectEx(m_handle, INFINITE, FALSE);
  CloseHandle(m_handle);
}
//----

void mp_thread::start()
{
  PFC_VERIFY_MSG(ResumeThread(m_handle)==1, ("Resuming thread failed\r\n"));
}
//----

void mp_thread::set_priority(e_thread_priority priority_)
{
  switch(priority_)
  {
    case threadpriority_idle:     SetThreadPriority(m_handle, THREAD_PRIORITY_IDLE); break;
    case threadpriority_lower:    SetThreadPriority(m_handle, THREAD_PRIORITY_LOWEST); break;
    case threadpriority_low:      SetThreadPriority(m_handle, THREAD_PRIORITY_BELOW_NORMAL); break;
    case threadpriority_normal:   SetThreadPriority(m_handle, THREAD_PRIORITY_NORMAL); break;
    case threadpriority_high:     SetThreadPriority(m_handle, THREAD_PRIORITY_ABOVE_NORMAL); break;
    case threadpriority_higher:   SetThreadPriority(m_handle, THREAD_PRIORITY_HIGHEST); break;
    case threadpriority_realtime: SetThreadPriority(m_handle, THREAD_PRIORITY_TIME_CRITICAL); break;
    default: PFC_ERROR("Unknown thread priority\r\n");
  }
}
//----------------------------------------------------------------------------

bool mp_thread::is_terminated() const
{
  return !m_handle || WaitForSingleObject(m_handle, 0)==WAIT_OBJECT_0;
}
//----------------------------------------------------------------------------


//============================================================================
// mp_event
//============================================================================
mp_event::mp_event()
{
  m_handle=CreateEventEx(NULL, NULL, 0, DELETE|SYNCHRONIZE|EVENT_MODIFY_STATE);
  PFC_CHECK_MSG(m_handle!=0, ("Event creation failed\r\n"));
}
//----

mp_event::~mp_event()
{
  CloseHandle(m_handle);
}
//----------------------------------------------------------------------------


//============================================================================
// mp_gate
//============================================================================
mp_gate::mp_gate()
{
  m_handle=CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, DELETE|SYNCHRONIZE|EVENT_MODIFY_STATE);
  PFC_CHECK_MSG(m_handle!=0, ("Event creation for gate failed\r\n"));
}
//----

mp_gate::~mp_gate()
{
  CloseHandle(m_handle);
}
//----------------------------------------------------------------------------


//============================================================================
// mp_critical_section
//============================================================================
mp_critical_section::mp_critical_section()
{
  InitializeCriticalSectionEx(&m_handle, 1000, CRITICAL_SECTION_NO_DEBUG_INFO);
}
//----

mp_critical_section::~mp_critical_section()
{
  DeleteCriticalSection(&m_handle);
}
//----------------------------------------------------------------------------


//============================================================================
// misc
//============================================================================
void pfc::set_hardware_thread(unsigned hw_thread_idx_)
{
  // set calling thread to run on given hardware thread
  SetThreadIdealProcessor(GetCurrentThread(), hw_thread_idx_);
}
//----

unsigned pfc::num_hardware_threads()
{
  // return number of hardware threads
  SYSTEM_INFO info;
  GetNativeSystemInfo(&info);
  return info.dwNumberOfProcessors;
}
//----

void pfc::set_process_priority(e_process_priority priority_)
{
  HANDLE phandle=GetCurrentProcess();
  switch(priority_)
  {
    case threadpriority_idle:     SetPriorityClass(phandle, IDLE_PRIORITY_CLASS); break;
    case threadpriority_lower:    SetPriorityClass(phandle, BELOW_NORMAL_PRIORITY_CLASS); break; // note: no "lowest" class for processes
    case threadpriority_low:      SetPriorityClass(phandle, BELOW_NORMAL_PRIORITY_CLASS); break;
    case threadpriority_normal:   SetPriorityClass(phandle, NORMAL_PRIORITY_CLASS); break;
    case threadpriority_high:     SetPriorityClass(phandle, ABOVE_NORMAL_PRIORITY_CLASS); break;
    case threadpriority_higher:   SetPriorityClass(phandle, HIGH_PRIORITY_CLASS); break;
    case threadpriority_realtime: SetPriorityClass(phandle, REALTIME_PRIORITY_CLASS); break;
    default: PFC_ERROR("Unknown process priority\r\n");
  }
}
//----------------------------------------------------------------------------
