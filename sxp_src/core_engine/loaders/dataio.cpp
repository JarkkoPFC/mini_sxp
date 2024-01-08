//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "dataio.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// collada_info
//============================================================================
collada_info::collada_info()
{
  m_basis_tform.set(1.0f, 0.0f,  0.0f,
                    0.0f, 1.0f,  0.0f,
                    0.0f, 0.0f, -1.0f);
}
//----

void collada_info::parse_asset_properties(xml_input_stream &stream_, string_t &item_name_)
{
  // parse "asset" sub-tags
  while(stream_.parse_element(item_name_, true))
  {
    if(item_name_=="up_axis")
    {
      string_t axis;
      stream_.read_word(axis);
      if(axis=="Z_UP")
      {
        // setup transformation to flip y-axis
        m_basis_tform.set(1.0f,  0.0f, 0.0f,
                          0.0f, -1.0f, 0.0f,
                          0.0f,  0.0f, 1.0f);
      }
    }
    stream_.skip_element();
  }
}
//----------------------------------------------------------------------------


//============================================================================
// collada_data
//============================================================================
collada_data::collada_data()
{
}
//----

void collada_data::parse_data_source(xml_input_stream &stream_, string_t &item_name_)
{
  // parse "source" attributes and sub-tags
  unsigned *stride=0;
  heap_str source_id;
  stream_.find_attrib_str("id", source_id);
  PFC_CHECK_MSG(source_id.size(), ("Source has no ID\r\n"));
  while(stream_.parse_element(item_name_))
  {
    if(item_name_=="float_array")
    {
      // read new float array
      unsigned num_floats=0;
      stream_.find_attrib("count", num_floats);
      data_array<float> &arr=m_data_array_float.push_back();
      arr.id.swap(source_id);
      stride=&arr.stride;
      arr.data.resize(num_floats);
      stream_.read(arr.data.data(), num_floats);
      stream_.skip_element();
    }
    else if(item_name_=="Name_array")
    {
      // read new name array
      unsigned num_names=0;
      data_array<heap_str> &arr=m_data_array_name.push_back();
      arr.id.swap(source_id);
      stream_.find_attrib("count", num_names);
      arr.data.resize(num_names);
      for(unsigned i=0; i<num_names; ++i)
        stream_.read_word(arr.data[i]);
      stream_.skip_element();
    }
    else if(item_name_=="technique_common")
    {
      // parse "technique_common" sub-tags
      stream_.skip_attribs();
      while(stream_.parse_element(item_name_))
      {
        if(stride && item_name_=="accessor")
          stream_.find_attrib("stride", *stride);
        stream_.skip_element();
      }
    }
    else
      stream_.skip_element();
  }
}
//----

void collada_data::parse_source_input_attribs(array<source_input> &inputs_, xml_input_stream &stream_, string_t &item_name_)
{
  // parse "input" attributes
  source_input input;
  string_t input_source;
  while(stream_.start_attrib_parsing(item_name_))
  {
    if(item_name_=="semantic")
    {
      // read input semantic
      string_t semantic;
      stream_.read_word(semantic);
      input.semantic=input_semantic(semantic);
    }
    else if(item_name_=="source")
    {
      // read input source
      stream_.read_word(input_source);
      input_source.remove_front(1);
    }
    else if(item_name_=="offset")
      stream_>>input.offset;
    else if(item_name_=="set")
      stream_>>input.set;
    stream_.end_attrib_parsing();
  }

  // search data source for the input semantic
  switch(input.semantic)
  {
    // undefined semantics
    case collsemantic_none: PFC_ERROR("No semantic defined for the input\r\n"); break;

    // vertex input semantic
    case collsemantic_vertex:
    {
      // add inputs of the source
      source *it=linear_search(m_sources.begin(), m_sources.size(), input_source);
      PFC_CHECK_MSG(it, ("Unknown source input: %s\r\n", input_source.c_str()));
      const source_input *inputs=it->inputs.data();
      unsigned num_inputs=(unsigned)it->inputs.size();
      for(unsigned i=0; i<num_inputs; ++i)
      {
        source_input in=*inputs++;
        in.offset+=input.offset;
        inputs_.push_back(in);
      }
    } break;

    // default input semantic
    default:
    {
      // add source input
      switch(input_semantic_type(input.semantic))
      {
        // float data
        case collsemantictype_float:
        {
          deque<data_array<float> >::const_iterator it=linear_search(m_data_array_float.begin(), m_data_array_float.size(), input_source);
          PFC_CHECK_MSG(is_valid(it), ("Unknown source input: %s\r\n", input_source.c_str()));
          if(is_valid(it))
            input.array_index=(unsigned)it.index();
        } break;

        // name data
        case collsemantictype_name:
        {
          deque<data_array<heap_str> >::const_iterator it=linear_search(m_data_array_name.begin(), m_data_array_name.size(), input_source);
          PFC_CHECK_MSG(is_valid(it), ("Unknown source input: %s\r\n", input_source.c_str()));
          if(is_valid(it))
            input.array_index=(unsigned)it.index();
        } break;

        // unsupported
        default: PFC_ERROR("Unsupported input semantic\r\n");
      }
      inputs_.push_back(input);
    }
  }
}
//----------------------------------------------------------------------------

e_collada_input_semantic collada_data::input_semantic(const string_t &semantic_)
{
  // map input semantic string to enumerated value
  if(semantic_=="VERTEX") return collsemantic_vertex;
  if(semantic_=="POSITION") return collsemantic_position;
  if(semantic_=="TEXCOORD") return collsemantic_texcoord;
  if(semantic_=="NORMAL") return collsemantic_normal;
  if(semantic_=="TEXTANGENT") return collsemantic_textangent;
  if(semantic_=="TEXBINORMAL") return collsemantic_texbinormal;
  if(semantic_=="JOINT") return collsemantic_joint;
  if(semantic_=="INV_BIND_MATRIX") return collsemantic_inv_bind_matrix;
  if(semantic_=="WEIGHT") return collsemantic_weight;
  if(semantic_=="INPUT") return collsemantic_input;
  if(semantic_=="OUTPUT") return collsemantic_output;
  if(semantic_=="IN_TANGENT") return collsemantic_in_tangent;
  if(semantic_=="OUT_TANGENT") return collsemantic_out_tangent;
  if(semantic_=="INTERPOLATION") return collsemantic_interpolation;

  // unsupported semantic
  PFC_WARNF("Unsupported input semantic: %s\r\n", semantic_.c_str());
  return collsemantic_none;
}
//----

collada_data::e_collada_input_semantic_type collada_data::input_semantic_type(e_collada_input_semantic semantic_)
{
  // return semantic type
  switch(int(semantic_))
  {
    case collsemantic_none: return collsemantictype_none;
    case collsemantic_vertex: return collsemantictype_reference;
    case collsemantic_joint:
    case collsemantic_interpolation: return collsemantictype_name;
  }
  return collsemantictype_float;
}
//----------------------------------------------------------------------------
