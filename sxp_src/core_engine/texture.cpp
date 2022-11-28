//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "texture.h"
#include "sxp_src/core/math/math.h"
#include "sxp_src/core/math/bit_math.h"
#include "sxp_src/core/math/numeric.h"
#include "sxp_src/core/fsys/fsys.h"
#ifdef PFC_ENGINEOP_NVTEXTURETOOLS
#include "sxp_extlibs/nvtexturetools/src/nvtt/nvtt.h"
#endif
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// external library dependencies
//============================================================================
// nvtexturetools
#ifdef PFC_ENGINEOP_NVTEXTURETOOLS
#ifdef PFC_ENGINEOP_CUDA
#pragma comment(lib, PFC_STR(PFC_CAT3(nvtexturetools_,PFC_BUILD_STR,_cuda)PFC_COMPILER_LIB_EXT))
#pragma comment(lib, "cudart.lib")
#else
#pragma comment(lib, PFC_STR(PFC_CAT2(nvtexturetools_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
#endif
#endif
//----------------------------------------------------------------------------


//============================================================================
// texture format configuration
//============================================================================
//              name             bpp    type                 conversion-fmt    R-mask    G-mask    B-mask    A-mask   rgba-order
#define PFC_TEXFORMAT_LIST \
  PFC_TEXFORMAT(a8,               8, 1, texfmttype_rgba,          a8r8g8b8,    0,  0,    0,  0,    0,  0,    0,  8,   0x0004) \
  PFC_TEXFORMAT(r8,               8, 1, texfmttype_rgba,          a8r8g8b8,    0,  8,    0,  0,    0,  0,    0,  0,   0x0001) \
  PFC_TEXFORMAT(a16,             16, 1, texfmttype_rgba,      a32b32g32r32,    0,  0,    0,  0,    0,  0,    0, 16,   0x0004) \
  PFC_TEXFORMAT(r16,             16, 1, texfmttype_rgba,      a32b32g32r32,    0, 16,    0,  0,    0,  0,    0,  0,   0x0001) \
  PFC_TEXFORMAT(r16f,            16, 1, texfmttype_rgba16f,  a32b32g32r32f,    0, 16,    0,  0,    0,  0,    0,  0,   0x0001) \
  PFC_TEXFORMAT(a8r8,            16, 1, texfmttype_rgba,          a8r8g8b8,    0,  8,    0,  0,    0,  0,    8,  8,   0x0041) \
  PFC_TEXFORMAT(g8r8,            16, 1, texfmttype_rgba,          a8r8g8b8,    0,  8,    8,  8,    0,  0,    0,  0,   0x0021) \
  PFC_TEXFORMAT(r5g6b5,          16, 1, texfmttype_rgba,          a8r8g8b8,   11,  5,    5,  6,    0,  5,    0,  0,   0x0123) \
  PFC_TEXFORMAT(a1r5g5b5,        16, 1, texfmttype_rgba,          a8r8g8b8,   10,  5,    5,  5,    0,  5,   15,  1,   0x4123) \
  PFC_TEXFORMAT(a4r4g4b4,        16, 1, texfmttype_rgba,          a8r8g8b8,    8,  4,    4,  4,    0,  4,   12,  4,   0x4123) \
  PFC_TEXFORMAT(r8g8b8,          24, 1, texfmttype_rgba,          a8r8g8b8,   16,  8,    8,  8,    0,  8,    0,  0,   0x0123) \
  PFC_TEXFORMAT(b8g8r8,          24, 1, texfmttype_rgba,          a8r8g8b8,    0,  8,    8,  8,   16,  8,    0,  0,   0x0321) \
  PFC_TEXFORMAT(a32,             32, 1, texfmttype_rgba,      a32b32g32r32,    0,  0,    0,  0,    0,  0,    0, 32,   0x0004) \
  PFC_TEXFORMAT(r32,             32, 1, texfmttype_rgba,      a32b32g32r32,    0, 32,    0,  0,    0,  0,    0,  0,   0x0001) \
  PFC_TEXFORMAT(r32f,            32, 1, texfmttype_rgba32f,  a32b32g32r32f,    0, 32,    0,  0,    0,  0,    0,  0,   0x0001) \
  PFC_TEXFORMAT(a16r16,          32, 1, texfmttype_rgba,      a32b32g32r32,    0, 16,    0,  0,    0,  0,   16, 16,   0x0041) \
  PFC_TEXFORMAT(g16r16,          32, 1, texfmttype_rgba,      a32b32g32r32,    0, 16,   16, 16,    0,  0,    0,  0,   0x0021) \
  PFC_TEXFORMAT(g16r16f,         32, 1, texfmttype_rgba16f,  a32b32g32r32f,    0, 16,   16, 16,    0,  0,    0,  0,   0x0021) \
  PFC_TEXFORMAT(a8r8g8b8,        32, 1, texfmttype_rgba,          a8r8g8b8,   16,  8,    8,  8,    0,  8,   24,  8,   0x4123) \
  PFC_TEXFORMAT(a8b8g8r8,        32, 1, texfmttype_rgba,          a8r8g8b8,    0,  8,    8,  8,   16,  8,   24,  8,   0x4321) \
  PFC_TEXFORMAT(b8g8r8a8,        32, 1, texfmttype_rgba,          a8r8g8b8,    8,  8,   16,  8,   24,  8,    0,  8,   0x3214) \
  PFC_TEXFORMAT(a2b10g10r10,     32, 1, texfmttype_rgba,      a32b32g32r32,    0, 10,   10, 10,   20, 10,   30,  2,   0x4321) \
  PFC_TEXFORMAT(b16g16r16,       48, 1, texfmttype_rgba,      a32b32g32r32,    0, 16,   16, 16,   32, 16,    0,  0,   0x0321) \
  PFC_TEXFORMAT(a32r32,          64, 1, texfmttype_rgba,      a32b32g32r32,    0, 32,    0,  0,    0,  0,   32, 32,   0x0041) \
  PFC_TEXFORMAT(g32r32,          64, 1, texfmttype_rgba,      a32b32g32r32,    0, 32,   32, 32,    0,  0,    0,  0,   0x0021) \
  PFC_TEXFORMAT(g32r32f,         64, 1, texfmttype_rgba32f,  a32b32g32r32f,    0, 32,   32, 32,    0,  0,    0,  0,   0x0021) \
  PFC_TEXFORMAT(b16g16r16a16,    64, 1, texfmttype_rgba,      a32b32g32r32,   16, 16,   32, 16,   48, 16,    0, 16,   0x3214) \
  PFC_TEXFORMAT(a16b16g16r16,    64, 1, texfmttype_rgba,      a32b32g32r32,    0, 16,   16, 16,   32, 16,   48, 16,   0x4321) \
  PFC_TEXFORMAT(a16b16g16r16f,   64, 1, texfmttype_rgba16f,  a32b32g32r32f,    0, 16,   16, 16,   32, 16,   48, 16,   0x4321) \
  PFC_TEXFORMAT(b32g32r32f,      96, 1, texfmttype_rgba32f,  a32b32g32r32f,    0, 32,   32, 32,   64, 32,    0,  0,   0x0321) \
  PFC_TEXFORMAT(a32b32g32r32,   128, 1, texfmttype_rgba,      a32b32g32r32,    0, 32,   32, 32,   64, 32,   96, 32,   0x4321) \
  PFC_TEXFORMAT(a32b32g32r32f,  128, 1, texfmttype_rgba32f,  a32b32g32r32f,    0, 32,   32, 32,   64, 32,   96, 32,   0x4321) \
  PFC_TEXFORMAT(bc1,              4, 4, texfmttype_bc,            a8r8g8b8,    0, -1,    0, -1,    0, -1,    0,  0,   0x0000) \
  PFC_TEXFORMAT(bc1a,             4, 4, texfmttype_bc,            a8r8g8b8,    0, -1,    0, -1,    0, -1,    0, -1,   0x0000) \
  PFC_TEXFORMAT(bc2,              8, 4, texfmttype_bc,            a8r8g8b8,    0, -1,    0, -1,    0, -1,    0, -1,   0x0000) \
  PFC_TEXFORMAT(bc3,              8, 4, texfmttype_bc,            a8r8g8b8,    0, -1,    0, -1,    0, -1,    0, -1,   0x0000) \
  PFC_TEXFORMAT(bc6h,             8, 4, texfmttype_bc,       a32b32g32r32f,    0, -1,    0, -1,    0, -1,    0,  0,   0x0000) \
  PFC_TEXFORMAT(bc7,              8, 4, texfmttype_bc,            a8r8g8b8,    0, -1,    0, -1,    0, -1,    0, -1,   0x0000)
//----------------------------------------------------------------------------
  

//============================================================================
// list of texture formats for bidirectional (to/from) conversion
//============================================================================
#define PFC_TEXFORMAT_CONVERSION_LIST \
  PFC_TEXFORMAT(a8)            \
  PFC_TEXFORMAT(r8)            \
  PFC_TEXFORMAT(a16)           \
  PFC_TEXFORMAT(r16)           \
  PFC_TEXFORMAT(r16f)          \
  PFC_TEXFORMAT(a8r8)          \
  PFC_TEXFORMAT(g8r8)          \
  PFC_TEXFORMAT(r5g6b5)        \
  PFC_TEXFORMAT(a1r5g5b5)      \
  PFC_TEXFORMAT(a4r4g4b4)      \
  PFC_TEXFORMAT(r8g8b8)        \
  PFC_TEXFORMAT(b8g8r8)        \
  PFC_TEXFORMAT(a32)           \
  PFC_TEXFORMAT(r32)           \
  PFC_TEXFORMAT(r32f)          \
  PFC_TEXFORMAT(a16r16)        \
  PFC_TEXFORMAT(g16r16)        \
  PFC_TEXFORMAT(g16r16f)       \
  PFC_TEXFORMAT(a8r8g8b8)      \
  PFC_TEXFORMAT(a8b8g8r8)      \
  PFC_TEXFORMAT(b8g8r8a8)      \
  PFC_TEXFORMAT(a2b10g10r10)   \
  PFC_TEXFORMAT(b16g16r16)     \
  PFC_TEXFORMAT(a32r32)        \
  PFC_TEXFORMAT(g32r32)        \
  PFC_TEXFORMAT(g32r32f)       \
  PFC_TEXFORMAT(b16g16r16a16)  \
  PFC_TEXFORMAT(a16b16g16r16)  \
  PFC_TEXFORMAT(a16b16g16r16f) \
  PFC_TEXFORMAT(b32g32r32f)    \
  PFC_TEXFORMAT(a32b32g32r32)  \
  PFC_TEXFORMAT(a32b32g32r32f)
//----------------------------------------------------------------------------


//============================================================================
// locals
//============================================================================
namespace
{
  //==========================================================================
  // get_converter_input_format
  //==========================================================================
  e_texture_format get_converter_input_format(e_texture_format fmt_)
  {
    // get texture format for texture conversion for given format
    switch(fmt_)
    {
      #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
        case texfmt_##name__: return texfmt_##conv_format__;
      PFC_TEXFORMAT_LIST
      #undef PFC_TEXFORMAT
      case texfmt_none:
      case texfmt_enum_end: PFC_ERROR("Invalid argument\r\n");
    }
    PFC_ERROR("Unsupported texture format\r\n");
    return texfmt_none;
  }
  //--------------------------------------------------------------------------


  //==========================================================================
  // cpu_texture_manager_2d
  //==========================================================================
  class cpu_texture_manager_2d: public texture_manager_base
  {
  public:
    cpu_texture_manager_2d()
    {
      // initialize manager
      mip_data=0;
      width=height=0;
      num_mips=0;
      array_size=0;
      m_format=texfmt_none;
    }
    //----

    virtual void create_texture(const texture_loader &tl_, const texture_loader_params &params_, unsigned num_mips_)
    {
      // create texture resources
      unsigned block_size=texfmt_blocksize(params_.target_format);
      width=max(block_size, texsize(tl_.width(), params_.resize_mode)>>params_.first_mip_level);
      height=max(block_size, texsize(tl_.height(), params_.resize_mode)>>params_.first_mip_level);
      num_mips=texture_mips_2d(tl_.width(), tl_.height(), params_.target_format, num_mips_);
      array_size=tl_.array_size();
      m_format=params_.target_format;
      mip_data=PFC_MEM_ALLOC(texture_size_2d(width, height, params_.target_format, num_mips)*array_size);
    }
    //----

