//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_LINUX_INET_POSIX_H
#define PFC_LINUX_INET_POSIX_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
namespace pfc
{

// new
#define PFC_CLOSESOCKET(s__) ::close(s__)
#define PFC_SET_SOCKET_NONBLOCKING(s__) {int flags=fcntl(s__, F_GETFL, 0); if(!(flags&O_NONBLOCK)) fcntl(s__, F_SETFL, flags|O_NONBLOCK);}
PFC_INLINE bool is_nonblocking_socket_fail() {return errno==EAGAIN || errno==EWOULDBLOCK || errno==EINPROGRESS;}
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
