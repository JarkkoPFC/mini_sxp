//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/platform/posix/posix_fsys.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// create_default_file_system
//============================================================================
owner_ref<file_system_base> pfc::create_default_file_system(bool set_active_)
{
  return PFC_NEW(posix_file_system)(set_active_);
}
//----------------------------------------------------------------------------