    virtual void finalize()
    {
    }
    //----

    virtual void *lock(const texture_layer &layer_, int &pitch_)
    {
      // return pointer & pitch of given mip level
      pitch_=texture_pitch(width, m_format, layer_.mip_level);
      void *data=((uint8_t*)mip_data)+(layer_.mip_level?texture_size_2d(width, height, m_format, layer_.mip_level):0)+layer_.array_slice*texture_size_2d(width, height, m_format, num_mips);
      return data;
    }
    //----

    virtual void unlock(const texture_layer &layer_)
    {
    }
    //------------------------------------------------------------------------

    // public data
    void *mip_data;
    unsigned width, height;
    unsigned num_mips;
    unsigned array_size;
    //------------------------------------------------------------------------

  private:
    e_texture_format m_format;
  };
  //--------------------------------------------------------------------------


  //==========================================================================
  // cpu_texture_manager_3d
  //==========================================================================
  class cpu_texture_manager_3d: public texture_manager_base
  {
  public:
    cpu_texture_manager_3d()
    {
      // initialize manager
      mip_data=0;
      width=height=depth=0;
      m_format=texfmt_none;
      num_mips=0;
    }
    //----

    virtual void create_texture(const texture_loader &tl_, const texture_loader_params &params_, unsigned num_mips_)
    {
      // create texture resources
      unsigned block_size=texfmt_blocksize(params_.target_format);
      width=max(block_size, texsize(tl_.width(), params_.resize_mode)>>params_.first_mip_level);
      height=max(block_size, texsize(tl_.height(), params_.resize_mode)>>params_.first_mip_level);
      depth=max(block_size, texsize(tl_.depth(), params_.resize_mode)>>params_.first_mip_level);
      num_mips=texture_mips_3d(tl_.width(), tl_.height(), tl_.depth(), params_.target_format, num_mips_);
      m_format=params_.target_format;
      mip_data=PFC_MEM_ALLOC(texture_size_3d(width, height, depth, m_format, num_mips));
    }
    //----

    virtual void finalize()
    {
    }
    //----

    virtual void *lock(const texture_layer &layer_, int &pitch_)
    {
      // return pointer & pitch of given mip level
      pitch_=texture_pitch(width, m_format, layer_.mip_level);
      unsigned slice_pitch=texture_mip_size_2d(width, height, m_format, layer_.mip_level);
      void *data=((uint8_t*)mip_data)+(layer_.mip_level?texture_size_3d(width, height, depth, m_format, layer_.mip_level):0)+slice_pitch*layer_.volume_slice;
      return data;
    }
    //----

    virtual void unlock(const texture_layer &layer_)
    {
    }
    //------------------------------------------------------------------------

    // public data
    void *mip_data;
    unsigned width, height, depth;
    unsigned num_mips;
    //------------------------------------------------------------------------

  private:
    e_texture_format m_format;
  };
  //--------------------------------------------------------------------------


  //==========================================================================
  // cpu_texture_manager_cube
  //==========================================================================
  class cpu_texture_manager_cube: public texture_manager_base
  {
  public:
    cpu_texture_manager_cube()
    {
      // initialize manager
      edge_len=0;
      num_mips=0;
      array_size=0;
      m_face_size=0;
      m_format=texfmt_none;
    }
    //----

    virtual void create_texture(const texture_loader &tl_, const texture_loader_params &params_, unsigned num_mips_)
    {
      // create texture data
      unsigned block_size=texfmt_blocksize(params_.target_format);
      edge_len=max(block_size, texsize(tl_.width(), params_.resize_mode)>>params_.first_mip_level);
      num_mips=texture_mips_2d(tl_.width(), tl_.height(), params_.target_format, num_mips_);
      array_size=tl_.array_size();
      m_format=params_.target_format;
      m_face_size=texture_size_2d(edge_len, edge_len, m_format, num_mips);
      mip_data.resize(array_size*6);
      for(unsigned fi=0; fi<6; ++fi)
        mip_data[fi]=PFC_MEM_ALLOC(m_face_size);
    }
    //----

    void finalize()
    {
    }
    //----

    virtual void *lock(const texture_layer &layer_, int &pitch_)
    {
      // return pointer & pitch of given mip level, and setup sub-resource
      pitch_=texture_pitch(edge_len, m_format, layer_.mip_level);
      void *data=((char*)mip_data[layer_.face+layer_.array_slice*6])+(layer_.mip_level?texture_size_2d(edge_len, edge_len, m_format, layer_.mip_level):0);
      return data;
    }
    //----

    virtual void unlock(const texture_layer &layer_)
    {
    }
    //------------------------------------------------------------------------

    // public data
    array<void*> mip_data;
    unsigned edge_len;
    unsigned num_mips;
    //------------------------------------------------------------------------

  private:
    unsigned m_face_size;
    unsigned array_size;
    e_texture_format m_format;
  };
} // namespace <anonymous>
//----------------------------------------------------------------------------


//============================================================================
// CUDA acceleration
//============================================================================
static bool s_is_cuda_texture_compression=true;
//----

void pfc::enable_cuda_texture_compression(bool enable_)
{
  s_is_cuda_texture_compression=enable_;
}
//----

bool pfc::is_cuda_texture_compression()
{
  return s_is_cuda_texture_compression;
}
//----------------------------------------------------------------------------


//============================================================================
// enum_str
//============================================================================
// e_texture_type
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_texture_type
#define PFC_ENUM_PREFIX textype_
#define PFC_ENUM_VALS PFC_ENUM_VAL(2d)\
                      PFC_ENUM_VAL(3d)\
                      PFC_ENUM_VAL(cube)
#include "sxp_src/core/enum.inc"
//----

// e_texture_content
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_texture_content
#define PFC_ENUM_PREFIX texcontent_
#define PFC_ENUM_VALS PFC_ENUM_VAL(color)\
                      PFC_ENUM_VAL(normal)
#include "sxp_src/core/enum.inc"
//----

// e_texture_format_type
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_texture_format_type
#define PFC_ENUM_PREFIX texfmttype_
#define PFC_ENUM_VALS PFC_ENUM_VAL(rgba)\
                      PFC_ENUM_VAL(rgba16f)\
                      PFC_ENUM_VAL(rgba32f)\
                      PFC_ENUM_VAL(bc)
#include "sxp_src/core/enum.inc"
//----

// e_texture_format
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_texture_format
#define PFC_ENUM_PREFIX texfmt_
#define PFC_ENUM_VALS PFC_ENUM_VAL(a8)\
                      PFC_ENUM_VAL(r8)\
                      PFC_ENUM_VAL(a16)\
                      PFC_ENUM_VAL(r16)\
                      PFC_ENUM_VAL(r16f)\
                      PFC_ENUM_VAL(a8r8)\
                      PFC_ENUM_VAL(g8r8)\
                      PFC_ENUM_VAL(r5g6b5)\
                      PFC_ENUM_VAL(a1r5g5b5)\
                      PFC_ENUM_VAL(a4r4g4b4)\
                      PFC_ENUM_VAL(r8g8b8)\
                      PFC_ENUM_VAL(b8g8r8)\
                      PFC_ENUM_VAL(r32)\
                      PFC_ENUM_VAL(r32f)\
                      PFC_ENUM_VAL(a16r16)\
                      PFC_ENUM_VAL(g16r16)\
                      PFC_ENUM_VAL(g16r16f)\
                      PFC_ENUM_VAL(a8r8g8b8)\
                      PFC_ENUM_VAL(a8b8g8r8)\
                      PFC_ENUM_VAL(b8g8r8a8)\
                      PFC_ENUM_VAL(a2b10g10r10)\
                      PFC_ENUM_VAL(b16g16r16)\
                      PFC_ENUM_VAL(a32r32)\
                      PFC_ENUM_VAL(g32r32)\
                      PFC_ENUM_VAL(g32r32f)\
                      PFC_ENUM_VAL(b16g16r16a16)\
                      PFC_ENUM_VAL(a16b16g16r16)\
                      PFC_ENUM_VAL(a16b16g16r16f)\
                      PFC_ENUM_VAL(a32b32g32r32)\
                      PFC_ENUM_VAL(a32b32g32r32f)\
                      PFC_ENUM_VAL(bc1)\
                      PFC_ENUM_VAL(bc1a)\
                      PFC_ENUM_VAL(bc2)\
                      PFC_ENUM_VAL(bc3)\
                      PFC_ENUM_VAL(bc6h)\
                      PFC_ENUM_VAL(bc7)
#define PFC_ENUM_DEP_VALS PFC_ENUM_DEP_VAL(dxt1, bc1)\
                          PFC_ENUM_DEP_VAL(dxt1a, bc1a)\
                          PFC_ENUM_DEP_VAL(dxt3, bc2)\
                          PFC_ENUM_DEP_VAL(dxt5, bc3)
#include "sxp_src/core/enum.inc"
//----

// e_texture_color_space
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_texture_color_space
#define PFC_ENUM_PREFIX texcolspace_
#define PFC_ENUM_VALS PFC_ENUM_VAL(linear_rgb)\
                      PFC_ENUM_VAL(srgb)
#include "sxp_src/core/enum.inc"
//----

// e_mip_filter
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_mip_filter
#define PFC_ENUM_PREFIX mipfilter_
#define PFC_ENUM_VALS PFC_ENUM_VAL(box)\
                      PFC_ENUM_VAL(sinc)
#include "sxp_src/core/enum.inc"
//----

// e_texture_filter
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_texture_filter
#define PFC_ENUM_PREFIX texfilter_
#define PFC_ENUM_VALS PFC_ENUM_VAL(point)\
                      PFC_ENUM_VAL(linear)\
                      PFC_ENUM_VAL(anisotropic)
#include "sxp_src/core/enum.inc"
//----

// e_texture_compression_quality
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_texture_compression_quality
#define PFC_ENUM_PREFIX texcq_
#define PFC_ENUM_VALS PFC_ENUM_VAL(fastest)\
                      PFC_ENUM_VAL(normal)\
                      PFC_ENUM_VAL(production)\
                      PFC_ENUM_VAL(highest)
#include "sxp_src/core/enum.inc"
//----

// e_texture_resize_mode
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_texture_resize_mode
#define PFC_ENUM_PREFIX texresize_
#define PFC_ENUM_VALS PFC_ENUM_VAL(none)\
                      PFC_ENUM_VAL(prev_pow2)\
                      PFC_ENUM_VAL(next_pow2)\
                      PFC_ENUM_VAL(nearest_pow2)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// texformat_cfg
//============================================================================
template<e_texture_format format> struct texformat_cfg;
#define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
template<>\
struct texformat_cfg<texfmt_##name__>\
{\
  enum {bpp=bpp__,\
        block_size=block_size__,\
        type=type__,\
        conversion_format=texfmt_##conv_format__,\
        rgba_order=rgba_order__,\
        rmask_pos=rmask_pos__, rmask_size=rmask_size__>0?rmask_size__:0,\
        gmask_pos=gmask_pos__, gmask_size=gmask_size__>0?gmask_size__:0,\
        bmask_pos=bmask_pos__, bmask_size=bmask_size__>0?bmask_size__:0,\
        amask_pos=amask_pos__, amask_size=amask_size__>0?amask_size__:0};\
};
PFC_TEXFORMAT_LIST
#undef PFC_TEXFORMAT
//----------------------------------------------------------------------------


//============================================================================
// texture_loader::loader_null
//============================================================================
class texture_loader::loader_null: public loader_base
{
public:
  // construction
  loader_null();
  //--------------------------------------------------------------------------

  // data loading
  virtual bool layer(texture_layer&) const;
  virtual void load_layer(void*, unsigned pitch_);
  virtual void skip_layer();
};
//----------------------------------------------------------------------------

texture_loader::loader_null::loader_null()
{
}
//----------------------------------------------------------------------------

bool texture_loader::loader_null::layer(texture_layer&) const
{
  return false;
}
//----

void texture_loader::loader_null::load_layer(void*, unsigned pitch_)
{
}
//----

