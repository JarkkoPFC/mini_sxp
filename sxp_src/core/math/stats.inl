//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// inv_standard_normal_cdf
//============================================================================
// inverse of the Standard Normal Distribution CDF
template<typename T>
T inv_standard_normal_cdf(T p_)
{
  PFC_ASSERT_PEDANTIC(p_>=0 && p_<=1);
  static const T s_rsqrt2=0.7071067811865475244;
  static const T s_sqrt2pi=2.5066282746310005;
  static const T s_max=1000000.0;
  if(p_<=0) return -s_max;
  if(p_>=1) return s_max;
  T x=0, prev_err=1;
  while(true)
  {
    T cdf=T(0.5)*(1+erf(x*s_rsqrt2));
    x-=(cdf-p_)*exp(T(0.5)*x*x)*s_sqrt2pi;
    T err=abs(cdf-p_);
    if(err>=prev_err)
      break;
    prev_err=err;
  }
  return x;
}
//----------------------------------------------------------------------------


//============================================================================
// inv_normal_cdf
//============================================================================
// inverse of the Normal Distribution CDF with given mean and standard deviation
template<typename T>
T inv_normal_cdf(T p_, T mean_, T deviation_)
{
  return mean_+deviation_*inv_standard_normal_cdf(p_);
}
//----------------------------------------------------------------------------
