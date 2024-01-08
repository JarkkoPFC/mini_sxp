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


#ifdef PFC_ENGINEOP_LIBTIFF
// check for libraries required by libtiff
#ifndef PFC_ENGINEOP_JPEGLIB
#error libtiff requires jpeglib library
#endif
#ifndef PFC_ENGINEOP_ZLIB
#error libtiff requires zlib library
#endif
#pragma comment(lib, PFC_STR(PFC_CAT2(libtiff_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
#pragma comment(lib, PFC_STR(PFC_CAT2(jpeglib_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
#pragma comment(lib, PFC_STR(PFC_CAT2(zlib_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
//----------------------------------------------------------------------------


//============================================================================
// texture_loader_tiff
//============================================================================
class texture_loader_tiff: public texture_loader::loader_base
{
public:
  // construction
  texture_loader_tiff(texture_loader&);
  //--------------------------------------------------------------------------

  // data loading
  virtual bool layer(texture_layer&) const;
  virtual void load_layer(void*, unsigned pitch_);
  virtual void skip_layer();
  //--------------------------------------------------------------------------

private:
  void operator=(const texture_loader_tiff&); // not implemented
  //--------------------------------------------------------------------------

  texture_loader &m_loader;
  bool m_has_layer;
};
//----------------------------------------------------------------------------

texture_loader_tiff::texture_loader_tiff(texture_loader &l_)
  :m_loader(l_)
{
  // read image properties
  bin_input_stream_base &stream=m_loader.stream();
  auto_stream_seek<bin_input_stream_base> aseek(stream);
  uint32_t tiff_id, ifd_offset;
  stream>>tiff_id>>ifd_offset;
  bool is_big_endian=tiff_id==0x2a004d4d;
  if(is_big_endian)
    ifd_offset=swap_bytes(ifd_offset);
  stream.skip(ifd_offset-8);
  uint16_t num_dir_entries;
  stream>>num_dir_entries;
  if(is_big_endian)
    num_dir_entries=swap_bytes(num_dir_entries);
  uint32_t width=0, height=0;
  while(num_dir_entries--)
  {
    // parse image file directory
    uint16_t id, field_type;
    uint32_t num_vals, val_offset;
    stream>>id>>field_type>>num_vals>>val_offset;
    if(is_big_endian)
      id=swap_bytes(id);

    // interpret tag
    switch(id)
    {
      case 0x0100: width=is_big_endian?swap_bytes(val_offset):val_offset; break;
      case 0x0101: height=is_big_endian?swap_bytes(val_offset):val_offset; break;
    }
  }
  PFC_CHECK_MSG(width && height, ("Invalid TIFF file\r\n"));

  // set texture type
  m_loader.set_source_type(textype_2d);
  m_loader.set_source_format(texfmt_a8r8g8b8);
  m_loader.set_source_size(width, height);
  m_has_layer=true;
}
//----------------------------------------------------------------------------

bool texture_loader_tiff::layer(texture_layer &l_) const
{
  // check for available layer
  l_=texture_layer();
  return m_has_layer;
}
//----

// libtiff declarations (tiffio.h not included due to name clashes)
typedef struct tiff TIFF;
typedef int32_t (*TIFFReadWriteProc)(void*, void*, int32_t);
typedef uint32_t (*TIFFSeekProc)(void*, uint32_t, int);
typedef int (*TIFFCloseProc)(void*);
typedef uint32_t (*TIFFSizeProc)(void*);
typedef int (*TIFFMapFileProc)(void*, void**, uint32_t*);
typedef void (*TIFFUnmapFileProc)(void*, void*, uint32_t);
typedef void (*TIFFErrorHandler)(const char*, const char*, va_list);
extern "C" TIFF *TIFFClientOpen(const char *filename_,
                                const char *mode_,
                                void *handle_,
                                TIFFReadWriteProc read_proc_,
                                TIFFReadWriteProc write_proc_,
                                TIFFSeekProc seek_proc_,
                                TIFFCloseProc close_proc_,
                                TIFFSizeProc size_proc_,
                                TIFFMapFileProc map_proc_,
                                TIFFUnmapFileProc unmap_proc_);
extern "C" int TIFFReadRGBAImageOriented(TIFF*, uint32_t, uint32_t, uint32_t*, int, int);
extern "C" void TIFFCleanup(TIFF*);
//----

void tiff_warning_handler(const char *module_, const char *fmt_, va_list args_)
{
  // output TIFF warning message
  char buf[256];
  vsnprintf(buf, sizeof(buf), fmt_, args_);
  PFC_WARN(buf);
}
//----

void tiff_error_handler(const char *module_, const char *fmt_, va_list args_)
{
  // output TIFF error message
  char buf[256];
  vsnprintf(buf, sizeof(buf), fmt_, args_);
  PFC_ERROR(buf);
}
//----

