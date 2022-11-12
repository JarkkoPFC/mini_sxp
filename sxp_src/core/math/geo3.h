//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_GEO3_H
#define PFC_CORE_MATH_GEO3_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "prim3/prim3.h"
#include "math_adv.h"
#include "sxp_src/core/containers.h"
namespace pfc
{

// new
// geometry properties
template<typename T> mat33<T> covariance_matrix(const vec3<T> *points_, usize_t num_points_);
template<typename T> mat33<T> covariance_matrix(const vec3<T> *points_, const uint32_t *tri_indices_, usize_t num_triangles_, bool is_tri_strip_=false);
// extended primitives
template<typename T> struct capcyl3;
template<typename T> struct oodop3_14;
template<typename T> struct seed_oobox3;
typedef capcyl3<float> capcyl3f;
typedef capcyl3<double> capcyl3d;
typedef capcyl3<simd_float4> simd_capcyl3f;
typedef oodop3_14<float> oodop3f_14;
typedef oodop3_14<double> oodop3d_14;
typedef oodop3_14<simd_float4> simd_oodop3f_14;
typedef seed_oobox3<float> seed_oobox3f;
typedef seed_oobox3<double> seed_oobox3d;
// bounding volume calculations
enum e_discrete_axes3 {discrete_axes3_3, discrete_axes3_7, discrete_axes3_13, discrete_axes3_49};
template<typename T> struct quickhull3_point;
template<typename T> void quickhull3(quickhull3_point<T> *points_, usize_t num_points_, array<vec3<T> > &hull_points_, array<uint32_t> *tri_indices_=0);
template<typename T> aabox3<T> bounding_aabox3(const vec3<T> *points_, usize_t num_points_);
template<typename T> seed_oobox3<T> seed_oobox3_discrete(const vec3<T> *points_, usize_t num_points_, e_discrete_axes3=discrete_axes3_49, const uint32_t *point_indices_=0);
template<typename T> seed_oobox3<T> seed_oobox3_cov(const vec3<T> *points_, usize_t num_points_, const mat33<T> &cov_matrix_, const uint32_t *point_indices_=0);
template<typename T> oobox3<T> optimize_oobox3(const vec3<T> *convex_points_, usize_t num_points_, const uint32_t *convex_tris_, usize_t num_tris_, const oobox3<T>&);
template<typename T> sphere3<T> bounding_sphere3(const vec3<T>&, const vec3<T>&);
template<typename T> sphere3<T> bounding_sphere3(const vec3<T>&, const vec3<T>&, const vec3<T>&);
template<typename T> sphere3<T> bounding_sphere3(const vec3<T>&, const vec3<T>&, const vec3<T>&, const vec3<T>&);
template<typename T> sphere3<T> bounding_sphere3_exp(const vec3<T> *points_, usize_t num_points_, const seed_oobox3<T>&, bool use_oobox_=false, const uint32_t *point_indices_=0);
template<typename T> sphere3<T> bounding_sphere3_maxexp(vec3<T> *points_, usize_t num_points_, const seed_oobox3<T>&, bool use_oobox_=false);
template<typename T> capcyl3<T> bounding_capcyl3_exp(const vec3<T> *points_, usize_t num_points_, const seed_oobox3<T>&, bool use_oobox_=false);
template<typename T> capcyl3<T> bounding_capcyl3_maxexp(vec3<T> *points_, usize_t num_points_, const seed_oobox3<T>&, bool use_oobox_=false);
template<typename T> oodop3_14<T> bounding_oodop3_14(const vec3<T> *points_, usize_t num_points_, const oobox3<T>&);
template<typename T> struct bounding_volume_set;
// topology
class triangle_mesh_topology;
//----------------------------------------------------------------------------


//============================================================================
// seed_oobox3
//============================================================================
template<typename T>
struct seed_oobox3
{
  oobox3<T> oobox;
  vec3<T> max_ext[2]; // extremal points for maximum axis
};
//----------------------------------------------------------------------------


//============================================================================
// capcyl3
//============================================================================
template<typename T>
struct capcyl3
{ PFC_MONO(capcyl3)  {PFC_MVAR3(capsule, cylinder_hlen, cylinder_posd);}
  // construction
  typedef typename math<T>::scalar_t scalar_t;
  PFC_INLINE capcyl3();
  PFC_INLINE capcyl3(const capsule3<T>&, scalar_t cylinder_hlen_, scalar_t cylinder_posd_);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE cylinder3<T> cylinder() const;
  //--------------------------------------------------------------------------

  static const capcyl3<T> s_zero;
  capsule3<T> capsule;
  scalar_t cylinder_hlen, cylinder_posd;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, capcyl3<T>, is_type_pod, is_type_pod<capsule3<T> >::res && is_type_pod<math<T>::scalar_t>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, capcyl3<T>, is_type_pod_stream, is_type_pod_stream<capsule3<T> >::res && is_type_pod_stream<math<T>::scalar_t>::res);
//----------------------------------------------------------------------------


//============================================================================
// oodop3_14
//============================================================================
template<typename T>
struct oodop3_14
{ PFC_MONO(oodop3_14)  {PFC_MVAR3(oobox, diag_axes_min, diag_axes_max);}
  // construction
  typedef typename math<T>::scalar_t scalar_t;
  PFC_INLINE oodop3_14();
  PFC_INLINE oodop3_14(const oobox3<T> &oobox_, const vec4<T> &diag_axes_min_, const vec4<T> &diag_axes_max_);
  //--------------------------------------------------------------------------

