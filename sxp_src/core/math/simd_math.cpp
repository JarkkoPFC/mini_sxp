//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "simd_math.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// math constants
//============================================================================
// pi variants
const float math<simd_float4>::pi=mathf::pi;
const float math<simd_float4>::quarter_pi=mathf::quarter_pi;
const float math<simd_float4>::half_pi=mathf::half_pi;
const float math<simd_float4>::two_pi=mathf::two_pi;
const float math<simd_float4>::rpi=mathf::rpi;
const float math<simd_float4>::quarter_rpi=mathf::quarter_rpi;
const float math<simd_float4>::half_rpi=mathf::half_rpi;
const float math<simd_float4>::two_rpi=mathf::two_rpi;
// angle conversion factors
const float math<simd_float4>::deg_to_rad=mathf::deg_to_rad;
const float math<simd_float4>::rad_to_deg=mathf::rad_to_deg;
//----------------------------------------------------------------------------


//============================================================================
// SIMD constants
//============================================================================
// component identities
const simd_float4 simd::g_ident_x={1.0f, 0.0f, 0.0f, 0.0f};
const simd_float4 simd::g_ident_y={0.0f, 1.0f, 0.0f, 0.0f};
const simd_float4 simd::g_ident_z={0.0f, 0.0f, 1.0f, 0.0f};
const simd_float4 simd::g_ident_w={0.0f, 0.0f, 0.0f, 1.0f};
// component negation
const simd_float4 simd::g_neg_w={1.0f,  1.0f,  1.0f, -1.0f};
const simd_float4 simd::g_neg_xz={-1.0f, 1.0f,  -1.0f, 1.0f};
const simd_float4 simd::g_neg_yw={1.0f, -1.0f,  1.0f, -1.0f};
const simd_float4 simd::g_neg_xyz={-1.0f, -1.0f, -1.0f,  1.0f};
// masks
const simd_float4 simd::g_mask_xyz={raw_cast<float32_t>(0xffffffff), raw_cast<float32_t>(0xffffffff), raw_cast<float32_t>(0xffffffff), 0};
const simd_float4 simd::g_mask_sign={raw_cast<float32_t>(0x80000000), raw_cast<float32_t>(0x80000000), raw_cast<float32_t>(0x80000000), raw_cast<float32_t>(0x80000000)};
const simd_float4 simd::g_mask_not_sign={raw_cast<float32_t>(0x7fffffff), raw_cast<float32_t>(0x7fffffff), raw_cast<float32_t>(0x7fffffff), raw_cast<float32_t>(0x7fffffff)};
// misc constants
const simd_float4 simd::g_one={1.0f, 1.0f, 1.0f, 1.0f};
const simd_float4 simd::g_neg_one={-1.0f, -1.0f, -1.0f, -1.0f};
const simd_float4 simd::g_scale_256={255.999f, 255.999f, 255.999f, 255.999f};
const simd_float4 simd::g_scale_128={127.999f, 127.999f, 127.999f, 127.999f};
//----------------------------------------------------------------------------


//============================================================================
// simd_vec3f
//============================================================================
const simd_vec3f simd_vec3f::s_zero(0.0f);
const simd_vec3f simd_vec3f::s_one(1.0f);
const simd_vec3f simd_vec3f::s_neg_one(-1.0f);
//----------------------------------------------------------------------------


//============================================================================
// simd_vec4f
//============================================================================
const simd_vec4f simd_vec4f::s_zero(0.0f);
const simd_vec4f simd_vec4f::s_one(1.0f);
const simd_vec4f simd_vec4f::s_neg_one(-1.0f);
//----------------------------------------------------------------------------


//============================================================================
// simd_mat33f
//============================================================================
const simd_mat33f simd_mat33f::s_zero(0.0f);
const simd_mat33f simd_mat33f::s_one(1.0f);
const simd_mat33f simd_mat33f::s_neg_one(-1.0f);
const simd_mat33f simd_mat33f::s_identity(1.0f, 0.0f, 0.0f,
                                          0.0f, 1.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f);
//----------------------------------------------------------------------------


//============================================================================
// simd_mat44f
//============================================================================
const simd_mat44f simd_mat44f::s_zero(0.0f);
const simd_mat44f simd_mat44f::s_one(1.0f);
const simd_mat44f simd_mat44f::s_neg_one(-1.0f);
const simd_mat44f simd_mat44f::s_identity(1.0f, 0.0f, 0.0f, 0.0f,
                                          0.0f, 1.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 1.0f);
//----------------------------------------------------------------------------


//============================================================================
// simd_quatf
//============================================================================
const simd_quatf simd_quatf::s_zero(0.0f);
const simd_quatf simd_quatf::s_one(1.0f);
const simd_quatf simd_quatf::s_neg_one(-1.0f);
const simd_quatf simd_quatf::s_identity(0.0f, 0.0f, 0.0f, 1.0f);
//----------------------------------------------------------------------------
