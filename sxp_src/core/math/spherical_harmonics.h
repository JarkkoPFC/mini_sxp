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
template<typename T> PFC_INLINE bool is_zero(const shvec2<T>&);                                             // test for zero-vector, i.e. all coeffs equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const shvec2<T>&);                                              // test for saturated vector, i.e. all coeffs are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const shvec2<T>&);                                             // test for signed saturated vector, i.e. all coeffs are in range [-1, 1]
template<typename T, typename U> PFC_INLINE bool operator==(const shvec2<T>&, const shvec2<U>&);            // test for equality of vectors, i.e. all coeffs of the vectors are equal (exact)
template<typename T, typename U> PFC_INLINE bool operator==(const shvec2<T>&, U);                           // test for equality of vector and value, i.e. all coeffs of the vector equals the value (exact)
template<typename T, typename U> PFC_INLINE bool operator==(typename U, const shvec2<T>&);                  // test for equality of vector and value, i.e. all coeffs of the vector equals the value (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(const shvec2<T>&, const shvec2<U>&);            // test for inequality of vectors, i.e. any of the coeffs of the vectors are unequal (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(const shvec2<T>&, U);                           // test for inequality of vector and value, i.e. any of the coeffs of the vector is unequal to the value (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(U, const shvec2<T>&);                           // test for inequality of vector and value, i.e. any of the coeffs of the vector is unequal to the value (exact)
template<typename T, typename U> PFC_INLINE void operator+=(shvec2<T>&, const shvec2<U>&);                  // add vector to vector
template<typename T, typename U> PFC_INLINE void operator+=(shvec2<T>&, U);                                 // add value to each coeff of the vector
template<typename T, typename U> PFC_INLINE void operator-=(shvec2<T>&, const shvec2<U>&);                  // subtract vector from vector
template<typename T, typename U> PFC_INLINE void operator-=(shvec2<T>&, U);                                 // subtract value from each coeff of the vector
template<typename T, typename U> PFC_INLINE void operator*=(shvec2<T>&, const shvec2<U>&);                  // coeff-wise vector by vector multiplication
template<typename T, typename U> PFC_INLINE void operator*=(shvec2<T>&, U);                                 // vector by value multiplication
template<typename T, typename U> PFC_INLINE void operator*=(shvec2<T>&, const shmat2<U>&);                  // vector by matrix multiplication
template<typename T, typename U> PFC_INLINE void operator/=(shvec2<T>&, const shvec2<U>&);                  // coeff-wise vector by vector division
template<typename T, typename U> PFC_INLINE void operator/=(shvec2<T>&, U);                                 // vector by value division
template<typename T, typename U> PFC_INLINE shvec2<T> operator+(const shvec2<T>&, const shvec2<U>&);        // add vector to vector
template<typename T, typename U> PFC_INLINE shvec2<T> operator+(const shvec2<T>&, U);                       // add value to each coeff of the vector
template<typename T, typename U> PFC_INLINE shvec2<T> operator+(U, const shvec2<T>&);                       // add each coeff of the vector to a value vector
template<typename T, typename U> PFC_INLINE shvec2<T> operator-(const shvec2<T>&, const shvec2<U>&);        // subtract vector from vector
template<typename T, typename U> PFC_INLINE shvec2<T> operator-(const shvec2<T>&, U);                       // subtract value from each coeff of the vector
template<typename T, typename U> PFC_INLINE shvec2<T> operator-(U, const shvec2<T>&);                       // subtract each coeff of the vector from a value vector
template<typename T> PFC_INLINE shvec2<T> operator-(const shvec2<T>&);                                      // negate the vector
template<typename T, typename U> PFC_INLINE shvec2<T> operator*(const shvec2<T>&, const shvec2<U>&);        // coeff-wise vector by vector multiplication
template<typename T, typename U> PFC_INLINE shvec2<T> operator*(const shvec2<T>&, U);                       // vector by value multiplication
template<typename T, typename U> PFC_INLINE shvec2<T> operator*(U, const shvec2<T>&);                       // value by vector multiplication
template<typename T, typename U> PFC_INLINE shvec2<T> operator*(const shvec2<T>&, const shmat2<U>&);        // vector by matrix multiplication
template<typename T, typename U> PFC_INLINE shvec2<T> operator*(const shmat2<T>&, const shvec2<U>&);        // matrix by transposed vector multiplication
template<typename T, typename U> PFC_INLINE shvec2<T> operator/(const shvec2<T>&, const shvec2<U>&);        // coeff-wise vector by vector division
template<typename T, typename U> PFC_INLINE shvec2<T> operator/(const shvec2<T>&, U);                       // vector by value division
template<typename T, typename U> PFC_INLINE shvec2<T> operator/(U, const shvec2<T>&);                       // value by vector division
template<typename T> PFC_INLINE T min(const shvec2<T>&);                                                    // minimum coeff value
template<typename T> PFC_INLINE shvec2<T> min(const shvec2<T>&, const shvec2<T>&);                          // coeff-wise minimum of the vectors
template<typename T> PFC_INLINE shvec2<T> min(const shvec2<T>&, const shvec2<T>&, const shvec2<T>&);
template<typename T> PFC_INLINE shvec2<T> min(const shvec2<T>&, const shvec2<T>&, const shvec2<T>&, const shvec2<T>&);
template<typename T, typename U> PFC_INLINE shvec2<T> min(const shvec2<T>&, U);                             // coeff-wise minimum of the vector and value
template<typename T, typename U> PFC_INLINE shvec2<T> min(U, const shvec2<T>&);                             // coeff-wise minimum of the vector and value
template<typename T> PFC_INLINE T max(const shvec2<T>&);                                                    // maximum coeff value
template<typename T> PFC_INLINE shvec2<T> max(const shvec2<T>&, const shvec2<T>&);                          // coeff-wise maximum of the vectors
template<typename T> PFC_INLINE shvec2<T> max(const shvec2<T>&, const shvec2<T>&, const shvec2<T>&);
template<typename T> PFC_INLINE shvec2<T> max(const shvec2<T>&, const shvec2<T>&, const shvec2<T>&, const shvec2<T>&);
template<typename T, typename U> PFC_INLINE shvec2<T> max(const shvec2<T>&, U);                             // coeff-wise maximum of the vector and value
template<typename T, typename U> PFC_INLINE shvec2<T> max(U, const shvec2<T>&);                             // coeff-wise maximum of the vector and value
template<typename T, typename U> PFC_INLINE shvec2<T> mul(const shvec2<T>&, const shvec2<T>&);              // coeff-wise vector multiply
template<typename T, typename U, typename V> PFC_INLINE shvec2<T> madd(const shvec2<T> &shv0_,              // coeff-wise multiply-add: shv0_*v1+shv2_
                                                                       const shvec2<U> &shv1_,
                                                                       const shvec2<V> &shv2_);
template<typename T, typename U, typename V> PFC_INLINE shvec2<T> madd(const shvec2<T> &shv_,               // vector-value-value multiply-add: shv_*mul_+add_
                                                                       U mul_,
                                                                       V add_);
template<typename T, typename U, typename V> PFC_INLINE shvec2<T> madd(const shvec2<T> &shv_,               // vector-vector-value multiply-add: shv_*mul_+add_
                                                                       const shvec2<U> &mul_,
                                                                       V add_);
template<typename T, typename U, typename V> PFC_INLINE shvec2<T> madd(const shvec2<T> &shv_,               // vector-value-vector multiply-add: shv_*mul_+add_
                                                                       U mul_,
                                                                       const shvec2<V> &add_);
