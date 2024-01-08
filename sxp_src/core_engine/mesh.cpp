//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "mesh.h"
#include "sxp_src/core/fsys/fsys.h"
#include "sxp_src/core/math/tform3.h"
#include "sxp_src/core/math/color.h"
#include "sxp_src/core/sort.h"
#include "sxp_src/core/class.h"
#ifdef PFC_ENGINEOP_NVTRISTRIP
#include "sxp_extlibs/nvtristrip/src/NvTriStrip.h"
#endif
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// external library dependencies
//============================================================================
// nvtristrip
#ifdef PFC_ENGINEOP_NVTRISTRIP
#pragma comment(lib, PFC_STR(PFC_CAT2(nvtristrip_,PFC_BUILD_STR)PFC_COMPILER_LIB_EXT))
#endif
//----------------------------------------------------------------------------


//============================================================================
// e_vertex_channel
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_vertex_channel
#define PFC_ENUM_PREFIX vtxchannel_
#define PFC_ENUM_VALS PFC_ENUM_VAL(position)\
                      PFC_ENUM_VAL(normal)\
                      PFC_ENUM_VAL(binormal)\
                      PFC_ENUM_VAL(tangent)\
                      PFC_ENUM_VAL(uv)\
                      PFC_ENUM_VAL(color)\
                      PFC_ENUM_VAL(joint_indices)\
                      PFC_ENUM_VAL(joint_weights)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// e_mesh_primitive_type
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_mesh_primitive_type
#define PFC_ENUM_PREFIX meshprim_
#define PFC_ENUM_VALS PFC_ENUM_VAL(pointlist)\
                      PFC_ENUM_VAL(linelist)\
                      PFC_ENUM_VAL(linestrip)\
                      PFC_ENUM_VAL(trilist)\
                      PFC_ENUM_VAL(tristrip)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// num_primitives
//============================================================================
unsigned pfc::num_primitives(e_mesh_primitive_type type_, unsigned num_vertices_)
{
  // switch to proper primitive type handling
  switch(unsigned(type_))
  {
    case meshprim_pointlist: return num_vertices_;

    case meshprim_linelist:
    {
      PFC_ASSERT_PEDANTIC_MSG((num_vertices_&1)==0, ("Invalid number of vertices (%i) for \"%s\" primitive\r\n", num_vertices_, enum_string(type_)));
      return num_vertices_/2;
    }

    case meshprim_linestrip:
    {
      PFC_ASSERT_PEDANTIC_MSG(num_vertices_!=1, ("Invalid number of vertices (%i) for \"%s\" primitive\r\n", num_vertices_, enum_string(type_)));
      return num_vertices_?num_vertices_-1:0;
    }

    case meshprim_trilist:
    {
      PFC_ASSERT_PEDANTIC_MSG((num_vertices_%3)==0, ("Invalid number of vertices (%i) for \"%s\" primitive\r\n", num_vertices_, enum_string(type_)));
      return num_vertices_/3;
    }

    case meshprim_tristrip:
    {
      PFC_ASSERT_PEDANTIC_MSG(!num_vertices_ || num_vertices_>2, ("Invalid number of vertices (%i) for \"%s\" primitive\r\n", num_vertices_, enum_string(type_)));
      return num_vertices_?num_vertices_-2:0;
    }
  }

  // unsupported type
  PFC_ERRORF("Unsupported primitive type (%s)\r\n", enum_string(type_));
  return 0;
}
//----------------------------------------------------------------------------


//============================================================================
// num_primitive_vertices
//============================================================================
unsigned pfc::num_primitive_vertices(e_mesh_primitive_type type_, unsigned num_primitives_)
{
  // switch to proper primitive type handling
  switch(unsigned(type_))
  {
    case meshprim_pointlist:      return num_primitives_;
    case meshprim_linelist:       return num_primitives_*2;
    case meshprim_linestrip:      return num_primitives_+1;
    case meshprim_trilist:        return num_primitives_*3;
    case meshprim_tristrip:       return num_primitives_+2;
  }

  // unsupported type
  PFC_ERRORF("Unsupported primitive type (%s)\r\n", enum_string(type_));
  return 0;
}
//----------------------------------------------------------------------------


