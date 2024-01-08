//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_INET_H
#define PFC_CORE_INET_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/utils.h"
#include "sxp_src/core/functor.h"
#include "sxp_src/core/variant.h"
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
class simple_inet_data_protocol_socket;
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

  // accessors
  virtual usize_t bufsize_recv() const=0;
  virtual usize_t bufsize_send() const=0;
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
  void set_timeout(unsigned min_bytes_per_sec_, udouble_t max_request_time_);
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
  void set_timeout(unsigned min_bytes_per_sec_, udouble_t max_request_time_);
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
// simple_inet_data_protocol_socket
//============================================================================
// A simple and efficient data protocol socket for bidirectional type-safe
// communication over a local/remote internet sockets. The data is sent as
// binary with minimal type info to optimize the transfer.
// The socket sends periodical keep-alive signal if no data is otherwise sent,
// to signal the connection that the socket is alive. This signal is being sent
// by process_input_data() which should be called frequently (at least twice
// within the timeout threshold) to maintain the connection and to avoid the
// potential connection timeout.
// The socket also implements double windowed receiver-driven pacing to avoid
// receiver data congestion while avoiding socket data starvation. The socket
// sends a pacing signal to the receiver every ~N sent bytes (window size) and
// blocks writes to the socket if pacing ACK signal for the previous window
// hasn't been returned from the receiver.
class simple_inet_data_protocol_socket
{
public:
  // construction and connecstion
  simple_inet_data_protocol_socket(inet_socket_base&, udouble_t timeout_=1.0);
  template<class T> void register_input_type_handler(const functor<void(const T&)>&, const char *alt_name_=0);
  bool connect();
  void disconnect();
  PFC_INLINE bool is_alive() const;
  PFC_INLINE void set_timeout(udouble_t timeout_);
  PFC_INLINE void reset_timeout();
  //--------------------------------------------------------------------------

  // data writing and reading
  template<class T> bool write(const T&, const char *alt_name_=0);
  bool process_input_data();
  //--------------------------------------------------------------------------

private:
  simple_inet_data_protocol_socket(const simple_inet_data_protocol_socket&); // not implemented
  void operator=(const simple_inet_data_protocol_socket&); // not implemented
  struct data_reader_base;
  template<class T> struct data_reader;
  struct registered_local_type;
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_connection_state
  //==========================================================================
  enum e_connection_state
  {
    constate_unconnected,  // hasn't been connected since construction
    constate_connected,    // is connected
    constate_disconnected, // has been connected and then disconnected
  };
  //--------------------------------------------------------------------------

  inet_socket_base &m_socket;
  inet_input_stream m_stream_in;
  inet_output_stream m_stream_out;
  udouble_t m_timeout;
  e_connection_state m_connection_state;
  udouble_t m_last_keepalive_signal_recv;
  udouble_t m_last_keepalive_signal_sent;
  uint32_t m_pacing_window_size;
  uint8_t m_pacing_id_recv;
  uint8_t m_pacing_id_sent;
  usize_t m_pacing_pos_next;
  array<registered_local_type> m_registered_local_types;
  map<heap_str, uint16_t> m_registered_remote_types;
};
//----------------------------------------------------------------------------

//============================================================================
#include "inet.inl"
} // namespace pfc
#endif
