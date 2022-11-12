//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// texture_layer
//============================================================================
texture_layer::texture_layer()
{
  mip_level=0;
  array_slice=0;
  volume_slice=0;
  face=cubeface_negx;
}
//----------------------------------------------------------------------------


//============================================================================
// texture_loader_params
//============================================================================
texture_loader_params::texture_loader_params(e_texture_format target_format_)
{
  target_format=target_format_;
  color_space=texcolspace_linear_rgb;
  content_type=texcontent_color;
  resize_mode=texresize_none;
  mip_filter=mipfilter_none;
  num_mips=-1;
  first_mip_level=0;
}
//----------------------------------------------------------------------------


//============================================================================
// texture_loader
//============================================================================
e_texture_type texture_loader::type() const
{
  return m_type;
}
//----

e_texture_format texture_loader::format() const
{
  return m_format;
}
//----

e_texture_format texture_loader::target_format() const
{
  return m_target_format;
}
//----

unsigned texture_loader::num_mips() const
{
  return m_num_mips;
}
//----

unsigned texture_loader::width() const
{
  return m_width;
}
//----

unsigned texture_loader::height() const
{
  return m_height;
}
//----

unsigned texture_loader::depth() const
{
  return m_depth;
}
//----

unsigned texture_loader::array_size() const
{
  return m_array_size;
}
//----------------------------------------------------------------------------

void texture_loader::set_target_format(e_texture_format f_)
{
  m_target_format=f_;
}
//----

void texture_loader::enable_gamma(bool enable_)
{
  m_enable_gamma=enable_;
}
//----

bool texture_loader::layer(texture_layer &l_) const
{
  return m_loader->layer(l_);
}
//----

void texture_loader::skip_layer()
{
  m_loader->skip_layer();
}
//----------------------------------------------------------------------------

bin_input_stream_base &texture_loader::stream()
{
  return m_stream;
}
//----

bool texture_loader::gamma_enabled() const
{
  return m_enable_gamma;
}
//----

void texture_loader::set_source_format(e_texture_format fmt_)
{
  m_format=fmt_;
}
//----

void texture_loader::set_source_type(e_texture_type type_)
{
  m_type=type_;
}
//----

void texture_loader::set_source_size(unsigned width_, unsigned height_, unsigned depth_, unsigned num_mips_, unsigned array_size_)
{
  m_width=width_;
  m_height=height_;
  m_depth=depth_;
  m_num_mips=num_mips_;
  m_array_size=array_size_;
}
//----------------------------------------------------------------------------


//============================================================================
// texture_converter
//============================================================================
void texture_converter::set_target_format(e_texture_format f_, e_texture_content content_type_)
{
  m_target_format=f_;
  m_content_type=content_type_;
}
//----

void texture_converter::set_gamma(float input_, float output_)
{
  m_gamma_input=input_;
  m_gamma_output=output_;
}
//----

void texture_converter::set_mip_filter(e_mip_filter f_)
{
  m_mip_filter=f_;
}
//----

void texture_converter::set_target(void *data_, unsigned pitch_, unsigned mip_)
{
  PFC_ASSERT(mip_<max_mips);
  m_targets[mip_].first=data_;
  m_targets[mip_].second=pitch_;
}
//----

void texture_converter::set_quality(e_texture_compression_quality quality_)
{
  m_compression_quality=quality_;
}
//----------------------------------------------------------------------------


//============================================================================
// tex2d_base
//============================================================================
tex2d_base::tex2d_base()
  :m_format(texfmt_none)
  ,m_color_space(texcolspace_linear_rgb)
  ,m_num_mips(0)
  ,m_width(0)
  ,m_height(0)
  ,m_array_size(0)
  ,m_source_width(0)
  ,m_source_height(0)
{
}
//----

tex2d_base::~tex2d_base()
{
}
//----------------------------------------------------------------------------

e_texture_format tex2d_base::format() const
{
  return m_format;
}
//----

e_texture_color_space tex2d_base::color_space() const
{
  return m_color_space;
}
//----

unsigned tex2d_base::num_mips() const
{
  return m_num_mips;
}
//----

