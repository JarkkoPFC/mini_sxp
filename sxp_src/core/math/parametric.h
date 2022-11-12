//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_MATH_PARAMETRIC_H
#define PFC_CORE_MATH_PARAMETRIC_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/math/math.h"
#include "sxp_src/core/meta.h"
namespace pfc
{

// new
// cubic spline
template<typename> struct cubic_spline;
template<typename T> PFC_INLINE T evaluate(const cubic_spline<T>&, typename math<T>::scalar_t t_);
template<typename T> PFC_INLINE T evaluate(const cubic_spline<T>&, T &tangent_, typename math<T>::scalar_t t_);
template<typename T> T inv_evaluate(const cubic_spline<T>&, T t_);
template<typename T> void make_hermite_spline(cubic_spline<T>&,
                                              typename type<T>::arg p0_,
                                              typename type<T>::arg p1_,
                                              typename type<T>::arg t0_,
                                              typename type<T>::arg t1_);     // p0=start point, p1=end point, t0=start tangent, t1=end tangent
template<typename T> void make_bezier_spline(cubic_spline<T>&,
                                             typename type<T>::arg p0_,
                                             typename type<T>::arg p1_,
                                             typename type<T>::arg p2_,
                                             typename type<T>::arg p3_);      // p0=start point, p3=end point, p1,p2=control points
template<typename T> void make_bspline(cubic_spline<T>&,
                                       typename type<T>::arg p0_,
                                       typename type<T>::arg p1_,
                                       typename type<T>::arg p2_,
                                       typename type<T>::arg p3_);            // p0..p3=control points
template<typename T> void make_catmull_rom_spline(cubic_spline<T>&,
                                                  typename type<T>::arg p0_,
                                                  typename type<T>::arg p1_,
                                                  typename type<T>::arg p2_,
                                                  typename type<T>::arg p3_); // p0..p3=control points
template<typename T> void make_interp_spline(cubic_spline<T>&,
                                             typename type<T>::arg p0_,
                                             typename type<T>::arg p1_,
                                             typename type<T>::arg p2_,
                                             typename type<T>::arg p3_); // p0..p3=control points
template<typename T> void make_interp_spline(cubic_spline<T>&,
                                             typename type<T>::arg p0_,
                                             typename type<T>::arg p1_,
                                             typename type<T>::arg p2_,
                                             typename type<T>::arg p3_,
                                             typename math<T>::scalar_t t1_,
                                             typename math<T>::scalar_t t2_); // p0..p3=control points, t1 & t2=time for p1 & p2 respectively (t0=0, t3=1)
// spline->key conversion
template<typename T> void get_hermite_spline_keys(T &p0_, T &p1_, T &t0_, T &t1_, const cubic_spline<T>&);
template<typename T> void get_bezier_spline_keys(T &p0_, T &p1_, T &p2_, T &p3_, const cubic_spline<T>&);
template<typename T> void get_bspline_keys(T &p0_, T &p1_, T &p2_, T &p3_, const cubic_spline<T>&);
template<typename T> void get_catmull_rom_spline_keys(T &p0_, T &p1_, T &p2_, T &p3_, const cubic_spline<T>&);
template<typename T> void get_interp_spline_keys(T &p0_, T &p1_, T &p2_, T &p3_, const cubic_spline<T>&);
// bicubic patch
template<typename> struct bicubic_patch;
template<typename T> T evaluate(const bicubic_patch<T>&, typename math<T>::scalar_t s_, typename math<T>::scalar_t t_);
template<typename T> void make_hermite_patch(bicubic_patch<T>&, const T cm_[16]);
template<typename T> void make_bezier_patch(bicubic_patch<T>&, const T cpnt_[16]);
template<typename T> void make_bspline_patch(bicubic_patch<T>&, const T cpnt_[16]);
template<typename T> void make_catmull_rom_patch(bicubic_patch<T>&, const T cpnt_[16]);
template<typename T> void make_interp_patch(bicubic_patch<T>&, const T cpnt_[16]);
// spline fitting
template<class T> class spline_fit_constraint_vec;
template<class T> class spline_fit_constraint_quat;
template<typename T, typename K, class Constraint> unsigned fit_spline(K keys_iterator_, unsigned num_keys_, Constraint&, unsigned max_cubic_spline_length_=0);
// misc spline operations
template<typename T> void reparametrize_spline(cubic_spline<T> &rs_, const cubic_spline<T> &s_, typename math<T>::scalar_t t_scale_, typename math<T>::scalar_t t_bias_);
template<typename T> void spline_bounds(T &min_, T &max_, const cubic_spline<T>&);
template<typename T> typename math<T>::scalar_t spline_length(const cubic_spline<T>&, unsigned num_steps_=100);
template<typename T> typename math<T>::scalar_t spline_distance_func(const cubic_spline<T>&, vec2<typename math<T>::scalar_t> &hermite_tangents_, unsigned num_steps_=100);
//----------------------------------------------------------------------------


//============================================================================
// cubic_spline
//============================================================================
template<typename T>
struct cubic_spline
{ PFC_MONO(cubic_spline) {PFC_VAR4(a, b, c, d);}
  // construction
  PFC_INLINE cubic_spline();
  PFC_INLINE cubic_spline(typename type<T>::arg a_, typename type<T>::arg b_, typename type<T>::arg c_, typename type<T>::arg d_);
  //--------------------------------------------------------------------------

