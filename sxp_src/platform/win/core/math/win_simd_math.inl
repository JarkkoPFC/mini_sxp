//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifdef PFC_PLATFORM_SSE4
} // namespace pfc
#include <smmintrin.h>
namespace pfc
{
#endif
//----------------------------------------------------------------------------


//============================================================================
// simd_vec3f
//============================================================================
simd_vec3f::vec3()
{
}
//----

simd_vec3f::vec3(float s_)
{
  // init vector with scalar
  (simd_float4&)*this=_mm_set1_ps(s_);
}
//----

simd_vec3f::vec3(float x_, float y_, float z_)
{
  // init vector with scalars
  x=x_;
  y=y_;
  z=z_;
}
//----

simd_vec3f::vec3(const vec2f &v_, float z_)
{
  // init vector with 2d fp-vector and z
  x=v_.x;
  y=v_.y;
  z=z_;
}
//----

simd_vec3f::vec3(const vec3f &v_)
{
  // init vector with 3d fp-vector
  (simd_float4&)*this=_mm_loadu_ps((const float*)&v_);
}
//----

simd_vec3f::vec3(const simd_float4 &v_)
{
  // init vector with SIMD float4
  (simd_float4&)*this=v_;
}
//----

simd_vec3f::vec3(const float *a_)
{
  // init vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  (simd_float4&)*this=_mm_loadu_ps(a_);
}
//----------------------------------------------------------------------------

const float &simd_vec3f::operator[](unsigned idx_) const
{
  // return reference to nth component (x=0, y=1, z=2)
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<const float*>(this)[idx_];
}
//----

float &simd_vec3f::operator[](unsigned idx_)
{
  // return reference to nth component (x=0, y=1, z=2)
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<float*>(this)[idx_];
}
//----

void simd_vec3f::set(float s_)
{
  // set vector with scalar
  (simd_float4&)*this=_mm_set1_ps(s_);
}
//----

void simd_vec3f::set(float x_, float y_, float z_)
{
  // set vector with scalars
  x=x_;
  y=y_;
  z=z_;
}
//----

void simd_vec3f::set(const vec2f &v_, float z_)
{
  // set vector with 2d fp-vector and z
  x=v_.x;
  y=v_.y;
  z=z_;
}
//----

void simd_vec3f::set(const simd_vec3f &v_)
{
  // set vector with 3d SIMD vector
  (simd_float4&)*this=(simd_float4&)v_;
}
//----

void simd_vec3f::set(const vec3f &v_)
{
  // set vector with 3d fp-vector
  (simd_float4&)*this=_mm_loadu_ps((const float*)&v_);
}
//----

void simd_vec3f::set(const simd_float4 &v_)
{
  // set vector with SIMD float4
  (simd_float4&)*this=v_;
}
//----

void simd_vec3f::set(const float *a_)
{
  // set vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  (simd_float4&)*this=_mm_loadu_ps(a_);
}
//----------------------------------------------------------------------------

PFC_INLINE bool is_zero(const simd_vec3f &v_)
{
  // test for zero-vector
  return (_mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)v_, _mm_setzero_ps()))&0x7)==0;
}
//----

PFC_INLINE bool is_sat(const simd_vec3f &v_)
{
  // test for saturated vector
  return (_mm_movemask_ps(_mm_or_ps(_mm_cmplt_ps((simd_float4&)v_, _mm_setzero_ps()),
                                    _mm_cmpgt_ps((simd_float4&)v_, simd::g_one)))&0x7)==0;
}
//----

PFC_INLINE bool is_ssat(const simd_vec3f &v_)
{
  // test for signed saturated vector
  return (_mm_movemask_ps(_mm_or_ps(_mm_cmplt_ps((simd_float4&)v_, simd::g_neg_one),
                                    _mm_cmpgt_ps((simd_float4&)v_, simd::g_one)))&0x7)==0;
}
//----

PFC_INLINE bool operator==(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // test for equality of vectors
  return (_mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)v0_, (simd_float4&)v1_))&0x7)==0;
}
//----

PFC_INLINE bool operator==(const simd_vec3f &v_, float s_)
{
  // test for equality of vector and scalar
  return (_mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)v_, _mm_set1_ps(s_)))&0x7)==0;
}
//----

PFC_INLINE bool operator==(float s_, const simd_vec3f &v_)
{
  // test for equality of vector and scalar
  return (_mm_movemask_ps(_mm_cmpneq_ps(_mm_set1_ps(s_), (simd_float4&)v_))&0x7)==0;
}
//----

PFC_INLINE bool operator!=(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // test for inequality of vectors
  return (_mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)v0_, (simd_float4&)v1_))&0x7)!=0;
}
//----

PFC_INLINE bool operator!=(const simd_vec3f &v_, float s_)
{
  // test for inequality of vector and scalar
  return (_mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)v_, _mm_set1_ps(s_)))&0x7)!=0;
}
//----

PFC_INLINE bool operator!=(float s_, const simd_vec3f &v_)
{
  // test for inequality of vector and scalar
  return (_mm_movemask_ps(_mm_cmpneq_ps(_mm_set1_ps(s_), (simd_float4&)v_))&0x7)!=0;
}
//----

