//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_ENGINE_DATAIO_H
#define PFC_CORE_ENGINE_DATAIO_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/math/math.h"
#include "sxp_src/core/xml.h"
namespace pfc
{

// new
class collada_info;
class collada_data;
//----------------------------------------------------------------------------


//============================================================================
// e_file_format
//============================================================================
enum e_file_format
{
  filefmt_none,
  // texture file formats
  filefmt_dds,
  filefmt_jp2,
  filefmt_jpg,
  filefmt_png,
  filefmt_psd,
  filefmt_tga,
  filefmt_tiff,
  filefmt_webp,
  // 3d asset file formats
  filefmt_3ds,
  filefmt_fbx,
  filefmt_lwo,
  filefmt_obj,
  filefmt_collada,
  filefmt_bvh,
  // audio file formats
  filefmt_wav,
  filefmt_ogg,
};
//----------------------------------------------------------------------------


//============================================================================
// e_file_format_support
//============================================================================
enum e_file_format_support
{
  filefmtsupport_none      = 0x00,
  filefmtsupport_read      = 0x01,
  filefmtsupport_write     = 0x02,
  filefmtsupport_readwrite = 0x03,
};
//----------------------------------------------------------------------------


//============================================================================
// e_collada_input_semantic
//============================================================================
enum e_collada_input_semantic
{
  collsemantic_none,
  collsemantic_vertex,
  collsemantic_position,
  collsemantic_texcoord,
  collsemantic_normal,
  collsemantic_textangent,
  collsemantic_texbinormal,
  collsemantic_joint,
  collsemantic_inv_bind_matrix,
  collsemantic_weight,
  collsemantic_input,
  collsemantic_output,
  collsemantic_in_tangent,
  collsemantic_out_tangent,
  collsemantic_interpolation,
};
//----------------------------------------------------------------------------


//============================================================================
// collada_info
//============================================================================
class collada_info
{
public:
  // nested types
  typedef xml_input_stream::string_t string_t;
  //--------------------------------------------------------------------------

  // construction
  collada_info();
  void parse_asset_properties(xml_input_stream&, string_t&);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE const mat33f &basis_tform() const;
  //--------------------------------------------------------------------------

private:
  mat33f m_basis_tform;
};
//----------------------------------------------------------------------------


//============================================================================
// collada_data
//============================================================================
class collada_data
{
public:
  // nested types
  typedef xml_input_stream::string_t string_t;
  template<typename> struct data_array;
  struct source;
  struct source_input;
  //--------------------------------------------------------------------------

  // construction
  collada_data();
  PFC_INLINE source &append_source();
  //--------------------------------------------------------------------------

  // data parsing
  void parse_data_source(xml_input_stream&, string_t&);
  void parse_source_input_attribs(array<source_input>&, xml_input_stream&, string_t&);
  //--------------------------------------------------------------------------

  // data accessors
  PFC_INLINE const data_array<heap_str> &name_array(unsigned idx_) const;
  PFC_INLINE const data_array<float> &float_array(unsigned idx_) const;
  //--------------------------------------------------------------------------

private:
  //==========================================================================
  // e_collada_input_semantic_type
  //==========================================================================
  enum e_collada_input_semantic_type
  {
    collsemantictype_none,
    collsemantictype_reference,
    collsemantictype_float,
    collsemantictype_name,
  };
  //--------------------------------------------------------------------------

  e_collada_input_semantic input_semantic(const string_t&);
  e_collada_input_semantic_type input_semantic_type(e_collada_input_semantic);
  //--------------------------------------------------------------------------

  deque<data_array<float> > m_data_array_float;
  deque<data_array<heap_str> > m_data_array_name;
  array<source> m_sources;
};
//----------------------------------------------------------------------------

//============================================================================
// collada_data::data_array
//============================================================================
template<typename T>
struct collada_data::data_array
{
  // construction and operations
  PFC_INLINE data_array();
  PFC_INLINE bool operator==(const string_t&) const;
  //--------------------------------------------------------------------------

  heap_str id;
  array<T> data;
  unsigned stride;
};
//----------------------------------------------------------------------------

//============================================================================
// collada_data::source_input
//============================================================================
struct collada_data::source_input
{
  // construction and operations
  PFC_INLINE source_input();
  PFC_INLINE bool operator==(e_collada_input_semantic) const;
  //--------------------------------------------------------------------------

  e_collada_input_semantic semantic;
  unsigned array_index;
  unsigned offset;
  unsigned set;
};
//----------------------------------------------------------------------------

//============================================================================
// collada_data::source
//============================================================================
struct collada_data::source
{
  // operations
  PFC_INLINE bool operator==(const string_t&) const;
  //--------------------------------------------------------------------------

  heap_str id;
  array<source_input> inputs;
};
//----------------------------------------------------------------------------

//============================================================================
#include "dataio.inl"
} // namespace pfc
#endif
