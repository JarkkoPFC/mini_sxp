//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_ZIP_H
#define PFC_CORE_ZIP_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "streams.h"
#include "sxp_extlibs/zlib/src/zlib.h"
namespace pfc
{

// new
class zip_input_stream;
class zip_output_stream;
//----------------------------------------------------------------------------


//============================================================================
// zip_input_stream
//============================================================================
class zip_input_stream: public bin_input_stream_base
{
public:
  // construction
  zip_input_stream(bin_input_stream_base&, usize_t stream_size_);
  virtual ~zip_input_stream();
  //--------------------------------------------------------------------------

private:
  zip_input_stream(const zip_input_stream&); // not implemented
  void operator=(const zip_input_stream&); // not implemented
  //--------------------------------------------------------------------------

  // stream implementation
  virtual usize_t update_buffer_impl(void*, usize_t num_bytes_, bool exact_);
  virtual void rewind_impl();
  virtual void rewind_impl(usize_t num_bytes_);
  virtual void skip_impl();
  virtual void seek_impl(usize_t abs_pos_);
  //--------------------------------------------------------------------------

  // helpers
  void init_stream();
  static void *alloc(void*, unsigned items_, unsigned size_);
  static void free(void*, void *data_);
  //--------------------------------------------------------------------------

  enum {compressed_buffer_size=4096};
  enum {uncompressed_buffer_size=4096};
  bin_input_stream_base &m_stream;
  usize_t m_stream_size;
  z_stream m_state;
  uint8_t m_buffer_compressed[compressed_buffer_size];
  uint8_t m_buffer_uncompressed[uncompressed_buffer_size];
};
//----------------------------------------------------------------------------


//============================================================================
// zip_output_stream
//============================================================================
class zip_output_stream: public bin_output_stream_base
{
public:
  // construction
  zip_output_stream(bin_output_stream_base&);
  virtual ~zip_output_stream();
  //--------------------------------------------------------------------------

private:
  zip_output_stream(const zip_output_stream&); // not implemented
  void operator=(const zip_output_stream&); // not implemented
  //--------------------------------------------------------------------------

  // stream implementation
  virtual void flush_buffer_impl(const void*, usize_t num_bytes_);
  //--------------------------------------------------------------------------

  // helpers
  void init_stream();
  static void *alloc(void*, unsigned items_, unsigned size_);
  static void free(void*, void *data_);
  //--------------------------------------------------------------------------

  enum {uncompressed_buffer_size=4096};
  enum {compressed_buffer_size=uncompressed_buffer_size};
  bin_output_stream_base &m_stream;
  z_stream m_state;
  uint8_t m_buffer_uncompressed[uncompressed_buffer_size];
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