//============================================================================
// load_mesh
//============================================================================
owner_ptr<mesh> pfc::load_mesh(bin_input_stream_base &stream_)
{
  // check for SXE mesh format
  char id[16];
  stream_.read_bytes(id, 16);
  stream_.rewind(16);
  if(mem_eq(id, "pfc_archsxe_mesh", 16))
    return read_object<mesh>(stream_);

  // load non-SXE mesh
  owner_ptr<mesh> m=PFC_NEW(mesh);
  return m.data->load(stream_)?m:owner_ptr<mesh>(0);
}
//----

owner_ptr<mesh> pfc::load_mesh(const char *filename_, const char *path_)
{
  // try to load a mesh file
  owner_ptr<bin_input_stream_base> f=afs_open_read(filename_, path_);
  if(!f.data)
  {
    PFC_WARNF("Unable to open mesh file \"%s\"\r\n", afs_complete_path(filename_, path_).c_str());
    return 0;
  }
  return load_mesh(*f.data);
}
//----------------------------------------------------------------------------


//============================================================================
// is_mesh_file_ext
//============================================================================
bool pfc::is_mesh_file_ext(const char *filename_ext_)
{
  // check if file extension is for mesh file
  stack_str16 fe=filename_ext_;
  str_lower(fe.c_str());
  if(fe=="3ds" || fe=="lwo" || fe=="lxo" || fe=="obj" || fe=="dae" || fe=="sxe_mesh")
    return true;
  return false;
}
//----------------------------------------------------------------------------


//============================================================================
// subobject_lod
//============================================================================
uint8_t pfc::subobject_lod(const char *subobject_name_)
{
  // get LOD from the object name (search for case-sensitive "LODn" sub-string)
  const char *n=subobject_name_, *end=n+str_size(n);
  while((n=str_find_substr(n, "LOD"))!=0)
  {
    const char *subend=n+3;
    if(   (n==subobject_name_ || !is_latin_alphanumeric(n[-1]))
       && (subend!=end && is_decimal(*subend)))
    {
      // try to parse lod number from the found string
      mem_input_stream mstream(n+3);
      text_input_stream tstream(mstream);
      unsigned lod;
      if(tstream.read(lod))
      {
        PFC_CHECK_MSG(lod<max_mesh_lods, ("Object LOD number must be less than %i (%i)\r\n", max_mesh_lods, lod));
        return uint8_t(lod);
        break;
      }
    }

    // proceed to the next "LOD" sub-string
    n=subend;
  }
  return 0;
}
//----------------------------------------------------------------------------


//============================================================================
// is_collision_subobject
//============================================================================
bool pfc::is_collision_subobject(const char *subobject_name_)
{
  // search for "CVOL" sub-string from the object name
  const char *n=subobject_name_, *end=n+str_size(n);
  while((n=str_find_substr(n, "CVOL"))!=0)
  {
    const char *subend=n+4;
    if(   (n==subobject_name_ || !is_latin_alphanumeric(n[-1]))
       && (subend==end || !is_latin_alphanumeric(*subend)))
      return true;
    n=subend;
  }
  return false;
}
//----------------------------------------------------------------------------


//============================================================================
// random_mesh_surface_tforms
//============================================================================
struct probability_surface_tri
{
  PFC_INLINE bool operator<(float p_) const
  {
    return p_end<p_;
  }
  //----

  PFC_INLINE bool operator==(float p_) const
  {
    return p_>=p_start && p_<=p_end;
  }
  //--------------------------------------------------------------------------

  vec3f p0, p1, p2;
  vec3f n0, n1, n2;
  ufloat_t p_start, p_end;  // probability range [p_start, p_end[
};
//----------------------------------------------------------------------------