unsigned tex2d_base::width() const
{
  return m_width;
}
//----

unsigned tex2d_base::height() const
{
  return m_height;
}
//----

unsigned tex2d_base::array_size() const
{
  return m_array_size;
}
//----------------------------------------------------------------------------


//============================================================================
// tex3d_base
//============================================================================
tex3d_base::tex3d_base()
  :m_format(texfmt_none)
  ,m_color_space(texcolspace_linear_rgb)
  ,m_num_mips(0)
  ,m_width(0)
  ,m_height(0)
  ,m_depth(0)
  ,m_source_width(0)
  ,m_source_height(0)
  ,m_source_depth(0)
{
}
//----

tex3d_base::~tex3d_base()
{
}
//----------------------------------------------------------------------------

e_texture_format tex3d_base::format() const
{
  return m_format;
}
//----

e_texture_color_space tex3d_base::color_space() const
{
  return m_color_space;
}
//----

unsigned tex3d_base::num_mips() const
{
  return m_num_mips;
}
//----

unsigned tex3d_base::width() const
{
  return m_width;
}
//----

unsigned tex3d_base::height() const
{
  return m_height;
}
//----

unsigned tex3d_base::depth() const
{
  return m_depth;
}
//----------------------------------------------------------------------------


//============================================================================
// texcube_base
//============================================================================
texcube_base::texcube_base()
  :m_format(texfmt_none)
  ,m_color_space(texcolspace_linear_rgb)
  ,m_num_mips(0)
  ,m_edge_len(0)
  ,m_source_edge_len(0)
{
}
//----

texcube_base::~texcube_base()
{
}
//----------------------------------------------------------------------------

e_texture_format texcube_base::format() const
{
  return m_format;
}
//----

e_texture_color_space texcube_base::color_space() const
{
  return m_color_space;
}
//----

unsigned texcube_base::num_mips() const
{
  return m_num_mips;
}
//----

unsigned texcube_base::edge_len() const
{
  return m_edge_len;
}
//----------------------------------------------------------------------------


//============================================================================
// cpu_tex2d
//============================================================================
const void *cpu_tex2d::data(unsigned mip_level_, unsigned array_slice_) const
{
  return static_cast<const char*>(m_mip_data)+(mip_level_?texture_size_2d(m_width, m_height, m_format, mip_level_-1):0)+array_slice_*texture_size_2d(m_width, m_height, m_format, m_num_mips);
}
//----

void *cpu_tex2d::data(unsigned mip_level_, unsigned array_slice_)
{
  return static_cast<char*>(m_mip_data)+(mip_level_?texture_size_2d(m_width, m_height, m_format, mip_level_-1):0)+array_slice_*texture_size_2d(m_width, m_height, m_format, m_num_mips);
}
//----------------------------------------------------------------------------


//============================================================================
// cpu_tex3d
//============================================================================
const void *cpu_tex3d::data(unsigned mip_level_) const
{
  return static_cast<const char*>(m_mip_data)+(mip_level_?texture_size_3d(m_width, m_height, m_depth, m_format, mip_level_-1):0);
}
//----

void *cpu_tex3d::data(unsigned mip_level_)
{
  return static_cast<char*>(m_mip_data)+(mip_level_?texture_size_3d(m_width, m_height, m_depth, m_format, mip_level_-1):0);
}
//----------------------------------------------------------------------------


//============================================================================
// cpu_texcube
//============================================================================
const void *cpu_texcube::data(e_cubemap_face face_, unsigned mip_level_) const
{
  return static_cast<const char*>(m_mip_data[face_])+(mip_level_?texture_size_2d(m_edge_len, m_edge_len, m_format, mip_level_-1):0);
}
//----

void *cpu_texcube::data(e_cubemap_face face_, unsigned mip_level_)
{
  return static_cast<char*>(m_mip_data[face_])+(mip_level_?texture_size_2d(m_edge_len, m_edge_len, m_format, mip_level_-1):0);
}
//----------------------------------------------------------------------------


