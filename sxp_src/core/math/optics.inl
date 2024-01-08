//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// reflections & refractions
//============================================================================
template<typename T>
PFC_INLINE vec2<T> refract_u(const vec2<T> &v_, const vec2<T> &n_, typename math<T>::scalar_t ior_)
{
  // refract vector about normal with given IOR between the interface
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t d=dot(v_, n_);
  scalar_t k=scalar_t(1)-ior_*ior_*(scalar_t(1)-d*d);
  return k<0?vec2<T>::s_zero:ior_*v_-(ior_*d-sqrt(k))*n_;
}
//----

template<typename T>
PFC_INLINE vec3<T> refract_u(const vec3<T> &v_, const vec3<T> &n_, typename math<T>::scalar_t ior_)
{
  // refract vector about normal with given IOR between the interface
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t d=dot(v_, n_);
  scalar_t k=scalar_t(1)-ior_*ior_*(scalar_t(1)-d*d);
  return k<0?vec3<T>::s_zero:ior_*v_-(ior_*d-sqrt(k))*n_;
}
//----

template<typename T>
PFC_INLINE T reflectance(T ior0_, T ior1_)
{
  T v=(ior0_-ior1_)/(ior0_+ior1_);
  return v*v;
}
//----

template<typename T>
PFC_INLINE T fresnel_schlick(const T &r0_, typename math<T>::scalar_t n_dot_wi_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return r0_+(scalar_t(1)-r0_)*pow(scalar_t(1)-n_dot_wi_, scalar_t(5));
}
//----

template<typename T>
PFC_INLINE T fresnel_schlick_tir(const T &r0_, typename math<T>::scalar_t ior_, typename math<T>::scalar_t n_dot_wi_)
{
  typedef typename math<T>::scalar_t scalar_t;
  n_dot_wi_=sqrt(max(scalar_t(0), scalar_t(1)-ior_*ior_*(scalar_t(1)-n_dot_wi_*n_dot_wi_)));
  return r0_+(scalar_t(1)-r0_)*pow(scalar_t(1)-n_dot_wi_, scalar_t(5));
}
//----------------------------------------------------------------------------


//============================================================================
// BRDF
//============================================================================
template<typename T>
PFC_INLINE T rcp_smith_gterm(T n_dot_v_, T alpha2_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return n_dot_v_+sqrt(alpha2_+n_dot_v_*n_dot_v_*(scalar_t(1)-alpha2_));
}
//----

template<typename T>
PFC_INLINE T brdf_lambert(const T &albedo_, typename math<T>::scalar_t n_dot_wi_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return albedo_*(n_dot_wi_*math<scalar_t>::rpi);
}
//----

template<typename T>
PFC_INLINE T brdf_phong(const vec3<typename math<T>::scalar_t> &wo_refl_, const vec3<typename math<T>::scalar_t> &wi_, const T &r0_, typename math<T>::scalar_t pow_, typename math<T>::scalar_t n_dot_wi_)
{
  return fresnel_schlick(r0_, n_dot_wi_)*((pow_+scalar_t(1))*math<T>::half_rpi*pow(sat(dot(wi_, wo_refl_)), pow_));
}
//----

template<typename T>
PFC_INLINE T brdf_blinn_phong(const vec3<typename math<T>::scalar_t> &wo_, const vec3<typename math<T>::scalar_t> &wi_, const vec3<typename math<T>::scalar_t> &n_, const T &r0_, typename math<T>::scalar_t pow_, typename math<T>::scalar_t n_dot_wi_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return fresnel_schlick(r0_, n_dot_wi_)*((pow_+scalar_t(2))*math<T>::half_rpi*pow(sat(dot(n_, unit(wo_+wi_))), pow_)*n_dot_wi_);
}
//----