PFC_INLINE simd_vec3f operator<(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise less-than (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmplt_ps((simd_float4&)v0_, (simd_float4&)v1_), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator<(const simd_vec3f &v_, float s_)
{
  // component-wise less-than (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmplt_ps((simd_float4&)v_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator<(float s_, const simd_vec3f &v_)
{
  // component-wise less-than (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmplt_ps(_mm_set1_ps(s_), (simd_float4&)v_), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator>(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise greater-than (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmpgt_ps((simd_float4&)v0_, (simd_float4&)v1_), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator>(const simd_vec3f &v_, float s_)
{
  // component-wise greater-than (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmpgt_ps((simd_float4&)v_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator>(float s_, const simd_vec3f &v_)
{
  // component-wise greater-than (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmpgt_ps(_mm_set1_ps(s_), (simd_float4&)v_), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator<=(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise less-or-equal (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmple_ps((simd_float4&)v0_, (simd_float4&)v1_), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator<=(const simd_vec3f &v_, float s_)
{
  // component-wise less-or-equal (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmple_ps((simd_float4&)v_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator<=(float s_, const simd_vec3f &v_)
{
  // component-wise less-or-equal (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmple_ps(_mm_set1_ps(s_), (simd_float4&)v_), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator>=(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise greater-or-equal (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmpge_ps((simd_float4&)v0_, (simd_float4&)v1_), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator>=(const simd_vec3f &v_, float s_)
{
  // component-wise greater-or-equal (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmpge_ps((simd_float4&)v_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_vec3f operator>=(float s_, const simd_vec3f &v_)
{
  // component-wise greater-or-equal (false=0, true=1)
  return simd_vec3f(_mm_and_ps(_mm_cmpge_ps(_mm_set1_ps(s_), (simd_float4&)v_), simd::g_one));
}
//----

PFC_INLINE simd_vec3f sel_eq(const simd_vec3f &t0_, const simd_vec3f &t1_, const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise equal vector select (t0_==t1_?v0_:v1_)
  simd_float4 r=_mm_cmpeq_ps((simd_float4&)t0_, (simd_float4&)t1_);
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec3f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE simd_vec3f sel_lt(const simd_vec3f &t0_, const simd_vec3f &t1_, const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise less-than vector select (t0_<t1_?v0_:v1_)
  simd_float4 r=_mm_cmplt_ps((simd_float4&)t0_, (simd_float4&)t1_);
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec3f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE simd_vec3f sel_le(const simd_vec3f &t0_, const simd_vec3f &t1_, const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise less-or-equal vector select (t0_<=t1_?v0_:v1_)
  simd_float4 r=_mm_cmple_ps((simd_float4&)t0_, (simd_float4&)t1_);
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec3f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE simd_vec3f sel_eqz(const simd_vec3f &t_, const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise equal-to-zero vector select (t_==0?v0_:v1_)
  simd_float4 r=_mm_cmpeq_ps((simd_float4&)t_, _mm_setzero_ps());
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec3f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE simd_vec3f sel_ltz(const simd_vec3f &t_, const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise less-than-zero vector select (t_<0?v0_:v1_)
  simd_float4 r=_mm_cmplt_ps((simd_float4&)t_, _mm_setzero_ps());
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec3f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE simd_vec3f sel_lez(const simd_vec3f &t_, const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise less-or-equal-to-zero vector select (t_<=0?v0_:v1_)
  simd_float4 r=_mm_cmple_ps((simd_float4&)t_, _mm_setzero_ps());
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec3f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE void operator+=(simd_vec3f &vr_, const simd_vec3f &v_)
{
  // add vector to vector
  (simd_float4&)vr_=_mm_add_ps((simd_float4&)vr_, (simd_float4&)v_);
}
//----

PFC_INLINE void operator+=(simd_vec3f &vr_, float s_)
{
  // add scalar to each component of the vector
  (simd_float4&)vr_=_mm_add_ps((simd_float4&)vr_, _mm_set1_ps(s_));
}
//----

PFC_INLINE void operator-=(simd_vec3f &vr_, const simd_vec3f &v_)
{
  // subtract vector from vector
  (simd_float4&)vr_=_mm_sub_ps((simd_float4&)vr_, (simd_float4&)v_);
}
//----

PFC_INLINE void operator-=(simd_vec3f &vr_, float s_)
{
  // subtract scalar from each component of the vector
  (simd_float4&)vr_=_mm_sub_ps((simd_float4&)vr_, _mm_set1_ps(s_));
}
//----

PFC_INLINE void operator*=(simd_vec3f &vr_, const simd_vec3f &v_)
{
  // component-wise vector by vector multiply
  (simd_float4&)vr_=_mm_mul_ps((simd_float4&)vr_, (simd_float4&)v_);
}
//----

PFC_INLINE void operator*=(simd_vec3f &vr_, float s_)
{
  // multiply vector by scalar
  (simd_float4&)vr_=_mm_mul_ps((simd_float4&)vr_, _mm_set1_ps(s_));
}
//----

PFC_INLINE void operator*=(simd_vec3f &vr_, const simd_mat33f &m_)
{
  // multiply vector by matrix
  (simd_float4&)vr_=_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                          _mm_mul_ps(_mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                          _mm_mul_ps(_mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z));
}
//----

PFC_INLINE void operator*=(simd_vec3f &vr_, const simd_mat44f &m_)
{
  // multiply vector by 4x4 matrix (assume vector w=1)
  (simd_float4&)vr_=_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                                     _mm_mul_ps(_mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                                     _mm_mul_ps(_mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z)),
                               (simd_float4&)m_.w);
}
//----

PFC_INLINE void operator*=(simd_vec3f &vr_, const simd_quatf &q_)
{
  // transform the vector by quaternion: v'=2(qv x (qv x v + wv)) + v
  simd_float4 qv1=_mm_shuffle_ps((simd_float4&)q_, (simd_float4&)q_, _MM_SHUFFLE(0, 0, 2, 1));
  simd_float4 v=_mm_sub_ps(_mm_mul_ps((simd_float4&)q_, _mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(0, 0, 2, 1))),
                           _mm_mul_ps(qv1, (simd_float4&)vr_));
  v=_mm_add_ps(v, _mm_mul_ps(_mm_shuffle_ps((simd_float4&)q_, (simd_float4&)q_, _MM_SHUFFLE(0, 3, 3, 3)), _mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(0, 1, 0, 2))));
  v=_mm_sub_ps(_mm_mul_ps(qv1, v),
               _mm_mul_ps(_mm_shuffle_ps(qv1, qv1, _MM_SHUFFLE(0, 0, 2, 1)), _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 1, 0, 2))));
  (simd_float4&)vr_=_mm_add_ps(_mm_add_ps(v, v), (simd_float4&)vr_);
}
//----

PFC_INLINE void operator/=(simd_vec3f &vr_, const simd_vec3f &v_)
{
  // component-wise vector by vector division
  (simd_float4&)vr_=_mm_mul_ps((simd_float4&)vr_, _mm_rcp_ps((simd_float4&)v_));
}
//----

PFC_INLINE void operator/=(simd_vec3f &vr_, float s_)
{
  // divide vector by scalar
  simd_float4 rs=_mm_rcp_ss(_mm_load_ss(&s_));
  (simd_float4&)vr_=_mm_mul_ps((simd_float4&)vr_, _mm_shuffle_ps(rs, rs, 0));
}
//----

PFC_INLINE simd_vec3f operator+(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // add vector to vector
  return simd_vec3f(_mm_add_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec3f operator+(const simd_vec3f &v_, float s_)
{
  // add scalar to each component of the vector
  return simd_vec3f(_mm_add_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec3f operator+(float s_, const simd_vec3f &v_)
{
  // add each component of the vector to a scalar vector
  return simd_vec3f(_mm_add_ps(_mm_set1_ps(s_), (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec3f operator-(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // subtract vector from vector
  return simd_vec3f(_mm_sub_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec3f operator-(const simd_vec3f &v_, float s_)
{
  // subtract scalar from each component of the vector
  return simd_vec3f(_mm_sub_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec3f operator-(float s_, const simd_vec3f &v_)
{
  // subtract each component of the vector from a scalar vector
  return simd_vec3f(_mm_sub_ps(_mm_set1_ps(s_), (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec3f operator-(const simd_vec3f &v_)
{
  // negate vector
  return simd_vec3f(_mm_sub_ps(_mm_setzero_ps(), (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec3f operator*(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise vector by vector multiply
  return simd_vec3f(_mm_mul_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec3f operator*(const simd_vec3f &v_, float s_)
{
  // multiply vector by scalar
  return simd_vec3f(_mm_mul_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec3f operator*(float s_, const simd_vec3f &v_)
{
  // multiply vector by scalar
  return simd_vec3f(_mm_mul_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec3f operator*(const simd_vec3f &v_, const simd_mat33f &m_)
{
  // multiply vector my matrix
  return simd_vec3f(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                          _mm_mul_ps(_mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                          _mm_mul_ps(_mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z)));
}
//----

PFC_INLINE simd_vec3f operator*(const simd_mat33f &m_, const simd_vec3f &v_)
{
  // multiply matrix by transposed vector
#ifdef PFC_PLATFORM_SSE4
  simd_vec3f vr;
  _mm_store_ss(&vr.x, _mm_dp_ps((simd_float4&)m_.x, (simd_float4&)v_, 0x71));
  _mm_store_ss(&vr.y, _mm_dp_ps((simd_float4&)m_.y, (simd_float4&)v_, 0x71));
  _mm_store_ss(&vr.z, _mm_dp_ps((simd_float4&)m_.z, (simd_float4&)v_, 0x71));
  return vr;
#else
  PFC_ALIGN(16) float32_t x[4], y[4], z[4];
  _mm_store_ps(x, _mm_mul_ps((simd_float4&)m_.x, (simd_float4&)v_));
  _mm_store_ps(y, _mm_mul_ps((simd_float4&)m_.y, (simd_float4&)v_));
  _mm_store_ps(z, _mm_mul_ps((simd_float4&)m_.z, (simd_float4&)v_));
  return simd_vec3f(x[0]+x[1]+x[2], y[0]+y[1]+y[2], z[0]+z[1]+z[2]);
#endif
}
//----

PFC_INLINE simd_vec3f operator*(const simd_vec3f &v_, const simd_mat44f &m_)
{
  // multiply vector by 4x4 matrix (assume vector w=1)
  return simd_vec3f(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                                     _mm_mul_ps(_mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                                     _mm_mul_ps(_mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z)),
                               (simd_float4&)m_.w));
}
//----

PFC_INLINE simd_vec3f operator*(const simd_mat44f &m_, const simd_vec3f &v_)
{
  // multiply 4x4 matrix by transposed vector (assume vector w=1)
#ifdef PFC_PLATFORM_SSE4
  simd_float4 v=_mm_insert_ps((simd_float4&)v_, simd::g_ident_w, 0xf0);
  simd_vec3f vr;
  _mm_store_ss(&vr.x, _mm_dp_ps((simd_float4&)m_.x, v, 0xf1));
  _mm_store_ss(&vr.y, _mm_dp_ps((simd_float4&)m_.y, v, 0xf1));
  _mm_store_ss(&vr.z, _mm_dp_ps((simd_float4&)m_.z, v, 0xf1));
  return vr;
#else
  PFC_ALIGN(16) float32_t x[4], y[4], z[4];
  _mm_store_ps(x, _mm_mul_ps((simd_float4&)m_.x, (simd_float4&)v_));
  _mm_store_ps(y, _mm_mul_ps((simd_float4&)m_.y, (simd_float4&)v_));
  _mm_store_ps(z, _mm_mul_ps((simd_float4&)m_.z, (simd_float4&)v_));
  return simd_vec3f(x[0]+x[1]+x[2]+m_.x.w, y[0]+y[1]+y[2]+m_.y.w, z[0]+z[1]+z[2]+m_.z.w);
#endif
}
//----

PFC_INLINE simd_vec3f operator*(const simd_vec3f &v_, const simd_quatf &q_)
{
  // transform the vector by quaternion: v'=2(qv x (qv x v + wv)) + v
  simd_float4 qv1=_mm_shuffle_ps((simd_float4&)q_, (simd_float4&)q_, _MM_SHUFFLE(0, 0, 2, 1));
  simd_float4 v=_mm_sub_ps(_mm_mul_ps((simd_float4&)q_, _mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(0, 0, 2, 1))),
                           _mm_mul_ps(qv1, (simd_float4&)v_));
  v=_mm_add_ps(v, _mm_mul_ps(_mm_shuffle_ps((simd_float4&)q_, (simd_float4&)q_, _MM_SHUFFLE(0, 3, 3, 3)), _mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(0, 1, 0, 2))));
  v=_mm_sub_ps(_mm_mul_ps(qv1, v),
               _mm_mul_ps(_mm_shuffle_ps(qv1, qv1, _MM_SHUFFLE(0, 0, 2, 1)), _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 1, 0, 2))));
  return simd_vec3f(_mm_add_ps(_mm_add_ps(v, v), (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec3f operator/(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise vector by vector division
  return simd_vec3f(_mm_mul_ps((simd_float4&)v0_, _mm_rcp_ps((simd_float4&)v1_)));
}
//----

PFC_INLINE simd_vec3f operator/(const simd_vec3f &v_, float s_)
{
  // divide vector by scalar
  simd_float4 rs=_mm_rcp_ss(_mm_load_ss(&s_));
  return simd_vec3f(_mm_mul_ps((simd_float4&)v_, _mm_shuffle_ps(rs, rs, 0)));
}
//----

PFC_INLINE simd_vec3f min(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise min vector
  return simd_vec3f(_mm_min_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec3f min(const simd_vec3f &v0_, const simd_vec3f &v1_, const simd_vec3f &v2_)
{
  // component-wise min vector
  return simd_vec3f(_mm_min_ps(_mm_min_ps((simd_float4&)v0_, (simd_float4&)v1_), (simd_float4&)v2_));
}
//----

PFC_INLINE simd_vec3f min(const simd_vec3f &v0_, const simd_vec3f &v1_, const simd_vec3f &v2_, const simd_vec3f &v3_)
{
  // component-wise min vector
  return simd_vec3f(_mm_min_ps(_mm_min_ps(_mm_min_ps((simd_float4&)v0_, (simd_float4&)v1_), (simd_float4&)v2_), (simd_float4&)v3_));
}
//----

PFC_INLINE simd_vec3f min(const simd_vec3f &v_, float s_)
{
  // component-wise min vector
  return simd_vec3f(_mm_min_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec3f min(float s_, const simd_vec3f &v_)
{
  // component-wise min vector
  return simd_vec3f(_mm_min_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec3f max(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise max vector
  return simd_vec3f(_mm_max_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec3f max(const simd_vec3f &v0_, const simd_vec3f &v1_, const simd_vec3f &v2_)
{
  // component-wise max vector
  return simd_vec3f(_mm_max_ps(_mm_max_ps((simd_float4&)v0_, (simd_float4&)v1_), (simd_float4&)v2_));
}
//----

PFC_INLINE simd_vec3f max(const simd_vec3f &v0_, const simd_vec3f &v1_, const simd_vec3f &v2_, const simd_vec3f &v3_)
{
  // component-wise max vector
  return simd_vec3f(_mm_max_ps(_mm_max_ps(_mm_max_ps((simd_float4&)v0_, (simd_float4&)v1_), (simd_float4&)v2_), (simd_float4&)v3_));
}
//----

PFC_INLINE simd_vec3f max(const simd_vec3f &v_, float s_)
{
  // component-wise max vector
  return simd_vec3f(_mm_max_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec3f max(float s_, const simd_vec3f &v_)
{
  // component-wise max vector
  return simd_vec3f(_mm_max_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec3f mul(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // component-wise multiply: v0_*v1_
  return simd_vec3f(_mm_mul_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec3f madd(const simd_vec3f &vm0_, const simd_vec3f &vm1_, const simd_vec3f &va_)
{
  // component-wise multiply-add: vm0_*vm1_+va_
  return simd_vec3f(_mm_add_ps(_mm_mul_ps((simd_float4&)vm0_, (simd_float4&)vm1_), (simd_float4&)va_));
}
//----

PFC_INLINE simd_vec3f madd(const simd_vec3f &vm_, float sm_, float sa_)
{
  // component-wise multiply-add: vm_*sm_+sa_
  return simd_vec3f(_mm_add_ps(_mm_mul_ps((simd_float4&)vm_, _mm_set1_ps(sm_)), _mm_set1_ps(sa_)));
}
//----

PFC_INLINE simd_vec3f madd(const simd_vec3f &vm0_, const simd_vec3f &vm1_, float sa_)
{
  // component-wise multiply-add: vm0_*vm1_+sa_
  return simd_vec3f(_mm_add_ps(_mm_mul_ps((simd_float4&)vm0_, (simd_float4&)vm1_), _mm_set1_ps(sa_)));
}
//----

PFC_INLINE simd_vec3f madd(const simd_vec3f &vm_, float sm_, const simd_vec3f &va_)
{
  // component-wise multiply-add: vm_*sm_+va_
  return simd_vec3f(_mm_add_ps(_mm_mul_ps((simd_float4&)vm_, _mm_set1_ps(sm_)), (simd_float4&)va_));
}
//----

PFC_INLINE simd_vec3f rcp(const simd_vec3f &v_)
{
  // component-wise reciprocal
  return simd_vec3f(_mm_rcp_ps((simd_float4&)v_));
}
//----

PFC_INLINE simd_vec3f rcp_z(const simd_vec3f &v_)
{
  // component-wise reciprocal (set to 0 for 0 components)
  return simd_vec3f(_mm_and_ps(_mm_cmpneq_ps((simd_float4&)v_, _mm_setzero_ps()), _mm_rcp_ps((simd_float4&)v_)));
}
//----

PFC_INLINE simd_vec3f floor(const simd_vec3f &v_)
{
  // component-wise floor
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_round_ps((simd_float4&)v_, _MM_FROUND_FLOOR));
#else
  const float *f=(const float*)&v_;
  return simd_vec3f(std::floor(f[0]), std::floor(f[1]), std::floor(f[2]));
#endif
}
//----

PFC_INLINE simd_vec3f ceil(const simd_vec3f &v_)
{
  // component-wise ceil
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_round_ps((simd_float4&)v_, _MM_FROUND_CEIL));
#else
  const float *f=(const float*)&v_;
  return simd_vec3f(std::ceil(f[0]), std::ceil(f[1]), std::ceil(f[2]));
#endif
}
//----

PFC_INLINE simd_vec3f trunc(const simd_vec3f &v_)
{
  // component-wise truncate
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_round_ps((simd_float4&)v_, _MM_FROUND_TO_ZERO));
#else
  return simd_vec3f(float(int(v_.x)), float(int(v_.y)), float(int(v_.z)));
#endif
}
//----

PFC_INLINE simd_vec3f frc(const simd_vec3f &v_)
{
  // component-wise fractional
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_sub_ps((simd_float4&)v_, _mm_round_ps((simd_float4&)v_, _MM_FROUND_TO_ZERO)));
#else
  const float *f=(const float*)&v_;
  return simd_vec3f(f[0]-float(int(f[0])), f[1]-float(int(f[1])), f[2]-float(int(f[2])));
#endif
}
//----

PFC_INLINE simd_vec3f mod(const simd_vec3f &v_, float div_)
{
  // component-wise modulo
#ifdef PFC_PLATFORM_SSE4
  simd_float4 d=_mm_set1_ps(div_);
  return simd_vec3f(_mm_sub_ps((simd_float4&)v_, _mm_mul_ps(_mm_round_ps(_mm_mul_ps((simd_float4&)v_, _mm_rcp_ps(d)), _MM_FROUND_TO_ZERO), d)));
#else
  const float *f=(const float*)&v_;
  return simd_vec3f(std::fmod(f[0], div_), std::fmod(f[1], div_), std::fmod(f[2], div_));
#endif
}
//----

PFC_INLINE simd_vec3f cycle(const simd_vec3f &v_, float cycle_)
{
  // component-wise cycle
#ifdef PFC_PLATFORM_SSE4
  simd_float4 d=_mm_set1_ps(cycle_);
  return simd_vec3f(_mm_sub_ps((simd_float4&)v_, _mm_mul_ps(_mm_round_ps(_mm_mul_ps((simd_float4&)v_, _mm_rcp_ps(d)), _MM_FROUND_TO_NEG_INF), d)));
#else
  const float *f=(const float*)&v_;
  float x=std::fmod(f[0], cycle_), y=std::fmod(f[1], cycle_), z=std::fmod(f[2], cycle_);
  return simd_vec3f(x<0?cycle_+x:x, y<0?cycle_+y:y, z<0?cycle_+z:z);
#endif
}
//----

PFC_INLINE simd_vec3f sat(const simd_vec3f &v_)
{
  // component-wise saturate
  return simd_vec3f(_mm_min_ps(_mm_max_ps((simd_float4&)v_, _mm_setzero_ps()), simd::g_one));
}
//----

PFC_INLINE simd_vec3f ssat(const simd_vec3f &v_)
{
  // component-wise signed saturate
  return simd_vec3f(_mm_min_ps(_mm_max_ps((simd_float4&)v_, simd::g_neg_one), simd::g_one));
}
//----

PFC_INLINE simd_vec3f clamp(const simd_vec3f &v_, const simd_vec3f &min_, const simd_vec3f &max_)
{
  // component-wise clamp (to vectors)
  return simd_vec3f(_mm_min_ps(_mm_max_ps((simd_float4&)v_, (simd_float4&)min_), (simd_float4&)max_));
}
//----

PFC_INLINE simd_vec3f clamp(const simd_vec3f &v_, float min_, float max_)
{
  // component-wise clamp (to scalars)
  return simd_vec3f(_mm_min_ps(_mm_max_ps((simd_float4&)v_, _mm_set1_ps(min_)), _mm_set1_ps(max_)));
}
//----

PFC_INLINE simd_vec3f abs(const simd_vec3f &v_)
{
  // component-wise absolute
  return simd_vec3f(_mm_and_ps((simd_float4&)v_, simd::g_mask_not_sign));
}
//----

PFC_INLINE simd_vec3f sgn(const simd_vec3f &v_)
{
  // component-wise signum (neg=-1, pos=+1, zero=0)
  return simd_vec3f(_mm_and_ps(_mm_cmpneq_ps((simd_float4&)v_, _mm_setzero_ps()), _mm_or_ps(_mm_and_ps(_mm_cmplt_ps((simd_float4&)v_, _mm_setzero_ps()), simd::g_mask_sign), simd::g_one)));
}
//----

PFC_INLINE simd_vec3f sgn_zp(const simd_vec3f &v_)
{
  // component-wise signum (neg=-1, pos&zero=+1)
  return simd_vec3f(_mm_or_ps(_mm_and_ps(_mm_cmplt_ps((simd_float4&)v_, _mm_setzero_ps()), simd::g_mask_sign), simd::g_one));
}
//----

PFC_INLINE simd_vec3f sqr(const simd_vec3f &v_)
{
  // component-wise square
  return simd_vec3f(_mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec3f cubic(const simd_vec3f &v_)
{
  // component-wise cubic
  return simd_vec3f(_mm_mul_ps(_mm_mul_ps((simd_float4&)v_, (simd_float4&)v_), (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec3f sqrt(const simd_vec3f &v_)
{
  // component-wise square root
  return simd_vec3f(_mm_sqrt_ps((simd_float4&)v_));
}
//----

PFC_INLINE simd_vec3f sqrt_z(const simd_vec3f &v_)
{
  // component-wise square root (set to 0 for components less than zero)
  return simd_vec3f(_mm_sqrt_ps(_mm_max_ps((simd_float4&)v_, _mm_setzero_ps())));
}
//----
/*
PFC_INLINE simd_vec3f cbrt(const simd_vec3f &v_)
{
  // component-wise cubic root
  return simd_vec3f(v_.x<0?-std::pow(-v_.x, float(1.0/3.0)):std::pow(v_.x, float(1.0/3.0)),
                    v_.y<0?-std::pow(-v_.y, float(1.0/3.0)):std::pow(v_.y, float(1.0/3.0)),
                    v_.z<0?-std::pow(-v_.z, float(1.0/3.0)):std::pow(v_.z, float(1.0/3.0)));
}
//----
*/
PFC_INLINE simd_vec3f rsqrt(const simd_vec3f &v_)
{
  // component-wise reciprocal square root
  return simd_vec3f(_mm_rsqrt_ps((simd_float4&)v_));
}
//----

PFC_INLINE simd_vec3f rsqrt_z(const simd_vec3f &v_)
{
  // component-wise reciprocal square root (set to 0 for components less than or equal to zero)
  return simd_vec3f(_mm_and_ps(_mm_cmpgt_ps((simd_float4&)v_, _mm_setzero_ps()), _mm_rsqrt_ps((simd_float4&)v_)));
}
//----
/*
PFC_INLINE simd_vec3f rcbrt(const simd_vec3f &v_)
{
  // component-wise reciprocal cubic root
  return simd_vec3f(v_.x<0?-std::pow(-v_.x, float(-1.0/3.0)):std::pow(v_.x, float(-1.0/3.0)),
                    v_.y<0?-std::pow(-v_.y, float(-1.0/3.0)):std::pow(v_.y, float(-1.0/3.0)),
                    v_.z<0?-std::pow(-v_.z, float(-1.0/3.0)):std::pow(v_.z, float(-1.0/3.0)));
}
//----

PFC_INLINE simd_vec3f rcbrt_z(const simd_vec3f &v_)
{
  // component-wise reciprocal cubic root (set to 0 for 0 components)
  return simd_vec3f(v_.x?v_.x<0?-std::pow(-v_.x, float(-1.0/3.0)):std::pow(v_.x, float(-1.0/3.0)):0,
                    v_.y?v_.y<0?-std::pow(-v_.y, float(-1.0/3.0)):std::pow(v_.y, float(-1.0/3.0)):0,
                    v_.z?v_.z<0?-std::pow(-v_.z, float(-1.0/3.0)):std::pow(v_.z, float(-1.0/3.0)):0);
}
//----
*/
PFC_INLINE float norm(const simd_vec3f &v_)
{
  // norm of the vector (=vector length)
#ifdef PFC_PLATFORM_SSE4
  float n;
  _mm_store_ss(&n, _mm_sqrt_ss(_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0x71)));
  return n;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  return sqrt(d[0]+d[1]+d[2]);
#endif
}
//----

PFC_INLINE float rnorm(const simd_vec3f &v_)
{
  // reciprocal norm of the vector
#ifdef PFC_PLATFORM_SSE4
  float rn;
  _mm_store_ss(&rn, _mm_rsqrt_ss(_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0x71)));
  return rn;
#else
  float r;
  simd_float4 v=_mm_mul_ps((simd_float4&)v_, (simd_float4&)v_);
  _mm_store_ss(&r, _mm_rsqrt_ss(_mm_add_ss(_mm_add_ss(v, _mm_shuffle_ps(v, v, 1)), _mm_shuffle_ps(v, v, 2))));
  return r;
#endif
}
//----

PFC_INLINE float rnorm_z(const simd_vec3f &v_)
{
  // reciprocal norm of the vector (set 0 for |v|=0)
#ifdef PFC_PLATFORM_SSE4
  float rn;
  simd_float4 n2=_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0x71);
  _mm_store_ss(&rn, _mm_and_ps(_mm_cmpgt_ss(n2, _mm_setzero_ps()), _mm_rsqrt_ss(n2)));
  return rn;
#else
  float rn;
  simd_float4 v=_mm_mul_ps((simd_float4&)v_, (simd_float4&)v_);
  v=_mm_add_ss(_mm_add_ss(v, _mm_shuffle_ps(v, v, 1)), _mm_shuffle_ps(v, v, 2));
  _mm_store_ss(&rn, _mm_and_ps(_mm_cmpgt_ss(v, _mm_setzero_ps()), _mm_rsqrt_ss(v)));
  return rn;
#endif
}
//----

PFC_INLINE float norm2(const simd_vec3f &v_)
{
  // squared norm of the vector
#ifdef PFC_PLATFORM_SSE4
  float n2;
  _mm_store_ss(&n2, _mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0x71));
  return n2;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  return d[0]+d[1]+d[2];
#endif
}
//----

PFC_INLINE float rnorm2(const simd_vec3f &v_)
{
  // reciprocal squared norm of the vector
#ifdef PFC_PLATFORM_SSE4
  float rn2;
  _mm_store_ss(&rn2, _mm_rcp_ss(_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0x71)));
  return rn2;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  return rcp(d[0]+d[1]+d[2]);
#endif
}
//----

PFC_INLINE float rnorm2_z(const simd_vec3f &v_)
{
  // reciprocal squared norm of the vector
#ifdef PFC_PLATFORM_SSE4
  float rn2;
  simd_float4 n2=_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0x71);
  _mm_store_ss(&rn2, _mm_and_ps(_mm_cmpgt_ss(n2, _mm_setzero_ps()), _mm_rcp_ss(n2)));
  return rn2;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  return rcp_z(d[0]+d[1]+d[2]);
#endif
}
//----

PFC_INLINE simd_vec3f unit(const simd_vec3f &v_)
{
  // unit vector of the vector
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_mul_ps((simd_float4&)v_, _mm_rsqrt_ps(_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0x7f))));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  float x=d[0]+d[1]+d[2];
  simd_float4 v=_mm_rsqrt_ss(_mm_load_ss(&x));
  return simd_vec3f(_mm_mul_ps(_mm_shuffle_ps(v, v, 0), (simd_float4&)v_));
#endif
}
//----

PFC_INLINE simd_vec3f unit_z(const simd_vec3f &v_)
{
  // unit vector of the vector. if |v|=0, return v=[0, 0, 0]
#ifdef PFC_PLATFORM_SSE4
  simd_float4 n2=_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0x7f);
  return simd_vec3f(_mm_and_ps(_mm_cmpgt_ps(n2, _mm_setzero_ps()), _mm_mul_ps((simd_float4&)v_, _mm_rsqrt_ps(n2))));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  float x=d[0]+d[1]+d[2];
  simd_float4 v=_mm_rsqrt_ss(_mm_load_ss(&x));
  return simd_vec3f(x?_mm_mul_ps(_mm_shuffle_ps(v, v, 0), (simd_float4&)v_):_mm_setzero_ps());
#endif
}
//----

PFC_INLINE simd_vec3f cross(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // cross-product of vectors
  simd_float4 v=_mm_sub_ps(_mm_mul_ps((simd_float4&)v0_, _mm_shuffle_ps((simd_float4&)v1_, (simd_float4&)v1_, _MM_SHUFFLE(3, 0, 2, 1))),
                           _mm_mul_ps((simd_float4&)v1_, _mm_shuffle_ps((simd_float4&)v0_, (simd_float4&)v0_, _MM_SHUFFLE(3, 0, 2, 1))));
  return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1));
}
//----

PFC_INLINE float dot(const simd_vec3f &v0_, const simd_vec3f &v1_)
{
  // dot-product of vectors
#ifdef PFC_PLATFORM_SSE4
  float d;
  _mm_store_ss(&d, _mm_dp_ps((simd_float4&)v0_, (simd_float4&)v1_, 0x71));
  return d;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v0_, (simd_float4&)v1_));
  return d[0]+d[1]+d[2];
#endif
}
//----

PFC_INLINE float dot1(const simd_vec3f &v_)
{
  // dot-product with [1, 1, 1]
/*#ifdef PFC_PLATFORM_SSE4
  float d;
  _mm_store_ss(&d, _mm_dp_ps((simd_float4&)v_, simd::g_one, 0x71));
  return d;
#else*/
  return v_.x+v_.y+v_.z;
/*#endif*/
}
//----

PFC_INLINE void neg(simd_vec3f &v_)
{
  // negate the vector
  (simd_float4&)v_=_mm_sub_ps(_mm_setzero_ps(), (simd_float4&)v_);
}
//----

PFC_INLINE simd_vec3f lerp(const simd_vec3f &v0_, const simd_vec3f &v1_, float t_)
{
  // linear vector interpolation. f(t=0)=v0, f(t=1)=v1
  return simd_vec3f(_mm_add_ps((simd_float4&)v0_, _mm_mul_ps(_mm_sub_ps((simd_float4&)v1_, (simd_float4&)v0_), _mm_set1_ps(t_))));
}
//----

PFC_INLINE simd_vec3f reflect(const simd_vec3f &v_, const simd_vec3f &n_)
{
  // reflect the vector about the normal: v'=2*n*(v.n)/(n.n)-v
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_sub_ps(_mm_mul_ps(_mm_mul_ps(_mm_add_ps((simd_float4&)n_, (simd_float4&)n_), _mm_dp_ps((simd_float4&)v_, (simd_float4&)n_, 0x7f)), _mm_rcp_ps(_mm_dp_ps((simd_float4&)n_, (simd_float4&)n_, 0x7f))), (simd_float4&)v_));
#else
  PFC_ALIGN(16) float32_t vn[4], nn[4];
  _mm_store_ps(vn, _mm_mul_ps((simd_float4&)v_, (simd_float4&)n_));
  _mm_store_ps(nn, _mm_mul_ps((simd_float4&)n_, (simd_float4&)n_));
  return simd_vec3f(_mm_sub_ps(_mm_mul_ps((simd_float4&)n_, _mm_set1_ps(2.0f*(vn[0]+vn[1]+vn[2])/(nn[0]+nn[1]+nn[2]))), (simd_float4&)v_));
#endif
}
//----

PFC_INLINE simd_vec3f reflect_u(const simd_vec3f &v_, const simd_vec3f &n_)
{
  // reflect the vector about the unit normal: v'=2*n*(v.n)-v
#ifdef PFC_PLATFORM_SSE4
  return simd_vec3f(_mm_sub_ps(_mm_mul_ps(_mm_add_ps((simd_float4&)n_, (simd_float4&)n_), _mm_dp_ps((simd_float4&)v_, (simd_float4&)n_, 0x7f)), (simd_float4&)v_));
#else
  simd_float4 v=_mm_mul_ps((simd_float4&)v_, (simd_float4&)n_);
  v=_mm_add_ps(_mm_add_ps(_mm_shuffle_ps(v, v, 0), _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1))), _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2)));
  return simd_vec3f(_mm_sub_ps(_mm_mul_ps(_mm_add_ps(v, v), (simd_float4&)n_), (simd_float4&)v_));
#endif
}
//----

template<>
PFC_INLINE vec3i to_vec3<int>(const simd_vec3f &v_)
{
  // convert to vec3i
  PFC_ALIGN(16) int32_t d[4];
  _mm_store_si128((__m128i*)d, _mm_cvttps_epi32((simd_float4&)v_));
  return vec3i(d[0], d[1], d[2]);
}
//----

template<>
PFC_INLINE simd_vec3f to_vec3<simd_float4>(const vec3i &v_)
{
  // convert to simd_vec3f
  return simd_vec3f(_mm_cvtepi32_ps(_mm_set_epi32(0, v_.z, v_.y, v_.x)));
}
//----------------------------------------------------------------------------


//============================================================================
// simd_vec4f
//============================================================================
simd_vec4f::vec4()
{
}
//----

simd_vec4f::vec4(float s_)
{
  // init vector with scalar
  (simd_float4&)*this=_mm_set1_ps(s_);
}
//----

simd_vec4f::vec4(float x_, float y_, float z_, float w_)
{
  // init vector with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

simd_vec4f::vec4(const simd_vec3f &v_, float w_)
{
  // init vector with 3d SIMD vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

simd_vec4f::vec4(const vec3f &v_, float w_)
{
  // init vector with 3d fp-vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

simd_vec4f::vec4(const vec4f &v_)
{
  // init vector with 4d fp-vector
  (simd_float4&)*this=_mm_loadu_ps((const float*)&v_);
}
//----

simd_vec4f::vec4(const simd_float4 &v_)
{
  // init vector with SIMD float4
  (simd_float4&)*this=v_;
}
//----

simd_vec4f::vec4(const float *a_)
{
  // init vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  (simd_float4&)*this=_mm_loadu_ps(a_);
}
//----------------------------------------------------------------------------

const float &simd_vec4f::operator[](unsigned idx_) const
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const float*>(this)[idx_];
}
//----

float &simd_vec4f::operator[](unsigned idx_)
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<float*>(this)[idx_];
}
//----

void simd_vec4f::set(float s_)
{
  // set vector with scalar
  (simd_float4&)*this=_mm_set1_ps(s_);
}
//----

void simd_vec4f::set(float x_, float y_, float z_, float w_)
{
  // set vector with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

void simd_vec4f::set(const simd_vec3f &v_, float w_)
{
  // set vector with 3d SIMD vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

void simd_vec4f::set(const vec3f &v_, float w_)
{
  // set vector with 3d fp-vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

void simd_vec4f::set(const simd_vec4f &v_)
{
  // set vector with 4d SIMD vector
  (simd_float4&)*this=(simd_float4&)v_;
}
//----

void simd_vec4f::set(const vec4f &v_)
{
  // set vector with 4d fp-vector
  (simd_float4&)*this=_mm_loadu_ps((const float*)&v_);
}
//----

void simd_vec4f::set(const simd_float4 &v_)
{
  // set vector with SIMD float4
  (simd_float4&)*this=v_;
}
//----

void simd_vec4f::set(const float *a_)
{
  // set vector with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  (simd_float4&)*this=_mm_loadu_ps(a_);
}
//----------------------------------------------------------------------------

PFC_INLINE bool is_zero(const simd_vec4f &v_)
{
  // test for zero-vector
  return _mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)v_, _mm_setzero_ps()))==0;
}
//----

PFC_INLINE bool is_sat(const simd_vec4f &v_)
{
  // test for saturated vector
  return _mm_movemask_ps(_mm_or_ps(_mm_cmplt_ps((simd_float4&)v_, _mm_setzero_ps()),
                                   _mm_cmpgt_ps((simd_float4&)v_, simd::g_one)))==0;
}
//----

PFC_INLINE bool is_ssat(const simd_vec4f &v_)
{
  // test for signed saturated vector
  return _mm_movemask_ps(_mm_or_ps(_mm_cmplt_ps((simd_float4&)v_, simd::g_neg_one),
                                   _mm_cmpgt_ps((simd_float4&)v_, simd::g_one)))==0;
}
//----

PFC_INLINE bool operator==(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // test for equality of vectors
  return _mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)v0_, (simd_float4&)v1_))==0;
}
//----

PFC_INLINE bool operator==(const simd_vec4f &v_, float s_)
{
  // test for equality of vector and scalar
  return _mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)v_, _mm_set1_ps(s_)))==0;
}
//----

PFC_INLINE bool operator==(float s_, const simd_vec4f &v_)
{
  // test for equality of vector and scalar
  return _mm_movemask_ps(_mm_cmpneq_ps(_mm_set1_ps(s_), (simd_float4&)v_))==0;
}
//----

PFC_INLINE bool operator!=(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // test for inequality of vectors
  return _mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)v0_, (simd_float4&)v1_))!=0;
}
//----

PFC_INLINE bool operator!=(const simd_vec4f &v_, float s_)
{
  // test for inequality of vector and scalar
  return _mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)v_, _mm_set1_ps(s_)))!=0;
}
//----

PFC_INLINE bool operator!=(float s_, const simd_vec4f &v_)
{
  // test for inequality of vector and scalar
  return _mm_movemask_ps(_mm_cmpneq_ps(_mm_set1_ps(s_), (simd_float4&)v_))!=0;
}
//----

PFC_INLINE simd_vec4f operator<(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise less-than (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmplt_ps((simd_float4&)v0_, (simd_float4&)v1_), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator<(const simd_vec4f &v_, float s_)
{
  // component-wise less-than (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmplt_ps((simd_float4&)v_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator<(float s_, const simd_vec4f &v_)
{
  // component-wise less-than (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmplt_ps(_mm_set1_ps(s_), (simd_float4&)v_), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator>(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise greater-than (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmpgt_ps((simd_float4&)v0_, (simd_float4&)v1_), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator>(const simd_vec4f &v_, float s_)
{
  // component-wise greater-than (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmpgt_ps((simd_float4&)v_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator>(float s_, const simd_vec4f &v_)
{
  // component-wise greater-than (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmpgt_ps(_mm_set1_ps(s_), (simd_float4&)v_), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator<=(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise less-or-equal (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmple_ps((simd_float4&)v0_, (simd_float4&)v1_), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator<=(const simd_vec4f &v_, float s_)
{
  // component-wise less-or-equal (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmple_ps((simd_float4&)v_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator<=(float s_, const simd_vec4f &v_)
{
  // component-wise less-or-equal (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmple_ps(_mm_set1_ps(s_), (simd_float4&)v_), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator>=(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise greater-or-equal (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmpge_ps((simd_float4&)v0_, (simd_float4&)v1_), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator>=(const simd_vec4f &v_, float s_)
{
  // component-wise greater-or-equal (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmpge_ps((simd_float4&)v_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_vec4f operator>=(float s_, const simd_vec4f &v_)
{
  // component-wise greater-or-equal (false=0, true=1)
  return simd_vec4f(_mm_and_ps(_mm_cmpge_ps(_mm_set1_ps(s_), (simd_float4&)v_), simd::g_one));
}
//----

PFC_INLINE simd_vec4f sel_eq(const simd_vec4f &t0_, const simd_vec4f &t1_, const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise equal vector select (t0_==t1_?v0_:v1_)
  simd_float4 r=_mm_cmpeq_ps((simd_float4&)t0_, (simd_float4&)t1_);
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec4f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE simd_vec4f sel_lt(const simd_vec4f &t0_, const simd_vec4f &t1_, const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise less-than vector select (t0_<t1_?v0_:v1_)
  simd_float4 r=_mm_cmplt_ps((simd_float4&)t0_, (simd_float4&)t1_);
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec4f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE simd_vec4f sel_le(const simd_vec4f &t0_, const simd_vec4f &t1_, const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise less-or-equal vector select (t0_<=t1_?v0_:v1_)
  simd_float4 r=_mm_cmple_ps((simd_float4&)t0_, (simd_float4&)t1_);
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec4f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE simd_vec4f sel_eqz(const simd_vec4f &t_, const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise equal-to-zero vector select (t_==0?v0_:v1_)
  simd_float4 r=_mm_cmpeq_ps((simd_float4&)t_, _mm_setzero_ps());
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec4f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE simd_vec4f sel_ltz(const simd_vec4f &t_, const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise less-than-zero vector select (t_<0?v0_:v1_)
  simd_float4 r=_mm_cmplt_ps((simd_float4&)t_, _mm_setzero_ps());
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec4f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE simd_vec4f sel_lez(const simd_vec4f &t_, const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise less-or-equal-to-zero vector select (t_<=0?v0_:v1_)
  simd_float4 r=_mm_cmple_ps((simd_float4&)t_, _mm_setzero_ps());
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_blendv_ps((simd_float4&)v1_, (simd_float4&)v0_, r));
#else
  return simd_vec4f(_mm_or_ps(_mm_and_ps(r, (simd_float4&)v0_), _mm_andnot_ps(r, (simd_float4&)v1_)));
#endif
}
//----

PFC_INLINE void operator+=(simd_vec4f &vr_, const simd_vec4f &v_)
{
  // add vector to vector
  (simd_float4&)vr_=_mm_add_ps((simd_float4&)vr_, (simd_float4&)v_);
}
//----

PFC_INLINE void operator+=(simd_vec4f &vr_, float s_)
{
  // add scalar to each component of the vector
  (simd_float4&)vr_=_mm_add_ps((simd_float4&)vr_, _mm_set1_ps(s_));
}
//----

PFC_INLINE void operator-=(simd_vec4f &vr_, const simd_vec4f &v_)
{
  // subtract vector from vector
  (simd_float4&)vr_=_mm_sub_ps((simd_float4&)vr_, (simd_float4&)v_);
}
//----

PFC_INLINE void operator-=(simd_vec4f &vr_, float s_)
{
  // subtract scalar from each component of the vector
  (simd_float4&)vr_=_mm_sub_ps((simd_float4&)vr_, _mm_set1_ps(s_));
}
//----

PFC_INLINE void operator*=(simd_vec4f &vr_, const simd_vec4f &v_)
{
  // component-wise vector by vector multiply
  (simd_float4&)vr_=_mm_mul_ps((simd_float4&)vr_, (simd_float4&)v_);
}
//----

PFC_INLINE void operator*=(simd_vec4f &vr_, float s_)
{
  // multiply vector by scalar
  (simd_float4&)vr_=_mm_mul_ps((simd_float4&)vr_, _mm_set1_ps(s_));
}
//----

PFC_INLINE void operator*=(simd_vec4f &vr_, const simd_mat44f &m_)
{
  // multiply vector by matrix
  (simd_float4&)vr_=_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                                     _mm_mul_ps(_mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                                     _mm_mul_ps(_mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z)),
                                                     _mm_mul_ps(_mm_shuffle_ps((simd_float4&)vr_, (simd_float4&)vr_, _MM_SHUFFLE(3, 3, 3, 3)), (simd_float4&)m_.w));
}
//----

PFC_INLINE void operator/=(simd_vec4f &vr_, const simd_vec4f &v_)
{
  // component-wise vector by vector division
  (simd_float4&)vr_=_mm_mul_ps((simd_float4&)vr_, _mm_rcp_ps((simd_float4&)v_));
}
//----

PFC_INLINE void operator/=(simd_vec4f &vr_, float s_)
{
  // divide vector by scalar
  simd_float4 rs=_mm_rcp_ss(_mm_load_ss(&s_));
  (simd_float4&)vr_=_mm_mul_ps((simd_float4&)vr_, _mm_shuffle_ps(rs, rs, 0));
}
//----

PFC_INLINE simd_vec4f operator+(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // add vector to vector
  return simd_vec4f(_mm_add_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec4f operator+(const simd_vec4f &v_, float s_)
{
  // add scalar to each component of the vector
  return simd_vec4f(_mm_add_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec4f operator+(float s_, const simd_vec4f &v_)
{
  // add each component of the vector to a scalar vector
  return simd_vec4f(_mm_add_ps(_mm_set1_ps(s_), (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec4f operator-(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // subtract vector from vector
  return simd_vec4f(_mm_sub_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec4f operator-(const simd_vec4f &v_, float s_)
{
  // subtract scalar from each component of the vector
  return simd_vec4f(_mm_sub_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec4f operator-(float s_, const simd_vec4f &v_)
{
  // subtract each component of the vector from a scalar vector
  return simd_vec4f(_mm_sub_ps(_mm_set1_ps(s_), (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec4f operator-(const simd_vec4f &v_)
{
  // negate vector
  return simd_vec4f(_mm_sub_ps(_mm_setzero_ps(), (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec4f operator*(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise vector by vector multiply
  return simd_vec4f(_mm_mul_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec4f operator*(const simd_vec4f &v_, float s_)
{
  // multiply vector by scalar
  return simd_vec4f(_mm_mul_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec4f operator*(float s_, const simd_vec4f &v_)
{
  // multiply vector by scalar
  return simd_vec4f(_mm_mul_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec4f operator*(const simd_vec4f &v_, const simd_mat44f &m_)
{
  // multiply vector by matrix
  return simd_vec4f(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                                     _mm_mul_ps(_mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                                     _mm_mul_ps(_mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z)),
                                                     _mm_mul_ps(_mm_shuffle_ps((simd_float4&)v_, (simd_float4&)v_, _MM_SHUFFLE(3, 3, 3, 3)), (simd_float4&)m_.w)));
}
//----

PFC_INLINE simd_vec4f operator*(const simd_mat44f &m_, const simd_vec4f &v_)
{
  // multiply matrix by transposed vector
#ifdef PFC_PLATFORM_SSE4
  simd_vec4f vr;
  _mm_store_ss(&vr.x, _mm_dp_ps((simd_float4&)m_.x, (simd_float4&)v_, 0xf1));
  _mm_store_ss(&vr.y, _mm_dp_ps((simd_float4&)m_.y, (simd_float4&)v_, 0xf1));
  _mm_store_ss(&vr.z, _mm_dp_ps((simd_float4&)m_.z, (simd_float4&)v_, 0xf1));
  _mm_store_ss(&vr.w, _mm_dp_ps((simd_float4&)m_.w, (simd_float4&)v_, 0xf1));
  return vr;
#else
  PFC_ALIGN(16) float32_t x[4], y[4], z[4], w[4];
  _mm_store_ps(x, _mm_mul_ps((simd_float4&)m_.x, (simd_float4&)v_));
  _mm_store_ps(y, _mm_mul_ps((simd_float4&)m_.y, (simd_float4&)v_));
  _mm_store_ps(z, _mm_mul_ps((simd_float4&)m_.z, (simd_float4&)v_));
  _mm_store_ps(w, _mm_mul_ps((simd_float4&)m_.w, (simd_float4&)v_));
  return simd_vec4f(x[0]+x[1]+x[2]+x[3], y[0]+y[1]+y[2]+y[3], z[0]+z[1]+z[2]+z[3], w[0]+w[1]+w[2]+w[3]);
#endif
}
//----

PFC_INLINE simd_vec4f operator/(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise vector by vector division
  return simd_vec4f(_mm_mul_ps((simd_float4&)v0_, _mm_rcp_ps((simd_float4&)v1_)));
}
//----

PFC_INLINE simd_vec4f operator/(const simd_vec4f &v_, float s_)
{
  // divide vector by scalar
  simd_float4 rs=_mm_rcp_ss(_mm_load_ss(&s_));
  return simd_vec4f(_mm_mul_ps((simd_float4&)v_, _mm_shuffle_ps(rs, rs, 0)));
}
//----

PFC_INLINE simd_vec4f min(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise min vector
  return simd_vec4f(_mm_min_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec4f min(const simd_vec4f &v0_, const simd_vec4f &v1_, const simd_vec4f &v2_)
{
  // component-wise min vector
  return simd_vec4f(_mm_min_ps(_mm_min_ps((simd_float4&)v0_, (simd_float4&)v1_), (simd_float4&)v2_));
}
//----

PFC_INLINE simd_vec4f min(const simd_vec4f &v0_, const simd_vec4f &v1_, const simd_vec4f &v2_, const simd_vec4f &v3_)
{
  // component-wise min vector
  return simd_vec4f(_mm_min_ps(_mm_min_ps(_mm_min_ps((simd_float4&)v0_, (simd_float4&)v1_), (simd_float4&)v2_), (simd_float4&)v3_));
}
//----

PFC_INLINE simd_vec4f min(const simd_vec4f &v_, float s_)
{
  // component-wise min vector
  return simd_vec4f(_mm_min_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec4f min(float s_, const simd_vec4f &v_)
{
  // component-wise min vector
  return simd_vec4f(_mm_min_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec4f max(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise max vector
  return simd_vec4f(_mm_max_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec4f max(const simd_vec4f &v0_, const simd_vec4f &v1_, const simd_vec4f &v2_)
{
  // component-wise max vector
  return simd_vec4f(_mm_max_ps(_mm_max_ps((simd_float4&)v0_, (simd_float4&)v1_), (simd_float4&)v2_));
}
//----

PFC_INLINE simd_vec4f max(const simd_vec4f &v0_, const simd_vec4f &v1_, const simd_vec4f &v2_, const simd_vec4f &v3_)
{
  // component-wise max vector
  return simd_vec4f(_mm_max_ps(_mm_max_ps(_mm_max_ps((simd_float4&)v0_, (simd_float4&)v1_), (simd_float4&)v2_), (simd_float4&)v3_));
}
//----

PFC_INLINE simd_vec4f max(const simd_vec4f &v_, float s_)
{
  // component-wise max vector
  return simd_vec4f(_mm_max_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec4f max(float s_, const simd_vec4f &v_)
{
  // component-wise max vector
  return simd_vec4f(_mm_max_ps((simd_float4&)v_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_vec4f mul(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // component-wise multiply: v0_*v1
  return simd_vec4f(_mm_mul_ps((simd_float4&)v0_, (simd_float4&)v1_));
}
//----

PFC_INLINE simd_vec4f madd(const simd_vec4f &vm0_, const simd_vec4f &vm1_, const simd_vec4f &va_)
{
  // component-wise multiply-add: vm0_*vm1+va_
  return simd_vec4f(_mm_add_ps(_mm_mul_ps((simd_float4&)vm0_, (simd_float4&)vm1_), (simd_float4&)va_));
}
//----

PFC_INLINE simd_vec4f madd(const simd_vec4f &vm_, float sm_, float sa_)
{
  // component-wise multiply-add: vm_*sm_+sa_
  return simd_vec4f(_mm_add_ps(_mm_mul_ps((simd_float4&)vm_, _mm_set1_ps(sm_)), _mm_set1_ps(sa_)));
}
//----

PFC_INLINE simd_vec4f madd(const simd_vec4f &vm0_, const simd_vec4f &vm1_, float sa_)
{
  // component-wise multiply-add: vm0_*vm1_+sa_
  return simd_vec4f(_mm_add_ps(_mm_mul_ps((simd_float4&)vm0_, (simd_float4&)vm1_), _mm_set1_ps(sa_)));
}
//----

PFC_INLINE simd_vec4f madd(const simd_vec4f &vm_, float sm_, const simd_vec4f &va_)
{
  // component-wise multiply-add: vm_*sm_+va_
  return simd_vec4f(_mm_add_ps(_mm_mul_ps((simd_float4&)vm_, _mm_set1_ps(sm_)), (simd_float4&)va_));
}
//----

PFC_INLINE simd_vec4f rcp(const simd_vec4f &v_)
{
  // component-wise reciprocal
  return simd_vec4f(_mm_rcp_ps((simd_float4&)v_));
}
//----

PFC_INLINE simd_vec4f rcp_z(const simd_vec4f &v_)
{
  // component-wise reciprocal (set to 0 for 0 components)
  return simd_vec4f(_mm_and_ps(_mm_cmpneq_ps((simd_float4&)v_, _mm_setzero_ps()), _mm_rcp_ps((simd_float4&)v_)));
}
//----

PFC_INLINE simd_vec4f floor(const simd_vec4f &v_)
{
  // component-wise floor
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_round_ps((simd_float4&)v_, _MM_FROUND_FLOOR));
#else
  const float *f=(const float*)&v_;
  return simd_vec4f(std::floor(f[0]), std::floor(f[1]), std::floor(f[2]), std::floor(f[3]));
#endif
}
//----

PFC_INLINE simd_vec4f ceil(const simd_vec4f &v_)
{
  // component-wise ceil
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_round_ps((simd_float4&)v_, _MM_FROUND_CEIL));
#else
  const float *f=(const float*)&v_;
  return simd_vec4f(std::ceil(f[0]), std::ceil(f[1]), std::ceil(f[2]), std::ceil(f[3]));
#endif
}
//----

PFC_INLINE simd_vec4f trunc(const simd_vec4f &v_)
{
  // component-wise truncate
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_round_ps((simd_float4&)v_, _MM_FROUND_TO_ZERO));
#else
  return simd_vec4f(float(int(v_.x)), float(int(v_.y)), float(int(v_.z)), float(int(v_.w)));
#endif
}
//----

PFC_INLINE simd_vec4f frc(const simd_vec4f &v_)
{
  // component-wise fractional
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_sub_ps((simd_float4&)v_, _mm_round_ps((simd_float4&)v_, _MM_FROUND_TO_ZERO)));
#else
  const float *f=(const float*)&v_;
  return simd_vec4f(f[0]-float(int(f[0])), f[1]-float(int(f[1])), f[2]-float(int(f[2])), f[3]-float(int(f[3])));
#endif
}
//----

PFC_INLINE simd_vec4f mod(const simd_vec4f &v_, float div_)
{
  // component-wise modulo
#ifdef PFC_PLATFORM_SSE4
  simd_float4 d=_mm_set1_ps(div_);
  return simd_vec4f(_mm_sub_ps((simd_float4&)v_, _mm_mul_ps(_mm_round_ps(_mm_mul_ps((simd_float4&)v_, _mm_rcp_ps(d)), _MM_FROUND_TO_ZERO), d)));
#else
  const float *f=(const float*)&v_;
  return simd_vec4f(std::fmod(f[0], div_), std::fmod(f[1], div_), std::fmod(f[2], div_), std::fmod(f[3], div_));
#endif
}
//----

PFC_INLINE simd_vec4f cycle(const simd_vec4f &v_, float cycle_)
{
  // component-wise cycle
#ifdef PFC_PLATFORM_SSE4
  simd_float4 d=_mm_set1_ps(cycle_);
  return simd_vec4f(_mm_sub_ps((simd_float4&)v_, _mm_mul_ps(_mm_round_ps(_mm_mul_ps((simd_float4&)v_, _mm_rcp_ps(d)), _MM_FROUND_TO_NEG_INF), d)));
#else
  const float *f=(const float*)&v_;
  float x=std::fmod(f[0], cycle_), y=std::fmod(f[1], cycle_), z=std::fmod(f[2], cycle_), w=std::fmod(f[3], cycle_);
  return simd_vec4f(x<0?cycle_+x:x, y<0?cycle_+y:y, z<0?cycle_+z:z, w<0?cycle_+w:w);
#endif
}
//----

PFC_INLINE simd_vec4f sat(const simd_vec4f &v_)
{
  // component-wise saturate
  return simd_vec4f(_mm_min_ps(_mm_max_ps((simd_float4&)v_, _mm_setzero_ps()), simd::g_one));
}
//----

PFC_INLINE simd_vec4f ssat(const simd_vec4f &v_)
{
  // component-wise signed saturate
  return simd_vec4f(_mm_min_ps(_mm_max_ps((simd_float4&)v_, simd::g_neg_one), simd::g_one));
}
//----

PFC_INLINE simd_vec4f clamp(const simd_vec4f &v_, const simd_vec4f &min_, const simd_vec4f &max_)
{
  // component-wise clamp (to vectors)
  return simd_vec4f(_mm_min_ps(_mm_max_ps((simd_float4&)v_, (simd_float4&)min_), (simd_float4&)max_));
}
//----

PFC_INLINE simd_vec4f clamp(const simd_vec4f &v_, float min_, float max_)
{
  // component-wise clamp (to scalars)
  return simd_vec4f(_mm_min_ps(_mm_max_ps((simd_float4&)v_, _mm_set1_ps(min_)), _mm_set1_ps(max_)));
}
//----

PFC_INLINE simd_vec4f abs(const simd_vec4f &v_)
{
  // component-wise absolute
  return simd_vec4f(_mm_and_ps((simd_float4&)v_, simd::g_mask_not_sign));
}
//----

PFC_INLINE simd_vec4f sgn(const simd_vec4f &v_)
{
  // component-wise signum (neg=-1, pos=+1, zero=0)
  return simd_vec4f(_mm_and_ps(_mm_cmpneq_ps((simd_float4&)v_, _mm_setzero_ps()), _mm_or_ps(_mm_and_ps(_mm_cmplt_ps((simd_float4&)v_, _mm_setzero_ps()), simd::g_mask_sign), simd::g_one)));
}
//----

PFC_INLINE simd_vec4f sgn_zp(const simd_vec4f &v_)
{
  // component-wise signum (neg=-1, pos&zero=+1)
  return simd_vec4f(_mm_or_ps(_mm_and_ps(_mm_cmplt_ps((simd_float4&)v_, _mm_setzero_ps()), simd::g_mask_sign), simd::g_one));
}
//----

PFC_INLINE simd_vec4f sqr(const simd_vec4f &v_)
{
  // component-wise square
  return simd_vec4f(_mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec4f cubic(const simd_vec4f &v_)
{
  // component-wise cubic
  return simd_vec4f(_mm_mul_ps(_mm_mul_ps((simd_float4&)v_, (simd_float4&)v_), (simd_float4&)v_));
}
//----

PFC_INLINE simd_vec4f sqrt(const simd_vec4f &v_)
{
  // component-wise square root
  return simd_vec4f(_mm_sqrt_ps((simd_float4&)v_));
}
//----

PFC_INLINE simd_vec4f sqrt_z(const simd_vec4f &v_)
{
  // component-wise square root (set to 0 for components less than zero)
  return simd_vec4f(_mm_sqrt_ps(_mm_max_ps((simd_float4&)v_, _mm_setzero_ps())));
}
//----
/*
PFC_INLINE simd_vec4f cbrt(const simd_vec4f &v_)
{
  // component-wise cubic root
  return simd_vec4f(v_.x<0?-std::pow(-v_.x, float(1.0/3.0)):std::pow(v_.x, float(1.0/3.0)),
                    v_.y<0?-std::pow(-v_.y, float(1.0/3.0)):std::pow(v_.y, float(1.0/3.0)),
                    v_.z<0?-std::pow(-v_.z, float(1.0/3.0)):std::pow(v_.z, float(1.0/3.0)),
                    v_.w<0?-std::pow(-v_.w, float(1.0/3.0)):std::pow(v_.w, float(1.0/3.0)));
}
//----
*/
PFC_INLINE simd_vec4f rsqrt(const simd_vec4f &v_)
{
  // component-wise reciprocal square root
  return simd_vec4f(_mm_rsqrt_ps((simd_float4&)v_));
}
//----

PFC_INLINE simd_vec4f rsqrt_z(const simd_vec4f &v_)
{
  // component-wise reciprocal square root (set to 0 for components less than or equal to zero)
  return simd_vec4f(_mm_and_ps(_mm_cmpgt_ps((simd_float4&)v_, _mm_setzero_ps()), _mm_rsqrt_ps((simd_float4&)v_)));
}
//----
/*
PFC_INLINE simd_vec4f rcbrt(const simd_vec4f &v_)
{
  // component-wise reciprocal cubic root
  return simd_vec4f(v_.x<0?-std::pow(-v_.x, float(-1.0/3.0)):std::pow(v_.x, float(-1.0/3.0)),
                    v_.y<0?-std::pow(-v_.y, float(-1.0/3.0)):std::pow(v_.y, float(-1.0/3.0)),
                    v_.z<0?-std::pow(-v_.z, float(-1.0/3.0)):std::pow(v_.z, float(-1.0/3.0)),
                    v_.w<0?-std::pow(-v_.w, float(-1.0/3.0)):std::pow(v_.w, float(-1.0/3.0)));
}
//----

PFC_INLINE simd_vec4f rcbrt_z(const simd_vec4f &v_)
{
  // component-wise reciprocal cubic root (set to 0 for 0 components)
  return simd_vec4f(v_.x?v_.x<0?-std::pow(-v_.x, float(-1.0/3.0)):std::pow(v_.x, float(-1.0/3.0)):0,
                    v_.y?v_.y<0?-std::pow(-v_.y, float(-1.0/3.0)):std::pow(v_.y, float(-1.0/3.0)):0,
                    v_.z?v_.z<0?-std::pow(-v_.z, float(-1.0/3.0)):std::pow(v_.z, float(-1.0/3.0)):0,
                    v_.w?v_.w<0?-std::pow(-v_.w, float(-1.0/3.0)):std::pow(v_.w, float(-1.0/3.0)):0);
}
//----
*/
PFC_INLINE float norm(const simd_vec4f &v_)
{
  // norm of the vector (=vector length)
#ifdef PFC_PLATFORM_SSE4
  float n;
  _mm_store_ss(&n, _mm_sqrt_ss(_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0xf1)));
  return n;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  return sqrt(d[0]+d[1]+d[2]+d[3]);
#endif
}
//----

PFC_INLINE float rnorm(const simd_vec4f &v_)
{
  // reciprocal norm of the vector
#ifdef PFC_PLATFORM_SSE4
  float rn;
  _mm_store_ss(&rn, _mm_rsqrt_ss(_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0xf1)));
  return rn;
#else
  float rn;
  simd_float4 v=_mm_mul_ps((simd_float4&)v_, (simd_float4&)v_);
  v=_mm_add_ps(_mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 1)), _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 2, 3)));
  _mm_store_ss(&rn, _mm_rsqrt_ss(_mm_add_ss(v, _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 1)))));
  return rn;
#endif
}
//----

PFC_INLINE float rnorm_z(const simd_vec4f &v_)
{
  // reciprocal norm of the vector
#ifdef PFC_PLATFORM_SSE4
  float rn;
  simd_float4 n2=_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0xf1);
  _mm_store_ss(&rn, _mm_and_ps(_mm_cmpgt_ss(n2, _mm_setzero_ps()), _mm_rsqrt_ss(n2)));
  return rn;
#else
  float rn;
  simd_float4 v=_mm_mul_ps((simd_float4&)v_, (simd_float4&)v_);
  v=_mm_add_ps(_mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 1)), _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 2, 3)));
  v=_mm_add_ss(v, _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 1)));
  _mm_store_ss(&rn, _mm_and_ps(_mm_cmpgt_ss(v, _mm_setzero_ps()), _mm_rsqrt_ss(v)));
  return rn;
#endif
}
//----

PFC_INLINE float norm2(const simd_vec4f &v_)
{
  // squared norm of the vector
#ifdef PFC_PLATFORM_SSE4
  float n2;
  _mm_store_ss(&n2, _mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0xf1));
  return n2;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  return d[0]+d[1]+d[2]+d[3];
#endif
}
//----

PFC_INLINE float rnorm2(const simd_vec4f &v_)
{
  // reciprocal squared norm of the vector
#ifdef PFC_PLATFORM_SSE4
  float rn2;
  _mm_store_ss(&rn2, _mm_rcp_ss(_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0xf1)));
  return rn2;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  return rcp(d[0]+d[1]+d[2]+d[3]);
#endif
}
//----

PFC_INLINE float rnorm2_z(const simd_vec4f &v_)
{
  // reciprocal squared norm of the vector
#ifdef PFC_PLATFORM_SSE4
  float rn2;
  simd_float4 n2=_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0xf1);
  _mm_store_ss(&rn2, _mm_and_ps(_mm_cmpgt_ss(n2, _mm_setzero_ps()), _mm_rcp_ss(n2)));
  return rn2;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  return rcp_z(d[0]+d[1]+d[2]+d[3]);
#endif
}
//----

PFC_INLINE simd_vec4f unit(const simd_vec4f &v_)
{
  // unit vector of the vector
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_mul_ps((simd_float4&)v_, _mm_rsqrt_ps(_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0xff))));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  float x=d[0]+d[1]+d[2]+d[3];
  simd_float4 v=_mm_rsqrt_ss(_mm_load_ss(&x));
  return simd_vec4f(_mm_mul_ps(_mm_shuffle_ps(v, v, 0), (simd_float4&)v_));
#endif
}
//----

PFC_INLINE simd_vec4f unit_z(const simd_vec4f &v_)
{
  // unit vector of the vector. if |v|=0, return v=[0, 0, 0, 0]
#ifdef PFC_PLATFORM_SSE4
  simd_float4 n2=_mm_dp_ps((simd_float4&)v_, (simd_float4&)v_, 0xff);
  return simd_vec4f(_mm_and_ps(_mm_cmpgt_ps(n2, _mm_setzero_ps()), _mm_mul_ps((simd_float4&)v_, _mm_rsqrt_ps(n2))));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v_, (simd_float4&)v_));
  float x=d[0]+d[1]+d[2]+d[3];
  simd_float4 v=_mm_rsqrt_ss(_mm_load_ss(&x));
  return simd_vec4f(x?_mm_mul_ps(_mm_shuffle_ps(v, v, 0), (simd_float4&)v_):_mm_setzero_ps());
#endif
}
//----

PFC_INLINE float dot(const simd_vec4f &v0_, const simd_vec4f &v1_)
{
  // dot-product of the vectors
#ifdef PFC_PLATFORM_SSE4
  float d;
  _mm_store_ss(&d, _mm_dp_ps((simd_float4&)v0_, (simd_float4&)v1_, 0xf1));
  return d;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)v0_, (simd_float4&)v1_));
  return d[0]+d[1]+d[2]+d[3];
#endif
}
//----

PFC_INLINE float dot1(const simd_vec4f &v_)
{
  // dot-product with [1, 1, 1, 1]
/*#ifdef PFC_PLATFORM_SSE4
  float d;
  _mm_store_ss(&d, _mm_dp_ps((simd_float4&)v_, simd::g_one, 0xf1));
  return d;
#else*/
  return v_.x+v_.y+v_.z+v_.w;
/*#endif*/
}
//----

PFC_INLINE void neg(simd_vec4f &v_)
{
  // negate the vector
  (simd_float4&)v_=_mm_sub_ps(_mm_setzero_ps(), (simd_float4&)v_);
}
//----

PFC_INLINE simd_vec4f lerp(const simd_vec4f &v0_, const simd_vec4f &v1_, float t_)
{
  // linear vector interpolation. f(t=0)=v0, f(t=1)=v1
  return simd_vec4f(_mm_add_ps((simd_float4&)v0_, _mm_mul_ps(_mm_sub_ps((simd_float4&)v1_, (simd_float4&)v0_), _mm_set1_ps(t_))));
}
//----

PFC_INLINE simd_vec4f reflect(const simd_vec4f &v_, const simd_vec4f &n_)
{
  // reflect the vector about the normal: v'=2*n*(v.n)/(n.n)-v
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_sub_ps(_mm_mul_ps(_mm_mul_ps(_mm_add_ps((simd_float4&)n_, (simd_float4&)n_), _mm_dp_ps((simd_float4&)v_, (simd_float4&)n_, 0xff)), _mm_rcp_ps(_mm_dp_ps((simd_float4&)n_, (simd_float4&)n_, 0xff))), (simd_float4&)v_));
#else
  PFC_ALIGN(16) float32_t vn[4], nn[4];
  _mm_store_ps(vn, _mm_mul_ps((simd_float4&)v_, (simd_float4&)n_));
  _mm_store_ps(nn, _mm_mul_ps((simd_float4&)n_, (simd_float4&)n_));
  return simd_vec4f(_mm_sub_ps(_mm_mul_ps((simd_float4&)n_, _mm_set1_ps(2.0f*(vn[0]+vn[1]+vn[2]+vn[3])/(nn[0]+nn[1]+nn[2]+nn[3]))), (simd_float4&)v_));
#endif
}
//----

PFC_INLINE simd_vec4f reflect_u(const simd_vec4f &v_, const simd_vec4f &n_)
{
  // reflect the vector about the unit normal: v'=2*n*(v.n)-v
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_sub_ps(_mm_mul_ps(_mm_add_ps((simd_float4&)n_, (simd_float4&)n_), _mm_dp_ps((simd_float4&)v_, (simd_float4&)n_, 0xff)), (simd_float4&)v_));
#else
  simd_float4 v=_mm_mul_ps((simd_float4&)v_, (simd_float4&)n_);
  v=_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_shuffle_ps(v, v, 0), _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1))), _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2))), _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3)));
  return simd_vec4f(_mm_sub_ps(_mm_mul_ps(_mm_add_ps(v, v), (simd_float4&)n_), (simd_float4&)v_));
#endif
}
//----

template<>
PFC_INLINE vec4i to_vec4<int>(const simd_vec4f &v_)
{
  // convert to vec4i
  PFC_ALIGN(16) int32_t d[4];
  _mm_store_si128((__m128i*)d, _mm_cvttps_epi32((simd_float4&)v_));
  return vec4i(d[0], d[1], d[2], d[3]);
}
//----

template<>
PFC_INLINE simd_vec4f to_vec4<simd_float4>(const vec4i &v_)
{
  // convert to simd_vec4f
  return simd_vec4f(_mm_cvtepi32_ps(_mm_set_epi32(v_.w, v_.z, v_.y, v_.x)));
}
//----------------------------------------------------------------------------


//============================================================================
// simd_mat33f
//============================================================================
simd_mat33f::mat33()
{
}
//----

simd_mat33f::mat33(float s_)
{
  // init matrix with scalar
  simd_float4 s=_mm_set1_ps(s_);
  (simd_float4&)x=s;
  (simd_float4&)y=s;
  (simd_float4&)z=s;
}
//----

simd_mat33f::mat33(const simd_vec3f &row0_,
                   const simd_vec3f &row1_,
                   const simd_vec3f &row2_)
  :x(row0_)
  ,y(row1_)
  ,z(row2_)
{
  // init matrix with row-vectors
}
//----

simd_mat33f::mat33(float d0_, float d1_, float d2_)
  :x(d0_,  0.0f, 0.0f)
  ,y(0.0f, d1_,  0.0f)
  ,z(0.0f, 0.0f, d2_ )
{
  // init matrix with diagonal scalars
}
//----

simd_mat33f::mat33(float m00_, float m01_, float m02_,
                   float m10_, float m11_, float m12_,
                   float m20_, float m21_, float m22_)
  :x(m00_, m01_, m02_)
  ,y(m10_, m11_, m12_)
  ,z(m20_, m21_, m22_)
{
  // init matrix with scalars
}
//----

simd_mat33f::mat33(const simd_float4 &row0_,
                   const simd_float4 &row1_,
                   const simd_float4 &row2_)
  :x(row0_)
  ,y(row1_)
  ,z(row2_)
{
  // init matrix with SIMD float4's
}
//----

simd_mat33f::mat33(const mat22f &m_)
  :x(m_.x, 0.0f)
  ,y(m_.y, 0.0f)
  ,z(simd::g_ident_z)
{
  // init matrix with 2d fp-matrix (upper-left matrix)
}
//----

simd_mat33f::mat33(const mat33f &m_)
  :x(m_.x)
  ,y(m_.y)
  ,z(m_.z)
{
  // init matrix with 3d fp-matrix
}
//----

simd_mat33f::mat33(const simd_mat44f &m_)
  :x((simd_float4&)m_.x)
  ,y((simd_float4&)m_.y)
  ,z((simd_float4&)m_.z)
{
  // init matrix with 4d SIMD matrix (upper-left matrix)
}
//----

simd_mat33f::mat33(const mat44f &m_)
  :x((const float*)&m_.x)
  ,y((const float*)&m_.y)
  ,z((const float*)&m_.z)
{
  // init matrix with 4d fp-matrix (upper-left matrix)
}
//----

simd_mat33f::mat33(const float *a_)
{
  // init matrix with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  (simd_float4&)x=_mm_loadu_ps(a_+0);
  (simd_float4&)y=_mm_loadu_ps(a_+3);
  (simd_float4&)z=_mm_loadu_ps(a_+6);
}
//----------------------------------------------------------------------------

const simd_vec3f &simd_mat33f::operator[](unsigned row_) const
{
  // return reference to nth vector (x=0, y=1, z=2)
  PFC_ASSERT_PEDANTIC(row_<3);
  return reinterpret_cast<const simd_vec3f*>(this)[row_];
}
//----

simd_vec3f &simd_mat33f::operator[](unsigned row_)
{
  // return reference to nth vector (x=0, y=1, z=2)
  PFC_ASSERT_PEDANTIC(row_<3);
  return reinterpret_cast<simd_vec3f*>(this)[row_];
}
//----

void simd_mat33f::set(float s_)
{
  // set matrix with scalar
  simd_float4 s=_mm_set1_ps(s_);
  (simd_float4&)x=s;
  (simd_float4&)y=s;
  (simd_float4&)z=s;
}
//----

void simd_mat33f::set(float d0_, float d1_, float d2_)
{
  // set matrix with diagonal scalars
  x.set(d0_,  0.0f, 0.0f);
  y.set(0.0f, d1_,  0.0f);
  z.set(0.0f, 0.0f, d2_ );
}
//----

void simd_mat33f::set(float m00_, float m01_, float m02_,
                      float m10_, float m11_, float m12_,
                      float m20_, float m21_, float m22_)
{
  // set matrix with scalars
  x.set(m00_, m01_, m02_);
  y.set(m10_, m11_, m12_);
  z.set(m20_, m21_, m22_);
}
//----

void simd_mat33f::set(const simd_float4 &row0_,
                      const simd_float4 &row1_,
                      const simd_float4 &row2_)
{
  // set matrix with SIMD row-vectors
  (simd_float4&)x=row0_;
  (simd_float4&)y=row1_;
  (simd_float4&)z=row2_;
}
//----

void simd_mat33f::set(const simd_vec3f &row0_,
                      const simd_vec3f &row1_,
                      const simd_vec3f &row2_)
{
  // set matrix with row-vectors
  x=row0_;
  y=row1_;
  z=row2_;
}
//----

void simd_mat33f::set(const mat22f &m_)
{
  // set matrix with 2d fp-matrix (upper-left matrix)
  x.set(m_.x, 0.0f);
  y.set(m_.y, 0.0f);
  z.set(simd::g_ident_z);
}
//----

void simd_mat33f::set(const simd_mat33f &m_)
{
  // set matrix with 3d SIMD matrix
  (simd_float4&)x=(simd_float4&)m_.x;
  (simd_float4&)y=(simd_float4&)m_.y;
  (simd_float4&)z=(simd_float4&)m_.z;
}
//----

void simd_mat33f::set(const mat33f &m_)
{
  // set matrix with 3d fp-matrix
  x.set(m_.x);
  y.set(m_.y);
  z.set(m_.z);
}
//----

void simd_mat33f::set(const simd_mat44f &m_)
{
  // set matrix with 4d SIMD matrix (upper-left matrix)
  (simd_float4&)x=(simd_float4&)m_.x;
  (simd_float4&)y=(simd_float4&)m_.y;
  (simd_float4&)z=(simd_float4&)m_.z;
}
//----

void simd_mat33f::set(const mat44f &m_)
{
  // set matrix from 4d fp-matrix (upper-left matrix)
  x.set((const float*)&m_.x);
  y.set((const float*)&m_.y);
  z.set((const float*)&m_.z);
}
//----

void simd_mat33f::set(const float *a_)
{
  // set matrix with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  (simd_float4&)x=_mm_loadu_ps(a_+0);
  (simd_float4&)y=_mm_loadu_ps(a_+3);
  (simd_float4&)z=_mm_loadu_ps(a_+6);
}
//----------------------------------------------------------------------------

PFC_INLINE bool is_zero(const simd_mat33f &m_)
{
  // test for zero-matrix
  return (_mm_movemask_ps(_mm_cmpneq_ps(_mm_or_ps((simd_float4&)m_.x,
                                        _mm_or_ps((simd_float4&)m_.y,
                                                  (simd_float4&)m_.z)), _mm_setzero_ps()))&0x7)==0;
}
//----

PFC_INLINE bool is_sat(const simd_mat33f &m_)
{
  // test for saturated matrix
  simd_float4 zero=_mm_setzero_ps();
  return (_mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_cmplt_ps((simd_float4&)m_.x, zero),
                                              _mm_or_ps(_mm_cmplt_ps((simd_float4&)m_.y, zero),
                                                        _mm_cmplt_ps((simd_float4&)m_.z, zero))),
                                    _mm_or_ps(_mm_cmpgt_ps((simd_float4&)m_.x, simd::g_one),
                                              _mm_or_ps(_mm_cmpgt_ps((simd_float4&)m_.y, simd::g_one),
                                                        _mm_cmpgt_ps((simd_float4&)m_.z, simd::g_one)))))&0x7)==0;
}
//----

PFC_INLINE bool is_ssat(const simd_mat33f &m_)
{
  // test for signed saturated matrix
  return (_mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_cmplt_ps((simd_float4&)m_.x, simd::g_neg_one),
                                              _mm_or_ps(_mm_cmplt_ps((simd_float4&)m_.y, simd::g_neg_one),
                                                        _mm_cmplt_ps((simd_float4&)m_.z, simd::g_neg_one))),
                                    _mm_or_ps(_mm_cmpgt_ps((simd_float4&)m_.x, simd::g_one),
                                              _mm_or_ps(_mm_cmpgt_ps((simd_float4&)m_.y, simd::g_one),
                                                        _mm_cmpgt_ps((simd_float4&)m_.z, simd::g_one)))))&0x7)==0;
}
//----

PFC_INLINE bool operator==(const simd_mat33f &m0_, const simd_mat33f &m1_)
{
  // test for equality of matrices
  return (_mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps((simd_float4&)m0_.x, (simd_float4&)m1_.x),
                                              _mm_cmpneq_ps((simd_float4&)m0_.y, (simd_float4&)m1_.y)),
                                              _mm_cmpneq_ps((simd_float4&)m0_.z, (simd_float4&)m1_.z)))&0x7)==0;
}
//----

PFC_INLINE bool operator==(const simd_mat33f &m_, float s_)
{
  // test for equality of matrix and scalar
  simd_float4 s=_mm_set1_ps(s_);
  return (_mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps((simd_float4&)m_.x, s),
                                              _mm_cmpneq_ps((simd_float4&)m_.y, s)),
                                              _mm_cmpneq_ps((simd_float4&)m_.z, s)))&0x7)==0;
}
//----

PFC_INLINE bool operator==(float s_, const simd_mat33f &m_)
{
  // test for equality of matrix and scalar
  simd_float4 s=_mm_set1_ps(s_);
  return (_mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps(s, (simd_float4&)m_.x),
                                              _mm_cmpneq_ps(s, (simd_float4&)m_.y)),
                                              _mm_cmpneq_ps(s, (simd_float4&)m_.z)))&0x7)==0;
}
//----

PFC_INLINE bool operator!=(const simd_mat33f &m0_, const simd_mat33f &m1_)
{
  // test for inequality of matrices
  return (_mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps((simd_float4&)m0_.x, (simd_float4&)m1_.x),
                                              _mm_cmpneq_ps((simd_float4&)m0_.y, (simd_float4&)m1_.y)),
                                              _mm_cmpneq_ps((simd_float4&)m0_.z, (simd_float4&)m1_.z)))&0x7)!=0;
}
//----

PFC_INLINE bool operator!=(const simd_mat33f &m_, float s_)
{
  // test for inequality of matrix and scalar
  simd_float4 s=_mm_set1_ps(s_);
  return (_mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps((simd_float4&)m_.x, s),
                                              _mm_cmpneq_ps((simd_float4&)m_.y, s)),
                                              _mm_cmpneq_ps((simd_float4&)m_.z, s)))&0x7)!=0;
}
//----

PFC_INLINE bool operator!=(float s_, const simd_mat33f &m_)
{
  // test for inequality of matrix and scalar
  simd_float4 s=_mm_set1_ps(s_);
  return (_mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps(s, (simd_float4&)m_.x),
                                              _mm_cmpneq_ps(s, (simd_float4&)m_.y)),
                                              _mm_cmpneq_ps(s, (simd_float4&)m_.z)))&0x7)!=0;
}
//----

PFC_INLINE void operator+=(simd_mat33f &mr_, const simd_mat33f &m_)
{
  // add matrix to matrix
  (simd_float4&)mr_.x=_mm_add_ps((simd_float4&)mr_.x, (simd_float4&)m_.x);
  (simd_float4&)mr_.y=_mm_add_ps((simd_float4&)mr_.y, (simd_float4&)m_.y);
  (simd_float4&)mr_.z=_mm_add_ps((simd_float4&)mr_.z, (simd_float4&)m_.z);
}
//----

PFC_INLINE void operator+=(simd_mat33f &mr_, float s_)
{
  // add scalar to matrix
  simd_float4 s=_mm_set1_ps(s_);
  (simd_float4&)mr_.x=_mm_add_ps((simd_float4&)mr_.x, s);
  (simd_float4&)mr_.y=_mm_add_ps((simd_float4&)mr_.y, s);
  (simd_float4&)mr_.z=_mm_add_ps((simd_float4&)mr_.z, s);
}
//----

PFC_INLINE void operator-=(simd_mat33f &mr_, const simd_mat33f &m_)
{
  // subtract matrix from matrix
  (simd_float4&)mr_.x=_mm_sub_ps((simd_float4&)mr_.x, (simd_float4&)m_.x);
  (simd_float4&)mr_.y=_mm_sub_ps((simd_float4&)mr_.y, (simd_float4&)m_.y);
  (simd_float4&)mr_.z=_mm_sub_ps((simd_float4&)mr_.z, (simd_float4&)m_.z);
}
//----

PFC_INLINE void operator-=(simd_mat33f &mr_, float s_)
{
  // subtract scalar from matrix
  simd_float4 s=_mm_set1_ps(s_);
  (simd_float4&)mr_.x=_mm_sub_ps((simd_float4&)mr_.x, s);
  (simd_float4&)mr_.y=_mm_sub_ps((simd_float4&)mr_.y, s);
  (simd_float4&)mr_.z=_mm_sub_ps((simd_float4&)mr_.z, s);
}
//----

PFC_INLINE void operator*=(simd_mat33f &mr_, const simd_mat33f &m_)
{
  // multiply matrix by matrix
  (simd_float4&)mr_.x=_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.x, (simd_float4&)mr_.x, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                            _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.x, (simd_float4&)mr_.x, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                            _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.x, (simd_float4&)mr_.x, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z));
  (simd_float4&)mr_.y=_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.y, (simd_float4&)mr_.y, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                            _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.y, (simd_float4&)mr_.y, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                            _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.y, (simd_float4&)mr_.y, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z));
  (simd_float4&)mr_.z=_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.z, (simd_float4&)mr_.z, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                            _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.z, (simd_float4&)mr_.z, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                            _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.z, (simd_float4&)mr_.z, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z));
}
//----
/*
PFC_INLINE void operator*=(simd_mat33f &mr_, simd_quatf &q_)
{
  // multiply matrix by quaternion
  mr_.x*=q_;
  mr_.y*=q_;
  mr_.z*=q_;
}
//----
*/
PFC_INLINE void operator*=(simd_mat33f &mr_, float s_)
{
  // multiply matrix by scalar
  simd_float4 s=_mm_set1_ps(s_);
  (simd_float4&)mr_.x=_mm_mul_ps((simd_float4&)mr_.x, s);
  (simd_float4&)mr_.y=_mm_mul_ps((simd_float4&)mr_.y, s);
  (simd_float4&)mr_.z=_mm_mul_ps((simd_float4&)mr_.z, s);
}
//----

PFC_INLINE void operator/=(simd_mat33f &mr_, float s_)
{
  // divide matrix by scalar
  simd_float4 rs=_mm_rcp_ss(_mm_load_ss(&s_));
  rs=_mm_shuffle_ps(rs, rs, 0);
  (simd_float4&)mr_.x=_mm_mul_ps((simd_float4&)mr_.x, rs);
  (simd_float4&)mr_.y=_mm_mul_ps((simd_float4&)mr_.y, rs);
  (simd_float4&)mr_.z=_mm_mul_ps((simd_float4&)mr_.z, rs);
}
//----

PFC_INLINE simd_mat33f operator+(const simd_mat33f &m0_, const simd_mat33f &m1_)
{
  // add matrix to matrix
  return simd_mat33f(_mm_add_ps((simd_float4&)m0_.x, (simd_float4&)m1_.x),
                     _mm_add_ps((simd_float4&)m0_.y, (simd_float4&)m1_.y),
                     _mm_add_ps((simd_float4&)m0_.z, (simd_float4&)m1_.z));
}
//----

PFC_INLINE simd_mat33f operator+(const simd_mat33f &m_, float s_)
{
  // add scalar to matrix
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat33f(_mm_add_ps((simd_float4&)m_.x, s),
                     _mm_add_ps((simd_float4&)m_.y, s),
                     _mm_add_ps((simd_float4&)m_.z, s));
}
//----

PFC_INLINE simd_mat33f operator+(float s_, const simd_mat33f &m_)
{
  // add matrix to scalar
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat33f(_mm_add_ps(s, (simd_float4&)m_.x),
                     _mm_add_ps(s, (simd_float4&)m_.y),
                     _mm_add_ps(s, (simd_float4&)m_.z));
}
//----

PFC_INLINE simd_mat33f operator-(const simd_mat33f &m0_, const simd_mat33f &m1_)
{
  // subtract matrix from matrix
  return simd_mat33f(_mm_sub_ps((simd_float4&)m0_.x, (simd_float4&)m1_.x),
                     _mm_sub_ps((simd_float4&)m0_.y, (simd_float4&)m1_.y),
                     _mm_sub_ps((simd_float4&)m0_.z, (simd_float4&)m1_.z));
}
//----

PFC_INLINE simd_mat33f operator-(const simd_mat33f &m_, float s_)
{
  // subtract scalar from matrix
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat33f(_mm_sub_ps((simd_float4&)m_.x, s),
                     _mm_sub_ps((simd_float4&)m_.y, s),
                     _mm_sub_ps((simd_float4&)m_.z, s));
}
//----

PFC_INLINE simd_mat33f operator-(float s_, const simd_mat33f &m_)
{
  // subtract matrix from scalar
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat33f(_mm_sub_ps(s, (simd_float4&)m_.x),
                     _mm_sub_ps(s, (simd_float4&)m_.y),
                     _mm_sub_ps(s, (simd_float4&)m_.z));
}
//----

PFC_INLINE simd_mat33f operator-(const simd_mat33f &m_)
{
  // negate matrix
  simd_float4 zero=_mm_setzero_ps();
  return simd_mat33f(_mm_sub_ps(zero, (simd_float4&)m_.x),
                     _mm_sub_ps(zero, (simd_float4&)m_.y),
                     _mm_sub_ps(zero, (simd_float4&)m_.z));
}
//----

PFC_INLINE simd_mat33f operator*(const simd_mat33f &m0_, const simd_mat33f &m1_)
{
  // multiply matrix by matrix
  return simd_mat33f(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.x, (simd_float4&)m0_.x, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m1_.x),
                                           _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.x, (simd_float4&)m0_.x, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m1_.y)),
                                           _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.x, (simd_float4&)m0_.x, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m1_.z)),
                     _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.y, (simd_float4&)m0_.y, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m1_.x),
                                           _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.y, (simd_float4&)m0_.y, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m1_.y)),
                                           _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.y, (simd_float4&)m0_.y, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m1_.z)),
                     _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.z, (simd_float4&)m0_.z, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m1_.x),
                                           _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.z, (simd_float4&)m0_.z, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m1_.y)),
                                           _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.z, (simd_float4&)m0_.z, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m1_.z)));
}
//----
/*
PFC_INLINE simd_mat33f operator*(const simd_mat33f &m_, const simd_quatf &q_)
{
  // multiply matrix by quaternion
  simd_mat33f m=m_;
  m.x*=q_;
  m.y*=q_;
  m.z*=q_;
  return m;
}
//----
*/
PFC_INLINE simd_mat33f operator*(const simd_mat33f &m_, float s_)
{
  // multiply matrix by scalar
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat33f(_mm_mul_ps((simd_float4&)m_.x, s),
                     _mm_mul_ps((simd_float4&)m_.y, s),
                     _mm_mul_ps((simd_float4&)m_.z, s));
}
//----

