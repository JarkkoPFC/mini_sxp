//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_ENGINE_MESH_H
#define PFC_CORE_ENGINE_MESH_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/math/tform3.h"
#include "sxp_src/core_engine/loaders/dataio.h"
namespace pfc
{
class bin_input_stream_base;

// new
class mesh_vertex_buffer;
struct mesh_skeleton;
struct mesh_segment;
struct mesh_collision_object;
class mesh;
owner_ptr<mesh> load_mesh(bin_input_stream_base&);
owner_ptr<mesh> load_mesh(const char *filename_, const char *path_=0);
void random_mesh_surface_tforms(array<tform_rt3f>&, const mesh&, unsigned num_tforms_, unsigned seed_=0);
void transform_joints_j2p_to_b2o(tform_rt3f*, const mesh_skeleton&);
bool is_mesh_file_ext(const char *filename_ext_);
uint8_t subobject_lod(const char *subobject_name_);
bool is_collision_subobject(const char *subobject_name_);
enum {max_mesh_lods=16};
//----------------------------------------------------------------------------


//============================================================================
// e_vertex_channel
//============================================================================
enum e_vertex_channel
{
  vtxchannel_position,      // vec3f
  vtxchannel_normal,        // vec3f
  vtxchannel_binormal,      // vec3f
  vtxchannel_tangent,       // vec3f
  vtxchannel_uv,            // vec2f
  vtxchannel_color,         // color_rgbaf
  vtxchannel_joint_indices, // vec4<uint16_t>
  vtxchannel_joint_weights, // vec4f
};
PFC_ENUM(e_vertex_channel);
//----------------------------------------------------------------------------


//============================================================================
// e_mesh_primitive_type
//============================================================================
enum e_mesh_primitive_type
{
  meshprim_none,
  meshprim_pointlist,
  meshprim_linelist,
  meshprim_linestrip,
  meshprim_trilist,
  meshprim_tristrip,
  //----
  meshprim_enum_end
};
PFC_ENUM(e_mesh_primitive_type);
//----------------------------------------------------------------------------

unsigned num_primitives(e_mesh_primitive_type, unsigned num_vertices_);
unsigned num_primitive_vertices(e_mesh_primitive_type, unsigned num_primitives_);
//----------------------------------------------------------------------------


//============================================================================
// mesh_vertex_buffer
//============================================================================
class mesh_vertex_buffer
{ PFC_MONO(mesh_vertex_buffer) {PFC_VAR2(m_num_vertices, m_vtx_channels);}
public:
  // construction
  mesh_vertex_buffer();
  ~mesh_vertex_buffer();
  void clear();
  //--------------------------------------------------------------------------

  // data accessors
  unsigned num_vertices() const;
  const void *vertex_channel(e_vertex_channel, unsigned idx_=0) const;
  void *vertex_channel(e_vertex_channel, unsigned idx_=0);
  //--------------------------------------------------------------------------

  // mutators
  void add_channel(e_vertex_channel, const owner_data&, unsigned num_vertices_);
  //--------------------------------------------------------------------------

private:
  mesh_vertex_buffer(const mesh_vertex_buffer&); // not implemented
  void operator=(const mesh_vertex_buffer&); // not implemented
  //--------------------------------------------------------------------------

  uint32_t m_num_vertices;
  array<pair<e_vertex_channel, raw_data> > m_vtx_channels;
};
//----------------------------------------------------------------------------


//============================================================================
// mesh_skeleton
//============================================================================
struct mesh_skeleton
{ PFC_MONO(mesh_skeleton) {PFC_VAR3(scale, inv_scale, joints); PFC_HVAR(joint_names);}
  PFC_INLINE mesh_skeleton();
  //--------------------------------------------------------------------------

  //==========================================================================
  // joint
  //==========================================================================
  struct joint
  { PFC_MONO(joint) {PFC_VAR6(parent_idx, name_idx, name_crc32, lod, bind_j2p, bind_o2j);}
    // construction
    PFC_INLINE joint();
    //------------------------------------------------------------------------

