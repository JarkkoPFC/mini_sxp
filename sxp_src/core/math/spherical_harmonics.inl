//==========================================7==================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// shvec2 ops
//============================================================================
template<typename T>
PFC_INLINE void operator+=(shvec2<T> &shvr_, const shvec2<T> &shv_)
{
  shvr_.coeffs[0]+=shv_.coeffs[0];
  shvr_.coeffs[1]+=shv_.coeffs[1];
  shvr_.coeffs[2]+=shv_.coeffs[2];
  shvr_.coeffs[3]+=shv_.coeffs[3];
}
//----

template<typename T>
PFC_INLINE void operator+=(shvec2<T> &shvr_, T v_)
{
  shvr_.coeffs[0]+=v_;
  shvr_.coeffs[1]+=v_;
  shvr_.coeffs[2]+=v_;
  shvr_.coeffs[3]+=v_;
}
//----

template<typename T>
PFC_INLINE void operator-=(shvec2<T> &shvr_, const shvec2<T> &shv_)
{
  shvr_.coeffs[0]-=shv_.coeffs[0];
  shvr_.coeffs[1]-=shv_.coeffs[1];
  shvr_.coeffs[2]-=shv_.coeffs[2];
  shvr_.coeffs[3]-=shv_.coeffs[3];
}
//----

template<typename T>
PFC_INLINE void operator-=(shvec2<T> &shvr_, T v_)
{
  shvr_.coeffs[0]-=v_;
  shvr_.coeffs[1]-=v_;
  shvr_.coeffs[2]-=v_;
  shvr_.coeffs[3]-=v_;
}
//----

template<typename T>
PFC_INLINE void operator*=(shvec2<T> &shvr_, const shvec2<T> &shv_)
{
  shvr_.coeffs[0]*=shv_.coeffs[0];
  shvr_.coeffs[1]*=shv_.coeffs[1];
  shvr_.coeffs[2]*=shv_.coeffs[2];
  shvr_.coeffs[3]*=shv_.coeffs[3];
}
//----

template<typename T>
PFC_INLINE void operator*=(shvec2<T> &shvr_, T v_)
{
  shvr_.coeffs[0]*=v_;
  shvr_.coeffs[1]*=v_;
  shvr_.coeffs[2]*=v_;
  shvr_.coeffs[3]*=v_;
}
//----

template<typename T>
PFC_INLINE void operator*=(shvec2<T> &shvr_, const shmat2<T> &shm_)
{
  shvec2<T> shv=shvr_;
  shvr_.coeffs[0]=shv.coeffs[0]*shm_.m[0][0]+shv.coeffs[1]*shm_.m[1][0]+shv.coeffs[2]*shm_.m[2][0]+shv.coeffs[3]*shm_.m[3][0];
  shvr_.coeffs[1]=shv.coeffs[0]*shm_.m[0][1]+shv.coeffs[1]*shm_.m[1][1]+shv.coeffs[2]*shm_.m[2][1]+shv.coeffs[3]*shm_.m[3][1];
  shvr_.coeffs[2]=shv.coeffs[0]*shm_.m[0][2]+shv.coeffs[1]*shm_.m[1][2]+shv.coeffs[2]*shm_.m[2][2]+shv.coeffs[3]*shm_.m[3][2];
  shvr_.coeffs[3]=shv.coeffs[0]*shm_.m[0][3]+shv.coeffs[1]*shm_.m[1][3]+shv.coeffs[2]*shm_.m[2][3]+shv.coeffs[3]*shm_.m[3][3];
}
//----

template<typename T>
PFC_INLINE void operator/=(shvec2<T> &shvr_, const shvec2<T> &shv_)
{
  shvr_.coeffs[0]/=shv_.coeffs[0];
  shvr_.coeffs[1]/=shv_.coeffs[1];
  shvr_.coeffs[2]/=shv_.coeffs[2];
  shvr_.coeffs[3]/=shv_.coeffs[3];
}
//----

