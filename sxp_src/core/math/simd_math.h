//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_SIMD_MATH_H
#define PFC_CORE_MATH_SIMD_MATH_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "math.h"
namespace pfc
{

// new
typedef vec3<simd_float4> simd_vec3f;
typedef vec4<simd_float4> simd_vec4f;
typedef mat33<simd_float4> simd_mat33f;
typedef mat44<simd_float4> simd_mat44f;
typedef quat<simd_float4> simd_quatf;
//----------------------------------------------------------------------------


//============================================================================
// math constants
//============================================================================
template<>
struct math<simd_float4>
{
  // pi variants
  static const float pi;          // 3.14159265358979323846 
  static const float quarter_pi;  // 0.25*3.14159265358979323846
  static const float half_pi;     // 0.5*3.14159265358979323846
  static const float two_pi;      // 2.0*3.14159265358979323846
  static const float rpi;         // 1.0/3.14159265358979323846 
  static const float quarter_rpi; // 0.25/3.14159265358979323846
  static const float half_rpi;    // 0.5/3.14159265358979323846
  static const float two_rpi;     // 2.0/3.14159265358979323846
  // angle conversion factors
  static const float deg_to_rad;  // 0.01745329251994329577
  static const float rad_to_deg;  // 57.29577951308232087680
  // type definitions
  typedef float scalar_t;
};
//----------------------------------------------------------------------------


//============================================================================
// SIMD constants
//============================================================================
namespace simd
{
  // component identities
  extern const simd_float4 g_ident_x;    // [1.0f, 0.0f, 0.0f, 0.0f]
  extern const simd_float4 g_ident_y;    // [0.0f, 1.0f, 0.0f, 0.0f]
  extern const simd_float4 g_ident_z;    // [0.0f, 0.0f, 1.0f, 0.0f]
  extern const simd_float4 g_ident_w;    // [0.0f, 0.0f, 0.0f, 1.0f]
  // component negation
  extern const simd_float4 g_neg_w;    // [ 1.0f,  1.0f,  1.0f, -1.0f]
  extern const simd_float4 g_neg_xz;   // [ 1.0f, -1.0f,  1.0f, -1.0f]
  extern const simd_float4 g_neg_yw;   // [ 1.0f, -1.0f,  1.0f, -1.0f]
  extern const simd_float4 g_neg_xyz;  // [-1.0f, -1.0f, -1.0f,  1.0f]
  // masks
  extern const simd_float4 g_mask_xyz;       // [0xffffffff, 0xffffffff, 0xffffffff, 0x00000000]
  extern const simd_float4 g_mask_sign;      // [0x80000000, 0x80000000, 0x80000000, 0x80000000]
  extern const simd_float4 g_mask_not_sign;  // [0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff]
  // misc constants
  extern const simd_float4 g_one;        // [1.0f, 1.0f, 1.0f, 1.0f]
  extern const simd_float4 g_neg_one;    // [-1.0f, -1.0f, -1.0f, -1.0f]
  extern const simd_float4 g_scale_256;  // [255.999f, 255.999f, 255.999f, 255.999f]
  extern const simd_float4 g_scale_128;  // [127.999f, 127.999f, 127.999f, 127.999f]
};
//----------------------------------------------------------------------------


//============================================================================
// simd_vec3f
//============================================================================
template<>
struct vec3<simd_float4>
{ PFC_MONO(simd_vec3f) {PFC_MVAR3(x, y, z);}
  typedef simd_float4 type_t;
  typedef float scalar_t;
  enum {dim=3};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE vec3();
  PFC_INLINE vec3(float s_);
  PFC_INLINE vec3(float x_, float y_, float z_);
  PFC_INLINE vec3(const vec2f&, float z_);
  PFC_INLINE vec3(const vec3f&);
  PFC_INLINE vec3(const simd_float4&);
  PFC_INLINE vec3(const float*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float s_);
  PFC_INLINE void set(float x_, float y_, float z_);
  PFC_INLINE void set(const vec2f&, float z_);
  PFC_INLINE void set(const simd_vec3f&);
  PFC_INLINE void set(const vec3f&);
  PFC_INLINE void set(const simd_float4&);
  PFC_INLINE void set(const float*);
  //--------------------------------------------------------------------------