//============================================================================
// texture property functions
//============================================================================
unsigned pfc::texture_mip_px_size_2d(unsigned width_, unsigned height_, unsigned mip_level_)
{
  // calculate size of the texture mip in pixels
  return max(1u, width_>>mip_level_)*max(1u, height_>>mip_level_);
}
//----

unsigned pfc::texture_mip_px_size_3d(unsigned width_, unsigned height_, unsigned depth_, unsigned mip_level_)
{
  // calculate size of the texture mip in pixels
  return max(1u, width_>>mip_level_)*max(1u, height_>>mip_level_)*max(1u, depth_>>mip_level_);
}
//----------------------------------------------------------------------------


//============================================================================
// pixel_reader
//============================================================================
template<unsigned byte_size_, unsigned mask_, e_texture_format_type src_type_, e_texture_format_type dst_type_>
struct pixel_reader
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    unsigned size=byte_size_; // VS ICE fix
    ::memcpy(dst_, src_, size);
  }
  //----

  static PFC_INLINE void read_unaligned(void *dst_, const void *src_, unsigned bit_pos_)
  {
    typedef typename meta_type_array<void, uint16_t, uint32_t, uint64_t, uint128_t>::get<meta_log2<meta_next_pow2<byte_size_+1>::res>::res>::res value_t;
    value_t v;
    ::memcpy(&v, src_, byte_size_+1);
    v>>=bit_pos_;
    ::memcpy(dst_, &v, byte_size_);
  }
};
//----

