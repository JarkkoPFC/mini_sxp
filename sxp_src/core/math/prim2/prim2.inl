//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// point2
//============================================================================
template<typename T>
point2<T>::point2()
{
}
//----

template<typename T>
point2<T>::point2(const vec2<T> &pos_)
  :pos(pos_)
{
}
//----

template<typename T>
point2<T>::point2(scalar_t x_, scalar_t y_)
  :pos(x_, y_)
{
}
//----

template<typename T>
void point2<T>::set(const vec2<T> &pos_)
{
  pos=pos_;
}
//----

template<typename T>
void point2<T>::set(scalar_t x_, scalar_t y_)
{
  pos=vec2<T>(x_, y_);
}
//----------------------------------------------------------------------------


//============================================================================
// line2
//============================================================================
template<typename T>
line2<T>::line2()
{
}
//----

template<typename T>
line2<T>::line2(const vec2<T> &pos_, const vec2<T> &dir_)
  :pos(pos_)
  ,dir(dir_)
{
}
//----

template<typename T>
void line2<T>::set(const vec2<T> &pos_, const vec2<T> &dir_)
{
  pos=pos_;
  dir=dir_;
}
//----------------------------------------------------------------------------


//============================================================================
// ray2
//============================================================================
template<typename T>
ray2<T>::ray2()
{
}
//----

template<typename T>
ray2<T>::ray2(const vec2<T> &pos_, const vec2<T> &dir_)
  :pos(pos_)
  ,dir(dir_)
{
}
//----

template<typename T>
void ray2<T>::set(const vec2<T> &pos_, const vec2<T> &dir_)
{
  pos=pos_;
  dir=dir_;
}
//----------------------------------------------------------------------------


//============================================================================
// segment2
//============================================================================
template<typename T>
segment2<T>::segment2()
{
}
//----

template<typename T>
segment2<T>::segment2(const vec2<T> &pos_, const vec2<T> &dir_, scalar_t hlen_)
  :pos(pos_)
  ,dir(dir_)
  ,hlen(hlen_)
{
}
//----

template<typename T>
void segment2<T>::set(const vec2<T> &pos_, const vec2<T> &dir_, scalar_t hlen_)
{
  pos=pos_;
  dir=dir_;
  hlen=hlen_;
}
//----------------------------------------------------------------------------


//============================================================================
// circle2
//============================================================================
template<typename T>
circle2<T>::circle2()
{
}
//----

template<typename T>
circle2<T>::circle2(const vec2<T> &pos_, scalar_t rad_)
  :pos(pos_)
  ,rad(rad_)
{
}
//----

template<typename T>
void circle2<T>::set(const vec2<T> &pos_, scalar_t rad_)
{
  pos=pos_;
  rad=rad_;
}
//----------------------------------------------------------------------------


//============================================================================
// tri2
//============================================================================
template<typename T>
tri2<T>::tri2()
{
}
//----

template<typename T>
tri2<T>::tri2(const vec2<T> &a_, const vec2<T> &b_, const vec2<T> &c_)
  :a(a_)
  ,b(b_)
  ,c(c_)
{
}
//----

template<typename T>
void tri2<T>::set(const vec2<T> &a_, const vec2<T> &b_, const vec2<T> &c_)
{
  a=a_;
  b=b_;
  c=c_;
}
//----------------------------------------------------------------------------


//============================================================================
// aarect2
//============================================================================
template<typename T>
aarect2<T>::aarect2()
{
}
//----

template<typename T>
aarect2<T>::aarect2(const vec2<T> &pos_, const vec2<T> &hsize_)
  :pos(pos_)
  ,hsize(hsize_)
{
}
//----

template<typename T>
void aarect2<T>::set(const vec2<T> &pos_, const vec2<T> &hsize_)
{
  pos=pos_;
  hsize=hsize_;
}
//----------------------------------------------------------------------------


//============================================================================
// oorect2
//============================================================================
template<typename T>
oorect2<T>::oorect2()
{
}
//----

template<typename T>
oorect2<T>::oorect2(const vec2<T> &pos_, const vec2<T> &hsize_, const mat22<T> &rot_)
  :pos(pos_)
  ,hsize(hsize_)
  ,rot(rot_)
{
}
//----

template<typename T>
void oorect2<T>::set(const vec2<T> &pos_, const vec2<T> &hsize_, const mat22<T> &rot_)
{
  pos=pos_;
  hsize=hsize_;
  rot=rot_;
}
//----------------------------------------------------------------------------


//============================================================================
// area functions
//============================================================================
template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const circle2<T> &circle_)
{
  return math<T>::pi*circle_.rad*circle_.rad;
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const tri2<T> &tri_)
{
  return norm(tri_.b-tri_.a, tri_.c-tri_.a)*typename math<T>::scalar_t(0.5);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const aarect2<T> &aar_)
{
  return aar_.hsize.x*aar_.hsize.y*typename math<T>::scalar_t(4.0);
}
//----

template<typename T>
PFC_INLINE typename math<T>::scalar_t area(const oorect2<T> &oor_)
{
  return oor_.hsize.x*oor_.hsize.y*typename math<T>::scalar_t(4.0);
}
//----------------------------------------------------------------------------
