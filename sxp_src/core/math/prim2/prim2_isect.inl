//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// intersection test routines
//============================================================================
template<typename T>
bool isect(const point2<T> &pnt_, const circle2<T> &circle_)
{
  return norm2(circle_.pos-pnt_.pos)<circle_.rad*circle_.rad;
}
//----

template<typename T>
bool isect(const point2<T> &pnt_, const tri2<T> &tri_)
{
  typedef typename math<T>::scalar_t scalar_t;
  vec2<T> v=pnt_.pos-tri_.a;
  scalar_t a=cross(v, tri_.b-tri_.a);
  scalar_t b=cross(pnt_.pos-tri_.b, tri_.c-tri_.b);
  scalar_t c=cross(v, tri_.a-tri_.c);
  return a*b>0 && a*c>0;
}
//----

template<typename T>
bool isect(const point2<T> &pnt_, const aarect2<T> &aarect_)
{
  vec2<T> v=abs(pnt_.pos-aarect_.pos)-aarect_.hsize;
  return v.x<0 && v.y<0;
}
//----

template<typename T>
bool isect(const point2<T> &pnt_, const oorect2<T> &oorect_)
{
  vec2<T> v=abs(oorect_.rot*(pnt_.pos-oorect_.pos))-oorect_.hsize;
  return v.x<0 && v.y<0;
}
//----

template<typename T>
bool isect(const line2<T> &line_, const ray2<T> &ray_)
{
  return cross(ray_.pos-line_.pos, line_.dir)*cross(line_.dir, ray_.dir)>0;
}
//----

template<typename T>
bool isect(const line2<T> &line_, const segment2<T> &seg_)
{
  vec2<T> p=seg_.pos-line_.pos, d=seg_.dir*seg_.hlen;
  return cross(p-d, line_.dir)*cross(line_.dir, p+d)>0;
}
//----

template<typename T>
bool isect(const line2<T> &line_, const segment2<T> &seg_, typename math<T>::scalar_t &t_)
{
  vec2<T> p=line_.pos-seg_.pos;
  vec2<T> n(line_.dir.y, line_.dir.x);
  t_=dot(p, n)/dot(seg_.dir, n);
  return t_>-seg_.hlen && t_<seg_.hlen;
}
//----

template<typename T>
bool isect(const line2<T> &line_, const circle2<T> &circle_)
{
  const vec2<T> v=line_.pos-circle_.pos;
  typename math<T>::scalar_t b=dot(line_.dir, v);
  return b*b-norm2(v)+circle_.rad*circle_.rad>=0;
}
//----

template<typename T>
bool isect(const line2<T> &line_, const tri2<T> &tri_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line2<T> &line_, const aarect2<T> &aarect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const line2<T> &line_, const oorect2<T> &oorect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray2<T> &ray0_, const ray2<T> &ray1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray2<T> &ray_, const segment2<T> &seg_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray2<T> &ray_, const circle2<T> &circle_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray2<T> &ray_, const tri2<T> &tri_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray2<T> &ray_, const aarect2<T> &aarect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const ray2<T> &ray_, const oorect2<T> &oorect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment2<T> &seg0_, const segment2<T> &seg1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment2<T> &seg_, const circle2<T> &circle_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment2<T> &seg_, const tri2<T> &tri_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment2<T> &seg_, const aarect2<T> &aarect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const segment2<T> &seg_, const oorect2<T> &oorect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const circle2<T> &circle0_, const circle2<T> &circle1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const circle2<T> &circle_, const tri2<T> &tri_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const circle2<T> &circle_, const aarect2<T> &aarect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const circle2<T> &circle_, const oorect2<T> &oorect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri2<T> &tri0_, const tri2<T> &tri1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri2<T> &tri_, const aarect2<T> &aarect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const tri2<T> &tri_, const oorect2<T> &oorect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const aarect2<T> &aarect0_, const aarect2<T> &aarect1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const aarect2<T> &aarect_, const oorect2<T> &oorect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

template<typename T>
bool isect(const oorect2<T> &oorect0_, const oorect2<T> &oorect1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----------------------------------------------------------------------------
