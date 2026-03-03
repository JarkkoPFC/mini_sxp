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
  void add_item_group(heap_str &item_group_attr_, const heap_str &file_cfg_)
  {
    if(file_cfg_.size())
    {
      item_group_attr_+="  <ItemGroup>\r\n";
      item_group_attr_+=file_cfg_;
      item_group_attr_+="  </ItemGroup>\r\n";
    }
  }
} // namespace <anonymous>
//----------------------------------------------------------------------------


//============================================================================
// generate_vs201x_project
//============================================================================
void generate_vs201x_project(const project_config &cfg_)
{
  // open vcproj template file
  heap_str project_template_filename, project_filter_template_filename, prop_group_template_filename;
  final_replace_attribs(cfg_, project_template_filename, cfg_.project_template_filename, cfg_.project_attribs);
  project_filter_template_filename=project_template_filename;
  prop_group_template_filename=project_template_filename;
  project_template_filename+=".vcxproj";
  project_filter_template_filename+=".vcxproj.filters";
  prop_group_template_filename+=".propgroup";
  heap_str project_template, project_filter_template;
  if(!load_text_file(project_template, project_template_filename.c_str(), cfg_.build_template_path))
    return;
  if(!load_text_file(project_filter_template, project_filter_template_filename.c_str(), cfg_.build_template_path))
    return;

  // generate @(ProjectConfigurations)
  list<xml_attribute> project_template_attr=cfg_.project_attribs;
  xml_attribute &proj_cfg_attr=project_template_attr.push_back();
  proj_cfg_attr.name="ProjectConfigurations";
  heap_str proj_cfg_template;
  heap_str proj_cfg_filename;
  proj_cfg_filename.format("%s.projcfg", cfg_.project_config_name.c_str());
  load_text_file(proj_cfg_template, proj_cfg_filename.c_str(), cfg_.build_template_path);
  list<project_build_config>::const_iterator build_cfg_it=cfg_.configs.begin();
  while(is_valid(build_cfg_it))
  {
    heap_str tmp;
    final_replace_attribs(cfg_, tmp, proj_cfg_template, build_cfg_it->attribs);
    proj_cfg_attr.value+=tmp;
    ++build_cfg_it;
  }
  remove_trailing_linefeed(proj_cfg_attr.value);

  // generate @(ProjectGroups), @(ImportGroups), @(PropertyGroups), @(CodeAnalysis) and @(ItemDefinitionGroups)
  typedef hash_map<const project_file_config*, array<heap_str> > file_cfg_map_t;
  file_cfg_map_t cfg_templates;
  heap_str import_group_filename, code_analysis_filename, excluded_file_cfg_path;
  import_group_filename.format("%s.impgroup", cfg_.project_config_name.c_str());
  code_analysis_filename.format("%s.codeanalysis", cfg_.project_config_name.c_str());
  excluded_file_cfg_path.format("file_configs/%s/excluded", cfg_.project_config_name.c_str());
  heap_str import_group_template, code_analysis_template, prop_group_template;
  load_text_file(import_group_template, import_group_filename.c_str(), cfg_.build_template_path);
  load_text_file(code_analysis_template, code_analysis_filename.c_str(), cfg_.build_template_path);
  load_text_file(prop_group_template, prop_group_template_filename.c_str(), cfg_.build_template_path);
  xml_attribute &proj_group_attr=project_template_attr.push_back();
  proj_group_attr.name="ProjectGroups";
  xml_attribute &imp_group_attr=project_template_attr.push_back();
  imp_group_attr.name="ImportGroups";
  xml_attribute &prop_group_attr=project_template_attr.push_back();
  prop_group_attr.name="PropertyGroups";
  xml_attribute &code_analysis_attr=project_template_attr.push_back();
  code_analysis_attr.name="CodeAnalysis";
  xml_attribute &item_def_groups_attr=project_template_attr.push_back();
  item_def_groups_attr.name="ItemDefinitionGroups";
  build_cfg_it=cfg_.configs.begin();
  while(is_valid(build_cfg_it))
  {
    // add @(ProjectGroups) entry
    heap_str fname;
    final_replace_attribs(cfg_, fname, cfg_.configs_template_filename, build_cfg_it->attribs);
    fname+=".propgroup";
    heap_str temp_file;
    if(load_text_file(temp_file, fname.c_str(), cfg_.build_template_path))
    {
      final_replace_attribs(cfg_, temp_file, temp_file, build_cfg_it->attribs);
      proj_group_attr.value+=temp_file;
    }

    // add @(ImportGroups) entry
    if(import_group_template.size())
    {
      heap_str tmp;
      final_replace_attribs(cfg_, tmp, import_group_template, build_cfg_it->attribs);
      imp_group_attr.value+=tmp;
    }

    // add @(PropertyGroups) entry
    if(prop_group_template.size())
    {
      heap_str tmp;
      final_replace_attribs(cfg_, tmp, prop_group_template, build_cfg_it->attribs);
      prop_group_attr.value+=tmp;
    }

    // add @(CodeAnalysis) entry
    if(code_analysis_template.size())
    {
      heap_str tmp;
      final_replace_attribs(cfg_, tmp, code_analysis_template, build_cfg_it->attribs);
      code_analysis_attr.value+=tmp;
    }

    // add @(ItemDefinitionGroups) entry
    heap_str item_def_template, item_def_template_filename;
    final_replace_attribs(cfg_, item_def_template_filename, cfg_.configs_template_filename, build_cfg_it->attribs);
    item_def_template_filename+=".itemdefgroup";
    if(load_text_file(item_def_template, item_def_template_filename.c_str(), cfg_.build_template_path))
    {
      heap_str tmp;
      final_replace_attribs(cfg_, tmp, item_def_template, build_cfg_it->attribs);
      item_def_groups_attr.value+=tmp;
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
      if(!cfg_template.size() && load_text_file(cfg_template, excluded_file_cfg_path.c_str(), cfg_.build_template_path))
        final_replace_attribs(cfg_, cfg_template, cfg_template, build_cfg_it->attribs);
    }

    ++build_cfg_it;
  }
  remove_trailing_linefeed(proj_group_attr.value);
  remove_trailing_linefeed(imp_group_attr.value);
  remove_trailing_linefeed(prop_group_attr.value);
  remove_trailing_linefeed(code_analysis_attr.value);
  remove_trailing_linefeed(item_def_groups_attr.value);

  // generate @(ItemGroups)
  list<project_file>::const_iterator pfile_it=cfg_.project_files.begin();
  heap_str compile_files, include_files, appxmanifest_files, custom_files, none_files;
  heap_str compile_file_filters, include_file_filters, appxmanifest_file_filters, custom_file_filters, none_file_filters;
  bool has_compile_filters=false, has_include_filters=false, has_appxmanifest_filters=false, has_custom_filters=false, has_none_filters=false;
  heap_str *file_str=0, *file_filter_str=0;
  bool *has_filters=0;
  array<heap_str> unique_filters;
  while(is_valid(pfile_it))
  {
    // construct project filename
    const project_file &pfile=*pfile_it;
    const char *orig_fname=pfile.name.c_str();
    heap_str fname="../";
    fname+=cfg_.files_rootdir;
    fname+='/';
    fname+=pfile.name;
    str_replace(fname.c_str(), '/', '\\');

    // setup file specific attributes
    heap_str fname_container=fname;
    str_replace(fname_container.c_str(), '\\', '/');
    char *filename=split_filepath(fname_container.c_str());
    heap_str relative_dir;
    if(filename!=fname_container.c_str())
    {
      relative_dir+=fname_container.c_str();
      relative_dir+='/';
    }
    split_filename(filename);
    list<xml_attribute> file_attribs;
    const char *file_ext=get_fileext(pfile.name.c_str());
    file_ext=file_ext?file_ext-1:"";

    // setup source-root relative dir for file-specific template replacement
    heap_str root_relative_dir=pfile.name;
    const char *root_filename=get_filename(root_relative_dir.c_str());
    if(root_filename!=root_relative_dir.c_str())
    {
      root_relative_dir.resize(unsigned(root_filename-root_relative_dir.c_str()));
      str_replace(root_relative_dir.c_str(), '/', '\\');
    }
    else
      root_relative_dir.clear();
    file_attribs.push_back(xml_attribute("Filename", filename));
    file_attribs.push_back(xml_attribute("Extension", file_ext));
    file_attribs.push_back(xml_attribute("RelativeDir", relative_dir.c_str()));

    // construct file config string
    usize_t num_cfgs=pfile.file_cfgs.size();
    heap_str file_cfg_str;
    for(usize_t ci=0; ci<num_cfgs; ++ci)
    {
      const project_file_config *fcfg=pfile.file_cfgs[ci];
      file_cfg_map_t::const_iterator it=cfg_templates.find(fcfg);
      if(is_valid(it))
      {
        heap_str templ;
        final_replace_attribs(cfg_, templ, (*it)[ci], file_attribs);
        file_cfg_str+=templ.c_str();
      }
    }

    // setup compile file state for file-specific overrides
    const char *fname_ext=get_fileext(orig_fname);
    bool is_compile_file=str_ieq(fname_ext, "cpp") || str_ieq(fname_ext, "c") || str_ieq(fname_ext, "cc");

    // add file-specific object file output dir for nested source files
    if(root_relative_dir.size() && is_compile_file)
      file_cfg_str.push_back_format("      <ObjectFileName>$(IntDir)%s</ObjectFileName>\r\n", root_relative_dir.c_str());

    // get file type tag for the extension
    const char *file_type_tag=0;
    if(is_compile_file)
    {
      file_type_tag="ClCompile";
      file_str=&compile_files;
      file_filter_str=&compile_file_filters;
      has_filters=&has_compile_filters;
    }
    else if(str_ieq(fname_ext, "h") || str_ieq(fname_ext, "hxx") || str_ieq(fname_ext, "hpp"))
    {
      file_type_tag="ClInclude";
      file_str=&include_files;
      file_filter_str=&include_file_filters;
      has_filters=&has_include_filters;
    }
    else if(str_ieq(fname_ext, "appxmanifest"))
    {
      file_type_tag="AppxManifest";
      file_str=&appxmanifest_files;
      file_filter_str=&appxmanifest_file_filters;
      has_filters=&has_appxmanifest_filters;
    }
    else if(file_cfg_str.size())
    {
      file_type_tag="CustomBuild";
      file_str=&custom_files;
      file_filter_str=&custom_file_filters;
      has_filters=&has_custom_filters;
    }
    else
    {
      file_type_tag="None";
      file_str=&none_files;
      file_filter_str=&none_file_filters;
      has_filters=&has_none_filters;
    }

    // add file entry
    if(file_cfg_str.size())
    {
      heap_str tmp;
      tmp.format("    <%s Include=\"%s\">\r\n", file_type_tag, fname.c_str());
      (*file_str)+=tmp;
      (*file_str)+=file_cfg_str;
      tmp.format("    </%s>\r\n", file_type_tag);
      (*file_str)+=tmp;
    }
    else
    {
      heap_str tmp;
      tmp.format("    <%s Include=\"%s\" />\r\n", file_type_tag, fname.c_str());
      (*file_str)+=tmp;
    }

    // create filter for the file
    heap_str filter=fname;
    filter.resize(split_filepath(filter.c_str())-filter.c_str());
    if(filter.size())
      filter.remove_back(1);
    filter.remove_front(cfg_.files_rootdir.size()+3);
    if(filter.size())
      filter.remove_front(1);

    // add file filter entry
    if(filter.size())
    {
      // add unique filters
      {
        char *p=filter.c_str(), *next_p;
        do
        {
          next_p=str_find(p, '\\');
          if(next_p)
            *next_p=0;
          if(!linear_search(unique_filters.begin(), unique_filters.size(), filter.c_str()))
            unique_filters.push_back(filter.c_str());
          if(next_p)
            *next_p='\\';
          p=next_p+1;
        } while(next_p);
      }

      // add config with filter
      heap_str tmp;
      tmp.format("    <%s Include=\"%s\">\r\n"
                 "      <Filter>%s</Filter>\r\n"
                 "    </%s>\r\n", file_type_tag, fname.c_str(), filter.c_str(), file_type_tag);
      (*file_filter_str)+=tmp;
      (*has_filters)=true;
    }
    else
    {
      heap_str tmp;
      tmp.format("    <%s Include=\"%s\" />\r\n", file_type_tag, fname.c_str());
      (*file_filter_str)+=tmp;
      (*has_filters)=true;
    }

    ++pfile_it;
  }

  // add item groups
  xml_attribute &item_group_attr=project_template_attr.push_back();
  item_group_attr.name="ItemGroups";
  add_item_group(item_group_attr.value, compile_files);
  add_item_group(item_group_attr.value, include_files);
  add_item_group(item_group_attr.value, appxmanifest_files);
  add_item_group(item_group_attr.value, custom_files);
  add_item_group(item_group_attr.value, none_files);
  remove_trailing_linefeed(item_group_attr.value);

  // add item filter groups
  xml_attribute &item_filter_group_attr=project_template_attr.push_back();
  item_filter_group_attr.name="ItemFilterGroups";
  if(unique_filters.size())
  {
    heap_str filter_group;
    for(unsigned i=0; i<unique_filters.size(); ++i)
    {
      heap_str tmp;
      tmp.format("    <Filter Include=\"%s\" />\r\n", unique_filters[i].c_str());
      filter_group+=tmp;
    }
    add_item_group(item_filter_group_attr.value, filter_group);
  }
  if(has_compile_filters)
    add_item_group(item_filter_group_attr.value, compile_file_filters);
  if(has_include_filters)
    add_item_group(item_filter_group_attr.value, include_file_filters);
  if(has_appxmanifest_filters)
    add_item_group(item_filter_group_attr.value, appxmanifest_file_filters);
  if(has_custom_filters)
    add_item_group(item_filter_group_attr.value, custom_file_filters);
  if(has_none_filters)
    add_item_group(item_filter_group_attr.value, none_file_filters);
  remove_trailing_linefeed(item_filter_group_attr.value);

  // generate project using project template file
  heap_str project_res;
  final_replace_attribs(cfg_, project_res, project_template, project_template_attr);
  save_project_file("%s/%s.vcxproj", cfg_, project_res);

  // generate project filter using project filter template file
  if(item_filter_group_attr.value.size())
  {
    heap_str project_filter_res;
    final_replace_attribs(cfg_, project_filter_res, project_filter_template, project_template_attr);
    save_project_file("%s/%s.vcxproj.filters", cfg_, project_filter_res);
  }
}
//----------------------------------------------------------------------------
