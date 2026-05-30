//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// mp_event
//============================================================================
void mp_event::trigger()
{
  SetEvent(m_handle);
}
//----------------------------------------------------------------------------


//============================================================================
// mp_gate
//============================================================================
void mp_gate::open()
{
  SetEvent(m_handle);
}
//----

void mp_gate::close()
{
  ResetEvent(m_handle);
}
//----------------------------------------------------------------------------


//============================================================================
// mp_critical_section
//============================================================================
void mp_critical_section::enter()
{
  EnterCriticalSection(&m_handle);
}
//----

void mp_critical_section::leave()
{
  LeaveCriticalSection(&m_handle);
}
//----------------------------------------------------------------------------


//============================================================================
// synchronization functions
//============================================================================
PFC_INLINE int wait_thread(mp_thread &thread_)
{
  PFC_VERIFY_MSG(!WaitForSingleObjectEx(thread_.m_handle, INFINITE, FALSE), ("Thread wait failed\r\n"));
  DWORD code;
  PFC_VERIFY_MSG(GetExitCodeThread(thread_.m_handle, &code), ("Thread exit code query failed\r\n"));
  return int(code);
}
//----

PFC_INLINE bool wait_event(mp_event &event_, float timeout_secs_)
{
  PFC_ASSERT(timeout_secs_>=0.0f);
  DWORD timeout_ms=timeout_secs_>0.0f?DWORD(timeout_secs_*1000.0f+0.5f):INFINITE;
  DWORD res=WaitForSingleObjectEx(event_.m_handle, timeout_ms, FALSE);
  PFC_VERIFY_MSG(timeout_secs_>0.0f || res==WAIT_OBJECT_0, ("Event wait failed\r\n"));
  return res==WAIT_OBJECT_0;
}
//----

PFC_INLINE bool wait_gate(mp_gate &gate_, float timeout_secs_)
{
  PFC_ASSERT(timeout_secs_>=0.0f);
  DWORD timeout_ms=timeout_secs_>0.0f?DWORD(timeout_secs_*1000.0f+0.5f):INFINITE;
  DWORD res=WaitForSingleObjectEx(gate_.m_handle, timeout_ms, FALSE);
  PFC_VERIFY_MSG(timeout_secs_>0.0f || res==WAIT_OBJECT_0, ("Gate wait failed\r\n"));
  return res==WAIT_OBJECT_0;
}
//----------------------------------------------------------------------------


//============================================================================
// include compiler specific inline implementations
//============================================================================
#ifndef PFC_IGNORE_WIN_MP_COMPILER_INL
#include PFC_STR(PFC_CAT2(win_mp__,PFC_COMPILER_SRC_STR.inl))
#endif
//----------------------------------------------------------------------------
