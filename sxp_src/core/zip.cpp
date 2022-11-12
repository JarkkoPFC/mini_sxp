//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "zip.h"
#ifdef PFC_ENGINEOP_ZLIB
#include "sxp_extlibs/zlib/src/zlib.h"
#endif
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// external library dependencies
//============================================================================
// zlib
#ifdef PFC_ENGINEOP_ZLIB
#pragma comment(lib, PFC_STR(PFC_CAT2(zlib_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
#endif
//----------------------------------------------------------------------------


//============================================================================
// zip_input_stream
//============================================================================
zip_input_stream::zip_input_stream(bin_input_stream_base &s_, usize_t stream_size_)
  :m_stream(s_)
  ,m_stream_size(stream_size_)
{
  init_stream();
  inflateInit2(&m_state, MAX_WBITS);
}
//----------------------------------------------------------------------------

usize_t zip_input_stream::update_buffer_impl(void *p_, usize_t num_bytes_, bool exact_)
{
  usize_t num_total_bytes=0;
/*  if(num_bytes_>uncompressed_buffer_size)
  {
    // todo: optimize for direct read
    PFC_ERROR_NOT_IMPL();
  }
  else*/
  {
    // decompress data to a buffer
    uint8_t *input_buffer=m_buffer_uncompressed;
    usize_t input_buffer_size=uncompressed_buffer_size;
    usize_t bytes_to_copy=num_bytes_;
    bool is_stream_end=false;
    do
    {
      m_state.next_out=(Bytef*)m_buffer_uncompressed;
      m_state.avail_out=uncompressed_buffer_size;
      if(!m_state.avail_in)
      {
        // read more compressed data
        unsigned compressed_data_left=min<unsigned>(compressed_buffer_size, unsigned(m_stream_size-m_state.total_in));
        m_stream.read_bytes(m_buffer_compressed, compressed_data_left);
        m_state.next_in=(Bytef*)m_buffer_compressed;
        m_state.avail_in=compressed_data_left;
      }

      // extract data
      is_stream_end=inflate(&m_state, Z_NO_FLUSH)==Z_STREAM_END;

      // copy data from input buffer to the target
      usize_t num_bytes=min(bytes_to_copy, input_buffer_size-m_state.avail_out);
      PFC_CHECK_MSG(num_bytes, ("ZIP data is corrupted\r\n"));
      mem_copy(p_, input_buffer, num_bytes);
      (uint8_t*&)p_+=num_bytes;
      bytes_to_copy-=num_bytes;
      num_total_bytes+=num_bytes;

      // update stream state
      m_begin_pos+=usize_t(m_end-m_begin);
      m_is_first=m_is_first&&m_begin!=0;
      m_is_last=is_stream_end;
      m_begin=input_buffer;
      m_end=m_begin+input_buffer_size-m_state.avail_out;
      m_data=m_begin+num_bytes;
    } while(num_total_bytes<num_bytes_ && !is_stream_end);
  }

  // check for valid result
  PFC_CHECK_MSG(!exact_ || num_total_bytes==num_bytes_, ("Trying to the read beyond end of the file\r\n"));
  return num_total_bytes;
}
//----

void zip_input_stream::rewind_impl()
{
  init_stream();
  inflateReset(&m_state);
}
//----

void zip_input_stream::rewind_impl(usize_t num_bytes_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
}
//----

void zip_input_stream::skip_impl()
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
}
//----

void zip_input_stream::seek_impl(usize_t abs_pos_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
}
//----------------------------------------------------------------------------

void zip_input_stream::init_stream()
{
  // read initial data to the compressed buffer
  unsigned compressed_data_left=min<unsigned>(compressed_buffer_size, unsigned(m_stream_size));
  m_stream.read_bytes(m_buffer_compressed, compressed_data_left);
  m_is_last=compressed_data_left==0;

  // initialize decompression
  m_state.next_in=(Bytef*)m_buffer_compressed;
  m_state.avail_in=compressed_data_left;
  m_state.next_out=(Bytef*)m_buffer_uncompressed;
  m_state.avail_out=uncompressed_buffer_size;
  m_state.zalloc=alloc;
  m_state.zfree=free;
  m_state.opaque=0;
}
//----

