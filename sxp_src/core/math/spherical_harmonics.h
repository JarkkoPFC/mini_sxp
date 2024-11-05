//==========================================7==================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_SPHERICAL_HARMONICS_H
#define PFC_CORE_MATH_SPHERICAL_HARMONICS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "math.h"
namespace pfc
{

// new
template<typename T> struct shvec2; // order-2 spherical harmonics vector
template<typename T> struct shvec3; // order-3 spherical harmonics vector
template<typename T> struct zhvec2; // order-2 zonal harmonics vector
template<typename T> struct zhvec3; // order-3 zonal harmonics vector
template<typename T> struct shmat2; // order-2 spherical harmonics matrix
template<typename T> struct shmat3; // order-3 spherical harmonics matrix
typedef shvec2<float> shvec2f;
typedef shvec2<double> shvec2d;
typedef shvec3<float> shvec3f;
typedef shvec3<double> shvec3d;
typedef zhvec2<float> zhvec2f;
typedef zhvec2<double> zhvec2d;
typedef zhvec3<float> zhvec3f;
typedef zhvec3<double> zhvec3d;
typedef shmat2<float> shmat2f;
typedef shmat2<double> shmat2d;
typedef shmat3<float> shmat3f;
typedef shmat3<double> shmat3d;
// SH2 vector ops
template<typename T, typename U> PFC_INLINE void operator+=(shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> PFC_INLINE void operator+=(shvec2<T>&, U);
template<typename T, typename U> PFC_INLINE void operator-=(shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> PFC_INLINE void operator-=(shvec2<T>&, U);
template<typename T, typename U> PFC_INLINE void operator*=(shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> PFC_INLINE void operator*=(shvec2<T>&, U);
template<typename T, typename U> PFC_INLINE void operator*=(shvec2<T>&, const shmat2<U>&);
template<typename T, typename U> PFC_INLINE void operator/=(shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> PFC_INLINE void operator/=(shvec2<T>&, U);
template<typename T, typename U> PFC_INLINE shvec2<T> operator+(const shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> PFC_INLINE shvec2<T> operator+(const shvec2<T>&, U);
template<typename T, typename U> PFC_INLINE shvec2<T> operator+(U, const shvec2<T>&);
template<typename T, typename U> PFC_INLINE shvec2<T> operator-(const shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> PFC_INLINE shvec2<T> operator-(const shvec2<T>&, U);
template<typename T, typename U> PFC_INLINE shvec2<T> operator-(U, const shvec2<T>&);
template<typename T, typename U> PFC_INLINE shvec2<T> operator*(const shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> PFC_INLINE shvec2<T> operator*(const shvec2<T>&, U);
template<typename T, typename U> PFC_INLINE shvec2<T> operator*(U, const shvec2<T>&);
template<typename T, typename U> PFC_INLINE shvec2<T> operator*(const shvec2<T>&, const shmat2<U>&);
template<typename T, typename U> PFC_INLINE shvec2<T> operator*(const shmat2<T>&, const shvec2<U>&);
template<typename T, typename U> PFC_INLINE shvec2<T> operator/(const shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> PFC_INLINE shvec2<T> operator/(const shvec2<T>&, T);
template<typename T, typename U> PFC_INLINE shvec2<T> operator/(T, const shvec2<T>&);
template<typename T, typename U> PFC_INLINE shvec2<T> operator/(const shvec2<T>&, U);
template<typename T, typename U> PFC_INLINE shvec2<T> operator/(U, const shvec2<T>&);
template<typename T, typename U> PFC_INLINE T sh_dot(const shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> PFC_INLINE void sh_basis(shvec2<T>&, const vec3<U>&);
template<typename T, typename U> shvec2<T> sh_product(const shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> shvec2<T> sh_product(const shvec2<T>&, const zhvec2<U>&);
// SH3 vector ops
template<typename T, typename U> PFC_INLINE void operator+=(shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> PFC_INLINE void operator+=(shvec3<T>&, U);
template<typename T, typename U> PFC_INLINE void operator-=(shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> PFC_INLINE void operator-=(shvec3<T>&, U);
template<typename T, typename U> PFC_INLINE void operator*=(shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> PFC_INLINE void operator*=(shvec3<T>&, U);
template<typename T, typename U> PFC_INLINE void operator*=(shvec3<T>&, const shmat3<U>&);
template<typename T, typename U> PFC_INLINE void operator/=(shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> PFC_INLINE void operator/=(shvec3<T>&, U);
template<typename T, typename U> PFC_INLINE shvec3<T> operator+(const shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> PFC_INLINE shvec3<T> operator+(const shvec3<T>&, U);
template<typename T, typename U> PFC_INLINE shvec3<T> operator+(U, const shvec3<T>&);
template<typename T, typename U> PFC_INLINE shvec3<T> operator-(const shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> PFC_INLINE shvec3<T> operator-(const shvec3<T>&, U);
template<typename T, typename U> PFC_INLINE shvec3<T> operator-(U, const shvec3<T>&);
template<typename T, typename U> PFC_INLINE shvec3<T> operator*(const shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> PFC_INLINE shvec3<T> operator*(const shvec3<T>&, U);
template<typename T, typename U> PFC_INLINE shvec3<T> operator*(U, const shvec3<T>&);
template<typename T, typename U> PFC_INLINE shvec3<T> operator*(const shvec3<T>&, const shmat3<U>&);
template<typename T, typename U> PFC_INLINE shvec3<T> operator*(const shmat3<T>&, const shvec3<U>&);
template<typename T, typename U> PFC_INLINE shvec3<T> operator/(const shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> PFC_INLINE shvec3<T> operator/(const shvec3<T>&, U);
template<typename T, typename U> PFC_INLINE shvec3<T> operator/(U, const shvec3<T>&);
template<typename T, typename U> PFC_INLINE T sh_dot(const shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> PFC_INLINE void sh_basis(shvec3<T>&, const vec3<U>&);
template<typename T, typename U> shvec3<T> sh_product(const shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> shvec3<T> sh_product(const shvec3<T>&, const zhvec3<U>&);
// ZH2 vector ops
template<typename T, typename U> PFC_INLINE void operator+=(zhvec2<T>&, const zhvec2<U>&);
template<typename T, typename U> PFC_INLINE void operator+=(zhvec2<T>&, U);
template<typename T, typename U> PFC_INLINE void operator-=(zhvec2<T>&, const zhvec2<U>&);
template<typename T, typename U> PFC_INLINE void operator-=(zhvec2<T>&, U);
template<typename T, typename U> PFC_INLINE void operator*=(zhvec2<T>&, const zhvec2<U>&);
template<typename T, typename U> PFC_INLINE void operator*=(zhvec2<T>&, U);
template<typename T, typename U> PFC_INLINE void operator/=(zhvec2<T>&, const zhvec2<U>&);
template<typename T, typename U> PFC_INLINE void operator/=(zhvec2<T>&, U);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator+(const zhvec2<T>&, const zhvec2<U>&);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator+(const zhvec2<T>&, U);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator+(U, const zhvec2<T>&);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator-(const zhvec2<T>&, const zhvec2<U>&);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator-(const zhvec2<T>&, U);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator-(U, const zhvec2<T>&);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator*(const zhvec2<T>&, const zhvec2<U>&);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator*(const zhvec2<T>&, U);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator*(U, const zhvec2<T>&);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator/(const zhvec2<T>&, const zhvec2<U>&);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator/(const zhvec2<T>&, U);
template<typename T, typename U> PFC_INLINE zhvec2<T> operator/(U, const zhvec2<T>&);
template<typename T, typename U> PFC_INLINE T sh_dot(const zhvec2<T>&, const zhvec2<U>&);
// ZH3 vector ops
template<typename T, typename U> PFC_INLINE void operator+=(zhvec3<T>&, const zhvec3<U>&);
template<typename T, typename U> PFC_INLINE void operator+=(zhvec3<T>&, U);
template<typename T, typename U> PFC_INLINE void operator-=(zhvec3<T>&, const zhvec3<U>&);
template<typename T, typename U> PFC_INLINE void operator-=(zhvec3<T>&, U);
template<typename T, typename U> PFC_INLINE void operator*=(zhvec3<T>&, const zhvec3<U>&);
template<typename T, typename U> PFC_INLINE void operator*=(zhvec3<T>&, U);
template<typename T, typename U> PFC_INLINE void operator/=(zhvec3<T>&, const zhvec3<U>&);
template<typename T, typename U> PFC_INLINE void operator/=(zhvec3<T>&, U);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator+(const zhvec3<T>&, const zhvec3<U>&);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator+(const zhvec3<T>&, U);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator+(U, const zhvec3<T>&);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator-(const zhvec3<T>&, const zhvec3<U>&);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator-(const zhvec3<T>&, U);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator-(U, const zhvec3<T>&);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator*(const zhvec3<T>&, const zhvec3<U>&);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator*(const zhvec3<T>&, U);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator*(U, const zhvec3<T>&);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator/(const zhvec3<T>&, const zhvec3<U>&);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator/(const zhvec3<T>&, U);
template<typename T, typename U> PFC_INLINE zhvec3<T> operator/(U, const zhvec3<T>&);
template<typename T, typename U> PFC_INLINE T sh_dot(const zhvec3<T>&, const zhvec3<U>&);
//----------------------------------------------------------------------------


//============================================================================
// shvec2
//============================================================================
template<typename T>
struct shvec2
{ PFC_MONO(shvec2) {PFC_AVAR(coeffs, 4);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {order=2};
  //--------------------------------------------------------------------------

  T coeffs[4]; // Y0_0, Y1_-1, Y1_0, Y1_1
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, shvec2<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, shvec2<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// shvec3
//============================================================================
template<typename T>
struct shvec3
{ PFC_MONO(shvec3) {PFC_AVAR(coeffs, 9);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {order=3};
  //--------------------------------------------------------------------------

  T coeffs[9]; // Y0_0, Y1_-1, Y1_0, Y1_1, Y2_-2, Y2_-1, Y2_0, Y2_1, Y2_2
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, shvec3<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, shvec3<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// zhvec2
//============================================================================
template<typename T>
struct zhvec2
{ PFC_MONO(zhvec2) {PFC_AVAR(coeffs, 2);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {order=2};
  //--------------------------------------------------------------------------

  static const zhvec2 s_cos;
  static const zhvec2 s_clamped_cos;
  static const zhvec2 s_cos2;
  static const zhvec2 s_clamped_cos2;
  T coeffs[2]; // Y0_0, Y1_1
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, zhvec2<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, zhvec2<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// zhvec3
//============================================================================
template<typename T>
struct zhvec3
{ PFC_MONO(zhvec3) {PFC_AVAR(coeffs, 3);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {order=3};
  //--------------------------------------------------------------------------

  static const zhvec3 s_cos;
  static const zhvec3 s_clamped_cos;
  static const zhvec3 s_cos2;
  static const zhvec3 s_clamped_cos2;
  T coeffs[3]; // Y0_0, Y1_1, Y2_2
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, zhvec3<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, zhvec3<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// shmat2
//============================================================================
template<typename T>
struct shmat2
{ PFC_MONO(shmat2) {PFC_AVAR(m, 16);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {order=2};
  //--------------------------------------------------------------------------

  T m[4][4];
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, shmat2<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, shmat2<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// shmat3
//============================================================================
template<typename T>
struct shmat3
{ PFC_MONO(shmat3) {PFC_AVAR(m, 81);}
  typedef T type_t;
  typedef typename math<T>::scalar_t scalar_t;
  enum {order=3};
  //--------------------------------------------------------------------------

  T m[9][9];
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, shmat3<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, shmat3<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------

//============================================================================
#include "spherical_harmonics.inl"
} // namespace pfc
#endif
