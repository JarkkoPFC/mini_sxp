//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/texture.h"
#include "sxp_extlibs/libwebp/src/webp/decode.h"
using namespace pfc;
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_LIBWEBP
#pragma comment(lib, PFC_STR(PFC_CAT2(libwebp_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
//----------------------------------------------------------------------------


//============================================================================
// texture_loader_webp
//============================================================================
class texture_loader_webp: public texture_loader::loader_base
{
public:
  // construction
  texture_loader_webp(texture_loader&);
  //--------------------------------------------------------------------------

  // data loading
  virtual bool layer(texture_layer&) const;
  virtual void load_layer(void*, unsigned pitch_);
  virtual void skip_layer();
  //--------------------------------------------------------------------------

private:
  void operator=(const texture_loader_webp&); // not implemented
  //--------------------------------------------------------------------------

  texture_loader &m_loader;
  bool m_has_layer;
  uint32_t m_filesize;
};
//----------------------------------------------------------------------------

texture_loader_webp::texture_loader_webp(texture_loader &l_)
  :m_loader(l_)
  ,m_has_layer(false)
  ,m_filesize(0)
{
  // parse image properties
  bin_input_stream_base &stream=l_.stream();
  auto_stream_seek<bin_input_stream_base> ass(stream);
  {
    // process stream until proper VP8 chunk found
    usize_t start_pos=stream.pos();
    uint32_t id_riff, fsize, id_webp;
    stream>>id_riff>>fsize>>id_webp;
    enum {max_fsize_error=20}; // max witnessed error in file size (lossless WebP Photoshop plugin)
    usize_t end_pos=start_pos+fsize+8-max_fsize_error;
    PFC_CHECK_MSG(id_riff==0x46464952 || id_webp==0x50424557, ("Invalid WebP file\r\n"));
    while(stream.pos()<end_pos)
    {
      uint32_t chunk_id, chunk_size;
      stream>>chunk_id>>chunk_size;
      if(chunk_size&1)
        ++chunk_size;
      if(chunk_id==0x20385056)
      {
        // parse image properties from 'VP8 ' chunk
        m_filesize=uint32_t(stream.pos()-start_pos+chunk_size);
        stream.skip(6);
        uint16_t width, height;
        stream>>width>>height;
        m_loader.set_source_type(textype_2d);
        m_loader.set_source_size(width&0x3fff, height&0x3fff);
        m_loader.set_source_format(texfmt_b8g8r8);
        m_has_layer=true;
        break;
      }
      else if(chunk_id==0x4c385056)
      {
        // parse image properties from 'VP8L' chunk
        m_filesize=uint32_t(stream.pos()-start_pos+chunk_size);
        stream.skip(1);
        uint32_t size_alpha;
        stream>>size_alpha;
        m_loader.set_source_type(textype_2d);
        m_loader.set_source_size((size_alpha&0x3fff)+1, ((size_alpha>>14)&0x3fff)+1);
        if(size_alpha&0x10000000)
          m_loader.set_source_format(texfmt_a8b8g8r8);
        else
          m_loader.set_source_format(texfmt_b8g8r8);
        m_has_layer=true;
        break;
      }
      else
        stream.skip(chunk_size);
    }
  }
}
//----------------------------------------------------------------------------

bool texture_loader_webp::layer(texture_layer &l_) const
{
  l_=texture_layer();
  return m_has_layer;
}
//----

void texture_loader_webp::load_layer(void *data_, unsigned pitch_)
{
  // check for available layer
  if(!m_has_layer)
    return;

  // setup decoder output format
  bin_input_stream_base &stream=m_loader.stream();
  e_texture_format dst_format=m_loader.target_format();
  WEBP_CSP_MODE webp_format=MODE_RGB;
  bool is_conv=false;
  switch(dst_format)
  {
    case texfmt_b8g8r8:   webp_format=MODE_RGB; break;
    case texfmt_a8b8g8r8: webp_format=MODE_RGBA; break;
    case texfmt_r8g8b8:   webp_format=MODE_BGR; break;
    case texfmt_a8r8g8b8: webp_format=MODE_BGRA; break;
    case texfmt_b8g8r8a8: webp_format=MODE_ARGB; break;
    default: is_conv=true; break;
  }

  // load image to the given buffer
  if(is_conv)
  {
    // decode the image and convert to the target format
    e_texture_format src_format=m_loader.format();
    bool has_alpha=texfmt_num_alpha_channels(dst_format) && texfmt_num_alpha_channels(src_format);
    unsigned tmp_pitch=m_loader.width()*(has_alpha?4:3);
    unsigned tmp_size=tmp_pitch*m_loader.height();
    raw_data tmp_img(tmp_size);
    WebPIDecoder *dec=WebPINewRGB(has_alpha?MODE_RGBA:MODE_RGB, (uint8_t*)tmp_img.data, tmp_size, tmp_pitch);
    raw_data data(m_filesize);
    stream.read_bytes(data.data, m_filesize);
    WebPIUpdate(dec, (const uint8_t*)data.data, m_filesize);
    convert_rgba_to_rgba(data_, tmp_img.data, dst_format, has_alpha?texfmt_a8b8g8r8:texfmt_b8g8r8, m_loader.width()*m_loader.height());
    WebPIDelete(dec);
  }
  else
  {
    // decode the image to the given buffer
    WebPIDecoder *dec=WebPINewRGB(webp_format, (uint8_t*)data_, m_loader.height()*pitch_, pitch_);
    raw_data data(m_filesize);
    stream.read_bytes(data.data, m_filesize);
    WebPIUpdate(dec, (const uint8_t*)data.data, m_filesize);
    WebPIDelete(dec);
  }
}
//----

void texture_loader_webp::skip_layer()
{
  m_has_layer=false;
}
//----------------------------------------------------------------------------


//============================================================================
// get_texture_loader_webp
//============================================================================
namespace pfc
{
  bool get_texture_loader_webp(texture_loader::loader_variant_t &v_, texture_loader &l_)
  {
    // check for WebP file format
    bin_input_stream_base &stream=l_.stream();
    uint32_t id_riff, len, id_webp;
    stream>>id_riff>>len>>id_webp;
    stream.rewind(12);
    if(id_riff!=0x46464952 || id_webp!=0x50424557)
      return false;

    // setup WebP loader
    v_=texture_loader_webp(l_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_webp
//============================================================================
e_file_format_support pfc::texture_support_webp()
{
  return filefmtsupport_read;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_webp
//============================================================================
bool pfc::write_texture_webp(bin_output_stream_base &s_, const texture_writer_params_webp &params_, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_)
{
  return false;
}
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_LIBWEBP
//============================================================================
// get_texture_loader_webp
//============================================================================
namespace pfc
{
  bool get_texture_loader_webp(texture_loader::loader_variant_t&, texture_loader&)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_webp
//============================================================================
e_file_format_support pfc::texture_support_webp()
{
  return filefmtsupport_none;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_webp
//============================================================================
bool pfc::write_texture_webp(bin_output_stream_base&, const texture_writer_params_webp&, const void*, e_texture_format, unsigned, unsigned, ssize_t)
{
  return false;
}
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_LIBWEBP
