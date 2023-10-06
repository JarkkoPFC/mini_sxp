//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "inet.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// is_ipv4
//============================================================================
bool pfc::is_ipv4(const ipv6_address &ip_)
{
  return    (!ip_.dwords[0] && !ip_.dwords[1] && !ip_.dwords[2] && ip_.dwords[3]==PFC_TO_BIG_ENDIAN_U32(1))
         || (!ip_.dwords[0] && !ip_.dwords[1] && ip_.dwords[2]==PFC_TO_BIG_ENDIAN_U32(0xffff));
}
//----------------------------------------------------------------------------


//============================================================================
// ipv4_to_str/ipv6_to_str
//============================================================================
ip_str pfc::ipv4_to_str(const ipv4_address &ip_)
{
  // format IPv4
  ip_str str;
  str.format("%i.%i.%i.%i", ip_.bytes[0], ip_.bytes[1], ip_.bytes[2], ip_.bytes[3]);
  return str;
}
//----

ip_str pfc::ipv6_to_str(const ipv6_address &ip_)
{
  // format IPv6 address with zero compression
  ip_str str='[';
  bool zero_compressed=false, is_compression=false;
  for(unsigned i=0; i<8; ++i)
  {
    if(!ip_.words[i] && !zero_compressed)
      is_compression=true;
    else
    {
      if(is_compression)
      {
        is_compression=false;
        zero_compressed=true;
        str.push_back(':');
      }
      str.push_back_format(i?":%x":"%x", to_big_endian(ip_.words[i]));
    }
  }
  if(is_compression && !zero_compressed)
    str+="::";
  str+=']';
  return str;
}
//----

ip_str pfc::ipv6_to_simple_str(const ipv6_address &ip_)
{
  return is_ipv4(ip_)?ipv4_to_str(ip_):ipv6_to_str(ip_);
}
//----------------------------------------------------------------------------


//============================================================================
// inet_system_base
//============================================================================
inet_system_base *inet_system_base::s_active=0;
//----------------------------------------------------------------------------

inet_system_base::inet_system_base(bool set_active_)
{
  if(set_active_)
    set_active(this);
}
//----

inet_system_base::~inet_system_base()
{
  if(s_active==this)
    s_active=0;
}
//----------------------------------------------------------------------------

owner_ref<inet_socket_local_base> inet_system_base::create_local_socket(unsigned port_, unsigned max_backlog_, const ipv6_address *ip_)
{
  owner_ref<inet_socket_local_base> socket=create_local_socket();
  socket->bind(port_, max_backlog_, ip_);
  return socket;
}
//----

owner_ptr<inet_socket_remote_base> inet_system_base::create_remote_socket(const ipv6_address &host_, unsigned port_)
{
  // create socket and try to connect to the host
  owner_ref<inet_socket_remote_base> socket=create_remote_socket();
  if(!socket->connect(host_, port_))
    return 0;
  return socket;
}
//----------------------------------------------------------------------------


//============================================================================
// inet_input_stream
//============================================================================
inet_input_stream::inet_input_stream(inet_socket_base &socket_)
  :m_socket(socket_)
{
  m_is_last=false;
  m_has_timeouted=false;
  m_timeout_max_spb=0;
  m_timeout_max_request_time=0;
}
//----

void inet_input_stream::set_timeout_threshold(unsigned min_bytes_per_sec_, udouble_t max_request_time_)
{
  // setup threshold values for timeout
  m_timeout_max_spb=min_bytes_per_sec_?1.0/min_bytes_per_sec_:0.0;
  m_timeout_max_request_time=max_request_time_;
}
//----------------------------------------------------------------------------

