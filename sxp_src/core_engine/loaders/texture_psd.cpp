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


#ifdef PFC_ENGINEOP_PSD
//============================================================================
// helpers
//============================================================================
#define PSD_FOURCC(c0__, c1__, c2__, c3__) (uint32_t(c0__)<<24|uint32_t(c1__)<<16|uint32_t(c2__)<<8|uint32_t(c3__))
//----------------------------------------------------------------------------


//============================================================================
// psd_layer_channel
//============================================================================
struct psd_layer_channel
{
  // construction
  psd_layer_channel();
  //--------------------------------------------------------------------------

  int16_t channel_id;
  uint32_t range_src, range_dst;
  uint16_t compression_type;
  uint64_t data_size;
  owner_data data;
};
//----------------------------------------------------------------------------

psd_layer_channel::psd_layer_channel()
{
  // init properties
  channel_id=0;
  range_src=range_dst=0;
  compression_type=0;
  data_size=0;
}
//----------------------------------------------------------------------------


//============================================================================
// psd_layer
//============================================================================
struct psd_layer
{
  // construction
  psd_layer();
  //--------------------------------------------------------------------------

  // general layer info
  heap_str name;
  int32_t top, left, bottom, right;
  uint32_t blend_mode;
  uint8_t opacity;
  uint8_t clipping;
  uint8_t flags;
  uint32_t extra_data_length;
  array<psd_layer_channel> channels;
  // mask info
  int32_t mask_top, mask_left, mask_bottom, mask_right;
  uint8_t default_mask;
  uint8_t mask_flags, real_mask_flags;
  uint8_t mask_params;
  uint8_t user_mask_density, vector_mask_density;
  double user_mask_feather, vector_mask_feather;
  uint8_t real_user_mask_bg;
  // blending ranges
  uint32_t composite_gray_range_src;
  uint32_t composite_gray_range_dst;
  // channel image data
  owner_data img_data;
};
//----------------------------------------------------------------------------

psd_layer::psd_layer()
{
  // init properties
  top=left=bottom=right=0;
  blend_mode=0;
  opacity=0;
  clipping=0;
  flags=0;
  extra_data_length=0;
  mask_top=mask_left=mask_bottom=mask_right=0;
  default_mask=0;
  mask_flags=real_mask_flags=0;
  mask_params=0;
  user_mask_density=vector_mask_density=0;
  user_mask_feather=vector_mask_feather=0.0;
  real_user_mask_bg=0;
  composite_gray_range_src=composite_gray_range_dst=0;
}
//----------------------------------------------------------------------------


//============================================================================
// texture_loader_psd
//============================================================================
class texture_loader_psd: public texture_loader::loader_base
{
public:
  // construction
  texture_loader_psd(texture_loader&);
  //--------------------------------------------------------------------------

  // data loading
  virtual bool layer(texture_layer&) const;
  virtual void load_layer(void*, unsigned pitch_);
  virtual void skip_layer();
  //--------------------------------------------------------------------------

private:
  void operator=(const texture_loader_psd&); // not implemented
  //--------------------------------------------------------------------------

  // data readers
  friend class texture_loader;
  PFC_INLINE int channel_idx(int16_t channel_id_);
  uint64_t read_data_block_size(endian_input_stream&);
  void read_pascal_string(heap_str&, endian_input_stream&, unsigned padding_);
  bool decode_layer(void *dst_, unsigned layer_idx_, unsigned pitch_);
  //--------------------------------------------------------------------------

  // data block parsing
  bool parse_color_mode_data(endian_input_stream&);
  bool parse_image_resource_section(endian_input_stream&);
  bool parse_layer_and_mask_info(endian_input_stream&);
  bool parse_additional_layer_info(endian_input_stream&, usize_t end_pos_);
  bool parse_image_data(endian_input_stream&, unsigned width_, unsigned height_);
  //--------------------------------------------------------------------------

  texture_loader &m_loader;
  // image data
  array<psd_layer> m_layers;
  owner_data m_scanline_scratchpad;
  unsigned m_scanline_scratchpad_channel_size;
  uint8_t m_is_psb;
  uint8_t m_color_mode;
  uint8_t m_bpc;
  // current loading state
  bool m_has_layer;
  unsigned m_cur_slice;
};
//----------------------------------------------------------------------------

