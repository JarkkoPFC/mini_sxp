//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_ZIP_FSYS_H
#define PFC_CORE_ZIP_FSYS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "fsys.h"
#include "sxp_src/core/containers.h"
namespace pfc
{

// new
class zip_file_system;
void write_zip(bin_output_stream_base&, const void *data_, usize_t data_size_, const char *filename_);
//----------------------------------------------------------------------------


//============================================================================
// zip_file_system
//============================================================================
class zip_file_system: public file_system_base
{
public:
  // construction
  zip_file_system(file_system_base&, const char *zip_filename_, bool set_active_=false);
  zip_file_system(file_system_base&, const char *const*zip_filenames_, unsigned num_zip_filenames_, bool set_active_=false);
  //--------------------------------------------------------------------------

  // generic operations
  virtual iterator find_first(e_fsys_find, const char *dirname_, const char *path_=0) const;
  //--------------------------------------------------------------------------

  // file operations
  virtual bool exists(const char *filename_, const char *path_=0) const;
  virtual usize_t file_size(const char *filename_, const char *path_=0) const;
  virtual bool is_writable(const char *filename_, const char *path_=0) const;
  virtual file_time mod_time(const char *filename_, const char *path_=0) const;
  virtual owner_ptr<bin_input_stream_base> open_read(const char *filename_, const char *path_=0, e_file_open_check=fopencheck_warn) const;
  virtual owner_ptr<bin_output_stream_base> open_write(const char *filename_, const char *path_=0, e_file_open_write_mode=fopenwritemode_clear, uint64_t fpos_=uint64_t(-1), bool makedir_=true, e_file_open_check=fopencheck_warn);
  virtual bool delete_file(const char *filename_, const char *path_=0);
  virtual bool rename_file(const char *filename_, const char *new_filename_, const char *path_=0, bool overwrite_existing_=false);
  virtual void touch_file(const char *filename_, const char *path_=0);
  //--------------------------------------------------------------------------

  // directory operations
  virtual void set_directory(const char *dirname_);
  virtual bool make_directory(const char *dirname_, const char *path_=0);
  virtual bool delete_directory(const char *dirname_, const char *path_=0, bool delete_content_=false);
  virtual bool rename_directory(const char *dirname_, const char *new_dirname_, const char *path_=0);
  virtual owner_ptr<directory_monitor_base> create_directory_monitor(const char *dirname_, bool notify_subdirs_=false) const;
  //--------------------------------------------------------------------------

private:
  class input_stream;
  class output_stream;
  class iterator_impl;
  zip_file_system(const zip_file_system&); // not implemented
  void operator=(const zip_file_system&); // not implemented
  void make_full_filename(char *buffer_, const char *path_, const char *filename_, unsigned buffer_size_) const;
  void init_dictionary(const char *const*zip_filenames_, unsigned num_filenames_);
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_compression_type
  //==========================================================================
  enum e_compression_type
  {
    comp_none,
    comp_deflated
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // zip_storage
  //==========================================================================
  struct zip_storage
  {
    const char *name;
    unsigned num_files;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // file_desc
  //==========================================================================
  struct file_desc
  {
    uint16_t zip_index;
    uint16_t compression_type;
    uint32_t data_location;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint32_t msdos_time; 
  };
  //--------------------------------------------------------------------------

  typedef hash_map<str_id, file_desc> dictionary;
  file_system_base &m_fsys;
  array<zip_storage> m_zips;
  dictionary m_dictionary;
  array<char> m_filenames;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