PFC_INLINE simd_mat33f operator*(float s_, const simd_mat33f &m_)
{
  // multiply matrix by scalar
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat33f(_mm_mul_ps((simd_float4&)m_.x, s),
                     _mm_mul_ps((simd_float4&)m_.y, s),
                     _mm_mul_ps((simd_float4&)m_.z, s));
}
//----

PFC_INLINE simd_mat33f operator/(const simd_mat33f &m_, float s_)
{
  // divide matrix by scalar
  simd_float4 rs=_mm_rcp_ss(_mm_load_ss(&s_));
  rs=_mm_shuffle_ps(rs, rs, 0);
  return simd_mat33f(_mm_mul_ps((simd_float4&)m_.x, rs),
                     _mm_mul_ps((simd_float4&)m_.y, rs),
                     _mm_mul_ps((simd_float4&)m_.z, rs));
}
//----

PFC_INLINE simd_mat33f mul(const simd_mat33f &m0_, const simd_mat33f &m1_)
{
  // component-wise multiply: m0_*m1
  return simd_mat33f(_mm_mul_ps((simd_float4&)m0_.x, (simd_float4&)m1_.x),
                     _mm_mul_ps((simd_float4&)m0_.y, (simd_float4&)m1_.y),
                     _mm_mul_ps((simd_float4&)m0_.z, (simd_float4&)m1_.z));
}
//----