texture_loader_psd::texture_loader_psd(texture_loader &l_)
  :m_loader(l_)
{
  // read header
  endian_input_stream es(l_.stream());
  uint32_t file_id;
  uint16_t version;
  es>>file_id>>version;
  PFC_CHECK_MSG(file_id==PSD_FOURCC('8', 'B', 'P', 'S') && (version!=1 || version!=2),
                ("Invalid PSD file\r\n"));
  es.skip(6);
  m_is_psb=version==2;
  uint16_t num_channels, img_bpc, img_color_mode;
  uint32_t img_height, img_width;
  es>>num_channels>>img_height>>img_width>>img_bpc>>img_color_mode;
  m_color_mode=uint8_t(img_color_mode);
  m_bpc=uint8_t(img_bpc);

  // validate header data
  if(num_channels<1 || num_channels>56)
  {
    PFC_WARNF("PSD: Invalid number of channels (%i)\r\n", num_channels);
    return;
  }
  if(!img_width || !img_height || (!m_is_psb && (img_width>30000 || img_height>30000)) || (m_is_psb && (img_width>300000 || img_height>300000)))
  {
    PFC_WARNF("PSD: Invalid image dimensions (%i x %i)\r\n", img_width, img_height);
    return;
  }
  if(img_bpc!=1 && img_bpc!=8 && img_bpc!=16 && img_bpc!=32)
  {
    PFC_WARNF("PSD: Invalid image bit-per-channel (%i)\r\n", img_bpc);
    return;
  }
  if(img_color_mode==5 || img_color_mode==6 || img_color_mode>9)
  {
    PFC_WARNF("PSD: Invalid color mode (%i)\r\n", img_color_mode);
    return;
  }

  // read the rest of the file
  if(   !parse_color_mode_data(es)
     || !parse_image_resource_section(es)
     || !parse_layer_and_mask_info(es)
     || !parse_image_data(es, img_width, img_height))
    return;

  // setup loader parameters
  switch(img_color_mode)
  {
    // grayscale
    case 1:
    {
      switch(img_bpc)
      {
        case 8: m_loader.set_source_format(texfmt_r8); break;
        case 16: m_loader.set_source_format(texfmt_r16); break;
        case 32: m_loader.set_source_format(texfmt_r32); break;
        default: PFC_WARNF("PSD: Unsupported grayscale bits-per-channel (%i)\r\n", img_bpc); return;
      }
    } break;

    // RGB
    case 3:
    {
      switch(img_bpc)
      {
        case 8: m_loader.set_source_format(num_channels>3?texfmt_a8r8g8b8:texfmt_r8g8b8); break;
        case 16: m_loader.set_source_format(num_channels>3?texfmt_a16b16g16r16:texfmt_b16g16r16); break;
        case 32: m_loader.set_source_format(texfmt_a32b32g32r32); break;
        default: PFC_WARNF("PSD: Unsupported RGB bits-per-channel (%i)\r\n", img_bpc); return;
      }
    } break;

    // unsupported color modes
    case 0: PFC_WARN("PSD: Bitmap color mode not supported\r\n"); return;
    case 2: PFC_WARN("PSD: Indexed color mode not supported\r\n"); return;
    case 4: PFC_WARN("PSD: CMYK color mode not supported\r\n"); return;
    case 7: PFC_WARN("PSD: Multichannel color mode not supported\r\n"); return;
    case 8: PFC_WARN("PSD: Duotone color mode not supported\r\n"); return;
    case 9: PFC_WARN("PSD: Lab color mode not supported\r\n"); return;

    // unknown color mode
    default:
    {
      PFC_WARNF("PSD: Unknown color mode (%i)\r\n", img_color_mode);
      return;
    }
  }
  m_loader.set_source_size(img_width, img_height, unsigned(m_layers.size())); /*todo: we need a better way to define what's 2d/3d/cubemap/array texture. layer names? file info in PS? */
  m_loader.set_source_type(m_layers.size()>1?textype_3d:textype_2d); /*todo*/

  // init layer state
  m_scanline_scratchpad=PFC_MEM_ALLOC(4*m_scanline_scratchpad_channel_size);
  m_has_layer=true;
  m_cur_slice=0;
}
//----------------------------------------------------------------------------