    uint16_t parent_idx;    // index to the parent joints (always smaller than the current joint index, except for root=0)
    uint16_t name_idx;      // index to joints_names character array for the joint name
    uint32_t name_crc32;    // CRC32 of the joints name string
    uint8_t lod;            // lowest detail mesh LOD the joints is animated
    tform_rt3f bind_j2p;  // joints->parent space bind pose transform
    tform_rt3f bind_o2j;  // object->joints space bind pose transform
  };
  //--------------------------------------------------------------------------

  float scale, inv_scale;
  array<joint> joints;
  array<char> joint_names;
};
//----------------------------------------------------------------------------


//============================================================================
// mesh_segment
//============================================================================
struct mesh_segment
{ PFC_MONO(mesh_segment) {PFC_VAR4(material_name, primitive_type, num_primitives, num_joints); PFC_HVAR4(lod, vertex_buffer, prim_start_index, joint_reindexing_start);}
  // construction
  PFC_INLINE mesh_segment();
  //--------------------------------------------------------------------------

  stack_str64 material_name;
  uint8_t lod;
  uint8_t vertex_buffer;
  e_mesh_primitive_type primitive_type;
  uint32_t num_primitives;
  uint32_t prim_start_index;
  uint16_t num_joints;
  uint16_t joint_reindexing_start;
};
//----------------------------------------------------------------------------


//============================================================================
// mesh_collision_object
//============================================================================
struct mesh_collision_object
{ PFC_MONO(mesh_collision_object) {PFC_VAR3(joint_index, points, indices);}
  // construction
  PFC_INLINE mesh_collision_object();
  //--------------------------------------------------------------------------

  int32_t joint_index;
  array<vec3f> points;
  array<uint32_t> indices;  // triangle list indices
};
//----------------------------------------------------------------------------


//============================================================================
// mesh
//============================================================================
class mesh
{ PFC_MONO(mesh)
  {
    PFC_VAR4(m_vertex_buffers, m_segments, m_coll_objects, m_skeleton);
    PFC_HVAR2(m_indices, m_joint_reindices);
  }
public:
  // construction
  mesh();
  mesh(bin_input_stream_base&);
  ~mesh();
  e_file_format load(bin_input_stream_base&);
  mesh_vertex_buffer *create_vertex_buffers(unsigned num_vertex_buffers_);
  mesh_skeleton *create_skeleton();
  void swap_indices(array<uint32_t> &indices_);
  void swap_segments(array<mesh_segment>&);
  void swap_collision_objects(array<mesh_collision_object>&);
  void swap_joint_reindices(array<uint16_t>&);
  //--------------------------------------------------------------------------

  // mesh operations
  void optimize();
  void scale(ufloat_t scale_);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE unsigned num_vertex_buffers() const;
  PFC_INLINE const mesh_vertex_buffer *vertex_buffers() const;
  PFC_INLINE const mesh_vertex_buffer &vertex_buffer(unsigned index_) const;
  PFC_INLINE unsigned max_vertex_index() const;
  PFC_INLINE const mesh_skeleton *skeleton() const;
  PFC_INLINE unsigned num_indices() const;
  PFC_INLINE const uint32_t *indices() const;
  PFC_INLINE unsigned num_segments() const;
  PFC_INLINE const mesh_segment *segments() const;
  PFC_INLINE const mesh_segment &segment(unsigned index_) const;
  PFC_INLINE unsigned num_collision_objects() const;
  PFC_INLINE const mesh_collision_object *collision_objects() const;
  PFC_INLINE const mesh_collision_object &collision_object(unsigned index_) const;
  PFC_INLINE unsigned num_joint_reindices() const;
  PFC_INLINE const uint16_t *joint_reindices() const;
  //--------------------------------------------------------------------------

private:
  mesh(const mesh&); // not implemented
  void operator=(const mesh&); // not implemented
  //--------------------------------------------------------------------------

  sarray<mesh_vertex_buffer, 4> m_vertex_buffers;
  owner_ptr<mesh_skeleton> m_skeleton;
  array<uint32_t> m_indices;
  array<mesh_segment> m_segments;
  array<mesh_collision_object> m_coll_objects;
  array<uint16_t> m_joint_reindices;
};
//----------------------------------------------------------------------------

//============================================================================
#include "mesh.inl"
} // namespace pfc
#endif
