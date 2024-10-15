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


#ifdef PFC_ENGINEOP_DDS
//============================================================================
// texture_loader_dds
//============================================================================
class texture_loader_dds: public texture_loader::loader_base
{
public:
  // construction
  texture_loader_dds(texture_loader&);
  //--------------------------------------------------------------------------

  // data loading
  virtual bool layer(texture_layer&) const;
  virtual void load_layer(void*, unsigned pitch_);
  virtual void skip_layer();
  //--------------------------------------------------------------------------

private:
  void operator=(const texture_loader_dds&); // not implemented
  void advance_layer();
  //--------------------------------------------------------------------------

  texture_loader &m_loader;
  bool m_has_layer;
  texture_layer m_cur_layer;
  bool m_faces[6];
};
//----------------------------------------------------------------------------

texture_loader_dds::texture_loader_dds(texture_loader &l_)
  :m_loader(l_)
{
  // bit flags
  enum
  {
    // basic file flags
    ddsd_caps       =0x00000001,
    ddsd_height     =0x00000002,
    ddsd_width      =0x00000004,
    ddsd_pitch      =0x00000008,
    ddsd_pixelformat=0x00001000,
    ddsd_mipmapcount=0x00020000,
    ddsd_linearsize =0x00080000,
//    ddsd_depth      =0x00800000,
    // format flags
    ddpf_alphapixels=0x00000001,
    ddpf_fourcc     =0x00000004,
    ddpf_rgb        =0x00000040,
    ddpf_luminance  =0x00020000,
    // caps1 flags
    ddscaps_complex =0x00000008,
    ddscaps_texture =0x00001000,
    ddscaps_mipmap  =0x00400000,
    // caps2 flags
    ddscaps2_cubemap     =0x00000200,
    ddscaps2_cubemap_posx=0x00000400,
    ddscaps2_cubemap_negx=0x00000800,
    ddscaps2_cubemap_posy=0x00001000,
    ddscaps2_cubemap_negy=0x00002000,
    ddscaps2_cubemap_posz=0x00004000,
    ddscaps2_cubemap_negz=0x00008000,
    ddscaps2_volume      =0x00200000,
  };

  // read header
  uint32_t file_id, header_size, flags;
  uint32_t height, width, pitch, depth, num_mips;
  bin_input_stream_base &stream=m_loader.stream();
  stream>>file_id>>header_size>>flags;
  stream>>height>>width>>pitch>>depth>>num_mips;
  stream.skip(44);
  PFC_CHECK_MSG(file_id==0x20534444 && (header_size==124 || header_size==144) && (flags&(ddsd_caps|ddsd_pixelformat|ddsd_width|ddsd_height))==(ddsd_caps|ddsd_pixelformat|ddsd_width|ddsd_height),
                ("Invalid DDS file\r\n"));

  // read pixel format
  uint32_t fmt_size, fmt_flags, fmt_fourcc, fmt_bits;
  uint32_t fmt_rmask, fmt_gmask, fmt_bmask, fmt_amask;
  stream>>fmt_size>>fmt_flags>>fmt_fourcc>>fmt_bits;
  stream>>fmt_rmask>>fmt_gmask>>fmt_bmask>>fmt_amask;

  // read caps
  uint32_t caps1, caps2;
  stream>>caps1>>caps2;
  stream.skip(12);

  // setup format
  if(fmt_flags&ddpf_rgb)
  {
    // setup RGB format
    if(fmt_bits==32 && fmt_amask==0xff000000 && fmt_rmask==0x00ff0000 && fmt_gmask==0x0000ff00 && fmt_bmask==0x000000ff)
      m_loader.set_source_format(texfmt_a8r8g8b8);
    else if(fmt_bits==32 && fmt_amask==0xff000000 && fmt_rmask==0x000000ff && fmt_gmask==0x0000ff00 && fmt_bmask==0x00ff0000)
      m_loader.set_source_format(texfmt_a8b8g8r8);
    else if(fmt_bits==16 && fmt_amask==0x0000 && fmt_rmask==0xf800 && fmt_gmask==0x07e0 && fmt_bmask==0x001f)
      m_loader.set_source_format(texfmt_r5g6b5);
    else if(fmt_bits==16 && fmt_amask==0x8000 && fmt_rmask==0x7c00 && fmt_gmask==0x03e0 && fmt_bmask==0x001f)
      m_loader.set_source_format(texfmt_a1r5g5b5);
    else if(fmt_bits==16 && fmt_amask==0xf000 && fmt_rmask==0x0f00 && fmt_gmask==0x00f0 && fmt_bmask==0x000f)
      m_loader.set_source_format(texfmt_a4r4g4b4);
    else if(fmt_bits==8 && fmt_amask==0x00 && fmt_rmask==0xff && fmt_gmask==0x00 && fmt_bmask==0x00)
      m_loader.set_source_format(texfmt_r8);
    else
      PFC_ERROR("Unsupported DDS ARGB texture format\r\n");
  }
  else if(fmt_flags&ddpf_luminance)
  {
    if(fmt_bits==8)
      m_loader.set_source_format(texfmt_r8);
    else if(fmt_bits==16)
      m_loader.set_source_format(texfmt_r16);
    else if(fmt_bits==32)
      m_loader.set_source_format(texfmt_r32);
  }
  else if(fmt_flags&ddpf_fourcc)
  {
    // setup four-cc format
    switch(fmt_fourcc)
    {
      case 0x00000024: m_loader.set_source_format(texfmt_a16b16g16r16); break;
      case 0x0000006f: m_loader.set_source_format(texfmt_r16f); break;
      case 0x00000070: m_loader.set_source_format(texfmt_g16r16f); break;
      case 0x00000071: m_loader.set_source_format(texfmt_a16b16g16r16f); break;
      case 0x00000072: m_loader.set_source_format(texfmt_r32f); break;
      case 0x00000073: m_loader.set_source_format(texfmt_g32r32f); break;
      case 0x00000074: m_loader.set_source_format(texfmt_a32b32g32r32f); break;
      case 0x31545844: m_loader.set_source_format(fmt_flags&ddpf_alphapixels?texfmt_bc1a:texfmt_bc1); break; /*todo: test detection of bc1a*/
      case 0x33545844: m_loader.set_source_format(texfmt_bc2); break;
      case 0x35545844: m_loader.set_source_format(texfmt_bc3); break;
      case 0x30315844:
      {
        // read DX10 header
        uint32_t dxgi_format, dimension, misc_flags, arr_size, misc_flags2;
        stream>>dxgi_format>>dimension>>misc_flags>>arr_size>>misc_flags2;
        switch(dxgi_format)
        {
          case 65:  m_loader.set_source_format(texfmt_a8); break; // DXGI_FORMAT_A8_UNORM
          case 60:  m_loader.set_source_format(texfmt_r8); break; // DXGI_FORMAT_R8_TYPELESS
          case 61:  m_loader.set_source_format(texfmt_r8); break; // DXGI_FORMAT_R8_UNORM
          case 62:  m_loader.set_source_format(texfmt_r8); break; // DXGI_FORMAT_R8_UINT
          case 63:  m_loader.set_source_format(texfmt_r8); break; // DXGI_FORMAT_R8_SNORM
          case 64:  m_loader.set_source_format(texfmt_r8); break; // DXGI_FORMAT_R8_SINT
          // case : m_loader.set_source_format(texfmt_a16); break;
          case 56:  m_loader.set_source_format(texfmt_r16); break; // DXGI_FORMAT_R16_UNORM
          case 54 : m_loader.set_source_format(texfmt_r16f); break; // DXGI_FORMAT_R16_FLOAT
          // case :  m_loader.set_source_format(texfmt_a8r8); break;
          // case :  m_loader.set_source_format(texfmt_g8r8); break;
          case 85:  m_loader.set_source_format(texfmt_r5g6b5); break; // DXGI_FORMAT_B5G6R5_UNORM
          case 86:  m_loader.set_source_format(texfmt_a1r5g5b5); break; // DXGI_FORMAT_B5G5R5A1_UNORM
          case 115: m_loader.set_source_format(texfmt_a4r4g4b4); break; // DXGI_FORMAT_B4G4R4A4_UNORM
          // case : m_loader.set_source_format(texfmt_r8g8b8); break;
          // case : m_loader.set_source_format(texfmt_b8g8r8); break;
          // case :  m_loader.set_source_format(texfmt_a32); break;
          case 42:  m_loader.set_source_format(texfmt_r32); break;
          case 43:  m_loader.set_source_format(texfmt_r32); break;
          case 40:  // DXGI_FORMAT_D32_FLOAT
          case 41:  m_loader.set_source_format(texfmt_r32f); break; // DXGI_FORMAT_R32_FLOAT
          // case :  m_loader.set_source_format(texfmt_a16r16); break;
          case 35:  m_loader.set_source_format(texfmt_g16r16); break; // DXGI_FORMAT_R16G16_UNORM
          case 34:  m_loader.set_source_format(texfmt_g16r16f); break; // DXGI_FORMAT_R16G16_FLOAT
          case 87:  m_loader.set_source_format(texfmt_a8r8g8b8); break; // DXGI_FORMAT_B8G8R8A8_UNORM
          case 28:  m_loader.set_source_format(texfmt_a8b8g8r8); break; // DXGI_FORMAT_R8G8B8A8_UNORM
          // case : m_loader.set_source_format(texfmt_b8g8r8a8); break;
          case 24: // DXGI_FORMAT_R10G10B10A2_UNORM
          case 25:  m_loader.set_source_format(texfmt_a2b10g10r10); break; // DXGI_FORMAT_R10G10B10A2_UINT
          // case : m_loader.set_source_format(texfmt_b16g16r16); break;
          // case : m_loader.set_source_format(texfmt_a32r32); break;
          case 17: m_loader.set_source_format(texfmt_g32r32); break; // DXGI_FORMAT_R32G32_UINT
          case 18: m_loader.set_source_format(texfmt_g32r32); break; // DXGI_FORMAT_R32G32_INT
          case 16: m_loader.set_source_format(texfmt_g32r32f); break; // DXGI_FORMAT_R32G32_FLOAT
          // case : m_loader.set_source_format(texfmt_b16g16r16a16); break;
          // case : m_loader.set_source_format(texfmt_a16b16g16r16); break;
          case 10:  m_loader.set_source_format(texfmt_a16b16g16r16f); break; // DXGI_FORMAT_R16G16B16A16_FLOAT
          // case : m_loader.set_source_format(texfmt_b32g32r32f); break;
          // case : m_loader.set_source_format(texfmt_a32b32g32r32); break;
          case 2:   m_loader.set_source_format(texfmt_a32b32g32r32f); break; // DXGI_FORMAT_R32G32B32A32_FLOAT
          case 71: case 72: m_loader.set_source_format(texfmt_bc1); break; // DXGI_FORMAT_BC1_UNORM/DXGI_FORMAT_BC1_UNORM_SRGB
          //case : m_loader.set_source_format(texfmt_bc1a); break;
          case 74: case 75: m_loader.set_source_format(texfmt_bc2); break; // DXGI_FORMAT_BC2_UNORM/DXGI_FORMAT_BC2_UNORM_SRGB
          case 77: case 78: m_loader.set_source_format(texfmt_bc3); break; // DXGI_FORMAT_BC3_UNORM/DXGI_FORMAT_BC3_UNORM_SRGB
          case 95: case 96: m_loader.set_source_format(texfmt_bc6h); break; // DXGI_FORMAT_BC6H_UF16/DXGI_FORMAT_BC6H_SF16
          case 98: case 99: m_loader.set_source_format(texfmt_bc7); break; // DXGI_FORMAT_BC7_UNORM/DXGI_FORMAT_BC7_UNORM_SRGB
          default: PFC_ERRORF("Unsupported DX10 FourCC texture format [0x%08x]\r\n", dxgi_format);
        }
      } break;
      default: PFC_ERRORF("Unsupported FourCC texture format [0x%08x]\r\n", fmt_fourcc);
    }
  }
  else
    PFC_ERROR("Unsupported DDS texture format\r\n");

  // map rest of the values to loader
  m_loader.set_source_type(caps2&ddscaps2_cubemap?textype_cube:caps2&ddscaps2_volume?textype_3d:textype_2d);
  m_loader.set_source_size(width, height, caps2&ddscaps2_volume?depth:0, caps1&ddscaps_mipmap && num_mips?num_mips:1);
/*  PFC_CHECK_MSG(is_pow2(width) && is_pow2(height) && is_pow2(depth),
                ("Only power-of-2 DDS textures are supported [%i x %i x %i]\r\n", width, height, depth));*/

  // init reader state
  m_has_layer=true;
  m_cur_layer.mip_level=0;
  m_cur_layer.array_slice=0;
  m_cur_layer.volume_slice=0;
  m_cur_layer.face=cubeface_posx;
  m_faces[cubeface_negz]=(caps2&ddscaps2_cubemap_negz)!=0; if(m_faces[cubeface_negz]) m_cur_layer.face=cubeface_negz;
  m_faces[cubeface_posz]=(caps2&ddscaps2_cubemap_posz)!=0; if(m_faces[cubeface_posz]) m_cur_layer.face=cubeface_posz;
  m_faces[cubeface_negy]=(caps2&ddscaps2_cubemap_negy)!=0; if(m_faces[cubeface_negy]) m_cur_layer.face=cubeface_negy;
  m_faces[cubeface_posy]=(caps2&ddscaps2_cubemap_posy)!=0; if(m_faces[cubeface_posy]) m_cur_layer.face=cubeface_posy;
  m_faces[cubeface_negx]=(caps2&ddscaps2_cubemap_negx)!=0; if(m_faces[cubeface_negx]) m_cur_layer.face=cubeface_negx;
  m_faces[cubeface_posx]=(caps2&ddscaps2_cubemap_posx)!=0; if(m_faces[cubeface_posx]) m_cur_layer.face=cubeface_posx;
}
//----------------------------------------------------------------------------