bool texture_loader_psd::layer(texture_layer &l_) const
{
  l_=texture_layer();
  l_.volume_slice=m_cur_slice;
  return m_has_layer;
}
//----

void texture_loader_psd::load_layer(void *dst_, unsigned pitch_)
{
  // check for available layer and decode
  if(!m_has_layer)
    return;
//  if(!decode_layer(dst_, unsigned(m_layers.size())-m_cur_slice-1, pitch_))
  if(!decode_layer(dst_, m_cur_slice, pitch_))
    m_has_layer=false;
  skip_layer();
}
//----

void texture_loader_psd::skip_layer()
{
  // move to the next layer
  if(!m_has_layer)
    return;
  ++m_cur_slice;
  if(m_cur_slice==m_layers.size())
    m_has_layer=false;
}
//----------------------------------------------------------------------------

int texture_loader_psd::channel_idx(int16_t channel_id_)
{
  switch(m_color_mode)
  {
    case 1: return channel_id_==0?0:channel_id_==-1?3:-1;
    case 3: return unsigned(channel_id_)<3?channel_id_:channel_id_==-1?3:-1;
  }
  return -1;
}
//----

uint64_t texture_loader_psd::read_data_block_size(endian_input_stream &es_)
{
  // read data block size for PSD or PSB file
  uint64_t data_size=0;
  if(m_is_psb)
    es_>>data_size;
  else
  {
    uint32_t s;
    es_>>s;
    data_size=s;
  }
  return data_size;
}
//----

void texture_loader_psd::read_pascal_string(heap_str &s_, endian_input_stream &es_, unsigned padding_)
{
  // read Pascal string (8-bit length + string data with padding)
  uint8_t str_len;
  es_>>str_len;
  s_.resize(str_len);
  es_.read_bytes(s_.data(), str_len);
  unsigned padding=(-str_len-1)&(padding_-1);
  if(padding)
    es_.skip(padding);
}
//----

