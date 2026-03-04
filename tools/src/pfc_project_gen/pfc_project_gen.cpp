//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/core/fsys/fsys.h"
#include "sxp_src/core/xml.h"
#include "sxp_src/core/main.h"
#include "project_config.h"
#include "solution_config.h"
using namespace pfc;
static const char *s_copyright_message=
  "C++ Project Generator v1.55\r\n"
  "Copyright (c) 2026, Profoundic Technologies, Inc. All rights reserved.\r\n"
  "\r\n";
//----------------------------------------------------------------------------


//============================================================================
// project generators
//============================================================================
void generate_vs201x_project(const project_config&);
void generate_xcode_project(const project_config&);
//----------------------------------------------------------------------------

bool find_file_group(const heap_str &fgroup_, const heap_str &fgroup_str_)
{
  // search if file group is found from the file group string
  heap_str fgroup_str=fgroup_str_;
  char *fg=str_skip_whitespace(fgroup_str.c_str()), *fg_next;
  do
  {
    fg_next=str_tokenize_words(fg);
    if(fgroup_==fg)
      return true;
    fg=fg_next;
  } while(*fg_next);
  return false;
}
//----

bool find_file(const char *fpath_, const list<heap_str> &file_filters_)
{
  // check if file path matches file filters
  if(!file_filters_.size())
    return true;
  list<heap_str>::const_iterator it=file_filters_.begin();
  while(is_valid(it))
  {
    if(str_eq_wildcard(fpath_, it->c_str()))
      return true;
    ++it;
  }
  return false;
}
//----

