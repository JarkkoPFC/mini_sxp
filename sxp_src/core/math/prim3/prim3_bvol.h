//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_PRIM3_BVOL_H
#define PFC_CORE_MATH_PRIM3_BVOL_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "prim3.h"
namespace pfc
{

// new
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const segment3<T>&);
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const tri3<T>&);
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const rect3<T>&);
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const disc3<T>&);
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const sphere3<T>&);
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const cylinder3<T>&);
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const capsule3<T>&);
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const cone3<T>&);
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const aabox3<T>&);
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const oobox3<T>&);
template<typename T> PFC_INLINE sphere3<T> bounding_sphere3(const frustum3<T>&);
//----------------------------------------------------------------------------

//============================================================================
#include "prim3_bvol.inl"
} // namespace pfc
#endif
