//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// ipv4_address
//============================================================================
ipv4_address::ipv4_address()
  :dword(0)
{
}
//----

ipv4_address::ipv4_address(uint8_t b0_, uint8_t b1_, uint8_t b2_, uint8_t b3_)
{
  bytes[0]=b0_;
  bytes[1]=b1_;
  bytes[2]=b2_;
  bytes[3]=b3_;
}
//----

ipv4_address::ipv4_address(const ipv6_address &ip_)
{
  // try convert ipv6 to ipv4
  dword=0;
  if(!ip_.dwords[0] && !ip_.dwords[1] && ip_.dwords[2]==PFC_TO_BIG_ENDIAN_U32(0xffff))
    dword=ip_.dwords[3];
  else if(!ip_.dwords[0] && !ip_.dwords[1] && !ip_.dwords[2] && ip_.dwords[3]==PFC_TO_BIG_ENDIAN_U32(1))
    dword=PFC_TO_BIG_ENDIAN_U32(0x7f000001);
}
//----------------------------------------------------------------------------

PFC_INLINE bool operator==(const ipv4_address &a0_, const ipv4_address &a1_)
{
  return mem_eq(&a0_, &a1_, sizeof(ipv4_address));
}
//----

PFC_INLINE bool operator!=(const ipv4_address &a0_, const ipv4_address &a1_)
{
  return !mem_eq(&a0_, &a1_, sizeof(ipv4_address));
}
//----------------------------------------------------------------------------


//============================================================================
// ipv6_address
//============================================================================
ipv6_address::ipv6_address()
{
  mem_zero(bytes, sizeof(bytes));
}
//----

ipv6_address::ipv6_address(uint32_t d0_, uint32_t d1_, uint32_t d2_, uint32_t d3_)
{
  dwords[0]=to_big_endian(d0_);
  dwords[1]=to_big_endian(d1_);
  dwords[2]=to_big_endian(d2_);
  dwords[3]=to_big_endian(d3_);
}
//----

ipv6_address::ipv6_address(uint16_t d0_, uint16_t d1_, uint16_t d2_, uint16_t d3_,
                           uint16_t d4_, uint16_t d5_, uint16_t d6_, uint16_t d7_)
{
  words[0]=to_big_endian(d0_);
  words[1]=to_big_endian(d1_);
  words[2]=to_big_endian(d2_);
  words[3]=to_big_endian(d3_);
  words[4]=to_big_endian(d4_);
  words[5]=to_big_endian(d5_);
  words[6]=to_big_endian(d6_);
  words[7]=to_big_endian(d7_);
}
//----

ipv6_address::ipv6_address(const ipv4_address &ip_)
{
  dwords[0]=0;
  dwords[1]=0;
  dwords[2]=PFC_TO_BIG_ENDIAN_U32(0xffff);
  dwords[3]=ip_.dword;
}
//----------------------------------------------------------------------------

PFC_INLINE bool operator==(const ipv6_address &a0_, const ipv6_address &a1_)
{
  return mem_eq(&a0_, &a1_, sizeof(ipv6_address));
}
//----

PFC_INLINE bool operator!=(const ipv6_address &a0_, const ipv6_address &a1_)
{
  return !mem_eq(&a0_, &a1_, sizeof(ipv6_address));
}
//----------------------------------------------------------------------------


//============================================================================
// inetv4_socket_address
//============================================================================
inetv4_socket_address::inetv4_socket_address()
  :port(0)
{
}
//----

inetv4_socket_address::inetv4_socket_address(const ipv4_address &ip_, uint16_t port_)
  :ip(ip_)
  ,port(port_)
{
}
//----------------------------------------------------------------------------

PFC_INLINE bool operator==(const inetv4_socket_address &sa0_, const inetv4_socket_address &sa1_)
{
  return sa0_.port==sa1_.port && mem_eq(&sa0_.ip, &sa1_.ip, sizeof(inetv4_socket_address));
}
//----

PFC_INLINE bool operator!=(const inetv4_socket_address &sa0_, const inetv4_socket_address &sa1_)
{
  return sa0_.port!=sa1_.port || !mem_eq(&sa0_.ip, &sa1_.ip, sizeof(inetv4_socket_address));
}
//----------------------------------------------------------------------------


//============================================================================
// inetv6_socket_address
//============================================================================
inetv6_socket_address::inetv6_socket_address()
  :port(0)
{
}
//----

inetv6_socket_address::inetv6_socket_address(const ipv6_address &ip_, uint16_t port_)
  :ip(ip_)
  ,port(port_)
{
}
//----------------------------------------------------------------------------

PFC_INLINE bool operator==(const inetv6_socket_address &sa0_, const inetv6_socket_address &sa1_)
{
  return sa0_.port==sa1_.port && mem_eq(&sa0_.ip, &sa1_.ip, sizeof(inetv6_socket_address));
}
//----

PFC_INLINE bool operator!=(const inetv6_socket_address &sa0_, const inetv6_socket_address &sa1_)
{
  return sa0_.port!=sa1_.port || !mem_eq(&sa0_.ip, &sa1_.ip, sizeof(inetv6_socket_address));
}
//----------------------------------------------------------------------------


//============================================================================
// inet_system_base
//============================================================================
void inet_system_base::set_active(inet_system_base *fs_)
{
  PFC_CHECK_MSG(!s_active || !fs_, ("Internet system has already been activated\r\n"));
  s_active=fs_;
}
//----

