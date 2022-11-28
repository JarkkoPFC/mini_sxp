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
        PFC_WARNF("Read from the internet stream timeouted after %f seconds\r\n", cur_time-start_time);
        break;
      }
    }
    thread_nap();
  }
  return usize_t(p_-buf);
}
//----------------------------------------------------------------------------
