//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "preprocessor.h"
#include "fsys/fsys.h"
#include "sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// clear_source_comments
//============================================================================
bool pfc::clear_source_comments(char *src_, bool is_block_comment_)
{
  // check for open block comment
  bool is_comment=is_block_comment_, is_line_comment=false;
  char *comment_start=src_;
  if(is_comment)
  {
    --src_;
    goto skip_comment;
  }

  // replace all commented out code with space (retain line feeds)
  while(*src_)
  {
    // check for a comment
    if(*src_++=='/' && (*src_=='*' || *src_=='/'))
    {
      // setup comment state
      is_line_comment=*src_=='/';
      is_comment=true;
      comment_start=src_-1;

      // skip comment
      skip_comment:
      while(*++src_)
      {
        // check for the end of comment
        if((is_line_comment && *src_=='\n') || (!is_line_comment && *src_=='*' && *++src_=='/'))
        {
          ++src_;
          is_comment=false;
          break;
        }
      }

      // clear commented code
      while(comment_start<src_)
      {
        if(*comment_start!='\r' && *comment_start!='\n')
          *comment_start=' ';
        ++comment_start;
      }
      if(is_comment && !is_line_comment)
        return true;
    }
  }
  return false;
}
//----------------------------------------------------------------------------


//============================================================================
// collect_source_dependencies
//============================================================================
void pfc::collect_source_dependencies(const char *filename_, array<heap_str> &dependencies_, bool verbose_)
{
  // create file path to given filename
  heap_str fpath=filename_;
  char *fname=split_filepath(fpath.c_str());
  if(fname==fpath.c_str())
    fpath="";
  else
  {
    fpath.resize(collapse_relative_dirs(fpath.c_str()));
    fpath+='/';
  }

  // read source
  heap_str source;
  read_file(file_system_base::active(), source, filename_);

  // clear comments and collect #include dependencies
  clear_source_comments(source.c_str());
  char *s=source.c_str();
  while(*s)
  {
    // check for preprocessor directive
    s=str_skip_whitespace(s);
    if(*s=='#')
    {
      // check for #include directive
      s=str_skip_whitespace(++s);
      if(str_eq(s, "include", 7))
      {
        // get #include file
        s=str_skip_whitespace(s+7);
        char eoi=*s=='<'?'>':*s=='\"'?'\"':0;
        if(eoi)
          ++s;
        char *incl_begin=s;
        while(*s && *s!='\r' && *s!='\n' && *s!=eoi)
          ++s;
        heap_str incl_file(incl_begin, unsigned(s-incl_begin));
        incl_file.resize(str_strip_outer_whitespace(incl_file.c_str(), true));
        str_replace(incl_file.c_str(), '\\', '/');
        heap_str orig_incl_file=incl_file;
        if(!is_absolute_filepath(incl_file.c_str()))
          incl_file.push_front(fpath.c_str(), fpath.size());
        str_lower(incl_file.c_str());

        // recursively collect #include file dependencies
        if(!is_valid(linear_search(dependencies_.begin(), dependencies_.size(), incl_file)))
        {
          if(!file_system_base::active().exists(incl_file.c_str()))
          {
            if(verbose_)
              errorf("#include file \"%s\" doesn't exist (#included in \"%s\").\r\n", orig_incl_file.c_str(), filename_);
          }
          else
          {
            dependencies_.push_back(incl_file);
            collect_source_dependencies(incl_file.c_str(), dependencies_);
          }
        }
      }
    }
    else
      while(*s && *s!='\n')
        ++s;
  }
}
//----------------------------------------------------------------------------


//============================================================================
// unfold_include_directives
//============================================================================
unsigned pfc::unfold_include_directives(heap_str &unfolded_code_, array<source_line_mapping> &line_map_, const char *source_code_, usize_t source_size_, const char *source_filename_, array<heap_str> *dependencies_, unsigned source_start_line_)
{
  // process lines in the input code
  mem_input_stream ms(source_code_, source_size_);
  text_input_stream ts(ms);
  char line_buffer[4096];
  bool is_comment_block=false;
  unsigned line_number=source_start_line_;
  while(!ts.is_eos())
  {
    // check for a pre-processor directive
    unsigned lsize=(unsigned)ts.read_line(line_buffer, sizeof(line_buffer), false);
    is_comment_block=clear_source_comments(line_buffer, is_comment_block);
    char *rc=str_skip_whitespace(line_buffer);
    bool is_include_line=false;
    if(*rc=='#')
    {
      // check for #include directive
      rc=str_skip_whitespace(rc+1);
      if(mem_eq(rc, "include", 7))
      {
        // get #include filename
        is_include_line=true;
        char *include_filename=str_skip_whitespace(rc+7);
        char *end=include_filename?str_find(include_filename+1, *include_filename=='<'?'>':'\"'):0;
        if(include_filename && end && (*include_filename=='<' || *include_filename=='\"'))
        {
          ++include_filename;
          *end=0;
          unsigned length=(unsigned)str_strip_outer_whitespace(include_filename, true);
          include_filename[length]=0;
        }
        else
        {
          errorf("%s(%i) : Invalid #include directive\r\n", source_filename_, line_number-source_start_line_+1, include_filename);
          return 0;
        }

        // add line mapping
        source_line_mapping &lm=line_map_.push_back();
        lm.filename=source_filename_;
        lm.unfolded_start_line=source_start_line_;
        lm.unfolded_end_line=line_number;

        // get filepath to the #include file
        heap_str include_filepath;
        if(!is_absolute_filepath(include_filename))
        {
          include_filepath=source_filename_;
          char *fn=split_filepath(include_filepath.c_str());
          include_filepath.resize(fn==include_filepath.c_str()?0:unsigned(fn-include_filepath.c_str()-1));
          if(include_filepath.size())
            include_filepath+='/';
          include_filepath.resize(collapse_relative_dirs(include_filepath.c_str()));
        }
        include_filepath+=include_filename;
        str_replace(include_filepath.c_str(), '\\', '/');

        // replace #include line with file content
        heap_str include_data;
        if(read_file(file_system_base::active(), include_data, include_filepath.c_str(), 0, fopencheck_none))
        {
          if(dependencies_ && !is_valid(linear_search(dependencies_->begin(), dependencies_->size(), include_filepath)))
            dependencies_->push_back(include_filepath);
          unsigned old_line_number=line_number;
          line_number=unfold_include_directives(unfolded_code_, line_map_, include_data.c_str(), include_data.size(), include_filepath.c_str(), dependencies_, line_number);
          if(!line_number)
            return 0;
          source_start_line_+=line_number-old_line_number-1;
        }
        else
        {
          errorf("%s(%i) : Cannot open include file: '%s': No such file or directory\r\n", source_filename_, line_number-source_start_line_+1, include_filename);
          return 0;
        }
      }
    }

    if(!is_include_line)
    {
      // add non-#include line
      unfolded_code_.push_back(line_buffer, lsize);
      unfolded_code_.push_back('\n');
      ++line_number;
    }
  }

  // add line mapping
  source_line_mapping &lm=line_map_.push_back();
  lm.filename=source_filename_;
  lm.unfolded_start_line=source_start_line_;
  lm.unfolded_end_line=line_number;
  return line_number;
}
//----------------------------------------------------------------------------