void texture_loader::loader_null::skip_layer()
{
}
//----------------------------------------------------------------------------


//============================================================================
// texture_loader
//============================================================================
namespace pfc
{
  bool get_texture_loader_dds(texture_loader::loader_variant_t&, texture_loader&);
  bool get_texture_loader_jp2(texture_loader::loader_variant_t&, texture_loader&);
  bool get_texture_loader_jpg(texture_loader::loader_variant_t&, texture_loader&);
  bool get_texture_loader_png(texture_loader::loader_variant_t&, texture_loader&);
  bool get_texture_loader_psd(texture_loader::loader_variant_t&, texture_loader&);
  bool get_texture_loader_tga(texture_loader::loader_variant_t&, texture_loader&);
  bool get_texture_loader_tiff(texture_loader::loader_variant_t&, texture_loader&);
  bool get_texture_loader_webp(texture_loader::loader_variant_t&, texture_loader&);
} // namespace pfc
//----

texture_loader::texture_loader(bin_input_stream_base &s_)
  :m_stream(s_)
  ,m_loader(meta_type<loader_null>())
{
  // init
  m_type=textype_none;
  m_format=texfmt_none;
  m_target_format=texfmt_none;
  m_enable_gamma=true;
  m_num_mips=0;
  m_width=0;
  m_height=0;
  m_depth=0;
  m_array_size=0;

  // try to load the texture with different format loaders
  m_file_format=filefmt_none;
  if(get_texture_loader_jpg(m_loader, *this))
    m_file_format=filefmt_jpg;
  else if(get_texture_loader_png(m_loader, *this))
    m_file_format=filefmt_png;
  else if(get_texture_loader_webp(m_loader, *this))
    m_file_format=filefmt_webp;
  else if(get_texture_loader_dds(m_loader, *this))
    m_file_format=filefmt_dds;
  else if(get_texture_loader_jp2(m_loader, *this))
    m_file_format=filefmt_jp2;
  else if(get_texture_loader_tga(m_loader, *this))
    m_file_format=filefmt_tga;
  else if(get_texture_loader_tiff(m_loader, *this))
    m_file_format=filefmt_tiff;
  else if(get_texture_loader_psd(m_loader, *this))
    m_file_format=filefmt_psd;
  else
    PFC_WARN("Unable to load the texture format\r\n");
  m_target_format=m_format;
}
//----------------------------------------------------------------------------

void texture_loader::load_layer(void *p_, unsigned pitch_)
{
  // load texture layer
  PFC_ASSERT_MSG(m_format==m_target_format || (texfmt_type(m_format)!=texfmttype_bc && texfmt_type(m_target_format)!=texfmttype_bc),
                 ("Unable to perform format conversion from %s to %s\r\n", enum_string(m_format), enum_string(m_target_format)));
  if(!pitch_)
    pitch_=m_width*texfmt_bpp(m_target_format)/8;
  m_loader->load_layer(p_, pitch_);
}
//----------------------------------------------------------------------------


//============================================================================
// texture_loader::loader_base
//============================================================================
texture_loader::loader_base::~loader_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// texture_manager_base
//============================================================================
texture_manager_base::texture_manager_base()
{
}
//----------------------------------------------------------------------------


//============================================================================
// texture_converter
//============================================================================
texture_converter::texture_converter()
{
  reset();
}
//----

void texture_converter::reset()
{
  // initialize converter
  m_input_format=texfmt_a8r8g8b8;
  m_target_format=texfmt_none;
  m_content_type=texcontent_color;
  m_compression_quality=texcq_highest;
  m_mip_filter=mipfilter_sinc;
  m_gamma_input=1.0f;
  m_gamma_output=1.0f;
  mem_zero(m_targets, sizeof(m_targets));
}
//----------------------------------------------------------------------------

void texture_converter::set_input_format(e_texture_format fmt_)
{
  PFC_ASSERT(fmt_==texfmt_a8r8g8b8 || fmt_==texfmt_a16b16g16r16f || fmt_==texfmt_a32b32g32r32f);
  m_input_format=fmt_;
}
//----------------------------------------------------------------------------

void texture_converter::convert(const void *source_, unsigned width_, unsigned height_, e_texture_resize_mode resize_mode_)
{
#ifdef PFC_ENGINEOP_NVTEXTURETOOLS
  // check inputs
  using namespace nvtt;
  PFC_ASSERT_MSG(source_, ("Source texture not defined\r\n"));
  PFC_ASSERT_MSG(m_target_format!=texfmt_none, ("Target format not defined\r\n"));

  // setup input options
  InputOptions iop;
  switch(m_input_format)
  {
    case texfmt_a8r8g8b8: iop.setFormat(InputFormat_BGRA_8UB); break;
    case texfmt_a16b16g16r16f: iop.setFormat(InputFormat_RGBA_16F); break;
    case texfmt_a32b32g32r32f: iop.setFormat(InputFormat_RGBA_32F); break;
    default: PFC_ERRORF("Given input format \"%s\" not supported\r\n", enum_string(m_input_format));
  }
  switch(m_mip_filter)
  {
    case mipfilter_none: iop.setMipmapGeneration(false); break;
    case mipfilter_box: iop.setMipmapFilter(MipmapFilter_Box); break;
    case mipfilter_sinc: iop.setMipmapFilter(MipmapFilter_Kaiser); break;
    default: PFC_ERRORF("Given mip filter \"%s\" not supported\r\n", enum_string(m_mip_filter));
  }
  if(m_content_type==texcontent_normal)
  {
    iop.setNormalMap(true);
    iop.setNormalizeMipmaps(true);
  }
  switch(resize_mode_)
  {
    case texresize_none: iop.setRoundMode(RoundMode_None); break;
    case texresize_prev_pow2: iop.setRoundMode(RoundMode_ToPreviousPowerOfTwo); break;
    case texresize_next_pow2: iop.setRoundMode(RoundMode_ToNextPowerOfTwo); break;
    case texresize_nearest_pow2: iop.setRoundMode(RoundMode_ToNearestPowerOfTwo); break;
    default: PFC_ERRORF("Texture resize mode \"%s\" not supported\r\n", enum_string(resize_mode_));
  }
  iop.setTextureLayout(TextureType_2D, width_, height_);
  iop.setMipmapData(source_, width_, height_);
  iop.setGamma(m_gamma_input, m_gamma_output);

  //==========================================================================
  // output_handler
  //==========================================================================
  struct output_handler: OutputHandler
  {
    output_handler(pair<void*, unsigned> *targets_, unsigned full_scan_bytes_)
    {
      targets=targets_;
      full_scan_bytes=full_scan_bytes_;
      scan_bytes=0;
      scan_pitch=0;
      scan_start=0;
      scan_end=0;
      scan_cursor=0;
    }
    //------------------------------------------------------------------------

    virtual void beginImage(int size_, int width_, int height_, int depth_, int face_, int mip_level_)
    {
      // init mip level
      PFC_ASSERT(mip_level_<16);
      scan_bytes=full_scan_bytes>>mip_level_;
      scan_pitch=targets[mip_level_].second;
      scan_start=targets[mip_level_].first;
      scan_end=(uint8_t*)scan_start+scan_bytes;
      scan_cursor=scan_start;
    }
    //------------------------------------------------------------------------

    virtual void endImage()
    {
    }
    //------------------------------------------------------------------------

    virtual bool writeData(const void *data_, int size_)
    {
      // ignore non-image data
      if(!scan_start)
        return true;

      // copy data
      do 
      {
        unsigned num_bytes=min(int((uint8_t*)scan_end-(uint8_t*)scan_cursor), size_);
        mem_copy(scan_cursor, data_, num_bytes);
        size_-=num_bytes;
        (uint8_t*&)data_+=num_bytes;
        (uint8_t*&)scan_cursor+=num_bytes;
        PFC_ASSERT(scan_cursor<=scan_end);
        if(scan_cursor==scan_end)
        {
          // restart scan
          (uint8_t*&)scan_start+=scan_pitch;
          scan_end=(uint8_t*)scan_start+scan_bytes;
          scan_cursor=scan_start;
        }
      } while(size_);
      return true;
    }
    //------------------------------------------------------------------------

    pair<void*, unsigned> *targets;
    unsigned full_scan_bytes;
    unsigned scan_bytes;
    unsigned scan_pitch;
    void *scan_start;
    void *scan_end;
    void *scan_cursor;
  };
  //--------------------------------------------------------------------------

  // setup target format
  CompressionOptions cop;
  unsigned full_scan_size=0, width=texsize(width_, resize_mode_);
  switch(texfmt_type(m_target_format))
  {
    // BC-format target type
    case texfmttype_bc:
    {
      // set BC-format target format
      width=(width+3)&-4;
      switch(m_target_format)
      {
        case texfmt_bc1: cop.setFormat(Format_BC1); full_scan_size=width*2; break;
        case texfmt_bc1a: cop.setFormat(Format_BC1a); full_scan_size=width*2; break;
        case texfmt_bc2: cop.setFormat(Format_BC2); full_scan_size=width*4; break;
        case texfmt_bc3: cop.setFormat(Format_BC3); full_scan_size=width*4; break;
        case texfmt_bc6h: cop.setFormat(Format_BC6); full_scan_size=width*4; break;
        case texfmt_bc7: cop.setFormat(Format_BC7); full_scan_size=width*4; break;
        default: PFC_ERROR("Unsupported target BC-format\r\n");
      }
    } break;

    // uint RGBA target type
    case texfmttype_rgba:
    {
      // set RGBA target format
      unsigned target_bpp=texfmt_bpp(m_target_format);
      full_scan_size=width*target_bpp/8;
      uint32_t rmask, gmask, bmask, amask;
      texfmt_rgba_mask32(m_target_format, rmask, gmask, bmask, amask);
      cop.setFormat(Format_RGB);
      cop.setPixelFormat(target_bpp, rmask, gmask, bmask, amask);
    } break;

    // RGBA 16-bit float target type
    case texfmttype_rgba16f:
    {
      PFC_ERROR_NOT_IMPL();
      /*todo*/
    } break;

    // RGBA 32-bit float target type
    case texfmttype_rgba32f:
    {
      PFC_ERROR_NOT_IMPL();
      /*todo*/
    } break;

    // Unsupported
    default: PFC_ERRORF("Unsupported target format type \"%s\"\r\n", enum_string(m_target_format));
  }

  // setup compression quality
  switch(m_compression_quality)
  {
    case texcq_fastest:    cop.setQuality(Quality_Fastest); break;
    case texcq_normal:     cop.setQuality(Quality_Normal); break;
    case texcq_production: cop.setQuality(Quality_Production); break;
    case texcq_highest:    cop.setQuality(Quality_Highest); break;
    default: PFC_ERRORF("Unsupported texture compression quality setting \"%s\"\r\n", enum_string(m_compression_quality));
  }

  // setup output options
  OutputOptions oop;
  oop.setContainer(Container_DDS10);
  output_handler oh(m_targets, full_scan_size);
  oop.setOutputHandler(&oh);

  // compress the texture & generate mipmaps
  Compressor c;
  c.enableCudaAcceleration(s_is_cuda_texture_compression);
  c.process(iop, cop, oop);
#else
  PFC_ERROR("Unable to perform texture conversion without NVIDIA Texture Tools library\r\n");
#endif
}
//----------------------------------------------------------------------------


//============================================================================
// tex2d_base
//============================================================================
PFC_CLASS_DEF(tex2d_base);
//----------------------------------------------------------------------------

void tex2d_base::init(unsigned width_, unsigned height_, int num_mips_, e_texture_format format_, e_texture_color_space color_space_, const mip_data*, unsigned array_size_)
{
  // setup texture properties
  m_format=format_;
  m_color_space=color_space_;
  m_num_mips=format_?texture_mips_2d(width_, height_, format_, num_mips_):num_mips_;
  m_width=width_;
  m_height=height_;
  m_source_width=width_;
  m_source_height=height_;
  m_array_size=array_size_; 
}
//----

void tex2d_base::load(bin_input_stream_base &s_, const texture_loader_params &params_)
{
  texture_loader tl(s_);
  load(tl, params_);
}
//----

