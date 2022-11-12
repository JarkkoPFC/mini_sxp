//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_PRIM3_DIST_H
#define PFC_CORE_MATH_PRIM3_DIST_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "prim3.h"
namespace pfc
{

// new
template<typename T> typename math<T>::scalar_t dist2(const point3<T>&, const point3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const point3<T>&, const line3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const point3<T>&, const ray3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const point3<T>&, const segment3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const point3<T>&, const tri3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const point3<T>&, const rect3<T>&);
template<typename T> typename math<T>::scalar_t dist (const point3<T>&, const disc3<T>&);
template<typename T> typename math<T>::scalar_t dist (const point3<T>&, const plane3<T>&);     // note: negative behind the plane
template<typename T> typename math<T>::scalar_t dist (const point3<T>&, const sphere3<T>&);    // note: negative inside the sphere
template<typename T> typename math<T>::scalar_t dist2(const point3<T>&, const cylinder3<T>&);
template<typename T> typename math<T>::scalar_t dist (const point3<T>&, const capsule3<T>&);   // note: negative inside the capsule
template<typename T> typename math<T>::scalar_t dist (const point3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const point3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const point3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const point3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist (const line3<T>&, const line3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const line3<T>&, const ray3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const line3<T>&, const segment3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const line3<T>&, const tri3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const line3<T>&, const rect3<T>&);
template<typename T> typename math<T>::scalar_t dist (const line3<T>&, const disc3<T>&);
template<typename T> typename math<T>::scalar_t dist (const line3<T>&, const sphere3<T>&);     // note: negative if line intersects the sphere
template<typename T> typename math<T>::scalar_t dist2(const line3<T>&, const cylinder3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const line3<T>&, const capsule3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const line3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const line3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const line3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const line3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist (const ray3<T>&, const ray3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const ray3<T>&, const segment3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const ray3<T>&, const tri3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const ray3<T>&, const rect3<T>&);
template<typename T> typename math<T>::scalar_t dist (const ray3<T>&, const disc3<T>&);
template<typename T> typename math<T>::scalar_t dist (const ray3<T>&, const sphere3<T>&);     // note: negative if ray intersects the sphere
template<typename T> typename math<T>::scalar_t dist2(const ray3<T>&, const cylinder3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const ray3<T>&, const capsule3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const ray3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const ray3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const ray3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const ray3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const segment3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const tri3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const rect3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const disc3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const plane3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const sphere3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const cylinder3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const capsule3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const segment3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const tri3<T>&, const tri3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const tri3<T>&, const rect3<T>&);
template<typename T> typename math<T>::scalar_t dist (const tri3<T>&, const disc3<T>&);
template<typename T> typename math<T>::scalar_t dist (const tri3<T>&, const plane3<T>&);       // note: negative result indicates the depth of negative half-space penetration of the plane
template<typename T> typename math<T>::scalar_t dist2(const tri3<T>&, const sphere3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const tri3<T>&, const cylinder3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const tri3<T>&, const capsule3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const tri3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const tri3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const tri3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const tri3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const rect3<T>&, const rect3<T>&);
template<typename T> typename math<T>::scalar_t dist (const rect3<T>&, const disc3<T>&);
template<typename T> typename math<T>::scalar_t dist (const rect3<T>&, const plane3<T>&);       // note: negative result indicates the depth of negative half-space penetration of the plane
template<typename T> typename math<T>::scalar_t dist2(const rect3<T>&, const sphere3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const rect3<T>&, const cylinder3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const rect3<T>&, const capsule3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const rect3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const rect3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const rect3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const rect3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist (const disc3<T>&, const disc3<T>&);
template<typename T> typename math<T>::scalar_t dist (const disc3<T>&, const plane3<T>&);       // note: negative result indicates the depth of negative half-space penetration of the plane
template<typename T> typename math<T>::scalar_t dist (const disc3<T>&, const sphere3<T>&);
template<typename T> typename math<T>::scalar_t dist (const disc3<T>&, const cylinder3<T>&);
template<typename T> typename math<T>::scalar_t dist (const disc3<T>&, const capsule3<T>&);
template<typename T> typename math<T>::scalar_t dist (const disc3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist (const disc3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist (const disc3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist (const disc3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist (const plane3<T>&, const sphere3<T>&);    // note: negative result indicates the depth of negative half-space penetration of the plane
template<typename T> typename math<T>::scalar_t dist2(const plane3<T>&, const cylinder3<T>&);
template<typename T> typename math<T>::scalar_t dist (const plane3<T>&, const capsule3<T>&);
template<typename T> typename math<T>::scalar_t dist (const plane3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist (const plane3<T>&, const aabox3<T>&);     // note: negative result indicates the depth of negative half-space penetration of the plane
template<typename T> typename math<T>::scalar_t dist (const plane3<T>&, const oobox3<T>&);     // note: negative result indicates the depth of negative half-space penetration of the plane
template<typename T> typename math<T>::scalar_t dist2(const plane3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist (const sphere3<T>&, const sphere3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const sphere3<T>&, const cylinder3<T>&);
template<typename T> typename math<T>::scalar_t dist (const sphere3<T>&, const capsule3<T>&);  // note: negative inside the sphere
template<typename T> typename math<T>::scalar_t dist (const sphere3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist (const sphere3<T>&, const aabox3<T>&);    // note: negative inside the sphere
template<typename T> typename math<T>::scalar_t dist (const sphere3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const sphere3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const cylinder3<T>&, const cylinder3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const cylinder3<T>&, const capsule3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const cylinder3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const cylinder3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const cylinder3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const cylinder3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const capsule3<T>&, const capsule3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const capsule3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const capsule3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const capsule3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const capsule3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const cone3<T>&, const cone3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const cone3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const cone3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const cone3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const aabox3<T>&, const aabox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const aabox3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const aabox3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const oobox3<T>&, const oobox3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const oobox3<T>&, const frustum3<T>&);
template<typename T> typename math<T>::scalar_t dist2(const frustum3<T>&, const frustum3<T>&);
//----------------------------------------------------------------------------

//============================================================================
#include "prim3_dist.inl"
} // namespace pfc
#endif