extern "C"
{
void *_TIFFmalloc(int32_t size_)
{
  uint32_t *p=(uint32_t*)PFC_MEM_ALLOC(size_+16);
  *p=size_;
  return p+4;
}

void *_TIFFrealloc(void *p_, int32_t size_)
{
  uint32_t *p=(uint32_t*)PFC_MEM_ALLOC(size_+16);
  *p=size_;
  if(p_)
  {
    mem_copy(p+4, p_, min(unsigned(size_), *((uint32_t*)p_-4)));
    PFC_MEM_FREE((uint8_t*)p_-16);
  }
  return p+4;
}
void _TIFFmemset(void *p_, int v_, int32_t size_) {::memset(p_, v_, size_);}
void _TIFFmemcpy(void *dst_, const void *src_, int32_t size_) {mem_copy(dst_, src_, size_);}
int _TIFFmemcmp(const void *p0_, const void *p1_, int32_t size_) {return mem_diff(p0_, p1_, size_);}
void _TIFFfree(void *p_) {PFC_MEM_FREE((char*)p_-16);}
TIFFErrorHandler _TIFFwarningHandler=tiff_warning_handler;
TIFFErrorHandler _TIFFerrorHandler=tiff_error_handler;
}
//----

void texture_loader_tiff::load_layer(void *p_, unsigned pitch_)
{
  // check for available layer
  if(!m_has_layer)
    return;

  struct file_wrapper
  {
    static int32_t read(void *handle_, void *data_, int32_t size_)
    {
      // read stream bytes
      bin_input_stream_base &stream=*(bin_input_stream_base*)handle_;
      return (unsigned)stream.read_bytes(data_, size_);
    }

    static int32_t write(void *handle_, void *data_, int32_t size_)
    {
      PFC_ERROR_NOT_IMPL();
      return 0;
    }

    static uint32_t seek(void *handle_, uint32_t pos_, int type_)
    {
      // seek the stream
      bin_input_stream_base &stream=*(bin_input_stream_base*)handle_;
      switch(type_)
      {
        case SEEK_SET: stream.seek(pos_); break;
        case SEEK_CUR: stream.skip(pos_); break;
        default: PFC_ERROR("Unsupported seek functionality\r\n");
      }
      return pos_;
    }

    static int close(void *handle_)
    {
      PFC_ERROR_NOT_IMPL();
      return 0;
    }

    static uint32_t size(void *handle_)
    {
      return 0;
    }
  };

  // read the image
  unsigned width=m_loader.width(), height=m_loader.height();
  owner_data image=PFC_MEM_ALLOC(width*height*4);
  TIFF *t=TIFFClientOpen("", "r", &m_loader.stream(), file_wrapper::read, file_wrapper::write, file_wrapper::seek, file_wrapper::close, file_wrapper::size, 0, 0);
  TIFFReadRGBAImageOriented(t, width, height, (uint32_t*)image.data, 1, 0);
  TIFFCleanup(t);

  // convert image to target format
  void *target=p_;
  const void *source=image.data;
  e_texture_format target_fmt=m_loader.target_format();
  for(unsigned y=0; y<height; ++y)
  {
    if(target_fmt!=texfmt_a8b8g8r8)
      convert_rgba_to_rgba(target, source, target_fmt, texfmt_a8b8g8r8, width);
    else
      memcpy(target, source, width*4);
    (uint8_t*&)target+=pitch_;
    (uint8_t*&)source+=width*4;
  }
  m_has_layer=false;
}
//----

void texture_loader_tiff::skip_layer()
{
  m_has_layer=false;
}
//----------------------------------------------------------------------------


//============================================================================
// get_texture_loader_tiff
//============================================================================
namespace pfc
{
  bool get_texture_loader_tiff(texture_loader::loader_variant_t &v_, texture_loader &l_)
  {
    // check for TIFF file format
    bin_input_stream_base &stream=l_.stream();
    uint32_t id;
    stream>>id;
    stream.rewind(4);
    if(id!=0x002a4949 && id!=0x2a004d4d)
      return false;

    // setup TIFF loader
    v_=texture_loader_tiff(l_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_tiff
//============================================================================
e_file_format_support pfc::texture_support_tiff()
{
  return filefmtsupport_read;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_tiff
//============================================================================
bool pfc::write_texture_tiff(bin_output_stream_base &s_, const texture_writer_params_tiff &params_, const void *src_, e_texture_format src_fmt_, unsigned width_, unsigned height_, ssize_t row_pitch_)
{
  return false;
}
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_LIBTIFF
//============================================================================
// get_texture_loader_tiff
//============================================================================
namespace pfc
{
  bool get_texture_loader_tiff(texture_loader::loader_variant_t&, texture_loader&)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------

//============================================================================
// texture_support_tiff
//============================================================================
e_file_format_support pfc::texture_support_tiff()
{
  return filefmtsupport_none;
}
//----------------------------------------------------------------------------

//============================================================================
// write_texture_tiff
//============================================================================
bool pfc::write_texture_tiff(bin_output_stream_base&, const texture_writer_params_tiff&, const void*, e_texture_format, unsigned, unsigned, ssize_t)
{
  return false;
}
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_LIBTIFF