void pfc::random_mesh_surface_tforms(array<tform_rt3f> &tforms_, const mesh &mesh_, unsigned num_tforms_, unsigned seed_)
{
  // generate triangles with probabilities based on triangle areas
  deque<probability_surface_tri> tris;
  const uint32_t *indices=mesh_.indices();
  unsigned num_segments=mesh_.num_segments();
  udouble_t prob_total=0.0;
  for(unsigned si=0; si<num_segments; ++si)
  {
    // get vertex channel data for the segment
    const mesh_segment &seg=mesh_.segment(si);
    const mesh_vertex_buffer &vbuf=mesh_.vertex_buffer(seg.vertex_buffer);
    const vec3f *chl_pos=(vec3f*)vbuf.vertex_channel(vtxchannel_position);
    const vec3f *chl_nrm=(vec3f*)vbuf.vertex_channel(vtxchannel_normal);

    // switch to proper primitive type processing
    switch(seg.primitive_type)
    {
      // process triangle list primitives
      case meshprim_trilist:
      {
        unsigned num_prims=seg.num_primitives;
        for(unsigned i=0; i<num_prims; ++i)
        {
          // setup triangle vertex positions and normals
          probability_surface_tri tri;
          unsigned i0=indices[seg.prim_start_index+i*3+0];
          unsigned i1=indices[seg.prim_start_index+i*3+1];
          unsigned i2=indices[seg.prim_start_index+i*3+2];
          tri.p0=chl_pos[i0];
          tri.p1=chl_pos[i1];
          tri.p2=chl_pos[i2];
          vec3f normal=cross(tri.p1-tri.p0, tri.p2-tri.p0);
          if(chl_nrm)
          {
            tri.n0=chl_nrm[i0];
            tri.n1=chl_nrm[i1];
            tri.n2=chl_nrm[i2];
          }
          else
            tri.n0=tri.n1=tri.n2=unit_z(normal);

          // calculate triangle probability weight (area) and store the triangle
          tri.p_start=0.0f;
          tri.p_end=norm(normal);
          prob_total+=tri.p_end;
          tris.push_back(tri);
        }
      } break;

      // process triangle strip primitives
      case meshprim_tristrip:
      {
        /*todo*/
        PFC_ERROR_NOT_IMPL();
      } break;

      // unsupported primitive type
      default: PFC_WARNF("Skipping segment using primitive \"%s\"\r\n", enum_string(seg.primitive_type));
    }
  }

  // check for triangles for transformation generation
  unsigned num_tris=(unsigned)tris.size();
  if(!num_tris)
    return;

  // calculate normalized probability ranges for triangles
  udouble_t inv_prop_total=rcp_z(prob_total);
  udouble_t prob_sum=0.0;
  for(unsigned i=0; i<num_tris; ++i)
  {
    tris[i].p_start=ufloat_t(prob_sum);
    prob_sum+=tris[i].p_end*inv_prop_total;
    tris[i].p_end=ufloat_t(prob_sum);
  }
  tris[num_tris-1].p_end=2.0f;

  // generate transforms on the mesh using the triangles
  rng_simple rng(seed_);
  tforms_.resize(num_tforms_);
  for(unsigned i=0; i<num_tforms_; ++i)
  {
    // get random triangle by using probabilities (even distribution on mesh)
    deque<probability_surface_tri>::iterator it=binary_search(tris.begin(), num_tris, rng.rand_ureal1());
    PFC_ASSERT(is_valid(it));
    const probability_surface_tri &tri=*it;

    // calculate random barycentric coordinates for the triangle
    ufloat1_t a=rng.rand_ureal1();
    ufloat1_t b=rng.rand_ureal1();
    if(a+b>1.0f)
    {
      a=1.0f-a;
      b=1.0f-b;
    }
    ufloat1_t c=1.0f-a-b;

    // calculate transformation by using the coordinates
    vec3f pos=tri.p0*a+tri.p1*b+tri.p2*c;
    vec3f normal=unit_z(tri.n0*a+tri.n1*b+tri.n2*c);
    tforms_[i].set(zrot_u(normal), pos);
  }
}
//----------------------------------------------------------------------------


