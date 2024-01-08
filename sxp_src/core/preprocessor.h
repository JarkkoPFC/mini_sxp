//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_PREPROCESSOR_H
#define PFC_CORE_PREPROCESSOR_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
#include "containers.h"
#include "str.h"
namespace pfc
{

// new
struct preprocessor_definition;
struct source_line_mapping;
bool clear_source_comments(char*, bool is_block_comment_=false);
void collect_source_dependencies(const char *filename_, array<heap_str> &dependencies_, bool verbose_=false);
unsigned unfold_include_directives(heap_str &unfolded_code_, array<source_line_mapping>&, const char *source_, usize_t source_size_, const char *source_filename_, array<heap_str> *dependencies_=0, unsigned source_start_line_=1);
//----------------------------------------------------------------------------


//============================================================================
// preprocessor_definition
//============================================================================
struct preprocessor_definition
{
  heap_str name;
  heap_str value;
};
//----------------------------------------------------------------------------


//============================================================================
// source_line_mapping
//============================================================================
struct source_line_mapping
{
  heap_str filename;
  unsigned unfolded_start_line;
  unsigned unfolded_end_line;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