void tex2d_base::swap(tex2d_base &tex_)
{
  // swap 2d texture contents
  pfc::swap(m_format, tex_.m_format);
  pfc::swap(m_color_space, tex_.m_color_space);
  pfc::swap(m_num_mips, tex_.m_num_mips);
  pfc::swap(m_width, tex_.m_width);
  pfc::swap(m_height, tex_.m_height);
  pfc::swap(m_array_size, tex_.m_array_size);
  pfc::swap(m_source_height, tex_.m_source_height);
  pfc::swap(m_source_width, tex_.m_source_width);
}
//----------------------------------------------------------------------------


//============================================================================
// tex3d_base
//============================================================================
PFC_CLASS_DEF(tex3d_base);
//----------------------------------------------------------------------------

void tex3d_base::init(unsigned width_, unsigned height_, unsigned depth_, int num_mips_, e_texture_format format_, e_texture_color_space color_space_, const mip_data*)
{
  // setup volume texture properties
  m_format=format_;
  m_color_space=color_space_;
  m_num_mips=format_?texture_mips_3d(width_, height_, depth_, format_, num_mips_):num_mips_;
  m_width=width_;
  m_height=height_;
  m_depth=depth_;
  m_source_width=width_;
  m_source_height=height_;
  m_source_depth=depth_;
}
//----

void tex3d_base::load(bin_input_stream_base &s_, const texture_loader_params &params_)
{
  texture_loader tl(s_);
  load(tl, params_);
}
//----

void tex3d_base::swap(tex3d_base &tex_)
{
  // swap 3d texture contents
  pfc::swap(m_format, tex_.m_format);
  pfc::swap(m_color_space, tex_.m_color_space);
  pfc::swap(m_num_mips, tex_.m_num_mips);
  pfc::swap(m_width, tex_.m_width);
  pfc::swap(m_height, tex_.m_height);
  pfc::swap(m_depth, tex_.m_depth);
  pfc::swap(m_source_width, tex_.m_source_width);
  pfc::swap(m_source_height, tex_.m_source_height);
  pfc::swap(m_source_depth, tex_.m_source_depth);
}
//----------------------------------------------------------------------------


//============================================================================
// texcube_base
//============================================================================
PFC_CLASS_DEF(texcube_base);
//----------------------------------------------------------------------------

void texcube_base::init(unsigned edge_len_, int num_mips_, e_texture_format format_, e_texture_color_space color_space_, const mip_data*)
{
  // setup cube texture properties
  m_format=format_;
  m_color_space=color_space_;
  m_num_mips=format_?texture_mips_2d(edge_len_, edge_len_, format_, num_mips_):num_mips_;
  m_edge_len=edge_len_;
  m_source_edge_len=edge_len_;
}
//----

void texcube_base::load(bin_input_stream_base &s_, const texture_loader_params &params_)
{
  texture_loader tl(s_);
  load(tl, params_);
}
//----

void texcube_base::swap(texcube_base &tex_)
{
  // swap cube texture contents
  pfc::swap(m_format, tex_.m_format);
  pfc::swap(m_color_space, tex_.m_color_space);
  pfc::swap(m_num_mips, tex_.m_num_mips);
  pfc::swap(m_edge_len, tex_.m_edge_len);
  pfc::swap(m_source_edge_len, tex_.m_source_edge_len);
}
//----------------------------------------------------------------------------


//============================================================================
// cpu_tex2d
//============================================================================
PFC_CLASS_DEF(cpu_tex2d);
PFC_INTROSPEC_CPP_DEF(cpu_tex2d)
{
  PFC_CUSTOM_STREAMING(0);
  switch(unsigned(PE::pe_type))
  {
    case penum_input:
    {
      // release old texture resources and load texture data
      PFC_MEM_FREE(m_mip_data);
      m_mip_data=0;
      unsigned tex_size=texture_size_2d(m_width, m_height, m_format, m_num_mips)*m_array_size;
      m_mip_data=PFC_MEM_ALLOC(tex_size);
      pe_.data(m_mip_data, tex_size);
    } break;

    case penum_output:
    {
      // save texture data
      if(m_width && m_height)
      {
        unsigned tex_size=texture_size_2d(m_width, m_height, m_format, m_num_mips)*m_array_size;
        pe_.data(m_mip_data, tex_size);
      }
    }
  }
}
//----------------------------------------------------------------------------

cpu_tex2d::cpu_tex2d()
  :m_mip_data(0)
{
}
//----

cpu_tex2d::~cpu_tex2d()
{
  PFC_MEM_FREE(m_mip_data);
}
//----

void cpu_tex2d::init(unsigned width_, unsigned height_, int num_mips_, e_texture_format format_, e_texture_color_space color_space_, const mip_data *data_, unsigned array_size_)
{
  // release old texture
  PFC_MEM_FREE(m_mip_data);
  m_mip_data=0;
  tex2d_base::init(width_, height_, num_mips_, format_, color_space_, 0);

  // allocate new texture data
  unsigned tex_size=texture_size_2d(m_width, m_height, m_format, m_num_mips);
  m_mip_data=PFC_MEM_ALLOC(tex_size);
  uint8_t *data_ptr=(uint8_t*)m_mip_data;
  for(unsigned mi=0; mi<m_num_mips; ++mi)
  {
    if(const mip_data *data=data_&&mi<m_num_mips?data_+mi:0)
    {
      unsigned mip_size=texture_mip_size_2d(m_width, m_height, m_format, mi);
      mem_copy(data_ptr, data->data, mip_size);
      data_ptr+=mip_size;
    }
  }
}
//----

void cpu_tex2d::load(texture_loader &tl_, const texture_loader_params &params_)
{
  // release old texture resource & resource view
  PFC_ASSERT_MSG(tl_.type()==textype_2d, ("Trying to load %s texture as a 2d texture\r\n", enum_string(tl_.type())));
  PFC_MEM_FREE(m_mip_data);
  m_mip_data=0;

  // load 2d texture
  cpu_texture_manager_2d manager;
  load_texture(manager, tl_, params_);
  m_mip_data=manager.mip_data;
  tex2d_base::init(manager.width, manager.height, manager.num_mips, params_.target_format?params_.target_format:tl_.format(), params_.color_space, 0);
  m_source_width=tl_.width();
  m_source_height=tl_.height();
}
//----

void cpu_tex2d::swap(tex2d_base &tex_)
{
  // swap 2d texture contents
  tex2d_base::swap(tex_);
  cpu_tex2d &tex=safe_cast<cpu_tex2d&>(tex_);
  pfc::swap(m_mip_data, tex.m_mip_data);
}
//----------------------------------------------------------------------------


//============================================================================
// cpu_tex3d
//============================================================================
PFC_CLASS_DEF(cpu_tex3d);
PFC_INTROSPEC_CPP_DEF(cpu_tex3d)
{
  PFC_CUSTOM_STREAMING(0);
  switch(unsigned(PE::pe_type))
  {
    case penum_input:
    {
      // release old texture resources and load texture data
      PFC_MEM_FREE(m_mip_data);
      m_mip_data=0;
      unsigned tex_size=texture_size_3d(m_width, m_height, m_depth, m_format, m_num_mips);
      m_mip_data=PFC_MEM_ALLOC(tex_size);
      pe_.data(m_mip_data, tex_size);
    } break;

    case penum_output:
    {
      // save texture data
      if(m_width && m_height && m_depth)
      {
          unsigned tex_size=texture_size_3d(m_width, m_height, m_depth, m_format, m_num_mips);
          pe_.data(m_mip_data, tex_size);
      }
    }
  }
}
//----------------------------------------------------------------------------

cpu_tex3d::cpu_tex3d()
  :m_mip_data(0)
{
}
//----

cpu_tex3d::~cpu_tex3d()
{
  PFC_MEM_FREE(m_mip_data);
}
//----

void cpu_tex3d::init(unsigned width_, unsigned height_, unsigned depth_, int num_mips_, e_texture_format format_, e_texture_color_space color_space_, const mip_data *data_)
{
  // release old texture resource & resource view
  PFC_MEM_FREE(m_mip_data);
  m_mip_data=0;
  tex3d_base::init(width_, height_, depth_, num_mips_, format_, color_space_, data_);

  // copy mip data to the texture
  unsigned tex_size=texture_size_3d(m_width, m_height, m_depth, m_format, m_num_mips);
  m_mip_data=PFC_MEM_ALLOC(tex_size);
  mem_copy(m_mip_data, data_, tex_size);
}
//----

void cpu_tex3d::load(texture_loader &tl_, const texture_loader_params &params_)
{
  // release old texture
  PFC_ASSERT_MSG(tl_.type()==textype_3d, ("Trying to load %s texture as a 3d texture\r\n", enum_string(tl_.type())));
  PFC_MEM_FREE(m_mip_data);
  m_mip_data=0;

  // load volume texture
  cpu_texture_manager_3d manager;
  load_texture(manager, tl_, params_);
  m_mip_data=manager.mip_data;
  tex3d_base::init(manager.width, manager.height, manager.depth, manager.num_mips, params_.target_format?params_.target_format:tl_.format(), params_.color_space, 0);
  m_source_width=tl_.width();
  m_source_height=tl_.height();
  m_source_depth=tl_.depth();
}
//----

void cpu_tex3d::swap(tex3d_base &tex_)
{
  // swap 3d texture contents
  tex3d_base::swap(tex_);
  cpu_tex3d &tex=safe_cast<cpu_tex3d&>(tex_);
  pfc::swap(m_mip_data, tex.m_mip_data);
}
//----------------------------------------------------------------------------


//============================================================================
// cpu_texcube
//============================================================================
PFC_CLASS_DEF(cpu_texcube);
PFC_INTROSPEC_CPP_DEF(cpu_texcube)
{
  PFC_CUSTOM_STREAMING(0);
  switch(unsigned(PE::pe_type))
  {
    case penum_input:
    {
      // release old cube texture and load new
      unsigned tex_face_size=texture_size_2d(m_edge_len, m_edge_len, m_format, m_num_mips);
      for(unsigned fi=0; fi<6; ++fi)
      {
        PFC_MEM_FREE(m_mip_data[fi]);
        m_mip_data[fi]=0;
        m_mip_data[fi]=PFC_MEM_ALLOC(tex_face_size);
        pe_.data(m_mip_data[fi], tex_face_size);
      }
    } break;

    case penum_output:
    {
      // save cube faces
      if(m_edge_len)
      {
        unsigned tex_face_size=texture_size_2d(m_edge_len, m_edge_len, m_format, m_num_mips);
        for(unsigned fi=0; fi<6; ++fi)
          pe_.data(m_mip_data[fi], tex_face_size);
      }
    } break;
  }
}
//----------------------------------------------------------------------------

cpu_texcube::cpu_texcube()
{
  mem_zero(m_mip_data, sizeof(m_mip_data));
}
//----

cpu_texcube::~cpu_texcube()
{
  for(unsigned fi=0; fi<6; ++fi)
    PFC_MEM_FREE(m_mip_data[fi]);
}
//----

void cpu_texcube::init(unsigned edge_len_, int num_mips_, e_texture_format format_, e_texture_color_space color_space_, const mip_data *data_)
{
  // release old and allocate new texture
  texcube_base::init(edge_len_, num_mips_, format_, color_space_, 0);
  unsigned tex_face_size=texture_size_2d(m_edge_len, m_edge_len, m_format, m_num_mips);
  for(unsigned fi=0; fi<6; ++fi)
  {
    PFC_MEM_FREE(m_mip_data[fi]);
    m_mip_data[fi]=0;
    m_mip_data[fi]=PFC_MEM_ALLOC(tex_face_size);
    uint8_t *data_ptr=(uint8_t*)(m_mip_data[fi]);
    for(unsigned mi=0; mi<m_num_mips; ++mi)
      if(const mip_data *data=data_&&mi<m_num_mips?data_+mi:0)
      {
        unsigned mip_size=texture_mip_size_2d(m_edge_len, m_edge_len, m_format, mi);
        mem_copy(data_ptr, data->data[fi], mip_size);
        data_ptr+=mip_size;
      }
  }
}
//----

