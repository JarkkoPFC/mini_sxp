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
  // xcode_object_id_generator
  //==========================================================================
  class xcode_object_id_generator
  {
  public:
    // construction
    xcode_object_id_generator()
      :m_next_id(1)
    {
    }
    //------------------------------------------------------------------------

    // generate deterministic-ish unique Xcode object id for the project
    heap_str generate(const char *tag_)
    {
      stack_str64 id;
      id.format("%08X%016llX", unsigned(crc32(tag_)), (unsigned long long)m_next_id++);
      return heap_str(id.c_str());
    }

  private:
    uint64_t m_next_id;
  };
  //--------------------------------------------------------------------------


  //==========================================================================
  // xcode_file_entry
  //==========================================================================
  struct xcode_file_entry
  {
    heap_str path;
    heap_str name;
    heap_str file_ref_id;
    heap_str build_file_id;
    bool is_source;
    const char *file_type;
  };
  //--------------------------------------------------------------------------


  //==========================================================================
  // xcode_helpers
  //==========================================================================
  const char *find_attrib_value(const list<xml_attribute> &attribs_, const char *name_)
  {
    list<xml_attribute>::const_iterator it=attribs_.begin();
    while(is_valid(it))
    {
      if(it->name==name_)
        return it->value.c_str();
      ++it;
    }
    return 0;
  }
  //----

  void append_string_setting(heap_str &settings_, const char *name_, const char *value_, bool normalize_path_)
  {
    if(!value_ || !*value_)
      return;
    heap_str value=value_;
    value.resize(str_strip_outer_whitespace(value.c_str()));
    if(!value.size())
      return;
    if(normalize_path_)
      str_replace(value.c_str(), '\\', '/');
    settings_.push_back_format("\t\t\t\t%s = \"%s\";\r\n", name_, value.c_str());
  }
  //----

  void append_list_setting(heap_str &settings_, const char *name_, const char *values_, bool normalize_paths_)
  {
    if(!values_ || !*values_)
      return;

    // collect non-empty semicolon-separated tokens
    list<heap_str> items;
    const char *p=values_;
    while(*p)
    {
      const char *next=str_find(p, ';');
      if(!next)
        next=p+str_size(p);
      if(next>p)
      {
        heap_str token;
        token.push_back(p, usize_t(next-p));
        token.resize(str_strip_outer_whitespace(token.c_str()));
        if(token.size())
          items.push_back(token);
      }
      if(!*next)
        break;
      p=next+1;
    }
    if(!items.size())
      return;

    settings_.push_back_format("\t\t\t\t%s = (\r\n", name_);
    list<heap_str>::iterator it=items.begin();
    while(is_valid(it))
    {
      heap_str value=*it;
      if(normalize_paths_)
        str_replace(value.c_str(), '\\', '/');
      settings_.push_back_format("\t\t\t\t\t\"%s\",\r\n", value.c_str());
      ++it;
    }
    settings_+="\t\t\t\t);\r\n";
  }
  //----

  heap_str xcode_config_name(const project_build_config &cfg_, bool append_platform_)
  {
    if(!append_platform_)
      return cfg_.target_build;
    heap_str name=cfg_.target_build;
    name.push_back_format("_%s", cfg_.target_platform.c_str());
    return name;
  }
} // namespace <anonymous>
//----------------------------------------------------------------------------