template<typename T> PFC_INLINE shvec2<T> rcp(const shvec2<T>&);                                            // coeff-wise vector reciprocal
template<typename T> PFC_INLINE shvec2<T> rcp_z(const shvec2<T>&);                                          // coeff-wise vector reciprocal (set 0 for 0 coeffs)
template<typename T> PFC_INLINE shvec2<T> floor(const shvec2<T>&);                                          // coeff-wise greatest integer less than or equal to the value
template<typename T> PFC_INLINE shvec2<T> ceil(const shvec2<T>&);                                           // coeff-wise smallest integer greater than or equal to the value
template<typename T> PFC_INLINE shvec2<T> trunc(const shvec2<T>&);                                          // coeff-wise truncate decimal part from the value
template<typename T> PFC_INLINE shvec2<T> frc(const shvec2<T>&);                                            // coeff-wise fractional part (for negative values returns 1-fractional part)
template<typename T, typename U> PFC_INLINE shvec2<T> mod(const shvec2<T>&, U div_);                        // coeff-wise modulo
template<typename T, typename U> PFC_INLINE shvec2<T> cycle(const shvec2<T>&, U cycle_);                    // coeff-wise cycle
template<typename T, typename U> PFC_INLINE shvec2<T> cycle(const shvec2<T>&, const shvec2<U>& cycle_);     // coeff-wise cycle
template<typename T> PFC_INLINE shvec2<T> cycle1(const shvec2<T>&);                                         // coeff-wise cycle1
template<typename T> PFC_INLINE shvec2<T> sat(const shvec2<T>&);                                            // coeff-wise vector saturate
template<typename T> PFC_INLINE shvec2<T> ssat(const shvec2<T>&);                                           // coeff-wise vector signed saturate
template<typename T, typename U> PFC_INLINE shvec2<T> clamp(const shvec2<T>&,                               // coeff-wise clamp of the vector
                                                            const shvec2<U> &min_,
                                                            const shvec2<U> &max_);
template<typename T, typename U> PFC_INLINE shvec2<T> clamp(const shvec2<T>&,                               // coeff-wise clamp of the vector with values
                                                            U min_,
                                                            U max_);
template<typename T> PFC_INLINE shvec2<T> abs(const shvec2<T>&);                                            // coeff-wise vector absolute
template<typename T> PFC_INLINE shvec2<T> sgn(const shvec2<T>&);                                            // coeff-wise signum (neg=-1, pos=+1, zero=0)
template<typename T> PFC_INLINE shvec2<T> sgn_zp(const shvec2<T>&);                                         // coeff-wise signum (neg=-1, pos&zero=+1)
template<typename T> PFC_INLINE shvec2<T> sqr(const shvec2<T>&);                                            // coeff-wise square: x*x
template<typename T> PFC_INLINE shvec2<T> cubic(const shvec2<T>&);                                          // coeff-wise cubic: x*x*x
template<typename T> PFC_INLINE shvec2<T> sqrt(const shvec2<T>&);                                           // coeff-wise square root
template<typename T> PFC_INLINE shvec2<T> sqrt_z(const shvec2<T>&);                                         // coeff-wise square root (set 0 for coeffs less than zero)
template<typename T> PFC_INLINE shvec2<T> cbrt(const shvec2<T>&);                                           // coeff-wise cubic root
template<typename T> PFC_INLINE shvec2<T> rsqrt(const shvec2<T>&);                                          // coeff-wise vector reciprocal square root
template<typename T> PFC_INLINE shvec2<T> rsqrt_z(const shvec2<T>&);                                        // coeff-wise vector reciprocal square root (set 0 for coeffs less than or equal to zero)
template<typename T> PFC_INLINE shvec2<T> rcbrt(const shvec2<T>&);                                          // coeff-wise reciprocal cubic root
template<typename T> PFC_INLINE shvec2<T> rcbrt_z(const shvec2<T>&);                                        // coeff-wise reciprocal cubic root (set 0 for coeffs that are 0)
template<typename T> PFC_INLINE T norm(const shvec2<T>&);                                                   // vector norm (length): |v|
template<typename T> PFC_INLINE T rnorm(const shvec2<T>&);                                                  // reciprocal of the vector norm: 1/|v|
template<typename T> PFC_INLINE T rnorm_z(const shvec2<T>&);                                                // reciprocal of the vector norm: 1/|v| (if |v|=0, return 0)
template<typename T> PFC_INLINE T norm2(const shvec2<T>&);                                                  // squared vector norm: |v|^2
template<typename T> PFC_INLINE T rnorm2(const shvec2<T>&);                                                 // reciprocal of the squared vector norm: 1/|v|^2
template<typename T> PFC_INLINE T rnorm2_z(const shvec2<T>&);                                               // reciprocal of the squared vector norm: 1/|v|^2 (if |v|=0, return 0)
template<typename T> PFC_INLINE T norm_l1(const shvec2<T>&);                                                // vector L1-norm (Manhattan norm)
template<typename T> PFC_INLINE T rnorm_l1(const shvec2<T>&);                                               // reciprocal of the vector L1-norm
template<typename T> PFC_INLINE T rnorm_l1_z(const shvec2<T>&);                                             // reciprocal of the vector L1-norm (if |v|=0, return 0)
template<typename T> PFC_INLINE shvec2<T> exp(const shvec2<T>&);                                            // coeff-wise natural exponent: e^x
template<typename T> PFC_INLINE shvec2<T> exp2(const shvec2<T>&);                                           // coeff-wise 2^x
template<typename T> PFC_INLINE shvec2<T> ln(const shvec2<T>&);                                             // coeff-wise natural logarithm
template<typename T> PFC_INLINE shvec2<T> log2(const shvec2<T>&);                                           // coeff-wise base-2 logarithm
template<typename T> PFC_INLINE shvec2<T> log10(const shvec2<T>&);                                          // coeff-wise base-10 logarithm
template<typename T, typename U> PFC_INLINE shvec2<T> pow(const shvec2<T>&, U);                             // coeff-wise power
template<typename T> PFC_INLINE shvec2<T> unit(const shvec2<T>&);                                           // unit vector of the vector: v/|v|
template<typename T> PFC_INLINE shvec2<T> unit_z(const shvec2<T>&);                                         // unit vector of the vector (if |v|=0, return v=[0, 0])
template<typename T, typename U> PFC_INLINE T dot(const shvec2<T>&, const shvec2<U>&);                      // vector dot-product
template<typename T> PFC_INLINE T dot1(const shvec2<T>&);                                                   // vector coeff sum
template<typename T> PFC_INLINE void neg(shvec2<T>&);                                                       // negate the vector
template<typename T, class Rng> PFC_INLINE void rand_real1(shvec2<T>&, Rng&);                               // random vector where each coeff is in range [-1, 1)
template<typename T, class Rng> PFC_INLINE void rand_ureal1(shvec2<T>&, Rng&);                              // random vector where each coeff is in range [0, 1)
template<typename T> PFC_INLINE shvec2<T> smoothstep(const shvec2<T>&);                                     // coeff-wise smoothstep function
template<typename T> PFC_INLINE shvec2<T> smootherstep(const shvec2<T>&);                                   // coeff-wise smootherstep function
template<typename T, typename U> PFC_INLINE shvec2<T> lerp(const shvec2<T> &shv0_,                          // linear interpolation of vectors: f(t=0)=shv0, f(t=1)=shv1
                                                           const shvec2<T> &shv1_,
                                                           U t_);
