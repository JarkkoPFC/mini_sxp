//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_CORE_ENGINE_TRACK_SET_H
#define PFC_CORE_ENGINE_TRACK_SET_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core_engine/loaders/dataio.h"
#include "sxp_src/core/math/parametric.h"
#include "sxp_src/core/class.h"
namespace pfc
{

// new
template<typename> struct track_key_hermite;
struct track_channel_info;
struct track_info;
struct track_set_splinify_settings;
class track_set;
class compressed_track_set;
owner_ptr<track_set> load_track_set(bin_input_stream_base&);
owner_ptr<track_set> load_track_set(const char *filename_, const char *path_=0);
//----------------------------------------------------------------------------


//============================================================================
// e_track_channel
//============================================================================
enum e_track_channel
{
  trackchannel_position =0x00000001, // vec3f
  trackchannel_rotation =0x00000002, // quatf
};
PFC_ENUM(e_track_channel);
//----------------------------------------------------------------------------


//============================================================================
// e_track_channel_format
//============================================================================
enum e_track_channel_format
{
  trackchannelformat_none,
  trackchannelformat_constant, // store constant value
  trackchannelformat_sample,   // store a sample for each key
  trackchannelformat_hermite,  // store a start value followed by sequence of track_key_hermite
};
PFC_ENUM(e_track_channel_format);
//----------------------------------------------------------------------------


//============================================================================
// track_key_hermite
//============================================================================
template<typename T>
struct track_key_hermite
{ PFC_MONO(track_key_hermite) {PFC_VAR4(num_frames, p1, t0, t1);}
  PFC_ALIGN(4)
  uint16_t num_frames;
  T p1, t0, t1;
};
//----------------------------------------------------------------------------


//============================================================================
// track_channel_info
//============================================================================
struct track_channel_info
{ PFC_MONO(track_channel_info) {PFC_VAR2(channel, format);}
  PFC_ALIGN(4)
  e_track_channel channel;
  e_track_channel_format format;
  uint32_t data_offset;
};
//----------------------------------------------------------------------------


//============================================================================
// track_info
//============================================================================
struct track_info
{ PFC_MONO(track_info) {PFC_VAR4(start_frame, num_frames, num_channels, channel_offset_start);}
  PFC_ALIGN(4)
  uint16_t start_frame;
  uint16_t num_frames;
  uint8_t num_channels;
  uint16_t channel_offset_start;
};
//----------------------------------------------------------------------------


//============================================================================
// track_set_splinify_settings
//============================================================================
struct track_set_splinify_settings
{ PFC_MONO(track_set_splinify_settings)
  {
    PFC_VAR_GROUP("position");
    PFC_MVAR(pos_input_curvature_tolerance_deg);
    PFC_MVAR(pos_input_velocity_tolerance);
    PFC_MVAR(pos_output_distance_tolerance);
    PFC_MVAR(pos_tangent_velocity_tolerance_percent);
    PFC_VAR_GROUP_END();
    PFC_VAR_GROUP("rotation");
    PFC_MVAR(rot_input_curvature_tolerance_deg);
    PFC_MVAR(rot_input_angular_velocity_tolerance);
    PFC_MVAR(rot_output_angle_tolerance_deg);
    PFC_MVAR(rot_tangent_angular_velocity_tolerance_percent);
    PFC_VAR_GROUP_END();
  }
  //--------------------------------------------------------------------------

  // construction
  track_set_splinify_settings();
  //--------------------------------------------------------------------------

  // position stream compression settings
  float pos_input_curvature_tolerance_deg;
  float pos_input_velocity_tolerance;
  float pos_output_distance_tolerance;
  float pos_tangent_velocity_tolerance_percent;
  // rotation stream compression settings
  float rot_input_curvature_tolerance_deg;
  float rot_input_angular_velocity_tolerance;
  float rot_output_angle_tolerance_deg;
  float rot_tangent_angular_velocity_tolerance_percent;
};
//----------------------------------------------------------------------------


//============================================================================
// track_set
//============================================================================
class track_set
{ PFC_REPOSITORY_BASE_CLASS_DECL(track_set)
  {
    PFC_VAR(m_fps);
    PFC_HVAR(m_spf);
    PFC_VAR3(m_variable_track_times, m_start_frame, m_num_frames);
    PFC_HVAR(m_track_data);
    PFC_HVAR(m_track_names);
  }
  template<typename> class const_iterator;
public:
  // nested types
  typedef const_iterator<vec3f> const_iterator_vec3f;
  typedef const_iterator<quatf> const_iterator_quatf;
  //--------------------------------------------------------------------------

