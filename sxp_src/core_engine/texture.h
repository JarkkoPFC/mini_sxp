//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_ENGINE_TEXTURE_H
#define PFC_CORE_ENGINE_TEXTURE_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core_engine/loaders/dataio.h"
#include "sxp_src/core/math/bit_math.h"
#include "sxp_src/core/math/numeric.h"
#include "sxp_src/core/class.h"
#include "sxp_src/core/variant.h"
namespace pfc
{

// new
struct texture_layer;
struct texture_loader_params;
class texture_loader;
class texture_converter;
class texture_manager_base;
class tex2d_base;
class tex3d_base;
class texcube_base;
class cpu_tex2d;
class cpu_tex3d;
class cpu_texcube;
void enable_cuda_texture_compression(bool enable_=true);
bool is_cuda_texture_compression();
//----------------------------------------------------------------------------


//============================================================================
// e_texture_type
//============================================================================
enum e_texture_type
{
  textype_none,
  //----
  textype_2d,
  textype_3d,
  textype_cube,
};
PFC_ENUM(e_texture_type);
//----------------------------------------------------------------------------


//============================================================================
// e_texture_content
//============================================================================
enum e_texture_content
{
  texcontent_none,
  //----
  texcontent_color,
  texcontent_normal,
};
PFC_ENUM(e_texture_content);
//----------------------------------------------------------------------------


//============================================================================
// e_texture_format_type
//============================================================================
enum e_texture_format_type
{
  texfmttype_none,
  //----
  texfmttype_rgba,    // unsigned integer RGBA format
  texfmttype_rgba16f, // 16-bit floating point RGBA format
  texfmttype_rgba32f, // 32-bit floating point RGBA format
  texfmttype_bc,      // block compressed format
};
PFC_ENUM(e_texture_format_type);
//----------------------------------------------------------------------------


//============================================================================
// e_texture_format
//============================================================================
enum e_texture_format
{
  texfmt_none,
  //----
  // RGBA formats
  texfmt_a8,
  texfmt_r8,
  texfmt_a16,
  texfmt_r16,
  texfmt_r16f,
  texfmt_a8r8,
  texfmt_g8r8,
  texfmt_r5g6b5,
  texfmt_a1r5g5b5,
  texfmt_a4r4g4b4,
  texfmt_r8g8b8,
  texfmt_b8g8r8,
  texfmt_a32,
  texfmt_r32,
  texfmt_r32f,
  texfmt_a16r16,
  texfmt_g16r16,
  texfmt_g16r16f,
  texfmt_a8r8g8b8,
  texfmt_a8b8g8r8,
  texfmt_b8g8r8a8,
  texfmt_a2b10g10r10,
  texfmt_b10g11r11f,
  texfmt_b16g16r16,
  texfmt_a32r32,
  texfmt_g32r32,
  texfmt_g32r32f,
  texfmt_b16g16r16a16,
  texfmt_a16b16g16r16,
  texfmt_a16b16g16r16f,
  texfmt_b32g32r32f,
  texfmt_a32b32g32r32,
  texfmt_a32b32g32r32f,
  // BC formats
  texfmt_bc1,
  texfmt_bc1a,
  texfmt_bc2,
  texfmt_bc3,
  texfmt_bc6h,
  texfmt_bc7,
  //----
  texfmt_enum_end
};
PFC_ENUM(e_texture_format);
//----------------------------------------------------------------------------


//============================================================================
// e_texture_color_space
//============================================================================
enum e_texture_color_space
{
  texcolspace_none,
  //----
  texcolspace_linear_rgb,
  texcolspace_srgb,
  //----
  texcolspace_enum_end
};
PFC_ENUM(e_texture_color_space);
//----------------------------------------------------------------------------


//============================================================================
// e_mip_filter
//============================================================================
enum e_mip_filter
{
  mipfilter_none,
  //----
  mipfilter_box,
  mipfilter_sinc,
};
PFC_ENUM(e_mip_filter);
//----------------------------------------------------------------------------


//============================================================================
// e_texture_filter
//============================================================================
enum e_texture_filter
{
  texfilter_point,
  texfilter_linear,
  texfilter_anisotropic,
};
PFC_ENUM(e_texture_filter);
//----------------------------------------------------------------------------


//============================================================================
// e_texture_compression_quality
//============================================================================
enum e_texture_compression_quality
{
  texcq_fastest,
  texcq_normal,
  texcq_production,
  texcq_highest,
};
PFC_ENUM(e_texture_compression_quality);
//----------------------------------------------------------------------------


//============================================================================
// e_texture_resize_mode
//============================================================================
enum e_texture_resize_mode
{
  texresize_none,
  texresize_prev_pow2,
  texresize_next_pow2,
  texresize_nearest_pow2,
};
PFC_ENUM(e_texture_resize_mode);
//----------------------------------------------------------------------------


//============================================================================
// e_cubemap_face
//============================================================================
enum e_cubemap_face
{
  cubeface_negx,
  cubeface_posx,
  cubeface_negy,
  cubeface_posy,
  cubeface_negz,
  cubeface_posz
};
//----------------------------------------------------------------------------


//============================================================================
// texture_layer
//============================================================================
struct texture_layer
{
  PFC_INLINE texture_layer();
  //--------------------------------------------------------------------------

