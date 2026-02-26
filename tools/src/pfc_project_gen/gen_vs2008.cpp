//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "project_config.h"
#include "sxp_src/core/fsys/fsys.h"
#include "sxp_src/core/xml.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// config
//============================================================================
static const char *s_excluded_cfg_file="file_configs/vs2008/excluded";
//----------------------------------------------------------------------------


//============================================================================
// locals
//============================================================================
namespace
{
  void add_filter(heap_str &files_attr_, heap_str fpath_, heap_str &prev_fpath_, unsigned &dir_depth_)
  {
    // add </Filter> tags
    unsigned cpath_size=common_path_size(prev_fpath_.c_str(), fpath_.c_str());
    char *fp=prev_fpath_.c_str()+cpath_size;
    while(char *next_fp=str_find(fp, '/'))
    {
      --dir_depth_;
      files_attr_.push_back('\t', dir_depth_);
      files_attr_+="\t\t</Filter>\r\n";
      fp=next_fp+1;
    }

    // add new <Filter> tags required by the file path
    prev_fpath_=fpath_;
    fp=fpath_.c_str()+cpath_size;
    while(char *next_fp=str_find(fp, '/'))
    {
      *next_fp++=0;
      files_attr_.push_back('\t', dir_depth_+2);
      files_attr_+="<Filter\r\n";
      files_attr_.push_back('\t', dir_depth_+3);
      files_attr_+="Name=\"";
      files_attr_+=fp;
      files_attr_+="\"\r\n";
      files_attr_.push_back('\t', dir_depth_+3);
      files_attr_+=">\r\n";
      fp=next_fp;
      ++dir_depth_;
    }
  }
} // namespace <anonymous>
//----------------------------------------------------------------------------