template<typename T, typename U> PFC_INLINE void sh_basis(shvec2<T>&, const vec3<U>&);
template<typename T, typename U> shvec2<T> sh_product(const shvec2<T>&, const shvec2<U>&);
template<typename T, typename U> shvec2<T> sh_product(const shvec2<T>&, const zhvec2<U>&);
// SH3 vector ops
template<typename T> PFC_INLINE bool is_zero(const shvec3<T>&);                                             // test for zero-vector, i.e. all coeffs equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const shvec3<T>&);                                              // test for saturated vector, i.e. all coeffs are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const shvec3<T>&);                                             // test for signed saturated vector, i.e. all coeffs are in range [-1, 1]
template<typename T, typename U> PFC_INLINE bool operator==(const shvec3<T>&, const shvec3<U>&);            // test for equality of vectors, i.e. all coeffs of the vectors are equal (exact)
template<typename T, typename U> PFC_INLINE bool operator==(const shvec3<T>&, U);                           // test for equality of vector and value, i.e. all coeffs of the vector equals the value (exact)
template<typename T, typename U> PFC_INLINE bool operator==(typename U, const shvec3<T>&);                  // test for equality of vector and value, i.e. all coeffs of the vector equals the value (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(const shvec3<T>&, const shvec3<U>&);            // test for inequality of vectors, i.e. any of the coeffs of the vectors are unequal (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(const shvec3<T>&, U);                           // test for inequality of vector and value, i.e. any of the coeffs of the vector is unequal to the value (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(U, const shvec3<T>&);                           // test for inequality of vector and value, i.e. any of the coeffs of the vector is unequal to the value (exact)
template<typename T, typename U> PFC_INLINE void operator+=(shvec3<T>&, const shvec3<U>&);                  // add vector to vector
template<typename T, typename U> PFC_INLINE void operator+=(shvec3<T>&, U);                                 // add value to each coeff of the vector
template<typename T, typename U> PFC_INLINE void operator-=(shvec3<T>&, const shvec3<U>&);                  // subtract vector from vector
template<typename T, typename U> PFC_INLINE void operator-=(shvec3<T>&, U);                                 // subtract value from each coeff of the vector
template<typename T, typename U> PFC_INLINE void operator*=(shvec3<T>&, const shvec3<U>&);                  // coeff-wise vector by vector multiplication
template<typename T, typename U> PFC_INLINE void operator*=(shvec3<T>&, U);                                 // vector by value multiplication
template<typename T, typename U> PFC_INLINE void operator*=(shvec3<T>&, const shmat3<U>&);                  // vector by matrix multiplication
template<typename T, typename U> PFC_INLINE void operator/=(shvec3<T>&, const shvec3<U>&);                  // coeff-wise vector by vector division
template<typename T, typename U> PFC_INLINE void operator/=(shvec3<T>&, U);                                 // vector by value division
template<typename T, typename U> PFC_INLINE shvec3<T> operator+(const shvec3<T>&, const shvec3<U>&);        // add vector to vector
template<typename T, typename U> PFC_INLINE shvec3<T> operator+(const shvec3<T>&, U);                       // add value to each coeff of the vector
template<typename T, typename U> PFC_INLINE shvec3<T> operator+(U, const shvec3<T>&);                       // add each coeff of the vector to a value vector
template<typename T, typename U> PFC_INLINE shvec3<T> operator-(const shvec3<T>&, const shvec3<U>&);        // subtract vector from vector
template<typename T, typename U> PFC_INLINE shvec3<T> operator-(const shvec3<T>&, U);                       // subtract value from each coeff of the vector
template<typename T, typename U> PFC_INLINE shvec3<T> operator-(U, const shvec3<T>&);                       // subtract each coeff of the vector from a value vector
template<typename T> PFC_INLINE shvec3<T> operator-(const shvec3<T>&);                                      // negate the vector
template<typename T, typename U> PFC_INLINE shvec3<T> operator*(const shvec3<T>&, const shvec3<U>&);        // coeff-wise vector by vector multiplication
template<typename T, typename U> PFC_INLINE shvec3<T> operator*(const shvec3<T>&, U);                       // vector by value multiplication
template<typename T, typename U> PFC_INLINE shvec3<T> operator*(U, const shvec3<T>&);                       // value by vector multiplication
template<typename T, typename U> PFC_INLINE shvec3<T> operator*(const shvec3<T>&, const shmat3<U>&);        // vector by matrix multiplication
template<typename T, typename U> PFC_INLINE shvec3<T> operator*(const shmat3<T>&, const shvec3<U>&);        // matrix by transposed vector multiplication
template<typename T, typename U> PFC_INLINE shvec3<T> operator/(const shvec3<T>&, const shvec3<U>&);        // coeff-wise vector by vector division
template<typename T, typename U> PFC_INLINE shvec3<T> operator/(const shvec3<T>&, U);                       // vector by value division
template<typename T, typename U> PFC_INLINE shvec3<T> operator/(U, const shvec3<T>&);                       // value by vector division
template<typename T> PFC_INLINE T min(const shvec3<T>&);                                                    // minimum coeff value
template<typename T> PFC_INLINE shvec3<T> min(const shvec3<T>&, const shvec3<T>&);                          // coeff-wise minimum of the vectors
template<typename T> PFC_INLINE shvec3<T> min(const shvec3<T>&, const shvec3<T>&, const shvec3<T>&);
template<typename T> PFC_INLINE shvec3<T> min(const shvec3<T>&, const shvec3<T>&, const shvec3<T>&, const shvec3<T>&);
template<typename T, typename U> PFC_INLINE shvec3<T> min(const shvec3<T>&, U);                             // coeff-wise minimum of the vector and value
template<typename T, typename U> PFC_INLINE shvec3<T> min(U, const shvec3<T>&);                             // coeff-wise minimum of the vector and value
template<typename T> PFC_INLINE T max(const shvec3<T>&);                                                    // maximum coeff value
template<typename T> PFC_INLINE shvec3<T> max(const shvec3<T>&, const shvec3<T>&);                          // coeff-wise maximum of the vectors
template<typename T> PFC_INLINE shvec3<T> max(const shvec3<T>&, const shvec3<T>&, const shvec3<T>&);
template<typename T> PFC_INLINE shvec3<T> max(const shvec3<T>&, const shvec3<T>&, const shvec3<T>&, const shvec3<T>&);
template<typename T, typename U> PFC_INLINE shvec3<T> max(const shvec3<T>&, U);                             // coeff-wise maximum of the vector and value
template<typename T, typename U> PFC_INLINE shvec3<T> max(U, const shvec3<T>&);                             // coeff-wise maximum of the vector and value
template<typename T, typename U> PFC_INLINE shvec3<T> mul(const shvec3<T>&, const shvec3<T>&);              // coeff-wise vector multiply
template<typename T, typename U, typename V> PFC_INLINE shvec3<T> madd(const shvec3<T> &shv0_,              // coeff-wise multiply-add: shv0_*v1+shv2_
                                                                       const shvec3<U> &shv1_,
                                                                       const shvec3<V> &shv2_);
template<typename T, typename U, typename V> PFC_INLINE shvec3<T> madd(const shvec3<T> &shv_,               // vector-value-value multiply-add: shv_*mul_+add_
                                                                       U mul_,
                                                                       V add_);
template<typename T, typename U, typename V> PFC_INLINE shvec3<T> madd(const shvec3<T> &shv_,               // vector-vector-value multiply-add: shv_*mul_+add_
                                                                       const shvec3<U> &mul_,
                                                                       V add_);
template<typename T, typename U, typename V> PFC_INLINE shvec3<T> madd(const shvec3<T> &shv_,               // vector-value-vector multiply-add: shv_*mul_+add_
                                                                       U mul_,
                                                                       const shvec3<V> &add_);