  unsigned mip_level;     // mipmap level
  unsigned array_slice;   // array slice
  unsigned volume_slice;  // valid only for 3d textures
  e_cubemap_face face;    // valid only for cube textures
};
//----------------------------------------------------------------------------


//============================================================================
// texture_loader_params
//============================================================================
struct texture_loader_params
{
  // construction
  PFC_INLINE texture_loader_params(e_texture_format=texfmt_none);
  //--------------------------------------------------------------------------

  e_texture_format target_format;
  e_texture_color_space color_space;
  e_texture_content content_type;
  e_texture_resize_mode resize_mode;
  e_mip_filter mip_filter;
  int num_mips;
  unsigned first_mip_level;
};
//----------------------------------------------------------------------------


//============================================================================
// texture_loader
//============================================================================
// note: loader can only do simple format conversions between RGBA formats.
class texture_loader
{
public:
  //==========================================================================
  // texture_loader::loader_base
  //==========================================================================
  class loader_base
  {
  public:
    // construction
    virtual ~loader_base()=0;
    //------------------------------------------------------------------------

    // loading
    virtual bool layer(texture_layer&) const=0;
    virtual void load_layer(void*, unsigned pitch_)=0;
    virtual void skip_layer()=0;
  };
  typedef poly_variant<texture_loader::loader_base, 256> loader_variant_t;
  //--------------------------------------------------------------------------

  // construction
  texture_loader(bin_input_stream_base&);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE e_texture_type type() const;
  PFC_INLINE e_texture_format format() const;
  PFC_INLINE e_texture_format target_format() const;
  PFC_INLINE unsigned num_mips() const;
  PFC_INLINE unsigned width() const;
  PFC_INLINE unsigned height() const;
  PFC_INLINE unsigned depth() const;
  PFC_INLINE unsigned array_size() const;
  //--------------------------------------------------------------------------

  // data loading
  PFC_INLINE void set_target_format(e_texture_format);
  PFC_INLINE void enable_gamma(bool enable_=true);
  PFC_INLINE bool layer(texture_layer&) const;
  void load_layer(void*, unsigned pitch_=0);
  PFC_INLINE void skip_layer();
  //--------------------------------------------------------------------------

  // texture reader accessors and mutators
  PFC_INLINE bin_input_stream_base &stream();
  PFC_INLINE bool gamma_enabled() const;
  PFC_INLINE void set_source_format(e_texture_format);
  PFC_INLINE void set_source_type(e_texture_type);
  PFC_INLINE void set_source_size(unsigned width_, unsigned height_, unsigned depth_=1, unsigned num_mips_=1, unsigned array_size_=1);
  //--------------------------------------------------------------------------

private:
  texture_loader(const texture_loader&); // not implemented
  void operator=(const texture_loader&); // not implemented
  class loader_null;
  //--------------------------------------------------------------------------

