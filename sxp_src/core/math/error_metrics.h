//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_ERROR_METRICS_H
#define PFC_CORE_MATH_ERROR_METRICS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/core.h"
namespace pfc
{

// new
template<typename T> T mse(const T *data_, const T *ref_data_, usize_t data_size_);
template<typename T> T rmse(const T *data_, const T *ref_data_, usize_t data_size_);
template<typename T> T rmsle(const T *data_, const T *ref_data_, usize_t data_size_);
template<typename T> T psnr(const T *data_, const T *ref_data_, usize_t data_size_);
template<typename T> T ssim(const T *img_, const T *ref_img_, unsigned width_, unsigned height_, unsigned window_rad_=5, T *ssim_img_=0);
//----------------------------------------------------------------------------

//============================================================================
#include "error_metrics.inl"
} // namespace pfc
#endif
