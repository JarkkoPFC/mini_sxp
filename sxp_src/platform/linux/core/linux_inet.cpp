//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/platform/posix/posix_inet.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// create_default_file_system
//============================================================================
owner_ptr<inet_system_base> pfc::create_default_inet_system(bool set_active_)
{
  return PFC_NEW(posix_inet_system)(set_active_);
}
//----------------------------------------------------------------------------