void export_filelists(const project_config &pcfg_)
{
  // construct full path to source file root directory
  heap_str full_rootdir=pcfg_.project_file_path;
  if(full_rootdir.size())
    full_rootdir+='/';
  if(pcfg_.files_rootdir.size())
  {
    full_rootdir+=pcfg_.files_rootdir;
    full_rootdir.resize(collapse_relative_dirs(full_rootdir.c_str()));
    full_rootdir+='/';
  }

  // export filelists
  list<project_filelist>::const_iterator flist_it=pcfg_.filelists.begin();
  while(is_valid(flist_it))
  {
    // merge attributes
    const project_filelist &flist=*flist_it;
    list<xml_attribute> flist_attribs=flist.attribs;
    merge_attrib_lists(flist_attribs, pcfg_.project_attribs);

    // build file filters
    list<heap_str> file_filters;
    heap_str flist_files=flist.files;
    char *f=str_skip_whitespace(flist_files.c_str());
    while(*f)
    {
      char *next_f=str_tokenize_words(f);
      file_filters.push_back(f);
      f=next_f;
    }

    // open output file and load filelist file template
    list<heap_str> filelist_entries;
    heap_str filelist_file_template;
    if(load_text_file(filelist_file_template, flist.file_template.c_str(), pcfg_.project_file_path))
    {
      // process all files
      list<project_file>::const_iterator pfile_it=pcfg_.project_files.begin();
      while(is_valid(pfile_it))
      {
        // check if file belongs to one of the file groups for the list
        const project_file &pfile=*pfile_it;
        usize_t num_file_configs=pfile.file_cfgs.size();
        for(usize_t fci=0; fci<num_file_configs; ++fci)
          if(   pfile.file_cfgs[fci]
             && pfile.file_cfgs[fci]->file_group.size()
             && find_file_group(pfile.file_cfgs[fci]->file_group, flist.file_groups)
             && find_file(pfile.name.c_str(), file_filters))
          {
            // add file specific parameters
            list<xml_attribute> file_attribs;
            heap_str fpath=pfile.name;
            char *filename=split_filepath(fpath.c_str());
            heap_str relative_dir;
            if(filename!=fpath.c_str())
            {
              relative_dir=fpath.c_str();
              relative_dir+='/';
            }
            heap_str fileext=".";
            fileext+=split_filename(filename);
            heap_str fullpath=full_rootdir;
            fullpath+=pfile.name;
            file_attribs.push_back(xml_attribute("Filename", filename));
            file_attribs.push_back(xml_attribute("Extension", fileext.c_str()));
            file_attribs.push_back(xml_attribute("FullPath", fullpath.c_str()));
            file_attribs.push_back(xml_attribute("RelativeDir", relative_dir.c_str()));

            // add filelist entry
            heap_str &filelist_entry=filelist_entries.push_back();
            replace_attribs(filelist_entry, filelist_file_template, file_attribs);
            replace_attribs(filelist_entry, filelist_entry, flist_attribs);
            break;
          }
        ++pfile_it;
      }
    }

    // split filelist entries to given number of filelist
    unsigned num_filelists=max(1u, flist.num_filelists);
    list<heap_str> filelists(num_filelists);
    {
      usize_t num_files_per_filelist=(filelist_entries.size()+num_filelists-1)/num_filelists;
      list<heap_str>::iterator filelist_entry_it=filelist_entries.begin();
      list<heap_str>::iterator filelist_it=filelists.begin();
      while(is_valid(filelist_it))
      {
        heap_str &filelist=*filelist_it;
        unsigned num_files=0;
        while(is_valid(filelist_entry_it) && num_files<num_files_per_filelist)
        {
          filelist+=*filelist_entry_it;
          ++num_files;
          ++filelist_entry_it;
        }
        ++filelist_it;
      }
    }

    // load filelist project template and construct filelists
    heap_str filelist_project_template;
    if(   flist.project_template.size()
       && load_text_file(filelist_project_template, flist.project_template.c_str(), pcfg_.project_file_path))
    {
      flist_attribs.push_back().name="Filelist";
      list<heap_str>::iterator filelist_it=filelists.begin();
      while(is_valid(filelist_it))
      {
        heap_str &filelist=*filelist_it;
        heap_str filelist_project;
        flist_attribs.back().value=filelist.c_str();
        replace_attribs(filelist_project, filelist_project_template, flist_attribs);
        filelist.swap(filelist_project);
        ++filelist_it;
      }
      flist_attribs.pop_back();
    }

    // write filelist if changed
    file_system_base &fsys=file_system_base::active();
    list<heap_str>::const_iterator filelist_it=filelists.begin();
    unsigned filelist_index=0;
    while(is_valid(filelist_it))
    {
      // setup filelist output filename
      heap_str output_filename;
      stack_str8 filelist_index_str;
      filelist_index_str.format("%03i", filelist_index);
      ++filelist_index;
      flist_attribs.push_back(xml_attribute("FilelistIndex", filelist_index_str.c_str()));
      replace_attribs(output_filename, flist.output_filename, flist_attribs);
      flist_attribs.pop_back();

      // write filelist
      const heap_str &filelist=*filelist_it;
      heap_str s;
      owner_ptr<bin_input_stream_base> ifile=fsys.open_read(output_filename.c_str(), pcfg_.project_file_path, fopencheck_none);
      if(ifile.data)
      {
        usize_t size=fsys.file_size(output_filename.c_str(), pcfg_.project_file_path);
        s.resize(size);
        ifile->read_bytes(s.data(), size);
      }
      if(!ifile.data || filelist!=s)
      {
        ifile=0;
        owner_ptr<bin_output_stream_base> ofile=afs_open_write(output_filename.c_str(), pcfg_.project_file_path);
        if(ofile.data)
          ofile->write_bytes(filelist.data(), filelist.size());
      }
      ++filelist_it;
    }

    // proceed to the next filelist
    ++flist_it;
  }
}
//----

void generate_project(const char *sxproj_name_, const char *sxproj_filename_, bin_input_stream_base &stream_, void(*generator_)(const project_config&), const char *compiler_tag_, const char *proj_dir_, const char *build_template_dir_)
{
  // load project config and generate project files
  logf("Generating \"%s\" project from %s\r\n", compiler_tag_, sxproj_filename_);
  stream_.rewind();
  project_config pcfg;
  pcfg.project_file_path=proj_dir_;
  pcfg.build_template_path=build_template_dir_;
  heap_str sxproj_name=sxproj_filename_;
  split_filename(sxproj_name.c_str());
  pcfg.parse(stream_, compiler_tag_, sxproj_name_?sxproj_name_:sxproj_name.c_str());
  (*generator_)(pcfg);
  export_filelists(pcfg);
}
//----