void *zip_input_stream::alloc(void*, unsigned items_, unsigned size_)
{
  return PFC_MEM_ALLOC(usize_t(items_)*usize_t(size_));
}
//----

void zip_input_stream::free(void*, void *data_)
{
  PFC_MEM_FREE(data_);
}
//----------------------------------------------------------------------------


//============================================================================
// zip_output_stream
//============================================================================
zip_output_stream::zip_output_stream(bin_output_stream_base &s_)
  :m_stream(s_)
{
  init_stream();
  PFC_VERIFY_MSG(deflateInit2(&m_state, Z_DEFAULT_COMPRESSION, Z_DEFLATED, MAX_WBITS, 8, Z_DEFAULT_STRATEGY)>=0,
                 ("ZIP data compression initialization failed\r\n"));
}
//----

zip_output_stream::~zip_output_stream()
{
  flush_buffer_impl(0, 0);
}
//----------------------------------------------------------------------------

void zip_output_stream::flush_buffer_impl(const void *p_, usize_t num_bytes_)
{
  // fill remaining buffer for compression
  usize_t num_buffer_bytes=usize_t(m_data-m_begin);
  usize_t copied_bytes=num_buffer_bytes?min(num_bytes_, uncompressed_buffer_size-num_buffer_bytes):0;
  mem_copy(m_data, p_, copied_bytes);
  m_data+=copied_bytes;
  (const uint8_t*&)p_+=copied_bytes;
  num_bytes_-=copied_bytes;

  // deflate the buffer
  uint8_t compressed_buffer[compressed_buffer_size];
  if(unsigned buf_size=unsigned(m_data-m_begin))
  {
    m_state.next_in=m_begin;
    m_state.avail_in=buf_size;
    m_state.next_out=compressed_buffer;
    m_state.avail_out=compressed_buffer_size;
    PFC_VERIFY_MSG(deflate(&m_state, Z_FINISH)>=0,
                    ("ZIP data compression failed\r\n"));
    m_stream.write_bytes(compressed_buffer, compressed_buffer_size-m_state.avail_out);
    m_begin_pos+=buf_size;
  }

  // deflate passed data in chunks if too big to fit into the buffer
  m_state.avail_in=unsigned(num_bytes_);
  m_state.next_in=(Bytef*)p_;
  while(m_state.avail_in>compressed_buffer_size)
  {
    m_state.next_out=compressed_buffer;
    m_state.avail_out=compressed_buffer_size;
    unsigned prev_avail_in=m_state.avail_in;
    PFC_VERIFY_MSG(deflate(&m_state, Z_FINISH)>=0,
                    ("ZIP data compression failed\r\n"));
    m_stream.write_bytes(compressed_buffer, compressed_buffer_size-m_state.avail_out);
    m_begin_pos+=prev_avail_in-m_state.avail_in;
  }

  // copy remaining data to the buffer
  m_data=m_buffer_uncompressed+m_state.avail_in;
  mem_copy(m_buffer_uncompressed, m_state.next_in, m_state.avail_in);
}
//----------------------------------------------------------------------------

void zip_output_stream::init_stream()
{
  // initialize buffer pointers
  m_begin=m_data=m_buffer_uncompressed;
  m_end=m_begin+uncompressed_buffer_size;
  m_begin_pos=0;
  
  // initialize compression
  m_state.next_in=0;
  m_state.avail_in=0;
  m_state.next_out=0;
  m_state.avail_out=0;
  m_state.zalloc=alloc;
  m_state.zfree=free;
  m_state.opaque=0;
}
//----

void *zip_output_stream::alloc(void*, unsigned items_, unsigned size_)
{
  return PFC_MEM_ALLOC(usize_t(items_)*usize_t(size_));
}
//----

void zip_output_stream::free(void*, void *data_)
{
  PFC_MEM_FREE(data_);
}
//----------------------------------------------------------------------------
