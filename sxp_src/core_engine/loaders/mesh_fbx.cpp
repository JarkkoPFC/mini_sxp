//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/mesh.h"
#include "sxp_src/core/math/color.h"
#include "sxp_src/core/zip.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
#if 0 // log FBX file structure
#define PFC_FBX_LOG(x__) PFC_LOG(x__)
#define PFC_FBX_INDENT_LOG() PFC_INDENT_LOG()
#define PFC_FBX_UNINDENT_LOG() PFC_UNINDENT_LOG()
#else
#define PFC_FBX_LOG(x__)
#define PFC_FBX_INDENT_LOG()
#define PFC_FBX_UNINDENT_LOG()
#endif
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_FBX
//==========================================================================
// fbx_vertex
//==========================================================================
struct fbx_vertex
{
  enum {max_uv_channels=2};
  vec3f pos;
  vec3f normal;
  vec2f uv[max_uv_channels];
};
PFC_SET_TYPE_TRAIT(fbx_vertex, pfc::is_type_pod, true);
//--------------------------------------------------------------------------


//============================================================================
// mesh_loader_fbx
//============================================================================
class mesh_loader_fbx
{
public:
  // construction and loading
  mesh_loader_fbx();
  void load(mesh&, bin_input_stream_base&);
  //--------------------------------------------------------------------------

private:
  //==========================================================================
  // e_mapping_type
  //==========================================================================
  enum e_mapping_type
  {
    maptype_none,
    maptype_by_poly,
    maptype_by_poly_vtx,
    maptype_by_vtx,
    maptype_by_edge,
    maptype_all_same
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_reference_type
  //==========================================================================
  enum e_reference_type
  {
    reftype_none,
    reftype_direct,
    reftype_index_to_direct,
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // buffer_data
  //==========================================================================
  template<typename T>
  struct buffer_data
  {
    const T *data;
    usize_t size;
    e_mapping_type maptype;
    e_reference_type reftype;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // buffer
  //==========================================================================
  struct buffer
  {
    // construction & comparison
    PFC_INLINE buffer() {maptype=maptype_none; reftype=reftype_none;}
    PFC_INLINE bool operator==(const char *name_) const {return name==name_;}
    //------------------------------------------------------------------------

    typedef variant<array<uint8_t>, array<int32_t>, array<float32_t>, array<int64_t>, array<float64_t> > buffer_variant_t;
    heap_str name;
    e_mapping_type maptype;
    e_reference_type reftype;
    buffer_variant_t arr;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // connection_oo
  //==========================================================================
  struct connection_oo
  {
    // construction & comparison
    PFC_INLINE connection_oo() {ids[0]=0; ids[1]=0;}
    PFC_INLINE bool operator==(int64_t id_) const {return ids[0]==id_ || ids[1]==id_;}
    //------------------------------------------------------------------------

    int64_t ids[2];
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // geometry
  //==========================================================================
  struct geometry
  {
    // construction & comparison
    PFC_INLINE geometry() {id=0;}
    PFC_INLINE bool operator==(const connection_oo &con_) const {return con_.ids[0]==id || con_.ids[1]==id;}
    //------------------------------------------------------------------------

    int64_t id;
    list<buffer> buffers;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // prop
  //==========================================================================
  struct prop
  {
    // comparison
    PFC_INLINE bool operator==(const char *name_) const {return name==name_;}
    //------------------------------------------------------------------------

    typedef variant<int32_t, int64_t, double, vec3d, heap_str> value_t;
    heap_str name;
    value_t value;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // model
  //==========================================================================
  struct model
  {
    // comparison
    PFC_INLINE bool operator==(int64_t id_) const {return id==id_;}
    //------------------------------------------------------------------------

    int64_t id;
    heap_str name;
    list<prop> props;
  };
  //--------------------------------------------------------------------------

