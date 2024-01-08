//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/texture.h"
using namespace pfc;
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_OPENJPEG
extern "C"
{
#define OPJ_STATIC
#include "sxp_extlibs/openjpeg/src/openjpeg.h"
#include "sxp_extlibs/openjpeg/src/j2k.h"
#include "sxp_extlibs/openjpeg/src/jp2.h"
}
#pragma comment(lib, PFC_STR(PFC_CAT2(openjpeg_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
//----------------------------------------------------------------------------


//============================================================================
// texture_loader_jp2
//============================================================================
class texture_loader_jp2: public texture_loader::loader_base
{
public:
  // construction
  texture_loader_jp2(texture_loader&);
  //--------------------------------------------------------------------------

  // data loading
  virtual bool layer(texture_layer&) const;
  virtual void load_layer(void*, unsigned pitch_);
  virtual void skip_layer();
  //--------------------------------------------------------------------------

private:
  void operator=(const texture_loader_jp2&); // not implemented
  //--------------------------------------------------------------------------

  texture_loader &m_loader;
  usize_t m_stream_size;
  unsigned m_num_components;
  unsigned m_rbpp, m_gbpp, m_bbpp, m_abpp;
  bool m_has_layer;
};
//----------------------------------------------------------------------------

texture_loader_jp2::texture_loader_jp2(texture_loader &l_)
  :m_loader(l_)
{
  // init reader
  m_stream_size=0;
  m_num_components=0;
  m_rbpp=m_gbpp=m_bbpp=m_abpp=0;

  // parse image properties
  bin_input_stream_base &stream=m_loader.stream();
  auto_stream_seek<bin_input_stream_base> aseek(stream);
  endian_input_stream endian_stream(stream);
  uint32_t width=0, height=0;
  uint16_t num_components=0;
  e_texture_format fmt=texfmt_none;
  do
  {
    // read box info
    uint32_t boxlen, boxid;
    endian_stream>>boxlen>>boxid;
    PFC_CHECK(boxlen!=1);
    auto_stream_seek<bin_input_stream_base> aseek(stream, boxlen-8);

    // switch to box parsing
    switch(boxid)
    {
      // 'jp2h': jp2 header box
      case 0x6a703268: aseek.reset(); break;
      // 'ihdr': image header box
      case 0x69686472:
      {
        int8_t bpc;
        endian_stream>>height>>width>>num_components>>bpc;
        m_num_components=num_components;
        PFC_CHECK(num_components>=1 && num_components<=4);
        if(bpc>=0)
        {
          ++bpc;
          if(num_components==3 && bpc==8)
          {
            fmt=texfmt_r8g8b8;
            m_rbpp=m_gbpp=m_bbpp=bpc;
          }
          else if(num_components==4 && bpc==8)
          {
            fmt=texfmt_a8r8g8b8;
            m_rbpp=m_gbpp=m_bbpp=m_abpp=bpc;
          }
          else if(num_components==4 && bpc==4)
          {
            fmt=texfmt_a4r4g4b4;
            m_rbpp=m_gbpp=m_bbpp=m_abpp=bpc;
          }
          else if(num_components==1 && bpc==8)
          {
            fmt=texfmt_a8;
            m_abpp=bpc;
          }
          else
            PFC_ERROR("Unsupported pixel format\r\n");
        }
      } break;
      // 'bpcc': bits per component box
      case 0x62706363:
      {
        PFC_CHECK(num_components);
        uint8_t bpc[4]={0};
        endian_stream.read(bpc, num_components);
        ++bpc[0]; ++bpc[1]; ++bpc[2]; ++bpc[3];
        if(num_components==3 && bpc[0]==5 && bpc[1]==6 && bpc[2]==5)
        {
          fmt=texfmt_r5g6b5;
          m_rbpp=5; m_gbpp=6; m_bbpp=5;
        }
        else if(num_components==4 && bpc[0]==5 && bpc[1]==5 && bpc[2]==5 && bpc[3]==1)
        {
          fmt=texfmt_a1r5g5b5;
          m_rbpp=5; m_gbpp=6; m_bbpp=5; m_abpp=1;
        }
        else if(num_components==4 && bpc[0]==10 && bpc[1]==10 && bpc[2]==10 && bpc[3]==2)
        {
          fmt=texfmt_a2b10g10r10;
          m_rbpp=10; m_gbpp=10; m_bbpp=10; m_abpp=2;
        }
        else
          PFC_ERROR("Unsupported pixel format\r\n");
      } break;
      // 'jp2c': contiguous code stream box
      case 0x6a703263:
      {
        /*todo: for OpenJPEG 2.0 (currently at alpha) we don't need to determine the stream size because it will support proper data streaming*/
        PFC_CHECK_MSG(boxlen, ("Unable to determine jp2 stream size\r\n"));
        m_stream_size=stream.pos()-8+boxlen;
      } break;
    }
  } while(!m_stream_size);

  // set texture type
  m_loader.set_source_type(textype_2d);
  m_loader.set_source_format(fmt);
  m_loader.set_source_size(width, height);
  m_has_layer=true;
}
//----------------------------------------------------------------------------