template<unsigned mask_>
struct pixel_reader<4, mask_, texfmttype_rgba32f, texfmttype_rgba>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    if(mask_&1)
    {
      f2u.f32=((float*)src_)[0]*8388607.0f+8388608.0f;
      ((uint32_t*)dst_)[0]=f2u.u32<<9;
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<8, mask_, texfmttype_rgba32f, texfmttype_rgba>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    if(mask_&1)
    {
      f2u.f32=((float*)src_)[0]*8388607.0f+8388608.0f;
      ((uint32_t*)dst_)[0]=f2u.u32<<9;
    }
    if(mask_&2)
    {
      f2u.f32=((float*)src_)[1]*8388607.0f+8388608.0f;
      ((uint32_t*)dst_)[1]=f2u.u32<<9;
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<12, mask_, texfmttype_rgba32f, texfmttype_rgba>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    if(mask_&1)
    {
      f2u.f32=((float*)src_)[0]*8388607.0f+8388608.0f;
      ((uint32_t*)dst_)[0]=f2u.u32<<9;
    }
    if(mask_&2)
    {
      f2u.f32=((float*)src_)[1]*8388607.0f+8388608.0f;
      ((uint32_t*)dst_)[1]=f2u.u32<<9;
    }
    if(mask_&4)
    {
      f2u.f32=((float*)src_)[2]*8388607.0f+8388608.0f;
      ((uint32_t*)dst_)[2]=f2u.u32<<9;
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<16, mask_, texfmttype_rgba32f, texfmttype_rgba>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    if(mask_&1)
    {
      f2u.f32=((float*)src_)[0]*8388607.0f+8388608.0f;
      ((uint32_t*)dst_)[0]=f2u.u32<<9;
    }
    if(mask_&2)
    {
      f2u.f32=((float*)src_)[1]*8388607.0f+8388608.0f;
      ((uint32_t*)dst_)[1]=f2u.u32<<9;
    }
    if(mask_&4)
    {
      f2u.f32=((float*)src_)[2]*8388607.0f+8388608.0f;
      ((uint32_t*)dst_)[2]=f2u.u32<<9;
    }
    if(mask_&8)
    {
      f2u.f32=((float*)src_)[3]*8388607.0f+8388608.0f;
      ((uint32_t*)dst_)[3]=f2u.u32<<9;
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<2, mask_, texfmttype_rgba16f, texfmttype_rgba>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    if(mask_&1)
    {
      f2u.u32=(((uint16_t*)src_)[0]<<13);
      f2u.u32+=f2u.u32?0xe0000:0;
      f2u.f32=f2u.f32*65535.0f+8388608.0f;
      ((uint16_t*)dst_)[0]=uint16_t(f2u.u32);
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<4, mask_, texfmttype_rgba16f, texfmttype_rgba>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    if(mask_&1)
    {
      f2u.u32=(((uint16_t*)src_)[0]<<13);
      f2u.u32+=f2u.u32?0xe0000:0;
      f2u.f32=f2u.f32*65535.0f+8388608.0f;
      ((uint16_t*)dst_)[0]=uint16_t(f2u.u32);
    }
    if(mask_&2)
    {
      f2u.u32=(((uint16_t*)src_)[1]<<13);
      f2u.u32+=f2u.u32?0xe0000:0;
      f2u.f32=f2u.f32*65535.0f+8388608.0f;
      ((uint16_t*)dst_)[1]=uint16_t(f2u.u32);
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<6, mask_, texfmttype_rgba16f, texfmttype_rgba>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    if(mask_&1)
    {
      f2u.u32=(((uint16_t*)src_)[0]<<13);
      f2u.u32+=f2u.u32?0xe0000:0;
      f2u.f32=f2u.f32*65535.0f+8388608.0f;
      ((uint16_t*)dst_)[0]=uint16_t(f2u.u32);
    }
    if(mask_&2)
    {
      f2u.u32=(((uint16_t*)src_)[1]<<13);
      f2u.u32+=f2u.u32?0xe0000:0;
      f2u.f32=f2u.f32*65535.0f+8388608.0f;
      ((uint16_t*)dst_)[1]=uint16_t(f2u.u32);
    }
    if(mask_&4)
    {
      f2u.u32=(((uint16_t*)src_)[2]<<13);
      f2u.u32+=f2u.u32?0xe0000:0;
      f2u.f32=f2u.f32*65535.0f+8388608.0f;
      ((uint16_t*)dst_)[2]=uint16_t(f2u.u32);
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<8, mask_, texfmttype_rgba16f, texfmttype_rgba>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    if(mask_&1)
    {
      f2u.u32=(((uint16_t*)src_)[0]<<13);
      f2u.u32+=f2u.u32?0xe0000:0;
      f2u.f32=f2u.f32*65535.0f+8388608.0f;
      ((uint16_t*)dst_)[0]=uint16_t(f2u.u32);
    }
    if(mask_&2)
    {
      f2u.u32=(((uint16_t*)src_)[1]<<13);
      f2u.u32+=f2u.u32?0xe0000:0;
      f2u.f32=f2u.f32*65535.0f+8388608.0f;
      ((uint16_t*)dst_)[1]=uint16_t(f2u.u32);
    }
    if(mask_&4)
    {
      f2u.u32=(((uint16_t*)src_)[2]<<13);
      f2u.u32+=f2u.u32?0xe0000:0;
      f2u.f32=f2u.f32*65535.0f+8388608.0f;
      ((uint16_t*)dst_)[2]=uint16_t(f2u.u32);
    }
    if(mask_&8)
    {
      f2u.u32=(((uint16_t*)src_)[3]<<13);
      f2u.u32+=f2u.u32?0xe0000:0;
      f2u.f32=f2u.f32*65535.0f+8388608.0f;
      ((uint16_t*)dst_)[3]=uint16_t(f2u.u32);
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<4, mask_, texfmttype_rgba32f, texfmttype_rgba16f>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    if(mask_&1)
    {
      uint16_t v=uint16_t(((uint32_t*)src_)[0]>>13);
      ((uint16_t*)dst_)[0]=v+(v?0x4000:0);
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<8, mask_, texfmttype_rgba32f, texfmttype_rgba16f>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    if(mask_&1)
    {
      uint16_t v=uint16_t(((uint32_t*)src_)[0]>>13);
      ((uint16_t*)dst_)[0]=v+(v?0x4000:0);
    }
    if(mask_&2)
    {
      uint16_t v=uint16_t(((uint32_t*)src_)[1]>>13);
      ((uint16_t*)dst_)[1]=v+(v?0x4000:0);
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<12, mask_, texfmttype_rgba32f, texfmttype_rgba16f>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    if(mask_&1)
    {
      uint16_t v=uint16_t(((uint32_t*)src_)[0]>>13);
      ((uint16_t*)dst_)[0]=v+(v?0x4000:0);
    }
    if(mask_&2)
    {
      uint16_t v=uint16_t(((uint32_t*)src_)[1]>>13);
      ((uint16_t*)dst_)[1]=v+(v?0x4000:0);
    }
    if(mask_&4)
    {
      uint16_t v=uint16_t(((uint32_t*)src_)[2]>>13);
      ((uint16_t*)dst_)[2]=v+(v?0x4000:0);
    }
  }
};
//----

template<unsigned mask_>
struct pixel_reader<16, mask_, texfmttype_rgba32f, texfmttype_rgba16f>
{
  static PFC_INLINE void read(void *dst_, const void *src_)
  {
    if(mask_&1)
    {
      uint16_t v=uint16_t(((uint32_t*)src_)[0]>>13);
      ((uint16_t*)dst_)[0]=v+(v?0x4000:0);
    }
    if(mask_&2)
    {
      uint16_t v=uint16_t(((uint32_t*)src_)[1]>>13);
      ((uint16_t*)dst_)[1]=v+(v?0x4000:0);
    }
    if(mask_&4)
    {
      uint16_t v=uint16_t(((uint32_t*)src_)[2]>>13);
      ((uint16_t*)dst_)[2]=v+(v?0x4000:0);
    }
    if(mask_&8)
    {
      uint16_t v=uint16_t(((uint32_t*)src_)[3]>>13);
      ((uint16_t*)dst_)[3]=v+(v?0x4000:0);
    }
  }
};
//----------------------------------------------------------------------------

template<e_texture_format_type src_type_, e_texture_format_type dst_type_, unsigned mask_>
struct pixel_reader<0, mask_, src_type_, dst_type_>
{
  static PFC_INLINE void read(void *dst_, const void *src_) {}
  static PFC_INLINE void read_unaligned(void *dst_, const void *src_, unsigned bit_pos_) {}
};
//----------------------------------------------------------------------------


//============================================================================
// pixel_writer
//============================================================================
template<unsigned byte_size_, e_texture_format_type src_type_, e_texture_format_type dst_type_>
struct pixel_writer
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    ::memcpy(dst_, src_, byte_size_);
  }
};
//----

template<>
struct pixel_writer<4, texfmttype_rgba, texfmttype_rgba32f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    ((float*)dst_)[0]=((uint32_t*)src_)[0]/4294967295.0f;
  }
};
//----

template<>
struct pixel_writer<8, texfmttype_rgba, texfmttype_rgba32f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    ((float*)dst_)[0]=((uint32_t*)src_)[0]/4294967295.0f;
    ((float*)dst_)[1]=((uint32_t*)src_)[1]/4294967295.0f;
  }
};
//----

template<>
struct pixel_writer<12, texfmttype_rgba, texfmttype_rgba32f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    ((float*)dst_)[0]=((uint32_t*)src_)[0]/4294967295.0f;
    ((float*)dst_)[1]=((uint32_t*)src_)[1]/4294967295.0f;
    ((float*)dst_)[2]=((uint32_t*)src_)[2]/4294967295.0f;
  }
};
//----