PFC_INLINE simd_mat33f madd(const simd_mat33f &mm0_, const simd_mat33f &mm1_, const simd_mat33f &ma_)
{
  // component-wise multiply-add: mm0_*mm1+ma_
  return simd_mat33f(_mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.x, (simd_float4&)mm1_.x), (simd_float4&)ma_.x),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.y, (simd_float4&)mm1_.y), (simd_float4&)ma_.y),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.z, (simd_float4&)mm1_.z), (simd_float4&)ma_.z));
}
//----

PFC_INLINE simd_mat33f madd(const simd_mat33f &mm_, float sm_, float sa_)
{
  // component-wise multiply-add: mm_*sm_+sa_
  simd_float4 vm=_mm_set1_ps(sm_);
  simd_float4 va=_mm_set1_ps(sa_);
  return simd_mat33f(_mm_add_ps(_mm_mul_ps((simd_float4&)mm_.x, vm), va),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm_.y, vm), va),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm_.z, vm), va));
}
//----

PFC_INLINE simd_mat33f madd(const simd_mat33f &mm0_, const simd_mat33f &mm1_, float sa_)
{
  // component-wise multiply-add: mm0_*mm1_+sa_
  simd_float4 va=_mm_set1_ps(sa_);
  return simd_mat33f(_mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.x, (simd_float4&)mm1_.x), va),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.y, (simd_float4&)mm1_.y), va),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.z, (simd_float4&)mm1_.z), va));
}
//----

PFC_INLINE simd_mat33f madd(const simd_mat33f &mm_, float sm_, const simd_mat33f &ma_)
{
  // component-wise multiply-add: mm_*sm_+ma_
  simd_float4 vm=_mm_set1_ps(sm_);
  return simd_mat33f(_mm_add_ps(_mm_mul_ps((simd_float4&)mm_.x, vm), (simd_float4&)ma_.x),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm_.y, vm), (simd_float4&)ma_.y),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm_.z, vm), (simd_float4&)ma_.z));
}
//----