  // construction
  track_set();
  track_set(ufloat_t fps_, unsigned num_tracks_, unsigned num_total_channels_, unsigned channel_data_size_);
  track_set(const track_set&, const track_set_splinify_settings&);
  track_set(bin_input_stream_base&);
  ~track_set();
  void init(ufloat_t fps_, unsigned num_tracks_, unsigned num_total_channels_, unsigned channel_data_size_);
  void finish_init();
  void splinify(const track_set&, const track_set_splinify_settings&);
  e_file_format load(bin_input_stream_base&);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE ufloat_t fps() const;
  PFC_INLINE ufloat_t spf() const;
  PFC_INLINE unsigned num_tracks() const;
  PFC_INLINE bool has_channel(e_track_channel) const;
  PFC_INLINE bool variable_track_times() const;
  PFC_INLINE unsigned start_frame() const;
  PFC_INLINE unsigned start_frame(unsigned track_index_) const;
  PFC_INLINE unsigned num_frames() const;
  PFC_INLINE unsigned num_frames(unsigned track_index_) const;
  //--------------------------------------------------------------------------

  // track and channel info accessors
  PFC_INLINE const track_info *track_infos() const;
  PFC_INLINE track_info *track_infos();
  PFC_INLINE const track_channel_info *channel_infos() const;
  PFC_INLINE track_channel_info *channel_infos();
  PFC_INLINE const track_channel_info *find_channel_info(const track_info&, e_track_channel) const;
  PFC_INLINE const void *channel_data() const;
  PFC_INLINE void *channel_data();
  PFC_INLINE const array<char> &track_names() const;
  PFC_INLINE void swap_track_names(array<char>&);
  //--------------------------------------------------------------------------

private:
  template<class PE, typename T> static void serialize_spline_channel(PE&, char *data_, unsigned &data_pos_, unsigned num_frames_, const meta_type<T>&);
  template<typename T, class Constraint> static void add_channel_spline_fit(array<uint8_t>&, const T *keys_, unsigned num_keys_, Constraint&);
  template<typename T> static void add_spline_channel(array<uint8_t>&, const uint8_t *data_, unsigned num_frames_, const meta_type<T>&);
  //--------------------------------------------------------------------------

  //==========================================================================
  // track_data
  //==========================================================================
  struct track_data
  { PFC_MONO(track_data) PFC_INTROSPEC_DECL;
    // construction
    PFC_INLINE track_data();
    PFC_INLINE track_data(const track_data&);
    void operator=(const track_data&);
    //------------------------------------------------------------------------

    unsigned num_tracks;
    unsigned num_total_channels;
    unsigned channel_data_size;
    void *data;
  };
  //--------------------------------------------------------------------------

  ufloat_t m_fps, m_spf;
  bool m_variable_track_times;
  unsigned m_start_frame;
  unsigned m_num_frames;
  track_data m_track_data;
  array<char> m_track_names;
};
//----

PFC_SET_TYPE_TRAIT(track_set, is_type_copyable, false);
//----------------------------------------------------------------------------

//============================================================================
// track_set::const_iterator
//============================================================================
template<typename T>
class track_set::const_iterator
{
public:
  PFC_INLINE const_iterator();
  PFC_INLINE const_iterator(const track_set&, e_track_channel, unsigned track_index_, float start_time_=0.0f);
  void init(const track_set&, e_track_channel, unsigned track_index_, const T &default_, float start_time_=0.0f);
  void init(const T&, ufloat_t time_, float start_time_=0.0f);
  void init(const T&);
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE bool advance(ufloat_t time_, const track_set&);
  PFC_INLINE void evaluate(T&, ufloat_t time_) const;
  PFC_INLINE bool evaluate(T&, ufloat_t time_, const track_set&);
  //--------------------------------------------------------------------------

private:
  bool find_segment(ufloat_t &seg_time_, ufloat_t time_, const track_set&);
  //--------------------------------------------------------------------------

  const void *m_data;
  ufloat_t m_segment_end;
  uint16_t m_num_frames_left;
  uint8_t m_channel_format;
  cubic_spline<T> m_segment;
};
//----------------------------------------------------------------------------


//============================================================================
// compressed_track_set
//============================================================================
class compressed_track_set
{ PFC_REPOSITORY_BASE_CLASS_DECL(compressed_track_set)
  {
    PFC_VAR(m_channels);
    PFC_VAR(m_num_tracks);
    PFC_VAR(m_fps);
    PFC_HVAR(m_spf);
    PFC_VAR3(m_variable_track_times, m_start_frame, m_num_frames);
    PFC_HVAR(m_track_channel_data);
    PFC_HVAR2(m_pos_start_scale, m_pos_start_bias);
    PFC_HVAR2(m_pos_delta_scale, m_pos_delta_bias);
    PFC_HVAR2(m_pos_tangent_scale, m_pos_tangent_bias);
    PFC_HVAR2(m_rot_tangent_norm_scale, m_rot_tangent_norm_bias);
  }
  template<class> class const_iterator;
public:
  // nested types
  typedef const_iterator<vec3f> const_iterator_vec3f;
  typedef const_iterator<quatf> const_iterator_quatf;
  //--------------------------------------------------------------------------