void generate_projects(const char *target_compilers_, const char *sxproj_name_, const char *sxproj_filename_, bin_input_stream_base &stream_, const char *proj_dir_, const char *build_template_dir_)
{
  // generate projects for given set of compilers
  heap_str target_compilers=target_compilers_;
  if(!target_compilers.size())
    target_compilers="VS2010 VS2012 VS2013 VS2015 VS2017 VS2019 VS2022 Xcode";
  char *p=target_compilers.c_str();
  do
  {
    char *next_p=str_tokenize_words(p);
    if(str_eq(p, "VS2010"))
      generate_project(sxproj_name_, sxproj_filename_, stream_, &generate_vs201x_project, "VS2010", proj_dir_, build_template_dir_);
    else if(str_eq(p, "VS2012"))
      generate_project(sxproj_name_, sxproj_filename_, stream_, &generate_vs201x_project, "VS2012", proj_dir_, build_template_dir_);
    else if(str_eq(p, "VS2013"))
      generate_project(sxproj_name_, sxproj_filename_, stream_, &generate_vs201x_project, "VS2013", proj_dir_, build_template_dir_);
    else if(str_eq(p, "VS2015"))
      generate_project(sxproj_name_, sxproj_filename_, stream_, &generate_vs201x_project, "VS2015", proj_dir_, build_template_dir_);
    else if(str_eq(p, "VS2017"))
      generate_project(sxproj_name_, sxproj_filename_, stream_, &generate_vs201x_project, "VS2017", proj_dir_, build_template_dir_);
    else if (str_eq(p, "VS2019"))
      generate_project(sxproj_name_, sxproj_filename_, stream_, &generate_vs201x_project, "VS2019", proj_dir_, build_template_dir_);
    else if (str_eq(p, "VS2022"))
      generate_project(sxproj_name_, sxproj_filename_, stream_, &generate_vs201x_project, "VS2022", proj_dir_, build_template_dir_);
    else if(str_eq(p, "Xcode"))
      generate_project(sxproj_name_, sxproj_filename_, stream_, &generate_xcode_project, "Xcode", proj_dir_, build_template_dir_);
    p=next_p;
  } while(*p);
}
//----------------------------------------------------------------------------


//============================================================================
// parse_argument
//============================================================================
void parse_argument(heap_str &arg_, const char **args_, unsigned num_args_, unsigned &idx_)
{
  // parse argument
  if(args_[idx_][2])
    arg_=args_[idx_]+2;
  else
    if(idx_+1<num_args_)
      arg_=args_[++idx_];
  str_lower(arg_.c_str());
}
//----------------------------------------------------------------------------


//============================================================================
// command_arguments
//============================================================================
struct command_arguments
{
  // construction
  command_arguments()
  {
    suppress_copyright=false;
  }
  //--------------------------------------------------------------------------

  heap_str in_filename;
  heap_str target_compilers;
  heap_str sxproj_name;
  bool suppress_copyright;
};
//----------------------------------------------------------------------------