void cpu_texcube::load(texture_loader &tl_, const texture_loader_params &params_)
{
  // release old texture
  PFC_ASSERT_MSG(tl_.type()==textype_cube, ("Trying to load %s texture as a cube texture\r\n", enum_string(tl_.type())));
  for(unsigned fi=0; fi<6; ++fi)
  {
    PFC_MEM_FREE(m_mip_data[fi]);
    m_mip_data[fi]=0;
  }

  // load cube texture
  cpu_texture_manager_cube manager;
  load_texture(manager, tl_, params_);
  for(unsigned fi=0; fi<6; ++fi)
    m_mip_data[fi]=manager.mip_data[fi];
  texcube_base::init(manager.edge_len, manager.num_mips, params_.target_format?params_.target_format:tl_.format(), params_.color_space, 0);
  m_source_edge_len=tl_.width();
}
//----

void cpu_texcube::swap(texcube_base &tex_)
{
  // swap cube texture contents
  texcube_base::swap(tex_);
  cpu_texcube &tex=safe_cast<cpu_texcube&>(tex_);
  pfc::swap(m_mip_data, tex.m_mip_data, 6);
}
//----------------------------------------------------------------------------


//============================================================================
// texture property functions
//============================================================================
unsigned pfc::texsize(unsigned size_, e_texture_resize_mode resize_mode_)
{
  // switch to resize mode handling
  switch(resize_mode_)
  {
    case texresize_none: return size_;
    case texresize_prev_pow2: return prev_pow2(size_);
    case texresize_next_pow2: return next_pow2(size_);
    case texresize_nearest_pow2: {unsigned p=prev_pow2(size_), n=p*2; return size_-p<n-size_?p:n;}
  }

  // unknown mode
  PFC_ERRORF("Unknown resize mode \"%s\"\r\n", enum_string(resize_mode_));
  return 0;
}
//----

unsigned pfc::texfmt_bpp(e_texture_format f_)
{
  // return bits per pixel for the format
  switch(int(f_))
  {
  #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
    case texfmt_##name__: return bpp__;
    PFC_TEXFORMAT_LIST
  #undef PFC_TEXFORMAT
  }
  PFC_ERRORF("Unsupported texture format (%s)\r\n", texfmt_str(f_));
  return 0;
}
//----

e_texture_format_type pfc::texfmt_type(e_texture_format f_)
{
  // return texture format type
  switch(int(f_))
  {
  #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
    case texfmt_##name__: return type__;
    PFC_TEXFORMAT_LIST
  #undef PFC_TEXFORMAT
  }
  PFC_ERRORF("Unsupported texture format (%s)\r\n", texfmt_str(f_));
  return texfmttype_none;
}
//----

unsigned pfc::texfmt_num_channels(e_texture_format f_)
{
  // return number of format channels
  switch(int(f_))
  {
  #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
    case texfmt_##name__: return (rmask_size__?1:0)+(gmask_size__?1:0)+(bmask_size__?1:0)+(amask_size__?1:0);
    PFC_TEXFORMAT_LIST
  #undef PFC_TEXFORMAT
  }
  return 0;
}
//----

unsigned pfc::texfmt_num_rgb_channels(e_texture_format f_)
{
  // return is format has alpha channel
  switch(int(f_))
  {
  #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
    case texfmt_##name__: return (rmask_size__?1:0)+(gmask_size__?1:0)+(bmask_size__?1:0);
    PFC_TEXFORMAT_LIST
  #undef PFC_TEXFORMAT
  }
  PFC_ERRORF("Unsupported texture format (%s)\r\n", texfmt_str(f_));
  return texfmttype_none;
}
//----

unsigned pfc::texfmt_num_alpha_channels(e_texture_format f_)
{
  // return is format has alpha channel
  switch(int(f_))
  {
  #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
    case texfmt_##name__: return amask_size__?1:0;
    PFC_TEXFORMAT_LIST
  #undef PFC_TEXFORMAT
  }
  PFC_ERRORF("Unsupported texture format (%s)\r\n", texfmt_str(f_));
  return texfmttype_none;
}
//----

unsigned pfc::texfmt_blocksize(e_texture_format f_)
{
  // return pixel block size of the format
  switch(int(f_))
  {
  #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
    case texfmt_##name__: return block_size__;
    PFC_TEXFORMAT_LIST
  #undef PFC_TEXFORMAT
  }
  PFC_ERRORF("Unsupported texture format (%s)\r\n", texfmt_str(f_));
  return 0;
}
//----------------------------------------------------------------------------

void pfc::texfmt_rgba_mask32(e_texture_format fmt_, uint32_t &rmask_, uint32_t &gmask_, uint32_t &bmask_, uint32_t &amask_)
{
  // return 32-bit RGBA mask of the texture format
  PFC_ASSERT(texfmt_bpp(fmt_)<=32);
  switch(int(fmt_))
  {
  #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
    case texfmt_##name__:\
      rmask_=bpp__<=32?uint32_t(mask32(rmask_size__>0?rmask_size__:0)<<(bpp__<=32?rmask_pos__:0)):0;\
      gmask_=bpp__<=32?uint32_t(mask32(gmask_size__>0?gmask_size__:0)<<(bpp__<=32?gmask_pos__:0)):0;\
      bmask_=bpp__<=32?uint32_t(mask32(bmask_size__>0?bmask_size__:0)<<(bpp__<=32?bmask_pos__:0)):0;\
      amask_=bpp__<=32?uint32_t(mask32(amask_size__>0?amask_size__:0)<<(bpp__<=32?amask_pos__:0)):0; break;
    PFC_TEXFORMAT_LIST
  #undef PFC_TEXFORMAT
  }
}
//----

void pfc::texfmt_rgba_mask_size(e_texture_format fmt_, uint32_t &rmask_size_, uint32_t &gmask_size_, uint32_t &bmask_size_, uint32_t &amask_size_)
{
  // return RGBA mask sizes of the texture format
  switch(int(fmt_))
  {
  #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
    case texfmt_##name__:\
      rmask_size_=rmask_size__>0?rmask_size__:0;\
      gmask_size_=gmask_size__>0?gmask_size__:0;\
      bmask_size_=bmask_size__>0?bmask_size__:0;\
      amask_size_=amask_size__>0?amask_size__:0; break;
    PFC_TEXFORMAT_LIST
  #undef PFC_TEXFORMAT
  }
}
//----

void pfc::texfmt_rgba_mask_pos(e_texture_format fmt_, uint32_t &rmask_pos_, uint32_t &gmask_pos_, uint32_t &bmask_pos_, uint32_t &amask_pos_)
{
  // return RGBA mask positions of the texture format
  switch(int(fmt_))
  {
  #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
    case texfmt_##name__:\
      rmask_pos_=rmask_pos__;\
      gmask_pos_=gmask_pos__;\
      bmask_pos_=bmask_pos__;\
      amask_pos_=amask_pos__; break;
    PFC_TEXFORMAT_LIST
  #undef PFC_TEXFORMAT
  }
}
//----------------------------------------------------------------------------

const char *pfc::texfmt_str(e_texture_format f_)
{
  // return string identifier for the texture format
  switch(int(f_))
  {
  #define PFC_TEXFORMAT(name__, bpp__, block_size__, type__, conv_format__, rmask_pos__, rmask_size__, gmask_pos__, gmask_size__, bmask_pos__, bmask_size__, amask_pos__, amask_size__, rgba_order__)\
    case texfmt_##name__: return #name__;
    PFC_TEXFORMAT_LIST
  #undef PFC_TEXFORMAT
  }
  return "<unknown>";
}
//----------------------------------------------------------------------------

unsigned pfc::texture_size_2d(unsigned width_, unsigned height_, e_texture_format format_, int num_mips_)
{
  // calculate total size of the texture in bytes
  unsigned block_size=texfmt_blocksize(format_);
  unsigned pixels_pb=block_size*block_size;
  unsigned bytes_pb=(texfmt_bpp(format_)*pixels_pb)>>3;
  unsigned mip_idx=0;
  unsigned mip_idx_end=unsigned(num_mips_?num_mips_:1);
  unsigned size=0;
  do
  {
    // calculate mip level width and height
    unsigned width=max(block_size, (block_size*((width_+block_size-1)/block_size))>>mip_idx);
    unsigned height=max(block_size, (block_size*((height_+block_size-1)/block_size))>>mip_idx);
    size+=width*height*bytes_pb/pixels_pb;
  } while(++mip_idx<mip_idx_end);
  return size;
}
//----

unsigned pfc::texture_size_3d(unsigned width_, unsigned height_, unsigned depth_, e_texture_format format_, int num_mips_)
{
  // calculate total size of the texture in bytes
  unsigned block_size=texfmt_blocksize(format_);
  unsigned pixels_pb=block_size*block_size;
  unsigned bytes_pb=(texfmt_bpp(format_)*pixels_pb)>>3;
  unsigned mip_idx=0;
  unsigned mip_idx_end=unsigned(num_mips_?num_mips_:1);
  unsigned size=0;
  do
  {
    // calculate mip level width and height
    unsigned width=max(block_size, (block_size*((width_+block_size-1)/block_size))>>mip_idx);
    unsigned height=max(block_size, (block_size*((height_+block_size-1)/block_size))>>mip_idx);
    unsigned depth=max(1u, depth_>>mip_idx);
    size+=width*height*depth*bytes_pb/pixels_pb;
  } while(++mip_idx<mip_idx_end);
  return size;
}
//----

unsigned pfc::texture_mip_size_2d(unsigned width_, unsigned height_, e_texture_format format_, unsigned mip_level_)
{
  // calculate size of the texture mip in bytes
  unsigned block_size=texfmt_blocksize(format_);
  unsigned pixels_pb=block_size*block_size;
  unsigned bytes_pb=(texfmt_bpp(format_)*(block_size*block_size))>>3;
  unsigned width=(block_size*((width_+block_size-1)/block_size))>>mip_level_;
  unsigned height=(block_size*((height_+block_size-1)/block_size))>>mip_level_;
  return bytes_pb*max(block_size, width)*max(block_size, height)/pixels_pb;
}
//----

unsigned pfc::texture_mip_size_3d(unsigned width_, unsigned height_, unsigned depth_, e_texture_format format_, unsigned mip_level_)
{
  // calculate size of the texture mip in bytes
  unsigned block_size=texfmt_blocksize(format_);
  unsigned pixels_pb=block_size*block_size;
  unsigned bytes_pb=(texfmt_bpp(format_)*(block_size*block_size))>>3;
  unsigned width=(block_size*((width_+block_size-1)/block_size))>>mip_level_;
  unsigned height=(block_size*((height_+block_size-1)/block_size))>>mip_level_;
  unsigned depth=depth_>>mip_level_;
  return bytes_pb*max(block_size, width)*max(block_size, height)*max(1u, depth)/pixels_pb;
}
//----

unsigned pfc::texture_px_size_2d(unsigned width_, unsigned height_, int num_mips_)
{
  // calculate total size of the texture in pixels
  unsigned mip_idx=0;
  unsigned mip_idx_end=unsigned(num_mips_?num_mips_:1);
  unsigned size=0;
  do
  {
    // calculate mip level width and height
    unsigned width=max(1u, width_>>mip_idx);
    unsigned height=max(1u, height_>>mip_idx);
    size+=width*height;
  } while(++mip_idx<mip_idx_end);
  return size;
}
//----

unsigned pfc::texture_px_size_3d(unsigned width_, unsigned height_, unsigned depth_, int num_mips_)
{
  // calculate total size of the texture in pixels
  unsigned mip_idx=0;
  unsigned mip_idx_end=unsigned(num_mips_?num_mips_:1);
  unsigned size=0;
  do
  {
    // calculate mip level width and height
    unsigned width=max(1u, width_>>mip_idx);
    unsigned height=max(1u, height_>>mip_idx);
    unsigned depth=max(1u, depth_>>mip_idx);
    size+=width*height*depth;
  } while(++mip_idx<mip_idx_end);
  return size;
}
//----

unsigned pfc::texture_mips_2d(unsigned width_, unsigned height_, e_texture_format format_, int num_mips_)
{
  // calculate maximum number of mip levels
  unsigned size=max(width_, height_);
  if(format_ && texfmt_type(format_)==texfmttype_bc)
    size>>=2;
  unsigned max_mips=bitpos(prev_pow2(size))+1;
  return clamp(unsigned(num_mips_), 1u, max_mips);
}
//----

