//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/mesh.h"
#include "sxp_src/core/math/bit_math.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_3DS
//============================================================================
// mesh_loader_3ds
//============================================================================
#define PFC_3DS_WARNF(...) {} //PFC_WARNF(__VA_ARGS__)
class mesh_loader_3ds
{
public:
  // loading
  void load(mesh&, bin_input_stream_base&);
  //--------------------------------------------------------------------------

private:
  void parse_sub_chunks(bin_input_stream_base&, unsigned chunk_size_);
  template<typename T> void parse_initial_track_value(bin_input_stream_base&, T&);
  void generate_mesh(mesh&);
  //--------------------------------------------------------------------------

  //==========================================================================
  // mesh_loader_3ds::sub_object
  //==========================================================================
  struct sub_object
  {
    // construction and operations
    PFC_INLINE sub_object()
    {
      num_instances=0;
      base_vertex_index=0;
      num_vertices=0;
      base_face_index=0;
      num_faces=0;
      lod=0;
      is_coll_object=false;
    }
    //----

    template<class S> PFC_INLINE bool operator==(const str_base<S> &str_) const  {return name==str_;}
    //------------------------------------------------------------------------

    heap_str name;
    tform3f tform_o2w;
    unsigned num_instances;
    unsigned base_vertex_index;
    unsigned num_vertices;
    unsigned base_face_index;
    unsigned num_faces;
    uint8_t lod;
    bool is_coll_object;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // mesh_loader_3ds::face
  //==========================================================================
  struct face
  {
    PFC_INLINE face()
    {
      material_idx=0;
      lod=0;
      smoothing_groups=0;
      mem_zero(src_vidx, sizeof(src_vidx));
      mem_zero(src_vidx, sizeof(src_vidx));
      mem_zero(vflist_next, sizeof(vflist_next));
    }
    //----

    uint16_t material_idx;
    uint8_t lod;
    uint32_t smoothing_groups;
    uint32_t src_vidx[3];
    uint32_t dst_vidx[3];
    uint32_t vflist_next[3];
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // mesh_loader_3ds::angle_axis
  //==========================================================================
  struct angle_axis
  { PFC_MONO(angle_axis) {PFC_VAR2(angle, axis);}
    // construction
    PFC_INLINE angle_axis()
      :angle(0.0f)
      ,axis(0.0f, 0.0f, 0.0f)
    {
    }
    //------------------------------------------------------------------------

    float angle;
    vec3f axis;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // mesh_loader_3ds::node
  //==========================================================================
  struct node
  {
    // construction
    PFC_INLINE node()
      :pivot(0.0f, 0.0f, 0.0f)
      ,init_position_n2p(0.0f, 0.0f, 0.0f)
      ,init_scale_n2p(1.0f, 1.0f, 1.0f)
    {
      id=-1;
      parent=-1;
      sub_object_idx=-1;
    }
    //------------------------------------------------------------------------

    int16_t id;
    int16_t parent;
    int sub_object_idx;
    vec3f pivot;
    vec3f init_position_n2p;
    angle_axis init_rotation_n2p;
    vec3f init_scale_n2p;
    tform3f init_tform_n2w;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // mesh::material
  //==========================================================================
  struct material
  {
    // construction
    PFC_INLINE material(const stack_str256 &name_) :name(name_) {mem_zero(num_faces, sizeof(num_faces)); mem_zero(start_face_idx, sizeof(start_face_idx));}
    PFC_INLINE bool operator==(const stack_str256 &name_) const {return name==name_;}
    //------------------------------------------------------------------------

    stack_str256 name;
    unsigned num_faces[max_mesh_lods];
    unsigned start_face_idx[max_mesh_lods];
  };
  //--------------------------------------------------------------------------