inet_system_base &inet_system_base::active()
{
  PFC_ASSERT_PEDANTIC_MSG(s_active, ("No internet system has been activated\r\n"));
  return *s_active;
}
//----------------------------------------------------------------------------


//============================================================================
// inet_socket_base
//============================================================================
inet_socket_base::inet_socket_base()
{
}
//----

inet_socket_base::~inet_socket_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// inet_socket_local_base
//============================================================================
inet_socket_local_base::inet_socket_local_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// inet_socket_remote_base
//============================================================================
inet_socket_remote_base::inet_socket_remote_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// inet_input_stream
//============================================================================
bool inet_input_stream::has_timeouted() const
{
  return m_has_timeouted;
}
//----

void inet_input_stream::reset_timeout()
{
  m_has_timeouted=false;
}
//----------------------------------------------------------------------------


//============================================================================
// inet_output_stream
//============================================================================
bool inet_output_stream::has_timeouted() const
{
  return m_has_timeouted;
}
//----

void inet_output_stream::reset_timeout()
{
  m_has_timeouted=false;
}
//----------------------------------------------------------------------------


//============================================================================
// is_valid
//============================================================================
bool is_valid(const ipv4_address &ip_)
{
  return !!ip_.dword;
}
//----

bool is_valid(const ipv6_address &ip_)
{
  return ip_.dwords[0] || ip_.dwords[1] || ip_.dwords[2] || ip_.dwords[3];
}
//----------------------------------------------------------------------------


//============================================================================
// simple_inet_data_protocol_socket::data_reader_base
//============================================================================
struct simple_inet_data_protocol_socket::data_reader_base
{
  virtual bool read(inet_input_stream&) const=0;
};
//----------------------------------------------------------------------------


//============================================================================
// simple_inet_data_protocol_socket::data_reader
//============================================================================
template<class T>
struct simple_inet_data_protocol_socket::data_reader: data_reader_base
{
  data_reader(const functor<void(const T&)>&);
  virtual bool read(inet_input_stream&) const;
  const functor<void(const T&)> handler;
};
//----------------------------------------------------------------------------

template<class T>
simple_inet_data_protocol_socket::data_reader<T>::data_reader(const functor<void(const T&)> &handler_)
  :handler(handler_)
{
}
//----

template<class T>
bool simple_inet_data_protocol_socket::data_reader<T>::read(inet_input_stream &stream_) const
{
  // read the object and evaluate the type handler
  T v;
  stream_>>v;
  if(stream_.has_timeouted())
    return false;
  handler(v);
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// simple_inet_data_protocol_socket::registered_local_type
//============================================================================
struct simple_inet_data_protocol_socket::registered_local_type
{
  heap_str type_name;
  poly_pod_variant<data_reader_base, ptr_size*4> reader;
};
//----------------------------------------------------------------------------


//============================================================================
// simple_inet_data_protocol_socket
//============================================================================
template<class T>
void simple_inet_data_protocol_socket::register_input_type_handler(const functor<void(const T&)> &handler_, const char *alt_name_)
{
  registered_local_type &lt=m_registered_local_types.push_back();
  lt.type_name=alt_name_?alt_name_:class_typename((T*)0);
  PFC_ASSERT(lt.type_name.size()<256);
  lt.reader=data_reader<T>(handler_);
}
//----

bool simple_inet_data_protocol_socket::is_alive() const
{
  return m_connection_state==constate_connected && (!m_timeout || get_global_time()-m_last_keepalive_signal_recv<m_timeout);
}
//----

void simple_inet_data_protocol_socket::set_timeout(udouble_t timeout_)
{
  m_timeout=timeout_;
  m_stream_in.set_timeout(0, timeout_);
  m_stream_out.set_timeout(0, timeout_);
}
//----

void simple_inet_data_protocol_socket::reset_timeout()
{
  m_last_keepalive_signal_recv=get_global_time();
  m_stream_in.reset_timeout();
  m_stream_out.reset_timeout();
}
//----------------------------------------------------------------------------

template<class T>
bool simple_inet_data_protocol_socket::write(const T &v_, const char *alt_name_)
{
  // check for a type that is processed by the remote socket
  if(m_connection_state!=constate_connected)
    return false;
  const char *type_name=alt_name_?alt_name_:class_typename((T*)0);
  auto it=m_registered_remote_types.find(type_name);
  if(!is_valid(it))
    return false;

  // ensure proper data pacing from the receiver
  while(((m_pacing_id_recv-m_pacing_id_sent)&0x7f)>1)
    if(!process_input_data())
      return false;

  // write type id and object data
  uint16_t id=*it;
  m_stream_out<<id<<v_;

  // check for sending the pacing signal
  usize_t so_pos=m_stream_out.pos();
  if(so_pos>=m_pacing_pos_next)
  {
    m_stream_out<<uint16_t(0xfffe)<<uint8_t(++m_pacing_id_sent|0x80);
    m_pacing_pos_next=so_pos+m_pacing_window_size;
  }

  // flush the data to the socket and check for timeout
  m_stream_out.flush();
  if(m_stream_out.has_timeouted())
    m_connection_state=constate_disconnected;
  m_last_keepalive_signal_sent=get_global_time();
  return m_connection_state==constate_connected;
}
//----------------------------------------------------------------------------