unsigned pfc::texture_mips_3d(unsigned width_, unsigned height_, unsigned depth_, e_texture_format format_, int num_mips_)
{
  // calculate maximum number of mip levels
  unsigned size=max(width_, height_);
  if(format_ && texfmt_type(format_)==texfmttype_bc)
    size>>=2;
  size=max(size, depth_);
  unsigned max_mips=bitpos(prev_pow2(size))+1;
  return clamp(unsigned(num_mips_), 1u, max_mips);
}
//----

unsigned pfc::texture_pitch(unsigned width_, e_texture_format format_, unsigned mip_level_)
{
  // calculate pitch for given mip level
  unsigned block_size=texfmt_blocksize(format_);
  unsigned bytes_pb=(texfmt_bpp(format_)*(block_size*block_size))>>3;
  unsigned width=max(block_size, (block_size*((width_+block_size-1)/block_size))>>mip_level_);
  return bytes_pb*width/block_size;
}
//----------------------------------------------------------------------------


//============================================================================
// RGBA conversion (interleaved -> interleaved)
//============================================================================
template<e_texture_format dst_format>
void convert_rgba_to(void *dst_, const void *src_, e_texture_format src_format_, usize_t num_pixels_)
{
  // switch to proper source format conversion
  switch(src_format_)
  {
    #define PFC_TEXFORMAT(fmt__) case texfmt_##fmt__: convert_rgba<texformat_cfg<dst_format>, texformat_cfg<texfmt_##fmt__> >(dst_, src_, num_pixels_); break;
    PFC_TEXFORMAT_CONVERSION_LIST
    #undef PFC_TEXFORMAT
    default: PFC_ERRORF("Color conversion from the source format not supported (%s -> %s)\r\n", texfmt_str(src_format_), texfmt_str(dst_format));
  }
}
//----

void pfc::convert_rgba_to_rgba(void *dst_, const void *src_, e_texture_format dst_format_, e_texture_format src_format_, usize_t num_pixels_)
{
  // switch to proper destination format conversion
  PFC_ASSERT_MSG(dst_format_!=src_format_, ("Destination and source formats do not differ\r\n"));
  switch(dst_format_)
  {
    #define PFC_TEXFORMAT(fmt__) case texfmt_##fmt__: convert_rgba_to<texfmt_##fmt__>(dst_, src_, src_format_, num_pixels_); break;
    PFC_TEXFORMAT_CONVERSION_LIST
    #undef PFC_TEXFORMAT
    default: PFC_ERRORF("Unsupported target texture format for RGBA color conversion (%s -> %s)\r\n", texfmt_str(src_format_), texfmt_str(dst_format_));
  }
}
//----------------------------------------------------------------------------


//============================================================================
// RGBA conversion (non-interleaved -> interleaved)
//============================================================================
template<e_texture_format dst_format, e_texture_format src_format>
void interleave_rgba_unaligned(void *dst_, const void *src_red_, const void *src_green_, const void *src_blue_, const void *src_alpha_, usize_t num_pixels_)
{
  // pixel interleaving config
  enum {dst_bytespp=texformat_cfg<dst_format>::bpp/8,
        dst_format_type=texformat_cfg<dst_format>::type,
        src_rmask_size=texformat_cfg<src_format>::rmask_size,
        src_gmask_size=texformat_cfg<src_format>::gmask_size,
        src_bmask_size=texformat_cfg<src_format>::bmask_size,
        src_amask_size=texformat_cfg<src_format>::amask_size,
        src_max_mask=meta_max<src_rmask_size, src_gmask_size, src_bmask_size, src_amask_size>::res,
        dst_rmask_size=texformat_cfg<dst_format>::rmask_size,
        dst_gmask_size=texformat_cfg<dst_format>::gmask_size,
        dst_bmask_size=texformat_cfg<dst_format>::bmask_size,
        dst_amask_size=texformat_cfg<dst_format>::amask_size,
        dst_rmask_pos=texformat_cfg<dst_format>::rmask_pos,
        dst_gmask_pos=texformat_cfg<dst_format>::gmask_pos,
        dst_bmask_pos=texformat_cfg<dst_format>::bmask_pos,
        dst_amask_pos=texformat_cfg<dst_format>::amask_pos,
        min_rmask_size=meta_min<src_rmask_size, dst_rmask_size>::res,
        min_gmask_size=meta_min<src_gmask_size, dst_gmask_size>::res,
        min_bmask_size=meta_min<src_bmask_size, dst_bmask_size>::res,
        min_amask_size=meta_min<src_amask_size, dst_amask_size>::res,
        dst_rshift=dst_rmask_size?dst_rmask_size+dst_rmask_pos-src_rmask_size:0,
        dst_gshift=dst_gmask_size?dst_gmask_size+dst_gmask_pos-src_gmask_size:0,
        dst_bshift=dst_bmask_size?dst_bmask_size+dst_bmask_pos-src_bmask_size:0,
        dst_ashift=dst_amask_size?dst_amask_size+dst_amask_pos-src_amask_size:0};

  // interleave unaligned color channel streams (bits packed)
  if(num_pixels_)
  {
    // interleave pixels
    uint32_t dummy_buffer=0;
    const uint8_t *src_r=(uint8_t*)(min_rmask_size?src_red_:&dummy_buffer);
    const uint8_t *src_g=(uint8_t*)(min_gmask_size?src_green_:&dummy_buffer);
    const uint8_t *src_b=(uint8_t*)(min_bmask_size?src_blue_:&dummy_buffer);
    const uint8_t *src_a=(uint8_t*)(min_amask_size?src_alpha_:&dummy_buffer);
    unsigned rbitpos=0;
    unsigned gbitpos=0;
    unsigned bbitpos=0;
    unsigned abitpos=0;
    uint8_t *dst=(uint8_t*)dst_;
    uint8_t *end=dst+dst_bytespp*num_pixels_;
    typedef meta_type_array<uint8_t, uint16_t, uint32_t, uint64_t, uint128_t> format_array_t;
    typedef typename format_array_t::get<meta_log2<meta_next_pow2<meta_max<dst_bytespp, (src_max_mask+7)/8>::res>::res>::res>::res convert_t;
    static const convert_t s_zero=numeric_type<convert_t>::zero();
    do
    {
      // interleave a pixel
      unsigned rbytepos=rbitpos>>3, rbytebitpos=rbitpos&7;
      unsigned gbytepos=gbitpos>>3, gbytebitpos=gbitpos&7;
      unsigned bbytepos=bbitpos>>3, bbytebitpos=bbitpos&7;
      unsigned abytepos=abitpos>>3, abytebitpos=abitpos&7;
      convert_t in_r, in_g, in_b, in_a;
      pixel_reader<min_rmask_size?(src_rmask_size+7)/8:0, 1, texfmttype_rgba, (e_texture_format_type)dst_format_type>::read_unaligned(&in_r, src_r+rbytepos, rbytebitpos);
      pixel_reader<min_gmask_size?(src_gmask_size+7)/8:0, 1, texfmttype_rgba, (e_texture_format_type)dst_format_type>::read_unaligned(&in_g, src_g+gbytepos, gbytebitpos);
      pixel_reader<min_bmask_size?(src_bmask_size+7)/8:0, 1, texfmttype_rgba, (e_texture_format_type)dst_format_type>::read_unaligned(&in_b, src_b+bbytepos, bbytebitpos);
      pixel_reader<min_amask_size?(src_amask_size+7)/8:0, 1, texfmttype_rgba, (e_texture_format_type)dst_format_type>::read_unaligned(&in_a, src_a+abytepos, abytebitpos);
      convert_t output= (min_rmask_size?(meta_mask<min_rmask_size, dst_rmask_pos+dst_rmask_size-min_rmask_size, convert_t>::res&bit_shift<dst_rshift>(in_r)):s_zero)
                       |(min_gmask_size?(meta_mask<min_gmask_size, dst_gmask_pos+dst_gmask_size-min_gmask_size, convert_t>::res&bit_shift<dst_gshift>(in_g)):s_zero)
                       |(min_bmask_size?(meta_mask<min_bmask_size, dst_bmask_pos+dst_bmask_size-min_bmask_size, convert_t>::res&bit_shift<dst_bshift>(in_b)):s_zero)
                       |(min_amask_size?(meta_mask<min_amask_size, dst_amask_pos+dst_amask_size-min_amask_size, convert_t>::res&bit_shift<dst_ashift>(in_a)):s_zero);
      pixel_writer<dst_bytespp, texfmttype_rgba, (e_texture_format_type)dst_format_type>::write(dst, &output);
      rbitpos+=min_rmask_size?src_rmask_size:0;
      gbitpos+=min_gmask_size?src_gmask_size:0;
      bbitpos+=min_bmask_size?src_bmask_size:0;
      abitpos+=min_amask_size?src_amask_size:0;
      dst+=dst_bytespp;
    } while(dst!=end);
  }
}
//----

template<e_texture_format dst_format, e_texture_format src_format, typename T>
void interleave_rgba_aligned(void *dst_, const void *src_red_, const void *src_green_, const void *src_blue_, const void *src_alpha_, usize_t num_pixels_)
{
  // pixel interleaving config
  enum {dst_bytespp=texformat_cfg<dst_format>::bpp/8,
        src_format_type=texformat_cfg<src_format>::type,
        dst_format_type=texformat_cfg<dst_format>::type,
        src_rmask_size=texformat_cfg<src_format>::rmask_size,
        src_gmask_size=texformat_cfg<src_format>::gmask_size,
        src_bmask_size=texformat_cfg<src_format>::bmask_size,
        src_amask_size=texformat_cfg<src_format>::amask_size,
        dst_rmask_size=texformat_cfg<dst_format>::rmask_size,
        dst_gmask_size=texformat_cfg<dst_format>::gmask_size,
        dst_bmask_size=texformat_cfg<dst_format>::bmask_size,
        dst_amask_size=texformat_cfg<dst_format>::amask_size,
        dst_rmask_pos=texformat_cfg<dst_format>::rmask_pos,
        dst_gmask_pos=texformat_cfg<dst_format>::gmask_pos,
        dst_bmask_pos=texformat_cfg<dst_format>::bmask_pos,
        dst_amask_pos=texformat_cfg<dst_format>::amask_pos,
        min_rmask_size=meta_min<src_rmask_size, dst_rmask_size>::res,
        min_gmask_size=meta_min<src_gmask_size, dst_gmask_size>::res,
        min_bmask_size=meta_min<src_bmask_size, dst_bmask_size>::res,
        min_amask_size=meta_min<src_amask_size, dst_amask_size>::res,
        dst_rshift=dst_rmask_size?dst_rmask_size+dst_rmask_pos-src_rmask_size:0,
        dst_gshift=dst_gmask_size?dst_gmask_size+dst_gmask_pos-src_gmask_size:0,
        dst_bshift=dst_bmask_size?dst_bmask_size+dst_bmask_pos-src_bmask_size:0,
        dst_ashift=dst_amask_size?dst_amask_size+dst_amask_pos-src_amask_size:0};

  // interleave color channels aligned to given type T
  if(num_pixels_)
  {
    // interleave pixels
    uint32_t dummy_buffer=0;
    const T *src_r=(T*)(src_rmask_size?src_red_:&dummy_buffer);
    const T *src_g=(T*)(src_gmask_size?src_green_:&dummy_buffer);
    const T *src_b=(T*)(src_bmask_size?src_blue_:&dummy_buffer);
    const T *src_a=(T*)(src_amask_size?src_alpha_:&dummy_buffer);
    uint8_t *dst=(uint8_t*)dst_;
    uint8_t *end=dst+dst_bytespp*num_pixels_;
    typedef meta_type_array<uint8_t, uint16_t, uint32_t, uint64_t, uint128_t> format_array_t;
    typedef typename format_array_t::get<meta_log2<meta_next_pow2<meta_max<sizeof(T), dst_bytespp>::res>::res>::res>::res convert_t;
    static const convert_t s_zero=numeric_type<convert_t>::zero();
    do
    {
      // interleave a pixel
      convert_t in_r, in_g, in_b, in_a;
      pixel_reader<min_rmask_size?sizeof(T):0, 1, (e_texture_format_type)src_format_type, (e_texture_format_type)dst_format_type>::read(&in_r, src_r);
      pixel_reader<min_gmask_size?sizeof(T):0, 1, (e_texture_format_type)src_format_type, (e_texture_format_type)dst_format_type>::read(&in_g, src_g);
      pixel_reader<min_bmask_size?sizeof(T):0, 1, (e_texture_format_type)src_format_type, (e_texture_format_type)dst_format_type>::read(&in_b, src_b);
      pixel_reader<min_amask_size?sizeof(T):0, 1, (e_texture_format_type)src_format_type, (e_texture_format_type)dst_format_type>::read(&in_a, src_a);
      convert_t output= (min_rmask_size?(meta_mask<min_rmask_size, dst_rmask_pos+dst_rmask_size-min_rmask_size, convert_t>::res&bit_shift<dst_rshift>(in_r)):s_zero)
                       |(min_gmask_size?(meta_mask<min_gmask_size, dst_gmask_pos+dst_gmask_size-min_gmask_size, convert_t>::res&bit_shift<dst_gshift>(in_g)):s_zero)
                       |(min_bmask_size?(meta_mask<min_bmask_size, dst_bmask_pos+dst_bmask_size-min_bmask_size, convert_t>::res&bit_shift<dst_bshift>(in_b)):s_zero)
                       |(min_amask_size?(meta_mask<min_amask_size, dst_amask_pos+dst_amask_size-min_amask_size, convert_t>::res&bit_shift<dst_ashift>(in_a)):s_zero);
      pixel_writer<dst_bytespp, (e_texture_format_type)src_format_type, (e_texture_format_type)dst_format_type>::write(dst, &output);
      src_r+=min_rmask_size?1:0;
      src_g+=min_gmask_size?1:0;
      src_b+=min_bmask_size?1:0;
      src_a+=min_amask_size?1:0;
      dst+=dst_bytespp;
    } while(dst!=end);
  }
}
//----