template<typename T> PFC_INLINE shvec3<T> rcp(const shvec3<T>&);                                            // coeff-wise vector reciprocal
template<typename T> PFC_INLINE shvec3<T> rcp_z(const shvec3<T>&);                                          // coeff-wise vector reciprocal (set 0 for 0 coeffs)
template<typename T> PFC_INLINE shvec3<T> floor(const shvec3<T>&);                                          // coeff-wise greatest integer less than or equal to the value
template<typename T> PFC_INLINE shvec3<T> ceil(const shvec3<T>&);                                           // coeff-wise smallest integer greater than or equal to the value
template<typename T> PFC_INLINE shvec3<T> trunc(const shvec3<T>&);                                          // coeff-wise truncate decimal part from the value
template<typename T> PFC_INLINE shvec3<T> frc(const shvec3<T>&);                                            // coeff-wise fractional part (for negative values returns 1-fractional part)
template<typename T, typename U> PFC_INLINE shvec3<T> mod(const shvec3<T>&, U div_);                        // coeff-wise modulo
template<typename T, typename U> PFC_INLINE shvec3<T> cycle(const shvec3<T>&, U cycle_);                    // coeff-wise cycle
template<typename T, typename U> PFC_INLINE shvec3<T> cycle(const shvec3<T>&, const shvec3<U>& cycle_);     // coeff-wise cycle
template<typename T> PFC_INLINE shvec3<T> cycle1(const shvec3<T>&);                                         // coeff-wise cycle1
template<typename T> PFC_INLINE shvec3<T> sat(const shvec3<T>&);                                            // coeff-wise vector saturate
template<typename T> PFC_INLINE shvec3<T> ssat(const shvec3<T>&);                                           // coeff-wise vector signed saturate
template<typename T, typename U> PFC_INLINE shvec3<T> clamp(const shvec3<T>&,                               // coeff-wise clamp of the vector
                                                            const shvec3<U> &min_,
                                                            const shvec3<U> &max_);
template<typename T, typename U> PFC_INLINE shvec3<T> clamp(const shvec3<T>&,                               // coeff-wise clamp of the vector with values
                                                            U min_,
                                                            U max_);
template<typename T> PFC_INLINE shvec3<T> abs(const shvec3<T>&);                                            // coeff-wise vector absolute
template<typename T> PFC_INLINE shvec3<T> sgn(const shvec3<T>&);                                            // coeff-wise signum (neg=-1, pos=+1, zero=0)
template<typename T> PFC_INLINE shvec3<T> sgn_zp(const shvec3<T>&);                                         // coeff-wise signum (neg=-1, pos&zero=+1)
template<typename T> PFC_INLINE shvec3<T> sqr(const shvec3<T>&);                                            // coeff-wise square: x*x
template<typename T> PFC_INLINE shvec3<T> cubic(const shvec3<T>&);                                          // coeff-wise cubic: x*x*x
template<typename T> PFC_INLINE shvec3<T> sqrt(const shvec3<T>&);                                           // coeff-wise square root
template<typename T> PFC_INLINE shvec3<T> sqrt_z(const shvec3<T>&);                                         // coeff-wise square root (set 0 for coeffs less than zero)
template<typename T> PFC_INLINE shvec3<T> cbrt(const shvec3<T>&);                                           // coeff-wise cubic root
template<typename T> PFC_INLINE shvec3<T> rsqrt(const shvec3<T>&);                                          // coeff-wise vector reciprocal square root
template<typename T> PFC_INLINE shvec3<T> rsqrt_z(const shvec3<T>&);                                        // coeff-wise vector reciprocal square root (set 0 for coeffs less than or equal to zero)
template<typename T> PFC_INLINE shvec3<T> rcbrt(const shvec3<T>&);                                          // coeff-wise reciprocal cubic root
template<typename T> PFC_INLINE shvec3<T> rcbrt_z(const shvec3<T>&);                                        // coeff-wise reciprocal cubic root (set 0 for coeffs that are 0)
template<typename T> PFC_INLINE T norm(const shvec3<T>&);                                                   // vector norm (length): |v|
template<typename T> PFC_INLINE T rnorm(const shvec3<T>&);                                                  // reciprocal of the vector norm: 1/|v|
template<typename T> PFC_INLINE T rnorm_z(const shvec3<T>&);                                                // reciprocal of the vector norm: 1/|v| (if |v|=0, return 0)
template<typename T> PFC_INLINE T norm2(const shvec3<T>&);                                                  // squared vector norm: |v|^2
template<typename T> PFC_INLINE T rnorm2(const shvec3<T>&);                                                 // reciprocal of the squared vector norm: 1/|v|^2
template<typename T> PFC_INLINE T rnorm2_z(const shvec3<T>&);                                               // reciprocal of the squared vector norm: 1/|v|^2 (if |v|=0, return 0)
template<typename T> PFC_INLINE T norm_l1(const shvec3<T>&);                                                // vector L1-norm (Manhattan norm)
template<typename T> PFC_INLINE T rnorm_l1(const shvec3<T>&);                                               // reciprocal of the vector L1-norm
template<typename T> PFC_INLINE T rnorm_l1_z(const shvec3<T>&);                                             // reciprocal of the vector L1-norm (if |v|=0, return 0)
template<typename T> PFC_INLINE shvec3<T> exp(const shvec3<T>&);                                            // coeff-wise natural exponent: e^x
template<typename T> PFC_INLINE shvec3<T> exp2(const shvec3<T>&);                                           // coeff-wise 2^x
template<typename T> PFC_INLINE shvec3<T> ln(const shvec3<T>&);                                             // coeff-wise natural logarithm
template<typename T> PFC_INLINE shvec3<T> log2(const shvec3<T>&);                                           // coeff-wise base-2 logarithm
template<typename T> PFC_INLINE shvec3<T> log10(const shvec3<T>&);                                          // coeff-wise base-10 logarithm
template<typename T, typename U> PFC_INLINE shvec3<T> pow(const shvec3<T>&, U);                             // coeff-wise power
template<typename T> PFC_INLINE shvec3<T> unit(const shvec3<T>&);                                           // unit vector of the vector: v/|v|
template<typename T> PFC_INLINE shvec3<T> unit_z(const shvec3<T>&);                                         // unit vector of the vector (if |v|=0, return v=[0, 0])
template<typename T, typename U> PFC_INLINE T dot(const shvec3<T>&, const shvec3<U>&);                      // vector dot-product
template<typename T> PFC_INLINE T dot1(const shvec3<T>&);                                                   // vector coeff sum
template<typename T> PFC_INLINE void neg(shvec3<T>&);                                                       // negate the vector
template<typename T, class Rng> PFC_INLINE void rand_real1(shvec3<T>&, Rng&);                               // random vector where each coeff is in range [-1, 1)
template<typename T, class Rng> PFC_INLINE void rand_ureal1(shvec3<T>&, Rng&);                              // random vector where each coeff is in range [0, 1)
template<typename T> PFC_INLINE shvec3<T> smoothstep(const shvec3<T>&);                                     // coeff-wise smoothstep function
template<typename T> PFC_INLINE shvec3<T> smootherstep(const shvec3<T>&);                                   // coeff-wise smootherstep function
template<typename T, typename U> PFC_INLINE shvec3<T> lerp(const shvec3<T> &shv0_,                          // linear interpolation of vectors: f(t=0)=shv0, f(t=1)=shv1
                                                           const shvec3<T> &shv1_,
                                                           U t_);
