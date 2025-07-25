//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// mse
//============================================================================
template<typename T>
T mse(const T *data_, const T *ref_data_, usize_t data_size_)
{
  // calculate mean squared error
  T mse=T();
  for(unsigned i=0; i<data_size_; ++i)
    mse+=sqr(data_[i]-ref_data_[i]);
  mse/=mathf::scalar_t(data_size_);
  return mse;
}
//----------------------------------------------------------------------------


//============================================================================
// rmse
//============================================================================
template<typename T>
T rmse(const T *data_, const T *ref_data_, usize_t data_size_)
{
  // return root mean squared error
  return sqrt(mse(data_, ref_data_, data_size_));
}
//----------------------------------------------------------------------------


//============================================================================
// rmsle
//============================================================================
template<typename T>
T rmsle(const T *data_, const T *ref_data_, usize_t data_size_)
{
  // calculate root mean squared logarithmic error
  typedef math<T>::scalar_t scalar_t;
  T msle=T();
  for(unsigned i=0; i<data_size_; ++i)
    msle+=sqr(ln(scalar_t(1)+data_[i])-ln(scalar_t(1)+ref_data_[i]));
  msle/=mathf::scalar_t(data_size_);
  return sqrt(msle);
}
//----------------------------------------------------------------------------


//============================================================================
// psnr
//============================================================================
template<typename T>
T psnr(const T *data_, const T *ref_data_, usize_t data_size_)
{
  // calculate mean squared error
  T mse=T(), max_val=T();
  for(unsigned i=0; i<data_size_; ++i)
  {
    mse+=sqr(data_[i]-ref_data_[i]);
    max_val=max(max_val, ref_data_[i]);
  }
  mse/=mathf::scalar_t(data_size_);

  // return peak signal-to-noise ratio
  return T(10.0)*log10(sqr(max_val)/mse);
}
//----------------------------------------------------------------------------


//============================================================================
// ssim
//============================================================================
template<typename T>
T ssim(const T *img_, const T *ref_img_, unsigned width_, unsigned height_, unsigned window_rad_, T *ssim_img_)
{
  // get max pixel value
  typedef math<T>::scalar_t scalar_t;
  T max_val=T();
  unsigned img_size=width_*height_;
  for(unsigned i=0; i<img_size; ++i)
    max_val=max(max_val, ref_img_[i]);
  T c1=sqr(scalar_t(0.01)*max_val);
  T c2=sqr(scalar_t(0.03)*max_val);
  T c3=c2/scalar_t(2);

  // calculate SSIM
  T avg_ssim=T();
  unsigned wnd_width=window_rad_*2+1;
  scalar_t wnd_size_scale=scalar_t(1.0)/(wnd_width*wnd_width);
  for(unsigned y=0; y<height_; ++y)
    for(unsigned x=0; x<width_; ++x)
    {
      // calculate mean of the image and ref-image for the pixel window
      T wnd_mean_img=T();
      T wnd_mean_ref=T();
      for(int wy=-int(window_rad_); wy<=int(window_rad_); ++wy)
        for(int wx=-int(window_rad_); wx<=int(window_rad_); ++wx)
        {
          unsigned sx=x+wx, sy=y+wy;
          if(sx<width_ && sy<height_)
          {
            unsigned px_offset=sx+sy*width_;
            wnd_mean_img+=img_[px_offset];
            wnd_mean_ref+=ref_img_[px_offset];
          }
        }
      wnd_mean_img*=wnd_size_scale;
      wnd_mean_ref*=wnd_size_scale;

      // calculate variance and co-variance of the image and ref-image for the pixel window
      T wnd_var_img=T();
      T wnd_var_ref=T();
      T wnd_cov=T();
      for(int wy=-int(window_rad_); wy<=int(window_rad_); ++wy)
        for(int wx=-int(window_rad_); wx<=int(window_rad_); ++wx)
        {
          unsigned sx=x+wx, sy=y+wy;
          if(sx<width_ && sy<height_)
          {
            unsigned px_offset=sx+sy*width_;
            T diff_img=img_[px_offset]-wnd_mean_img;
            T diff_ref=ref_img_[px_offset]-wnd_mean_ref;
            wnd_var_img+=sqr(diff_img);
            wnd_var_ref+=sqr(diff_ref);
            wnd_cov+=diff_img*diff_ref;
          }
        }
      wnd_var_img*=wnd_size_scale;
      wnd_var_ref*=wnd_size_scale;
      wnd_cov*=wnd_size_scale;

      // calculate standard SSIM for the window
      T ssim=((scalar_t(2)*wnd_mean_img*wnd_mean_ref+c1)*(scalar_t(2)*wnd_cov+c2))/((sqr(wnd_mean_img)+sqr(wnd_mean_ref)+c1)*(wnd_var_img+wnd_var_ref+c2));
      avg_ssim+=ssim;
      if(ssim_img_)
        *ssim_img_++=ssim;
    }
  return avg_ssim/scalar_t(width_*height_);
}
//----------------------------------------------------------------------------