  // construction
  compressed_track_set();
  compressed_track_set(const track_set&, const track_set_splinify_settings&);
  void init(const track_set&, const track_set_splinify_settings&);
  //--------------------------------------------------------------------------

  // accessors
  PFC_INLINE ufloat_t fps() const;
  PFC_INLINE ufloat_t spf() const;
  PFC_INLINE unsigned num_tracks() const;
  PFC_INLINE bool has_channel(e_track_channel) const;
  PFC_INLINE bool variable_track_times() const;
  PFC_INLINE unsigned start_frame() const;
  PFC_INLINE unsigned start_frame(unsigned track_index_) const;
  PFC_INLINE unsigned num_frames() const;
  PFC_INLINE unsigned num_frames(unsigned track_index_) const;
  //--------------------------------------------------------------------------

private:
  template<typename> struct track_channel_config;
  //--------------------------------------------------------------------------

  //==========================================================================
  // track_times
  //==========================================================================
  struct track_times
  {
    uint16_t start_frame;
    uint16_t num_frames;
  };
  //--------------------------------------------------------------------------

  compressed_track_set(const compressed_track_set&); // not implemented
  void operator=(const compressed_track_set&); // not implemented
  void init_members();
  template<class Cfg> void compress_channel(Cfg&, const track_set&, unsigned &channel_offset_writepos_, unsigned &channel_data_writepos_);
  void compress_position_stream(const track_set&, const track_set_splinify_settings&, unsigned &channel_offset_writepos_, unsigned &channel_data_writepos_);
  void compress_rotation_stream(const track_set&, const track_set_splinify_settings&, unsigned &channel_offset_writepos_, unsigned &channel_data_writepos_);
  PFC_INLINE const void *track_channel_data(e_track_channel, unsigned track_index_) const;
  //--------------------------------------------------------------------------

  typedef uint32_t channel_offset;
  enum {null_channel_offset=0xffffffff};
  sarray<e_track_channel, 4> m_channels;
  ufloat_t m_fps, m_spf;
  unsigned m_num_tracks;
  bool m_variable_track_times;
  unsigned m_start_frame;
  unsigned m_num_frames;
  array<uint8_t> m_track_channel_data;
  // dequantization scale & bias
  vec3f m_pos_start_scale, m_pos_start_bias;
  vec3f m_pos_delta_scale, m_pos_delta_bias;
  vec3f m_pos_tangent_scale, m_pos_tangent_bias;
  float m_rot_tangent_norm_scale, m_rot_tangent_norm_bias;
};
//----

PFC_SET_TYPE_TRAIT(compressed_track_set, is_type_copyable, false);
//----------------------------------------------------------------------------

//============================================================================
// compressed_track_set::const_iterator
//============================================================================
template<typename T>
class compressed_track_set::const_iterator
{
public:
  PFC_INLINE const_iterator();
  PFC_INLINE const_iterator(const compressed_track_set&, e_track_channel, unsigned track_index_, float start_time_=0.0f);
  void init(const compressed_track_set&, e_track_channel, unsigned track_index_, const T &default_, float start_time_=0.0f);
  void init(const T&, ufloat_t time_, float start_time_=0.0f);
  void init(const T&);
  //--------------------------------------------------------------------------

  // iteration
  PFC_INLINE bool advance(ufloat_t time_, const compressed_track_set&);
  PFC_INLINE void evaluate(T&, ufloat_t time_) const;
  PFC_INLINE bool evaluate(T&, ufloat_t time_, const compressed_track_set&);
  //--------------------------------------------------------------------------

private:
  bool find_segment(ufloat_t &seg_time_, ufloat_t time_, const compressed_track_set&);
  //--------------------------------------------------------------------------

  ufloat_t m_segment_end;
  const void *m_data;
  uint8_t m_num_segments_left;
  cubic_spline<T> m_segment;
};
//----------------------------------------------------------------------------

//============================================================================
#include "track_set.inl"
} // namespace pfc
#endif
