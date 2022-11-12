//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/mesh.h"
#include "sxp_src/core/math/color.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_LWO
//============================================================================
// mesh_loader_lwo
//============================================================================
#define PFC_LWO_CHUNKID(c0__, c1__, c2__, c3__) ((uint32_t(c0__)<<24)|(uint32_t(c1__)<<16)|(uint32_t(c2__)<<8)|uint32_t(c3__))
#define PFC_LWO_WARN(warn__) {} //PFC_WARN(warn__)
class mesh_loader_lwo
{
public:
  // loading
  void load(mesh&, bin_input_stream_base&);
  //--------------------------------------------------------------------------

private:
  //==========================================================================
  // e_polygon_type
  //==========================================================================
  enum e_polygon_type
  {
    polytype_none,
    polytype_face,
    polytype_ptch,
    polytype_bone,
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // tag
  //==========================================================================
  struct tag
  {
    heap_str name;
    unsigned surface_idx;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // polygon
  //==========================================================================
  struct polygon
  {
    // construction
    PFC_INLINE polygon() :type(polytype_none), surface_tag_index(0), part_index(uint16_t(-1)), smoothing_group(uint16_t(-1)), num_indices(0), index_start(0), next(0) {}
    //------------------------------------------------------------------------

    e_polygon_type type:16;
    uint16_t surface_tag_index;
    uint16_t part_index;
    uint16_t smoothing_group;
    uint16_t num_indices;
    unsigned index_start;
    polygon *next;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // point
  //==========================================================================
  struct point
  {
    vec3f position;
    unsigned first_polygon_idx;
    uint16_t first_polygon_vtx_idx;
    uint16_t valence;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // index
  //==========================================================================
  struct index
  {
    unsigned point_idx;
    unsigned vertex_idx;
    unsigned next_polygon_idx;
    unsigned next_polygon_vtx_idx;
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

    mat33f tbn;
    vec2f uv;
    float max_smooth_angle;
    bool double_sided;
    index *idx;
    uint16_t smoothing_group;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // vertex
  //==========================================================================
  struct vertex
  {
    vec3f position;
    vec2f uv;
    mat33f tbn;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // vertex_channel
  //==========================================================================
  template<class T>
  struct vertex_channel
  {
    // comparison
    PFC_INLINE bool operator==(const heap_str &str_) const  {return name==str_;}
    //------------------------------------------------------------------------

    heap_str name;
    array<T> data;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // vertex_channel_disco
  //==========================================================================
  template<class T>
  struct vertex_channel_disco
  {
    // nested types
    struct channel_data
    {
      unsigned poly_index;
      unsigned next;
      T data;
    };
    //------------------------------------------------------------------------

    // comparison
    PFC_INLINE bool operator==(const heap_str &str_) const  {return name==str_;}
    //------------------------------------------------------------------------

    heap_str name;
    array<unsigned> point_data_start_idx;
    array<channel_data> chl_data;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // layer
  //==========================================================================
  struct layer
  {
    // construction
    PFC_INLINE layer() :number(0), parent(0), lod(0), is_coll_object(false), pivot(0.0f), max_valence(0) {}
    //------------------------------------------------------------------------

    uint16_t number;
    uint16_t parent;
    uint8_t lod;
    bool is_coll_object;
    vec3f pivot;
    uint16_t max_valence;
    heap_str name;
    array<point> points;
    array<polygon> polygons;
    list<vertex_channel<vec2f> > uv_channels;
    list<vertex_channel<color_rgbaf> > color_channels;
    list<vertex_channel_disco<vec2f> > uv_channels_disco;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // surface
  //==========================================================================
  struct surface
  {
    // construction and comparison
    PFC_INLINE surface() :max_smooth_angle(0.0f), double_sided(false), base_color(1.0f, 1.0f, 1.0f), parent_id(0) {mem_zero(polygon_list, sizeof(polygon_list));}
    PFC_INLINE bool operator==(const heap_str &str_) const  {return name==str_;}
    //------------------------------------------------------------------------

    heap_str name;
    float32_t max_smooth_angle;
    bool double_sided;
    color_rgbaf base_color;
    uint32_t parent_id;
    polygon *polygon_list[max_mesh_lods];
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // material_mask
  //==========================================================================
  struct material_mask
  {
    // operations
    PFC_INLINE bool operator==(unsigned id_) const  {return item_id==id_;}
    //------------------------------------------------------------------------

    heap_str name;
    unsigned item_id;
  };
  //--------------------------------------------------------------------------

  // stream parsing and mesh generation
  unsigned parse_chunk(endian_input_stream&);
  template<class S> unsigned parse_str(str_base<S>&, endian_input_stream&);
  unsigned parse_index(endian_input_stream&, unsigned &chunk_size_);
  void parse_form(endian_input_stream&, unsigned size_);
  void parse_tags(endian_input_stream&, unsigned size_);
  void parse_layer(endian_input_stream&, unsigned size_);
  void parse_points(endian_input_stream&, unsigned size_);
  void parse_polygons(endian_input_stream&, unsigned size_);
  void parse_polygon_tags(endian_input_stream&, unsigned size_);
  void parse_vertex_map(endian_input_stream&, unsigned size_);
  void parse_discontinuous_vertex_map(endian_input_stream&, unsigned size_);
  void parse_surface(endian_input_stream&, unsigned size_);
  void parse_lxo_channel_names(endian_input_stream&, unsigned size_);
  void parse_lxo_item(endian_input_stream&, unsigned size_);
  void parse_lxo_material(endian_input_stream&, unsigned size_, const heap_str &name_);
  void parse_lxo_mask(endian_input_stream&, unsigned size_, unsigned item_id_);
  uint16_t get_channel_name_idx(const char*) const;
  PFC_INLINE const vec2f &get_vertex_uv(const vec2f *uvs_, const vertex_channel_disco<vec2f> *uvs_disco_, unsigned point_idx_, unsigned poly_idx_) const;
  void generate_mesh(mesh&);
  //--------------------------------------------------------------------------