bool texture_loader_psd::decode_layer(void *dst_, unsigned layer_idx_, unsigned pitch_)
{
  // decode image a scanline at the time
  const psd_layer &l=m_layers[layer_idx_];
  (uint8_t*&)dst_+=max(0, l.left)*texfmt_bpp(m_loader.target_format())/8+pitch_*max(0, l.top);
  unsigned num_channels=unsigned(l.channels.size());
  unsigned layer_width=l.right-l.left;
  unsigned layer_height=l.bottom-l.top;
  unsigned num_scan_bytes=layer_width*m_bpc/8;
  const uint8_t *channel_data_poss[4]={0};
  for(unsigned y=0; y<layer_height; ++y)
  {
    // process all channels for the scanline
    mem_zero(m_scanline_scratchpad.data, 4*m_scanline_scratchpad_channel_size);
    for(unsigned ci=0; ci<num_channels; ++ci)
    {
      // check for proper channel type (RGBA) & ignore the rest
      const psd_layer_channel &chl=l.channels[ci];
      int chl_data_idx=channel_idx(chl.channel_id);
      if(chl_data_idx<0)
        continue;
      uint8_t *dst_data=(uint8_t*)m_scanline_scratchpad.data+chl_data_idx*m_scanline_scratchpad_channel_size;

      // switch to proper data decompression
      switch(chl.compression_type)
      {
        // process raw data
        case 0:
        {
          const uint8_t *chl_data=channel_data_poss[chl_data_idx];
          if(!chl_data)
            chl_data=channel_data_poss[chl_data_idx]=(const uint8_t*)chl.data.data;
          mem_copy(dst_data, chl_data, num_scan_bytes);
          channel_data_poss[chl_data_idx]=chl_data+num_scan_bytes;
        } break;

        // process RLE data
        case 1:
        {
          // access channel data for the scanline
          const uint8_t *chl_data=channel_data_poss[chl_data_idx];
          if(!chl_data)
            chl_data=channel_data_poss[chl_data_idx]=(const uint8_t*)chl.data.data+layer_height*(m_is_psb?4:2);

          // decode RLE data
          uint8_t *dst_end=dst_data+num_scan_bytes;
          while(dst_data<dst_end)
          {
            int8_t rle_size=*chl_data++;
            if(rle_size&0x80)
            {
              unsigned num_bytes=1-rle_size;
              if(dst_data+num_bytes>dst_end)
              {
                PFC_WARN("PSD: Image data is corrupted\r\n");
                return false;
              }
              mem_set(dst_data, *chl_data++, num_bytes);
              dst_data+=num_bytes;
            }
            else
            {
              unsigned num_bytes=1+rle_size;
              if(dst_data+num_bytes>dst_end)
              {
                PFC_WARN("PSD: Image data is corrupted\r\n");
                return false;
              }
              mem_copy(dst_data, chl_data, num_bytes);
              dst_data+=num_bytes;
              chl_data+=num_bytes;
            }
          }
          channel_data_poss[chl_data_idx]=chl_data;
        } break;

        // unsupported compression types
        case 2: PFC_WARN("PDF: Image decompression \"ZIP without prediction\" not implemented\r\n"); return false;
        case 3: PFC_WARN("PDF: Image decompression \"ZIP with prediction\" not implemented\r\n"); return false;
        default: PFC_WARNF("PDF: Unknown image compression type (%i)\r\n", chl.compression_type); return false;
      }
    }

    // check scanline bounds
    int dst_y=l.top+y;
    if(dst_y>=0 && dst_y<int(m_loader.height()))
    {
      // interleave the pixel data from scratchpad to the destination buffer
      unsigned src_xoffs=-min(0, l.left)*m_bpc/8;
      unsigned scan_width=m_loader.width()-clamp(l.left, 0, int(m_loader.width()));
      interleave_rgba_to_rgba((uint8_t*)dst_,
                              (uint8_t*)m_scanline_scratchpad.data+src_xoffs+0*m_scanline_scratchpad_channel_size,
                              (uint8_t*)m_scanline_scratchpad.data+src_xoffs+1*m_scanline_scratchpad_channel_size,
                              (uint8_t*)m_scanline_scratchpad.data+src_xoffs+2*m_scanline_scratchpad_channel_size,
                              (uint8_t*)m_scanline_scratchpad.data+src_xoffs+3*m_scanline_scratchpad_channel_size,
                              m_loader.target_format(),
                              m_loader.format(),
                              scan_width);
      (uint8_t*&)dst_+=pitch_;
    }
  }
  return true;
}
//----------------------------------------------------------------------------

bool texture_loader_psd::parse_color_mode_data(endian_input_stream &es_)
{
  // skip color mode data (used only for indexed and duotone color modes, which we don't currently support)
  uint32_t data_size;
  es_>>data_size;
  es_.skip(data_size);
  return true;
}
//----

bool texture_loader_psd::parse_image_resource_section(endian_input_stream &es_)
{
  // process all image resource blocks
  uint32_t data_size;
  es_>>data_size;
  usize_t end_pos=es_.pos()+data_size;
  heap_str res_name;
  while(es_.pos()<end_pos)
  {
    // read resource block properties
    uint32_t signature;
    uint16_t id;
    uint32_t res_data_size;
    es_>>signature>>id;
    if(signature!=PSD_FOURCC('8', 'B', 'I', 'M'))
    {
      PFC_WARN("PSD: Invalid resource block signature\r\n");
      return false;
    }
    read_pascal_string(res_name, es_, 2);
    es_>>res_data_size;

    // process resource block
    auto_stream_seek<endian_input_stream> ass(es_, (res_data_size+1)&-2);
    /*todo: process resource blocks that we are interested in*/
  }
  return true;
}
//----