usize_t inet_input_stream::update_buffer_impl(void *p_, usize_t num_bytes_, bool exact_)
{
  // check for timeout and setup timeout times
  if(m_has_timeouted)
    return 0;
  udouble_t timeout_time=m_timeout_max_request_time+num_bytes_*m_timeout_max_spb;
  udouble_t start_time=timeout_time?get_global_time():0.0;
  udouble_t end_time=start_time+timeout_time;

  // try to fill the data buffer by at least the number of needed bytes
  uint8_t *const buf_begin=num_bytes_>=buffer_size?(uint8_t*)p_:m_buffer, *buf=buf_begin;
  usize_t num_bytes_left=max(num_bytes_, usize_t(buffer_size));
  while(true)
  {
    // read data to the buffer
    usize_t num_bytes_read=m_socket.read(buf, num_bytes_left);
    num_bytes_left-=num_bytes_read;
    buf+=num_bytes_read;

    // check if read is completed
    if(!num_bytes_left || !exact_ || usize_t(buf-buf_begin)>=num_bytes_)
      break;

    // check for timeout
    if(timeout_time)
    {
      udouble_t cur_time=get_global_time();
      if(cur_time>end_time)
      {
        m_has_timeouted=true;
        PFC_WARNF("Read from the internet stream timeouted after %f seconds\r\n", cur_time-start_time);
        break;
      }
    }
    thread_nap();
  }

  // setup stream state
  usize_t num_total_bytes_read=usize_t(buf-buf_begin);
  m_is_first=m_is_first && !num_total_bytes_read;
  m_begin_pos+=num_total_bytes_read;
  m_begin=m_end=m_data=0;
  if(num_bytes_<buffer_size)
  {
    // copy data from buffer to the pointer
    usize_t num_bytes_copied=min(num_total_bytes_read, num_bytes_);
    mem_copy(p_, m_buffer, num_bytes_copied);
    m_begin=m_buffer;
    m_end=m_buffer+num_total_bytes_read;
    m_data=m_buffer+num_bytes_copied;
  }
  return num_total_bytes_read;
}
//----

void inet_input_stream::rewind_impl()
{
  PFC_ERROR("Unable to rewind internet input stream\r\n");
}
//----

void inet_input_stream::rewind_impl(usize_t num_bytes_)
{
  PFC_ERROR("Unable to rewind internet input stream\r\n");
}
//----

void inet_input_stream::skip_impl()
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
}
//----

void inet_input_stream::seek_impl(usize_t abs_pos_)
{
  PFC_ASSERT_MSG(abs_pos_>=m_begin_pos, ("Unable to rewind internet input stream\r\n"));
  /*todo*/
  PFC_ERROR_NOT_IMPL();
}
//----------------------------------------------------------------------------


//============================================================================
// inet_output_stream
//============================================================================
inet_output_stream::inet_output_stream(inet_socket_base &socket_)
  :m_socket(socket_)
{
  m_has_timeouted=false;
  m_timeout_max_spb=0;
  m_timeout_max_request_time=0;
}
//----

inet_output_stream::~inet_output_stream()
{
  flush_buffer_impl(0, 0);
}
//----

void inet_output_stream::set_timeout_threshold(unsigned min_bytes_per_sec_, udouble_t max_request_time_)
{
  // setup threshold values for timeout
  m_timeout_max_spb=min_bytes_per_sec_?1.0/min_bytes_per_sec_:0.0;
  m_timeout_max_request_time=max_request_time_;
}
//----------------------------------------------------------------------------

void inet_output_stream::flush_buffer_impl(const void *p_, usize_t num_bytes_)
{
  // flush content of the data buffer
  if(m_has_timeouted)
    return;
  usize_t num_bytes_write=write_data(m_begin, usize_t(m_data-m_begin));
  m_begin_pos+=num_bytes_write;
  m_begin+=num_bytes_write;
  if(m_has_timeouted)
    return;

  // handle data in the given pointer
  if(num_bytes_>=buffer_size)
  {
    // write data directly to the socket
    usize_t num_bytes_write=write_data((const uint8_t*)p_, num_bytes_);
    m_begin_pos+=num_bytes_write;
    if(!m_has_timeouted)
      m_begin=m_end=m_data=0;
  }
  else
  {
    // copy data to the buffer
    mem_copy(m_buffer, p_, num_bytes_);
    m_begin=m_buffer;
    m_end=m_buffer+buffer_size;
    m_data=m_begin+num_bytes_;
  }
}
//----

usize_t inet_output_stream::write_data(const uint8_t *p_, usize_t num_bytes_)
{
  // check for number of bytes
  if(!num_bytes_)
    return 0;
  PFC_ASSERT(p_);

  // setup timeout times and write the given data to the socket
  udouble_t timeout_time=m_timeout_max_request_time+num_bytes_*m_timeout_max_spb;
  udouble_t start_time=timeout_time?get_global_time():0.0;
  udouble_t end_time=start_time+timeout_time;
  const uint8_t *buf=p_;
  while(true)
  {
    // write to the socket
    usize_t num_bytes_write=m_socket.write(buf, num_bytes_);
    num_bytes_-=num_bytes_write;
    buf+=num_bytes_write;
    if(!num_bytes_)
      break;

    // check for timeout
    if(timeout_time)
    {
      udouble_t cur_time=get_global_time();
      if(cur_time>end_time)
      {
        m_has_timeouted=true;
        PFC_WARNF("Write to the internet stream timeouted after %f seconds\r\n", cur_time-start_time);
        break;
      }
    }
    thread_nap();
  }
  return usize_t(p_-buf);
}
//----------------------------------------------------------------------------


