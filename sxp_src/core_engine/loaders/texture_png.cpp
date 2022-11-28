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


#ifdef PFC_ENGINEOP_LIBPNG
// check for libraries required by libpng
#ifndef PFC_ENGINEOP_ZLIB
#error libpng requires zlib library
#endif
//----
#include "sxp_extlibs/libpng/src/png.h"
#pragma comment(lib, PFC_STR(PFC_CAT2(libpng_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
#pragma comment(lib, PFC_STR(PFC_CAT2(zlib_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
//----------------------------------------------------------------------------


//============================================================================
// texture_loader_png
//============================================================================
class texture_loader_png: public texture_loader::loader_base
{
public:
  // construction
  texture_loader_png(texture_loader&);
  //--------------------------------------------------------------------------

  // data loading
  virtual bool layer(texture_layer&) const;
  virtual void load_layer(void*, unsigned pitch_);
  virtual void skip_layer();
  //--------------------------------------------------------------------------

private:
  void operator=(const texture_loader_png&); // not implemented
  static bool check_format(bin_input_stream_base&);
  static void read_data_func(png_structp png_, png_bytep data_, png_size_t length_);
  //--------------------------------------------------------------------------

  texture_loader &m_loader;
  bool m_has_layer;
};
//----------------------------------------------------------------------------

texture_loader_png::texture_loader_png(texture_loader &l_)
  :m_loader(l_)
{
  // read image properties
  bin_input_stream_base &stream=m_loader.stream();
  stream.skip(12);
  uint32_t chunk_id, width, height;
  uint8_t bpc, color_type;
  stream>>chunk_id>>width>>height>>bpc>>color_type;
  PFC_CHECK_MSG(chunk_id==0x52444849, ("Invalid PNG file\r\n"));
  stream.rewind(26);
  width=swap_bytes(width);
  height=swap_bytes(height);

  // map texture format
  e_texture_format tf=texfmt_none;
  switch(color_type)
  {
    // gray scale
    case 0:
    {
      PFC_CHECK_MSG(bpc==8 || bpc==16, ("Unsupported gray scale image bit depth (%ibpp)\r\n", bpc));
      tf=bpc==8?texfmt_a8:texfmt_r16;
    } break;
    // RGB
    case 2:
    {
      PFC_CHECK_MSG(bpc==8 || bpc==16, ("Unsupported RGB image bit depth (%ibpp)\r\n", bpc*3));
      tf=bpc==8?texfmt_b8g8r8:texfmt_b16g16r16;
    } break;
    // RGBA
    case 6:
    {
      PFC_CHECK_MSG(bpc==8 || bpc==16, ("Unsupported ARGB image bit depth (%ibpp)\r\n", bpc*4));
      tf=bpc==8?texfmt_b8g8r8a8:texfmt_b16g16r16a16;
    } break;
    // unsupported
    default: PFC_ERROR("Unsupported PNG pixel format\r\n");
  }

  // set texture type
  m_loader.set_source_type(textype_2d);
  m_loader.set_source_format(tf);
  m_loader.set_source_size(width, height);
  m_has_layer=true;
}
//----------------------------------------------------------------------------

bool texture_loader_png::layer(texture_layer &l_) const
{
  l_=texture_layer();
  return m_has_layer;
}
//----

void texture_loader_png::load_layer(void *data_, unsigned pitch_)
{
  // check for available layer
  if(!m_has_layer)
    return;

  // read PNG header
  png_structp png=png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  png_infop info=png_create_info_struct(png);
  png_set_read_fn(png, &m_loader.stream(), read_data_func);
  png_read_info(png, info);
  png_uint_32 img_width, img_height;
  int bit_depth, color_type, interlace_type, intent;
  png_get_IHDR(png, info, &img_width, &img_height, &bit_depth, &color_type, &interlace_type, 0, 0);

  // initialize PNG reading
  png_set_packing(png);
  if(bit_depth>8 && !PFC_BIG_ENDIAN)
    png_set_swap(png);
  if(color_type==PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);
  if(color_type==PNG_COLOR_TYPE_GRAY && bit_depth<8)
    png_set_expand_gray_1_2_4_to_8(png);
  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);
  if(m_loader.gamma_enabled())
  {
    if(png_get_sRGB(png, info, &intent))
      png_set_gamma(png, 1.0, 0.45455);
    else
    {
      double image_gamma;
      if(png_get_gAMA(png, info, &image_gamma))
        png_set_gamma(png, 1.0, image_gamma);
    }
  }
  png_set_swap_alpha(png);
  PFC_VERIFY_MSG(png_set_interlace_handling(png)==1,
                 ("Multi-pass PNG files not supported\r\n"));

  // read PNG image
  e_texture_format src_format=m_loader.format();
  e_texture_format dst_format=m_loader.target_format();
  if(src_format==dst_format)
  {
    // read image directly to the target buffer
    for(unsigned y=0; y<img_height; ++y)
    {
      png_read_row(png, (png_bytep)data_, 0);
      (uint8_t*&)data_+=pitch_;
    }
  }
  else
  {
    // read image to temp buffer and convert to the target buffer
    owner_data row=PFC_MEM_ALLOC(png_get_rowbytes(png, info));
    unsigned width=m_loader.width();
    for(unsigned y=0; y<img_height; ++y)
    {
      png_read_row(png, (png_bytep)row.data, 0);
      convert_rgba_to_rgba(data_, row.data, dst_format, src_format, width);
      (uint8_t*&)data_+=pitch_;
    }
  }

  // finish reading
  png_read_end(png, info);
  png_destroy_read_struct(&png, &info, 0);
  m_has_layer=false;
}
//----

