//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_COLOR_H
#define PFC_CORE_MATH_COLOR_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "math.h"
#include "numeric.h"
namespace pfc
{

// new
template<typename> struct color_rgb;
template<typename> struct color_rgba;
template<typename> struct color_xyz;
template<typename> struct color_xyza;
template<typename> struct color_yiq;
template<typename> struct color_yiqa;
template<typename> struct color_hsv;
template<typename> struct color_hsva;
// RGB color types
typedef color_rgb<float32_t> color_rgbf;
typedef color_rgb<float64_t> color_rgbd;
typedef color_rgb<uint8_t> color_rgb32;
typedef color_rgb<int32_t> color_rgbi;
typedef color_rgb<uint32_t> color_rgbu;
typedef color_rgb<simd_float4> simd_color_rgbf;
typedef color_rgba<float32_t> color_rgbaf;
typedef color_rgba<float64_t> color_rgbad;
typedef color_rgba<uint8_t> color_rgba32;
typedef color_rgba<int32_t> color_rgbai;
typedef color_rgba<uint32_t> color_rgbau;
typedef color_rgba<simd_float4> simd_color_rgbaf;
// XYZ color types
typedef color_xyz<float32_t> color_xyzf;
typedef color_xyz<float64_t> color_xyzd;
typedef color_xyz<uint8_t> color_xyz32;
typedef color_xyz<int32_t> color_xyzi;
typedef color_xyz<uint32_t> color_xyzu;
typedef color_xyz<simd_float4> simd_color_xyzf;
typedef color_xyza<float32_t> color_xyzaf;
typedef color_xyza<float64_t> color_xyzad;
typedef color_xyza<uint8_t> color_xyza32;
typedef color_xyza<int32_t> color_xyzai;
typedef color_xyza<uint32_t> color_xyzau;
typedef color_xyza<simd_float4> simd_color_xyzaf;
// YIQ color types
typedef color_yiq<float32_t> color_yiqf;
typedef color_yiq<float64_t> color_yiqd;
typedef color_yiq<uint8_t> color_yiq32;
typedef color_yiq<int32_t> color_yiqi;
typedef color_yiq<uint32_t> color_yiqu;
typedef color_yiq<simd_float4> simd_color_yiqf;
typedef color_yiqa<float32_t> color_yiqaf;
typedef color_yiqa<float64_t> color_yiqad;
typedef color_yiqa<uint8_t> color_yiqa32;
typedef color_yiqa<int32_t> color_yiqai;
typedef color_yiqa<uint32_t> color_yiqau;
typedef color_yiqa<simd_float4> simd_color_yiqaf;
// HSV color types
typedef color_hsv<float32_t> color_hsvf;
typedef color_hsv<float64_t> color_hsvd;
typedef color_hsv<uint8_t> color_hsv32;
typedef color_hsv<int32_t> color_hsvi;
typedef color_hsv<uint32_t> color_hsvu;
typedef color_hsv<simd_float4> simd_color_hsvf;
typedef color_hsva<float32_t> color_hsvaf;
typedef color_hsva<float64_t> color_hsvad;
typedef color_hsva<uint8_t> color_hsva32;
typedef color_hsva<int32_t> color_hsvai;
typedef color_hsva<uint32_t> color_hsvau;
typedef color_hsva<simd_float4> simd_color_hsvaf;
// RGB color spaces
enum e_rgb_color_space
{
  rgbcs_srgb,     // sRGB / Rec. 709 / BT.709
  rgbcs_rec2020,  // Rec. 2020 / BT.2020
  rgbcs_dcip3,    // DCI-P3
  rgbcs_dcip3t,   // DCI-P3 Theater
  rgbcs_adobe,    // Adobe RGB
  rgbcs_adobe_wg, // Adobe Wide Gamut RGB
  rgbcs_prophoto, // ProPhoto
  rgbcs_aces_ap0, // ACES AP0
  rgbcs_aces_ap1, // ACES AP1
};
PFC_ENUM(e_rgb_color_space);
// RGB <-> XYZ color space conversion
template<typename T> mat33<T> tform_rgb_to_xyz(const vec2<T> &prim_rxy_, const vec2<T> &prim_gxy_, const vec2<T> &prim_bxy_, const vec2<T> &wp_);
template<typename T> mat33<T> tform_xyz_to_rgb(const vec2<T> &prim_rxy_, const vec2<T> &prim_gxy_, const vec2<T> &prim_bxy_, const vec2<T> &wp_);
template<typename T> mat33<T> tform_rgb_to_xyz(e_rgb_color_space);
template<typename T> mat33<T> tform_xyz_to_rgb(e_rgb_color_space);
// RGB <-> YIQ color space conversion
template<typename T> PFC_INLINE mat33<T> tform_srgb_to_yiq();
template<typename T> PFC_INLINE mat33<T> tform_yiq_to_srgb();
template<typename T> PFC_INLINE color_yiq<T> srgb_to_yiq(const color_rgb<T>&);
template<typename T> PFC_INLINE color_rgb<T> yiq_to_srgb(const color_yiq<T>&);
template<typename T> PFC_INLINE color_yiqa<T> srgb_to_yiq(const color_rgba<T>&);
template<typename T> PFC_INLINE color_rgba<T> yiq_to_srgb(const color_yiqa<T>&);
// RGB <-> HSV color space conversion
template<typename T> color_rgb<T> hsv_to_srgb(const color_hsv<T>&);
template<typename T> color_hsv<T> srgb_to_hsv(const color_rgb<T>&);
template<typename T> color_rgba<T> hsv_to_srgb(const color_hsva<T>&);
template<typename T> color_hsva<T> srgb_to_hsv(const color_rgba<T>&);
// sRGB <-> linear conversion
template<typename T> PFC_INLINE T linear_to_srgb(T);
template<typename T> PFC_INLINE color_rgb<T> linear_to_srgb(const color_rgb<T>&);
template<typename T> PFC_INLINE color_rgba<T> linear_to_srgb(const color_rgba<T>&);
template<typename T> PFC_INLINE T srgb_to_linear(T);
template<typename T> PFC_INLINE color_rgb<T> srgb_to_linear(const color_rgb<T>&);
template<typename T> PFC_INLINE color_rgba<T> srgb_to_linear(const color_rgba<T>&);
// color operations
template<typename T> typename math<T>::scalar_t PFC_INLINE luminance_srgb(const color_rgb<T>&);
template<typename T> typename math<T>::scalar_t PFC_INLINE luminance_srgb(const color_rgba<T>&);
// CIE standard illuminant white points
enum e_cie_white_point
{
  // CIE 1931 2-degree standard observer illuminant white points
  ciewpnt_2deg_a,       // A   (2856K) - Incandescent / Tungsten
  ciewpnt_2deg_b,       // B   (4874K) - Direct sunlight at noon
  ciewpnt_2deg_c,       // C   (6774K) - Average / North sky Daylight
  ciewpnt_2deg_d50,     // D50 (5003K) - Horizon Light. ICC profile PCS
  ciewpnt_2deg_d55,     // D55 (5503K) - Mid-morning / Mid-afternoon Daylight
  ciewpnt_2deg_d60,     // D60 (6000K)
  ciewpnt_2deg_d65,     // D65 (6504K) - Noon Daylight: Television, sRGB color space
  ciewpnt_2deg_d65_p3t, // D65 DCI-P3 Theater
  ciewpnt_2deg_d75,     // D75 (7504K) - North sky Daylight
  ciewpnt_2deg_e,       // E   (5454K) - Equal energy
  ciewpnt_2deg_f1,      // F1  (6430K) - Daylight Fluorescent
  ciewpnt_2deg_f2,      // F2  (4230K) - Cool White Fluorescent
  ciewpnt_2deg_f3,      // F3  (3450K) - White Fluorescent
  ciewpnt_2deg_f4,      // F4  (2940K) - Warm White Fluorescent
  ciewpnt_2deg_f5,      // F5  (6350K) - Daylight Fluorescent
  ciewpnt_2deg_f6,      // F6  (4150K) - Lite White Fluorescent
  ciewpnt_2deg_f7,      // F7  (6500K) - D65 simulator, Daylight simulator
  ciewpnt_2deg_f8,      // F8  (5000K) - D50 simulator, Sylvania F40 Design 50t
  ciewpnt_2deg_f9,      // F9  (4150K) - Cool White Deluxe Fluorescent
  ciewpnt_2deg_f10,     // F10 (5000K) - Philips TL85, Ultralume 50
  ciewpnt_2deg_f11,     // F11 (4000K) - Philips TL84, Ultralume 40
  ciewpnt_2deg_f12,     // F12 (3000K) - Philips TL83, Ultralume 30
  // CIE 1964 10-degree standard observer illuminant white points
  ciewpnt_10deg_a,      // A   (2856K) - Incandescent / Tungsten
  ciewpnt_10deg_b,      // B   (4874K) - Direct sunlight at noon
  ciewpnt_10deg_c,      // C   (6774K) - Average / North sky Daylight
  ciewpnt_10deg_d50,    // D50 (5003K) - Horizon Light. ICC profile PCS
  ciewpnt_10deg_d55,    // D55 (5503K) - Mid-morning / Mid-afternoon Daylight
  ciewpnt_10deg_d65,    // D65 (6504K) - Noon Daylight: Television, sRGB color space
  ciewpnt_10deg_d75,    // D75 (7504K) - North sky Daylight
  ciewpnt_10deg_e,      // E   (5454K) - Equal energy
  ciewpnt_10deg_f1,     // F1  (6430K) - Daylight Fluorescent
  ciewpnt_10deg_f2,     // F2  (4230K) - Cool White Fluorescent
  ciewpnt_10deg_f3,     // F3  (3450K) - White Fluorescent
  ciewpnt_10deg_f4,     // F4  (2940K) - Warm White Fluorescent
  ciewpnt_10deg_f5,     // F5  (6350K) - Daylight Fluorescent
  ciewpnt_10deg_f6,     // F6  (4150K) - Lite White Fluorescent
  ciewpnt_10deg_f7,     // F7  (6500K) - D65 simulator, Daylight simulator
  ciewpnt_10deg_f8,     // F8  (5000K) - D50 simulator, Sylvania F40 Design 50t
  ciewpnt_10deg_f9,     // F9  (4150K) - Cool White Deluxe Fluorescent
  ciewpnt_10deg_f10,    // F10 (5000K) - Philips TL85, Ultralume 50
  ciewpnt_10deg_f11,    // F11 (4000K) - Philips TL84, Ultralume 40
  ciewpnt_10deg_f12,    // F12 (3000K) - Philips TL83, Ultralume 30
};
PFC_ENUM(e_cie_white_point);
template<typename T> vec2<T> cie_white_point(e_cie_white_point);
//----------------------------------------------------------------------------


//============================================================================
// math constants
//============================================================================
template<typename T> struct math<color_xyz<T> >:math<T> {};
template<typename T> struct math<color_xyza<T> >:math<T> {};
template<typename T> struct math<color_rgb<T> >:math<T> {};
template<typename T> struct math<color_rgba<T> >:math<T> {};
template<typename T> struct math<color_yiq<T> >:math<T> {};
template<typename T> struct math<color_yiqa<T> >:math<T> {};
template<typename T> struct math<color_hsv<T> >:math<T> {};
template<typename T> struct math<color_hsva<T> >:math<T> {};
//----------------------------------------------------------------------------


//============================================================================
// color_rgb
//============================================================================
template<typename T>
struct color_rgb
{ PFC_MONO(color_rgb) {PFC_MVAR3(r, g, b);}
  // construction
  PFC_INLINE color_rgb();
  PFC_INLINE color_rgb(T v_);
  PFC_INLINE color_rgb(T r_, T g_, T b_);
  PFC_INLINE color_rgb(const color_rgba<T>&);
  template<typename U> PFC_INLINE color_rgb(const color_rgb<U>&);
  template<typename U> PFC_INLINE color_rgb(const color_rgba<U>&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T v_);
  PFC_INLINE void set(T r_, T g_, T b_);
  template<typename U> PFC_INLINE void set(const color_rgb<U>&);
  //--------------------------------------------------------------------------