template<e_texture_format dst_format>
void interleave_rgba_to(void *dst_, const void *src_red_, const void *src_green_, const void *src_blue_, const void *src_alpha_, e_texture_format src_format_, usize_t num_pixels_, unsigned src_byte_packing_)
{
  // switch to proper source format interleaving
  switch(src_format_)
  {
    #define PFC_TEXFORMAT(fmt__)\
      case texfmt_##fmt__:\
      {\
        enum {component_size_mask= texformat_cfg<texfmt_##fmt__>::rmask_size\
                                  |texformat_cfg<texfmt_##fmt__>::gmask_size\
                                  |texformat_cfg<texfmt_##fmt__>::bmask_size\
                                  |texformat_cfg<texfmt_##fmt__>::amask_size,\
              is_optimized=meta_is_pow2<component_size_mask>::res && !(component_size_mask&7)};\
        switch(src_byte_packing_?src_byte_packing_:is_optimized?component_size_mask/8:0)\
        {\
          case 0: interleave_rgba_unaligned<dst_format, texfmt_##fmt__>(dst_, src_red_, src_green_, src_blue_, src_alpha_, num_pixels_); break;\
          case 1: interleave_rgba_aligned<dst_format, texfmt_##fmt__, uint8_t>(dst_, src_red_, src_green_, src_blue_, src_alpha_, num_pixels_); break;\
          case 2: interleave_rgba_aligned<dst_format, texfmt_##fmt__, uint16_t>(dst_, src_red_, src_green_, src_blue_, src_alpha_, num_pixels_); break;\
          case 4: interleave_rgba_aligned<dst_format, texfmt_##fmt__, uint32_t>(dst_, src_red_, src_green_, src_blue_, src_alpha_, num_pixels_); break;\
          default: PFC_ERRORF("Invalid source byte packing (%i) for color interleaving\r\n", src_byte_packing_);\
        } break;\
      } break;
    PFC_TEXFORMAT_CONVERSION_LIST
    #undef PFC_TEXFORMAT
    default: PFC_ERRORF("Color interleaving from the source format not supported (%s -> %s)\r\n", texfmt_str(src_format_), texfmt_str(dst_format));
  }
}
//----

void pfc::interleave_rgba_to_rgba(void *dst_, const void *src_red_, const void *src_green_, const void *src_blue_, const void *src_alpha_, e_texture_format dst_format_, e_texture_format src_format_, usize_t num_pixels_, unsigned src_byte_packing_)
{
  // switch to proper destination format interleaving
  switch(dst_format_)
  {
    #define PFC_TEXFORMAT(fmt__) case texfmt_##fmt__: interleave_rgba_to<texfmt_##fmt__>(dst_, src_red_, src_green_, src_blue_, src_alpha_, src_format_, num_pixels_, src_byte_packing_); break;
    PFC_TEXFORMAT_CONVERSION_LIST
    #undef PFC_TEXFORMAT
    default: PFC_ERRORF("Unsupported target texture format for RGBA color interleaving (%s -> %s)\r\n", texfmt_str(src_format_), texfmt_str(dst_format_));
  }
}
//----------------------------------------------------------------------------


//============================================================================
// texture creation functions
//============================================================================
owner_ref<tex2d_base> pfc::create_texture_2d(unsigned width_, unsigned height_, unsigned num_mips_, e_texture_format format_, e_texture_color_space color_space_, const tex2d_base::mip_data *data_, unsigned array_size_)
{
  // create and init 2d texture object
  tex2d_base *t=create_object<tex2d_base>();
  PFC_CHECK_MSG(t, ("Unable to create tex2d_base class instance\r\n"))
  t->init(width_, height_, num_mips_, format_, color_space_, data_, array_size_);
  return t;
}
//----

owner_ref<tex3d_base> pfc::create_texture_3d(unsigned width_, unsigned height_, unsigned depth_, unsigned num_mips_, e_texture_format format_, e_texture_color_space color_space_, const tex3d_base::mip_data *data_)
{
  // create and init 3d texture object
  tex3d_base *t=create_object<tex3d_base>();
  PFC_CHECK_MSG(t, ("Unable to create tex3d_base class instance\r\n"))
  t->init(width_, height_, depth_, num_mips_, format_, color_space_, data_);
  return t;
}
//----

owner_ref<texcube_base> pfc::create_texture_cube(unsigned edge_len_, unsigned num_mips_, e_texture_format format_, e_texture_color_space color_space_, const texcube_base::mip_data *data_)
{
  // create and init cube texture object
  texcube_base *t=create_object<texcube_base>();
  PFC_CHECK_MSG(t, ("Unable to create texcube_base class instance\r\n"))
  t->init(edge_len_, num_mips_, format_, color_space_, data_);
  return t;
}
//----------------------------------------------------------------------------


//============================================================================
// texture loading functions
//============================================================================
e_file_format pfc::texture_file_format(const char *filename_ext_)
{
  // check the texture file format from the file extension
  if(str_ieq(filename_ext_, "jpg") || str_ieq(filename_ext_, "jpeg"))
    return filefmt_jpg;
  if(str_ieq(filename_ext_, "png"))
    return filefmt_png;
  if(str_ieq(filename_ext_, "webp"))
    return filefmt_webp;
  if(str_ieq(filename_ext_, "dds"))
    return filefmt_dds;
  if(str_ieq(filename_ext_, "psd"))
    return filefmt_psd;
  if(str_ieq(filename_ext_, "tga"))
    return filefmt_tga;
  if(str_ieq(filename_ext_, "tif") || str_ieq(filename_ext_, "tiff"))
    return filefmt_tiff;
  if(str_ieq(filename_ext_, "jp2"))
    return filefmt_jp2;
  return filefmt_none;
}
//----

bool pfc::read_texture_2d(tex2d_base &tex_, bin_input_stream_base &stream_, const texture_loader_params &params_, const char *id_)
{
  // init texture loader and check for correct texture type
  texture_loader tl(stream_);
  if(tl.type()!=textype_2d)
  {
    PFC_WARNF("The loaded file \"%s\" is not a 2d texture\r\n", id_?id_:"<unknown>");
    return false;
  }

  // check for power-of-2 2D BC-format texture
  if(params_.resize_mode==texresize_none && params_.target_format && texfmt_type(params_.target_format)==texfmttype_bc && (!is_pow2(tl.width()) || !is_pow2(tl.height())))
  {
    PFC_WARNF("Unable to load 2D texture \"%s\" as BC-format which doesn't have power-of-2 dimensions (%i x %i)\r\n", id_?id_:"<unknown>", tl.width(), tl.height());
    return false;
  }

  // load the texture
  tl.enable_gamma(params_.content_type==texcontent_color);
  tex_.load(tl, params_);
  return true;
}
//----

bool pfc::read_texture_3d(tex3d_base &tex_, bin_input_stream_base &stream_, const texture_loader_params &params_, const char *id_)
{
  // init texture loader and check for correct texture type
  texture_loader tl(stream_);
  if(tl.type()!=textype_3d)
  {
    PFC_WARNF("The loaded file \"%s\" is not a 3d texture\r\n", id_?id_:"<unknown>");
    return false;
  }

  // check for power-of-2 3d BC-format texture
  if(params_.resize_mode==texresize_none && params_.target_format && texfmt_type(params_.target_format)==texfmttype_bc && (!is_pow2(tl.width()) || !is_pow2(tl.height()) || !is_pow2(tl.depth())))
  {
    PFC_WARNF("Unable to load 3D texture \"%s\" as BC-format which doesn't have power-of-2 dimensions (%i x %i x %i)\r\n", id_?id_:"<unknown>", tl.width(), tl.height(), tl.depth());
    return false;
  }

  // load the texture
  tl.enable_gamma(params_.content_type==texcontent_color);
  tex_.load(tl, params_);
  return true;
}
//----

bool pfc::read_texture_cube(texcube_base &tex_, bin_input_stream_base &stream_, const texture_loader_params &params_, const char *id_)
{
  // init texture loader and check for correct texture type
  texture_loader tl(stream_);
  if(tl.type()!=textype_cube)
  {
    PFC_WARNF("The loaded file \"%s\" is not a cube texture\r\n", id_?id_:"<unknown>");
    return false;
  }

  // check for power-of-2 cube BC-format texture
  if(params_.resize_mode==texresize_none && params_.target_format && texfmt_type(params_.target_format)==texfmttype_bc && !is_pow2(tl.width()))
  {
    PFC_WARNF("Unable to load cube texture \"%s\" as BC-format which doesn't have power-of-2 dimensions (edge length %i)\r\n", id_?id_:"<unknown>", tl.width());
    return false;
  }

  // load the texture
  tl.enable_gamma(params_.content_type==texcontent_color);
  tex_.load(tl, params_);
  return true;
}
//----