template<typename T, typename U> PFC_INLINE void sh_basis(shvec3<T>&, const vec3<U>&);
template<typename T, typename U> shvec3<T> sh_product(const shvec3<T>&, const shvec3<U>&);
template<typename T, typename U> shvec3<T> sh_product(const shvec3<T>&, const zhvec3<U>&);
// ZH2 vector ops
template<typename T> PFC_INLINE bool is_zero(const zhvec2<T>&);                                             // test for zero-vector, i.e. all coeffs equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const zhvec2<T>&);                                              // test for saturated vector, i.e. all coeffs are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const zhvec2<T>&);                                             // test for signed saturated vector, i.e. all coeffs are in range [-1, 1]
template<typename T, typename U> PFC_INLINE bool operator==(const zhvec2<T>&, const zhvec2<U>&);            // test for equality of vectors, i.e. all coeffs of the vectors are equal (exact)
template<typename T, typename U> PFC_INLINE bool operator==(const zhvec2<T>&, U);                           // test for equality of vector and value, i.e. all coeffs of the vector equals the value (exact)
template<typename T, typename U> PFC_INLINE bool operator==(typename U, const zhvec2<T>&);                  // test for equality of vector and value, i.e. all coeffs of the vector equals the value (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(const zhvec2<T>&, const zhvec2<U>&);            // test for inequality of vectors, i.e. any of the coeffs of the vectors are unequal (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(const zhvec2<T>&, U);                           // test for inequality of vector and value, i.e. any of the coeffs of the vector is unequal to the value (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(U, const zhvec2<T>&);                           // test for inequality of vector and value, i.e. any of the coeffs of the vector is unequal to the value (exact)
template<typename T, typename U> PFC_INLINE void operator+=(zhvec2<T>&, const zhvec2<U>&);                  // add vector to vector
template<typename T, typename U> PFC_INLINE void operator+=(zhvec2<T>&, U);                                 // add value to each coeff of the vector
template<typename T, typename U> PFC_INLINE void operator-=(zhvec2<T>&, const zhvec2<U>&);                  // subtract vector from vector
template<typename T, typename U> PFC_INLINE void operator-=(zhvec2<T>&, U);                                 // subtract value from each coeff of the vector
template<typename T, typename U> PFC_INLINE void operator*=(zhvec2<T>&, const zhvec2<U>&);                  // coeff-wise vector by vector multiplication
template<typename T, typename U> PFC_INLINE void operator*=(zhvec2<T>&, U);                                 // vector by value multiplication
template<typename T, typename U> PFC_INLINE void operator/=(zhvec2<T>&, const zhvec2<U>&);                  // coeff-wise vector by vector division
template<typename T, typename U> PFC_INLINE void operator/=(zhvec2<T>&, U);                                 // vector by value division
template<typename T, typename U> PFC_INLINE zhvec2<T> operator+(const zhvec2<T>&, const zhvec2<U>&);        // add vector to vector
template<typename T, typename U> PFC_INLINE zhvec2<T> operator+(const zhvec2<T>&, U);                       // add value to each coeff of the vector
template<typename T, typename U> PFC_INLINE zhvec2<T> operator+(U, const zhvec2<T>&);                       // add each coeff of the vector to a value vector
template<typename T, typename U> PFC_INLINE zhvec2<T> operator-(const zhvec2<T>&, const zhvec2<U>&);        // subtract vector from vector
template<typename T, typename U> PFC_INLINE zhvec2<T> operator-(const zhvec2<T>&, U);                       // subtract value from each coeff of the vector
template<typename T, typename U> PFC_INLINE zhvec2<T> operator-(U, const zhvec2<T>&);                       // subtract each coeff of the vector from a value vector
template<typename T> PFC_INLINE zhvec2<T> operator-(const zhvec2<T>&);                                      // negate the vector
template<typename T, typename U> PFC_INLINE zhvec2<T> operator*(const zhvec2<T>&, const zhvec2<U>&);        // coeff-wise vector by vector multiplication
template<typename T, typename U> PFC_INLINE zhvec2<T> operator*(const zhvec2<T>&, U);                       // vector by value multiplication
template<typename T, typename U> PFC_INLINE zhvec2<T> operator*(U, const zhvec2<T>&);                       // value by vector multiplication
template<typename T, typename U> PFC_INLINE zhvec2<T> operator/(const zhvec2<T>&, const zhvec2<U>&);        // coeff-wise vector by vector division
template<typename T, typename U> PFC_INLINE zhvec2<T> operator/(const zhvec2<T>&, U);                       // vector by value division
template<typename T, typename U> PFC_INLINE zhvec2<T> operator/(U, const zhvec2<T>&);                       // value by vector division
template<typename T> PFC_INLINE T min(const zhvec2<T>&);                                                    // minimum coeff value
template<typename T> PFC_INLINE zhvec2<T> min(const zhvec2<T>&, const zhvec2<T>&);                          // coeff-wise minimum of the vectors
template<typename T> PFC_INLINE zhvec2<T> min(const zhvec2<T>&, const zhvec2<T>&, const zhvec2<T>&);
template<typename T> PFC_INLINE zhvec2<T> min(const zhvec2<T>&, const zhvec2<T>&, const zhvec2<T>&, const zhvec2<T>&);
template<typename T, typename U> PFC_INLINE zhvec2<T> min(const zhvec2<T>&, U);                             // coeff-wise minimum of the vector and value
template<typename T, typename U> PFC_INLINE zhvec2<T> min(U, const zhvec2<T>&);                             // coeff-wise minimum of the vector and value
template<typename T> PFC_INLINE T max(const zhvec2<T>&);                                                    // maximum coeff value
template<typename T> PFC_INLINE zhvec2<T> max(const zhvec2<T>&, const zhvec2<T>&);                          // coeff-wise maximum of the vectors
template<typename T> PFC_INLINE zhvec2<T> max(const zhvec2<T>&, const zhvec2<T>&, const zhvec2<T>&);
template<typename T> PFC_INLINE zhvec2<T> max(const zhvec2<T>&, const zhvec2<T>&, const zhvec2<T>&, const zhvec2<T>&);
template<typename T, typename U> PFC_INLINE zhvec2<T> max(const zhvec2<T>&, U);                             // coeff-wise maximum of the vector and value
template<typename T, typename U> PFC_INLINE zhvec2<T> max(U, const zhvec2<T>&);                             // coeff-wise maximum of the vector and value
template<typename T, typename U> PFC_INLINE zhvec2<T> mul(const zhvec2<T>&, const zhvec2<T>&);              // coeff-wise vector multiply
template<typename T, typename U, typename V> PFC_INLINE zhvec2<T> madd(const zhvec2<T> &zhv0_,              // coeff-wise multiply-add: zhv0_*v1+zhv2_
                                                                       const zhvec2<U> &zhv1_,
                                                                       const zhvec2<V> &zhv2_);
template<typename T, typename U, typename V> PFC_INLINE zhvec2<T> madd(const zhvec2<T> &zhv_,               // vector-value-value multiply-add: zhv_*mul_+add_
                                                                       U mul_,
                                                                       V add_);
template<typename T, typename U, typename V> PFC_INLINE zhvec2<T> madd(const zhvec2<T> &zhv_,               // vector-vector-value multiply-add: zhv_*mul_+add_
                                                                       const zhvec2<U> &mul_,
                                                                       V add_);
template<typename T, typename U, typename V> PFC_INLINE zhvec2<T> madd(const zhvec2<T> &zhv_,               // vector-value-vector multiply-add: zhv_*mul_+add_
                                                                       U mul_,
                                                                       const zhvec2<V> &add_);
