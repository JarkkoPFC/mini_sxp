//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// cubic_spline
//============================================================================
template<typename T>
cubic_spline<T>::cubic_spline()
{
}
//----

template<typename T>
cubic_spline<T>::cubic_spline(typename type<T>::arg a_, typename type<T>::arg b_, typename type<T>::arg c_, typename type<T>::arg d_)
  :a(a_)
  ,b(b_)
  ,c(c_)
  ,d(d_)
{
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE T evaluate(const cubic_spline<T> &s_, typename math<T>::scalar_t t_)
{
  // evaluate spline position at given t
  return madd(madd(madd(s_.a, t_, s_.b), t_, s_.c), t_, s_.d);
}
//----

template<typename T>
PFC_INLINE T evaluate(const cubic_spline<T> &s_, T &tangent_, typename math<T>::scalar_t t_)
{
  // evaluate spline position and tangent at given t
  tangent_=madd(madd(s_.a, typename math<T>::scalar_t(1.5)*t_, s_.b), typename math<T>::scalar_t(2)*t_, s_.c);
  return madd(madd(madd(s_.a, t_, s_.b), t_, s_.c), t_, s_.d);
}
//----

template<typename T> T inv_evaluate(const cubic_spline<T> &ds_, T t_)
{
  PFC_ASSERT_PEDANTIC(t_>=T(0.0) && t_<=T(1.0));
  if(ds_.a)
  {
    // calculate inverse of the cubic spline distance function
    T r3a=rcp(T(3.0)*ds_.a), br3a=ds_.b*r3a;
    T q=ds_.c*r3a-br3a*br3a, q3=q*q*q;
    T r=T(1.5)*r3a*(t_-ds_.d+ds_.c*br3a)-br3a*br3a*br3a;
    T d=q3+r*r;
    if(d>=0)
    {
      // single root
      T s=sqrt(d);
      return cbrt(r+s)+cbrt(r-s)-br3a;
    }

    // triple root (get root in range [0, 1])
    T sth, cth, sq=sqrt(-q);
    sincos(sth, cth, acos(r/(sq*sq*sq))*T(1.0/3.0));
    float z=sq*(math<T>::sqrt3*sth-cth)-br3a;
    static const T epsilon=T(0.00001);
    if(z>=-epsilon && z<=T(1.0)+epsilon)
      return sat(z);
    z=-sq*(math<T>::sqrt3*sth+cth)-br3a;
    if(z>=-epsilon && z<=T(1.0)+epsilon)
      return sat(z);
    return T(2.0)*sq*cth-br3a;
  }

  if(ds_.b)
  {
    // calculate inverse of the quadratic spline distance function
    T sq=ds_.c*ds_.c-T(4.0)*ds_.b*(ds_.d-t_);
    if(sq<=0)
      return 0;
    return (ds_.c-sqrt(sq))/(T(2.0)*ds_.b);
  }

  // for the rest use linear f(t)=t
  return t_;
}
//----------------------------------------------------------------------------

template<typename T>
void make_hermite_spline(cubic_spline<T> &s_, typename type<T>::arg p0_, typename type<T>::arg p1_, typename type<T>::arg t0_, typename type<T>::arg t1_)
{
  // setup Hermite spline coefficients: C=B*P
  //   [ 2 -2  1  1]
  //   [-3  3 -2 -1]
  // B=[ 0  0  1  0]
  //   [ 1  0  0  0]
  typedef typename math<T>::scalar_t scalar_t;
  s_.a=(p0_-p1_)*scalar_t(2.0)+t0_+t1_;
  s_.b=(p1_-p0_)*scalar_t(3.0)-t0_*scalar_t(2.0)-t1_;
  s_.c=t0_;
  s_.d=p0_;
}
//----

template<typename T>
void make_bezier_spline(cubic_spline<T> &s_, typename type<T>::arg p0_, typename type<T>::arg p1_, typename type<T>::arg p2_, typename type<T>::arg p3_)
{
  // setup Bezier spline coefficients: C=B*P
  //   [-1  3 -3  1]
  //   [ 3 -6  3  0]
  // B=[-3  3  0  0]
  //   [ 1  0  0  0]
  typedef typename math<T>::scalar_t scalar_t;
  s_.a=(p1_-p2_)*scalar_t(3.0)-p0_+p3_;
  s_.b=(p0_+p2_)*scalar_t(3.0)-p1_*scalar_t(6.0);
  s_.c=(p1_-p0_)*scalar_t(3.0);
  s_.d=p0_;
}
//----

template<typename T>
void make_bspline(cubic_spline<T> &s_, typename type<T>::arg p0_, typename type<T>::arg p1_, typename type<T>::arg p2_, typename type<T>::arg p3_)
{
  // setup B-spline coefficients: C=B*P
  //       [-1  3 -3  1]
  //       [ 3 -6  3  0]
  // B=1/6*[-3  0  3  0]
  //       [ 1  4  1  0]
  typedef typename math<T>::scalar_t scalar_t;
  s_.a=(p1_-p2_)*scalar_t(0.5)+(p3_-p0_)*scalar_t(1.0/6.0);
  s_.b=(p0_+p2_)*scalar_t(0.5)-p1_;
  s_.c=(p2_-p0_)*scalar_t(0.5);
  s_.d=(p0_+p2_)*scalar_t(1.0/6.0)+p1_*scalar_t(4.0/6.0);
}
//----

template<typename T>
void make_catmull_rom_spline(cubic_spline<T> &s_, typename type<T>::arg p0_, typename type<T>::arg p1_, typename type<T>::arg p2_, typename type<T>::arg p3_)
{
  // setup Catmull-Rom spline coefficients: C=B*P
  //       [-1  3 -3  1]
  //       [ 2 -5  4 -1]
  // B=0.5*[-1  0  1  0]
  //       [ 0  2  0  0]
  typedef typename math<T>::scalar_t scalar_t;
  s_.a=(p1_-p2_)*scalar_t(1.5)+(p3_-p0_)*scalar_t(0.5);
  s_.b=p0_-p1_*scalar_t(2.5)+p2_*scalar_t(2.0)-p3_*scalar_t(0.5);
  s_.c=(p2_-p0_)*scalar_t(0.5);
  s_.d=p1_;
}
//----

template<typename T>
void make_interp_spline(cubic_spline<T> &s_, typename type<T>::arg p0_, typename type<T>::arg p1_, typename type<T>::arg p2_, typename type<T>::arg p3_)
{
  // setup interpolating spline coefficients: C=B*P
  //       [ -9  27 -27  9]
  //       [ 18 -45  36 -9]
  // B=0.5*[-11  18  -9  2]
  //       [  2   0   0  0]
  typedef typename math<T>::scalar_t scalar_t;
  s_.a=(p3_-p0_)*scalar_t(4.5)+(p1_-p2_)*scalar_t(13.5);
  s_.b=p0_*scalar_t(9)-p1_*scalar_t(22.5)+p2_*scalar_t(18)-p3_*scalar_t(4.5);
  s_.c=p1_*scalar_t(9)-p0_*scalar_t(5.5)-p2_*scalar_t(4.5)+p3_;
  s_.d=p0_;
}
//----

template<typename T>
void make_interp_spline(cubic_spline<T> &s_, typename type<T>::arg p0_, typename type<T>::arg p1_, typename type<T>::arg p2_, typename type<T>::arg p3_, typename math<T>::scalar_t t1_, typename math<T>::scalar_t t2_)
{
  // setup interpolating spline coefficients so that:
  //   q(0)=p0_, q(t1_)=p1_, q(t2_)=p2_ and q(1)=p3_
  typedef typename math<T>::scalar_t scalar_t;
  PFC_ASSERT_PEDANTIC_MSG(t1_>0 && t1_<t2_ && t2_<scalar_t(1), ("Invalid control point time values\r\n"));
  scalar_t t12=t1_*t1_, t13=t12*t1_;
  scalar_t t22=t2_*t2_, t23=t22*t2_;
  mat33<scalar_t> inv_t(t22-t2_, t1_-t12, t12*t2_-t1_*t22,
                        t2_-t23, t13-t1_, t1_*t23-t13*t2_,
                        t23-t22, t12-t13, t13*t22-t12*t23);
  inv_t/=inv_t.x.z+inv_t.y.z+inv_t.z.z;
  T p1=p1_-p0_, p2=p2_-p0_, p3=p3_-p0_;
  s_.a=p1*inv_t.x.x+p2*inv_t.x.y+p3*inv_t.x.z;
  s_.b=p1*inv_t.y.x+p2*inv_t.y.y+p3*inv_t.y.z;
  s_.c=p1*inv_t.z.x+p2*inv_t.z.y+p3*inv_t.z.z;
  s_.d=p0_;
}
//----------------------------------------------------------------------------

template<typename T>
void get_hermite_spline_keys(T &p0_, T &p1_, T &t0_, T &t1_, const cubic_spline<T> &s_)
{
  // convert spline to Hermite spline keys
  //   [ 2 -2  1  1]        [0, 0, 0, 1]
  //   [-3  3 -2 -1]        [1, 1, 1, 1]
  // B=[ 0  0  1  0],  B^-1=[0, 0, 1, 0]
  //   [ 1  0  0  0]        [3, 2, 1, 0]
  typedef typename math<T>::scalar_t scalar_t;
  p0_=s_.d;
  p1_=s_.a+s_.b+s_.c+s_.d;
  t0_=s_.c;
  t1_=s_.a*scalar_t(3.0)+s_.b*scalar_t(2.0)+s_.c;
}
//----

template<typename T>
void get_bezier_spline_keys(T &p0_, T &p1_, T &p2_, T &p3_, const cubic_spline<T> &s_)
{
  // convert spline to Bezier spline keys
  //   [-1  3 -3  1]       [0,   0,   0, 1]
  //   [ 3 -6  3  0]       [0,   0, 1/3, 1]
  // B=[-3  3  0  0], B^-1=[0, 1/3, 2/3, 1]
  //   [ 1  0  0  0]       [1,   1,   1, 1]
  typedef typename math<T>::scalar_t scalar_t;
  p0_=s_.d;
  p1_=s_.c*scalar_t(1.0/3.0)+s_.d;
  p2_=s_.b*scalar_t(1.0/3.0)+s_.c*scalar_t(2.0/3.0)+s_.d;
  p3_=s_.a+s_.b+s_.c+s_.d;
}
//----

template<typename T>
void get_bspline_keys(T &p0_, T &p1_, T &p2_, T &p3_, const cubic_spline<T> &s_)
{
  // convert spline to B-spline keys
  //       [-1  3 -3  1]       [0,  2/3, -1, 1]
  //       [ 3 -6  3  0]       [0, -1/3,  0, 1]
  // B=1/6*[-3  0  3  0]. B^-1=[0,  2/3,  1, 1]
  //       [ 1  4  1  0]       [6, 11/3,  2, 1]
  typedef typename math<T>::scalar_t scalar_t;
  p0_=s_.b*scalar_t(2.0/3.0)-s_.c+s_.d;
  p1_=s_.d-s_.b*scalar_t(1.0/3.0);
  p2_=s_.b*scalar_t(2.0/3.0)+s_.c+s_.d;
  p3_=s_.a*scalar_t(6.0)+s_.b*scalar_t(11.0/3.0)+s_.c*scalar_t(2.0)+s_.d;
}
//----

template<typename T>
void get_catmull_rom_spline_keys(T &p0_, T &p1_, T &p2_, T &p3_, const cubic_spline<T> &s_)
{
  // convert spline to Catmull-Rom spline keys
  //       [-1  3 -3  1]       [1, 1, -1, 1]
  //       [ 2 -5  4 -1]       [0, 0,  0, 1]
  // B=0.5*[-1  0  1  0], B^-1=[1, 1,  1, 1]
  //       [ 0  2  0  0]       [6, 4,  2, 1]
  typedef typename math<T>::scalar_t scalar_t;
  p0_=s_.a+s_.b-s_.c+s_.d;
  p1_=s_.d;
  p2_=s_.a+s_.b+s_.c+s_.d;
  p3_=s_.a*scalar_t(6.0)+s_.b*scalar_t(4.0)+s_.c*scalar_t(2.0)+s_.d;
}
//----

template<typename T>
void get_interp_spline_keys(T &p0_, T &p1_, T &p2_, T &p3_, const cubic_spline<T> &s_)
{
  // convert spline to interpolating spline keys
  //       [ -9  27 -27  9]       [   0,   0,   0, 1]
  //       [ 18 -45  36 -9]       [1/27, 1/9, 1/3, 1]
  // B=0.5*[-11  18  -9  2], B^-1=[2/27, 2/9, 2/3, 1]
  //       [  2   0   0  0]       [   1,   1,   1, 1]
  typedef typename math<T>::scalar_t scalar_t;
  p0_=s_.d;
  p1_=s_.a*scalar_t(1.0/27.0)+s_.b*scalar_t(1.0/9.0)+s_.c*scalar_t(1.0/3.0)+s_.d;
  p2_=s_.a*scalar_t(2.0/27.0)+s_.b*scalar_t(2.0/9.0)+s_.c*scalar_t(2.0/3.0)+s_.d;
  p3_=s_.a+s_.b+s_.c+s_.d;
}
//----------------------------------------------------------------------------


//============================================================================
// bicubic_patch
//============================================================================
template<typename T>
bicubic_patch<T>::bicubic_patch()
{
}
//----

template<typename T>
bicubic_patch<T>::bicubic_patch(const T coeffs_[16])
{
  for(unsigned i=0; i<16; ++i)
    coeffs[i]=coeffs_[i];
}
//----------------------------------------------------------------------------

template<typename T>
T evaluate(const bicubic_patch<T> &p_, typename math<T>::scalar_t s_, typename math<T>::scalar_t t_)
{
  // evaluate the patch position at [s_, t_]
  return (( ((((p_.coeffs[0]*s_)+p_.coeffs[1])*s_+p_.coeffs[2])*s_+p_.coeffs[3])*t_
           +((((p_.coeffs[4]*s_)+p_.coeffs[5])*s_+p_.coeffs[6])*s_+p_.coeffs[7]))*t_
           +((((p_.coeffs[8]*s_)+p_.coeffs[9])*s_+p_.coeffs[10])*s_+p_.coeffs[11]))*t_
           +((((p_.coeffs[12]*s_)+p_.coeffs[13])*s_+p_.coeffs[14])*s_+p_.coeffs[15]);
}
//----------------------------------------------------------------------------

template<typename T>
void make_hermite_patch(bicubic_patch<T> &p_, const T cm_[16])
{
  // setup Hermite patch coefficients: C=B*P*transpose(B)
  //   [ 2 -2  1  1]
  //   [-3  3 -2 -1]
  // B=[ 0  0  1  0]
  //   [ 1  0  0  0]
  typedef typename math<T>::scalar_t scalar_t;
  const T c[8]={(cm_[0]-cm_[4])*scalar_t(2.0)+cm_[8]+cm_[12],
                (cm_[1]-cm_[5])*scalar_t(2.0)+cm_[9]+cm_[13],
                (cm_[2]-cm_[6])*scalar_t(2.0)+cm_[10]+cm_[14],
                (cm_[3]-cm_[7])*scalar_t(2.0)+cm_[11]+cm_[15],
                (cm_[4]-cm_[0])*scalar_t(3.0)-cm_[8]*scalar_t(2.0)-cm_[12],
                (cm_[5]-cm_[1])*scalar_t(3.0)-cm_[9]*scalar_t(2.0)-cm_[13],
                (cm_[6]-cm_[2])*scalar_t(3.0)-cm_[10]*scalar_t(2.0)-cm_[14],
                (cm_[7]-cm_[3])*scalar_t(3.0)-cm_[11]*scalar_t(2.0)-cm_[15]};
  p_.coeffs[0]=(c[0]-c[1])*scalar_t(2.0)+c[2]+c[3];
  p_.coeffs[1]=(c[1]-c[0])*scalar_t(3.0)-c[2]*scalar_t(2.0)-c[3];
  p_.coeffs[2]=c[2];
  p_.coeffs[3]=c[0];
  p_.coeffs[4]=(c[4]-c[5])*scalar_t(2.0)+c[6]+c[7];
  p_.coeffs[5]=(c[5]-c[4])*scalar_t(3.0)-c[6]*scalar_t(2.0)-c[7];
  p_.coeffs[6]=c[6];
  p_.coeffs[7]=c[4];
  p_.coeffs[8]=(cm_[8]-cm_[9])*scalar_t(2.0)+cm_[10]+cm_[11];
  p_.coeffs[9]=(cm_[9]-cm_[8])*scalar_t(3.0)-cm_[10]*scalar_t(2.0)-cm_[11];
  p_.coeffs[10]=cm_[10];
  p_.coeffs[11]=cm_[8];
  p_.coeffs[12]=(cm_[0]-cm_[1])*scalar_t(2.0)+cm_[2]+cm_[3];
  p_.coeffs[13]=(cm_[1]-cm_[0])*scalar_t(3.0)-cm_[2]*scalar_t(2.0)-cm_[3];
  p_.coeffs[14]=cm_[2];
  p_.coeffs[15]=cm_[0];
}
//----

template<typename T>
void make_bezier_patch(bicubic_patch<T> &p_, const T cpnt_[16])
{
  // setup Bezier bicubic patch coefficients: C=B*P*transpose(B)
  //   [-1  3 -3  1]
  //   [ 3 -6  3  0]
  // B=[-3  3  0  0]
  //   [ 1  0  0  0]
  typedef typename math<T>::scalar_t scalar_t;
  const T c[12]={(cpnt_[4]-cpnt_[8])*scalar_t(3.0)+cpnt_[12]-cpnt_[0],
                 (cpnt_[5]-cpnt_[9])*scalar_t(3.0)+cpnt_[13]-cpnt_[1],
                 (cpnt_[6]-cpnt_[10])*scalar_t(3.0)+cpnt_[14]-cpnt_[2],
                 (cpnt_[7]-cpnt_[11])*scalar_t(3.0)+cpnt_[15]-cpnt_[3],
                 (cpnt_[0]+cpnt_[8])*scalar_t(3.0)-cpnt_[4]*scalar_t(6.0),
                 (cpnt_[1]+cpnt_[9])*scalar_t(3.0)-cpnt_[5]*scalar_t(6.0),
                 (cpnt_[2]+cpnt_[10])*scalar_t(3.0)-cpnt_[6]*scalar_t(6.0),
                 (cpnt_[3]+cpnt_[11])*scalar_t(3.0)-cpnt_[7]*scalar_t(6.0),
                 (cpnt_[4]-cpnt_[0])*scalar_t(3.0),
                 (cpnt_[5]-cpnt_[1])*scalar_t(3.0),
                 (cpnt_[6]-cpnt_[2])*scalar_t(3.0),
                 (cpnt_[7]-cpnt_[3])*scalar_t(3.0)};
  p_.coeffs[0]=(c[1]-c[2])*scalar_t(3.0)+c[3]-c[0];
  p_.coeffs[1]=(c[0]+c[2])*scalar_t(3.0)-c[1]*scalar_t(6.0);
  p_.coeffs[2]=(c[1]-c[0])*scalar_t(3.0);
  p_.coeffs[3]=c[0];
  p_.coeffs[4]=(c[5]-c[6])*scalar_t(3.0)+c[7]-c[4];
  p_.coeffs[5]=(c[4]+c[6])*scalar_t(3.0)-c[5]*scalar_t(6.0);
  p_.coeffs[6]=(c[5]-c[4])*scalar_t(3.0);
  p_.coeffs[7]=c[4];
  p_.coeffs[8]=(c[9]-c[10])*scalar_t(3.0)+c[11]-c[8];
  p_.coeffs[9]=(c[8]+c[10])*scalar_t(3.0)-c[9]*scalar_t(6.0);
  p_.coeffs[10]=(c[9]-c[8])*scalar_t(3.0);
  p_.coeffs[11]=c[8];
  p_.coeffs[12]=(cpnt_[1]-cpnt_[2])*scalar_t(3.0)+cpnt_[3]-cpnt_[0];
  p_.coeffs[13]=(cpnt_[0]+cpnt_[2])*scalar_t(3.0)-cpnt_[1]*scalar_t(6.0);
  p_.coeffs[14]=(cpnt_[1]-cpnt_[0])*scalar_t(3.0);
  p_.coeffs[15]=cpnt_[0];
}
//----

template<typename T>
void make_bspline_patch(bicubic_patch<T> &p_, const T cpnt_[16])
{
  // setup B-spline bicubic patch coefficients: C=B*P*transpose(B)
  //       [-1  3 -3  1]
  //       [ 3 -6  3  0]
  // B=1/6*[-3  0  3  0]
  //       [ 1  4  1  0]
  typedef typename math<T>::scalar_t scalar_t;
  const T c[16]={(cpnt_[4]-cpnt_[8])*scalar_t(3.0)+cpnt_[12]-cpnt_[0],
                 (cpnt_[5]-cpnt_[9])*scalar_t(3.0)+cpnt_[13]-cpnt_[1],
                 (cpnt_[6]-cpnt_[10])*scalar_t(3.0)+cpnt_[14]-cpnt_[2],
                 (cpnt_[7]-cpnt_[11])*scalar_t(3.0)+cpnt_[15]-cpnt_[3],
                 (cpnt_[0]+cpnt_[8])*scalar_t(3.0)-cpnt_[4]*scalar_t(6.0),
                 (cpnt_[1]+cpnt_[9])*scalar_t(3.0)-cpnt_[5]*scalar_t(6.0),
                 (cpnt_[2]+cpnt_[10])*scalar_t(3.0)-cpnt_[6]*scalar_t(6.0),
                 (cpnt_[3]+cpnt_[11])*scalar_t(3.0)-cpnt_[7]*scalar_t(6.0),
                 (cpnt_[8]-cpnt_[0])*scalar_t(3.0),
                 (cpnt_[9]-cpnt_[1])*scalar_t(3.0),
                 (cpnt_[10]-cpnt_[2])*scalar_t(3.0),
                 (cpnt_[11]-cpnt_[3])*scalar_t(3.0),
                 cpnt_[0]+cpnt_[4]*scalar_t(4.0)+cpnt_[8],
                 cpnt_[1]+cpnt_[5]*scalar_t(4.0)+cpnt_[9],
                 cpnt_[2]+cpnt_[6]*scalar_t(4.0)+cpnt_[10],
                 cpnt_[3]+cpnt_[7]*scalar_t(4.0)+cpnt_[11]};
  p_.coeffs[0]=(c[1]-c[2])*scalar_t(3.0/36.0)+(c[3]-c[0])*scalar_t(1.0/36.0);
  p_.coeffs[1]=(c[0]+c[2])*scalar_t(3.0/36.0)-c[1]*scalar_t(6.0/36.0);
  p_.coeffs[2]=(c[2]-c[0])*scalar_t(3.0/36.0);
  p_.coeffs[3]=(c[0]+c[2])*scalar_t(1.0/36.0)+c[1]*scalar_t(4.0/36.0);
  p_.coeffs[4]=(c[5]-c[6])*scalar_t(3.0/36.0)+(c[7]-c[4])*scalar_t(1.0/36.0);
  p_.coeffs[5]=(c[4]+c[6])*scalar_t(3.0/36.0)-c[5]*scalar_t(6.0/36.0);
  p_.coeffs[6]=(c[6]-c[4])*scalar_t(3.0/36.0);
  p_.coeffs[7]=(c[4]+c[6])*scalar_t(1.0/36.0)+c[5]*scalar_t(4.0/36.0);
  p_.coeffs[8]=(c[9]-c[10])*scalar_t(3.0/36.0)+(c[11]-c[8])*scalar_t(1.0/36.0);
  p_.coeffs[9]=(c[8]+c[10])*scalar_t(3.0/36.0)-c[9]*scalar_t(6.0/36.0);
  p_.coeffs[10]=(c[10]-c[8])*scalar_t(3.0/36.0);
  p_.coeffs[11]=(c[8]+c[10])*scalar_t(1.0/36.0)+c[9]*scalar_t(4.0/36.0);
  p_.coeffs[12]=(c[13]-c[14])*scalar_t(3.0/36.0)+(c[15]-c[12])*scalar_t(1.0/36.0);
  p_.coeffs[13]=(c[12]+c[14])*scalar_t(3.0/36.0)-c[13]*scalar_t(6.0/36.0);
  p_.coeffs[14]=(c[14]-c[12])*scalar_t(3.0/36.0);
  p_.coeffs[15]=(c[12]+c[14])*scalar_t(1.0/36.0)+c[13]*scalar_t(4.0/36.0);
}
//----

template<typename T>
void make_catmull_rom_patch(bicubic_patch<T> &p_, const T cpnt_[16])
{
  // setup Catmull-Rom bicubic patch coefficients: C=B*P*transpose(B)
  //       [-1  3 -3  1]
  //       [ 2 -5  4 -1]
  // B=0.5*[-1  0  1  0]
  //       [ 0  2  0  0]
  typedef typename math<T>::scalar_t scalar_t;
  const T c[16]={(cpnt_[4]-cpnt_[8])*scalar_t(3.0)+cpnt_[12]-cpnt_[0],
                 (cpnt_[5]-cpnt_[9])*scalar_t(3.0)+cpnt_[13]-cpnt_[1],
                 (cpnt_[6]-cpnt_[10])*scalar_t(3.0)+cpnt_[14]-cpnt_[2],
                 (cpnt_[7]-cpnt_[11])*scalar_t(3.0)+cpnt_[15]-cpnt_[3],
                 cpnt_[0]*scalar_t(2.0)-cpnt_[4]*scalar_t(5.0)+cpnt_[8]*scalar_t(4.0)-cpnt_[12],
                 cpnt_[1]*scalar_t(2.0)-cpnt_[5]*scalar_t(5.0)+cpnt_[9]*scalar_t(4.0)-cpnt_[13],
                 cpnt_[2]*scalar_t(2.0)-cpnt_[6]*scalar_t(5.0)+cpnt_[10]*scalar_t(4.0)-cpnt_[14],
                 cpnt_[3]*scalar_t(2.0)-cpnt_[7]*scalar_t(5.0)+cpnt_[11]*scalar_t(4.0)-cpnt_[15],
                 cpnt_[8]-cpnt_[0],
                 cpnt_[9]-cpnt_[1],
                 cpnt_[10]-cpnt_[2],
                 cpnt_[11]-cpnt_[3],
                 cpnt_[4]*scalar_t(2.0),
                 cpnt_[5]*scalar_t(2.0),
                 cpnt_[6]*scalar_t(2.0),
                 cpnt_[7]*scalar_t(2.0)};
  p_.coeffs[0]=(c[1]-c[2])*scalar_t(3.0/4.0)+(c[3]-c[0])*scalar_t(0.25);
  p_.coeffs[1]=c[0]*scalar_t(0.5)-c[1]*scalar_t(5.0/4.0)+c[2]-c[3]*scalar_t(0.25);
  p_.coeffs[2]=(c[2]-c[0])*scalar_t(0.25);
  p_.coeffs[3]=c[1]*scalar_t(0.5);
  p_.coeffs[4]=(c[5]-c[6])*scalar_t(3.0/4.0)+(c[7]-c[4])*scalar_t(0.25);
  p_.coeffs[5]=c[4]*scalar_t(0.5)-c[5]*scalar_t(5.0/4.0)+c[6]-c[7]*scalar_t(0.25);
  p_.coeffs[6]=(c[6]-c[4])*scalar_t(0.25);
  p_.coeffs[7]=c[5]*scalar_t(0.5);
  p_.coeffs[8]=(c[9]-c[10])*scalar_t(3.0/4.0)+(c[11]-c[8])*scalar_t(0.25);
  p_.coeffs[9]=c[8]*scalar_t(0.5)-c[9]*scalar_t(5.0/4.0)+c[10]-c[11]*scalar_t(0.25);
  p_.coeffs[10]=(c[10]-c[8])*scalar_t(0.25);
  p_.coeffs[11]=c[9]*scalar_t(0.5);
  p_.coeffs[12]=(c[13]-c[14])*scalar_t(3.0/4.0)+(c[15]-c[12])*scalar_t(0.25);
  p_.coeffs[13]=c[12]*scalar_t(0.5)-c[13]*scalar_t(5.0/4.0)+c[14]-c[15]*scalar_t(0.25);
  p_.coeffs[14]=(c[14]-c[12])*scalar_t(0.25);
  p_.coeffs[15]=c[13]*scalar_t(0.5);
}
//----

template<typename T>
void make_interp_patch(bicubic_patch<T> &p_, const T cpnt_[16])
{
  // setup interpolating bicubic patch coefficients: C=B*P*transpose(B)
  //       [ -9  27 -27  9]
  //       [ 18 -45  36 -9]
  // B=0.5*[-11  18  -9  2]
  //       [  2   0   0  0]
  typedef typename math<T>::scalar_t scalar_t;
  const T c[16]={(cpnt_[12]-cpnt_[0])*scalar_t(9.0)+(cpnt_[4]-cpnt_[8])*scalar_t(27.0),
                 (cpnt_[13]-cpnt_[1])*scalar_t(9.0)+(cpnt_[5]-cpnt_[9])*scalar_t(27.0),
                 (cpnt_[14]-cpnt_[2])*scalar_t(9.0)+(cpnt_[6]-cpnt_[10])*scalar_t(27.0),
                 (cpnt_[15]-cpnt_[3])*scalar_t(9.0)+(cpnt_[7]-cpnt_[11])*scalar_t(27.0),
                 cpnt_[0]*scalar_t(18.0)+cpnt_[4]*scalar_t(-45.0)+cpnt_[8]*scalar_t(36.0)+cpnt_[12]*scalar_t(-9.0),
                 cpnt_[1]*scalar_t(18.0)+cpnt_[5]*scalar_t(-45.0)+cpnt_[9]*scalar_t(36.0)+cpnt_[13]*scalar_t(-9.0),
                 cpnt_[2]*scalar_t(18.0)+cpnt_[6]*scalar_t(-45.0)+cpnt_[10]*scalar_t(36.0)+cpnt_[14]*scalar_t(-9.0),
                 cpnt_[3]*scalar_t(18.0)+cpnt_[7]*scalar_t(-45.0)+cpnt_[11]*scalar_t(36.0)+cpnt_[15]*scalar_t(-9.0),
                 cpnt_[0]*scalar_t(-11.0)+cpnt_[4]*scalar_t(18.0)+cpnt_[8]*scalar_t(-9.0)+cpnt_[12]*scalar_t(2.0),
                 cpnt_[1]*scalar_t(-11.0)+cpnt_[5]*scalar_t(18.0)+cpnt_[9]*scalar_t(-9.0)+cpnt_[13]*scalar_t(2.0),
                 cpnt_[2]*scalar_t(-11.0)+cpnt_[6]*scalar_t(18.0)+cpnt_[10]*scalar_t(-9.0)+cpnt_[14]*scalar_t(2.0),
                 cpnt_[3]*scalar_t(-11.0)+cpnt_[7]*scalar_t(18.0)+cpnt_[11]*scalar_t(-9.0)+cpnt_[15]*scalar_t(2.0),
                 cpnt_[0]*scalar_t(2.0),
                 cpnt_[1]*scalar_t(2.0),
                 cpnt_[2]*scalar_t(2.0),
                 cpnt_[3]*scalar_t(2.0)};
  p_.coeffs[0]=(c[3]-c[0])*scalar_t(9.0/4.0)+(c[1]-c[2])*scalar_t(27.0/4.0);
  p_.coeffs[1]=c[0]*scalar_t(18.0/4.0)+c[1]*scalar_t(-45.0/4.0)+c[2]*scalar_t(36.0/4.0)+c[3]*scalar_t(-9.0/4.0);
  p_.coeffs[2]=c[0]*scalar_t(-11.0/4.0)+c[1]*scalar_t(18.0/4.0)+c[2]*scalar_t(-9.0/4.0)+c[3]*scalar_t(2.0/4.0);
  p_.coeffs[3]=c[0]*scalar_t(2.0/4.0);
  p_.coeffs[4]=(c[7]-c[4])*scalar_t(9.0/4.0)+(c[5]-c[6])*scalar_t(27.0/4.0);
  p_.coeffs[5]=c[4]*scalar_t(18.0/4.0)+c[5]*scalar_t(-45.0/4.0)+c[6]*scalar_t(36.0/4.0)+c[7]*scalar_t(-9.0/4.0);
  p_.coeffs[6]=c[4]*scalar_t(-11.0/4.0)+c[5]*scalar_t(18.0/4.0)+c[6]*scalar_t(-9.0/4.0)+c[7]*scalar_t(2.0/4.0);
  p_.coeffs[7]=c[4]*scalar_t(2.0/4.0);
  p_.coeffs[8]=(c[11]-c[8])*scalar_t(9.0/4.0)+(c[9]-c[10])*scalar_t(27.0/4.0);
  p_.coeffs[9]=c[8]*scalar_t(18.0/4.0)+c[9]*scalar_t(-45.0/4.0)+c[10]*scalar_t(36.0/4.0)+c[11]*scalar_t(-9.0/4.0);
  p_.coeffs[10]=c[8]*scalar_t(-11.0/4.0)+c[9]*scalar_t(18.0/4.0)+c[10]*scalar_t(-9.0/4.0)+c[11]*scalar_t(2.0/4.0);
  p_.coeffs[11]=c[8]*scalar_t(2.0/4.0);
  p_.coeffs[12]=(c[15]-c[12])*scalar_t(9.0/4.0)+(c[13]-c[14])*scalar_t(27.0/4.0);
  p_.coeffs[13]=c[12]*scalar_t(18.0/4.0)+c[13]*scalar_t(-45.0/4.0)+c[14]*scalar_t(36.0/4.0)+c[15]*scalar_t(-9.0/4.0);
  p_.coeffs[14]=c[12]*scalar_t(-11.0/4.0)+c[13]*scalar_t(18.0/4.0)+c[14]*scalar_t(-9.0/4.0)+c[15]*scalar_t(2.0/4.0);
  p_.coeffs[15]=c[12]*scalar_t(2.0/4.0);
}
//----------------------------------------------------------------------------


//============================================================================
// spline_fit_constraint_vec
//============================================================================
template<class T>
spline_fit_constraint_vec<T>::spline_fit_constraint_vec(scalar_t input_curvature_tolerance_deg_,
                                                        scalar_t input_velocity_tolerance_,
                                                        scalar_t output_distance_tolerance_,
                                                        scalar_t tangent_velocity_percent_)
{
  // initialize the constraint
  init_constraints(input_curvature_tolerance_deg_, input_velocity_tolerance_, output_distance_tolerance_, tangent_velocity_percent_);
  init_buffers(0, 0, 0);
}
//----

template<class T>
spline_fit_constraint_vec<T>::spline_fit_constraint_vec(cubic_spline<T> *spline_buffer_,
                                                        unsigned *spline_length_buffer_,
                                                        unsigned buffer_capacity_,
                                                        scalar_t input_curvature_tolerance_deg_,
                                                        scalar_t input_velocity_tolerance_,
                                                        scalar_t output_distance_tolerance_,
                                                        scalar_t tangent_velocity_percent_)
{
  // initialize the constraint
  PFC_ASSERT_MSG(!buffer_capacity_ || spline_buffer_, ("Spline buffer not defined\r\n"));
  PFC_ASSERT_MSG(!buffer_capacity_ || spline_length_buffer_, ("Spline length buffer not defined\r\n"));
  init_constraints(input_curvature_tolerance_deg_, input_velocity_tolerance_, output_distance_tolerance_, tangent_velocity_percent_);
  init_buffers(spline_buffer_, spline_length_buffer_, buffer_capacity_);
}
//----

template<class T>
void spline_fit_constraint_vec<T>::init_buffers(cubic_spline<T> *spline_buffer_,
                                                unsigned *spline_length_buffer_,
                                                unsigned buffer_capacity_)
{
  // initialize constraint buffers
  m_spline_buffer=spline_buffer_;
  m_spline_length_buffer=spline_length_buffer_;
  m_buffer_capacity=buffer_capacity_;
}
//----------------------------------------------------------------------------

template<class T>
bool spline_fit_constraint_vec<T>::input_constraints(const T&, const T &prev_, const T &key_, const T &next_) const
{
  // test if input key is within the constraints in relation to other keys
  T in=key_-prev_;
  T out=next_-key_;
  scalar_t norm_in=norm(in);
  scalar_t norm_out=norm(out);
  if(norm_in<m_tolerance_input_velocity || norm_out<m_tolerance_input_velocity)
    return true;
  return dot(in, out)>=norm_in*norm_out*m_tolerance_input_curvature;
}
//----

template<class T>
bool spline_fit_constraint_vec<T>::spline_constraints(const T &prev_, const T &key_, const cubic_spline<T> &s_, scalar_t t_) const
{
  // test if the input key is within the distance constraints
  T v=evaluate(s_, t_);
  return norm2(key_-v)<=m_tolerance_sqr_distance;
}
//----

template<class T>
bool spline_fit_constraint_vec<T>::add_spline(const cubic_spline<T> &s_, unsigned spline_length_)
{
  // add spline to the buffer
  if(!m_buffer_capacity)
    return false;
  *m_spline_buffer++=s_;
  *m_spline_length_buffer++=spline_length_;
  --m_buffer_capacity;
  return true;
}
//----------------------------------------------------------------------------

template<class T>
bool spline_fit_constraint_vec<T>::tangent_constraints(const T &in_, const T &out_) const
{
  // test if input key is within the constraints in relation to other keys
  scalar_t norm_in=norm(in_);
  scalar_t norm_out=norm(out_);
  if(norm_in<m_tolerance_input_velocity && norm_out<m_tolerance_input_velocity)
    return true;
  return    dot(in_, out_)>=norm_in*norm_out*m_tolerance_input_curvature
         && abs(norm_in-norm_out)<min(norm_in, norm_out)*m_tolerance_tangent_velocity_factor;
}
//----------------------------------------------------------------------------

template<class T>
void spline_fit_constraint_vec<T>::init_constraints(scalar_t input_curvature_tolerance_deg_,
                                                    scalar_t input_velocity_tolerance_,
                                                    scalar_t output_distance_tolerance_,
                                                    scalar_t tangent_velocity_percent_)
{
  // initialize constraint values
  PFC_ASSERT_MSG(input_curvature_tolerance_deg_<=scalar_t(180.0), ("Input curvature tolerance (%f) must be in range [0, 180]\r\n", input_curvature_tolerance_deg_));
  PFC_ASSERT_MSG(input_velocity_tolerance_>=0, ("Input velocity tolerance (%f) must be greater than or equal to zero\r\n", input_velocity_tolerance_));
  PFC_ASSERT_MSG(output_distance_tolerance_>0, ("Output distance tolerance (%f) must be greater than 0\r\n", output_distance_tolerance_));
  m_tolerance_input_curvature=cos(input_curvature_tolerance_deg_*math<T>::deg_to_rad);
  m_tolerance_input_velocity=input_velocity_tolerance_;
  m_tolerance_sqr_distance=sqr(output_distance_tolerance_);
  m_tolerance_tangent_velocity_factor=tangent_velocity_percent_*scalar_t(0.01);
}
//----------------------------------------------------------------------------


//============================================================================
// spline_fit_constraint_quat
//============================================================================
template<class T>
spline_fit_constraint_quat<T>::spline_fit_constraint_quat(scalar_t input_curvature_tolerance_deg_,
                                                          scalar_t input_angular_velocity_tolerance_,
                                                          scalar_t output_angle_tolerance_deg_,
                                                          scalar_t tangent_angular_velocity_percent_)
{
  init_constraints(input_curvature_tolerance_deg_, input_angular_velocity_tolerance_, output_angle_tolerance_deg_, tangent_angular_velocity_percent_);
  init_buffers(0, 0, 0);
}
//----

template<class T>
spline_fit_constraint_quat<T>::spline_fit_constraint_quat(cubic_spline<T> *spline_buffer_,
                                                          unsigned *spline_length_buffer_,
                                                          unsigned buffer_capacity_,
                                                          scalar_t input_curvature_tolerance_deg_,
                                                          scalar_t input_angular_velocity_tolerance_,
                                                          scalar_t output_angle_tolerance_deg_,
                                                          scalar_t tangent_angular_velocity_percent_)
{
  // initialize the constraint
  PFC_ASSERT_MSG(!buffer_capacity_ || spline_buffer_, ("Spline buffer not defined\r\n"));
  PFC_ASSERT_MSG(!buffer_capacity_ || spline_length_buffer_, ("Spline length buffer not defined\r\n"));
  init_constraints(input_curvature_tolerance_deg_, input_angular_velocity_tolerance_, output_angle_tolerance_deg_, tangent_angular_velocity_percent_);
  init_buffers(spline_buffer_, spline_length_buffer_, buffer_capacity_);
}
//----

template<class T>
void spline_fit_constraint_quat<T>::init_buffers(cubic_spline<T> *spline_buffer_, unsigned *spline_length_buffer_, unsigned buffer_capacity_)
{
  // initialize constraint buffers
  m_spline_buffer=spline_buffer_;
  m_spline_length_buffer=spline_length_buffer_;
  m_buffer_capacity=buffer_capacity_;
}
//----------------------------------------------------------------------------

template<class T>
bool spline_fit_constraint_quat<T>::input_constraints(const T&, const T &prev_, const T &key_, const T &next_) const
{
  // test if input key is within the constraints in relation to other keys
  T in=inv_u(prev_)*key_;
  T out=inv_u(key_)*next_;
  scalar_t norm_in=norm(vec(in));
  scalar_t norm_out=norm(vec(out));
  if(norm_in<m_tolerance_input_angular_velocity || norm_out<m_tolerance_input_angular_velocity)
    return true;
  return dot(in, out)>=m_tolerance_input_curvature;
}
//----

template<class T>
bool spline_fit_constraint_quat<T>::spline_constraints(const T &prev_, const T &key_, const cubic_spline<T> &s_, scalar_t t_) const
{
  // test if the input key is within the rotation constraints
  T v=evaluate(s_, t_);
  return dot(v, key_)>=norm(v)*m_tolerance_output_angle;
}
//----

template<class T>
bool spline_fit_constraint_quat<T>::add_spline(const cubic_spline<T> &s_, unsigned spline_length_)
{
  // add spline to the buffer
  if(!m_buffer_capacity)
    return false;
  *m_spline_buffer++=s_;
  *m_spline_length_buffer++=spline_length_;
  --m_buffer_capacity;
  return true;
}
//----------------------------------------------------------------------------

template<class T>
bool spline_fit_constraint_quat<T>::tangent_constraints(const T &in_, const T &out_) const
{
  // test if input key is within the constraints in relation to other keys
  scalar_t norm_in=norm(in_);
  scalar_t norm_out=norm(out_);
  if(norm_in<m_tolerance_input_angular_velocity && norm_out<m_tolerance_input_angular_velocity)
    return true;
  return    dot(in_, out_)>=norm_in*norm_out*m_tolerance_input_curvature
         && abs(norm_in-norm_out)<min(norm_in, norm_out)*m_tolerance_tangent_angular_velocity_factor;
}
//----------------------------------------------------------------------------

template<class T>
void spline_fit_constraint_quat<T>::init_constraints(scalar_t input_curvature_tolerance_deg_,
                                                     scalar_t input_angular_velocity_tolerance_,
                                                     scalar_t output_angle_tolerance_deg_,
                                                     scalar_t tangent_angular_velocity_percent_)
{
  // initialize constraint values
  PFC_ASSERT_MSG(input_curvature_tolerance_deg_>=0 && input_curvature_tolerance_deg_<=scalar_t(180.0), ("Input curvature tolerance (%f) must be in range [0, 180]\r\n", input_curvature_tolerance_deg_));
  PFC_ASSERT_MSG(input_angular_velocity_tolerance_>=0, ("Input angular velocity tolerance (%f) must be greater than or equal to zero\r\n", input_angular_velocity_tolerance_));
  PFC_ASSERT_MSG(output_angle_tolerance_deg_>=0 && output_angle_tolerance_deg_<=scalar_t(180.0), ("Output angle tolerance (%f) must be in range [0, 180]\r\n", output_angle_tolerance_deg_));
  m_tolerance_input_curvature=cos(input_curvature_tolerance_deg_*math<T>::deg_to_rad);
  m_tolerance_input_angular_velocity=input_angular_velocity_tolerance_;
  m_tolerance_output_angle=cos(output_angle_tolerance_deg_*math<T>::deg_to_rad);
  m_tolerance_tangent_angular_velocity_factor=tangent_angular_velocity_percent_*scalar_t(0.01);
}
//----------------------------------------------------------------------------


//============================================================================
// fit_spline
//============================================================================
namespace priv
{
  template<typename T, typename K>
  PFC_INLINE typename math<T>::scalar_t setup_spline_from_mid_keys(cubic_spline<T> &spline_, const K &keys_iterator_, unsigned first_idx_, unsigned last_idx_)
  {
    // setup spline which passes through first, last and two middle keys
    typedef typename math<T>::scalar_t scalar_t;
    scalar_t ki_diff=scalar_t(last_idx_-first_idx_);
    scalar_t dt=scalar_t(1.0)/ki_diff;
    unsigned idx=unsigned(ki_diff*scalar_t(1.0/3.0)+scalar_t(0.5));
    scalar_t t=dt*scalar_t(idx);
    make_interp_spline(spline_, keys_iterator_[first_idx_], keys_iterator_[first_idx_+idx], keys_iterator_[last_idx_-idx], keys_iterator_[last_idx_], t, scalar_t(1.0)-t);
    return dt;
  }
} // namespace priv
//----

template<typename T, typename K, class Constraint>
unsigned fit_spline(K keys_iterator_, unsigned num_keys_, Constraint &c_, unsigned max_cubic_spline_length_)
{
  /*todo: fix to conform spline input constraints for the first 4 keys within each spline segment*/
  // setup initial spline from the first 4 input keys
  if(num_keys_<2)
    return 0;
  typedef typename math<T>::scalar_t scalar_t;
  cubic_spline<T> spline;
  if(num_keys_>3)
    make_interp_spline(spline, keys_iterator_[0], keys_iterator_[1], keys_iterator_[2], keys_iterator_[3]);

  // iteratively fit spline until there are no input keys left
  unsigned num_spline_keys=0;
  unsigned first_key_idx=0;
  unsigned test_key_idx=4;
  scalar_t dt=scalar_t(1.0/3.0);
  while(test_key_idx<num_keys_)
  {
    // test if input key is within allowed input constraints
    if(   (!max_cubic_spline_length_ || test_key_idx-first_key_idx-1<max_cubic_spline_length_)
       && c_.input_constraints(keys_iterator_[first_key_idx], keys_iterator_[test_key_idx-2], keys_iterator_[test_key_idx-1], keys_iterator_[test_key_idx]))
    {
      // test if the new key matches the spline within the constraints
      if(!c_.spline_constraints(keys_iterator_[test_key_idx-1], keys_iterator_[test_key_idx], spline, dt*scalar_t(test_key_idx-first_key_idx)))
      {
        // construct new spline which might have better fit with input keys
        cubic_spline<T> new_spline;
        dt=priv::setup_spline_from_mid_keys(new_spline, keys_iterator_, first_key_idx, test_key_idx);

        // test if all previous keys conform the new spline within constraints
        for(unsigned i=first_key_idx+1; i<test_key_idx; ++i)
          if(!c_.spline_constraints(keys_iterator_[i-1], keys_iterator_[i], new_spline, dt*scalar_t(i-first_key_idx)))
            goto add_spline;

        // continue with the new spline
        spline=new_spline;
      }
      ++test_key_idx;
      continue;
    }

    // add a spline key and start a new spline
    add_spline:
    if(first_key_idx<test_key_idx-4)
      dt=priv::setup_spline_from_mid_keys(spline, keys_iterator_, first_key_idx, test_key_idx-1);
    if(!c_.add_spline(spline, test_key_idx-first_key_idx-1))
      return 0;
    ++num_spline_keys;
    first_key_idx=test_key_idx-1;
    test_key_idx+=3;
    if(test_key_idx<=num_keys_)
      make_interp_spline(spline, keys_iterator_[first_key_idx], keys_iterator_[first_key_idx+1], keys_iterator_[first_key_idx+2], keys_iterator_[first_key_idx+3]);
  }

  // add the last spline key
  if(test_key_idx==num_keys_)
  {
    // complete the last full length segment
    if(first_key_idx<num_keys_-4)
      priv::setup_spline_from_mid_keys(spline, keys_iterator_, first_key_idx, test_key_idx-1);
    if(!c_.add_spline(spline, test_key_idx-first_key_idx-1))
      return 0;
    ++num_spline_keys;
  }
  else
  {
    // complete the last <4 input key segment
    unsigned num_keys_left=num_keys_-first_key_idx;
    if(num_keys_left==2)
    {
      // only two keys left
      const T &first_key=keys_iterator_[first_key_idx];
      const T &last_key=keys_iterator_[first_key_idx+1];
      spline.a-=spline.a;
      spline.b=spline.a;
      spline.c=last_key-first_key;
      spline.d=first_key;
    }
    else
    {
      // only three keys left
      const T &first_key=keys_iterator_[first_key_idx];
      const T &mid_key=keys_iterator_[first_key_idx+1];
      const T &last_key=keys_iterator_[first_key_idx+2];
      const T mid_wkey=mid_key*scalar_t(2.0/3.0);
      T k1=first_key*scalar_t(1.0/3.0)+mid_wkey;
      T k2=last_key*scalar_t(1.0/3.0)+mid_wkey;
      make_interp_spline(spline, first_key, k1, k2, last_key);
    }
    if(!c_.add_spline(spline, num_keys_left-1))
      return 0;
    ++num_spline_keys;
  }
  return num_spline_keys;
}
//----------------------------------------------------------------------------


//============================================================================
// misc spline operations
//============================================================================
template<typename T>
void reparametrize_spline(cubic_spline<T> &rs_, const cubic_spline<T> &s_, typename math<T>::scalar_t t_scale_, typename math<T>::scalar_t t_bias_)
{
  // reparametrize spline so that: rs(t) = s(t*t_scale_+t_bias_)
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t ts2=t_scale_*t_scale_;
  rs_.a=s_.a;
  rs_.a*=ts2*t_scale_;
  rs_.b=(scalar_t(3)*t_bias_)*s_.a+s_.b;
  rs_.b*=ts2;
  rs_.c=(scalar_t(3)*t_bias_*t_bias_)*s_.a+(scalar_t(2)*t_bias_)*s_.b+s_.c;
  rs_.c*=t_scale_;
  rs_.d=((s_.a*t_bias_+s_.b)*t_bias_+s_.c)*t_bias_+s_.d;
}
//----

template<typename T>
void spline_bounds(T &min_, T &max_, const cubic_spline<T> &s_)
{
  // init min and max values with spline min/max at t=0 and t=1
  typedef typename math<T>::scalar_t scalar_t;
  T v=s_.a+s_.b+s_.c+s_.d;
  T minv=min(s_.d, v), maxv=max(s_.d, v);

  // evaluate spline at zero-derivates
  T a=scalar_t(6)*s_.a;
  T b=scalar_t(-2)*s_.b;
  T sq=madd(b, b, scalar_t(-2)*mul(a, s_.c));
  T s=sqrt_z(sq);
  T r=mul(rcp_z(a), T(sq>=scalar_t(0)));
  T t0=mul(b+s, r), t1=mul(b-s, r);
  T v0=madd(madd(madd(s_.a, t0, s_.b), t0, s_.c), t0, s_.d);
  T v1=madd(madd(madd(s_.a, t1, s_.b), t1, s_.c), t1, s_.d);
  min_=min(minv, v0, v1);
  max_=max(maxv, v0, v1);
}
//----

template<typename T>
typename math<T>::scalar_t spline_length(const cubic_spline<T> &s_, unsigned num_steps_)
{
  // calculate spline length with given number of iterations
  PFC_ASSERT(num_steps_);
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t step=scalar_t(1)/scalar_t(num_steps_);
  T v0=s_.d;
  scalar_t len=0;
  for(unsigned i=1; i<=num_steps_; ++i)
  {
    T v1=evaluate(s_, scalar_t(i)*step);
    len+=norm(v1-v0);
    v0=v1;
  }
  return len;
}
//----

template<typename T> typename math<T>::scalar_t spline_distance_func(const cubic_spline<T> &s_, vec2<typename math<T>::scalar_t> &hermite_tangents_, unsigned num_steps_)
{
  // calculate coefficients for least-squares cubic fit of the spline distance function (monotonic in range [0, 1])
  PFC_ASSERT(num_steps_);
  typedef typename math<T>::scalar_t scalar_t;
  const scalar_t step=scalar_t(1)/scalar_t(num_steps_);
  T v0=s_.d;
  vec4<scalar_t> coeffs(0, 0, 0, 0);
  scalar_t len=0;
  scalar_t x0=0, x1=0, x2=0, x3=0, x4=0, x5=0, x6=0;
  for(unsigned i=1; i<=num_steps_; ++i)
  {
    // calculate cumulative distance and least-squares fit coefficients
    scalar_t si=scalar_t(i)*step, si2=si*si, si3=si2*si;
    T v1=evaluate(s_, si);
    len+=norm(v1-v0);
    v0=v1;
    coeffs+=vec4<scalar_t>(len*si3, len*si2, len*si, len);
    x0+=scalar_t(1.0); x1+=si; x2+=si2; x3+=si3; x4+=si2*si2; x5+=si3*si2; x6+=si3*si3;
  }

  // calculate cubic spline coefficients for normalized distance function
  coeffs*=rcp_z(len);
  coeffs*=inv(mat44<scalar_t>(x6, x5, x4, x3,
                              x5, x4, x3, x2,
                              x4, x3, x2, x1,
                              x3, x2, x1, x0));

  // calculate Hermite tangents for the spline distance approximation
  hermite_tangents_.x=coeffs.z;
  hermite_tangents_.y=coeffs.x*scalar_t(3.0)+coeffs.y*scalar_t(2.0)+coeffs.z;
  return len;
}
//----------------------------------------------------------------------------
