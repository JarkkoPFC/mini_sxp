//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "posix_fsys.h"
#if !defined(PFC_PLATFORM_WIN32) && !defined(PFC_PLATFORM_WIN64)
#include <dirent.h>
#include <fnmatch.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// Win32/64 implementation for POSIX directory iteration
//============================================================================
#if defined(PFC_PLATFORM_WIN32) || defined(PFC_PLATFORM_WIN64)
#include <io.h>
#include <direct.h>
struct dirent
{
  const char *d_name;
};

struct DIR
{
  intptr_t handle;
  _finddata_t data;
  bool first;
  dirent entry;
};

static DIR *opendir(const char *directory_)
{
  pfc::filepath_str search=directory_;
  if(search.size() && search.back()!='/')
    search+='/';
  search+='*';

  DIR *dir=PFC_NEW(DIR);
  dir->handle=_findfirst(search.c_str(), &dir->data);
  if(dir->handle==-1)
  {
    PFC_DELETE(dir);
    return 0;
  }
  dir->first=true;
  return dir;
}
//----

static dirent *readdir(DIR *dir_)
{
  if(!dir_->first && _findnext(dir_->handle, &dir_->data)!=0)
    return 0;
  dir_->first=false;
  dir_->entry.d_name=dir_->data.name;
  return &dir_->entry;
}
//----

static int closedir(DIR *dir_)
{
  _findclose(dir_->handle);
  PFC_DELETE(dir_);
  return 0;
}
//----

static int fnmatch(const char *pattern_, const char *name_, int)
{
  return pfc::str_eq_wildcard(name_, pattern_)?0:1;
}
#ifdef PFC_COMPILER_MSVC
#define S_ISDIR(mode__) ((mode__&_S_IFDIR)!=0)
#endif
#endif
//----------------------------------------------------------------------------


//============================================================================
// posix_file_system::input_stream
//============================================================================
class posix_file_system::input_stream: public bin_input_stream_base
{
public:
  // construction
  input_stream(FILE*, const char *filename_);
  virtual ~input_stream();
  //--------------------------------------------------------------------------

private:
  virtual usize_t update_buffer_impl(void*, usize_t num_bytes_, bool exact_);
  virtual void rewind_impl();
  virtual void rewind_impl(usize_t num_bytes_);
  virtual void skip_impl();
  virtual void seek_impl(usize_t abs_pos_);
  //--------------------------------------------------------------------------

  enum {buffer_size=4096};
  FILE *const m_handle;
  usize_t m_size;
  usize_t m_fptr_pos;
  uint8_t m_buffer[buffer_size];
};
//----------------------------------------------------------------------------

posix_file_system::input_stream::input_stream(FILE *handle_, const char *filename_)
  :m_handle(handle_)
{
  struct stat attr;
  stat(filename_, &attr);
  m_size=attr.st_size;
  m_fptr_pos=0;
  m_is_last=m_size==0;
}
//----

posix_file_system::input_stream::~input_stream()
{
  fclose(m_handle);
}
//----------------------------------------------------------------------------

usize_t posix_file_system::input_stream::update_buffer_impl(void *p_, usize_t num_bytes_, bool exact_)
{
  // read the rest of the data
  if(num_bytes_>=buffer_size)
  {
    // read data directly to the pointer
    usize_t num_read=fread(p_, 1, num_bytes_, m_handle);
    PFC_CHECK_MSG(!exact_ || num_read==num_bytes_, ("Trying to read beyond the end of the file\r\n"));
    m_fptr_pos+=num_read;
    m_is_first=false;
    m_is_last=m_fptr_pos==m_size;
    m_begin_pos+=usize_t(m_end-m_begin)+num_read;
    m_begin=m_end=m_data=0;
    return num_read;
  }

  // read data to buffer and copy it to the pointer
  usize_t num_read=fread(m_buffer, 1, buffer_size, m_handle);
  PFC_CHECK_MSG(!exact_ || num_read>=num_bytes_, ("Trying to read beyond the end of the file\r\n"));
  usize_t num_copied=min(num_read, num_bytes_);
  mem_copy(p_, m_buffer, num_copied);
  m_fptr_pos+=num_read;
  m_is_first=m_is_first&&m_begin!=0;
  m_is_last=m_size==m_fptr_pos;
  m_begin_pos+=usize_t(m_end-m_begin);
  m_begin=m_buffer;
  m_end=m_buffer+num_read;
  m_data=m_begin+num_copied;
  return num_copied;
}
//----