bool texture_loader_jp2::layer(texture_layer &l_) const
{
  // check for available layer
  l_=texture_layer();
  return m_has_layer;
}
//----

void texture_loader_jp2::load_layer(void *p_, unsigned pitch_)
{
  // check for available layer
  if(!m_has_layer)
    return;

  // load jp2 data
  owner_data jp2_data=PFC_MEM_ALLOC(m_stream_size);
  m_loader.stream().read_bytes(jp2_data.data, m_stream_size);

  // create and setup decoder
  opj_common_struct_t common={0, 0, true, CODEC_JP2, 0, 0, 0};
  opj_jp2_t *dec=jp2_create_decompress(&common);
  opj_dparameters_t params;
  params.cp_reduce=0;
  params.cp_layer=0;
  params.cp_limit_decoding=NO_LIMITATION;
  jp2_setup_decoder(dec, &params);

  // decode the image
  opj_cio_t cio;
  cio.openmode=OPJ_STREAM_READ;
  cio.buffer=(uint8_t*)jp2_data.data;
  cio.length=(unsigned)m_stream_size;
  cio.start=(uint8_t*)jp2_data.data;
  cio.end=cio.start+m_stream_size;
  cio.bp=cio.start;
  opj_codestream_info_t info;
  opj_image_t *image=jp2_decode(dec, &cio, &info);

  // interleave image to the target format
  const int *rdata=m_rbpp?image->comps[0].data:0;
  const int *gdata=m_gbpp?image->comps[1].data:0;
  const int *bdata=m_bbpp?image->comps[2].data:0;
  const int *adata=m_abpp?m_rbpp?image->comps[3].data:image->comps[0].data:0;
  unsigned width=m_loader.width();
  unsigned height=m_loader.height();
  array<uint32_t> scanline(width);
  for(unsigned y=0; y<height; ++y)
  {
    interleave_rgba_to_rgba(p_, rdata, gdata, bdata, adata, m_loader.target_format(), m_loader.format(), width, 4);
    rdata+=width;
    gdata+=width;
    bdata+=width;
    adata+=width;
    (char*&)p_+=pitch_;
  }

  // finish decoding
  opj_image_destroy(image);
  opj_destroy_cstr_info(&info);
  jp2_destroy_decompress(dec);
  m_has_layer=false;
}
//----

void texture_loader_jp2::skip_layer()
{
  m_has_layer=false;
}
//----------------------------------------------------------------------------


//============================================================================
// get_texture_loader_jp2
//============================================================================
namespace pfc
{
  bool get_texture_loader_jp2(texture_loader::loader_variant_t &v_, texture_loader &l_)
  {
    // check for JP2 file format
    bin_input_stream_base &stream=l_.stream();
    uint32_t id1, id2, id3;
    stream>>id1>>id2>>id3;
    stream.rewind(12);
    if(id1!=0x0c000000 || id2!=0x2020506a || id3!=0x0a870a0d)
      return false;

    // setup JP2 loader
    v_=texture_loader_jp2(l_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_jp2
//============================================================================
e_file_format_support pfc::texture_support_jp2()
{
  return filefmtsupport_read;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_jp2
//============================================================================
bool pfc::write_texture_jp2(bin_output_stream_base &s_, const texture_writer_params_jp2 &params_, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_)
{
  return false;
}
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_OPENJPEG
//==========================================================================
// get_texture_loader_jp2
//==========================================================================
namespace pfc
{
  bool get_texture_loader_jp2(texture_loader::loader_variant_t&, texture_loader&)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_jp2
//============================================================================
e_file_format_support pfc::texture_support_jp2()
{
  return filefmtsupport_none;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_jp2
//============================================================================
bool pfc::write_texture_jp2(bin_output_stream_base&, const texture_writer_params_jp2&, const void*, e_texture_format, unsigned, unsigned, ssize_t)
{
  return false;
}
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_OPENJPEG
