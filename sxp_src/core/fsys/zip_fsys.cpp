//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "zip_fsys.h"
#ifdef PFC_ENGINEOP_ZLIB
#include "sxp_extlibs/zlib/src/zlib.h"
#endif
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// external library dependencies
//============================================================================
// zlib
#ifdef PFC_ENGINEOP_ZLIB
#pragma comment(lib, PFC_STR(PFC_CAT2(zlib_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
#endif
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_ZLIB
//============================================================================
// zip_file_system::input_stream
//============================================================================
class zip_file_system::input_stream: public bin_input_stream_base
{
public:
  // construction
  input_stream(const owner_ref<bin_input_stream_base>&, const file_desc&);
  //--------------------------------------------------------------------------

private:
  virtual usize_t update_buffer_impl(void*, usize_t num_bytes_, bool exact_);
  virtual void rewind_impl();
  virtual void rewind_impl(usize_t num_bytes_);
  virtual void skip_impl();
  virtual void seek_impl(usize_t abs_pos_);
  //--------------------------------------------------------------------------

  void init_stream();
  static void *alloc(void*, unsigned items_, unsigned size_);
  static void free(void*, void *data_);
  //--------------------------------------------------------------------------

  enum {compressed_buffer_size=4096};
  enum {uncompressed_buffer_size=4096};
  owner_ref<bin_input_stream_base> m_stream;
  file_desc m_desc;
  z_stream m_state;
  uint8_t m_buffer_compressed[compressed_buffer_size];
  uint8_t m_buffer_uncompressed[uncompressed_buffer_size];
};
//----------------------------------------------------------------------------

zip_file_system::input_stream::input_stream(const owner_ref<bin_input_stream_base> &stream_, const file_desc &desc_)
  :m_stream(stream_)
  ,m_desc(desc_)
{
  init_stream();
  inflateInit2(&m_state, -MAX_WBITS);
}
//----------------------------------------------------------------------------

usize_t zip_file_system::input_stream::update_buffer_impl(void *p_, usize_t num_bytes_, bool exact_)
{
  usize_t num_total_bytes=0;
/*  if(num_bytes_>uncompressed_buffer_size)
  {
    // todo: optimize for direct read
    PFC_ERROR_NOT_IMPL();
  }
  else*/
  {
    // decompress data to a buffer
    uint8_t *input_buffer=m_buffer_uncompressed;
    usize_t input_buffer_size=uncompressed_buffer_size;
    usize_t bytes_to_copy=num_bytes_;
    bool is_stream_end=false;
    do
    {
      m_state.next_out=(Bytef*)m_buffer_uncompressed;
      m_state.avail_out=uncompressed_buffer_size;
      if(!m_state.avail_in)
      {
        // read more compressed data
        unsigned compressed_data_left=min<unsigned>(compressed_buffer_size, m_desc.compressed_size-m_state.total_in);
        m_stream->read_bytes(m_buffer_compressed, compressed_data_left);
        m_state.next_in=(Bytef*)m_buffer_compressed;
        m_state.avail_in=compressed_data_left;
      }

      // extract data with the appropriate method
      switch(m_desc.compression_type)
      {
        // no compression
        case comp_none:
        {
          input_buffer=m_buffer_compressed;
          input_buffer_size=compressed_buffer_size;
          m_state.avail_out=compressed_buffer_size-m_state.avail_in;
          m_state.avail_in=0;
          is_stream_end=m_state.avail_out!=0;
        } break;

        // deflated data
        case comp_deflated:
        {
          is_stream_end=inflate(&m_state, Z_NO_FLUSH)==Z_STREAM_END;
        } break;
      }

      // copy data from input buffer to the target
      usize_t num_bytes=min(bytes_to_copy, input_buffer_size-m_state.avail_out);
      PFC_CHECK_MSG(num_bytes, ("ZIP archive data is corrupted\r\n"));
      mem_copy(p_, input_buffer, num_bytes);
      (uint8_t*&)p_+=num_bytes;
      bytes_to_copy-=num_bytes;
      num_total_bytes+=num_bytes;

      // update stream state
      m_begin_pos+=usize_t(m_end-m_begin);
      m_is_first=m_is_first&&m_begin!=0;
      m_is_last=is_stream_end;
      m_begin=input_buffer;
      m_end=m_begin+input_buffer_size-m_state.avail_out;
      m_data=m_begin+num_bytes;
    } while(num_total_bytes<num_bytes_ && !is_stream_end);
  }

  // check for valid result
  PFC_CHECK_MSG(!exact_ || num_total_bytes==num_bytes_, ("Trying to the read beyond end of the file\r\n"));
  return num_total_bytes;
}
//----