  T r, g, b;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_rgb<T>, is_type_pod, is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_rgb<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// color_rgba
//============================================================================
template<typename T>
struct color_rgba
{ PFC_MONO(color_rgba) {PFC_MVAR4(r, g, b, a);}
  // construction
  PFC_INLINE color_rgba();
  PFC_INLINE color_rgba(T v_);
  PFC_INLINE color_rgba(T r_, T g_, T b_);
  PFC_INLINE color_rgba(T r_, T g_, T b_, T a_);
  PFC_INLINE color_rgba(const color_rgb<T>&);
  PFC_INLINE color_rgba(const color_rgb<T>&, T a_);
  template<typename U> PFC_INLINE color_rgba(const color_rgba<U>&);
  template<typename U> PFC_INLINE color_rgba(const color_rgb<U>&);
  template<typename U> PFC_INLINE color_rgba(const color_rgb<U>&, U a_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T v_);
  PFC_INLINE void set(T r_, T g_, T b_);
  PFC_INLINE void set(T r_, T g_, T b_, T a_);
  PFC_INLINE void set(const color_rgb<T>&, T a_);
  template<typename U> PFC_INLINE void set(const color_rgba<U>&);
  //--------------------------------------------------------------------------

  T r, g, b, a;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_rgba<T>, is_type_pod, is_type_pod<vec4<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_rgba<T>, is_type_pod_stream, is_type_pod_stream<vec4<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// color_xyz
//============================================================================
template<typename T>
struct color_xyz
{ PFC_MONO(color_xyz) {PFC_MVAR3(x, y, z);}
  // construction
  PFC_INLINE color_xyz();
  PFC_INLINE color_xyz(T v_);
  PFC_INLINE color_xyz(T x_, T y_, T z_);
  PFC_INLINE color_xyz(const color_xyza<T>&);
  template<typename U> PFC_INLINE color_xyz(const color_xyz<U>&);
  template<typename U> PFC_INLINE color_xyz(const color_xyza<U>&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T v_);
  PFC_INLINE void set(T x_, T y_, T z_);
  template<typename U> PFC_INLINE void set(const color_xyz<U>&);
  //--------------------------------------------------------------------------