  T a, b, c, d;
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, cubic_spline<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, cubic_spline<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// bicubic_patch
//============================================================================
template<typename T>
struct bicubic_patch
{ PFC_MONO(bicubic_patch) {PFC_AVAR(coeffs, 16);}
  // construction
  PFC_INLINE bicubic_patch();
  PFC_INLINE bicubic_patch(const T coeffs_[16]);
  //--------------------------------------------------------------------------

  T coeffs[16];
};
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, bicubic_patch<T>, is_type_pod, is_type_pod<T>::res);
PFC_SET_TYPE_TRAIT_PARTIAL(typename T, bicubic_patch<T>, is_type_pod_stream, is_type_pod_stream<T>::res);
//----------------------------------------------------------------------------


//============================================================================
// spline_fit_constraint_vec
//============================================================================
template<class T>
class spline_fit_constraint_vec
{ typedef typename math<T>::scalar_t scalar_t;
public:
  // construction
  spline_fit_constraint_vec(scalar_t input_curvature_tolerance_deg_,  // if the angle between in & out vectors of an input key is greater than the tolerance, results spline tangent discontinuity
                            scalar_t input_velocity_tolerance_,       // if the velocity of in/out vectors of an input key is less than the tolerance, doesn't cause spline tangent discontinuity in any case
                            scalar_t output_distance_tolerance_,      // the resulting spline is maximum of the output distance tolerance from the input keys
                            scalar_t tangent_velocity_percent_);      // if connected spline segment tangent velocities differ more than the given percent, doesn't merge the tangents
  spline_fit_constraint_vec(cubic_spline<T> *spline_buffer_,
                            unsigned *spline_length_buffer_,          // the length of each cubic spline in frames
                            unsigned buffer_capacity_,
                            scalar_t input_curvature_tolerance_deg_,
                            scalar_t input_velocity_tolerance_,
                            scalar_t output_distance_tolerance_,
                            scalar_t tangent_velocity_percent_);
  void init_buffers(cubic_spline<T> *spline_buffer_,
                    unsigned *spline_length_buffer_,
                    unsigned buffer_capacity_);
  //--------------------------------------------------------------------------

  // predicate interface
  PFC_INLINE bool input_constraints(const T &first_, const T &prev_, const T &key_, const T &next_) const;
  PFC_INLINE bool spline_constraints(const T &prev_, const T &key_, const cubic_spline<T>&, scalar_t t_) const;
  PFC_INLINE bool add_spline(const cubic_spline<T>&, unsigned spline_length_);
  //--------------------------------------------------------------------------

  // additional tests
  PFC_INLINE bool tangent_constraints(const T &in_, const T &out_) const;
  //--------------------------------------------------------------------------

private:
  void init_constraints(scalar_t input_curvature_tolerance_deg_,
                        scalar_t input_velocity_tolerance_,
                        scalar_t output_distance_tolerance_,
                        scalar_t tangent_velocity_percent_);
  //--------------------------------------------------------------------------

  scalar_t m_tolerance_input_curvature;
  scalar_t m_tolerance_input_velocity;
  scalar_t m_tolerance_sqr_distance;
  scalar_t m_tolerance_tangent_velocity_factor;
  cubic_spline<T> *m_spline_buffer;
  unsigned *m_spline_length_buffer;
  unsigned m_buffer_capacity;
};
//----------------------------------------------------------------------------


//============================================================================
// spline_fit_constraint_quat
//============================================================================
template<class T>
class spline_fit_constraint_quat
{ typedef typename math<T>::scalar_t scalar_t;
public:
  // construction
  spline_fit_constraint_quat(scalar_t input_curvature_tolerance_deg_,
                             scalar_t input_angular_velocity_tolerance_,
                             scalar_t output_angle_tolerance_deg_,
                             scalar_t tangent_angular_velocity_percent_);
  spline_fit_constraint_quat(cubic_spline<T> *spline_buffer_,
                             unsigned *spline_length_buffer_,
                             unsigned buffer_capacity_,
                             scalar_t input_curvature_tolerance_deg_,
                             scalar_t input_angular_velocity_tolerance_,
                             scalar_t output_angle_tolerance_deg_,
                             scalar_t tangent_angular_velocity_percent_);
  void init_buffers(cubic_spline<T> *spline_buffer_,
                    unsigned *spline_length_buffer_,
                    unsigned buffer_capacity_);
  //--------------------------------------------------------------------------

  // predicate interface
  PFC_INLINE bool input_constraints(const T &first_, const T &prev_, const T &key_, const T &next_) const;
  PFC_INLINE bool spline_constraints(const T &prev_, const T &key_, const cubic_spline<T>&, scalar_t t_) const;
  PFC_INLINE bool add_spline(const cubic_spline<T>&, unsigned spline_length_);
  //--------------------------------------------------------------------------

  // additional tests
  PFC_INLINE bool tangent_constraints(const T &in_, const T &out_) const;
  //--------------------------------------------------------------------------

private:
  void init_constraints(scalar_t input_curvature_tolerance_deg_,
                        scalar_t input_angular_velocity_tolerance_,
                        scalar_t output_angle_tolerance_deg_,
                        scalar_t tangent_angular_velocity_percent_);
  //--------------------------------------------------------------------------

  cubic_spline<T> *m_spline_buffer;
  unsigned *m_spline_length_buffer;
  unsigned m_buffer_capacity;
  scalar_t m_tolerance_input_curvature;
  scalar_t m_tolerance_input_angular_velocity;
  scalar_t m_tolerance_output_angle;
  scalar_t m_tolerance_tangent_angular_velocity_factor;
};
//----------------------------------------------------------------------------

//============================================================================
#include "parametric.inl"
} // namespace pfc
#endif