void zip_file_system::input_stream::rewind_impl()
{
  init_stream();
  inflateReset(&m_state);
}
//----

void zip_file_system::input_stream::rewind_impl(usize_t num_bytes_)
{
  PFC_ASSERT(num_bytes_);
  switch(m_desc.compression_type)
  {
    // uncompressed stream rewind
    case comp_none:
    {
      // rewind the stream
      usize_t rewind=num_bytes_+usize_t(m_end-m_data);
      PFC_CHECK_MSG(m_stream->pos()>=m_desc.data_location+rewind, ("Trying to seek beyond the beginning of the file\r\n"));
      m_stream->rewind(rewind);
      m_is_first=false;
      m_is_last=false;
      m_begin_pos-=num_bytes_-usize_t(m_data-m_begin);
      m_begin=m_end=m_data=0;
    } break;

    // deflated stream rewind
    case comp_deflated:
    {
      /*todo*/
      PFC_ERROR_NOT_IMPL();
    } break;
  }
}
//----

void zip_file_system::input_stream::skip_impl()
{
  switch(m_desc.compression_type)
  {
    // uncompressed stream skip
    case comp_none:
    {
      // advance the stream
      usize_t skip=usize_t(m_data-m_end);
      PFC_CHECK_MSG(m_stream->pos()+skip<=m_desc.data_location+m_desc.uncompressed_size, ("Trying to seek beyond the end of the file\r\n"));
      m_stream->skip(skip);
      m_is_first=false;
      m_is_last=m_stream->pos()==m_desc.data_location+m_desc.uncompressed_size;
      m_begin_pos+=usize_t(m_data-m_begin);
      m_begin=m_end=m_data=0;
    } break;

    // deflated stream skip
    case comp_deflated:
    {
      /*todo*/
      PFC_ERROR_NOT_IMPL();
    } break;
  }
}
//----

void zip_file_system::input_stream::seek_impl(usize_t abs_pos_)
{
  switch(m_desc.compression_type)
  {
    // uncompressed stream seek
    case comp_none:
    {
      // set stream position
      PFC_CHECK_MSG(abs_pos_<=m_desc.uncompressed_size, ("Trying to seek beyond the end of the file\r\n"));
      m_stream->seek(m_desc.data_location+abs_pos_);
      m_is_first=abs_pos_==0;
      m_is_last=abs_pos_==m_desc.uncompressed_size;
      m_begin_pos=abs_pos_;
      m_begin=m_end=m_data=0;
    } break;

    // deflated stream seek
    case comp_deflated:
    {
      /*todo*/
      PFC_ERROR_NOT_IMPL();
    } break;
  }
}
//----------------------------------------------------------------------------

void zip_file_system::input_stream::init_stream()
{
  // read initial data to the compressed buffer
  bin_input_stream_base &stream=*m_stream;
  stream.seek(m_desc.data_location);
  unsigned compressed_data_left=min(unsigned(compressed_buffer_size), m_desc.compressed_size);
  stream.read_bytes(m_buffer_compressed, compressed_data_left);
  m_is_last=compressed_data_left==0;

  // initialize decompression
  m_state.next_in=(Bytef*)m_buffer_compressed;
  m_state.avail_in=compressed_data_left;
  m_state.next_out=(Bytef*)m_buffer_uncompressed;
  m_state.avail_out=uncompressed_buffer_size;
  m_state.zalloc=alloc;
  m_state.zfree=free;
  m_state.opaque=0;
}
//----

