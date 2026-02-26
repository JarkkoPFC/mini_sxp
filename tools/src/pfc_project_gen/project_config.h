//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_PROJGEN_PROJECT_CONFIG_H
#define PFC_PROJGEN_PROJECT_CONFIG_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/containers.h"
#include "sxp_src/core/str.h"
#include "sxp_src/core/functor.h"
namespace pfc
{
class bin_input_stream_base;
struct xml_attribute;

// new
struct project_build_platform;
struct project_build_type;
struct project_build_config;
struct project_file_config;
struct project_file;
class project_config;
bool replace_attrib(heap_str &res_, const heap_str &str_, const heap_str &attrib_name_, const heap_str &attrib_value_);
void replace_attribs(heap_str &res_, const heap_str &str_, const list<xml_attribute>&, const xml_attribute *skip_attrib_=0);
void replace_attribs(list<xml_attribute> &dst_, const list<xml_attribute> &src_);
void final_replace_attribs(const project_config&, heap_str &res_, const heap_str &str_, const list<xml_attribute>&);
void merge_attrib(list<xml_attribute> &dst_, const xml_attribute &attrib_);
void merge_attrib_lists(list<xml_attribute> &dst_, const list<xml_attribute> &src_);
bool load_text_file(heap_str&, const char *filename_, const char *path_=0);
void remove_trailing_linefeed(heap_str&);
void save_project_file(const char *filename_, const project_config&, const heap_str&);
//----------------------------------------------------------------------------


//============================================================================
// project_build_type
//============================================================================
struct project_build_type
{
  heap_str name;
  list<xml_attribute> attribs;
};
//----------------------------------------------------------------------------


//============================================================================
// project_build_platform
//============================================================================
struct project_build_platform
{
  heap_str name;
  list<xml_attribute> attribs;
};
//----------------------------------------------------------------------------


//============================================================================
// project_build_config
//============================================================================
struct project_build_config
{
  unsigned config_index;
  heap_str target_build, target_platform;
  list<xml_attribute> attribs;
};
//----------------------------------------------------------------------------


//============================================================================
// project_file_config
//============================================================================
struct project_file_config
{
  // construction
  project_file_config();
  //--------------------------------------------------------------------------

  heap_str builds;
  heap_str platforms;
  heap_str directory;
  heap_str files;
  heap_str template_filename;
  heap_str file_group;
  bool recursive;
  bool exclude;
  list<xml_attribute> attribs;
};
//----------------------------------------------------------------------------


//============================================================================
// project_filelist
//============================================================================
struct project_filelist
{
  // construction
  project_filelist();
  //--------------------------------------------------------------------------

  heap_str file_groups;
  heap_str files;
  unsigned num_filelists;
  heap_str project_template;
  heap_str file_template;
  heap_str output_filename;
  list<xml_attribute> attribs;
};
//----------------------------------------------------------------------------


//============================================================================
// project_file
//============================================================================
struct project_file
{
  // operations
  PFC_INLINE bool operator<(const project_file&) const;
  PFC_INLINE bool operator==(const heap_str &fname_) const {return name==fname_;}
  //--------------------------------------------------------------------------

  heap_str name;
  array<const project_file_config*> file_cfgs;
};
//----------------------------------------------------------------------------


//============================================================================
// property_list_input_format
//============================================================================
struct property_list_input_format
{
  PFC_INLINE bool operator==(const heap_str &name_) const {return name==name_;}
  //--------------------------------------------------------------------------

  heap_str name;
  heap_str separator;
};
//----------------------------------------------------------------------------


//============================================================================
// property_list_output_format
//============================================================================
struct property_list_output_format
{
  PFC_INLINE bool operator==(const heap_str &name_) const {return name==name_;}
  //--------------------------------------------------------------------------

  heap_str name;
  heap_str format;
  heap_str separator;
};
//----------------------------------------------------------------------------


//============================================================================
// project_config
//============================================================================
class project_config
{
public:
  // construction
  project_config();
  ~project_config();
  void parse(bin_input_stream_base&, const char *compiler_tag_, const char *sxproj_name_);
  //--------------------------------------------------------------------------

  // parsed project properties
  heap_str project_config_name;
  heap_str supported_platforms;
  list<xml_attribute> base_project_attribs;
  list<xml_attribute> compiler_attribs;
  list<project_build_type> base_builds;
  list<project_build_platform> base_platforms;
  heap_str project_name;
  heap_str project_template_filename;
  list<xml_attribute> project_attribs;
  list<project_build_type> builds;
  list<project_build_platform> platforms;
  heap_str configs_template_filename;
  list<project_build_config> configs;
  heap_str files_rootdir;
  list<xml_attribute> file_cfgs_attr;
  list<project_file_config> file_cfgs;
  list<project_filelist> filelists;
  list<property_list_input_format> property_list_input_formats;
  list<property_list_output_format> property_list_output_formats;
  // transient
  heap_str default_platforms, default_builds;
  list<project_file> project_files;
  // project properties
  const char *project_file_path;
  const char *build_template_path;
  //--------------------------------------------------------------------------

private:
  // parsing and setup
  void setup_project_envvars();
  void parse_base_project_config(const char *compiler_tag_);
  void parse_project_config(bin_input_stream_base&);
  void merge_shared_project_attributes(const char *sxproj_name_);
  void setup_config_attribs();
  void setup_project_files();
  void collect_files(const project_file_config&, const list<heap_str> &files_, const heap_str &directory_);
  void collect_files(const list<project_file_config>&);
  void collect_build_configs(const project_file_config&, const functor<void(const project_build_config&)>&);
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
