//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_POSIX_FSYS_H
#define PFC_CORE_POSIX_FSYS_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/fsys/fsys.h"
namespace pfc
{

// new
class posix_file_system;
//----------------------------------------------------------------------------


//============================================================================
// posix_file_system
//============================================================================
class posix_file_system: public file_system_base
{
public:
  // construction
  posix_file_system(bool set_active_=false, const char *system_root_dir_=0);
  void enable_temp_write(bool enable_=true);
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
  virtual bool make_directory(const char *dirname_, const char *path_=0);
  virtual bool delete_directory(const char *dirname_, const char *path_=0, bool delete_content_=false);
  virtual bool rename_directory(const char *dirname_, const char *new_dirname_, const char *path_=0);
  virtual owner_ptr<directory_monitor_base> create_directory_monitor(const char *dirname_, bool notify_subdirs_=false) const;
  //--------------------------------------------------------------------------

private:
  posix_file_system(const posix_file_system&); // not implemented
  void operator=(const posix_file_system&); // not implemented
  class input_stream;
  class output_stream;
  class iterator_impl;
  //--------------------------------------------------------------------------

  bool m_temp_write;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