  static const simd_vec3f s_zero;
  static const simd_vec3f s_one;
  static const simd_vec3f s_neg_one;
  PFC_ALIGN(16) float x;
  float y, z;
};
PFC_SET_TYPE_TRAIT(simd_vec3f, is_type_pod, true);
PFC_SET_TYPE_TRAIT(simd_vec3f, is_type_pod_stream, false);
//----------------------------------------------------------------------------


//============================================================================
// simd_vec4f
//============================================================================
template<>
struct vec4<simd_float4>
{ PFC_MONO(simd_vec4f) {PFC_MVAR4(x, y, z, w);}
  typedef simd_float4 type_t;
  typedef float scalar_t;
  enum {dim=4};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE vec4();
  PFC_INLINE vec4(float s_);
  PFC_INLINE vec4(float x_, float y_, float z_, float w_);
  PFC_INLINE vec4(const simd_vec3f&, float w_);
  PFC_INLINE vec4(const vec3f&, float w_);
  PFC_INLINE vec4(const vec4f&);
  PFC_INLINE vec4(const simd_float4&);
  PFC_INLINE vec4(const float*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float s_);
  PFC_INLINE void set(float x_, float y_, float z_, float w_);
  PFC_INLINE void set(const simd_vec3f&, float w_);
  PFC_INLINE void set(const vec3f&, float w_);
  PFC_INLINE void set(const simd_vec4f&);
  PFC_INLINE void set(const vec4f&);
  PFC_INLINE void set(const simd_float4&);
  PFC_INLINE void set(const float*);
  //--------------------------------------------------------------------------