template<typename T> PFC_INLINE zhvec2<T> rcp(const zhvec2<T>&);                                            // coeff-wise vector reciprocal
template<typename T> PFC_INLINE zhvec2<T> rcp_z(const zhvec2<T>&);                                          // coeff-wise vector reciprocal (set 0 for 0 coeffs)
template<typename T> PFC_INLINE zhvec2<T> floor(const zhvec2<T>&);                                          // coeff-wise greatest integer less than or equal to the value
template<typename T> PFC_INLINE zhvec2<T> ceil(const zhvec2<T>&);                                           // coeff-wise smallest integer greater than or equal to the value
template<typename T> PFC_INLINE zhvec2<T> trunc(const zhvec2<T>&);                                          // coeff-wise truncate decimal part from the value
template<typename T> PFC_INLINE zhvec2<T> frc(const zhvec2<T>&);                                            // coeff-wise fractional part (for negative values returns 1-fractional part)
template<typename T, typename U> PFC_INLINE zhvec2<T> mod(const zhvec2<T>&, U div_);                        // coeff-wise modulo
template<typename T, typename U> PFC_INLINE zhvec2<T> cycle(const zhvec2<T>&, U cycle_);                    // coeff-wise cycle
template<typename T, typename U> PFC_INLINE zhvec2<T> cycle(const zhvec2<T>&, const zhvec2<U>& cycle_);     // coeff-wise cycle
template<typename T> PFC_INLINE zhvec2<T> cycle1(const zhvec2<T>&);                                         // coeff-wise cycle1
template<typename T> PFC_INLINE zhvec2<T> sat(const zhvec2<T>&);                                            // coeff-wise vector saturate
template<typename T> PFC_INLINE zhvec2<T> ssat(const zhvec2<T>&);                                           // coeff-wise vector signed saturate
template<typename T, typename U> PFC_INLINE zhvec2<T> clamp(const zhvec2<T>&,                               // coeff-wise clamp of the vector
                                                            const zhvec2<U> &min_,
                                                            const zhvec2<U> &max_);
template<typename T, typename U> PFC_INLINE zhvec2<T> clamp(const zhvec2<T>&,                               // coeff-wise clamp of the vector with values
                                                            U min_,
                                                            U max_);
template<typename T> PFC_INLINE zhvec2<T> abs(const zhvec2<T>&);                                            // coeff-wise vector absolute
template<typename T> PFC_INLINE zhvec2<T> sgn(const zhvec2<T>&);                                            // coeff-wise signum (neg=-1, pos=+1, zero=0)
template<typename T> PFC_INLINE zhvec2<T> sgn_zp(const zhvec2<T>&);                                         // coeff-wise signum (neg=-1, pos&zero=+1)
template<typename T> PFC_INLINE zhvec2<T> sqr(const zhvec2<T>&);                                            // coeff-wise square: x*x
template<typename T> PFC_INLINE zhvec2<T> cubic(const zhvec2<T>&);                                          // coeff-wise cubic: x*x*x
template<typename T> PFC_INLINE zhvec2<T> sqrt(const zhvec2<T>&);                                           // coeff-wise square root
template<typename T> PFC_INLINE zhvec2<T> sqrt_z(const zhvec2<T>&);                                         // coeff-wise square root (set 0 for coeffs less than zero)
template<typename T> PFC_INLINE zhvec2<T> cbrt(const zhvec2<T>&);                                           // coeff-wise cubic root
template<typename T> PFC_INLINE zhvec2<T> rsqrt(const zhvec2<T>&);                                          // coeff-wise vector reciprocal square root
template<typename T> PFC_INLINE zhvec2<T> rsqrt_z(const zhvec2<T>&);                                        // coeff-wise vector reciprocal square root (set 0 for coeffs less than or equal to zero)
template<typename T> PFC_INLINE zhvec2<T> rcbrt(const zhvec2<T>&);                                          // coeff-wise reciprocal cubic root
template<typename T> PFC_INLINE zhvec2<T> rcbrt_z(const zhvec2<T>&);                                        // coeff-wise reciprocal cubic root (set 0 for coeffs that are 0)
template<typename T> PFC_INLINE T norm(const zhvec2<T>&);                                                   // vector norm (length): |v|
template<typename T> PFC_INLINE T rnorm(const zhvec2<T>&);                                                  // reciprocal of the vector norm: 1/|v|
template<typename T> PFC_INLINE T rnorm_z(const zhvec2<T>&);                                                // reciprocal of the vector norm: 1/|v| (if |v|=0, return 0)
template<typename T> PFC_INLINE T norm2(const zhvec2<T>&);                                                  // squared vector norm: |v|^2
template<typename T> PFC_INLINE T rnorm2(const zhvec2<T>&);                                                 // reciprocal of the squared vector norm: 1/|v|^2
template<typename T> PFC_INLINE T rnorm2_z(const zhvec2<T>&);                                               // reciprocal of the squared vector norm: 1/|v|^2 (if |v|=0, return 0)
template<typename T> PFC_INLINE T norm_l1(const zhvec2<T>&);                                                // vector L1-norm (Manhattan norm)
template<typename T> PFC_INLINE T rnorm_l1(const zhvec2<T>&);                                               // reciprocal of the vector L1-norm
template<typename T> PFC_INLINE T rnorm_l1_z(const zhvec2<T>&);                                             // reciprocal of the vector L1-norm (if |v|=0, return 0)
template<typename T> PFC_INLINE zhvec2<T> exp(const zhvec2<T>&);                                            // coeff-wise natural exponent: e^x
template<typename T> PFC_INLINE zhvec2<T> exp2(const zhvec2<T>&);                                           // coeff-wise 2^x
template<typename T> PFC_INLINE zhvec2<T> ln(const zhvec2<T>&);                                             // coeff-wise natural logarithm
template<typename T> PFC_INLINE zhvec2<T> log2(const zhvec2<T>&);                                           // coeff-wise base-2 logarithm
template<typename T> PFC_INLINE zhvec2<T> log10(const zhvec2<T>&);                                          // coeff-wise base-10 logarithm
template<typename T, typename U> PFC_INLINE zhvec2<T> pow(const zhvec2<T>&, U);                             // coeff-wise power
template<typename T> PFC_INLINE zhvec2<T> unit(const zhvec2<T>&);                                           // unit vector of the vector: v/|v|
template<typename T> PFC_INLINE zhvec2<T> unit_z(const zhvec2<T>&);                                         // unit vector of the vector (if |v|=0, return v=[0, 0])
template<typename T, typename U> PFC_INLINE T dot(const zhvec2<T>&, const zhvec2<U>&);                      // vector dot-product
template<typename T> PFC_INLINE T dot1(const zhvec2<T>&);                                                   // vector coeff sum
template<typename T> PFC_INLINE void neg(zhvec2<T>&);                                                       // negate the vector
template<typename T, class Rng> PFC_INLINE void rand_real1(zhvec2<T>&, Rng&);                               // random vector where each coeff is in range [-1, 1)
template<typename T, class Rng> PFC_INLINE void rand_ureal1(zhvec2<T>&, Rng&);                              // random vector where each coeff is in range [0, 1)
template<typename T> PFC_INLINE zhvec2<T> smoothstep(const zhvec2<T>&);                                     // coeff-wise smoothstep function
template<typename T> PFC_INLINE zhvec2<T> smootherstep(const zhvec2<T>&);                                   // coeff-wise smootherstep function
template<typename T, typename U> PFC_INLINE shvec2<T> lerp(const zhvec2<T> &zhv0_,                          // linear interpolation of vectors: f(t=0)=zhv0, f(t=1)=zhv1
                                                           const zhvec2<T> &zhv1_,
                                                           U t_);