void *zip_file_system::input_stream::alloc(void*, unsigned items_, unsigned size_)
{
  return PFC_MEM_ALLOC(usize_t(items_)*usize_t(size_));
}
//----

void zip_file_system::input_stream::free(void*, void *data_)
{
  PFC_MEM_FREE(data_);
}
//----------------------------------------------------------------------------
#endif // PFC_ENGINEOP_ZLIB


//============================================================================
// zip_file_system::iterator_impl
//============================================================================
class zip_file_system::iterator_impl: public file_system_base::iterator_impl_base
{
public:
  // construction
  iterator_impl(const zip_file_system &fs_, file_system_base::iterator&, e_fsys_find, const char *dirname_, const char *path_);
  virtual ~iterator_impl();
  //------------------------------------------------------------------------

  // iteration
  virtual bool advance(file_system_base::iterator&);
  //------------------------------------------------------------------------

private:
  void operator=(const iterator_impl&); // not implemented
  //------------------------------------------------------------------------

  const e_fsys_find m_find_type;
};
//----------------------------------------------------------------------------

zip_file_system::iterator_impl::iterator_impl(const zip_file_system &fs_, file_system_base::iterator &it_, e_fsys_find find_, const char *dirname_, const char *path_)
  :m_find_type(find_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
}
//----

zip_file_system::iterator_impl::~iterator_impl()
{
}
//----------------------------------------------------------------------------

bool zip_file_system::iterator_impl::advance(file_system_base::iterator&)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----------------------------------------------------------------------------


//============================================================================
// zip_file_system
//============================================================================
zip_file_system::zip_file_system(file_system_base &fsys_, const char *zip_filename_, bool set_active_)
  :file_system_base(set_active_)
  ,m_fsys(fsys_)
{
  init_dictionary(&zip_filename_, 1);
}
//----

zip_file_system::zip_file_system(file_system_base &fsys_, const char *const*zip_filenames_, unsigned num_zip_filenames_, bool set_active_)
  :file_system_base(set_active_)
  ,m_fsys(fsys_)
{
  init_dictionary(zip_filenames_, num_zip_filenames_);
}
//----------------------------------------------------------------------------

file_system_base::iterator zip_file_system::find_first(e_fsys_find find_, const char *dirname_, const char *path_) const
{
  // find first file and construct iterator
  iterator it;
  PFC_NEW(iterator_impl)(*this, it, find_, dirname_, path_);
  return it;
}
//----------------------------------------------------------------------------

bool zip_file_system::exists(const char *filename_, const char *path_) const
{
  // search for the file from the file dictionary
  enum {fullname_size=1024};
  char fullname[fullname_size];
  make_full_filename(fullname, path_, filename_, fullname_size);
  return is_valid(m_dictionary.find(fullname));
}
//----

usize_t zip_file_system::file_size(const char *filename_, const char *path_) const
{
  // search for file and return uncompressed file size if found
  enum {fullname_size=1024};
  char fullname[fullname_size];
  make_full_filename(fullname, path_, filename_, fullname_size);
  dictionary::const_iterator it=m_dictionary.find(fullname);
  return is_valid(it)?it->uncompressed_size:0;
}
//----

bool zip_file_system::is_writable(const char *filename_, const char *path_) const
{
  return m_fsys.is_writable(filename_, path_);
}
//----

file_time zip_file_system::mod_time(const char *filename_, const char *path_) const
{
  // search for file and return file mod time if found
  enum {fullname_size=1024};
  char fullname[fullname_size];
  make_full_filename(fullname, path_, filename_, fullname_size);
  dictionary::const_iterator it=m_dictionary.find(fullname);
  if(!is_valid(it))
    return file_time();
  uint32_t msdos_time=it->msdos_time;
  return file_time(1980+((msdos_time>>25)&0x7f), (msdos_time>>21)&0xf, (msdos_time>>16)&0x1f, (msdos_time>>11)&0x1f, (msdos_time>>5)&0x3f, msdos_time&0x1f);
}
//----

