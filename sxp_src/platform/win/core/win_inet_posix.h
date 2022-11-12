//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_WIN_INET_POSIX_H
#define PFC_WIN_INET_POSIX_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include <WS2tcpip.h>
namespace pfc
{

// new
#define PFC_CLOSESOCKET(s__) ::closesocket(s__)
#define PFC_SET_SOCKET_NONBLOCKING(s__) {u_long socket_mode=1; PFC_VERIFY(::ioctlsocket(s__, FIONBIO, &socket_mode)==0);}
PFC_INLINE bool is_nonblocking_socket_fail() {return WSAGetLastError()==WSAEWOULDBLOCK;}
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
