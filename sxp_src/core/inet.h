//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_INET_H
#define PFC_CORE_INET_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/streams.h"
#include "sxp_src/core/utils.h"
namespace pfc
{

// new
typedef stack_str64 ip_str;
union ipv4_address;
union ipv6_address;
struct inetv4_socket_address;
struct inetv6_socket_address;
class inet_system_base;
class inet_socket_base;
class inet_socket_local_base;
class inet_socket_remote_base;
class inet_input_stream;
class inet_output_stream;
bool is_ipv4(const ipv6_address&);
ip_str ipv4_to_str(const ipv4_address&);
ip_str ipv6_to_str(const ipv6_address&);
ip_str ipv6_to_simple_str(const ipv6_address&);
PFC_INLINE bool is_valid(const ipv4_address&);
PFC_INLINE bool is_valid(const ipv6_address&);
owner_ptr<inet_system_base> create_default_inet_system(bool set_active_=false);
//----------------------------------------------------------------------------


//============================================================================
// ipv4_address
//============================================================================
union ipv4_address
{ PFC_MONO(ipv4_address) {PFC_VAR(dword);}
  // construction
  PFC_INLINE ipv4_address();
  PFC_INLINE ipv4_address(uint8_t b0_, uint8_t b1_, uint8_t b2_, uint8_t b3_);
  PFC_INLINE ipv4_address(const ipv6_address&);
  //--------------------------------------------------------------------------

  uint8_t bytes[4];
  uint16_t words[2];
  uint32_t dword;
};
PFC_SET_TYPE_TRAIT(ipv4_address, is_type_pod, true);
PFC_SET_TYPE_TRAIT(ipv4_address, is_type_pod_stream, true);
//----

PFC_INLINE bool operator==(const ipv4_address&, const ipv4_address&);
PFC_INLINE bool operator!=(const ipv4_address&, const ipv4_address&);
//----------------------------------------------------------------------------


//============================================================================
// ipv6_address
//============================================================================
union ipv6_address
{ PFC_MONO(ipv6_address) {PFC_AVAR(dwords, 4);}
  // construction
  PFC_INLINE ipv6_address();
  PFC_INLINE ipv6_address(uint32_t d0_, uint32_t d1_, uint32_t d2_, uint32_t d3_);
  PFC_INLINE ipv6_address(uint16_t d0_, uint16_t d1_, uint16_t d2_, uint16_t d3_,
                          uint16_t d4_, uint16_t d5_, uint16_t d6_, uint16_t d7_);
  PFC_INLINE ipv6_address(const ipv4_address&);
  //--------------------------------------------------------------------------

  uint8_t bytes[16];
  uint16_t words[8];
  uint32_t dwords[4];
};
PFC_SET_TYPE_TRAIT(ipv6_address, is_type_pod, true);
PFC_SET_TYPE_TRAIT(ipv6_address, is_type_pod_stream, true);
//----

PFC_INLINE bool operator==(const ipv6_address&, const ipv6_address&);
PFC_INLINE bool operator!=(const ipv6_address&, const ipv6_address&);
//----------------------------------------------------------------------------


//============================================================================
// inetv4_socket_address
//============================================================================
struct inetv4_socket_address
{ PFC_MONO(inetv4_socket_address) {PFC_VAR2(ip, port);}
  // construction
  PFC_INLINE inetv4_socket_address();
  PFC_INLINE inetv4_socket_address(const ipv4_address&, uint16_t port_);
  //--------------------------------------------------------------------------

  ipv4_address ip;
  uint16_t port;
};
PFC_SET_TYPE_TRAIT(inetv4_socket_address, is_type_pod, true);
PFC_SET_TYPE_TRAIT(inetv4_socket_address, is_type_pod_stream, true);
//----

PFC_INLINE bool operator==(const inetv4_socket_address&, const inetv4_socket_address&);
PFC_INLINE bool operator!=(const inetv4_socket_address&, const inetv4_socket_address&);
//----------------------------------------------------------------------------


//============================================================================
// inetv6_socket_address
//============================================================================
struct inetv6_socket_address
{ PFC_MONO(inetv6_socket_address) {PFC_VAR2(ip, port);}
  // construction
  PFC_INLINE inetv6_socket_address();
  PFC_INLINE inetv6_socket_address(const ipv6_address&, uint16_t port_);
  //--------------------------------------------------------------------------

  ipv6_address ip;
  uint16_t port;
};
PFC_SET_TYPE_TRAIT(inetv6_socket_address, is_type_pod, true);
PFC_SET_TYPE_TRAIT(inetv6_socket_address, is_type_pod_stream, true);
//----

PFC_INLINE bool operator==(const inetv6_socket_address&, const inetv6_socket_address&);
PFC_INLINE bool operator!=(const inetv6_socket_address&, const inetv6_socket_address&);
//----------------------------------------------------------------------------


//============================================================================
// inet_system_base
//============================================================================
class inet_system_base
{
public:
  // construction
  inet_system_base(bool set_active_=false);
  virtual ~inet_system_base()=0;
  static PFC_INLINE void set_active(inet_system_base*);
  static PFC_INLINE inet_system_base &active();
  //--------------------------------------------------------------------------

