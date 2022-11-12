//==========================================7==================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_OPTICS_H
#define PFC_CORE_MATH_OPTICS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "math.h"
namespace pfc
{

// new
// refraction
template<typename T> PFC_INLINE vec2<T> refract_u(const vec2<T> &v_,                              // refract unit vector about unit normal with given index of refraction (IOR) between the material interface
                                                  const vec2<T> &n_,
                                                  typename math<T>::scalar_t ior_);
template<typename T> PFC_INLINE vec3<T> refract_u(const vec3<T> &v_,                              // refract unit vector about unit normal with given index of refraction (IOR) between the material interface
                                                  const vec3<T> &n_,
                                                  typename math<T>::scalar_t ior_);
// reflectance
template<typename T> PFC_INLINE T reflectance(T ior0_, T ior1_);                                  // calculate R0 (normal-incident reflectance) for material interface from the index-of-refraction values of the two materials
template<typename T> PFC_INLINE T fresnel_schlick(const T &r0_,                                   // Schlick's approximation of Fresnel factor
                                                  typename math<T>::scalar_t n_dot_wi_);
template<typename T> PFC_INLINE T fresnel_schlick_tir(const T &r0_,                               // Schlick's approximation of Fresnel factor for optically more to less dense medium interface
                                                      typename math<T>::scalar_t ior_,
                                                      typename math<T>::scalar_t n_dot_wi_);
// BRDF
template<typename T> PFC_INLINE T rcp_smith_gterm(T n_dot_v_, T alpha2_);
template<typename T> PFC_INLINE T brdf_lambert(const T &albedo_,
                                               typename math<T>::scalar_t n_dot_wi_);
template<typename T> PFC_INLINE T brdf_phong(const vec3<typename math<T>::scalar_t> &wo_refl_,
                                             const vec3<typename math<T>::scalar_t> &wi_,
                                             const T &r0_,
                                             typename math<T>::scalar_t pow_,
                                             typename math<T>::scalar_t n_dot_wi_);
template<typename T> PFC_INLINE T brdf_blinn_phong(const vec3<typename math<T>::scalar_t> &wo_,
                                                   const vec3<typename math<T>::scalar_t> &wi_,
                                                   const vec3<typename math<T>::scalar_t> &n_,
                                                   const T &r0_,
                                                   typename math<T>::scalar_t pow_,
                                                   typename math<T>::scalar_t n_dot_wi_);
template<typename T> PFC_INLINE T brdf_ggx(const vec3<typename math<T>::scalar_t> &wo_,
                                           const vec3<typename math<T>::scalar_t> &wi_,
                                           const vec3<typename math<T>::scalar_t> &n_,
                                           const T &r0_,
                                           typename math<T>::scalar_t alpha2_,
                                           typename math<T>::scalar_t rcp_smith_gwo_,
                                           typename math<T>::scalar_t n_dot_wi_);
// BRDF importance sampling
template<typename T> PFC_INLINE T isample_brdf_lambert(vec3<typename math<T>::scalar_t> &wi_,
                                                       const vec2<typename math<T>::scalar_t> &xi_,
                                                       const T &albedo_);
template<typename T> PFC_INLINE T isample_brdf_phong(vec3<typename math<T>::scalar_t> &wi_,
                                                     const vec2<typename math<T>::scalar_t> &xi_,
                                                     const vec3<typename math<T>::scalar_t> &wo_,
                                                     const T &r0_,
                                                     typename math<T>::scalar_t pow_);
template<typename T> PFC_INLINE T isample_brdf_blinn_phong(vec3<typename math<T>::scalar_t> &wi_,
                                                           const vec2<typename math<T>::scalar_t> &xi_,
                                                           const vec3<typename math<T>::scalar_t> &wo_,
                                                           const vec3<typename math<T>::scalar_t> &n_,
                                                           const T &r0_,
                                                           typename math<T>::scalar_t pow_);
template<typename T> PFC_INLINE T isample_brdf_ggx(vec3<typename math<T>::scalar_t> &wi_,
                                                   const vec2<typename math<T>::scalar_t> &xi_,
                                                   const vec3<typename math<T>::scalar_t> &wo_,
                                                   const mat33<typename math<T>::scalar_t> &tbn_,
                                                   const T &r0_,
                                                   typename math<T>::scalar_t alpha2_,
                                                   typename math<T>::scalar_t rcp_smith_gwo_);
template<typename T> PFC_INLINE vec3<T> isample_brdf_ggx(const vec2<T> &xi_,
                                                         typename math<T>::scalar_t alpha2_);
//----------------------------------------------------------------------------

//============================================================================
#include "optics.inl"
} // namespace pfc
#endif
