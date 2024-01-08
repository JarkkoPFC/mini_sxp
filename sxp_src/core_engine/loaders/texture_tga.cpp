//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/texture.h"
#include "sxp_src/core/math/bit_math.h"
using namespace pfc;
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_TGA
//============================================================================
// texture_loader_tga
//============================================================================
class texture_loader_tga: public texture_loader::loader_base
{
public:
  // construction
  texture_loader_tga(texture_loader&);
  //--------------------------------------------------------------------------

  // data loading
  virtual bool layer(texture_layer&) const;
  virtual void load_layer(void*, unsigned pitch_);
  virtual void skip_layer();
  //--------------------------------------------------------------------------

private:
  void operator=(const texture_loader_tga&); // not implemented
  //--------------------------------------------------------------------------

  texture_loader &m_loader;
  bool m_bottom_up;
  bool m_has_layer;
};
//----------------------------------------------------------------------------

texture_loader_tga::texture_loader_tga(texture_loader &l_)
  :m_loader(l_)
{
  // read header
  bin_input_stream_base &stream=m_loader.stream();
  uint8_t id, cmap_type, image_type, cmap_bpe;
  uint16_t cmap_start, cmap_len;
  stream>>id>>cmap_type>>image_type;
  stream>>cmap_start>>cmap_len>>cmap_bpe;

  // read image info
  uint16_t orig_x, orig_y, width, height;
  uint8_t bpp, desc;
  stream>>orig_x>>orig_y>>width>>height>>bpp>>desc;
  stream.skip(id);
  PFC_ASSERT_MSG(cmap_type==0, ("Color mapped TGA's not supported\r\n"));
  PFC_ASSERT_MSG(image_type==2, ("Only uncompressed true-color TGA's are supported\r\n"));
  PFC_ASSERT_MSG(bpp==16 || bpp==32 || bpp==24, ("Only 16, 24 & 32 bpp TGA's are supported (%ibpp)\r\n", bpp));
  PFC_ASSERT_MSG((desc&0x10)==0, ("Right-to-left ordered TGA's not supported\r\n"));
  m_bottom_up=(desc&0x20)==0;

  // set texture type
  m_loader.set_source_type(textype_2d);
  m_loader.set_source_format(bpp==16?texfmt_r5g6b5:bpp==24?texfmt_r8g8b8:texfmt_a8r8g8b8);
  m_loader.set_source_size(width, height);
  m_has_layer=true;
}
//----------------------------------------------------------------------------

bool texture_loader_tga::layer(texture_layer &l_) const
{
  l_=texture_layer();
  return m_has_layer;
}
//----

void texture_loader_tga::load_layer(void *p_, unsigned pitch_)
{
  // check for available layer
  if(!m_has_layer)
    return;

  // read image
  bin_input_stream_base &stream=m_loader.stream();
  unsigned width=m_loader.width();
  unsigned height=m_loader.height();
  uint8_t *p=(uint8_t*)p_+(m_bottom_up?pitch_*(height-1):0);
  int pitch=m_bottom_up?-int(pitch_):pitch_;
  e_texture_format src_format=m_loader.format();
  e_texture_format dst_format=m_loader.target_format();
  unsigned bytespp=texfmt_bpp(src_format)/8;
  if(src_format==dst_format)
  {
    for(unsigned y=0; y<height; ++y)
    {
      // read scan line
      stream.read_bytes(p, width*bytespp);
      p+=pitch;
    }
  }
  else
  {
    // perform format conversion
    unsigned scan_bytes=width*bytespp;
    owner_data row=PFC_MEM_ALLOC(scan_bytes);
    for(unsigned y=0; y<height; ++y)
    {
      // read scan line and convert to target
      stream.read_bytes(row.data, scan_bytes);
      convert_rgba_to_rgba(p, row.data, dst_format, src_format, width);
      p+=pitch;
    }
  }

  m_has_layer=false;
}
//----

void texture_loader_tga::skip_layer()
{
  if(m_has_layer)
  {
    m_loader.stream().skip(m_loader.width()*m_loader.height()*texfmt_bpp(m_loader.format()));
    m_has_layer=false;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// get_texture_loader_tga
//============================================================================
namespace pfc
{
  bool get_texture_loader_tga(texture_loader::loader_variant_t &v_, texture_loader &l_)
  {
    // check for TGA file format
    bin_input_stream_base &stream=l_.stream();
    uint8_t id, cmap_type, image_type, cmap_bpe, bpp, desc;
    uint16_t cmap_start, cmap_len, orig_x, orig_y, width, height;
    stream>>id>>cmap_type>>image_type;
    stream>>cmap_start>>cmap_len>>cmap_bpe;
    stream>>orig_x>>orig_y>>width>>height>>bpp>>desc;
    stream.rewind(18);
    bool is_tga=   (   (cmap_type==0 && cmap_start==0 && cmap_len==0 && cmap_bpe==0 && (image_type==0 || image_type==2 || image_type==3 || image_type==10 || image_type==11))
                    || (cmap_type==1 && (cmap_bpe==15 || cmap_bpe==16 || cmap_bpe==24 || cmap_bpe==32) && (image_type==1 || image_type==9)))
                && (bpp==8 || bpp==16 || bpp==24 || bpp==32)
                && ((desc&0xc0)==0 && is_pow2(uint8_t(desc&0xf)));
    if(!is_tga)
      return false;

    // setup TGA loader
    v_=texture_loader_tga(l_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_tga
//============================================================================
e_file_format_support pfc::texture_support_tga()
{
  return filefmtsupport_read;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_tga
//============================================================================
bool pfc::write_texture_tga(bin_output_stream_base &s_, const texture_writer_params_tga &params_, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_)
{
  return false;
}
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_TGA
//============================================================================
// get_texture_loader_tga
//============================================================================
namespace pfc
{
  bool get_texture_loader_tga(texture_loader::loader_variant_t&, texture_loader&)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_tga
//============================================================================
e_file_format_support pfc::texture_support_tga()
{
  return filefmtsupport_none;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_tga
//============================================================================
bool pfc::write_texture_tga(bin_output_stream_base&, const texture_writer_params_tga&, const void*, e_texture_format, unsigned, unsigned, ssize_t)
{
  return false;
}
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_TGA
