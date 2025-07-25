//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// color_rgb
//============================================================================
template<typename T>
color_rgb<T>::color_rgb()
{
}
//----

template<typename T>
color_rgb<T>::color_rgb(T v_)
  :r(v_)
  ,g(v_)
  ,b(v_)
{
}
//----

template<typename T>
color_rgb<T>::color_rgb(T r_, T g_, T b_)
  :r(r_)
  ,g(g_)
  ,b(b_)
{
}
//----

template<typename T>
color_rgb<T>::color_rgb(const color_rgba<T> &c_)
  :r(c_.r)
  ,g(c_.g)
  ,b(c_.b)
{
}
//----

template<typename T>
template<typename U>
color_rgb<T>::color_rgb(const color_rgb<U> &c_)
  :r(T(c_.r))
  ,g(T(c_.g))
  ,b(T(c_.b))
{
}
//----

template<typename T>
template<typename U>
color_rgb<T>::color_rgb(const color_rgba<U> &c_)
  :r(T(c_.r))
  ,g(T(c_.g))
  ,b(T(c_.b))
{
}
//----------------------------------------------------------------------------

template<typename T>
const T &color_rgb<T>::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &color_rgb<T>::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void color_rgb<T>::set(T v_)
{
  r=v_;
  g=v_;
  b=v_;
}
//----

template<typename T>
void color_rgb<T>::set(T r_, T g_, T b_)
{
  r=r_;
  g=g_;
  b=b_;
}
//----

template<typename T>
template<typename U>
void color_rgb<T>::set(const color_rgb<U> &c_)
{
  r=T(c_.r);
  g=T(c_.g);
  b=T(c_.b);
}
//----------------------------------------------------------------------------