void texture_loader_png::skip_layer()
{
  m_has_layer=false;
}
//----------------------------------------------------------------------------

bool texture_loader_png::check_format(bin_input_stream_base &s_)
{
  // check for PNG format
  uint32_t id1, id2;
  s_>>id1>>id2;
  s_.rewind(8);
  return id1==0x474e5089 && id2==0x0a1a0a0d;
}
//----

void texture_loader_png::read_data_func(png_structp png_, png_bytep data_, png_size_t length_)
{
  // read PNG data
  bin_input_stream_base &stream=*(bin_input_stream_base*)png_->io_ptr;
  stream.read_bytes(data_, unsigned(length_));
}
//----------------------------------------------------------------------------


//============================================================================
// get_texture_loader_png
//============================================================================
namespace pfc
{
  bool get_texture_loader_png(texture_loader::loader_variant_t &v_, texture_loader &l_)
  {
    // check for PNG file format
    bin_input_stream_base &stream=l_.stream();
    uint32_t id1, id2;
    stream>>id1>>id2;
    stream.rewind(8);
    if(id1!=0x474e5089 || id2!=0x0a1a0a0d)
      return false;

    // setup PNG loader
    v_=texture_loader_png(l_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_png
//============================================================================
e_file_format_support pfc::texture_support_png()
{
  return filefmtsupport_read;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_png
//============================================================================
static void write_data_func(png_structp png_, png_bytep data_, png_size_t length_)
{
  // write PNG data
  bin_output_stream_base &stream=*(bin_output_stream_base*)png_->io_ptr;
  stream.write_bytes(data_, length_);
}
//----

bool pfc::write_texture_png(bin_output_stream_base &s_, const texture_writer_params_png &params_, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_)
{
  // setup PNG color type
  unsigned num_channels=texfmt_num_channels(src_fmt_);
  unsigned num_rgb_channels=texfmt_num_rgb_channels(src_fmt_);
  unsigned dst_color_type= (num_rgb_channels>1?PNG_COLOR_MASK_COLOR:0)
                          |(params_.save_alpha?PNG_COLOR_MASK_ALPHA:0);

  // get PNG format
  e_texture_format png_fmt=texfmt_none;
  if(params_.save_alpha)
  {
    if(params_.is_16bpp)
      png_fmt=num_channels==1?texfmt_a16:num_channels==2?texfmt_a16r16:texfmt_a16b16g16r16;
    else
      png_fmt=num_channels==1?texfmt_a8:num_channels==2?texfmt_a8r8:texfmt_a8b8g8r8;
  }
  else
  {
    if(params_.is_16bpp)
      png_fmt=num_channels==1?texfmt_r16:num_channels==2?texfmt_g16r16:texfmt_b16g16r16;
    else
      png_fmt=num_channels==1?texfmt_r8:num_channels==2?texfmt_g8r8:texfmt_b8g8r8;
  }

  // write PNG header
  png_structp png=png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info=png_create_info_struct(png);
  png_set_write_fn(png, &s_, write_data_func, 0);
  png_set_IHDR(png, info, width_, height_, params_.is_16bpp?16:8, dst_color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
  png_write_info(png, info);

  // convert image if necessary and setup row pointers
  if(!row_pitch_)
    row_pitch_=texture_pitch(width_, src_fmt_);
  raw_data tmp_img_data;
  raw_data row_data(height_*sizeof(png_byte*));
  uint8_t **rows=(uint8_t**)row_data.data;
  if(png_fmt!=src_fmt_)
  {
    unsigned tmp_row_size=width_*texfmt_bpp(png_fmt)/8;
    tmp_img_data.alloc(tmp_row_size*height_);
    for(unsigned i=0; i<height_; ++i)
    {
      rows[i]=(uint8_t*)tmp_img_data.data+i*tmp_row_size;
      convert_rgba_to_rgba(rows[i], (uint8_t*)src_+i*row_pitch_, png_fmt, src_fmt_, width_);
      if(params_.is_16bpp)
        swap_bytes((uint16_t*)rows[i], tmp_row_size/2);
    }
  }
  else
    for(unsigned i=0; i<height_; ++i)
      rows[i]=(uint8_t*)src_+i*row_pitch_;

  // write the PNG
  png_write_image(png, rows);
  png_write_end(png, 0);
  return false;
}
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_LIBPNG
//============================================================================
// get_texture_loader_png
//============================================================================
namespace pfc
{
  bool get_texture_loader_png(texture_loader::loader_variant_t&, texture_loader&)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_png
//============================================================================
e_file_format_support pfc::texture_support_png()
{
  return filefmtsupport_none;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_png
//============================================================================
bool pfc::write_texture_png(bin_output_stream_base&, const texture_writer_params_png&, const void*, e_texture_format, unsigned, unsigned, ssize_t)
{
  return false;
}
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_LIBPNG