  T x, y, z;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_xyz<T>, is_type_pod, is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_xyz<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// color_xyza
//============================================================================
template<typename T>
struct color_xyza
{ PFC_MONO(color_xyza) {PFC_MVAR4(x, y, z, a);}
  // construction
  PFC_INLINE color_xyza();
  PFC_INLINE color_xyza(T v_);
  PFC_INLINE color_xyza(T x_, T y_, T z_);
  PFC_INLINE color_xyza(T x_, T y_, T z_, T a_);
  PFC_INLINE color_xyza(const color_xyz<T>&);
  PFC_INLINE color_xyza(const color_xyz<T>&, T a_);
  template<typename U> PFC_INLINE color_xyza(const color_xyza<U>&);
  template<typename U> PFC_INLINE color_xyza(const color_xyz<U>&);
  template<typename U> PFC_INLINE color_xyza(const color_xyz<U>&, U a_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T v_);
  PFC_INLINE void set(T x_, T y_, T z_);
  PFC_INLINE void set(T x_, T y_, T z_, T a_);
  PFC_INLINE void set(const color_xyz<T>&, T a_);
  template<typename U> PFC_INLINE void set(const color_xyza<U>&);
  //--------------------------------------------------------------------------

  T x, y, z, a;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_xyza<T>, is_type_pod, is_type_pod<vec4<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_xyza<T>, is_type_pod_stream, is_type_pod_stream<vec4<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// color_yiq
//============================================================================
template<typename T>
struct color_yiq
{ PFC_MONO(color_yiq) {PFC_MVAR3(y, i, q);}
  // construction
  PFC_INLINE color_yiq();
  PFC_INLINE color_yiq(T y_, T i_, T q_);
  PFC_INLINE color_yiq(const color_yiqa<T>&);
  template<typename U> PFC_INLINE color_yiq(const color_yiq<U>&);
  template<typename U> PFC_INLINE color_yiq(const color_yiqa<U>&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T y_, T i_, T q_);
  template<typename U> PFC_INLINE void set(const color_yiq<U>&);
  //--------------------------------------------------------------------------