  static const oodop3_14<T> s_zero;
  oobox3<T> oobox;
  vec4<T> diag_axes_min, diag_axes_max;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, oodop3_14<T>, is_type_pod, is_type_pod<oobox3<T> >::res && is_type_pod<vec4<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, oodop3_14<T>, is_type_pod_stream, is_type_pod_stream<oobox3<T> >::res && is_type_pod_stream<vec4<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// quickhull3_point
//============================================================================
template<typename T>
struct quickhull3_point
{
  vec3<T> pos;
  uint32_t next_pnt;
};
//----------------------------------------------------------------------------


//============================================================================
// bounding_volume_set
//============================================================================
template<typename T>
struct bounding_volume_set
{ PFC_MONO(bounding_volume_set) {PFC_MVAR3(sphere, capcyl, oobox);}
  // construction
  typedef typename math<T>::scalar_t scalar_t;
  bounding_volume_set();
  bounding_volume_set(const vec3<T> *points_, usize_t num_points_);
  void init(const vec3<T> *points_, usize_t num_points_);
  void scale(scalar_t);
  //--------------------------------------------------------------------------

  sphere3<T> sphere;
  capcyl3<T> capcyl;
  oobox3<T> oobox;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, bounding_volume_set<T>, is_type_pod, is_type_pod<sphere3<T> >::res && is_type_pod<capcyl3<T> >::res && is_type_pod<oobox3<T> >::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, bounding_volume_set<T>, is_type_pod_stream, is_type_pod_stream<sphere3<T> >::res && is_type_pod_stream<capcyl3<T> >::res && is_type_pod_stream<oobox3<T> >::res);
//----------------------------------------------------------------------------


//============================================================================
// triangle_mesh_topology
//============================================================================
class triangle_mesh_topology
{
public:
  // construction
  triangle_mesh_topology();
  triangle_mesh_topology(const uint32_t *indices_, usize_t num_verts_, usize_t num_tris_, bool is_tri_strip_=false);
  void init(const uint32_t *indices_, usize_t num_verts_, usize_t num_tris_, bool is_tri_strip_=false);
  ~triangle_mesh_topology();
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE usize_t num_vertices() const;
  PFC_INLINE usize_t num_edges() const;
  PFC_INLINE usize_t num_triangles() const;
  PFC_INLINE usize_t num_clusters() const;
  PFC_INLINE usize_t num_cluster_tris(uint32_t cluster_idx_) const;
  //--------------------------------------------------------------------------

  // cluster construction
  PFC_INLINE uint32_t add_cluster();
  PFC_INLINE void add_cluster_tri(uint32_t tri_idx_, uint32_t cluster_idx_);
  //--------------------------------------------------------------------------

  // triangle operators
  PFC_INLINE const uint32_t *tri_vidx(uint32_t tri_idx_) const;
  PFC_INLINE const uint32_t *tri_eidx(uint32_t tri_idx_) const;
  PFC_INLINE uint32_t tri_cluster(uint32_t tri_idx_) const;
  PFC_INLINE void set_tri_cluster(uint32_t tri_idx_, uint32_t cluster_idx_);
  void update_cluster_tri_list(uint32_t cluster_idx_);
  //--------------------------------------------------------------------------

  // mesh traversal
  template<class Pred> void for_each_vtx_tri(uint32_t vtx_idx_, Pred&) const;
  template<class Pred> void for_each_edge_tri(uint32_t edge_idx_, Pred&) const;
  template<class Pred> void for_each_tri_vtx_tri(uint32_t tri_idx_, Pred&) const;
  template<class Pred> void for_each_tri_edge_tri(uint32_t tri_idx_, Pred&) const;
  template<class Pred> void for_each_cluster_vtx(uint32_t cluster_idx_, Pred&) const;
  template<class Pred> void for_each_cluster_tri(uint32_t cluster_idx_, Pred&) const;
  template<class Pred> void for_each_edge_connected_cluster_tri(uint32_t start_tri_idx_, Pred&) const;
  //--------------------------------------------------------------------------

private:
  //==========================================================================
  // vertex
  //==========================================================================
  struct vertex
  {
    mutable uint32_t pass_id;
    uint32_t edge_list;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // edge
  //==========================================================================
  struct edge
  {
    mutable uint32_t pass_id;
    uint32_t vidx_min, vidx_max;
    uint32_t tri_list;
    uint32_t next_vtx_edge[2];
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // triangle
  //==========================================================================
  struct triangle
  {
    mutable uint32_t pass_id;
    uint32_t cidx;
    uint32_t vidx[3];
    uint32_t eidx[3];
    uint32_t next_edge_tri[3];
    uint32_t next_cluster_tri;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // cluster
  //==========================================================================
  struct cluster
  {
    uint32_t tri_list;
    uint32_t num_tris;
  };
  //--------------------------------------------------------------------------

  mutable uint32_t m_pass_id;
  array<vertex> m_vertices;
  array<edge> m_edges;
  array<triangle> m_triangles;
  array<cluster> m_clusters;
};
//----------------------------------------------------------------------------

//============================================================================
#include "geo3.inl"
} // namespace pfc
#endif