// ZH3 vector ops
template<typename T> PFC_INLINE bool is_zero(const zhvec3<T>&);                                             // test for zero-vector, i.e. all coeffs equal zero (exact)
template<typename T> PFC_INLINE bool is_sat(const zhvec3<T>&);                                              // test for saturated vector, i.e. all coeffs are in range [0, 1]
template<typename T> PFC_INLINE bool is_ssat(const zhvec3<T>&);                                             // test for signed saturated vector, i.e. all coeffs are in range [-1, 1]
template<typename T, typename U> PFC_INLINE bool operator==(const zhvec3<T>&, const zhvec3<U>&);            // test for equality of vectors, i.e. all coeffs of the vectors are equal (exact)
template<typename T, typename U> PFC_INLINE bool operator==(const zhvec3<T>&, U);                           // test for equality of vector and value, i.e. all coeffs of the vector equals the value (exact)
template<typename T, typename U> PFC_INLINE bool operator==(typename U, const zhvec3<T>&);                  // test for equality of vector and value, i.e. all coeffs of the vector equals the value (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(const zhvec3<T>&, const zhvec3<U>&);            // test for inequality of vectors, i.e. any of the coeffs of the vectors are unequal (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(const zhvec3<T>&, U);                           // test for inequality of vector and value, i.e. any of the coeffs of the vector is unequal to the value (exact)
template<typename T, typename U> PFC_INLINE bool operator!=(U, const zhvec3<T>&);                           // test for inequality of vector and value, i.e. any of the coeffs of the vector is unequal to the value (exact)
template<typename T, typename U> PFC_INLINE void operator+=(zhvec3<T>&, const zhvec3<U>&);                  // add vector to vector
template<typename T, typename U> PFC_INLINE void operator+=(zhvec3<T>&, U);                                 // add value to each coeff of the vector
template<typename T, typename U> PFC_INLINE void operator-=(zhvec3<T>&, const zhvec3<U>&);                  // subtract vector from vector
template<typename T, typename U> PFC_INLINE void operator-=(zhvec3<T>&, U);                                 // subtract value from each coeff of the vector
template<typename T, typename U> PFC_INLINE void operator*=(zhvec3<T>&, const zhvec3<U>&);                  // coeff-wise vector by vector multiplication
template<typename T, typename U> PFC_INLINE void operator*=(zhvec3<T>&, U);                                 // vector by value multiplication
template<typename T, typename U> PFC_INLINE void operator/=(zhvec3<T>&, const zhvec3<U>&);                  // coeff-wise vector by vector division
template<typename T, typename U> PFC_INLINE void operator/=(zhvec3<T>&, U);                                 // vector by value division
template<typename T, typename U> PFC_INLINE zhvec3<T> operator+(const zhvec3<T>&, const zhvec3<U>&);        // add vector to vector
template<typename T, typename U> PFC_INLINE zhvec3<T> operator+(const zhvec3<T>&, U);                       // add value to each coeff of the vector
template<typename T, typename U> PFC_INLINE zhvec3<T> operator+(U, const zhvec3<T>&);                       // add each coeff of the vector to a value vector
template<typename T, typename U> PFC_INLINE zhvec3<T> operator-(const zhvec3<T>&, const zhvec3<U>&);        // subtract vector from vector
template<typename T, typename U> PFC_INLINE zhvec3<T> operator-(const zhvec3<T>&, U);                       // subtract value from each coeff of the vector
template<typename T, typename U> PFC_INLINE zhvec3<T> operator-(U, const zhvec3<T>&);                       // subtract each coeff of the vector from a value vector
template<typename T> PFC_INLINE zhvec3<T> operator-(const zhvec3<T>&);                                      // negate the vector
template<typename T, typename U> PFC_INLINE zhvec3<T> operator*(const zhvec3<T>&, const zhvec3<U>&);        // coeff-wise vector by vector multiplication
template<typename T, typename U> PFC_INLINE zhvec3<T> operator*(const zhvec3<T>&, U);                       // vector by value multiplication
template<typename T, typename U> PFC_INLINE zhvec3<T> operator*(U, const zhvec3<T>&);                       // value by vector multiplication
template<typename T, typename U> PFC_INLINE zhvec3<T> operator/(const zhvec3<T>&, const zhvec3<U>&);        // coeff-wise vector by vector division
template<typename T, typename U> PFC_INLINE zhvec3<T> operator/(const zhvec3<T>&, U);                       // vector by value division
template<typename T, typename U> PFC_INLINE zhvec3<T> operator/(U, const zhvec3<T>&);                       // value by vector division
template<typename T> PFC_INLINE T min(const zhvec3<T>&);                                                    // minimum coeff value
template<typename T> PFC_INLINE zhvec3<T> min(const zhvec3<T>&, const zhvec3<T>&);                          // coeff-wise minimum of the vectors
template<typename T> PFC_INLINE zhvec3<T> min(const zhvec3<T>&, const zhvec3<T>&, const zhvec3<T>&);
template<typename T> PFC_INLINE zhvec3<T> min(const zhvec3<T>&, const zhvec3<T>&, const zhvec3<T>&, const zhvec3<T>&);
template<typename T, typename U> PFC_INLINE zhvec3<T> min(const zhvec3<T>&, U);                             // coeff-wise minimum of the vector and value
template<typename T, typename U> PFC_INLINE zhvec3<T> min(U, const zhvec3<T>&);                             // coeff-wise minimum of the vector and value
template<typename T> PFC_INLINE T max(const zhvec3<T>&);                                                    // maximum coeff value
template<typename T> PFC_INLINE zhvec3<T> max(const zhvec3<T>&, const zhvec3<T>&);                          // coeff-wise maximum of the vectors
template<typename T> PFC_INLINE zhvec3<T> max(const zhvec3<T>&, const zhvec3<T>&, const zhvec3<T>&);
template<typename T> PFC_INLINE zhvec3<T> max(const zhvec3<T>&, const zhvec3<T>&, const zhvec3<T>&, const zhvec3<T>&);
template<typename T, typename U> PFC_INLINE zhvec3<T> max(const zhvec3<T>&, U);                             // coeff-wise maximum of the vector and value
template<typename T, typename U> PFC_INLINE zhvec3<T> max(U, const zhvec3<T>&);                             // coeff-wise maximum of the vector and value
template<typename T, typename U> PFC_INLINE zhvec3<T> mul(const zhvec3<T>&, const zhvec3<T>&);              // coeff-wise vector multiply
template<typename T, typename U, typename V> PFC_INLINE zhvec3<T> madd(const zhvec3<T> &zhv0_,              // coeff-wise multiply-add: zhv0_*v1+zhv2_
                                                                       const zhvec3<U> &zhv1_,
                                                                       const zhvec3<V> &zhv2_);
template<typename T, typename U, typename V> PFC_INLINE zhvec3<T> madd(const zhvec3<T> &zhv_,               // vector-value-value multiply-add: zhv_*mul_+add_
                                                                       U mul_,
                                                                       V add_);
template<typename T, typename U, typename V> PFC_INLINE zhvec3<T> madd(const zhvec3<T> &zhv_,               // vector-vector-value multiply-add: zhv_*mul_+add_
                                                                       const zhvec3<U> &mul_,
                                                                       V add_);
template<typename T, typename U, typename V> PFC_INLINE zhvec3<T> madd(const zhvec3<T> &zhv_,               // vector-value-vector multiply-add: zhv_*mul_+add_
                                                                       U mul_,
                                                                       const zhvec3<V> &add_);
