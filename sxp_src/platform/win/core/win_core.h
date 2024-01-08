//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_WIN_CORE_H
#define PFC_WIN_CORE_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/config.h"
#include <xmmintrin.h>
#include <cmath>
#include <stdlib.h>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
namespace pfc
{

// new
#define PFC_BIG_ENDIAN 0
#define PFC_SNPRINTF _snprintf
#define PFC_ALLOCA _alloca
#define PFC_MKDIR(dir__) mkdir(dir__)
#define PFC_TIMEGM(x__) _mkgmtime(x__)
typedef struct HWND__ *graphics_window_handle_t;
//----------------------------------------------------------------------------


//============================================================================
// fundamental data types
//============================================================================
// SIMD types
typedef __m128 simd_float4;
//----------------------------------------------------------------------------


//============================================================================
// sleeping
//============================================================================
__forceinline void thread_nap()
{
  SleepEx(0, FALSE);
}
//----

__forceinline void thread_sleep(float time_)
{
  unsigned num_msecs=unsigned(time_*1000.0f+0.5f);
  SleepEx(num_msecs, FALSE);
}
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