// vec3 interface for color_rgb
template<typename T> PFC_INLINE bool is_zero(const color_rgb<T> &c_)                                             {return is_zero(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_black(const color_rgb<T> &c_)                                            {return is_zero(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_sat(const color_rgb<T> &c_)                                              {return is_sat(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_ssat(const color_rgb<T> &c_)                                             {return is_ssat(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool operator==(const color_rgb<T> &c0_, const color_rgb<T> &c1_)                {return reinterpret_cast<const vec3<T>&>(c0_)==reinterpret_cast<const vec3<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator==(const color_rgb<T> &c_, typename math<T>::scalar_t s_)           {return reinterpret_cast<const vec3<T>&>(c_)==s_;}
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const color_rgb<T> &c_)           {return s_==reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE bool operator!=(const color_rgb<T> &c0_, const color_rgb<T> &c1_)                {return reinterpret_cast<const vec3<T>&>(c0_)!=reinterpret_cast<const vec3<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator!=(const color_rgb<T> &c_, typename math<T>::scalar_t s_)           {return reinterpret_cast<const vec3<T>&>(c_)!=s_;}
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const color_rgb<T> &c_)           {return s_!=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE color_rgb<T> operator<(const color_rgb<T> &c0_, const color_rgb<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)<reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator<(const color_rgb<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)<s_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator<(typename math<T>::scalar_t s_, const color_rgb<T> &c_)    {const vec3<T> &v=s_<reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator>(const color_rgb<T> &c0_, const color_rgb<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)>reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator>(const color_rgb<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)>s_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator>(typename math<T>::scalar_t s_, const color_rgb<T> &c_)    {const vec3<T> &v=s_>reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator<=(const color_rgb<T> &c0_, const color_rgb<T> &c1_)        {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)<=reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator<=(const color_rgb<T> &c_, typename math<T>::scalar_t s_)   {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)<=s_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator<=(typename math<T>::scalar_t s_, const color_rgb<T> &c_)   {const vec3<T> &v=s_<=reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator>=(const color_rgb<T> &c0_, const color_rgb<T> &c1_)        {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)>=reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator>=(const color_rgb<T> &c_, typename math<T>::scalar_t s_)   {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)>=s_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator>=(typename math<T>::scalar_t s_, const color_rgb<T> &c_)   {const vec3<T> &v=s_>=reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sel_eq(const color_rgb<T> &t0_, const color_rgb<T> &t1_,
                                                     const color_rgb<T> &c0_, const color_rgb<T> &c1_)           {const vec3<T> &v=sel_eq(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sel_lt(const color_rgb<T> &t0_, const color_rgb<T> &t1_,
                                                     const color_rgb<T> &c0_, const color_rgb<T> &c1_)           {const vec3<T> &v=sel_lt(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sel_le(const color_rgb<T> &t0_, const color_rgb<T> &t1_,
                                                     const color_rgb<T> &c0_, const color_rgb<T> &c1_)           {const vec3<T> &v=sel_le(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sel_eqz(const color_rgb<T> &t_,
                                                      const color_rgb<T> &c0_, const color_rgb<T> &c1_)          {const vec3<T> &v=sel_eqz(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sel_ltz(const color_rgb<T> &t_,
                                                      const color_rgb<T> &c0_, const color_rgb<T> &c1_)          {const vec3<T> &v=sel_ltz(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sel_lez(const color_rgb<T> &t_,
                                                      const color_rgb<T> &c0_, const color_rgb<T> &c1_)          {const vec3<T> &v=sel_lez(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE void operator+=(color_rgb<T> &cr_, const color_rgb<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_rgb<T> &cr_, const color_rgba<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_rgb<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)+=s_;}
template<typename T> PFC_INLINE void operator-=(color_rgb<T> &cr_, const color_rgb<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_rgb<T> &cr_, const color_rgba<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_rgb<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)-=s_;}
template<typename T> PFC_INLINE void operator*=(color_rgb<T> &cr_, const color_rgb<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_rgb<T> &cr_, const color_rgba<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_rgb<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)*=s_;}
template<typename T> PFC_INLINE void operator*=(color_rgb<T> &cr_, const mat33<T> &m_)                           {reinterpret_cast<vec3<T>&>(cr_)*=m_;}
template<typename T> PFC_INLINE void operator*=(color_rgb<T> &cr_, const mat44<T> &m_)                           {reinterpret_cast<vec3<T>&>(cr_)*=m_;}
template<typename T> PFC_INLINE void operator*=(color_rgb<T> &cr_, const quat<T> &q_)                            {reinterpret_cast<vec3<T>&>(cr_)*=q_;}
template<typename T> PFC_INLINE void operator/=(color_rgb<T> &cr_, const color_rgb<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_rgb<T> &cr_, const color_rgba<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_rgb<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)/=s_;}
template<typename T> PFC_INLINE color_rgb<T> operator+(const color_rgb<T> &c0_, const color_rgb<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)+reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator+(const color_rgb<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)+s_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator+(typename math<T>::scalar_t s_, const color_rgb<T> &c_)    {const vec3<T> &v=s_+reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator-(const color_rgb<T> &c0_, const color_rgb<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)-reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator-(const color_rgb<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)-s_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator-(typename math<T>::scalar_t s_, const color_rgb<T> &c_)    {const vec3<T> &v=s_-reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator-(const color_rgb<T> &c_)                                   {const vec3<T> &v=-reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator*(const color_rgb<T> &c0_, const color_rgb<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)*reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator*(const color_rgb<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*s_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator*(typename math<T>::scalar_t s_, const color_rgb<T> &c_)    {const vec3<T> &v=s_*reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator*(const color_rgb<T> &c_, const mat33<T> &m_)               {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*m_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator*(const mat33<T> &m_, const color_rgb<T> &c_)               {const vec3<T> &v=m_*reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator*(const color_rgb<T> &c_, const mat44<T> &m_)               {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*m_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator*(const mat44<T> &m_, const color_rgb<T> &c_)               {const vec3<T> &v=m_*reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator*(const color_rgb<T> &c_, const quat<T> &q_)                {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*q_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator/(const color_rgb<T> &c0_, const color_rgb<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)/reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator/(const color_rgb<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)/s_; return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> operator/(typename math<T>::scalar_t s_, const color_rgb<T> &c_)    {const vec3<T> &v=s_/reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const color_rgb<T> &c_)                           {return min(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_rgb<T> min(const color_rgb<T> &c0_,
                                                  const color_rgb<T> &c1_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> min(const color_rgb<T> &c0_,
                                                  const color_rgb<T> &c1_,
                                                  const color_rgb<T> &c2_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> min(const color_rgb<T> &c0_,
                                                  const color_rgb<T> &c1_,
                                                  const color_rgb<T> &c2_,
                                                  const color_rgb<T> &c3_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_), reinterpret_cast<const vec3<T>&>(c3_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> min(const color_rgb<T> &c_, typename math<T>::scalar_t s_)          {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c_), s_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> min(typename math<T>::scalar_t s_, const color_rgb<T> &c_)          {const vec3<T> &v=min(s_, reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const color_rgb<T> &c_)                           {return max(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_rgb<T> max(const color_rgb<T> &c0_,
                                                  const color_rgb<T> &c1_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> max(const color_rgb<T> &c0_,
                                                  const color_rgb<T> &c1_,
                                                  const color_rgb<T> &c2_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> max(const color_rgb<T> &c0_,
                                                  const color_rgb<T> &c1_,
                                                  const color_rgb<T> &c2_,
                                                  const color_rgb<T> &c3_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_), reinterpret_cast<const vec3<T>&>(c3_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> max(const color_rgb<T> &c_, typename math<T>::scalar_t s_)          {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c_), s_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> max(typename math<T>::scalar_t s_, const color_rgb<T> &c_)          {const vec3<T> &v=max(s_, reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> mul(const color_rgb<T> &c0_, const color_rgb<T> &c1_)               {const vec3<T> &v=mul(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> madd(const color_rgb<T> &c0_,
                                                   const color_rgb<T> &c1_,
                                                   const color_rgb<T> &c2_)                                      {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> madd(const color_rgb<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   typename math<T>::scalar_t add_)                              {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), mul_, add_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> madd(const color_rgb<T> &c_,
                                                   const color_rgb<T> &mul_,
                                                   typename math<T>::scalar_t add_)                              {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(mul_), add_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> madd(const color_rgb<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   const color_rgb<T> &add_)                                     {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), mul_, reinterpret_cast<const vec3<T>&>(add_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> rcp(const color_rgb<T> &c_)                                         {const vec3<T> &v=rcp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> rcp_z(const color_rgb<T> &c_)                                       {const vec3<T> &v=rcp_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> floor(const color_rgb<T> &c_)                                       {const vec3<T> &v=floor(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> ceil(const color_rgb<T> &c_)                                        {const vec3<T> &v=ceil(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> trunc(const color_rgb<T> &c_)                                       {const vec3<T> &v=trunc(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> frc(const color_rgb<T> &c_)                                         {const vec3<T> &v=frc(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> mod(const color_rgb<T> &c_, T div_)                                 {const vec3<T> &v=mod(reinterpret_cast<const vec3<T>&>(c_), div_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> cycle(const color_rgb<T> &c_, T cycle_)                             {const vec3<T> &v=cycle(reinterpret_cast<const vec3<T>&>(c_), cycle_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> cycle1(const color_rgb<T> &c_)                                      {const vec3<T> &v=cycle1(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sat(const color_rgb<T> &c_)                                         {const vec3<T> &v=sat(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> ssat(const color_rgb<T> &c_)                                        {const vec3<T> &v=ssat(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> clamp(const color_rgb<T> &c_,
                                                    const color_rgb<T> &min_,
                                                    const color_rgb<T> &max_)                                    {const vec3<T> &v=clamp(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(min_), reinterpret_cast<const vec3<T>&>(max_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> clamp(const color_rgb<T> &c_,
                                                    typename math<T>::scalar_t min_,
                                                    typename math<T>::scalar_t max_)                             {const vec3<T> &v=clamp(reinterpret_cast<const vec3<T>&>(c_), min_, max_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> abs(const color_rgb<T> &c_)                                         {const vec3<T> &v=abs(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sgn(const color_rgb<T> &c_)                                         {const vec3<T> &v=sgn(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sgn_zp(const color_rgb<T> &c_)                                      {const vec3<T> &v=sgn_zp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sqr(const color_rgb<T> &c_)                                         {const vec3<T> &v=sqr(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> cubic(const color_rgb<T> &c_)                                       {const vec3<T> &v=cubic(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sqrt(const color_rgb<T> &c_)                                        {const vec3<T> &v=sqrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> sqrt_z(const color_rgb<T> &c_)                                      {const vec3<T> &v=sqrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> cbrt(const color_rgb<T> &c_)                                        {const vec3<T> &v=cbrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> rsqrt(const color_rgb<T> &c_)                                       {const vec3<T> &v=rsqrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> rsqrt_z(const color_rgb<T> &c_)                                     {const vec3<T> &v=rsqrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> rcbrt(const color_rgb<T> &c_)                                       {const vec3<T> &v=rcbrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> rcbrt_z(const color_rgb<T> &c_)                                     {const vec3<T> &v=rcbrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const color_rgb<T> &c_)                          {return norm(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const color_rgb<T> &c_)                         {return rnorm(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const color_rgb<T> &c_)                       {return rnorm_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const color_rgb<T> &c_)                         {return norm2(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const color_rgb<T> &c_)                        {return rnorm2(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const color_rgb<T> &c_)                      {return rnorm2_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const color_rgb<T> &c_)                       {return norm_l1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const color_rgb<T> &c_)                      {return rnorm_l1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const color_rgb<T> &c_)                    {return rnorm_l1_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_rgb<T> exp(const color_rgb<T> &c_)                                         {const vec3<T> &v=exp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> exp2(const color_rgb<T> &c_)                                        {const vec3<T> &v=exp2(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> ln(const color_rgb<T> &c_)                                          {const vec3<T> &v=ln(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> log2(const color_rgb<T> &c_)                                        {const vec3<T> &v=log2(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> log10(const color_rgb<T> &c_)                                       {const vec3<T> &v=log10(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> pow(const color_rgb<T> &c_, typename math<T>::scalar_t p_)          {const vec3<T> &v=pow(reinterpret_cast<const vec3<T>&>(c_), p_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> unit(const color_rgb<T> &c_)                                        {const vec3<T> &v=unit(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> unit_z(const color_rgb<T> &c_)                                      {const vec3<T> &v=unit_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> cross(const color_rgb<T> &c0_, const color_rgb<T> &c1_)             {const vec3<T> &v=cross(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const color_rgb<T> &c0_, const color_rgb<T> &c1_) {return dot(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const color_rgb<T> &c_)                          {return dot1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void neg(color_rgb<T> &c_)                                                       {neg(reinterpret_cast<vec3<T>&>(c_));}
template<typename T, class Rand> PFC_INLINE void rand_u(color_rgb<T> &c_, Rand &rnd_)                            {rand_u(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_real1(color_rgb<T> &c_, Rand &rnd_)                        {rand_real1(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_ureal1(color_rgb<T> &c_, Rand &rnd_)                       {rand_ureal1(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T> PFC_INLINE color_rgb<T> smoothstep(const color_rgb<T> &c_)                                  {const vec3<T> &v=smoothstep(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> smootherstep(const color_rgb<T> &c_)                                {const vec3<T> &v=smootherstep(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> lerp(const color_rgb<T> &c0_, const color_rgb<T> &c1_, float t_)    {const vec3<T> &v=lerp(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), t_); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> reflect(const color_rgb<T> &c_, const color_rgb<T> &cn_)            {const vec3<T> &v=reflect(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(cn_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE color_rgb<T> reflect_u(const color_rgb<T> &c_, const color_rgb<T> &cn_)          {const vec3<T> &v=reflect_u(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(cn_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<unsigned shuffle_, typename T> PFC_INLINE color_rgb<T> shuffle(const color_rgb<T> &c_)                  {const vec3<T> &v=shuffle<shuffle_>(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_rgb<T>&>(v);}
template<typename T> PFC_INLINE void pack_u1(color_rgb32 &cr_, const color_rgb<T> &c_)                           {pack_u1(reinterpret_cast<vec3_32u&>(cr_), reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void pack_s1(color_rgb32 &cr_, const color_rgb<T> &c_)                           {pack_s1(reinterpret_cast<vec3_32s&>(cr_), reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void unpack_u1(color_rgb<T> &cr_, const color_rgb32 &c_)                         {unpack_u1(reinterpret_cast<vec3<T>&>(cr_), reinterpret_cast<const vec3_32u&>(c_));}
template<typename T> PFC_INLINE void unpack_s1(color_rgb<T> &cr_, const color_rgb32 &c_)                         {unpack_s1(reinterpret_cast<vec3<T>&>(cr_), reinterpret_cast<const vec3_32s&>(c_));}
//----------------------------------------------------------------------------


//============================================================================
// color_rgba
//============================================================================
template<typename T>
color_rgba<T>::color_rgba()
{
}
//----

template<typename T>
color_rgba<T>::color_rgba(T v_)
  :r(v_)
  ,g(v_)
  ,b(v_)
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
color_rgba<T>::color_rgba(T r_, T g_, T b_)
  :r(r_)
  ,g(g_)
  ,b(b_)
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
color_rgba<T>::color_rgba(T r_, T g_, T b_, T a_)
  :r(r_)
  ,g(g_)
  ,b(b_)
  ,a(a_)
{
}
//----

template<typename T>
color_rgba<T>::color_rgba(const color_rgb<T> &c_)
  :r(c_.r)
  ,g(c_.g)
  ,b(c_.b)
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
color_rgba<T>::color_rgba(const color_rgb<T> &c_, T a_)
  :r(c_.r)
  ,g(c_.g)
  ,b(c_.b)
  ,a(a_)
{
}
//----

template<typename T>
template<typename U>
color_rgba<T>::color_rgba(const color_rgba<U> &c_)
  :r(T(c_.r))
  ,g(T(c_.g))
  ,b(T(c_.b))
  ,a(T(c_.a))
{
}
//----

template<typename T>
template<typename U>
color_rgba<T>::color_rgba(const color_rgb<U> &c_)
  :r(T(c_.r))
  ,g(T(c_.g))
  ,b(T(c_.b))
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
template<typename U>
color_rgba<T>::color_rgba(const color_rgb<U> &c_, U a_)
  :r(T(c_.r))
  ,g(T(c_.g))
  ,b(T(c_.b))
  ,a(T(a_))
{
}
//----------------------------------------------------------------------------

template<typename T>
const T &color_rgba<T>::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &color_rgba<T>::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void color_rgba<T>::set(T v_)
{
  r=v_;
  g=v_;
  b=v_;
}
//----

template<typename T>
void color_rgba<T>::set(T r_, T g_, T b_)
{
  r=r_;
  g=g_;
  b=b_;
}
//----

template<typename T>
void color_rgba<T>::set(T r_, T g_, T b_, T a_)
{
  r=r_;
  g=g_;
  b=b_;
  a=a_;
}
//----

template<typename T>
void color_rgba<T>::set(const color_rgb<T> &c_, T a_)
{
  r=c_.r;
  g=c_.g;
  b=c_.b;
  a=a_;
}
//----

template<typename T>
template<typename U>
void color_rgba<T>::set(const color_rgba<U> &c_)
{
  r=T(c_.r);
  g=T(c_.g);
  b=T(c_.b);
  a=T(c_.a);
}
//----------------------------------------------------------------------------

// vec4 interface for color_rgba
template<typename T> PFC_INLINE bool is_zero(const color_rgba<T> &c_)                                              {return is_zero(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool is_black(const color_rgba<T> &c_)                                             {return is_zero(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_sat(const color_rgba<T> &c_)                                               {return is_sat(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool is_ssat(const color_rgba<T> &c_)                                              {return is_ssat(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool operator==(const color_rgba<T> &c0_, const color_rgba<T> &c1_)                {return reinterpret_cast<const vec4<T>&>(c0_)==reinterpret_cast<const vec4<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator==(const color_rgba<T> &c_, typename math<T>::scalar_t s_)            {return reinterpret_cast<const vec4<T>&>(c_)==s_;}
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const color_rgba<T> &c_)            {return s_==reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE bool operator!=(const color_rgba<T> &c0_, const color_rgba<T> &c1_)                {return reinterpret_cast<const vec4<T>&>(c0_)!=reinterpret_cast<const vec4<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator!=(const color_rgba<T> &c_, typename math<T>::scalar_t s_)            {return reinterpret_cast<const vec4<T>&>(c_)!=s_;}
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const color_rgba<T> &c_)            {return s_!=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE color_rgba<T> operator<(const color_rgba<T> &c0_, const color_rgba<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)<reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator<(const color_rgba<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)<s_; return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator<(typename math<T>::scalar_t s_, const color_rgba<T> &c_)    {const vec4<T> &v=s_<reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator>(const color_rgba<T> &c0_, const color_rgba<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)>reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator>(const color_rgba<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)>s_; return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator>(typename math<T>::scalar_t s_, const color_rgba<T> &c_)    {const vec4<T> &v=s_>reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator<=(const color_rgba<T> &c0_, const color_rgba<T> &c1_)       {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)<=reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator<=(const color_rgba<T> &c_, typename math<T>::scalar_t s_)   {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)<=s_; return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator<=(typename math<T>::scalar_t s_, const color_rgba<T> &c_)   {const vec4<T> &v=s_<=reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator>=(const color_rgba<T> &c0_, const color_rgba<T> &c1_)       {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)>=reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator>=(const color_rgba<T> &c_, typename math<T>::scalar_t s_)   {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)>=s_; return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator>=(typename math<T>::scalar_t s_, const color_rgba<T> &c_)   {const vec4<T> &v=s_>=reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sel_eq(const color_rgba<T> &t0_, const color_rgba<T> &t1_,
                                                     const color_rgba<T> &c0_, const color_rgba<T> &c1_)           {const vec4<T> &v=sel_eq(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sel_lt(const color_rgba<T> &t0_, const color_rgba<T> &t1_,
                                                     const color_rgba<T> &c0_, const color_rgba<T> &c1_)           {const vec4<T> &v=sel_lt(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sel_le(const color_rgba<T> &t0_, const color_rgba<T> &t1_,
                                                     const color_rgba<T> &c0_, const color_rgba<T> &c1_)           {const vec4<T> &v=sel_le(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sel_eqz(const color_rgba<T> &t_,
                                                      const color_rgba<T> &c0_, const color_rgba<T> &c1_)          {const vec4<T> &v=sel_eqz(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sel_ltz(const color_rgba<T> &t_,
                                                      const color_rgba<T> &c0_, const color_rgba<T> &c1_)          {const vec4<T> &v=sel_ltz(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sel_lez(const color_rgba<T> &t_,
                                                      const color_rgba<T> &c0_, const color_rgba<T> &c1_)          {const vec4<T> &v=sel_lez(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE void operator+=(color_rgba<T> &cr_, const color_rgba<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)+=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_rgba<T> &cr_, const color_rgb<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_rgba<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)+=s_;}
template<typename T> PFC_INLINE void operator-=(color_rgba<T> &cr_, const color_rgba<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)-=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_rgba<T> &cr_, const color_rgb<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_rgba<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)-=s_;}
template<typename T> PFC_INLINE void operator*=(color_rgba<T> &cr_, const color_rgba<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)*=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_rgba<T> &cr_, const color_rgb<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_rgba<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)*=s_;}
template<typename T> PFC_INLINE void operator*=(color_rgba<T> &cr_, const mat44<T> &m_)                            {reinterpret_cast<vec4<T>&>(cr_)*=m_;}
template<typename T> PFC_INLINE void operator/=(color_rgba<T> &cr_, const color_rgba<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)/=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_rgba<T> &cr_, const color_rgb<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_rgba<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)/=s_;}
template<typename T> PFC_INLINE color_rgba<T> operator+(const color_rgba<T> &c0_, const color_rgba<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)+reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator+(const color_rgba<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)+s_; return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator+(typename math<T>::scalar_t s_, const color_rgba<T> &c_)    {const vec4<T> &v=s_+reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator-(const color_rgba<T> &c0_, const color_rgba<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)-reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator-(const color_rgba<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)-s_; return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator-(typename math<T>::scalar_t s_, const color_rgba<T> &c_)    {const vec4<T> &v=s_-reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator-(const color_rgba<T> &c_)                                   {const vec4<T> &v=-reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator*(const color_rgba<T> &c0_, const color_rgba<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)*reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator*(const color_rgba<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)*s_; return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator*(typename math<T>::scalar_t s_, const color_rgba<T> &c_)    {const vec4<T> &v=s_*reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator*(const color_rgba<T> &c_, const mat44<T> &m_)               {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)*m_; return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator*(const mat44<T> &m_, const color_rgba<T> &c_)               {const vec4<T> &v=m_*reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator/(const color_rgba<T> &c0_, const color_rgba<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)/reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator/(const color_rgba<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)/s_; return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> operator/(typename math<T>::scalar_t s_, const color_rgba<T> &c_)    {const vec4<T> &v=s_/reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const color_rgba<T> &c_)                            {return min(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_rgba<T> min(const color_rgba<T> &c0_,
                                                  const color_rgba<T> &c1_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> min(const color_rgba<T> &c0_,
                                                  const color_rgba<T> &c1_,
                                                  const color_rgba<T> &c2_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> min(const color_rgba<T> &c0_,
                                                  const color_rgba<T> &c1_,
                                                  const color_rgba<T> &c2_,
                                                  const color_rgba<T> &c3_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_), reinterpret_cast<const vec4<T>&>(c3_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> min(const color_rgba<T> &c_, typename math<T>::scalar_t s_)          {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c_), s_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> min(typename math<T>::scalar_t s_, const color_rgba<T> &c_)          {const vec4<T> &v=min(s_, reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const color_rgba<T> &c_)                            {return max(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_rgba<T> max(const color_rgba<T> &c0_,
                                                  const color_rgba<T> &c1_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> max(const color_rgba<T> &c0_,
                                                  const color_rgba<T> &c1_,
                                                  const color_rgba<T> &c2_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> max(const color_rgba<T> &c0_,
                                                  const color_rgba<T> &c1_,
                                                  const color_rgba<T> &c2_,
                                                  const color_rgba<T> &c3_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_), reinterpret_cast<const vec4<T>&>(c3_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> max(const color_rgba<T> &c_, typename math<T>::scalar_t s_)          {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c_), s_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> max(typename math<T>::scalar_t s_, const color_rgba<T> &c_)          {const vec4<T> &v=max(s_, reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> mul(const color_rgba<T> &c0_, const color_rgba<T> &c1_)              {const vec4<T> &v=mul(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> madd(const color_rgba<T> &c0_,
                                                   const color_rgba<T> &c1_,
                                                   const color_rgba<T> &c2_)                                       {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> madd(const color_rgba<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   typename math<T>::scalar_t add_)                                {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), mul_, add_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> madd(const color_rgba<T> &c_,
                                                   const color_rgba<T> &mul_,
                                                   typename math<T>::scalar_t add_)                                {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(mul_), add_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> madd(const color_rgba<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   const color_rgba<T> &add_)                                      {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), mul_, reinterpret_cast<const vec4<T>&>(add_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> rcp(const color_rgba<T> &c_)                                         {const vec4<T> &v=rcp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> rcp_z(const color_rgba<T> &c_)                                       {const vec4<T> &v=rcp_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> floor(const color_rgba<T> &c_)                                       {const vec4<T> &v=floor(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> ceil(const color_rgba<T> &c_)                                        {const vec4<T> &v=ceil(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> trunc(const color_rgba<T> &c_)                                       {const vec4<T> &v=trunc(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> frc(const color_rgba<T> &c_)                                         {const vec4<T> &v=frc(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> mod(const color_rgba<T> &c_, T div_)                                 {const vec4<T> &v=mod(reinterpret_cast<const vec4<T>&>(c_), div_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> cycle(const color_rgba<T> &c_, T cycle_)                             {const vec4<T> &v=cycle(reinterpret_cast<const vec4<T>&>(c_), cycle_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> cycle1(const color_rgba<T> &c_)                                      {const vec4<T> &v=cycle1(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sat(const color_rgba<T> &c_)                                         {const vec4<T> &v=sat(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> ssat(const color_rgba<T> &c_)                                        {const vec4<T> &v=ssat(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> clamp(const color_rgba<T> &c_,
                                                    const color_rgba<T> &min_,
                                                    const color_rgba<T> &max_)                                     {const vec4<T> &v=clamp(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(min_), reinterpret_cast<const vec4<T>&>(max_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> clamp(const color_rgba<T> &c_,
                                                    typename math<T>::scalar_t min_,
                                                    typename math<T>::scalar_t max_)                               {const vec4<T> &v=clamp(reinterpret_cast<const vec4<T>&>(c_), min_, max_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> abs(const color_rgba<T> &c_)                                         {const vec4<T> &v=abs(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sgn(const color_rgba<T> &c_)                                         {const vec4<T> &v=sgn(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sgn_zp(const color_rgba<T> &c_)                                      {const vec4<T> &v=sgn_zp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sqr(const color_rgba<T> &c_)                                         {const vec4<T> &v=sqr(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> cubic(const color_rgba<T> &c_)                                       {const vec4<T> &v=cubic(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sqrt(const color_rgba<T> &c_)                                        {const vec4<T> &v=sqrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> sqrt_z(const color_rgba<T> &c_)                                      {const vec4<T> &v=sqrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> cbrt(const color_rgba<T> &c_)                                        {const vec4<T> &v=cbrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> rsqrt(const color_rgba<T> &c_)                                       {const vec4<T> &v=rsqrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> rsqrt_z(const color_rgba<T> &c_)                                     {const vec4<T> &v=rsqrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> rcbrt(const color_rgba<T> &c_)                                       {const vec4<T> &v=rcbrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> rcbrt_z(const color_rgba<T> &c_)                                     {const vec4<T> &v=rcbrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const color_rgba<T> &c_)                           {return norm(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const color_rgba<T> &c_)                          {return rnorm(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const color_rgba<T> &c_)                        {return rnorm_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const color_rgba<T> &c_)                          {return norm2(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const color_rgba<T> &c_)                         {return rnorm2(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const color_rgba<T> &c_)                       {return rnorm2_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const color_rgba<T> &c_)                        {return norm_l1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const color_rgba<T> &c_)                       {return rnorm_l1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const color_rgba<T> &c_)                     {return rnorm_l1_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_rgba<T> exp(const color_rgba<T> &c_)                                         {const vec4<T> &v=exp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> exp2(const color_rgba<T> &c_)                                        {const vec4<T> &v=exp2(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> ln(const color_rgba<T> &c_)                                          {const vec4<T> &v=ln(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> log2(const color_rgba<T> &c_)                                        {const vec4<T> &v=log2(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> log10(const color_rgba<T> &c_)                                       {const vec4<T> &v=log10(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> pow(const color_rgba<T> &c_, typename math<T>::scalar_t p_)          {const vec4<T> &v=pow(reinterpret_cast<const vec4<T>&>(c_), p_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> unit(const color_rgba<T> &c_)                                        {const vec4<T> &v=unit(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> unit_z(const color_rgba<T> &c_)                                      {const vec4<T> &v=unit_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const color_rgba<T> &c0_, const color_rgba<T> &c1_) {return dot(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const color_rgba<T> &c_)                           {return dot1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void neg(color_rgba<T> &c_)                                                        {neg(reinterpret_cast<vec4<T>&>(c_));}
template<typename T, class Rand> PFC_INLINE void rand_u(color_rgba<T> &c_, Rand &rnd_)                             {rand_u(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_real1(color_rgba<T> &c_, Rand &rnd_)                         {rand_real1(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_ureal1(color_rgba<T> &c_, Rand &rnd_)                        {rand_ureal1(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T> PFC_INLINE color_rgba<T> smoothstep(const color_rgba<T> &c_)                                  {const vec4<T> &v=smoothstep(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> smootherstep(const color_rgba<T> &c_)                                {const vec4<T> &v=smootherstep(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> lerp(const color_rgba<T> &c0_, const color_rgba<T> &c1_, float t_)   {const vec4<T> &v=lerp(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), t_); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> reflect(const color_rgba<T> &c_, const color_rgba<T> &cn_)           {const vec4<T> &v=reflect(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(cn_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE color_rgba<T> reflect_u(const color_rgba<T> &c_, const color_rgba<T> &cn_)         {const vec4<T> &v=reflect_u(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(cn_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<unsigned shuffle_, typename T> PFC_INLINE color_rgba<T> shuffle(const color_rgba<T> &c_)                  {const vec4<T> &v=shuffle<shuffle_>(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_rgba<T>&>(v);}
template<typename T> PFC_INLINE void pack_u1(color_rgba32 &cr_, const color_rgba<T> &c_)                           {pack_u1(reinterpret_cast<vec4_32u&>(cr_), reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void pack_s1(color_rgba32 &cr_, const color_rgba<T> &c_)                           {pack_s1(reinterpret_cast<vec4_32s&>(cr_), reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void unpack_u1(color_rgba<T> &cr_, const color_rgba32 &c_)                         {unpack_u1(reinterpret_cast<vec4<T>&>(cr_), reinterpret_cast<const vec4_32u&>(c_));}
template<typename T> PFC_INLINE void unpack_s1(color_rgba<T> &cr_, const color_rgba32 &c_)                         {unpack_s1(reinterpret_cast<vec4<T>&>(cr_), reinterpret_cast<const vec4_32s&>(c_));}
//----------------------------------------------------------------------------


//============================================================================
// color_xyz
//============================================================================
template<typename T>
color_xyz<T>::color_xyz()
{
}
//----

template<typename T>
color_xyz<T>::color_xyz(T v_)
  :x(v_)
  ,y(v_)
  ,z(v_)
{
}
//----

template<typename T>
color_xyz<T>::color_xyz(T x_, T y_, T z_)
  :x(x_)
  ,y(y_)
  ,z(z_)
{
}
//----

template<typename T>
color_xyz<T>::color_xyz(const color_xyza<T> &c_)
  :x(c_.x)
  ,y(c_.y)
  ,z(c_.z)
{
}
//----

template<typename T>
template<typename U>
color_xyz<T>::color_xyz(const color_xyz<U> &c_)
  :x(T(c_.x))
  ,y(T(c_.y))
  ,z(T(c_.z))
{
}
//----

template<typename T>
template<typename U>
color_xyz<T>::color_xyz(const color_xyza<U> &c_)
  :x(T(c_.x))
  ,y(T(c_.y))
  ,z(T(c_.z))
{
}
//----------------------------------------------------------------------------

template<typename T>
const T &color_xyz<T>::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &color_xyz<T>::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void color_xyz<T>::set(T v_)
{
  x=v_;
  y=v_;
  z=v_;
}
//----

template<typename T>
void color_xyz<T>::set(T x_, T y_, T z_)
{
  x=x_;
  y=y_;
  z=z_;
}
//----

template<typename T>
template<typename U>
void color_xyz<T>::set(const color_xyz<U> &c_)
{
  x=T(c_.x);
  y=T(c_.y);
  z=T(c_.z);
}
//----------------------------------------------------------------------------

// vec3 interface for color_xyz
template<typename T> PFC_INLINE bool is_zero(const color_xyz<T> &c_)                                             {return is_zero(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_black(const color_xyz<T> &c_)                                            {return is_zero(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_sat(const color_xyz<T> &c_)                                              {return is_sat(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_ssat(const color_xyz<T> &c_)                                             {return is_ssat(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool operator==(const color_xyz<T> &c0_, const color_xyz<T> &c1_)                {return reinterpret_cast<const vec3<T>&>(c0_)==reinterpret_cast<const vec3<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator==(const color_xyz<T> &c_, typename math<T>::scalar_t s_)           {return reinterpret_cast<const vec3<T>&>(c_)==s_;}
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const color_xyz<T> &c_)           {return s_==reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE bool operator!=(const color_xyz<T> &c0_, const color_xyz<T> &c1_)                {return reinterpret_cast<const vec3<T>&>(c0_)!=reinterpret_cast<const vec3<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator!=(const color_xyz<T> &c_, typename math<T>::scalar_t s_)           {return reinterpret_cast<const vec3<T>&>(c_)!=s_;}
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const color_xyz<T> &c_)           {return s_!=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE color_xyz<T> operator<(const color_xyz<T> &c0_, const color_xyz<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)<reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator<(const color_xyz<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)<s_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator<(typename math<T>::scalar_t s_, const color_xyz<T> &c_)    {const vec3<T> &v=s_<reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator>(const color_xyz<T> &c0_, const color_xyz<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)>reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator>(const color_xyz<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)>s_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator>(typename math<T>::scalar_t s_, const color_xyz<T> &c_)    {const vec3<T> &v=s_>reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator<=(const color_xyz<T> &c0_, const color_xyz<T> &c1_)        {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)<=reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator<=(const color_xyz<T> &c_, typename math<T>::scalar_t s_)   {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)<=s_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator<=(typename math<T>::scalar_t s_, const color_xyz<T> &c_)   {const vec3<T> &v=s_<=reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator>=(const color_xyz<T> &c0_, const color_xyz<T> &c1_)        {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)>=reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator>=(const color_xyz<T> &c_, typename math<T>::scalar_t s_)   {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)>=s_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator>=(typename math<T>::scalar_t s_, const color_xyz<T> &c_)   {const vec3<T> &v=s_>=reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sel_eq(const color_xyz<T> &t0_, const color_xyz<T> &t1_,
                                                     const color_xyz<T> &c0_, const color_xyz<T> &c1_)           {const vec3<T> &v=sel_eq(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sel_lt(const color_xyz<T> &t0_, const color_xyz<T> &t1_,
                                                     const color_xyz<T> &c0_, const color_xyz<T> &c1_)           {const vec3<T> &v=sel_lt(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sel_le(const color_xyz<T> &t0_, const color_xyz<T> &t1_,
                                                     const color_xyz<T> &c0_, const color_xyz<T> &c1_)           {const vec3<T> &v=sel_le(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sel_eqz(const color_xyz<T> &t_,
                                                      const color_xyz<T> &c0_, const color_xyz<T> &c1_)          {const vec3<T> &v=sel_eqz(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sel_ltz(const color_xyz<T> &t_,
                                                      const color_xyz<T> &c0_, const color_xyz<T> &c1_)          {const vec3<T> &v=sel_ltz(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sel_lez(const color_xyz<T> &t_,
                                                      const color_xyz<T> &c0_, const color_xyz<T> &c1_)          {const vec3<T> &v=sel_lez(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE void operator+=(color_xyz<T> &cr_, const color_xyz<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_xyz<T> &cr_, const color_xyza<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_xyz<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)+=s_;}
template<typename T> PFC_INLINE void operator-=(color_xyz<T> &cr_, const color_xyz<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_xyz<T> &cr_, const color_xyza<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_xyz<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)-=s_;}
template<typename T> PFC_INLINE void operator*=(color_xyz<T> &cr_, const color_xyz<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_xyz<T> &cr_, const color_xyza<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_xyz<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)*=s_;}
template<typename T> PFC_INLINE void operator*=(color_xyz<T> &cr_, const mat33<T> &m_)                           {reinterpret_cast<vec3<T>&>(cr_)*=m_;}
template<typename T> PFC_INLINE void operator*=(color_xyz<T> &cr_, const mat44<T> &m_)                           {reinterpret_cast<vec3<T>&>(cr_)*=m_;}
template<typename T> PFC_INLINE void operator*=(color_xyz<T> &cr_, const quat<T> &q_)                            {reinterpret_cast<vec3<T>&>(cr_)*=q_;}
template<typename T> PFC_INLINE void operator/=(color_xyz<T> &cr_, const color_xyz<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_xyz<T> &cr_, const color_xyza<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_xyz<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)/=s_;}
template<typename T> PFC_INLINE color_xyz<T> operator+(const color_xyz<T> &c0_, const color_xyz<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)+reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator+(const color_xyz<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)+s_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator+(typename math<T>::scalar_t s_, const color_xyz<T> &c_)    {const vec3<T> &v=s_+reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator-(const color_xyz<T> &c0_, const color_xyz<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)-reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator-(const color_xyz<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)-s_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator-(typename math<T>::scalar_t s_, const color_xyz<T> &c_)    {const vec3<T> &v=s_-reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator-(const color_xyz<T> &c_)                                   {const vec3<T> &v=-reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator*(const color_xyz<T> &c0_, const color_xyz<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)*reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator*(const color_xyz<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*s_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator*(typename math<T>::scalar_t s_, const color_xyz<T> &c_)    {const vec3<T> &v=s_*reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator*(const color_xyz<T> &c_, const mat33<T> &m_)               {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*m_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator*(const mat33<T> &m_, const color_xyz<T> &c_)               {const vec3<T> &v=m_*reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator*(const color_xyz<T> &c_, const mat44<T> &m_)               {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*m_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator*(const mat44<T> &m_, const color_xyz<T> &c_)               {const vec3<T> &v=m_*reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator*(const color_xyz<T> &c_, const quat<T> &q_)                {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*q_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator/(const color_xyz<T> &c0_, const color_xyz<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)/reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator/(const color_xyz<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)/s_; return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> operator/(typename math<T>::scalar_t s_, const color_xyz<T> &c_)    {const vec3<T> &v=s_/reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const color_xyz<T> &c_)                           {return min(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_xyz<T> min(const color_xyz<T> &c0_,
                                                  const color_xyz<T> &c1_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> min(const color_xyz<T> &c0_,
                                                  const color_xyz<T> &c1_,
                                                  const color_xyz<T> &c2_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> min(const color_xyz<T> &c0_,
                                                  const color_xyz<T> &c1_,
                                                  const color_xyz<T> &c2_,
                                                  const color_xyz<T> &c3_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_), reinterpret_cast<const vec3<T>&>(c3_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> min(const color_xyz<T> &c_, typename math<T>::scalar_t s_)          {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c_), s_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> min(typename math<T>::scalar_t s_, const color_xyz<T> &c_)          {const vec3<T> &v=min(s_, reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const color_xyz<T> &c_)                           {return max(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_xyz<T> max(const color_xyz<T> &c0_,
                                                  const color_xyz<T> &c1_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> max(const color_xyz<T> &c0_,
                                                  const color_xyz<T> &c1_,
                                                  const color_xyz<T> &c2_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> max(const color_xyz<T> &c0_,
                                                  const color_xyz<T> &c1_,
                                                  const color_xyz<T> &c2_,
                                                  const color_xyz<T> &c3_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_), reinterpret_cast<const vec3<T>&>(c3_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> max(const color_xyz<T> &c_, typename math<T>::scalar_t s_)          {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c_), s_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> max(typename math<T>::scalar_t s_, const color_xyz<T> &c_)          {const vec3<T> &v=max(s_, reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> mul(const color_xyz<T> &c0_, const color_xyz<T> &c1_)               {const vec3<T> &v=mul(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> madd(const color_xyz<T> &c0_,
                                                   const color_xyz<T> &c1_,
                                                   const color_xyz<T> &c2_)                                      {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> madd(const color_xyz<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   typename math<T>::scalar_t add_)                              {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), mul_, add_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> madd(const color_xyz<T> &c_,
                                                   const color_xyz<T> &mul_,
                                                   typename math<T>::scalar_t add_)                              {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(mul_), add_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> madd(const color_xyz<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   const color_xyz<T> &add_)                                     {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), mul_, reinterpret_cast<const vec3<T>&>(add_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> rcp(const color_xyz<T> &c_)                                         {const vec3<T> &v=rcp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> rcp_z(const color_xyz<T> &c_)                                       {const vec3<T> &v=rcp_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> floor(const color_xyz<T> &c_)                                       {const vec3<T> &v=floor(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> ceil(const color_xyz<T> &c_)                                        {const vec3<T> &v=ceil(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> trunc(const color_xyz<T> &c_)                                       {const vec3<T> &v=trunc(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> frc(const color_xyz<T> &c_)                                         {const vec3<T> &v=frc(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> mod(const color_xyz<T> &c_, T div_)                                 {const vec3<T> &v=mod(reinterpret_cast<const vec3<T>&>(c_), div_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> cycle(const color_xyz<T> &c_, T cycle_)                             {const vec3<T> &v=cycle(reinterpret_cast<const vec3<T>&>(c_), cycle_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> cycle1(const color_xyz<T> &c_)                                      {const vec3<T> &v=cycle1(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sat(const color_xyz<T> &c_)                                         {const vec3<T> &v=sat(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> ssat(const color_xyz<T> &c_)                                        {const vec3<T> &v=ssat(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> clamp(const color_xyz<T> &c_,
                                                    const color_xyz<T> &min_,
                                                    const color_xyz<T> &max_)                                    {const vec3<T> &v=clamp(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(min_), reinterpret_cast<const vec3<T>&>(max_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> clamp(const color_xyz<T> &c_,
                                                    typename math<T>::scalar_t min_,
                                                    typename math<T>::scalar_t max_)                             {const vec3<T> &v=clamp(reinterpret_cast<const vec3<T>&>(c_), min_, max_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> abs(const color_xyz<T> &c_)                                         {const vec3<T> &v=abs(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sgn(const color_xyz<T> &c_)                                         {const vec3<T> &v=sgn(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sgn_zp(const color_xyz<T> &c_)                                      {const vec3<T> &v=sgn_zp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sqr(const color_xyz<T> &c_)                                         {const vec3<T> &v=sqr(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> cubic(const color_xyz<T> &c_)                                       {const vec3<T> &v=cubic(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sqrt(const color_xyz<T> &c_)                                        {const vec3<T> &v=sqrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> sqrt_z(const color_xyz<T> &c_)                                      {const vec3<T> &v=sqrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> cbrt(const color_xyz<T> &c_)                                        {const vec3<T> &v=cbrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> rsqrt(const color_xyz<T> &c_)                                       {const vec3<T> &v=rsqrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> rsqrt_z(const color_xyz<T> &c_)                                     {const vec3<T> &v=rsqrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> rcbrt(const color_xyz<T> &c_)                                       {const vec3<T> &v=rcbrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> rcbrt_z(const color_xyz<T> &c_)                                     {const vec3<T> &v=rcbrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const color_xyz<T> &c_)                          {return norm(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const color_xyz<T> &c_)                         {return rnorm(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const color_xyz<T> &c_)                       {return rnorm_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const color_xyz<T> &c_)                         {return norm2(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const color_xyz<T> &c_)                        {return rnorm2(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const color_xyz<T> &c_)                      {return rnorm2_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const color_xyz<T> &c_)                       {return norm_l1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const color_xyz<T> &c_)                      {return rnorm_l1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const color_xyz<T> &c_)                    {return rnorm_l1_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_xyz<T> exp(const color_xyz<T> &c_)                                         {const vec3<T> &v=exp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> exp2(const color_xyz<T> &c_)                                        {const vec3<T> &v=exp2(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> ln(const color_xyz<T> &c_)                                          {const vec3<T> &v=ln(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> log2(const color_xyz<T> &c_)                                        {const vec3<T> &v=log2(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> log10(const color_xyz<T> &c_)                                       {const vec3<T> &v=log10(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> pow(const color_xyz<T> &c_, typename math<T>::scalar_t p_)          {const vec3<T> &v=pow(reinterpret_cast<const vec3<T>&>(c_), p_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> unit(const color_xyz<T> &c_)                                        {const vec3<T> &v=unit(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> unit_z(const color_xyz<T> &c_)                                      {const vec3<T> &v=unit_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> cross(const color_xyz<T> &c0_, const color_xyz<T> &c1_)             {const vec3<T> &v=cross(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const color_xyz<T> &c0_, const color_xyz<T> &c1_) {return dot(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const color_xyz<T> &c_)                          {return dot1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void neg(color_xyz<T> &c_)                                                       {neg(reinterpret_cast<vec3<T>&>(c_));}
template<typename T, class Rand> PFC_INLINE void rand_u(color_xyz<T> &c_, Rand &rnd_)                            {rand_u(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_real1(color_xyz<T> &c_, Rand &rnd_)                        {rand_real1(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_ureal1(color_xyz<T> &c_, Rand &rnd_)                       {rand_ureal1(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T> PFC_INLINE color_xyz<T> smoothstep(const color_xyz<T> &c_)                                  {const vec3<T> &v=smoothstep(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> smootherstep(const color_xyz<T> &c_)                                {const vec3<T> &v=smootherstep(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> lerp(const color_xyz<T> &c0_, const color_xyz<T> &c1_, float t_)    {const vec3<T> &v=lerp(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), t_); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> reflect(const color_xyz<T> &c_, const color_xyz<T> &cn_)            {const vec3<T> &v=reflect(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(cn_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE color_xyz<T> reflect_u(const color_xyz<T> &c_, const color_xyz<T> &cn_)          {const vec3<T> &v=reflect_u(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(cn_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<unsigned shuffle_, typename T> PFC_INLINE color_xyz<T> shuffle(const color_xyz<T> &c_)                  {const vec3<T> &v=shuffle<shuffle_>(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_xyz<T>&>(v);}
template<typename T> PFC_INLINE void pack_u1(color_xyz32 &cr_, const color_xyz<T> &c_)                           {pack_u1(reinterpret_cast<vec3_32u&>(cr_), reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void pack_s1(color_xyz32 &cr_, const color_xyz<T> &c_)                           {pack_s1(reinterpret_cast<vec3_32s&>(cr_), reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void unpack_u1(color_xyz<T> &cr_, const color_xyz32 &c_)                         {unpack_u1(reinterpret_cast<vec3<T>&>(cr_), reinterpret_cast<const vec3_32u&>(c_));}
template<typename T> PFC_INLINE void unpack_s1(color_xyz<T> &cr_, const color_xyz32 &c_)                         {unpack_s1(reinterpret_cast<vec3<T>&>(cr_), reinterpret_cast<const vec3_32s&>(c_));}
//----------------------------------------------------------------------------


//============================================================================
// color_xyza
//============================================================================
template<typename T>
color_xyza<T>::color_xyza()
{
}
//----

template<typename T>
color_xyza<T>::color_xyza(T v_)
  :x(v_)
  ,y(v_)
  ,z(v_)
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
color_xyza<T>::color_xyza(T x_, T y_, T z_)
  :x(x_)
  ,y(y_)
  ,z(z_)
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
color_xyza<T>::color_xyza(T x_, T y_, T z_, T a_)
  :x(x_)
  ,y(y_)
  ,z(z_)
  ,a(a_)
{
}
//----

template<typename T>
color_xyza<T>::color_xyza(const color_xyz<T> &c_)
  :x(c_.x)
  ,y(c_.y)
  ,z(c_.z)
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
color_xyza<T>::color_xyza(const color_xyz<T> &c_, T a_)
  :x(c_.x)
  ,y(c_.y)
  ,z(c_.z)
  ,a(a_)
{
}
//----

template<typename T>
template<typename U>
color_xyza<T>::color_xyza(const color_xyza<U> &c_)
  :x(T(c_.x))
  ,y(T(c_.y))
  ,z(T(c_.z))
  ,a(T(c_.a))
{
}
//----

template<typename T>
template<typename U>
color_xyza<T>::color_xyza(const color_xyz<U> &c_)
  :x(T(c_.x))
  ,y(T(c_.y))
  ,z(T(c_.z))
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
template<typename U>
color_xyza<T>::color_xyza(const color_xyz<U> &c_, U a_)
  :x(T(c_.x))
  ,y(T(c_.y))
  ,z(T(c_.z))
  ,a(T(a_))
{
}
//----------------------------------------------------------------------------

template<typename T>
const T &color_xyza<T>::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &color_xyza<T>::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void color_xyza<T>::set(T v_)
{
  x=v_;
  y=v_;
  z=v_;
}
//----

template<typename T>
void color_xyza<T>::set(T x_, T y_, T z_)
{
  x=x_;
  y=y_;
  z=z_;
}
//----

template<typename T>
void color_xyza<T>::set(T x_, T y_, T z_, T a_)
{
  x=x_;
  y=y_;
  z=z_;
  a=a_;
}
//----

template<typename T>
void color_xyza<T>::set(const color_xyz<T> &c_, T a_)
{
  x=c_.x;
  y=c_.y;
  z=c_.z;
  a=a_;
}
//----

template<typename T>
template<typename U>
void color_xyza<T>::set(const color_xyza<U> &c_)
{
  x=T(c_.x);
  y=T(c_.y);
  z=T(c_.z);
  a=T(c_.a);
}
//----------------------------------------------------------------------------

// vec4 interface for color_xyza
template<typename T> PFC_INLINE bool is_zero(const color_xyza<T> &c_)                                              {return is_zero(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool is_black(const color_xyza<T> &c_)                                             {return is_zero(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_sat(const color_xyza<T> &c_)                                               {return is_sat(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool is_ssat(const color_xyza<T> &c_)                                              {return is_ssat(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool operator==(const color_xyza<T> &c0_, const color_xyza<T> &c1_)                {return reinterpret_cast<const vec4<T>&>(c0_)==reinterpret_cast<const vec4<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator==(const color_xyza<T> &c_, typename math<T>::scalar_t s_)            {return reinterpret_cast<const vec4<T>&>(c_)==s_;}
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const color_xyza<T> &c_)            {return s_==reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE bool operator!=(const color_xyza<T> &c0_, const color_xyza<T> &c1_)                {return reinterpret_cast<const vec4<T>&>(c0_)!=reinterpret_cast<const vec4<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator!=(const color_xyza<T> &c_, typename math<T>::scalar_t s_)            {return reinterpret_cast<const vec4<T>&>(c_)!=s_;}
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const color_xyza<T> &c_)            {return s_!=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE color_xyza<T> operator<(const color_xyza<T> &c0_, const color_xyza<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)<reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator<(const color_xyza<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)<s_; return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator<(typename math<T>::scalar_t s_, const color_xyza<T> &c_)    {const vec4<T> &v=s_<reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator>(const color_xyza<T> &c0_, const color_xyza<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)>reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator>(const color_xyza<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)>s_; return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator>(typename math<T>::scalar_t s_, const color_xyza<T> &c_)    {const vec4<T> &v=s_>reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator<=(const color_xyza<T> &c0_, const color_xyza<T> &c1_)       {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)<=reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator<=(const color_xyza<T> &c_, typename math<T>::scalar_t s_)   {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)<=s_; return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator<=(typename math<T>::scalar_t s_, const color_xyza<T> &c_)   {const vec4<T> &v=s_<=reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator>=(const color_xyza<T> &c0_, const color_xyza<T> &c1_)       {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)>=reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator>=(const color_xyza<T> &c_, typename math<T>::scalar_t s_)   {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)>=s_; return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator>=(typename math<T>::scalar_t s_, const color_xyza<T> &c_)   {const vec4<T> &v=s_>=reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sel_eq(const color_xyza<T> &t0_, const color_xyza<T> &t1_,
                                                     const color_xyza<T> &c0_, const color_xyza<T> &c1_)           {const vec4<T> &v=sel_eq(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sel_lt(const color_xyza<T> &t0_, const color_xyza<T> &t1_,
                                                     const color_xyza<T> &c0_, const color_xyza<T> &c1_)           {const vec4<T> &v=sel_lt(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sel_le(const color_xyza<T> &t0_, const color_xyza<T> &t1_,
                                                     const color_xyza<T> &c0_, const color_xyza<T> &c1_)           {const vec4<T> &v=sel_le(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sel_eqz(const color_xyza<T> &t_,
                                                      const color_xyza<T> &c0_, const color_xyza<T> &c1_)          {const vec4<T> &v=sel_eqz(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sel_ltz(const color_xyza<T> &t_,
                                                      const color_xyza<T> &c0_, const color_xyza<T> &c1_)          {const vec4<T> &v=sel_ltz(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sel_lez(const color_xyza<T> &t_,
                                                      const color_xyza<T> &c0_, const color_xyza<T> &c1_)          {const vec4<T> &v=sel_lez(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE void operator+=(color_xyza<T> &cr_, const color_xyza<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)+=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_xyza<T> &cr_, const color_xyz<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_xyza<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)+=s_;}
template<typename T> PFC_INLINE void operator-=(color_xyza<T> &cr_, const color_xyza<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)-=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_xyza<T> &cr_, const color_xyz<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_xyza<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)-=s_;}
template<typename T> PFC_INLINE void operator*=(color_xyza<T> &cr_, const color_xyza<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)*=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_xyza<T> &cr_, const color_xyz<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_xyza<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)*=s_;}
template<typename T> PFC_INLINE void operator*=(color_xyza<T> &cr_, const mat44<T> &m_)                            {reinterpret_cast<vec4<T>&>(cr_)*=m_;}
template<typename T> PFC_INLINE void operator/=(color_xyza<T> &cr_, const color_xyza<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)/=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_xyza<T> &cr_, const color_xyz<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_xyza<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)/=s_;}
template<typename T> PFC_INLINE color_xyza<T> operator+(const color_xyza<T> &c0_, const color_xyza<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)+reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator+(const color_xyza<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)+s_; return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator+(typename math<T>::scalar_t s_, const color_xyza<T> &c_)    {const vec4<T> &v=s_+reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator-(const color_xyza<T> &c0_, const color_xyza<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)-reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator-(const color_xyza<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)-s_; return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator-(typename math<T>::scalar_t s_, const color_xyza<T> &c_)    {const vec4<T> &v=s_-reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator-(const color_xyza<T> &c_)                                   {const vec4<T> &v=-reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator*(const color_xyza<T> &c0_, const color_xyza<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)*reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator*(const color_xyza<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)*s_; return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator*(typename math<T>::scalar_t s_, const color_xyza<T> &c_)    {const vec4<T> &v=s_*reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator*(const color_xyza<T> &c_, const mat44<T> &m_)               {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)*m_; return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator*(const mat44<T> &m_, const color_xyza<T> &c_)               {const vec4<T> &v=m_*reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator/(const color_xyza<T> &c0_, const color_xyza<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)/reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator/(const color_xyza<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)/s_; return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> operator/(typename math<T>::scalar_t s_, const color_xyza<T> &c_)    {const vec4<T> &v=s_/reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const color_xyza<T> &c_)                            {return min(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_xyza<T> min(const color_xyza<T> &c0_,
                                                  const color_xyza<T> &c1_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> min(const color_xyza<T> &c0_,
                                                  const color_xyza<T> &c1_,
                                                  const color_xyza<T> &c2_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> min(const color_xyza<T> &c0_,
                                                  const color_xyza<T> &c1_,
                                                  const color_xyza<T> &c2_,
                                                  const color_xyza<T> &c3_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_), reinterpret_cast<const vec4<T>&>(c3_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> min(const color_xyza<T> &c_, typename math<T>::scalar_t s_)          {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c_), s_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> min(typename math<T>::scalar_t s_, const color_xyza<T> &c_)          {const vec4<T> &v=min(s_, reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const color_xyza<T> &c_)                            {return max(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_xyza<T> max(const color_xyza<T> &c0_,
                                                  const color_xyza<T> &c1_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> max(const color_xyza<T> &c0_,
                                                  const color_xyza<T> &c1_,
                                                  const color_xyza<T> &c2_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> max(const color_xyza<T> &c0_,
                                                  const color_xyza<T> &c1_,
                                                  const color_xyza<T> &c2_,
                                                  const color_xyza<T> &c3_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_), reinterpret_cast<const vec4<T>&>(c3_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> max(const color_xyza<T> &c_, typename math<T>::scalar_t s_)          {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c_), s_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> max(typename math<T>::scalar_t s_, const color_xyza<T> &c_)          {const vec4<T> &v=max(s_, reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> mul(const color_xyza<T> &c0_, const color_xyza<T> &c1_)              {const vec4<T> &v=mul(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> madd(const color_xyza<T> &c0_,
                                                   const color_xyza<T> &c1_,
                                                   const color_xyza<T> &c2_)                                       {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> madd(const color_xyza<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   typename math<T>::scalar_t add_)                                {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), mul_, add_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> madd(const color_xyza<T> &c_,
                                                   const color_xyza<T> &mul_,
                                                   typename math<T>::scalar_t add_)                                {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(mul_), add_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> madd(const color_xyza<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   const color_xyza<T> &add_)                                      {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), mul_, reinterpret_cast<const vec4<T>&>(add_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> rcp(const color_xyza<T> &c_)                                         {const vec4<T> &v=rcp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> rcp_z(const color_xyza<T> &c_)                                       {const vec4<T> &v=rcp_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> floor(const color_xyza<T> &c_)                                       {const vec4<T> &v=floor(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> ceil(const color_xyza<T> &c_)                                        {const vec4<T> &v=ceil(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> trunc(const color_xyza<T> &c_)                                       {const vec4<T> &v=trunc(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> frc(const color_xyza<T> &c_)                                         {const vec4<T> &v=frc(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> mod(const color_xyza<T> &c_, T div_)                                 {const vec4<T> &v=mod(reinterpret_cast<const vec4<T>&>(c_), div_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> cycle(const color_xyza<T> &c_, T cycle_)                             {const vec4<T> &v=cycle(reinterpret_cast<const vec4<T>&>(c_), cycle_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> cycle1(const color_xyza<T> &c_)                                      {const vec4<T> &v=cycle1(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sat(const color_xyza<T> &c_)                                         {const vec4<T> &v=sat(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> ssat(const color_xyza<T> &c_)                                        {const vec4<T> &v=ssat(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> clamp(const color_xyza<T> &c_,
                                                    const color_xyza<T> &min_,
                                                    const color_xyza<T> &max_)                                     {const vec4<T> &v=clamp(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(min_), reinterpret_cast<const vec4<T>&>(max_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> clamp(const color_xyza<T> &c_,
                                                    typename math<T>::scalar_t min_,
                                                    typename math<T>::scalar_t max_)                               {const vec4<T> &v=clamp(reinterpret_cast<const vec4<T>&>(c_), min_, max_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> abs(const color_xyza<T> &c_)                                         {const vec4<T> &v=abs(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sgn(const color_xyza<T> &c_)                                         {const vec4<T> &v=sgn(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sgn_zp(const color_xyza<T> &c_)                                      {const vec4<T> &v=sgn_zp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sqr(const color_xyza<T> &c_)                                         {const vec4<T> &v=sqr(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> cubic(const color_xyza<T> &c_)                                       {const vec4<T> &v=cubic(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sqrt(const color_xyza<T> &c_)                                        {const vec4<T> &v=sqrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> sqrt_z(const color_xyza<T> &c_)                                      {const vec4<T> &v=sqrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> cbrt(const color_xyza<T> &c_)                                        {const vec4<T> &v=cbrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> rsqrt(const color_xyza<T> &c_)                                       {const vec4<T> &v=rsqrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> rsqrt_z(const color_xyza<T> &c_)                                     {const vec4<T> &v=rsqrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> rcbrt(const color_xyza<T> &c_)                                       {const vec4<T> &v=rcbrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> rcbrt_z(const color_xyza<T> &c_)                                     {const vec4<T> &v=rcbrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const color_xyza<T> &c_)                           {return norm(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const color_xyza<T> &c_)                          {return rnorm(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const color_xyza<T> &c_)                        {return rnorm_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const color_xyza<T> &c_)                          {return norm2(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const color_xyza<T> &c_)                         {return rnorm2(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const color_xyza<T> &c_)                       {return rnorm2_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const color_xyza<T> &c_)                        {return norm_l1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const color_xyza<T> &c_)                       {return rnorm_l1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const color_xyza<T> &c_)                     {return rnorm_l1_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_xyza<T> exp(const color_xyza<T> &c_)                                         {const vec4<T> &v=exp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> exp2(const color_xyza<T> &c_)                                        {const vec4<T> &v=exp2(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> ln(const color_xyza<T> &c_)                                          {const vec4<T> &v=ln(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> log2(const color_xyza<T> &c_)                                        {const vec4<T> &v=log2(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> log10(const color_xyza<T> &c_)                                       {const vec4<T> &v=log10(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> pow(const color_xyza<T> &c_, typename math<T>::scalar_t p_)          {const vec4<T> &v=pow(reinterpret_cast<const vec4<T>&>(c_), p_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> unit(const color_xyza<T> &c_)                                        {const vec4<T> &v=unit(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> unit_z(const color_xyza<T> &c_)                                      {const vec4<T> &v=unit_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const color_xyza<T> &c0_, const color_xyza<T> &c1_) {return dot(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const color_xyza<T> &c_)                           {return dot1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void neg(color_xyza<T> &c_)                                                        {neg(reinterpret_cast<vec4<T>&>(c_));}
template<typename T, class Rand> PFC_INLINE void rand_u(color_xyza<T> &c_, Rand &rnd_)                             {rand_u(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_real1(color_xyza<T> &c_, Rand &rnd_)                         {rand_real1(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_ureal1(color_xyza<T> &c_, Rand &rnd_)                        {rand_ureal1(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T> PFC_INLINE color_xyza<T> smoothstep(const color_xyza<T> &c_)                                  {const vec4<T> &v=smoothstep(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> smootherstep(const color_xyza<T> &c_)                                {const vec4<T> &v=smootherstep(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> lerp(const color_xyza<T> &c0_, const color_xyza<T> &c1_, float t_)   {const vec4<T> &v=lerp(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), t_); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> reflect(const color_xyza<T> &c_, const color_xyza<T> &cn_)           {const vec4<T> &v=reflect(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(cn_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE color_xyza<T> reflect_u(const color_xyza<T> &c_, const color_xyza<T> &cn_)         {const vec4<T> &v=reflect_u(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(cn_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<unsigned shuffle_, typename T> PFC_INLINE color_xyza<T> shuffle(const color_xyza<T> &c_)                  {const vec4<T> &v=shuffle<shuffle_>(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_xyza<T>&>(v);}
template<typename T> PFC_INLINE void pack_u1(color_xyza32 &cr_, const color_xyza<T> &c_)                           {pack_u1(reinterpret_cast<vec4_32u&>(cr_), reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void pack_s1(color_xyza32 &cr_, const color_xyza<T> &c_)                           {pack_s1(reinterpret_cast<vec4_32s&>(cr_), reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void unpack_u1(color_xyza<T> &cr_, const color_xyza32 &c_)                         {unpack_u1(reinterpret_cast<vec4<T>&>(cr_), reinterpret_cast<const vec4_32u&>(c_));}
template<typename T> PFC_INLINE void unpack_s1(color_xyza<T> &cr_, const color_xyza32 &c_)                         {unpack_s1(reinterpret_cast<vec4<T>&>(cr_), reinterpret_cast<const vec4_32s&>(c_));}
//----------------------------------------------------------------------------


//============================================================================
// color_yiq
//============================================================================
template<typename T>
color_yiq<T>::color_yiq()
{
}
//----

template<typename T>
color_yiq<T>::color_yiq(T y_, T i_, T q_)
  :y(y_)
  ,i(i_)
  ,q(q_)
{
}
//----

template<typename T>
color_yiq<T>::color_yiq(const color_yiqa<T> &c_)
  :y(c_.y)
  ,i(c_.i)
  ,q(c_.q)
{
}
//----

template<typename T>
template<typename U>
color_yiq<T>::color_yiq(const color_yiq<U> &c_)
  :y(T(c_.y))
  ,i(T(c_.i))
  ,q(T(c_.q))
{
}
//----

template<typename T>
template<typename U>
color_yiq<T>::color_yiq(const color_yiqa<U> &c_)
  :y(T(c_.y))
  ,i(T(c_.i))
  ,q(T(c_.q))
{
}
//----------------------------------------------------------------------------

template<typename T>
const T &color_yiq<T>::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &color_yiq<T>::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void color_yiq<T>::set(T y_, T i_, T q_)
{
  y=y_;
  i=i_;
  q=q_;
}
//----

template<typename T>
template<typename U>
void color_yiq<T>::set(const color_yiq<U> &c_)
{
  y=T(c_.y);
  i=T(c_.i);
  q=T(c_.q);
}
//----------------------------------------------------------------------------

// vec3 interface for color_yiq
template<typename T> PFC_INLINE bool is_zero(const color_yiq<T> &c_)                                             {return is_zero(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_sat(const color_yiq<T> &c_)                                              {return is_sat(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_ssat(const color_yiq<T> &c_)                                             {return is_ssat(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool operator==(const color_yiq<T> &c0_, const color_yiq<T> &c1_)                {return reinterpret_cast<const vec3<T>&>(c0_)==reinterpret_cast<const vec3<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator==(const color_yiq<T> &c_, typename math<T>::scalar_t s_)           {return reinterpret_cast<const vec3<T>&>(c_)==s_;}
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const color_yiq<T> &c_)           {return s_==reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE bool operator!=(const color_yiq<T> &c0_, const color_yiq<T> &c1_)                {return reinterpret_cast<const vec3<T>&>(c0_)!=reinterpret_cast<const vec3<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator!=(const color_yiq<T> &c_, typename math<T>::scalar_t s_)           {return reinterpret_cast<const vec3<T>&>(c_)!=s_;}
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const color_yiq<T> &c_)           {return s_!=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE color_yiq<T> operator<(const color_yiq<T> &c0_, const color_yiq<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)<reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator<(const color_yiq<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)<s_; return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator<(typename math<T>::scalar_t s_, const color_yiq<T> &c_)    {const vec3<T> &v=s_<reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator>(const color_yiq<T> &c0_, const color_yiq<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)>reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator>(const color_yiq<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)>s_; return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator>(typename math<T>::scalar_t s_, const color_yiq<T> &c_)    {const vec3<T> &v=s_>reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator<=(const color_yiq<T> &c0_, const color_yiq<T> &c1_)        {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)<=reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator<=(const color_yiq<T> &c_, typename math<T>::scalar_t s_)   {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)<=s_; return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator<=(typename math<T>::scalar_t s_, const color_yiq<T> &c_)   {const vec3<T> &v=s_<=reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator>=(const color_yiq<T> &c0_, const color_yiq<T> &c1_)        {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)>=reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator>=(const color_yiq<T> &c_, typename math<T>::scalar_t s_)   {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)>=s_; return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator>=(typename math<T>::scalar_t s_, const color_yiq<T> &c_)   {const vec3<T> &v=s_>=reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sel_eq(const color_yiq<T> &t0_, const color_yiq<T> &t1_,
                                                     const color_yiq<T> &c0_, const color_yiq<T> &c1_)           {const vec3<T> &v=sel_eq(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sel_lt(const color_yiq<T> &t0_, const color_yiq<T> &t1_,
                                                     const color_yiq<T> &c0_, const color_yiq<T> &c1_)           {const vec3<T> &v=sel_lt(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sel_le(const color_yiq<T> &t0_, const color_yiq<T> &t1_,
                                                     const color_yiq<T> &c0_, const color_yiq<T> &c1_)           {const vec3<T> &v=sel_le(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sel_eqz(const color_yiq<T> &t_,
                                                      const color_yiq<T> &c0_, const color_yiq<T> &c1_)          {const vec3<T> &v=sel_eqz(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sel_ltz(const color_yiq<T> &t_,
                                                      const color_yiq<T> &c0_, const color_yiq<T> &c1_)          {const vec3<T> &v=sel_ltz(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sel_lez(const color_yiq<T> &t_,
                                                      const color_yiq<T> &c0_, const color_yiq<T> &c1_)          {const vec3<T> &v=sel_lez(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE void operator+=(color_yiq<T> &cr_, const color_yiq<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_yiq<T> &cr_, const color_yiqa<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_yiq<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)+=s_;}
template<typename T> PFC_INLINE void operator-=(color_yiq<T> &cr_, const color_yiq<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_yiq<T> &cr_, const color_yiqa<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_yiq<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)-=s_;}
template<typename T> PFC_INLINE void operator*=(color_yiq<T> &cr_, const color_yiq<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_yiq<T> &cr_, const color_yiqa<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_yiq<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)*=s_;}
template<typename T> PFC_INLINE void operator*=(color_yiq<T> &cr_, const mat44<T> &m_)                           {reinterpret_cast<vec3<T>&>(cr_)*=m_;}
template<typename T> PFC_INLINE void operator/=(color_yiq<T> &cr_, const color_yiq<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_yiq<T> &cr_, const color_yiqa<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_yiq<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)/=s_;}
template<typename T> PFC_INLINE color_yiq<T> operator+(const color_yiq<T> &c0_, const color_yiq<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)+reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator+(const color_yiq<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)+s_; return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator+(typename math<T>::scalar_t s_, const color_yiq<T> &c_)    {const vec3<T> &v=s_+reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator-(const color_yiq<T> &c0_, const color_yiq<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)-reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator-(const color_yiq<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)-s_; return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator-(typename math<T>::scalar_t s_, const color_yiq<T> &c_)    {const vec3<T> &v=s_-reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator-(const color_yiq<T> &c_)                                   {const vec3<T> &v=-reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator*(const color_yiq<T> &c0_, const color_yiq<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)*reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator*(const color_yiq<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*s_; return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator*(typename math<T>::scalar_t s_, const color_yiq<T> &c_)    {const vec3<T> &v=s_*reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator*(const color_yiq<T> &c_, const mat44<T> &m_)               {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*m_; return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator*(const mat44<T> &m_, const color_yiq<T> &c_)               {const vec3<T> &v=m_*reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator/(const color_yiq<T> &c0_, const color_yiq<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)/reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator/(const color_yiq<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)/s_; return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> operator/(typename math<T>::scalar_t s_, const color_yiq<T> &c_)    {const vec3<T> &v=s_/reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const color_yiq<T> &c_)                           {return min(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_yiq<T> min(const color_yiq<T> &c0_,
                                                  const color_yiq<T> &c1_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> min(const color_yiq<T> &c0_,
                                                  const color_yiq<T> &c1_,
                                                  const color_yiq<T> &c2_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> min(const color_yiq<T> &c0_,
                                                  const color_yiq<T> &c1_,
                                                  const color_yiq<T> &c2_,
                                                  const color_yiq<T> &c3_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_), reinterpret_cast<const vec3<T>&>(c3_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> min(const color_yiq<T> &c_, typename math<T>::scalar_t s_)          {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c_), s_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> min(typename math<T>::scalar_t s_, const color_yiq<T> &c_)          {const vec3<T> &v=min(s_, reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const color_yiq<T> &c_)                           {return max(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_yiq<T> max(const color_yiq<T> &c0_,
                                                  const color_yiq<T> &c1_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> max(const color_yiq<T> &c0_,
                                                  const color_yiq<T> &c1_,
                                                  const color_yiq<T> &c2_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> max(const color_yiq<T> &c0_,
                                                  const color_yiq<T> &c1_,
                                                  const color_yiq<T> &c2_,
                                                  const color_yiq<T> &c3_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_), reinterpret_cast<const vec3<T>&>(c3_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> max(const color_yiq<T> &c_, typename math<T>::scalar_t s_)          {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c_), s_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> max(typename math<T>::scalar_t s_, const color_yiq<T> &c_)          {const vec3<T> &v=max(s_, reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> mul(const color_yiq<T> &c0_, const color_yiq<T> &c1_)               {const vec3<T> &v=mul(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> madd(const color_yiq<T> &c0_,
                                                   const color_yiq<T> &c1_,
                                                   const color_yiq<T> &c2_)                                      {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> madd(const color_yiq<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   typename math<T>::scalar_t add_)                              {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), mul_, add_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> madd(const color_yiq<T> &c_,
                                                   const color_yiq<T> &mul_,
                                                   typename math<T>::scalar_t add_)                              {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(mul_), add_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> madd(const color_yiq<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   const color_yiq<T> &add_)                                     {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), mul_, reinterpret_cast<const vec3<T>&>(add_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> rcp(const color_yiq<T> &c_)                                         {const vec3<T> &v=rcp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> rcp_z(const color_yiq<T> &c_)                                       {const vec3<T> &v=rcp_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> floor(const color_yiq<T> &c_)                                       {const vec3<T> &v=floor(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> ceil(const color_yiq<T> &c_)                                        {const vec3<T> &v=ceil(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> trunc(const color_yiq<T> &c_)                                       {const vec3<T> &v=trunc(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> frc(const color_yiq<T> &c_)                                         {const vec3<T> &v=frc(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> mod(const color_yiq<T> &c_, T div_)                                 {const vec3<T> &v=mod(reinterpret_cast<const vec3<T>&>(c_), div_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> cycle(const color_yiq<T> &c_, T cycle_)                             {const vec3<T> &v=cycle(reinterpret_cast<const vec3<T>&>(c_), cycle_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> cycle1(const color_yiq<T> &c_)                                      {const vec3<T> &v=cycle1(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sat(const color_yiq<T> &c_)                                         {const vec3<T> &v=sat(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> ssat(const color_yiq<T> &c_)                                        {const vec3<T> &v=ssat(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> clamp(const color_yiq<T> &c_,
                                                    const color_yiq<T> &min_,
                                                    const color_yiq<T> &max_)                                    {const vec3<T> &v=clamp(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(min_), reinterpret_cast<const vec3<T>&>(max_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> clamp(const color_yiq<T> &c_,
                                                    typename math<T>::scalar_t min_,
                                                    typename math<T>::scalar_t max_)                             {const vec3<T> &v=clamp(reinterpret_cast<const vec3<T>&>(c_), min_, max_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> abs(const color_yiq<T> &c_)                                         {const vec3<T> &v=abs(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sgn(const color_yiq<T> &c_)                                         {const vec3<T> &v=sgn(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sgn_zp(const color_yiq<T> &c_)                                      {const vec3<T> &v=sgn_zp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sqr(const color_yiq<T> &c_)                                         {const vec3<T> &v=sqr(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> cubic(const color_yiq<T> &c_)                                       {const vec3<T> &v=cubic(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sqrt(const color_yiq<T> &c_)                                        {const vec3<T> &v=sqrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> sqrt_z(const color_yiq<T> &c_)                                      {const vec3<T> &v=sqrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> cbrt(const color_yiq<T> &c_)                                        {const vec3<T> &v=cbrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> rsqrt(const color_yiq<T> &c_)                                       {const vec3<T> &v=rsqrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> rsqrt_z(const color_yiq<T> &c_)                                     {const vec3<T> &v=rsqrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> rcbrt(const color_yiq<T> &c_)                                       {const vec3<T> &v=rcbrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> rcbrt_z(const color_yiq<T> &c_)                                     {const vec3<T> &v=rcbrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const color_yiq<T> &c_)                          {return norm(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const color_yiq<T> &c_)                         {return rnorm(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const color_yiq<T> &c_)                       {return rnorm_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const color_yiq<T> &c_)                         {return norm2(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const color_yiq<T> &c_)                        {return rnorm2(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const color_yiq<T> &c_)                      {return rnorm2_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const color_yiq<T> &c_)                       {return norm_l1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const color_yiq<T> &c_)                      {return rnorm_l1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const color_yiq<T> &c_)                    {return rnorm_l1_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_yiq<T> exp(const color_yiq<T> &c_)                                         {const vec3<T> &v=exp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> exp2(const color_yiq<T> &c_)                                        {const vec3<T> &v=exp2(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> ln(const color_yiq<T> &c_)                                          {const vec3<T> &v=ln(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> log2(const color_yiq<T> &c_)                                        {const vec3<T> &v=log2(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> log10(const color_yiq<T> &c_)                                       {const vec3<T> &v=log10(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> pow(const color_yiq<T> &c_, typename math<T>::scalar_t p_)          {const vec3<T> &v=pow(reinterpret_cast<const vec3<T>&>(c_), p_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> unit(const color_yiq<T> &c_)                                        {const vec3<T> &v=unit(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> unit_z(const color_yiq<T> &c_)                                      {const vec3<T> &v=unit_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> cross(const color_yiq<T> &c0_, const color_yiq<T> &c1_)             {const vec3<T> &v=cross(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const color_yiq<T> &c0_, const color_yiq<T> &c1_) {return dot(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const color_yiq<T> &c_)                          {return dot1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void neg(color_yiq<T> &c_)                                                       {neg(reinterpret_cast<vec3<T>&>(c_));}
template<typename T, class Rand> PFC_INLINE void rand_u(color_yiq<T> &c_, Rand &rnd_)                            {rand_u(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_real1(color_yiq<T> &c_, Rand &rnd_)                        {rand_real1(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_ureal1(color_yiq<T> &c_, Rand &rnd_)                       {rand_ureal1(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T> PFC_INLINE color_yiq<T> smoothstep(const color_yiq<T> &c_)                                  {const vec3<T> &v=smoothstep(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> smootherstep(const color_yiq<T> &c_)                                {const vec3<T> &v=smootherstep(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> lerp(const color_yiq<T> &c0_, const color_yiq<T> &c1_, float t_)    {const vec3<T> &v=lerp(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), t_); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> reflect(const color_yiq<T> &c_, const color_yiq<T> &cn_)            {const vec3<T> &v=reflect(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(cn_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE color_yiq<T> reflect_u(const color_yiq<T> &c_, const color_yiq<T> &cn_)          {const vec3<T> &v=reflect_u(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(cn_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<unsigned shuffle_, typename T> PFC_INLINE color_yiq<T> shuffle(const color_yiq<T> &c_)                  {const vec3<T> &v=shuffle<shuffle_>(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_yiq<T>&>(v);}
template<typename T> PFC_INLINE void pack_u1(color_yiq32 &cr_, const color_yiq<T> &c_)                           {pack_u1(reinterpret_cast<vec3_32u&>(cr_), reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void pack_s1(color_yiq32 &cr_, const color_yiq<T> &c_)                           {pack_s1(reinterpret_cast<vec3_32s&>(cr_), reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void unpack_u1(color_yiq<T> &cr_, const color_yiq32 &c_)                         {unpack_u1(reinterpret_cast<vec3<T>&>(cr_), reinterpret_cast<const vec3_32u&>(c_));}
template<typename T> PFC_INLINE void unpack_s1(color_yiq<T> &cr_, const color_yiq32 &c_)                         {unpack_s1(reinterpret_cast<vec3<T>&>(cr_), reinterpret_cast<const vec3_32s&>(c_));}
//----------------------------------------------------------------------------


//============================================================================
// color_yiqa
//============================================================================
template<typename T>
color_yiqa<T>::color_yiqa()
{
}
//----

template<typename T>
color_yiqa<T>::color_yiqa(T y_, T i_, T q_)
  :y(y_)
  ,i(i_)
  ,q(q_)
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
color_yiqa<T>::color_yiqa(T y_, T i_, T q_, T a_)
  :y(y_)
  ,i(i_)
  ,q(q_)
  ,a(a_)
{
}
//----

template<typename T>
color_yiqa<T>::color_yiqa(const color_yiq<T> &c_)
  :y(c_.y)
  ,i(c_.i)
  ,q(c_.q)
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
color_yiqa<T>::color_yiqa(const color_yiq<T> &c_, T a_)
  :y(c_.y)
  ,i(c_.i)
  ,q(c_.q)
  ,a(a_)
{
}
//----

template<typename T>
template<typename U>
color_yiqa<T>::color_yiqa(const color_yiqa<U> &c_)
  :y(T(c_.y))
  ,i(T(c_.i))
  ,q(T(c_.q))
  ,a(T(c_.a))
{
}
//----

template<typename T>
template<typename U>
color_yiqa<T>::color_yiqa(const color_yiq<U> &c_)
  :y(T(c_.y))
  ,i(T(c_.i))
  ,q(T(c_.q))
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
template<typename U>
color_yiqa<T>::color_yiqa(const color_yiq<U> &c_, U a_)
  :y(T(c_.y))
  ,i(T(c_.i))
  ,q(T(c_.q))
  ,a(T(a_))
{
}
//----------------------------------------------------------------------------

template<typename T>
const T &color_yiqa<T>::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &color_yiqa<T>::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void color_yiqa<T>::set(T y_, T i_, T q_)
{
  y=y_;
  i=i_;
  q=q_;
}
//----

template<typename T>
void color_yiqa<T>::set(T y_, T i_, T q_, T a_)
{
  y=y_;
  i=i_;
  q=q_;
  a=a_;
}
//----

template<typename T>
void color_yiqa<T>::set(const color_yiq<T> &c_, T a_)
{
  y=c_.y;
  i=c_.i;
  q=c_.q;
  a=a_;
}
//----

template<typename T>
template<typename U>
void color_yiqa<T>::set(const color_yiqa<U> &c_)
{
  y=T(c_.y);
  i=T(c_.i);
  q=T(c_.q);
  a=T(c_.a);
}
//----------------------------------------------------------------------------

// vec4 interface for color_yiqa
template<typename T> PFC_INLINE bool is_zero(const color_yiqa<T> &c_)                                              {return is_zero(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool is_sat(const color_yiqa<T> &c_)                                               {return is_sat(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool is_ssat(const color_yiqa<T> &c_)                                              {return is_ssat(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool operator==(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)                {return reinterpret_cast<const vec4<T>&>(c0_)==reinterpret_cast<const vec4<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator==(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)            {return reinterpret_cast<const vec4<T>&>(c_)==s_;}
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)            {return s_==reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE bool operator!=(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)                {return reinterpret_cast<const vec4<T>&>(c0_)!=reinterpret_cast<const vec4<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator!=(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)            {return reinterpret_cast<const vec4<T>&>(c_)!=s_;}
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)            {return s_!=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE color_yiqa<T> operator<(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)<reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator<(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)<s_; return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator<(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)    {const vec4<T> &v=s_<reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator>(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)>reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator>(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)>s_; return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator>(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)    {const vec4<T> &v=s_>reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator<=(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)       {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)<=reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator<=(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)   {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)<=s_; return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator<=(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)   {const vec4<T> &v=s_<=reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator>=(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)       {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)>=reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator>=(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)   {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)>=s_; return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator>=(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)   {const vec4<T> &v=s_>=reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sel_eq(const color_yiqa<T> &t0_, const color_yiqa<T> &t1_,
                                                     const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)           {const vec4<T> &v=sel_eq(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sel_lt(const color_yiqa<T> &t0_, const color_yiqa<T> &t1_,
                                                     const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)           {const vec4<T> &v=sel_lt(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sel_le(const color_yiqa<T> &t0_, const color_yiqa<T> &t1_,
                                                     const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)           {const vec4<T> &v=sel_le(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sel_eqz(const color_yiqa<T> &t_,
                                                      const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)          {const vec4<T> &v=sel_eqz(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sel_ltz(const color_yiqa<T> &t_,
                                                      const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)          {const vec4<T> &v=sel_ltz(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sel_lez(const color_yiqa<T> &t_,
                                                      const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)          {const vec4<T> &v=sel_lez(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE void operator+=(color_yiqa<T> &cr_, const color_yiqa<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)+=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_yiqa<T> &cr_, const color_yiq<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_yiqa<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)+=s_;}
template<typename T> PFC_INLINE void operator-=(color_yiqa<T> &cr_, const color_yiqa<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)-=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_yiqa<T> &cr_, const color_yiq<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_yiqa<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)-=s_;}
template<typename T> PFC_INLINE void operator*=(color_yiqa<T> &cr_, const color_yiqa<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)*=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_yiqa<T> &cr_, const color_yiq<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_yiqa<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)*=s_;}
template<typename T> PFC_INLINE void operator*=(color_yiqa<T> &cr_, const mat44<T> &m_)                            {reinterpret_cast<vec4<T>&>(cr_)*=m_;}
template<typename T> PFC_INLINE void operator/=(color_yiqa<T> &cr_, const color_yiqa<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)/=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_yiqa<T> &cr_, const color_yiq<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_yiqa<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)/=s_;}
template<typename T> PFC_INLINE color_yiqa<T> operator+(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)+reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator+(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)+s_; return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator+(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)    {const vec4<T> &v=s_+reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator-(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)-reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator-(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)-s_; return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator-(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)    {const vec4<T> &v=s_-reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator-(const color_yiqa<T> &c_)                                   {const vec4<T> &v=-reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator*(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)*reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator*(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)*s_; return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator*(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)    {const vec4<T> &v=s_*reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator*(const color_yiqa<T> &c_, const mat44<T> &m_)               {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)*m_; return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator*(const mat44<T> &m_, const color_yiqa<T> &c_)               {const vec4<T> &v=m_*reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator/(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)/reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator/(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)/s_; return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> operator/(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)    {const vec4<T> &v=s_/reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const color_yiqa<T> &c_)                            {return min(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_yiqa<T> min(const color_yiqa<T> &c0_,
                                                  const color_yiqa<T> &c1_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> min(const color_yiqa<T> &c0_,
                                                  const color_yiqa<T> &c1_,
                                                  const color_yiqa<T> &c2_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> min(const color_yiqa<T> &c0_,
                                                  const color_yiqa<T> &c1_,
                                                  const color_yiqa<T> &c2_,
                                                  const color_yiqa<T> &c3_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_), reinterpret_cast<const vec4<T>&>(c3_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> min(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)          {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c_), s_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> min(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)          {const vec4<T> &v=min(s_, reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const color_yiqa<T> &c_)                            {return max(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_yiqa<T> max(const color_yiqa<T> &c0_,
                                                  const color_yiqa<T> &c1_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> max(const color_yiqa<T> &c0_,
                                                  const color_yiqa<T> &c1_,
                                                  const color_yiqa<T> &c2_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> max(const color_yiqa<T> &c0_,
                                                  const color_yiqa<T> &c1_,
                                                  const color_yiqa<T> &c2_,
                                                  const color_yiqa<T> &c3_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_), reinterpret_cast<const vec4<T>&>(c3_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> max(const color_yiqa<T> &c_, typename math<T>::scalar_t s_)          {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c_), s_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> max(typename math<T>::scalar_t s_, const color_yiqa<T> &c_)          {const vec4<T> &v=max(s_, reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> mul(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_)              {const vec4<T> &v=mul(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> madd(const color_yiqa<T> &c0_,
                                                   const color_yiqa<T> &c1_,
                                                   const color_yiqa<T> &c2_)                                       {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> madd(const color_yiqa<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   typename math<T>::scalar_t add_)                                {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), mul_, add_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> madd(const color_yiqa<T> &c_,
                                                   const color_yiqa<T> &mul_,
                                                   typename math<T>::scalar_t add_)                                {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(mul_), add_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> madd(const color_yiqa<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   const color_yiqa<T> &add_)                                      {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), mul_, reinterpret_cast<const vec4<T>&>(add_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> rcp(const color_yiqa<T> &c_)                                         {const vec4<T> &v=rcp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> rcp_z(const color_yiqa<T> &c_)                                       {const vec4<T> &v=rcp_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> floor(const color_yiqa<T> &c_)                                       {const vec4<T> &v=floor(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> ceil(const color_yiqa<T> &c_)                                        {const vec4<T> &v=ceil(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> trunc(const color_yiqa<T> &c_)                                       {const vec4<T> &v=trunc(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> frc(const color_yiqa<T> &c_)                                         {const vec4<T> &v=frc(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> mod(const color_yiqa<T> &c_, T div_)                                 {const vec4<T> &v=mod(reinterpret_cast<const vec4<T>&>(c_), div_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> cycle(const color_yiqa<T> &c_, T cycle_)                             {const vec4<T> &v=cycle(reinterpret_cast<const vec4<T>&>(c_), cycle_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> cycle1(const color_yiqa<T> &c_)                                      {const vec4<T> &v=cycle1(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sat(const color_yiqa<T> &c_)                                         {const vec4<T> &v=sat(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> ssat(const color_yiqa<T> &c_)                                        {const vec4<T> &v=ssat(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> clamp(const color_yiqa<T> &c_,
                                                    const color_yiqa<T> &min_,
                                                    const color_yiqa<T> &max_)                                     {const vec4<T> &v=clamp(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(min_), reinterpret_cast<const vec4<T>&>(max_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> clamp(const color_yiqa<T> &c_,
                                                    typename math<T>::scalar_t min_,
                                                    typename math<T>::scalar_t max_)                               {const vec4<T> &v=clamp(reinterpret_cast<const vec4<T>&>(c_), min_, max_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> abs(const color_yiqa<T> &c_)                                         {const vec4<T> &v=abs(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sgn(const color_yiqa<T> &c_)                                         {const vec4<T> &v=sgn(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sgn_zp(const color_yiqa<T> &c_)                                      {const vec4<T> &v=sgn_zp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sqr(const color_yiqa<T> &c_)                                         {const vec4<T> &v=sqr(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> cubic(const color_yiqa<T> &c_)                                       {const vec4<T> &v=cubic(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sqrt(const color_yiqa<T> &c_)                                        {const vec4<T> &v=sqrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> sqrt_z(const color_yiqa<T> &c_)                                      {const vec4<T> &v=sqrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> cbrt(const color_yiqa<T> &c_)                                        {const vec4<T> &v=cbrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> rsqrt(const color_yiqa<T> &c_)                                       {const vec4<T> &v=rsqrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> rsqrt_z(const color_yiqa<T> &c_)                                     {const vec4<T> &v=rsqrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> rcbrt(const color_yiqa<T> &c_)                                       {const vec4<T> &v=rcbrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> rcbrt_z(const color_yiqa<T> &c_)                                     {const vec4<T> &v=rcbrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const color_yiqa<T> &c_)                           {return norm(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const color_yiqa<T> &c_)                          {return rnorm(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const color_yiqa<T> &c_)                        {return rnorm_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const color_yiqa<T> &c_)                          {return norm2(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const color_yiqa<T> &c_)                         {return rnorm2(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const color_yiqa<T> &c_)                       {return rnorm2_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const color_yiqa<T> &c_)                        {return norm_l1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const color_yiqa<T> &c_)                       {return rnorm_l1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const color_yiqa<T> &c_)                     {return rnorm_l1_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_yiqa<T> exp(const color_yiqa<T> &c_)                                         {const vec4<T> &v=exp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> exp2(const color_yiqa<T> &c_)                                        {const vec4<T> &v=exp2(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> ln(const color_yiqa<T> &c_)                                          {const vec4<T> &v=ln(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> log2(const color_yiqa<T> &c_)                                        {const vec4<T> &v=log2(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> log10(const color_yiqa<T> &c_)                                       {const vec4<T> &v=log10(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> pow(const color_yiqa<T> &c_, typename math<T>::scalar_t p_)          {const vec4<T> &v=pow(reinterpret_cast<const vec4<T>&>(c_), p_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> unit(const color_yiqa<T> &c_)                                        {const vec4<T> &v=unit(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> unit_z(const color_yiqa<T> &c_)                                      {const vec4<T> &v=unit_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_) {return dot(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const color_yiqa<T> &c_)                           {return dot1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void neg(color_yiqa<T> &c_)                                                        {neg(reinterpret_cast<vec4<T>&>(c_));}
template<typename T, class Rand> PFC_INLINE void rand_u(color_yiqa<T> &c_, Rand &rnd_)                             {rand_u(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_real1(color_yiqa<T> &c_, Rand &rnd_)                         {rand_real1(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_ureal1(color_yiqa<T> &c_, Rand &rnd_)                        {rand_ureal1(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T> PFC_INLINE color_yiqa<T> smoothstep(const color_yiqa<T> &c_)                                  {const vec4<T> &v=smoothstep(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> smootherstep(const color_yiqa<T> &c_)                                {const vec4<T> &v=smootherstep(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> lerp(const color_yiqa<T> &c0_, const color_yiqa<T> &c1_, float t_)   {const vec4<T> &v=lerp(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), t_); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> reflect(const color_yiqa<T> &c_, const color_yiqa<T> &cn_)           {const vec4<T> &v=reflect(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(cn_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE color_yiqa<T> reflect_u(const color_yiqa<T> &c_, const color_yiqa<T> &cn_)         {const vec4<T> &v=reflect_u(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(cn_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<unsigned shuffle_, typename T> PFC_INLINE color_yiqa<T> shuffle(const color_yiqa<T> &c_)                  {const vec4<T> &v=shuffle<shuffle_>(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_yiqa<T>&>(v);}
template<typename T> PFC_INLINE void pack_u1(color_yiqa32 &cr_, const color_yiqa<T> &c_)                           {pack_u1(reinterpret_cast<vec4_32u&>(cr_), reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void pack_s1(color_yiqa32 &cr_, const color_yiqa<T> &c_)                           {pack_s1(reinterpret_cast<vec4_32s&>(cr_), reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void unpack_u1(color_yiqa<T> &cr_, const color_yiqa32 &c_)                         {unpack_u1(reinterpret_cast<vec4<T>&>(cr_), reinterpret_cast<const vec4_32u&>(c_));}
template<typename T> PFC_INLINE void unpack_s1(color_yiqa<T> &cr_, const color_yiqa32 &c_)                         {unpack_s1(reinterpret_cast<vec4<T>&>(cr_), reinterpret_cast<const vec4_32s&>(c_));}
//----------------------------------------------------------------------------


//============================================================================
// color_hsv
//============================================================================
template<typename T>
color_hsv<T>::color_hsv()
{
}
//----

template<typename T>
color_hsv<T>::color_hsv(T h_, T s_, T v_)
  :h(h_)
  ,s(s_)
  ,v(v_)
{
}
//----

template<typename T>
color_hsv<T>::color_hsv(const color_hsva<T> &c_)
  :h(c_.h)
  ,s(c_.s)
  ,v(c_.v)
{
}
//----

template<typename T>
template<typename U>
color_hsv<T>::color_hsv(const color_hsv<U> &c_)
  :h(T(c_.h))
  ,s(T(c_.s))
  ,v(T(c_.v))
{
}
//----

template<typename T>
template<typename U>
color_hsv<T>::color_hsv(const color_hsva<U> &c_)
  :h(T(c_.h))
  ,s(T(c_.s))
  ,v(T(c_.v))
{
}
//----------------------------------------------------------------------------

template<typename T>
const T &color_hsv<T>::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &color_hsv<T>::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void color_hsv<T>::set(T h_, T s_, T v_)
{
  h=h_;
  s=s_;
  v=v_;
}
//----

template<typename T>
template<typename U>
void color_hsv<T>::set(const color_hsv<U> &c_)
{
  h=T(c_.h);
  s=T(c_.s);
  v=T(c_.v);
}
//----------------------------------------------------------------------------

// vec3 interface for color_hsv
template<typename T> PFC_INLINE bool is_zero(const color_hsv<T> &c_)                                             {return is_zero(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_sat(const color_hsv<T> &c_)                                              {return is_sat(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool is_ssat(const color_hsv<T> &c_)                                             {return is_ssat(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE bool operator==(const color_hsv<T> &c0_, const color_hsv<T> &c1_)                {return reinterpret_cast<const vec3<T>&>(c0_)==reinterpret_cast<const vec3<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator==(const color_hsv<T> &c_, typename math<T>::scalar_t s_)           {return reinterpret_cast<const vec3<T>&>(c_)==s_;}
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const color_hsv<T> &c_)           {return s_==reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE bool operator!=(const color_hsv<T> &c0_, const color_hsv<T> &c1_)                {return reinterpret_cast<const vec3<T>&>(c0_)!=reinterpret_cast<const vec3<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator!=(const color_hsv<T> &c_, typename math<T>::scalar_t s_)           {return reinterpret_cast<const vec3<T>&>(c_)!=s_;}
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const color_hsv<T> &c_)           {return s_!=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE color_hsv<T> operator<(const color_hsv<T> &c0_, const color_hsv<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)<reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator<(const color_hsv<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)<s_; return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator<(typename math<T>::scalar_t s_, const color_hsv<T> &c_)    {const vec3<T> &v=s_<reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator>(const color_hsv<T> &c0_, const color_hsv<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)>reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator>(const color_hsv<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)>s_; return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator>(typename math<T>::scalar_t s_, const color_hsv<T> &c_)    {const vec3<T> &v=s_>reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator<=(const color_hsv<T> &c0_, const color_hsv<T> &c1_)        {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)<=reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator<=(const color_hsv<T> &c_, typename math<T>::scalar_t s_)   {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)<=s_; return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator<=(typename math<T>::scalar_t s_, const color_hsv<T> &c_)   {const vec3<T> &v=s_<=reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator>=(const color_hsv<T> &c0_, const color_hsv<T> &c1_)        {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)>=reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator>=(const color_hsv<T> &c_, typename math<T>::scalar_t s_)   {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)>=s_; return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator>=(typename math<T>::scalar_t s_, const color_hsv<T> &c_)   {const vec3<T> &v=s_>=reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> sel_eq(const color_hsv<T> &t0_, const color_hsv<T> &t1_,
                                                     const color_hsv<T> &c0_, const color_hsv<T> &c1_)           {const vec3<T> &v=sel_eq(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> sel_lt(const color_hsv<T> &t0_, const color_hsv<T> &t1_,
                                                     const color_hsv<T> &c0_, const color_hsv<T> &c1_)           {const vec3<T> &v=sel_lt(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> sel_le(const color_hsv<T> &t0_, const color_hsv<T> &t1_,
                                                     const color_hsv<T> &c0_, const color_hsv<T> &c1_)           {const vec3<T> &v=sel_le(reinterpret_cast<const vec3<T>&>(t0_), reinterpret_cast<const vec3<T>&>(t1_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> sel_eqz(const color_hsv<T> &t_,
                                                      const color_hsv<T> &c0_, const color_hsv<T> &c1_)          {const vec3<T> &v=sel_eqz(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> sel_ltz(const color_hsv<T> &t_,
                                                      const color_hsv<T> &c0_, const color_hsv<T> &c1_)          {const vec3<T> &v=sel_ltz(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> sel_lez(const color_hsv<T> &t_,
                                                      const color_hsv<T> &c0_, const color_hsv<T> &c1_)          {const vec3<T> &v=sel_lez(reinterpret_cast<const vec3<T>&>(t_), reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE void operator+=(color_hsv<T> &cr_, const color_hsv<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_hsv<T> &cr_, const color_hsva<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_hsv<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)+=s_;}
template<typename T> PFC_INLINE void operator-=(color_hsv<T> &cr_, const color_hsv<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_hsv<T> &cr_, const color_hsva<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_hsv<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)-=s_;}
template<typename T> PFC_INLINE void operator*=(color_hsv<T> &cr_, const color_hsv<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_hsv<T> &cr_, const color_hsva<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_hsv<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)*=s_;}
template<typename T> PFC_INLINE void operator*=(color_hsv<T> &cr_, const mat44<T> &m_)                           {reinterpret_cast<vec3<T>&>(cr_)*=m_;}
template<typename T> PFC_INLINE void operator/=(color_hsv<T> &cr_, const color_hsv<T> &c_)                       {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_hsv<T> &cr_, const color_hsva<T> &c_)                      {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_hsv<T> &cr_, typename math<T>::scalar_t s_)                {reinterpret_cast<vec3<T>&>(cr_)/=s_;}
template<typename T> PFC_INLINE color_hsv<T> operator+(const color_hsv<T> &c0_, const color_hsv<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)+reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator+(const color_hsv<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)+s_; return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator+(typename math<T>::scalar_t s_, const color_hsv<T> &c_)    {const vec3<T> &v=s_+reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator-(const color_hsv<T> &c0_, const color_hsv<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)-reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator-(const color_hsv<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)-s_; return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator-(typename math<T>::scalar_t s_, const color_hsv<T> &c_)    {const vec3<T> &v=s_-reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator-(const color_hsv<T> &c_)                                   {const vec3<T> &v=-reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator*(const color_hsv<T> &c0_, const color_hsv<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)*reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator*(const color_hsv<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*s_; return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator*(typename math<T>::scalar_t s_, const color_hsv<T> &c_)    {const vec3<T> &v=s_*reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator*(const color_hsv<T> &c_, const mat44<T> &m_)               {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)*m_; return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator*(const mat44<T> &m_, const color_hsv<T> &c_)               {const vec3<T> &v=m_*reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator/(const color_hsv<T> &c0_, const color_hsv<T> &c1_)         {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c0_)/reinterpret_cast<const vec3<T>&>(c1_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator/(const color_hsv<T> &c_, typename math<T>::scalar_t s_)    {const vec3<T> &v=reinterpret_cast<const vec3<T>&>(c_)/s_; return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> operator/(typename math<T>::scalar_t s_, const color_hsv<T> &c_)    {const vec3<T> &v=s_/reinterpret_cast<const vec3<T>&>(c_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const color_hsv<T> &c_)                           {return min(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_hsv<T> min(const color_hsv<T> &c0_,
                                                  const color_hsv<T> &c1_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> min(const color_hsv<T> &c0_,
                                                  const color_hsv<T> &c1_,
                                                  const color_hsv<T> &c2_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> min(const color_hsv<T> &c0_,
                                                  const color_hsv<T> &c1_,
                                                  const color_hsv<T> &c2_,
                                                  const color_hsv<T> &c3_)                                       {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_), reinterpret_cast<const vec3<T>&>(c3_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> min(const color_hsv<T> &c_, typename math<T>::scalar_t s_)          {const vec3<T> &v=min(reinterpret_cast<const vec3<T>&>(c_), s_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> min(typename math<T>::scalar_t s_, const color_hsv<T> &c_)          {const vec3<T> &v=min(s_, reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const color_hsv<T> &c_)                           {return max(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_hsv<T> max(const color_hsv<T> &c0_,
                                                  const color_hsv<T> &c1_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> max(const color_hsv<T> &c0_,
                                                  const color_hsv<T> &c1_,
                                                  const color_hsv<T> &c2_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> max(const color_hsv<T> &c0_,
                                                  const color_hsv<T> &c1_,
                                                  const color_hsv<T> &c2_,
                                                  const color_hsv<T> &c3_)                                       {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_), reinterpret_cast<const vec3<T>&>(c3_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> max(const color_hsv<T> &c_, typename math<T>::scalar_t s_)          {const vec3<T> &v=max(reinterpret_cast<const vec3<T>&>(c_), s_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> max(typename math<T>::scalar_t s_, const color_hsv<T> &c_)          {const vec3<T> &v=max(s_, reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> mul(const color_hsv<T> &c0_, const color_hsv<T> &c1_)               {const vec3<T> &v=mul(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> madd(const color_hsv<T> &c0_,
                                                   const color_hsv<T> &c1_,
                                                   const color_hsv<T> &c2_)                                      {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), reinterpret_cast<const vec3<T>&>(c2_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> madd(const color_hsv<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   typename math<T>::scalar_t add_)                              {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), mul_, add_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> madd(const color_hsv<T> &c_,
                                                   const color_hsv<T> &mul_,
                                                   typename math<T>::scalar_t add_)                              {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(mul_), add_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> madd(const color_hsv<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   const color_hsv<T> &add_)                                     {const vec3<T> &v=madd(reinterpret_cast<const vec3<T>&>(c_), mul_, reinterpret_cast<const vec3<T>&>(add_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> rcp(const color_hsv<T> &c_)                                         {const vec3<T> &v=rcp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> rcp_z(const color_hsv<T> &c_)                                       {const vec3<T> &v=rcp_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> floor(const color_hsv<T> &c_)                                       {const vec3<T> &v=floor(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> ceil(const color_hsv<T> &c_)                                        {const vec3<T> &v=ceil(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> trunc(const color_hsv<T> &c_)                                       {const vec3<T> &v=trunc(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> frc(const color_hsv<T> &c_)                                         {const vec3<T> &v=frc(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> mod(const color_hsv<T> &c_, T div_)                                 {const vec3<T> &v=mod(reinterpret_cast<const vec3<T>&>(c_), div_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> cycle(const color_hsv<T> &c_, T cycle_)                             {const vec3<T> &v=cycle(reinterpret_cast<const vec3<T>&>(c_), cycle_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> cycle1(const color_hsv<T> &c_)                                      {const vec3<T> &v=cycle1(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> sat(const color_hsv<T> &c_)                                         {const vec3<T> &v=sat(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> ssat(const color_hsv<T> &c_)                                        {const vec3<T> &v=ssat(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> clamp(const color_hsv<T> &c_,
                                                    const color_hsv<T> &min_,
                                                    const color_hsv<T> &max_)                                    {const vec3<T> &v=clamp(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(min_), reinterpret_cast<const vec3<T>&>(max_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> clamp(const color_hsv<T> &c_,
                                                    typename math<T>::scalar_t min_,
                                                    typename math<T>::scalar_t max_)                             {const vec3<T> &v=clamp(reinterpret_cast<const vec3<T>&>(c_), min_, max_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> abs(const color_hsv<T> &c_)                                         {const vec3<T> &v=abs(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> sqr(const color_hsv<T> &c_)                                         {const vec3<T> &v=sqr(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> cubic(const color_hsv<T> &c_)                                       {const vec3<T> &v=cubic(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> sqrt(const color_hsv<T> &c_)                                        {const vec3<T> &v=sqrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> sqrt_z(const color_hsv<T> &c_)                                      {const vec3<T> &v=sqrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> cbrt(const color_hsv<T> &c_)                                        {const vec3<T> &v=cbrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> rsqrt(const color_hsv<T> &c_)                                       {const vec3<T> &v=rsqrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> rsqrt_z(const color_hsv<T> &c_)                                     {const vec3<T> &v=rsqrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> rcbrt(const color_rgba<T> &c_)                                      {const vec3<T> &v=rcbrt(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> rcbrt_z(const color_rgba<T> &c_)                                    {const vec3<T> &v=rcbrt_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const color_hsv<T> &c_)                          {return norm(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const color_hsv<T> &c_)                         {return rnorm(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const color_hsv<T> &c_)                       {return rnorm_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const color_hsv<T> &c_)                         {return norm2(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const color_hsv<T> &c_)                        {return rnorm2(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const color_hsv<T> &c_)                      {return rnorm2_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const color_hsv<T> &c_)                       {return norm_l1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const color_hsv<T> &c_)                      {return rnorm_l1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const color_hsv<T> &c_)                    {return rnorm_l1_z(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE color_hsv<T> exp(const color_hsv<T> &c_)                                         {const vec3<T> &v=exp(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> exp2(const color_hsv<T> &c_)                                        {const vec3<T> &v=exp2(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> ln(const color_hsv<T> &c_)                                          {const vec3<T> &v=ln(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> log2(const color_hsv<T> &c_)                                        {const vec3<T> &v=log2(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> log10(const color_hsv<T> &c_)                                       {const vec3<T> &v=log10(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> pow(const color_hsv<T> &c_, typename math<T>::scalar_t p_)          {const vec3<T> &v=pow(reinterpret_cast<const vec3<T>&>(c_), p_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> unit(const color_hsv<T> &c_)                                        {const vec3<T> &v=unit(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> unit_z(const color_hsv<T> &c_)                                      {const vec3<T> &v=unit_z(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> cross(const color_hsv<T> &c0_, const color_hsv<T> &c1_)             {const vec3<T> &v=cross(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const color_hsv<T> &c0_, const color_hsv<T> &c1_) {return dot(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const color_hsv<T> &c_)                          {return dot1(reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void neg(color_hsv<T> &c_)                                                       {neg(reinterpret_cast<vec3<T>&>(c_));}
template<typename T, class Rand> PFC_INLINE void rand_u(color_hsv<T> &c_, Rand &rnd_)                            {rand_u(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_real1(color_hsv<T> &c_, Rand &rnd_)                        {rand_real1(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_ureal1(color_hsv<T> &c_, Rand &rnd_)                       {rand_ureal1(reinterpret_cast<vec3<T>&>(c_), rnd_);}
template<typename T> PFC_INLINE color_hsv<T> smoothstep(const color_hsv<T> &c_)                                  {const vec3<T> &v=smoothstep(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> smootherstep(const color_hsv<T> &c_)                                {const vec3<T> &v=smootherstep(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> lerp(const color_hsv<T> &c0_, const color_hsv<T> &c1_, float t_)    {const vec3<T> &v=lerp(reinterpret_cast<const vec3<T>&>(c0_), reinterpret_cast<const vec3<T>&>(c1_), t_); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> reflect(const color_hsv<T> &c_, const color_hsv<T> &cn_)            {const vec3<T> &v=reflect(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(cn_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE color_hsv<T> reflect_u(const color_hsv<T> &c_, const color_hsv<T> &cn_)          {const vec3<T> &v=reflect_u(reinterpret_cast<const vec3<T>&>(c_), reinterpret_cast<const vec3<T>&>(cn_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<unsigned shuffle_, typename T> PFC_INLINE color_hsv<T> shuffle(const color_hsv<T> &c_)                  {const vec3<T> &v=shuffle<shuffle_>(reinterpret_cast<const vec3<T>&>(c_)); return reinterpret_cast<const color_hsv<T>&>(v);}
template<typename T> PFC_INLINE void pack_u1(color_hsv32 &cr_, const color_hsv<T> &c_)                           {pack_u1(reinterpret_cast<vec3_32u&>(cr_), reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void pack_s1(color_hsv32 &cr_, const color_hsv<T> &c_)                           {pack_s1(reinterpret_cast<vec3_32s&>(cr_), reinterpret_cast<const vec3<T>&>(c_));}
template<typename T> PFC_INLINE void unpack_u1(color_hsv<T> &cr_, const color_hsv32 &c_)                         {unpack_u1(reinterpret_cast<vec3<T>&>(cr_), reinterpret_cast<const vec3_32u&>(c_));}
template<typename T> PFC_INLINE void unpack_s1(color_hsv<T> &cr_, const color_hsv32 &c_)                         {unpack_s1(reinterpret_cast<vec3<T>&>(cr_), reinterpret_cast<const vec3_32s&>(c_));}
//----------------------------------------------------------------------------


//============================================================================
// color_hsva
//============================================================================
template<typename T>
color_hsva<T>::color_hsva()
{
}
//----

template<typename T>
color_hsva<T>::color_hsva(T h_, T s_, T v_)
  :h(h_)
  ,s(s_)
  ,v(v_)
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
color_hsva<T>::color_hsva(T h_, T s_, T v_, T a_)
  :h(h_)
  ,s(s_)
  ,v(v_)
  ,a(a_)
{
}
//----

template<typename T>
color_hsva<T>::color_hsva(const color_hsv<T> &c_)
  :h(c_.h)
  ,s(c_.s)
  ,v(c_.v)
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
color_hsva<T>::color_hsva(const color_hsv<T> &c_, T a_)
  :h(c_.h)
  ,s(c_.s)
  ,v(c_.v)
  ,a(a_)
{
}
//----

template<typename T>
template<typename U>
color_hsva<T>::color_hsva(const color_hsva<U> &c_)
  :h(T(c_.h))
  ,s(T(c_.s))
  ,v(T(c_.v))
  ,a(T(c_.a))
{
}
//----

template<typename T>
template<typename U>
color_hsva<T>::color_hsva(const color_hsv<U> &c_)
  :h(T(c_.h))
  ,s(T(c_.s))
  ,v(T(c_.v))
  ,a(numeric_type<T>::float_one())
{
}
//----

template<typename T>
template<typename U>
color_hsva<T>::color_hsva(const color_hsv<U> &c_, U a_)
  :h(T(c_.h))
  ,s(T(c_.s))
  ,v(T(c_.v))
  ,a(T(a_))
{
}
//----------------------------------------------------------------------------

template<typename T>
const T &color_hsva<T>::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const T*>(this)[idx_];
}
//----

template<typename T>
T &color_hsva<T>::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<T*>(this)[idx_];
}
//----

template<typename T>
void color_hsva<T>::set(T h_, T s_, T v_)
{
  h=h_;
  s=s_;
  v=v_;
}
//----

template<typename T>
void color_hsva<T>::set(T h_, T s_, T v_, T a_)
{
  h=h_;
  s=s_;
  v=v_;
  a=a_;
}
//----

template<typename T>
void color_hsva<T>::set(const color_hsv<T> &c_, T a_)
{
  h=c_.h;
  s=c_.s;
  v=c_.v;
  a=a_;
}
//----

template<typename T>
template<typename U>
void color_hsva<T>::set(const color_hsva<U> &c_)
{
  h=T(c_.h);
  s=T(c_.s);
  v=T(c_.v);
  a=T(c_.a);
}
//----------------------------------------------------------------------------

// vec4 interface for color_hsva
template<typename T> PFC_INLINE bool is_zero(const color_hsva<T> &c_)                                              {return is_zero(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool is_sat(const color_hsva<T> &c_)                                               {return is_sat(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool is_ssat(const color_hsva<T> &c_)                                              {return is_ssat(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE bool operator==(const color_hsva<T> &c0_, const color_hsva<T> &c1_)                {return reinterpret_cast<const vec4<T>&>(c0_)==reinterpret_cast<const vec4<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator==(const color_hsva<T> &c_, typename math<T>::scalar_t s_)            {return reinterpret_cast<const vec4<T>&>(c_)==s_;}
template<typename T> PFC_INLINE bool operator==(typename math<T>::scalar_t s_, const color_hsva<T> &c_)            {return s_==reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE bool operator!=(const color_hsva<T> &c0_, const color_hsva<T> &c1_)                {return reinterpret_cast<const vec4<T>&>(c0_)!=reinterpret_cast<const vec4<T>&>(c1_);}
template<typename T> PFC_INLINE bool operator!=(const color_hsva<T> &c_, typename math<T>::scalar_t s_)            {return reinterpret_cast<const vec4<T>&>(c_)!=s_;}
template<typename T> PFC_INLINE bool operator!=(typename math<T>::scalar_t s_, const color_hsva<T> &c_)            {return s_!=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE color_hsva<T> operator<(const color_hsva<T> &c0_, const color_hsva<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)<reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator<(const color_hsva<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)<s_; return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator<(typename math<T>::scalar_t s_, const color_hsva<T> &c_)    {const vec4<T> &v=s_<reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator>(const color_hsva<T> &c0_, const color_hsva<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)>reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator>(const color_hsva<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)>s_; return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator>(typename math<T>::scalar_t s_, const color_hsva<T> &c_)    {const vec4<T> &v=s_>reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator<=(const color_hsva<T> &c0_, const color_hsva<T> &c1_)       {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)<=reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator<=(const color_hsva<T> &c_, typename math<T>::scalar_t s_)   {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)<=s_; return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator<=(typename math<T>::scalar_t s_, const color_hsva<T> &c_)   {const vec4<T> &v=s_<=reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator>=(const color_hsva<T> &c0_, const color_hsva<T> &c1_)       {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)>=reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator>=(const color_hsva<T> &c_, typename math<T>::scalar_t s_)   {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)>=s_; return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator>=(typename math<T>::scalar_t s_, const color_hsva<T> &c_)   {const vec4<T> &v=s_>=reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> sel_eq(const color_hsva<T> &t0_, const color_hsva<T> &t1_,
                                                     const color_hsva<T> &c0_, const color_hsva<T> &c1_)           {const vec4<T> &v=sel_eq(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> sel_lt(const color_hsva<T> &t0_, const color_hsva<T> &t1_,
                                                     const color_hsva<T> &c0_, const color_hsva<T> &c1_)           {const vec4<T> &v=sel_lt(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> sel_le(const color_hsva<T> &t0_, const color_hsva<T> &t1_,
                                                     const color_hsva<T> &c0_, const color_hsva<T> &c1_)           {const vec4<T> &v=sel_le(reinterpret_cast<const vec4<T>&>(t0_), reinterpret_cast<const vec4<T>&>(t1_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> sel_eqz(const color_hsva<T> &t_,
                                                      const color_hsva<T> &c0_, const color_hsva<T> &c1_)          {const vec4<T> &v=sel_eqz(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> sel_ltz(const color_hsva<T> &t_,
                                                      const color_hsva<T> &c0_, const color_hsva<T> &c1_)          {const vec4<T> &v=sel_ltz(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> sel_lez(const color_hsva<T> &t_,
                                                      const color_hsva<T> &c0_, const color_hsva<T> &c1_)          {const vec4<T> &v=sel_lez(reinterpret_cast<const vec4<T>&>(t_), reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE void operator+=(color_hsva<T> &cr_, const color_hsva<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)+=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_hsva<T> &cr_, const color_hsv<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)+=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator+=(color_hsva<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)+=s_;}
template<typename T> PFC_INLINE void operator-=(color_hsva<T> &cr_, const color_hsva<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)-=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_hsva<T> &cr_, const color_hsv<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)-=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator-=(color_hsva<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)-=s_;}
template<typename T> PFC_INLINE void operator*=(color_hsva<T> &cr_, const color_hsva<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)*=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_hsva<T> &cr_, const color_hsv<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)*=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator*=(color_hsva<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)*=s_;}
template<typename T> PFC_INLINE void operator*=(color_hsva<T> &cr_, const mat44<T> &m_)                            {reinterpret_cast<vec4<T>&>(cr_)*=m_;}
template<typename T> PFC_INLINE void operator/=(color_hsva<T> &cr_, const color_hsva<T> &c_)                       {reinterpret_cast<vec4<T>&>(cr_)/=reinterpret_cast<const vec4<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_hsva<T> &cr_, const color_hsv<T> &c_)                        {reinterpret_cast<vec3<T>&>(cr_)/=reinterpret_cast<const vec3<T>&>(c_);}
template<typename T> PFC_INLINE void operator/=(color_hsva<T> &cr_, typename math<T>::scalar_t s_)                 {reinterpret_cast<vec4<T>&>(cr_)/=s_;}
template<typename T> PFC_INLINE color_hsva<T> operator+(const color_hsva<T> &c0_, const color_hsva<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)+reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator+(const color_hsva<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)+s_; return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator+(typename math<T>::scalar_t s_, const color_hsva<T> &c_)    {const vec4<T> &v=s_+reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator-(const color_hsva<T> &c0_, const color_hsva<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)-reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator-(const color_hsva<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)-s_; return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator-(typename math<T>::scalar_t s_, const color_hsva<T> &c_)    {const vec4<T> &v=s_-reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator-(const color_hsva<T> &c_)                                   {const vec4<T> &v=-reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator*(const color_hsva<T> &c0_, const color_hsva<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)*reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator*(const color_hsva<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)*s_; return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator*(typename math<T>::scalar_t s_, const color_hsva<T> &c_)    {const vec4<T> &v=s_*reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator*(const color_hsva<T> &c_, const mat44<T> &m_)               {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)*m_; return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator*(const mat44<T> &m_, const color_hsva<T> &c_)               {const vec4<T> &v=m_*reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator/(const color_hsva<T> &c0_, const color_hsva<T> &c1_)        {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c0_)/reinterpret_cast<const vec4<T>&>(c1_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator/(const color_hsva<T> &c_, typename math<T>::scalar_t s_)    {const vec4<T> &v=reinterpret_cast<const vec4<T>&>(c_)/s_; return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> operator/(typename math<T>::scalar_t s_, const color_hsva<T> &c_)    {const vec4<T> &v=s_/reinterpret_cast<const vec4<T>&>(c_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t min(const color_hsva<T> &c_)                            {return min(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_hsva<T> min(const color_hsva<T> &c0_,
                                                  const color_hsva<T> &c1_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> min(const color_hsva<T> &c0_,
                                                  const color_hsva<T> &c1_,
                                                  const color_hsva<T> &c2_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> min(const color_hsva<T> &c0_,
                                                  const color_hsva<T> &c1_,
                                                  const color_hsva<T> &c2_,
                                                  const color_hsva<T> &c3_)                                        {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_), reinterpret_cast<const vec4<T>&>(c3_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> min(const color_hsva<T> &c_, typename math<T>::scalar_t s_)          {const vec4<T> &v=min(reinterpret_cast<const vec4<T>&>(c_), s_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> min(typename math<T>::scalar_t s_, const color_hsva<T> &c_)          {const vec4<T> &v=min(s_, reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t max(const color_hsva<T> &c_)                            {return max(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_hsva<T> max(const color_hsva<T> &c0_,
                                                  const color_hsva<T> &c1_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> max(const color_hsva<T> &c0_,
                                                  const color_hsva<T> &c1_,
                                                  const color_hsva<T> &c2_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> max(const color_hsva<T> &c0_,
                                                  const color_hsva<T> &c1_,
                                                  const color_hsva<T> &c2_,
                                                  const color_hsva<T> &c3_)                                        {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_), reinterpret_cast<const vec4<T>&>(c3_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> max(const color_hsva<T> &c_, typename math<T>::scalar_t s_)          {const vec4<T> &v=max(reinterpret_cast<const vec4<T>&>(c_), s_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> max(typename math<T>::scalar_t s_, const color_hsva<T> &c_)          {const vec4<T> &v=max(s_, reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> mul(const color_hsva<T> &c0_, const color_hsva<T> &c1_)              {const vec4<T> &v=mul(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> madd(const color_hsva<T> &c0_,
                                                   const color_hsva<T> &c1_,
                                                   const color_hsva<T> &c2_)                                       {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), reinterpret_cast<const vec4<T>&>(c2_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> madd(const color_hsva<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   typename math<T>::scalar_t add_)                                {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), mul_, add_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> madd(const color_hsva<T> &c_,
                                                   const color_hsva<T> &mul_,
                                                   typename math<T>::scalar_t add_)                                {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(mul_), add_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> madd(const color_hsva<T> &c_,
                                                   typename math<T>::scalar_t mul_,
                                                   const color_hsva<T> &add_)                                      {const vec4<T> &v=madd(reinterpret_cast<const vec4<T>&>(c_), mul_, reinterpret_cast<const vec4<T>&>(add_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> rcp(const color_hsva<T> &c_)                                         {const vec4<T> &v=rcp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> rcp_z(const color_hsva<T> &c_)                                       {const vec4<T> &v=rcp_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> floor(const color_hsva<T> &c_)                                       {const vec4<T> &v=floor(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> ceil(const color_hsva<T> &c_)                                        {const vec4<T> &v=ceil(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> trunc(const color_hsva<T> &c_)                                       {const vec4<T> &v=trunc(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> frc(const color_hsva<T> &c_)                                         {const vec4<T> &v=frc(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> mod(const color_hsva<T> &c_, T div_)                                 {const vec4<T> &v=mod(reinterpret_cast<const vec4<T>&>(c_), div_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> cycle(const color_hsva<T> &c_, T cycle_)                             {const vec4<T> &v=cycle(reinterpret_cast<const vec4<T>&>(c_), cycle_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> cycle1(const color_hsva<T> &c_)                                      {const vec4<T> &v=cycle1(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> sat(const color_hsva<T> &c_)                                         {const vec4<T> &v=sat(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> ssat(const color_hsva<T> &c_)                                        {const vec4<T> &v=ssat(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> clamp(const color_hsva<T> &c_,
                                                    const color_hsva<T> &min_,
                                                    const color_hsva<T> &max_)                                     {const vec4<T> &v=clamp(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(min_), reinterpret_cast<const vec4<T>&>(max_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> clamp(const color_hsva<T> &c_,
                                                    typename math<T>::scalar_t min_,
                                                    typename math<T>::scalar_t max_)                               {const vec4<T> &v=clamp(reinterpret_cast<const vec4<T>&>(c_), min_, max_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> abs(const color_hsva<T> &c_)                                         {const vec4<T> &v=abs(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> sqr(const color_hsva<T> &c_)                                         {const vec4<T> &v=sqr(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> cubic(const color_hsva<T> &c_)                                       {const vec4<T> &v=cubic(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> sqrt(const color_hsva<T> &c_)                                        {const vec4<T> &v=sqrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> sqrt_z(const color_hsva<T> &c_)                                      {const vec4<T> &v=sqrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> cbrt(const color_hsva<T> &c_)                                        {const vec4<T> &v=cbrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> rsqrt(const color_hsva<T> &c_)                                       {const vec4<T> &v=rsqrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> rsqrt_z(const color_hsva<T> &c_)                                     {const vec4<T> &v=rsqrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> rcbrt(const color_rgba<T> &c_)                                       {const vec4<T> &v=rcbrt(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> rcbrt_z(const color_rgba<T> &c_)                                     {const vec4<T> &v=rcbrt_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm(const color_hsva<T> &c_)                           {return norm(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm(const color_hsva<T> &c_)                          {return rnorm(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_z(const color_hsva<T> &c_)                        {return rnorm_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm2(const color_hsva<T> &c_)                          {return norm2(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2(const color_hsva<T> &c_)                         {return rnorm2(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm2_z(const color_hsva<T> &c_)                       {return rnorm2_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t norm_l1(const color_hsva<T> &c_)                        {return norm_l1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1(const color_hsva<T> &c_)                       {return rnorm_l1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t rnorm_l1_z(const color_hsva<T> &c_)                     {return rnorm_l1_z(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE color_hsva<T> exp(const color_hsva<T> &c_)                                         {const vec4<T> &v=exp(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> exp2(const color_hsva<T> &c_)                                        {const vec4<T> &v=exp2(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> ln(const color_hsva<T> &c_)                                          {const vec4<T> &v=ln(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> log2(const color_hsva<T> &c_)                                        {const vec4<T> &v=log2(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> log10(const color_hsva<T> &c_)                                       {const vec4<T> &v=log10(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> pow(const color_hsva<T> &c_, typename math<T>::scalar_t p_)          {const vec4<T> &v=pow(reinterpret_cast<const vec4<T>&>(c_), p_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> unit(const color_hsva<T> &c_)                                        {const vec4<T> &v=unit(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> unit_z(const color_hsva<T> &c_)                                      {const vec4<T> &v=unit_z(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot(const color_hsva<T> &c0_, const color_hsva<T> &c1_) {return dot(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_));}
template<typename T> PFC_INLINE typename math<T>::scalar_t dot1(const color_hsva<T> &c_)                           {return dot1(reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void neg(color_hsva<T> &c_)                                                        {neg(reinterpret_cast<vec4<T>&>(c_));}
template<typename T, class Rand> PFC_INLINE void rand_u(color_hsva<T> &c_, Rand &rnd_)                             {rand_u(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_real1(color_hsva<T> &c_, Rand &rnd_)                         {rand_real1(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T, class Rand> PFC_INLINE void rand_ureal1(color_hsva<T> &c_, Rand &rnd_)                        {rand_ureal1(reinterpret_cast<vec4<T>&>(c_), rnd_);}
template<typename T> PFC_INLINE color_hsva<T> smoothstep(const color_hsva<T> &c_)                                  {const vec4<T> &v=smoothstep(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> smootherstep(const color_hsva<T> &c_)                                {const vec4<T> &v=smootherstep(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> lerp(const color_hsva<T> &c0_, const color_hsva<T> &c1_, float t_)   {const vec4<T> &v=lerp(reinterpret_cast<const vec4<T>&>(c0_), reinterpret_cast<const vec4<T>&>(c1_), t_); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> reflect(const color_hsva<T> &c_, const color_hsva<T> &cn_)           {const vec4<T> &v=reflect(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(cn_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE color_hsva<T> reflect_u(const color_hsva<T> &c_, const color_hsva<T> &cn_)         {const vec4<T> &v=reflect_u(reinterpret_cast<const vec4<T>&>(c_), reinterpret_cast<const vec4<T>&>(cn_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<unsigned shuffle_, typename T> PFC_INLINE color_hsva<T> shuffle(const color_hsva<T> &c_)                  {const vec4<T> &v=shuffle<shuffle_>(reinterpret_cast<const vec4<T>&>(c_)); return reinterpret_cast<const color_hsva<T>&>(v);}
template<typename T> PFC_INLINE void pack_u1(color_hsva32 &cr_, const color_hsva<T> &c_)                           {pack_u1(reinterpret_cast<vec4_32u&>(cr_), reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void pack_s1(color_hsva32 &cr_, const color_hsva<T> &c_)                           {pack_s1(reinterpret_cast<vec4_32s&>(cr_), reinterpret_cast<const vec4<T>&>(c_));}
template<typename T> PFC_INLINE void unpack_u1(color_hsva<T> &cr_, const color_hsva32 &c_)                         {unpack_u1(reinterpret_cast<vec4<T>&>(cr_), reinterpret_cast<const vec4_32u&>(c_));}
template<typename T> PFC_INLINE void unpack_s1(color_hsva<T> &cr_, const color_hsva32 &c_)                         {unpack_s1(reinterpret_cast<vec4<T>&>(cr_), reinterpret_cast<const vec4_32s&>(c_));}
//----------------------------------------------------------------------------


//============================================================================
// simd_color_rgbf
//============================================================================
simd_color_rgbf::color_rgb()
{
}
//----

simd_color_rgbf::color_rgb(float r_, float g_, float b_)
  :r(r_)
  ,g(g_)
  ,b(b_)
{
}
//----

simd_color_rgbf::color_rgb(const color_rgba<simd_float4> &c_)
  :r(c_.r)
  ,g(c_.g)
  ,b(c_.b)
{
}
//----------------------------------------------------------------------------

const float &simd_color_rgbf::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<const float*>(this)[idx_];
}
//----

float &simd_color_rgbf::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<float*>(this)[idx_];
}
//----

void simd_color_rgbf::set(float r_, float g_, float b_)
{
  r=r_;
  g=g_;
  b=b_;
}
//----------------------------------------------------------------------------


//============================================================================
// simd_color_rgbaf
//============================================================================
simd_color_rgbaf::color_rgba()
{
}
//----

simd_color_rgbaf::color_rgba(float r_, float g_, float b_)
  :r(r_)
  ,g(g_)
  ,b(b_)
  ,a(1.0f)
{
}
//----

simd_color_rgbaf::color_rgba(float r_, float g_, float b_, float a_)
  :r(r_)
  ,g(g_)
  ,b(b_)
  ,a(a_)
{
}
//----

simd_color_rgbaf::color_rgba(const color_rgb<simd_float4> &c_)
  :r(c_.r)
  ,g(c_.g)
  ,b(c_.b)
  ,a(1.0f)
{
}
//----

simd_color_rgbaf::color_rgba(const color_rgb<simd_float4> &c_, float a_)
  :r(c_.r)
  ,g(c_.g)
  ,b(c_.b)
  ,a(a_)
{
}
//----------------------------------------------------------------------------

const float &simd_color_rgbaf::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const float*>(this)[idx_];
}
//----

float &simd_color_rgbaf::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<float*>(this)[idx_];
}
//----

void simd_color_rgbaf::set(float r_, float g_, float b_)
{
  r=r_;
  g=g_;
  b=b_;
}
//----

void simd_color_rgbaf::set(float r_, float g_, float b_, float a_)
{
  r=r_;
  g=g_;
  b=b_;
  a=a_;
}
//----------------------------------------------------------------------------


//============================================================================
// simd_color_yiqf
//============================================================================
simd_color_yiqf::color_yiq()
{
}
//----

simd_color_yiqf::color_yiq(float y_, float i_, float q_)
  :y(y_)
  ,i(i_)
  ,q(q_)
{
}
//----

simd_color_yiqf::color_yiq(const color_yiqa<simd_float4> &c_)
  :y(c_.y)
  ,i(c_.i)
  ,q(c_.q)
{
}
//----------------------------------------------------------------------------

const float &simd_color_yiqf::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<const float*>(this)[idx_];
}
//----

float &simd_color_yiqf::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<float*>(this)[idx_];
}
//----

void simd_color_yiqf::set(float y_, float i_, float q_)
{
  y=y_;
  i=i_;
  q=q_;
}
//----------------------------------------------------------------------------


//============================================================================
// simd_color_yiqaf
//============================================================================
simd_color_yiqaf::color_yiqa()
{
}
//----

simd_color_yiqaf::color_yiqa(float y_, float i_, float q_)
  :y(y_)
  ,i(i_)
  ,q(q_)
  ,a(1.0f)
{
}
//----

simd_color_yiqaf::color_yiqa(float y_, float i_, float q_, float a_)
  :y(y_)
  ,i(i_)
  ,q(q_)
  ,a(a_)
{
}
//----

simd_color_yiqaf::color_yiqa(const color_yiq<simd_float4> &c_)
  :y(c_.y)
  ,i(c_.i)
  ,q(c_.q)
  ,a(1.0f)
{
}
//----

simd_color_yiqaf::color_yiqa(const color_yiq<simd_float4> &c_, float a_)
  :y(c_.y)
  ,i(c_.i)
  ,q(c_.q)
  ,a(a_)
{
}
//----------------------------------------------------------------------------

const float &simd_color_yiqaf::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const float*>(this)[idx_];
}
//----

float &simd_color_yiqaf::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<float*>(this)[idx_];
}
//----

void simd_color_yiqaf::set(float y_, float i_, float q_)
{
  y=y_;
  i=i_;
  q=q_;
}
//----

void simd_color_yiqaf::set(float y_, float i_, float q_, float a_)
{
  y=y_;
  i=i_;
  q=q_;
  a=a_;
}
//----------------------------------------------------------------------------


//============================================================================
// simd_color_hsvf
//============================================================================
simd_color_hsvf::color_hsv()
{
}
//----

simd_color_hsvf::color_hsv(float h_, float s_, float v_)
  :h(h_)
  ,s(s_)
  ,v(v_)
{
}
//----

simd_color_hsvf::color_hsv(const color_hsva<simd_float4> &c_)
  :h(c_.h)
  ,s(c_.s)
  ,v(c_.v)
{
}
//----------------------------------------------------------------------------

const float &simd_color_hsvf::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<const float*>(this)[idx_];
}
//----

float &simd_color_hsvf::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<3);
  return reinterpret_cast<float*>(this)[idx_];
}
//----

void simd_color_hsvf::set(float h_, float s_, float v_)
{
  h=h_;
  s=s_;
  v=v_;
}
//----------------------------------------------------------------------------


//============================================================================
// simd_color_hsvaf
//============================================================================
simd_color_hsvaf::color_hsva()
{
}
//----

simd_color_hsvaf::color_hsva(float h_, float s_, float v_)
  :h(h_)
  ,s(s_)
  ,v(v_)
  ,a(1.0f)
{
}
//----

simd_color_hsvaf::color_hsva(float h_, float s_, float v_, float a_)
  :h(h_)
  ,s(s_)
  ,v(v_)
  ,a(a_)
{
}
//----

simd_color_hsvaf::color_hsva(const color_hsv<simd_float4> &c_)
  :h(c_.h)
  ,s(c_.s)
  ,v(c_.v)
  ,a(1.0f)
{
}
//----

simd_color_hsvaf::color_hsva(const color_hsv<simd_float4> &c_, float a_)
  :h(c_.h)
  ,s(c_.s)
  ,v(c_.v)
  ,a(a_)
{
}
//----------------------------------------------------------------------------

const float &simd_color_hsvaf::operator[](unsigned idx_) const
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<const float*>(this)[idx_];
}
//----

float &simd_color_hsvaf::operator[](unsigned idx_)
{
  PFC_ASSERT_PEDANTIC(idx_<4);
  return reinterpret_cast<float*>(this)[idx_];
}
//----

void simd_color_hsvaf::set(float h_, float s_, float v_)
{
  h=h_;
  s=s_;
  v=v_;
}
//----

void simd_color_hsvaf::set(float h_, float s_, float v_, float a_)
{
  h=h_;
  s=s_;
  v=v_;
  a=a_;
}
//----------------------------------------------------------------------------


//============================================================================
// RGB <-> XYZ color space conversion
//============================================================================
template<typename T>
mat33<T> tform_rgb_to_xyz(const vec2<T> &prim_rxy_, const vec2<T> &prim_gxy_, const vec2<T> &prim_bxy_, const vec2<T> &wp_)
{
  // generate RGB->XYZ transform matrix for given RGB primaries & white point
  typedef typename math<T>::scalar_t scalar_t;
  mat33<T> m(prim_rxy_.x/prim_rxy_.y, scalar_t(1.0), (scalar_t(1.0)-prim_rxy_.x-prim_rxy_.y)/prim_rxy_.y,
             prim_gxy_.x/prim_gxy_.y, scalar_t(1.0), (scalar_t(1.0)-prim_gxy_.x-prim_gxy_.y)/prim_gxy_.y,
             prim_bxy_.x/prim_bxy_.y, scalar_t(1.0), (scalar_t(1.0)-prim_bxy_.x-prim_bxy_.y)/prim_bxy_.y);
  vec3<T> wp_norm(wp_.x/wp_.y, scalar_t(1.0), (scalar_t(1.0)-wp_.x-wp_.y)/wp_.y);
  return mat33<T>(wp_norm*inv(m))*m;
}
//----

template<typename T>
mat33<T> tform_xyz_to_rgb(const vec2<T> &prim_rxy_, const vec2<T> &prim_gxy_, const vec2<T> &prim_bxy_, const vec2<T> &wp_)
{
  // generate XYZ->RGB transform matrix for given RGB primaries & white point
  typedef typename math<T>::scalar_t scalar_t;
  mat33<T> m(prim_rxy_.x/prim_rxy_.y, scalar_t(1.0), (scalar_t(1.0)-prim_rxy_.x-prim_rxy_.y)/prim_rxy_.y,
             prim_gxy_.x/prim_gxy_.y, scalar_t(1.0), (scalar_t(1.0)-prim_gxy_.x-prim_gxy_.y)/prim_gxy_.y,
             prim_bxy_.x/prim_bxy_.y, scalar_t(1.0), (scalar_t(1.0)-prim_bxy_.x-prim_bxy_.y)/prim_bxy_.y);
  vec3<T> wp_norm(wp_.x/wp_.y, scalar_t(1.0), (scalar_t(1.0)-wp_.x-wp_.y)/wp_.y);
  mat33<T> inv_m=inv(m);
  return inv_m*mat33<T>(rcp(wp_norm*inv_m));
}
//----

template<typename T>
mat33<T> tform_rgb_to_xyz(e_rgb_color_space rgb_cspace_)
{
  typedef typename math<T>::scalar_t scalar_t;
  switch(rgb_cspace_)
  {
    case rgbcs_srgb:     return tform_rgb_to_xyz(vec2<T>(scalar_t(0.64000), scalar_t(0.33000)), vec2<T>(scalar_t(0.30000), scalar_t(0.60000)), vec2<T>(scalar_t(0.15000), scalar_t( 0.06000)), cie_white_point<T>(ciewpnt_2deg_d65));
    case rgbcs_rec2020:  return tform_rgb_to_xyz(vec2<T>(scalar_t(0.70792), scalar_t(0.29203)), vec2<T>(scalar_t(0.17024), scalar_t(0.79652)), vec2<T>(scalar_t(0.13137), scalar_t( 0.04588)), cie_white_point<T>(ciewpnt_2deg_d65));
    case rgbcs_dcip3:    return tform_rgb_to_xyz(vec2<T>(scalar_t(0.68000), scalar_t(0.32000)), vec2<T>(scalar_t(0.26500), scalar_t(0.69000)), vec2<T>(scalar_t(0.15000), scalar_t( 0.06000)), cie_white_point<T>(ciewpnt_2deg_d65));
    case rgbcs_dcip3t:   return tform_rgb_to_xyz(vec2<T>(scalar_t(0.68000), scalar_t(0.32000)), vec2<T>(scalar_t(0.26500), scalar_t(0.69000)), vec2<T>(scalar_t(0.15000), scalar_t( 0.06000)), cie_white_point<T>(ciewpnt_2deg_d65_p3t));
    case rgbcs_adobe:    return tform_rgb_to_xyz(vec2<T>(scalar_t(0.64000), scalar_t(0.33000)), vec2<T>(scalar_t(0.21000), scalar_t(0.71000)), vec2<T>(scalar_t(0.15000), scalar_t( 0.06000)), cie_white_point<T>(ciewpnt_2deg_d65));
    case rgbcs_adobe_wg: return tform_rgb_to_xyz(vec2<T>(scalar_t(0.73469), scalar_t(0.26531)), vec2<T>(scalar_t(0.11416), scalar_t(0.82621)), vec2<T>(scalar_t(0.15664), scalar_t( 0.01770)), cie_white_point<T>(ciewpnt_2deg_d50));
    case rgbcs_prophoto: return tform_rgb_to_xyz(vec2<T>(scalar_t(0.73470), scalar_t(0.26530)), vec2<T>(scalar_t(0.15960), scalar_t(0.84040)), vec2<T>(scalar_t(0.03660), scalar_t( 0.00010)), cie_white_point<T>(ciewpnt_2deg_d50));
    case rgbcs_aces_ap0: return tform_rgb_to_xyz(vec2<T>(scalar_t(0.73470), scalar_t(0.26530)), vec2<T>(scalar_t(0.00000), scalar_t(1.00000)), vec2<T>(scalar_t(0.00010), scalar_t(-0.07700)), cie_white_point<T>(ciewpnt_2deg_d60));
    case rgbcs_aces_ap1: return tform_rgb_to_xyz(vec2<T>(scalar_t(0.71300), scalar_t(0.29300)), vec2<T>(scalar_t(0.16500), scalar_t(0.83000)), vec2<T>(scalar_t(0.12800), scalar_t( 0.04400)), cie_white_point<T>(ciewpnt_2deg_d60));
  }
  PFC_ERRORF("Unknown color space \"%s\"", enum_string(rgb_cspace_));
  return mat33<T>::s_zero;
}
//----

template<typename T>
mat33<T> tform_xyz_to_rgb(e_rgb_color_space rgb_cspace_)
{
  typedef typename math<T>::scalar_t scalar_t;
  switch(rgb_cspace_)
  {
    case rgbcs_srgb:     return tform_xyz_to_rgb(vec2<T>(scalar_t(0.64000), scalar_t(0.33000)), vec2<T>(scalar_t(0.30000), scalar_t(0.60000)), vec2<T>(scalar_t(0.15000), scalar_t( 0.06000)), cie_white_point<T>(ciewpnt_2deg_d65));
    case rgbcs_rec2020:  return tform_xyz_to_rgb(vec2<T>(scalar_t(0.70792), scalar_t(0.29203)), vec2<T>(scalar_t(0.17024), scalar_t(0.79652)), vec2<T>(scalar_t(0.13137), scalar_t( 0.04588)), cie_white_point<T>(ciewpnt_2deg_d65));
    case rgbcs_dcip3:    return tform_xyz_to_rgb(vec2<T>(scalar_t(0.68000), scalar_t(0.32000)), vec2<T>(scalar_t(0.26500), scalar_t(0.69000)), vec2<T>(scalar_t(0.15000), scalar_t( 0.06000)), cie_white_point<T>(ciewpnt_2deg_d65));
    case rgbcs_dcip3t:   return tform_xyz_to_rgb(vec2<T>(scalar_t(0.68000), scalar_t(0.32000)), vec2<T>(scalar_t(0.26500), scalar_t(0.69000)), vec2<T>(scalar_t(0.15000), scalar_t( 0.06000)), cie_white_point<T>(ciewpnt_2deg_d65_p3t));
    case rgbcs_adobe:    return tform_xyz_to_rgb(vec2<T>(scalar_t(0.64000), scalar_t(0.33000)), vec2<T>(scalar_t(0.21000), scalar_t(0.71000)), vec2<T>(scalar_t(0.15000), scalar_t( 0.06000)), cie_white_point<T>(ciewpnt_2deg_d65));
    case rgbcs_adobe_wg: return tform_xyz_to_rgb(vec2<T>(scalar_t(0.73469), scalar_t(0.26531)), vec2<T>(scalar_t(0.11416), scalar_t(0.82621)), vec2<T>(scalar_t(0.15664), scalar_t( 0.01770)), cie_white_point<T>(ciewpnt_2deg_d50));
    case rgbcs_prophoto: return tform_xyz_to_rgb(vec2<T>(scalar_t(0.73470), scalar_t(0.26530)), vec2<T>(scalar_t(0.15960), scalar_t(0.84040)), vec2<T>(scalar_t(0.03660), scalar_t( 0.00010)), cie_white_point<T>(ciewpnt_2deg_d50));
    case rgbcs_aces_ap0: return tform_xyz_to_rgb(vec2<T>(scalar_t(0.73470), scalar_t(0.26530)), vec2<T>(scalar_t(0.00000), scalar_t(1.00000)), vec2<T>(scalar_t(0.00010), scalar_t(-0.07700)), cie_white_point<T>(ciewpnt_2deg_d60));
    case rgbcs_aces_ap1: return tform_xyz_to_rgb(vec2<T>(scalar_t(0.71300), scalar_t(0.29300)), vec2<T>(scalar_t(0.16500), scalar_t(0.83000)), vec2<T>(scalar_t(0.12800), scalar_t( 0.04400)), cie_white_point<T>(ciewpnt_2deg_d60));
  }
  PFC_ERRORF("Unknown color space \"%s\"", enum_string(rgb_cspace_));
  return mat33<T>::s_zero;
}
//----------------------------------------------------------------------------


//============================================================================
// RGB <-> YIQ color space conversion
//============================================================================
template<typename T>
PFC_INLINE mat33<T> tform_srgb_to_yiq()
{
  typedef typename math<T>::scalar_t scalar_t;
  return mat33<T>(scalar_t(0.29906252315023879), scalar_t( 0.59619793162446932), scalar_t( 0.21158684041481168),
                  scalar_t(0.58673030847027274), scalar_t(-0.27501215228975523), scalar_t(-0.52313197234453446),
                  scalar_t(0.11420716837948833), scalar_t(-0.32118577933471409), scalar_t( 0.31154513192972272));
}
//----

template<typename T>
PFC_INLINE mat33<T> tform_yiq_to_srgb()
{
  typedef typename math<T>::scalar_t scalar_t;
  return mat33<T>(scalar_t(1.0),   scalar_t( 1.0),   scalar_t( 1.0),
                  scalar_t(0.956), scalar_t(-0.272), scalar_t(-1.106),
                  scalar_t(0.619), scalar_t(-0.647), scalar_t( 1.703));
}
//----

template<typename T>
PFC_INLINE color_yiq<T> srgb_to_yiq(const color_rgb<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_yiq<T>(scalar_t(0.29906252315023879)*c_.r+scalar_t(0.58673030847027274)*c_.g+scalar_t(0.11420716837948833)*c_.b,
                      scalar_t(0.59619793162446932)*c_.r-scalar_t(0.27501215228975523)*c_.g-scalar_t(0.32118577933471409)*c_.b,
                      scalar_t(0.21158684041481168)*c_.r-scalar_t(0.52313197234453446)*c_.g+scalar_t(0.31154513192972272)*c_.b);
}
//----

template<typename T>
PFC_INLINE color_rgb<T> yiq_to_srgb(const color_yiq<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_rgb<T>(c_.y+scalar_t(0.956)*c_.i+scalar_t(0.619)*c_.q,
                      c_.y-scalar_t(0.272)*c_.i-scalar_t(0.647)*c_.q,
                      c_.y-scalar_t(1.106)*c_.i+scalar_t(1.703)*c_.q);
}
//----

template<typename T>
PFC_INLINE color_yiqa<T> srgb_to_yiq(const color_rgba<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_yiqa<T>(scalar_t(0.29906252315023879)*c_.r+scalar_t(0.58673030847027274)*c_.g+scalar_t(0.11420716837948833)*c_.b,
                       scalar_t(0.59619793162446932)*c_.r-scalar_t(0.27501215228975523)*c_.g-scalar_t(0.32118577933471409)*c_.b,
                       scalar_t(0.21158684041481168)*c_.r-scalar_t(0.52313197234453446)*c_.g+scalar_t(0.31154513192972272)*c_.b,
                       c_.a);
}
//----

template<typename T>
PFC_INLINE color_rgba<T> yiq_to_srgb(const color_yiqa<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_rgba<T>(c_.y+scalar_t(0.956)*c_.i+scalar_t(0.619)*c_.q,
                       c_.y-scalar_t(0.272)*c_.i-scalar_t(0.647)*c_.q,
                       c_.y-scalar_t(1.106)*c_.i+scalar_t(1.703)*c_.q,
                       c_.a);
}
//----

template<typename T>
PFC_INLINE color_yiq<T> hdr_srgb_to_yiq(const color_rgb<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  float y=scalar_t(0.29906252315023879)*c_.r+scalar_t(0.58673030847027274)*c_.g+scalar_t(0.11420716837948833)*c_.b;
  float rcp_y=rcp_z(y);
  return color_yiq<T>(y,
                      (scalar_t(0.12369251693453720)*c_.r-scalar_t(0.05705646313065461)*c_.g-scalar_t(0.06663605380388259)*c_.b)*rcp_y+scalar_t(0.58506224066390041),
                      (scalar_t(0.05828838578920432)*c_.r-scalar_t(0.14411349100400398)*c_.g+scalar_t(0.08582510521479965)*c_.b)*rcp_y+scalar_t(0.24793388429752066));
}
//----

template<typename T>
PFC_INLINE color_rgb<T> hdr_yiq_to_srgb(const color_yiq<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_rgb<T>(c_.y*(scalar_t(-2.25302)+scalar_t(4.60792)*c_.i+scalar_t(2.24697)*c_.q),
                      c_.y*(scalar_t( 2.34934)-scalar_t(1.31104)*c_.i-scalar_t(2.34861)*c_.q),
                      c_.y*(scalar_t( 2.58622)-scalar_t(5.33092)*c_.i+scalar_t(6.18189)*c_.q));
}
//----

template<typename T>
PFC_INLINE color_yiqa<T> hdr_srgb_to_yiq(const color_rgba<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t y=scalar_t(0.29906252315023879)*c_.r+scalar_t(0.58673030847027274)*c_.g+scalar_t(0.11420716837948833)*c_.b;
  scalar_t rcp_y=rcp_z(y);
  return color_yiqa<T>(y,
                       rcp_y*(scalar_t(0.12369251693453720)*c_.r-scalar_t(0.05705646313065461)*c_.g-scalar_t(0.06663605380388259)*c_.b)+scalar_t(0.58506224066390041),
                       rcp_y*(scalar_t(0.05828838578920432)*c_.r-scalar_t(0.14411349100400398)*c_.g+scalar_t(0.08582510521479965)*c_.b)+scalar_t(0.24793388429752066),
                       c_.a);
}
//----

template<typename T>
PFC_INLINE color_rgba<T> hdr_yiq_to_srgb(const color_yiqa<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_rgba<T>(c_.y*(scalar_t(-2.25302)+scalar_t(4.60792)*c_.i+scalar_t(2.24697)*c_.q),
                       c_.y*(scalar_t( 2.34934)-scalar_t(1.31104)*c_.i-scalar_t(2.34861)*c_.q),
                       c_.y*(scalar_t( 2.58622)-scalar_t(5.33092)*c_.i+scalar_t(6.18189)*c_.q),
                       c_.a);
}
//----------------------------------------------------------------------------


//============================================================================
// RGB <-> YUV color space conversion
//============================================================================
template<typename T>
PFC_INLINE mat33<T> tform_srgb_to_yuv()
{
  typedef typename math<T>::scalar_t scalar_t;
  return mat33<T>(scalar_t(0.29900200912406033), scalar_t(-0.14713869284834993), scalar_t( 0.61500222917096392),
                  scalar_t(0.58699872555955512), scalar_t(-0.28886168837294984), scalar_t(-0.51498795922159890),
                  scalar_t(0.11399926531638466), scalar_t( 0.43600038122129975), scalar_t(-0.10001426994936496));
}
//----

template<typename T>
PFC_INLINE mat33<T> tform_yuv_to_srgb()
{
  typedef typename math<T>::scalar_t scalar_t;
  return mat33<T>(scalar_t(1.0),     scalar_t( 1.0),     scalar_t(1.0),
                  scalar_t(0.0),     scalar_t(-0.39465), scalar_t(2.03211),
                  scalar_t(1.13983), scalar_t(-0.58060), scalar_t(0.0));
}
//----

template<typename T>
PFC_INLINE color_yiq<T> hdr_srgb_to_yuv(const color_rgb<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  float y=scalar_t(0.29900200912406033)*c_.r+scalar_t(0.58699872555955512)*c_.g+scalar_t(0.11399926531638466)*c_.b;
  float rcp_y=rcp_z(y);
  return color_yiq<T>(y,
                      rcp_y*(scalar_t(-0.0340756583715493)*c_.r-scalar_t(0.06689710244857569)*c_.g+scalar_t(0.100972760820125)*c_.b)+scalar_t(0.11399926531638466),
                      rcp_y*(scalar_t( 0.2095407935846555)*c_.r-scalar_t(0.17546438133614954)*c_.g-scalar_t(0.034075658371549)*c_.b)+scalar_t(0.29900200912406033));
}
//----

template<typename T>
PFC_INLINE color_rgb<T> hdr_yuv_to_srgb(const color_yiq<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_rgb<T>(c_.y*(scalar_t(3.34540)*c_.q),
                      c_.y*(scalar_t(1.70410)*(scalar_t(1)-c_.i-c_.q)),
                      c_.y*(scalar_t(8.77465)*c_.i));
}
//----

template<typename T>
PFC_INLINE color_yiqa<T> hdr_srgb_to_yuv(const color_rgba<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  float y=scalar_t(0.29900200912406033)*c_.r+scalar_t(0.58699872555955512)*c_.g+scalar_t(0.11399926531638466)*c_.b;
  float rcp_y=rcp_z(y);
  return color_yiqa<T>(y,
                       rcp_y*(scalar_t(-0.0340756583715493)*c_.r-scalar_t(0.06689710244857569)*c_.g+scalar_t(0.100972760820125)*c_.b)+scalar_t(0.11399926531638466),
                       rcp_y*(scalar_t( 0.2095407935846555)*c_.r-scalar_t(0.17546438133614954)*c_.g-scalar_t(0.034075658371549)*c_.b)+scalar_t(0.29900200912406033),
                       c_.a);
}
//----

template<typename T>
PFC_INLINE color_rgba<T> hdr_yuv_to_srgb(const color_yiqa<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_rgba<T>(c_.y*(scalar_t(3.34540)*c_.q),
                       c_.y*(scalar_t(1.70410)*(scalar_t(1)-c_.i-c_.q)),
                       c_.y*(scalar_t(8.77465)*c_.i),
                       c_.a);
}
//----------------------------------------------------------------------------


//============================================================================
// RGB <-> HSV color space conversion
//============================================================================
template<typename T>
color_rgb<T> hsv_to_srgb(const color_hsv<T> &c_)
{
  // convert color from HSV->RGB
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT(c_.h>=0 && c_.h<=1);
#if 0
  scalar_t f=c_.h*scalar_t(5.9999);
  unsigned i=unsigned(f);
  f-=scalar_t(i);
  scalar_t p=c_.v-c_.v*c_.s;
  scalar_t q=c_.v-c_.v*c_.s*f;
  return color_rgb<T>((i-1>2?c_.v:0)+(i-2<3?p:0)+(i==1?q:i==4?-q:0),
                      (  i<3?c_.v:0)+(i-1>2?p:0)+(i==3?q:i==0?-q:0),
                      (i-2<3?c_.v:0)+(  i<3?p:0)+(i==5?q:i==2?-q:0));
#else
  scalar_t f=c_.h*scalar_t(6.0);
  unsigned i=unsigned(f);
  f-=scalar_t(i);
  scalar_t p=c_.v*(1.0f-c_.s), q=c_.v*(1.0f-c_.s*f), t=p+c_.v*c_.s*f;
  const scalar_t clut[]={p, p, t, c_.v, c_.v, q, p, p, t, c_.v, c_.v};
  return color_rgb<T>(clut[i+4], clut[i+2], clut[i+0]);
#endif
}
//----

template<typename T>
color_hsv<T> srgb_to_hsv(const color_rgb<T> &c_)
{
  // convert color from HSV->RGB
  // calculate RGB component min, max and delta
  typedef typename math<T>::scalar_t scalar_t;
  T cmin=min(c_.r, c_.g, c_.b);
  T cmax=max(c_.r, c_.g, c_.b);
  T d=cmax-cmin;
  if(!d)
    return color_hsv<T>(scalar_t(0.0), scalar_t(0.0), cmax);
  T rcpd=rcp(d);
 
  // calculate hue
  T hue;
  if(c_.r==cmax)
    hue=(c_.g-c_.b)*rcpd;
  else if(c_.g==cmax)
    hue=(c_.b-c_.r)*rcpd+scalar_t(2.0);
  else
    hue=(c_.r-c_.g)*rcpd+scalar_t(4.0);
  hue/=scalar_t(6.0);
  if(hue<scalar_t(0.0))
      hue+=scalar_t(1.0);

  // return HSV color
  return color_hsv<T>(hue, d/cmax, cmax);
}
//----

template<typename T>
color_rgba<T> hsv_to_srgb(const color_hsva<T> &c_)
{
  // convert color from HSV->RGB
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT(c_.h>=0 && c_.h<=1);
  scalar_t f=c_.h*scalar_t(5.9999);
  unsigned i=unsigned(f);
  f-=scalar_t(i);
  scalar_t p=scalar_t(1)-c_.s;
  scalar_t q=scalar_t(1)-c_.s*f;
  return color_rgba<T>((i-1>2?c_.v:0)+(i-2<3?p:0)+(i==1?q:i==4?-q:0),
                       (  i<3?c_.v:0)+(i-1>2?p:0)+(i==3?q:i==0?-q:0),
                       (i-2<3?c_.v:0)+(  i<3?p:0)+(i==5?q:i==2?-q:0),
                       c_.a);
}
//----

template<typename T>
color_hsva<T> srgb_to_hsv(const color_rgba<T> &c_)
{
  // calculate RGB component min, max and delta
  typedef typename math<T>::scalar_t scalar_t;
  T cmin=min(c_.r, c_.g, c_.b);
  T cmax=max(c_.r, c_.g, c_.b);
  T d=cmax-cmin;
  if(!d)
    return color_hsv<T>(scalar_t(0.0), scalar_t(0.0), cmax, c_.a);
  T rcpd=rcp(d);
 
  // calculate hue
  T hue;
  if(c_.r==cmax)
    hue=(c_.g-c_.b)*rcpd;
  else if(c_.g==cmax)
    hue=(c_.b-c_.r)*rcpd+scalar_t(2.0);
  else
    hue=(c_.r-c_.g)*rcpd+scalar_t(4.0);
  hue/=scalar_t(6.0);
  if(hue<scalar_t(0.0))
      hue+=scalar_t(1.0);

  // return HSV color
  return color_hsv<T>(hue, d/cmax, cmax, c_.a);
}
//----------------------------------------------------------------------------


//============================================================================
// sRGB <-> linear conversions
//============================================================================
template<typename T>
PFC_INLINE T linear_to_srgb(T v_)
{
  return v_<=T(0.0031308)?v_*T(12.92):T(1.055)*pow(v_, T(1.0/2.4))-T(0.055);
}
//----

template<typename T>
PFC_INLINE color_rgb<T> linear_to_srgb(const color_rgb<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_rgb<T>(c_.r<=scalar_t(0.0031308)?c_.r*scalar_t(12.92):scalar_t(1.055)*pow(c_.r, scalar_t(1.0/2.4))-scalar_t(0.055),
                      c_.g<=scalar_t(0.0031308)?c_.g*scalar_t(12.92):scalar_t(1.055)*pow(c_.g, scalar_t(1.0/2.4))-scalar_t(0.055),
                      c_.b<=scalar_t(0.0031308)?c_.b*scalar_t(12.92):scalar_t(1.055)*pow(c_.b, scalar_t(1.0/2.4))-scalar_t(0.055));
}
//----

template<typename T>
PFC_INLINE color_rgba<T> linear_to_srgb(const color_rgba<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_rgba<T>(c_.r<=scalar_t(0.0031308)?c_.r*scalar_t(12.92):scalar_t(1.055)*pow(c_.r, scalar_t(1.0/2.4))-scalar_t(0.055),
                       c_.g<=scalar_t(0.0031308)?c_.g*scalar_t(12.92):scalar_t(1.055)*pow(c_.g, scalar_t(1.0/2.4))-scalar_t(0.055),
                       c_.b<=scalar_t(0.0031308)?c_.b*scalar_t(12.92):scalar_t(1.055)*pow(c_.b, scalar_t(1.0/2.4))-scalar_t(0.055),
                       c_.a);
}
//----

template<typename T>
PFC_INLINE T srgb_to_linear(T v_)
{
  return v_<=T(0.04045)?v_/T(12.92):pow((v_+T(0.055))/T(1.055), T(2.4));
}
//----

template<typename T>
PFC_INLINE color_rgb<T> srgb_to_linear(const color_rgb<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_rgb<T>(c_.r<=scalar_t(0.04045)?c_.r/scalar_t(12.92):pow((c_.r+scalar_t(0.055))/scalar_t(1.055), scalar_t(2.4)),
                      c_.g<=scalar_t(0.04045)?c_.g/scalar_t(12.92):pow((c_.g+scalar_t(0.055))/scalar_t(1.055), scalar_t(2.4)),
                      c_.b<=scalar_t(0.04045)?c_.b/scalar_t(12.92):pow((c_.b+scalar_t(0.055))/scalar_t(1.055), scalar_t(2.4)));
}
//----

template<typename T>
PFC_INLINE color_rgba<T> srgb_to_linear(const color_rgba<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return color_rgba<T>(c_.r<=scalar_t(0.04045)?c_.r/scalar_t(12.92):pow((c_.r+scalar_t(0.055))/scalar_t(1.055), scalar_t(2.4)),
                       c_.g<=scalar_t(0.04045)?c_.g/scalar_t(12.92):pow((c_.g+scalar_t(0.055))/scalar_t(1.055), scalar_t(2.4)),
                       c_.b<=scalar_t(0.04045)?c_.b/scalar_t(12.92):pow((c_.b+scalar_t(0.055))/scalar_t(1.055), scalar_t(2.4)),
                       c_.a);
}
//----------------------------------------------------------------------------


//============================================================================
// luminance
//============================================================================
template<typename T>
typename math<T>::scalar_t PFC_INLINE luminance_srgb(const color_rgb<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return scalar_t(0.29893602129377533)*c_.r+scalar_t(0.58704307445112125)*c_.g+scalar_t(0.11402090425510331)*c_.b;
}
//----

template<typename T>
typename math<T>::scalar_t PFC_INLINE luminance_srgb(const color_rgba<T> &c_)
{
  typedef typename math<T>::scalar_t scalar_t;
  return scalar_t(0.29893602129377533)*c_.r+scalar_t(0.58704307445112125)*c_.g+scalar_t(0.11402090425510331)*c_.b;
}
//----------------------------------------------------------------------------


//============================================================================
// white_point
//============================================================================
template<typename T>
vec2<T> cie_white_point(e_cie_white_point wp_)
{
  typedef typename math<T>::scalar_t scalar_t;
  switch(wp_)
  {
    case ciewpnt_2deg_a:       return vec2<T>(scalar_t(0.44757), scalar_t(0.40745));
    case ciewpnt_2deg_b:       return vec2<T>(scalar_t(0.34842), scalar_t(0.35161));
    case ciewpnt_2deg_c:       return vec2<T>(scalar_t(0.31006), scalar_t(0.31616));
    case ciewpnt_2deg_d50:     return vec2<T>(scalar_t(0.34567), scalar_t(0.35850));
    case ciewpnt_2deg_d55:     return vec2<T>(scalar_t(0.33242), scalar_t(0.34743));
    case ciewpnt_2deg_d60:     return vec2<T>(scalar_t(0.32168), scalar_t(0.33767));
    case ciewpnt_2deg_d65:     return vec2<T>(scalar_t(0.31271), scalar_t(0.32902));
    case ciewpnt_2deg_d65_p3t: return vec2<T>(scalar_t(0.314),   scalar_t(0.351));
    case ciewpnt_2deg_d75:     return vec2<T>(scalar_t(0.29902), scalar_t(0.31485));
    case ciewpnt_2deg_e:       return vec2<T>(scalar_t(1.0/3.0), scalar_t(1.0/3.0));
    case ciewpnt_2deg_f1:      return vec2<T>(scalar_t(0.31310), scalar_t(0.33727));
    case ciewpnt_2deg_f2:      return vec2<T>(scalar_t(0.37208), scalar_t(0.37529));
    case ciewpnt_2deg_f3:      return vec2<T>(scalar_t(0.40910), scalar_t(0.39430));
    case ciewpnt_2deg_f4:      return vec2<T>(scalar_t(0.44018), scalar_t(0.40329));
    case ciewpnt_2deg_f5:      return vec2<T>(scalar_t(0.31379), scalar_t(0.34531));
    case ciewpnt_2deg_f6:      return vec2<T>(scalar_t(0.37790), scalar_t(0.38835));
    case ciewpnt_2deg_f7:      return vec2<T>(scalar_t(0.31292), scalar_t(0.32933));
    case ciewpnt_2deg_f8:      return vec2<T>(scalar_t(0.34588), scalar_t(0.35875));
    case ciewpnt_2deg_f9:      return vec2<T>(scalar_t(0.37417), scalar_t(0.37281));
    case ciewpnt_2deg_f10:     return vec2<T>(scalar_t(0.34609), scalar_t(0.35986));
    case ciewpnt_2deg_f11:     return vec2<T>(scalar_t(0.38052), scalar_t(0.37713));
    case ciewpnt_2deg_f12:     return vec2<T>(scalar_t(0.43695), scalar_t(0.40441));
    case ciewpnt_10deg_a:      return vec2<T>(scalar_t(0.45117), scalar_t(0.40594));
    case ciewpnt_10deg_b:      return vec2<T>(scalar_t(0.34980), scalar_t(0.35270));
    case ciewpnt_10deg_c:      return vec2<T>(scalar_t(0.31039), scalar_t(0.31905));
    case ciewpnt_10deg_d50:    return vec2<T>(scalar_t(0.34773), scalar_t(0.35952));
    case ciewpnt_10deg_d55:    return vec2<T>(scalar_t(0.33411), scalar_t(0.34877));
    case ciewpnt_10deg_d65:    return vec2<T>(scalar_t(0.31382), scalar_t(0.33100));
    case ciewpnt_10deg_d75:    return vec2<T>(scalar_t(0.29968), scalar_t(0.31740));
    case ciewpnt_10deg_e:      return vec2<T>(scalar_t(1.0/3.0), scalar_t(1.0/3.0));
    case ciewpnt_10deg_f1:     return vec2<T>(scalar_t(0.31811), scalar_t(0.33559));
    case ciewpnt_10deg_f2:     return vec2<T>(scalar_t(0.37925), scalar_t(0.36733));
    case ciewpnt_10deg_f3:     return vec2<T>(scalar_t(0.41761), scalar_t(0.38324));
    case ciewpnt_10deg_f4:     return vec2<T>(scalar_t(0.44920), scalar_t(0.39074));
    case ciewpnt_10deg_f5:     return vec2<T>(scalar_t(0.31975), scalar_t(0.34246));
    case ciewpnt_10deg_f6:     return vec2<T>(scalar_t(0.38660), scalar_t(0.37847));
    case ciewpnt_10deg_f7:     return vec2<T>(scalar_t(0.31569), scalar_t(0.32960));
    case ciewpnt_10deg_f8:     return vec2<T>(scalar_t(0.34902), scalar_t(0.35939));
    case ciewpnt_10deg_f9:     return vec2<T>(scalar_t(0.37829), scalar_t(0.37045));
    case ciewpnt_10deg_f10:    return vec2<T>(scalar_t(0.35090), scalar_t(0.35444));
    case ciewpnt_10deg_f11:    return vec2<T>(scalar_t(0.38541), scalar_t(0.37123));
    case ciewpnt_10deg_f12:    return vec2<T>(scalar_t(0.44256), scalar_t(0.39717));
  }
  PFC_ERRORF("Unknown white point \"%s\"\r\n", enum_string(wp_));
  return vec2<T>(0, 0);
}
//----------------------------------------------------------------------------
