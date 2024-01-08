//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_PRIM3_ANGLE_H
#define PFC_CORE_MATH_PRIM3_ANGLE_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "prim3.h"
namespace pfc
{

// new
// subtended angle calculations
template<typename T> typename math<T>::scalar_t subtended_angle(const segment3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t subtended_angle(const tri3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t subtended_angle(const rect3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t subtended_angle(const disc3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t subtended_angle(const plane3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t sin_half_subtended_angle(const sphere3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t subtended_angle(const cylinder3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t subtended_angle(const capsule3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t subtended_angle(const cone3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t subtended_angle(const aabox3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t subtended_angle(const oobox3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t subtended_angle(const frustum3<T>&, const vec3<T> &pos_);
// solid angle calculations
template<typename T> typename math<T>::scalar_t solid_angle(const segment3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const tri3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const rect3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const disc3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const plane3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const sphere3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const cylinder3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const capsule3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const cone3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const aabox3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const oobox3<T>&, const vec3<T> &pos_);
template<typename T> typename math<T>::scalar_t solid_angle(const frustum3<T>&, const vec3<T> &pos_);
//----------------------------------------------------------------------------

//============================================================================
#include "prim3_angle.inl"
} // namespace pfc
#endif