  // mesh data parsing and generation
  template<typename> bool parse_geometry_buffer(bin_input_stream_base&, const char *name_);
  template<typename T, typename U> buffer_data<T> find_buffer(const geometry&, const char *name_, unsigned idx_=0);
  bool parse_node_data(bin_input_stream_base&, unsigned recursion_depth_);
  bool generate_mesh(mesh&);
  template<typename T> bool map_vertex_data(deque<fbx_vertex>&, const buffer_data<int32_t> &vtx_idx_, usize_t base_vidx_, const buffer_data<T> &data_, const buffer_data<uint32_t> &idx_data_, void(mesh_loader_fbx::*tform_)(fbx_vertex&, const T&));
  void normal_tform(fbx_vertex &vtx_, const vec3d &v_) {vtx_.normal=to_vec3<float>(v_*m_cur_normal_tform);}
  void uv_tform(fbx_vertex &vtx_, const vec2d &v_) {vtx_.uv[m_cur_uv_channel]=to_vec2<float>(v_);}
  //--------------------------------------------------------------------------

  // current state
  usize_t m_stream_start_pos;
  geometry *m_cur_geometry;
  list<buffer> *m_cur_buffer_list;
  model *m_cur_model;
  list<prop> *m_cur_prop_list;
  prop *m_cur_prop;
  bool m_is_connections;
  e_mapping_type m_cur_maptype;
  e_reference_type m_cur_reftype;
  mat33d m_cur_normal_tform;
  unsigned m_cur_uv_channel;
  // data
  list<geometry> m_geometries;
  list<model> m_models;
  list<connection_oo> m_connections_oo;
};
//----------------------------------------------------------------------------

mesh_loader_fbx::mesh_loader_fbx()
{
  m_stream_start_pos=0;
  m_cur_geometry=0;
  m_cur_buffer_list=0;
  m_cur_model=0;
  m_cur_prop_list=0;
  m_cur_prop=0;
  m_is_connections=false;
  m_cur_maptype=maptype_none;
  m_cur_reftype=reftype_none;
  m_cur_normal_tform=mat33d::s_identity;
  m_cur_uv_channel=0;
}
//----

void mesh_loader_fbx::load(mesh &mesh_, bin_input_stream_base &s_)
{
  // read the FBX file header and check for proper FBX format
  m_stream_start_pos=s_.pos();
  uint8_t id[21];
  s_.read_bytes(id, sizeof(id));
  PFC_CHECK_MSG(mem_eq(id, "Kaydara FBX Binary  ", sizeof(id)), ("Invalid FBX file\r\n"));
  uint16_t eof_marker;
  uint32_t version;
  s_>>eof_marker>>version;

  // parse data and generate mesh
  while(parse_node_data(s_, 0));
  generate_mesh(mesh_);
}
//----------------------------------------------------------------------------

template<typename T>
bool mesh_loader_fbx::parse_geometry_buffer(bin_input_stream_base &s_, const char *name_)
{
  // read buffer properties
  uint32_t size, encoding_type, comp_size;
  s_>>size>>encoding_type>>comp_size;
  PFC_FBX_LOG(("array<%s> (size=%i)\r\n", typeid(T).name(), size));
  if(encoding_type>1)
  {
    PFC_ERROR(("Unknown array data encoding type \"%i\" for property \"%s\"\r\n", encoding_type, name_));
    return false;
  }

  // check for active buffer list
  if(!m_cur_buffer_list)
  {
    s_.skip(encoding_type=1?comp_size:size*sizeof(T));
    return true;
  }

  // add new buffer
  buffer &buf=m_cur_buffer_list->push_back();
  buf.name=name_;
  buf.maptype=m_cur_maptype;
  buf.reftype=m_cur_reftype;
  array<T> &arr=type_set<array<T> >(buf.arr);
  arr.resize(size);

  // read buffer data
  if(encoding_type==1)
  {
    // read zlib compressed data
    raw_data comp_data(comp_size);
    s_.read_bytes(comp_data.data, comp_size);
    mem_input_stream ms(comp_data.data, comp_size);
    zip_input_stream zs(ms, comp_size);
    zs.read(arr.data(), size);
  }
  else
    s_.read(arr.data(), size);
  return true;
}
//----

template<typename T, typename U>
mesh_loader_fbx::buffer_data<T> mesh_loader_fbx::find_buffer(const geometry &geo_, const char *name_, unsigned idx_)
{
  // find buffer of given instance of given name buffer
  list<buffer>::const_iterator it=geo_.buffers.begin();
  do 
  {
    it=linear_search(it, geo_.buffers.end(), name_);
  } while(is_valid(it) && idx_-- && is_valid(++it));

  // return buffer contents
  buffer_data<T> bdata={0, 0};
  if(const buffer *buf=ptr(it))
  {
    const array<U> &arr=type_ref<array<U> >(buf->arr);
    bdata.data=(const T*)arr.data();
    bdata.size=unsigned(arr.size()*sizeof(U)/sizeof(T));
    bdata.maptype=buf->maptype;
    bdata.reftype=buf->reftype;
  }
  return bdata;
}
//----

bool mesh_loader_fbx::parse_node_data(bin_input_stream_base &s_, unsigned recursion_depth_)
{
  // read node header
  uint32_t end_offset, num_props, prop_list_size;
  uint8_t node_name_len;
  char node_name[256];
  s_>>end_offset>>num_props>>prop_list_size>>node_name_len;
  s_.read_bytes(node_name, node_name_len);
  node_name[node_name_len]=0;
  if(!recursion_depth_ && !end_offset)
    return false;
  PFC_FBX_LOG(("\"%s\":\r\n", node_name));
  PFC_FBX_LOG(("{\r\n"));

  // check for specific node types
  bool is_model=recursion_depth_==1 && str_eq(node_name, "Model");
  if(is_model)
  {
    m_cur_model=&m_models.push_back();
    m_cur_prop_list=&m_cur_model->props;
  }
  bool is_geometry=recursion_depth_==1 && str_eq(node_name, "Geometry");
  if(is_geometry)
  {
    m_cur_geometry=&m_geometries.push_back();
    m_cur_buffer_list=&m_cur_geometry->buffers;
  }
  bool is_connections=recursion_depth_==0 && str_eq(node_name, "Connections");
  if(is_connections)
    m_is_connections=true;
  bool is_connection=m_is_connections && recursion_depth_==1 && str_eq(node_name, "C");
  bool is_connection_oo=false;

  // check for property node and init property parsing state
  bool is_prop=str_eq(node_name, "P");
  if(is_prop && m_cur_prop_list)
    m_cur_prop=&m_cur_prop_list->push_back();
  bool is_prop_used=false;
  heap_str prop_type;

  // parse node properties
  PFC_FBX_INDENT_LOG();
  for(unsigned pi=0; pi<num_props; ++pi)
  {
    uint8_t type;
    s_>>type;
    switch(type)
    {
      // year (2 bytes)
      case 'Y':
      {
        // read 16-bit int
        int16_t v;
        s_>>v;
        PFC_FBX_LOG(("int16_t: %i\r\n", v));
      } break;

      // char (1 byte)
      case 'C':
      {
        // read character
        char v;
        s_>>v;
        PFC_FBX_LOG(("char: 0x%02x\r\n", v));
      } break;

      // int (4 bytes)
      case 'I':
      {
        // read 32-bit integer
        int v;
        s_>>v;
        if(m_cur_prop && (prop_type=="int" || prop_type=="enum" || prop_type=="bool"))
        {
          type_set<int32_t>(m_cur_prop->value)=v;
          is_prop_used=true;
        }
        PFC_FBX_LOG(("int32_t: %i\r\n", v));
      } break;

      // float (4 bytes)
      case 'F':
      {
        // read float
        float32_t v;
        s_>>v;
        PFC_FBX_LOG(("float32_t: %f\r\n", v));
      } break;

      // double (8 bytes)
      case 'D':
      {
        // read double
        float64_t v;
        s_>>v;
        PFC_FBX_LOG(("float64_t: %f\r\n", v));

        // check for property node 3d vector value
        if(m_cur_prop && (prop_type=="ColorRGB" || prop_type=="Vector3D" ||  prop_type=="Lcl Translation" || prop_type=="Lcl Rotation" || prop_type=="Lcl Scaling"))
        {
          if(pi==4)
          {
            type_set<vec3d>(m_cur_prop->value);
            is_prop_used=true;
          }
          type_ref<vec3d>(m_cur_prop->value)[pi-4]=v;
        }

        // check for property node scalar value
        if(m_cur_prop && (prop_type=="double" || prop_type=="Number"))
        {
          type_set<float64_t>(m_cur_prop->value)=v;
          is_prop_used=true;
        }
      } break;

      // long int (8 bytes)
      case 'L':
      {
        // read 64-bit int (long)
        uint64_t v;
        s_>>v;
        PFC_FBX_LOG(("int64_t: %ld\r\n", v));

        // check geometry or model ID
        if(is_geometry && pi==0)
          m_cur_geometry->id=v;
        if(is_model && pi==0)
          m_cur_model->id=v;

        // check for property node value
        if(m_cur_prop && (prop_type=="KTime" || prop_type=="ULongLong"))
        {
          type_set<int64_t>(m_cur_prop->value)=v;
          is_prop_used=true;
        }

        // check for connection data
        if(is_connection_oo && (pi==1 || pi==2))
          m_connections_oo.back().ids[pi-1]=v;
      } break;

      // string
      case 'S':
      {
        // read string
        uint32_t size;
        s_>>size;
        char str[256];
        s_.read_bytes(str, size);
        str[size]=0;
        PFC_FBX_LOG(("str: \"%s\"\r\n", str));

        // check for property node
        if(m_cur_prop)
        {
          switch(pi)
          {
            case 0: m_cur_prop->name=str; break;
            case 1: prop_type=str; break;
            case 4:
            {
              if(prop_type=="KString" || prop_type=="DateTime")
              {
                type_set<heap_str>(m_cur_prop->value)=str;
                is_prop_used=true;
              }
            } break;
          }
        }

        // check for model name
        if(is_model && pi==1)
          m_cur_model->name=str;

        // check for OO-connection node
        if(is_connection && pi==0 && str_eq(str, "OO"))
        {
          m_connections_oo.push_back();
          is_connection_oo=true;
        }

        // check for mapping type node
        if(recursion_depth_==3 && str_eq(node_name, "MappingInformationType"))
        {
          m_cur_maptype=maptype_none;
          if(str_eq(str, "ByPolygon"))
            m_cur_maptype=maptype_by_poly;
          else if(str_eq(str, "ByPolygonVertex"))
            m_cur_maptype=maptype_by_poly_vtx;
          else if(str_eq(str, "ByVertex"))
            m_cur_maptype=maptype_by_vtx;
          else if(str_eq(str, "ByEdge"))
            m_cur_maptype=maptype_by_edge;
          else if(str_eq(str, "AllSame"))
            m_cur_maptype=maptype_all_same;
        }

        // check for reference type node
        if(recursion_depth_==3 && str_eq(node_name, "ReferenceInformationType"))
        {
          m_cur_reftype=reftype_none;
          if(str_eq(str, "Direct"))
            m_cur_reftype=reftype_direct;
          else if(str_eq(str, "IndexToDirect"))
            m_cur_reftype=reftype_index_to_direct;
        }
      } break;

      // raw data
      case 'R':
      {
        // skip raw data
        uint32_t size;
        s_>>size;
        s_.skip(size);
        PFC_FBX_LOG(("<raw-data>\r\n"));
      } break;

      // arrays
      case 'b': if(!parse_geometry_buffer<uint8_t>(s_, node_name)) return false; break;
      case 'i': if(!parse_geometry_buffer<int32_t>(s_, node_name)) return false; break;
      case 'f': if(!parse_geometry_buffer<float32_t>(s_, node_name)) return false; break;
      case 'l': if(!parse_geometry_buffer<int64_t>(s_, node_name)) return false; break;
      case 'd': if(!parse_geometry_buffer<float64_t>(s_, node_name)) return false; break;

      // unknown type
      default:
      {
        PFC_ERROR(("Unsupported node \"%s\" property type \'0x%02x\'\r\n", node_name, type));
        return false;
      } break;
    }
  }

  // parse nested nodes
  usize_t end=m_stream_start_pos+end_offset;
  bool parse_ok=true;
  while(parse_ok && s_.pos()<end)
    parse_ok=parse_node_data(s_, recursion_depth_+1);
  PFC_FBX_UNINDENT_LOG();

  // restore state
  if(is_prop && m_cur_prop)
  {
    if(!is_prop_used)
      m_cur_prop_list->pop_back();
    m_cur_prop=0;
  }
  if(is_geometry || is_model)
  {
    m_cur_geometry=0;
    m_cur_buffer_list=0;
    m_cur_model=0;
    m_cur_prop_list=0;
  }
  if(is_connections)
    m_is_connections=false;
  if(recursion_depth_==2)
  {
    m_cur_maptype=maptype_none;
    m_cur_reftype=reftype_none;
  }

  // finish node
  PFC_FBX_LOG(("}\r\n"));
  return parse_ok;
}
//----

bool mesh_loader_fbx::generate_mesh(mesh &m_)
{
  // collect model-geometry connections
  deque<fbx_vertex> vertices;
  unsigned num_prim_verts=0;
  array<uint32_t> tri_list_idx;
  array<mesh_segment> segs;
  bool has_normals=false;
  unsigned num_uv_channels=0;
  for(list<model>::const_iterator model_it=m_models.begin(); is_valid(model_it); ++model_it)
  {
    // setup model local->world transformation (positions & normals)
    const model &m=*model_it;
    tform3d l2w;
    if(const prop *lcl_scaling=ptr(linear_search(m.props.begin(), m.props.size(), "Lcl Scaling")))
    {
      // apply scaling
      const vec3d &scale=type_ref<vec3d>(lcl_scaling->value);
      l2w.set(scale.x, scale.y, scale.z);
    }
    if(const prop *lcl_rotation=ptr(linear_search(m.props.begin(), m.props.size(), "Lcl Rotation")))
    {
      // apply rotation
      const vec3d &rot_angles=type_ref<vec3d>(lcl_rotation->value);
      mat33d rm;
      set_rotation_xyz(rm, rot_angles.x, rot_angles.y, rot_angles.z);
      l2w*=rm;
    }
    m_cur_normal_tform=inv(l2w.matrix33());
    transpose(m_cur_normal_tform);
    if(const prop *lcl_translation=ptr(linear_search(m.props.begin(), m.props.size(), "Lcl Translation")))
      // apply translation
      l2w.set_translation(type_ref<vec3d>(lcl_translation->value));

    // search for model-geometry connection
    list<connection_oo>::const_iterator con_it=m_connections_oo.begin(), con_it_end=m_connections_oo.end();
    while(is_valid(con_it=linear_search(con_it, con_it_end, m.id)))
    {
      // search for geometry for the connection
      if(const geometry *geo=ptr(linear_search(m_geometries.begin(), m_geometries.size(), *con_it)))
      {
        // check for valid vertex index data
        buffer_data<int32_t> pvtx_idx=find_buffer<int32_t, int32_t>(*geo, "PolygonVertexIndex");
        if(pvtx_idx.size<3)
          break;

        // build triangle list
        usize_t tri_list_start=tri_list_idx.size();
        {
          // find proper face start (at least two successive positive indices)
          usize_t pvi=0;
          int32_t i0, i1;
          do
          {
            i0=pvtx_idx.data[pvi+0];
            i1=pvtx_idx.data[pvi+1];
            ++pvi;
          } while((i0<0 || i1<0) && pvi<pvtx_idx.size-1);
          i0=num_prim_verts++;
          i1=num_prim_verts++;

          // add triangle list primitives (fanify faces)
          while(++pvi<pvtx_idx.size)
          {
            tri_list_idx.push_back(i0);
            tri_list_idx.push_back(i1);
            int32_t i2=pvtx_idx.data[pvi];
            if(i2<0)
            {
              // end of primitive
              i2=num_prim_verts++;
              tri_list_idx.push_back(i2);
//              tri_list_idx.push_back(~i2);

              // get next primitive (skip prims with <3 vertices)
              while(++pvi<pvtx_idx.size-1)
              {
                i0=pvtx_idx.data[pvi+0];
                i2=pvtx_idx.data[pvi+1];
                if(i0>=0 && i1>=0)
                  break;
              }
              i0=num_prim_verts++;
              i2=num_prim_verts++;
              ++pvi;
            }
            else
            {
              i2=num_prim_verts++;
              tri_list_idx.push_back(i2);
            }
            i1=i2;
          }
        }
        if(tri_list_idx.size()==tri_list_start)
          break;

        // add mesh segment
        mesh_segment &seg=segs.push_back();
        seg.primitive_type=meshprim_trilist;
        seg.num_primitives=unsigned((tri_list_idx.size()-tri_list_start)/3);
        seg.prim_start_index=unsigned(tri_list_start);

        // add initial vertices for polygons
        usize_t base_vidx=vertices.size();
        buffer_data<vec3d> positions=find_buffer<vec3d, float64_t>(*geo, "Vertices");
        vertices.insert_back(pvtx_idx.size);
        for(usize_t pvi=0; pvi<pvtx_idx.size; ++pvi)
        {
          fbx_vertex &v=vertices[base_vidx+pvi];
          int vidx=pvtx_idx.data[pvi];
          if(vidx<0)
            vidx=~vidx;
          v.pos=to_vec3<float>(positions.data[vidx]*l2w);
        }

        // setup vertex normals
        buffer_data<vec3d> normals=find_buffer<vec3d, float64_t>(*geo, "Normals");
        if(normals.size)
        {
          has_normals=true;
          buffer_data<uint32_t> normal_idx=find_buffer<uint32_t, int32_t>(*geo, "NormalsIndex");
          if(!map_vertex_data(vertices, pvtx_idx, base_vidx, normals, normal_idx, &mesh_loader_fbx::normal_tform))
          {
            errorf("Vertex normal mapping failed\r\n");
            return false;
          }
        }

        // setup UV mapping
        for(unsigned uvi=0; uvi<fbx_vertex::max_uv_channels; ++uvi)
        {
          buffer_data<vec2d> uvs=find_buffer<vec2d, float64_t>(*geo, "UV", uvi);
          if(!uvs.size)
            break;
          num_uv_channels=max(uvi+1, num_uv_channels);
          buffer_data<uint32_t> uv_idx=find_buffer<uint32_t, int32_t>(*geo, "UVIndex");
          m_cur_uv_channel=uvi;
          if(!map_vertex_data(vertices, pvtx_idx, base_vidx, uvs, uv_idx, &mesh_loader_fbx::uv_tform))
          {
            errorf("Vertex UV mapping failed (channel %i)\r\n", uvi);
            return false;
          }
        }
        break;
      }
      ++con_it;
    }
  }

  // setup mesh segments & indices
  m_.swap_segments(segs);
  m_.swap_indices(tri_list_idx);

  // allocate vertex buffer data
  unsigned num_verts=unsigned(vertices.size());
  owner_data vtx_position_data=PFC_MEM_ALLOC(num_verts*sizeof(vec3f));
  vec3f *vtx_positions=(vec3f*)vtx_position_data.data;
  owner_data vtx_normal_data=has_normals?PFC_MEM_ALLOC(num_verts*sizeof(vec3f)):0;
  vec3f *vtx_normals=(vec3f*)vtx_normal_data.data;
  owner_data vtx_uv_data[fbx_vertex::max_uv_channels];
  vec2f *vtx_uvs[fbx_vertex::max_uv_channels]={0};
  for(unsigned uvi=0; uvi<num_uv_channels; ++uvi)
  {
    vtx_uv_data[uvi]=PFC_MEM_ALLOC(num_verts*sizeof(vec2f));
    vtx_uvs[uvi]=(vec2f*)vtx_uv_data[uvi].data;
  }

  // split vertex data to channels
  for(unsigned vi=0; vi<num_verts; ++vi)
  {
    const fbx_vertex &vtx=vertices[vi];
    vtx_positions[vi]=vtx.pos;
    if(has_normals)
      vtx_normals[vi]=vtx.normal;
    for(unsigned uvi=0; uvi<num_uv_channels; ++uvi)
      vtx_uvs[uvi][vi]=vtx.uv[uvi];
  }

  // create mesh vertex buffer
  mesh_vertex_buffer &vbuf=*m_.create_vertex_buffers(1);
  vbuf.add_channel(vtxchannel_position, vtx_position_data, num_verts);
  if(has_normals)
    vbuf.add_channel(vtxchannel_normal, vtx_normal_data, num_verts);
  for(unsigned uvi=0; uvi<num_uv_channels; ++uvi)
    vbuf.add_channel(vtxchannel_uv, vtx_uv_data[uvi], num_verts);

  return true;
}
//----

template<typename T>
bool mesh_loader_fbx::map_vertex_data(deque<fbx_vertex> &vertices_, const buffer_data<int32_t> &pvtx_idx_, usize_t base_vidx_, const buffer_data<T> &data_, const buffer_data<uint32_t> &data_idx_, void(mesh_loader_fbx::*tform_)(fbx_vertex&, const T&))
{
  switch(data_.maptype)
  {
    // map data by polygon
    case maptype_by_poly:
    {
      usize_t poly_idx=0;
      for(usize_t pvi=0; pvi<pvtx_idx_.size; ++pvi)
      {
        fbx_vertex &v=vertices_[base_vidx_+pvi];
        usize_t didx=data_.reftype==reftype_index_to_direct?data_idx_.data[poly_idx]:poly_idx;
        (this->*tform_)(v, data_.data[didx]);
        if(pvtx_idx_.data[pvi]<0)
          ++poly_idx;
      }
    } break;

    // map data by polygon vertex
    case maptype_by_poly_vtx:
    {
      for(usize_t pvi=0; pvi<pvtx_idx_.size; ++pvi)
      {
        fbx_vertex &v=vertices_[base_vidx_+pvi];
        usize_t didx=data_.reftype==reftype_index_to_direct?data_idx_.data[pvi]:pvi;
        (this->*tform_)(v, data_.data[didx]);
      }
    } break;

    // map data by vertex
    case maptype_by_vtx:
    {
      for(usize_t pvi=0; pvi<pvtx_idx_.size; ++pvi)
      {
        fbx_vertex &v=vertices_[base_vidx_+pvi];
        int vidx=pvtx_idx_.data[pvi];
        if(vidx<0)
          vidx=~vidx;
        usize_t didx=data_.reftype==reftype_index_to_direct?data_idx_.data[vidx]:vidx;
        (this->*tform_)(v, data_.data[didx]);
      }
    } break;

    // map data by edge
    case maptype_by_edge:
    {
      /*todo*/
      PFC_ERROR_NOT_IMPL();
    } break;

    // map same data to all vertices
    case maptype_all_same:
    {
      for(usize_t pvi=0; pvi<pvtx_idx_.size; ++pvi)
      {
        fbx_vertex &v=vertices_[base_vidx_+pvi];
        (this->*tform_)(v, data_.data[0]);
      }
    } break;

    // unknown mapping
    default: errorf("Unsupported data mapping type\r\n"); return false;
  }
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// load_mesh_fbx
//============================================================================
namespace pfc
{
  bool load_mesh_fbx(mesh &m_, bin_input_stream_base &s_)
  {
    // check for FBX file format
    uint8_t id[21];
    s_.read_bytes(id, sizeof(id));
    s_.rewind(sizeof(id));
    if(!mem_eq(id, "Kaydara FBX Binary  ", sizeof(id)))
      return false;

    // load the mesh
    mesh_loader_fbx loader;
    loader.load(m_, s_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_FBX
namespace pfc
{
  bool load_mesh_fbx(mesh &m_, bin_input_stream_base &s_)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_FBX
