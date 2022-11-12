//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// mesh_skeleton
//============================================================================
mesh_skeleton::mesh_skeleton()
{
  scale=inv_scale=1.0f;
}
//----------------------------------------------------------------------------


//============================================================================
// mesh_skeleton::joint
//============================================================================
mesh_skeleton::joint::joint()
{
  // init members
  parent_idx=0;
  name_idx=0;
  name_crc32=0;
  lod=0;
}
//----------------------------------------------------------------------------


//============================================================================
// mesh_segment
//============================================================================
mesh_segment::mesh_segment()
{
  // init segment
  lod=0;
  vertex_buffer=0;
  primitive_type=meshprim_none;
  num_primitives=0;
  prim_start_index=0;
  num_joints=0;
  joint_reindexing_start=0;
}
//----------------------------------------------------------------------------


//============================================================================
// mesh_collision_object
//============================================================================
mesh_collision_object::mesh_collision_object()
{
  joint_index=-1;
}
//----------------------------------------------------------------------------


//============================================================================
// mesh
//============================================================================
unsigned mesh::num_vertex_buffers() const
{
  return (unsigned)m_vertex_buffers.size();
}
//----

const mesh_vertex_buffer *mesh::vertex_buffers() const
{
  return m_vertex_buffers.data();
}
//----

const mesh_vertex_buffer &mesh::vertex_buffer(unsigned index_) const
{
  return m_vertex_buffers[index_];
}
//----

unsigned mesh::max_vertex_index() const
{
  // get maximum vertex index
  unsigned max_vertex_index=0;
  for(unsigned i=0; i<m_vertex_buffers.size(); ++i)
  {
    unsigned num_vertices=m_vertex_buffers[i].num_vertices();
    max_vertex_index=max(max_vertex_index, num_vertices?num_vertices-1:0);
  }
  return max_vertex_index;
}
//----

const mesh_skeleton *mesh::skeleton() const
{
  return m_skeleton.data;
}
//----

unsigned mesh::num_indices() const
{
  return (unsigned)m_indices.size();
}
//----

const uint32_t *mesh::indices() const
{
  return m_indices.data();
}
//----

unsigned mesh::num_segments() const
{
  return (unsigned)m_segments.size();
}
//----

const mesh_segment *mesh::segments() const
{
  return m_segments.data();
}
//----

const mesh_segment &mesh::segment(unsigned index_) const
{
  return m_segments[index_];
}
//----

unsigned mesh::num_collision_objects() const
{
  return (unsigned)m_coll_objects.size();
}
//----

const mesh_collision_object *mesh::collision_objects() const
{
  return m_coll_objects.data();
}
//----

const mesh_collision_object &mesh::collision_object(unsigned index_) const
{
  return m_coll_objects[index_];
}
//----

unsigned mesh::num_joint_reindices() const
{
  return (unsigned)m_joint_reindices.size();
}
//----

const uint16_t *mesh::joint_reindices() const
{
  return m_joint_reindices.data();
}
//----------------------------------------------------------------------------
