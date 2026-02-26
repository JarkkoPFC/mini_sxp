//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "solution_config.h"
#include "project_config.h"
#include "sxp_src/core/xml.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// solution_project
//============================================================================
solution_project::solution_project()
{
}
//----------------------------------------------------------------------------


//============================================================================
// solution_config
//============================================================================
solution_config::solution_config()
{
}
//----

solution_config::~solution_config()
{
}
//----

void solution_config::parse(bin_input_stream_base &stream_)
{
  // setup structure for XML parsing
  // <Projects>
  xml_stream_parser parser;
  parser.begin_element("Projects").
           attribs_ftl(projects_attribs);

    // <Project>
    parser.begin_element("Project", projects).
             attrib("File", &solution_project::file).
             attrib("SXProjName", &solution_project::sxproj_name).
             attrib("Compilers", &solution_project::compilers).
           end_element();
  parser.end_element();

  // parse XML stream
  xml_input_stream xml_stream(stream_);
  parser.process_stream(xml_stream);

  list<solution_project>::iterator proj_it=projects.begin();
  while(is_valid(proj_it))
  {
    replace_attribs(proj_it->compilers, proj_it->compilers, projects_attribs);
    ++proj_it;
  }
}
//----------------------------------------------------------------------------