PFC_INLINE float det(const simd_mat33f &m_)
{
  // determinant of the matrix
  simd_float4 dv=_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m_.x, (simd_float4&)m_.x, _MM_SHUFFLE(0, 1, 0, 2)),
                            _mm_sub_ps(_mm_mul_ps((simd_float4&)m_.y, _mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.z, _MM_SHUFFLE(0, 0, 2, 1))),
                                       _mm_mul_ps((simd_float4&)m_.z, _mm_shuffle_ps((simd_float4&)m_.y, (simd_float4&)m_.y, _MM_SHUFFLE(0, 0, 2, 1)))));
  PFC_ALIGN(16) float32_t v[4];
  _mm_store_ps(v, dv);
  return v[0]+v[1]+v[2];
}
//----

PFC_INLINE simd_mat33f inv(const simd_mat33f &m_, float *det_=0)
{
  // calculate determinant
  simd_float4 y_yzx=_mm_shuffle_ps((simd_float4&)m_.y, (simd_float4&)m_.y, _MM_SHUFFLE(0, 0, 2, 1));
  simd_float4 y_zxy=_mm_shuffle_ps((simd_float4&)m_.y, (simd_float4&)m_.y, _MM_SHUFFLE(0, 1, 0, 2));
  simd_float4 z_yzx=_mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.z, _MM_SHUFFLE(0, 0, 2, 1));
  simd_float4 z_zxy=_mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.z, _MM_SHUFFLE(0, 1, 0, 2));
  simd_float4 sdx=_mm_sub_ps(_mm_mul_ps(y_yzx, z_zxy), _mm_mul_ps(y_zxy, z_yzx));
  PFC_ALIGN(16) float32_t v[4];
  _mm_store_ps(v, _mm_mul_ps(sdx, (simd_float4&)m_.x));
  float d=v[0]+v[1]+v[2];
  if(det_)
    *det_=d;
  if(!d)
    return simd_mat33f::s_zero;

  // calculate inverse of the matrix
  simd_mat33f res;
  simd_float4 rd=_mm_rcp_ps(_mm_set1_ps(d));
  (simd_float4&)res.x=_mm_mul_ps(rd, sdx);
  simd_float4 x_yzx=_mm_shuffle_ps((simd_float4&)m_.x, (simd_float4&)m_.x, _MM_SHUFFLE(0, 0, 2, 1));
  simd_float4 x_zxy=_mm_shuffle_ps((simd_float4&)m_.x, (simd_float4&)m_.x, _MM_SHUFFLE(0, 1, 0, 2));
  (simd_float4&)res.y=_mm_mul_ps(rd, _mm_sub_ps(_mm_mul_ps(z_yzx, x_zxy), _mm_mul_ps(z_zxy, x_yzx)));
  (simd_float4&)res.z=_mm_mul_ps(rd, _mm_sub_ps(_mm_mul_ps(x_yzx, y_zxy), _mm_mul_ps(x_zxy, y_yzx)));

  // transpose and return the matrix
  float t=res.x.y;
  res.x.y=res.y.x;
  res.y.x=t;
  t=res.x.z;
  res.x.z=res.z.x;
  res.z.x=t;
  t=res.y.z;
  res.y.z=res.z.y;
  res.z.y=t;
  return res;
}
//----
/*
PFC_INLINE float tr(const simd_mat33f &m_)
{
  // trace of the matrix
  return m_.x.x+m_.y.y+m_.z.z;
}
//----
*/
PFC_INLINE void identity(simd_mat33f &m_)
{
  // set identity
  (simd_float4&)m_.x=simd::g_ident_x;
  (simd_float4&)m_.y=simd::g_ident_y;
  (simd_float4&)m_.z=simd::g_ident_z;
}
//----
/*
PFC_INLINE void transpose(simd_mat33f &m_)
{
  // transpose the matrix
  float t=m_.x.y;
  m_.x.y=m_.y.x;
  m_.y.x=t;
  t=m_.x.z;
  m_.x.z=m_.z.x;
  m_.z.x=t;
  t=m_.y.z;
  m_.y.z=m_.z.y;
  m_.z.y=t;
}
//----

PFC_INLINE void transpose(simd_mat33f &res_, const simd_mat33f &m_)
{
  // transpose the matrix
  res_.x.x=m_.x.x; res_.x.y=m_.y.x; res_.x.z=m_.z.x;
  res_.y.x=m_.x.y; res_.y.y=m_.y.y; res_.y.z=m_.z.y;
  res_.z.x=m_.x.z; res_.z.y=m_.y.z; res_.z.z=m_.z.z;
}
//----
*/
PFC_INLINE void neg(simd_mat33f &m_)
{
  // negate the matrix
  simd_float4 zero=_mm_setzero_ps();
  (simd_float4&)m_.x=_mm_sub_ps(zero, (simd_float4&)m_.x);
  (simd_float4&)m_.y=_mm_sub_ps(zero, (simd_float4&)m_.y);
  (simd_float4&)m_.z=_mm_sub_ps(zero, (simd_float4&)m_.z);
}
//----

PFC_INLINE simd_mat33f lerp(const simd_mat33f &m0_, const simd_mat33f &m1_, float t_)
{
  // linear matrix interpolation. f(t=0)=v0, f(t=1)=v1
  simd_float4 t=_mm_set1_ps(t_);
  return simd_mat33f(_mm_add_ps((simd_float4&)m0_.x, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.x, (simd_float4&)m0_.x), t)),
                     _mm_add_ps((simd_float4&)m0_.y, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.y, (simd_float4&)m0_.y), t)),
                     _mm_add_ps((simd_float4&)m0_.z, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.z, (simd_float4&)m0_.z), t)));
}
//----

PFC_INLINE void lerp(simd_mat33f &res_, const simd_mat33f &m0_, const simd_mat33f &m1_, float t_)
{
  // linear matrix interpolation. f(t=0)=v0, f(t=1)=v1
  simd_float4 t=_mm_set1_ps(t_);
  (simd_float4&)res_.x=_mm_add_ps((simd_float4&)m0_.x, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.x, (simd_float4&)m0_.x), t));
  (simd_float4&)res_.y=_mm_add_ps((simd_float4&)m0_.y, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.y, (simd_float4&)m0_.y), t));
  (simd_float4&)res_.z=_mm_add_ps((simd_float4&)m0_.z, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.z, (simd_float4&)m0_.z), t));
}
//----
/*
PFC_INLINE void orthonormalize(simd_mat33f &mr_)
{
  // ortho-normalize the matrix
  mr_.x=unit(mr_.x);
  mr_.y=unit(cross(mr_.z, mr_.x));
  mr_.z=cross(mr_.x, mr_.y);
}*/
//----------------------------------------------------------------------------


//============================================================================
// simd_mat44f
//============================================================================
simd_mat44f::mat44()
{
}
//----

simd_mat44f::mat44(float s_)
{
  // init matrix with scalar
  simd_float4 s=_mm_set1_ps(s_);
  (simd_float4&)x=s;
  (simd_float4&)y=s;
  (simd_float4&)z=s;
  (simd_float4&)w=s;
}
//----

simd_mat44f::mat44(const simd_vec4f &row0_,
                   const simd_vec4f &row1_,
                   const simd_vec4f &row2_,
                   const simd_vec4f &row3_)
  :x(row0_)
  ,y(row1_)
  ,z(row2_)
  ,w(row3_)
{
  // init matrix with row-vectors
}
//----

simd_mat44f::mat44(float d0_, float d1_, float d2_, float d3_)
  :x(d0_,  0.0f, 0.0f, 0.0f)
  ,y(0.0f, d1_,  0.0f, 0.0f)
  ,z(0.0f, 0.0f, d2_,  0.0f)
  ,w(0.0f, 0.0f, 0.0f, d3_ )
{
  // init matrix with diagonal scalars
}
//----

simd_mat44f::mat44(float m00_, float m01_, float m02_, float m03_,
                   float m10_, float m11_, float m12_, float m13_,
                   float m20_, float m21_, float m22_, float m23_,
                   float m30_, float m31_, float m32_, float m33_)
  :x(m00_, m01_, m02_, m03_)
  ,y(m10_, m11_, m12_, m13_)
  ,z(m20_, m21_, m22_, m23_)
  ,w(m30_, m31_, m32_, m33_)
{
  // init matrix with scalars
}
//----

simd_mat44f::mat44(const simd_float4 &row0_,
                   const simd_float4 &row1_,
                   const simd_float4 &row2_,
                   const simd_float4 &row3_)
  :x(row0_)
  ,y(row1_)
  ,z(row2_)
  ,w(row3_)
{
  // init matrix with SIMD row-vectors
}
//----

simd_mat44f::mat44(const simd_mat33f &m_)
  :x(m_.x, 0.0f)
  ,y(m_.y, 0.0f)
  ,z(m_.z, 0.0f)
  ,w(simd::g_ident_w)
{
  // init matrix with 3d SIMD matrix (upper-left matrix)
}
//----

simd_mat44f::mat44(const mat33f &m_)
  :x(m_.x, 0.0f)
  ,y(m_.y, 0.0f)
  ,z(m_.z, 0.0f)
  ,w(simd::g_ident_w)
{
  // init matrix with 3d fp-matrix (upper-left matrix)
}
//----

simd_mat44f::mat44(const mat44f &m_)
  :x(m_.x)
  ,y(m_.y)
  ,z(m_.z)
  ,w(m_.w)
{
  // init matrix with 4d fp-matrix
}
//----

simd_mat44f::mat44(const float *a_)
{
  // init matrix with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  (simd_float4&)x=_mm_loadu_ps(a_+0);
  (simd_float4&)y=_mm_loadu_ps(a_+4);
  (simd_float4&)z=_mm_loadu_ps(a_+8);
  (simd_float4&)w=_mm_loadu_ps(a_+12);
}
//----------------------------------------------------------------------------

const simd_vec4f &simd_mat44f::operator[](unsigned row_) const
{
  // return reference to nth vector (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(row_<4);
  return reinterpret_cast<const simd_vec4f*>(this)[row_];
}
//----

simd_vec4f &simd_mat44f::operator[](unsigned row_)
{
  // return reference to nth vector (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(row_<4);
  return reinterpret_cast<simd_vec4f*>(this)[row_];
}
//----

void simd_mat44f::set(float s_)
{
  // set matrix with scalar
  simd_float4 s=_mm_set1_ps(s_);
  (simd_float4&)x=s;
  (simd_float4&)y=s;
  (simd_float4&)z=s;
  (simd_float4&)w=s;
}
//----

void simd_mat44f::set(float d0_, float d1_, float d2_, float d3_)
{
  // set matrix with diagonal scalars
  x.set(d0_,  0.0f, 0.0f, 0.0f);
  y.set(0.0f, d1_,  0.0f, 0.0f);
  z.set(0.0f, 0.0f, d2_,  0.0f);
  w.set(0.0f, 0.0f, 0.0f, d3_ );
}
//----

void simd_mat44f::set(float m00_, float m01_, float m02_, float m03_,
                      float m10_, float m11_, float m12_, float m13_,
                      float m20_, float m21_, float m22_, float m23_,
                      float m30_, float m31_, float m32_, float m33_)
{
  // set matrix with scalars
  x.set(m00_, m01_, m02_, m03_);
  y.set(m10_, m11_, m12_, m13_);
  z.set(m20_, m21_, m22_, m23_);
  w.set(m30_, m31_, m32_, m33_);
}
//----

void simd_mat44f::set(const simd_float4 &row0_,
                      const simd_float4 &row1_,
                      const simd_float4 &row2_,
                      const simd_float4 &row3_)
{
  // set matrix with SIMD row-vectors
  (simd_float4&)x=row0_;
  (simd_float4&)y=row1_;
  (simd_float4&)z=row2_;
  (simd_float4&)w=row3_;
}
//----

void simd_mat44f::set(const simd_vec4f &row0_,
                      const simd_vec4f &row1_,
                      const simd_vec4f &row2_,
                      const simd_vec4f &row3_)
{
  // set matrix with row-vectors
  x=row0_;
  y=row1_;
  z=row2_;
  w=row3_;
}
//----

void simd_mat44f::set(const simd_mat33f &m_)
{
  // set matrix with 3d SIMD matrix (upper-left matrix)
  x.set(m_.x, 0.0f);
  y.set(m_.y, 0.0f);
  z.set(m_.z, 0.0f);
  w.set(simd::g_ident_w);
}
//----

void simd_mat44f::set(const mat33f &m_)
{
  // set matrix with 3d fp-matrix (upper-left matrix)
  x.set(m_.x, 0.0f);
  y.set(m_.y, 0.0f);
  z.set(m_.z, 0.0f);
  w.set(simd::g_ident_w);
}
//----

void simd_mat44f::set(const simd_mat44f &m_)
{
  // set matrix with 4d SIMD matrix
  (simd_float4&)x=(simd_float4&)m_.x;
  (simd_float4&)y=(simd_float4&)m_.y;
  (simd_float4&)z=(simd_float4&)m_.z;
  (simd_float4&)w=(simd_float4&)m_.w;
}
//----

void simd_mat44f::set(const mat44f &m_)
{
  // set matrix with 4d fp-matrix
  x.set(m_.x);
  y.set(m_.y);
  z.set(m_.z);
  w.set(m_.w);
}
//----

void simd_mat44f::set(const float *a_)
{
  // set matrix with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  (simd_float4&)x=_mm_loadu_ps(a_+0);
  (simd_float4&)y=_mm_loadu_ps(a_+4);
  (simd_float4&)z=_mm_loadu_ps(a_+8);
  (simd_float4&)w=_mm_loadu_ps(a_+12);
}
//----------------------------------------------------------------------------

PFC_INLINE bool is_zero(const simd_mat44f &m_)
{
  // test for zero-matrix
  return _mm_movemask_ps(_mm_cmpneq_ps(_mm_or_ps((simd_float4&)m_.x,
                                       _mm_or_ps((simd_float4&)m_.y,
                                       _mm_or_ps((simd_float4&)m_.z,
                                                 (simd_float4&)m_.w))), _mm_setzero_ps()))==0;
}
//----

PFC_INLINE bool is_sat(const simd_mat44f &m_)
{
  // test for saturated matrix
  simd_float4 zero=_mm_setzero_ps();
  return _mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_cmplt_ps((simd_float4&)m_.x, zero),
                                             _mm_or_ps(_mm_cmplt_ps((simd_float4&)m_.y, zero),
                                                       _mm_or_ps(_mm_cmplt_ps((simd_float4&)m_.z, zero),
                                                                 _mm_cmplt_ps((simd_float4&)m_.w, zero)))),
                                   _mm_or_ps(_mm_cmpgt_ps((simd_float4&)m_.x, simd::g_one),
                                             _mm_or_ps(_mm_cmpgt_ps((simd_float4&)m_.y, simd::g_one),
                                                       _mm_or_ps(_mm_cmpgt_ps((simd_float4&)m_.z, simd::g_one),
                                                                 _mm_cmpgt_ps((simd_float4&)m_.w, simd::g_one))))))==0;
}
//----

PFC_INLINE bool is_ssat(const simd_mat44f &m_)
{
  // test for signed saturated matrix
  return _mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_cmplt_ps((simd_float4&)m_.x, simd::g_neg_one),
                                             _mm_or_ps(_mm_cmplt_ps((simd_float4&)m_.y, simd::g_neg_one),
                                                       _mm_or_ps(_mm_cmplt_ps((simd_float4&)m_.z, simd::g_neg_one),
                                                                 _mm_cmplt_ps((simd_float4&)m_.w, simd::g_neg_one)))),
                                   _mm_or_ps(_mm_cmpgt_ps((simd_float4&)m_.x, simd::g_one),
                                             _mm_or_ps(_mm_cmpgt_ps((simd_float4&)m_.y, simd::g_one),
                                                       _mm_or_ps(_mm_cmpgt_ps((simd_float4&)m_.z, simd::g_one),
                                                                 _mm_cmpgt_ps((simd_float4&)m_.w, simd::g_one))))))==0;
}
//----

PFC_INLINE bool operator==(const simd_mat44f &m0_, const simd_mat44f &m1_)
{
  // test for equality of matrices
  return _mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps((simd_float4&)m0_.x, (simd_float4&)m1_.x),
                                                       _mm_cmpneq_ps((simd_float4&)m0_.y, (simd_float4&)m1_.y)),
                                                       _mm_cmpneq_ps((simd_float4&)m0_.z, (simd_float4&)m1_.z)),
                                                       _mm_cmpneq_ps((simd_float4&)m0_.w, (simd_float4&)m1_.w)))==0;
}
//----

PFC_INLINE bool operator==(const simd_mat44f &m_, float s_)
{
  // test for equality of matrix and scalar
  simd_float4 s=_mm_set1_ps(s_);
  return _mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps((simd_float4&)m_.x, s),
                                                       _mm_cmpneq_ps((simd_float4&)m_.y, s)),
                                                       _mm_cmpneq_ps((simd_float4&)m_.z, s)),
                                                       _mm_cmpneq_ps((simd_float4&)m_.w, s)))==0;
}
//----

PFC_INLINE bool operator==(float s_, const simd_mat44f &m_)
{
  // test for equality of matrix and scalar
  simd_float4 s=_mm_set1_ps(s_);
  return _mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps(s, (simd_float4&)m_.x),
                                                       _mm_cmpneq_ps(s, (simd_float4&)m_.y)),
                                                       _mm_cmpneq_ps(s, (simd_float4&)m_.z)),
                                                       _mm_cmpneq_ps(s, (simd_float4&)m_.w)))==0;
}
//----

PFC_INLINE bool operator!=(const simd_mat44f &m0_, const simd_mat44f &m1_)
{
  // test for inequality of matrices
  return _mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps((simd_float4&)m0_.x, (simd_float4&)m1_.x),
                                                       _mm_cmpneq_ps((simd_float4&)m0_.y, (simd_float4&)m1_.y)),
                                                       _mm_cmpneq_ps((simd_float4&)m0_.z, (simd_float4&)m1_.z)),
                                                       _mm_cmpneq_ps((simd_float4&)m0_.w, (simd_float4&)m1_.w)))!=0;
}
//----

PFC_INLINE bool operator!=(const simd_mat44f &m_, float s_)
{
  // test for inequality of matrix and scalar
  simd_float4 s=_mm_set1_ps(s_);
  return _mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps((simd_float4&)m_.x, s),
                                                       _mm_cmpneq_ps((simd_float4&)m_.y, s)),
                                                       _mm_cmpneq_ps((simd_float4&)m_.z, s)),
                                                       _mm_cmpneq_ps((simd_float4&)m_.w, s)))!=0;
}
//----

PFC_INLINE bool operator!=(float s_, const simd_mat44f &m_)
{
  // test for inequality of matrix and scalar
  simd_float4 s=_mm_set1_ps(s_);
  return _mm_movemask_ps(_mm_or_ps(_mm_or_ps(_mm_or_ps(_mm_cmpneq_ps(s, (simd_float4&)m_.x),
                                                       _mm_cmpneq_ps(s, (simd_float4&)m_.y)),
                                                       _mm_cmpneq_ps(s, (simd_float4&)m_.z)),
                                                       _mm_cmpneq_ps(s, (simd_float4&)m_.w)))!=0;
}
//----

PFC_INLINE void operator+=(simd_mat44f &mr_, const simd_mat44f &m_)
{
  // add matrix to matrix
  (simd_float4&)mr_.x=_mm_add_ps((simd_float4&)mr_.x, (simd_float4&)m_.x);
  (simd_float4&)mr_.y=_mm_add_ps((simd_float4&)mr_.y, (simd_float4&)m_.y);
  (simd_float4&)mr_.z=_mm_add_ps((simd_float4&)mr_.z, (simd_float4&)m_.z);
  (simd_float4&)mr_.w=_mm_add_ps((simd_float4&)mr_.w, (simd_float4&)m_.w);
}
//----

PFC_INLINE void operator+=(simd_mat44f &mr_, float s_)
{
  // add scalar to matrix
  simd_float4 s=_mm_set1_ps(s_);
  (simd_float4&)mr_.x=_mm_add_ps((simd_float4&)mr_.x, s);
  (simd_float4&)mr_.y=_mm_add_ps((simd_float4&)mr_.y, s);
  (simd_float4&)mr_.z=_mm_add_ps((simd_float4&)mr_.z, s);
  (simd_float4&)mr_.w=_mm_add_ps((simd_float4&)mr_.w, s);
}
//----

PFC_INLINE void operator-=(simd_mat44f &mr_, const simd_mat44f &m_)
{
  // subtract matrix from matrix
  (simd_float4&)mr_.x=_mm_sub_ps((simd_float4&)mr_.x, (simd_float4&)m_.x);
  (simd_float4&)mr_.y=_mm_sub_ps((simd_float4&)mr_.y, (simd_float4&)m_.y);
  (simd_float4&)mr_.z=_mm_sub_ps((simd_float4&)mr_.z, (simd_float4&)m_.z);
  (simd_float4&)mr_.w=_mm_sub_ps((simd_float4&)mr_.w, (simd_float4&)m_.w);
}
//----

PFC_INLINE void operator-=(simd_mat44f &mr_, float s_)
{
  // subtract scalar from matrix
  simd_float4 s=_mm_set1_ps(s_);
  (simd_float4&)mr_.x=_mm_sub_ps((simd_float4&)mr_.x, s);
  (simd_float4&)mr_.y=_mm_sub_ps((simd_float4&)mr_.y, s);
  (simd_float4&)mr_.z=_mm_sub_ps((simd_float4&)mr_.z, s);
  (simd_float4&)mr_.w=_mm_sub_ps((simd_float4&)mr_.w, s);
}
//----

PFC_INLINE void operator*=(simd_mat44f &mr_, const simd_mat44f &m_)
{
  // multiply matrix by matrix
  (simd_float4&)mr_.x=_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.x, (simd_float4&)mr_.x, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.x, (simd_float4&)mr_.x, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.x, (simd_float4&)mr_.x, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z)),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.x, (simd_float4&)mr_.x, _MM_SHUFFLE(3, 3, 3, 3)), (simd_float4&)m_.w));
  (simd_float4&)mr_.y=_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.y, (simd_float4&)mr_.y, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.y, (simd_float4&)mr_.y, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.y, (simd_float4&)mr_.y, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z)),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.y, (simd_float4&)mr_.y, _MM_SHUFFLE(3, 3, 3, 3)), (simd_float4&)m_.w));
  (simd_float4&)mr_.z=_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.z, (simd_float4&)mr_.z, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.z, (simd_float4&)mr_.z, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.z, (simd_float4&)mr_.z, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z)),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.z, (simd_float4&)mr_.z, _MM_SHUFFLE(3, 3, 3, 3)), (simd_float4&)m_.w));
  (simd_float4&)mr_.w=_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.w, (simd_float4&)mr_.w, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m_.x),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.w, (simd_float4&)mr_.w, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m_.y)),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.w, (simd_float4&)mr_.w, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m_.z)),
                                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)mr_.w, (simd_float4&)mr_.w, _MM_SHUFFLE(3, 3, 3, 3)), (simd_float4&)m_.w));
}
//----

PFC_INLINE void operator*=(simd_mat44f &mr_, float s_)
{
  // multiply matrix by scalar
  simd_float4 s=_mm_set1_ps(s_);
  (simd_float4&)mr_.x=_mm_mul_ps((simd_float4&)mr_.x, s);
  (simd_float4&)mr_.y=_mm_mul_ps((simd_float4&)mr_.y, s);
  (simd_float4&)mr_.z=_mm_mul_ps((simd_float4&)mr_.z, s);
  (simd_float4&)mr_.w=_mm_mul_ps((simd_float4&)mr_.w, s);
}
//----

PFC_INLINE void operator/=(simd_mat44f &mr_, float s_)
{
  // divide matrix by scalar
  simd_float4 rs=_mm_rcp_ss(_mm_load_ss(&s_));
  rs=_mm_shuffle_ps(rs, rs, 0);
  (simd_float4&)mr_.x=_mm_mul_ps((simd_float4&)mr_.x, rs);
  (simd_float4&)mr_.y=_mm_mul_ps((simd_float4&)mr_.y, rs);
  (simd_float4&)mr_.z=_mm_mul_ps((simd_float4&)mr_.z, rs);
  (simd_float4&)mr_.w=_mm_mul_ps((simd_float4&)mr_.w, rs);
}
//----

PFC_INLINE simd_mat44f operator+(const simd_mat44f &m0_, const simd_mat44f &m1_)
{
  // add matrix to matrix
  return simd_mat44f(_mm_add_ps((simd_float4&)m0_.x, (simd_float4&)m1_.x),
                     _mm_add_ps((simd_float4&)m0_.y, (simd_float4&)m1_.y),
                     _mm_add_ps((simd_float4&)m0_.z, (simd_float4&)m1_.z),
                     _mm_add_ps((simd_float4&)m0_.w, (simd_float4&)m1_.w));
}
//----

PFC_INLINE simd_mat44f operator+(const simd_mat44f &m_, float s_)
{
  // add scalar to matrix
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat44f(_mm_add_ps((simd_float4&)m_.x, s),
                     _mm_add_ps((simd_float4&)m_.y, s),
                     _mm_add_ps((simd_float4&)m_.z, s),
                     _mm_add_ps((simd_float4&)m_.w, s));
}
//----

