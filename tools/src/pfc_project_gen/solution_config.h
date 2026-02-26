//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_PROJGEN_SOLUTION_CONFIG_H
#define PFC_PROJGEN_SOLUTION_CONFIG_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/containers.h"
#include "sxp_src/core/str.h"
namespace pfc
{
class bin_input_stream_base;
struct xml_attribute;

// new
struct solution_project;
class solution_config;
//----------------------------------------------------------------------------


//============================================================================
// solution_project
//============================================================================
struct solution_project
{
  // construction
  solution_project();
  //--------------------------------------------------------------------------

  heap_str file;
  heap_str sxproj_name;
  heap_str compilers;
};
//----------------------------------------------------------------------------


//============================================================================
// solution_config
//============================================================================
class solution_config
{
public:
  // construction
  solution_config();
  ~solution_config();
  void parse(bin_input_stream_base&);
  //--------------------------------------------------------------------------

  // parsed solution properties
  list<xml_attribute> projects_attribs;
  list<solution_project> projects;
  // project properties
  const char *solution_file_path;
  //--------------------------------------------------------------------------

private:
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