template<typename T>
PFC_INLINE T brdf_ggx(const vec3<typename math<T>::scalar_t> &wo_, const vec3<typename math<T>::scalar_t> &wi_, const vec3<typename math<T>::scalar_t> &n_, const T &r0_, typename math<T>::scalar_t alpha2_, typename math<T>::scalar_t rcp_smith_gwo_, typename math<T>::scalar_t n_dot_wi_)
{
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t n_dot_h=sat(dot(n_, unit(wo_+wi_)));
  scalar_t ndf_denom=n_dot_h*n_dot_h*(alpha2_-scalar_t(1))+scalar_t(1);
  scalar_t rcp_smith_gwi=rcp_smith_gterm(n_dot_wi_, alpha2_);
  return fresnel_schlick(r0_, n_dot_wi_)*(n_dot_wi_*alpha2_*rcp_z(math<scalar_t>::pi*ndf_denom*ndf_denom*rcp_smith_gwo_*rcp_smith_gwi));
}
//----------------------------------------------------------------------------


//============================================================================
// BRDF importance sampling
//============================================================================
template<typename T>
PFC_INLINE T isample_brdf_lambert(vec3<typename math<T>::scalar_t> &sample_dir_, const vec2<typename math<T>::scalar_t> &xi_, const T &albedo_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
PFC_INLINE T isample_brdf_phong(vec3<typename math<T>::scalar_t> &sample_dir_, const vec2<typename math<T>::scalar_t> &xi_, const vec3<typename math<T>::scalar_t> &wo_, const T &r0_, typename math<T>::scalar_t pow_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
PFC_INLINE T isample_brdf_blinn_phong(vec3<typename math<T>::scalar_t> &sample_dir_, const vec2<typename math<T>::scalar_t> &xi_, const vec3<typename math<T>::scalar_t> &wo_, const vec3<typename math<T>::scalar_t> &n_, const T &r0_, typename math<T>::scalar_t pow_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
PFC_INLINE T isample_brdf_ggx(vec3<typename math<T>::scalar_t> &wi_, const vec2<typename math<T>::scalar_t> &xi_, const vec3<typename math<T>::scalar_t> &wo_, const mat33<typename math<T>::scalar_t> &tbn_, const T &r0_, typename math<T>::scalar_t alpha2_, typename math<T>::scalar_t rcp_smith_gwo_)
{
  // generate GGX sample direction using PDF=NDF
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t cp, sp;
  sincos(sp, cp, math<scalar_t>::two_pi*xi_.x);
  scalar_t ct=sqrt((scalar_t(1)-xi_.y)/(scalar_t(1)+(alpha2_-scalar_t(1))*xi_.y));
  scalar_t st=sqrt(scalar_t(1)-ct*ct);
  vec3<scalar_t> h(st*cp, st*sp, ct);
  h*=tbn_;
  scalar_t v_dot_h=dot(v, h);
  vec3<scalar_t> l=scalar_t(2)*v_dot_h*h-v;

  scalar_t n_dot_l=dot(tbn_.z, l);
  scalar_t rcp_smith_gwi=rcp_smith_gterm(n_dot_l, alpha2_);
  scalar_t l_dot_h=sat(dot(l, h));
  scalar_t n_dot_h=sat(dot(tbn_.z, h));
  return fresnel_schlick(r0_, l_dot_h)*(4.0f*n_dot_l*v_dot_h*rcp(rcp_smith_gwi*rcp_smith_gwo_*n_dot_h)); // pdf_l=pdf_h/(4.0f*l_dot_h), pdf_h=D*cos(theta_h)
}
//----

template<typename T>
PFC_INLINE vec3<T> isample_brdf_ggx(const vec2<T> &xi_, typename math<T>::scalar_t alpha2_)
{
  // generate GGX sample direction using PDF=NDF
  typedef typename math<vec2<T> >::scalar_t scalar_t;
  scalar_t cp, sp;
  sincos(sp, cp, math<scalar_t>::two_pi*xi_.x);
  scalar_t ct=sqrt((scalar_t(1)-xi_.y)/(scalar_t(1)+(alpha2_-scalar_t(1))*xi_.y));
  scalar_t st=sqrt(scalar_t(1)-ct*ct);
  return vec3<scalar_t>(st*cp, st*sp, ct);
}
//----------------------------------------------------------------------------