  // socket construction
  virtual ipv6_address local_ipv6() const=0;
  virtual ipv6_address dns_lookup_ipv6(const char *hostname_)=0;
  virtual owner_ref<inet_socket_local_base> create_local_socket()=0;
  owner_ref<inet_socket_local_base> create_local_socket(unsigned port_, unsigned max_backlog_=1, const ipv6_address *ip_=0);
  virtual owner_ref<inet_socket_remote_base> create_remote_socket()=0;
  owner_ptr<inet_socket_remote_base> create_remote_socket(const ipv6_address&, unsigned port_);
  //--------------------------------------------------------------------------

private:
  inet_system_base(const inet_system_base&); // not implemented
  void operator=(const inet_system_base&); // not implemented
  //--------------------------------------------------------------------------

  static inet_system_base *s_active;
};
//----------------------------------------------------------------------------


//============================================================================
// inet_socket_base
//============================================================================
class inet_socket_base
{
public:
  // construction
  PFC_INLINE inet_socket_base();
  virtual PFC_INLINE ~inet_socket_base();
  virtual void disconnect()=0;
  //--------------------------------------------------------------------------

  // data streaming
  virtual usize_t read(void *buffer_, usize_t buffer_size_)=0;
  virtual usize_t write(const void *data_, usize_t data_size_)=0;
  //--------------------------------------------------------------------------

private:
  inet_socket_base(const inet_socket_base&); // not implemented
  void operator=(const inet_socket_base&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// inet_socket_local_base
//============================================================================
class inet_socket_local_base: public inet_socket_base
{
public:
  // construction
  PFC_INLINE inet_socket_local_base();
  //--------------------------------------------------------------------------

  // connection
  virtual void bind(unsigned port_, unsigned max_backlog_=1, const ipv6_address *ip_=0)=0;
  virtual void disconnect()=0;
  virtual bool wait_connection(float timeout_=-1)=0;
  //--------------------------------------------------------------------------

private:
  inet_socket_local_base(const inet_socket_local_base&); // not implemented
  void operator=(const inet_socket_local_base&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// inet_socket_remote_base
//============================================================================
class inet_socket_remote_base: public inet_socket_base
{
public:
  // construction
  PFC_INLINE inet_socket_remote_base();
  //--------------------------------------------------------------------------

  // connection
  virtual bool connect(const ipv6_address&, unsigned port_)=0;
  virtual void disconnect()=0;
  //--------------------------------------------------------------------------

private:
  inet_socket_remote_base(const inet_socket_remote_base&); // not implemented
  void operator=(const inet_socket_remote_base&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// inet_input_stream
//============================================================================
class inet_input_stream: public bin_input_stream_base
{
public:
  // construction
  inet_input_stream(inet_socket_base&);
  void set_timeout_threshold(unsigned min_bytes_per_sec_, udouble_t max_request_time_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE bool has_timeouted() const;
  PFC_INLINE void reset_timeout();
  //--------------------------------------------------------------------------

private:
  inet_input_stream(const inet_input_stream&); // not implemented
  void operator=(const inet_input_stream&); // not implemented
  virtual usize_t update_buffer_impl(void*, usize_t num_bytes_, bool exact_);
  virtual void rewind_impl();
  virtual void rewind_impl(usize_t num_bytes_);
  virtual void skip_impl();
  virtual void seek_impl(usize_t abs_pos_);
  //--------------------------------------------------------------------------

  enum {buffer_size=1024};
  inet_socket_base &m_socket;
  bool m_has_timeouted;
  udouble_t m_timeout_max_spb;
  udouble_t m_timeout_max_request_time;
  uint8_t m_buffer[buffer_size];
};
//----------------------------------------------------------------------------


//============================================================================
// inet_output_stream
//============================================================================
class inet_output_stream: public bin_output_stream_base
{
public:
  // construction
  inet_output_stream(inet_socket_base&);
  virtual ~inet_output_stream();
  void set_timeout_threshold(unsigned min_bytes_per_sec_, udouble_t max_request_time_);
  //--------------------------------------------------------------------------

  // accessors and mutators
  PFC_INLINE bool has_timeouted() const;
  PFC_INLINE void reset_timeout();
  //--------------------------------------------------------------------------

private:
  inet_output_stream(const inet_output_stream&); // not implemented
  void operator=(const inet_output_stream&); // not implemented
  virtual void flush_buffer_impl(const void*, usize_t num_bytes_);
  usize_t write_data(const uint8_t*, usize_t num_bytes_);
  //--------------------------------------------------------------------------

  enum {buffer_size=1024};
  inet_socket_base &m_socket;
  bool m_has_timeouted;
  udouble_t m_timeout_max_spb;
  udouble_t m_timeout_max_request_time;
  uint8_t m_buffer[buffer_size];
};
//----------------------------------------------------------------------------

//============================================================================
#include "inet.inl"
} // namespace pfc
#endif
