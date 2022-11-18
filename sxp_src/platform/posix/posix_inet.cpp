//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "posix_inet.h"
#include <fcntl.h>
#include PFC_STR(PFC_CAT2(sxp_src/platform/PFC_PLATFORM_SRC_STR/core/PFC_PLATFORM_SRC_STR, _inet_posix.h))  // expands to e.g. "sxp_src/platform/win/core/win_inet_posix.h"
using namespace pfc;
static const float s_connection_wait_sleep_time=0.001f; // balance between idle CPU usage and responsiveness to connections
//----------------------------------------------------------------------------


//============================================================================
// posix_inet_system
//============================================================================
posix_inet_system::posix_inet_system(bool set_active_)
  :inet_system_base(set_active_)
{
}
//----

posix_inet_system::~posix_inet_system()
{
}
//----------------------------------------------------------------------------

ipv6_address posix_inet_system::local_ipv6() const
{
  // get ipv4 of localhost
  char buf[1024];
  if(::gethostname(buf, sizeof(buf)))
  {
    PFC_WARN(("Unable to retrieve local IP address\r\n"));
    return ipv6_address();
  }
  const hostent *host=gethostbyname(buf);
  const uint8_t *addr=(const uint8_t*)host->h_addr_list[0];
  return ipv4_address(addr[0], addr[1], addr[2], addr[3]);
}
//----

ipv6_address posix_inet_system::dns_lookup_ipv6(const char *hostname_)
{
  // check for no hostname
  if(!hostname_ || !*hostname_)
    return ipv6_address();

  // get ipv6 address
  ipv6_address ip;
  addrinfo *ainfo=0, hints;
  mem_zero(&hints, sizeof(hints));
  if(::getaddrinfo(hostname_, 0, &hints, &ainfo))
  {
    PFC_WARN(("Unable to retrieve IP address for host \"%s\"\r\n", hostname_));
    return ip;
  }

  switch(ainfo->ai_family)
  {
    case AF_INET:
    {
      // extract IPv4 address
      const uint8_t *addr=(const uint8_t*)&((const sockaddr_in*)ainfo->ai_addr)->sin_addr.s_addr;
      ip=ipv4_address(addr[0], addr[1], addr[2], addr[3]);
    } break;

    case AF_INET6:
    {
      // extract IPv6 address
      sockaddr_in6 ipv6;
      mem_copy(&ipv6, ainfo->ai_addr, ainfo->ai_addrlen);
      mem_copy(&ip, &ipv6.sin6_addr, sizeof(ip));
    } break;
  }

  // release resources
  ::freeaddrinfo(ainfo);
  return ip;
}
//----

owner_ref<inet_socket_local_base> posix_inet_system::create_local_socket()
{
  return PFC_NEW(posix_inet_socket_local);
}
//----

owner_ref<inet_socket_remote_base> posix_inet_system::create_remote_socket()
{
  return PFC_NEW(posix_inet_socket_remote);
}
//----------------------------------------------------------------------------


//============================================================================
// posix_inet_socket_local
//============================================================================
posix_inet_socket_local::posix_inet_socket_local()
{
  m_local_socket=size_t(-1);
  m_remote_socket=size_t(-1);
}
//----

posix_inet_socket_local::posix_inet_socket_local(unsigned port_, unsigned max_backlog_, const ipv6_address *ip_)
{
  m_local_socket=size_t(-1);
  m_remote_socket=size_t(-1);
  bind(port_, max_backlog_, ip_);
}
//----

posix_inet_socket_local::~posix_inet_socket_local()
{
  close();
}
//----

void posix_inet_socket_local::close()
{
  // close socket
  PFC_CLOSESOCKET(m_local_socket);
  PFC_CLOSESOCKET(m_remote_socket);
  m_local_socket=size_t(-1);
  m_remote_socket=size_t(-1);
}
//----------------------------------------------------------------------------

void posix_inet_socket_local::bind(unsigned port_, unsigned max_backlog_, const ipv6_address *ip_)
{
  // create socket
  close();
  m_local_socket=::socket(AF_INET6, SOCK_STREAM, 0);
  PFC_CHECK_MSG(m_local_socket>=0, ("Unable to create internet stream socket\r\n"));
  PFC_SET_SOCKET_NONBLOCKING(m_local_socket);

  // bind socket to the given port
  sockaddr_in6 addr_v6;
  mem_zero((char*)&addr_v6, sizeof(addr_v6));
  addr_v6.sin6_family=AF_INET6;
  addr_v6.sin6_port=to_big_endian(u_short(port_));
  if(ip_)
    mem_copy(&addr_v6.sin6_addr, ip_, sizeof(addr_v6.sin6_addr));
  PFC_VERIFY_MSG(::bind(m_local_socket, (const sockaddr*)&addr_v6, sizeof(addr_v6))==0,
                 ("Binding internet socket to port %i failed\r\n", port_));
  PFC_VERIFY_MSG(::listen(m_local_socket, max_backlog_)>=0,
                 ("Unable to set the socket to listen mode with %i max backlog\r\n", max_backlog_));
}
//----

void posix_inet_socket_local::disconnect()
{
  // disconnect socket
  PFC_CLOSESOCKET(m_remote_socket);
  m_remote_socket=size_t(-1);
}
//----