  T y, i, q;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_yiq<T>, is_type_pod, is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_yiq<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// color_yiqa
//============================================================================
template<typename T>
struct color_yiqa
{ PFC_MONO(color_yiqa) {PFC_MVAR4(y, i, q, a);}
  // construction
  PFC_INLINE color_yiqa();
  PFC_INLINE color_yiqa(T y_, T i_, T q_);
  PFC_INLINE color_yiqa(T y_, T i_, T q_, T a_);
  PFC_INLINE color_yiqa(const color_yiq<T>&);
  PFC_INLINE color_yiqa(const color_yiq<T>&, T a_);
  template<typename U> PFC_INLINE color_yiqa(const color_yiqa<U>&);
  template<typename U> PFC_INLINE color_yiqa(const color_yiq<U>&);
  template<typename U> PFC_INLINE color_yiqa(const color_yiq<U>&, U a_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T y_, T i_, T q_);
  PFC_INLINE void set(T y_, T i_, T q_, T a_);
  PFC_INLINE void set(const color_yiq<T>&, T a_);
  template<typename U> PFC_INLINE void set(const color_yiqa<U>&);
  //--------------------------------------------------------------------------

  T y, i, q, a;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_yiqa<T>, is_type_pod, is_type_pod<vec4<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_yiqa<T>, is_type_pod_stream, is_type_pod_stream<vec4<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// color_hsv
//============================================================================
template<typename T>
struct color_hsv
{ PFC_MONO(color_hsv) {PFC_MVAR3(h, s, v);}
  // construction
  PFC_INLINE color_hsv();
  PFC_INLINE color_hsv(T h_, T s_, T v_);
  PFC_INLINE color_hsv(const color_hsva<T>&);
  template<typename U> PFC_INLINE color_hsv(const color_hsv<U>&);
  template<typename U> PFC_INLINE color_hsv(const color_hsva<U>&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T h_, T s_, T v_);
  template<typename U> PFC_INLINE void set(const color_hsv<U>&);
  //--------------------------------------------------------------------------