owner_ptr<bin_input_stream_base> zip_file_system::open_read(const char *filename_, const char *path_, e_file_open_check fopen_check_) const
{
  // search for file and return stream if found
  enum {fullname_size=1024};
  char fullname[fullname_size];
  make_full_filename(fullname, path_, filename_, fullname_size);
  dictionary::const_iterator it=m_dictionary.find(fullname);
  if(!is_valid(it))
  {
    PFC_CHECK_MSG(fopen_check_!=fopencheck_abort, ("Unable to open file \"%s\" for reading\r\n", complete_path(filename_, path_).c_str()));
    if(fopen_check_==fopencheck_warn)
      PFC_WARNF("Unable to open file \"%s\" for reading\r\n", complete_path(filename_, path_).c_str());
    return 0;
  }
#ifdef PFC_ENGINEOP_ZLIB
  return PFC_NEW(input_stream)(m_fsys.open_read(m_zips[it->zip_index].name), *it);
#else
  PFC_ERROR("Unable to open zip file for reading without zlib library\r\n");
  return 0;
#endif
}
//----

owner_ptr<bin_output_stream_base> zip_file_system::open_write(const char *filename_, const char *path_, e_file_open_write_mode mode_, uint64_t fpos_, bool makedir_, e_file_open_check fopen_check_)
{
  return m_fsys.open_write(filename_, path_, mode_, fpos_, makedir_, fopen_check_);
}
//----

bool zip_file_system::delete_file(const char *filename_, const char *path_)
{
  return m_fsys.delete_file(filename_, path_);
}
//----

bool zip_file_system::rename_file(const char *filename_, const char *new_filename_, const char *path_, bool overwrite_existing_)
{
  return m_fsys.rename_file(filename_, new_filename_, path_, overwrite_existing_);
}
//----

void zip_file_system::touch_file(const char *filename_, const char *path_)
{
  m_fsys.touch_file(filename_, path_);
}
//----------------------------------------------------------------------------

void zip_file_system::set_directory(const char *dirname_)
{
  file_system_base::set_directory(dirname_);
}
//----

bool zip_file_system::make_directory(const char *dirname_, const char *path_)
{
  return m_fsys.make_directory(dirname_, path_);
}
//----

bool zip_file_system::delete_directory(const char *dirname_, const char *path_, bool delete_content_)
{
  return m_fsys.delete_directory(dirname_, path_, delete_content_);
}
//----

bool zip_file_system::rename_directory(const char *dirname_, const char *new_dirname_, const char *path_)
{
  return m_fsys.rename_directory(dirname_, new_dirname_, path_);
}
//----

owner_ptr<directory_monitor_base> zip_file_system::create_directory_monitor(const char *dirname_, bool notify_subdirs_) const
{
  return m_fsys.create_directory_monitor(dirname_, notify_subdirs_);
}
//----------------------------------------------------------------------------

void zip_file_system::make_full_filename(char *buffer_, const char *path_, const char *filename_, unsigned buffer_size_) const
{
  // build full filename
  PFC_ASSERT_PEDANTIC(filename_);
  unsigned dirlen=(unsigned)m_directory.size();
  mem_copy(buffer_, m_directory.data(), dirlen);
  if(path_)
  {
    dirlen+=(unsigned)str_copy(buffer_+dirlen, path_, buffer_size_-dirlen);
    if(buffer_[dirlen-1]!='/' && buffer_[dirlen-1]!='\\')
      buffer_[dirlen++]='/';
  }
  str_copy(buffer_+dirlen, filename_, buffer_size_-dirlen);

  // convert all backslashes to slashes and low-case the string
  str_replace(buffer_, '\\', '/');
  str_lower(buffer_);
}
//----