e_texture_type pfc::load_texture(bin_input_stream_base &stream_, const str_id &id_, const texture_loader_params &params_)
{
  // init texture loader and instantiate and load proper texture type
  texture_loader tl(stream_);
  tl.enable_gamma(params_.content_type==texcontent_color);
  e_texture_type type=textype_none;
  switch(tl.type())
  {
    // 2d texture
    case textype_2d:
    {
      // check for power-of-2 2D BC-format texture
      if(params_.resize_mode==texresize_none && texfmt_type(params_.target_format)==texfmttype_bc && (!is_pow2(tl.width()) || !is_pow2(tl.height())))
      {
        PFC_WARNF("Unable to load 2D texture \"%s\" as BC-format which doesn't have power-of-2 dimensions (%i x %i)\r\n", id_.c_str(), tl.width(), tl.height());
        return textype_none;
      }

      tex2d_base *trep=find_object<tex2d_base>(id_);
      tex2d_base *t=trep?trep:create_object<tex2d_base>();
      if(!t)
      {
        PFC_WARN_ONCE("Unable to create tex2d_base class instance\r\n");
        break;
      }
      t->load(tl, params_);
      if(!trep)
        add_object(id_, *t);
      type=textype_2d;
    } break;

    // 3d texture
    case textype_3d:
    {
      // check for power-of-2 3d BC-format texture
      if(params_.resize_mode==texresize_none && texfmt_type(params_.target_format)==texfmttype_bc && (!is_pow2(tl.width()) || !is_pow2(tl.height()) || !is_pow2(tl.depth())))
      {
        PFC_WARNF("Unable to load 3D texture \"%s\" as BC-format which doesn't have power-of-2 dimensions (%i x %i x %i)\r\n", id_.c_str(), tl.width(), tl.height(), tl.depth());
        return textype_none;
      }

      tex3d_base *trep=find_object<tex3d_base>(id_);
      tex3d_base *t=trep?trep:create_object<tex3d_base>();
      if(!t)
      {
        PFC_WARN_ONCE("Unable to create tex3d_base class instance\r\n");
        break;
      }
      t->load(tl, params_);
      if(!trep)
        add_object(id_, *t);
      type=textype_3d;
    } break;

    // cube texture
    case textype_cube:
    {
      // check for power-of-2 cube BC-format texture
      if(params_.resize_mode==texresize_none && texfmt_type(params_.target_format)==texfmttype_bc && !is_pow2(tl.width()))
      {
        PFC_WARNF("Unable to load cube texture \"%s\" as BC-format which doesn't have power-of-2 dimensions (edge length %i)\r\n", id_.c_str(), tl.width());
        return textype_none;
      }

      texcube_base *trep=find_object<texcube_base>(id_);
      texcube_base *t=trep?trep:create_object<texcube_base>();
      if(!t)
      {
        PFC_WARN_ONCE("Unable to create texcube_base class instance\r\n");
        break;
      }
      t->load(tl, params_);
      if(!trep)
        add_object(id_, *t);
      type=textype_cube;
    } break;

    default: PFC_WARNF("Unknown texture type in file \"%s\"\r\n", id_.c_str());
  }

  return type;
}
//----

e_texture_type pfc::load_texture(const str_id &id_, const texture_loader_params &params_, const char *path_)
{
  // try to open file for reading
  owner_ptr<bin_input_stream_base> file=afs_open_read(id_.c_str(), path_);
  if(!file.data)
  {
    PFC_WARNF("Unable to open texture file \"%s\"\r\n", afs_complete_path(id_.c_str(), path_).c_str());
    return textype_none;
  }
  return load_texture(*file, id_, params_);
}
//----

void pfc::load_texture(texture_manager_base &manager_, texture_loader &tl_, const texture_loader_params &params_)
{
  // determine texture format
  unsigned layer_width=tl_.width();
  unsigned layer_height=tl_.height();
  e_texture_format target_format=params_.target_format?params_.target_format:tl_.format();
  switch(int(texfmt_type(tl_.format())))
  {
    // RGBA source texture
    case texfmttype_rgba:
    case texfmttype_rgba16f:
    case texfmttype_rgba32f:
    {
      // determine number of mip levels and create texture resources
      unsigned num_mips=tl_.num_mips();
      bool load_mips=num_mips>1;
      unsigned mip0_width=texsize(layer_width, params_.resize_mode)>>params_.first_mip_level;
      unsigned mip0_height=texsize(layer_height, params_.resize_mode)>>params_.first_mip_level;
      unsigned mip0_depth=tl_.depth();
      if(!load_mips && params_.mip_filter)
        num_mips=bitpos(prev_pow2(min(mip0_width, mip0_height)>>1));
      num_mips=clamp(num_mips, 1u, max(1u, texture_mips_3d(mip0_width, mip0_height, mip0_depth, target_format, unsigned(params_.num_mips))));
      manager_.create_texture(tl_, params_, num_mips);

      // initialize texture loading & conversion/mip generation
      bool generate_mips=!load_mips&&num_mips>1;
      bool convert_to_bc=texfmt_type(target_format)==texfmttype_bc;
      bool run_converter=generate_mips||convert_to_bc||(mip0_width!=layer_width)||(mip0_height!=layer_height);
      e_texture_format tf=run_converter?get_converter_input_format(target_format):target_format;
      tl_.set_target_format(tf);
      unsigned bpp=texfmt_bpp(tf);
      owner_data image_layer=run_converter?PFC_MEM_ALLOC(layer_width*layer_height*bpp/8):0;
      texture_converter tc;
      if(run_converter)
      {
        tc.set_input_format(tf);
        tc.set_target_format(target_format, params_.content_type);
      }

      // load the texture and convert format and/or generate mip levels
      if(load_mips || !generate_mips)
      {
        // process all mip levels available in the loader
        texture_layer layer;
        while(tl_.layer(layer))
        {
          // check if mip level must be skipped
          unsigned mi=layer.mip_level;
          if(mi<params_.first_mip_level || mi>=params_.first_mip_level+num_mips)
          {
            tl_.skip_layer();
            continue;
          }
          layer.mip_level-=params_.first_mip_level;

          // calculate mip dimensions and lock the mip level
          unsigned src_width=layer_width>>mi;
          unsigned src_height=layer_height>>mi;
          unsigned src_pitch=src_width*bpp/8;
          int dst_pitch=0;
          void *dst_data=manager_.lock(layer, dst_pitch);

          // either convert the mip level or load directly to the buffer/surface
          if(run_converter)
          {
            // load image to the target buffer
            tl_.load_layer(image_layer.data, src_pitch);
            tc.set_mip_filter(mipfilter_none);
            tc.set_target(dst_data, dst_pitch);
            tc.convert(image_layer.data, src_width, src_height, params_.resize_mode);
          }
          else
            tl_.load_layer(dst_data, dst_pitch);

          // unlock the mip level
          manager_.unlock(layer);
        }
      }
      else
      {
        texture_layer layer;
        while(tl_.layer(layer))
        {
          // skip non-zero mip levels
          if(layer.mip_level!=0)
          {
            tl_.skip_layer();
            continue;
          }

          // load the top most mip level and lock all mip levels for mipmap generation
          enum {max_mip_levels=16};
          PFC_ASSERT(num_mips<=max_mip_levels);
          void *surf_bits[max_mip_levels];
          int surf_pitch[max_mip_levels];
          unsigned src_pitch=layer_width*bpp/8;
          tl_.load_layer(image_layer.data, src_pitch);
          for(unsigned mi=0; mi<num_mips; ++mi)
          {
            // select target for the image conversion
            layer.mip_level=mi;
            surf_bits[mi]=manager_.lock(layer, surf_pitch[mi]);
            void *dst_data=surf_bits[mi];
            unsigned dst_pitch=surf_pitch[mi];
            tc.set_target(dst_data, dst_pitch, mi+params_.first_mip_level);
          }

          // convert the texture and/or generate mips
          tc.set_mip_filter(params_.mip_filter);
          tc.convert(image_layer.data, layer_width, layer_height, params_.resize_mode);

          // unlock all mip levels
          for(unsigned mi=0; mi<num_mips; ++mi)
          {
            layer.mip_level=mi;
            manager_.unlock(layer);
          }
          layer.mip_level=0;
        }
      }
      manager_.finalize();
    } break;

    // BC source texture
    case texfmttype_bc:
    {
      // create texture resource
      unsigned num_mips=clamp(unsigned(params_.num_mips), 1u, texture_mips_3d(layer_width, layer_height, tl_.depth(), target_format, tl_.num_mips()));
      manager_.create_texture(tl_, params_, num_mips);

      // load texture mip levels
      tl_.set_target_format(target_format);
      texture_layer layer;
      while(tl_.layer(layer))
      {
        // check if mip level must be skipped
        unsigned mi=layer.mip_level;
        if(mi>=num_mips)
        {
          tl_.skip_layer();
          continue;
        }

        // select target for the image load/conversion and load the image
        int surf_pitch=0;
        void *surf_bits=manager_.lock(layer, surf_pitch);
        void *dst_data=surf_bits;
        unsigned dst_pitch=surf_pitch;
        tl_.load_layer(dst_data, dst_pitch);

        // unlock the texture
        manager_.unlock(layer);
      }
      manager_.finalize();
    } break;
  }
}
//----

tex2d_base *pfc::load_texture_2d(bin_input_stream_base &stream_, const str_id &id_, const texture_loader_params &params_)
{
  // try to create 2d texture object
  tex2d_base *t=create_object<tex2d_base>();
  if(!t)
  {
    PFC_WARN_ONCE("Unable to create tex2d_base class instance\r\n");
    return 0;
  }

  // load the texture
  if(!read_texture_2d(*t, stream_, params_, id_.c_str()))
  {
    PFC_DELETE(t);
    return 0;
  }
  add_object(id_, *t);
  return t;
}
//----

tex2d_base *pfc::load_texture_2d(const str_id &id_, const texture_loader_params &params_, const char *path_)
{
  // try to open file for reading
  owner_ptr<bin_input_stream_base> file=afs_open_read(id_.c_str(), path_);
  if(!file.data)
  {
    PFC_WARNF("Unable to open file \"%s\" for reading\r\n", afs_complete_path(id_.c_str(), path_).c_str());
    return 0;
  }
  return load_texture_2d(*file, id_, params_);
}
//----

tex3d_base *pfc::load_texture_3d(bin_input_stream_base &stream_, const str_id &id_, const texture_loader_params &params_)
{
  // try to create 3d texture object
  tex3d_base *t=create_object<tex3d_base>();
  if(!t)
  {
    PFC_WARN_ONCE("Unable to create tex3d_base class instance\r\n");
    return 0;
  }

  // load the texture
  if(!read_texture_3d(*t, stream_, params_, id_.c_str()))
  {
    PFC_DELETE(t);
    return 0;
  }
  add_object(id_, *t);
  return t;
}
//----

tex3d_base *pfc::load_texture_3d(const str_id &id_, const texture_loader_params &params_, const char *path_)
{
  // try to open file for reading
  owner_ptr<bin_input_stream_base> file=afs_open_read(id_.c_str(), path_);
  if(!file.data)
  {
    PFC_WARNF("Unable to open file \"%s\" for reading\r\n", afs_complete_path(id_.c_str(), path_).c_str());
    return 0;
  }
  return load_texture_3d(*file, id_, params_);
}
//----

texcube_base *pfc::load_texture_cube(bin_input_stream_base &stream_, const str_id &id_, const texture_loader_params &params_)
{
  // try to create cube texture object
  texcube_base *t=create_object<texcube_base>();
  if(!t)
  {
    PFC_WARN_ONCE("Unable to create texcube_base class instance\r\n");
    return 0;
  }

  // load the texture
  if(!read_texture_cube(*t, stream_, params_, id_.c_str()))
  {
    PFC_DELETE(t);
    return 0;
  }
  add_object(id_, *t);
  return t;
}
//----

texcube_base *pfc::load_texture_cube(const str_id &id_, const texture_loader_params &params_, const char *path_)
{
  // try to open file for reading
  owner_ptr<bin_input_stream_base> file=afs_open_read(id_.c_str(), path_);
  if(!file.data)
  {
    PFC_WARNF("Unable to open file \"%s\" for reading\r\n", afs_complete_path(id_.c_str(), path_).c_str());
    return 0;
  }
  return load_texture_cube(*file, id_, params_);
}
//----------------------------------------------------------------------------


//============================================================================
// texture write function params
//============================================================================
texture_writer_params_dds::texture_writer_params_dds()
{
}
//----------------------------------------------------------------------------

texture_writer_params_jp2::texture_writer_params_jp2()
{
}
//----------------------------------------------------------------------------

texture_writer_params_jpg::texture_writer_params_jpg()
  :quality(0.5f)
{
}
//----

texture_writer_params_jpg::texture_writer_params_jpg(float quality_)
  :quality(quality_)
{
}
//----------------------------------------------------------------------------

texture_writer_params_png::texture_writer_params_png()
  :is_16bpp(false)
  ,save_alpha(false)
{
}
//----

texture_writer_params_png::texture_writer_params_png(bool is_16bpp_, bool save_alpha_)
  :is_16bpp(is_16bpp_)
  ,save_alpha(save_alpha_)
{
}
//----------------------------------------------------------------------------

texture_writer_params_psd::texture_writer_params_psd()
{
}
//----------------------------------------------------------------------------

texture_writer_params_tga::texture_writer_params_tga()
{
}
//----------------------------------------------------------------------------

texture_writer_params_tiff::texture_writer_params_tiff()
{
}
//----------------------------------------------------------------------------

texture_writer_params_webp::texture_writer_params_webp()
{
}
//----------------------------------------------------------------------------