//============================================================================
// simple_data_protocol_socket
//============================================================================
simple_data_protocol_socket::simple_data_protocol_socket(inet_socket_base &socket_, udouble_t keepalive_timeout_)
  :m_socket(socket_)
  ,m_stream_out(socket_)
  ,m_stream_in(socket_)
  ,m_keepalive_timeout(keepalive_timeout_)
  ,m_use_type_info(false)
  ,m_connection_state(constate_unconnected)
  ,m_last_keepalive_signal_recv(0.0)
  ,m_last_keepalive_signal_sent(0.0)
{
  PFC_ASSERT(keepalive_timeout_>=0.0);
  if(keepalive_timeout_)
  {
    m_stream_out.set_timeout_threshold(1024, keepalive_timeout_);
    m_stream_in.set_timeout_threshold(1024, keepalive_timeout_);
  }
}
//----

bool simple_data_protocol_socket::connect()
{
  // check that the socket is in "clean" unconnected state
  if(m_connection_state!=constate_unconnected)
    return false;
  m_connection_state=constate_disconnected; // if the connection fails while trying to connect, stay in disconnected state

  // check for proper protocol connection
  enum {sidp_id=PFC_LE_FOURCC_ID('S', 'I', 'D', 'P')};
  enum {sidp_version=0x1000};
  m_stream_out<<uint32_t(sidp_id)<<uint16_t(sidp_version);
  m_stream_out.flush();
  uint32_t id;
  uint16_t version;
  m_stream_in>>id>>version;
  if(id!=sidp_id)
  {
    errorf("Invalid Simple Data Protocol Socket ID: 0x%8x (expecting 0x%8x)\r\n", id, sidp_id);
    return false;
  }
  if(version!=sidp_version)
  {
    errorf("Invalid Simple Data Protocol version: v%s (expecting v%s)\r\n", bcd16_version_str(version).c_str(), bcd16_version_str(sidp_version).c_str());
    return false;
  }

  {
    // send registered local type names to the remote socket
    unsigned num_reg_types=(unsigned)m_registered_local_types.size();
    m_stream_out<<uint16_t(num_reg_types);
    for(unsigned i=0; i<num_reg_types; ++i)
      m_stream_out<<m_registered_local_types[i].type_name.c_str()<<'\0';
    m_stream_out.flush();
    if(m_stream_out.has_timeouted())
      return false;
  }

  {
    // read registered remote type names from the remote socket
    uint16_t num_reg_types;
    m_stream_in>>num_reg_types;
    if(m_stream_in.has_timeouted())
      return false;
    for(unsigned i=0; i<num_reg_types; ++i)
    {
      char type_name[256];
      m_stream_in.read_cstr(type_name, sizeof(type_name));
      if(m_stream_in.has_timeouted())
        return false;
      m_registered_remote_types.insert(type_name, uint16_t(i));
    }
  }

  // setup initial keepalive time stamps
  udouble_t time=get_global_time();
  m_last_keepalive_signal_sent=time;
  m_last_keepalive_signal_recv=time;
  m_connection_state=constate_connected;
  return true;
}
//----

void simple_data_protocol_socket::disconnect()
{
  m_connection_state=constate_disconnected;
}
//----------------------------------------------------------------------------

bool simple_data_protocol_socket::process_input_data()
{
  // check for sending keepalive signal
  if(m_connection_state!=constate_connected)
    return false;
  udouble_t time=get_global_time();
  if(m_keepalive_timeout && time-m_last_keepalive_signal_sent>m_keepalive_timeout*0.5)
  {
    m_stream_out<<uint16_t(0xffff);
    m_stream_out.flush();
    if(m_stream_out.has_timeouted())
    {
      m_connection_state=constate_disconnected;
      return false;
    }
    m_last_keepalive_signal_sent=time;
  }

  // try to read the inet type id
  uint16_t type_id;
  if(!m_stream_in.read_bytes(&type_id, 2, false))
    return false;
  m_last_keepalive_signal_recv=time;

  // check for keepalive signal or invalid ID
  if(type_id==0xffff) // keepalive signal
    return false;
  if(type_id>=m_registered_local_types.size())
  {
    // invalid ID, disconnect
    m_socket.disconnect();
    m_connection_state=constate_disconnected;
    return false;
  }

  // read and process the object
  if(!m_registered_local_types[type_id].reader->read(m_stream_in))
    m_connection_state=constate_disconnected;
  return m_connection_state==constate_connected;
}
//----------------------------------------------------------------------------