void zip_file_system::init_dictionary(const char *const*zip_filenames_, unsigned num_zip_filenames_)
{
  m_dictionary.clear();
  m_filenames.clear();
  m_zips.resize(num_zip_filenames_);
  mem_zero(m_zips.data(), sizeof(m_zips[0])*num_zip_filenames_);
  deque<file_desc> file_descs;
  unsigned total_zip_filenames_storage=0;
  for(unsigned zi=0; zi<num_zip_filenames_; ++zi)
  {
    // open zip archive
    owner_ptr<bin_input_stream_base> zip_file=m_fsys.open_read(zip_filenames_[zi]);
    if(!zip_file.data)
      continue;

    // parse zip dictionary
#if PFC_BIG_ENDIAN==0
    bin_input_stream_base &stream=*zip_file;
#else
    bin_input_stream_base &zip_stream=*zip_file;
    endian_input_stream stream(zip_stream);
#endif
    unsigned num_files=0;
    for(;;)
    {
      // read local file header signature
      uint32_t id;
      if(stream.read_bytes(&id, 4, false)!=4 || id!=PFC_TO_LITTLE_ENDIAN_U32(0x04034b50))
        break;

      // read rest of the local file header data
      uint16_t extract_ver, flags, compression_method;
      uint16_t last_mod_time, last_mod_date;
      uint32_t crc32;
      uint32_t compressed_size, uncompressed_size;
      uint16_t filename_len, extra_field_len;
      stream>>extract_ver>>flags>>compression_method;
      stream>>last_mod_time>>last_mod_date;
      stream>>crc32;
      stream>>compressed_size>>uncompressed_size;
      stream>>filename_len>>extra_field_len;

      // check for supported format
      e_compression_type comp_type=comp_none;
      bool is_supported=true;
      {
        // check for supported compression method
        switch(compression_method)
        {
          case 0: break;
          case 8: comp_type=comp_deflated; break;
          default: is_supported=false;
        }

        // check for encryption
        if(flags&1)
          is_supported=false;
      }

      if(is_supported)
      {
        // read filename
        unsigned filename_pos=(unsigned)m_filenames.size();
        m_filenames.insert_back(filename_len+1);
        stream.read_bytes(m_filenames.data()+filename_pos, filename_len);
        m_filenames[filename_pos+filename_len]=0;
        str_lower(m_filenames.data()+filename_pos);

        // add file description
        file_desc &desc=file_descs.push_back();
        desc.zip_index=uint16_t(zi);
        desc.compression_type=uint16_t(comp_type);
        desc.data_location=(unsigned)stream.pos()+extra_field_len;
        desc.compressed_size=compressed_size;
        desc.uncompressed_size=uncompressed_size;
        desc.msdos_time=(uint32_t(last_mod_date)<<16)|uint32_t(last_mod_time);
        ++num_files;
      }
      else
        stream.skip(filename_len);
      stream.skip(extra_field_len);

      // skip compressed data & optional data descriptor
      stream.skip(compressed_size);
      if(flags&8)
        stream.skip(12);
    }

    // update number of available files in zip archive
    m_zips[zi].num_files=num_files;
    if(num_files)
      total_zip_filenames_storage+=(unsigned)str_size(zip_filenames_[zi])+1;
  }

  // store zip filenames
  unsigned filenames_size=(unsigned)m_filenames.size();
  m_filenames.insert_back(total_zip_filenames_storage);
  char *zip_filename=m_filenames.data()+filenames_size;
  for(unsigned zi=0; zi<num_zip_filenames_; ++zi)
  {
    zip_storage &zs=m_zips[zi];
    const char *zfn=zip_filenames_[zi];
    if(zs.num_files)
    {
      unsigned namelen=(unsigned)str_size(zfn);
      mem_copy(zip_filename, zfn, namelen+1);
      m_zips[zi].name=zip_filename;
      zip_filename+=namelen+1;
    }
  }

  // generate file dictionary
  const char *filename=m_filenames.data();
  for(unsigned zi=0; zi<num_zip_filenames_; ++zi)
  {
    unsigned num_files=m_zips[zi].num_files;
    for(unsigned i=0; i<num_files; ++i)
    {
      unsigned name_len=(unsigned)str_size(filename);
      m_dictionary.insert(str_id(filename), file_descs[i]);
      filename+=name_len+1;
    }
  }
}
//----------------------------------------------------------------------------