template<>
struct pixel_writer<16, texfmttype_rgba, texfmttype_rgba32f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    ((float*)dst_)[0]=((uint32_t*)src_)[0]/4294967295.0f;
    ((float*)dst_)[1]=((uint32_t*)src_)[1]/4294967295.0f;
    ((float*)dst_)[2]=((uint32_t*)src_)[2]/4294967295.0f;
    ((float*)dst_)[3]=((uint32_t*)src_)[3]/4294967295.0f;
  }
};
//----

template<>
struct pixel_writer<2, texfmttype_rgba, texfmttype_rgba16f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    f2u.f32=((uint16_t*)src_)[0]/65535.0f;
    ((uint16_t*)dst_)[0]=uint16_t((f2u.u32>>13)+(f2u.u32?0x4000:0));
  }
};
//----

template<>
struct pixel_writer<4, texfmttype_rgba, texfmttype_rgba16f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    f2u.f32=((uint16_t*)src_)[0]/65535.0f;
    ((uint16_t*)dst_)[0]=uint16_t((f2u.u32>>13)+(f2u.u32?0x4000:0));
    f2u.f32=((uint16_t*)src_)[1]/65535.0f;
    ((uint16_t*)dst_)[1]=uint16_t((f2u.u32>>13)+(f2u.u32?0x4000:0));
  }
};
//----

