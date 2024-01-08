//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/mesh.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_COLLADA
//============================================================================
// mesh_loader_collada
//============================================================================
class mesh_loader_collada
{
public:
  // loading
  void load(mesh&, bin_input_stream_base&);
  //--------------------------------------------------------------------------

private:
  struct geometry;
  typedef xml_input_stream::string_t string_t;
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_primitive_type
  //==========================================================================
  enum e_primitive_type
  {
    primtype_none,
    primtype_polygon_list,
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // segment
  //==========================================================================
  struct segment
  {
    // construction and operations
    PFC_INLINE segment() {geo=0; is_processed=false; primitive_type=primtype_none; start_index=0; num_primitives=0; num_tris=0; num_vtx_indices=0; num_joints=0;}
    //------------------------------------------------------------------------

    geometry *geo;
    bool is_processed;
    heap_str material_name;
    array<collada_data::source_input> inputs;
    e_primitive_type primitive_type;
    unsigned start_index;
    unsigned num_primitives;
    unsigned num_tris;
    unsigned num_vtx_indices;
    unsigned num_joints;
    array<uint16_t> joint_reindices;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // vertex
  //==========================================================================
  struct vertex
  {
    // vertex compare
    PFC_INLINE bool operator==(const vertex &v_) const
    {
      static const float epsilon_uv_sqr=sqr(0.001f);
      static const float epsilon_axis_sqr=sqr(cos(2.0f*mathf::deg_to_rad));
      return    joint_indices==v_.joint_indices
             && norm2(uv-v_.uv)<=epsilon_uv_sqr
             && (is_zero(tbn.x) || dot(tbn.x, v_.tbn.x)>=epsilon_axis_sqr)
             && (is_zero(tbn.y) || dot(tbn.y, v_.tbn.y)>=epsilon_axis_sqr)
             && dot(tbn.z, v_.tbn.z)>=epsilon_axis_sqr;
    }
    //------------------------------------------------------------------------

    mat33f tbn;
    vec2f uv;
    vertex *next;
    bool calc_tb;
    vec4<uint16_t> joint_indices;
    unsigned vertex_index;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // point
  //==========================================================================
  struct point
  {
    // construction
    PFC_INLINE point()  {vertices=0; valence=0;}
    //------------------------------------------------------------------------

    vec3f pos;
    vertex *vertices;
    unsigned valence;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // vertex_influence
  //==========================================================================
  enum {max_vertex_influences=4};
  struct vertex_influence
  {
    vec4<uint16_t> joint_indices;
    vec4f joint_weights;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_node_type
  //==========================================================================
  enum e_node_type
  {
    nodetype_node,
    nodetype_joint,
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // e_node_instance_type
  //==========================================================================
  enum e_node_instance_type
  {
    nodeinsttype_none,
    nodeinsttype_geometry,
    nodeinsttype_controller,
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // joint
  //==========================================================================
  struct joint
  {
    // construction and operations
    PFC_INLINE joint() {index=0; parent=-1;}
    PFC_INLINE bool operator==(const string_t &str_) const  {return name==str_;}
    //------------------------------------------------------------------------

    heap_str name;
    tform3f bind_o2j;
    unsigned index;
    int parent;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // node
  //==========================================================================
  struct node
  {
    // construction and operations
    PFC_INLINE node()  {type=nodetype_node; parent=-1; index=0; is_cvol=false; lod=0; inst_type=nodeinsttype_none; joint_idx=-1;}
    PFC_INLINE bool operator==(const string_t &str_) const  {return id==str_;}
    tform3f node_to_world(const node *nodes_) const  {return parent>=0?tform_n2p*nodes_[parent].node_to_world(nodes_):tform_n2p;}
    //------------------------------------------------------------------------

    e_node_type type;
    heap_str id, name, sid;
    int parent;
    unsigned index;
    bool is_cvol;
    uint8_t lod;
    tform3f tform_n2p;
    e_node_instance_type inst_type;
    heap_str inst_url;
    int joint_idx;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // geometry
  //==========================================================================
  struct geometry
  {
    // construction and operations
    PFC_INLINE geometry() {lod=0; is_cvol=false; total_vtx_count=num_total_vertices=num_total_triangles=num_total_materials=num_total_reindices=0; base_vertex_idx=unsigned(-1);}
    template<class S> PFC_INLINE bool operator==(const str_base<S> &id_) const  {return id==id_;}
    //------------------------------------------------------------------------

    string_t id;
    collada_data data;
    uint8_t lod;
    bool is_cvol;
    array<vec3f> mesh_positions;
    array<vec2f> mesh_uvs;
    array<vec3f> mesh_tangents;
    array<vec3f> mesh_binormals;
    array<vec3f> mesh_normals;
    array<vec4<uint16_t> > mesh_joint_indices;
    array<vec4f> mesh_joint_weights;
    array<unsigned> mesh_indices;
    array<vertex> vertices_sp;
    array<segment> segments;
    array<vertex_influence> vertex_joint_influences;
    array<joint> joints;
    tform3f bind_shape_tform;
    unsigned total_vtx_count;
    unsigned num_total_vertices;
    unsigned num_total_triangles;
    unsigned num_total_materials;
    unsigned num_total_reindices;
    unsigned base_vertex_idx;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // controller
  //==========================================================================
  struct controller
  {
    // construction and operations
    PFC_INLINE controller() {geo=0;}
    template<class S> PFC_INLINE bool operator==(const str_base<S> &id_) const  {return id==id_;}
    //------------------------------------------------------------------------

    string_t id;
    geometry *geo;
  };
  //--------------------------------------------------------------------------

  // data parsing
  void parse_geometries(xml_input_stream&, string_t&);
  void parse_mesh(xml_input_stream&, string_t&, geometry&);
  void parse_controllers(xml_input_stream&, string_t&);
  void parse_visual_scenes(xml_input_stream&, string_t&);
  void parse_node(xml_input_stream&, string_t&, int parent_idx_);
  unsigned num_source_inputs(const array<collada_data::source_input>&);
  //--------------------------------------------------------------------------

  // mesh generation
  void generate_mesh(mesh&);
  void init_joints(geometry&);
  //--------------------------------------------------------------------------