bool texture_loader_dds::layer(texture_layer &l_) const
{
  l_=m_cur_layer;
  return m_has_layer;
}
//----

void texture_loader_dds::load_layer(void *p_, unsigned pitch_)
{
  // read layer data
  PFC_CHECK_MSG(m_loader.format()==m_loader.target_format(),
                ("Unable to perform conversion from %s to %s\r\n", texfmt_str(m_loader.format()), texfmt_str(m_loader.target_format())));
  m_loader.stream().read_bytes(p_, texture_mip_size_2d(m_loader.width(), m_loader.height(), m_loader.format(), m_cur_layer.mip_level));
  advance_layer();
}
//----

void texture_loader_dds::skip_layer()
{
  // skip layer data and move to the next layer
  m_loader.stream().skip(texture_mip_size_2d(m_loader.width(), m_loader.height(), m_loader.format(), m_cur_layer.mip_level));
  advance_layer();
}
//----------------------------------------------------------------------------

void texture_loader_dds::advance_layer()
{
  // check for available layer
  if(!m_has_layer)
    return;

  texture_loader &l=m_loader;
  switch(int(l.type()))
  {
    // 2d texture layer
    case textype_2d:
    {
      if(++m_cur_layer.mip_level==l.num_mips())
      {
        m_cur_layer.mip_level=0;
        if(++m_cur_layer.array_slice==l.array_size())
        {
          m_cur_layer.array_slice=0;
          m_has_layer=false;
        }
      }
    } break;

    // 3d texture layer
    case textype_3d:
    {
      if(++m_cur_layer.volume_slice==max(1u, l.depth()>>m_cur_layer.mip_level))
      {
        m_cur_layer.volume_slice=0;
        if(++m_cur_layer.mip_level==l.num_mips())
        {
          m_cur_layer.mip_level=0;
          m_has_layer=false;
        }
      }
    } break;

    // cube texture layer
    case textype_cube:
    {
      if(++m_cur_layer.mip_level==l.num_mips())
      {
        m_cur_layer.mip_level=0;
        switch(m_cur_layer.face)
        {
          case cubeface_posx: m_cur_layer.face=cubeface_negx; if(m_faces[m_cur_layer.face]) break;
          case cubeface_negx: m_cur_layer.face=cubeface_posy; if(m_faces[m_cur_layer.face]) break;
          case cubeface_posy: m_cur_layer.face=cubeface_negy; if(m_faces[m_cur_layer.face]) break;
          case cubeface_negy: m_cur_layer.face=cubeface_posz; if(m_faces[m_cur_layer.face]) break;
          case cubeface_posz: m_cur_layer.face=cubeface_negz; if(m_faces[m_cur_layer.face]) break;
          case cubeface_negz:
          {
            m_cur_layer.face=cubeface_posx;
            if(++m_cur_layer.array_slice==l.array_size())
            {
              m_cur_layer.array_slice=0;
              m_has_layer=false;
            }
          }
        }
      }
    } break;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// get_texture_loader_dds
//============================================================================
namespace pfc
{
  bool get_texture_loader_dds(texture_loader::loader_variant_t &v_, texture_loader &l_)
  {
    // check for DDS file format
    uint32_t file_id, header_size, flags;
    bin_input_stream_base &stream=l_.stream();
    stream>>file_id>>header_size>>flags;
    stream.rewind(12);
    if(file_id!=0x20534444 || (header_size!=124 && header_size!=144) || (flags&0x1007)!=0x1007)
      return false;

    // setup DDS loader
    v_=texture_loader_dds(l_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_dds
//============================================================================
e_file_format_support pfc::texture_support_dds()
{
  return filefmtsupport_read;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_dds
//============================================================================
bool pfc::write_texture_dds(bin_output_stream_base &s_, const texture_writer_params_dds &params_, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, unsigned depth_, ssize_t row_pitch_, ssize_t slice_pitch_)
{
  return false;
}
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_DDS
//============================================================================
// get_texture_loader_dds
//============================================================================
namespace pfc
{
  bool get_texture_loader_dds(texture_loader::loader_variant_t&, texture_loader&)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_dds
//============================================================================
e_file_format_support pfc::texture_support_dds()
{
  return filefmtsupport_none;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_dds
//============================================================================
bool pfc::write_texture_dds(bin_output_stream_base&, const texture_writer_params_dds&, const void*, e_texture_format, unsigned, unsigned, unsigned, ssize_t, ssize_t)
{
  return false;
}
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_DDS
