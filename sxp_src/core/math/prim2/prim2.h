//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_PRIM2_H
#define PFC_CORE_MATH_PRIM2_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/math/math.h"
#include "sxp_src/core/math/numeric.h"
namespace pfc
{

// new
template<typename> struct point2;
template<typename> struct line2;
template<typename> struct ray2;
template<typename> struct segment2;
template<typename> struct circle2;
template<typename> struct tri2;
template<typename> struct aarect2;
template<typename> struct oorect2;
typedef point2<float> point2f;
typedef point2<double> point2d;
typedef line2<float> line2f;
typedef line2<double> line2d;
typedef ray2<float> ray2f;
typedef ray2<double> ray2d;
typedef segment2<float> segment2f;
typedef segment2<double> segment2d;
typedef circle2<float> circle2f;
typedef circle2<double> circle2d;
typedef tri2<float> tri2f;
typedef tri2<double> tri2d;
typedef aarect2<float> aarect2f;
typedef aarect2<double> aarect2d;
typedef oorect2<float> oorect2f;
typedef oorect2<double> oorect2d;
// area functions
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const circle2<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const tri2<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const aarect2<T>&);
template<typename T> PFC_INLINE typename math<T>::scalar_t area(const oorect2<T>&);
//----------------------------------------------------------------------------


//============================================================================
// point2
//============================================================================
template<typename T>
struct point2
{ PFC_MONO(point2) {PFC_MVAR(pos);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE point2();
  PFC_INLINE point2(const vec2<T> &pos_);
  PFC_INLINE point2(scalar_t x_, scalar_t y_);
  PFC_INLINE void set(const vec2<T> &pos_);
  PFC_INLINE void set(scalar_t x_, scalar_t y_);
  //--------------------------------------------------------------------------

  static const point2<T> s_zero;
  vec2<T> pos;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, point2<T>, is_type_pod, is_type_pod<vec2<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, point2<T>, is_type_pod_stream, is_type_pod_stream<vec2<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// line2
//============================================================================
template<typename T>
struct line2
{ PFC_MONO(line2) {PFC_MVAR2(pos, dir);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE line2();
  PFC_INLINE line2(const vec2<T> &pos_, const vec2<T> &dir_);
  PFC_INLINE void set(const vec2<T> &pos_, const vec2<T> &dir_);
  //--------------------------------------------------------------------------

  static const line2<T> s_zero;
  vec2<T> pos;  // point on the line
  vec2<T> dir;  // unit direction of the line
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, line2<T>, is_type_pod, is_type_pod<vec2<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, line2<T>, is_type_pod_stream, is_type_pod_stream<vec2<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// ray2
//============================================================================
template<typename T>
struct ray2
{ PFC_MONO(ray2) {PFC_MVAR2(pos, dir);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE ray2();
  PFC_INLINE ray2(const vec2<T> &pos_, const vec2<T> &dir_);
  PFC_INLINE void set(const vec2<T> &pos_, const vec2<T> &dir_);
  //--------------------------------------------------------------------------

  static const ray2<T> s_zero;
  vec2<T> pos;  // starting point of the ray
  vec2<T> dir;  // unit direction of the ray
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, ray2<T>, is_type_pod, is_type_pod<vec2<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, ray2<T>, is_type_pod_stream, is_type_pod_stream<vec2<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// segment2
//============================================================================
template<typename T>
struct segment2
{ PFC_MONO(segment2) {PFC_MVAR3(pos, dir, hlen);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE segment2();
  PFC_INLINE segment2(const vec2<T> &pos_, const vec2<T> &dir_, scalar_t hlen_);
  PFC_INLINE void set(const vec2<T> &pos_, const vec2<T> &dir_, scalar_t hlen_);
  //--------------------------------------------------------------------------

  static const segment2<T> s_zero;
  vec2<T> pos;   // center position of the segment
  vec2<T> dir;   // unit direction of the segment
  typename math<T>::scalar_t hlen; // half-length of the segment
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, segment2<T>, is_type_pod, is_type_pod<vec2<T> >::res && is_type_pod<math<T>::scalar_t>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, segment2<T>, is_type_pod_stream, is_type_pod_stream<vec2<T> >::res && is_type_pod_stream<math<T>::scalar_t>::res);
//----------------------------------------------------------------------------


//============================================================================
// circle2
//============================================================================
template<typename T>
struct circle2
{ PFC_MONO(circle2) {PFC_MVAR2(pos, rad);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE circle2();
  PFC_INLINE circle2(const vec2<T> &pos_, scalar_t rad_);
  PFC_INLINE void set(const vec2<T> &pos_, scalar_t rad_);
  //--------------------------------------------------------------------------

  static const circle2<T> s_zero;
  vec2<T> pos;   // center position of the circle
  scalar_t rad;  // circle radius
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, circle2<T>, is_type_pod, is_type_pod<vec2<T> >::res && is_type_pod<math<T>::scalar_t>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, circle2<T>, is_type_pod_stream, is_type_pod_stream<vec2<T> >::res && is_type_pod_stream<math<T>::scalar_t>::res);
//----------------------------------------------------------------------------


//============================================================================
// tri2
//============================================================================
template<typename T>
struct tri2
{ PFC_MONO(tri2) {PFC_MVAR3(a, b, c);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE tri2();
  PFC_INLINE tri2(const vec2<T>&, const vec2<T>&, const vec2<T>&);
  PFC_INLINE void set(const vec2<T>&, const vec2<T>&, const vec2<T>&);
  //--------------------------------------------------------------------------

  static const tri2<T> s_zero;
  vec2<T> a, b, c;  // 3 points of the triangle, clock-wise order for front-facing
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, tri2<T>, is_type_pod, is_type_pod<vec2<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, tri2<T>, is_type_pod_stream, is_type_pod_stream<vec2<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// aarect2
//============================================================================
template<typename T>
struct aarect2
{ PFC_MONO(aarect2) {PFC_MVAR2(pos, hsize);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE aarect2();
  PFC_INLINE aarect2(const vec2<T> &pos_, const vec2<T> &hsize_);
  PFC_INLINE void set(const vec2<T> &pos_, const vec2<T> &hsize_);
  //--------------------------------------------------------------------------

  static const aarect2<T> s_zero;
  vec2<T> pos;
  vec2<T> hsize;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, aarect2<T>, is_type_pod, is_type_pod<vec2<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, aarect2<T>, is_type_pod_stream, is_type_pod_stream<vec2<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// oorect2
//============================================================================
template<typename T>
struct oorect2
{ PFC_MONO(oorect2) {PFC_MVAR3(pos, hsize, rot);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE oorect2();
  PFC_INLINE oorect2(const vec2<T> &pos_, const vec2<T> &hsize_, const mat22<T> &rot_);
  PFC_INLINE void set(const vec2<T> &pos_, const vec2<T> &hsize_, const mat22<T> &rot_);
  //--------------------------------------------------------------------------

  static const oorect2<T> s_zero;
  vec2<T> pos;
  vec2<T> hsize;
  mat22<T> rot;
};
//----------------------------------------------------------------------------

//============================================================================
#include "prim2.inl"
} // namespace pfc
#endif
