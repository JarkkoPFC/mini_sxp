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
PFC_INLINE bool is_zero(const shvec2<T> &shv_)
{
  return    shv_.coeffs[0]==0
         && shv_.coeffs[1]==0
         && shv_.coeffs[2]==0
         && shv_.coeffs[3]==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const shvec2<T> &shv_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return    shv_.coeffs[0]>=0 && shv_.coeffs[0]<=scalar_t(1)
         && shv_.coeffs[1]>=0 && shv_.coeffs[1]<=scalar_t(1)
         && shv_.coeffs[2]>=0 && shv_.coeffs[2]<=scalar_t(1)
         && shv_.coeffs[3]>=0 && shv_.coeffs[3]<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const shvec2<T> &shv_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return    shv_.coeffs[0]>=scalar_t(-1) && shv_.coeffs[0]<=scalar_t(1)
         && shv_.coeffs[1]>=scalar_t(-1) && shv_.coeffs[1]<=scalar_t(1)
         && shv_.coeffs[2]>=scalar_t(-1) && shv_.coeffs[2]<=scalar_t(1)
         && shv_.coeffs[3]>=scalar_t(-1) && shv_.coeffs[3]<=scalar_t(1);
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const shvec2<T> &shv0_, const shvec2<U> &shv1_)
{
  return    shv0_.coeffs[0]==shv1_.coeffs[0]
         && shv0_.coeffs[1]==shv1_.coeffs[1]
         && shv0_.coeffs[2]==shv1_.coeffs[2]
         && shv0_.coeffs[3]==shv1_.coeffs[3];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const shvec2<T> &shv_, U v_)
{
  return    shv_.coeffs[0]==v_
         && shv_.coeffs[1]==v_
         && shv_.coeffs[2]==v_
         && shv_.coeffs[3]==v_;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(U v_, const shvec2<T> &shv_)
{
  return    v_==shv_.coeffs[0]
         && v_==shv_.coeffs[1]
         && v_==shv_.coeffs[2]
         && v_==shv_.coeffs[3];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const shvec2<T> &shv0_, const shvec2<U> &shv1_)
{
  return    shv0_.coeffs[0]!=shv1_.coeffs[0]
         || shv0_.coeffs[1]!=shv1_.coeffs[1]
         || shv0_.coeffs[2]!=shv1_.coeffs[2]
         || shv0_.coeffs[3]!=shv1_.coeffs[3];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const shvec2<T> &shv_, U v_)
{
  return    shv_.coeffs[0]!=v_
         || shv_.coeffs[1]!=v_
         || shv_.coeffs[2]!=v_
         || shv_.coeffs[3]!=v_;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(U v_, const shvec2<T> &shv_)
{
  return    v_!=shv_.coeffs[0]
         || v_!=shv_.coeffs[1]
         || v_!=shv_.coeffs[2]
         || v_!=shv_.coeffs[3];
}
//----

template<typename T, typename U>
PFC_INLINE void operator+=(shvec2<T> &shvr_, const shvec2<U> &shv_)
{
  shvr_.coeffs[0]+=shv_.coeffs[0];
  shvr_.coeffs[1]+=shv_.coeffs[1];
  shvr_.coeffs[2]+=shv_.coeffs[2];
  shvr_.coeffs[3]+=shv_.coeffs[3];
}
//----

template<typename T, typename U>
PFC_INLINE void operator+=(shvec2<T> &shvr_, U v_)
{
  shvr_.coeffs[0]+=v_;
  shvr_.coeffs[1]+=v_;
  shvr_.coeffs[2]+=v_;
  shvr_.coeffs[3]+=v_;
}
//----

template<typename T, typename U>
PFC_INLINE void operator-=(shvec2<T> &shvr_, const shvec2<U> &shv_)
{
  shvr_.coeffs[0]-=shv_.coeffs[0];
  shvr_.coeffs[1]-=shv_.coeffs[1];
  shvr_.coeffs[2]-=shv_.coeffs[2];
  shvr_.coeffs[3]-=shv_.coeffs[3];
}
//----

template<typename T, typename U>
PFC_INLINE void operator-=(shvec2<T> &shvr_, U v_)
{
  shvr_.coeffs[0]-=v_;
  shvr_.coeffs[1]-=v_;
  shvr_.coeffs[2]-=v_;
  shvr_.coeffs[3]-=v_;
}
//----

template<typename T, typename U>
PFC_INLINE void operator*=(shvec2<T> &shvr_, const shvec2<U> &shv_)
{
  shvr_.coeffs[0]*=shv_.coeffs[0];
  shvr_.coeffs[1]*=shv_.coeffs[1];
  shvr_.coeffs[2]*=shv_.coeffs[2];
  shvr_.coeffs[3]*=shv_.coeffs[3];
}
//----

template<typename T, typename U>
PFC_INLINE void operator*=(shvec2<T> &shvr_, U v_)
{
  shvr_.coeffs[0]*=v_;
  shvr_.coeffs[1]*=v_;
  shvr_.coeffs[2]*=v_;
  shvr_.coeffs[3]*=v_;
}
//----

template<typename T, typename U>
PFC_INLINE void operator*=(shvec2<T> &shvr_, const shmat2<U> &shm_)
{
  shvec2<T> shv=shvr_;
  shvr_.coeffs[0]=shv.coeffs[0]*shm_.m[0][0]+shv.coeffs[1]*shm_.m[1][0]+shv.coeffs[2]*shm_.m[2][0]+shv.coeffs[3]*shm_.m[3][0];
  shvr_.coeffs[1]=shv.coeffs[0]*shm_.m[0][1]+shv.coeffs[1]*shm_.m[1][1]+shv.coeffs[2]*shm_.m[2][1]+shv.coeffs[3]*shm_.m[3][1];
  shvr_.coeffs[2]=shv.coeffs[0]*shm_.m[0][2]+shv.coeffs[1]*shm_.m[1][2]+shv.coeffs[2]*shm_.m[2][2]+shv.coeffs[3]*shm_.m[3][2];
  shvr_.coeffs[3]=shv.coeffs[0]*shm_.m[0][3]+shv.coeffs[1]*shm_.m[1][3]+shv.coeffs[2]*shm_.m[2][3]+shv.coeffs[3]*shm_.m[3][3];
}
//----

template<typename T, typename U>
PFC_INLINE void operator/=(shvec2<T> &shvr_, const shvec2<U> &shv_)
{
  shvr_.coeffs[0]/=shv_.coeffs[0];
  shvr_.coeffs[1]/=shv_.coeffs[1];
  shvr_.coeffs[2]/=shv_.coeffs[2];
  shvr_.coeffs[3]/=shv_.coeffs[3];
}
//----

template<typename T, typename U>
PFC_INLINE void operator/=(shvec2<T> &shvr_, U v_)
{
  T rcp_v=rcp(v_);
  shvr_.coeffs[0]*=rcp_v;
  shvr_.coeffs[1]*=rcp_v;
  shvr_.coeffs[2]*=rcp_v;
  shvr_.coeffs[3]*=rcp_v;
}
//----

template<typename T, typename U>
PFC_INLINE shvec2<T> operator+(const shvec2<T> &shv0_, const shvec2<U> &shv1_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator+(const shvec2<T> &shv_, U v_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator+(U v_, const shvec2<T> &shv_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator-(const shvec2<T> &shv0_, const shvec2<U> &shv1_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator-(const shvec2<T> &shv_, U v_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator-(U v_, const shvec2<T> &shv_)
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
PFC_INLINE shvec2<T> operator-(const shvec2<T> &shv_)
{
  shvec2<T> res=
  {
    -shv_.coeffs[0],
    -shv_.coeffs[1],
    -shv_.coeffs[2],
    -shv_.coeffs[3]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec2<T> operator*(const shvec2<T> &shv0_, const shvec2<U> &shv1_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator*(const shvec2<T> &shv_, U v_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator*(U v_, const shvec2<T> &shv_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator*(const shvec2<T> &shv_, const shmat2<U> &shm_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator*(const shmat2<T> &shm_, const shvec2<U> &shv_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator/(const shvec2<T> &shv0_, const shvec2<U> &shv1_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator/(const shvec2<T> &shv_, U v_)
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

template<typename T, typename U>
PFC_INLINE shvec2<T> operator/(U v_, const shvec2<T> &shv_)
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
PFC_INLINE shvec2<T> min(const shvec2<T> &shv_)
{
  return min(shv_.coeffs[0], shv_.coeffs[1], shv_.coeffs[2], shv_.coeffs[3]);
}
//----

template<typename T>
PFC_INLINE shvec2<T> min(const shvec2<T> &shv0_, const shvec2<T> &shv1_)
{
  shvec2<T> res=
  {
    shv0_.coeffs[0]<shv1_.coeffs[0]?shv0_.coeffs[0]:shv1_.coeffs[0],
    shv0_.coeffs[1]<shv1_.coeffs[1]?shv0_.coeffs[1]:shv1_.coeffs[1],
    shv0_.coeffs[2]<shv1_.coeffs[2]?shv0_.coeffs[2]:shv1_.coeffs[2],
    shv0_.coeffs[3]<shv1_.coeffs[3]?shv0_.coeffs[3]:shv1_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> min(const shvec2<T> &shv0_, const shvec2<T> &shv1_, const shvec2<T> &shv2_)
{
  shvec2<T> res=
  {
    min(shv0_.coeffs[0], shv1_.coeffs[1], shv2_.coeffs[0]),
    min(shv0_.coeffs[1], shv1_.coeffs[1], shv2_.coeffs[1]),
    min(shv0_.coeffs[2], shv1_.coeffs[2], shv2_.coeffs[2]),
    min(shv0_.coeffs[3], shv1_.coeffs[3], shv2_.coeffs[3])
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> min(const shvec2<T> &shv0_, const shvec2<T> &shv1_, const shvec2<T> &shv2_, const shvec2<T> &shv3_)
{
  shvec2<T> res=
  {
    min(shv0_.coeffs[0], shv1_.coeffs[1], shv2_.coeffs[0], shv3_.coeffs[0]),
    min(shv0_.coeffs[1], shv1_.coeffs[1], shv2_.coeffs[1], shv3_.coeffs[1]),
    min(shv0_.coeffs[2], shv1_.coeffs[2], shv2_.coeffs[2], shv3_.coeffs[2]),
    min(shv0_.coeffs[3], shv1_.coeffs[3], shv2_.coeffs[3], shv3_.coeffs[3])
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec2<T> min(const shvec2<T> &shv_, U v_)
{
  shvec2<T> res=
  {
    shv_.coeffs[0]<v_?shv_.coeffs[0]:v_,
    shv_.coeffs[1]<v_?shv_.coeffs[1]:v_,
    shv_.coeffs[2]<v_?shv_.coeffs[2]:v_,
    shv_.coeffs[3]<v_?shv_.coeffs[3]:v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec2<T> min(U v_, const shvec2<T> &shv_)
{
  shvec2<T> res=
  {
    v_<shv_.coeffs[0]?v_:shv_.coeffs[0],
    v_<shv_.coeffs[1]?v_:shv_.coeffs[1],
    v_<shv_.coeffs[2]?v_:shv_.coeffs[2],
    v_<shv_.coeffs[3]?v_:shv_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> max(const shvec2<T> &shv_)
{
  return max(shv_.coeffs[0], shv_.coeffs[1], shv_.coeffs[2], shv_.coeffs[3]);
}
//----

template<typename T>
PFC_INLINE shvec2<T> max(const shvec2<T> &shv0_, const shvec2<T> &shv1_)
{
  shvec2<T> res=
  {
    shv0_.coeffs[0]>shv1_.coeffs[0]?shv0_.coeffs[0]:shv1_.coeffs[0],
    shv0_.coeffs[1]>shv1_.coeffs[1]?shv0_.coeffs[1]:shv1_.coeffs[1],
    shv0_.coeffs[2]>shv1_.coeffs[2]?shv0_.coeffs[2]:shv1_.coeffs[2],
    shv0_.coeffs[3]>shv1_.coeffs[3]?shv0_.coeffs[3]:shv1_.coeffs[3]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> max(const shvec2<T> &shv0_, const shvec2<T> &shv1_, const shvec2<T> &shv2_)
{
  shvec2<T> res=
  {
    max(shv0_.coeffs[0], shv1_.coeffs[1], shv2_.coeffs[0]),
    max(shv0_.coeffs[1], shv1_.coeffs[1], shv2_.coeffs[1]),
    max(shv0_.coeffs[2], shv1_.coeffs[2], shv2_.coeffs[2]),
    max(shv0_.coeffs[3], shv1_.coeffs[3], shv2_.coeffs[3])
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec2<T> max(const shvec2<T> &shv0_, const shvec2<T> &shv1_, const shvec2<T> &shv2_, const shvec2<T> &shv3_)
{
  shvec2<T> res=
  {
    max(shv0_.coeffs[0], shv1_.coeffs[1], shv2_.coeffs[0], shv3_.coeffs[0]),
    max(shv0_.coeffs[1], shv1_.coeffs[1], shv2_.coeffs[1], shv3_.coeffs[1]),
    max(shv0_.coeffs[2], shv1_.coeffs[2], shv2_.coeffs[2], shv3_.coeffs[2]),
    max(shv0_.coeffs[3], shv1_.coeffs[3], shv2_.coeffs[3], shv3_.coeffs[3])
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec2<T> max(const shvec2<T> &shv_, U v_)
{
  shvec2<T> res=
  {
    shv_.coeffs[0]>v_?shv_.coeffs[0]:v_,
    shv_.coeffs[1]>v_?shv_.coeffs[1]:v_,
    shv_.coeffs[2]>v_?shv_.coeffs[2]:v_,
    shv_.coeffs[3]>v_?shv_.coeffs[3]:v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec2<T> max(U v_, const shvec2<T> &shv_)
{
  shvec2<T> res=
  {
    v_>shv_.coeffs[0]?v_:shv_.coeffs[0],
    v_>shv_.coeffs[1]?v_:shv_.coeffs[1],
    v_>shv_.coeffs[2]?v_:shv_.coeffs[2],
    v_>shv_.coeffs[3]?v_:shv_.coeffs[3]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec2<T> mul(const shvec2<T> &shv0_, const shvec2<T> &shv1_)
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

template<typename T, typename U, typename V>
PFC_INLINE shvec2<T> madd(const shvec2<T> &shv0_,
                          const shvec2<U> &shv1_,
                          const shvec2<V> &shv2_)
{
  shvec2<T> res=
  {
    shv0_.coeffs[0]*shv1_.coeffs[0]+shv2_.coeffs[0],
    shv0_.coeffs[1]*shv1_.coeffs[1]+shv2_.coeffs[1],
    shv0_.coeffs[2]*shv1_.coeffs[2]+shv2_.coeffs[2],
    shv0_.coeffs[3]*shv1_.coeffs[3]+shv2_.coeffs[3]
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE shvec2<T> madd(const shvec2<T> &shv_,
                          U mul_,
                          V add_)
{
  shvec2<T> res=
  {
    shv_.coeffs[0]*mul_+add_,
    shv_.coeffs[1]*mul_+add_,
    shv_.coeffs[2]*mul_+add_,
    shv_.coeffs[3]*mul_+add_
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE shvec2<T> madd(const shvec2<T> &shv_,
                          const shvec2<U> &mul_,
                          V add_)
{
  shvec2<T> res=
  {
    shv_.coeffs[0]*mul_.coeffs[0]+add_,
    shv_.coeffs[1]*mul_.coeffs[1]+add_,
    shv_.coeffs[2]*mul_.coeffs[2]+add_,
    shv_.coeffs[3]*mul_.coeffs[3]+add_
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE shvec2<T> madd(const shvec2<T> &shv_,
                          U mul_,
                          const shvec2<V> &add_)
{
  shvec2<T> res=
  {
    shv_.coeffs[0]*mul_+add_.coeffs[0],
    shv_.coeffs[1]*mul_+add_.coeffs[1],
    shv_.coeffs[2]*mul_+add_.coeffs[2],
    shv_.coeffs[3]*mul_+add_.coeffs[3]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE T dot(const shvec2<T> &shv0_, const shvec2<U> &shv1_)
{
  return  shv0_.coeffs[0]*shv1_.coeffs[0]
         +shv0_.coeffs[1]*shv1_.coeffs[1]
         +shv0_.coeffs[2]*shv1_.coeffs[2]
         +shv0_.coeffs[3]*shv1_.coeffs[3];
}
//----

template<typename T, typename U>
PFC_INLINE void sh_basis(shvec2<T> &shv_, const vec3<U> &dir_)
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
//----

template<typename T, typename U>
shvec2<T> sh_product(const shvec2<T> &shv_, const zhvec2<U> &zhv_)
{
  shvec2<T> res=
  {
    shv0_.coeffs[0]*zhv_.coeffs[0],
    shv0_.coeffs[1]*zhv_.coeffs[1],
    shv0_.coeffs[2]*zhv_.coeffs[1],
    shv0_.coeffs[3]*zhv_.coeffs[1]
  };
  return res;
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_real1(shvec2<T> &shvr_, Rng &rng_)
{
  typedef typename math<T>::scalar_t scalar_t;
  shvr_.coeffs[0]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[1]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[2]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[3]=scalar_t(rng_.rand_real1());
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_ureal1(shvec2<T> &shvr_, Rng &rng_)
{
  typedef typename math<T>::scalar_t scalar_t;
  shvr_.coeffs[0]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[1]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[2]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[3]=scalar_t(rng_.rand_ureal1());
}
//----------------------------------------------------------------------------


//============================================================================
// shvec3 ops
//============================================================================
template<typename T>
PFC_INLINE bool is_zero(const shvec3<T> &shv_)
{
  return    shv_.coeffs[0]==0
         && shv_.coeffs[1]==0
         && shv_.coeffs[2]==0
         && shv_.coeffs[3]==0
         && shv_.coeffs[4]==0
         && shv_.coeffs[5]==0
         && shv_.coeffs[6]==0
         && shv_.coeffs[7]==0
         && shv_.coeffs[8]==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const shvec3<T> &shv_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return    shv_.coeffs[0]>=0 && shv_.coeffs[0]<=scalar_t(1)
         && shv_.coeffs[1]>=0 && shv_.coeffs[1]<=scalar_t(1)
         && shv_.coeffs[2]>=0 && shv_.coeffs[2]<=scalar_t(1)
         && shv_.coeffs[3]>=0 && shv_.coeffs[3]<=scalar_t(1)
         && shv_.coeffs[4]>=0 && shv_.coeffs[4]<=scalar_t(1)
         && shv_.coeffs[5]>=0 && shv_.coeffs[5]<=scalar_t(1)
         && shv_.coeffs[6]>=0 && shv_.coeffs[6]<=scalar_t(1)
         && shv_.coeffs[7]>=0 && shv_.coeffs[7]<=scalar_t(1)
         && shv_.coeffs[8]>=0 && shv_.coeffs[8]<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const shvec3<T> &shv_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return    shv_.coeffs[0]>=scalar_t(-1) && shv_.coeffs[0]<=scalar_t(1)
         && shv_.coeffs[1]>=scalar_t(-1) && shv_.coeffs[1]<=scalar_t(1)
         && shv_.coeffs[2]>=scalar_t(-1) && shv_.coeffs[2]<=scalar_t(1)
         && shv_.coeffs[3]>=scalar_t(-1) && shv_.coeffs[3]<=scalar_t(1)
         && shv_.coeffs[4]>=scalar_t(-1) && shv_.coeffs[4]<=scalar_t(1)
         && shv_.coeffs[5]>=scalar_t(-1) && shv_.coeffs[5]<=scalar_t(1)
         && shv_.coeffs[6]>=scalar_t(-1) && shv_.coeffs[6]<=scalar_t(1)
         && shv_.coeffs[7]>=scalar_t(-1) && shv_.coeffs[7]<=scalar_t(1)
         && shv_.coeffs[8]>=scalar_t(-1) && shv_.coeffs[8]<=scalar_t(1);
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const shvec3<T> &shv0_, const shvec3<U> &shv1_)
{
  return    shv0_.coeffs[0]==shv1_.coeffs[0]
         && shv0_.coeffs[1]==shv1_.coeffs[1]
         && shv0_.coeffs[2]==shv1_.coeffs[2]
         && shv0_.coeffs[3]==shv1_.coeffs[3]
         && shv0_.coeffs[4]==shv1_.coeffs[4]
         && shv0_.coeffs[5]==shv1_.coeffs[5]
         && shv0_.coeffs[6]==shv1_.coeffs[6]
         && shv0_.coeffs[7]==shv1_.coeffs[7]
         && shv0_.coeffs[8]==shv1_.coeffs[8];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const shvec3<T> &shv_, U v_)
{
  return    shv_.coeffs[0]==v_
         && shv_.coeffs[1]==v_
         && shv_.coeffs[2]==v_
         && shv_.coeffs[3]==v_
         && shv_.coeffs[4]==v_
         && shv_.coeffs[5]==v_
         && shv_.coeffs[6]==v_
         && shv_.coeffs[7]==v_
         && shv_.coeffs[8]==v_;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(U v_, const shvec3<T> &shv_)
{
  return    v_==shv_.coeffs[0]
         && v_==shv_.coeffs[1]
         && v_==shv_.coeffs[2]
         && v_==shv_.coeffs[3]
         && v_==shv_.coeffs[4]
         && v_==shv_.coeffs[5]
         && v_==shv_.coeffs[6]
         && v_==shv_.coeffs[7]
         && v_==shv_.coeffs[8];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const shvec3<T> &shv0_, const shvec3<U> &shv1_)
{
  return    shv0_.coeffs[0]!=shv1_.coeffs[0]
         || shv0_.coeffs[1]!=shv1_.coeffs[1]
         || shv0_.coeffs[2]!=shv1_.coeffs[2]
         || shv0_.coeffs[3]!=shv1_.coeffs[3]
         || shv0_.coeffs[4]!=shv1_.coeffs[4]
         || shv0_.coeffs[5]!=shv1_.coeffs[5]
         || shv0_.coeffs[6]!=shv1_.coeffs[6]
         || shv0_.coeffs[7]!=shv1_.coeffs[7]
         || shv0_.coeffs[8]!=shv1_.coeffs[8];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const shvec3<T> &shv_, U v_)
{
  return    shv_.coeffs[0]!=v_
         || shv_.coeffs[1]!=v_
         || shv_.coeffs[2]!=v_
         || shv_.coeffs[3]!=v_
         || shv_.coeffs[4]!=v_
         || shv_.coeffs[5]!=v_
         || shv_.coeffs[6]!=v_
         || shv_.coeffs[7]!=v_
         || shv_.coeffs[8]!=v_;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(U v_, const shvec3<T> &shv_)
{
  return    v_!=shv_.coeffs[0]
         || v_!=shv_.coeffs[1]
         || v_!=shv_.coeffs[2]
         || v_!=shv_.coeffs[3]
         || v_!=shv_.coeffs[4]
         || v_!=shv_.coeffs[5]
         || v_!=shv_.coeffs[6]
         || v_!=shv_.coeffs[7]
         || v_!=shv_.coeffs[8];
}
//----

template<typename T, typename U>
PFC_INLINE void operator+=(shvec3<T> &shvr_, const shvec3<U> &shv_)
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

template<typename T, typename U>
PFC_INLINE void operator+=(shvec3<T> &shvr_, U v_)
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

template<typename T, typename U>
PFC_INLINE void operator-=(shvec3<T> &shvr_, const shvec3<U> &shv_)
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

template<typename T, typename U>
PFC_INLINE void operator-=(shvec3<T> &shvr_, U v_)
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

template<typename T, typename U>
PFC_INLINE void operator*=(shvec3<T> &shvr_, const shvec3<U> &shv_)
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

template<typename T, typename U>
PFC_INLINE void operator*=(shvec3<T> &shvr_, U v_)
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

template<typename T, typename U>
PFC_INLINE void operator*=(shvec3<T> &shvr_, const shmat3<U> &shm_)
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

template<typename T, typename U>
PFC_INLINE void operator/=(shvec3<T> &shvr_, const shvec3<U> &shv_)
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

template<typename T, typename U>
PFC_INLINE void operator/=(shvec3<T> &shvr_, U v_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator+(const shvec3<T> &shv0_, const shvec3<U> &shv1_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator+(const shvec3<T> &shv_, U v_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator+(U v_, const shvec3<T> &shv_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator-(const shvec3<T> &shv0_, const shvec3<U> &shv1_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator-(const shvec3<T> &shv_, U v_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator-(U v_, const shvec3<T> &shv_)
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
PFC_INLINE shvec3<T> operator-(const shvec3<T> &shv_)
{
  shvec3<T> res=
  {
    -shv_.coeffs[0],
    -shv_.coeffs[1],
    -shv_.coeffs[2],
    -shv_.coeffs[3],
    -shv_.coeffs[4],
    -shv_.coeffs[5],
    -shv_.coeffs[6],
    -shv_.coeffs[7],
    -shv_.coeffs[8]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec3<T> operator*(const shvec3<T> &shv0_, const shvec3<U> &shv1_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator*(const shvec3<T> &shv_, U v_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator*(U v_, const shvec3<T> &shv_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator*(const shvec3<T> &shv_, const shmat3<U> &shm_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator*(const shmat3<T> &shm_, const shvec3<U> &shv_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator/(const shvec3<T> &shv0_, const shvec3<U> &shv1_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator/(const shvec3<T> &shv_, U v_)
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

template<typename T, typename U>
PFC_INLINE shvec3<T> operator/(U v_, const shvec3<T> &shv_)
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
PFC_INLINE shvec3<T> min(const shvec3<T> &shv_)
{
  return min(min(shv_.coeffs[0], shv_.coeffs[1], shv_.coeffs[2], shv_.coeffs[3]),
             min(shv_.coeffs[4], shv_.coeffs[5], shv_.coeffs[6], shv_.coeffs[7]),
             shv_.coeffs[8]);
}
//----

template<typename T>
PFC_INLINE shvec3<T> min(const shvec3<T> &shv0_, const shvec3<T> &shv1_)
{
  shvec3<T> res=
  {
    shv0_.coeffs[0]<shv1_.coeffs[0]?shv0_.coeffs[0]:shv1_.coeffs[0],
    shv0_.coeffs[1]<shv1_.coeffs[1]?shv0_.coeffs[1]:shv1_.coeffs[1],
    shv0_.coeffs[2]<shv1_.coeffs[2]?shv0_.coeffs[2]:shv1_.coeffs[2],
    shv0_.coeffs[3]<shv1_.coeffs[3]?shv0_.coeffs[3]:shv1_.coeffs[3],
    shv0_.coeffs[4]<shv1_.coeffs[4]?shv0_.coeffs[4]:shv1_.coeffs[4],
    shv0_.coeffs[5]<shv1_.coeffs[5]?shv0_.coeffs[5]:shv1_.coeffs[5],
    shv0_.coeffs[6]<shv1_.coeffs[6]?shv0_.coeffs[6]:shv1_.coeffs[6],
    shv0_.coeffs[7]<shv1_.coeffs[7]?shv0_.coeffs[7]:shv1_.coeffs[7],
    shv0_.coeffs[8]<shv1_.coeffs[8]?shv0_.coeffs[8]:shv1_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> min(const shvec3<T> &shv0_, const shvec3<T> &shv1_, const shvec3<T> &shv2_)
{
  shvec3<T> res=
  {
    min(shv0_.coeffs[0], shv1_.coeffs[1], shv2_.coeffs[0]),
    min(shv0_.coeffs[1], shv1_.coeffs[1], shv2_.coeffs[1]),
    min(shv0_.coeffs[2], shv1_.coeffs[2], shv2_.coeffs[2]),
    min(shv0_.coeffs[3], shv1_.coeffs[3], shv2_.coeffs[3]),
    min(shv0_.coeffs[4], shv1_.coeffs[4], shv2_.coeffs[4]),
    min(shv0_.coeffs[5], shv1_.coeffs[5], shv2_.coeffs[5]),
    min(shv0_.coeffs[6], shv1_.coeffs[6], shv2_.coeffs[6]),
    min(shv0_.coeffs[7], shv1_.coeffs[7], shv2_.coeffs[7]),
    min(shv0_.coeffs[8], shv1_.coeffs[8], shv2_.coeffs[8])
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> min(const shvec3<T> &shv0_, const shvec3<T> &shv1_, const shvec3<T> &shv2_, const shvec3<T> &shv3_)
{
  shvec3<T> res=
  {
    min(shv0_.coeffs[0], shv1_.coeffs[1], shv2_.coeffs[0], shv3_.coeffs[0]),
    min(shv0_.coeffs[1], shv1_.coeffs[1], shv2_.coeffs[1], shv3_.coeffs[1]),
    min(shv0_.coeffs[2], shv1_.coeffs[2], shv2_.coeffs[2], shv3_.coeffs[2]),
    min(shv0_.coeffs[3], shv1_.coeffs[3], shv2_.coeffs[3], shv3_.coeffs[3]),
    min(shv0_.coeffs[4], shv1_.coeffs[4], shv2_.coeffs[4], shv3_.coeffs[4]),
    min(shv0_.coeffs[5], shv1_.coeffs[5], shv2_.coeffs[5], shv3_.coeffs[5]),
    min(shv0_.coeffs[6], shv1_.coeffs[6], shv2_.coeffs[6], shv3_.coeffs[6]),
    min(shv0_.coeffs[7], shv1_.coeffs[7], shv2_.coeffs[7], shv3_.coeffs[7]),
    min(shv0_.coeffs[8], shv1_.coeffs[8], shv2_.coeffs[8], shv3_.coeffs[8])
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec3<T> min(const shvec3<T> &shv_, U v_)
{
  shvec3<T> res=
  {
    shv_.coeffs[0]<v_?shv_.coeffs[0]:v_,
    shv_.coeffs[1]<v_?shv_.coeffs[1]:v_,
    shv_.coeffs[2]<v_?shv_.coeffs[2]:v_,
    shv_.coeffs[3]<v_?shv_.coeffs[3]:v_,
    shv_.coeffs[4]<v_?shv_.coeffs[4]:v_,
    shv_.coeffs[5]<v_?shv_.coeffs[5]:v_,
    shv_.coeffs[6]<v_?shv_.coeffs[6]:v_,
    shv_.coeffs[7]<v_?shv_.coeffs[7]:v_,
    shv_.coeffs[8]<v_?shv_.coeffs[8]:v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec3<T> min(U v_, const shvec3<T> &shv_)
{
  shvec3<T> res=
  {
    v_<shv_.coeffs[0]?v_:shv_.coeffs[0],
    v_<shv_.coeffs[1]?v_:shv_.coeffs[1],
    v_<shv_.coeffs[2]?v_:shv_.coeffs[2],
    v_<shv_.coeffs[3]?v_:shv_.coeffs[3],
    v_<shv_.coeffs[4]?v_:shv_.coeffs[4],
    v_<shv_.coeffs[5]?v_:shv_.coeffs[5],
    v_<shv_.coeffs[6]?v_:shv_.coeffs[6],
    v_<shv_.coeffs[7]?v_:shv_.coeffs[7],
    v_<shv_.coeffs[8]?v_:shv_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> max(const shvec3<T> &shv_)
{
  return max(max(shv_.coeffs[0], shv_.coeffs[1], shv_.coeffs[2], shv_.coeffs[3]),
             max(shv_.coeffs[4], shv_.coeffs[5], shv_.coeffs[6], shv_.coeffs[7]),
             shv_.coeffs[8]);
}
//----

template<typename T>
PFC_INLINE shvec3<T> max(const shvec3<T> &shv0_, const shvec3<T> &shv1_)
{
  shvec3<T> res=
  {
    shv0_.coeffs[0]>shv1_.coeffs[0]?shv0_.coeffs[0]:shv1_.coeffs[0],
    shv0_.coeffs[1]>shv1_.coeffs[1]?shv0_.coeffs[1]:shv1_.coeffs[1],
    shv0_.coeffs[2]>shv1_.coeffs[2]?shv0_.coeffs[2]:shv1_.coeffs[2],
    shv0_.coeffs[3]>shv1_.coeffs[3]?shv0_.coeffs[3]:shv1_.coeffs[3],
    shv0_.coeffs[4]>shv1_.coeffs[4]?shv0_.coeffs[4]:shv1_.coeffs[4],
    shv0_.coeffs[5]>shv1_.coeffs[5]?shv0_.coeffs[5]:shv1_.coeffs[5],
    shv0_.coeffs[6]>shv1_.coeffs[6]?shv0_.coeffs[6]:shv1_.coeffs[6],
    shv0_.coeffs[7]>shv1_.coeffs[7]?shv0_.coeffs[7]:shv1_.coeffs[7],
    shv0_.coeffs[8]>shv1_.coeffs[8]?shv0_.coeffs[8]:shv1_.coeffs[8]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> max(const shvec3<T> &shv0_, const shvec3<T> &shv1_, const shvec3<T> &shv2_)
{
  shvec3<T> res=
  {
    max(shv0_.coeffs[0], shv1_.coeffs[0], shv2_.coeffs[0]),
    max(shv0_.coeffs[1], shv1_.coeffs[1], shv2_.coeffs[1]),
    max(shv0_.coeffs[2], shv1_.coeffs[2], shv2_.coeffs[2]),
    max(shv0_.coeffs[3], shv1_.coeffs[3], shv2_.coeffs[3]),
    max(shv0_.coeffs[4], shv1_.coeffs[4], shv2_.coeffs[4]),
    max(shv0_.coeffs[5], shv1_.coeffs[5], shv2_.coeffs[5]),
    max(shv0_.coeffs[6], shv1_.coeffs[6], shv2_.coeffs[6]),
    max(shv0_.coeffs[7], shv1_.coeffs[7], shv2_.coeffs[7]),
    max(shv0_.coeffs[8], shv1_.coeffs[8], shv2_.coeffs[8])
  };
  return res;
}
//----

template<typename T>
PFC_INLINE shvec3<T> max(const shvec3<T> &shv0_, const shvec3<T> &shv1_, const shvec3<T> &shv2_, const shvec3<T> &shv3_)
{
  shvec3<T> res=
  {
    max(shv0_.coeffs[0], shv1_.coeffs[0], shv2_.coeffs[0], shv3_.coeffs[0]),
    max(shv0_.coeffs[1], shv1_.coeffs[1], shv2_.coeffs[1], shv3_.coeffs[1]),
    max(shv0_.coeffs[2], shv1_.coeffs[2], shv2_.coeffs[2], shv3_.coeffs[2]),
    max(shv0_.coeffs[3], shv1_.coeffs[3], shv2_.coeffs[3], shv3_.coeffs[3]),
    max(shv0_.coeffs[4], shv1_.coeffs[4], shv2_.coeffs[4], shv3_.coeffs[4]),
    max(shv0_.coeffs[5], shv1_.coeffs[5], shv2_.coeffs[5], shv3_.coeffs[5]),
    max(shv0_.coeffs[6], shv1_.coeffs[6], shv2_.coeffs[6], shv3_.coeffs[6]),
    max(shv0_.coeffs[7], shv1_.coeffs[7], shv2_.coeffs[7], shv3_.coeffs[7]),
    max(shv0_.coeffs[8], shv1_.coeffs[8], shv2_.coeffs[8], shv3_.coeffs[8])
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec3<T> max(const shvec3<T> &shv_, U v_)
{
  shvec3<T> res=
  {
    shv_.coeffs[0]>v_?shv_.coeffs[0]:v_,
    shv_.coeffs[1]>v_?shv_.coeffs[1]:v_,
    shv_.coeffs[2]>v_?shv_.coeffs[2]:v_,
    shv_.coeffs[3]>v_?shv_.coeffs[3]:v_,
    shv_.coeffs[4]>v_?shv_.coeffs[4]:v_,
    shv_.coeffs[5]>v_?shv_.coeffs[5]:v_,
    shv_.coeffs[6]>v_?shv_.coeffs[6]:v_,
    shv_.coeffs[7]>v_?shv_.coeffs[7]:v_,
    shv_.coeffs[8]>v_?shv_.coeffs[8]:v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec3<T> max(U v_, const shvec3<T> &shv_)
{
  shvec3<T> res=
  {
    v_>shv_.coeffs[0]?v_:shv_.coeffs[0],
    v_>shv_.coeffs[1]?v_:shv_.coeffs[1],
    v_>shv_.coeffs[2]?v_:shv_.coeffs[2],
    v_>shv_.coeffs[3]?v_:shv_.coeffs[3],
    v_>shv_.coeffs[4]?v_:shv_.coeffs[4],
    v_>shv_.coeffs[5]?v_:shv_.coeffs[5],
    v_>shv_.coeffs[6]?v_:shv_.coeffs[6],
    v_>shv_.coeffs[7]?v_:shv_.coeffs[7],
    v_>shv_.coeffs[8]?v_:shv_.coeffs[8]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE shvec3<T> mul(const shvec3<T> &shv0_, const shvec3<T> &shv1_)
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

template<typename T, typename U, typename V>
PFC_INLINE shvec3<T> madd(const shvec3<T> &shv0_,
                          const shvec3<U> &shv1_,
                          const shvec3<V> &shv2_)
{
  shvec3<T> res=
  {
    shv0_.coeffs[0]*shv1_.coeffs[0]+shv2_.coeffs[0],
    shv0_.coeffs[1]*shv1_.coeffs[1]+shv2_.coeffs[1],
    shv0_.coeffs[2]*shv1_.coeffs[2]+shv2_.coeffs[2],
    shv0_.coeffs[3]*shv1_.coeffs[3]+shv2_.coeffs[3],
    shv0_.coeffs[4]*shv1_.coeffs[4]+shv2_.coeffs[4],
    shv0_.coeffs[5]*shv1_.coeffs[5]+shv2_.coeffs[5],
    shv0_.coeffs[6]*shv1_.coeffs[6]+shv2_.coeffs[6],
    shv0_.coeffs[7]*shv1_.coeffs[7]+shv2_.coeffs[7],
    shv0_.coeffs[8]*shv1_.coeffs[8]+shv2_.coeffs[8]
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE shvec3<T> madd(const shvec3<T> &shv_,
                          U mul_,
                          V add_)
{
  shvec3<T> res=
  {
    shv_.coeffs[0]*mul_+add_,
    shv_.coeffs[1]*mul_+add_,
    shv_.coeffs[2]*mul_+add_,
    shv_.coeffs[3]*mul_+add_,
    shv_.coeffs[4]*mul_+add_,
    shv_.coeffs[5]*mul_+add_,
    shv_.coeffs[6]*mul_+add_,
    shv_.coeffs[7]*mul_+add_,
    shv_.coeffs[8]*mul_+add_
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE shvec3<T> madd(const shvec3<T> &shv_,
                          const shvec3<U> &mul_,
                          V add_)
{
  shvec3<T> res=
  {
    shv_.coeffs[0]*mul_.coeffs[0]+add_,
    shv_.coeffs[1]*mul_.coeffs[1]+add_,
    shv_.coeffs[2]*mul_.coeffs[2]+add_,
    shv_.coeffs[3]*mul_.coeffs[3]+add_,
    shv_.coeffs[4]*mul_.coeffs[4]+add_,
    shv_.coeffs[5]*mul_.coeffs[5]+add_,
    shv_.coeffs[6]*mul_.coeffs[6]+add_,
    shv_.coeffs[7]*mul_.coeffs[7]+add_,
    shv_.coeffs[8]*mul_.coeffs[8]+add_
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE shvec3<T> madd(const shvec3<T> &shv_,
                          U mul_,
                          const shvec3<V> &add_)
{
  shvec3<T> res=
  {
    shv_.coeffs[0]*mul_+add_.coeffs[0],
    shv_.coeffs[1]*mul_+add_.coeffs[1],
    shv_.coeffs[2]*mul_+add_.coeffs[2],
    shv_.coeffs[3]*mul_+add_.coeffs[3],
    shv_.coeffs[4]*mul_+add_.coeffs[4],
    shv_.coeffs[5]*mul_+add_.coeffs[5],
    shv_.coeffs[6]*mul_+add_.coeffs[6],
    shv_.coeffs[7]*mul_+add_.coeffs[7],
    shv_.coeffs[8]*mul_+add_.coeffs[8]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE T dot(const shvec3<T> &shv0_, const shvec3<U> &shv1_)
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

template<typename T, typename U>
PFC_INLINE void sh_basis(shvec3<T> &shv_, const vec3<U> &dir_)
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
  typedef math<T>::scalar_t scalar_t;
  static const scalar_t s_f0=scalar_t(0.3194382824999699566298819526759); // sqrt(5/49)
  static const scalar_t s_f1=scalar_t(0.4472135954999579392818347337463); // sqrt(1/5)
  static const scalar_t s_f2=scalar_t(0.5532833351724881264541807713975); // sqrt(15/49)
  static const scalar_t s_f3=scalar_t(0.6388765649999399132597639053518); // 2*sqrt(5/49)
  static const scalar_t s_f4=scalar_t(0.7745966692414833770358530799565); // sqrt(3/5)
  static const scalar_t s_f5=scalar_t(0.8944271909999158785636694674925); // 2*sqrt(1/5)
  static const scalar_t s_scale=scalar_t(0.07957747154594766788444188168626); // 1/(4pi)
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
  };
  return res;
}
//----

template<typename T, typename U>
shvec3<T> sh_product(const shvec3<T> &shv_, const zhvec3<U> &zhv_)
{
  shvec3<T> res=
  {
    shv0_.coeffs[0]*zhv_.coeffs[0],
    shv0_.coeffs[1]*zhv_.coeffs[1],
    shv0_.coeffs[2]*zhv_.coeffs[1],
    shv0_.coeffs[3]*zhv_.coeffs[1],
    shv0_.coeffs[4]*zhv_.coeffs[2],
    shv0_.coeffs[5]*zhv_.coeffs[2],
    shv0_.coeffs[6]*zhv_.coeffs[2],
    shv0_.coeffs[7]*zhv_.coeffs[2],
    shv0_.coeffs[8]*zhv_.coeffs[2]
  };
  return res;
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_real1(shvec3<T> &shvr_, Rng &rng_)
{
  typedef typename math<T>::scalar_t scalar_t;
  shvr_.coeffs[0]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[1]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[2]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[3]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[4]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[5]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[6]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[7]=scalar_t(rng_.rand_real1());
  shvr_.coeffs[8]=scalar_t(rng_.rand_real1());
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_ureal1(shvec3<T> &shvr_, Rng &rng_)
{
  typedef typename math<T>::scalar_t scalar_t;
  shvr_.coeffs[0]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[1]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[2]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[3]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[4]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[5]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[6]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[7]=scalar_t(rng_.rand_ureal1());
  shvr_.coeffs[8]=scalar_t(rng_.rand_ureal1());
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
PFC_INLINE bool is_zero(const zhvec2<T> &zhv_)
{
  return    zhv_.coeffs[0]==0
         && zhv_.coeffs[1]==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const zhvec2<T> &zhv_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return    zhv_.coeffs[0]>=0 && zhv_.coeffs[0]<=scalar_t(1)
         && zhv_.coeffs[1]>=0 && zhv_.coeffs[1]<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const zhvec2<T> &zhv_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return    zhv_.coeffs[0]>=scalar_t(-1) && zhv_.coeffs[0]<=scalar_t(1)
         && zhv_.coeffs[1]>=scalar_t(-1) && zhv_.coeffs[1]<=scalar_t(1);
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const zhvec2<T> &zhv0_, const zhvec2<U> &zhv1_)
{
  return    zhv0_.coeffs[0]==zhv1_.coeffs[0]
         && zhv0_.coeffs[1]==zhv1_.coeffs[1];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const zhvec2<T> &zhv_, U v_)
{
  return    zhv_.coeffs[0]==v_
         && zhv_.coeffs[1]==v_;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(U v_, const zhvec2<T> &zhv_)
{
  return    v_==zhv_.coeffs[0]
         && v_==zhv_.coeffs[1];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const zhvec2<T> &zhv0_, const zhvec2<U> &zhv1_)
{
  return    zhv0_.coeffs[0]!=zhv1_.coeffs[0]
         || zhv0_.coeffs[1]!=zhv1_.coeffs[1];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const zhvec2<T> &zhv_, U v_)
{
  return    zhv_.coeffs[0]!=v_
         || zhv_.coeffs[1]!=v_;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(U v_, const zhvec2<T> &zhv_)
{
  return    v_!=zhv_.coeffs[0]
         || v_!=zhv_.coeffs[1];
}
//----

template<typename T, typename U>
PFC_INLINE void operator+=(zhvec2<T> &zhvr_, const zhvec2<U> &zhv_)
{
  zhvr_.coeffs[0]+=zhv_.coeffs[0];
  zhvr_.coeffs[1]+=zhv_.coeffs[1];
}
//----

template<typename T, typename U>
PFC_INLINE void operator+=(zhvec2<T> &zhvr_, U v_)
{
  zhvr_.coeffs[0]+=v_;
  zhvr_.coeffs[1]+=v_;
}
//----

template<typename T, typename U>
PFC_INLINE void operator-=(zhvec2<T> &zhvr_, const zhvec2<U>&)
{
  zhvr_.coeffs[0]-=zhv_.coeffs[0];
  zhvr_.coeffs[1]-=zhv_.coeffs[1];
}
//----

template<typename T, typename U>
PFC_INLINE void operator-=(zhvec2<T> &zhvr_, U v_)
{
  zhvr_.coeffs[0]-=v_;
  zhvr_.coeffs[1]-=v_;
}
//----

template<typename T, typename U>
PFC_INLINE void operator*=(zhvec2<T> &zhvr_, const zhvec2<U>&)
{
  zhvr_.coeffs[0]*=zhv_.coeffs[0];
  zhvr_.coeffs[1]*=zhv_.coeffs[1];
}
//----

template<typename T, typename U>
PFC_INLINE void operator*=(zhvec2<T> &zhvr_, U v_)
{
  zhvr_.coeffs[0]*=v_;
  zhvr_.coeffs[1]*=v_;
}
//----

template<typename T, typename U>
PFC_INLINE void operator/=(zhvec2<T> &zhvr_, const zhvec2<U> &zhv_)
{
  zhvr_.coeffs[0]/=zhv_.coeffs[0];
  zhvr_.coeffs[1]/=zhv_.coeffs[1];
}
//----

template<typename T, typename U>
PFC_INLINE void operator/=(zhvec2<T> &zhvr_, U v_)
{
  T rcp_v=rcp(v_);
  zhvr_.coeffs[0]*=rcp_v;
  zhvr_.coeffs[1]*=rcp_v;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator+(const zhvec2<T> &zhv0_, const zhvec2<U> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]+zhv1_.coeffs[0],
    zhv0_.coeffs[1]+zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator+(const zhvec2<T> &zhv_, U v_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]+v_,
    zhv_.coeffs[1]+v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator+(U v_, const zhvec2<T> &zhv_)
{
  zhvec2<T> res=
  {
    v_+zhv_.coeffs[0],
    v_+zhv_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator-(const zhvec2<T> &zhv0_, const zhvec2<U> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]-zhv1_.coeffs[0],
    zhv0_.coeffs[1]-zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator-(const zhvec2<T> &zhv_, U v_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]-v_,
    zhv_.coeffs[1]-v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator-(U v_, const zhvec2<T> &zhv_)
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
PFC_INLINE zhvec2<T> operator-(const zhvec2<T> &zhv_)
{
  zhvec2<T> res=
  {
    -zhv_.coeffs[0],
    -zhv_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator*(const zhvec2<T> &zhv0_, const zhvec2<U> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]*zhv1_.coeffs[0],
    zhv0_.coeffs[1]*zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator*(const zhvec2<T> &zhv_, U v_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]*v_,
    zhv_.coeffs[1]*v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator*(T U_, const zhvec2<T> &zhv_)
{
  zhvec2<T> res=
  {
    v_*zhv_.coeffs[0],
    v_*zhv_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator/(const zhvec2<T> &zhv0_, const zhvec2<U> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]/zhv1_.coeffs[0],
    zhv0_.coeffs[1]/zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator/(const zhvec2<T> &zhv_, U v_)
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

template<typename T, typename U>
PFC_INLINE zhvec2<T> operator/(U v_, const zhvec2<T> &zhv_)
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
PFC_INLINE zhvec2<T> min(const zhvec2<T> &zhv_)
{
  return zhv_.coeffs[0]<zhv_.coeffs[1]?zhv_.coeffs[0]:zhv_.coeffs[1];
}
//----

template<typename T>
PFC_INLINE zhvec2<T> min(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]<zhv1_.coeffs[0]?zhv0_.coeffs[0]:zhv1_.coeffs[0],
    zhv0_.coeffs[1]<zhv1_.coeffs[1]?zhv0_.coeffs[1]:zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> min(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_, const zhvec2<T> &zhv2_)
{
  zhvec2<T> res=
  {
    min(zhv0_.coeffs[0], zhv1_.coeffs[1], zhv2_.coeffs[0]),
    min(zhv0_.coeffs[1], zhv1_.coeffs[1], zhv2_.coeffs[1])
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> min(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_, const zhvec2<T> &zhv2_, const zhvec2<T> &zhv3_)
{
  zhvec2<T> res=
  {
    min(zhv0_.coeffs[0], zhv1_.coeffs[1], zhv2_.coeffs[0], zhv3_.coeffs[0]),
    min(zhv0_.coeffs[1], zhv1_.coeffs[1], zhv2_.coeffs[1], zhv3_.coeffs[1])
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> min(const zhvec2<T> &zhv_, U v_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]<v_?zhv_.coeffs[0]:v_,
    zhv_.coeffs[1]<v_?zhv_.coeffs[1]:v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> min(U v_, const zhvec2<T> &zhv_)
{
  zhvec2<T> res=
  {
    v_<zhv_.coeffs[0]?v_:zhv_.coeffs[0],
    v_<zhv_.coeffs[1]?v_:zhv_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> max(const zhvec2<T> &zhv_)
{
  return zhv_.coeffs[0]>zhv_.coeffs[1]?zhv_.coeffs[0]:zhv_.coeffs[1];
}
//----

template<typename T>
PFC_INLINE zhvec2<T> max(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]>zhv1_.coeffs[0]?zhv0_.coeffs[0]:zhv1_.coeffs[0],
    zhv0_.coeffs[1]>zhv1_.coeffs[1]?zhv0_.coeffs[1]:zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> max(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_, const zhvec2<T> &zhv2_)
{
  zhvec2<T> res=
  {
    max(zhv0_.coeffs[0], zhv1_.coeffs[1], zhv2_.coeffs[0]),
    max(zhv0_.coeffs[1], zhv1_.coeffs[1], zhv2_.coeffs[1])
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec2<T> max(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_, const zhvec2<T> &zhv2_, const zhvec2<T> &zhv3_)
{
  zhvec2<T> res=
  {
    max(zhv0_.coeffs[0], zhv1_.coeffs[1], zhv2_.coeffs[0], zhv3_.coeffs[0]),
    max(zhv0_.coeffs[1], zhv1_.coeffs[1], zhv2_.coeffs[1], zhv3_.coeffs[1])
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> max(const zhvec2<T> &zhv_, U v_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]>v_?zhv_.coeffs[0]:v_,
    zhv_.coeffs[1]>v_?zhv_.coeffs[1]:v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> max(U v_, const zhvec2<T> &zhv_)
{
  zhvec2<T> res=
  {
    v_>zhv_.coeffs[0]?v_:zhv_.coeffs[0],
    v_>zhv_.coeffs[1]?v_:zhv_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec2<T> mul(const zhvec2<T> &zhv0_, const zhvec2<T> &zhv1_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]*zhv1_.coeffs[0],
    zhv0_.coeffs[1]*zhv1_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE zhvec2<T> madd(const zhvec2<T> &zhv0_,
                          const zhvec2<U> &zhv1_,
                          const zhvec2<V> &zhv2_)
{
  zhvec2<T> res=
  {
    zhv0_.coeffs[0]*zhv1_.coeffs[0]+zhv2_.coeffs[0],
    zhv0_.coeffs[1]*zhv1_.coeffs[1]+zhv2_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE zhvec2<T> madd(const zhvec2<T> &zhv_,
                          U mul_,
                          V add_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]*mul_+add_,
    zhv_.coeffs[1]*mul_+add_
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE zhvec2<T> madd(const zhvec2<T> &zhv_,
                          const zhvec2<U> &mul_,
                          V add_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]*mul_.coeffs[0]+add_,
    zhv_.coeffs[1]*mul_.coeffs[1]+add_
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE zhvec2<T> madd(const zhvec2<T> &zhv_,
                          U mul_,
                          const zhvec2<V> &add_)
{
  zhvec2<T> res=
  {
    zhv_.coeffs[0]*mul_+add_.coeffs[0],
    zhv_.coeffs[1]*mul_+add_.coeffs[1]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE T dot(const zhvec2<T> &zhv0_, const zhvec2<U> &zhv1_)
{
  return  zhv0_.coeffs[0]*zhv1_.coeffs[0]
         +zhv0_.coeffs[1]*zhv1_.coeffs[1];
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_real1(zhvec2<T> &zhvr_, Rng &rng_)
{
  typedef typename math<T>::scalar_t scalar_t;
  zhvr_.coeffs[0]=scalar_t(rng_.rand_real1());
  zhvr_.coeffs[1]=scalar_t(rng_.rand_real1());
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_ureal1(zhvec2<T> &zhvr_, Rng &rng_)
{
  typedef typename math<T>::scalar_t scalar_t;
  zhvr_.coeffs[0]=scalar_t(rng_.rand_ureal1());
  zhvr_.coeffs[1]=scalar_t(rng_.rand_ureal1());
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
PFC_INLINE bool is_zero(const zhvec3<T> &zhv_)
{
  return    zhv_.coeffs[0]==0
         && zhv_.coeffs[1]==0
         && zhv_.coeffs[2]==0;
}
//----

template<typename T>
PFC_INLINE bool is_sat(const zhvec3<T> &zhv_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return    zhv_.coeffs[0]>=0 && zhv_.coeffs[0]<=scalar_t(1)
         && zhv_.coeffs[1]>=0 && zhv_.coeffs[1]<=scalar_t(1)
         && zhv_.coeffs[2]>=0 && zhv_.coeffs[2]<=scalar_t(1);
}
//----

template<typename T>
PFC_INLINE bool is_ssat(const zhvec3<T> &zhv_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return    zhv_.coeffs[0]>=scalar_t(-1) && zhv_.coeffs[0]<=scalar_t(1)
         && zhv_.coeffs[1]>=scalar_t(-1) && zhv_.coeffs[1]<=scalar_t(1)
         && zhv_.coeffs[2]>=scalar_t(-1) && zhv_.coeffs[2]<=scalar_t(1);
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const zhvec3<T> &zhv0_, const zhvec3<U> &zhv1_)
{
  return    zhv0_.coeffs[0]==zhv1_.coeffs[0]
         && zhv0_.coeffs[1]==zhv1_.coeffs[1]
         && zhv0_.coeffs[2]==zhv1_.coeffs[2];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(const zhvec3<T> &zhv_, U v_)
{
  return    zhv_.coeffs[0]==v_
         && zhv_.coeffs[1]==v_
         && zhv_.coeffs[2]==v_;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator==(U v_, const zhvec3<T> &zhv_)
{
  return    v_==zhv_.coeffs[0]
         && v_==zhv_.coeffs[1]
         && v_==zhv_.coeffs[2];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const zhvec3<T> &zhv0_, const zhvec3<U> &zhv1_)
{
  return    zhv0_.coeffs[0]!=zhv1_.coeffs[0]
         || zhv0_.coeffs[1]!=zhv1_.coeffs[1]
         || zhv0_.coeffs[2]!=zhv1_.coeffs[2];
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(const zhvec3<T> &zhv_, U v_)
{
  return    zhv_.coeffs[0]!=v_
         || zhv_.coeffs[1]!=v_
         || zhv_.coeffs[2]!=v_;
}
//----

template<typename T, typename U>
PFC_INLINE bool operator!=(U v_, const zhvec3<T> &zhv_)
{
  return    v_!=zhv_.coeffs[0]
         || v_!=zhv_.coeffs[1]
         || v_!=zhv_.coeffs[2];
}
//----

template<typename T, typename U>
PFC_INLINE void operator+=(zhvec3<T> &zhvr_, const zhvec3<U> &zhv_)
{
  zhvr_.coeffs[0]+=zhv_.coeffs[0];
  zhvr_.coeffs[1]+=zhv_.coeffs[1];
  zhvr_.coeffs[2]+=zhv_.coeffs[2];
}
//----

template<typename T, typename U>
PFC_INLINE void operator+=(zhvec3<T> &zhvr_, U v_)
{
  zhvr_.coeffs[0]+=v_;
  zhvr_.coeffs[1]+=v_;
  zhvr_.coeffs[2]+=v_;
}
//----

template<typename T, typename U>
PFC_INLINE void operator-=(zhvec3<T> &zhvr_, const zhvec3<U>&)
{
  zhvr_.coeffs[0]-=zhv_.coeffs[0];
  zhvr_.coeffs[1]-=zhv_.coeffs[1];
  zhvr_.coeffs[2]-=zhv_.coeffs[2];
}
//----

template<typename T, typename U>
PFC_INLINE void operator-=(zhvec3<T> &zhvr_, U v_)
{
  zhvr_.coeffs[0]-=v_;
  zhvr_.coeffs[1]-=v_;
  zhvr_.coeffs[2]-=v_;
}
//----

template<typename T, typename U>
PFC_INLINE void operator*=(zhvec3<T> &zhvr_, const zhvec3<U>&)
{
  zhvr_.coeffs[0]*=zhv_.coeffs[0];
  zhvr_.coeffs[1]*=zhv_.coeffs[1];
  zhvr_.coeffs[2]*=zhv_.coeffs[2];
}
//----

template<typename T, typename U>
PFC_INLINE void operator*=(zhvec3<T> &zhvr_, U v_)
{
  zhvr_.coeffs[0]*=v_;
  zhvr_.coeffs[1]*=v_;
  zhvr_.coeffs[2]*=v_;
}
//----

template<typename T, typename U>
PFC_INLINE void operator/=(zhvec3<T> &zhvr_, const zhvec3<U> &zhv_)
{
  zhvr_.coeffs[0]/=zhv_.coeffs[0];
  zhvr_.coeffs[1]/=zhv_.coeffs[1];
  zhvr_.coeffs[2]/=zhv_.coeffs[2];
}
//----

template<typename T, typename U>
PFC_INLINE void operator/=(zhvec3<T> &zhvr_, U v_)
{
  T rcp_v=rcp(v_);
  zhvr_.coeffs[0]*=rcp_v;
  zhvr_.coeffs[1]*=rcp_v;
  zhvr_.coeffs[2]*=rcp_v;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator+(const zhvec3<T> &zhv0_, const zhvec3<U> &zhv1_)
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

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator+(const zhvec3<T> &zhv_, U v_)
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

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator+(U v_, const zhvec3<T> &zhv_)
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

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator-(const zhvec3<T> &zhv0_, const zhvec3<U> &zhv1_)
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

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator-(const zhvec3<T> &zhv_, U v_)
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

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator-(U v_, const zhvec3<T> &zhv_)
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
PFC_INLINE zhvec3<T> operator-(const zhvec3<T> &zhv_)
{
  zhvec3<T> res=
  {
    -zhv_.coeffs[0],
    -zhv_.coeffs[1],
    -zhv_.coeffs[2]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator*(const zhvec3<T> &zhv0_, const zhvec3<U> &zhv1_)
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

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator*(const zhvec3<T> &zhv_, U v_)
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

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator*(U v_, const zhvec3<T> &zhv_)
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

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator/(const zhvec3<T> &zhv0_, const zhvec3<U> &zhv1_)
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

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator/(const zhvec3<T> &zhv_, U v_)
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

template<typename T, typename U>
PFC_INLINE zhvec3<T> operator/(U v_, const zhvec3<T> &zhv_)
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
PFC_INLINE zhvec3<T> min(const zhvec3<T> &zhv_)
{
  return min(zhv_.coeffs[0], zhv_.coeffs[1], zhv_.coeffs[2]);
}
//----

template<typename T>
PFC_INLINE zhvec3<T> min(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_)
{
  zhvec3<T> res=
  {
    zhv0_.coeffs[0]<zhv1_.coeffs[0]?zhv0_.coeffs[0]:zhv1_.coeffs[0],
    zhv0_.coeffs[1]<zhv1_.coeffs[1]?zhv0_.coeffs[1]:zhv1_.coeffs[1],
    zhv0_.coeffs[2]<zhv1_.coeffs[2]?zhv0_.coeffs[2]:zhv1_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> min(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_, const zhvec3<T> &zhv2_)
{
  zhvec3<T> res=
  {
    min(zhv0_.coeffs[0], zhv1_.coeffs[1], zhv2_.coeffs[0]),
    min(zhv0_.coeffs[1], zhv1_.coeffs[1], zhv2_.coeffs[1]),
    min(zhv0_.coeffs[2], zhv1_.coeffs[2], zhv2_.coeffs[2])
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> min(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_, const zhvec3<T> &zhv2_, const zhvec3<T> &zhv3_)
{
  zhvec3<T> res=
  {
    min(zhv0_.coeffs[0], zhv1_.coeffs[1], zhv2_.coeffs[0], zhv3_.coeffs[0]),
    min(zhv0_.coeffs[1], zhv1_.coeffs[1], zhv2_.coeffs[1], zhv3_.coeffs[1]),
    min(zhv0_.coeffs[2], zhv1_.coeffs[2], zhv2_.coeffs[2], zhv3_.coeffs[2])
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec3<T> min(const zhvec3<T> &zhv_, U v_)
{
  zhvec3<T> res=
  {
    zhv_.coeffs[0]<v_?zhv_.coeffs[0]:v_,
    zhv_.coeffs[1]<v_?zhv_.coeffs[1]:v_,
    zhv_.coeffs[2]<v_?zhv_.coeffs[2]:v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec3<T> min(U v_, const zhvec3<T> &zhv_)
{
  zhvec3<T> res=
  {
    v_<zhv_.coeffs[0]?v_:zhv_.coeffs[0],
    v_<zhv_.coeffs[1]?v_:zhv_.coeffs[1],
    v_<zhv_.coeffs[2]?v_:zhv_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> max(const zhvec3<T> &zhv_)
{
  return max(zhv_.coeffs[0], zhv_.coeffs[1], zhv_.coeffs[2]);
}
//----

template<typename T>
PFC_INLINE zhvec3<T> max(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_)
{
  zhvec3<T> res=
  {
    zhv0_.coeffs[0]>zhv1_.coeffs[0]?zhv0_.coeffs[0]:zhv1_.coeffs[0],
    zhv0_.coeffs[1]>zhv1_.coeffs[1]?zhv0_.coeffs[1]:zhv1_.coeffs[1],
    zhv0_.coeffs[2]>zhv1_.coeffs[2]?zhv0_.coeffs[2]:zhv1_.coeffs[2]
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> max(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_, const zhvec3<T> &zhv2_)
{
  zhvec3<T> res=
  {
    max(zhv0_.coeffs[0], zhv1_.coeffs[1], zhv2_.coeffs[0]),
    max(zhv0_.coeffs[1], zhv1_.coeffs[1], zhv2_.coeffs[1]),
    max(zhv0_.coeffs[2], zhv1_.coeffs[2], zhv2_.coeffs[2])
  };
  return res;
}
//----

template<typename T>
PFC_INLINE zhvec3<T> max(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_, const zhvec3<T> &zhv2_, const zhvec3<T> &zhv3_)
{
  zhvec3<T> res=
  {
    max(zhv0_.coeffs[0], zhv1_.coeffs[1], zhv2_.coeffs[0], zhv3_.coeffs[0]),
    max(zhv0_.coeffs[1], zhv1_.coeffs[1], zhv2_.coeffs[1], zhv3_.coeffs[1]),
    max(zhv0_.coeffs[2], zhv1_.coeffs[2], zhv2_.coeffs[2], zhv3_.coeffs[2])
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec3<T> max(const zhvec3<T> &zhv_, U v_)
{
  zhvec3<T> res=
  {
    zhv_.coeffs[0]>v_?zhv_.coeffs[0]:v_,
    zhv_.coeffs[1]>v_?zhv_.coeffs[1]:v_,
    zhv_.coeffs[2]>v_?zhv_.coeffs[2]:v_
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec3<T> max(U v_, const zhvec3<T> &zhv_)
{
  zhvec3<T> res=
  {
    v_>zhv_.coeffs[0]?v_:zhv_.coeffs[0],
    v_>zhv_.coeffs[1]?v_:zhv_.coeffs[1],
    v_>zhv_.coeffs[2]?v_:zhv_.coeffs[2]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE zhvec3<T> mul(const zhvec3<T> &zhv0_, const zhvec3<T> &zhv1_)
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

template<typename T, typename U, typename V>
PFC_INLINE zhvec3<T> madd(const zhvec3<T> &zhv0_,
                          const zhvec3<U> &zhv1_,
                          const zhvec3<V> &zhv2_)
{
  zhvec3<T> res=
  {
    zhv0_.coeffs[0]*zhv1_.coeffs[0]+zhv2_.coeffs[0],
    zhv0_.coeffs[1]*zhv1_.coeffs[1]+zhv2_.coeffs[1],
    zhv0_.coeffs[2]*zhv1_.coeffs[2]+zhv2_.coeffs[2]
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE zhvec3<T> madd(const zhvec3<T> &zhv_,
                          U mul_,
                          V add_)
{
  zhvec3<T> res=
  {
    zhv_.coeffs[0]*mul_+add_,
    zhv_.coeffs[1]*mul_+add_,
    zhv_.coeffs[2]*mul_+add_
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE zhvec3<T> madd(const zhvec3<T> &zhv_,
                          const zhvec3<U> &mul_,
                          V add_)
{
  zhvec3<T> res=
  {
    zhv_.coeffs[0]*mul_.coeffs[0]+add_,
    zhv_.coeffs[1]*mul_.coeffs[1]+add_,
    zhv_.coeffs[2]*mul_.coeffs[2]+add_
  };
  return res;
}
//----

template<typename T, typename U, typename V>
PFC_INLINE zhvec3<T> madd(const zhvec3<T> &zhv_,
                          U mul_,
                          const zhvec3<V> &add_)
{
  zhvec3<T> res=
  {
    zhv_.coeffs[0]*mul_+add_.coeffs[0],
    zhv_.coeffs[1]*mul_+add_.coeffs[1],
    zhv_.coeffs[2]*mul_+add_.coeffs[2]
  };
  return res;
}
//----

template<typename T, typename U>
PFC_INLINE T dot(const zhvec3<T> &zhv0_, const zhvec3<U> &zhv1_)
{
  return  zhv0_.coeffs[0]*zhv1_.coeffs[0]
         +zhv0_.coeffs[1]*zhv1_.coeffs[1]
         +zhv0_.coeffs[2]*zhv1_.coeffs[2];
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_real1(zhvec3<T> &zhvr_, Rng &rng_)
{
  typedef typename math<T>::scalar_t scalar_t;
  zhvr_.coeffs[0]=scalar_t(rng_.rand_real1());
  zhvr_.coeffs[1]=scalar_t(rng_.rand_real1());
  zhvr_.coeffs[2]=scalar_t(rng_.rand_real1());
}
//----

template<typename T, class Rng>
PFC_INLINE void rand_ureal1(zhvec3<T> &zhvr_, Rng &rng_)
{
  typedef typename math<T>::scalar_t scalar_t;
  zhvr_.coeffs[0]=scalar_t(rng_.rand_ureal1());
  zhvr_.coeffs[1]=scalar_t(rng_.rand_ureal1());
  zhvr_.coeffs[2]=scalar_t(rng_.rand_ureal1());
}
//----------------------------------------------------------------------------