PFC_INLINE simd_mat44f operator+(float s_, const simd_mat44f &m_)
{
  // add matrix to scalar
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat44f(_mm_add_ps(s, (simd_float4&)m_.x),
                     _mm_add_ps(s, (simd_float4&)m_.y),
                     _mm_add_ps(s, (simd_float4&)m_.z),
                     _mm_add_ps(s, (simd_float4&)m_.w));
}
//----

PFC_INLINE simd_mat44f operator-(const simd_mat44f &m0_, const simd_mat44f &m1_)
{
  // subtract matrix from matrix
  return simd_mat44f(_mm_sub_ps((simd_float4&)m0_.x, (simd_float4&)m1_.x),
                     _mm_sub_ps((simd_float4&)m0_.y, (simd_float4&)m1_.y),
                     _mm_sub_ps((simd_float4&)m0_.z, (simd_float4&)m1_.z),
                     _mm_sub_ps((simd_float4&)m0_.w, (simd_float4&)m1_.w));
}
//----

PFC_INLINE simd_mat44f operator-(const simd_mat44f &m_, float s_)
{
  // subtract scalar from matrix
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat44f(_mm_sub_ps((simd_float4&)m_.x, s),
                     _mm_sub_ps((simd_float4&)m_.y, s),
                     _mm_sub_ps((simd_float4&)m_.z, s),
                     _mm_sub_ps((simd_float4&)m_.w, s));
}
//----

PFC_INLINE simd_mat44f operator-(float s_, const simd_mat44f &m_)
{
  // subtract matrix from scalar
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat44f(_mm_sub_ps(s, (simd_float4&)m_.x),
                     _mm_sub_ps(s, (simd_float4&)m_.y),
                     _mm_sub_ps(s, (simd_float4&)m_.z),
                     _mm_sub_ps(s, (simd_float4&)m_.w));
}
//----

PFC_INLINE simd_mat44f operator-(const simd_mat44f &m_)
{
  // negate matrix
  simd_float4 zero=_mm_setzero_ps();
  return simd_mat44f(_mm_sub_ps(zero, (simd_float4&)m_.x),
                     _mm_sub_ps(zero, (simd_float4&)m_.y),
                     _mm_sub_ps(zero, (simd_float4&)m_.z),
                     _mm_sub_ps(zero, (simd_float4&)m_.w));
}
//----

PFC_INLINE simd_mat44f operator*(const simd_mat44f &m0_, const simd_mat44f &m1_)
{
  // multiply matrix by matrix
  return simd_mat44f(_mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.x, (simd_float4&)m0_.x, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m1_.x),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.x, (simd_float4&)m0_.x, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m1_.y)),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.x, (simd_float4&)m0_.x, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m1_.z)),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.x, (simd_float4&)m0_.x, _MM_SHUFFLE(3, 3, 3, 3)), (simd_float4&)m1_.w)),
                     _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.y, (simd_float4&)m0_.y, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m1_.x),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.y, (simd_float4&)m0_.y, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m1_.y)),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.y, (simd_float4&)m0_.y, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m1_.z)),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.y, (simd_float4&)m0_.y, _MM_SHUFFLE(3, 3, 3, 3)), (simd_float4&)m1_.w)),
                     _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.z, (simd_float4&)m0_.z, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m1_.x),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.z, (simd_float4&)m0_.z, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m1_.y)),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.z, (simd_float4&)m0_.z, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m1_.z)),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.z, (simd_float4&)m0_.z, _MM_SHUFFLE(3, 3, 3, 3)), (simd_float4&)m1_.w)),
                     _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.w, (simd_float4&)m0_.w, _MM_SHUFFLE(0, 0, 0, 0)), (simd_float4&)m1_.x),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.w, (simd_float4&)m0_.w, _MM_SHUFFLE(1, 1, 1, 1)), (simd_float4&)m1_.y)),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.w, (simd_float4&)m0_.w, _MM_SHUFFLE(2, 2, 2, 2)), (simd_float4&)m1_.z)),
                                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m0_.w, (simd_float4&)m0_.w, _MM_SHUFFLE(3, 3, 3, 3)), (simd_float4&)m1_.w)));
}
//----

PFC_INLINE simd_mat44f operator*(const simd_mat44f &m_, float s_)
{
  // multiply matrix by scalar
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat44f(_mm_mul_ps((simd_float4&)m_.x, s),
                     _mm_mul_ps((simd_float4&)m_.y, s),
                     _mm_mul_ps((simd_float4&)m_.z, s),
                     _mm_mul_ps((simd_float4&)m_.w, s));
}
//----

PFC_INLINE simd_mat44f operator*(float s_, const simd_mat44f &m_)
{
  // multiply matrix by scalar
  simd_float4 s=_mm_set1_ps(s_);
  return simd_mat44f(_mm_mul_ps((simd_float4&)m_.x, s),
                     _mm_mul_ps((simd_float4&)m_.y, s),
                     _mm_mul_ps((simd_float4&)m_.z, s),
                     _mm_mul_ps((simd_float4&)m_.w, s));
}
//----

PFC_INLINE simd_mat44f operator/(const simd_mat44f &m_, float s_)
{
  // divide matrix by scalar
  simd_float4 rs=_mm_rcp_ss(_mm_load_ss(&s_));
  rs=_mm_shuffle_ps(rs, rs, 0);
  return simd_mat44f(_mm_mul_ps((simd_float4&)m_.x, rs),
                     _mm_mul_ps((simd_float4&)m_.y, rs),
                     _mm_mul_ps((simd_float4&)m_.z, rs),
                     _mm_mul_ps((simd_float4&)m_.w, rs));
}
//----

PFC_INLINE simd_mat44f mul(const simd_mat44f &m0_, const simd_mat44f &m1_)
{
  // component-wise multiply: m0_*m1
  return simd_mat44f(_mm_mul_ps((simd_float4&)m0_.x, (simd_float4&)m1_.x),
                     _mm_mul_ps((simd_float4&)m0_.y, (simd_float4&)m1_.y),
                     _mm_mul_ps((simd_float4&)m0_.z, (simd_float4&)m1_.z),
                     _mm_mul_ps((simd_float4&)m0_.w, (simd_float4&)m1_.w));
}
//----

PFC_INLINE simd_mat44f madd(const simd_mat44f &mm0_, const simd_mat44f &mm1_, const simd_mat44f &ma_)
{
  // component-wise multiply-add: mm0_*mm1_+ma_
  return simd_mat44f(_mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.x, (simd_float4&)mm1_.x), (simd_float4&)ma_.x),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.y, (simd_float4&)mm1_.y), (simd_float4&)ma_.y),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.z, (simd_float4&)mm1_.z), (simd_float4&)ma_.z),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.w, (simd_float4&)mm1_.w), (simd_float4&)ma_.w));
}
//----

PFC_INLINE simd_mat44f madd(const simd_mat44f &mm_, float sm_, float sa_)
{
  // component-wise multiply-add: mm_*sm_+ma_
  simd_float4 vm=_mm_set1_ps(sm_);
  simd_float4 va=_mm_set1_ps(sa_);
  return simd_mat44f(_mm_add_ps(_mm_mul_ps((simd_float4&)mm_.x, vm), va),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm_.y, vm), va),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm_.z, vm), va),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm_.w, vm), va));
}
//----

PFC_INLINE simd_mat44f madd(const simd_mat44f &mm0_, const simd_mat44f &mm1_, float sa_)
{
  // component-wise multiply-add: mm0_*mm1_+sa_
  simd_float4 va=_mm_set1_ps(sa_);
  return simd_mat44f(_mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.x, (simd_float4&)mm1_.x), va),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.y, (simd_float4&)mm1_.y), va),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.z, (simd_float4&)mm1_.z), va),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm0_.w, (simd_float4&)mm1_.w), va));
}
//----

PFC_INLINE simd_mat44f madd(const simd_mat44f &mm_, float sm_, const simd_mat44f &ma_)
{
  // component-wise multiply-add: mm_*sm_+ma_
  simd_float4 vm=_mm_set1_ps(sm_);
  return simd_mat44f(_mm_add_ps(_mm_mul_ps((simd_float4&)mm_.x, vm), (simd_float4&)ma_.x),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm_.y, vm), (simd_float4&)ma_.y),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm_.z, vm), (simd_float4&)ma_.z),
                     _mm_add_ps(_mm_mul_ps((simd_float4&)mm_.w, vm), (simd_float4&)ma_.w));
}
//----

PFC_INLINE float det(const simd_mat44f &m_)
{
  // determinant of the matrix
  simd_float4 d2=_mm_sub_ps(_mm_mul_ps((simd_float4&)m_.z, _mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.w, _MM_SHUFFLE(0, 3, 2, 1))),
                            _mm_mul_ps((simd_float4&)m_.w, _mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.z, _MM_SHUFFLE(0, 3, 2, 1))));
  simd_float4 d2s=_mm_sub_ps(_mm_mul_ps((simd_float4&)m_.w, _mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.z, _MM_SHUFFLE(1, 0, 3, 2))),
                             _mm_mul_ps((simd_float4&)m_.z, _mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.w, _MM_SHUFFLE(1, 0, 3, 2))));
  simd_float4 d3=_mm_add_ps(_mm_add_ps(_mm_mul_ps((simd_float4&)m_.y, _mm_shuffle_ps(d2, d2, _MM_SHUFFLE(0, 3, 2, 1))),
                                       _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m_.y, (simd_float4&)m_.y, _MM_SHUFFLE(0, 3, 2, 1)), d2s)),
                            _mm_mul_ps(_mm_shuffle_ps((simd_float4&)m_.y, (simd_float4&)m_.y, _MM_SHUFFLE(1, 0, 3, 2)), d2));
  PFC_ALIGN(16) float32_t v[4];
  _mm_store_ps(v, _mm_mul_ps((simd_float4&)m_.x, _mm_shuffle_ps(d3, d3, _MM_SHUFFLE(0, 3, 2, 1))));
  return v[0]-v[1]+v[2]-v[3];
}
//----

PFC_INLINE simd_mat44f inv(const simd_mat44f &m_, float *det_=0)
{
  // 4x4 matrix inverse based on SSE matrix inverse implementation by Christophe Riccio
  // calculate 18 2x2 matrix determinants for 3 3x3 sub-matrices
  simd_float4 swp0a=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(3, 3, 3, 3));
  simd_float4 swp0b=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(2, 2, 2, 2));
  simd_float4 fac0=_mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(2, 2, 2, 2)),
                                         _mm_shuffle_ps(swp0a, swp0a, _MM_SHUFFLE(2, 0, 0, 0))),
                              _mm_mul_ps(_mm_shuffle_ps(swp0b, swp0b, _MM_SHUFFLE(2, 0, 0, 0)),
                                         _mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(3, 3, 3, 3))));
  simd_float4 swp1a=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(3, 3, 3, 3));
  simd_float4 swp1b=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(1, 1, 1, 1));
  simd_float4 fac1=_mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(1, 1, 1, 1)),
                                         _mm_shuffle_ps(swp1a, swp1a, _MM_SHUFFLE(2, 0, 0, 0))),
                              _mm_mul_ps(_mm_shuffle_ps(swp1b, swp1b, _MM_SHUFFLE(2, 0, 0, 0)),
                                         _mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(3, 3, 3, 3))));
  simd_float4 swp2a=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(2, 2, 2, 2));
  simd_float4 swp2b=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(1, 1, 1, 1));
  simd_float4 fac2=_mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(1, 1, 1, 1)),
                                         _mm_shuffle_ps(swp2a, swp2a, _MM_SHUFFLE(2, 0, 0, 0))),
                              _mm_mul_ps(_mm_shuffle_ps(swp2b, swp2b, _MM_SHUFFLE(2, 0, 0, 0)),
                                         _mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(2, 2, 2, 2))));
  simd_float4 swp3a=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(3, 3, 3, 3));
  simd_float4 swp3b=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(0, 0, 0, 0));
  simd_float4 fac3=_mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(0, 0, 0, 0)),
                                         _mm_shuffle_ps(swp3a, swp3a, _MM_SHUFFLE(2, 0, 0, 0))),
                              _mm_mul_ps(_mm_shuffle_ps(swp3b, swp3b, _MM_SHUFFLE(2, 0, 0, 0)),
                                         _mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(3, 3, 3, 3))));
  simd_float4 swp4a=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(2, 2, 2, 2));
  simd_float4 swp4b=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(0, 0, 0, 0));
  simd_float4 fac4=_mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(0, 0, 0, 0)),
                                         _mm_shuffle_ps(swp4a, swp4a, _MM_SHUFFLE(2, 0, 0, 0))),
                              _mm_mul_ps(_mm_shuffle_ps(swp4b, swp4b, _MM_SHUFFLE(2, 0, 0, 0)),
                                         _mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(2, 2, 2, 2))));
  simd_float4 swp5a=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(1, 1, 1, 1));
  simd_float4 swp5b=_mm_shuffle_ps((simd_float4&)m_.w, (simd_float4&)m_.z, _MM_SHUFFLE(0, 0, 0, 0));
  simd_float4 fac5=_mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(0, 0, 0, 0)),
                                         _mm_shuffle_ps(swp5a, swp5a, _MM_SHUFFLE(2, 0, 0, 0))),
                              _mm_mul_ps(_mm_shuffle_ps(swp5b, swp5b, _MM_SHUFFLE(2, 0, 0, 0)),
                                         _mm_shuffle_ps((simd_float4&)m_.z, (simd_float4&)m_.y, _MM_SHUFFLE(1, 1, 1, 1))));

  // calculate adjugate matrix
  simd_float4 temp0=_mm_shuffle_ps((simd_float4&)m_.y, (simd_float4&)m_.x, _MM_SHUFFLE(0, 0, 0, 0));
  simd_float4 v0=_mm_shuffle_ps(temp0, temp0, _MM_SHUFFLE(2, 2, 2, 0));
  simd_float4 temp1=_mm_shuffle_ps((simd_float4&)m_.y, (simd_float4&)m_.x, _MM_SHUFFLE(1, 1, 1, 1));
  simd_float4 v1=_mm_shuffle_ps(temp1, temp1, _MM_SHUFFLE(2, 2, 2, 0));
  simd_float4 temp2=_mm_shuffle_ps((simd_float4&)m_.y, (simd_float4&)m_.x, _MM_SHUFFLE(2, 2, 2, 2));
  simd_float4 v2=_mm_shuffle_ps(temp2, temp2, _MM_SHUFFLE(2, 2, 2, 0));
  simd_float4 temp3=_mm_shuffle_ps((simd_float4&)m_.y, (simd_float4&)m_.x, _MM_SHUFFLE(3, 3, 3, 3));
  simd_float4 v3=_mm_shuffle_ps(temp3, temp3, _MM_SHUFFLE(2, 2, 2, 0));
  simd_float4 adj0=_mm_mul_ps(simd::g_neg_yw,
                              _mm_add_ps(_mm_sub_ps(_mm_mul_ps(v1, fac0),
                                                    _mm_mul_ps(v2, fac1)),
                                                    _mm_mul_ps(v3, fac2)));
  simd_float4 adj2=_mm_mul_ps(simd::g_neg_yw,
                              _mm_add_ps(_mm_sub_ps(_mm_mul_ps(v0, fac1),
                                                    _mm_mul_ps(v1, fac3)),
                                                    _mm_mul_ps(v3, fac5)));
  simd_float4 adj1=_mm_mul_ps(simd::g_neg_xz,
                              _mm_add_ps(_mm_sub_ps(_mm_mul_ps(v0, fac0),
                                                    _mm_mul_ps(v2, fac3)),
                                                    _mm_mul_ps(v3, fac4)));
  simd_float4 adj3=_mm_mul_ps(simd::g_neg_xz,
                              _mm_add_ps(_mm_sub_ps(_mm_mul_ps(v0, fac2),
                                                    _mm_mul_ps(v1, fac4)),
                                                    _mm_mul_ps(v2, fac5)));

  // multiply the adjugate matrix with determinant reciprocal for inverse matrix
  simd_float4 row0=_mm_shuffle_ps(adj0, adj1, _MM_SHUFFLE(0, 0, 0, 0));
  simd_float4 row1=_mm_shuffle_ps(adj2, adj3, _MM_SHUFFLE(0, 0, 0, 0));
  simd_float4 row2=_mm_shuffle_ps(row0, row1, _MM_SHUFFLE(2, 0, 2, 0));
  simd_float4 mul0=_mm_mul_ps((simd_float4&)m_.x, row2);
  simd_float4 add0=_mm_add_ps(mul0, _mm_shuffle_ps(mul0, mul0, _MM_SHUFFLE(2, 3, 0, 1)));
  simd_float4 det0=_mm_add_ps(add0, _mm_shuffle_ps(add0, add0, _MM_SHUFFLE(0, 1, 2, 3)));
  simd_float4 rcp0=_mm_rcp_ps(det0);
  if(det_)
    *det_=(float&)det0;
  return simd_mat44f(_mm_mul_ps(adj0, rcp0),
                     _mm_mul_ps(adj1, rcp0),
                     _mm_mul_ps(adj2, rcp0),
                     _mm_mul_ps(adj3, rcp0));
}
//----
/*
PFC_INLINE float tr(const simd_mat44f &m_)
{
  // trace of the matrix
  return m_.x.x+m_.y.y+m_.z.z+m_.w.w;
}
//----
*/
PFC_INLINE void identity(simd_mat44f &m_)
{
  // set identity
  (simd_float4&)m_.x=simd::g_ident_x;
  (simd_float4&)m_.y=simd::g_ident_y;
  (simd_float4&)m_.z=simd::g_ident_z;
  (simd_float4&)m_.w=simd::g_ident_w;
}
//----
/*
PFC_INLINE void transpose(simd_mat44f &m_)
{
  // transpose the matrix
  float t=m_.x.y;
  m_.x.y=m_.y.x;
  m_.y.x=t;
  t=m_.x.z;
  m_.x.z=m_.z.x;
  m_.z.x=t;
  t=m_.x.w;
  m_.x.w=m_.w.x;
  m_.w.x=t;
  t=m_.y.z;
  m_.y.z=m_.z.y;
  m_.z.y=t;
  t=m_.y.w;
  m_.y.w=m_.w.y;
  m_.w.y=t;
  t=m_.z.w;
  m_.z.w=m_.w.z;
  m_.w.z=t;
}
//----

PFC_INLINE void transpose(simd_mat44f &res_, const simd_mat44f &m_)
{
  // transpose the matrix
  res_.x.x=m_.x.x; res_.x.y=m_.y.x; res_.x.z=m_.z.x; res_.x.w=m_.w.x;
  res_.y.x=m_.x.y; res_.y.y=m_.y.y; res_.y.z=m_.z.y; res_.y.w=m_.w.y;
  res_.z.x=m_.x.z; res_.z.y=m_.y.z; res_.z.z=m_.z.z; res_.z.w=m_.w.z;
  res_.w.x=m_.x.w; res_.w.y=m_.y.w; res_.w.z=m_.z.w; res_.w.w=m_.w.w;
}
//----
*/
PFC_INLINE void neg(simd_mat44f &m_)
{
  // negate the matrix
  simd_float4 zero=_mm_setzero_ps();
  (simd_float4&)m_.x=_mm_sub_ps(zero, (simd_float4&)m_.x);
  (simd_float4&)m_.y=_mm_sub_ps(zero, (simd_float4&)m_.y);
  (simd_float4&)m_.z=_mm_sub_ps(zero, (simd_float4&)m_.z);
  (simd_float4&)m_.w=_mm_sub_ps(zero, (simd_float4&)m_.w);
}
//----

PFC_INLINE simd_mat44f lerp(const simd_mat44f &m0_, const simd_mat44f &m1_, float t_)
{
  // linear matrix interpolation. f(t=0)=v0, f(t=1)=v1
  simd_float4 t=_mm_set1_ps(t_);
  return simd_mat44f(_mm_add_ps((simd_float4&)m0_.x, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.x, (simd_float4&)m0_.x), t)),
                     _mm_add_ps((simd_float4&)m0_.y, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.y, (simd_float4&)m0_.y), t)),
                     _mm_add_ps((simd_float4&)m0_.z, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.z, (simd_float4&)m0_.z), t)),
                     _mm_add_ps((simd_float4&)m0_.w, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.w, (simd_float4&)m0_.w), t)));
}
//----

PFC_INLINE void lerp(simd_mat44f &res_, const simd_mat44f &m0_, const simd_mat44f &m1_, float t_)
{
  // linear matrix interpolation. f(t=0)=v0, f(t=1)=v1
  simd_float4 t=_mm_set1_ps(t_);
  (simd_float4&)res_.x=_mm_add_ps((simd_float4&)m0_.x, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.x, (simd_float4&)m0_.x), t));
  (simd_float4&)res_.y=_mm_add_ps((simd_float4&)m0_.y, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.y, (simd_float4&)m0_.y), t));
  (simd_float4&)res_.z=_mm_add_ps((simd_float4&)m0_.z, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.z, (simd_float4&)m0_.z), t));
  (simd_float4&)res_.w=_mm_add_ps((simd_float4&)m0_.w, _mm_mul_ps(_mm_sub_ps((simd_float4&)m1_.w, (simd_float4&)m0_.w), t));
}
//----------------------------------------------------------------------------


//============================================================================
// simd_quatf
//============================================================================
simd_quatf::quat()
{
}
//----

simd_quatf::quat(float s_)
{
  // init quat with scalar
  (simd_float4&)*this=_mm_set1_ps(s_);
}
//----

simd_quatf::quat(float x_, float y_, float z_, float w_)
{
  // init quat with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

simd_quatf::quat(const simd_vec3f &v_)
{
  // init quat with 3d SIMD vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=0.0f;
}
//----

simd_quatf::quat(const vec3f &v_)
{
  // init quat with 3d fp-vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=0.0f;
}
//----

simd_quatf::quat(const simd_vec3f &v_, float w_)
{
  // init quat with 3d SIMD vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

simd_quatf::quat(const vec3f &v_, float w_)
{
  // init quat with 3d fp-vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

simd_quatf::quat(const simd_vec4f &v_)
{
  // init quat with 4d SIMD vector
  (simd_float4&)*this=(simd_float4&)v_;
}
//----

simd_quatf::quat(const vec4f &v_)
{
  // init quat with 4d fp-vector
  (simd_float4&)*this=_mm_loadu_ps((const float*)&v_);
}
//----

simd_quatf::quat(const quatf &q_)
{
  // init quat with fp-quat
  (simd_float4&)*this=_mm_loadu_ps((const float*)&q_);
}
//----

simd_quatf::quat(const simd_float4 &v_)
{
  // init quat with SIMD float4
  (simd_float4&)*this=v_;
}
//----

simd_quatf::quat(const float *a_)
{
  // init quat with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  (simd_float4&)*this=_mm_loadu_ps(a_);
}
//----------------------------------------------------------------------------

const float &simd_quatf::operator[](unsigned idx_) const
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const float*>(this)[idx_];
}
//----

float &simd_quatf::operator[](unsigned idx_)
{
  // return reference to nth component (x=0, y=1, z=2, w=3)
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<float*>(this)[idx_];
}
//----

void simd_quatf::set(float s_)
{
  // set quat with scalar
  (simd_float4&)*this=_mm_set1_ps(s_);
}
//----

void simd_quatf::set(float x_, float y_, float z_, float w_)
{
  // set quat with scalars
  x=x_;
  y=y_;
  z=z_;
  w=w_;
}
//----

void simd_quatf::set(const simd_vec3f &v_)
{
  // set quat with 3d SIMD vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=0;
}
//----

void simd_quatf::set(const vec3f &v_)
{
  // set quat with 3d fp-vector
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=0;
}
//----

void simd_quatf::set(const simd_vec3f &v_, float w_)
{
  // set quat with 3d SIMD vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

void simd_quatf::set(const vec3f &v_, float w_)
{
  // set quat with 3d fp-vector and w
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=w_;
}
//----

void simd_quatf::set(const simd_vec4f &v_)
{
  // set quat with 4d SIMD vector
  (simd_float4&)*this=(simd_float4&)v_;
}
//----

void simd_quatf::set(const vec4f &v_)
{
  // set quat with 4d fp-vector
  (simd_float4&)*this=_mm_loadu_ps((const float*)&v_);
}
//----

void simd_quatf::set(const simd_quatf &v_)
{
  // set quat with SIMD quat
  (simd_float4&)*this=(simd_float4&)v_;
}
//----

void simd_quatf::set(const quatf &q_)
{
  // set quat with fp-quat
  (simd_float4&)*this=_mm_loadu_ps((const float*)&q_);
}
//----

void simd_quatf::set(const simd_float4 &v_)
{
  // set quat with SIMD float4
  (simd_float4&)*this=v_;
}
//----

void simd_quatf::set(const float *a_)
{
  // set quat with an array of scalars
  PFC_ASSERT_PEDANTIC(a_);
  (simd_float4&)*this=_mm_loadu_ps(a_);
}
//----------------------------------------------------------------------------

PFC_INLINE bool is_zero(const simd_quatf &q_)
{
  // test for zero-quaternion
  return _mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)q_, _mm_setzero_ps()))==0;
}
//----

