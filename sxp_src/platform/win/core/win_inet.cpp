//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/platform/posix/posix_inet.h"
#include <WinSock2.h>
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// win_inet_system
//============================================================================
class win_inet_system: public posix_inet_system
{
public:
  // construction
  win_inet_system(bool set_active_);
  virtual ~win_inet_system();
};
//----------------------------------------------------------------------------

win_inet_system::win_inet_system(bool set_active_)
  :posix_inet_system(set_active_)
{
  WSADATA wsaData;
  PFC_VERIFY_MSG(WSAStartup(MAKEWORD(2, 2), &wsaData)==NO_ERROR, ("Unable to initialize network system\r\n"));
}
//----

win_inet_system::~win_inet_system()
{
  WSACleanup();
}
//----------------------------------------------------------------------------


//============================================================================
// create_default_file_system
//============================================================================
owner_ptr<inet_system_base> pfc::create_default_inet_system(bool set_active_)
{
  return PFC_NEW(win_inet_system)(set_active_);
}
//----------------------------------------------------------------------------