  ufloat_t m_scale;
  array<material> m_materials;
  array<sub_object> m_sub_objects;
  array<node> m_nodes;
  array<vec3f> m_positions;
  array<vec2f> m_uvs;
  array<face> m_faces;
  unsigned m_base_vertex_idx;
  unsigned m_base_face_idx;
  unsigned m_num_collision_objects;
};
//----------------------------------------------------------------------------

void mesh_loader_3ds::load(mesh &mesh_, bin_input_stream_base &stream_)
{
  // check precondition
  m_scale=1.0f;
  m_base_vertex_idx=0;
  m_base_face_idx=0;
  m_num_collision_objects=0;

  // read main chunk and process sub-chunks
  uint16_t id;
  uint32_t chunk_size;
  stream_>>id>>chunk_size;
  PFC_CHECK_MSG(id==0x4d4d, ("Invalid 3DS file\r\n"));
  parse_sub_chunks(stream_, chunk_size-6);
  if(!m_materials.size())
    m_materials.push_back(stack_str256(""));

  // generate mesh & cleanup
  generate_mesh(mesh_);
  m_materials.clear();
  m_positions.clear();
  m_uvs.clear();
  m_faces.clear();
}
//----------------------------------------------------------------------------

void mesh_loader_3ds::parse_sub_chunks(bin_input_stream_base &stream_, unsigned chunk_size_)
{
  while(chunk_size_)
  {
    // read sub-chunk
    uint16_t chunk_id;
    uint32_t chunk_size;
    stream_>>chunk_id>>chunk_size;
    chunk_size_-=chunk_size;
    chunk_size-=6;
    auto_stream_seek<bin_input_stream_base> aseek(stream_, chunk_size);
    switch(chunk_id)
    {
      // master scale
      case 0x0100:
      {
        stream_>>m_scale;
      } break;

      // 3d editor
      case 0x3d3d: parse_sub_chunks(stream_, chunk_size); break;

      // object block
      case 0x4000:
      {
        char obj_name[256];
        chunk_size-=(unsigned)stream_.read_cstr(obj_name, sizeof(obj_name))+1;
        sub_object &obj=m_sub_objects.push_back();
        obj.name=obj_name;
        obj.lod=subobject_lod(obj_name);
        obj.is_coll_object=is_collision_subobject(obj_name);
        if(obj.is_coll_object)
          ++m_num_collision_objects;
        parse_sub_chunks(stream_, chunk_size);
      } break;

      // triangular mesh
      case 0x4100: parse_sub_chunks(stream_, chunk_size); break;

      // vertices
      case 0x4110:
      {
        // read vertex positions
        uint16_t num_verts;
        stream_>>num_verts;
        m_base_vertex_idx=(unsigned)m_positions.size();
        sub_object &obj=m_sub_objects.back();
        obj.base_vertex_index=m_base_vertex_idx;
        obj.num_vertices=num_verts;
        m_positions.insert_back(num_verts);
        m_uvs.insert_back(num_verts, vec2f(0.0f, 0.0f));
        stream_.read(m_positions.data()+m_base_vertex_idx, num_verts);
      } break;

      // faces
      case 0x4120:
      {
        // read face indices
        sub_object &obj=m_sub_objects.back();
        uint16_t num_faces;
        stream_>>num_faces;
        m_base_face_idx=(unsigned)m_faces.size();
        obj.base_face_index=m_base_face_idx;
        obj.num_faces=num_faces;
        uint8_t lod=obj.lod;
        m_faces.insert_back(num_faces);
        face *f=m_faces.data()+m_base_face_idx;
        uint16_t data[4];
        for(unsigned i=0; i<num_faces; ++i)
        {
          stream_.read(data, 4);
          f->src_vidx[0]=data[0]+m_base_vertex_idx;
          f->src_vidx[1]=data[1]+m_base_vertex_idx;
          f->src_vidx[2]=data[2]+m_base_vertex_idx;
          f->lod=lod;
          ++f;
        }
        if(!obj.is_coll_object)
          parse_sub_chunks(stream_, chunk_size-2-num_faces*2*4);
      } break;

      // face materials
      case 0x4130:
      {
        stack_str256 material_name;
        material_name.resize(stream_.read_cstr(material_name.data(), 256));
        uint16_t num_faces;
        stream_>>num_faces;
        if(num_faces)
        {
          // check if material already exists and add to the material array if not
          material *mat=linear_search(m_materials.begin(), m_materials.end(), material_name);
          if(!mat)
          {
            m_materials.push_back(material_name);
            mat=&m_materials.back();
          }

          // read material faces
          uint16_t material_idx=uint16_t(mat-m_materials.begin());
          for(unsigned i=0; i<num_faces; ++i)
          {
            uint16_t face_idx;
            stream_>>face_idx;
            m_faces[face_idx+m_base_face_idx].material_idx=material_idx;
          }
        }
      } break;

      // mapping coordinates
      case 0x4140:
      {
        // read UV coordinates
        uint16_t num_verts;
        stream_>>num_verts;
        PFC_CHECK(m_base_vertex_idx+num_verts==m_uvs.size());
        stream_.read(m_uvs.data()+m_base_vertex_idx, num_verts);
      } break;

      // smoothing groups
      case 0x4150:
      {
        // read face smoothing groups
        unsigned num_faces=(unsigned)m_faces.size()-m_base_face_idx;
        face *f=m_faces.data()+m_base_face_idx;
        for(unsigned i=0; i<num_faces; ++i)
          stream_>>f++->smoothing_groups;
      } break;

      // local coordinate system
      case 0x4160:
      {
        // read local transformation for the object
        vec3f x, y, z, t;
        stream_>>x>>y>>z>>t;
        m_sub_objects.back().tform_o2w=tform3f(x, y, z, t);
      } break;

      // key frame chunk
      case 0xb000: parse_sub_chunks(stream_, chunk_size); break;

      // mesh information block
      case 0xb002:
      {
        m_nodes.push_back();
        parse_sub_chunks(stream_, chunk_size);
      } break;

      // node parameters
      case 0xb010:
      {
        // read node parameters
        stack_str256 object_name;
        object_name.resize(stream_.read_cstr(object_name.data(), 256));
        node &n=m_nodes.back();
        stream_.skip(4);
        stream_>>n.parent;
        sub_object *obj=linear_search(m_sub_objects.begin(), m_sub_objects.end(), object_name);
        if(obj)
        {
          ++obj->num_instances;
          n.sub_object_idx=unsigned(obj-m_sub_objects.begin());
        }
      } break;

      // node pivot
      case 0xb013: stream_>>m_nodes.back().pivot; break;

      // position track
      case 0xb020: parse_initial_track_value(stream_, m_nodes.back().init_position_n2p); break;

      // rotation track
      case 0xb021: parse_initial_track_value(stream_, m_nodes.back().init_rotation_n2p); break;

      // scale track
      case 0xb022: parse_initial_track_value(stream_, m_nodes.back().init_scale_n2p); break;

      // node id
      case 0xb030: stream_>>m_nodes.back().id; break;

      // unsupported chunk ID
      default: PFC_3DS_WARNF("Unsupported chunk: 0x%04x", chunk_id);
    }
  }
}
//----

template<typename T>
void mesh_loader_3ds::parse_initial_track_value(bin_input_stream_base &stream_, T &v_)
{
  // read track properties
  stream_.skip(10);
  uint32_t num_keys;
  stream_>>num_keys;
  if(num_keys)
  {
    // read the first key
    uint32_t key_num;
    uint16_t flags;
    stream_>>key_num>>flags;
    stream_.skip(num_bits(flags));
    stream_>>v_;
  }
}
//----

void mesh_loader_3ds::generate_mesh(mesh &mesh_)
{
  // epsilon TBN-axis angle for merging vertices
  static const float s_sqr_epsilon=sqr(cos(2.0f*mathf::deg_to_rad));
/*  static const float s_epsilon_t_dot=cos(90.0f*mathf::deg_to_rad);
  static const float s_epsilon_b_dot=cos(90.0f*mathf::deg_to_rad);*/
  array<mesh_collision_object> mesh_coll_objects;
  mesh_coll_objects.reserve(m_num_collision_objects);

  {
    // transform mesh vertices
    unsigned num_sub_objects=(unsigned)m_sub_objects.size();
    sub_object *sub_objects=m_sub_objects.data();
    unsigned num_nodes=(unsigned)m_nodes.size();
    node *nodes=m_nodes.data();
    if(!num_nodes)
    {
      vec3f *positions=m_positions.data();
      for(unsigned si=0; si<num_sub_objects; ++si)
      {
        // setup sub-object transform
        sub_object &obj=sub_objects[si];
        tform3f mesh_tform=obj.tform_o2w*tform3f(m_scale,     0.0f,    0.0f, 0.0f,
                                                    0.0f, -m_scale,    0.0f, 0.0f,
                                                    0.0f,     0.0f, m_scale, 0.0f);

        // transform sub-object vertices
        unsigned base_vertex_index=obj.base_vertex_index;
        unsigned num_sub_verts=obj.num_vertices;
        for(unsigned i=0; i<num_sub_verts; ++i)
          positions[base_vertex_index+i]*=mesh_tform;
        if(obj.is_coll_object)
        {
          // add collision object
          mesh_collision_object &coll_obj=mesh_coll_objects.push_back();
          coll_obj.points.resize(num_sub_verts);
          mem_copy(coll_obj.points.data(), positions+base_vertex_index, num_sub_verts*sizeof(*coll_obj.points.data()));
          unsigned num_indices=obj.num_faces*3;
          coll_obj.indices.resize(num_indices);
          uint32_t *indices=coll_obj.indices.data();
          const face *faces=m_faces.data()+obj.base_face_index;
          for(unsigned i=0; i<obj.num_faces; ++i)
          {
            *indices++=faces->src_vidx[0]-base_vertex_index;
            *indices++=faces->src_vidx[1]-base_vertex_index;
            *indices++=faces->src_vidx[2]-base_vertex_index;
            ++faces;
          }
        }
      }
    }
    else
    {
      // generate geometry for nodes
      for(unsigned ni=0; ni<num_nodes; ++ni)
      {
        // setup node transformation
        node &n=nodes[ni];
        PFC_CHECK(n.parent<int(ni));
        tform3f p2w;
        if(n.parent>=0)
          p2w=nodes[n.parent].init_tform_n2w;
        n.init_tform_n2w= tform3f(n.init_scale_n2p.x, n.init_scale_n2p.y, n.init_scale_n2p.z)
                         *tform3f(axis_rot(n.init_rotation_n2p.axis, -n.init_rotation_n2p.angle), n.init_position_n2p)
                         *p2w;

        if(n.sub_object_idx>=0)
        {
          // duplicate sub-object geometry if it has more than one instance
          sub_object &obj=sub_objects[n.sub_object_idx];
          unsigned num_faces=obj.num_faces;
          face *faces=m_faces.data()+obj.base_face_index;
          unsigned num_vertices=obj.num_vertices;
          vec3f *positions=m_positions.data()+obj.base_vertex_index;
          if(--obj.num_instances)
          {
            // duplicate vertex data for the node
            unsigned base_vertex_idx=(unsigned)m_positions.size();
            m_positions.insert_back(num_vertices);
            positions=m_positions.data()+base_vertex_idx;
            mem_copy(positions, m_positions.data()+obj.base_vertex_index, num_vertices*sizeof(m_positions[0]));
            m_uvs.insert_back(num_vertices);
            mem_copy(m_uvs.data()+base_vertex_idx, m_uvs.data()+obj.base_vertex_index, num_vertices*sizeof(m_uvs[0]));

            // duplicate face data for the node
            unsigned base_face_idx=(unsigned)m_faces.size();
            m_faces.insert_back(num_faces);
            faces=m_faces.data()+base_face_idx;
            mem_copy(faces, m_faces.data()+obj.base_face_index, num_faces*sizeof(m_faces[0]));
            unsigned vidx_delta=base_vertex_idx-obj.base_vertex_index;
            for(unsigned i=0; i<num_faces; ++i)
            {
              faces[i].src_vidx[0]+=vidx_delta;
              faces[i].src_vidx[1]+=vidx_delta;
              faces[i].src_vidx[2]+=vidx_delta;
            }
          }

          // transform vertices
          tform3f tform_w2l;
          tform_w2l=inv(obj.tform_o2w);
          if(det(obj.tform_o2w)<0.0f)
          {
            // flip x-axis for negative scale
            tform_w2l.x.x*=-1.0f;
            tform_w2l.y.x*=-1.0f;
            tform_w2l.z.x*=-1.0f;
            tform_w2l.x.w*=-1.0f;

            // flip face direction
            for(unsigned i=0; i<num_faces; ++i)
              swap(faces[i].src_vidx[1], faces[i].src_vidx[2]);
          };
          tform3f tform=tform_w2l*tform3f(-n.pivot)*n.init_tform_n2w;
          tform*=tform3f(m_scale, -m_scale, m_scale);
          for(unsigned i=0; i<num_vertices; ++i)
            positions[i]*=tform;
          if(obj.is_coll_object)
          {
            // add collision object
            mesh_collision_object &coll_obj=mesh_coll_objects.push_back();
            coll_obj.points.resize(num_vertices);
            mem_copy(coll_obj.points.data(), positions, num_vertices*sizeof(*coll_obj.points.data()));
            unsigned num_indices=obj.num_faces*3;
            coll_obj.indices.resize(num_indices);
            uint32_t *indices=coll_obj.indices.data();
            const face *faces=m_faces.data()+obj.base_face_index;
            for(unsigned i=0; i<obj.num_faces; ++i)
            {
              *indices++=faces->src_vidx[0]-obj.base_vertex_index;
              *indices++=faces->src_vidx[1]-obj.base_vertex_index;
              *indices++=faces->src_vidx[2]-obj.base_vertex_index;
              ++faces;
            }
          }
        }
      }
    }
  }

  // vertex output buffers
  array<vec3f> mesh_positions;
  array<vec2f> mesh_uvs;
  array<vec3f> mesh_tangents;
  array<vec3f> mesh_binormals;
  array<vec3f> mesh_normals;
  vec3f *positions=m_positions.data();
  unsigned num_verts=(unsigned)m_positions.size();
  unsigned capacity=num_verts;
  mesh_positions.reserve(capacity);
  mesh_uvs.reserve(capacity);
  mesh_tangents.reserve(capacity);
  mesh_binormals.reserve(capacity);
  mesh_normals.reserve(capacity);

  // build attached face lists for each mesh vertex
  unsigned num_degenerated_faces=0;
  unsigned num_faces=(unsigned)m_faces.size();
  array<pair<uint32_t, uint32_t> > vtx_face_lists(num_verts);
  material *materials=m_materials.data();
  pair<uint32_t, uint32_t> *vflists=vtx_face_lists.data();
  mem_zero(vflists, sizeof(*vflists)*num_verts);
  face *faces=m_faces.data();
  vec2f *uvs=m_uvs.data();
  for(unsigned i=0; i<num_faces; ++i)
  {
    // check for a degenerated face
    face &f=faces[i];
    if(is_zero(cross(positions[f.src_vidx[1]]-positions[f.src_vidx[0]], positions[f.src_vidx[2]]-positions[f.src_vidx[0]])))
    {
      ++num_degenerated_faces;
      f.material_idx=uint16_t(-1);
      continue;
    }

    // add the face to the face list of each face vertex
    uint32_t fidx=(i+1)<<2;
    f.vflist_next[0]=vflists[f.src_vidx[0]].first;
    vflists[f.src_vidx[0]].first=fidx|0;
    ++vflists[f.src_vidx[0]].second;
    f.vflist_next[1]=vflists[f.src_vidx[1]].first;
    vflists[f.src_vidx[1]].first=fidx|1;
    ++vflists[f.src_vidx[1]].second;
    f.vflist_next[2]=vflists[f.src_vidx[2]].first;
    vflists[f.src_vidx[2]].first=fidx|2;
    ++vflists[f.src_vidx[2]].second;
    ++materials[f.material_idx].num_faces[f.lod];
  }

  // find maximum valence of all vertices
  unsigned max_valence=0;
  for(unsigned i=0; i<num_verts; ++i)
    max_valence=max(max_valence, vflists[i].second);

  // smooth the mesh and duplicate vertices when necessary
  array<mat33f> face_smooths(max_valence), vtx_smooths(max_valence);
  mat33f *fsmooths=face_smooths.data(), *vsmooths=vtx_smooths.data();
  unsigned num_generated_vertices=0;
  for(unsigned i=0; i<num_verts; ++i)
  {
    // check for isolated vertex
    uint32_t idx=vflists[i].first;
    if(!idx)
      continue;

    // init tangent space scratch pads for faces & vertices
    unsigned spvi=0;
    do
    {
      // calculate face normal (length twice the triangular area of the face)
      mat33f &tbn=fsmooths[spvi];
      static const unsigned s_nfvidx[3][2]={{1, 2}, {2, 0}, {0, 1}};
      unsigned idx_face=(idx>>2)-1, idx_fvi=idx&3;
      const face &f=faces[idx_face];
      unsigned vidx0=f.src_vidx[s_nfvidx[idx_fvi][0]];
      unsigned vidx1=f.src_vidx[s_nfvidx[idx_fvi][1]];
      const vec3f &e0=positions[vidx0]-positions[i];
      const vec3f &e1=positions[vidx1]-positions[i];
      tbn.z=cross(e1, e0);

      // calculate tangent & binormal and weight scaled TBN with face opening angle
      const vec2f &t0=uvs[vidx0]-uvs[i];
      const vec2f &t1=uvs[vidx1]-uvs[i];
      tbn.x=e0*t1.y-e1*t0.y;
      tbn.y=e0*t1.x-e1*t0.x;
      tbn*=acos(ssat(dot(unit_z(e0), unit_z(e1))));

      // proceed to the next face
      vsmooths[spvi]=tbn;
      ++spvi;
      idx=faces[idx_face].vflist_next[idx_fvi];
    } while(idx);

    // process all smoothing vertices for the vertex
    unsigned num_vgen=0;
    idx=vflists[i].first;
    spvi=0;
    do
    {
      // add faces with compatible smoothing groups to the smoothing vertex
      unsigned idx_face=(idx>>2)-1, idx_fvi=idx&3;
      uint32_t smth_grp=faces[idx_face].smoothing_groups;
      idx=faces[idx_face].vflist_next[idx_fvi];
      unsigned idx_s=idx;
      unsigned spvi_s=spvi;
      while(idx_s)
      {
        // add tangent spaces of compatible smoothing groups
        unsigned idx_face_s=(idx_s>>2)-1;
        ++spvi_s;
        if(smth_grp&faces[idx_face_s].smoothing_groups)
        {
          /*todo: consider TBN mirroring*/
          vsmooths[spvi]+=fsmooths[spvi_s];
          vsmooths[spvi_s]+=fsmooths[spvi];
        }

        // proceed to the next face
        idx_s=faces[idx_face_s].vflist_next[idx_s&3];
      }

      // search for vertex duplicate and add new vertex if none found
      const mat33f &tbn=vsmooths[spvi];
      spvi_s=0;
      while(spvi_s<num_vgen)
      {
        const mat33f &tbn_s=vsmooths[spvi_s];
        if(   sqr(dot(tbn.x, tbn_s.x))>=s_sqr_epsilon*(norm2(tbn.x)*norm2(tbn_s.x))
           && sqr(dot(tbn.y, tbn_s.y))>=s_sqr_epsilon*(norm2(tbn.y)*norm2(tbn_s.y))
           && sqr(dot(tbn.z, tbn_s.z))>=s_sqr_epsilon*(norm2(tbn.z)*norm2(tbn_s.z)))
          goto found_matching_vertex;
        ++spvi_s;
      }

      {
        // add vertex
        mesh_positions.push_back()=m_positions[i];
        vec2f &uv=mesh_uvs.push_back();
        uv.x=uvs[i].x;
        uv.y=1.0f-uvs[i].y;
        mesh_tangents.push_back()=unit_z(tbn.x);
        mesh_binormals.push_back()=unit_z(tbn.y);
        mesh_normals.push_back()=unit_z(tbn.z);
        vsmooths[num_vgen]=tbn;
        ++num_vgen;
      }
      found_matching_vertex:

      // setup face vertex index and proceed to the next face
      faces[idx_face].dst_vidx[idx_fvi]=num_generated_vertices+spvi_s;
      ++spvi;
    } while(idx);

    // proceed to the next vertex
    num_generated_vertices+=num_vgen;
  }

  // set mesh vertex data
  mesh_positions.trim();
  mesh_uvs.trim();
  mesh_tangents.trim();
  mesh_binormals.trim();
  mesh_normals.trim();
  mesh_vertex_buffer &vb=*mesh_.create_vertex_buffers(1);
  vb.add_channel(vtxchannel_position, mesh_positions.steal_data().steal_data(), num_generated_vertices);
  vb.add_channel(vtxchannel_uv, mesh_uvs.steal_data().steal_data(), num_generated_vertices);
  vb.add_channel(vtxchannel_tangent, mesh_tangents.steal_data().steal_data(), num_generated_vertices);
  vb.add_channel(vtxchannel_binormal, mesh_binormals.steal_data().steal_data(), num_generated_vertices);
  vb.add_channel(vtxchannel_normal, mesh_normals.steal_data().steal_data(), num_generated_vertices);

  // get number of faces and segments after removing degenerated faces
  unsigned num_total_faces=0;
  unsigned num_total_segments=0;
  for(unsigned lod=0; lod<max_mesh_lods; ++lod)
    for(unsigned i=0; i<m_materials.size(); ++i)
    {
      materials[i].start_face_idx[lod]=num_total_faces;
      num_total_faces+=materials[i].num_faces[lod];
      if(materials[i].num_faces[lod])
        ++num_total_segments;
    }

  // set mesh segments
  array<mesh_segment> mesh_segments;
  mesh_segments.resize(num_total_segments);
  mesh_segment *msegment=mesh_segments.data();
  uint16_t mat_idx=0;
  for(unsigned lod=0; lod<max_mesh_lods; ++lod)
    for(unsigned i=0; i<m_materials.size(); ++i)
      if(materials[i].num_faces[lod])
      {
        mesh_segment &seg=msegment[mat_idx];
        seg.material_name=m_materials[i].name;
        seg.vertex_buffer=0;
        seg.primitive_type=meshprim_trilist;
        seg.num_primitives=materials[i].num_faces[lod];
        seg.prim_start_index=materials[i].start_face_idx[lod]*3;
        ++mat_idx;
      }

  // set mesh indices
  array<uint32_t> mesh_indices;
  mesh_indices.resize(num_total_faces*3);
  uint32_t *ibuf=mesh_indices.data();
  for(unsigned i=0; i<num_faces; ++i)
  {
    const face &f=faces[i];
    mat_idx=f.material_idx;
    if(mat_idx!=uint16_t(-1))
    {
      unsigned iidx=materials[mat_idx].start_face_idx[f.lod]*3;
      ++materials[mat_idx].start_face_idx[f.lod];
      ibuf[iidx+0]=f.dst_vidx[0];
      ibuf[iidx+1]=f.dst_vidx[2];
      ibuf[iidx+2]=f.dst_vidx[1];
    }
  }

  // swap mesh content
  mesh_.swap_indices(mesh_indices);
  mesh_.swap_segments(mesh_segments);
  mesh_.swap_collision_objects(mesh_coll_objects);
}
//----------------------------------------------------------------------------


//============================================================================
// load_mesh_3ds
//============================================================================
namespace pfc
{
  bool load_mesh_3ds(mesh &m_, bin_input_stream_base &s_)
  {
    // check for 3DS file format
    uint16_t id;
    s_>>id;
    s_.rewind(2);
    if(id!=0x4d4d)
      return false;

    // load the mesh
    mesh_loader_3ds loader;
    loader.load(m_, s_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_3DS
namespace pfc
{
  bool load_mesh_3ds(mesh &m_, bin_input_stream_base &s_)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_3DS