  collada_info m_asset_info;
  deque<geometry> m_geometries;
  deque<controller> m_controllers;
  array<node> m_nodes;
  float m_tform_quatw;
  unsigned m_tri_index[3];
};
//----------------------------------------------------------------------------

void mesh_loader_collada::load(mesh &mesh_, bin_input_stream_base &stream_)
{
  // parse <?xml...> and <COLLADA...> tags
  xml_input_stream xml_stream(stream_);
  string_t item_name;
  xml_stream.parse_item(item_name, true);
  xml_stream.parse_item(item_name, true);
  PFC_CHECK(item_name=="COLLADA");

  // setup mesh default transforms
  m_tform_quatw=-1.0f;
  m_tri_index[0]=0;
  m_tri_index[1]=m_tform_quatw>0.0f?1:2;
  m_tri_index[2]=m_tform_quatw>0.0f?2:1;

  // parse COLLADA elements
  while(xml_stream.parse_element(item_name, true))
  {
    if(item_name=="asset")
      m_asset_info.parse_asset_properties(xml_stream, item_name);
    else if(item_name=="library_geometries")
      parse_geometries(xml_stream, item_name);
    else if(item_name=="library_controllers")
      parse_controllers(xml_stream, item_name);
    else if(item_name=="library_visual_scenes")
      parse_visual_scenes(xml_stream, item_name);
    else
      xml_stream.skip_element();
  }

  // generate mesh from parsed data
  generate_mesh(mesh_);
}
//----------------------------------------------------------------------------

void mesh_loader_collada::parse_geometries(xml_input_stream &stream_, string_t &item_name_)
{
  // parse "library_geometries" elements
  while(stream_.parse_element(item_name_))
  {
    if(item_name_=="geometry")
    {
      // check "geometry" id attribute
      geometry &geo=m_geometries.push_back();
      stream_.find_attrib_str("id", geo.id);

      // parse "geometry" elements
      while(stream_.parse_element(item_name_, true))
      {
        if(item_name_=="mesh")
          parse_mesh(stream_, item_name_, geo);
        else
          stream_.skip_element();
      }
    }
    else
      stream_.skip_element();
  }
}
//----

void mesh_loader_collada::parse_mesh(xml_input_stream &stream_, string_t &item_name_, geometry &geo_)
{
  // parse "mesh" elements
  while(stream_.parse_element(item_name_))
    if(item_name_=="source")
      geo_.data.parse_data_source(stream_, item_name_);
    else if(item_name_=="vertices")
    {
      // parse "vertices" attributes and element
      collada_data::source &vformat=geo_.data.append_source();
      stream_.find_attrib_str("id", vformat.id);
      while(stream_.parse_element(item_name_))
      {
        if(item_name_=="input")
        {
          // parse vertex "input" attributes
          geo_.data.parse_source_input_attribs(vformat.inputs, stream_, item_name_);
          collada_data::source_input &input=vformat.inputs.back();
          input.offset=(unsigned)vformat.inputs.size()-1;
        }
        stream_.skip_element();
      }
    }
    else if(item_name_=="polygons")
    {
      // parse "polygons" attributes and elements
      segment &seg=geo_.segments.push_back();
      seg.primitive_type=primtype_polygon_list;
      seg.start_index=(unsigned)geo_.mesh_indices.size();
      stream_.find_attrib("count", seg.num_primitives);
      while(stream_.parse_element(item_name_))
      {
        if(item_name_=="p")
        {
          // read indices for the polygon
          stream_.skip_attribs();
          unsigned vtx_count_idx=(unsigned)geo_.mesh_indices.size();
          geo_.mesh_indices.push_back();
          unsigned old_mesh_indices=(unsigned)geo_.mesh_indices.size();
          unsigned idx;
          while(stream_.read(idx))
            geo_.mesh_indices.push_back(idx);
          unsigned vtx_count=((unsigned)geo_.mesh_indices.size()-old_mesh_indices)/seg.num_vtx_indices;
          geo_.total_vtx_count+=vtx_count;
          geo_.mesh_indices[vtx_count_idx]=vtx_count;
          seg.num_tris+=vtx_count-2;
        }
        else if(item_name_=="input")
        {
          // read segment vertex inputs
          geo_.data.parse_source_input_attribs(seg.inputs, stream_, item_name_);
          seg.num_vtx_indices=num_source_inputs(seg.inputs);
        }
        stream_.skip_element();
      }
    }
    else if(item_name_=="polylist")
    {
      // parse "polylist" attributes
      segment &seg=geo_.segments.push_back();
      seg.primitive_type=primtype_polygon_list;
      while(stream_.start_attrib_parsing(item_name_))
      {
        if(item_name_=="material")
          stream_.read_word(seg.material_name);
        else if(item_name_=="count")
          stream_>>seg.num_primitives;
        stream_.end_attrib_parsing();
      }

      // parse "polylist" elements
      unsigned num_primitives=seg.num_primitives;
      array<unsigned> vertex_counts(num_primitives);
      while(stream_.parse_element(item_name_))
      {
        if(item_name_=="input")
        {
          // read segment vertex inputs
          geo_.data.parse_source_input_attribs(seg.inputs, stream_, item_name_);
          seg.num_vtx_indices=num_source_inputs(seg.inputs);
        }
        else if(item_name_=="vcount")
        {
          stream_.skip_attribs();
          stream_.read(vertex_counts.data(), num_primitives);
        }
        else if(item_name_=="p")
        {
          // allocate indices for polygons
          stream_.skip_attribs();
          unsigned num_vtx_indices=seg.num_vtx_indices;
          unsigned num_total_poly_vertices=0;
          const unsigned *const vtx_counts=vertex_counts.data();
          for(unsigned i=0; i<num_primitives; ++i)
            num_total_poly_vertices+=vtx_counts[i];
          seg.start_index=(unsigned)geo_.mesh_indices.size();
          geo_.mesh_indices.insert_back(num_primitives+num_total_poly_vertices*num_vtx_indices);

          // setup indices for polygons
          unsigned *indices=geo_.mesh_indices.data()+seg.start_index;
          for(unsigned i=0; i<num_primitives; ++i)
          {
            unsigned vtx_count=vtx_counts[i];
            geo_.total_vtx_count+=vtx_count;
            *indices++=vtx_count;
            seg.num_tris+=vtx_count-2;
            unsigned num_poly_indices=vtx_counts[i]*num_vtx_indices;
            stream_.read(indices, num_poly_indices);
            indices+=num_poly_indices;
          }
        }

        stream_.skip_element();
      }
    }
    else if(item_name_=="triangles")
    {
      // parse "triangles" attributes
      segment &seg=geo_.segments.push_back();
      seg.primitive_type=primtype_polygon_list;
      while(stream_.start_attrib_parsing(item_name_))
      {
        if(item_name_=="material")
          stream_.read_word(seg.material_name);
        else if(item_name_=="count")
        {
          stream_>>seg.num_primitives;
          seg.num_tris+=seg.num_primitives;
        }
        stream_.end_attrib_parsing();
      }

      // parse "triangles" elements
      while(stream_.parse_element(item_name_))
      {
        if(item_name_=="input")
        {
          // read segment vertex inputs
          geo_.data.parse_source_input_attribs(seg.inputs, stream_, item_name_);
          seg.num_vtx_indices=num_source_inputs(seg.inputs);
        }
        else if(item_name_=="p")
        {
          // read triangle list indices
          stream_.skip_attribs();
          unsigned vtx_count=3*seg.num_primitives;
          geo_.total_vtx_count+=vtx_count;
          seg.start_index=(unsigned)geo_.mesh_indices.size();
          unsigned num_primitives=seg.num_primitives;
          unsigned num_vtx_indices=seg.num_vtx_indices;
          geo_.mesh_indices.insert_back(num_primitives+num_vtx_indices*vtx_count);
          unsigned *indices=geo_.mesh_indices.data()+seg.start_index;
          for(unsigned i=0; i<num_primitives; ++i)
          {
            *indices++=3;
            stream_.read(indices, 3*num_vtx_indices);
            indices+=3*num_vtx_indices;
          }
        }
        stream_.skip_element();
      }
    }
    else
      stream_.skip_element();
}
//----

void mesh_loader_collada::parse_controllers(xml_input_stream &stream_, string_t &item_name_)
{
  // parse "library_controllers" elements
  while(stream_.parse_element(item_name_))
  {
    // check for "controller"
    if(item_name_!="controller")
    {
      stream_.skip_element();
      continue;
    }

    // parse "controller" attributes
    string_t id;
    if(!stream_.find_attrib_str("id", id))
    {
      stream_.skip_element();
      continue;
    }

    // parse "controller" elements
    controller &ctrl=m_controllers.push_back();
    ctrl.id=id;
    while(stream_.parse_element(item_name_))
    {
      // check for "skin" controller
      if(item_name_!="skin")
      {
        stream_.skip_element();
        continue;
      }

      // parse "skin" attributes & elements
      string_t source_id;
      stream_.find_attrib_str("source", source_id);
      source_id.remove_front(1);
      geometry *geo=ptr(linear_search(m_geometries.begin(), m_geometries.end(), source_id));
      PFC_CHECK_MSG(geo, ("Geometry \"%s\" for the skin controller not found\r\n", source_id.c_str()));
      ctrl.geo=geo;
      while(stream_.parse_element(item_name_))
      {
        if(item_name_=="bind_shape_matrix")
        {
          // read skeleton transformation matrix
          stream_.skip_attribs();
          mat44f bsm;
          stream_.read(bsm);
          geo->bind_shape_tform.set(bsm.x.x, bsm.y.x, bsm.z.x, bsm.x.w,
                                    bsm.x.y, bsm.y.y, bsm.z.y, bsm.y.w,
                                    bsm.x.z, bsm.y.z, bsm.z.z, bsm.z.w);
          stream_.skip_element();
        }
        else if(item_name_=="source")
          geo->data.parse_data_source(stream_, item_name_);
        else if(item_name_=="joints")
        {
          // parse "joints" elements
          array<collada_data::source_input> inputs;
          stream_.skip_attribs();
          while(stream_.parse_element(item_name_))
          {
            if(item_name_=="input")
              geo->data.parse_source_input_attribs(inputs, stream_, item_name_);
            stream_.skip_element();
          }

          // setup joints
          const collada_data::source_input *joint_data=linear_search(inputs.begin(), inputs.end(), collsemantic_joint);
          PFC_CHECK(joint_data);
          const collada_data::data_array<heap_str> &joint_names=geo->data.name_array(joint_data->array_index);
          const collada_data::source_input *inv_bind_data=linear_search(inputs.begin(), inputs.end(), collsemantic_inv_bind_matrix);
          PFC_CHECK(inv_bind_data);
          const collada_data::data_array<float> &inv_bind_tforms=geo->data.float_array(inv_bind_data->array_index);
          unsigned stride=inv_bind_tforms.stride;
          PFC_CHECK(stride==16);
          unsigned num_joints=(unsigned)joint_names.data.size();
          geo->joints.resize(num_joints);
          const float *ibd=inv_bind_tforms.data.data();
          for(unsigned i=0; i<num_joints; ++i)
          {
            // setup joint
            joint &j=geo->joints[i];
            j.name=joint_names.data[i];
            j.bind_o2j.set(ibd[0], ibd[4],  ibd[8],  ibd[3],
                           ibd[1], ibd[5],  ibd[9],  ibd[7],
                           ibd[2], ibd[6], ibd[10], ibd[11]);
            ibd+=stride;
          }
        }
        else if(item_name_=="vertex_weights")
        {
          // parse "vertex_weights" attributes and elements
          unsigned num_verts=0;
          stream_.find_attrib("count", num_verts);
          array<collada_data::source_input> inputs;
          array<unsigned> influence_counts;
          while(stream_.parse_element(item_name_))
          {
            if(item_name_=="input")
              geo->data.parse_source_input_attribs(inputs, stream_, item_name_);
            else if(item_name_=="vcount")
            {
              // read vertex influence counts
              stream_.skip_attribs();
              influence_counts.resize(num_verts);
              stream_.read(influence_counts.data(), num_verts);
            }
            else if(item_name_=="v")
            {
              // setup vertex influence access
              stream_.skip_attribs();
              unsigned num_inf_indices=num_source_inputs(inputs);
              collada_data::source_input *input_joint=linear_search(inputs.begin(), inputs.end(), collsemantic_joint);
              PFC_CHECK(input_joint);
              unsigned offset_joint=input_joint->offset;
              collada_data::source_input *input_weight=linear_search(inputs.begin(), inputs.end(), collsemantic_weight);
              PFC_CHECK(input_weight);
              unsigned offset_weight=input_weight->offset;
              const float *data_weight=geo->data.float_array(input_weight->array_index).data.data();

              // setup joint influences for vertices
              array<unsigned> index_sp(num_inf_indices);
              unsigned *indices=index_sp.data();
              geo->vertex_joint_influences.resize(num_verts);
              mem_zero(geo->vertex_joint_influences.data(), sizeof(vertex_influence)*num_verts);
              for(unsigned vi=0; vi<num_verts; ++vi)
              {
                // read and setup joint influences for the vertex
                vertex_influence &inf=geo->vertex_joint_influences[vi];
                unsigned num_joint_influences=influence_counts[vi];
                for(unsigned i=0; i<num_joint_influences; ++i)
                {
                  // read influence and replace smallest influence with the new influence
                  stream_.read(indices, num_inf_indices);
                  float weight=data_weight[indices[offset_weight]];
                  unsigned idx=i;
                  if(i>=max_vertex_influences)
                  {
                    // find smallest influence
                    float min_weight=numeric_type<float>::range_max();
                    for(unsigned wi=0; wi<max_vertex_influences; ++wi)
                      if(inf.joint_weights[wi]<min_weight)
                      {
                        min_weight=inf.joint_weights[wi];
                        idx=wi;
                      }

                    // discard current influence if smaller than smallest influence
                    if(weight<min_weight)
                      continue;
                  }

                  // store joint influence
                  inf.joint_indices[idx]=uint16_t(indices[offset_joint]);
                  inf.joint_weights[idx]=weight;
                }

                // normalize weights
                inf.joint_weights*=rcp_z(dot1(inf.joint_weights));
              }
            }
            stream_.skip_element();
          }
        }
        else
          stream_.skip_element();
      }
    }
  }
}
//----

void mesh_loader_collada::parse_visual_scenes(xml_input_stream &stream_, string_t &item_name_)
{
  // parse "library_visual_scenes" elements
  while(stream_.parse_element(item_name_, true))
  {
    // skip other than "visual_scene" elements
    if(item_name_!="visual_scene")
    {
      stream_.skip_element();
      continue;
    }

    // parse "visual_scene" elements
    while(stream_.parse_element(item_name_))
    {
      if(item_name_=="node")
        parse_node(stream_, item_name_, -1);
      else
        stream_.skip_element();
    }
  }
}
//----

void mesh_loader_collada::parse_node(xml_input_stream &stream_, string_t &item_name_, int parent_idx_)
{
  // parse "node" attributes
  unsigned node_index=(unsigned)m_nodes.size();
  node *n=&m_nodes.push_back();
  n->index=node_index;
  while(stream_.start_attrib_parsing(item_name_))
  {
    if(item_name_=="id")
      stream_.read_word(n->id);
    else if(item_name_=="name")
    {
      stream_.read_word(n->name);
      n->is_cvol=(parent_idx_>=0?m_nodes[parent_idx_].is_cvol:false) || is_collision_subobject(n->name.c_str());
      n->lod=subobject_lod(n->name.c_str());
      if(!n->lod && parent_idx_>=0)
        n->lod=m_nodes[parent_idx_].lod;
    }
    else if(item_name_=="sid")
      stream_.read_word(n->sid);
    else if(item_name_=="type")
    {
      string_t node_type;
      stream_.read_word(node_type);
      if(node_type=="JOINT")
        n->type=nodetype_joint;
    }
    stream_.end_attrib_parsing();
  }
  if(!n->sid.size())
    n->sid=n->id;

  // parse "node" elements
  n->parent=parent_idx_;
  n=0; // recursive calls will invalidate this by pushing values to m_nodes
  tform3f node_tform_n2p;
  while(stream_.parse_element(item_name_))
  {
    if(item_name_=="node")
    {
      parse_node(stream_, item_name_, node_index);
      continue;
    }
    if(item_name_=="instance_geometry")
    {
      node &n=m_nodes[node_index];
      if(stream_.find_attrib_str("url", n.inst_url))
      {
        n.inst_url.remove_front(1);
        n.inst_type=nodeinsttype_geometry;
      }
    }
    else if(item_name_=="instance_controller")
    {
      node &n=m_nodes[node_index];
      if(stream_.find_attrib_str("url", n.inst_url))
      {
        n.inst_url.remove_front(1);
        n.inst_type=nodeinsttype_controller;
      }
    }
    else
    {
      stream_.skip_attribs();
      if(item_name_=="matrix")
      {
        // parse node transformation matrix
        mat44f m;
        stream_>>m;
        node_tform_n2p=tform3f(m.x.x, m.y.x, m.z.x, m.x.w,
                               m.x.y, m.y.y, m.z.y, m.y.w,
                               m.x.z, m.y.z, m.z.z, m.z.w)*node_tform_n2p;
      }
      else if(item_name_=="translate")
      {
        vec3f translation;
        stream_>>translation;
        node_tform_n2p=tform3f(translation)*node_tform_n2p;
      }
      else if(item_name_=="rotate")
      {
        vec4f rot;
        stream_>>rot;
        node_tform_n2p=tform3f(axis_rot(vec3f(rot.x, rot.y, rot.z), rot.w*mathf::deg_to_rad))*node_tform_n2p;
      }
      else if(item_name_=="scale")
      {
        vec3f scaling;
        stream_>>scaling;
        node_tform_n2p=tform3f(scaling.x, scaling.y, scaling.z)*node_tform_n2p;
      }
    }
    stream_.skip_element();
  }

  // setup node transform
  m_nodes[node_index].tform_n2p=node_tform_n2p;
}
//----------------------------------------------------------------------------

unsigned mesh_loader_collada::num_source_inputs(const array<collada_data::source_input> &inputs_)
{
  // get max input offset
  const collada_data::source_input *inputs=inputs_.data();
  unsigned num_inputs=(unsigned)inputs_.size();
  unsigned max_offset=0;
  for(unsigned i=0; i<num_inputs; ++i)
    max_offset=max(max_offset, inputs[i].offset);
  return max_offset+1;
}
//----------------------------------------------------------------------------

void mesh_loader_collada::generate_mesh(mesh &mesh_)
{
  // process all parsed nodes
  geometry *skinning_geo=0;
  array<segment*> mesh_segment_ptrs;
  array<mesh_collision_object> mesh_collision_objects;
  for(unsigned cur_node_idx=0; cur_node_idx<m_nodes.size(); ++cur_node_idx)
  {
    // find geometry & setup geometry transform
    geometry *geo=0;
    tform3f geo_tform;
    node &n=m_nodes[cur_node_idx];
    switch(n.inst_type)
    {
      case nodeinsttype_geometry:
      {
        // find geometry for the node
        deque<geometry>::iterator it=linear_search(m_geometries.begin(), m_geometries.end(), n.inst_url);
        if(is_valid(it))
        {
          geo=ptr(it);
          geo_tform=n.node_to_world(m_nodes.data());
        }
      } break;

      case nodeinsttype_controller:
      {
        deque<controller>::iterator it=linear_search(m_controllers.begin(), m_controllers.end(), n.inst_url);
        if(is_valid(it))
        {
          geo=it->geo;
          geo_tform=geo->bind_shape_tform;
          geo_tform*=n.node_to_world(m_nodes.data());
        }
      } break;

      case nodeinsttype_none: break;
    }

    // check for geometry and initialize geometry transformations
    if(!geo)
      continue;
    geo->is_cvol=n.is_cvol;
    geo->lod=n.lod;
    geo_tform*=m_asset_info.basis_tform();
    mat33f vec_tform=geo_tform.matrix33();
    normalize(vec_tform);

    // check for collision volume
    if(geo->is_cvol)
    {
      // add segments
      for(unsigned si=0; si<geo->segments.size(); ++si)
      {
        // access geometry points and indices
        const segment &seg=geo->segments[si];
        const collada_data::source_input *input_pos=linear_search(seg.inputs.begin(), seg.inputs.end(), collsemantic_position);
        PFC_CHECK_MSG(input_pos, ("Mesh segment doesn't contain vertex positions\r\n"));
        unsigned offset_pos=input_pos->offset;
        const collada_data::data_array<float> &pos_data_array=geo->data.float_array(input_pos->array_index);
        const float *data_pos=pos_data_array.data.data();
        unsigned num_points=(unsigned)pos_data_array.data.size()/3;
        unsigned stride_pos=pos_data_array.stride;
        const unsigned *indices=geo->mesh_indices.data()+seg.start_index+offset_pos;
        unsigned num_vtx_indices=seg.num_vtx_indices;

        // add collision object and get associated joint node index
        mesh_collision_object &cobj=mesh_collision_objects.push_back();
        int nidx=n.index;
        while(nidx!=-1 && m_nodes[nidx].type!=nodetype_joint)
          nidx=m_nodes[nidx].parent;
        cobj.joint_index=nidx;

        // add collision geometry points
        cobj.points.resize(num_points);
        vec3f *coll_points=cobj.points.data();
        for(unsigned i=0; i<num_points; ++i)
          coll_points[i]=*(const vec3f*)(data_pos+i*stride_pos)*geo_tform;

        // add collision geometry triangles
        cobj.indices.resize(seg.num_tris*3);
        uint32_t *coll_indices=cobj.indices.data();
        switch(seg.primitive_type)
        {
          // polygon list
          case primtype_polygon_list:
          {
            // generate triangles for the polygon /*todo: fix for concave polygons*/
            for(unsigned pi=0; pi<seg.num_primitives; ++pi)
            {
              const unsigned num_poly_verts=*indices++;
              unsigned vidx0=*indices; indices+=num_vtx_indices;
              unsigned vidx1=*indices; indices+=num_vtx_indices;
              unsigned vidx2=*indices; indices+=num_vtx_indices;
              coll_indices[0]=vidx0;
              coll_indices[1]=vidx1;
              coll_indices[2]=vidx2;
              coll_indices+=3;
              for(unsigned i=3; i<num_poly_verts; ++i)
              {
                vidx1=vidx2;
                vidx2=*indices; indices+=num_vtx_indices;
                *coll_indices++=vidx0;
                *coll_indices++=vidx1;
                *coll_indices++=vidx2;
              }
            }
          } break;

          // unsupported type
          default: PFC_ERROR("Unsupported primitive type\r\n");
        }
      }
      continue;
    }

    // init geometry info
    geo->num_total_vertices=0;
    geo->num_total_triangles=0;
    geo->num_total_materials=0;
    geo->num_total_reindices=0;
    unsigned max_valence=0;

    // setup scratch pad data arrays
    array<point> points_sp;
    geo->vertices_sp.resize(geo->total_vtx_count);
    vertex *const vertices=geo->vertices_sp.data();

    // init joints and access joint & influence data
    if(geo->joints.size())
    {
      init_joints(*geo);
      if(!skinning_geo)
        skinning_geo=geo;
    }
    const vertex_influence *joint_influences=geo->vertex_joint_influences.data();
    const unsigned num_joint_influences=(unsigned)geo->vertex_joint_influences.size();
    const unsigned num_joints=(unsigned)geo->joints.size();

    // build mesh connectivity info
    array<uint16_t> inv_joint_reindices_sp(num_joints);
    uint16_t *inv_joint_reindices=inv_joint_reindices_sp.data();
    array<pair<unsigned, unsigned> > pos_offsets;
    for(unsigned si=0; si<geo->segments.size(); ++si)
    {
      // setup vertex element access for the segment
      segment &seg=geo->segments[si];
      mat33f polygon_tbn;
      collada_data::source_input *input_pos=linear_search(seg.inputs.begin(), seg.inputs.end(), collsemantic_position);
      PFC_CHECK_MSG(input_pos, ("Mesh segment doesn't contain vertex positions\r\n"));
      unsigned offset_pos=input_pos->offset;
      const float *data_pos=geo->data.float_array(input_pos->array_index).data.data();
      unsigned stride_pos=geo->data.float_array(input_pos->array_index).stride;
      collada_data::source_input *input_texcoord=linear_search(seg.inputs.begin(), seg.inputs.end(), collsemantic_texcoord);
      unsigned offset_texcoord=input_texcoord?input_texcoord->offset:0;
      const float *data_texcoord=input_texcoord?geo->data.float_array(input_texcoord->array_index).data.data():(const float*)&vec2f::s_zero;
      unsigned stride_texcoord=input_texcoord?geo->data.float_array(input_texcoord->array_index).stride:0;
      collada_data::source_input *input_textangent=linear_search(seg.inputs.begin(), seg.inputs.end(), collsemantic_textangent);
      unsigned offset_textangent=input_textangent?input_textangent->offset:0;
      const float *data_textangent=input_textangent?geo->data.float_array(input_textangent->array_index).data.data():(const float*)&polygon_tbn.x;
      unsigned stride_textangent=input_textangent?geo->data.float_array(input_textangent->array_index).stride:0;
      collada_data::source_input *input_texbinormal=linear_search(seg.inputs.begin(), seg.inputs.end(), collsemantic_texbinormal);
      unsigned offset_texbinormal=input_texbinormal?input_texbinormal->offset:0;
      const float *data_texbinormal=input_texbinormal?geo->data.float_array(input_texbinormal->array_index).data.data():(const float*)&polygon_tbn.y;
      unsigned stride_texbinormal=input_texbinormal?geo->data.float_array(input_texbinormal->array_index).stride:0;
      collada_data::source_input *input_normal=linear_search(seg.inputs.begin(), seg.inputs.end(), collsemantic_normal);
      unsigned offset_normal=input_normal?input_normal->offset:0;
      const float *data_normal=input_normal?geo->data.float_array(input_normal->array_index).data.data():(const float*)&polygon_tbn.z;
      unsigned stride_normal=input_normal?geo->data.float_array(input_normal->array_index).stride:0;
      bool calc_tb=input_texcoord && input_normal && (!input_textangent || !input_texbinormal);

      // search for points array for given data array
      unsigned pos_offset=unsigned(-1);
      for(unsigned i=0; i<pos_offsets.size(); ++i)
        if(pos_offsets[i].first==input_pos->array_index)
        {
          pos_offset=pos_offsets[i].second;
          break;
        }

      // append new points array if no match found
      if(pos_offset==unsigned(-1))
      {
        pos_offset=(unsigned)points_sp.size();
        pos_offsets.push_back(pair<unsigned, unsigned>(input_pos->array_index, pos_offset));
        points_sp.insert_back(geo->data.float_array(input_pos->array_index).data.size()/3);
      }
      point *points=points_sp.data()+pos_offset;

      // switch to proper primitive type handling
      mem_zero(inv_joint_reindices, num_joints*sizeof(*inv_joint_reindices));
      switch(seg.primitive_type)
      {
        // polygon list
        case primtype_polygon_list:
        {
          // setup segment
          const unsigned *indices=geo->mesh_indices.data()+seg.start_index;
          unsigned num_vtx_indices=seg.num_vtx_indices;
          if(seg.num_primitives)
          {
            seg.geo=geo;
            mesh_segment_ptrs.push_back(&seg);
            ++geo->num_total_materials;
          }

          // process all primitives for the segment
          for(unsigned pi=0; pi<seg.num_primitives; ++pi)
          {
            // get 3 vertices for polygon TBN calculation
            const unsigned num_poly_verts=*indices++;
            geo->num_total_triangles+=num_poly_verts-2;
            const unsigned *const poly_indices=indices;
            vec3f p0=*(const vec3f*)(data_pos+indices[offset_pos]*stride_pos);
            vec3f p1=*(const vec3f*)(data_pos+indices[offset_pos+num_vtx_indices]*stride_pos);
            vec3f p2=*(const vec3f*)(data_pos+indices[offset_pos+num_vtx_indices*2]*stride_pos);
            vec2f t0=*(const vec2f*)(data_texcoord+indices[offset_texcoord]*stride_texcoord);
            vec2f t1=*(const vec2f*)(data_texcoord+indices[offset_texcoord+num_vtx_indices]*stride_texcoord);
            vec2f t2=*(const vec2f*)(data_texcoord+indices[offset_texcoord+num_vtx_indices*2]*stride_texcoord);

            // calculate TBN for the polygon
            const vec3f &e0=p1-p0;
            const vec3f &e1=p2-p0;
            const vec2f &te0=t1-t0;
            const vec2f &te1=t2-t0;
            polygon_tbn.set(unit_z(e0*te1.y-e1*te0.y),
                            unit_z(e0*te1.x-e1*te0.x),
                            unit_z(cross(e0, e1)));

            // add vertices for the polygon
            for(unsigned vi=0; vi<num_poly_verts; ++vi)
            {
              // add vertex to the vertex list of the polygon point
              vertex &vtx=vertices[geo->num_total_vertices++];
              unsigned pnt_index=indices[offset_pos];
              point &pnt=points[pnt_index];
              pnt.pos=*(const vec3f*)(data_pos+indices[offset_pos]*stride_pos)*geo_tform;
              vtx.next=pnt.vertices;
              vtx.calc_tb=calc_tb;
              vtx.vertex_index=0;
              pnt.vertices=&vtx;
              ++pnt.valence;
              max_valence=max(max_valence, pnt.valence);

              vtx.joint_indices.set(uint16_t(0));
              if(joint_influences)
              {
                // setup re-indexed joint indices for the segment
                const vec4<uint16_t> &joint_indices=joint_influences[pnt_index].joint_indices;
                const vec4f &joint_weights=joint_influences[pnt_index].joint_weights;
                for(unsigned i=0; i<max_vertex_influences; ++i)
                  if(joint_weights[i])
                  {
                    uint16_t ji=inv_joint_reindices[joint_indices[i]];
                    if(!ji)
                      inv_joint_reindices[joint_indices[i]]=ji=uint16_t(++seg.num_joints);
                    vtx.joint_indices[i]=ji-1;
                  }
              }

              // setup vertex UV coordinates and TBN
              const float *texcoord=data_texcoord+indices[offset_texcoord]*stride_texcoord;
              vtx.uv.set(texcoord[0], 1.0f-texcoord[1]);
              const float *textangent=data_textangent+indices[offset_textangent]*stride_textangent;
              vtx.tbn.x.set(textangent[0], textangent[1], textangent[2]);
              const float *texbinormal=data_texbinormal+indices[offset_texbinormal]*stride_texbinormal;
              vtx.tbn.y.set(texbinormal[0], texbinormal[1], texbinormal[2]);
              const float *normal=data_normal+indices[offset_normal]*stride_normal;
              vtx.tbn.z=unit_z(vec3f(normal[0], normal[1], normal[2]));

              // weight vertex tangent & binormal with triangular area & angle of adjacent edges
              unsigned vi_prev=(vi?vi:num_poly_verts)-1;
              unsigned vi_next=(vi==num_poly_verts-1)?0:vi+1;
              vec3f p=*(const vec3f*)(data_pos+poly_indices[vi*num_vtx_indices+offset_pos]*stride_pos);
              vec3f pp=*(const vec3f*)(data_pos+poly_indices[vi_prev*num_vtx_indices+offset_pos]*stride_pos);
              vec3f pn=*(const vec3f*)(data_pos+poly_indices[vi_next*num_vtx_indices+offset_pos]*stride_pos);
              const vec3f &edge_prev=pp-p;
              const vec3f &edge_next=pn-p;
              float weight=norm(cross(edge_prev, edge_next))*acos(ssat(dot(unit_z(edge_prev), unit_z(edge_next))));
              vtx.tbn.x*=weight;
              vtx.tbn.y*=weight;
              vtx.tbn*=vec_tform;

              // proceed to the next vertex
              indices+=num_vtx_indices;
            }
          }
        } break;

        // unsupported type
        default: PFC_ERROR("Unsupported primitive type\r\n");
      }

      // setup joint re-indexing for the segment
      seg.joint_reindices.resize(seg.num_joints);
      uint16_t *joint_reindices=seg.joint_reindices.data();
      for(unsigned i=0; i<num_joints; ++i)
        if(inv_joint_reindices[i])
          joint_reindices[inv_joint_reindices[i]-1]=uint16_t(i);
      geo->num_total_reindices+=seg.num_joints;
    }

    // setup TBN-axis and UV epsilons for merging
    static const float epsilon_uv_sqr=sqr(0.001f);
    static const float s_epsilon_t_dot=cos(90.0f*mathf::deg_to_rad);
    static const float s_epsilon_b_dot=cos(90.0f*mathf::deg_to_rad);
    static const float s_epsilon_n_dot_sqr=sqr(cos(2.0f*mathf::deg_to_rad));

    // init vertex output buffers
    unsigned num_points=(unsigned)points_sp.size();
    geo->mesh_positions.reserve(num_points);
    geo->mesh_uvs.reserve(num_points);
    geo->mesh_tangents.reserve(num_points);
    geo->mesh_binormals.reserve(num_points);
    geo->mesh_normals.reserve(num_points);
    geo->mesh_joint_indices.reserve(num_joint_influences?num_points:0);
    geo->mesh_joint_weights.reserve(num_joint_influences?num_points:0);

    // process all mesh points
    geo->num_total_vertices=0;
    array<vertex> point_vertices(max_valence);
    vertex *pnt_verts=point_vertices.data();
    const point *points=points_sp.data();
    for(unsigned pi=0; pi<num_points; ++pi)
    {
      // process all vertices for the point
      unsigned num_point_vertices=0;
      vertex *vtx=points[pi].vertices;
      while(vtx)
      {
        vertex new_vertex=*vtx;
        if(vtx->calc_tb)
        {
          // calculate tangent and binormal for the vertex
          const float vtx_epsilon_t_dot=s_epsilon_t_dot*norm(vtx->tbn.x);
          const float vtx_epsilon_b_dot=s_epsilon_b_dot*norm(vtx->tbn.y);
          const vertex *v=points[pi].vertices;
          while(v)
          {
            if(   v!=vtx
               && norm2(v->uv-vtx->uv)<=epsilon_uv_sqr
               && dot(v->tbn.x, vtx->tbn.x)>=norm(v->tbn.x)*vtx_epsilon_t_dot
               && dot(v->tbn.y, vtx->tbn.y)>=norm(v->tbn.y)*vtx_epsilon_b_dot
               && dot(v->tbn.z, vtx->tbn.z)>=s_epsilon_n_dot_sqr)
            {
              new_vertex.tbn.x+=v->tbn.x;
              new_vertex.tbn.y+=v->tbn.y;
            }
            v=v->next;
          }
        }

        // search for vertex duplicate
        new_vertex.tbn.x=unit_z(new_vertex.tbn.x);
        new_vertex.tbn.y=unit_z(new_vertex.tbn.y);
        vertex *dup_vertex=linear_search(pnt_verts, num_point_vertices, new_vertex);
        if(dup_vertex)
          vtx->vertex_index=dup_vertex->vertex_index;
        else
        {
          // no duplicate => add new vertex
          new_vertex.vertex_index=geo->num_total_vertices;
          pnt_verts[num_point_vertices++]=new_vertex;
          vtx->vertex_index=geo->num_total_vertices++;
          geo->mesh_positions.push_back(points[pi].pos);
          geo->mesh_uvs.push_back(new_vertex.uv);
          geo->mesh_tangents.push_back(new_vertex.tbn.x);
          geo->mesh_binormals.push_back(new_vertex.tbn.y);
          geo->mesh_normals.push_back(new_vertex.tbn.z);
          if(num_joint_influences)
          {
            PFC_CHECK(pi<num_joint_influences);
            geo->mesh_joint_indices.push_back(vtx->joint_indices);
            geo->mesh_joint_weights.push_back(joint_influences[pi].joint_weights);
          }
        }

        // proceed to the next vertex
        vtx=vtx->next;
      }
    }
    geo->num_total_vertices=0;
  }

  // map collision mesh node indices to joint indices
  unsigned num_coll_objs=(unsigned)mesh_collision_objects.size();
  for(unsigned i=0; i<num_coll_objs; ++i)
  {
    mesh_collision_object &cobj=mesh_collision_objects[i];
    if(cobj.joint_index>=0)
    {
      const node &n=m_nodes[cobj.joint_index];
      cobj.joint_index=n.joint_idx;
    }
  }

  // generate final geometry from the segment data
  array<vec3f> mesh_positions;
  array<vec2f> mesh_uvs;
  array<vec3f> mesh_tangents;
  array<vec3f> mesh_binormals;
  array<vec3f> mesh_normals;
  array<vec4<uint16_t> > mesh_joint_indices;
  array<vec4f> mesh_joint_weights;
  array<uint32_t> mesh_indices;
  array<mesh_segment> mesh_segments;
  array<uint16_t> mesh_joint_reindices;
  segment **seg_end=mesh_segment_ptrs.data()+mesh_segment_ptrs.size();
  for(unsigned seg_idx=0; seg_idx<mesh_segment_ptrs.size(); ++seg_idx)
  {
    segment **find_seg=mesh_segment_ptrs.data()+seg_idx;
    segment *init_seg=*find_seg, *seg=init_seg;
    unsigned start_idx=(unsigned)mesh_indices.size();
    unsigned num_triangles=0;
    do
    {
      geometry *geo=seg->geo;
      if(!seg->is_processed)
      {
        // check if geometry data is stored to mesh_* arrays
        seg->is_processed=true;
        unsigned base_vertex_idx=geo->base_vertex_idx;
        if(base_vertex_idx==unsigned(-1))
        {
          // copy mesh geometry data to mesh_* arrays
          base_vertex_idx=(unsigned)mesh_positions.size();
          geo->base_vertex_idx=base_vertex_idx;
          unsigned num_verts=(unsigned)geo->mesh_positions.size();
          mesh_positions.insert_back(num_verts, geo->mesh_positions.data());
          mesh_uvs.insert_back(num_verts, geo->mesh_uvs.data());
          mesh_tangents.insert_back(num_verts, geo->mesh_tangents.data());
          mesh_binormals.insert_back(num_verts, geo->mesh_binormals.data());
          mesh_normals.insert_back(num_verts, geo->mesh_normals.data());
          if(geo->mesh_joint_indices.size())
          {
            mesh_joint_indices.insert_back(num_verts, geo->mesh_joint_indices.data());
            mesh_joint_weights.insert_back(num_verts, geo->mesh_joint_weights.data());
          }
          else
            if(skinning_geo)
            {
              mesh_joint_indices.insert_back(num_verts, vec4<uint16_t>::s_zero);
              mesh_joint_weights.insert_back(num_verts, vec4f::s_zero);
            }
        }

        // setup segment index data
        switch(int(seg->primitive_type))
        {
          // polygon list
          case primtype_polygon_list:
          {
            // triangulate polygon list
            const vertex *vertices=geo->vertices_sp.data();
            const unsigned *indices=geo->mesh_indices.data()+seg->start_index;
            for(unsigned pi=0; pi<seg->num_primitives; ++pi)
            {
              // create triangle fan out of the polygon /*todo: fix for concave polygons*/
              const unsigned num_poly_verts=*indices++;
              unsigned vidx[3]={vertices[geo->num_total_vertices++].vertex_index+base_vertex_idx,
                                vertices[geo->num_total_vertices++].vertex_index+base_vertex_idx,
                                vertices[geo->num_total_vertices++].vertex_index+base_vertex_idx};
              mesh_indices.push_back(vidx[m_tri_index[0]]);
              mesh_indices.push_back(vidx[m_tri_index[1]]);
              mesh_indices.push_back(vidx[m_tri_index[2]]);
              for(unsigned i=3; i<num_poly_verts; ++i)
              {
                vidx[1]=vidx[2];
                vidx[2]=vertices[geo->num_total_vertices++].vertex_index+base_vertex_idx;
                mesh_indices.push_back(vidx[m_tri_index[0]]);
                mesh_indices.push_back(vidx[m_tri_index[1]]);
                mesh_indices.push_back(vidx[m_tri_index[2]]);
              }
              indices+=seg->num_vtx_indices*num_poly_verts;
              num_triangles+=num_poly_verts-2;
            }
          } break;
        }
      }

      // proceed to the next segment with the same material name & LOD
      if(skinning_geo)
        break;
      while(   ++find_seg!=seg_end
            && (   (*find_seg)->geo->lod!=seg->geo->lod
                || (*find_seg)->geo->is_cvol
                || (*find_seg)->material_name!=seg->material_name));
      seg=find_seg!=seg_end?*find_seg:0;
    } while(seg);

    if(num_triangles)
    {
      // setup mesh segment
      mesh_segment &mseg=mesh_segments.push_back();
      mseg.material_name=init_seg->material_name;
      mseg.lod=init_seg->geo->lod;
      mseg.vertex_buffer=0;
      mseg.primitive_type=meshprim_trilist;
      mseg.num_primitives=num_triangles;
      mseg.prim_start_index=start_idx;
      mseg.num_joints=uint16_t(init_seg->num_joints);
      mseg.joint_reindexing_start=uint16_t(mesh_joint_reindices.size());
      mesh_joint_reindices.insert_back(init_seg->num_joints, init_seg->joint_reindices.data());
    }
  }

  mesh_vertex_buffer &vb=*mesh_.create_vertex_buffers(1);
  unsigned num_total_vertices=(unsigned)mesh_positions.size();
  vb.add_channel(vtxchannel_position, mesh_positions.steal_data().steal_data(), num_total_vertices);
  vb.add_channel(vtxchannel_uv, mesh_uvs.steal_data().steal_data(), num_total_vertices);
  vb.add_channel(vtxchannel_tangent, mesh_tangents.steal_data().steal_data(), num_total_vertices);
  vb.add_channel(vtxchannel_binormal, mesh_binormals.steal_data().steal_data(), num_total_vertices);
  vb.add_channel(vtxchannel_normal, mesh_normals.steal_data().steal_data(), num_total_vertices);
  if(mesh_joint_indices.size())
  {
    // add mesh joint influences for skinning
    vb.add_channel(vtxchannel_joint_indices, mesh_joint_indices.steal_data().steal_data(), num_total_vertices);
    vb.add_channel(vtxchannel_joint_weights, mesh_joint_weights.steal_data().steal_data(), num_total_vertices);
  }

  if(skinning_geo)
  {
    // setup mesh skeleton joints
    unsigned num_joints=(unsigned)skinning_geo->joints.size();
    mesh_skeleton *skel=mesh_.create_skeleton();
    skel->joints.resize(num_joints);
    const joint *joints=skinning_geo->joints.data();
    mesh_skeleton::joint *mesh_joints=skel->joints.data();
    array<char> &joint_names=skel->joint_names;
    for(unsigned ji=0; ji<num_joints; ++ji)
    {
      // setup joint parent & name
      const joint &j=joints[ji];
      mesh_skeleton::joint &mb=mesh_joints[ji];
      mb.parent_idx=j.parent>=0?uint16_t(j.parent):0;
      mb.name_idx=uint16_t(joint_names.size());
      const char *joint_name=j.name.c_str();
      joint_names.insert_back(j.name.size()+1, joint_name);
      mb.name_crc32=crc32(joint_name);

      // setup joint transformation
      tform_rt3f j2o(inv(j.bind_o2j)*m_asset_info.basis_tform());
      mb.bind_o2j=inv(j2o);
      mb.bind_j2p=j2o;
      if(j.parent>=0)
        mb.bind_j2p*=mesh_joints[j.parent].bind_o2j;
    }
  }

  // swap mesh content
  mesh_.swap_indices(mesh_indices);
  mesh_.swap_segments(mesh_segments);
  mesh_.swap_collision_objects(mesh_collision_objects);
  mesh_.swap_joint_reindices(mesh_joint_reindices);
}
//----

void mesh_loader_collada::init_joints(geometry &geo_)
{
  // sort joints based on the scene node hierarchy (depth-first)
  const unsigned num_joints=(unsigned)geo_.joints.size();
  joint *joints=geo_.joints.data();
  array<joint> new_joints(num_joints);
  unsigned num_nodes=(unsigned)m_nodes.size();
  node *nodes=m_nodes.data();
  unsigned ji=0;
  for(unsigned i=0; i<num_nodes; ++i)
  {
    // search for joint name with given joint node sid
    node &n=nodes[i];
    if(n.type==nodetype_joint)
    {
      joint *j=linear_search(joints, num_joints, n.sid);
      if(j)
      {
        j->index=ji;
        new_joints[ji]=*j;
        j=&new_joints[ji];
      }
/*      else
      {
        // add new joint in hierarchy not used by skinning controller
        new_joints.push_back();
        j=&new_joints[ji];
        j->name=n.sid;
        j->bind_o2j=inv(n.node_to_world(nodes));
        j->index=ji;
      }*/

      // setup joint parent and index
      n.joint_idx=ji;
      j->parent=n.parent>=0?nodes[n.parent].joint_idx:-1;
      ++ji;
    }
  }
  geo_.joints.swap(new_joints);

  // update vertex influences to the new hierarchical joint indices
  vertex_influence *influences=geo_.vertex_joint_influences.data();
  unsigned num_influences=(unsigned)geo_.vertex_joint_influences.size();
  for(unsigned vi=0; vi<num_influences; ++vi)
  {
    vertex_influence &inf=influences[vi];
    for(unsigned i=0; i<max_vertex_influences; ++i)
    {
      inf.joint_indices[i]=inf.joint_weights[i]?uint16_t(joints[inf.joint_indices[i]].index):0;
      PFC_ASSERT(inf.joint_indices[i]<geo_.joints.size());
    }
  }
}
//----------------------------------------------------------------------------


//============================================================================
// load_mesh_collada
//============================================================================
namespace pfc
{
  bool load_mesh_collada(mesh &m_, bin_input_stream_base &s_)
  {
    {
      // check for COLLADA file format
      auto_stream_seek<bin_input_stream_base> aseek(s_);
      text_input_stream txt_stream(s_);
      char sig_str[8];
      txt_stream.read_word(sig_str, sizeof(sig_str));
      if(!str_eq(sig_str, "<?xml"))
        return false;
      txt_stream.skip_to('<', true);
      txt_stream.read_word(sig_str, sizeof(sig_str));
      if(!str_eq(sig_str, "COLLADA"))
        return false;
    }

    // load the mesh
    mesh_loader_collada loader;
    loader.load(m_, s_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_COLLADA
namespace pfc
{
  bool load_mesh_collada(mesh &m_, bin_input_stream_base &s_)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_COLLADA
