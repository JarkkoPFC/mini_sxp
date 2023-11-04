//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_POSIX_INET_H
#define PFC_POSIX_INET_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/inet.h"
namespace pfc
{

// new
class posix_inet_system;
class posix_inet_socket_local;
class posix_inet_socket_remote;
//----------------------------------------------------------------------------


//============================================================================
// posix_inet_system
//============================================================================
class posix_inet_system: public inet_system_base
{
public:
  // construction
  posix_inet_system(bool set_active_=false);
  virtual ~posix_inet_system();
  //--------------------------------------------------------------------------

  // socket construction
  virtual ipv6_address local_ipv6() const;
  virtual ipv6_address dns_lookup_ipv6(const char *hostname_);
  virtual owner_ref<inet_socket_local_base> create_local_socket();
  virtual owner_ref<inet_socket_remote_base> create_remote_socket();
  //--------------------------------------------------------------------------

private:
  posix_inet_system(const posix_inet_system&); // not implemented
  void operator=(const posix_inet_system&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// posix_inet_socket_local
//============================================================================
class posix_inet_socket_local: public inet_socket_local_base
{
public:
  // construction
  posix_inet_socket_local();
  posix_inet_socket_local(unsigned port_, unsigned max_backlog_=1, const ipv6_address *ip_=0);
  virtual ~posix_inet_socket_local();
  void close();
  //--------------------------------------------------------------------------

  // connection
  virtual void bind(unsigned port_, unsigned max_backlog_=1, const ipv6_address *ip_=0);
  virtual void disconnect();
  virtual bool wait_connection(float timeout_=-1);
  //--------------------------------------------------------------------------

  // accessors
  virtual usize_t bufsize_recv() const;
  virtual usize_t bufsize_send() const;
  //--------------------------------------------------------------------------

  // data streaming
  virtual usize_t read(void *buffer_, usize_t buffer_size_);
  virtual usize_t write(const void *data_, usize_t data_size_);
  //--------------------------------------------------------------------------

private:
  posix_inet_socket_local(const posix_inet_socket_local&); // not implemented
  void operator=(const posix_inet_socket_local&); // not implemented
  //--------------------------------------------------------------------------

  size_t m_local_socket;
  size_t m_remote_socket;
};
//----------------------------------------------------------------------------


//============================================================================
// posix_inet_socket_remote
//============================================================================
class posix_inet_socket_remote: public inet_socket_remote_base
{
public:
  // construction
  posix_inet_socket_remote();
  posix_inet_socket_remote(const ipv6_address &ip_, unsigned port_);
  virtual ~posix_inet_socket_remote();
  //--------------------------------------------------------------------------

  // connection
  virtual bool connect(const ipv6_address &ip_, unsigned port_);
  virtual void disconnect();
  //--------------------------------------------------------------------------

  // accessors
  virtual usize_t bufsize_recv() const;
  virtual usize_t bufsize_send() const;
  //--------------------------------------------------------------------------

  // data streaming
  virtual usize_t read(void *buffer_, usize_t buffer_size_);
  virtual usize_t write(const void *data_, usize_t data_size_);
  //--------------------------------------------------------------------------

private:
  posix_inet_socket_remote(const posix_inet_socket_remote&); // not implemented
  void operator=(const posix_inet_socket_remote&); // not implemented
  //--------------------------------------------------------------------------

  size_t m_socket;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
