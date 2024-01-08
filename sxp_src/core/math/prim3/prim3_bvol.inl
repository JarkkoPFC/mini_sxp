//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// bounding_sphere3
//============================================================================
template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const segment3<T> &seg_)
{
  return sphere3<T>(seg_.pos, seg_.hlen);
}
//----

template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const tri3<T> &tri_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return sphere3<T>();
}
//----

template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const rect3<T> &rect_)
{
  return sphere3<T>(rect_.pos, norm(rect_.hsize));
}
//----

template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const disc3<T> &disc_)
{
  return sphere3<T>(disc_.pos, disc_.rad);
}
//----

template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const sphere3<T> &sphere_)
{
  return sphere_;
}
//----

template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const cylinder3<T> &cyl_)
{
  return sphere3<T>(cyl_.pos, cyl_.hlen+cyl_.rad);
}
//----

template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const capsule3<T> &cap_)
{
  return sphere3<T>(cap_.pos, cap_.hlen+cap_.rad);
}
//----

template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return sphere3<T>();
}
//----

template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const aabox3<T> &aab_)
{
  return sphere3<T>(aab_.pos, norm(aab_.hsize));
}
//----

template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const oobox3<T> &oob_)
{
  return sphere3<T>(oob_.pos, norm(oob_.hsize));
}
//----

template<typename T>
PFC_INLINE sphere3<T> bounding_sphere3(const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return sphere3<T>();
}
//----------------------------------------------------------------------------