//============================================================================
// transform_joints_j2p_to_b2o
//============================================================================
void pfc::transform_joints_j2p_to_b2o(tform_rt3f *tforms_, const mesh_skeleton &skel_)
{
  // construct bind->joint->object space transforms for joint->parent transforms
  PFC_PERF_TIMER_AUTO(transform_joints_j2p_to_b2o, "animation", "transform_joints_j2p_to_b2o()");
  unsigned num_joints=(unsigned)skel_.joints.size();
  const mesh_skeleton::joint *joints=skel_.joints.data();
  float scale=skel_.scale;
  tforms_[0].translation*=scale;
  for(unsigned i=1; i<num_joints; ++i)
  {
    tforms_[i].translation*=scale;
    tforms_[i]*=tforms_[joints[i].parent_idx];
  }
  for(unsigned i=0; i<num_joints; ++i)
    tforms_[i]=joints[i].bind_o2j*tforms_[i];
}
//----------------------------------------------------------------------------


//============================================================================
// mesh_vertex_buffer
//============================================================================
mesh_vertex_buffer::mesh_vertex_buffer()
{
  m_num_vertices=0;
}
//----

mesh_vertex_buffer::~mesh_vertex_buffer()
{
  clear();
}
//----

void mesh_vertex_buffer::clear()
{
  // release vertex buffer channels
  m_num_vertices=0;
  m_vtx_channels.clear();
}
//----------------------------------------------------------------------------

unsigned mesh_vertex_buffer::num_vertices() const
{
  return m_num_vertices;
}
//----

const void *mesh_vertex_buffer::vertex_channel(e_vertex_channel vc_, unsigned idx_) const
{
  // search for the vertex channel
  unsigned num_channels=(unsigned)m_vtx_channels.size();
  const pair<e_vertex_channel, raw_data> *d=m_vtx_channels.data();
  while(num_channels--)
  {
    if(d->first==vc_)
      if(!idx_--)
        return d->second.data;
    ++d;
  }
  return 0;
}
//----

void *mesh_vertex_buffer::vertex_channel(e_vertex_channel vc_, unsigned idx_)
{
  return (void*)((const mesh_vertex_buffer*)this)->vertex_channel(vc_, idx_);
}
//----------------------------------------------------------------------------

void mesh_vertex_buffer::add_channel(e_vertex_channel vc_, const owner_data &data_, unsigned num_vertices_)
{
  unsigned element_size=0;
  switch(vc_)
  {
    case vtxchannel_position:
    case vtxchannel_normal:
    case vtxchannel_binormal:
    case vtxchannel_tangent:       element_size=sizeof(vec3f); break;
    case vtxchannel_uv:            element_size=sizeof(vec2f); break;
    case vtxchannel_color:         element_size=sizeof(color_rgbaf); break;
    case vtxchannel_joint_indices: element_size=sizeof(vec4<uint16_t>); break;
    case vtxchannel_joint_weights: element_size=sizeof(vec4f); break;
    default: PFC_ERROR("Unsupported vertex channel type\r\n");
  }

  // add new channel to the vertex buffer
  PFC_ASSERT_MSG(!m_num_vertices || num_vertices_==m_num_vertices, ("Adding vertex channel with unequal number of vertex elements (%i != %i)\r\n", num_vertices_, m_num_vertices));
  m_num_vertices=num_vertices_;
  pair<e_vertex_channel, raw_data> &channel=m_vtx_channels.push_back();
  channel.first=vc_;
  channel.second.data=data_.data;
  channel.second.size=num_vertices_*element_size;
  data_.data=0;
}
//----------------------------------------------------------------------------


//============================================================================
// mesh
//============================================================================
mesh::mesh()
{
}
//----

mesh::mesh(bin_input_stream_base &stream_)
{
  load(stream_);
}
//----

mesh::~mesh()
{
}
//----

namespace pfc
{
  bool load_mesh_fbx(mesh&, bin_input_stream_base&);
  bool load_mesh_3ds(mesh&, bin_input_stream_base&);
  bool load_mesh_collada(mesh&, bin_input_stream_base&);
  bool load_mesh_lwo(mesh&, bin_input_stream_base&);
  bool load_mesh_obj(mesh&, bin_input_stream_base&);
} // namespace pfc
//----