PFC_INLINE bool is_sat(const simd_quatf &q_)
{
  // test for saturated quaternion
  return _mm_movemask_ps(_mm_or_ps(_mm_cmplt_ps((simd_float4&)q_, _mm_setzero_ps()),
                                   _mm_cmpgt_ps((simd_float4&)q_, simd::g_one)))==0;
}
//----

PFC_INLINE bool is_ssat(const simd_quatf &q_)
{
  // test for signed saturated quaternion
  return _mm_movemask_ps(_mm_or_ps(_mm_cmplt_ps((simd_float4&)q_, simd::g_neg_one),
                                   _mm_cmpgt_ps((simd_float4&)q_, simd::g_one)))==0;
}
//----

PFC_INLINE bool operator==(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // test for equality of quats
  return _mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)q0_, (simd_float4&)q1_))==0;
}
//----

PFC_INLINE bool operator==(const simd_quatf &q_, float s_)
{
  // test for equality of quat and scalar
  return _mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)q_, _mm_set1_ps(s_)))==0;
}
//----

PFC_INLINE bool operator==(float s_, const simd_quatf &q_)
{
  // test for equality of quat and scalar
  return _mm_movemask_ps(_mm_cmpneq_ps(_mm_set1_ps(s_), (simd_float4&)q_))==0;
}
//----

PFC_INLINE bool operator!=(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // test for inequality of quats
  return _mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)q0_, (simd_float4&)q1_))!=0;
}
//----

PFC_INLINE bool operator!=(const simd_quatf &q_, float s_)
{
  // test for inequality of quat and scalar
  return _mm_movemask_ps(_mm_cmpneq_ps((simd_float4&)q_, _mm_set1_ps(s_)))!=0;
}
//----

PFC_INLINE bool operator!=(float s_, const simd_quatf &q_)
{
  // test for inequality of quat and scalar
  return _mm_movemask_ps(_mm_cmpneq_ps(_mm_set1_ps(s_), (simd_float4&)q_))!=0;
}
//----

PFC_INLINE simd_quatf operator<(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise less-than (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmplt_ps((simd_float4&)q0_, (simd_float4&)q1_), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator<(const simd_quatf &q_, float s_)
{
  // component-wise less-than (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmplt_ps((simd_float4&)q_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator<(float s_, const simd_quatf &q_)
{
  // component-wise less-than (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmplt_ps(_mm_set1_ps(s_), (simd_float4&)q_), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator>(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise greater-than (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmpgt_ps((simd_float4&)q0_, (simd_float4&)q1_), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator>(const simd_quatf &q_, float s_)
{
  // component-wise greater-than (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmpgt_ps((simd_float4&)q_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator>(float s_, const simd_quatf &q_)
{
  // component-wise greater-than (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmpgt_ps(_mm_set1_ps(s_), (simd_float4&)q_), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator<=(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise less-or-equal (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmple_ps((simd_float4&)q0_, (simd_float4&)q1_), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator<=(const simd_quatf &q_, float s_)
{
  // component-wise less-or-equal (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmple_ps((simd_float4&)q_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator<=(float s_, const simd_quatf &q_)
{
  // component-wise less-or-equal (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmple_ps(_mm_set1_ps(s_), (simd_float4&)q_), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator>=(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise greater-or-equal (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmpge_ps((simd_float4&)q0_, (simd_float4&)q1_), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator>=(const simd_quatf &q_, float s_)
{
  // component-wise greater-or-equal (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmpge_ps((simd_float4&)q_, _mm_set1_ps(s_)), simd::g_one));
}
//----

PFC_INLINE simd_quatf operator>=(float s_, const simd_quatf &q_)
{
  // component-wise greater-or-equal (false=0, true=1)
  return simd_quatf(_mm_and_ps(_mm_cmpge_ps(_mm_set1_ps(s_), (simd_float4&)q_), simd::g_one));
}
//----

PFC_INLINE simd_quatf sel_eq(const simd_quatf &t0_, const simd_quatf &t1_, const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise equal quaternion select (t0_==t1_?q0_:q1_)
  simd_float4 r=_mm_cmpeq_ps((simd_float4&)t0_, (simd_float4&)t1_);
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_blendv_ps((simd_float4&)q1_, (simd_float4&)q0_, r));
#else
  return simd_quatf(_mm_or_ps(_mm_and_ps(r, (simd_float4&)q0_), _mm_andnot_ps(r, (simd_float4&)q1_)));
#endif
}
//----

PFC_INLINE simd_quatf sel_lt(const simd_quatf &t0_, const simd_quatf &t1_, const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise less-than quaternion select (t0_<t1_?q0_:q1_)
  simd_float4 r=_mm_cmplt_ps((simd_float4&)t0_, (simd_float4&)t1_);
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_blendv_ps((simd_float4&)q1_, (simd_float4&)q0_, r));
#else
  return simd_quatf(_mm_or_ps(_mm_and_ps(r, (simd_float4&)q0_), _mm_andnot_ps(r, (simd_float4&)q1_)));
#endif
}
//----

PFC_INLINE simd_quatf sel_le(const simd_quatf &t0_, const simd_quatf &t1_, const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise less-or-equal quaternion select (t0_<=t1_?q0_:q1_)
  simd_float4 r=_mm_cmple_ps((simd_float4&)t0_, (simd_float4&)t1_);
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_blendv_ps((simd_float4&)q1_, (simd_float4&)q0_, r));
#else
  return simd_quatf(_mm_or_ps(_mm_and_ps(r, (simd_float4&)q0_), _mm_andnot_ps(r, (simd_float4&)q1_)));
#endif
}
//----

PFC_INLINE simd_quatf sel_eqz(const simd_quatf &t_, const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise equal-to-zero quaternion select (t_==0?q0_:q1_)
  simd_float4 r=_mm_cmpeq_ps((simd_float4&)t_, _mm_setzero_ps());
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_blendv_ps((simd_float4&)q1_, (simd_float4&)q0_, r));
#else
  return simd_quatf(_mm_or_ps(_mm_and_ps(r, (simd_float4&)q0_), _mm_andnot_ps(r, (simd_float4&)q1_)));
#endif
}
//----

PFC_INLINE simd_quatf sel_ltz(const simd_quatf &t_, const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise less-than-zero quaternion select (t_<0?q0_:q1_)
  simd_float4 r=_mm_cmplt_ps((simd_float4&)t_, _mm_setzero_ps());
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_blendv_ps((simd_float4&)q1_, (simd_float4&)q0_, r));
#else
  return simd_quatf(_mm_or_ps(_mm_and_ps(r, (simd_float4&)q0_), _mm_andnot_ps(r, (simd_float4&)q1_)));
#endif
}
//----

PFC_INLINE simd_quatf sel_lez(const simd_quatf &t_, const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise less-or-equal-to-zero quaternion select (t_<=0?q0_:q1_)
  simd_float4 r=_mm_cmple_ps((simd_float4&)t_, _mm_setzero_ps());
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_blendv_ps((simd_float4&)q1_, (simd_float4&)q0_, r));
#else
  return simd_quatf(_mm_or_ps(_mm_and_ps(r, (simd_float4&)q0_), _mm_andnot_ps(r, (simd_float4&)q1_)));
#endif
}
//----

PFC_INLINE void operator+=(simd_quatf &qr_, const simd_quatf &q_)
{
  // add quat to quat
  (simd_float4&)qr_=_mm_add_ps((simd_float4&)qr_, (simd_float4&)q_);
}
//----

PFC_INLINE void operator+=(simd_quatf &qr_, float s_)
{
  // add scalar to each component of the quat
  (simd_float4&)qr_=_mm_add_ps((simd_float4&)qr_, _mm_set1_ps(s_));
}
//----

PFC_INLINE void operator-=(simd_quatf &qr_, const simd_quatf &q_)
{
  // subtract quat from quat
  (simd_float4&)qr_=_mm_sub_ps((simd_float4&)qr_, (simd_float4&)q_);
}
//----

PFC_INLINE void operator-=(simd_quatf &qr_, float s_)
{
  // subtract scalar from each component of the quat
  (simd_float4&)qr_=_mm_sub_ps((simd_float4&)qr_, _mm_set1_ps(s_));
}
//----

PFC_INLINE void operator*=(simd_quatf &qr_, const simd_quatf &q_)
{
  // multiply quat by quat
  simd_float4 v=_mm_add_ps(_mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)qr_, (simd_float4&)qr_, _MM_SHUFFLE(0, 0, 2, 1)),
                                                 _mm_shuffle_ps((simd_float4&)q_,  (simd_float4&)q_,  _MM_SHUFFLE(0, 1, 0, 2))),
                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)qr_, (simd_float4&)qr_, _MM_SHUFFLE(3, 1, 0, 2)),
                                                 _mm_shuffle_ps((simd_float4&)q_,  (simd_float4&)q_,  _MM_SHUFFLE(3, 0, 2, 1)))),
                           _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)qr_, (simd_float4&)qr_, _MM_SHUFFLE(1, 3, 3, 3)),
                                                 _mm_shuffle_ps((simd_float4&)q_,  (simd_float4&)q_,  _MM_SHUFFLE(1, 2, 1, 0))),
                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)qr_, (simd_float4&)qr_, _MM_SHUFFLE(2, 2, 1, 0)),
                                                 _mm_shuffle_ps((simd_float4&)q_,  (simd_float4&)q_,  _MM_SHUFFLE(2, 3, 3, 3)))));
  (simd_float4&)qr_=_mm_mul_ps(v, simd::g_neg_w);
}
//----

PFC_INLINE void operator*=(simd_quatf &qr_, float s_)
{
  // multiply quat by scalar
  (simd_float4&)qr_=_mm_mul_ps((simd_float4&)qr_, _mm_set1_ps(s_));
}
//----

PFC_INLINE void operator/=(simd_quatf &qr_, float s_)
{
  // divide quat by scalar
  simd_float4 rs=_mm_rcp_ss(_mm_load_ss(&s_));
  (simd_float4&)qr_=_mm_mul_ps((simd_float4&)qr_, _mm_shuffle_ps(rs, rs, 0));
}
//----

PFC_INLINE simd_quatf operator+(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // add quat to quat
  return simd_quatf(_mm_add_ps((simd_float4&)q0_, (simd_float4&)q1_));
}
//----

PFC_INLINE simd_quatf operator+(const simd_quatf &q_, float s_)
{
  // add scalar to each component of the quat
  return simd_quatf(_mm_add_ps((simd_float4&)q_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_quatf operator+(float s_, const simd_quatf &q_)
{
  // add each component of the quat to a scalar quat
  return simd_quatf(_mm_add_ps(_mm_set1_ps(s_), (simd_float4&)q_));
}
//----

PFC_INLINE simd_quatf operator-(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // subtract quat from quat
  return simd_quatf(_mm_sub_ps((simd_float4&)q0_, (simd_float4&)q1_));
}
//----

PFC_INLINE simd_quatf operator-(const simd_quatf &q_, float s_)
{
  // subtract scalar from each component of the quat
  return simd_quatf(_mm_sub_ps((simd_float4&)q_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_quatf operator-(float s_, const simd_quatf &q_)
{
  // subtract each component of the quat from a scalar quat
  return simd_quatf(_mm_sub_ps(_mm_set1_ps(s_), (simd_float4&)q_));
}
//----

PFC_INLINE simd_quatf operator-(const simd_quatf &q_)
{
  // negate quat
  return simd_quatf(_mm_sub_ps(_mm_setzero_ps(), (simd_float4&)q_));
}
//----

PFC_INLINE simd_quatf operator*(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // multiply quat by quat
  simd_float4 v=_mm_add_ps(_mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)q0_, (simd_float4&)q0_, _MM_SHUFFLE(0, 0, 2, 1)),
                                                 _mm_shuffle_ps((simd_float4&)q1_, (simd_float4&)q1_, _MM_SHUFFLE(0, 1, 0, 2))),
                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)q0_, (simd_float4&)q0_, _MM_SHUFFLE(3, 1, 0, 2)),
                                                 _mm_shuffle_ps((simd_float4&)q1_, (simd_float4&)q1_, _MM_SHUFFLE(3, 0, 2, 1)))),
                           _mm_add_ps(_mm_mul_ps(_mm_shuffle_ps((simd_float4&)q0_, (simd_float4&)q0_, _MM_SHUFFLE(1, 3, 3, 3)),
                                                 _mm_shuffle_ps((simd_float4&)q1_, (simd_float4&)q1_, _MM_SHUFFLE(1, 2, 1, 0))),
                                      _mm_mul_ps(_mm_shuffle_ps((simd_float4&)q0_, (simd_float4&)q0_, _MM_SHUFFLE(2, 2, 1, 0)),
                                                 _mm_shuffle_ps((simd_float4&)q1_, (simd_float4&)q1_, _MM_SHUFFLE(2, 3, 3, 3)))));
  return simd_quatf(_mm_mul_ps(v, simd::g_neg_w));
}
//----

PFC_INLINE simd_quatf operator*(const simd_quatf &q_, float s_)
{
  // multiply quat by scalar
  return simd_quatf(_mm_mul_ps((simd_float4&)q_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_quatf operator*(float s_, const simd_quatf &q_)
{
  // multiply quat by scalar
  return simd_quatf(_mm_mul_ps((simd_float4&)q_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_quatf operator/(const simd_quatf &q_, float s_)
{
  // divide quat by scalar
  simd_float4 rs=_mm_rcp_ss(_mm_load_ss(&s_));
  return simd_quatf(_mm_mul_ps((simd_float4&)q_, _mm_shuffle_ps(rs, rs, 0)));
}
//----

PFC_INLINE simd_quatf min(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise min quat
  return simd_quatf(_mm_min_ps((simd_float4&)q0_, (simd_float4&)q1_));
}
//----

PFC_INLINE simd_quatf min(const simd_quatf &q0_, const simd_quatf &q1_, const simd_quatf &q2_)
{
  // component-wise min quat
  return simd_quatf(_mm_min_ps(_mm_min_ps((simd_float4&)q0_, (simd_float4&)q1_), (simd_float4&)q2_));
}
//----

PFC_INLINE simd_quatf min(const simd_quatf &q0_, const simd_quatf &q1_, const simd_quatf &q2_, const simd_quatf &q3_)
{
  // component-wise min quat
  return simd_quatf(_mm_min_ps(_mm_min_ps(_mm_min_ps((simd_float4&)q0_, (simd_float4&)q1_), (simd_float4&)q2_), (simd_float4&)q3_));
}
//----

PFC_INLINE simd_quatf min(const simd_quatf &q_, float s_)
{
  // component-wise min quat
  return simd_quatf(_mm_min_ps((simd_float4&)q_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_quatf min(float s_, const simd_quatf &q_)
{
  // component-wise min quat
  return simd_quatf(_mm_min_ps((simd_float4&)q_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_quatf max(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise max quat
  return simd_quatf(_mm_max_ps((simd_float4&)q0_, (simd_float4&)q1_));
}
//----

PFC_INLINE simd_quatf max(const simd_quatf &q0_, const simd_quatf &q1_, const simd_quatf &q2_)
{
  // component-wise max quat
  return simd_quatf(_mm_max_ps(_mm_max_ps((simd_float4&)q0_, (simd_float4&)q1_), (simd_float4&)q2_));
}
//----

PFC_INLINE simd_quatf max(const simd_quatf &q0_, const simd_quatf &q1_, const simd_quatf &q2_, const simd_quatf &q3_)
{
  // component-wise max quat
  return simd_quatf(_mm_max_ps(_mm_max_ps(_mm_max_ps((simd_float4&)q0_, (simd_float4&)q1_), (simd_float4&)q2_), (simd_float4&)q3_));
}
//----

PFC_INLINE simd_quatf max(const simd_quatf &q_, float s_)
{
  // component-wise max quat
  return simd_quatf(_mm_max_ps((simd_float4&)q_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_quatf max(float s_, const simd_quatf &q_)
{
  // component-wise max quat
  return simd_quatf(_mm_max_ps((simd_float4&)q_, _mm_set1_ps(s_)));
}
//----

PFC_INLINE simd_quatf mul(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // component-wise multiply: q0_*q1
  return simd_quatf(_mm_mul_ps((simd_float4&)q0_, (simd_float4&)q1_));
}
//----

PFC_INLINE simd_quatf madd(const simd_quatf &qm0_, const simd_quatf &qm1_, const simd_quatf &qa_)
{
  // component-wise multiply-add: qm0_*qm1_+qa_
  return simd_quatf(_mm_add_ps(_mm_mul_ps((simd_float4&)qm0_, (simd_float4&)qm1_), (simd_float4&)qa_));
}
//----

PFC_INLINE simd_quatf madd(const simd_quatf &qm_, float sm_, float sa_)
{
  // component-wise multiply-add: qm_*sm_+sa_
  return simd_quatf(_mm_add_ps(_mm_mul_ps((simd_float4&)qm_, _mm_set1_ps(sm_)), _mm_set1_ps(sa_)));
}
//----

PFC_INLINE simd_quatf madd(const simd_quatf &qm_, const simd_quatf &sm_, float sa_)
{
  // component-wise multiply-add: qm_*sm_+sa_
  return simd_quatf(_mm_add_ps(_mm_mul_ps((simd_float4&)qm_, (simd_float4&)sm_), _mm_set1_ps(sa_)));
}
//----

PFC_INLINE simd_quatf madd(const simd_quatf &qm_, float sm_, const simd_quatf &qa_)
{
  // component-wise multiply-add: qm_*sm_+qa_
  return simd_quatf(_mm_add_ps(_mm_mul_ps((simd_float4&)qm_, _mm_set1_ps(sm_)), (simd_float4&)qa_));
}
//----

PFC_INLINE simd_quatf rcp(const simd_quatf &q_)
{
  // component-wise reciprocal
  return simd_quatf(_mm_rcp_ps((simd_float4&)q_));
}
//----

PFC_INLINE simd_quatf rcp_z(const simd_quatf &q_)
{
  // component-wise reciprocal (set to 0 for 0 components)
  return simd_quatf(_mm_and_ps(_mm_cmpneq_ps((simd_float4&)q_, _mm_setzero_ps()), _mm_rcp_ps((simd_float4&)q_)));
}
//----

PFC_INLINE simd_quatf floor(const simd_quatf &q_)
{
  // component-wise floor
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_round_ps((simd_float4&)q_, _MM_FROUND_FLOOR));
#else
  const float *f=(const float*)&q_;
  return simd_quatf(std::floor(f[0]), std::floor(f[1]), std::floor(f[2]), std::floor(f[3]));
#endif
}
//----

PFC_INLINE simd_quatf ceil(const simd_quatf &q_)
{
  // component-wise ceil
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_round_ps((simd_float4&)q_, _MM_FROUND_CEIL));
#else
  const float *f=(const float*)&q_;
  return simd_quatf(std::ceil(f[0]), std::ceil(f[1]), std::ceil(f[2]), std::ceil(f[3]));
#endif
}
//----

PFC_INLINE simd_quatf trunc(const simd_quatf &q_)
{
  // component-wise truncate
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_round_ps((simd_float4&)q_, _MM_FROUND_TO_ZERO));
#else
  return simd_quatf(float(int(q_.x)), float(int(q_.y)), float(int(q_.z)), float(int(q_.w)));
#endif
}
//----

PFC_INLINE simd_quatf frc(const simd_quatf &q_)
{
  // component-wise fractional
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_sub_ps((simd_float4&)q_, _mm_round_ps((simd_float4&)q_, _MM_FROUND_TO_ZERO)));
#else
  const float *f=(const float*)&q_;
  return simd_quatf(f[0]-float(int(f[0])), f[1]-float(int(f[1])), f[2]-float(int(f[2])), f[3]-float(int(f[3])));
#endif
}
//----

PFC_INLINE simd_quatf mod(const simd_quatf &q_, float div_)
{
  // component-wise modulo
#ifdef PFC_PLATFORM_SSE4
  simd_float4 d=_mm_set1_ps(div_);
  return simd_quatf(_mm_sub_ps((simd_float4&)q_, _mm_mul_ps(_mm_round_ps(_mm_mul_ps((simd_float4&)q_, _mm_rcp_ps(d)), _MM_FROUND_TO_ZERO), d)));
#else
  const float *f=(const float*)&q_;
  return simd_quatf(std::fmod(f[0], div_), std::fmod(f[1], div_), std::fmod(f[2], div_), std::fmod(f[3], div_));
#endif
}
//----

PFC_INLINE simd_quatf cycle(const simd_quatf &q_, float cycle_)
{
  // component-wise cycle
#ifdef PFC_PLATFORM_SSE4
  simd_float4 d=_mm_set1_ps(cycle_);
  return simd_quatf(_mm_sub_ps((simd_float4&)q_, _mm_mul_ps(_mm_round_ps(_mm_mul_ps((simd_float4&)q_, _mm_rcp_ps(d)), _MM_FROUND_TO_NEG_INF), d)));
#else
  const float *f=(const float*)&q_;
  float x=std::fmod(f[0], cycle_), y=std::fmod(f[1], cycle_), z=std::fmod(f[2], cycle_), w=std::fmod(f[3], cycle_);
  return simd_quatf(x<0?cycle_+x:x, y<0?cycle_+y:y, z<0?cycle_+z:z, w<0?cycle_+w:w);
#endif
}
//----

PFC_INLINE simd_quatf sat(const simd_quatf &q_)
{
  // component-wise saturate
  return simd_quatf(_mm_min_ps(_mm_max_ps((simd_float4&)q_, _mm_setzero_ps()), simd::g_one));
}
//----

PFC_INLINE simd_quatf ssat(const simd_quatf &q_)
{
  // component-wise signed saturate
  return simd_quatf(_mm_min_ps(_mm_max_ps((simd_float4&)q_, simd::g_neg_one), simd::g_one));
}
//----

PFC_INLINE simd_quatf clamp(const simd_quatf &q_, const simd_quatf &min_, const simd_quatf &max_)
{
  // component-wise clamp (to quats)
  return simd_quatf(_mm_min_ps(_mm_max_ps((simd_float4&)q_, (simd_float4&)min_), (simd_float4&)max_));
}
//----

PFC_INLINE simd_quatf clamp(const simd_quatf &q_, float min_, float max_)
{
  // component-wise clamp (to scalars)
  return simd_quatf(_mm_min_ps(_mm_max_ps((simd_float4&)q_, _mm_set1_ps(min_)), _mm_set1_ps(max_)));
}
//----

PFC_INLINE simd_quatf abs(const simd_quatf &q_)
{
  // component-wise absolute
  return simd_quatf(_mm_and_ps((simd_float4&)q_, simd::g_mask_not_sign));
}
//----

PFC_INLINE simd_quatf sgn(const simd_quatf &q_)
{
  // component-wise signum (neg=-1, pos=+1, zero=0)
  return simd_quatf(_mm_and_ps(_mm_cmpneq_ps((simd_float4&)q_, _mm_setzero_ps()), _mm_or_ps(_mm_and_ps(_mm_cmplt_ps((simd_float4&)q_, _mm_setzero_ps()), simd::g_mask_sign), simd::g_one)));
}
//----

PFC_INLINE simd_quatf sgn_zp(const simd_quatf &q_)
{
  // component-wise signum (neg=-1, pos&zero=+1)
  return simd_quatf(_mm_or_ps(_mm_and_ps(_mm_cmplt_ps((simd_float4&)q_, _mm_setzero_ps()), simd::g_mask_sign), simd::g_one));
}
//----

PFC_INLINE simd_quatf sqr(const simd_quatf &q_)
{
  // component-wise square
  return simd_quatf(_mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
}
//----

PFC_INLINE simd_quatf cubic(const simd_quatf &q_)
{
  // component-wise cubic
  return simd_quatf(_mm_mul_ps(_mm_mul_ps((simd_float4&)q_, (simd_float4&)q_), (simd_float4&)q_));
}
//----

PFC_INLINE simd_quatf sqrt(const simd_quatf &q_)
{
  // component-wise square root
  return simd_quatf(_mm_sqrt_ps((simd_float4&)q_));
}
//----

PFC_INLINE simd_quatf sqrt_z(const simd_quatf &q_)
{
  // component-wise square root (set to 0 for components less than zero)
  return simd_quatf(_mm_sqrt_ps(_mm_max_ps((simd_float4&)q_, _mm_setzero_ps())));
}
//----
/*
PFC_INLINE simd_quatf cbrt(const simd_quatf &q_)
{
  // component-wise cubic root
  return simd_quatf(q_.x<0?-std::pow(-q_.x, float(1.0/3.0)):std::pow(q_.x, float(1.0/3.0)),
                    q_.y<0?-std::pow(-q_.y, float(1.0/3.0)):std::pow(q_.y, float(1.0/3.0)),
                    q_.z<0?-std::pow(-q_.z, float(1.0/3.0)):std::pow(q_.z, float(1.0/3.0)),
                    q_.w<0?-std::pow(-q_.w, float(1.0/3.0)):std::pow(q_.w, float(1.0/3.0)));
}
//----
*/
PFC_INLINE simd_quatf rsqrt(const simd_quatf &q_)
{
  // component-wise reciprocal square root
  return simd_quatf(_mm_rsqrt_ps((simd_float4&)q_));
}
//----

PFC_INLINE simd_quatf rsqrt_z(const simd_quatf &q_)
{
  // component-wise reciprocal square root (set to 0 for components less than or equal to zero)
  return simd_quatf(_mm_and_ps(_mm_cmpgt_ps((simd_float4&)q_, _mm_setzero_ps()), _mm_rsqrt_ps((simd_float4&)q_)));
}
//----
/*
PFC_INLINE simd_quatf rcbrt(const simd_quatf &q_)
{
  // component-wise reciprocal cubic root
  return simd_quatf(q_.x<0?-std::pow(-q_.x, float(-1.0/3.0)):std::pow(q_.x, float(-1.0/3.0)),
                    q_.y<0?-std::pow(-q_.y, float(-1.0/3.0)):std::pow(q_.y, float(-1.0/3.0)),
                    q_.z<0?-std::pow(-q_.z, float(-1.0/3.0)):std::pow(q_.z, float(-1.0/3.0)),
                    q_.w<0?-std::pow(-q_.w, float(-1.0/3.0)):std::pow(q_.w, float(-1.0/3.0)));
}
//----

PFC_INLINE simd_quatf rcbrt_z(const simd_quatf &q_)
{
  // component-wise reciprocal cubic root (set to 0 for 0 component)
  return simd_quatf(q_.x?q_.x<0?-std::pow(-q_.x, float(-1.0/3.0)):std::pow(q_.x, float(-1.0/3.0)):0,
                    q_.y?q_.y<0?-std::pow(-q_.y, float(-1.0/3.0)):std::pow(q_.y, float(-1.0/3.0)):0,
                    q_.z?q_.z<0?-std::pow(-q_.z, float(-1.0/3.0)):std::pow(q_.z, float(-1.0/3.0)):0,
                    q_.w?q_.w<0?-std::pow(-q_.w, float(-1.0/3.0)):std::pow(q_.w, float(-1.0/3.0)):0);
}
//----
*/
PFC_INLINE float norm(const simd_quatf &q_)
{
  // norm of the quat (=quat length)
#ifdef PFC_PLATFORM_SSE4
  float n;
  _mm_store_ss(&n, _mm_sqrt_ss(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xf1)));
  return n;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  return sqrt(d[0]+d[1]+d[2]+d[3]);
#endif
}
//----

PFC_INLINE float rnorm(const simd_quatf &q_)
{
  // reciprocal norm of the quat
#ifdef PFC_PLATFORM_SSE4
  float rn;
  _mm_store_ss(&rn, _mm_rsqrt_ss(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xf1)));
  return rn;
#else
  float rn;
  simd_float4 v=_mm_mul_ps((simd_float4&)q_, (simd_float4&)q_);
  v=_mm_add_ps(_mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 1)), _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 2, 3)));
  _mm_store_ss(&rn, _mm_rsqrt_ss(_mm_add_ss(v, _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 1)))));
  return rn;
#endif
}
//----

PFC_INLINE float rnorm_z(const simd_quatf &q_)
{
  // reciprocal norm of the quat
#ifdef PFC_PLATFORM_SSE4
  float rn;
  simd_float4 n2=_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xf1);
  _mm_store_ss(&rn, _mm_and_ps(_mm_cmpgt_ss(n2, _mm_setzero_ps()), _mm_rsqrt_ss(n2)));
  return rn;
#else
  float rn;
  simd_float4 q=_mm_mul_ps((simd_float4&)q_, (simd_float4&)q_);
  q=_mm_add_ps(_mm_shuffle_ps(q, q, _MM_SHUFFLE(0, 0, 0, 1)), _mm_shuffle_ps(q, q, _MM_SHUFFLE(0, 0, 2, 3)));
  q=_mm_add_ss(q, _mm_shuffle_ps(q, q, _MM_SHUFFLE(0, 0, 0, 1)));
  _mm_store_ss(&rn, _mm_and_ps(_mm_cmpgt_ss(q, _mm_setzero_ps()), _mm_rsqrt_ss(q)));
  return rn;
#endif
}
//----

PFC_INLINE float norm2(const simd_quatf &q_)
{
  // squared norm of the quat
#ifdef PFC_PLATFORM_SSE4
  float n2;
  _mm_store_ss(&n2, _mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xf1));
  return n2;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  return d[0]+d[1]+d[2]+d[3];
#endif
}
//----

PFC_INLINE float rnorm2(const simd_quatf &q_)
{
  // reciprocal squared norm of the quat
#ifdef PFC_PLATFORM_SSE4
  float rn2;
  _mm_store_ss(&rn2, _mm_rcp_ss(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xf1)));
  return rn2;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  return rcp(d[0]+d[1]+d[2]+d[3]);
#endif
}
//----

PFC_INLINE float rnorm2_z(const simd_quatf &q_)
{
  // reciprocal squared norm of the quat
#ifdef PFC_PLATFORM_SSE4
  float rn2;
  simd_float4 n2=_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xf1);
  _mm_store_ss(&rn2, _mm_and_ps(_mm_cmpgt_ss(n2, _mm_setzero_ps()), _mm_rcp_ss(n2)));
  return rn2;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  return rcp_z(d[0]+d[1]+d[2]+d[3]);
#endif
}
//----

