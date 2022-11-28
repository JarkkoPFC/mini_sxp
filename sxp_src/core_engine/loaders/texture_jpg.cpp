//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/texture.h"
using namespace pfc;
//----------------------------------------------------------------------------

#ifdef PFC_ENGINEOP_JPEGLIB
#define XMD_H
#ifdef FAR
#undef FAR
#endif
extern "C"
{
#include "sxp_extlibs/jpeglib/src/jpeglib.h"
}
#pragma comment(lib, PFC_STR(PFC_CAT2(jpeglib_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
//----------------------------------------------------------------------------


//============================================================================
// error & massege management
//============================================================================
static void jpg_error_exit(j_common_ptr cinfo_)
{
  // output error and abort
  char buf[JMSG_LENGTH_MAX];
  (*cinfo_->err->format_message)(cinfo_, buf);
  jpeg_destroy(cinfo_);
  PFC_ERRORF("JPEG error: %s\r\n", buf);
}
//----

static void jpg_output_message(j_common_ptr cinfo_)
{
  char buf[JMSG_LENGTH_MAX];
  (*cinfo_->err->format_message)(cinfo_, buf);
  PFC_LOGF("JPEG: %s\r\n", buf);
}
//----------------------------------------------------------------------------


//============================================================================
// texture_loader_jpg
//============================================================================
class texture_loader_jpg: public texture_loader::loader_base
{
public:
  // construction
  texture_loader_jpg(texture_loader&);
  //--------------------------------------------------------------------------

  // data loading
  virtual bool layer(texture_layer&) const;
  virtual void load_layer(void*, unsigned pitch_);
  virtual void skip_layer();
  //--------------------------------------------------------------------------

private:
  void operator=(const texture_loader_jpg&); // not implemented
  //--------------------------------------------------------------------------

  //==========================================================================
  // texture_loader_jpg::jpeg_loader_source
  //==========================================================================
  struct jpeg_loader_source: jpeg_source_mgr
  {
    enum {buffer_size=4096};
    bin_input_stream_base *stream;
    uint8_t buffer[buffer_size];
    //----

    static void init_source_func(j_decompress_ptr);
    static boolean fill_input_buffer_func(j_decompress_ptr);
    static void skip_input_data_func(j_decompress_ptr, long num_bytes);
    static void term_source_func(j_decompress_ptr);
  };
  //--------------------------------------------------------------------------

  texture_loader &m_loader;
  bool m_has_layer;
};
//----------------------------------------------------------------------------

//============================================================================
// texture_loader_jpg::jpeg_loader_source
//============================================================================
void texture_loader_jpg::jpeg_loader_source::init_source_func(j_decompress_ptr)
{
}
//----

boolean texture_loader_jpg::jpeg_loader_source::fill_input_buffer_func(j_decompress_ptr cinfo_)
{
  // read data from the stream
  jpeg_loader_source *src=(jpeg_loader_source*)cinfo_->src;
  unsigned num_bytes=(unsigned)src->stream->read_bytes(src->buffer, buffer_size, false);
  if(!num_bytes)
  {
    src->buffer[0]=uint8_t(0xff);
    src->buffer[1]=uint8_t(JPEG_EOI);
    num_bytes=2;
  }

  // setup buffer
  src->next_input_byte=(JOCTET*)src->buffer;
  src->bytes_in_buffer=num_bytes;
  return TRUE;
}
//----

void texture_loader_jpg::jpeg_loader_source::skip_input_data_func(j_decompress_ptr cinfo_, long num_bytes_)
{
  // skip bytes in the buffer/stream
  jpeg_loader_source *src=(jpeg_loader_source*)cinfo_->src;
  unsigned skip_bytes=min(long(src->bytes_in_buffer), num_bytes_);
  src->bytes_in_buffer-=skip_bytes;
  src->next_input_byte=src->bytes_in_buffer?src->next_input_byte+skip_bytes:0;
  src->stream->skip(num_bytes_-skip_bytes);
}
//----

void texture_loader_jpg::jpeg_loader_source::term_source_func(j_decompress_ptr)
{
}
//----------------------------------------------------------------------------

