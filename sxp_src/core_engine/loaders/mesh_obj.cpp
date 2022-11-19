//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/mesh.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// config
//============================================================================
enum {max_line_length=1024};
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_OBJ
//============================================================================
// mesh_loader_obj
//============================================================================
class mesh_loader_obj
{
public:
  // loading
  void load(mesh&, bin_input_stream_base&);
  //--------------------------------------------------------------------------

private:
  void parse_data(bin_input_stream_base&);
  void generate_mesh(mesh&);
  //--------------------------------------------------------------------------

  //==========================================================================
  // vertex
  //==========================================================================
  struct vertex
  {
    int point_idx;
    int uv_idx;
    int normal_idx;
    unsigned face_idx;
    unsigned face_vertex_idx;
    unsigned vertex_idx;
    vertex *next;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // point
  //==========================================================================
  struct point
  {
    vec3f position;
    vertex *vertices;
    unsigned num_vertices;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // face
  //==========================================================================
  struct face
  {
    unsigned start_vertex;
    unsigned num_vertices;
    unsigned smoothing_group;
    face *next;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // smoother
  //==========================================================================
  struct smoother
  {
    // comparison
    PFC_INLINE bool operator==(const smoother &smtr_) const
    {
      // test if vertices are within given epsilons
      static const float uv_sqr_epsilon=sqr(0.001f);
      static const float tbn_sqr_epsilon=sqr(cos(2.0f*mathf::deg_to_rad));
      return    norm2(uv-smtr_.uv)<uv_sqr_epsilon
             && sqr(dot(tbn.x, smtr_.tbn.x))>=tbn_sqr_epsilon*(norm2(tbn.x)*norm2(smtr_.tbn.x))
             && sqr(dot(tbn.y, smtr_.tbn.y))>=tbn_sqr_epsilon*(norm2(tbn.y)*norm2(smtr_.tbn.y))
             && sqr(dot(tbn.z, smtr_.tbn.z))>=tbn_sqr_epsilon*(norm2(tbn.z)*norm2(smtr_.tbn.z));
    }
    //------------------------------------------------------------------------

    vec2f uv;
    mat33f tbn;
    unsigned vertex_idx;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // material
  //==========================================================================
  struct material
  {
    // construction and operations
    PFC_INLINE material() {mem_zero(faces, sizeof(faces));}
    template<unsigned capacity> PFC_INLINE bool operator==(const stack_str<capacity> &str_) const  {return name==str_;}
    //------------------------------------------------------------------------

    heap_str name;
    face *faces[max_mesh_lods];
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // collision_object_info
  //==========================================================================
  struct collision_object_info
  {
    unsigned points_start, points_end;
    unsigned faces_start, faces_end;
  };
  //--------------------------------------------------------------------------

