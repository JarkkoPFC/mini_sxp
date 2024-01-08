//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "mp_fiber.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// ffunc_sleep
//============================================================================
PFC_FFUNC_IMPL(ffunc_sleep)
{
  // count down the sleep time
  sleep_time-=__ffunc_dtime_;
  if(sleep_time<=0.0f)
  {
    __ffunc_dtime_+=sleep_time;
    return false;
  }
  __ffunc_dtime_=0.0f;
  return !__ffunc_cs_.is_abort();
}
//----------------------------------------------------------------------------