//============================================================================
// generate_vs2008_project
//============================================================================
void generate_vs2008_project(const project_config &cfg_)
{
  // open vcproj template file
  heap_str project_template_filename, platform_template;
  final_replace_attribs(cfg_, project_template_filename, cfg_.project_template_filename, cfg_.project_attribs);
  project_template_filename+=".vcproj";
  heap_str project_template, project_res;
  if(!load_text_file(project_template, project_template_filename.c_str(), cfg_.build_template_path))
    return;
  if(!load_text_file(platform_template, "vs2008.platform", cfg_.build_template_path))
    return;

  // generate @(Platforms) attribute
  list<xml_attribute> project_template_attr=cfg_.project_attribs;
  xml_attribute &platforms_attr=project_template_attr.push_back();
  platforms_attr.name="Platforms";
  list<project_build_platform>::const_iterator platform_it=cfg_.platforms.begin();
  while(is_valid(platform_it))
  {
    heap_str plat;
    final_replace_attribs(cfg_, plat, platform_template, platform_it->attribs);
    platforms_attr.value+=plat;
    ++platform_it;
  }
  remove_trailing_linefeed(platforms_attr.value);

  // generate @(Configurations) attribute
  typedef hash_map<const project_file_config*, array<heap_str> > file_cfg_map_t;
  file_cfg_map_t cfg_templates;
  xml_attribute &configurations_attr=project_template_attr.push_back();
  configurations_attr.name="Configurations";
  list<project_build_config>::const_iterator build_cfg_it=cfg_.configs.begin();
  while(is_valid(build_cfg_it))
  {
    // try to open build config template file
    heap_str cfg_template_filename;
    final_replace_attribs(cfg_, cfg_template_filename, cfg_.configs_template_filename, build_cfg_it->attribs);
    cfg_template_filename+=".config";
    heap_str cfg_template, cfg_template_res;
    if(load_text_file(cfg_template, cfg_template_filename.c_str(), cfg_.build_template_path))
    {
      // add configuration entry to @(Configurations) using the template file
      xml_attribute cfg_template_attr;
      final_replace_attribs(cfg_, cfg_template_res, cfg_template, build_cfg_it->attribs);
      configurations_attr.value+=cfg_template_res;
    }

    // add file config template file for the build config
    list<project_file_config>::const_iterator inc_file_cfg_it=cfg_.file_cfgs.begin();
    while(is_valid(inc_file_cfg_it))
    {
      const project_file_config &file_cfg=*inc_file_cfg_it;
      if(!file_cfg.exclude && file_cfg.template_filename.size())
      {
        heap_str fname;
        final_replace_attribs(cfg_, fname, file_cfg.template_filename, build_cfg_it->attribs);
        file_cfg_map_t::inserter ins=cfg_templates.insert(&file_cfg, array<heap_str>(), false);
        array<heap_str> &cfg_template_arr=*ins.it;
        if(ins.is_new)
          cfg_template_arr.resize(cfg_.configs.size());
        heap_str &cfg_template=cfg_template_arr[build_cfg_it->config_index];
        if(!cfg_template.size() && load_text_file(cfg_template, fname.c_str(), cfg_.build_template_path))
        {
          list<xml_attribute> attribs=file_cfg.attribs;
          merge_attrib_lists(attribs, build_cfg_it->attribs);
          final_replace_attribs(cfg_, cfg_template, cfg_template, attribs);
        }
      }
      ++inc_file_cfg_it;
    }

    // add "excluded" config for the build config
    {
      file_cfg_map_t::inserter ins=cfg_templates.insert(0, array<heap_str>(), false);
      array<heap_str> &cfg_template_arr=*ins.it;
      if(ins.is_new)
        cfg_template_arr.resize(cfg_.configs.size());
      heap_str &cfg_template=cfg_template_arr[build_cfg_it->config_index];
      if(!cfg_template.size() && load_text_file(cfg_template, s_excluded_cfg_file, cfg_.build_template_path))
        final_replace_attribs(cfg_, cfg_template, cfg_template, build_cfg_it->attribs);
    }

    // proceed to the next build config
    ++build_cfg_it;
  }
  remove_trailing_linefeed(configurations_attr.value);

  // generate @(Files) attribute
  xml_attribute &files_attr=project_template_attr.push_back();
  files_attr.name="Files";
  list<project_file>::const_iterator file_it=cfg_.project_files.begin();
  heap_str prev_dir;
  unsigned dir_depth=0;
  while(is_valid(file_it))
  {
    // add filter and file tags
    const project_file &pfile=*file_it;
    add_filter(files_attr.value, pfile.name, prev_dir, dir_depth);
    files_attr.value.push_back('\t', dir_depth+2);
    files_attr.value+="<File\r\n";
    files_attr.value.push_back('\t', dir_depth+3);
    files_attr.value+="RelativePath=\"..\\";
    heap_str fname=cfg_.files_rootdir;
    fname+='/';
    fname+=pfile.name;
    str_replace(fname.c_str(), '/', '\\');
    files_attr.value+=fname;
    files_attr.value+="\"\r\n";
    files_attr.value.push_back('\t', dir_depth+3);
    files_attr.value+=">\r\n";

    // setup file specific attributes
    heap_str fname_container=fname;
    str_replace(fname_container.c_str(), '\\', '/');
    char *filename=split_filepath(fname_container.c_str());
    heap_str relative_dir="../";
    if(filename!=fname_container.c_str())
    {
      relative_dir+=fname_container.c_str();
      relative_dir+='/';
    }
    split_filename(filename);
    list<xml_attribute> file_attribs;
    const char *file_ext=get_fileext(pfile.name.c_str());
    file_ext=file_ext?file_ext-1:"";
    file_attribs.push_back(xml_attribute("Filename", filename));
    file_attribs.push_back(xml_attribute("Extension", file_ext));
    file_attribs.push_back(xml_attribute("RelativeDir", relative_dir.c_str()));

    // add configs for the file
    usize_t num_cfgs=pfile.file_cfgs.size();
    for(usize_t ci=0; ci<num_cfgs; ++ci)
    {
      const project_file_config *fcfg=pfile.file_cfgs[ci];
      file_cfg_map_t::const_iterator it=cfg_templates.find(fcfg);
      if(is_valid(it))
      {
        // add file config template with given indention
        heap_str templ;
        final_replace_attribs(cfg_, templ, (*it)[ci], file_attribs);
        const char *s=templ.c_str();
        while(*s)
        {
          files_attr.value.push_back('\t', dir_depth+3);
          const char *next_s=str_find_next_line(s);
          files_attr.value.push_back(s, unsigned(next_s-s));
          s=next_s;
        }
      }
    }

    // add file end tag
    files_attr.value.push_back('\t', dir_depth+2);
    files_attr.value+="</File>\r\n";
    ++file_it;
  }
  if(dir_depth)
    add_filter(files_attr.value, "", prev_dir, dir_depth);
  remove_trailing_linefeed(files_attr.value);

  // generate project using project template file
  final_replace_attribs(cfg_, project_res, project_template, project_template_attr);
  save_project_file("%s/%s.vcproj", cfg_, project_res);
}
//----------------------------------------------------------------------------