  bin_input_stream_base &m_stream;
  loader_variant_t m_loader;
  e_texture_type m_type;
  e_texture_format m_format;
  e_texture_format m_target_format;
  e_file_format m_file_format;
  bool m_enable_gamma;
  unsigned m_num_mips;
  unsigned m_width, m_height, m_depth;
  unsigned m_array_size;
};
//----------------------------------------------------------------------------


//============================================================================
// texture_manager_base
//============================================================================
class texture_manager_base
{
public:
  // construction
  texture_manager_base();
  //--------------------------------------------------------------------------

  // manager interface
  virtual void create_texture(const texture_loader&, const texture_loader_params&, unsigned num_mips_)=0;
  virtual void finalize()=0;
  virtual void *lock(const texture_layer&, int &pitch_)=0;
  virtual void unlock(const texture_layer&)=0;
  //--------------------------------------------------------------------------

private:
  texture_manager_base(const texture_manager_base&); // not implemented
  void operator=(const texture_manager_base&); // not implemented
};
//----------------------------------------------------------------------------


//============================================================================
// texture_converter
//============================================================================
// note: supported input formats are texfmt_a8r8g8b8 (default),
//       texfmt_a16b16g16r16f and texfmt_a32b32g32r32f
class texture_converter
{
public:
  // construction
  texture_converter();
  void reset();
  //--------------------------------------------------------------------------

  // configuration
  void set_input_format(e_texture_format);
  PFC_INLINE void set_target_format(e_texture_format, e_texture_content=texcontent_color);
  PFC_INLINE void set_gamma(float input_, float output_);
  PFC_INLINE void set_mip_filter(e_mip_filter);
  PFC_INLINE void set_target(void*, unsigned pitch_, unsigned mip_=0);
  PFC_INLINE void set_quality(e_texture_compression_quality);
  //--------------------------------------------------------------------------

