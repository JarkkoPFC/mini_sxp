//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "project_config.h"
#include "sxp_src/core/fsys/fsys.h"
#include "sxp_src/core/xml.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// locals
//============================================================================
namespace
{
  //==========================================================================
  // name_cmp
  //==========================================================================
  template<class T>
  struct name_cmp
  {
    PFC_INLINE bool equal(const T &a0_, const T &a1_) const
    {
      return a0_.name==a1_.name;
    }
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // file_cfg_setter
  //==========================================================================
  struct file_cfg_setter
  {
    project_file *pfile;
    const project_file_config *pfile_cfg;
    //----

    static void exec(const file_cfg_setter &setter_, const project_build_config &cfg_)
    {
      setter_.pfile->file_cfgs[cfg_.config_index]=setter_.pfile_cfg;
    }
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // generate_vsproj_guid
  //==========================================================================
  stack_str64 generate_vsproj_guid(const char *sxproj_filename_)
  {
    // generate VS-compatible GUID from the sxproj filename
    rng_simple rng(crc32(sxproj_filename_));
    stack_str64 guid;
    guid.format("%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                rng.rand_uint16()&255, rng.rand_uint16()&255, rng.rand_uint16()&255, rng.rand_uint16()&255,
                rng.rand_uint16()&255, rng.rand_uint16()&255,
                rng.rand_uint16()&255, rng.rand_uint16()&255,
                rng.rand_uint16()&255, rng.rand_uint16()&255,
                rng.rand_uint16()&255, rng.rand_uint16()&255, rng.rand_uint16()&255, rng.rand_uint16()&255, rng.rand_uint16()&255, rng.rand_uint16()&255);
    return guid;
  }
} // namespace <anonymous>
//----------------------------------------------------------------------------


//============================================================================
// project_filelist
//============================================================================
project_filelist::project_filelist()
{
  num_filelists=0;
}
//----------------------------------------------------------------------------


//============================================================================
// project_file
//============================================================================
bool project_file::operator<(const project_file &f_) const
{
  heap_str fp0=name, fp1=f_.name;
  const char *fn0=split_filepath(fp0.c_str());
  const char *fn1=split_filepath(fp1.c_str());
  int cmp=str_idiff(fp0.c_str()==fn0?"":fp0.c_str(), fp1.c_str()==fn1?"":fp1.c_str());
  return (cmp?cmp:str_idiff(fn0, fn1))<0;
}
//----------------------------------------------------------------------------


//============================================================================
// project_file_config
//============================================================================
project_file_config::project_file_config()
{
  recursive=false;
  exclude=false;
}
//----------------------------------------------------------------------------


//============================================================================
// project_config
//============================================================================
project_config::project_config()
{
  project_file_path=0;
  build_template_path=0;
}
//----

project_config::~project_config()
{
}
//----

void project_config::parse(bin_input_stream_base &stream_, const char *compiler_tag_, const char *sxproj_name_)
{
  // parse project XML file and setup project config
/*  setup_project_envvars();*/
  parse_base_project_config(compiler_tag_);
  parse_project_config(stream_);
  merge_shared_project_attributes(sxproj_name_);
  setup_config_attribs();
  setup_project_files();
}
//----------------------------------------------------------------------------
/*
void project_config::setup_project_envvars()
{
  // skip the first two environment variables
  const char *env_strs=GetEnvironmentStrings();
  for(unsigned i=0; i<2; ++i)
    env_strs+=str_size(env_strs)+1;

  // add environment variables to project attributes
  while(*env_strs)
  {
    unsigned estr_len=str_size(env_strs);
    const char *eq_pos=str_find(env_strs, '=');
    if(eq_pos && eq_pos[1])
    {
      xml_attribute &attr=project_attribs.push_back();
      attr.name.push_back(env_strs, unsigned(eq_pos-env_strs));
      attr.value.push_back(eq_pos+1, unsigned(env_strs+estr_len-eq_pos-1));
    }
    env_strs+=estr_len+1;
  }
}
//----
*/

void project_config::parse_base_project_config(const char *compiler_tag_)
{
  // parse base project attributes
  owner_ptr<bin_input_stream_base> file=afs_open_read("base_project.config", build_template_path);
  if(file.data)
  {
    // setup structure for XML file parsing
    // <BaseProject>
    xml_stream_parser parser;
    parser.begin_element("BaseProject").
             attribs_ftl(base_project_attribs).
           end_element();

    // <PropertyListFormats>
    parser.begin_element("PropertyListInputFormats").
             begin_element("PropertyList", property_list_input_formats).
               attrib("Name", &property_list_input_format::name).
               attrib("Separator", &property_list_input_format::separator).
             end_element().
           end_element();

    // <Compiler Tag> (e.g. <VS2008>)
    parser.begin_element(compiler_tag_).
             attrib("SupportedPlatforms", supported_platforms).
             attribs_ftl(compiler_attribs).
             begin_element("PropertyListOutputFormats").
               begin_element("PropertyList", property_list_output_formats).
                 attrib("Name", &property_list_output_format::name).
                 attrib("Format", &property_list_output_format::format).
               end_element().
             end_element().
           end_element();

    // <Builds>
    parser.begin_element("Builds").
             begin_element("Build", base_builds).
               attrib("BuildName", &project_build_type::name).
               attribs_ftl(&project_build_type::attribs).
             end_element().
           end_element();

    // <Platforms>
    parser.begin_element("Platforms").
             begin_element("Platform", base_platforms).
               attrib("PlatformName", &project_build_platform::name).
               attribs_ftl(&project_build_platform::attribs).
             end_element().
           end_element();

    // parse XML stream
    xml_input_stream xml_stream(*file);
    parser.process_stream(xml_stream);
  }

  // get name prefix for the project build template files & dirs
  list<xml_attribute>::iterator prefix_it=linear_search(compiler_attribs.begin(), compiler_attribs.size(), "ProjectConfigName", name_cmp<xml_attribute>());
  if(is_valid(prefix_it))
    project_config_name=prefix_it->value;
  else
    project_config_name=compiler_tag_;
  str_lower(project_config_name.c_str());
}
//----

void project_config::parse_project_config(bin_input_stream_base &stream_)
{
  // setup structure for XML file parsing
  // <Project>
  xml_stream_parser parser;
  parser.begin_element("Project").
           attrib("ProjectName", project_name).
           attribs_ftl(project_attribs);

    // <Builds>
    parser.begin_element("Builds");
      parser.begin_element("Build", builds).
               attrib("BuildName", &project_build_type::name).
               attribs_ftl(&project_build_type::attribs).
             end_element();
    parser.end_element();

    // <Platforms>
    parser.begin_element("Platforms");
      parser.begin_element("Platform", platforms).
               attrib("PlatformName", &project_build_platform::name).
               attribs_ftl(&project_build_platform::attribs).
             end_element();
    parser.end_element();

    // <Configurations>
    parser.begin_element("Configurations").
             attrib("TemplateFile", configs_template_filename);
      parser.begin_element("Config", configs).
               attrib("PlatformName", &project_build_config::target_platform).
               attrib("BuildName", &project_build_config::target_build).
               attribs_ftl(&project_build_config::attribs).
             end_element();
    parser.end_element();

    // <FileConfigs>
    parser.begin_element("FileConfigs").attrib("RootDir", files_rootdir).attribs_ftl(file_cfgs_attr);
      // <FileConfig>
      parser.begin_element("FileConfig", file_cfgs).
               attrib("Builds", &project_file_config::builds).
               attrib("Platforms", &project_file_config::platforms).
               attrib("Dir", &project_file_config::directory).
               attrib("Files", &project_file_config::files).
               attrib("TemplateFile", &project_file_config::template_filename).
               attrib("FileGroup", &project_file_config::file_group).
               attrib("Recursive", &project_file_config::recursive).
               attrib("Exclude", &project_file_config::exclude).
               attribs_ftl(&project_file_config::attribs).
             end_element();
    parser.end_element();

    // <Filelists>
    parser.begin_element("Filelists");
      parser.begin_element("Filelist", filelists).
        attrib("FileGroups", &project_filelist::file_groups).
        attrib("Files", &project_filelist::files).
        attrib("NumFilelists", &project_filelist::num_filelists).
        attrib("ProjectTemplate", &project_filelist::project_template).
        attrib("FileTemplate", &project_filelist::file_template).
        attrib("OutputFile", &project_filelist::output_filename).
        attribs_ftl(&project_filelist::attribs).
      end_element();
    parser.end_element();
  parser.end_element();

  // parse XML stream
  xml_input_stream xml_stream(stream_);
  parser.process_stream(xml_stream);

  // setup format conversion and convert parsed attributes
  list<property_list_output_format>::iterator plist_it=property_list_output_formats.begin();
  while(is_valid(plist_it))
  {
    list<property_list_input_format>::const_iterator it=linear_search(property_list_input_formats.begin(), property_list_input_formats.size(), plist_it->name);
    if(is_valid(it))
      plist_it->separator=it->separator;
    ++plist_it;
  }
}
//----

void project_config::merge_shared_project_attributes(const char *sxproj_name_)
{
  // setup project attribs
  merge_attrib_lists(compiler_attribs, base_project_attribs);
  merge_attrib_lists(project_attribs, compiler_attribs);
  project_attribs.push_back(xml_attribute("SXProjName", sxproj_name_));
  project_attribs.push_back(xml_attribute("SXProjVSProjectGUID", generate_vsproj_guid(sxproj_name_).c_str()));
  replace_attribs(project_name, project_name, project_attribs);
  project_attribs.push_back(xml_attribute("ProjectName", project_name.c_str()));
  replace_attribs(project_attribs, project_attribs);
  replace_attribs(file_cfgs_attr, project_attribs);

  // setup <FileConfigs> attributes and setup all <FileConfig> attributes
  replace_attribs(files_rootdir, files_rootdir, project_attribs);
  merge_attrib(file_cfgs_attr, xml_attribute("RootDir", files_rootdir.c_str()));
  list<project_file_config>::iterator fcfg_it=file_cfgs.begin();
  while(is_valid(fcfg_it))
  {
    replace_attribs(fcfg_it->files, fcfg_it->files, file_cfgs_attr);
    replace_attribs(fcfg_it->template_filename, fcfg_it->template_filename, file_cfgs_attr);
    replace_attribs(fcfg_it->file_group, fcfg_it->file_group, file_cfgs_attr);
    ++fcfg_it;
  }

  // merge base build attribute with project build attributes
  list<project_build_type>::iterator pbuild_it=builds.begin();
  while(is_valid(pbuild_it))
  {
    list<project_build_type>::const_iterator bbuild_it=linear_search(base_builds.begin(), base_builds.size(), *pbuild_it, name_cmp<project_build_type>());
    if(is_valid(bbuild_it))
      merge_attrib_lists(pbuild_it->attribs, bbuild_it->attribs);
    ++pbuild_it;
  }

  // merge base platform attributes with project platform attributes
  list<project_build_platform>::iterator pplatform_it=platforms.begin();
  while(is_valid(pplatform_it))
  {
    list<project_build_platform>::const_iterator bplatform_it=linear_search(base_platforms.begin(), base_platforms.size(), *pplatform_it, name_cmp<project_build_platform>());
    if(is_valid(bplatform_it))
      merge_attrib_lists(pplatform_it->attribs, bplatform_it->attribs);
    ++pplatform_it;
  }
}
//----

void project_config::setup_config_attribs()
{
  // setup default platforms
  list<project_build_platform>::iterator it_plat=platforms.begin();
  while(is_valid(it_plat))
  {
    // check if platform is in supported platform list
    bool is_supported_platform=true;
    if(supported_platforms.size())
    {
      is_supported_platform=false;
      heap_str plats=supported_platforms;
      char *p=plats.c_str();
      do
      {
        char *next_p=str_tokenize_words(p);
        if(it_plat->name==p)
        {
          is_supported_platform=true;
          break;
        }
        p=next_p;
      } while(*p);
    }

    if(is_supported_platform)
    {
      if(default_platforms.size())
        default_platforms+=' ';
      default_platforms+=it_plat->name;
      ++it_plat;
    }
    else
      platforms.erase(it_plat);
  }

  // setup default builds
  list<project_build_type>::const_iterator it_build=builds.begin();
  while(is_valid(it_build))
  {
    if(default_builds.size())
      default_builds+=' ';
    default_builds+=it_build->name;
    ++it_build;
  }

  // setup project template filename
  list<xml_attribute>::iterator pattr_it=linear_search(project_attribs.begin(), project_attribs.size(), "ProjectTemplateFile", name_cmp<xml_attribute>());
  if(is_valid(pattr_it))
    project_template_filename=pattr_it->value;

  // iterate through target builds
  list<project_build_type>::const_iterator build_it=builds.begin();
  while(is_valid(build_it))
  {
    // merge project attributes to build attributes
    const project_build_type &target_build=*build_it;
    list<xml_attribute> build_attribs=target_build.attribs;
    build_attribs.push_back(xml_attribute("BuildName", target_build.name.c_str()));
    merge_attrib_lists(build_attribs, project_attribs);

    // iterate through target platforms
    list<project_build_platform>::const_iterator platform_it=platforms.begin();
    while(is_valid(platform_it))
    {
      // merge build attributes platform attributes
      const project_build_platform &target_platform=*platform_it;
      list<xml_attribute> platform_attribs=target_platform.attribs;
      platform_attribs.push_back(xml_attribute("PlatformName", target_platform.name.c_str()));
      merge_attrib_lists(platform_attribs, build_attribs);
      replace_attribs(platform_attribs, platform_attribs);

      // search for the config
      list<project_build_config>::iterator cit=configs.begin();
      project_build_config *cfg=0;
      unsigned cfg_idx=0;
      while(is_valid(cit))
      {
        if(cit->target_build==target_build.name && cit->target_platform==target_platform.name)
        {
          cfg=ptr(cit);
          cfg->config_index=cfg_idx;
          break;
        }
        ++cit;
        ++cfg_idx;
      }

      // add new config if none found
      if(!cfg)
      {
        cfg=&configs.push_back();
        cfg->config_index=(unsigned)configs.size()-1;
        cfg->target_build=target_build.name;
        cfg->target_platform=target_platform.name;
      }

      // merge build attributes to build config attributes
      merge_attrib_lists(cfg->attribs, platform_attribs);

      // strip extra whitespace from values
      list<xml_attribute>::iterator attr_it=cfg->attribs.begin();
      while(is_valid(attr_it))
      {
        attr_it->value.resize(str_strip_extra_whitespace(attr_it->value.c_str()));
        attr_it->value.resize(str_strip_outer_chars(attr_it->value.c_str(), ';', true));
        ++attr_it;
      }
      ++platform_it;
    }
    ++build_it;
  }
}
//----

void project_config::setup_project_files()
{
  // collect project files defined by include and exclude file configs
  collect_files(file_cfgs);
  insertion_sort(project_files.begin(), project_files.size());
/*
  // remove files which do not belong to any file config
  list<project_file>::iterator it=project_files.begin();
  unsigned num_cfgs=configs.size();
  while(is_valid(it))
  {
    // check if file has any file config
    project_file *pfile=ptr(it);
    for(unsigned i=0; i<num_cfgs; ++i)
      if(pfile->file_cfgs[i])
      {
        ++it;
        break;
      }
    if(pfile==ptr(it))
      it.remove();
  }*/
}
//----

void project_config::collect_files(const project_file_config &file_cfg_, const list<heap_str> &files_, const heap_str &directory_)
{
  // construct path to the files
  heap_str file_path;
  if(project_file_path && *project_file_path)
  {
    file_path+=project_file_path;
    file_path+='/';
  }
  file_path+=files_rootdir;
  file_path+='/';
  file_path+=directory_;

  // check for recursive directory iteration
  file_system_base &fsys=file_system_base::active();
  if(file_cfg_.recursive)
  {
    file_system_base::iterator dir_it=fsys.find_first(fsysfind_dirs, file_path.c_str());
    while(is_valid(dir_it))
    {
      heap_str dir=directory_;
      dir+=dir_it.name();
      dir+='/';
      collect_files(file_cfg_, files_, dir);
      ++dir_it;
    }
  }

  // iterate through all files in the directory
  file_system_base::iterator file_it=fsys.find_first(fsysfind_files, file_path.c_str());
  while(is_valid(file_it))
  {
    // check if file matches filters
    list<heap_str>::const_iterator it=files_.begin();
    while(is_valid(it))
    {
      if(str_eq_wildcard(file_it.name(), it->c_str()))
        break;
      ++it;
    }

    // update or add file if it matches the file filter
    if(is_valid(it))
    {
      // check if project file already exists
      heap_str fname=directory_;
      fname+=file_it.name();
      list<project_file>::iterator pit=linear_search(project_files.begin(), project_files.size(), fname);
      if(is_valid(pit) || !file_cfg_.exclude)
      {
        if(!is_valid(pit))
        {
          // add new project file
          project_file &pfile=project_files.push_back();
          pit=project_files.last();
          pfile.name=fname;
          pfile.file_cfgs.resize(configs.size());
        }
        else
        {
          // update project file configs
          project_file &pfile=*pit;
          mem_zero(pfile.file_cfgs.data(), pfile.file_cfgs.size()*sizeof(*pfile.file_cfgs.data()));
        }
        file_cfg_setter setter={ptr(pit), !file_cfg_.exclude?&file_cfg_:0};
        collect_build_configs(file_cfg_, make_functor(setter, file_cfg_setter::exec));
      }
    }
    ++file_it;
  }
}
//----

void project_config::collect_files(const list<project_file_config> &file_cfgs_)
{
  // iterate through all file configs
  list<project_file_config>::const_iterator file_cfg_it=file_cfgs_.begin();
  while(is_valid(file_cfg_it))
  {
    // build filter list
    heap_str files_str=file_cfg_it->files;
    replace_attribs(files_str, files_str, project_attribs);
    list<heap_str> files;
    char *f=str_skip_whitespace(files_str.c_str());
    while(*f)
    {
      char *next_f=str_tokenize_words(f);
      files.push_back(f);
      f=next_f;
    }

    // build source directory
    heap_str directory;
    replace_attribs(directory, file_cfg_it->directory, project_attribs);
    if(directory.size())
    {
      str_replace(directory.c_str(), '\\', '/');
      if(directory.back()!='/')
        directory+='/';
    }

    // iterate through all files in the directory
    collect_files(*file_cfg_it, files, directory);

    ++file_cfg_it;
  }
}
//----

void project_config::collect_build_configs(const project_file_config &file_cfg_, const functor<void(const project_build_config&)> &func_)
{
  // process all platforms for the file config
  heap_str platforms=file_cfg_.platforms.size()?file_cfg_.platforms:default_platforms;
  replace_attribs(platforms, platforms, project_attribs);
  char *platform=str_skip_whitespace(platforms.c_str());
  while(*platform)
  {
    // process all builds for the file config
    char *next_platform=str_tokenize_words(platform);
    heap_str builds=file_cfg_.builds.size()?file_cfg_.builds:default_builds;
    replace_attribs(builds, builds, project_attribs);
    char *build=str_skip_whitespace(builds.c_str());
    while(*build)
    {
      // search for build config with matching platform and build
      char *next_build=str_tokenize_words(build);
      list<project_build_config>::const_iterator it=configs.begin();
      while(is_valid(it))
      {
        // set project file config for matching build config
        if(it->target_platform==platform && it->target_build==build)
        {
          func_(*it);
          break;
        }
        ++it;
      }
      build=next_build;
    }
    platform=next_platform;
  }
}
//----------------------------------------------------------------------------

bool pfc::replace_attrib(heap_str &res_, const heap_str &str_, const heap_str &attrib_name_, const heap_str &attrib_value_)
{
  // construct attribute search string: "@(AttributeName)"
  PFC_ASSERT(&res_!=&str_);
  heap_str attr_search;
  attr_search.reserve(attrib_name_.size()+3);
  attr_search="@(";
  attr_search+=attrib_name_;
  attr_search+=')';

  // replace "@(AttributeName)" in the string with attribute value
  res_.clear();
  const char *start=str_.c_str();
  while(const char *s=str_find_substr(start, attr_search.c_str()))
  {
    res_.push_back(start, unsigned(s-start));
    res_+=attrib_value_;
    start=s+attr_search.size();
  }

  // return true if any string replacement was made
  if(start==str_.c_str())
    return false;
  res_+=start;
  return true;
}
//----

void pfc::replace_attribs(heap_str &res_, const heap_str &str_, const list<xml_attribute> &attribs_, const xml_attribute *skip_attrib_)
{
  // perform attribute replacement with given list of attributes
  heap_str res, temp_res;
  bool has_replaced=false;
  list<xml_attribute>::const_iterator attrib_it=attribs_.begin();
  while(is_valid(attrib_it))
  {
    if(   ptr(attrib_it)!=skip_attrib_
       && replace_attrib(temp_res, has_replaced?res:str_, attrib_it->name, attrib_it->value))
    {
      res.swap(temp_res);
      has_replaced=true;
    }
    ++attrib_it;
  }

  // return result
  if(has_replaced)
    res_.swap(res);
  else
    if(&res_!=&str_)
      res_=str_;
}
//----

void pfc::replace_attribs(list<xml_attribute> &dst_, const list<xml_attribute> &src_)
{
  // replace attribute names in the list of attributes
  list<xml_attribute>::iterator attrib_it=dst_.begin();
  while(is_valid(attrib_it))
  {
    replace_attribs(attrib_it->value, attrib_it->value, src_, ptr(attrib_it));
    ++attrib_it;
  }
}
//----

void pfc::final_replace_attribs(const project_config &cfg_, heap_str &res_, const heap_str &str_, const list<xml_attribute> &attribs_)
{
  // perform attribute replacement with given list of attributes
  heap_str res, temp_res;
  bool has_replaced=false;
  list<xml_attribute>::const_iterator attrib_it=attribs_.begin();
  while(is_valid(attrib_it))
  {
    // perform format conversions
    const xml_attribute &attr=*attrib_it;
    heap_str attr_final_value=attr.value;
    list<property_list_input_format>::const_iterator in_fmt_it=linear_search(cfg_.property_list_input_formats.begin(), cfg_.property_list_input_formats.size(), attr.name);
    if(is_valid(in_fmt_it))
    {
      attr_final_value.resize(str_strip_extra_substrs(attr_final_value.c_str(), in_fmt_it->separator.c_str()));
      list<property_list_output_format>::const_iterator out_fmt_it=linear_search(cfg_.property_list_output_formats.begin(), cfg_.property_list_output_formats.size(), attr.name);
      if(is_valid(out_fmt_it))
      {
        // convert attribute value using conversion format
        const heap_str value_attr_name("Value");
        heap_str new_value;
        const char *separator=out_fmt_it->separator.c_str();
        const char *pos=attr_final_value.c_str(), *end=pos+attr_final_value.size();
        usize_t separator_size=out_fmt_it->separator.size();
        do
        {
          const char *next_pos=str_find_substr(pos, separator);
          usize_t num_chars=(next_pos?next_pos:end)-pos;
          if(num_chars)
          {
            heap_str value_attr, tmp;
            value_attr.push_back(pos, num_chars);
            replace_attrib(tmp, out_fmt_it->format, value_attr_name, value_attr);
            new_value+=tmp;
          }
          pos+=num_chars+separator_size;
        } while(pos<end);
        attr_final_value.swap(new_value);
        attr_final_value.resize(str_strip_outer_whitespace(attr_final_value.c_str()));
      }
    }

    // replace attribute value
    if(replace_attrib(temp_res, has_replaced?res:str_, attr.name, attr_final_value))
    {
      res.swap(temp_res);
      has_replaced=true;
    }
    ++attrib_it;
  }

  // return result
  if(has_replaced)
    res_.swap(res);
  else
    if(&res_!=&str_)
      res_=str_;
}
//----------------------------------------------------------------------------


//============================================================================
// merge_attrib
//============================================================================
void pfc::merge_attrib(list<xml_attribute> &dst_, const xml_attribute &attrib_)
{
  // check if attribute name already exists in the destination list
  list<xml_attribute>::iterator it=linear_search(dst_.begin(), dst_.size(), attrib_, name_cmp<xml_attribute>());
  if(is_valid(it))
  {
    // perform attribute replacement with the old attribute value
    heap_str new_value;
    if(replace_attrib(new_value, it->value, attrib_.name, attrib_.value))
      new_value.swap(it->value);
  }
  else
    dst_.push_back(attrib_);
}
//----------------------------------------------------------------------------


//============================================================================
// merge_attrib_lists
//============================================================================
void pfc::merge_attrib_lists(list<xml_attribute> &dst_, const list<xml_attribute> &src_)
{
  // merge source attribute list to destination attribute list
  list<xml_attribute>::const_iterator it=src_.begin();
  while(is_valid(it))
  {
    merge_attrib(dst_, *it);
    ++it;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// load_text_file
//============================================================================
bool pfc::load_text_file(heap_str &str_, const char *filename_, const char *path_)
{
  // load text file to heap_str
  file_system_base &fs=file_system_base::active();
  if(!fs.exists(filename_, path_))
    return false;
  owner_ref<bin_input_stream_base> file=fs.open_read(filename_, path_, fopencheck_abort);
  usize_t file_size=fs.file_size(filename_, path_);
  str_.resize(file_size);
  file->read_bytes(str_.data(), file_size);
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// remove_trailing_linefeed
//============================================================================
void pfc::remove_trailing_linefeed(heap_str &str_)
{
  if(str_.size() && str_.back()=='\n')
    str_.remove_back(1);
  if(str_.size() && str_.back()=='\r')
    str_.remove_back(1);
}
//----------------------------------------------------------------------------


//============================================================================
// save_project_file
//============================================================================
void pfc::save_project_file(const char *filename_, const project_config &cfg_, const heap_str &content_)
{
  heap_str proj_fname;
  list<xml_attribute>::const_iterator it=linear_search(cfg_.project_attribs.begin(), cfg_.project_attribs.size(), "ProjectOutputDir", name_cmp<xml_attribute>());
  if(is_valid(it))
  {
    // construct project filename
    file_system_base &fs=file_system_base::active();
    const char *project_output_dir=it->value.c_str();
    proj_fname.format(filename_, project_output_dir, cfg_.project_name.c_str());

    // check if file has changed
    if(fs.exists(proj_fname.c_str(), cfg_.project_file_path))
    {
      owner_ref<bin_input_stream_base> ifile=fs.open_read(proj_fname.c_str(), cfg_.project_file_path, fopencheck_abort);
      usize_t size=fs.file_size(proj_fname.c_str(), cfg_.project_file_path);
      heap_str s;
      s.resize(size);
      ifile->read_bytes(s.data(), size);
      if(content_==s)
        return;
    }

    // write content to the file
    owner_ptr<bin_output_stream_base> ofile=fs.open_write(proj_fname.c_str(), cfg_.project_file_path);
    if(ofile.data)
      ofile->write_bytes(content_.data(), content_.size());
  }
}
//----------------------------------------------------------------------------