texture_loader_jpg::texture_loader_jpg(texture_loader &l_)
  :m_loader(l_)
{
  // parse JPG width and height info
  unsigned width=0;
  unsigned height=0;
  {
    bin_input_stream_base &stream=m_loader.stream();
    auto_stream_seek<bin_input_stream_base> aseek(stream);
    uint16_t id;
    stream>>id;
    for(;;)
    {
      // parse JPG data
      uint8_t tag;
      uint16_t length;
      stream>>tag;
      PFC_CHECK_MSG(tag==0xff, ("Invalid JPG tag\r\n"));
      stream>>tag>>length;
      length=swap_bytes(length)-2;
      auto_stream_seek<bin_input_stream_base> aseek2(stream, length);
      if((tag&0xfc)==0xc0)
      {
        // read width and height
        uint8_t sample_precision, num_components;
        uint16_t w, h;
        stream>>sample_precision>>h>>w>>num_components;
        width=swap_bytes(w);
        height=swap_bytes(h);
        switch(num_components)
        {
          case 1: m_loader.set_source_format(texfmt_a8); break;
          case 3: m_loader.set_source_format(texfmt_b8g8r8); break;
          default: PFC_ERRORF("Unsupported number of JPG color components (%i)\r\n", num_components);
        }
        break;
      }
    }
  }

  // set texture type
  m_loader.set_source_type(textype_2d);
  m_loader.set_source_size(width, height);
  m_has_layer=true;
}
//----------------------------------------------------------------------------

bool texture_loader_jpg::layer(texture_layer &l_) const
{
  l_=texture_layer();
  return m_has_layer;
}
//----

void texture_loader_jpg::load_layer(void *data_, unsigned pitch_)
{
  // check for available layer
  if(!m_has_layer)
    return;

  // setup error management and initialize JPG decompression
  jpeg_decompress_struct cinfo;
  jpeg_error_mgr err;
  jpeg_std_error(&err);
  err.error_exit=jpg_error_exit;
  err.output_message=jpg_output_message;
  cinfo.err=&err;
  jpeg_create_decompress(&cinfo);

  // setup data source
  jpeg_loader_source src;
  cinfo.src=&src;
  src.init_source=jpeg_loader_source::init_source_func;
  src.fill_input_buffer=jpeg_loader_source::fill_input_buffer_func;
  src.skip_input_data=jpeg_loader_source::skip_input_data_func;
  src.resync_to_restart=jpeg_resync_to_restart;
  src.term_source=jpeg_loader_source::term_source_func;
  src.bytes_in_buffer=0;
  src.next_input_byte=0;
  src.stream=&m_loader.stream();

  // read the image
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);
  e_texture_format src_format=m_loader.format();
  e_texture_format dst_format=m_loader.target_format();
  if(src_format==dst_format)
  {
    // read image directly to the target buffer
    while(cinfo.output_scanline<cinfo.output_height)
    {
      jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&data_, 1);
      (uint8_t*&)data_+=pitch_;
    }
  }
  else
  {
    // read image to temp buffer and convert to the target buffer
    unsigned width=m_loader.width();
    owner_data buf=PFC_MEM_ALLOC(cinfo.output_width*cinfo.output_components);
    while(cinfo.output_scanline<cinfo.output_height)
    {
      jpeg_read_scanlines(&cinfo, (JSAMPARRAY)&buf.data, 1);
      convert_rgba_to_rgba(data_, buf.data, dst_format, src_format, width);
      (uint8_t*&)data_+=pitch_;
    }
  }

  // finish decompression
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  m_has_layer=false;
}
//----

void texture_loader_jpg::skip_layer()
{
  m_has_layer=false;
}
//----------------------------------------------------------------------------