  // convert
  void convert(const void *source_, unsigned width_, unsigned height_, e_texture_resize_mode mode_=texresize_none);
  //--------------------------------------------------------------------------

private:
  enum {max_mips=16};
  e_texture_format m_input_format;
  e_texture_format m_target_format;
  e_texture_content m_content_type;
  e_texture_compression_quality m_compression_quality;
  e_mip_filter m_mip_filter;
  float m_gamma_input, m_gamma_output;
  pair<void*, unsigned> m_targets[max_mips];
};
//----------------------------------------------------------------------------


//============================================================================
// tex2d_base
//============================================================================
class tex2d_base
{ PFC_REPOSITORY_BASE_CLASS_DECL(tex2d_base)
  {
    PFC_VAR_D(m_format, "Texture format");
    PFC_VAR_D(m_color_space, "Texture color space");
    PFC_VAR_D(m_num_mips, "Number of texture mipmaps");
    PFC_VAR_D(m_width, "Texture width");
    PFC_VAR_D(m_height, "Texture height");
    PFC_VAR_D(m_array_size, "Texture array size");
    PFC_VAR_D(m_source_width, "Width of the source texture");
    PFC_VAR_D(m_source_height, "Height of the source texture");
  }
  PFC_LEAF_CLASS_ALIAS("tex2d");
public:
  // nested types
  struct mip_data;
  enum {type=textype_2d};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE tex2d_base();
  virtual PFC_INLINE ~tex2d_base()=0;
  virtual void init(unsigned width_, unsigned height_, int num_mips_, e_texture_format, e_texture_color_space, const mip_data*, unsigned array_size_=1)=0;
  virtual void load(texture_loader&, const texture_loader_params&)=0;
  void load(bin_input_stream_base&, const texture_loader_params&);
  virtual void swap(tex2d_base&)=0;
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE e_texture_format format() const;
  PFC_INLINE e_texture_color_space color_space() const;
  PFC_INLINE unsigned num_mips() const;
  PFC_INLINE unsigned width() const;
  PFC_INLINE unsigned height() const;
  PFC_INLINE unsigned array_size() const;
  //--------------------------------------------------------------------------

protected:
  e_texture_format m_format;
  e_texture_color_space m_color_space;
  unsigned m_num_mips;
  unsigned m_width, m_height;
  unsigned m_array_size;
  unsigned m_source_width, m_source_height;
};
//----------------------------------------------------------------------------

//============================================================================
// tex2d_base::mip_data
//============================================================================
struct tex2d_base::mip_data
{
  const void *data;
};
//----------------------------------------------------------------------------


//============================================================================
// tex3d_base
//============================================================================
class tex3d_base
{ PFC_REPOSITORY_BASE_CLASS_DECL(tex3d_base)
  {
    PFC_VAR_D(m_format, "Texture format");
    PFC_VAR_D(m_color_space, "Texture color space");
    PFC_VAR_D(m_num_mips, "Number of texture mipmaps");
    PFC_VAR_D(m_width, "Texture width");
    PFC_VAR_D(m_height, "Texture height");
    PFC_VAR_D(m_depth, "Texture depth");
    PFC_VAR_D(m_source_width, "Width of the source texture");
    PFC_VAR_D(m_source_height, "Height of the source texture");
    PFC_VAR_D(m_source_depth, "Depth of the source texture");
  }
  PFC_LEAF_CLASS_ALIAS("tex3d");
public:
  // nested types
  struct mip_data;
  enum {type=textype_3d};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE tex3d_base();
  virtual PFC_INLINE ~tex3d_base()=0;
  virtual void init(unsigned width_, unsigned height_, unsigned depth_, int num_mips_, e_texture_format, e_texture_color_space, const mip_data*)=0;
  virtual void load(texture_loader&, const texture_loader_params&)=0;
  void load(bin_input_stream_base&, const texture_loader_params&);
  virtual void swap(tex3d_base&)=0;
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE e_texture_format format() const;
  PFC_INLINE e_texture_color_space color_space() const;
  PFC_INLINE unsigned num_mips() const;
  PFC_INLINE unsigned width() const;
  PFC_INLINE unsigned height() const;
  PFC_INLINE unsigned depth() const;
  //--------------------------------------------------------------------------

protected:
  e_texture_format m_format;
  e_texture_color_space m_color_space;
  unsigned m_num_mips;
  unsigned m_width, m_height, m_depth;
  unsigned m_source_width, m_source_height, m_source_depth;
};
//----------------------------------------------------------------------------

//============================================================================
// tex3d_base::mip_data
//============================================================================
struct tex3d_base::mip_data
{
  const void *data;
};
//----------------------------------------------------------------------------


//============================================================================
// texcube_base
//============================================================================
class texcube_base
{ PFC_REPOSITORY_BASE_CLASS_DECL(texcube_base)
  {
    PFC_VAR_D(m_format, "Texture format");
    PFC_VAR_D(m_color_space, "Texture color space");
    PFC_VAR_D(m_num_mips, "Number of texture mipmaps");
    PFC_VAR_D(m_edge_len, "Length of the cube texture edge");
    PFC_VAR_D(m_source_edge_len, "Length of the source cube texture edge");
  }
  PFC_LEAF_CLASS_ALIAS("texcube");
public:
  // nested types
  struct mip_data;
  enum {type=textype_cube};
  //--------------------------------------------------------------------------