template<typename T> PFC_INLINE zhvec3<T> rcp(const zhvec3<T>&);                                            // coeff-wise vector reciprocal
template<typename T> PFC_INLINE zhvec3<T> rcp_z(const zhvec3<T>&);                                          // coeff-wise vector reciprocal (set 0 for 0 coeffs)
template<typename T> PFC_INLINE zhvec3<T> floor(const zhvec3<T>&);                                          // coeff-wise greatest integer less than or equal to the value
template<typename T> PFC_INLINE zhvec3<T> ceil(const zhvec3<T>&);                                           // coeff-wise smallest integer greater than or equal to the value
template<typename T> PFC_INLINE zhvec3<T> trunc(const zhvec3<T>&);                                          // coeff-wise truncate decimal part from the value
template<typename T> PFC_INLINE zhvec3<T> frc(const zhvec3<T>&);                                            // coeff-wise fractional part (for negative values returns 1-fractional part)
template<typename T, typename U> PFC_INLINE zhvec3<T> mod(const zhvec3<T>&, U div_);                        // coeff-wise modulo
template<typename T, typename U> PFC_INLINE zhvec3<T> cycle(const zhvec3<T>&, U cycle_);                    // coeff-wise cycle
template<typename T, typename U> PFC_INLINE zhvec3<T> cycle(const zhvec3<T>&, const zhvec3<U>& cycle_);     // coeff-wise cycle
template<typename T> PFC_INLINE zhvec3<T> cycle1(const zhvec3<T>&);                                         // coeff-wise cycle1
template<typename T> PFC_INLINE zhvec3<T> sat(const zhvec3<T>&);                                            // coeff-wise vector saturate
template<typename T> PFC_INLINE zhvec3<T> ssat(const zhvec3<T>&);                                           // coeff-wise vector signed saturate
template<typename T, typename U> PFC_INLINE zhvec3<T> clamp(const zhvec3<T>&,                               // coeff-wise clamp of the vector
                                                            const zhvec3<U> &min_,
                                                            const zhvec3<U> &max_);
template<typename T, typename U> PFC_INLINE zhvec3<T> clamp(const zhvec3<T>&,                               // coeff-wise clamp of the vector with values
                                                            U min_,
                                                            U max_);
template<typename T> PFC_INLINE zhvec3<T> abs(const zhvec3<T>&);                                            // coeff-wise vector absolute
template<typename T> PFC_INLINE zhvec3<T> sgn(const zhvec3<T>&);                                            // coeff-wise signum (neg=-1, pos=+1, zero=0)
template<typename T> PFC_INLINE zhvec3<T> sgn_zp(const zhvec3<T>&);                                         // coeff-wise signum (neg=-1, pos&zero=+1)
template<typename T> PFC_INLINE zhvec3<T> sqr(const zhvec3<T>&);                                            // coeff-wise square: x*x
template<typename T> PFC_INLINE zhvec3<T> cubic(const zhvec3<T>&);                                          // coeff-wise cubic: x*x*x
template<typename T> PFC_INLINE zhvec3<T> sqrt(const zhvec3<T>&);                                           // coeff-wise square root
template<typename T> PFC_INLINE zhvec3<T> sqrt_z(const zhvec3<T>&);                                         // coeff-wise square root (set 0 for coeffs less than zero)
template<typename T> PFC_INLINE zhvec3<T> cbrt(const zhvec3<T>&);                                           // coeff-wise cubic root
template<typename T> PFC_INLINE zhvec3<T> rsqrt(const zhvec3<T>&);                                          // coeff-wise vector reciprocal square root
template<typename T> PFC_INLINE zhvec3<T> rsqrt_z(const zhvec3<T>&);                                        // coeff-wise vector reciprocal square root (set 0 for coeffs less than or equal to zero)
template<typename T> PFC_INLINE zhvec3<T> rcbrt(const zhvec3<T>&);                                          // coeff-wise reciprocal cubic root
template<typename T> PFC_INLINE zhvec3<T> rcbrt_z(const zhvec3<T>&);                                        // coeff-wise reciprocal cubic root (set 0 for coeffs that are 0)
template<typename T> PFC_INLINE T norm(const zhvec3<T>&);                                                   // vector norm (length): |v|
template<typename T> PFC_INLINE T rnorm(const zhvec3<T>&);                                                  // reciprocal of the vector norm: 1/|v|
template<typename T> PFC_INLINE T rnorm_z(const zhvec3<T>&);                                                // reciprocal of the vector norm: 1/|v| (if |v|=0, return 0)
template<typename T> PFC_INLINE T norm2(const zhvec3<T>&);                                                  // squared vector norm: |v|^2
template<typename T> PFC_INLINE T rnorm2(const zhvec3<T>&);                                                 // reciprocal of the squared vector norm: 1/|v|^2
template<typename T> PFC_INLINE T rnorm2_z(const zhvec3<T>&);                                               // reciprocal of the squared vector norm: 1/|v|^2 (if |v|=0, return 0)
template<typename T> PFC_INLINE T norm_l1(const zhvec3<T>&);                                                // vector L1-norm (Manhattan norm)
template<typename T> PFC_INLINE T rnorm_l1(const zhvec3<T>&);                                               // reciprocal of the vector L1-norm
template<typename T> PFC_INLINE T rnorm_l1_z(const zhvec3<T>&);                                             // reciprocal of the vector L1-norm (if |v|=0, return 0)
template<typename T> PFC_INLINE zhvec3<T> exp(const zhvec3<T>&);                                            // coeff-wise natural exponent: e^x
template<typename T> PFC_INLINE zhvec3<T> exp2(const zhvec3<T>&);                                           // coeff-wise 2^x
template<typename T> PFC_INLINE zhvec3<T> ln(const zhvec3<T>&);                                             // coeff-wise natural logarithm
template<typename T> PFC_INLINE zhvec3<T> log2(const zhvec3<T>&);                                           // coeff-wise base-2 logarithm
template<typename T> PFC_INLINE zhvec3<T> log10(const zhvec3<T>&);                                          // coeff-wise base-10 logarithm
template<typename T, typename U> PFC_INLINE zhvec3<T> pow(const zhvec3<T>&, U);                             // coeff-wise power
template<typename T> PFC_INLINE zhvec3<T> unit(const zhvec3<T>&);                                           // unit vector of the vector: v/|v|
template<typename T> PFC_INLINE zhvec3<T> unit_z(const zhvec3<T>&);                                         // unit vector of the vector (if |v|=0, return v=[0, 0])
template<typename T, typename U> PFC_INLINE T dot(const zhvec3<T>&, const zhvec3<U>&);                      // vector dot-product
template<typename T> PFC_INLINE T dot1(const zhvec3<T>&);                                                   // vector coeff sum
template<typename T> PFC_INLINE void neg(zhvec3<T>&);                                                       // negate the vector
template<typename T, class Rng> PFC_INLINE void rand_real1(zhvec3<T>&, Rng&);                               // random vector where each coeff is in range [-1, 1)
template<typename T, class Rng> PFC_INLINE void rand_ureal1(zhvec3<T>&, Rng&);                              // random vector where each coeff is in range [0, 1)
template<typename T> PFC_INLINE zhvec3<T> smoothstep(const zhvec3<T>&);                                     // coeff-wise smoothstep function
template<typename T> PFC_INLINE zhvec3<T> smootherstep(const zhvec3<T>&);                                   // coeff-wise smootherstep function
template<typename T, typename U> PFC_INLINE shvec2<T> lerp(const zhvec3<T> &zhv0_,                          // linear interpolation of vectors: f(t=0)=zhv0, f(t=1)=zhv1
                                                           const zhvec3<T> &zhv1_,
                                                           U t_);
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
  enum {num_coeffs=4};
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
  enum {num_coeffs=9};
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
  enum {num_coeffs=2};
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
  enum {num_coeffs=3};
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
