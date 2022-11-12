//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// eigenvalues_symmetric
//============================================================================
template<typename T> vec3<T> eigenvalues_sym(const mat33<T> &m_)
{
  // return eigenvalues of a symmetric 3x3 matrix
  typedef typename math<T>::scalar_t scalar_t;
  scalar_t m=tr(m_)*scalar_t(1.0/3.0);
  mat33<T> k=m_;
  k.x.x-=m; k.y.y-=m; k.z.z-=m;
  scalar_t q=det(k)*scalar_t(0.5);
  scalar_t p=scalar_t(1.0/6.0)*(k.x.x*k.x.x+k.y.y*k.y.y+k.z.z*k.z.z)+scalar_t(1.0/3.0)*(k.x.y*k.x.y+k.x.z*k.x.z+k.y.z*k.y.z);
  scalar_t sphi, cphi;
  scalar_t phi=scalar_t(1.0/3.0)*atan(sqrt(p*p*p-q*q)/q);
  sincos(sphi, cphi, phi<0?phi+mathf::pi*scalar_t(1.0/3.0):phi);
  scalar_t sp=sqrt(p);
  cphi*=sp; sphi*=math<T>::sqrt3*sp;
  return vec3<T>(m+scalar_t(2.0)*cphi, m-cphi-sphi, m-cphi+sphi);
}
//----------------------------------------------------------------------------


//============================================================================
// eigenvector_pow
//============================================================================
// if there are multiple eigenvectors for maximum absolute eigenvalue, a random
// vector on the plane defined by the eigenvectors is returned.
// to calculate minimum eigenvector instead, use this function with the inverse
// matrix instead (inverse power method).
template<typename T>
vec3<T> eigenvector_pow(const mat33<T> &m_)
{
  // calculate eigenvector for maximum absolute eigenvalue using inverse power method
  typedef typename math<T>::scalar_t scalar_t;
  vec3<T> b(math<T>::rsqrt3), ob;
  do
  {
    ob=b;
    b=unit(b*m_);
  } while(abs(dot(b, ob))<scalar_t(0.999999));
  return b;
}
//----------------------------------------------------------------------------