template<typename T>
PFC_INLINE void operator/=(shvec2<T> &shvr_, T v_)
{
  T rcp_v=rcp(v_);
  shvr_.coeffs[0]*=rcp_v;
  shvr_.coeffs[1]*=rcp_v;
  shvr_.coeffs[2]*=rcp_v;
  shvr_.coeffs[3]*=rcp_v;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator+(const shvec2<T> &shv0_, const shvec2<T> &shv1_)
{
  shvec2<T> res=
  {
    shv0_.coeffs[0]+shv1_.coeffs[0],
    shv0_.coeffs[1]+shv1_.coeffs[1],
    shv0_.coeffs[2]+shv1_.coeffs[2],
    shv0_.coeffs[3]+shv1_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator+(const shvec2<T> &shv_, T v_)
{
  shvec2<T> res=
  {
    shv_.coeffs[0]+v_,
    shv_.coeffs[1]+v_,
    shv_.coeffs[2]+v_,
    shv_.coeffs[3]+v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator+(T v_, const shvec2<T> &shv_)
{
  shvec2<T> res=
  {
    v_+shv_.coeffs[0],
    v_+shv_.coeffs[1],
    v_+shv_.coeffs[2],
    v_+shv_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator-(const shvec2<T> &shv0_, const shvec2<T> &shv1_)
{
  shvec2<T> res=
  {
    shv0_.coeffs[0]-shv1_.coeffs[0],
    shv0_.coeffs[1]-shv1_.coeffs[1],
    shv0_.coeffs[2]-shv1_.coeffs[2],
    shv0_.coeffs[3]-shv1_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator-(const shvec2<T> &shv_, T v_)
{
  shvec2<T> res=
  {
    shv_.coeffs[0]-v_,
    shv_.coeffs[1]-v_,
    shv_.coeffs[2]-v_,
    shv_.coeffs[3]-v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator-(T v_, const shvec2<T> &shv_)
{
  shvec2<T> res=
  {
    v_-shv_.coeffs[0],
    v_-shv_.coeffs[1],
    v_-shv_.coeffs[2],
    v_-shv_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator*(const shvec2<T> &shv0_, const shvec2<T> &shv1_)
{
  shvec2<T> res=
  {
    shv0_.coeffs[0]*shv1_.coeffs[0],
    shv0_.coeffs[1]*shv1_.coeffs[1],
    shv0_.coeffs[2]*shv1_.coeffs[2],
    shv0_.coeffs[3]*shv1_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator*(const shvec2<T> &shv_, T v_)
{
  shvec2<T> res=
  {
    shv_.coeffs[0]*v_,
    shv_.coeffs[1]*v_,
    shv_.coeffs[2]*v_,
    shv_.coeffs[3]*v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator*(T v_, const shvec2<T> &shv_)
{
  shvec2<T> res=
  {
    v_*shv_.coeffs[0],
    v_*shv_.coeffs[1],
    v_*shv_.coeffs[2],
    v_*shv_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator*(const shvec2<T> &shv_, const shmat2<T> &shm_)
{
  shvec2<T> res=
  {
    shv_.coeffs[0]*shm_.m[0][0]+shv_.coeffs[1]*shm_.m[1][0]+shv_.coeffs[2]*shm_.m[2][0]+shv_.coeffs[3]*shm_.m[3][0],
    shv_.coeffs[0]*shm_.m[0][1]+shv_.coeffs[1]*shm_.m[1][1]+shv_.coeffs[2]*shm_.m[2][1]+shv_.coeffs[3]*shm_.m[3][1],
    shv_.coeffs[0]*shm_.m[0][2]+shv_.coeffs[1]*shm_.m[1][2]+shv_.coeffs[2]*shm_.m[2][2]+shv_.coeffs[3]*shm_.m[3][2],
    shv_.coeffs[0]*shm_.m[0][3]+shv_.coeffs[1]*shm_.m[1][3]+shv_.coeffs[2]*shm_.m[2][3]+shv_.coeffs[3]*shm_.m[3][3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator*(const shmat2<T> &shm_, const shvec2<T> &shv_)
{
  shvec2<T> res=
  {
    shv_.coeffs[0]*shm_.m[0][0]+shv_.coeffs[1]*shm_.m[0][1]+shv_.coeffs[2]*shm_.m[0][2]+shv_.coeffs[3]*shm_.m[0][3],
    shv_.coeffs[0]*shm_.m[1][0]+shv_.coeffs[1]*shm_.m[1][1]+shv_.coeffs[2]*shm_.m[1][2]+shv_.coeffs[3]*shm_.m[1][3],
    shv_.coeffs[0]*shm_.m[2][0]+shv_.coeffs[1]*shm_.m[2][1]+shv_.coeffs[2]*shm_.m[2][2]+shv_.coeffs[3]*shm_.m[2][3],
    shv_.coeffs[0]*shm_.m[3][0]+shv_.coeffs[1]*shm_.m[3][1]+shv_.coeffs[2]*shm_.m[3][2]+shv_.coeffs[3]*shm_.m[3][3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator/(const shvec2<T> &shv0_, const shvec2<T> &shv1_)
{
  shvec2<T> res=
  {
    shv0_.coeffs[0]/shv1_.coeffs[0],
    shv0_.coeffs[1]/shv1_.coeffs[1],
    shv0_.coeffs[2]/shv1_.coeffs[2],
    shv0_.coeffs[3]/shv1_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator/(const shvec2<T> &shv_, T v_)
{
  T rcp_v=rcp(v_);
  shvec2<T> res=
  {
    shv_.coeffs[0]*rcp_v,
    shv_.coeffs[1]*rcp_v,
    shv_.coeffs[2]*rcp_v,
    shv_.coeffs[3]*rcp_v
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> operator/(T v_, const shvec2<T> &shv_)
{
  shvec2<T> res=
  {
    v_/shv_.coeffs[0],
    v_/shv_.coeffs[1],
    v_/shv_.coeffs[2],
    v_/shv_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE T sh_dot(const shvec2<T> &shv0_, const shvec2<T> &shv1_)
{
  return  shv0_.coeffs[0]*shv1_.coeffs[0]
         +shv0_.coeffs[1]*shv1_.coeffs[1]
         +shv0_.coeffs[2]*shv1_.coeffs[2]
         +shv0_.coeffs[3]*shv1_.coeffs[3];
}
//----

template<typename T>
PFC_INLINE void sh_dir(shvec2<T> &shv_, const vec3<T> &dir_)
{
  typedef math<T>::scalar_t scalar_t;
  static const scalar_t s_c0=scalar_t(0.28209479177387814347403972578039); // 0.5*sqrt(1/pi)
  static const scalar_t s_c1=scalar_t(0.48860251190291992158638462283835); // 0.5*sqrt(3/pi)
  shv_.coeffs[0]=s_c0;
  shv_.coeffs[1]=s_c1*dir.y;
  shv_.coeffs[2]=s_c1*dir.z;
  shv_.coeffs[3]=s_c1*dir.x;
}
//----

template<typename T, typename U>
shvec2<T> sh_product(const shvec2<T> &shv0_, const shvec2<U> &shv1_)
{
  // calculate product of two SH2 vectors (14 muls + 6 adds)
  static const U s_scale=math<U>::quarter_rpi;
  shvec2<T> res=
  {
    s_scale*(shv1_.coeffs[0]*shv0_.coeffs[0]+shv1_.coeffs[1]*shv0_.coeffs[1]+shv1_.coeffs[2]*shv0_.coeffs[2]+shv1_.coeffs[3]*shv0_.coeffs[3]),
    s_scale*(shv1_.coeffs[1]*shv0_.coeffs[0]+shv1_.coeffs[0]*shv0_.coeffs[1]),
    s_scale*(shv1_.coeffs[2]*shv0_.coeffs[0]+shv1_.coeffs[0]*shv0_.coeffs[2]),
    s_scale*(shv1_.coeffs[3]*shv0_.coeffs[0]+shv1_.coeffs[0]*shv0_.coeffs[3])
  };
  return res;
}
//----------------------------------------------------------------------------


//============================================================================
// shvec3 ops
//============================================================================
template<typename T>
PFC_INLINE void operator+=(shvec3<T> &shvr_, const shvec3<T> &shv_)
{
  shvr_.coeffs[0]+=shv_.coeffs[0];
  shvr_.coeffs[1]+=shv_.coeffs[1];
  shvr_.coeffs[2]+=shv_.coeffs[2];
  shvr_.coeffs[3]+=shv_.coeffs[3];
  shvr_.coeffs[4]+=shv_.coeffs[4];
  shvr_.coeffs[5]+=shv_.coeffs[5];
  shvr_.coeffs[6]+=shv_.coeffs[6];
  shvr_.coeffs[7]+=shv_.coeffs[7];
  shvr_.coeffs[8]+=shv_.coeffs[8];
}
//----

template<typename T>
PFC_INLINE void operator+=(shvec3<T> &shvr_, T v_)
{
  shvr_.coeffs[0]+=v_;
  shvr_.coeffs[1]+=v_;
  shvr_.coeffs[2]+=v_;
  shvr_.coeffs[3]+=v_;
  shvr_.coeffs[4]+=v_;
  shvr_.coeffs[5]+=v_;
  shvr_.coeffs[6]+=v_;
  shvr_.coeffs[7]+=v_;
  shvr_.coeffs[8]+=v_;
}
//----

template<typename T>
PFC_INLINE void operator-=(shvec3<T> &shvr_, const shvec3<T> &shv_)
{
  shvr_.coeffs[0]-=shv_.coeffs[0];
  shvr_.coeffs[1]-=shv_.coeffs[1];
  shvr_.coeffs[2]-=shv_.coeffs[2];
  shvr_.coeffs[3]-=shv_.coeffs[3];
  shvr_.coeffs[4]-=shv_.coeffs[4];
  shvr_.coeffs[5]-=shv_.coeffs[5];
  shvr_.coeffs[6]-=shv_.coeffs[6];
  shvr_.coeffs[7]-=shv_.coeffs[7];
  shvr_.coeffs[8]-=shv_.coeffs[8];
}
//----

template<typename T>
PFC_INLINE void operator-=(shvec3<T> &shvr_, T v_)
{
  shvr_.coeffs[0]-=v_;
  shvr_.coeffs[1]-=v_;
  shvr_.coeffs[2]-=v_;
  shvr_.coeffs[3]-=v_;
  shvr_.coeffs[4]-=v_;
  shvr_.coeffs[5]-=v_;
  shvr_.coeffs[6]-=v_;
  shvr_.coeffs[7]-=v_;
  shvr_.coeffs[8]-=v_;
}
//----

template<typename T>
PFC_INLINE void operator*=(shvec3<T> &shvr_, const shvec3<T> &shv_)
{
  shvr_.coeffs[0]*=shv_.coeffs[0];
  shvr_.coeffs[1]*=shv_.coeffs[1];
  shvr_.coeffs[2]*=shv_.coeffs[2];
  shvr_.coeffs[3]*=shv_.coeffs[3];
  shvr_.coeffs[4]*=shv_.coeffs[4];
  shvr_.coeffs[5]*=shv_.coeffs[5];
  shvr_.coeffs[6]*=shv_.coeffs[6];
  shvr_.coeffs[7]*=shv_.coeffs[7];
  shvr_.coeffs[8]*=shv_.coeffs[8];
}
//----

template<typename T>
PFC_INLINE void operator*=(shvec3<T> &shvr_, T v_)
{
  shvr_.coeffs[0]*=v_;
  shvr_.coeffs[1]*=v_;
  shvr_.coeffs[2]*=v_;
  shvr_.coeffs[3]*=v_;
  shvr_.coeffs[4]*=v_;
  shvr_.coeffs[5]*=v_;
  shvr_.coeffs[6]*=v_;
  shvr_.coeffs[7]*=v_;
  shvr_.coeffs[8]*=v_;
}
//----

template<typename T>
PFC_INLINE void operator*=(shvec3<T> &shvr_, const shmat3<T> &shm_)
{
  shvec3<T> shv=shvr_;
  shvr_.coeffs[0]=shv.coeffs[0]*shm_.m[0][0]+shv.coeffs[1]*shm_.m[1][0]+shv.coeffs[2]*shm_.m[2][0]+shv.coeffs[3]*shm_.m[3][0]+shv.coeffs[4]*shm_.m[4][0]+shv.coeffs[5]*shm_.m[5][0]+shv.coeffs[6]*shm_.m[6][0]+shv.coeffs[7]*shm_.m[7][0]+shv.coeffs[8]*shm_.m[8][0];
  shvr_.coeffs[1]=shv.coeffs[0]*shm_.m[0][1]+shv.coeffs[1]*shm_.m[1][1]+shv.coeffs[2]*shm_.m[2][1]+shv.coeffs[3]*shm_.m[3][1]+shv.coeffs[4]*shm_.m[4][1]+shv.coeffs[5]*shm_.m[5][1]+shv.coeffs[6]*shm_.m[6][1]+shv.coeffs[7]*shm_.m[7][1]+shv.coeffs[8]*shm_.m[8][1];
  shvr_.coeffs[2]=shv.coeffs[0]*shm_.m[0][2]+shv.coeffs[1]*shm_.m[1][2]+shv.coeffs[2]*shm_.m[2][2]+shv.coeffs[3]*shm_.m[3][2]+shv.coeffs[4]*shm_.m[4][2]+shv.coeffs[5]*shm_.m[5][2]+shv.coeffs[6]*shm_.m[6][2]+shv.coeffs[7]*shm_.m[7][2]+shv.coeffs[8]*shm_.m[8][2];
  shvr_.coeffs[3]=shv.coeffs[0]*shm_.m[0][3]+shv.coeffs[1]*shm_.m[1][3]+shv.coeffs[2]*shm_.m[2][3]+shv.coeffs[3]*shm_.m[3][3]+shv.coeffs[4]*shm_.m[4][3]+shv.coeffs[5]*shm_.m[5][3]+shv.coeffs[6]*shm_.m[6][3]+shv.coeffs[7]*shm_.m[7][3]+shv.coeffs[8]*shm_.m[8][3];
  shvr_.coeffs[4]=shv.coeffs[0]*shm_.m[0][4]+shv.coeffs[1]*shm_.m[1][4]+shv.coeffs[2]*shm_.m[2][4]+shv.coeffs[3]*shm_.m[3][4]+shv.coeffs[4]*shm_.m[4][4]+shv.coeffs[5]*shm_.m[5][4]+shv.coeffs[6]*shm_.m[6][4]+shv.coeffs[7]*shm_.m[7][4]+shv.coeffs[8]*shm_.m[8][4];
  shvr_.coeffs[5]=shv.coeffs[0]*shm_.m[0][5]+shv.coeffs[1]*shm_.m[1][5]+shv.coeffs[2]*shm_.m[2][5]+shv.coeffs[3]*shm_.m[3][5]+shv.coeffs[4]*shm_.m[4][5]+shv.coeffs[5]*shm_.m[5][5]+shv.coeffs[6]*shm_.m[6][5]+shv.coeffs[7]*shm_.m[7][5]+shv.coeffs[8]*shm_.m[8][5];
  shvr_.coeffs[6]=shv.coeffs[0]*shm_.m[0][6]+shv.coeffs[1]*shm_.m[1][6]+shv.coeffs[2]*shm_.m[2][6]+shv.coeffs[3]*shm_.m[3][6]+shv.coeffs[4]*shm_.m[4][6]+shv.coeffs[5]*shm_.m[5][6]+shv.coeffs[6]*shm_.m[6][6]+shv.coeffs[7]*shm_.m[7][6]+shv.coeffs[8]*shm_.m[8][6];
  shvr_.coeffs[7]=shv.coeffs[0]*shm_.m[0][7]+shv.coeffs[1]*shm_.m[1][7]+shv.coeffs[2]*shm_.m[2][7]+shv.coeffs[3]*shm_.m[3][7]+shv.coeffs[4]*shm_.m[4][7]+shv.coeffs[5]*shm_.m[5][7]+shv.coeffs[6]*shm_.m[6][7]+shv.coeffs[7]*shm_.m[7][7]+shv.coeffs[8]*shm_.m[8][7];
  shvr_.coeffs[8]=shv.coeffs[0]*shm_.m[0][8]+shv.coeffs[1]*shm_.m[1][8]+shv.coeffs[2]*shm_.m[2][8]+shv.coeffs[3]*shm_.m[3][8]+shv.coeffs[4]*shm_.m[4][8]+shv.coeffs[5]*shm_.m[5][8]+shv.coeffs[6]*shm_.m[6][8]+shv.coeffs[7]*shm_.m[7][8]+shv.coeffs[8]*shm_.m[8][8];
}
//----

template<typename T>
PFC_INLINE void operator/=(shvec3<T> &shvr_, const shvec3<T> &shv_)
{
  shvr_.coeffs[0]/=shv_.coeffs[0];
  shvr_.coeffs[1]/=shv_.coeffs[1];
  shvr_.coeffs[2]/=shv_.coeffs[2];
  shvr_.coeffs[3]/=shv_.coeffs[3];
  shvr_.coeffs[4]/=shv_.coeffs[4];
  shvr_.coeffs[5]/=shv_.coeffs[5];
  shvr_.coeffs[6]/=shv_.coeffs[6];
  shvr_.coeffs[7]/=shv_.coeffs[7];
  shvr_.coeffs[8]/=shv_.coeffs[8];
}
//----

template<typename T>
PFC_INLINE void operator/=(shvec3<T> &shvr_, T v_)
{
  T rcp_v=rcp(v_);
  shvr_.coeffs[0]*=rcp_v;
  shvr_.coeffs[1]*=rcp_v;
  shvr_.coeffs[2]*=rcp_v;
  shvr_.coeffs[3]*=rcp_v;
  shvr_.coeffs[4]*=rcp_v;
  shvr_.coeffs[5]*=rcp_v;
  shvr_.coeffs[6]*=rcp_v;
  shvr_.coeffs[7]*=rcp_v;
  shvr_.coeffs[8]*=rcp_v;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator+(const shvec3<T> &shv0_, const shvec3<T> &shv1_)
{
  shvec3<T> res=
  {
    shv0_.coeffs[0]+shv1_.coeffs[0],
    shv0_.coeffs[1]+shv1_.coeffs[1],
    shv0_.coeffs[2]+shv1_.coeffs[2],
    shv0_.coeffs[3]+shv1_.coeffs[3],
    shv0_.coeffs[4]+shv1_.coeffs[4],
    shv0_.coeffs[5]+shv1_.coeffs[5],
    shv0_.coeffs[6]+shv1_.coeffs[6],
    shv0_.coeffs[7]+shv1_.coeffs[7],
    shv0_.coeffs[8]+shv1_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator+(const shvec3<T> &shv_, T v_)
{
  shvec3<T> res=
  {
    shv_.coeffs[0]+v_,
    shv_.coeffs[1]+v_,
    shv_.coeffs[2]+v_,
    shv_.coeffs[3]+v_,
    shv_.coeffs[4]+v_,
    shv_.coeffs[5]+v_,
    shv_.coeffs[6]+v_,
    shv_.coeffs[7]+v_,
    shv_.coeffs[8]+v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator+(T v_, const shvec3<T> &shv_)
{
  shvec3<T> res=
  {
    v_+shv_.coeffs[0],
    v_+shv_.coeffs[1],
    v_+shv_.coeffs[2],
    v_+shv_.coeffs[3],
    v_+shv_.coeffs[4],
    v_+shv_.coeffs[5],
    v_+shv_.coeffs[6],
    v_+shv_.coeffs[7],
    v_+shv_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator-(const shvec3<T> &shv0_, const shvec3<T> &shv1_)
{
  shvec3<T> res=
  {
    shv0_.coeffs[0]-shv1_.coeffs[0],
    shv0_.coeffs[1]-shv1_.coeffs[1],
    shv0_.coeffs[2]-shv1_.coeffs[2],
    shv0_.coeffs[3]-shv1_.coeffs[3],
    shv0_.coeffs[4]-shv1_.coeffs[4],
    shv0_.coeffs[5]-shv1_.coeffs[5],
    shv0_.coeffs[6]-shv1_.coeffs[6],
    shv0_.coeffs[7]-shv1_.coeffs[7],
    shv0_.coeffs[8]-shv1_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator-(const shvec3<T> &shv_, T v_)
{
  shvec3<T> res=
  {
    shv_.coeffs[0]-v_,
    shv_.coeffs[1]-v_,
    shv_.coeffs[2]-v_,
    shv_.coeffs[3]-v_,
    shv_.coeffs[4]-v_,
    shv_.coeffs[5]-v_,
    shv_.coeffs[6]-v_,
    shv_.coeffs[7]-v_,
    shv_.coeffs[8]-v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator-(T v_, const shvec3<T> &shv_)
{
  shvec3<T> res=
  {
    v_-shv_.coeffs[0],
    v_-shv_.coeffs[1],
    v_-shv_.coeffs[2],
    v_-shv_.coeffs[3],
    v_-shv_.coeffs[4],
    v_-shv_.coeffs[5],
    v_-shv_.coeffs[6],
    v_-shv_.coeffs[7],
    v_-shv_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator*(const shvec3<T> &shv0_, const shvec3<T> &shv1_)
{
  shvec3<T> res=
  {
    shv0_.coeffs[0]*shv1_.coeffs[0],
    shv0_.coeffs[1]*shv1_.coeffs[1],
    shv0_.coeffs[2]*shv1_.coeffs[2],
    shv0_.coeffs[3]*shv1_.coeffs[3],
    shv0_.coeffs[4]*shv1_.coeffs[4],
    shv0_.coeffs[5]*shv1_.coeffs[5],
    shv0_.coeffs[6]*shv1_.coeffs[6],
    shv0_.coeffs[7]*shv1_.coeffs[7],
    shv0_.coeffs[8]*shv1_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator*(const shvec3<T> &shv_, T v_)
{
  shvec3<T> res=
  {
    shv_.coeffs[0]*v_,
    shv_.coeffs[1]*v_,
    shv_.coeffs[2]*v_,
    shv_.coeffs[3]*v_,
    shv_.coeffs[4]*v_,
    shv_.coeffs[5]*v_,
    shv_.coeffs[6]*v_,
    shv_.coeffs[7]*v_,
    shv_.coeffs[8]*v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator*(T v_, const shvec3<T> &shv_)
{
  shvec3<T> res=
  {
    v_*shv_.coeffs[0],
    v_*shv_.coeffs[1],
    v_*shv_.coeffs[2],
    v_*shv_.coeffs[3],
    v_*shv_.coeffs[4],
    v_*shv_.coeffs[5],
    v_*shv_.coeffs[6],
    v_*shv_.coeffs[7],
    v_*shv_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator*(const shvec3<T> &shv_, const shmat3<T> &shm_)
{
  shvec3<T> res=
  {
    shv.coeffs[0]*shm_.m[0][0]+shv.coeffs[1]*shm_.m[1][0]+shv.coeffs[2]*shm_.m[2][0]+shv.coeffs[3]*shm_.m[3][0]+shv.coeffs[4]*shm_.m[4][0]+shv.coeffs[5]*shm_.m[5][0]+shv.coeffs[6]*shm_.m[6][0]+shv.coeffs[7]*shm_.m[7][0]+shv.coeffs[8]*shm_.m[8][0],
    shv.coeffs[0]*shm_.m[0][1]+shv.coeffs[1]*shm_.m[1][1]+shv.coeffs[2]*shm_.m[2][1]+shv.coeffs[3]*shm_.m[3][1]+shv.coeffs[4]*shm_.m[4][1]+shv.coeffs[5]*shm_.m[5][1]+shv.coeffs[6]*shm_.m[6][1]+shv.coeffs[7]*shm_.m[7][1]+shv.coeffs[8]*shm_.m[8][1],
    shv.coeffs[0]*shm_.m[0][2]+shv.coeffs[1]*shm_.m[1][2]+shv.coeffs[2]*shm_.m[2][2]+shv.coeffs[3]*shm_.m[3][2]+shv.coeffs[4]*shm_.m[4][2]+shv.coeffs[5]*shm_.m[5][2]+shv.coeffs[6]*shm_.m[6][2]+shv.coeffs[7]*shm_.m[7][2]+shv.coeffs[8]*shm_.m[8][2],
    shv.coeffs[0]*shm_.m[0][3]+shv.coeffs[1]*shm_.m[1][3]+shv.coeffs[2]*shm_.m[2][3]+shv.coeffs[3]*shm_.m[3][3]+shv.coeffs[4]*shm_.m[4][3]+shv.coeffs[5]*shm_.m[5][3]+shv.coeffs[6]*shm_.m[6][3]+shv.coeffs[7]*shm_.m[7][3]+shv.coeffs[8]*shm_.m[8][3],
    shv.coeffs[0]*shm_.m[0][4]+shv.coeffs[1]*shm_.m[1][4]+shv.coeffs[2]*shm_.m[2][4]+shv.coeffs[3]*shm_.m[3][4]+shv.coeffs[4]*shm_.m[4][4]+shv.coeffs[5]*shm_.m[5][4]+shv.coeffs[6]*shm_.m[6][4]+shv.coeffs[7]*shm_.m[7][4]+shv.coeffs[8]*shm_.m[8][4],
    shv.coeffs[0]*shm_.m[0][5]+shv.coeffs[1]*shm_.m[1][5]+shv.coeffs[2]*shm_.m[2][5]+shv.coeffs[3]*shm_.m[3][5]+shv.coeffs[4]*shm_.m[4][5]+shv.coeffs[5]*shm_.m[5][5]+shv.coeffs[6]*shm_.m[6][5]+shv.coeffs[7]*shm_.m[7][5]+shv.coeffs[8]*shm_.m[8][5],
    shv.coeffs[0]*shm_.m[0][6]+shv.coeffs[1]*shm_.m[1][6]+shv.coeffs[2]*shm_.m[2][6]+shv.coeffs[3]*shm_.m[3][6]+shv.coeffs[4]*shm_.m[4][6]+shv.coeffs[5]*shm_.m[5][6]+shv.coeffs[6]*shm_.m[6][6]+shv.coeffs[7]*shm_.m[7][6]+shv.coeffs[8]*shm_.m[8][6],
    shv.coeffs[0]*shm_.m[0][7]+shv.coeffs[1]*shm_.m[1][7]+shv.coeffs[2]*shm_.m[2][7]+shv.coeffs[3]*shm_.m[3][7]+shv.coeffs[4]*shm_.m[4][7]+shv.coeffs[5]*shm_.m[5][7]+shv.coeffs[6]*shm_.m[6][7]+shv.coeffs[7]*shm_.m[7][7]+shv.coeffs[8]*shm_.m[8][7],
    shv.coeffs[0]*shm_.m[0][8]+shv.coeffs[1]*shm_.m[1][8]+shv.coeffs[2]*shm_.m[2][8]+shv.coeffs[3]*shm_.m[3][8]+shv.coeffs[4]*shm_.m[4][8]+shv.coeffs[5]*shm_.m[5][8]+shv.coeffs[6]*shm_.m[6][8]+shv.coeffs[7]*shm_.m[7][8]+shv.coeffs[8]*shm_.m[8][8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator*(const shmat3<T> &shm_, const shvec3<T> &shv_)
{
  shvec3<T> res=
  {
    shv.coeffs[0]*shm_.m[0][0]+shv.coeffs[1]*shm_.m[0][1]+shv.coeffs[2]*shm_.m[0][2]+shv.coeffs[3]*shm_.m[0][3]+shv.coeffs[4]*shm_.m[0][4]+shv.coeffs[5]*shm_.m[0][5]+shv.coeffs[6]*shm_.m[0][6]+shv.coeffs[7]*shm_.m[0][7]+shv.coeffs[8]*shm_.m[0][8],
    shv.coeffs[0]*shm_.m[1][0]+shv.coeffs[1]*shm_.m[1][1]+shv.coeffs[2]*shm_.m[1][2]+shv.coeffs[3]*shm_.m[1][3]+shv.coeffs[4]*shm_.m[1][4]+shv.coeffs[5]*shm_.m[1][5]+shv.coeffs[6]*shm_.m[1][6]+shv.coeffs[7]*shm_.m[1][7]+shv.coeffs[8]*shm_.m[1][8],
    shv.coeffs[0]*shm_.m[2][0]+shv.coeffs[1]*shm_.m[2][1]+shv.coeffs[2]*shm_.m[2][2]+shv.coeffs[3]*shm_.m[2][3]+shv.coeffs[4]*shm_.m[2][4]+shv.coeffs[5]*shm_.m[2][5]+shv.coeffs[6]*shm_.m[2][6]+shv.coeffs[7]*shm_.m[2][7]+shv.coeffs[8]*shm_.m[2][8],
    shv.coeffs[0]*shm_.m[3][0]+shv.coeffs[1]*shm_.m[3][1]+shv.coeffs[2]*shm_.m[3][2]+shv.coeffs[3]*shm_.m[3][3]+shv.coeffs[4]*shm_.m[3][4]+shv.coeffs[5]*shm_.m[3][5]+shv.coeffs[6]*shm_.m[3][6]+shv.coeffs[7]*shm_.m[3][7]+shv.coeffs[8]*shm_.m[3][8],
    shv.coeffs[0]*shm_.m[4][0]+shv.coeffs[1]*shm_.m[4][1]+shv.coeffs[2]*shm_.m[4][2]+shv.coeffs[3]*shm_.m[4][3]+shv.coeffs[4]*shm_.m[4][4]+shv.coeffs[5]*shm_.m[4][5]+shv.coeffs[6]*shm_.m[4][6]+shv.coeffs[7]*shm_.m[4][7]+shv.coeffs[8]*shm_.m[4][8],
    shv.coeffs[0]*shm_.m[5][0]+shv.coeffs[1]*shm_.m[5][1]+shv.coeffs[2]*shm_.m[5][2]+shv.coeffs[3]*shm_.m[5][3]+shv.coeffs[4]*shm_.m[5][4]+shv.coeffs[5]*shm_.m[5][5]+shv.coeffs[6]*shm_.m[5][6]+shv.coeffs[7]*shm_.m[5][7]+shv.coeffs[8]*shm_.m[5][8],
    shv.coeffs[0]*shm_.m[6][0]+shv.coeffs[1]*shm_.m[6][1]+shv.coeffs[2]*shm_.m[6][2]+shv.coeffs[3]*shm_.m[6][3]+shv.coeffs[4]*shm_.m[6][4]+shv.coeffs[5]*shm_.m[6][5]+shv.coeffs[6]*shm_.m[6][6]+shv.coeffs[7]*shm_.m[6][7]+shv.coeffs[8]*shm_.m[6][8],
    shv.coeffs[0]*shm_.m[7][0]+shv.coeffs[1]*shm_.m[7][1]+shv.coeffs[2]*shm_.m[7][2]+shv.coeffs[3]*shm_.m[7][3]+shv.coeffs[4]*shm_.m[7][4]+shv.coeffs[5]*shm_.m[7][5]+shv.coeffs[6]*shm_.m[7][6]+shv.coeffs[7]*shm_.m[7][7]+shv.coeffs[8]*shm_.m[7][8],
    shv.coeffs[0]*shm_.m[8][0]+shv.coeffs[1]*shm_.m[8][1]+shv.coeffs[2]*shm_.m[8][2]+shv.coeffs[3]*shm_.m[8][3]+shv.coeffs[4]*shm_.m[8][4]+shv.coeffs[5]*shm_.m[8][5]+shv.coeffs[6]*shm_.m[8][6]+shv.coeffs[7]*shm_.m[8][7]+shv.coeffs[8]*shm_.m[8][8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator/(const shvec3<T> &shv0_, const shvec3<T> &shv1_)
{
  shvec3<T> res=
  {
    shv0_.coeffs[0]/shv1_.coeffs[0],
    shv0_.coeffs[1]/shv1_.coeffs[1],
    shv0_.coeffs[2]/shv1_.coeffs[2],
    shv0_.coeffs[3]/shv1_.coeffs[3],
    shv0_.coeffs[4]/shv1_.coeffs[4],
    shv0_.coeffs[5]/shv1_.coeffs[5],
    shv0_.coeffs[6]/shv1_.coeffs[6],
    shv0_.coeffs[7]/shv1_.coeffs[7],
    shv0_.coeffs[8]/shv1_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator/(const shvec3<T> &shv_, T v_)
{
  T rcp_v=rcp(v_);
  shvec3<T> res=
  {
    shv_.coeffs[0]*rcp_v,
    shv_.coeffs[1]*rcp_v,
    shv_.coeffs[2]*rcp_v,
    shv_.coeffs[3]*rcp_v,
    shv_.coeffs[4]*rcp_v,
    shv_.coeffs[5]*rcp_v,
    shv_.coeffs[6]*rcp_v,
    shv_.coeffs[7]*rcp_v,
    shv_.coeffs[8]*rcp_v
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> operator/(T v_, const shvec3<T> &shv_)
{
  shvec3<T> res=
  {
    v_/shv_.coeffs[0],
    v_/shv_.coeffs[1],
    v_/shv_.coeffs[2],
    v_/shv_.coeffs[3],
    v_/shv_.coeffs[4],
    v_/shv_.coeffs[5],
    v_/shv_.coeffs[6],
    v_/shv_.coeffs[7],
    v_/shv_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE T sh_dot(const shvec3<T> &shv0_, const shvec3<T> &shv1_)
{
  return  shv0_.coeffs[0]*shv1_.coeffs[0]
         +shv0_.coeffs[1]*shv1_.coeffs[1]
         +shv0_.coeffs[2]*shv1_.coeffs[2]
         +shv0_.coeffs[3]*shv1_.coeffs[3]
         +shv0_.coeffs[3]*shv1_.coeffs[4]
         +shv0_.coeffs[3]*shv1_.coeffs[5]
         +shv0_.coeffs[3]*shv1_.coeffs[6]
         +shv0_.coeffs[3]*shv1_.coeffs[7]
         +shv0_.coeffs[3]*shv1_.coeffs[8];
}
//----

template<typename T>
PFC_INLINE void sh_dir(shvec3<T> &shv_, const vec3<T> &dir_)
{
  typedef math<T>::scalar_t scalar_t;
  static const scalar_t s_c0=scalar_t(0.28209479177387814347403972578039);  //  0.5*sqrt(1/pi)
  static const scalar_t s_c1=scalar_t(0.48860251190291992158638462283835);  //  0.5*sqrt(3/pi)
  static const scalar_t s_c20=scalar_t(1.0925484305920790705433857058027);  //  0.5*sqrt(15/pi)
  static const scalar_t s_c21=scalar_t(0.31539156525252000603089369029571); // 0.25*sqrt(5/pi)
  static const scalar_t s_c22=scalar_t(0.54627421529603953527169285290134); // 0.25*sqrt(15/pi)
  shv_.coeffs[0]=s_c0;
  shv_.coeffs[1]=s_c1*dir_.y;
  shv_.coeffs[2]=s_c1*dir_.z;
  shv_.coeffs[3]=s_c1*dir_.x;
  shv_.coeffs[4]=s_c20*dir_.x*dir_.y;
  shv_.coeffs[5]=s_c20*dir_.y*dir_.z;
  shv_.coeffs[6]=s_c21*(3.0f*dir_.z*dir_.z-1.0f);
  shv_.coeffs[7]=s_c20*dir_.x*dir_.z;
  shv_.coeffs[8]=s_c22*(dir_.x*dir_.x-dir_.y*dir_.y);
}
//----

template<typename T, typename U>
shvec3<T> sh_product(const shvec3<T> &shv0_, const shvec3<U> &shv1_)
{
  // product constants (22 muls)
  static const U s_f0=T(0.31943828);
  static const U s_f1=T(0.44721360);
  static const U s_f2=T(0.55328334);
  static const U s_f3=T(0.63887656);
  static const U s_f4=T(0.77459667);
  static const U s_f5=T(0.89442719);
  static const U s_scale=math<U>::quarter_rpi;
  const U s1f1=shv1_.coeffs[1]*s_f1;
  const U s1f4=shv1_.coeffs[1]*s_f4;
  const U s2f4=shv1_.coeffs[2]*s_f4;
  const U s2f5=shv1_.coeffs[2]*s_f5;
  const U s3f1=shv1_.coeffs[3]*s_f1;
  const U s3f4=shv1_.coeffs[3]*s_f4;
  const U s4f2=shv1_.coeffs[4]*s_f2;
  const U s4f3=shv1_.coeffs[4]*s_f3;
  const U s4f4=shv1_.coeffs[4]*s_f4;
  const U s5f0=shv1_.coeffs[5]*s_f0;
  const U s5f2=shv1_.coeffs[5]*s_f2;
  const U s5f4=shv1_.coeffs[5]*s_f4;
  const U s6f0=shv1_.coeffs[6]*s_f0;
  const U s6f1=shv1_.coeffs[6]*s_f1;
  const U s6f3=shv1_.coeffs[6]*s_f3;
  const U s6f5=shv1_.coeffs[6]*s_f5;
  const U s7f0=shv1_.coeffs[7]*s_f0;
  const U s7f2=shv1_.coeffs[7]*s_f2;
  const U s7f4=shv1_.coeffs[7]*s_f4;
  const U s8f2=shv1_.coeffs[8]*s_f2;
  const U s8f3=shv1_.coeffs[8]*s_f3;
  const U s8f4=shv1_.coeffs[8]*s_f4;

  // calculate product of two SH3 vectors (80 muls + 74 adds)
  shvec3<T> res=
  {
    s_scale*(shv1_.coeffs[0]*shv0_.coeffs[0]+shv1_.coeffs[1]*shv0_.coeffs[1]+shv1_.coeffs[2]*shv0_.coeffs[2]+shv1_.coeffs[3]*shv0_.coeffs[3]+shv1_.coeffs[4]*shv0_.coeffs[4]+shv1_.coeffs[5]*shv0_.coeffs[5]+shv1_.coeffs[6]*shv0_.coeffs[6]+shv1_.coeffs[7]*shv0_.coeffs[7]+shv1_.coeffs[8]*shv0_.coeffs[8]),
    s_scale*(shv1_.coeffs[1]*shv0_.coeffs[0]+(shv1_.coeffs[0]-s6f1-s8f4)*shv0_.coeffs[1]+s5f4*shv0_.coeffs[2]+s4f4*shv0_.coeffs[3]+s3f4*shv0_.coeffs[4]+s2f4*shv0_.coeffs[5]-s1f1*shv0_.coeffs[6]-s1f4*shv0_.coeffs[8]),
    s_scale*(shv1_.coeffs[2]*shv0_.coeffs[0]+s5f4*shv0_.coeffs[1]+(shv1_.coeffs[0]+s6f5)*shv0_.coeffs[2]+s7f4*shv0_.coeffs[3]+s1f4*shv0_.coeffs[5]+s2f5*shv0_.coeffs[6]+s3f4*shv0_.coeffs[7]),
    s_scale*(shv1_.coeffs[3]*shv0_.coeffs[0]+s4f4*shv0_.coeffs[1]+s7f4*shv0_.coeffs[2]+(shv1_.coeffs[0]-s6f1+s8f4)*shv0_.coeffs[3]+s1f4*shv0_.coeffs[4]-s3f1*shv0_.coeffs[6]+s2f4*shv0_.coeffs[7]+s3f4*shv0_.coeffs[8]),
    s_scale*(shv1_.coeffs[4]*shv0_.coeffs[0]+s3f4*shv0_.coeffs[1]+s1f4*shv0_.coeffs[3]+(shv1_.coeffs[0]-s6f3)*shv0_.coeffs[4]+s7f2*shv0_.coeffs[5]-s4f3*shv0_.coeffs[6]+s5f2*shv0_.coeffs[7]),
    s_scale*(shv1_.coeffs[5]*shv0_.coeffs[0]+s2f4*shv0_.coeffs[1]+s1f4*shv0_.coeffs[2]+s7f2*shv0_.coeffs[4]+(shv1_.coeffs[0]+s6f0-s8f2)*shv0_.coeffs[5]+s5f0*shv0_.coeffs[6]+s4f2*shv0_.coeffs[7]-s5f2*shv0_.coeffs[8]),
    s_scale*(shv1_.coeffs[6]*shv0_.coeffs[0]-s1f1*shv0_.coeffs[1]+s2f5*shv0_.coeffs[2]-s3f1*shv0_.coeffs[3]-s4f3*shv0_.coeffs[4]+s5f0*shv0_.coeffs[5]+(shv1_.coeffs[0]+s6f3)*shv0_.coeffs[6]+s7f0*shv0_.coeffs[7]-s8f3*shv0_.coeffs[8]),
    s_scale*(shv1_.coeffs[7]*shv0_.coeffs[0]+s3f4*shv0_.coeffs[2]+s2f4*shv0_.coeffs[3]+s5f2*shv0_.coeffs[4]+s4f2*shv0_.coeffs[5]+s7f0*shv0_.coeffs[6]+(shv1_.coeffs[0]+s6f0+s8f2)*shv0_.coeffs[7]+s7f2*shv0_.coeffs[8]),
    s_scale*(shv1_.coeffs[8]*shv0_.coeffs[0]-s1f4*shv0_.coeffs[1]+s3f4*shv0_.coeffs[3]-s5f2*shv0_.coeffs[5]-s8f3*shv0_.coeffs[6]+s7f2*shv0_.coeffs[7]+(shv1_.coeffs[0]-s6f3)*shv0_.coeffs[8])
  }
  return res;
}
//----------------------------------------------------------------------------


//============================================================================
// zhvec2
//============================================================================
template<typename T> const zhvec2<T> zhvec2<T>::s_cos={math<T>::pi, math<T>::two_pi/T(3.0)};
template<typename T> const zhvec2<T> zhvec2<T>::s_clamped_cos={math<T>::pi, T(3.6275987284648186)};
template<typename T> const zhvec2<T> zhvec2<T>::s_cos2={math<T>::two_pi/3.0f, math<T>::half_pi};
template<typename T> const zhvec2<T> zhvec2<T>::s_clamped_cos2={math<T>::two_pi/3.0f, T(2.7206990463457954)};
//----------------------------------------------------------------------------


//============================================================================
// zhvec2 ops
//============================================================================
template<typename T>
PFC_INLINE void operator+=(zhvec2<T> &zhvr_, const zhvec2<T> &zhv_)
{
  zhvr_.coeffs[0]+=zhv_.coeffs[0];
  zhvr_.coeffs[1]+=zhv_.coeffs[1];
}
//----

template<typename T>
PFC_INLINE void operator+=(zhvec2<T> &zhvr_, T v_)
{
  zhvr_.coeffs[0]+=v_;
  zhvr_.coeffs[1]+=v_;
}
//----

template<typename T>
PFC_INLINE void operator-=(zhvec2<T> &zhvr_, const zhvec2<T>&)
{
  zhvr_.coeffs[0]-=zhv_.coeffs[0];
  zhvr_.coeffs[1]-=zhv_.coeffs[1];
}
//----

template<typename T>
PFC_INLINE void operator-=(zhvec2<T> &zhvr_, T v_)
{
  zhvr_.coeffs[0]-=v_;
  zhvr_.coeffs[1]-=v_;
}
//----

template<typename T>
PFC_INLINE void operator*=(zhvec2<T> &zhvr_, const zhvec2<T>&)
{
  zhvr_.coeffs[0]*=zhv_.coeffs[0];
  zhvr_.coeffs[1]*=zhv_.coeffs[1];
}
//----

template<typename T>
PFC_INLINE void operator*=(zhvec2<T> &zhvr_, T v_)
{
  zhvr_.coeffs[0]*=v_;
  zhvr_.coeffs[1]*=v_;
}
//----

template<typename T>
PFC_INLINE void operator/=(zhvec2<T> &zhvr_, const zhvec2<T> &zhv_)
{
  zhvr_.coeffs[0]/=zhv_.coeffs[0];
  zhvr_.coeffs[1]/=zhv_.coeffs[1];
}
//----

template<typename T>
PFC_INLINE void operator/=(zhvec2<T> &zhvr_, T v_)
{
  T rcp_v=rcp(v_);
  zhvr_.coeffs[0]*=rcp_v;
  zhvr_.coeffs[1]*=rcp_v;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator+(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]+zhv1_.coeffs[0],
    zhv0_.coeffs[1]+zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator+(const zhvec2<T> &zhv_, T v_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]+v_,
    zhv_.coeffs[1]+v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator+(T v_, const zhvec2<T> &zhv_)
{
  zhvec2<T> res=
  {
    v_+zhv_.coeffs[0],
    v_+zhv_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator-(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]-zhv1_.coeffs[0],
    zhv0_.coeffs[1]-zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator-(const zhvec2<T> &zhv_, T v_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]-v_,
    zhv_.coeffs[1]-v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator-(T v_, const zhvec2<T> &zhv_)
{
  zhvec2<T> res=
  {
    v_-zhv_.coeffs[0],
    v_-zhv_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator*(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]*zhv1_.coeffs[0],
    zhv0_.coeffs[1]*zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator*(const zhvec2<T> &zhv_, T v_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]*v_,
    zhv_.coeffs[1]*v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator*(T v_, const zhvec2<T> &zhv_)
{
  zhvec2<T> res=
  {
    v_*zhv_.coeffs[0],
    v_*zhv_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator/(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]/zhv1_.coeffs[0],
    zhv0_.coeffs[1]/zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator/(const zhvec2<T> &zhv_, T v_)
{
  T rcp_v=rcp(v_);
  zhvec2<T> res=
  {
    zhv_.coeffs[0]*rcp_v,
    zhv_.coeffs[1]*rcp_v
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> operator/(T v_, const zhvec2<T> &zhv_)
{
  zhvec2<T> res=
  {
    v_/zhv_.coeffs[0],
    v_/zhv_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE T sh_dot(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_)
{
  return  zhv0_.coeffs[0]*zhv1_.coeffs[0]
         +zhv0_.coeffs[1]*zhv1_.coeffs[1];
}
//----------------------------------------------------------------------------


//============================================================================
// zhvec3
//============================================================================
template<typename T> const zhvec3<T> zhvec3<T>::s_cos={math<T>::pi, math<T>::two_pi/T(3.0), math<T>::quarter_pi};
template<typename T> const zhvec3<T> zhvec3<T>::s_clamped_cos={math<T>::pi, T(3.6275987284648186), T(1.7562036827495804)};
template<typename T> const zhvec3<T> zhvec3<T>::s_cos2={math<T>::two_pi/3.0f, math<T>::half_pi, math<T>::four_pi/T(15.0)};
template<typename T> const zhvec3<T> zhvec3<T>::s_clamped_cos2={math<T>::two_pi/3.0f, T(2.7206990463457954), T(1.8732839282658524)};
//----------------------------------------------------------------------------


//============================================================================
// zhvec3 ops
//============================================================================
template<typename T>
PFC_INLINE void operator+=(zhvec3<T> &zhvr_, const zhvec3<T> &zhv_)
{
  zhvr_.coeffs[0]+=zhv_.coeffs[0];
  zhvr_.coeffs[1]+=zhv_.coeffs[1];
  zhvr_.coeffs[2]+=zhv_.coeffs[2];
}
//----

template<typename T>
PFC_INLINE void operator+=(zhvec3<T> &zhvr_, T v_)
{
  zhvr_.coeffs[0]+=v_;
  zhvr_.coeffs[1]+=v_;
  zhvr_.coeffs[2]+=v_;
}
//----

template<typename T>
PFC_INLINE void operator-=(zhvec3<T> &zhvr_, const zhvec3<T>&)
{
  zhvr_.coeffs[0]-=zhv_.coeffs[0];
  zhvr_.coeffs[1]-=zhv_.coeffs[1];
  zhvr_.coeffs[2]-=zhv_.coeffs[2];
}
//----

template<typename T>
PFC_INLINE void operator-=(zhvec3<T> &zhvr_, T v_)
{
  zhvr_.coeffs[0]-=v_;
  zhvr_.coeffs[1]-=v_;
  zhvr_.coeffs[2]-=v_;
}
//----

template<typename T>
PFC_INLINE void operator*=(zhvec3<T> &zhvr_, const zhvec3<T>&)
{
  zhvr_.coeffs[0]*=zhv_.coeffs[0];
  zhvr_.coeffs[1]*=zhv_.coeffs[1];
  zhvr_.coeffs[2]*=zhv_.coeffs[2];
}
//----

template<typename T>
PFC_INLINE void operator*=(zhvec3<T> &zhvr_, T v_)
{
  zhvr_.coeffs[0]*=v_;
  zhvr_.coeffs[1]*=v_;
  zhvr_.coeffs[2]*=v_;
}
//----

template<typename T>
PFC_INLINE void operator/=(zhvec3<T> &zhvr_, const zhvec3<T> &zhv_)
{
  zhvr_.coeffs[0]/=zhv_.coeffs[0];
  zhvr_.coeffs[1]/=zhv_.coeffs[1];
  zhvr_.coeffs[2]/=zhv_.coeffs[2];
}
//----

template<typename T>
PFC_INLINE void operator/=(zhvec3<T> &zhvr_, T v_)
{
  T rcp_v=rcp(v_);
  zhvr_.coeffs[0]*=rcp_v;
  zhvr_.coeffs[1]*=rcp_v;
  zhvr_.coeffs[2]*=rcp_v;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator+(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_)
{
  zhvec3<T> res=
  {
    zhv0_.coeffs[0]+zhv1_.coeffs[0],
    zhv0_.coeffs[1]+zhv1_.coeffs[1],
    zhv0_.coeffs[2]+zhv1_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator+(const zhvec3<T> &zhv_, T v_)
{
  zhvec3<T> res=
  {
    zhv_.coeffs[0]+v_,
    zhv_.coeffs[1]+v_,
    zhv_.coeffs[2]+v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator+(T v_, const zhvec3<T> &zhv_)
{
  zhvec3<T> res=
  {
    v_+zhv_.coeffs[0],
    v_+zhv_.coeffs[1],
    v_+zhv_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator-(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_)
{
  zhvec3<T> res=
  {
    zhv0_.coeffs[0]-zhv1_.coeffs[0],
    zhv0_.coeffs[1]-zhv1_.coeffs[1],
    zhv0_.coeffs[2]-zhv1_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator-(const zhvec3<T> &zhv_, T v_)
{
  zhvec3<T> res=
  {
    zhv_.coeffs[0]-v_,
    zhv_.coeffs[1]-v_,
    zhv_.coeffs[2]-v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator-(T v_, const zhvec3<T> &zhv_)
{
  zhvec3<T> res=
  {
    v_-zhv_.coeffs[0],
    v_-zhv_.coeffs[1],
    v_-zhv_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator*(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_)
{
  zhvec3<T> res=
  {
    zhv0_.coeffs[0]*zhv1_.coeffs[0],
    zhv0_.coeffs[1]*zhv1_.coeffs[1],
    zhv0_.coeffs[2]*zhv1_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator*(const zhvec3<T> &zhv_, T v_)
{
  zhvec3<T> res=
  {
    zhv_.coeffs[0]*v_,
    zhv_.coeffs[1]*v_,
    zhv_.coeffs[2]*v_
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator*(T v_, const zhvec3<T> &zhv_)
{
  zhvec3<T> res=
  {
    v_*zhv_.coeffs[0],
    v_*zhv_.coeffs[1],
    v_*zhv_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator/(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_)
{
  zhvec3<T> res=
  {
    zhv0_.coeffs[0]/zhv1_.coeffs[0],
    zhv0_.coeffs[1]/zhv1_.coeffs[1],
    zhv0_.coeffs[2]/zhv1_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator/(const zhvec3<T> &zhv_, T v_)
{
  T rcp_v=rcp(v_);
  zhvec3<T> res=
  {
    zhv_.coeffs[0]*rcp_v,
    zhv_.coeffs[1]*rcp_v,
    zhv_.coeffs[2]*rcp_v
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> operator/(T v_, const zhvec3<T> &zhv_)
{
  zhvec3<T> res=
  {
    v_/zhv_.coeffs[0],
    v_/zhv_.coeffs[1],
    v_/zhv_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE T sh_dot(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_)
{
  return  zhv0_.coeffs[0]*zhv1_.coeffs[0]
         +zhv0_.coeffs[1]*zhv1_.coeffs[1]
         +zhv0_.coeffs[2]*zhv1_.coeffs[2];
}
//----------------------------------------------------------------------------