void posix_file_system::input_stream::rewind_impl()
{
  // seek to the beginning of the file
  PFC_ASSERT(m_is_first==false);
  PFC_VERIFY_MSG(fseek(m_handle, 0, SEEK_SET)==0, ("Failed to set the file pointer to the beginning of the file\r\n"));
  m_fptr_pos=0;
  m_is_first=true;
  m_is_last=false;
  m_begin_pos=0;
  m_begin=m_end=m_data=0;
}
//----

void posix_file_system::input_stream::rewind_impl(usize_t num_bytes_)
{
  // rewind file stream
  PFC_ASSERT(num_bytes_);
  usize_t rewind=num_bytes_+usize_t(m_end-m_data);
  PFC_VERIFY_MSG(fseek(m_handle, -long(rewind), SEEK_CUR)==0, ("Trying to seek beyond beginning of the file\r\n"));
  m_fptr_pos-=rewind;
  m_begin_pos-=num_bytes_-usize_t(m_data-m_begin);
  m_is_first=m_begin_pos==0;
  m_is_last=false;
  m_begin=m_end=m_data=0;
}
//----

void posix_file_system::input_stream::skip_impl()
{
  // advance file stream
  usize_t skip=usize_t(m_data-m_end);
  m_fptr_pos+=skip;
  PFC_VERIFY_MSG(fseek(m_handle, (unsigned)skip, SEEK_CUR)==0, ("Trying to seek beyond end of the file\r\n"));
  m_is_first=false;
  m_is_last=m_fptr_pos==m_size;
  m_begin_pos+=usize_t(m_data-m_begin);
  m_begin=m_end=m_data=0;
}
//----

void posix_file_system::input_stream::seek_impl(usize_t abs_pos_)
{
  // set file pointer position
  PFC_VERIFY_MSG(fseek(m_handle, (unsigned)abs_pos_, SEEK_SET)==0, ("Trying to seek beyond end of the file\r\n"));
  m_fptr_pos=abs_pos_;
  m_is_first=abs_pos_==0;
  m_is_last=m_fptr_pos==m_size;
  m_begin_pos=abs_pos_;
  m_begin=m_end=m_data=0;
}
//----------------------------------------------------------------------------


//============================================================================
// posix_file_system::output_stream
//============================================================================
class posix_file_system::output_stream: public bin_output_stream_base
{
public:
  // construction
  output_stream(FILE*, bool use_temp_, const filepath_str &filepath_);
  virtual ~output_stream();
  //------------------------------------------------------------------------

private:
  virtual void flush_buffer_impl(const void*, usize_t num_bytes_);
  //------------------------------------------------------------------------

  enum {buffer_size=4096};
  FILE *const m_handle;
  const bool m_use_temp;
  filepath_str m_filepath;
  uint8_t m_buffer[buffer_size];
};
//----------------------------------------------------------------------------

posix_file_system::output_stream::output_stream(FILE *handle_, bool use_temp_, const filepath_str &filepath_)
  :m_handle(handle_)
  ,m_use_temp(use_temp_)
  ,m_filepath(filepath_)
{
  m_begin_pos=ftell(handle_);
}
//----

posix_file_system::output_stream::~output_stream()
{
  flush_buffer_impl(0, 0);
  fclose(m_handle);
  if(m_use_temp)
  {
    // construct temp filename and rename file to target filename
    stack_str1024 fpath_temp;
    build_temp_filepath(fpath_temp, m_filepath);
    remove(m_filepath.c_str());
    PFC_VERIFY_MSG(rename(fpath_temp.c_str(), m_filepath.c_str())==0,
                   ("Unable to rename file \"%s\" to \"%s\"\r\n", fpath_temp.c_str(), m_filepath.c_str()));
  }
}
//----------------------------------------------------------------------------

