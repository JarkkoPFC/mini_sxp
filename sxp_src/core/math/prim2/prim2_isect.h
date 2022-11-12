//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_PRIM2_ISECT_H
#define PFC_CORE_MATH_PRIM2_ISECT_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "prim2.h"
namespace pfc
{

// new
template<typename T> bool isect(const point2<T>&, const circle2<T>&);
template<typename T> bool isect(const point2<T>&, const tri2<T>&);
template<typename T> bool isect(const point2<T>&, const aarect2<T>&);
template<typename T> bool isect(const point2<T>&, const oorect2<T>&);
template<typename T> bool isect(const line2<T>&, const ray2<T>&);
template<typename T> bool isect(const line2<T>&, const segment2<T>&);
template<typename T> bool isect(const line2<T>&, const segment2<T>&, typename math<T>::scalar_t &t_); // if intersecting, returns t_ of the segment at the intersection;
template<typename T> bool isect(const line2<T>&, const circle2<T>&);
template<typename T> bool isect(const line2<T>&, const tri2<T>&);
template<typename T> bool isect(const line2<T>&, const aarect2<T>&);
template<typename T> bool isect(const line2<T>&, const oorect2<T>&);
template<typename T> bool isect(const ray2<T>&, const ray2<T>&);
template<typename T> bool isect(const ray2<T>&, const segment2<T>&);
template<typename T> bool isect(const ray2<T>&, const circle2<T>&);
template<typename T> bool isect(const ray2<T>&, const tri2<T>&);
template<typename T> bool isect(const ray2<T>&, const aarect2<T>&);
template<typename T> bool isect(const ray2<T>&, const oorect2<T>&);
template<typename T> bool isect(const segment2<T>&, const segment2<T>&);
template<typename T> bool isect(const segment2<T>&, const circle2<T>&);
template<typename T> bool isect(const segment2<T>&, const tri2<T>&);
template<typename T> bool isect(const segment2<T>&, const aarect2<T>&);
template<typename T> bool isect(const segment2<T>&, const oorect2<T>&);
template<typename T> bool isect(const circle2<T>&, const circle2<T>&);
template<typename T> bool isect(const circle2<T>&, const tri2<T>&);
template<typename T> bool isect(const circle2<T>&, const aarect2<T>&);
template<typename T> bool isect(const circle2<T>&, const oorect2<T>&);
template<typename T> bool isect(const tri2<T>&, const tri2<T>&);
template<typename T> bool isect(const tri2<T>&, const aarect2<T>&);
template<typename T> bool isect(const tri2<T>&, const oorect2<T>&);
template<typename T> bool isect(const aarect2<T>&, const aarect2<T>&);
template<typename T> bool isect(const aarect2<T>&, const oorect2<T>&);
template<typename T> bool isect(const oorect2<T>&, const oorect2<T>&);
//----------------------------------------------------------------------------

//============================================================================
#include "prim2_isect.inl"
} // namespace pfc
#endif
