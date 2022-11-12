//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_LINUX_CORE_GCC_H
#define PFC_LINUX_CORE_GCC_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "linux_core.h"
#include <mm_malloc.h>
namespace pfc
{

// new
#define PFC_INLINE __attribute__((always_inline))
#ifdef PFC_DEBUG
#define PFC_ABORT_FUNC() {__builtin_trap();}
#else
#define PFC_ABORT_FUNC() {exit(-1);}
#endif
#define PFC_STRICMP ::strcasecmp
#define PFC_WCSICMP ::wcscasecmp
#define PFC_STRNICMP ::strncasecmp
#define PFC_WCSNICMP ::wcsncasecmp
#define PFC_FUNCTION __PRETTY_FUNCTION__
//----------------------------------------------------------------------------


//============================================================================
// alignment macros
//============================================================================
#define PFC_ALIGN(v__) __attribute__((aligned(v__)))
#define PFC_ALIGN_CACHE __attribute__((aligned(128)))
//----------------------------------------------------------------------------


//============================================================================
// memory allocation
//============================================================================
#define PFC_ALIGNED_MALLOC(size__, align__) _mm_malloc(size__, align__)
#define PFC_ALIGNED_FREE(ptr__) _mm_free(ptr__)
//----------------------------------------------------------------------------


//============================================================================
// heap check macro
//============================================================================
#ifdef PFC_BUILDOP_HEAP_CHECKS
#define PFC_CHECK_HEAP() /*todo*/
#endif
//----------------------------------------------------------------------------

  
//============================================================================
// misc
//============================================================================
#define PFC_THREAD_VAR __thread
//----------------------------------------------------------------------------

  
//============================================================================
// fundamental data types
//============================================================================
typedef long long int64_t;
typedef unsigned long long uint64_t;
#define PFC_CONST_INT64(v__) int64_t(v__##LL)
#define PFC_CONST_UINT64(v__) uint64_t(v__##LLU)
//----------------------------------------------------------------------------


//============================================================================
// intrinsic macros
//============================================================================
#ifdef PFC_BUILDOP_INTRINSICS
#endif
//----------------------------------------------------------------------------


//============================================================================
// timing and sleeping
//============================================================================
PFC_INLINE unsigned long long get_thread_cycles()
{
  register unsigned long long tsc;
  asm volatile (".byte 0x0f, 0x31" : "=A"(tsc));
  return tsc;
}
//----

PFC_INLINE void thread_nap()
{
  sched_yield();
}
//----

PFC_INLINE void thread_sleep(ufloat_t time_)
{
  unsigned num_usecs=unsigned(time_*1000000.0f+0.5f);
  usleep(num_usecs);
}
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