//============================================================================
// get_texture_loader_jpg
//============================================================================
namespace pfc
{
  bool get_texture_loader_jpg(texture_loader::loader_variant_t &v_, texture_loader &l_)
  {
    // check for JPG file format
    bin_input_stream_base &stream=l_.stream();
    uint16_t id;
    stream>>id;
    stream.rewind(2);
    if(id!=0xd8ff)
      return false;

    // setup JPG loader
    v_=texture_loader_jpg(l_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_jpg
//============================================================================
e_file_format_support texture_support_jpg()
{
  return filefmtsupport_read;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_jpg
//============================================================================
namespace
{
  struct jpeg_writer: jpeg_destination_mgr
  {
    enum {buffer_size=4096};
    bin_output_stream_base *stream;
    uint8_t buffer[buffer_size];
    //------------------------------------------------------------------------

    static void init_destination_func(j_compress_ptr);
    static boolean empty_output_buffer_func(j_compress_ptr);
    static void term_destination_func(j_compress_ptr);
  };
  //--------------------------------------------------------------------------

  void jpeg_writer::init_destination_func(j_compress_ptr cinfo_)
  {
    jpeg_writer *dst=(jpeg_writer*)cinfo_->dest;
    dst->next_output_byte=dst->buffer;
    dst->free_in_buffer=buffer_size;
  }
  //----

  boolean jpeg_writer::empty_output_buffer_func(j_compress_ptr cinfo_)
  {
    jpeg_writer *dst=(jpeg_writer*)cinfo_->dest;
    dst->stream->write_bytes(dst->buffer, buffer_size);
    dst->next_output_byte=dst->buffer;
    dst->free_in_buffer=buffer_size;
    return true;
  }
  //----

  void jpeg_writer::term_destination_func(j_compress_ptr cinfo_)
  {
    jpeg_writer *dst=(jpeg_writer*)cinfo_->dest;
    dst->stream->write_bytes(dst->buffer, buffer_size-dst->free_in_buffer);
  }
}
//----------------------------------------------------------------------------

bool pfc::write_texture_jpg(bin_output_stream_base &s_, const texture_writer_params_jpg &params_, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_)
{
  // setup error management and initialize JPG compressor
  jpeg_compress_struct cinfo;
  jpeg_error_mgr err;
  jpeg_std_error(&err);
  err.error_exit=jpg_error_exit;
  err.output_message=jpg_output_message;
  cinfo.err=&err;
  jpeg_create_compress(&cinfo);

  // setup data target
  jpeg_writer dst;
  cinfo.dest=&dst;
  dst.init_destination=jpeg_writer::init_destination_func;
  dst.empty_output_buffer=jpeg_writer::empty_output_buffer_func;
  dst.term_destination=jpeg_writer::term_destination_func;
  dst.next_output_byte=0;
  dst.free_in_buffer=0;
  dst.stream=&s_;

  // setup compression parameters
  bool is_mono=texfmt_num_rgb_channels(src_fmt_)<=1;
  bool requires_conversion=src_fmt_!=texfmt_r8 && src_fmt_!=texfmt_a8 && src_fmt_!=texfmt_b8g8r8;
  if(!row_pitch_)
    row_pitch_=texture_pitch(width_, src_fmt_);
  cinfo.image_width=width_;
  cinfo.image_height=height_;
  cinfo.input_components=is_mono?1:3;
  cinfo.in_color_space=is_mono?JCS_GRAYSCALE:JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, unsigned(sat(params_.quality)*100+0.5f), TRUE);

  // compress the image
  jpeg_start_compress(&cinfo, TRUE);
  const uint8_t *src_row=(const uint8_t*)src_;
  raw_data row_data(requires_conversion?is_mono?width_:width_*3:0);
  e_texture_format conv_fmt=is_mono?texfmt_r8:texfmt_b8g8r8;
  while(cinfo.next_scanline<cinfo.image_height)
  {
    if(requires_conversion)
      convert_rgba_to_rgba(row_data.data, src_row, conv_fmt, src_fmt_, width_);
    jpeg_write_scanlines(&cinfo, requires_conversion?(JSAMPARRAY)&row_data.data:(JSAMPARRAY)&src_row, 1);
    src_row+=row_pitch_;
  }

  // finish compression
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
  return false;
}
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_JPEGLIB
//============================================================================
// get_texture_loader_jpg
//============================================================================
namespace pfc
{
  bool get_texture_loader_jpg(texture_loader::loader_variant_t&, texture_loader&)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_jpg
//============================================================================
e_file_format_support pfc::texture_support_jpg()
{
  return filefmtsupport_none;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_jpg
//============================================================================
bool pfc::write_texture_jpg(bin_output_stream_base&, const texture_writer_params_jpg&, const void*, e_texture_format, unsigned, unsigned, ssize_t)
{
  return false;
}
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_JPEGLIB
