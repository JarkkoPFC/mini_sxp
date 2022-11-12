//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// distance functions
//============================================================================
template<typename T>
typename math<T>::scalar_t dist2(const point3<T> &pnt0_, const point3<T> &pnt1_)
{
  return norm2(pnt0_.pos-pnt1_.pos);
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const point3<T> &pnt_, const line3<T> &line_)
{
  vec3<T> v=pnt_.pos-line_.pos;
  return norm2(v-line_.dir*dot(line_.dir, v));
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const point3<T> &pnt_, const ray3<T> &ray_)
{
  vec3<T> v=pnt_.pos-ray_.pos;
  return norm2(v-ray_.dir*max(math<T>::scalar_t(0), dot(ray_.dir, v)));
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const point3<T> &pnt_, const segment3<T> &seg_)
{
  /*todo: test*/
  typename math<T>::scalar_t t=clamp(dot(pnt_.pos-seg_.pos, seg_.dir), -seg_.hlen, seg_.hlen);
  return norm2(seg_.pos+t*seg_.dir-pnt_.pos);
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const point3<T> &pnt_, const tri3<T> &tri_)
{
  // calculate shared coefficients
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> e0=tri_.b-tri_.a, e1=tri_.c-tri_.a, pv=tri_.a-pnt_.pos;
  scalar_t a=norm2(e0), b=dot(e0, e1), c=norm2(e1), d=dot(e0, pv), e=dot(e1, pv), f=norm2(pv);
  scalar_t det=abs(a*c-b*b), s=b*e-c*d, t=b*d-a*e;

  // switch to proper region calculation
  if(s+t<=det)
  {
    if(s<0)
    {
      // regions 3 and 4
      if(t<0 && d<0)
        return -d<a?-d*d/a+f:a+2*d+f;
      return e<0?-e<c?-e*e/c+f:c+2*e+f:f;
    }

    // region 5
    if(t<0)
      return d<0?-d<a?-d*d/a+f:a+2*d+f:f;

    // region 0
    scalar_t rd=rcp(det);
    s*=rd;
    t*=rd;
    return s*(a*s+b*t+2*d)+
           t*(b*s+c*t+2*e)+f;
  }

  if(s<0 || t>=0)
  {
    // regions 1 & 2
    scalar_t num=c+e-b-d;
    if(num>0)
    {
      scalar_t den=a-2*b+c;
      if(num>=den)
        return a+2*d+f;
      s=num/den;
      t=1-s;
      return s*(a*s+b*t+2*d)+
             t*(b*s+c*t+2*e)+f;
    }
    return t<0?c>-e?c+2*e+f:e<0?-e*e/c+f:f:c+2*e+f;
  }

  // region 6
  scalar_t num=a+d-b-e;
  if(num>0)
  {
    scalar_t den=a-2*b+c;
    if(num>=den)
      return c+2*e+f;
    t=num/den;
    s=1-t;
    return s*(a*s+b*t+2*d)+
           t*(b*s+c*t+2*e)+f;
  }
  return a>-d?d<0?-d*d/a+f:f:a+2*d+f;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const point3<T> &pnt_, const rect3<T> &rect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const point3<T> &pnt_, const disc3<T> &disc_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const point3<T> &pnt_, const plane3<T> &plane_)
{
  return dot(pnt_.pos, plane_.normal)-plane_.d;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const point3<T> &pnt_, const sphere3<T> &sphere_)
{
  return norm(sphere_.pos-pnt_.pos)-sphere_.rad;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const point3<T> &pnt_, const cylinder3<T> &cyl_)
{
  vec3<T> v=pnt_.pos-cyl_.pos;
  typename math<T>::scalar_t d, d2=0, pl=dot(v, cyl_.dir);
  if((d=abs(pl)-cyl_.hlen)>0)
    d2+=d*d;
  if((d=norm(v-cyl_.dir*pl)-cyl_.rad)>0)
    d2+=d*d;
  return d2;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const point3<T> &pnt_, const capsule3<T> &cap_)
{
  vec3<T> v=pnt_.pos-cap_.pos;
  return norm(v-cap_.dir*clamp(dot(v, cap_.dir), -cap_.hlen, cap_.hlen))-cap_.rad;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const point3<T> &pnt_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const point3<T> &pnt_, const aabox3<T> &aab_)
{
  // calculate squared distance of point from aabox
  return norm2(max(abs(pnt_.pos-aab_.pos)-aab_.hsize, typename math<T>::scalar_t(0)));
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const point3<T> &pnt_, const oobox3<T> &oob_)
{
  // calculate squared distance of point from oobox
  return norm2(max(abs((pnt_.pos-oob_.pos)*inv_u(oob_.rot))-oob_.hsize, typename math<T>::scalar_t(0)));
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const point3<T> &pnt_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const line3<T> &line0_, const line3<T> &line1_)
{
  /*todo: fix parallel line problem*/
  vec3<T> v=unit(cross(line0_.dir, line1_.dir));
  return abs(dot(line1_.pos-line0_.pos, v));
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const line3<T> &line_, const ray3<T> &ray_)
{
  /*todo: fix parallel line problem*/
  vec3<T> a=ray_.dir-dot(ray_.dir, line_.dir)*line_.dir;
  vec3<T> pd=ray_.pos-line_.pos;
  vec3<T> b=(dot(ray_.pos, line_.dir)-dot(line_.pos, line_.dir))*line_.dir-pd;
  vec3<T> v=pd+max(dot(a, b)/dot(a, a), math<T>::scalar_t(0));
  return norm2(v-line_.dir*dot(line_.dir, v));
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const line3<T> &line_, const segment3<T> &seg_)
{
  /*todo: fix parallel line problem*/
  vec3<T> a=seg_.dir-dot(seg_.dir, line_.dir)*line_.dir;
  vec3<T> pd=seg_.pos-line_.pos;
  vec3<T> b=(dot(seg_.pos, line_.dir)-dot(line_.pos, line_.dir))*line_.dir-pd;
  vec3<T> v=pd+clamp(dot(a, b)/dot(a, a), -seg_.hlen, seg_.hlen);
  return norm2(v-line_.dir*dot(line_.dir, v));
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const line3<T> &line_, const tri3<T> &tri_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const line3<T> &line_, const rect3<T> &rect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const line3<T> &line_, const disc3<T> &disc_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const line3<T> &line_, const sphere3<T> &sphere_)
{
  vec3<T> v=sphere_.pos-line_.pos;
  return norm(v-line_.dir*dot(line_.dir, v))-sphere_.rad;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const line3<T> &line_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const line3<T> &line_, const capsule3<T> &cap_)
{
  // calculate distance of closest point on capsule segment from the line
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> pv=cap_.pos-line_.pos;
  scalar_t a=dot(line_.dir, cap_.dir);
  scalar_t t=(dot(line_.dir, pv)*a-dot(pv, cap_.dir))/(cap_.hlen*(1.0f-a*a));
  vec3<T> nv=pv+(ssat(t)*cap_.hlen)*cap_.dir;
  return norm2(nv-line_.dir*dot(line_.dir, nv));
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const line3<T> &line_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const line3<T> &line_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const line3<T> &line_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const line3<T> &line_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const ray3<T> &ray_, const segment3<T> &seg_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const ray3<T> &ray_, const tri3<T> &tri_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const ray3<T> &ray_, const rect3<T> &rect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const ray3<T> &ray_, const disc3<T> &disc_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const ray3<T> &ray_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const ray3<T> &ray_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const ray3<T> &ray_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const ray3<T> &ray_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const ray3<T> &ray_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const ray3<T> &ray_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const ray3<T> &ray_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg0_, const segment3<T> &seg1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const tri3<T> &tri_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const rect3<T> &rect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const disc3<T> &disc_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const segment3<T> &seg_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const tri3<T> &tri0_, const tri3<T> &tri1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const tri3<T> &tri_, const rect3<T> &rect_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const tri3<T> &tri_, const disc3<T> &disc_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const tri3<T> &tri_, const plane3<T> &plane_)
{
  return min(dot(tri_.a, plane_.normal),
             dot(tri_.b, plane_.normal),
             dot(tri_.c, plane_.normal))-plane_.d;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const tri3<T> &tri_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const tri3<T> &tri_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const tri3<T> &tri_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const tri3<T> &tri_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const tri3<T> &tri_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const tri3<T> &tri_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const tri3<T> &tri_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const rect3<T> &rect0_, const rect3<T> &rect1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist (const rect3<T> &rect_, const disc3<T> &disc_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist (const rect3<T> &rect_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const rect3<T> &rect_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const rect3<T> &rect_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const rect3<T> &rect_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const rect3<T> &rect_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const rect3<T> &rect_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const rect3<T> &rect_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const rect3<T> &rect_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const disc3<T> &disc0_, const disc3<T> &disc1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const disc3<T> &disc_, const plane3<T> &plane_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const disc3<T> &disc_, const sphere3<T> &sphere_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const disc3<T> &disc_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const disc3<T> &disc_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const disc3<T> &disc_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const disc3<T> &disc_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const disc3<T> &disc_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const disc3<T> &disc_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const plane3<T> &plane_, const sphere3<T> &sphere_)
{
  return dot(sphere_.pos, plane_.normal)-plane_.d-sphere_.rad;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const plane3<T> &plane_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const plane3<T> &plane_, const capsule3<T> &cap_)
{
  return dot(plane_.normal, cap_.pos-cap_.dir*(sgn_zp(dot(plane_.normal, cap_.dir))*cap_.hlen))-plane_.d-cap_.rad;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const plane3<T> &plane_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const plane3<T> &plane_, const aabox3<T> &aab_)
{
  return dot(aab_.pos+sel_lez(plane_.normal, aab_.hsize, -aab_.hsize), plane_.normal)-plane_.d;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const plane3<T> &plane_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const plane3<T> &plane_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const sphere3<T> &sphere0_, const sphere3<T> &sphere1_)
{
  return norm(sphere1_.pos-sphere0_.pos)-sphere0_.rad-sphere1_.rad;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const sphere3<T> &sphere_, const cylinder3<T> &cyl_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const sphere3<T> &sphere_, const capsule3<T> &cap_)
{
  vec3<T> v=sphere_.pos-cap_.pos;
  return norm(v-cap_.dir*clamp(dot(v, cap_.dir), -cap_.hlen, cap_.hlen))-cap_.rad-sphere_.rad;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const sphere3<T> &sphere_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const sphere3<T> &sphere_, const aabox3<T> &aab_)
{
  return norm(max(abs(sphere_.pos-aab_.pos)-aab_.hsize, typename math<T>::scalar_t(0)))-sphere_.rad;
}
//----

template<typename T>
typename math<T>::scalar_t dist(const sphere3<T> &sphere_, const oobox3<T> &oob_)
{
  return norm(max(abs((sphere_.pos-oob_.pos)*inv_u(oob_.rot))-oob_.hsize, typename math<T>::scalar_t(0)))-sphere_.rad;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const sphere3<T> &sphere_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const cylinder3<T> &cyl0_, const cylinder3<T> &cyl1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const cylinder3<T> &cyl_, const capsule3<T> &cap_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const cylinder3<T> &cyl_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const cylinder3<T> &cyl_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const cylinder3<T> &cyl_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const cylinder3<T> &cyl_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const capsule3<T> &cap0_, const capsule3<T> &cap1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const capsule3<T> &cap_, const cone3<T> &cone_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const capsule3<T> &cap_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const capsule3<T> &cap_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const capsule3<T> &cap_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const cone3<T> &cone0_, const cone3<T> &cone1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const cone3<T> &cone_, const aabox3<T> &aab_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const cone3<T> &cone_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const cone3<T> &cone_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const aabox3<T> &aab0_, const aabox3<T> &aab1_)
{
  return norm2(max(abs(aab0_.pos-aab1_.pos)-aab0_.hsize-aab1_.hsize, typename math<T>::scalar_t(0)));
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const aabox3<T> &aab_, const oobox3<T> &oob_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const aabox3<T> &aab_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const oobox3<T> &oob0_, const oobox3<T> &oob1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const oobox3<T> &oob_, const frustum3<T> &frustum_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----

template<typename T>
typename math<T>::scalar_t dist2(const frustum3<T> &frustum0_, const frustum3<T> &frustum1_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----------------------------------------------------------------------------
