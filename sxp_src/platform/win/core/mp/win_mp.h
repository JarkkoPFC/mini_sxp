//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_WIN_CORE_MP_H
#define PFC_WIN_CORE_MP_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
#include "sxp_src/core/core.h"
namespace pfc
{

// new
typedef HANDLE mp_thread_handle_t;
typedef HANDLE mp_event_handle_t;
typedef HANDLE mp_gate_handle_t;
typedef CRITICAL_SECTION mp_critical_section_handle_t;
#define PFC_THREAD_PROC DWORD WINAPI thread_proc(void*)
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