template<>
struct pixel_writer<6, texfmttype_rgba, texfmttype_rgba16f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    f2u.f32=((uint16_t*)src_)[0]/65535.0f;
    ((uint16_t*)dst_)[0]=uint16_t((f2u.u32>>13)+(f2u.u32?0x4000:0));
    f2u.f32=((uint16_t*)src_)[1]/65535.0f;
    ((uint16_t*)dst_)[1]=uint16_t((f2u.u32>>13)+(f2u.u32?0x4000:0));
    f2u.f32=((uint16_t*)src_)[2]/65535.0f;
    ((uint16_t*)dst_)[2]=uint16_t((f2u.u32>>13)+(f2u.u32?0x4000:0));
  }
};
//----

template<>
struct pixel_writer<8, texfmttype_rgba, texfmttype_rgba16f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    f2u.f32=((uint16_t*)src_)[0]/65535.0f;
    ((uint16_t*)dst_)[0]=uint16_t((f2u.u32>>13)+(f2u.u32?0x4000:0));
    f2u.f32=((uint16_t*)src_)[1]/65535.0f;
    ((uint16_t*)dst_)[1]=uint16_t((f2u.u32>>13)+(f2u.u32?0x4000:0));
    f2u.f32=((uint16_t*)src_)[2]/65535.0f;
    ((uint16_t*)dst_)[2]=uint16_t((f2u.u32>>13)+(f2u.u32?0x4000:0));
    f2u.f32=((uint16_t*)src_)[3]/65535.0f;
    ((uint16_t*)dst_)[3]=uint16_t((f2u.u32>>13)+(f2u.u32?0x4000:0));
  }
};
//----

template<>
struct pixel_writer<4, texfmttype_rgba16f, texfmttype_rgba32f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    f2u.u32=(((uint16_t*)src_)[0]<<13);
    f2u.u32+=f2u.u32?0xe0000:0;
    ((float32_t*)dst_)[0]=f2u.f32;
  }
};
//----

template<>
struct pixel_writer<8, texfmttype_rgba16f, texfmttype_rgba32f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    f2u.u32=(((uint16_t*)src_)[0]<<13);
    f2u.u32+=f2u.u32?0xe0000:0;
    ((float32_t*)dst_)[0]=f2u.f32;
    f2u.u32=(((uint16_t*)src_)[1]<<13);
    f2u.u32+=f2u.u32?0xe0000:0;
    ((float32_t*)dst_)[1]=f2u.f32;
  }
};
//----

template<>
struct pixel_writer<12, texfmttype_rgba16f, texfmttype_rgba32f>
{
  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    f2u.u32=(((uint16_t*)src_)[0]<<13);
    f2u.u32+=f2u.u32?0xe0000:0;
    ((float32_t*)dst_)[0]=f2u.f32;
    f2u.u32=(((uint16_t*)src_)[1]<<13);
    f2u.u32+=f2u.u32?0xe0000:0;
    ((float32_t*)dst_)[1]=f2u.f32;
    f2u.u32=(((uint16_t*)src_)[2]<<13);
    f2u.u32+=f2u.u32?0xe0000:0;
    ((float32_t*)dst_)[2]=f2u.f32;
  }
};
//----

template<>
struct pixel_writer<16, texfmttype_rgba16f, texfmttype_rgba32f>
{
  static float32_t half_to_float(uint16_t half_)
  {
    union convert
    {
      uint32_t u32;
      float32_t f32;
    } f2u;
    f2u.u32=(half_<<16)&0x80000000;
    f2u.u32|=(((half_>>10)&0x1f)+127-15)<<23;
    f2u.u32|=(half_&0x3ff)<<13;
    return f2u.f32;
  }
  //----