  // construction
  PFC_INLINE texcube_base();
  virtual PFC_INLINE ~texcube_base()=0;
  virtual void init(unsigned edge_len_, int num_mips_, e_texture_format, e_texture_color_space, const mip_data*)=0;
  virtual void load(texture_loader&, const texture_loader_params&)=0;
  void load(bin_input_stream_base&, const texture_loader_params&);
  virtual void swap(texcube_base&)=0;
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE e_texture_format format() const;
  PFC_INLINE e_texture_color_space color_space() const;
  PFC_INLINE unsigned num_mips() const;
  PFC_INLINE unsigned edge_len() const;
  //--------------------------------------------------------------------------

protected:
  e_texture_format m_format;
  e_texture_color_space m_color_space;
  unsigned m_num_mips;
  unsigned m_edge_len;
  unsigned m_source_edge_len;
};
//----------------------------------------------------------------------------

//============================================================================
// texcube_base::mip_data
//============================================================================
struct texcube_base::mip_data
{
  const void *data[6]; // faces in order: -x, +x, -y, +y, -z, +z (-x=z-right/y-up, +x=z-left/y-up, -y=x-right/z-up, +y=x-right/z-down, -z=x-left/y-up, +z=x-right/y-up)
};
//----------------------------------------------------------------------------


//============================================================================
// cpu_tex2d
//============================================================================
class cpu_tex2d: public tex2d_base
{ PFC_CLASS_DECL(cpu_tex2d, tex2d_base) PFC_INTROSPEC_DECL;
public:
  // construction
  cpu_tex2d();
  virtual ~cpu_tex2d();
  virtual void init(unsigned width_, unsigned height_, int num_mips_, e_texture_format, e_texture_color_space, const mip_data*, unsigned array_size_=1);
  virtual void load(texture_loader&, const texture_loader_params&);
  using tex2d_base::load;
  virtual void swap(tex2d_base&);
  owner_data steal_data();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE const void *data(unsigned mip_level_=0, unsigned array_slice_=0) const;
  PFC_INLINE void *data(unsigned mip_level_=0, unsigned array_slice_=0);
  //--------------------------------------------------------------------------

private:
  cpu_tex2d(const cpu_tex2d&); // not implemented
  void operator=(const cpu_tex2d&); // not implemented
  //--------------------------------------------------------------------------

  void *m_mip_data;
};
//----------------------------------------------------------------------------


//============================================================================
// cpu_tex3d
//============================================================================
class cpu_tex3d: public tex3d_base
{ PFC_CLASS_DECL(cpu_tex3d, tex3d_base) PFC_INTROSPEC_DECL;
public:
  // construction
  cpu_tex3d();
  virtual ~cpu_tex3d();
  virtual void init(unsigned width_, unsigned height_, unsigned depth_, int num_mips_, e_texture_format, e_texture_color_space, const mip_data*);
  virtual void load(texture_loader&, const texture_loader_params&);
  using tex3d_base::load;
  virtual void swap(tex3d_base&);
  owner_data steal_data();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE const void *data(unsigned mip_level_=0) const;
  PFC_INLINE void *data(unsigned mip_level_=0);
  //--------------------------------------------------------------------------

private:
  cpu_tex3d(const cpu_tex3d&); // not implemented
  void operator=(const cpu_tex3d&); // not implemented
  //--------------------------------------------------------------------------

  void *m_mip_data;
};
//----------------------------------------------------------------------------


//============================================================================
// cpu_texcube
//============================================================================
class cpu_texcube: public texcube_base
{ PFC_CLASS_DECL(cpu_texcube, texcube_base) PFC_INTROSPEC_DECL;
public:
  // construction
  cpu_texcube();
  virtual ~cpu_texcube();
  virtual void init(unsigned edge_len_, int num_mips_, e_texture_format, e_texture_color_space, const mip_data*);
  virtual void load(texture_loader&, const texture_loader_params&);
  using texcube_base::load;
  virtual void swap(texcube_base&);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE const void *data(e_cubemap_face face_, unsigned mip_level_=0) const;
  PFC_INLINE void *data(e_cubemap_face face_, unsigned mip_level_=0);
  //--------------------------------------------------------------------------

private:
  cpu_texcube(const cpu_texcube&); // not implemented
  void operator=(const cpu_texcube&); // not implemented
  //--------------------------------------------------------------------------