bool texture_loader_psd::parse_layer_and_mask_info(endian_input_stream &es_)
{
  // read layer and mask info
  uint64_t layer_and_mask_info_size=read_data_block_size(es_);
  usize_t layer_and_mask_info_end=es_.pos()+usize_t(layer_and_mask_info_size);
  if(!layer_and_mask_info_size)
    return true;
  uint64_t layer_info_size=read_data_block_size(es_);
  usize_t layer_info_end=es_.pos()+usize_t(layer_info_size);
  int16_t layer_count=0;
  if(layer_info_size)
    es_>>layer_count;
  unsigned num_layers=abs(layer_count);
  m_layers.resize(num_layers);
  unsigned max_scan_width=0;
  for(unsigned li=0; li<num_layers; ++li)
  {
    // read layer content bounds and channel data
    psd_layer &l=m_layers[li];
    es_>>l.top>>l.left>>l.bottom>>l.right;
    max_scan_width=max(max_scan_width, unsigned(l.right-l.left));
    uint16_t num_channels;
    es_>>num_channels;
    l.channels.resize(num_channels);
    for(unsigned ci=0; ci<num_channels; ++ci)
    {
      psd_layer_channel &chl=l.channels[ci];
      es_>>chl.channel_id;
      chl.data_size=read_data_block_size(es_)-2;
    }

    // read blend mode
    uint32_t blend_signature;
    es_>>blend_signature;
    if(blend_signature!=PSD_FOURCC('8', 'B', 'I', 'M'))
    {
      PFC_WARN("PSD: Invalid blend mode signature\r\n");
      return false;
    }
    es_>>l.blend_mode;

    // read the rest of the layer properties
    es_>>l.opacity>>l.clipping>>l.flags;
    es_.skip(1);

    // read layer mask data
    uint32_t extra_data_size;
    es_>>extra_data_size;
    usize_t extra_data_end=es_.pos()+extra_data_size;
    uint32_t layer_mask_data_size;
    es_>>layer_mask_data_size;
    if(layer_mask_data_size)
    {
      es_>>l.mask_top>>l.mask_left>>l.mask_bottom>>l.mask_right;
      es_>>l.default_mask>>l.mask_flags;
      if(l.mask_flags&0x10)
      {
        es_>>l.mask_params;
        if(l.mask_params&1)
          es_>>l.user_mask_density;
        if(l.mask_params&2)
          es_>>l.user_mask_feather;
        if(l.mask_params&4)
          es_>>l.vector_mask_density;
        if(l.mask_params&8)
          es_>>l.vector_mask_feather;
      }
      if(layer_mask_data_size==20)
        es_.skip(2);
      
      // read remaining layer mask properties
      if(layer_mask_data_size>20)
      {
        es_>>l.real_mask_flags>>l.real_user_mask_bg;
        int32_t mask_top, mask_left, mask_bottom, mask_right;
        es_>>mask_top>>mask_left>>mask_bottom>>mask_right;
        if(mask_top!=l.mask_top || mask_left!=l.mask_left || mask_bottom!=l.mask_bottom || mask_right!=l.mask_right)
        {
          PFC_WARN("PSD: Invalid layer mask bounds\r\n");
          return false;
        }
      }
    }

    // read layer blending ranges
    {
      uint32_t layer_blending_ranges_data_size;
      es_>>layer_blending_ranges_data_size;
      auto_stream_seek<endian_input_stream> ass(es_, layer_blending_ranges_data_size);
      es_>>l.composite_gray_range_src>>l.composite_gray_range_dst;
      for(unsigned ci=0; ci<num_channels; ++ci)
      {
        psd_layer_channel &chl=l.channels[ci];
        es_>>chl.range_src>>chl.range_dst;
      }
    }

    // read layer name and additional info
    read_pascal_string(l.name, es_, 4);
    if(!parse_additional_layer_info(es_, extra_data_end))
      return false;
  }
  m_scanline_scratchpad_channel_size=max_scan_width*m_bpc/8;

  // read image data for layer channels
  for(unsigned li=0; li<num_layers; ++li)
  {
    psd_layer &l=m_layers[li];
    unsigned num_channels=unsigned(l.channels.size());
    for(unsigned ci=0; ci<num_channels; ++ci)
    {
      psd_layer_channel &chl=l.channels[ci];
      es_>>chl.compression_type;
      if(chl.compression_type>3)
      {
        PFC_WARNF("Invalid layer channel compression type (%i)\r\n", chl.compression_type);
      }
      chl.data=PFC_MEM_ALLOC(usize_t(chl.data_size));
      es_.read_bytes(chl.data.data, usize_t(chl.data_size));
    }
  }
  es_.skip(layer_info_end-es_.pos());

  // skip global layer mask info
  uint32_t global_layer_mask_info_size;
  es_>>global_layer_mask_info_size;
  es_.skip(global_layer_mask_info_size);

  // parse remaining layer infos
  if(!parse_additional_layer_info(es_, layer_and_mask_info_end))
    return false;
  return true;
}
//----

