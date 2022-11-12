//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


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
  x=s_;
  y=s_;
  z=s_;
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
  x=v_.x;
  y=v_.y;
  z=v_.z;
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
  x=a_[0];
  y=a_[1];
  z=a_[2];
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
  x=s_;
  y=s_;
  z=s_;
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
  x=v_.x;
  y=v_.y;
  z=v_.z;
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
  x=a_[0];
  y=a_[1];
  z=a_[2];
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
  x=s_;
  y=s_;
  z=s_;
  w=s_;
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
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=v_.w;
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
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
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
  x=s_;
  y=s_;
  z=s_;
  w=s_;
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
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=v_.w;
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
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
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
  x.x=s_; x.y=s_; x.z=s_;
  y.x=s_; y.y=s_; y.z=s_;
  z.x=s_; z.y=s_; z.z=s_;
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
  x.x=a_[0]; x.y=a_[1]; x.z=a_[2];
  y.x=a_[3]; y.y=a_[4]; y.z=a_[5];
  z.x=a_[6]; z.y=a_[7]; z.z=a_[8];
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
  x.x=s_; x.y=s_; x.z=s_;
  y.x=s_; y.y=s_; y.z=s_;
  z.x=s_; z.y=s_; z.z=s_;
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
  x.x=a_[0]; x.y=a_[1]; x.z=a_[2];
  y.x=a_[3]; y.y=a_[4]; y.z=a_[5];
  z.x=a_[6]; z.y=a_[7]; z.z=a_[8];
}
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
  x.x=s_; x.y=s_; x.z=s_; x.w=s_;
  y.x=s_; y.y=s_; y.z=s_; y.w=s_;
  z.x=s_; z.y=s_; z.z=s_; z.w=s_;
  w.x=s_; w.y=s_; w.z=s_; w.w=s_;
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
  x.x=a_[0];  x.y=a_[1];  x.z=a_[2];  x.w=a_[3];
  y.x=a_[4];  y.y=a_[5];  y.z=a_[6];  y.w=a_[7];
  z.x=a_[8];  z.y=a_[9];  z.z=a_[10]; z.w=a_[11];
  w.x=a_[12]; w.y=a_[13]; w.z=a_[14]; w.w=a_[15];
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
  x.x=s_; x.y=s_; x.z=s_; x.w=s_;
  y.x=s_; y.y=s_; y.z=s_; y.w=s_;
  z.x=s_; z.y=s_; z.z=s_; z.w=s_;
  w.x=s_; w.y=s_; w.z=s_; w.w=s_;
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
  x.x=a_[0];  x.y=a_[1];  x.z=a_[2];  x.w=a_[3];
  y.x=a_[4];  y.y=a_[5];  y.z=a_[6];  y.w=a_[7];
  z.x=a_[8];  z.y=a_[9];  z.z=a_[10]; z.w=a_[11];
  w.x=a_[12]; w.y=a_[13]; w.z=a_[14]; w.w=a_[15];
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
  x=s_;
  y=s_;
  z=s_;
  w=s_;
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
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=v_.w;
}
//----

simd_quatf::quat(const quatf &q_)
{
  // init quat with fp-quat
  x=q_.x;
  y=q_.y;
  z=q_.z;
  w=q_.w;
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
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
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
  x=s_;
  y=s_;
  z=s_;
  w=s_;
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
  x=v_.x;
  y=v_.y;
  z=v_.z;
  w=v_.w;
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
  x=q_.x;
  y=q_.y;
  z=q_.z;
  w=q_.w;
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
  x=a_[0];
  y=a_[1];
  z=a_[2];
  w=a_[3];
}
//----------------------------------------------------------------------------