  static PFC_INLINE void write(void *dst_, const void *src_)
  {
    ((float32_t*)dst_)[0]=half_to_float(((uint16_t*)src_)[1]);
    ((float32_t*)dst_)[1]=half_to_float(((uint16_t*)src_)[3]);
    ((float32_t*)dst_)[2]=half_to_float(((uint16_t*)src_)[5]);
    ((float32_t*)dst_)[3]=half_to_float(((uint16_t*)src_)[7]);
  }
};
//----------------------------------------------------------------------------

PFC_INLINE uint128_t operator&(const uint128_t &v0_, const uint128_t &v1_)
{
  uint128_t v={v0_.lo&v1_.lo, v0_.hi&v1_.hi};
  return v;
}
//----

PFC_INLINE uint128_t operator|(const uint128_t &v0_, const uint128_t &v1_)
{
  uint128_t v={v0_.lo|v1_.lo, v0_.hi|v1_.hi};
  return v;
}
//----------------------------------------------------------------------------

template<typename T>
PFC_INLINE T get_default_alpha_value(uint32_t v_)
{
  return T(v_);
}
//----

template<>
PFC_INLINE uint128_t get_default_alpha_value<uint128_t>(uint32_t v_)
{
  uint128_t v;
  v.lo=v_;
  v.hi=0;
  return v;
}
//----------------------------------------------------------------------------