void posix_file_system::output_stream::flush_buffer_impl(const void *p_, usize_t num_bytes_)
{
  // flush content of the data written to the buffer and handle remaining data
  usize_t num_write=fwrite(m_buffer, 1, usize_t(m_data-m_begin), m_handle);
  PFC_VERIFY_MSG(num_write==usize_t(m_data-m_begin), ("Failed to write all requested data to the file\r\n"));
  if(num_bytes_>=buffer_size)
  {
    // write data directly to the file
    usize_t num_write=fwrite(p_, 1, num_bytes_, m_handle);
    PFC_VERIFY_MSG(num_write==num_bytes_, ("Failed to write all requested data to the file\r\n"));
    m_begin_pos+=usize_t(m_data-m_begin)+num_write;
    m_begin=m_end=m_data=0;
  }
  else
  {
    // copy data to the buffer
    mem_copy(m_buffer, p_, num_bytes_);
    m_begin_pos+=usize_t(m_data-m_begin);
    m_begin=m_buffer;
    m_end=m_buffer+buffer_size;
    m_data=m_begin+num_bytes_;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// posix_file_system
//============================================================================
class posix_file_system::iterator_impl: public file_system_base::iterator_impl_base
{
public:
  // construction
  iterator_impl(iterator&, e_fsys_find, DIR*, const char*, const char*, const char*, bool);
  virtual ~iterator_impl();
  //--------------------------------------------------------------------------

  // iteration
  virtual bool advance(iterator&);
  //--------------------------------------------------------------------------

private:
  void operator=(const iterator_impl&); // not implemented
  //--------------------------------------------------------------------------

  const e_fsys_find m_find_type;
  DIR *const m_dir;
  const filepath_str m_directory;
  const heap_str m_pattern;
  heap_str m_name;
};
//----------------------------------------------------------------------------

static bool find_next_posix_entry(DIR *dir_, const char *directory_, const char *pattern_, e_fsys_find find_,
                                  heap_str &name_, bool &is_dir_)
{
  // search for the next matching directory entry
  for(dirent *entry=readdir(dir_); entry; entry=readdir(dir_))
  {
    // skip special entries and filter by the requested filename pattern
    const char *name=entry->d_name;
    if(   (name[0]=='.' && name[1]==0)
       || (name[0]=='.' && name[1]=='.' && name[2]==0)
       || fnmatch(pattern_, name, 0)!=0)
      continue;

    // determine whether the entry is a directory or a file
    filepath_str filepath=directory_;
    if(filepath.size() && filepath.back()!='/')
      filepath+='/';
    filepath+=name;
    struct stat attr;
    if(stat(filepath.c_str(), &attr)!=0)
      continue;
    is_dir_=S_ISDIR(attr.st_mode)!=0;

    // filter by the requested entry type
    if(   (find_==fsysfind_dirs && !is_dir_)
       || (find_==fsysfind_files && is_dir_))
      continue;

    name_=name;
    return true;
  }
  return false;
}
//----------------------------------------------------------------------------

posix_file_system::iterator_impl::iterator_impl(iterator &it_, e_fsys_find find_, DIR *dir_, const char *directory_,
                                                const char *pattern_, const char *name_, bool is_dir_)
  :m_find_type(find_)
  ,m_dir(dir_)
  ,m_directory(directory_)
  ,m_pattern(pattern_)
  ,m_name(name_)
{
  init_iterator(it_);
  update(it_, m_name.c_str(), is_dir_, !is_dir_);
}
//----

posix_file_system::iterator_impl::~iterator_impl()
{
  closedir(m_dir);
}
//----

bool posix_file_system::iterator_impl::advance(iterator &it_)
{
  bool is_dir;
  if(!find_next_posix_entry(m_dir, m_directory.c_str(), m_pattern.c_str(), m_find_type, m_name, is_dir))
    return false;
  update(it_, m_name.c_str(), is_dir, !is_dir);
  return true;
}
//----------------------------------------------------------------------------

posix_file_system::posix_file_system(bool set_active_, const char *system_root_dir_)
  :file_system_base(set_active_)
{
  m_temp_write=true;
  set_system_root_directory(system_root_dir_);
}
//----

void posix_file_system::enable_temp_write(bool enable_)
{
  m_temp_write=enable_;
}
//----------------------------------------------------------------------------

file_system_base::iterator posix_file_system::find_first(e_fsys_find find_, const char *filename_, const char *path_) const
{
  // split the complete search path into directory and filename pattern
  PFC_ASSERT(filename_);
  filepath_str search=complete_path(filename_, path_);
  str_replace(search.c_str(), '\\', '/');
  const char *pattern=get_filename(search.c_str());
  filepath_str directory;
  if(pattern==search.c_str())
    directory=".";
  else
  {
    usize_t directory_size=usize_t(pattern-search.c_str())-1;
    directory.set(search.c_str(), directory_size?directory_size:1);
    if(!directory_size)
      directory[0]='/';
  }

  // open the directory and find its first matching entry
  DIR *dir=opendir(directory.c_str());
  if(!dir)
    return iterator();
  heap_str name;
  bool is_dir;
  if(!find_next_posix_entry(dir, directory.c_str(), pattern, find_, name, is_dir))
  {
    closedir(dir);
    return iterator();
  }

  iterator it;
  PFC_NEW(iterator_impl)(it, find_, dir, directory.c_str(), pattern, name.c_str(), is_dir);
  return it;
}
//----------------------------------------------------------------------------

bool posix_file_system::exists(const char *filename_, const char *path_) const
{
  // check if the file exists
  PFC_ASSERT(filename_);
  filepath_str fn=complete_path(filename_, path_);
  struct stat attr;
  return stat(fn.c_str(), &attr)==0;
}
//----

usize_t posix_file_system::file_size(const char *filename_, const char *path_) const
{
  // get size of the file
  PFC_ASSERT(filename_);
  filepath_str fn=complete_path(filename_, path_);
  struct stat attr;
  return stat(fn.c_str(), &attr)?0:attr.st_size;
}
//----

bool posix_file_system::is_writable(const char *filename_, const char *path_) const
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

file_time posix_file_system::mod_time(const char *filename_, const char *path_) const
{
  // get file attributes
  PFC_ASSERT(filename_);
  filepath_str fn=complete_path(filename_, path_);
  struct stat attr;
  if(stat(fn.c_str(), &attr))
    return file_time();

  // get file date & time
  struct tm *t=localtime(&attr.st_mtime);
  return file_time(uint16_t(t->tm_year)+1900, uint8_t(t->tm_mon)+1, uint8_t(t->tm_mday), uint8_t(t->tm_hour), uint8_t(t->tm_min), uint8_t(t->tm_sec));
}
//----

owner_ptr<bin_input_stream_base> posix_file_system::open_read(const char *filename_, const char *path_, e_file_open_check fopen_check_) const
{
  // open file for reading
  PFC_ASSERT(filename_);
  filepath_str fn=complete_path(filename_, path_);
  FILE *handle=fopen(fn.c_str(), "rb");
  if(!handle)
  {
    PFC_CHECK_MSG(fopen_check_!=fopencheck_abort, ("Unable to open file \"%s\" for reading\r\n", complete_path(filename_, path_).c_str()));
    if(fopen_check_==fopencheck_warn)
      PFC_WARNF("Unable to open file \"%s\" for reading\r\n", complete_path(filename_, path_).c_str());
  }
  return handle?PFC_NEW(input_stream)(handle, fn.c_str()):0;
}
//----

owner_ptr<bin_output_stream_base> posix_file_system::open_write(const char *filename_, const char *path_, e_file_open_write_mode mode_, uint64_t fpos_, bool makedir_, e_file_open_check fopen_check_)
{
  // setup file path and target file path
  PFC_ASSERT(filename_);
  filepath_str fpath=complete_path(filename_, path_);
  filepath_str fpath_target;
  bool temp_write=m_temp_write && (mode_==fopenwritemode_clear || !exists(filename_, path_));
  if(temp_write)
    build_temp_filepath(fpath_target, fpath);
  else
    fpath_target=fpath;

  // open file for writing
  if(makedir_)
  {
    filepath_str fp=filename_;
    const char *fname=split_filepath(fp.c_str());
    make_directory(fp.c_str()!=fname?fp.c_str():"", path_);
  }
  FILE *handle=fopen(fpath_target.c_str(), mode_==fopenwritemode_clear?"wb":fpos_==uint64_t(-1)?"ab":"rb+");
  if(!handle)
  {
    PFC_CHECK_MSG(fopen_check_!=fopencheck_abort, ("Unable to open file \"%s\" for writing\r\n", complete_path(filename_, path_).c_str()));
    if(fopen_check_==fopencheck_warn)
      PFC_WARNF("Unable to open file \"%s\" for writing\r\n", complete_path(filename_, path_).c_str());
  }
  if(fpos_ && fpos_!=uint64_t(-1))
    fseek(handle, long(fpos_), SEEK_SET);
  return handle?PFC_NEW(output_stream)(handle, temp_write, fpath):0;
}
//----

bool posix_file_system::delete_file(const char *filename_, const char *path_)
{
  // delete file
  PFC_ASSERT(filename_);
  filepath_str fpath=complete_path(filename_, path_);
  return remove(fpath.c_str())==0;
}
//----

bool posix_file_system::rename_file(const char *filename_, const char *new_filename_, const char *path_, bool overwrite_existing_)
{
  // rename given filename to the new filename
  PFC_ASSERT(filename_);
  PFC_ASSERT(new_filename_);
  filepath_str fpath=complete_path(filename_, path_);
  filepath_str fpath_new=complete_path(new_filename_, path_);
  if(overwrite_existing_)
    PFC_CHECK_MSG(remove(fpath.c_str())==0, ("Unable to remove existing file \"%s\"\r\n", fpath.c_str()));
  return rename(fpath.c_str(), fpath_new.c_str())==0;
}
//----

void posix_file_system::touch_file(const char *filename_, const char *path_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
}
//----------------------------------------------------------------------------

bool posix_file_system::make_directory(const char *dirname_, const char *path_)
{
  // setup full directory name and get attributes
  PFC_ASSERT(dirname_);
  filepath_str dn=complete_path(dirname_, path_);
  if(!dn.size())
    return true;
  struct stat attr;
  if(stat(dn.c_str(), &attr) && (!is_absolute_filepath(dn.c_str()) || str_find(dn.c_str(), "/\\")))
  {
    // strip off potential trailing slash
    filepath_str parent_dn=dn;
    unsigned parent_dnsize=(unsigned)parent_dn.size();
    if(parent_dn[parent_dnsize-1]=='/')
    {
      parent_dn[--parent_dnsize]=0;
      dn.resize(parent_dnsize);
    }

    // try to create parent directories backwards starting from the target dir
    while(parent_dnsize && PFC_MKDIR(parent_dn.c_str()))
    {
      while(--parent_dnsize && parent_dn[parent_dnsize]!='/');
      parent_dn[parent_dnsize]=0;
    }
    if(!parent_dnsize)
    {
      PFC_ERRORF("Unable to create directory \"%s\"\r\n", dn.c_str());
      return false;
    }

    // try to create directories forward from the first successfully created parent dir
    unsigned dnsize=(unsigned)dn.size();
    while(parent_dnsize<dnsize)
    {
      parent_dn[parent_dnsize]='/';
      while(++parent_dnsize<dnsize && parent_dn[parent_dnsize]);
      if(PFC_MKDIR(parent_dn.c_str()))
      {
        PFC_ERRORF("Unable to create directory \"%s\"\r\n", dn.c_str());
        return false;
      }
    }
  }
  else
  {
    // verify that the existing file isn't a directory
    if(!S_ISDIR(attr.st_mode))
    {
      PFC_ERRORF("Unable to create directory \"%s\" because a file with that name already exists\r\n", dn.c_str());
      return false;
    }
  }

  // directory successfully created
  return true;
}
//----

bool posix_file_system::delete_directory(const char *dirname_, const char *path_, bool delete_content_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

bool posix_file_system::rename_directory(const char *dirname_, const char *new_dirname_, const char *path_)
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return false;
}
//----

owner_ptr<directory_monitor_base> posix_file_system::create_directory_monitor(const char *dirname_, bool notify_subdirs_) const
{
  /*todo*/
  PFC_ERROR_NOT_IMPL();
  return 0;
}
//----------------------------------------------------------------------------
