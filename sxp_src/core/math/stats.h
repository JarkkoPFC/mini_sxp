//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_STATS_H
#define PFC_CORE_MATH_STATS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "math.h"
namespace pfc
{

// new
template<typename T> T inv_standard_normal_cdf(T p_);
template<typename T> T inv_normal_cdf(T p_, T mean_, T deviation_);
//----------------------------------------------------------------------------

//============================================================================
#include "stats.inl"
} // namespace pfc
#endif