PFC_INLINE simd_quatf unit(const simd_quatf &q_)
{
  // unit quat of the quat
#ifdef PFC_PLATFORM_SSE4
  return simd_vec4f(_mm_mul_ps((simd_float4&)q_, _mm_rsqrt_ps(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xff))));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  float x=d[0]+d[1]+d[2]+d[3];
  simd_float4 v=_mm_rsqrt_ss(_mm_load_ss(&x));
  return simd_quatf(_mm_mul_ps(_mm_shuffle_ps(v, v, 0), (simd_float4&)q_));
#endif
}
//----

PFC_INLINE simd_quatf unit_z(const simd_quatf &q_)
{
  // unit of the quat. if |q|=0, return q=[v=0, w=1]
#ifdef PFC_PLATFORM_SSE4
  simd_float4 n2=_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xff);
  simd_float4 c=_mm_cmpgt_ps(n2, _mm_setzero_ps());
  return simd_vec4f(_mm_or_ps(_mm_and_ps(c, _mm_mul_ps((simd_float4&)q_, _mm_rsqrt_ps(n2))), _mm_andnot_ps(c, simd::g_ident_w)));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  float x=d[0]+d[1]+d[2]+d[3];
  simd_float4 v=_mm_rsqrt_ss(_mm_load_ss(&x));
  return simd_quatf(x?_mm_mul_ps(_mm_shuffle_ps(v, v, 0), (simd_float4&)q_):simd::g_ident_w);
#endif
}
//----

PFC_INLINE float dot(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // dot-product of quats
#ifdef PFC_PLATFORM_SSE4
  float d;
  _mm_store_ss(&d, _mm_dp_ps((simd_float4&)q0_, (simd_float4&)q1_, 0xf1));
  return d;
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q0_, (simd_float4&)q1_));
  return d[0]+d[1]+d[2]+d[3];
#endif
}
//----

PFC_INLINE float dot1(const simd_quatf &q_)
{
  // dot-product with [1, 1, 1, 1]
/*#ifdef PFC_PLATFORM_SSE4
  float d;
  _mm_store_ss(&d, _mm_dp_ps((simd_float4&)q_, simd::g_one, 0xf1));
  return d;
#else*/
  return q_.x+q_.y+q_.z+q_.w;
/*#endif*/
}
//----

PFC_INLINE simd_quatf cross(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // cross-product of quats: cross(q0, q1)=[v0 x v1, 0]
  simd_float4 v=_mm_sub_ps(_mm_mul_ps((simd_float4&)q0_, _mm_shuffle_ps((simd_float4&)q1_, (simd_float4&)q1_, _MM_SHUFFLE(3, 0, 2, 1))),
                           _mm_mul_ps((simd_float4&)q1_, _mm_shuffle_ps((simd_float4&)q0_, (simd_float4&)q0_, _MM_SHUFFLE(3, 0, 2, 1))));
  return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1));
}
//----

PFC_INLINE simd_quatf outer(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // outer-product of quats: outer(q0, q1)=[w0*v1-w1*v0-(v0 x v1), 0]
  simd_float4 v=_mm_sub_ps(_mm_mul_ps((simd_float4&)q0_, _mm_shuffle_ps((simd_float4&)q1_, (simd_float4&)q1_, _MM_SHUFFLE(3, 0, 2, 1))),
                           _mm_mul_ps((simd_float4&)q1_, _mm_shuffle_ps((simd_float4&)q0_, (simd_float4&)q0_, _MM_SHUFFLE(3, 0, 2, 1))));
  v=_mm_sub_ps(_mm_sub_ps(_mm_mul_ps((simd_float4&)q1_, _mm_shuffle_ps((simd_float4&)q0_, (simd_float4&)q0_, _MM_SHUFFLE(3, 3, 3, 3))),
                          _mm_mul_ps((simd_float4&)q0_, _mm_shuffle_ps((simd_float4&)q1_, (simd_float4&)q1_, _MM_SHUFFLE(3, 3, 3, 3)))),
               _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1)));
  return simd_quatf(_mm_and_ps(v, simd::g_mask_xyz));
}
//----

PFC_INLINE simd_quatf even(const simd_quatf &q0_, const simd_quatf &q1_)
{
  // even-product of quats: even(q0, q1)=[w0*v1+w1*v0, w0*w1-dot(v0, v1)]
  simd_float4 v=_mm_add_ps(_mm_mul_ps((simd_float4&)q1_, _mm_shuffle_ps((simd_float4&)q0_, (simd_float4&)q0_, _MM_SHUFFLE(3, 3, 3, 3))),
                           _mm_mul_ps((simd_float4&)q0_, _mm_shuffle_ps((simd_float4&)q1_, (simd_float4&)q1_, _MM_SHUFFLE(3, 3, 3, 3))));
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_sub_ps(v, _mm_dp_ps((simd_float4&)q0_, (simd_float4&)q1_, 0xf8)));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q0_, (simd_float4&)q1_));
  PFC_ALIGN(16) float32_t d2[4]={0.0f, 0.0f, 0.0f, d[0]+d[1]+d[2]+d[3]};
  return simd_quatf(_mm_sub_ps(v, (simd_float4&)*d2));
#endif
}
//----

PFC_INLINE simd_quatf conj(const simd_quatf &q_)
{
  // conjugate of the quat
  return simd_quatf(_mm_mul_ps((simd_float4&)q_, simd::g_neg_xyz));
}
//----

PFC_INLINE simd_quatf inv(const simd_quatf &q_)
{
  // inverse of the quat
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_mul_ps(_mm_mul_ps((simd_float4&)q_, simd::g_neg_xyz), _mm_rcp_ps(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xff))));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  return simd_quatf(_mm_mul_ps(_mm_mul_ps((simd_float4&)q_, simd::g_neg_xyz), _mm_rcp_ps(_mm_set1_ps(d[0]+d[1]+d[2]+d[3]))));
#endif
}
//----

PFC_INLINE simd_quatf inv_u(const simd_quatf &q_)
{
  // inverse of the unit-quat
  return simd_quatf(_mm_mul_ps((simd_float4&)q_, simd::g_neg_xyz));
}
//----

PFC_INLINE simd_quatf exp(const simd_quatf &q_)
{
  // quat natural exponent: exp(w)*[sin(|v|)*v/|v|, cos(|v|)]
#ifdef PFC_PLATFORM_SSE4
  float vn, rvn;
  simd_float4 rvnv=_mm_rsqrt_ss(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0x71));
  _mm_store_ss(&rvn, rvnv);
  _mm_store_ss(&vn, _mm_rcp_ss(rvnv));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  float vn=sqrt(d[0]+d[1]+d[2]), rvn=1.0f/vn;
#endif
  float s, c;
  sincos(s, c, vn);
  float ew=exp(q_.w);
  float vf=ew*s*rvn;
  return simd_quatf(q_.x*vf, q_.y*vf, q_.z*vf, ew*c);
}
//----
/*
PFC_INLINE simd_quatf exp_u(const simd_quatf &q_)
{
  // unit quat natural exponent: exp(w)*[sin(|v|)*v/|v|, cos(|v|)]
  float vn=sqrt(1.0f-q_.w*q_.w);
  float s, c;
  sincos(s, c, vn);
  float ew=exp(q_.w);
  float vf=ew*s*rcp(vn);
  return simd_quatf(q_.x*vf, q_.y*vf, q_.z*vf, ew*c);
}
//----
*/
PFC_INLINE simd_quatf ln(const simd_quatf &q_)
{
  // quat natural logarithm: [acos(w/|q|)*v/|v|, ln(|q|)]
#ifdef PFC_PLATFORM_SSE4
  float rvn, rqn;
  _mm_store_ss(&rvn, _mm_rsqrt_ss(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0x71)));
  _mm_store_ss(&rqn, _mm_rsqrt_ss(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xf1)));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  float vn2=d[0]+d[1]+d[2];
  float rvn=rsqrt(vn2), rqn=rsqrt(vn2+d[3]);
#endif
  float vf=rvn*acos(q_.w*rqn);
  return simd_quatf(q_.x*vf, q_.y*vf, q_.z*vf, -ln(rqn));
}
//----

PFC_INLINE simd_quatf ln_u(const simd_quatf &q_)
{
  // unit quat natural logarithm: [acos(w)*v/|v|, 0]
#ifdef PFC_PLATFORM_SSE4
  float rvn;
  _mm_store_ss(&rvn, _mm_rsqrt_ss(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0x71)));
  float vf=rvn*acos(q_.w);
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  float vf=rsqrt(d[0]+d[1]+d[2])*acos(q_.w);
#endif
  return simd_quatf(q_.x*vf, q_.y*vf, q_.z*vf, 0);
}
//----

PFC_INLINE simd_quatf pow(const simd_quatf &q_, float s_)
{
  // quat power: exp(ln(q)*s_)
#ifdef PFC_PLATFORM_SSE4
  float rvn, rqn, qn;
  _mm_store_ss(&rvn, _mm_rsqrt_ss(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0x71)));
  simd_float4 rqn_v=_mm_rsqrt_ss(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xf1));
  _mm_store_ss(&rqn, rqn_v);
  _mm_store_ss(&qn, _mm_rcp_ss(rqn_v));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  float vn2=d[0]+d[1]+d[2], rvn=rsqrt(vn2);
  float qn=sqrt(vn2+d[3]), rqn=1.0f/qn;
#endif
  float s, c;
  sincos(s, c, acos(q_.w*rqn)*s_);
  float ew=pow(qn, s_);
  float vf=ew*s*rvn;
  return simd_quatf(q_.x*vf, q_.y*vf, q_.z*vf, ew*c);
}
//----
/*
PFC_INLINE simd_quatf pow_u(const simd_quatf &q_, float s_)
{
  // unit quat power: exp(ln_u(q)*s_)
  float s, c;
  float vn=s_*acos(q_.w);
  sincos(s, c, vn);
  float vf=s*rcp(vn);
  return simd_quatf(q_.x*vf, q_.y*vf, q_.z*vf, c);
}
//----
*/
PFC_INLINE float arg(const simd_quatf &q_)
{
  // argument of the quat
#ifdef PFC_PLATFORM_SSE4
  float rn;
  _mm_store_ss(&rn, _mm_rsqrt_ss(_mm_dp_ps((simd_float4&)q_, (simd_float4&)q_, 0xf1)));
  return acos(q_.w*rn);
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q_, (simd_float4&)q_));
  return acos(q_.w*rsqrt(d[0]+d[1]+d[2]+d[3]));
#endif
}
//----
/*
PFC_INLINE float arg_u(const simd_quatf &q_)
{
  // argument of the unit quat
  return acos(q_.w);
}
//----
*/
PFC_INLINE void neg(simd_quatf &q_)
{
  // negate the quat
  (simd_float4&)q_=_mm_sub_ps(_mm_setzero_ps(), (simd_float4&)q_);
}
//----

PFC_INLINE simd_quatf lerp(const simd_quatf &q0_, const simd_quatf &q1_, float t_)
{
  // linear quat interpolation. f(t=0)=q0, f(t=1)=q1
  return simd_quatf(_mm_add_ps((simd_float4&)q0_, _mm_mul_ps(_mm_sub_ps((simd_float4&)q1_, (simd_float4&)q0_), _mm_set1_ps(t_))));
}
//----

PFC_INLINE simd_quatf nlerp(const simd_quatf &q0_, const simd_quatf &q1_, float t_)
{
  // normalized linear quat interpolation. f(t=0)=q0/|q0|, f(t=1)=q1/|q1|
  simd_float4 v=_mm_add_ps((simd_float4&)q0_, _mm_mul_ps(_mm_sub_ps((simd_float4&)q1_, (simd_float4&)q0_), _mm_set1_ps(t_)));
#ifdef PFC_PLATFORM_SSE4
  return simd_quatf(_mm_mul_ps(v, _mm_rsqrt_ps(_mm_dp_ps(v, v, 0xff))));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps(v, v));
  return simd_quatf(_mm_mul_ps(v, _mm_rsqrt_ps(_mm_set1_ps(d[0]+d[1]+d[2]))));
#endif
}
//----

PFC_INLINE simd_quatf nlerp_z(const simd_quatf &q0_, const simd_quatf &q1_, float t_)
{
  // normalized linear quat interpolation. f(t=0)=q0/|q0|, f(t=1)=q1/|q1|. if interpolated |q|=0, return [0, 0, 0, 1]
  simd_float4 v=_mm_add_ps((simd_float4&)q0_, _mm_mul_ps(_mm_sub_ps((simd_float4&)q1_, (simd_float4&)q0_), _mm_set1_ps(t_)));
#ifdef PFC_PLATFORM_SSE4
  simd_float4 n2=_mm_dp_ps(v, v, 0xff);
  simd_float4 c=_mm_cmpgt_ps(n2, _mm_setzero_ps());
  return simd_vec4f(_mm_or_ps(_mm_and_ps(c, _mm_mul_ps(v, _mm_rsqrt_ps(n2))), _mm_andnot_ps(c, simd::g_ident_w)));
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps(v, v));
  float d2=d[0]+d[1]+d[2];
  return simd_quatf(d2?_mm_mul_ps(v, _mm_rsqrt_ps(_mm_set1_ps(d2))):simd::g_ident_w);
#endif
}
//----

PFC_INLINE simd_quatf slerp(const simd_quatf &q0_, const simd_quatf &q1_, float t_)
{
  // spherical linear quat interpolation. f(t=0)=q0, f(t=1)=q1
#ifdef PFC_PLATFORM_SSE4
  float d;
  _mm_store_ss(&d, _mm_dp_ps((simd_float4&)q0_, (simd_float4&)q1_, 0xf1));
  float a=acos(d);
#else
  PFC_ALIGN(16) float32_t d[4];
  _mm_store_ps(d, _mm_mul_ps((simd_float4&)q0_, (simd_float4&)q1_));
  float a=acos(d[0]+d[1]+d[2]+d[3]);
#endif
  float rs=csc(a);
  return simd_quatf(_mm_add_ps(_mm_mul_ps((simd_float4&)q0_, _mm_set1_ps(sin((1.0f-t_)*a)*rs)),
                               _mm_mul_ps((simd_float4&)q1_, _mm_set1_ps(sin(t_*a)*rs))));
}
//----

PFC_INLINE simd_quatf rot_u(const simd_vec3f &src_, const simd_vec3f &dst_)
{
  // generate rotation from source to destination direction
  simd_vec3f v=unit_z(simd_vec3f(_mm_add_ps((simd_float4&)src_, (simd_float4&)dst_)));
  return simd_quatf(cross(v, dst_), dot(v, dst_));
}
//----

PFC_INLINE simd_quatf zrot_u(const simd_vec3f &dst_)
{
  // generate rotation from z-axis to destination direction
  simd_vec3f v=unit_z(simd_vec3f(_mm_add_ps((simd_float4&)dst_, simd::g_ident_z)));
  if(is_zero(v))
    v=simd::g_ident_x;
  return simd_quatf(cross(v, dst_), dot(v, dst_));
}
//----
/*
PFC_INLINE simd_quatf axis_rot_u(const simd_vec3f &axis_, float angle_)
{
  // generate rotation from unit axis and angle (radians)
  float s, c;
  sincos(s, c, angle_*0.5f);
  return simd_quatf(axis_*s, c);
}
//----

PFC_INLINE void convert_u(simd_mat33f &m_, const simd_quatf &q_)
{
  // convert the unit quat to 3x3 row major rotation matrix
  float xs=q_.x+q_.x;
  float ys=q_.y+q_.y;
  float zs=q_.z+q_.z;
  float xx=q_.x*xs;
  float yy=q_.y*ys;
  float zz=q_.z*zs;
  m_.x.x=1.0f-yy-zz;
  m_.y.y=1.0f-xx-zz;
  m_.z.z=1.0f-xx-yy;
  float xy=q_.x*ys;
  float wz=q_.w*zs;
  m_.x.y=xy+wz;
  m_.y.x=xy-wz;
  float xz=q_.x*zs;
  float wy=q_.w*ys;
  m_.x.z=xz-wy;
  m_.z.x=xz+wy;
  float yz=q_.y*zs;
  float wx=q_.w*xs;
  m_.y.z=yz+wx;
  m_.z.y=yz-wx;
}
//----

PFC_INLINE void convert(simd_mat33f &m_, const simd_quatf &q_)
{
  // convert the quat to 3x3 row major rotation matrix
  float s=rnorm2(q_);
  s+=s;
  float xs=q_.x*s;
  float ys=q_.y*s;
  float zs=q_.z*s;
  float xx=q_.x*xs;
  float yy=q_.y*ys;
  float zz=q_.z*zs;
  m_.x.x=1.0f-yy-zz;
  m_.y.y=1.0f-xx-zz;
  m_.z.z=1.0f-xx-yy;
  float xy=q_.x*ys;
  float wz=q_.w*zs;
  m_.x.y=xy+wz;
  m_.y.x=xy-wz;
  float xz=q_.x*zs;
  float wy=q_.w*ys;
  m_.x.z=xz-wy;
  m_.z.x=xz+wy;
  float yz=q_.y*zs;
  float wx=q_.w*xs;
  m_.y.z=yz+wx;
  m_.z.y=yz-wx;
}
//----

PFC_INLINE void convert(simd_quatf &q_, const simd_mat33f &m_)
{
  // check for positive matrix trace
  PFC_ASSERT_PEDANTIC_MSG(abs(det(m_)-1.0f)<0.01f, ("Matrix determinant must be 1 for quaternion conversion\r\n"));
  float tr=m_.x.x+m_.y.y+m_.z.z;
  if(tr>0)
  {
    float s=sqrt(tr+1.0f);
    q_.w=s*0.5f;
    s=0.5f/s;
    q_.x=(m_.y.z-m_.z.y)*s;
    q_.y=(m_.z.x-m_.x.z)*s;
    q_.z=(m_.x.y-m_.y.x)*s;
  }
  else
  {
    // find largest diagonal value and setup element indices
    unsigned i=m_.y.y>m_.x.x?1:0;
    if(m_.z.z>m_[i][i])
      i=2;
    const unsigned next[3]={1, 2, 0};
    unsigned j=next[i], k=next[j];

    // convert the matrix
    float s=sqrt(m_[i][i]-m_[j][j]-m_[k][k]+1.0f);
    q_[i]=s*0.5f;
    s=0.5f/s;
    q_.w=(m_[j][k]-m_[k][j])*s;
    q_[j]=(m_[i][j]+m_[j][i])*s;
    q_[k]=(m_[i][k]+m_[k][i])*s;
  }
}
//----
*/
template<>
PFC_INLINE quati to_quat<int>(const simd_quatf &q_)
{
  // convert to quati
  PFC_ALIGN(16) int32_t d[4];
  _mm_store_si128((__m128i*)d, _mm_cvttps_epi32((simd_float4&)q_));
  return quati(d[0], d[1], d[2], d[3]);
}
//----

template<>
PFC_INLINE simd_quatf to_quat<simd_float4>(const quati &q_)
{
  // convert to simd_quatf
  return simd_quatf(_mm_cvtepi32_ps(_mm_set_epi32(q_.w, q_.z, q_.y, q_.x)));
}
//----------------------------------------------------------------------------