e_file_format mesh::load(bin_input_stream_base &stream_)
{
  // clear the mesh
  m_vertex_buffers.clear();
  m_indices.clear();
  m_segments.clear();
  m_skeleton=0;

  // try to load the mesh with different format loaders
  e_file_format fmt=filefmt_none;
  if(load_mesh_fbx(*this, stream_))
    fmt=filefmt_fbx;
  else if(load_mesh_3ds(*this, stream_))
    fmt=filefmt_3ds;
  else if(load_mesh_collada(*this, stream_))
    fmt=filefmt_collada;
  else if(load_mesh_lwo(*this, stream_))
    fmt=filefmt_lwo;
  else if(load_mesh_obj(*this, stream_))
    fmt=filefmt_obj;
  else
    PFC_WARN("Unable to load the mesh format\r\n");
  return fmt;
}
//----

mesh_vertex_buffer *mesh::create_vertex_buffers(unsigned num_vertex_buffers_)
{
  // create given number of vertex buffers
  m_vertex_buffers.clear();
  m_vertex_buffers.insert_back(num_vertex_buffers_);
  return m_vertex_buffers.data();
}
//----

mesh_skeleton *mesh::create_skeleton()
{
  m_skeleton=PFC_NEW(mesh_skeleton);
  return m_skeleton.data;
}
//----

void mesh::swap_indices(array<uint32_t> &indices_)
{
  m_indices.swap(indices_);
}
//----

void mesh::swap_segments(array<mesh_segment> &segments_)
{
  m_segments.swap(segments_);
}
//----

void mesh::swap_collision_objects(array<mesh_collision_object> &coll_objects_)
{
  m_coll_objects.swap(coll_objects_);
}
//----

void mesh::swap_joint_reindices(array<uint16_t> &joint_reindices_)
{
  m_joint_reindices.swap(joint_reindices_);
}
//----------------------------------------------------------------------------