  void *m_mip_data[6];
};
//----------------------------------------------------------------------------


//============================================================================
// texture property functions
//============================================================================
unsigned texsize(unsigned size_, e_texture_resize_mode);
unsigned texfmt_bpp(e_texture_format);
e_texture_format_type texfmt_type(e_texture_format);
unsigned texfmt_num_channels(e_texture_format);
unsigned texfmt_num_rgb_channels(e_texture_format);
unsigned texfmt_num_alpha_channels(e_texture_format);
unsigned texfmt_blocksize(e_texture_format);
void texfmt_rgba_mask32(e_texture_format, uint32_t &rmask_, uint32_t &gmask_, uint32_t &bmask_, uint32_t &amask_);
void texfmt_rgba_mask_size(e_texture_format, uint32_t &rmask_size_, uint32_t &gmask_size_, uint32_t &bmask_size_, uint32_t &amask_size_);
void texfmt_rgba_mask_pos(e_texture_format, uint32_t &rmask_pos_, uint32_t &gmask_pos_, uint32_t &bmask_pos_, uint32_t &amask_pos_);
const char *texfmt_str(e_texture_format);
unsigned texture_size_2d(unsigned width_, unsigned height_, e_texture_format, int num_mips_=-1);
unsigned texture_size_3d(unsigned width_, unsigned height_, unsigned depth_, e_texture_format, int num_mips_=-1);
unsigned texture_mip_size_2d(unsigned width_, unsigned height_, e_texture_format, unsigned mip_level_);
unsigned texture_mip_size_3d(unsigned width_, unsigned height_, unsigned depth_, e_texture_format, unsigned mip_level_);
unsigned texture_px_size_2d(unsigned width_, unsigned height_, int num_mips_=-1);
unsigned texture_px_size_3d(unsigned width_, unsigned height_, unsigned depth_, int num_mips_=-1);
PFC_INLINE unsigned texture_mip_px_size_2d(unsigned width_, unsigned height_, unsigned mip_level_);
PFC_INLINE unsigned texture_mip_px_size_3d(unsigned width_, unsigned height_, unsigned depth_, unsigned mip_level_);
unsigned texture_mips_2d(unsigned width_, unsigned height_, e_texture_format=texfmt_none, int num_mips_=-1);
unsigned texture_mips_3d(unsigned width_, unsigned height_, unsigned depth_, e_texture_format=texfmt_none, int num_mips_=-1);
unsigned texture_pitch(unsigned width_, e_texture_format, unsigned mip_level_=0);
//----------------------------------------------------------------------------


//============================================================================
// texture conversion
//============================================================================
template<unsigned byte_size_, unsigned mask_, e_texture_format_type src_type_, e_texture_format_type dst_type_> struct pixel_reader;
template<unsigned byte_size_, e_texture_format_type src_type_, e_texture_format_type dst_type_> struct pixel_writer;
template<class DstFormatCfg, class SrcFormatCfg> void convert_rgba(void *dst_, const void *src_, usize_t num_pixels_);
void convert_rgba_to_rgba(void *dst_, const void *src_, e_texture_format dst_format_, e_texture_format src_format_, usize_t num_pixels_);
void interleave_rgba_to_rgba(void *dst_, const void *src_red_, const void *src_green_, const void *src_blue_, const void *src_alpha_, e_texture_format dst_format_, e_texture_format src_format_, usize_t num_pixels_, unsigned src_byte_packing_=0);
//----------------------------------------------------------------------------


//============================================================================
// texture creation functions
//============================================================================
owner_ref<tex2d_base> create_texture_2d(unsigned width_, unsigned height_, unsigned num_mips_, e_texture_format, e_texture_color_space, const tex2d_base::mip_data*, unsigned array_size_=1);
owner_ref<tex3d_base> create_texture_3d(unsigned width_, unsigned height_, unsigned depth_, unsigned num_mips_, e_texture_format, e_texture_color_space, const tex3d_base::mip_data*);
owner_ref<texcube_base> create_texture_cube(unsigned edge_len_, unsigned num_mips_, e_texture_format, e_texture_color_space, const texcube_base::mip_data*);
//----------------------------------------------------------------------------


//============================================================================
// texture format support query
//============================================================================
e_file_format_support texture_support_dds();
e_file_format_support texture_support_jp2();
e_file_format_support texture_support_jpg();
e_file_format_support texture_support_png();
e_file_format_support texture_support_psd();
e_file_format_support texture_support_tga();
e_file_format_support texture_support_tiff();
e_file_format_support texture_support_webp();
//----------------------------------------------------------------------------


//============================================================================
// texture loading functions
//============================================================================
e_file_format texture_file_format(const char *filename_ext_);
bool read_texture_2d(tex2d_base&, bin_input_stream_base&, const texture_loader_params &params_=texture_loader_params(), const char *id_=0);
bool read_texture_3d(tex3d_base&, bin_input_stream_base&, const texture_loader_params &params_=texture_loader_params(), const char *id_=0);
bool read_texture_cube(texcube_base&, bin_input_stream_base&, const texture_loader_params &params_=texture_loader_params(), const char *id_=0);
e_texture_type load_texture(bin_input_stream_base&, const str_id&, const texture_loader_params &params_=texture_loader_params());
e_texture_type load_texture(const str_id&, const texture_loader_params &params_=texture_loader_params(), const char *path_=0);
void load_texture(texture_manager_base&, texture_loader&, const texture_loader_params &params_=texture_loader_params());
tex2d_base *load_texture_2d(bin_input_stream_base&, const str_id&, const texture_loader_params &params_=texture_loader_params());
tex2d_base *load_texture_2d(const str_id&, const texture_loader_params &params_=texture_loader_params(), const char *path_=0);
tex3d_base *load_texture_3d(bin_input_stream_base&, const str_id&, const texture_loader_params &params_=texture_loader_params());
tex3d_base *load_texture_3d(const str_id&, const texture_loader_params &params_=texture_loader_params(), const char *path_=0);
texcube_base *load_texture_cube(bin_input_stream_base&, const str_id&, const texture_loader_params &params_=texture_loader_params());
texcube_base *load_texture_cube(const str_id&, const texture_loader_params &params_=texture_loader_params(), const char *path_=0);
//----------------------------------------------------------------------------


//============================================================================
// texture write functions
//============================================================================
struct texture_writer_params_dds
{
  texture_writer_params_dds();
};
//----------------------------------------------------------------------------

struct texture_writer_params_jp2
{
  texture_writer_params_jp2();
};
//----------------------------------------------------------------------------

struct texture_writer_params_jpg
{
  // construction
  texture_writer_params_jpg();
  texture_writer_params_jpg(ufloat1_t quality_);
  //--------------------------------------------------------------------------

