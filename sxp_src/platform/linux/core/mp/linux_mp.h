//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_LINUX_CORE_MP_H
#define PFC_LINUX_CORE_MP_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
#include "sxp_src/core/core.h"
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
namespace pfc
{

// new
struct mp_thread_handle_t {pthread_t thread_id; pthread_attr_t thread_attr; bool is_running;};
struct mp_event_handle_t {pthread_cond_t cond; pthread_mutex_t mutex;};
struct mp_gate_handle_t {pthread_cond_t cond; pthread_mutex_t mutex; volatile bool is_open;};
typedef pthread_mutex_t mp_critical_section_handle_t;
#define PFC_THREAD_PROC void *thread_proc(void*)
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