  bool m_is_lxo;
  array<tag> m_tags;
  array<heap_str> m_channel_names;
  deque<layer> m_layers;
  array<index> m_indices;
  array<surface> m_surfaces;
  array<material_mask> m_material_masks;
  unsigned m_num_points_total;
  bool m_current_layer_visible;
};
//----------------------------------------------------------------------------

void mesh_loader_lwo::load(mesh &mesh_, bin_input_stream_base &stream_)
{
  // read data through endian conversion stream
  m_is_lxo=false;
  m_current_layer_visible=true;
  m_surfaces.resize(1);
  m_num_points_total=0;
  endian_input_stream stream(stream_);
  parse_chunk(stream);
  generate_mesh(mesh_);
}
//----------------------------------------------------------------------------

unsigned mesh_loader_lwo::parse_chunk(endian_input_stream &stream_)
{
  // read chunk id & size
  uint32_t id, size;
  stream_>>id>>size;
  auto_stream_seek<endian_input_stream> aseek(stream_, size);

  // switch to proper chunk ID handler
  switch(id)
  {
    case PFC_LWO_CHUNKID('F', 'O', 'R', 'M'): parse_form(stream_, size); break;
    case PFC_LWO_CHUNKID('T', 'A', 'G', 'S'): parse_tags(stream_, size); break;
    case PFC_LWO_CHUNKID('L', 'A', 'Y', 'R'): parse_layer(stream_, size); break;
    case PFC_LWO_CHUNKID('P', 'N', 'T', 'S'): if(m_current_layer_visible) parse_points(stream_, size); break;
    case PFC_LWO_CHUNKID('P', 'O', 'L', 'S'): if(m_current_layer_visible) parse_polygons(stream_, size); break;
    case PFC_LWO_CHUNKID('P', 'T', 'A', 'G'): if(m_current_layer_visible) parse_polygon_tags(stream_, size); break;
    case PFC_LWO_CHUNKID('V', 'M', 'A', 'P'): if(m_current_layer_visible) parse_vertex_map(stream_, size); break;
    case PFC_LWO_CHUNKID('V', 'M', 'A', 'D'): if(m_current_layer_visible) parse_discontinuous_vertex_map(stream_, size); break;
    case PFC_LWO_CHUNKID('S', 'U', 'R', 'F'): if(m_current_layer_visible) parse_surface(stream_, size); break;
    case PFC_LWO_CHUNKID('C', 'H', 'N', 'M'): parse_lxo_channel_names(stream_, size); break;
    case PFC_LWO_CHUNKID('I', 'T', 'E', 'M'): parse_lxo_item(stream_, size); break;
    default: PFC_LWO_WARN(("Ignored LWO chunk \"%c%c%c%c\"", char(id>>24), char(id>>16), char(id>>8), char(id)));
  }
  return size+8;
}
//----

template<class S>
unsigned mesh_loader_lwo::parse_str(str_base<S> &str_, endian_input_stream &stream_)
{
  // read c-string and skip padding byte if parsing odd number of bytes
  char c;
  stream_>>c;
  while(c)
  {
    str_+=c;
    stream_>>c;
  }
  unsigned size=(unsigned)str_.size()+1;
  if(size&1)
  {
    stream_.skip(1);
    ++size;
  }
  return size;
}
//----

unsigned mesh_loader_lwo::parse_index(endian_input_stream &stream_, unsigned &chunk_size_)
{
  // read 16- or 24-bit index from the stream
  uint8_t b[4];
  stream_.read_bytes(b, 2);
  chunk_size_-=2;
  if(b[0]==0xff)
  {
    stream_.read_bytes(b+2, 2);
    chunk_size_-=2;
    return b[1]*65536+b[2]*256+b[3];
  }
  else
    return b[0]*256+b[1];
}
//----

void mesh_loader_lwo::parse_form(endian_input_stream &stream_, unsigned size_)
{
  // validate "LWO2" id and parse chunks in the form
  char id[4];
  stream_.read_bytes(id, 4);
  m_is_lxo=mem_eq(id, "LXOB", 4);
  PFC_CHECK_MSG(m_is_lxo || mem_eq(id, "LWO2", 4), ("Invalid LightWave LWO form\r\n"));
  size_-=4;
  while(size_)
  {
    // parse chunk
    unsigned chunk_size=parse_chunk(stream_);
    PFC_CHECK_MSG(size_>=chunk_size, ("Invalid LWO chunk size\r\n"));
    size_-=chunk_size;
  }
}
//----

void mesh_loader_lwo::parse_tags(endian_input_stream &stream_, unsigned size_)
{
  // parse all LWO tags
  while(size_)
  {
    tag &t=m_tags.push_back();
    t.surface_idx=0;
    size_-=parse_str(t.name, stream_);
  }
}
//----

void mesh_loader_lwo::parse_layer(endian_input_stream &stream_, unsigned size_)
{
  // read layer properties
  uint16_t number, flags;
  stream_>>number>>flags;
  m_current_layer_visible=m_is_lxo?flags&1:true;
  if(!m_current_layer_visible)
  {
    stream_.skip(12);
    heap_str name;
    parse_str(name, stream_);
    PFC_WARN(("Skipping invisible LWO layer \"%s\"\r\n", name.c_str()));
    return;
  }
  layer &l=m_layers.push_back();
  l.number=number;
  stream_>>l.pivot;
  size_-=16+parse_str(l.name, stream_);
  if(size_)
    stream_>>l.parent;
  l.lod=subobject_lod(l.name.c_str());
  l.is_coll_object=is_collision_subobject(l.name.c_str());
}
//----

void mesh_loader_lwo::parse_points(endian_input_stream &stream_, unsigned size_)
{
  // read point coordinates
  PFC_CHECK_MSG(m_layers.size(), ("LWO layer chunk not defined\r\n"));
  layer &l=m_layers.back();
  PFC_CHECK_MSG(!l.points.size(), ("Points already defined for the LWO layer\r\n"));
  unsigned num_points=size_/12;
  l.points.resize(num_points);
  point *points=l.points.data();
  for(unsigned i=0; i<num_points; ++i)
  {
    point &pnt=points[i];
    stream_>>pnt.position;
    pnt.first_polygon_idx=uint32_t(-1);
    pnt.first_polygon_vtx_idx=0;
    pnt.valence=0;
    ++m_num_points_total;
  }
}
//----

void mesh_loader_lwo::parse_polygons(endian_input_stream &stream_, unsigned size_)
{
  // check for parsed data required by polygons
  PFC_CHECK_MSG(m_layers.size(), ("LWO layer chunk not defined\r\n"));
  layer &l=m_layers.back();
  PFC_CHECK_MSG(l.points.size(), ("Points not defined for the LWO layer\r\n"));

  // read polygon type and switch to proper polygon setup
  polygon poly;
  uint32_t type;
  stream_>>type;
  size_-=4;
  switch(type)
  {
    case PFC_LWO_CHUNKID('F', 'A', 'C', 'E'): poly.type=polytype_face; break;
    case PFC_LWO_CHUNKID('P', 'T', 'C', 'H'): poly.type=polytype_ptch; break;
    case PFC_LWO_CHUNKID('B', 'O', 'N', 'E'): poly.type=polytype_bone; break;
    default: PFC_LWO_WARN(("Ignored LWO polygon type \"%c%c%c%c\"", char(type>>24), char(type>>16), char(type>>8), char(type)));
  }

  // process all polygons for the chunk
  point *points=l.points.data();
  unsigned num_polys=(unsigned)l.polygons.size();
  while(size_)
  {
    // read number of polygon vertices
    uint16_t vertflags;
    stream_>>vertflags;
    size_-=2;
    unsigned num_vertices=vertflags&0x3ff;
    if(type==PFC_LWO_CHUNKID('C', 'U', 'R', 'V'))
      num_vertices+=(vertflags&0xff00)>>2;

    // add new polygon and add polygon point indices to the index array
    poly.num_indices=uint16_t(num_vertices);
    poly.index_start=(unsigned)m_indices.size();
    l.polygons.push_back(poly);
    for(unsigned i=0; i<num_vertices; ++i)
    {
      // add polygon to the polygon list for the point
      unsigned point_idx=parse_index(stream_, size_);
      point &pnt=points[point_idx];
      index idx={point_idx, 0, pnt.first_polygon_idx, pnt.first_polygon_vtx_idx};
      pnt.first_polygon_idx=num_polys;
      pnt.first_polygon_vtx_idx=uint16_t(i);
      ++pnt.valence;
      l.max_valence=max(l.max_valence, pnt.valence);
      m_indices.push_back(idx);
    }
    ++num_polys;
  }
}
//----

void mesh_loader_lwo::parse_polygon_tags(endian_input_stream &stream_, unsigned size_)
{
  // check for parsed data required by polygons
  PFC_CHECK_MSG(m_layers.size(), ("LWO layer chunk not defined\r\n"));
  layer &l=m_layers.back();
  PFC_CHECK_MSG(l.polygons.size(), ("Polygons not defined for the LWO layer\r\n"));

  // read tag type and switch to proper tag parsing
  uint32_t type;
  stream_>>type;
  size_-=4;
  while(size_)
  {
    // read polygon index & tag
    unsigned poly_idx=parse_index(stream_, size_);
    uint16_t tag_idx;
    stream_>>tag_idx;
    size_-=2;
    polygon &poly=l.polygons[poly_idx];

    // assign tag to polygon
    switch(type)
    {
      case PFC_LWO_CHUNKID('S', 'U', 'R', 'F'): poly.surface_tag_index=tag_idx; break;
      case PFC_LWO_CHUNKID('P', 'A', 'R', 'T'): poly.part_index=tag_idx; break;
      case PFC_LWO_CHUNKID('S', 'M', 'G', 'P'): poly.smoothing_group=tag_idx; break;
      case PFC_LWO_CHUNKID('M', 'A', 'T', 'R'): poly.surface_tag_index=tag_idx; break;
      default: PFC_LWO_WARN(("Ignored LWO polygon tag type \"%c%c%c%c\"", char(type>>24), char(type>>16), char(type>>8), char(type))); return;
    }
  }
}
//----

void mesh_loader_lwo::parse_vertex_map(endian_input_stream &stream_, unsigned size_)
{
  // check for parsed data required by polygons
  PFC_CHECK_MSG(m_layers.size(), ("LWO layer chunk not defined\r\n"));
  layer &l=m_layers.back();
  PFC_CHECK_MSG(l.points.size(), ("Points not defined for the LWO layer\r\n"));

  // read map type and switch to proper map parsing
  uint32_t type;
  uint16_t dimension;
  stream_>>type>>dimension;
  heap_str name;
  size_-=6+parse_str(name, stream_);
  switch(type)
  {
    // "TXUV" vertex map
    case PFC_LWO_CHUNKID('T', 'X', 'U', 'V'):
    {
      // add a texture coordinates channel for vertices
      PFC_CHECK_MSG(dimension==2, ("Invalid vertex texture coordinate dimension (%i)\r\n", dimension));
      PFC_CHECK_MSG(!is_valid(linear_search(l.uv_channels.begin(), l.uv_channels.end(), name)), ("UV channel \"%s\" already defined for the layer\r\n", name.c_str()));
      vertex_channel<vec2f> &uv_channel=l.uv_channels.push_back();
      array<vec2f> &uvs=uv_channel.data;
      uv_channel.name=name;
      uvs.resize(l.points.size());
      mem_zero(uvs.data(), uvs.size()*sizeof(uvs[0]));

      // parse vertex coordinates from the stream
      while(size_)
      {
        unsigned vertex_index=parse_index(stream_, size_);
        stream_>>uvs[vertex_index];
        size_-=8;
      }
    } break;

    // "RGB" or "RGBA" vertex map
    case PFC_LWO_CHUNKID('R', 'G', 'B', ' '):
    case PFC_LWO_CHUNKID('R', 'G', 'B', 'A'):
    {
      // add a color channel for vertices
      PFC_CHECK_MSG(dimension==3 || dimension==4, ("Invalid color channel coordinate dimension (%i)\r\n", dimension));
      PFC_CHECK_MSG(!is_valid(linear_search(l.color_channels.begin(), l.color_channels.end(), name)),
                    ("Color channel \"%s\" already defined for the layer\r\n", name.c_str()));
      vertex_channel<color_rgbaf> &color_channel=l.color_channels.push_back();
      array<color_rgbaf> &colors=color_channel.data;
      color_channel.name=name;
      colors.resize(l.points.size());
      mem_zero(colors.data(), colors.size()*sizeof(colors[0]));

      // parse colors from the stream
      if(dimension==3)
      {
        while(size_)
        {
          color_rgbaf &col=colors[parse_index(stream_, size_)];
          stream_>>col.r>>col.g>>col.b;
          size_-=12;
        }
      }
      else
      {
        while(size_)
        {
          stream_>>colors[parse_index(stream_, size_)];
          size_-=16;
        }
      }
    } break;
  }
}
//----

void mesh_loader_lwo::parse_discontinuous_vertex_map(endian_input_stream &stream_, unsigned size_)
{
  // check for parsed data required by polygons
  PFC_CHECK_MSG(m_layers.size(), ("LWO layer chunk not defined\r\n"));
  layer &l=m_layers.back();
  PFC_CHECK_MSG(l.polygons.size(), ("Polygons not defined for the LWO layer\r\n"));

  // read map type and switch to proper map parsing
  uint32_t type;
  uint16_t dimension;
  stream_>>type>>dimension;
  heap_str name;
  size_-=6+parse_str(name, stream_);
  switch(type)
  {
    // "TXUV" vertex map
    case PFC_LWO_CHUNKID('T', 'X', 'U', 'V'):
    {
      // add a discontinuous texture coordinate channel for vertices
      PFC_CHECK_MSG(dimension==2, ("Invalid discontinuous vertex texture coordinate dimension (%i)\r\n", dimension));
      PFC_CHECK_MSG(!is_valid(linear_search(l.uv_channels_disco.begin(), l.uv_channels_disco.end(), name)),
                    ("Discontinuous texture coordinate channel \"%s\" already defined for the layer\r\n", name.c_str()));
      vertex_channel_disco<vec2f> &uv_channel=l.uv_channels_disco.push_back();
      array<vertex_channel_disco<vec2f>::channel_data> &uvs=uv_channel.chl_data;
      array<unsigned> &vertex_lists=uv_channel.point_data_start_idx;
      uv_channel.name=name;
      uvs.resize(1);
      vertex_lists.resize(l.points.size());
      mem_zero(vertex_lists.data(), vertex_lists.size()*sizeof(vertex_lists[0]));

      // parse vertex coordinates from the stream
      unsigned uv_index=(unsigned)uvs.size();
      while(size_)
      {
        vertex_channel_disco<vec2f>::channel_data &chl_data=uvs.push_back();
        unsigned vertex_index=parse_index(stream_, size_);
        chl_data.poly_index=parse_index(stream_, size_);
        stream_>>chl_data.data;
        chl_data.next=vertex_lists[vertex_index];
        vertex_lists[vertex_index]=uv_index++;
        size_-=8;
      }
    } break;
  }
}
//----

void mesh_loader_lwo::parse_surface(endian_input_stream &stream_, unsigned size_)
{
  // add new surface
  surface &surf=m_surfaces.push_back();
  heap_str name, source_name;
  size_-=parse_str(surf.name, stream_);
  size_-=parse_str(source_name, stream_);
  if(surface *source_surf=linear_search(m_surfaces.data()+1, m_surfaces.last(), source_name))
    surf=*source_surf;

  // parse all sub-chunks
  while(size_)
  {
    // read sub-chunk properties and switch to proper parsing routine
    uint32_t id;
    uint16_t size;
    stream_>>id>>size;
    size_-=6+size;
    switch(id)
    {
      case PFC_LWO_CHUNKID('S', 'M', 'A', 'N'): stream_>>surf.max_smooth_angle; break;
      case PFC_LWO_CHUNKID('S', 'I', 'D', 'E'): {uint16_t sidedness; stream_>>sidedness; surf.double_sided=sidedness==3;} break;
      case PFC_LWO_CHUNKID('C', 'O', 'L', 'R'): {color_rgbaf &col=surf.base_color; stream_>>col.r>>col.g>>col.b; unsigned dummy_size; parse_index(stream_, dummy_size);} break;
      // unknown surface sub-chunk
      default:
      {
        PFC_LWO_WARN(("Ignored LWO surface sub-chunk \"%c%c%c%c\"", char(id>>24), char(id>>16), char(id>>8), char(id)));
        stream_.skip(size);
      }
    }
  }
}
//----

void mesh_loader_lwo::parse_lxo_channel_names(endian_input_stream &stream_, unsigned size_)
{
  // read channel names
  uint32_t num_names;
  stream_>>num_names;
  m_channel_names.resize(num_names);
  for(unsigned i=0; i<num_names; ++i)
    parse_str(m_channel_names[i], stream_);
}
//----

void mesh_loader_lwo::parse_lxo_item(endian_input_stream &stream_, unsigned size_)
{
  // parse item properties and sub-chunks
  heap_str item_type, item_name;
  uint32_t item_id;
  size_-=parse_str(item_type, stream_);
  size_-=parse_str(item_name, stream_);
  stream_>>item_id;
  size_-=4;
  auto_stream_seek<endian_input_stream> aseek(stream_, size_);
  if(item_type=="advancedMaterial")
    parse_lxo_material(stream_, size_, item_name);
  else if(item_type=="mask")
    parse_lxo_mask(stream_, size_, item_id);
  else
    PFC_LWO_WARN(("Ignoring LXO item type \"%s\"", item_type.c_str()));
}
//----

void mesh_loader_lwo::parse_lxo_material(endian_input_stream &stream_, unsigned size_, const heap_str &name_)
{
  // add new surface
  surface &surf=name_=="Base Material"?m_surfaces[0]:m_surfaces.push_back();
  surf.name=name_;

  // get relevant material chunk name id's
  uint16_t nameidx_double_sided=get_channel_name_idx("dblSided");
  uint16_t nameidx_smoothing_angle=get_channel_name_idx("smAngle");

  // parse material sub-chunks
  while(size_)
  {
    // read chunk id & size
    uint32_t id;
    uint16_t size;
    stream_>>id>>size;
    size_-=6+size;
    auto_stream_seek<endian_input_stream> aseek(stream_, size);
    switch(id)
    {
      case PFC_LWO_CHUNKID('L', 'I', 'N', 'K'):
      {
        // read link
        heap_str name;
        parse_str(name, stream_);
        stream_>>surf.parent_id;
      } break;

      case PFC_LWO_CHUNKID('C', 'H', 'A', 'N'):
      {
        // switch to proper type handling
        uint16_t nameidx, data_type;
        stream_>>nameidx>>data_type;
        if(nameidx==nameidx_double_sided)
        {
          // read double-sided flag
          PFC_CHECK_MSG(data_type==1, ("Material double sided flag not stored in int format\r\n"));
          int val;
          stream_>>val;
          surf.double_sided=val!=0;
        }
        else if(nameidx==nameidx_smoothing_angle)
        {
          // read smoothing angle
          PFC_CHECK_MSG(data_type==2, ("Material smoothing angle not stored in float format\r\n"));
          stream_>>surf.max_smooth_angle;
        }
      } break;

      case PFC_LWO_CHUNKID('C', 'H', 'N', 'V'):
      {
        // switch to proper type handling
        heap_str name;
        uint16_t data_type, num_vcomps;
        parse_str(name, stream_);
        stream_>>data_type>>num_vcomps;
        if(name=="diffCol")
        {
          // read diffuse color
          PFC_CHECK_MSG(data_type==2 && num_vcomps==3, ("Material diffuse color not stored in 3 component float format\r\n"));
          stream_.skip(2);
          stream_>>surf.base_color.r;
          stream_.skip(2);
          stream_>>surf.base_color.g;
          stream_.skip(2);
          stream_>>surf.base_color.b;
        }
      } break;

      default: PFC_LWO_WARN(("Ignoring LXO material chunk \"%c%c%c%c\"\r\n", char(id>>24), char(id>>16), char(id>>8), char(id)));
    }
  }
}
//----

void mesh_loader_lwo::parse_lxo_mask(endian_input_stream &stream_, unsigned size_, unsigned item_id_)
{
  // parse material sub-chunks
  heap_str ptag, mask_type;
  while(size_)
  {
    // read chunk id & size
    uint32_t id;
    uint16_t size;
    stream_>>id>>size;
    size_-=6+size;
    auto_stream_seek<endian_input_stream> aseek(stream_, size);
    switch(id)
    {
      case PFC_LWO_CHUNKID('C', 'H', 'N', 'S'):
      {
        heap_str str_name;
        parse_str(str_name, stream_);
        if(str_name=="ptag")
          parse_str(ptag, stream_);
        else if(str_name=="ptyp")
          parse_str(mask_type, stream_);
      } break;

      default: PFC_LWO_WARN(("Ignoring LXO mask chunk \"%c%c%c%c\"", char(id>>24), char(id>>16), char(id>>8), char(id)));
    }
  }

  // add material mask
  if(ptag.size() && mask_type=="Material")
  {
    material_mask &m=m_material_masks.push_back();
    m.name.swap(ptag);
    m.item_id=item_id_;
  }
}
//----

uint16_t mesh_loader_lwo::get_channel_name_idx(const char *name_) const
{
  const heap_str *name=linear_search(m_channel_names.begin(), m_channel_names.end(), name_);
  if(name)
    return uint16_t(name-m_channel_names.begin());
  return 0;
}
//----

const vec2f &mesh_loader_lwo::get_vertex_uv(const vec2f *uvs_, const vertex_channel_disco<vec2f> *uvs_disco_, unsigned point_idx_, unsigned poly_idx_) const
{
  if(uvs_disco_)
  {
    // search for uv coordinate from the discontinuous uv list for the point
    unsigned uv_idx=uvs_disco_->point_data_start_idx[point_idx_];
    const vertex_channel_disco<vec2f>::channel_data *chl_data=uvs_disco_->chl_data.data();
    while(uv_idx)
    {
      if(chl_data[uv_idx].poly_index==poly_idx_)
        return chl_data[uv_idx].data;
      uv_idx=chl_data[uv_idx].next;
    }
  }

  // return point uv coordinate (or [0, 0] if no uvs)
  return uvs_?uvs_[point_idx_]:vec2f::s_zero;
}
//----

void mesh_loader_lwo::generate_mesh(mesh &mesh_)
{
  // vertex output buffers
  array<vec3f> mesh_positions;
  array<vec2f> mesh_uvs;
  array<vec3f> mesh_tangents;
  array<vec3f> mesh_binormals;
  array<vec3f> mesh_normals;
  mesh_positions.reserve(m_num_points_total);
  mesh_uvs.reserve(m_num_points_total);
  mesh_tangents.reserve(m_num_points_total);
  mesh_binormals.reserve(m_num_points_total);
  mesh_normals.reserve(m_num_points_total);

  // setup mesh transforms
  mat33f mesh_tform( 1.0f,  0.0f, 0.0f,
                     0.0f,  0.0f, 1.0f,
                     0.0f, -1.0f, 0.0f);

  // init surfaces
  surface *const surfaces=m_surfaces.data();
  unsigned num_surfaces=(unsigned)m_surfaces.size();
  for(unsigned i=0; i<num_surfaces; ++i)
  {
    // check for material mask for the surface
    surface &surf=surfaces[i];
    const material_mask *mask=linear_search(m_material_masks.begin(), m_material_masks.end(), surf.parent_id);
    if(mask)
      surf.name=mask->name;
  }

  // initialize tag surface indices
  unsigned num_tags=(unsigned)m_tags.size();
  tag *tags=m_tags.data();
  for(unsigned i=0; i<num_tags; ++i)
  {
    surface *surf=linear_search(surfaces, m_surfaces.end(), tags[i].name);
    if(surf)
      tags[i].surface_idx=unsigned(surf-surfaces);
  }

  // process all layers
  array<smoother> point_face_smoothers_sp, point_vertex_smoothers_sp;
  unsigned num_points_total=0;
  unsigned num_vertices_total=0;
  unsigned num_layers=(unsigned)m_layers.size();
  unsigned num_collision_objects=0;
  index *indices=m_indices.data();
  for(unsigned li=0; li<num_layers; ++li)
  {
    // skip collision objects
    layer &l=m_layers[li];
    if(l.is_coll_object)
    {
      ++num_collision_objects;
      continue;
    }

    // get uv channel and discontinuous uv channel
    const vec2f *uvs=l.uv_channels.size()?l.uv_channels.front().data.data():0;
    const vertex_channel_disco<vec2f> *uvs_disco=l.uv_channels_disco.size()?&l.uv_channels_disco.front():0;
    if(uvs)
    {
      list<vertex_channel_disco<vec2f> >::const_iterator uvs_disco_it=linear_search(l.uv_channels_disco.begin(), l.uv_channels_disco.end(), l.uv_channels.front().name);
      if(is_valid(uvs_disco_it))
        uvs_disco=&*uvs_disco_it;
    }

    // setup mesh smoothing scratch pads
    point_face_smoothers_sp.resize(l.max_valence);
    point_vertex_smoothers_sp.resize(l.max_valence);
    smoother *point_face_smoothers=point_face_smoothers_sp.data();
    smoother *point_vertex_smoothers=point_vertex_smoothers_sp.data();

    // process all points in the layer
    const polygon *polys=l.polygons.data();
    const point *points=l.points.data();
    unsigned num_points=(unsigned)l.points.size();
    for(unsigned point_idx=0; point_idx<num_points; ++point_idx)
    {
      // check for an isolated point
      const point &pnt=points[point_idx];
      if(!pnt.valence)
        continue;
      ++num_points_total;

      // process all polygons attached to the point
      unsigned num_faces=0;
      unsigned poly_idx=pnt.first_polygon_idx;
      unsigned poly_vtx_idx=pnt.first_polygon_vtx_idx;
      do 
      {
        // check for "face" polygon
        const polygon &poly=polys[poly_idx];
        if(poly.type==polytype_face)
        {
          // calculate face normal (length twice the triangular area of the face)
          smoother &smtr=point_face_smoothers[num_faces];
          mat33f &tbn=smtr.tbn;
          smtr.idx=indices+poly.index_start+poly_vtx_idx;
          unsigned pidx0=smtr.idx->point_idx;
          unsigned pidx1=indices[poly.index_start+(poly_vtx_idx+1<poly.num_indices?poly_vtx_idx+1:0)].point_idx;
          unsigned pidx2=indices[poly.index_start+(poly_vtx_idx>0?poly_vtx_idx:poly.num_indices)-1].point_idx;
          const vec3f &e0=points[pidx1].position-points[pidx0].position;
          const vec3f &e1=points[pidx2].position-points[pidx0].position;
          tbn.z=cross(e0, e1);

          // calculate tangent & binormal and weight scaled TBN with face opening angle
          const vec2f &t0=get_vertex_uv(uvs, uvs_disco, pidx0, poly_idx);
          const vec2f &t1=get_vertex_uv(uvs, uvs_disco, pidx1, poly_idx);
          const vec2f &t2=get_vertex_uv(uvs, uvs_disco, pidx2, poly_idx);
          const vec2f &te0=t1-t0;
          const vec2f &te1=t2-t0;
          tbn.x=e1*te0.y-e0*te1.y;
          tbn.y=e1*te0.x-e0*te1.x;
          tbn*=acos(ssat(dot(unit_z(e0), unit_z(e1))));

          // setup smoother properties and proceed to the next face
          smtr.uv=t0;
          smtr.smoothing_group=poly.smoothing_group;
          const surface &surf=surfaces[tags[poly.surface_tag_index].surface_idx];
          smtr.max_smooth_angle=surf.max_smooth_angle;
          smtr.double_sided=surf.double_sided;
          ++num_faces;
        }

        // proceed to the next polygon
        const index &idx=indices[poly.index_start+poly_vtx_idx];
        poly_idx=idx.next_polygon_idx;
        poly_vtx_idx=idx.next_polygon_vtx_idx;
      } while(poly_idx!=uint32_t(-1));

      // generate vertices for the point
      unsigned num_point_vertices=0;
      for(unsigned fi=0; fi<num_faces; ++fi)
      {
        // generate smoothed tangent space for face attached to the point
        const smoother &pvtx0=point_face_smoothers[fi];
        smoother pvtx=pvtx0;
        float cos_smooth_angle=cos(pvtx0.max_smooth_angle);
        for(unsigned i=0; i<num_faces; ++i)
        {
          const smoother &pvtx1=point_face_smoothers[i];
          if(   fi!=i
             && pvtx0.smoothing_group==pvtx1.smoothing_group
             && dot(pvtx0.tbn.z, pvtx1.tbn.z)>cos_smooth_angle*norm(pvtx0.tbn.z)*norm(pvtx1.tbn.z))
            pvtx.tbn+=pvtx1.tbn; /*todo: consider TBN mirroring*/
        }

        // normalize tangent space
        pvtx.tbn.x=unit_z(pvtx.tbn.x);
        pvtx.tbn.y=unit_z(pvtx.tbn.y);
        pvtx.tbn.z=unit_z(pvtx.tbn.z);

        // search for matching vertex
        if(smoother *matching_vtx=linear_search(point_vertex_smoothers, point_vertex_smoothers+num_point_vertices, pvtx))
          pvtx0.idx->vertex_idx=matching_vtx->idx->vertex_idx;
        else
        {
          // add new vertex
          pvtx.idx->vertex_idx=num_vertices_total++;
          point_vertex_smoothers[num_point_vertices++]=pvtx;
          mesh_positions.push_back()=points[pvtx.idx->point_idx].position*mesh_tform;
          vec2f &uv=mesh_uvs.push_back();
          uv.x=pvtx.uv.x;
          uv.y=1.0f-pvtx.uv.y;
          mesh_tangents.push_back()=pvtx.tbn.x*mesh_tform;
          mesh_binormals.push_back()=pvtx.tbn.y*mesh_tform;
          mesh_normals.push_back()=pvtx.tbn.z*mesh_tform;

          // check for double sided vertex
          if(pvtx.double_sided)
          {
            num_vertices_total++;
            mesh_positions.push_back()=points[pvtx.idx->point_idx].position*mesh_tform;
            vec2f &tex_uv=mesh_uvs.push_back();
            tex_uv.x=pvtx.uv.x;
            tex_uv.y=1.0f-pvtx.uv.y;
            mesh_tangents.push_back()=pvtx.tbn.x*mesh_tform;
            mesh_binormals.push_back()=pvtx.tbn.y*mesh_tform;
            mesh_normals.push_back()=-pvtx.tbn.z*mesh_tform;
          }
        }
      }
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
  vb.add_channel(vtxchannel_uv, mesh_uvs.steal_data().steal_data(), num_vertices_total);
  vb.add_channel(vtxchannel_tangent, mesh_tangents.steal_data().steal_data(), num_vertices_total);
  vb.add_channel(vtxchannel_binormal, mesh_binormals.steal_data().steal_data(), num_vertices_total);
  vb.add_channel(vtxchannel_normal, mesh_normals.steal_data().steal_data(), num_vertices_total);
  array<mesh_collision_object> mesh_coll_objects;
  mesh_coll_objects.reserve(num_collision_objects);

  // assign polygons of all layers to surfaces
  unsigned num_segments=0;
  for(unsigned li=0; li<num_layers; ++li)
  {
    // check for collision object
    layer &l=m_layers[li];
    unsigned num_polygons=(unsigned)l.polygons.size();
    polygon *polygons=l.polygons.data();
    if(l.is_coll_object)
    {
      // setup collision object points
      unsigned num_points=(unsigned)l.points.size();
      const point *points=l.points.data();
      mesh_collision_object &coll_obj=mesh_coll_objects.push_back();
      coll_obj.points.resize(num_points);
      vec3f *coll_points=coll_obj.points.data();
      for(unsigned i=0; i<num_points; ++i)
        coll_points[i]=points[i].position*mesh_tform;

      // setup collision object faces
      for(unsigned pi=0; pi<num_polygons; ++pi)
      {
        polygon &poly=polygons[pi];
        if(poly.type==polytype_face)
        {
          unsigned num_indices=poly.num_indices;
          if(num_indices>=3)
          {
            // create triangle fan out of face polygon /*todo: fix for concave polygons*/
            {
              unsigned pidx0=indices[poly.index_start+0].point_idx;
              unsigned pidx1=indices[poly.index_start+1].point_idx;
              unsigned pidx2=indices[poly.index_start+2].point_idx;
              coll_obj.indices.push_back(pidx0);
              coll_obj.indices.push_back(pidx1);
              coll_obj.indices.push_back(pidx2);
              for(unsigned i=3; i<num_indices; ++i)
              {
                pidx1=pidx2;
                pidx2=indices[poly.index_start+i].point_idx;
                coll_obj.indices.push_back(pidx0);
                coll_obj.indices.push_back(pidx1);
                coll_obj.indices.push_back(pidx2);
              }
            }
          }
        }
      }
      continue;
    }

    // process polygons for the layer
    for(unsigned pi=0; pi<num_polygons; ++pi)
    {
      // add "face" polygon to the surface polygon list
      polygon &poly=polygons[pi];
      if(poly.type==polytype_face)
      {
        unsigned surface_idx=tags[poly.surface_tag_index].surface_idx;
        PFC_ASSERT_PEDANTIC(surface_idx<num_surfaces);
        surface &surf=surfaces[surface_idx];
        if(!surf.polygon_list[l.lod])
          ++num_segments;
        poly.next=surf.polygon_list[l.lod];
        surf.polygon_list[l.lod]=polygons+pi;
      }
    }
  }

  // create mesh segments and primitives from surfaces
  array<mesh_segment> mesh_segments;
  mesh_segments.resize(num_segments);
  array<uint32_t> mesh_indices;
  unsigned num_triangles_total=0;
  unsigned segment_idx=0;
  mesh_segment *msegments=mesh_segments.data();
  for(unsigned si=0; si<num_surfaces; ++si)
    for(unsigned lod=0; lod<max_mesh_lods; ++lod)
      if(surfaces[si].polygon_list[lod])
      {
        // add mesh segment
        PFC_ASSERT(segment_idx<num_segments);
        mesh_segment &seg=msegments[segment_idx++];
        seg.material_name=surfaces[si].name;
        seg.vertex_buffer=0;
        seg.primitive_type=meshprim_trilist;
        seg.prim_start_index=num_triangles_total*3;
        seg.lod=uint8_t(lod);

        // triangulate polygons
        bool double_sided=surfaces[si].double_sided;
        unsigned num_triangles=0;
        const polygon *poly=surfaces[si].polygon_list[lod];
        while(poly)
        {
          switch(poly->type)
          {
            // triangulate face polygon
            case polytype_face:
            {
              unsigned num_indices=poly->num_indices;
              if(num_indices>=3)
              {
                // create triangle fan out of face polygon /*todo: fix for concave polygons*/
                {
                  unsigned vidx0=indices[poly->index_start+0].vertex_idx;
                  unsigned vidx1=indices[poly->index_start+1].vertex_idx;
                  unsigned vidx2=indices[poly->index_start+2].vertex_idx;
                  mesh_indices.push_back(vidx0);
                  mesh_indices.push_back(vidx1);
                  mesh_indices.push_back(vidx2);
                  for(unsigned i=3; i<num_indices; ++i)
                  {
                    vidx1=vidx2;
                    vidx2=indices[poly->index_start+i].vertex_idx;
                    mesh_indices.push_back(vidx0);
                    mesh_indices.push_back(vidx1);
                    mesh_indices.push_back(vidx2);
                  }
                  num_triangles+=num_indices-2;
                }

                if(double_sided)
                {
                  // create triangle fan out of face polygon /*todo: fix for concave polygons*/
                  unsigned vidx0=indices[poly->index_start+0].vertex_idx+1;
                  unsigned vidx1=indices[poly->index_start+2].vertex_idx+1;
                  unsigned vidx2=indices[poly->index_start+1].vertex_idx+1;
                  mesh_indices.push_back(vidx0);
                  mesh_indices.push_back(vidx1);
                  mesh_indices.push_back(vidx2);
                  for(unsigned i=3; i<num_indices; ++i)
                  {
                    vidx2=vidx1;
                    vidx1=indices[poly->index_start+i].vertex_idx+1;
                    mesh_indices.push_back(vidx0);
                    mesh_indices.push_back(vidx1);
                    mesh_indices.push_back(vidx2);
                  }
                  num_triangles+=num_indices-2;
                }
              }
            } break;
          }

          // proceed to the next polygon
          poly=poly->next;
        }

        // finish segment setup
        num_triangles_total+=num_triangles;
        seg.num_primitives=num_triangles;
      }

  // finish mesh generation and swap mesh content
  mesh_indices.trim();
  mesh_.swap_indices(mesh_indices);
  mesh_.swap_segments(mesh_segments);
  mesh_.swap_collision_objects(mesh_coll_objects);
}
//----------------------------------------------------------------------------
#undef PFC_LWO_CHUNKID


//============================================================================
// load_mesh_lwo
//============================================================================
namespace pfc
{
  bool load_mesh_lwo(mesh &m_, bin_input_stream_base &s_)
  {
    // check for LWO2 file format
    char id[8];
    s_.read_bytes(id, 4);
    s_.skip(4);
    s_.read_bytes(id+4, 4);
    s_.rewind(12);
    if(!mem_eq(id, "FORMLWO2", 8) && !mem_eq(id, "FORMLXOB", 8))
      return false;

    // load the mesh
    mesh_loader_lwo loader;
    loader.load(m_, s_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_LWO
namespace pfc
{
  bool load_mesh_lwo(mesh &m_, bin_input_stream_base &s_)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_LWO