//============================================================================
// parse_command_arguments
//============================================================================
bool parse_command_arguments(command_arguments &ca_, const char **args_, unsigned num_args_)
{
  for(unsigned arg_idx=0; arg_idx<num_args_; ++arg_idx)
  {
    // check compiler for option
    if(args_[arg_idx][0]=='-')
    {
      // switch to proper argument handling
      const char *carg=args_[arg_idx];
      usize_t arg_size=str_size(carg);
      switch(to_lower(carg[1]))
      {
        case 'h':
        {
          if(arg_size==2)
          {
            // output help
            logf("%s"
                  "Usage: Usage: project_gen [options] <.sxproj/.sxsln file>\r\n"
                  "\r\n"
                  "Options:\r\n"
                  "  -t \"<comp>\"   Target compilers (e.g. -t \"VS2010 VS2022\")\r\n"
                  "  comp          VS2010 - Visual Studio 2010\r\n"
                  "                VS2012 - Visual Studio 2012\r\n"
                  "                VS2013 - Visual Studio 2013\r\n"
                  "                VS2015 - Visual Studio 2015\r\n"
                  "                VS2017 - Visual Studio 2017\r\n"
                  "                VS2019 - Visual Studio 2019\r\n"
                  "                VS2022 - Visual Studio 2022\r\n"
                  "                Xcode - Xcode\r\n"
                  " -pn <name>     For .sxproj override SXProjName\r\n"
                  "\r\n"
                  "  -h            Print this screen\n"
                  "  -c            Suppress copyright message\r\n", s_copyright_message);
            return false;
          }
        } break;

        case 't':
        {
          if(arg_size==2)
          {
            // parse target compilers
            heap_str arg;
            parse_argument(arg, args_, num_args_, arg_idx);
            arg.resize(str_strip_outer_chars(arg.c_str(), '\"'));
            str_upper(arg.c_str());
            ca_.target_compilers.swap(arg);
          }
        } break;

        case 'p':
        {
          if(arg_size==3 && to_lower(carg[2])!='n' && arg_idx+1<num_args_)
            ca_.sxproj_name=args_[arg_idx+1];
        } break;

        case 'c':
        {
          if(arg_size==2)
            ca_.suppress_copyright=true;
        } break;
      }
    }
    else
    {
      ca_.in_filename=args_[arg_idx];
      ca_.in_filename.resize(str_strip_outer_chars(ca_.in_filename.c_str(), '\"'));
      str_replace(ca_.in_filename.c_str(), '\\', '/');
    }
  }

  // check for necessary arguments
  if(!ca_.in_filename.size())
  {
    // print info and exit
    logf("Usage: project_gen [options] <.sxproj/.sxsln file>   (-h for help)\r\n");
    return false;
  }

  if(!ca_.suppress_copyright)
    logf(s_copyright_message);
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// process_solution
//============================================================================
void process_solution(const solution_config &cfg_, const char *build_template_dir_)
{
  // process solution projects
  list<solution_project>::const_iterator proj_it=cfg_.projects.begin();
  while(is_valid(proj_it))
  {
    const solution_project &proj=*proj_it;
    heap_str proj_dir=cfg_.solution_file_path, proj_filepath=proj.file;
    const char *proj_filename=split_filepath(proj_filepath.c_str());
    if(proj_filepath.c_str()!=proj_filename)
    {
      if(proj_dir.size())
        proj_dir+='/';
      proj_dir+=proj_filepath.c_str();
    }
    owner_ptr<bin_input_stream_base> proj_file=afs_open_read(proj_filename, proj_dir.c_str(), fopencheck_none);
    if(proj_file.data)
      generate_projects(proj.compilers.c_str(), proj.sxproj_name.size()?proj.sxproj_name.c_str():0, proj_filename, *proj_file, proj_dir.c_str(), build_template_dir_);
    else
      errorf("Unable to open project file \"%s\" for reading\r\n", proj_filename);
    ++proj_it;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// main
//============================================================================
PFC_MAIN(const char *args_[], unsigned num_args_)
{
  // parse command arguments
  command_arguments ca;
  if(!parse_command_arguments(ca, args_, num_args_))
    return 0;

  // open sxproj/sxsln file
  owner_ref<file_system_base> fs=create_default_file_system(true);
  owner_ptr<bin_input_stream_base> in_file=fs->open_read(ca.in_filename.c_str());
  if(!in_file.data)
  {
    errorf("Unable to open input file \"%s\"\r\n", ca.in_filename.c_str());
    return -1;
  }
  const char *in_filename=split_filepath(ca.in_filename.c_str());
  const char *in_filedir=in_filename==ca.in_filename.c_str()?"":ca.in_filename.c_str();

  heap_str build_template_dir=executable_dir();
  build_template_dir+="build_templates";
  if(str_ieq(get_fileext(in_filename), "sxsln"))
  {
    // parse solution config
    solution_config config;
    config.parse(*in_file);
    config.solution_file_path=in_filedir;
    in_file=0;
    process_solution(config, build_template_dir.c_str());
  }
  else if(str_ieq(get_fileext(in_filename), "sxproj"))
    generate_projects(ca.target_compilers.c_str(), ca.sxproj_name.size()?ca.sxproj_name.c_str():0, in_filename, *in_file, in_filedir, build_template_dir.c_str());

  return 0;
}
//----------------------------------------------------------------------------