//============================================================================
// convert_rgba
//============================================================================
template<class DstFormatCfg, class SrcFormatCfg>
void convert_rgba(void *dst_, const void *src_, usize_t num_pixels_)
{
  // pixel conversion config
  enum {src_bytespp=SrcFormatCfg::bpp/8,
        dst_bytespp=DstFormatCfg::bpp/8,
        src_format_type=SrcFormatCfg::type,
        dst_format_type=DstFormatCfg::type,
        src_rmask_size=SrcFormatCfg::rmask_size,
        src_gmask_size=SrcFormatCfg::gmask_size,
        src_bmask_size=SrcFormatCfg::bmask_size,
        src_amask_size=SrcFormatCfg::amask_size,
        src_rmask_pos=SrcFormatCfg::rmask_pos,
        src_gmask_pos=SrcFormatCfg::gmask_pos,
        src_bmask_pos=SrcFormatCfg::bmask_pos,
        src_amask_pos=SrcFormatCfg::amask_pos,
        src_num_channels=(src_rmask_size?1:0)+(src_gmask_size?1:0)+(src_bmask_size?1:0)+(src_amask_size?1:0),
        dst_rmask_size=DstFormatCfg::rmask_size,
        dst_gmask_size=DstFormatCfg::gmask_size,
        dst_bmask_size=DstFormatCfg::bmask_size,
        dst_amask_size=DstFormatCfg::amask_size,
        dst_rmask_pos=DstFormatCfg::rmask_pos,
        dst_gmask_pos=DstFormatCfg::gmask_pos,
        dst_bmask_pos=DstFormatCfg::bmask_pos,
        dst_amask_pos=DstFormatCfg::amask_pos,
        dst_num_channels=(dst_rmask_size?1:0)+(dst_gmask_size?1:0)+(dst_bmask_size?1:0)+(dst_amask_size?1:0),
        min_rmask_size=meta_min<src_rmask_size, dst_rmask_size>::res,
        min_gmask_size=meta_min<src_gmask_size, dst_gmask_size>::res,
        min_bmask_size=meta_min<src_bmask_size, dst_bmask_size>::res,
        min_amask_size=meta_min<src_amask_size, dst_amask_size>::res,
        rshift=dst_rmask_size&&src_rmask_size?(dst_rmask_pos+dst_rmask_size)-(src_rmask_pos+src_rmask_size):0,
        gshift=dst_gmask_size&&src_gmask_size?(dst_gmask_pos+dst_gmask_size)-(src_gmask_pos+src_gmask_size):0,
        bshift=dst_bmask_size&&src_bmask_size?(dst_bmask_pos+dst_bmask_size)-(src_bmask_pos+src_bmask_size):0,
        ashift=dst_amask_size&&src_amask_size?(dst_amask_pos+dst_amask_size)-(src_amask_pos+src_amask_size):0,
        src_mask0=(SrcFormatCfg::rgba_order>>0)&0xf,
        src_mask1=(SrcFormatCfg::rgba_order>>4)&0xf,
        src_mask2=(SrcFormatCfg::rgba_order>>8)&0xf,
        src_mask3=(SrcFormatCfg::rgba_order>>12)&0xf,
        dst_mask0=(DstFormatCfg::rgba_order>>0)&0xf,
        dst_mask1=(DstFormatCfg::rgba_order>>4)&0xf,
        dst_mask2=(DstFormatCfg::rgba_order>>8)&0xf,
        dst_mask3=(DstFormatCfg::rgba_order>>12)&0xf,
        read_mask= (src_mask0&&(src_mask0==dst_mask0||src_mask0==dst_mask1||src_mask0==dst_mask2||src_mask0==dst_mask3)?0x1:0)
                  |(src_mask1&&(src_mask1==dst_mask0||src_mask1==dst_mask1||src_mask1==dst_mask2||src_mask1==dst_mask3)?0x2:0)
                  |(src_mask2&&(src_mask2==dst_mask0||src_mask2==dst_mask1||src_mask2==dst_mask2||src_mask2==dst_mask3)?0x4:0)
                  |(src_mask3&&(src_mask3==dst_mask0||src_mask3==dst_mask1||src_mask3==dst_mask2||src_mask3==dst_mask3)?0x8:0),
  };

  if(num_pixels_)
  {
    // convert pixels
    const uint8_t *src=(uint8_t*)src_;
    uint8_t *dst=(uint8_t*)dst_;
    uint8_t *end=dst+dst_bytespp*num_pixels_;
    typedef meta_type_array<uint8_t, uint16_t, uint32_t, uint64_t, uint128_t> format_array_t;
    typedef typename format_array_t::get<meta_log2<meta_next_pow2<meta_max<src_bytespp, dst_bytespp>::res>::res>::res>::res convert_t;
    static const convert_t s_zero=numeric_type<convert_t>::zero();
    enum {default_alpha_value=dst_format_type==texfmttype_rgba32f?0x3f800000:dst_format_type==texfmttype_rgba16f?0x00003c00:(0xffffffff&meta_mask<dst_amask_size>::res)};
    static const convert_t s_default_alpha=dst_amask_size?bit_shift<dst_amask_pos>(get_default_alpha_value<convert_t>(uint32_t(default_alpha_value))):s_zero;
    do
    {
      convert_t input;
      pixel_reader<src_bytespp, read_mask, (e_texture_format_type)src_format_type, (e_texture_format_type)dst_format_type>::read(&input, src);
      convert_t output= (min_rmask_size?(bit_shift<rshift>(input)&meta_mask<min_rmask_size, dst_rmask_pos+dst_rmask_size-min_rmask_size, convert_t>::res):s_zero)
                       |(min_gmask_size?(bit_shift<gshift>(input)&meta_mask<min_gmask_size, dst_gmask_pos+dst_gmask_size-min_gmask_size, convert_t>::res):s_zero)
                       |(min_bmask_size?(bit_shift<bshift>(input)&meta_mask<min_bmask_size, dst_bmask_pos+dst_bmask_size-min_bmask_size, convert_t>::res):s_zero)
                       |(min_amask_size?(bit_shift<ashift>(input)&meta_mask<min_amask_size, dst_amask_pos+dst_amask_size-min_amask_size, convert_t>::res):s_default_alpha);
      pixel_writer<dst_bytespp, (e_texture_format_type)src_format_type, (e_texture_format_type)dst_format_type>::write(dst, &output);
      src+=src_bytespp;
      dst+=dst_bytespp;
    } while(dst!=end);
  }
}
//----------------------------------------------------------------------------