bool posix_inet_socket_local::wait_connection(float timeout_)
{
  // wait for connection to the sockets
  PFC_ASSERT_MSG(m_remote_socket==size_t(-1), ("Internet socket is already connected\r\n"));
  double end_time=timeout_>0.0f?get_global_time()+timeout_:0.0;
  size_t s;
  do
  {
    s=::accept(m_local_socket, 0, 0);
    if(s!=size_t(-1))
    {
      m_remote_socket=s;
      return true;
    }
    PFC_ASSERT_MSG(is_nonblocking_socket_fail(), ("Waiting for the socket failed\r\n"));
    if(!timeout_)
      return false;
    thread_sleep(s_connection_wait_sleep_time);
  } while(timeout_<0 || get_global_time()<end_time);
  return false;
}
//----------------------------------------------------------------------------

usize_t posix_inet_socket_local::read(void *buffer_, usize_t buffer_size_)
{
  // read data from the socket
  PFC_ASSERT_MSG(m_remote_socket!=size_t(-1), ("Internet socket isn't connected\r\n"));
  if(!buffer_size_)
    return 0;
  usize_t num_bytes=::recv(m_remote_socket, (char*)buffer_, (unsigned)buffer_size_, 0);
  return num_bytes==usize_t(-1)?0:num_bytes;
}
//----

usize_t posix_inet_socket_local::write(const void *data_, usize_t data_size_)
{
  // write data to the socket
  PFC_ASSERT_MSG(m_remote_socket!=size_t(-1), ("Internet socket isn't connected\r\n"));
  if(!data_size_)
    return 0;
  usize_t num_bytes_sent=::send(m_remote_socket, (const char*)data_, (unsigned)data_size_, 0);
  return num_bytes_sent==usize_t(-1)?0:num_bytes_sent;
}
//----------------------------------------------------------------------------


//============================================================================
// posix_inet_socket_remote
//============================================================================
posix_inet_socket_remote::posix_inet_socket_remote()
{
  m_socket=size_t(-1);
}
//----

posix_inet_socket_remote::posix_inet_socket_remote(const ipv6_address &ip_, unsigned port_)
{
  m_socket=size_t(-1);
  connect(ip_, port_);
}
//----

posix_inet_socket_remote::~posix_inet_socket_remote()
{
  disconnect();
}
//----------------------------------------------------------------------------

bool posix_inet_socket_remote::connect(const ipv6_address &ip_, unsigned port_)
{
  // create socket
  disconnect();
  m_socket=::socket(AF_INET6, SOCK_STREAM, 0);
  PFC_CHECK_MSG(m_socket>=0, ("Unable to create internet stream socket\r\n"));
  PFC_SET_SOCKET_NONBLOCKING(m_socket);

  // setup address
  sockaddr_in6 addr;
  mem_zero(&addr, sizeof(addr));
  addr.sin6_family=AF_INET6;
  addr.sin6_port=to_big_endian(u_short(port_));
  mem_copy(&addr.sin6_addr, &ip_, sizeof(ip_));

  // try to connect to the given host & port
  if(::connect(m_socket, (const sockaddr*)&addr, sizeof(addr))==0)
    return true;
  if(!is_nonblocking_socket_fail())
  {
    PFC_WARN(("Unable to connect to host %s:%i\r\n", ipv6_to_simple_str(ip_).c_str(), port_));
    disconnect();
    return false;
  }

  // wait max one second for the connection completion (non-blocking)
  fd_set wfds;
  FD_ZERO(&wfds);
  FD_SET(m_socket, &wfds);
  timeval tval;
  tval.tv_sec=1;
  tval.tv_usec=0;
  if(::select(1, 0, &wfds, 0, &tval)<=0)
  {
    PFC_WARN(("Connection timeout to host %s:%i\r\n", ipv6_to_simple_str(ip_).c_str(), port_));
    disconnect();
    return false;
  }

  // check for proper connection
  int err=0;
  socklen_t len=sizeof(err);
  if(::getsockopt(m_socket, SOL_SOCKET, SO_ERROR, (char*)&err, &len)==-1 || err!=0)
  {
    PFC_WARN(("Connection failure to host %s:%i\r\n", ipv6_to_simple_str(ip_).c_str(), port_));
    disconnect();
    return false;
  }
  return true;
}
//----

void posix_inet_socket_remote::disconnect()
{
  PFC_CLOSESOCKET(m_socket);
  m_socket=size_t(-1);
}
//----------------------------------------------------------------------------

usize_t posix_inet_socket_remote::read(void *buffer_, usize_t buffer_size_)
{
  // read data from the socket
  PFC_ASSERT_MSG(m_socket!=size_t(-1), ("Internet socket isn't open\r\n"));
  if(!buffer_size_)
    return 0;
  usize_t num_bytes=::recv(m_socket, (char*)buffer_, (unsigned)buffer_size_, 0);
  return num_bytes==usize_t(-1)?0:num_bytes;
}
//----

usize_t posix_inet_socket_remote::write(const void *data_, usize_t data_size_)
{
  // write data to the socket
  PFC_ASSERT_MSG(m_socket!=size_t(-1), ("Internet socket isn't open\r\n"));
  if(!data_size_)
    return 0;
  usize_t num_bytes_sent=::send(m_socket, (const char*)data_, (unsigned)data_size_, 0);
  return num_bytes_sent==usize_t(-1)?0:num_bytes_sent;
}
//----------------------------------------------------------------------------