//============================================================================
// generate_xcode_project
//============================================================================
void generate_xcode_project(const project_config &cfg_)
{
  // validate project config for xcode generation
  if(!cfg_.configs.size())
  {
    errorf("Xcode generation failed for %s: no build configurations found\r\n", cfg_.project_name.c_str());
    return;
  }
  if(!cfg_.project_files.size())
  {
    errorf("Xcode generation failed for %s: no project files found\r\n", cfg_.project_name.c_str());
    return;
  }

  // resolve output type and validate required output attributes
  bool is_static_library=false;
  {
    list<project_build_config>::const_iterator cfg_it=cfg_.configs.begin();
    const char *first_output_ext=find_attrib_value(cfg_it->attribs, "OutputFileExt");
    if(!first_output_ext)
    {
      errorf("Xcode generation failed for %s: missing OutputFileExt attribute\r\n", cfg_.project_name.c_str());
      return;
    }
    if(str_eq(first_output_ext, ".a"))
      is_static_library=true;
    else if(!str_size(first_output_ext))
      is_static_library=false;
    else
    {
      errorf("Xcode generation failed for %s: unsupported OutputFileExt \"%s\"\r\n", cfg_.project_name.c_str(), first_output_ext);
      return;
    }

    ++cfg_it;
    while(is_valid(cfg_it))
    {
      const char *output_ext=find_attrib_value(cfg_it->attribs, "OutputFileExt");
      if(!output_ext || !str_eq(output_ext, first_output_ext))
      {
        errorf("Xcode generation failed for %s: inconsistent OutputFileExt across build configurations\r\n", cfg_.project_name.c_str());
        return;
      }
      ++cfg_it;
    }
  }

  // collect file entries for Xcode sections and build phase wiring
  xcode_object_id_generator id_gen;
  list<xcode_file_entry> files;
  list<project_file>::const_iterator pfile_it=cfg_.project_files.begin();
  while(is_valid(pfile_it))
  {
    const project_file &pfile=*pfile_it;
    const char *ext=get_fileext(pfile.name.c_str());
    xcode_file_entry &file=files.push_back();
    file.path=pfile.name;
    file.name=get_filename(pfile.name.c_str());
    file.file_ref_id=id_gen.generate("PBXFileReference");
    file.build_file_id.clear();
    // classify file extension for source membership and xcode file type
    file.is_source=   str_eq(ext, "c")
                   || str_eq(ext, "cc")
                   || str_eq(ext, "cpp")
                   || str_eq(ext, "cxx")
                   || str_eq(ext, "m")
                   || str_eq(ext, "mm");
    if(str_eq(ext, "c"))
      file.file_type="sourcecode.c.c";
    else if(   str_eq(ext, "cc")
            || str_eq(ext, "cpp")
            || str_eq(ext, "cxx"))
      file.file_type="sourcecode.cpp.cpp";
    else if(str_eq(ext, "m"))
      file.file_type="sourcecode.c.objc";
    else if(str_eq(ext, "mm"))
      file.file_type="sourcecode.cpp.objcpp";
    else if(   str_eq(ext, "h")
            || str_eq(ext, "hh")
            || str_eq(ext, "hpp")
            || str_eq(ext, "hxx")
            || str_eq(ext, "inl")
            || str_eq(ext, "inc"))
      file.file_type="sourcecode.c.h";
    else
      file.file_type="text";
    if(file.is_source)
      file.build_file_id=id_gen.generate("PBXBuildFile");
    ++pfile_it;
  }

  // detect whether configuration names need platform suffix for uniqueness
  bool append_platform_to_config_name=false;
  {
    list<project_build_config>::const_iterator cfg_a=cfg_.configs.begin();
    while(is_valid(cfg_a) && !append_platform_to_config_name)
    {
      list<project_build_config>::const_iterator cfg_b=cfg_.configs.begin();
      while(is_valid(cfg_b))
      {
        if(   ptr(cfg_a)!=ptr(cfg_b)
           && cfg_a->target_build==cfg_b->target_build)
        {
          append_platform_to_config_name=true;
          break;
        }
        ++cfg_b;
      }
      ++cfg_a;
    }
  }

  // allocate shared object ids for project and target graph
  const heap_str id_project=id_gen.generate("PBXProject");
  const heap_str id_target=id_gen.generate("PBXNativeTarget");
  const heap_str id_main_group=id_gen.generate("PBXGroupMain");
  const heap_str id_sources_group=id_gen.generate("PBXGroupSources");
  const heap_str id_products_group=id_gen.generate("PBXGroupProducts");
  const heap_str id_product_file_ref=id_gen.generate("PBXProductFileReference");
  const heap_str id_sources_phase=id_gen.generate("PBXSourcesBuildPhase");
  const heap_str id_project_cfg_list=id_gen.generate("XCConfigurationListProject");
  const heap_str id_target_cfg_list=id_gen.generate("XCConfigurationListTarget");

  // generate per-configuration build settings and configuration lists
  heap_str xcode_project_cfg_refs, xcode_target_cfg_refs;
  heap_str xcode_project_cfg_section, xcode_target_cfg_section;
  {
    list<project_build_config>::const_iterator cfg_it=cfg_.configs.begin();
    while(is_valid(cfg_it))
    {
      const project_build_config &build_cfg=*cfg_it;
      const char *output_file=find_attrib_value(build_cfg.attribs, "OutputFile");
      if(!output_file || !*output_file)
      {
        errorf("Xcode generation failed for %s: missing OutputFile for config %s/%s\r\n",
               cfg_.project_name.c_str(),
               build_cfg.target_build.c_str(),
               build_cfg.target_platform.c_str());
        return;
      }

      const heap_str id_project_cfg=id_gen.generate("XCBuildConfigurationProject");
      const heap_str id_target_cfg=id_gen.generate("XCBuildConfigurationTarget");
      const heap_str cfg_name=xcode_config_name(build_cfg, append_platform_to_config_name);

      xcode_project_cfg_refs.push_back_format("\t\t\t\t%s /* %s */,\r\n", id_project_cfg.c_str(), cfg_name.c_str());
      xcode_target_cfg_refs.push_back_format("\t\t\t\t%s /* %s */,\r\n", id_target_cfg.c_str(), cfg_name.c_str());

      // keep project-level config settings intentionally minimal
      xcode_project_cfg_section.push_back_format("\t\t%s /* %s */ = {\r\n", id_project_cfg.c_str(), cfg_name.c_str());
      xcode_project_cfg_section+="\t\t\tisa = XCBuildConfiguration;\r\n";
      xcode_project_cfg_section+="\t\t\tbuildSettings = {\r\n";
      xcode_project_cfg_section+="\t\t\t\tSDKROOT = macosx;\r\n";
      xcode_project_cfg_section+="\t\t\t};\r\n";
      xcode_project_cfg_section.push_back_format("\t\t\tname = %s;\r\n", cfg_name.c_str());
      xcode_project_cfg_section+="\t\t};\r\n";

      // validate and read language standard settings from config
      const char *cpp_standard=find_attrib_value(build_cfg.attribs, "XcodeCppStandard");
      const char *c_standard=find_attrib_value(build_cfg.attribs, "XcodeCStandard");
      if(!cpp_standard || !*cpp_standard)
      {
        errorf("Xcode generation failed for %s: missing XcodeCppStandard attribute\r\n", cfg_.project_name.c_str());
        return;
      }
      if(!c_standard || !*c_standard)
      {
        errorf("Xcode generation failed for %s: missing XcodeCStandard attribute\r\n", cfg_.project_name.c_str());
        return;
      }

      // construct target build settings directly from merged sxproj attributes
      heap_str target_settings;
      target_settings.push_back_format("\t\t\t\tCLANG_CXX_LANGUAGE_STANDARD = \"%s\";\r\n", cpp_standard);
      target_settings.push_back_format("\t\t\t\tGCC_C_LANGUAGE_STANDARD = %s;\r\n", c_standard);
      target_settings+="\t\t\t\tSDKROOT = macosx;\r\n";
      if(is_static_library)
      {
        target_settings+="\t\t\t\tMACH_O_TYPE = staticlib;\r\n";
        target_settings+="\t\t\t\tSKIP_INSTALL = YES;\r\n";
      }
      append_string_setting(target_settings, "PRODUCT_NAME", output_file, false);
      append_string_setting(target_settings, "CONFIGURATION_BUILD_DIR", find_attrib_value(build_cfg.attribs, "OutputDirectory"), true);
      append_list_setting(target_settings, "HEADER_SEARCH_PATHS", find_attrib_value(build_cfg.attribs, "IncludeDirectories"), true);
      append_list_setting(target_settings, "LIBRARY_SEARCH_PATHS", find_attrib_value(build_cfg.attribs, "LibraryDirectories"), true);
      append_list_setting(target_settings, "GCC_PREPROCESSOR_DEFINITIONS", find_attrib_value(build_cfg.attribs, "PreprocessorDefinitions"), false);

      xcode_target_cfg_section.push_back_format("\t\t%s /* %s */ = {\r\n", id_target_cfg.c_str(), cfg_name.c_str());
      xcode_target_cfg_section+="\t\t\tisa = XCBuildConfiguration;\r\n";
      xcode_target_cfg_section+="\t\t\tbuildSettings = {\r\n";
      xcode_target_cfg_section+=target_settings;
      xcode_target_cfg_section+="\t\t\t};\r\n";
      xcode_target_cfg_section.push_back_format("\t\t\tname = %s;\r\n", cfg_name.c_str());
      xcode_target_cfg_section+="\t\t};\r\n";

      ++cfg_it;
    }
  }

  // generate pbx build-file and file-reference sections
  heap_str xcode_build_file_section, xcode_file_ref_section;
  heap_str xcode_sources_phase_refs, xcode_source_group_refs;
  {
    list<xcode_file_entry>::const_iterator file_it=files.begin();
    while(is_valid(file_it))
    {
      const xcode_file_entry &file=*file_it;
      xcode_file_ref_section.push_back_format("\t\t%s /* %s */ = {isa = PBXFileReference; lastKnownFileType = %s; path = \"%s\"; sourceTree = \"<group>\"; };\r\n",
                                               file.file_ref_id.c_str(),
                                               file.name.c_str(),
                                               file.file_type,
                                               file.path.c_str());
      xcode_source_group_refs.push_back_format("\t\t\t\t%s /* %s */,\r\n", file.file_ref_id.c_str(), file.name.c_str());
      if(file.is_source)
      {
        xcode_build_file_section.push_back_format("\t\t%s /* %s in Sources */ = {isa = PBXBuildFile; fileRef = %s /* %s */; };\r\n",
                                                  file.build_file_id.c_str(),
                                                  file.name.c_str(),
                                                  file.file_ref_id.c_str(),
                                                  file.name.c_str());
        xcode_sources_phase_refs.push_back_format("\t\t\t\t%s /* %s in Sources */,\r\n", file.build_file_id.c_str(), file.name.c_str());
      }
      ++file_it;
    }
  }

  // generate file reference for build product
  const char *product_file_type=is_static_library?"archive.ar":"compiled.mach-o.executable";
  const char *product_type=is_static_library?"com.apple.product-type.library.static":"com.apple.product-type.tool";
  xcode_file_ref_section.push_back_format("\t\t%s /* %s */ = {isa = PBXFileReference; explicitFileType = %s; includeInIndex = 0; path = \"$(EXECUTABLE_NAME)\"; sourceTree = BUILT_PRODUCTS_DIR; };\r\n",
                                           id_product_file_ref.c_str(),
                                           cfg_.project_name.c_str(),
                                           product_file_type);

  // derive default config name from the first build configuration
  const heap_str default_cfg_name=xcode_config_name(*cfg_.configs.begin(), append_platform_to_config_name);

  // assemble full Xcode project file content
  heap_str xcode_project;
  xcode_project+=
    "// !$*UTF8*$!\r\n"
    "{\r\n"
    "\tarchiveVersion = 1;\r\n"
    "\tclasses = {\r\n"
    "\t};\r\n"
    "\tobjectVersion = 56;\r\n"
    "\tobjects = {\r\n"
    "\r\n"
    "/* Begin PBXBuildFile section */\r\n";
  xcode_project+=xcode_build_file_section;
  xcode_project+=
    "/* End PBXBuildFile section */\r\n"
    "\r\n"
    "/* Begin PBXFileReference section */\r\n";
  xcode_project+=xcode_file_ref_section;
  xcode_project+=
    "/* End PBXFileReference section */\r\n"
    "\r\n"
    "/* Begin PBXGroup section */\r\n";
  xcode_project.push_back_format("\t\t%s = {\r\n", id_main_group.c_str());
  xcode_project+=
    "\t\t\tisa = PBXGroup;\r\n"
    "\t\t\tchildren = (\r\n";
  xcode_project.push_back_format("\t\t\t\t%s /* source */,\r\n", id_sources_group.c_str());
  xcode_project.push_back_format("\t\t\t\t%s /* Products */,\r\n", id_products_group.c_str());
  xcode_project+=
    "\t\t\t);\r\n"
    "\t\t\tsourceTree = \"<group>\";\r\n"
    "\t\t};\r\n";
  xcode_project.push_back_format("\t\t%s /* source */ = {\r\n", id_sources_group.c_str());
  xcode_project+=
    "\t\t\tisa = PBXGroup;\r\n"
    "\t\t\tchildren = (\r\n";
  xcode_project+=xcode_source_group_refs;
  xcode_project+="\t\t\t);\r\n";
  xcode_project.push_back_format("\t\t\tpath = \"%s\";\r\n", cfg_.files_rootdir.c_str());
  xcode_project+=
    "\t\t\tsourceTree = \"<group>\";\r\n"
    "\t\t};\r\n";
  xcode_project.push_back_format("\t\t%s /* Products */ = {\r\n", id_products_group.c_str());
  xcode_project+=
    "\t\t\tisa = PBXGroup;\r\n"
    "\t\t\tchildren = (\r\n";
  xcode_project.push_back_format("\t\t\t\t%s /* %s */,\r\n", id_product_file_ref.c_str(), cfg_.project_name.c_str());
  xcode_project+=
    "\t\t\t);\r\n"
    "\t\t\tname = Products;\r\n"
    "\t\t\tsourceTree = \"<group>\";\r\n"
    "\t\t};\r\n"
    "/* End PBXGroup section */\r\n"
    "\r\n"
    "/* Begin PBXNativeTarget section */\r\n";
  xcode_project.push_back_format("\t\t%s /* %s */ = {\r\n", id_target.c_str(), cfg_.project_name.c_str());
  xcode_project+="\t\t\tisa = PBXNativeTarget;\r\n";
  xcode_project.push_back_format("\t\t\tbuildConfigurationList = %s /* Build configuration list for PBXNativeTarget \\\"%s\\\" */;\r\n",
                                  id_target_cfg_list.c_str(),
                                  cfg_.project_name.c_str());
  xcode_project+="\t\t\tbuildPhases = (\r\n";
  xcode_project.push_back_format("\t\t\t\t%s /* Sources */,\r\n", id_sources_phase.c_str());
  xcode_project+=
    "\t\t\t);\r\n"
    "\t\t\tbuildRules = (\r\n"
    "\t\t\t);\r\n"
    "\t\t\tdependencies = (\r\n"
    "\t\t\t);\r\n";
  xcode_project.push_back_format("\t\t\tname = %s;\r\n", cfg_.project_name.c_str());
  xcode_project.push_back_format("\t\t\tproductName = %s;\r\n", cfg_.project_name.c_str());
  xcode_project.push_back_format("\t\t\tproductReference = %s /* %s */;\r\n", id_product_file_ref.c_str(), cfg_.project_name.c_str());
  xcode_project.push_back_format("\t\t\tproductType = \"%s\";\r\n", product_type);
  xcode_project+=
    "\t\t};\r\n"
    "/* End PBXNativeTarget section */\r\n"
    "\r\n"
    "/* Begin PBXProject section */\r\n";
  xcode_project.push_back_format("\t\t%s /* Project object */ = {\r\n", id_project.c_str());
  xcode_project+="\t\t\tisa = PBXProject;\r\n";
  xcode_project.push_back_format("\t\t\tbuildConfigurationList = %s /* Build configuration list for PBXProject \\\"%s\\\" */;\r\n",
                                  id_project_cfg_list.c_str(),
                                  cfg_.project_name.c_str());
  xcode_project+=
    "\t\t\tcompatibilityVersion = \"Xcode 15.0\";\r\n"
    "\t\t\tdevelopmentRegion = en;\r\n"
    "\t\t\thasScannedForEncodings = 0;\r\n"
    "\t\t\tknownRegions = (\r\n"
    "\t\t\t\ten,\r\n"
    "\t\t\t\tBase,\r\n"
    "\t\t\t);\r\n";
  xcode_project.push_back_format("\t\t\tmainGroup = %s;\r\n", id_main_group.c_str());
  xcode_project.push_back_format("\t\t\tproductRefGroup = %s /* Products */;\r\n", id_products_group.c_str());
  xcode_project+=
    "\t\t\tprojectDirPath = \"\";\r\n"
    "\t\t\tprojectRoot = \"\";\r\n"
    "\t\t\ttargets = (\r\n";
  xcode_project.push_back_format("\t\t\t\t%s /* %s */,\r\n", id_target.c_str(), cfg_.project_name.c_str());
  xcode_project+=
    "\t\t\t);\r\n"
    "\t\t};\r\n"
    "/* End PBXProject section */\r\n"
    "\r\n"
    "/* Begin PBXSourcesBuildPhase section */\r\n";
  xcode_project.push_back_format("\t\t%s /* Sources */ = {\r\n", id_sources_phase.c_str());
  xcode_project+=
    "\t\t\tisa = PBXSourcesBuildPhase;\r\n"
    "\t\t\tbuildActionMask = 2147483647;\r\n"
    "\t\t\tfiles = (\r\n";
  xcode_project+=xcode_sources_phase_refs;
  xcode_project+=
    "\t\t\t);\r\n"
    "\t\t\trunOnlyForDeploymentPostprocessing = 0;\r\n"
    "\t\t};\r\n"
    "/* End PBXSourcesBuildPhase section */\r\n"
    "\r\n"
    "/* Begin XCBuildConfiguration section */\r\n";
  xcode_project+=xcode_project_cfg_section;
  xcode_project+=xcode_target_cfg_section;
  xcode_project+=
    "/* End XCBuildConfiguration section */\r\n"
    "\r\n"
    "/* Begin XCConfigurationList section */\r\n";
  xcode_project.push_back_format("\t\t%s /* Build configuration list for PBXProject \\\"%s\\\" */ = {\r\n",
                                  id_project_cfg_list.c_str(),
                                  cfg_.project_name.c_str());
  xcode_project+=
    "\t\t\tisa = XCConfigurationList;\r\n"
    "\t\t\tbuildConfigurations = (\r\n";
  xcode_project+=xcode_project_cfg_refs;
  xcode_project+="\t\t\t);\r\n\t\t\tdefaultConfigurationIsVisible = 0;\r\n";
  xcode_project.push_back_format("\t\t\tdefaultConfigurationName = %s;\r\n\t\t};\r\n", default_cfg_name.c_str());
  xcode_project.push_back_format("\t\t%s /* Build configuration list for PBXNativeTarget \\\"%s\\\" */ = {\r\n",
                                  id_target_cfg_list.c_str(),
                                  cfg_.project_name.c_str());
  xcode_project+=
    "\t\t\tisa = XCConfigurationList;\r\n"
    "\t\t\tbuildConfigurations = (\r\n";
  xcode_project+=xcode_target_cfg_refs;
  xcode_project+="\t\t\t);\r\n\t\t\tdefaultConfigurationIsVisible = 0;\r\n";
  xcode_project.push_back_format("\t\t\tdefaultConfigurationName = %s;\r\n\t\t};\r\n", default_cfg_name.c_str());
  xcode_project+=
    "/* End XCConfigurationList section */\r\n"
    "\r\n"
    "\t};\r\n";
  xcode_project.push_back_format("\trootObject = %s /* Project object */;\r\n", id_project.c_str());
  xcode_project+="}\r\n";

  // write generated Xcode project file
  save_project_file("%s/%s.xcodeproj/project.pbxproj", cfg_, xcode_project);
}
//----------------------------------------------------------------------------
