//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
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

PFC_INLINE void wait_event(mp_event &event_)
{
  PFC_VERIFY_MSG(!WaitForSingleObjectEx(event_.m_handle, INFINITE, FALSE), ("Event wait failed\r\n"));
}
//----

PFC_INLINE void wait_gate(mp_gate &gate_)
{
  PFC_VERIFY_MSG(!WaitForSingleObjectEx(gate_.m_handle, INFINITE, FALSE), ("Event wait for gate failed\r\n"));
}
//----------------------------------------------------------------------------


//============================================================================
// include compiler specific inline implementations
//============================================================================
#ifndef PFC_IGNORE_WIN_MP_COMPILER_INL
#include PFC_STR(PFC_CAT2(win_mp__,PFC_COMPILER_SRC_STR.inl))
#endif
//----------------------------------------------------------------------------