void mesh::optimize()
{
#ifdef PFC_ENGINEOP_NVTRISTRIP
  // optimize all mesh segments
  SetCacheSize(24);
  unsigned num_segments=(unsigned)m_segments.size();
  array<uint32_t> new_indices;
  new_indices.reserve(m_indices.size());
  for(unsigned si=0; si<num_segments; ++si)
  {
    mesh_segment &seg=m_segments[si];
    array<uint16_t> indices;
    unsigned num_indices=0;
    switch(seg.primitive_type)
    {
      // triangle list
      case meshprim_trilist:
      {
        // convert from 32-bit index buffer to 16-bit buffer
        num_indices=seg.num_primitives*3;
        indices.resize(num_indices);
        uint16_t *indices_dst=indices.data();
        uint32_t *indices_src=m_indices.data()+seg.prim_start_index;
        for(unsigned i=0; i<num_indices; ++i)
        {
          uint32_t idx=indices_src[i];
          if(idx>65535)
          {
            PFC_WARNF("Can't optimize segment with indices not representable with 16-bit value (%i)\r\n", idx);
            indices.clear();
            break;
          }
          *indices_dst++=uint16_t(idx);
        }
      } break;

      // triangle strip
      case meshprim_tristrip:
      {
        // convert from 32-bit triangle strip index buffer to 16-bit triangle list
        num_indices=seg.num_primitives+2;
        unsigned num_primitives=seg.num_primitives;
        indices.resize(seg.num_primitives*3);
        uint16_t *indices_dst=indices.data();
        uint32_t *indices_src=m_indices.data()+seg.prim_start_index;
        for(unsigned i=0; i<num_primitives; ++i)
        {
          uint32_t idx0=indices_src[i+0];
          uint32_t idx1=indices_src[i+1];
          uint32_t idx2=indices_src[i+2];
          if((idx0|idx1|idx2)>65535)
          {
            PFC_WARNF("Can't optimize segment with indices not representable with 16-bit value (%i)\r\n", max(idx0, idx1, idx2));
            indices.clear();
            break;
          }
          *indices_dst++=i&1?uint16_t(idx2):uint16_t(idx0);
          *indices_dst++=uint16_t(idx1);
          *indices_dst++=i&1?uint16_t(idx0):uint16_t(idx2);
        }
      } break;

      // non-optimizable primitives
      case meshprim_linelist: num_indices=seg.num_primitives*2; break;
      case meshprim_linestrip: num_indices=seg.num_primitives+1; break;
      case meshprim_pointlist: num_indices=seg.num_primitives; break;
      default: PFC_ERROR("Unknown primitive type\r\n");
    }

    // copy old indices if the primitive can't be optimized
    if(!indices.size())
    {
      // copy indices from the old buffer
      unsigned start_index=(unsigned)new_indices.size();
      new_indices.insert_back(num_indices);
      mem_copy(new_indices.data()+start_index, m_indices.data()+seg.prim_start_index, num_indices*4);
      seg.prim_start_index=start_index;
      continue;
    }

    // optimize indices
    PrimitiveGroup *pg=0;
    unsigned short num_pg=0;
    GenerateStrips(indices.data(), (unsigned)indices.size(), &pg, &num_pg);
    PFC_CHECK(num_pg==1);

    // add optimized primitives to the index buffer
    unsigned start_index=(unsigned)new_indices.size();
    num_indices=pg->numIndices;
    new_indices.insert_back(num_indices);
    seg.prim_start_index=start_index;
    uint32_t *indices_dst=new_indices.data()+start_index;
    uint16_t *indices_src=pg->indices;
    for(unsigned i=0; i<num_indices; ++i)
      *indices_dst++=*indices_src++;
    PrimType type=pg->type;
    delete[]pg;

    // setup segment primitive
    switch(type)
    {
      // triangle list
      case PT_LIST:
      {
        PFC_ASSERT_MSG(num_indices>2 && num_indices%3==0, ("Invalid number of triangle list indices (%i)\r\n", num_indices));
        unsigned num_primitives=num_indices/3;
        seg.primitive_type=meshprim_trilist;
        seg.num_primitives=num_primitives;
      } break;

      // triangle strip
      case PT_STRIP:
      {
        PFC_ASSERT_MSG(num_indices>2, ("Invalid number of triangle strip indices (%i)\r\n", num_indices));
        unsigned num_primitives=num_indices-2;
        seg.primitive_type=meshprim_tristrip;
        seg.num_primitives=num_primitives;
      } break;

      default: PFC_ERROR("Unsupported primitive type\r\n");
    }
  }

  // replace index buffer with the optimized index buffer
  m_indices.swap(new_indices);
#else
  PFC_ERROR("Unable to optimize mesh without nvTriStrip library\r\n");
#endif
}
//----

void mesh::scale(ufloat_t scale_)
{
  // scale vertex positions
  for(unsigned vbi=0; vbi<m_vertex_buffers.size(); ++vbi)
  {
    mesh_vertex_buffer &vb=m_vertex_buffers[vbi];
    vec3f *vtx=(vec3f*)vb.vertex_channel(vtxchannel_position);
    if(vtx)
    {
      unsigned num_vertices=vb.num_vertices();
      for(unsigned i=0; i<num_vertices; ++i)
        *vtx++*=scale_;
    }
  }

  // scale skeleton
  if(m_skeleton.data)
  {
    m_skeleton->scale*=scale_;
    m_skeleton->inv_scale/=scale_;
    unsigned num_joints=(unsigned)m_skeleton->joints.size();
    mesh_skeleton::joint *joints=m_skeleton->joints.data();
    for(unsigned i=0; i<num_joints; ++i)
    {
      joints[i].bind_o2j.translation*=scale_;
      joints[i].bind_j2p.translation*=scale_;
    }
  }

  // scale collision objects
  unsigned num_coll_objects=(unsigned)m_coll_objects.size();
  for(unsigned coi=0; coi<num_coll_objects; ++coi)
  {
    unsigned num_points=(unsigned)m_coll_objects[coi].points.size();
    vec3f *points=m_coll_objects[coi].points.data();
    for(unsigned i=0; i<num_points; ++i)
      points[i]*=scale_;
  }
}
//----------------------------------------------------------------------------