  ufloat1_t quality;
};
//----------------------------------------------------------------------------

struct texture_writer_params_png
{
  // construction
  texture_writer_params_png();
  texture_writer_params_png(bool is_16bpp_, bool save_alpha_);
  //--------------------------------------------------------------------------

  bool is_16bpp;
  bool save_alpha;
};
//----------------------------------------------------------------------------

struct texture_writer_params_psd
{
  texture_writer_params_psd();
};
//----------------------------------------------------------------------------

struct texture_writer_params_tga
{
  texture_writer_params_tga();
};
//----------------------------------------------------------------------------

struct texture_writer_params_tiff
{
  texture_writer_params_tiff();
};
//----------------------------------------------------------------------------

struct texture_writer_params_webp
{
  texture_writer_params_webp();
};
//----------------------------------------------------------------------------

bool write_texture_dds(bin_output_stream_base&, const texture_writer_params_dds&, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, unsigned depth_, ssize_t row_pitch_=0, ssize_t slice_pitch_=0);
bool write_texture_jp2(bin_output_stream_base&, const texture_writer_params_jp2&, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_=0);
bool write_texture_jpg(bin_output_stream_base&, const texture_writer_params_jpg&, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_=0);
bool write_texture_png(bin_output_stream_base&, const texture_writer_params_png&, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_=0);
bool write_texture_psd(bin_output_stream_base&, const texture_writer_params_psd&, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_=0);
bool write_texture_tga(bin_output_stream_base&, const texture_writer_params_tga&, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_=0);
bool write_texture_tiff(bin_output_stream_base&, const texture_writer_params_tiff&, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_=0);
bool write_texture_webp(bin_output_stream_base&, const texture_writer_params_webp&, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_=0);
//----------------------------------------------------------------------------

//============================================================================
#include "texture.inl"
} // namespace pfc
#endif
