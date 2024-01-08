//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_LINUX_CORE_H
#define PFC_LINUX_CORE_H
//----------------------------------------------------------------------------
                 

//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/config.h"
#include <cmath>
namespace pfc
{

// new
#define PFC_BIG_ENDIAN 0 /*todo*/
#define PFC_SNPRINTF snprintf
#define PFC_ALLOCA alloca
#define PFC_MKDIR(dir__) mkdir(dir__, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)
#define PFC_TIMEGM(x__) timegm(x__)
//----------------------------------------------------------------------------


//============================================================================
// fundamental data types
//============================================================================
// SIMD types
typedef float simd_float4 __attribute__ ((vector_size(16)));
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