  T h, s, v;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_hsv<T>, is_type_pod, is_type_pod<vec3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_hsv<T>, is_type_pod_stream, is_type_pod_stream<vec3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// color_hsva
//============================================================================
template<typename T>
struct color_hsva
{ PFC_MONO(color_hsva) {PFC_MVAR4(h, s, v, a);}
  // construction
  PFC_INLINE color_hsva();
  PFC_INLINE color_hsva(T h_, T s_, T v_);
  PFC_INLINE color_hsva(T h_, T s_, T v_, T a_);
  PFC_INLINE color_hsva(const color_hsv<T>&);
  PFC_INLINE color_hsva(const color_hsv<T>&, T a_);
  template<typename U> PFC_INLINE color_hsva(const color_hsva<U>&);
  template<typename U> PFC_INLINE color_hsva(const color_hsv<U>&);
  template<typename U> PFC_INLINE color_hsva(const color_hsv<U>&, U a_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const T &operator[](unsigned idx_) const;
  PFC_INLINE T &operator[](unsigned idx_);
  PFC_INLINE void set(T h_, T s_, T v_);
  PFC_INLINE void set(T h_, T s_, T v_, T a_);
  PFC_INLINE void set(const color_hsv<T>&, T a_);
  template<typename U> PFC_INLINE void set(const color_hsva<U>&);
  //--------------------------------------------------------------------------

  T h, s, v, a;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_hsva<T>, is_type_pod, is_type_pod<vec4<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, color_hsva<T>, is_type_pod_stream, is_type_pod_stream<vec4<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// simd_color_xyzf
//============================================================================
template<>
struct color_xyz<simd_float4>
{ PFC_MONO(simd_color_xyzf) {PFC_MVAR3(x, y, z);}
  // construction
  PFC_INLINE color_xyz();
  PFC_INLINE color_xyz(float x_, float y_, float z_);
  PFC_INLINE color_xyz(const color_xyza<simd_float4>&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float x_, float y_, float z_);
  //--------------------------------------------------------------------------

  PFC_ALIGN(16) float x;
  float y, z;
};
//----------------------------------------------------------------------------


//============================================================================
// simd_color_xyzaf
//============================================================================
template<>
struct color_xyza<simd_float4>
{ PFC_MONO(simd_color_xyzaf) {PFC_MVAR4(x, y, z, a);}
  // construction
  PFC_INLINE color_xyza();
  PFC_INLINE color_xyza(float x_, float y_, float z_);
  PFC_INLINE color_xyza(float x_, float y_, float z_, float a_);
  PFC_INLINE color_xyza(const color_xyz<simd_float4>&);
  PFC_INLINE color_xyza(const color_xyz<simd_float4>&, float a_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float x_, float y_, float z_);
  PFC_INLINE void set(float x_, float y_, float z_, float a_);
  //--------------------------------------------------------------------------

  PFC_ALIGN(16) float x;
  float y, z, a;
};
//----------------------------------------------------------------------------


//============================================================================
// simd_color_rgbf
//============================================================================
template<>
struct color_rgb<simd_float4>
{ PFC_MONO(simd_color_rgbf) {PFC_MVAR3(r, g, b);}
  // construction
  PFC_INLINE color_rgb();
  PFC_INLINE color_rgb(float r_, float g_, float b_);
  PFC_INLINE color_rgb(const color_rgba<simd_float4>&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float r_, float g_, float b_);
  //--------------------------------------------------------------------------

  PFC_ALIGN(16) float r;
  float g, b;
};
//----------------------------------------------------------------------------


//============================================================================
// simd_color_rgbaf
//============================================================================
template<>
struct color_rgba<simd_float4>
{ PFC_MONO(simd_color_rgbaf) {PFC_MVAR4(r, g, b, a);}
  // construction
  PFC_INLINE color_rgba();
  PFC_INLINE color_rgba(float r_, float g_, float b_);
  PFC_INLINE color_rgba(float r_, float g_, float b_, float a_);
  PFC_INLINE color_rgba(const color_rgb<simd_float4>&);
  PFC_INLINE color_rgba(const color_rgb<simd_float4>&, float a_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float r_, float g_, float b_);
  PFC_INLINE void set(float r_, float g_, float b_, float a_);
  //--------------------------------------------------------------------------

  PFC_ALIGN(16) float r;
  float g, b, a;
};
//----------------------------------------------------------------------------


//============================================================================
// simd_color_yiqf
//============================================================================
template<>
struct color_yiq<simd_float4>
{ PFC_MONO(simd_color_yiqf) {PFC_MVAR3(y, i, q);}
  // construction
  PFC_INLINE color_yiq();
  PFC_INLINE color_yiq(float y_, float i_, float q_);
  PFC_INLINE color_yiq(const color_yiqa<simd_float4>&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float y_, float i_, float q_);
  //--------------------------------------------------------------------------

  PFC_ALIGN(16) float y;
  float i, q;
};
//----------------------------------------------------------------------------


//============================================================================
// simd_color_yiqaf
//============================================================================
template<>
struct color_yiqa<simd_float4>
{ PFC_MONO(simd_color_yiqaf) {PFC_MVAR4(y, i, q, a);}
  // construction
  PFC_INLINE color_yiqa();
  PFC_INLINE color_yiqa(float y_, float i_, float q_);
  PFC_INLINE color_yiqa(float y_, float i_, float q_, float a_);
  PFC_INLINE color_yiqa(const color_yiq<simd_float4>&);
  PFC_INLINE color_yiqa(const color_yiq<simd_float4>&, float a_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float y_, float i_, float q_);
  PFC_INLINE void set(float y_, float i_, float q_, float a_);
  //--------------------------------------------------------------------------

  PFC_ALIGN(16) float y;
  float i, q, a;
};
//----------------------------------------------------------------------------


//============================================================================
// simd_color_hsvf
//============================================================================
template<>
struct color_hsv<simd_float4>
{ PFC_MONO(simd_color_hsvf) {PFC_MVAR3(h, s, v);}
  // construction
  PFC_INLINE color_hsv();
  PFC_INLINE color_hsv(float h_, float s_, float v_);
  PFC_INLINE color_hsv(const color_hsva<simd_float4>&);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float h_, float s_, float v_);
  //--------------------------------------------------------------------------

  PFC_ALIGN(16) float h;
  float s, v;
};
//----------------------------------------------------------------------------


//============================================================================
// simd_color_hsvaf
//============================================================================
template<>
struct color_hsva<simd_float4>
{ PFC_MONO(simd_color_hsvaf) {PFC_MVAR4(h, s, v, a);}
  // construction
  PFC_INLINE color_hsva();
  PFC_INLINE color_hsva(float h_, float s_, float v_);
  PFC_INLINE color_hsva(float h_, float s_, float v_, float a_);
  PFC_INLINE color_hsva(const color_hsv<simd_float4>&);
  PFC_INLINE color_hsva(const color_hsv<simd_float4>&, float a_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float h_, float s_, float v_);
  PFC_INLINE void set(float h_, float s_, float v_, float a_);
  //--------------------------------------------------------------------------

  PFC_ALIGN(16) float h;
  float s, v, a;
};
//----------------------------------------------------------------------------

//============================================================================
#include "color.inl"
} // namespace pfc
#endif