  static const simd_vec4f s_zero;
  static const simd_vec4f s_one;
  static const simd_vec4f s_neg_one;
  PFC_ALIGN(16) float x;
  float y, z, w;
};
PFC_SET_TYPE_TRAIT(simd_vec4f, is_type_pod, true);
PFC_SET_TYPE_TRAIT(simd_vec4f, is_type_pod_stream, true);
//----------------------------------------------------------------------------


//============================================================================
// simd_mat33f
//============================================================================
template<>
struct mat33<simd_float4>
{ PFC_MONO(simd_mat33f) {PFC_MVAR3(x, y, z);}
  typedef simd_float4 type_t;
  typedef float scalar_t;
  enum {dim_rows=3, dim_columns=3};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE mat33();
  PFC_INLINE mat33(float s_);
  PFC_INLINE mat33(float d0_, float d1_, float d2_);
  PFC_INLINE mat33(float m00_, float m01_, float m02_,
                   float m10_, float m11_, float m12_,
                   float m20_, float m21_, float m22_);
  PFC_INLINE mat33(const simd_float4 &row0_,
                   const simd_float4 &row1_,
                   const simd_float4 &row2_);
  PFC_INLINE mat33(const simd_vec3f &row0_,
                   const simd_vec3f &row1_,
                   const simd_vec3f &row2_);
  PFC_INLINE mat33(const mat22f&);
  PFC_INLINE mat33(const mat33f&);
  PFC_INLINE mat33(const simd_mat44f&);
  PFC_INLINE mat33(const mat44f&);
  PFC_INLINE mat33(const float*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const simd_vec3f &operator[](unsigned row_) const;
  PFC_INLINE simd_vec3f &operator[](unsigned row_);
  PFC_INLINE void set(float s_);
  PFC_INLINE void set(float d0_, float d1_, float d2_);
  PFC_INLINE void set(float m00_, float m01_, float m02_,
                      float m10_, float m11_, float m12_,
                      float m20_, float m21_, float m22_);
  PFC_INLINE void set(const simd_float4 &row0_,
                      const simd_float4 &row1_,
                      const simd_float4 &row2_);
  PFC_INLINE void set(const simd_vec3f &row0_,
                      const simd_vec3f &row1_,
                      const simd_vec3f &row2_);
  PFC_INLINE void set(const mat22f&);
  PFC_INLINE void set(const simd_mat33f&);
  PFC_INLINE void set(const mat33f&);
  PFC_INLINE void set(const simd_mat44f&);
  PFC_INLINE void set(const mat44f&);
  PFC_INLINE void set(const float*);
  //--------------------------------------------------------------------------

  static const simd_mat33f s_zero;
  static const simd_mat33f s_one;
  static const simd_mat33f s_neg_one;
  static const simd_mat33f s_identity;
  simd_vec3f x;
  simd_vec3f y;
  simd_vec3f z;
};
PFC_SET_TYPE_TRAIT(simd_mat33f, is_type_pod, true);
PFC_SET_TYPE_TRAIT(simd_mat33f, is_type_pod_stream, false);
//----------------------------------------------------------------------------


//============================================================================
// simd_mat44f
//============================================================================
template<>
struct mat44<simd_float4>
{ PFC_MONO(simd_mat44f) {PFC_MVAR4(x, y, z, w);}
  typedef simd_float4 type_t;
  typedef float scalar_t;
  enum {dim_rows=4, dim_columns=4};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE mat44();
  PFC_INLINE mat44(float s_);
  PFC_INLINE mat44(float d0_, float d1_, float d2_, float d3_);
  PFC_INLINE mat44(float m00_, float m01_, float m02_, float m03_,
                   float m10_, float m11_, float m12_, float m13_,
                   float m20_, float m21_, float m22_, float m23_,
                   float m30_, float m31_, float m32_, float m33_);
  PFC_INLINE mat44(const simd_float4 &row0_,
                   const simd_float4 &row1_,
                   const simd_float4 &row2_,
                   const simd_float4 &row3_);
  PFC_INLINE mat44(const simd_vec4f &row0_,
                   const simd_vec4f &row1_,
                   const simd_vec4f &row2_,
                   const simd_vec4f &row3_);
  PFC_INLINE mat44(const simd_mat33f&);
  PFC_INLINE mat44(const mat33f&);
  PFC_INLINE mat44(const mat44f&);
  PFC_INLINE mat44(const float*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const simd_vec4f &operator[](unsigned row_) const;
  PFC_INLINE simd_vec4f &operator[](unsigned row_);
  PFC_INLINE void set(float s_);
  PFC_INLINE void set(float d0_, float d1_, float d2_, float d3_);
  PFC_INLINE void set(float m00_, float m01_, float m02_, float m03_,
                      float m10_, float m11_, float m12_, float m13_,
                      float m20_, float m21_, float m22_, float m23_,
                      float m30_, float m31_, float m32_, float m33_);
  PFC_INLINE void set(const simd_float4 &row0_,
                      const simd_float4 &row1_,
                      const simd_float4 &row2_,
                      const simd_float4 &row3_);
  PFC_INLINE void set(const simd_vec4f &row0_,
                      const simd_vec4f &row1_,
                      const simd_vec4f &row2_,
                      const simd_vec4f &row3_);
  PFC_INLINE void set(const simd_mat33f&);
  PFC_INLINE void set(const mat33f&);
  PFC_INLINE void set(const simd_mat44f&);
  PFC_INLINE void set(const mat44f&);
  PFC_INLINE void set(const float*);
  //--------------------------------------------------------------------------

  static const simd_mat44f s_zero;
  static const simd_mat44f s_one;
  static const simd_mat44f s_neg_one;
  static const simd_mat44f s_identity;
  simd_vec4f x;
  simd_vec4f y;
  simd_vec4f z;
  simd_vec4f w;
};
PFC_SET_TYPE_TRAIT(simd_mat44f, is_type_pod, true);
PFC_SET_TYPE_TRAIT(simd_mat44f, is_type_pod_stream, true);
//----------------------------------------------------------------------------


//============================================================================
// simd_quatf
//============================================================================
template<>
struct quat<simd_float4>
{ PFC_MONO(simd_quatf) {PFC_MVAR4(x, y, z, w);}
  typedef simd_float4 type_t;
  typedef float scalar_t;
  enum {dim=4};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE quat();
  PFC_INLINE quat(float s_);
  PFC_INLINE quat(float x_, float y_, float z_, float w_);
  PFC_INLINE quat(const simd_vec3f&);
  PFC_INLINE quat(const vec3f&);
  PFC_INLINE quat(const simd_vec3f&, float w_);
  PFC_INLINE quat(const vec3f&, float w_);
  PFC_INLINE quat(const simd_vec4f&);
  PFC_INLINE quat(const vec4f&);
  PFC_INLINE quat(const quatf&);
  PFC_INLINE quat(const simd_float4&);
  PFC_INLINE quat(const float*);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE const float &operator[](unsigned idx_) const;
  PFC_INLINE float &operator[](unsigned idx_);
  PFC_INLINE void set(float s_);
  PFC_INLINE void set(float x_, float y_, float z_, float w_);
  PFC_INLINE void set(const simd_vec3f&);
  PFC_INLINE void set(const vec3f&);
  PFC_INLINE void set(const simd_vec3f&, float w_);
  PFC_INLINE void set(const vec3f&, float w_);
  PFC_INLINE void set(const simd_vec4f&);
  PFC_INLINE void set(const vec4f&);
  PFC_INLINE void set(const simd_quatf&);
  PFC_INLINE void set(const quatf&);
  PFC_INLINE void set(const simd_float4&);
  PFC_INLINE void set(const float*);
  //--------------------------------------------------------------------------

  static const simd_quatf s_zero;
  static const simd_quatf s_one;
  static const simd_quatf s_neg_one;
  static const simd_quatf s_identity;
  PFC_ALIGN(16) float x;
  float y, z, w;
};
PFC_SET_TYPE_TRAIT(simd_quatf, is_type_pod, true);
PFC_SET_TYPE_TRAIT(simd_quatf, is_type_pod_stream, true);
//----------------------------------------------------------------------------

//============================================================================
#include PFC_STR(PFC_CAT2(sxp_src/platform/PFC_PLATFORM_SRC_STR/core/math/PFC_PLATFORM_SRC_STR, _simd_math.inl))  // expands to e.g. "sxp_src/platform/win/core/math/win_simd_math.inl"
} // namespace pfc
#endif