bool texture_loader_psd::parse_additional_layer_info(endian_input_stream &es_, usize_t end_pos_)
{
  while(es_.pos()<end_pos_-8)
  {
    uint32_t signature, fourcc;
    es_>>signature>>fourcc;
    if(signature!=PSD_FOURCC('8', 'B', 'I', 'M'))
    {
      PFC_WARN("PSD: Invalid additional layer info signature\r\n");
      return false;
    }

    // check for size field size
    bool is_size_64bit=false;
    if(m_is_psb)
      switch(fourcc)
      {
        // handle 64-bit data size
        case PSD_FOURCC('L', 'M', 's', 'k'):
        case PSD_FOURCC('L', 'r', '1', '6'):
        case PSD_FOURCC('L', 'r', '3', '2'):
        case PSD_FOURCC('L', 'a', 'y', 'r'):
        case PSD_FOURCC('M', 't', '1', '6'):
        case PSD_FOURCC('M', 't', '3', '2'):
        case PSD_FOURCC('M', 't', 'r', 'n'):
        case PSD_FOURCC('A', 'l', 'p', 'h'):
        case PSD_FOURCC('F', 'M', 's', 'k'):
        case PSD_FOURCC('l', 'n', 'k', '2'):
        case PSD_FOURCC('F', 'E', 'i', 'd'):
        case PSD_FOURCC('F', 'X', 'i', 'd'):
        case PSD_FOURCC('P', 'x', 'S', 'D'):
          is_size_64bit=true; break;
      }

    // get additional info chunk size
    uint64_t size=0;
    if(is_size_64bit)
      es_>>size;
    else
    {
      uint32_t s;
      es_>>s;
      size=s;
    }

    // process additional layer info
    auto_stream_seek<endian_input_stream> ass(es_, usize_t(size));
    /*todo: process layer info we are interested in*/
  }
  es_.skip(end_pos_-es_.pos());
  return true;
}
//----

bool texture_loader_psd::parse_image_data(endian_input_stream &es_, unsigned width_, unsigned height_)
{
  /*todo: add new layer if no layers*/
  uint16_t compression_type;
  es_>>compression_type;
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// get_texture_loader_psd
//============================================================================
namespace pfc
{
  bool get_texture_loader_psd(texture_loader::loader_variant_t &v_, texture_loader &l_)
  {
    // check for PSD file format
    bin_input_stream_base &stream=l_.stream();
    uint32_t file_id;
    uint16_t version;
    stream>>file_id>>version;
    stream.rewind(6);
    if(file_id!=PSD_FOURCC('S', 'P', 'B', '8') || (version!=0x0100 && version!=0x0200))
      return false;

    // setup PSD loader
    v_=texture_loader_psd(l_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_psd
//============================================================================
e_file_format_support pfc::texture_support_psd()
{
  return filefmtsupport_read;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_psd
//============================================================================
bool pfc::write_texture_psd(bin_output_stream_base &s_, const texture_writer_params_psd &params_, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_)
{
  return false;
}
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_PSD
//============================================================================
// get_texture_loader_psd
//============================================================================
namespace pfc
{
  bool get_texture_loader_psd(texture_loader::loader_variant_t&, texture_loader&)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_psd
//============================================================================
e_file_format_support pfc::texture_support_psd()
{
  return filefmtsupport_none;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_psd
//============================================================================
bool pfc::write_texture_psd(bin_output_stream_base&, const texture_writer_params_psd&, const void*, e_texture_format, unsigned, unsigned, ssize_t)
{
  return false;
}
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_PSD