  array<point> m_points;
  array<vec3f> m_normals;
  array<vec2f> m_uvs;
  array<collision_object_info> m_coll_object_info;
  deque<vertex> m_vertices;
  deque<face> m_faces;
  array<material> m_materials;
  unsigned m_max_valence;
  unsigned m_num_segments;
};
//----------------------------------------------------------------------------

void mesh_loader_obj::load(mesh &mesh_, bin_input_stream_base &stream_)
{
  parse_data(stream_);
  generate_mesh(mesh_);
}
//----------------------------------------------------------------------------

void mesh_loader_obj::parse_data(bin_input_stream_base &stream_)
{
  // reset loading
  m_points.clear();
  m_normals.clear();
  m_uvs.clear();
  m_vertices.clear();
  m_materials.clear();
  mem_zero(&m_points.push_back(), sizeof(point));
  m_normals.push_back(vec3f(0.0f, 0.0f, 0.0f));
  m_uvs.push_back(vec2f(0.0f, 0.0f));
  m_materials.resize(1);
  m_max_valence=0;
  m_num_segments=0;
  //unsigned active_material_idx=0;
  unsigned active_lod=0;
  bool is_coll_object=false;
  unsigned smoothing_group=0xffffffff;
  material *active_material=m_materials.data();

  // parse all lines in the stream
  text_input_stream text_stream(stream_);
  while(!stream_.is_eos())
  {
    char line[max_line_length];
    unsigned line_len=(unsigned)text_stream.read_line(line, max_line_length);
    if(line_len)
    {
      // parse keyword
      enum {max_keyword_length=32};
      char keyword[max_keyword_length];
      mem_input_stream mem_stream(line, line_len);
      text_input_stream text_stream_line(mem_stream);
      unsigned keyword_length=(unsigned)text_stream_line.read_word(keyword, max_keyword_length);

      // check for 1-char keywords
      if(keyword_length==1)
      {
        // switch to proper 1-char keyword parsing
        switch(keyword[0])
        {
          // object: "o"-keyword
          case 'o':
          {
            // get LOD from the object name
            stack_str<max_line_length> obj_name;
            obj_name.resize(text_stream_line.read_line(obj_name.data(), max_line_length));
            active_lod=subobject_lod(obj_name.c_str());

            // setup collision object
            if(is_coll_object)
            {
              collision_object_info &coll_obj_info=m_coll_object_info.back();
              coll_obj_info.points_end=(unsigned)m_points.size();
              coll_obj_info.faces_end=(unsigned)m_faces.size();
            }
            is_coll_object=is_collision_subobject(obj_name.c_str());
            if(is_coll_object)
            {
              collision_object_info &coll_obj_info=m_coll_object_info.push_back();
              coll_obj_info.points_start=(unsigned)m_points.size();
              coll_obj_info.faces_start=(unsigned)m_faces.size();
            }
          } break;

          // vertex: "v"-keyword
          case 'v':
          {
            // read vertex coordinates
            point &pnt=m_points.push_back();
            pnt.vertices=0;
            pnt.num_vertices=0;
            text_stream_line>>pnt.position;
          } break;

          // face: "f"-keyword
          case 'f':
          {
            // add new face
            unsigned face_idx=(unsigned)m_faces.size();
            unsigned face_vertex_idx=0;
            face &f=m_faces.push_back();
            f.start_vertex=(unsigned)m_vertices.size();
            f.smoothing_group=smoothing_group;

            // read position, uv and normal indices for face vertices
            if(!is_coll_object)
            {
              if(!active_material->faces[active_lod])
                ++m_num_segments;
              f.next=active_material->faces[active_lod];
              active_material->faces[active_lod]=&f;
            }
            do
            {
              // parse vertex indices from the stream (uv & normal are optional)
              vertex &vtx=m_vertices.push_back();
              vtx.uv_idx=0;
              vtx.normal_idx=0;
              text_stream_line>>vtx.point_idx;
              PFC_CHECK(vtx.point_idx);
              if(vtx.point_idx<0)
                vtx.point_idx=(int)m_points.size()+vtx.point_idx;
              if(!text_stream_line.is_eos() && text_stream_line.read_char()=='/')
              {
                text_stream_line>>vtx.uv_idx;
                if(vtx.uv_idx<0)
                  vtx.uv_idx=(int)m_uvs.size()+vtx.uv_idx;
                if(!text_stream_line.is_eos() && text_stream_line.read_char()=='/')
                {
                  text_stream_line>>vtx.normal_idx;
                  if(vtx.normal_idx<0)
                    vtx.normal_idx=(int)m_normals.size()+vtx.normal_idx;
                }
              }

              // add vertex to vertex list of the point and proceed to the next vertex
              vtx.face_idx=face_idx;
              vtx.face_vertex_idx=face_vertex_idx++;
              if(!is_coll_object)
              {
                point &pnt=m_points[vtx.point_idx];
                vtx.next=pnt.vertices;
                pnt.vertices=&vtx;
                m_max_valence=max(++pnt.num_vertices, m_max_valence);
              }
              text_stream_line.skip_whitespace();
            } while(!text_stream_line.is_eos());
            f.num_vertices=(unsigned)m_vertices.size()-f.start_vertex;
          } break;

          // smoothing group: "s"-keyword
          case 's':
          {
            // read current smoothing group number
            text_stream_line>>smoothing_group;
          } break;
        }
      }
      else
      {
        // check for vertex normal: "vn"-keyword
        if(mem_eq(keyword, "vn", 3))
        {
          // read vertex normal
          vec3f &normal=m_normals.push_back();
          text_stream_line>>normal;
          normal=unit_z(normal);
          continue;
        }

        // check for vertex texture coordinate: "vt"-keyword
        if(mem_eq(keyword, "vt", 3))
        {
          // read vertex texture coordinate
          vec2f &uv=m_uvs.push_back();
          text_stream_line>>uv;
          continue;
        }

        // check for material setup: "usemtl"-keyword
        if(mem_eq(keyword, "usemtl", 7))
        {
          // check for empty material
          bool empty_material=true;
          for(unsigned i=0; i<max_mesh_lods; ++i)
            if(active_material->faces[i])
            {
              empty_material=false;
              break;
            }
          if(empty_material)
            m_materials.pop_back();

          // read material name and add new material if doesn't already exists
          stack_str<max_line_length> mat_name;
          mat_name.resize(text_stream_line.read_word(mat_name.data(), max_line_length));
          active_material=linear_search(m_materials.begin(), m_materials.end(), mat_name);
          if(!active_material)
          {
            //active_material_idx=(unsigned)m_materials.size();
            active_material=&m_materials.push_back();
            active_material->name=mat_name;
          }

          // setup material index
          //active_material_idx=unsigned(active_material-m_materials.begin());
          continue;
        }
      }
    }
  }

  // setup last collision object
  if(is_coll_object)
  {
    collision_object_info &coll_obj_info=m_coll_object_info.back();
    coll_obj_info.points_end=(unsigned)m_points.size();
    coll_obj_info.faces_end=(unsigned)m_faces.size();
  }
}
//----

void mesh_loader_obj::generate_mesh(mesh &mesh_)
{
  // define thresholds
  static const float s_epsilon_t_dot=cos(90.0f*mathf::deg_to_rad);
  static const float s_epsilon_b_dot=cos(90.0f*mathf::deg_to_rad);
  static const float s_epsilon_n_dot=cos(2.0f*mathf::deg_to_rad);

  // setup mesh transforms
  mat33f mesh_tform( 1.0f,  0.0f,  0.0f,
                     0.0f,  0.0f,  1.0f,
                     0.0f,  1.0f,  0.0f);

  // create collision objects
  array<mesh_collision_object> mesh_coll_objects;
  mesh_coll_objects.reserve(m_coll_object_info.size());
  for(unsigned ci=0; ci<m_coll_object_info.size(); ++ci)
  {
    // setup collision object points
    collision_object_info &coll_obj_info=m_coll_object_info[ci];
    mesh_collision_object &coll_obj=mesh_coll_objects.push_back();
    unsigned num_coll_points=coll_obj_info.points_end-coll_obj_info.points_start;
    coll_obj.points.resize(num_coll_points);
    vec3f *coll_points=coll_obj.points.data();
    const point *points=m_points.data()+coll_obj_info.points_start;
    for(unsigned i=0; i<num_coll_points; ++i)
      coll_points[i]=points[i].position*mesh_tform;

    // setup collision object faces
    unsigned num_coll_faces=coll_obj_info.faces_end-coll_obj_info.faces_start;
    unsigned face_idx=coll_obj_info.faces_start;
    for(unsigned i=0; i<num_coll_faces; ++i)
    {
      // triangulate face
      const face &f=m_faces[face_idx++];
      unsigned num_indices=f.num_vertices;
      if(num_indices>=3)
      {
        // create triangle fan out of the face /*todo: fix for concave polygons*/
        unsigned vidx0=m_vertices[f.start_vertex+0].point_idx-coll_obj_info.points_start;
        unsigned vidx1=m_vertices[f.start_vertex+1].point_idx-coll_obj_info.points_start;
        unsigned vidx2=m_vertices[f.start_vertex+2].point_idx-coll_obj_info.points_start;
        coll_obj.indices.push_back(vidx0);
        coll_obj.indices.push_back(vidx2);
        coll_obj.indices.push_back(vidx1);
        for(unsigned i=3; i<num_indices; ++i)
        {
          vidx1=vidx2;
          vidx2=m_vertices[f.start_vertex+i].point_idx-coll_obj_info.points_start;
          coll_obj.indices.push_back(vidx0);
          coll_obj.indices.push_back(vidx2);
          coll_obj.indices.push_back(vidx1);
        }
      }
    }
  }

  // vertex output buffers
  unsigned num_points=(unsigned)m_points.size();
  array<vec3f> mesh_positions;
  array<vec2f> mesh_uvs;
  array<vec3f> mesh_tangents;
  array<vec3f> mesh_binormals;
  array<vec3f> mesh_normals;
  mesh_positions.reserve(num_points);
  mesh_uvs.reserve(num_points);
  mesh_tangents.reserve(num_points);
  mesh_binormals.reserve(num_points);
  mesh_normals.reserve(num_points);

  // setup data pointers for mesh generation
  typedef pair<mat33f, unsigned> face_tbn_t;
  array<face_tbn_t> face_tbns_sp(m_max_valence);
  array<smoother> vertex_smoothers_sp(m_max_valence);
  face_tbn_t *face_tbns=face_tbns_sp.data();
  smoother *vertex_smoothers=vertex_smoothers_sp.data();
  const point *points=m_points.data();
  const vec2f *uvs=m_uvs.data();
  const vec3f *normals=m_normals.data();

  // process all points in the mesh
  unsigned num_vertices_total=0;
  for(unsigned pi=1; pi<num_points; ++pi)
  {
    // process all face vertices attached to the point
    vertex *vtx=points[pi].vertices;
    unsigned point_vertex_idx=0;
    while(vtx)
    {
      // calculate TBN scaled by face triangular area and opening angle
      face &f=m_faces[vtx->face_idx];
      const vertex &v0=m_vertices[f.start_vertex+vtx->face_vertex_idx];
      const vertex &v1=m_vertices[f.start_vertex+(vtx->face_vertex_idx+1==f.num_vertices?0:vtx->face_vertex_idx+1)];
      const vertex &v2=m_vertices[f.start_vertex+(vtx->face_vertex_idx==0?f.num_vertices-1:vtx->face_vertex_idx-1)];
      const vec3f &pos0=points[v0.point_idx].position;
      const vec3f &e0=points[v1.point_idx].position-pos0;
      const vec3f &e1=points[v2.point_idx].position-pos0;
      const vec2f &te0=uvs[v1.uv_idx]-uvs[v0.uv_idx];
      const vec2f &te1=uvs[v2.uv_idx]-uvs[v0.uv_idx];
      vec3f normal=cross(e0, e1);
      if(v0.normal_idx)
        normal=normals[v0.normal_idx]*norm(normal);
      mat33f face_tbn(e0*te1.y-e1*te0.y,
                      e0*te1.x-e1*te0.x,
                      normal);
      face_tbn*=acos(ssat(dot(unit_z(e0), unit_z(e1))));
      face_tbns[point_vertex_idx].first=face_tbn;
      face_tbns[point_vertex_idx].second=f.smoothing_group;

      // average vertex tangent space vectors within given angle thresholds
      smoother vertex_smoother;
      vertex_smoother.tbn=face_tbn;
      vertex_smoother.uv=uvs[v0.uv_idx];
      vec3f tbn_norm(norm(face_tbn.x), norm(face_tbn.y), norm(face_tbn.z));
      for(unsigned i=0; i<point_vertex_idx; ++i)
      {
        // average tangent spaces for normals within given angle threshold
        if((f.smoothing_group && f.smoothing_group==face_tbns[i].second) || dot(face_tbns[i].first.z, face_tbn.z)>s_epsilon_n_dot*norm(face_tbns[i].first.z)*tbn_norm.z)
        {
          // average tangents within given threshold
          if(dot(face_tbns[i].first.x, face_tbn.x)>s_epsilon_t_dot*norm(face_tbns[i].first.x)*tbn_norm.x)
          {
            vertex_smoothers[i].tbn.x+=face_tbn.x;
            vertex_smoother.tbn.x+=face_tbns[i].first.x;
          }

          // average binormals within given threshold
          if(dot(face_tbns[i].first.y, face_tbn.y)>s_epsilon_b_dot*norm(face_tbns[i].first.y)*tbn_norm.y)
          {
            vertex_smoothers[i].tbn.y+=face_tbn.y;
            vertex_smoother.tbn.y+=face_tbns[i].first.y;
          }

          // average normals
          vertex_smoothers[i].tbn.z+=face_tbn.z;
          vertex_smoother.tbn.z+=face_tbns[i].first.z;
        }
      }
      vertex_smoothers[point_vertex_idx++]=vertex_smoother;
      vtx=vtx->next;
    }

    // generate vertex streams for the point
    vtx=points[pi].vertices;
    unsigned vertex_idx=0;
    while(vtx)
    {
      // search for matching vertex
      smoother &vsmtr=vertex_smoothers[vertex_idx];
      smoother *smtr=linear_search(vertex_smoothers, vertex_smoothers+vertex_idx, vsmtr);
      if(smtr)
      {
        vtx->vertex_idx=smtr->vertex_idx;
        vsmtr.vertex_idx=smtr->vertex_idx;
      }
      else
      {
        // no match found, add new vertex
        vsmtr.vertex_idx=num_vertices_total;
        vtx->vertex_idx=num_vertices_total++;
        mesh_positions.push_back()=points[vtx->point_idx].position*mesh_tform;
        vec2f &uv=mesh_uvs.push_back();
        uv.x=vsmtr.uv.x;
        uv.y=1.0f-vsmtr.uv.y;
        vsmtr.tbn.x=unit_z(vsmtr.tbn.x);
        vsmtr.tbn.y=unit_z(vsmtr.tbn.y);
        vsmtr.tbn.z=unit_z(vsmtr.tbn.z);
        mesh_tangents.push_back()=vsmtr.tbn.x*mesh_tform;
        mesh_binormals.push_back()=vsmtr.tbn.y*mesh_tform;
        mesh_normals.push_back()=vsmtr.tbn.z*mesh_tform;
      }

      // proceed to the next vertex
      ++vertex_idx;
      vtx=vtx->next;
    }
  }

  // set mesh vertex data
  mesh_positions.trim();
  mesh_uvs.trim();
  mesh_tangents.trim();
  mesh_binormals.trim();
  mesh_normals.trim();
  mesh_vertex_buffer &vb=*mesh_.create_vertex_buffers(1);
  vb.add_channel(vtxchannel_position, mesh_positions.steal_data().steal_data(), num_vertices_total);
  if(m_uvs.size()>1)
  {
    vb.add_channel(vtxchannel_uv, mesh_uvs.steal_data().steal_data(), num_vertices_total);
    vb.add_channel(vtxchannel_tangent, mesh_tangents.steal_data().steal_data(), num_vertices_total);
    vb.add_channel(vtxchannel_binormal, mesh_binormals.steal_data().steal_data(), num_vertices_total);
  }
  vb.add_channel(vtxchannel_normal, mesh_normals.steal_data().steal_data(), num_vertices_total);

  // init mesh segments
  bool empty_material=true;
  material &mat=m_materials.back();
  for(unsigned i=0; i<max_mesh_lods; ++i)
    if(mat.faces[i])
    {
      empty_material=false;
      break;
    }
  if(empty_material)
    m_materials.pop_back();
  material *materials=m_materials.data();
  array<mesh_segment> mesh_segments(m_num_segments);
  mesh_segment *msegments=mesh_segments.data();
  array<uint32_t> mesh_indices;

  // create mesh segments and primitives from materials
  unsigned num_triangles_total=0;
  unsigned si=0;
  unsigned num_materials=(unsigned)m_materials.size();
  for(unsigned mi=0; mi<num_materials; ++mi)
  {
    // process all lods for the material
    for(unsigned lod=0; lod<max_mesh_lods; ++lod)
    {
      const face *f=materials[mi].faces[lod];
      if(f)
      {
        // setup mesh segment
        mesh_segment &seg=msegments[si];
        seg.material_name=materials[mi].name;
        seg.vertex_buffer=0;
        seg.primitive_type=meshprim_trilist;
        seg.prim_start_index=num_triangles_total*3;
        seg.lod=uint8_t(lod);
        ++si;

        // process all faces for the lod
        unsigned num_triangles=0;
        do
        {
          // triangulate face
          unsigned num_indices=f->num_vertices;
          if(num_indices>=3)
          {
            // create triangle fan out of the face /*todo: fix for concave polygons*/
            unsigned vidx0=m_vertices[f->start_vertex+0].vertex_idx;
            unsigned vidx1=m_vertices[f->start_vertex+1].vertex_idx;
            unsigned vidx2=m_vertices[f->start_vertex+2].vertex_idx;
            mesh_indices.push_back(vidx0);
            mesh_indices.push_back(vidx2);
            mesh_indices.push_back(vidx1);
            for(unsigned i=3; i<num_indices; ++i)
            {
              vidx1=vidx2;
              vidx2=m_vertices[f->start_vertex+i].vertex_idx;
              mesh_indices.push_back(vidx0);
              mesh_indices.push_back(vidx2);
              mesh_indices.push_back(vidx1);
            }
            num_triangles+=num_indices-2;
          }
          f=f->next;
        } while(f);

        // setup segment primitives
        seg.num_primitives=num_triangles;
        num_triangles_total+=num_triangles;
      }
    }
  }

  // finish mesh generation
  mesh_indices.trim();
  mesh_.swap_indices(mesh_indices);
  mesh_.swap_segments(mesh_segments);
  mesh_.swap_collision_objects(mesh_coll_objects);
}
//----------------------------------------------------------------------------


//============================================================================
// load_mesh_obj
//============================================================================
namespace pfc
{
  bool load_mesh_obj(mesh &m_, bin_input_stream_base &s_)
  {
    // check for OBJ file format
    {
      // determine OBJ format from the first non-empty line (must start with '#')
      auto_stream_seek<bin_input_stream_base> aseek(s_);
      text_input_stream stream(s_);
      stream.skip_whitespace();
      if(stream.is_eos())
        return false;
      char line[max_line_length];
      unsigned num_chars=(unsigned)stream.read_line(line, max_line_length);
      if(!num_chars || !is_ascii(line, num_chars) || line[0]!='#')
        return false;
    }

    // load the mesh
    mesh_loader_obj loader;
    loader.load(m_, s_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_OBJ
namespace pfc
{
  bool load_mesh_obj(mesh &m_, bin_input_stream_base &s_)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_OBJ
