//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2024, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "track_set.h"
#include "sxp_src/core/fsys/fsys.h"
#include "sxp_src/core/math/tform3.h"
#include "sxp_src/core/sort.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// locals
//============================================================================
namespace
{
  //==========================================================================
  // unaligned_uint16
  //==========================================================================
  struct unaligned_uint16
  {
    PFC_INLINE unaligned_uint16()
    {
    }
    //----

    PFC_INLINE unaligned_uint16(float v_)
    {
      uint16_t v=uint16_t(v_);
      lo=uint8_t(v);
      hi=uint8_t(v>>8);
    }
    //----

    PFC_INLINE unaligned_uint16(uint16_t v_)
    {
      lo=uint8_t(v_);
      hi=uint8_t(v_>>8);
    }
    //----

    PFC_INLINE operator uint16_t() const
    {
      return uint16_t(lo+(hi<<8));
    }
    //------------------------------------------------------------------------

    uint8_t lo, hi;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // scaled_compressed_rotation32
  //==========================================================================
  struct scaled_compressed_rotation32
  {
    compressed_rotation_spi24 rot;
    uint8_t scale:7;
    uint8_t sign:1;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // compressed_spline
  //==========================================================================
  template<typename> struct compressed_spline;
  //----

  template<>
  struct compressed_spline<vec3f>
  {
    uint8_t num_segments;
    vec3<unaligned_uint16> start_pos;  // quantized spline start position
    vec3<uint8_t> start_tangent;         // quantized start tangent
  };
  //----

  template<>
  struct compressed_spline<quatf>
  {
    uint8_t num_segments:7;
    uint8_t start_rot_sign:1;
    compressed_rotation_spi24 start_rot;
    scaled_compressed_rotation32 start_tangent;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // compressed_const_spline
  //==========================================================================
  template<typename> struct compressed_const_spline;
  //----

  template<>
  struct compressed_const_spline<vec3f>
  {
    uint8_t num_segments;
    vec3<unaligned_uint16> start_pos;  // quantized spline start position
  };
  //----

  template<>
  struct compressed_const_spline<quatf>
  {
    uint8_t num_segments:7;
    uint8_t start_rot_sign:1;
    compressed_rotation_spi24 start_rot;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // compressed_spline_segment
  //==========================================================================
  template<typename> struct compressed_spline_segment;
  //----

  template<>
  struct compressed_spline_segment<vec3f>
  {
    uint8_t segment_frames;     // length of the spline segment in frames
    vec3<uint8_t> end_tangent;  // quantized spline segment end tangent vector
    vec3<uint8_t> delta_pos;    // quantized spline start->end position vector
  };
  //----

  template<>
  struct compressed_spline_segment<quatf>
  {
    uint8_t segment_frames:7;
    uint8_t end_rot_sign:1;
    scaled_compressed_rotation32 end_tangent;
    compressed_rotation_spi24 end_rot;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // degenerated_compressed_spline_segment
  //==========================================================================
  template<typename> struct degenerated_compressed_spline_segment;
  //----

  template<>
  struct degenerated_compressed_spline_segment<vec3f>
  {
    uint8_t segment_frames;
    vec3<uint8_t> end_tangent;
  };
  //----

  template<>
  struct degenerated_compressed_spline_segment<quatf>
  {
    uint8_t segment_frames;
    scaled_compressed_rotation32 end_tangent;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // hermite_key
  //==========================================================================
  template<typename T>
  struct hermite_key
  {
    unsigned num_frames;
    bool merge_tangent;
    T p0, p1, t0, t1;
  };
  //--------------------------------------------------------------------------

  //==========================================================================
  // quantization/dequantization functions
  //==========================================================================
  template<typename T>
  PFC_INLINE vec3<T> quantize(const vec3f &v_, const vec3f &scale_, const vec3f &bias_)
  {
    vec3f v=(v_-bias_)*scale_;
    return vec3<T>(T(v.x+0.5f), T(v.y+0.5f), T(v.z+0.5f));
  }
  //----

  template<typename T>
  PFC_INLINE vec3f dequantize(const vec3<T> &v_, const vec3f &scale_, const vec3f &bias_)
  {
    return madd(vec3f(v_.x, v_.y, v_.z), scale_, bias_);
  }
  //--------------------------------------------------------------------------
} // namespace <anonymous>
//----------------------------------------------------------------------------


//============================================================================
// load_track_set
//============================================================================
owner_ptr<track_set> pfc::load_track_set(bin_input_stream_base &stream_)
{
  // check for SXE track set format
  char id[16];
  stream_.read_bytes(id, 16);
  stream_.rewind(16);
  if(mem_eq(id, "pfc_archsxe_tset", 16))
    return read_object<track_set>(stream_);

  // load non-SXE track set
  owner_ptr<track_set> tset=PFC_NEW(track_set);
  return tset.data->load(stream_)?tset:owner_ptr<track_set>(0);
}
//----

owner_ptr<track_set> pfc::load_track_set(const char *filename_, const char *path_)
{
  // try to load a track set file
  owner_ptr<bin_input_stream_base> f=afs_open_read(filename_, path_);
  if(!f.data)
  {
    PFC_WARNF("Unable to open track set file \"%s\"\r\n", afs_complete_path(filename_, path_).c_str());
    return 0;
  }
  return load_track_set(*f.data);
}
//----------------------------------------------------------------------------


//============================================================================
// e_track_channel
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_track_channel
#define PFC_ENUM_PREFIX trackchannel_
#define PFC_ENUM_VALS PFC_ENUM_VAL(position)\
                      PFC_ENUM_VAL(rotation)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// e_track_channel_format
//============================================================================
#define PFC_ENUM_NAMESPACE pfc
#define PFC_ENUM_TYPE e_track_channel_format
#define PFC_ENUM_PREFIX trackchannelformat_
#define PFC_ENUM_VALS PFC_ENUM_VAL(constant)\
                      PFC_ENUM_VAL(sample)\
                      PFC_ENUM_VAL(hermite)
#include "sxp_src/core/enum.inc"
//----------------------------------------------------------------------------


//============================================================================
// track_set::const_iterator
//============================================================================
template<typename T>
void track_set::const_iterator<T>::init(const track_set &set_, e_track_channel channel_, unsigned track_index_, const T &default_, float start_time_)
{
  const track_info &tinfo=set_.track_infos()[track_index_];
  const track_channel_info *cinfo=set_.find_channel_info(tinfo, channel_);
  if(cinfo)
  {
    // setup the first spline segment
    m_data=((const uint8_t*)set_.channel_data()+cinfo->data_offset);
    switch(cinfo->format)
    {
      case trackchannelformat_constant:
      {
        // setup constant value for the entire channel
        const T *data=(const T*)m_data;
        m_segment_end=floor(tinfo.num_frames+start_time_*set_.m_fps+0.5f)*set_.m_spf;
        m_num_frames_left=0;
        m_segment.a.set(0.0f);
        m_segment.c=m_segment.b=m_segment.a;
        m_segment.d=*data;
      } break;

      case trackchannelformat_sample:
      {
        // setup linear interpolation between samples
        const T *data=(const T*)m_data;
        m_segment_end=start_time_+set_.m_spf;
        m_num_frames_left=uint16_t(tinfo.num_frames-1);
        m_segment.a.set(0.0f);
        m_segment.b=m_segment.a;
        m_segment.c=(data[0]-data[1])*set_.m_fps;
        m_segment.d=data[1];
      } break;

      case trackchannelformat_hermite:
      {
        // setup Hermite spline interpolation
        const T *data_start=(const T*)m_data;
        const track_key_hermite<T> *data_spline=(const track_key_hermite<T>*)(data_start+1);
        m_data=data_spline;
        unsigned num_frames=data_spline->num_frames;
        float segment_time=num_frames*set_.m_spf;
        m_segment_end=start_time_+segment_time;
        m_num_frames_left=uint16_t(tinfo.num_frames-num_frames);
        make_hermite_spline(m_segment, data_spline->p1, *data_start, -data_spline->t1, -data_spline->t0);
        float segment_rtime=1.0f/segment_time, segment_rtime2=segment_rtime*segment_rtime;
        m_segment.a*=segment_rtime2*segment_rtime;
        m_segment.b*=segment_rtime2;
        m_segment.c*=segment_rtime;
      } break;

      default: PFC_ERROR("Unsupported track channel format\r\n");
    }
    m_channel_format=uint8_t(cinfo->format);
  }
  else
  {
    // setup spline segment with default constant value
    m_data=0;
    m_segment_end=floor(tinfo.num_frames+start_time_*set_.m_fps+0.5f)*set_.m_spf;
    m_num_frames_left=0;
    m_channel_format=trackchannelformat_constant;
    m_segment.a.set(0.0f);
    m_segment.c=m_segment.b=m_segment.a;
    m_segment.d=default_;
  }
}
//----

template<typename T>
void track_set::const_iterator<T>::init(const T &v_, ufloat_t time_, float start_time_)
{
  // init iterator with constant value for given period of time
  m_data=0;
  m_segment_end=time_+start_time_;
  m_num_frames_left=0;
  m_channel_format=trackchannelformat_constant;
  m_segment.a.set(0.0f);
  m_segment.c=m_segment.b=m_segment.a;
  m_segment.d=v_;
}
//----

template<typename T>
void track_set::const_iterator<T>::init(const T &v_)
{
  // init iterator with infinite constant value
  m_data=0;
  m_segment_end=numeric_type<float>::range_max();
  m_num_frames_left=0;
  m_channel_format=trackchannelformat_constant;
  m_segment.a.set(0.0f);
  m_segment.c=m_segment.b=m_segment.a;
  m_segment.d=v_;
}
//----------------------------------------------------------------------------

template<typename T>
bool track_set::const_iterator<T>::find_segment(ufloat_t &seg_time_, ufloat_t time_, const track_set &set_)
{
  // find the spline segment for the given time value
  if(!m_num_frames_left)
    return false;
  switch(m_channel_format)
  {
    case trackchannelformat_constant: return false;

    case trackchannelformat_sample:
    {
      // get number of frames to skip
      unsigned num_skip_frames=unsigned((time_-m_segment_end)*set_.m_fps);
      float end_time;
      while((end_time=m_segment_end+num_skip_frames*set_.m_spf)<time_ && ++num_skip_frames<=m_num_frames_left);
      m_segment_end=end_time;
      if(num_skip_frames>=m_num_frames_left)
      {
        // setup last frame
        const T *data=(const T*)m_data+m_num_frames_left-1;
        m_num_frames_left=0;
        m_segment.c.set(0.0f);
        m_segment.d=*data;
        return false;
      }
      seg_time_=m_segment_end-time_;

      // setup linear interpolation between samples
      m_num_frames_left-=uint16_t(num_skip_frames);
      const T *data=(const T*)m_data+num_skip_frames;
      m_data=data;
      m_segment.c=(data[0]-data[1])*set_.m_fps;
      m_segment.d=data[1];
    } break;

    case trackchannelformat_hermite:
    {
      // find spline segment for the given time value
      const track_key_hermite<T> *data_spline=(const track_key_hermite<T>*)m_data;
      unsigned num_seg_frames;
      T p0, p1=m_segment.d;
      do 
      {
        ++data_spline;
        p0=p1;
        p1=data_spline->p1;
        num_seg_frames=data_spline->num_frames;
        m_num_frames_left-=uint16_t(num_seg_frames);
        m_segment_end+=num_seg_frames*set_.m_spf;
      } while(m_segment_end<time_ && m_num_frames_left);

      // check for end of track
      m_data=data_spline;
      if(m_segment_end<time_)
      {
        m_segment.a.set(0.0f);
        m_segment.c=m_segment.b=m_segment.a;
        m_segment.d=p1;
        return false;
      }
      seg_time_=m_segment_end-time_;

      // setup Hermite spline interpolation
      float segment_rtime=set_.m_fps/float(num_seg_frames), segment_rtime2=segment_rtime*segment_rtime;
      make_hermite_spline(m_segment, data_spline->p1, p0, -data_spline->t1, -data_spline->t0);
      m_segment.a*=segment_rtime2*segment_rtime;
      m_segment.b*=segment_rtime2;
      m_segment.c*=segment_rtime;
    } break;

    default: PFC_ERROR("Unsupported track channel format\r\n");
  }
  return true;
}
//----------------------------------------------------------------------------

// explicitly instantiate track_set iterators
template class track_set::const_iterator<vec3f>;
template class track_set::const_iterator<quatf>;
//----------------------------------------------------------------------------


//============================================================================
// track_set
//============================================================================
PFC_CLASS_DEF(track_set);
//----------------------------------------------------------------------------

track_set::track_set()
{
  // init track set
  m_fps=0.0f;
  m_spf=0.0f;
  m_variable_track_times=false;
  m_start_frame=0;
  m_num_frames=0;
  m_track_data.num_tracks=0;
  m_track_data.num_total_channels=0;
  m_track_data.channel_data_size=0;
  m_track_data.data=0;
}
//----

track_set::track_set(ufloat_t fps_, unsigned num_tracks_, unsigned num_total_channels_, unsigned channel_data_size_)
{
  m_track_data.data=0;
  init(fps_, num_tracks_, num_total_channels_, channel_data_size_);
}
//----

track_set::track_set(const track_set &tset_, const track_set_splinify_settings &settings_)
{
  m_track_data.data=0;
  splinify(tset_, settings_);
}
//----

track_set::track_set(bin_input_stream_base &stream_)
{
  m_track_data.data=0;
  load(stream_);
}
//----

track_set::~track_set()
{
  PFC_MEM_FREE(m_track_data.data);
}
//----

void track_set::init(ufloat_t fps_, unsigned num_tracks_, unsigned num_total_channels_, unsigned channel_data_size_)
{
  // initialize track set with given properties
  PFC_MEM_FREE(m_track_data.data);
  m_fps=fps_;
  m_spf=rcp_z(fps_);
  m_variable_track_times=false;
  m_start_frame=0;
  m_num_frames=0;
  m_track_data.num_tracks=num_tracks_;
  m_track_data.num_total_channels=num_total_channels_;
  m_track_data.channel_data_size=channel_data_size_;
  m_track_data.data=PFC_MEM_ALLOC(m_track_data.num_tracks*sizeof(track_info)+m_track_data.num_total_channels*sizeof(track_channel_info)+m_track_data.channel_data_size);
}
//----

void track_set::finish_init()
{
  // check for number of tracks
  if(!m_track_data.num_tracks)
  {
    m_variable_track_times=false;
    m_start_frame=0;
    m_num_frames=0;
    return;
  }

  // get global start and end frame for all the tracks
  const track_info *tracks=track_infos();
  unsigned global_frame_start=tracks->start_frame;
  unsigned global_frame_end=global_frame_start+tracks->num_frames;
  for(unsigned i=1; i<m_track_data.num_tracks; ++i)
  {
    // update global start/end frames with track frames
    ++tracks;
    unsigned frame_start=tracks->start_frame;
    unsigned frame_end=frame_start+tracks->num_frames;
    if(global_frame_start!=frame_start || global_frame_end!=frame_end)
    {
      m_variable_track_times=true;
      frame_start=min(frame_start, frame_start);
      global_frame_end=max(global_frame_end, frame_end);
    }
  }

  // setup start frame & number of frames
  m_start_frame=global_frame_start;
  m_num_frames=global_frame_end-global_frame_start;
}
//----

void track_set::splinify(const track_set &tset_, const track_set_splinify_settings &settings_)
{
  // preliminary init of the data
  PFC_MEM_FREE(m_track_data.data);
  m_fps=tset_.m_fps;
  m_spf=tset_.m_spf;
  m_variable_track_times=tset_.m_variable_track_times;
  m_start_frame=tset_.m_start_frame;
  m_num_frames=tset_.m_num_frames;
  m_track_names=tset_.m_track_names;
  m_track_data=tset_.m_track_data;
  m_track_data.channel_data_size=0;
  m_track_data.data=0;

  // allocate new track containers
  array<track_channel_info> new_cinfos;
  new_cinfos.reserve(m_track_data.num_total_channels);
  array<uint8_t> new_channel_data;

  // process all the tracks
  const track_info *tinfos=tset_.track_infos();
  const track_channel_info *cinfos=tset_.channel_infos();
  for(unsigned ti=0; ti<m_track_data.num_tracks; ++ti)
  {
    // add new track
    const track_info &tinfo=tinfos[ti];
    if(!tinfo.num_frames)
      continue;

    // process all track channels
    for(unsigned ci=0; ci<tinfo.num_channels; ++ci)
    {
      // setup channel info
      track_channel_info &new_cinfo=new_cinfos.push_back();
      const track_channel_info &cinfo=cinfos[tinfo.channel_offset_start+ci];
      new_cinfo.channel=cinfo.channel;
      new_cinfo.format=trackchannelformat_hermite;
      new_cinfo.data_offset=(unsigned)new_channel_data.size();

      // switch to proper channel format handling
      const uint8_t *cdata=(const uint8_t*)tset_.channel_data()+cinfo.data_offset;
      switch(cinfo.format)
      {
        case trackchannelformat_sample:
        {
          unsigned num_keys=tinfo.num_frames+1;
          switch(cinfo.channel)
          {
            case trackchannel_position:
            {
              // add spline fitted position channel
              spline_fit_constraint_vec<vec3f> constraint(settings_.pos_input_curvature_tolerance_deg,
                                                          settings_.pos_input_velocity_tolerance,
                                                          settings_.pos_output_distance_tolerance,
                                                          settings_.pos_tangent_velocity_tolerance_percent);
              add_channel_spline_fit(new_channel_data, (const vec3f*)cdata, num_keys, constraint);
            } break;

            case trackchannel_rotation:
            {
              // add spline fitted rotation channel
              spline_fit_constraint_quat<quatf> constraint(settings_.rot_input_curvature_tolerance_deg,
                                                           settings_.rot_input_angular_velocity_tolerance,
                                                           settings_.rot_output_angle_tolerance_deg,
                                                           settings_.rot_tangent_angular_velocity_tolerance_percent);
              add_channel_spline_fit(new_channel_data, (const quatf*)cdata, num_keys, constraint);
            } break;

            default: PFC_ERROR("Unsupported sample track channel type\r\n");
          }
        } break;

        case trackchannelformat_hermite:
        {
          // switch to proper spline format copy function
          switch(cinfo.channel)
          {
            case trackchannel_position: add_spline_channel(new_channel_data, cdata, tinfo.num_frames, meta_type<vec3f>()); break;
            case trackchannel_rotation: add_spline_channel(new_channel_data, cdata, tinfo.num_frames, meta_type<quatf>()); break;
            default: PFC_ERROR("Unsupported Hermite track channel type\r\n");
          }
        } break;

        default: PFC_ERRORF("Unsupported channel format \"%s\"\r\n", enum_string(cinfo.format));
      }
    }
  }

  // setup the data for the track set
  unsigned tinfo_size=m_track_data.num_tracks*sizeof(track_info);
  unsigned cinfo_size=m_track_data.num_total_channels*sizeof(track_channel_info);
  unsigned data_size=(unsigned)(tinfo_size+cinfo_size+new_channel_data.size());
  char *new_data=(char*)PFC_MEM_ALLOC(data_size);
  mem_copy(new_data, tinfos, tinfo_size);
  mem_copy(new_data+tinfo_size, new_cinfos.data(), cinfo_size);
  mem_copy(new_data+tinfo_size+cinfo_size, new_channel_data.data(), new_channel_data.size());
  m_track_data.channel_data_size=(unsigned)new_channel_data.size();
  m_track_data.data=new_data;
}
//----

namespace pfc
{
  bool load_track_set_collada(track_set&, bin_input_stream_base&);
  bool load_track_set_bvh(track_set&, bin_input_stream_base&);
} // namespace pfc
//----

e_file_format track_set::load(bin_input_stream_base &stream_)
{
  // try to load the track set with different format loaders
  e_file_format fmt=filefmt_none;
  if(load_track_set_collada(*this, stream_))
    fmt=filefmt_collada;
  else if(load_track_set_bvh(*this, stream_))
    fmt=filefmt_collada;
  else
    PFC_WARN("Unable to load the track set format\r\n");
  return fmt;
}
//----------------------------------------------------------------------------

template<typename T, class Constraint>
void track_set::add_channel_spline_fit(array<uint8_t> &res_data_, const T *keys_, unsigned num_keys_, Constraint &constraint_)
{
  // fit keys to the spline
  enum {max_splines=256};
  cubic_spline<T> spline_buf[max_splines];
  unsigned spline_len_buf[max_splines];
  constraint_.init_buffers(spline_buf, spline_len_buf, max_splines);
  unsigned num_segments=fit_spline<T>(keys_, num_keys_, constraint_);
  PFC_CHECK_MSG(num_segments, ("The track channel generates too many splines\r\n"));

  // convert generated spline to Hermite spline segments
  T p0;
  track_key_hermite<T> hkey;
  for(unsigned i=0; i<num_segments; ++i)
  {
    PFC_CHECK(spline_len_buf[i]<65536);
    hkey.num_frames=uint16_t(spline_len_buf[i]);
    get_hermite_spline_keys(p0, hkey.p1, hkey.t0, hkey.t1, spline_buf[i]);
    if(!i)
      res_data_.insert_back(sizeof(T), (const uint8_t*)&p0);
    res_data_.insert_back(sizeof(track_key_hermite<T>), (const uint8_t*)&hkey);
  }
}
//----

template<typename T>
void track_set::add_spline_channel(array<uint8_t> &res_data_, const uint8_t *data_, unsigned num_frames_, const meta_type<T>&)
{
  // copy spline data
  res_data_.insert_back(sizeof(T), data_);
  data_+=sizeof(T);
  do
  {
    res_data_.insert_back(sizeof(track_key_hermite<T>), data_);
    num_frames_-=((const track_key_hermite<T>*)data_)->num_frames;
    data_+=sizeof(track_key_hermite<T>);
  } while(num_frames_);
}
//----------------------------------------------------------------------------


//============================================================================
// track_set::track_data
//============================================================================
PFC_INTROSPEC_CPP_DEF(track_set::track_data)
{
  PFC_CUSTOM_STREAMING(0);
  switch(unsigned(PE::pe_type))
  {
    case penum_input:
    case penum_output:
    {
      // serialize basic track_set info
      PFC_VAR3(num_tracks, num_total_channels, channel_data_size);
      if(unsigned(PE::pe_type)==penum_input)
      {
        // allocate track data
        PFC_MEM_FREE(data);
        unsigned num_bytes=num_tracks*sizeof(track_info)+num_total_channels*sizeof(track_channel_info)+channel_data_size;
        data=PFC_MEM_ALLOC(num_bytes);
      }

      // serialize track and channel infos
      track_info *tinfos=(track_info*)data;
      track_channel_info *cinfos=(track_channel_info*)((char*)data+num_tracks*sizeof(track_info));
      char *cdata=(char*)data+num_tracks*sizeof(track_info)+num_total_channels*sizeof(track_channel_info);
      pe_.avar(tinfos, num_tracks);
      pe_.avar(cinfos, num_total_channels);

      // serialize tracks
      unsigned cdata_pos=0;
      for(unsigned ti=0; ti<num_tracks; ++ti)
      {
        // check for empty track
        const track_info &tinfo=tinfos[ti];
        if(!tinfo.num_frames)
          continue;

        // serialize channels for the track
        for(unsigned ci=0; ci<tinfo.num_channels; ++ci)
        {
          // switch to proper channel format handling
          track_channel_info &cinfo=cinfos[tinfo.channel_offset_start+ci];
          if(unsigned(PE::pe_type)==penum_input)
            cinfo.data_offset=cdata_pos;
          switch(cinfo.format)
          {
            case trackchannelformat_constant:
            {
              // switch to proper channel type handling
              switch(cinfo.channel)
              {
                case trackchannel_position:
                {
                  // serialize position track constant value
                  pe_.var(*(vec3f*)(cdata+cdata_pos));
                  cdata_pos+=sizeof(vec3f);
                } break;

                case trackchannel_rotation:
                {
                  // serialize rotation track constant value
                  pe_.var(*(quatf*)(cdata+cdata_pos));
                  cdata_pos+=sizeof(quatf);
                } break;

                default: PFC_ERRORF("Unsupported constant track channel type \"%s\" (%i)\r\n", enum_string(cinfo.channel), unsigned(cinfo.channel));
              }
            } break;

            case trackchannelformat_sample:
            {
              // switch to proper channel type handling
              switch(cinfo.channel)
              {
                case trackchannel_position:
                {
                  // serialize position track channel
                  unsigned num_keys=tinfo.num_frames+1;
                  pe_.avar((vec3f*)(cdata+cdata_pos), num_keys);
                  cdata_pos+=sizeof(vec3f)*num_keys;
                } break;

                case trackchannel_rotation:
                {
                  // serialize rotation track channel
                  unsigned num_keys=tinfo.num_frames+1;
                  pe_.avar((quatf*)(cdata+cdata_pos), num_keys);
                  cdata_pos+=sizeof(quatf)*num_keys;
                } break;

                default: PFC_ERRORF("Unsupported sample track channel type \"%s\" (%i)\r\n", enum_string(cinfo.channel), unsigned(cinfo.channel));
              }
            } break;

            case trackchannelformat_hermite:
            {
              // switch to proper channel type handling
              switch(cinfo.channel)
              {
                case trackchannel_position: serialize_spline_channel(pe_, cdata, cdata_pos, tinfo.num_frames, meta_type<vec3f>()); break;
                case trackchannel_rotation: serialize_spline_channel(pe_, cdata, cdata_pos, tinfo.num_frames, meta_type<quatf>()); break;
                default: PFC_ERROR("Unsupported track channel type\r\n");
              }
            } break;

            default: PFC_ERRORF("Unsupported Hermite track channel type \"%s\" (%i)\r\n", enum_string(cinfo.format), unsigned(cinfo.format));
          }
        }
      }
    } break;
  }
}
//----------------------------------------------------------------------------

void track_set::track_data::operator=(const track_data &tdata_)
{
  // assign the data
  PFC_MEM_FREE(data);
  num_tracks=tdata_.num_tracks;
  num_total_channels=tdata_.num_total_channels;
  channel_data_size=tdata_.channel_data_size;
  unsigned data_size=num_tracks*sizeof(track_info)+num_total_channels*sizeof(track_channel_info)+channel_data_size;
  data=PFC_MEM_ALLOC(data_size);
  mem_copy(data, tdata_.data, data_size);
}
//----------------------------------------------------------------------------


//============================================================================
// track_set_splinify_settings
//============================================================================
track_set_splinify_settings::track_set_splinify_settings()
{
  // setup initial position channel spline fit settings
  pos_input_curvature_tolerance_deg=45.0f;
  pos_input_velocity_tolerance=0.1f;
  pos_output_distance_tolerance=0.01f;
  pos_tangent_velocity_tolerance_percent=25.0f;
  // setup initial rotation channel spline fit settings
  rot_input_curvature_tolerance_deg=10.0f;
  rot_input_angular_velocity_tolerance=0.0f;
  rot_output_angle_tolerance_deg=5.0f;
  rot_tangent_angular_velocity_tolerance_percent=25.0f;
}
//----------------------------------------------------------------------------


namespace pfc
{
//============================================================================
// compressed_track_set::track_channel_config
//============================================================================
template<>
struct compressed_track_set::track_channel_config<vec3f>
{
  // config properties
  enum {max_spline_segments=255};
  enum {max_spline_segment_frames=255};
  typedef vec3f key_type;
  typedef vec3<uint8_t> tangent_t;
  //--------------------------------------------------------------------------

  // construction
  track_channel_config(e_track_channel channel_,
                       float input_curvature_tolerance_deg_,
                       float input_velocity_tolerance_,
                       float output_distance_tolerance_,
                       float tangent_velocity_percent_)
    :channel(channel_)
    ,input_curvature_tolerance_deg(input_curvature_tolerance_deg_)
    ,input_velocity_tolerance(input_velocity_tolerance_)
    ,output_distance_tolerance(output_distance_tolerance_)
    ,tangent_velocity_percent(tangent_velocity_percent_)
    ,constraint(input_curvature_tolerance_deg_,
                input_velocity_tolerance_,
                output_distance_tolerance_,
                tangent_velocity_percent_)
  {
    // init channel min/max values
    min_start_pos.set(numeric_type<float>::range_max(), numeric_type<float>::range_max(), numeric_type<float>::range_max());
    max_start_pos.set(numeric_type<float>::range_min(), numeric_type<float>::range_min(), numeric_type<float>::range_min());
    min_delta_pos.set(numeric_type<float>::range_max(), numeric_type<float>::range_max(), numeric_type<float>::range_max());
    max_delta_pos.set(numeric_type<float>::range_min(), numeric_type<float>::range_min(), numeric_type<float>::range_min());
    min_segment_tangent.set(numeric_type<float>::range_max(), numeric_type<float>::range_max(), numeric_type<float>::range_max());
    max_segment_tangent.set(numeric_type<float>::range_min(), numeric_type<float>::range_min(), numeric_type<float>::range_min());
  }
  //--------------------------------------------------------------------------

  const e_track_channel channel;
  const float input_curvature_tolerance_deg;
  const float input_velocity_tolerance;
  const float output_distance_tolerance;
  const float tangent_velocity_percent;
  spline_fit_constraint_vec<vec3f> constraint;
  // track set properties
  vec3f min_start_pos, max_start_pos;
  vec3f min_delta_pos, max_delta_pos;
  vec3f min_segment_tangent, max_segment_tangent;
  // de-quantization & quantization factors
  vec3f dq_start_pos_scale, q_start_pos_scale;
  vec3f dq_delta_pos_scale, q_delta_pos_scale;
  vec3f dq_segment_tangent_scale, q_segment_tangent_scale;
  vec3f current_pos;
  //--------------------------------------------------------------------------

  PFC_INLINE bool is_const_spline(const vec3f &min_pos_, const vec3f &max_pos_) const
  {
    // check if all values are within output distance tolerance from the average
    return norm2(max_pos_-min_pos_)<=sqr(2.0f*output_distance_tolerance);
  }

  PFC_INLINE bool is_null_spline(const vec3f &pos_) const
  {
    // check if the average is max distance tolerance from [0, 0, 0]
    return norm2(pos_)<=sqr(output_distance_tolerance);
  }

  PFC_INLINE void add_spline(const vec3f &start_pos_)
  {
    // update start position boundaries
    min_start_pos=min(min_start_pos, start_pos_);
    max_start_pos=max(max_start_pos, start_pos_);
  }

  PFC_INLINE void add_spline_segment(const hermite_key<vec3f> &hkey_)
  {
    // update spline segment boundaries
    vec3f delta_pos=hkey_.p1-hkey_.p0;
    min_delta_pos=min(min_delta_pos, delta_pos);
    max_delta_pos=max(max_delta_pos, delta_pos);
    min_segment_tangent=min(min_segment_tangent, hkey_.t0, hkey_.t1);
    max_segment_tangent=max(max_segment_tangent, hkey_.t0, hkey_.t1);
  }

  PFC_INLINE void init_quantization_factors(bool has_segments_, bool has_splines_)
  {
    // initialize quantization and de-quantization factors for compression
    if(!has_segments_)
      max_delta_pos=min_delta_pos=max_segment_tangent=min_segment_tangent=vec3f::s_zero;
    if(!has_splines_)
      max_start_pos=min_start_pos=vec3f::s_zero;
    dq_start_pos_scale=(max_start_pos-min_start_pos)/65535.0f;
    dq_delta_pos_scale=(max_delta_pos-min_delta_pos)/255.0f;
    dq_segment_tangent_scale=(max_segment_tangent-min_segment_tangent)/255.0f;
    q_start_pos_scale=rcp_z(dq_start_pos_scale);
    q_delta_pos_scale=rcp_z(dq_delta_pos_scale);
    q_segment_tangent_scale=rcp_z(dq_segment_tangent_scale);
  }

  PFC_INLINE void add_compressed_spline(compressed_spline<vec3f> &spline_, const hermite_key<vec3f> &hkey_)
  {
    // add new compressed spline
    spline_.start_pos=quantize<unaligned_uint16>(hkey_.p0, q_start_pos_scale, min_start_pos);
    spline_.start_tangent=quantize<uint8_t>(hkey_.t0, q_segment_tangent_scale, min_segment_tangent);
    current_pos=dequantize(spline_.start_pos, dq_start_pos_scale, min_start_pos);
  }

  PFC_INLINE void add_compressed_spline(compressed_const_spline<vec3f> &spline_, const vec3f &pos_)
  {
    // add new constant compressed spline
    spline_.start_pos=quantize<unaligned_uint16>(pos_, q_start_pos_scale, min_start_pos);
  }

  PFC_INLINE void add_compressed_segment(compressed_spline_segment<vec3f> &segment_, const hermite_key<vec3f> &hkey_)
  {
    // add new compressed spline segment
    segment_.end_tangent=quantize<uint8_t>(hkey_.t1, q_segment_tangent_scale, min_segment_tangent);
    segment_.delta_pos=quantize<uint8_t>(hkey_.p1-current_pos, q_delta_pos_scale, min_delta_pos);
    current_pos+=dequantize(segment_.delta_pos, dq_delta_pos_scale, min_delta_pos);
  }

  PFC_INLINE void add_compressed_segment(degenerated_compressed_spline_segment<vec3f> &segment_, const hermite_key<vec3f> &hkey_)
  {
    // add degenerated compressed spline segment for tangent discontinuity
    segment_.end_tangent=quantize<uint8_t>(hkey_.t0, q_segment_tangent_scale, min_segment_tangent);
  }
  //--------------------------------------------------------------------------

  static PFC_INLINE vec3f spline_start_value(const compressed_spline<vec3f> *spline_, const compressed_track_set &set_, const vec3f &default_)
  {
    // return spline start value
    return spline_?dequantize(spline_->start_pos, set_.m_pos_start_scale, set_.m_pos_start_bias):default_;
  }
  //----

  static PFC_INLINE void init_spline_segment(cubic_spline<vec3f> &cs_, const compressed_spline<vec3f> &spline_, const compressed_spline_segment<vec3f> &segment_, const compressed_track_set &set_)
  {
    // initialize cubic spline with given segment
    vec3f p1=dequantize(spline_.start_pos, set_.m_pos_start_scale, set_.m_pos_start_bias);
    vec3f t1=dequantize(spline_.start_tangent, set_.m_pos_tangent_scale, set_.m_pos_tangent_bias);
    vec3f p0=p1+dequantize(segment_.delta_pos, set_.m_pos_delta_scale, set_.m_pos_delta_bias);
    vec3f t0=dequantize(segment_.end_tangent, set_.m_pos_tangent_scale, set_.m_pos_tangent_bias);
    make_hermite_spline(cs_, p0, p1, t0, t1);
  }
  //----

  static PFC_INLINE void next_segment(vec3f &v_, const compressed_spline_segment<vec3f> &segment_, const compressed_track_set &set_)
  {
    // advance to the next segment
    v_+=dequantize(segment_.delta_pos, set_.m_pos_delta_scale, set_.m_pos_delta_bias);
  }
  //----

  static PFC_INLINE void dequantize_tangents(vec3f &t0_, vec3f &t1_, const tangent_t &prev_tan_, const compressed_spline_segment<vec3f> &segment_, const compressed_track_set &set_)
  {
    // dequantize tangents
    t1_=dequantize(prev_tan_, set_.m_pos_tangent_scale, set_.m_pos_tangent_bias);
    t0_=dequantize(segment_.end_tangent, set_.m_pos_tangent_scale, set_.m_pos_tangent_bias);
  }
  //--------------------------------------------------------------------------

private:
  track_channel_config(const track_channel_config&); // not implemented
  void operator=(const track_channel_config&); // not implemented
};
//--------------------------------------------------------------------------

template<>
struct compressed_track_set::track_channel_config<quatf>
{
  // config properties
  enum {max_spline_segments=127};
  enum {max_spline_segment_frames=127};
  typedef quatf key_type;
  typedef scaled_compressed_rotation32 tangent_t;
  //--------------------------------------------------------------------------

  // construction
  track_channel_config(e_track_channel channel_,
                       float input_curvature_tolerance_deg_,
                       float input_angular_velocity_tolerance_,
                       float output_angle_tolerance_deg_,
                       float tangent_angular_velocity_tolerance_percent_)
    :channel(channel_)
    ,input_curvature_tolerance_deg(input_curvature_tolerance_deg_)
    ,input_angular_velocity_tolerance(input_angular_velocity_tolerance_)
    ,output_angle_tolerance_deg(output_angle_tolerance_deg_)
    ,tangent_angular_velocity_tolerance_percent(tangent_angular_velocity_tolerance_percent_)
    ,constraint(input_curvature_tolerance_deg_,
                input_angular_velocity_tolerance_,
                output_angle_tolerance_deg_,
                tangent_angular_velocity_tolerance_percent_)
  {
    min_segment_tangent_norm=numeric_type<float>::range_max();
    max_segment_tangent_norm=numeric_type<float>::range_min();
  }
  //--------------------------------------------------------------------------

  const e_track_channel channel;
  const float input_curvature_tolerance_deg;
  const float input_angular_velocity_tolerance;
  const float output_angle_tolerance_deg;
  const float tangent_angular_velocity_tolerance_percent;
  spline_fit_constraint_quat<quatf> constraint;
  // track set properties
  float min_segment_tangent_norm, max_segment_tangent_norm;
  // de-quantization & quantization factors
  float dq_segment_tangent_norm_scale, q_segment_tangent_norm_scale;
  //--------------------------------------------------------------------------

  PFC_INLINE bool is_const_spline(const quatf &min_rot_, const quatf &max_rot_) const
  {
    // check if all values are within output distance tolerance from the average
    return dot(min_rot_, max_rot_)>=norm(min_rot_)*norm(max_rot_)*cos(2.0f*output_angle_tolerance_deg*mathf::deg_to_rad);
  }

  PFC_INLINE bool is_null_spline(const quatf &rot_) const
  {
    // check if the average is max distance tolerance from [0, 0, 0]
    return sqr(rot_.w)>=norm2(rot_)*sqr(cos(output_angle_tolerance_deg*mathf::deg_to_rad));
  }

  PFC_INLINE void add_spline(const quatf &start_pos_)
  {
  }

  PFC_INLINE void add_spline_segment(const hermite_key<quatf> &hkey_)
  {
    // update spline segment tangent norm boundaries
    ufloat_t nt0=norm(hkey_.t0);
    ufloat_t nt1=norm(hkey_.t1);
    min_segment_tangent_norm=min(min_segment_tangent_norm, nt0, nt1);
    max_segment_tangent_norm=max(max_segment_tangent_norm, nt0, nt1);
  }

  PFC_INLINE void init_quantization_factors(bool has_segments_, bool has_splines_)
  {
    // initialize quantization and de-quantization factors for compression
    if(!has_segments_)
      max_segment_tangent_norm=min_segment_tangent_norm=0.0f;
    dq_segment_tangent_norm_scale=(max_segment_tangent_norm-min_segment_tangent_norm)/127.0f;
    q_segment_tangent_norm_scale=rcp_z(dq_segment_tangent_norm_scale);
  }

  PFC_INLINE void add_compressed_spline(compressed_spline<quatf> &spline_, const hermite_key<quatf> &hkey_)
  {
    // add new compressed spline
    spline_.start_rot_sign=spline_.start_rot.init_precise(hkey_.p0);
    spline_.start_tangent.sign=spline_.start_tangent.rot.init_precise(unit_z(hkey_.t0));
    spline_.start_tangent.scale=uint8_t((norm(hkey_.t0)-min_segment_tangent_norm)*q_segment_tangent_norm_scale+0.5f);
  }

  PFC_INLINE void add_compressed_spline(compressed_const_spline<quatf> &spline_, const quatf &rot_)
  {
    // add new constant compressed spline
    spline_.start_rot_sign=spline_.start_rot.init_precise(rot_);
  }

  PFC_INLINE void add_compressed_segment(compressed_spline_segment<quatf> &segment_, const hermite_key<quatf> &hkey_)
  {
    // add new compressed spline segment
    segment_.end_tangent.sign=segment_.end_tangent.rot.init_precise(unit_z(hkey_.t1));
    segment_.end_tangent.scale=uint8_t((norm(hkey_.t1)-min_segment_tangent_norm)*q_segment_tangent_norm_scale+0.5f);
    segment_.end_rot_sign=segment_.end_rot.init_precise(hkey_.p1);
  }

  PFC_INLINE void add_compressed_segment(degenerated_compressed_spline_segment<quatf> &segment_, const hermite_key<quatf> &hkey_)
  {
    // add degenerated compressed spline segment for tangent discontinuity
    segment_.end_tangent.sign=segment_.end_tangent.rot.init_precise(unit_z(hkey_.t0));
    segment_.end_tangent.scale=uint8_t((norm(hkey_.t0)-min_segment_tangent_norm)*q_segment_tangent_norm_scale+0.5f);
  }
  //--------------------------------------------------------------------------

  static PFC_INLINE quatf spline_start_value(const compressed_spline<quatf> *spline_, const compressed_track_set &set_, const quatf &default_)
  {
    // return spline start value
    return spline_?axis_rot_u(spline_->start_rot.axis(), spline_->start_rot.angle())*(spline_->start_rot_sign?-1.0f:1.0f):default_;
  }
  //----

  static PFC_INLINE void init_spline_segment(cubic_spline<quatf> &cs_, const compressed_spline<quatf> &spline_, const compressed_spline_segment<quatf> &segment_, const compressed_track_set &set_)
  {
    // initialize cubic spline with given segment
    quatf p1=axis_rot_u(spline_.start_rot.axis(), spline_.start_rot.angle())*(spline_.start_rot_sign?-1.0f:1.0f);
    quatf p0=axis_rot_u(segment_.end_rot.axis(), segment_.end_rot.angle())*(segment_.end_rot_sign?-1.0f:1.0f);
    quatf t1=axis_rot_u(spline_.start_tangent.rot.axis(), spline_.start_tangent.rot.angle())*(spline_.start_tangent.scale*set_.m_rot_tangent_norm_scale+set_.m_rot_tangent_norm_bias)*(spline_.start_tangent.sign?-1.0f:1.0f);
    quatf t0=axis_rot_u(segment_.end_tangent.rot.axis(), segment_.end_tangent.rot.angle())*(segment_.end_tangent.scale*set_.m_rot_tangent_norm_scale+set_.m_rot_tangent_norm_bias)*(segment_.end_tangent.sign?-1.0f:1.0f);
    make_hermite_spline(cs_, p0, p1, t0, t1);
  }
  //----

  static PFC_INLINE void next_segment(quatf &v_, const compressed_spline_segment<quatf> &segment_, const compressed_track_set&)
  {
    // advance to the next segment
    v_=axis_rot_u(segment_.end_rot.axis(), segment_.end_rot.angle())*(segment_.end_rot_sign?-1.0f:1.0f);
  }
  //----

  static PFC_INLINE void dequantize_tangents(quatf &t0_, quatf &t1_, const tangent_t &prev_tan_, const compressed_spline_segment<quatf> &segment_, const compressed_track_set &set_)
  {
    // dequantize spline segment tangents
    t0_=axis_rot_u(segment_.end_tangent.rot.axis(), segment_.end_tangent.rot.angle())*((segment_.end_tangent.scale*set_.m_rot_tangent_norm_scale+set_.m_rot_tangent_norm_bias)*(segment_.end_tangent.sign?-1.0f:1.0f));
    t1_=axis_rot_u(prev_tan_.rot.axis(), prev_tan_.rot.angle())*((prev_tan_.scale*set_.m_rot_tangent_norm_scale+set_.m_rot_tangent_norm_bias)*(prev_tan_.sign?-1.0f:1.0f));
  }
  //--------------------------------------------------------------------------

private:
  track_channel_config(const track_channel_config&); // not implemented
  void operator=(const track_channel_config&); // not implemented
};
//----------------------------------------------------------------------------
} // namespace pfc


//============================================================================
// compressed_track_set::const_iterator
//============================================================================
template<typename T>
void compressed_track_set::const_iterator<T>::init(const compressed_track_set &set_, e_track_channel channel_, unsigned track_index_, const T &default_, float start_time_)
{
  const compressed_spline<T> *spline=(const compressed_spline<T>*)set_.track_channel_data(channel_, track_index_);
  if(spline && spline->num_segments)
  {
    // setup the first spline segment
    const compressed_spline_segment<T> *segment=(const compressed_spline_segment<T>*)(spline+1);
    m_data=segment;
    m_num_segments_left=spline->num_segments-1;
    float segment_time=segment->segment_frames*set_.m_spf;
    m_segment_end=floor((start_time_+segment_time)*set_.m_fps+0.5f)*set_.m_spf;
    track_channel_config<T>::init_spline_segment(m_segment, *spline, *segment, set_);
    float segment_rtime=1.0f/segment_time, segment_rtime2=segment_rtime*segment_rtime;
    m_segment.a*=segment_rtime2*segment_rtime;
    m_segment.b*=segment_rtime2;
    m_segment.c*=segment_rtime;
  }
  else
  {
    // setup constant spline segment
    unsigned num_frames=set_.m_variable_track_times?set_.num_frames(track_index_):set_.m_num_frames;
    m_segment_end=floor(num_frames+start_time_*set_.m_fps+0.5f)*set_.m_spf;
    m_segment.a.set(0.0f);
    m_segment.c=m_segment.b=m_segment.a;
    m_segment.d=track_channel_config<T>::spline_start_value(spline, set_, default_);
    m_data=0;
    m_num_segments_left=0;
  }
}
//----

template<typename T>
void compressed_track_set::const_iterator<T>::init(const T &v_, ufloat_t time_, float start_time_)
{
  // init iterator with constant value for given period of time
  m_segment_end=time_+start_time_;
  m_segment.a.set(0.0f);
  m_segment.c=m_segment.b=m_segment.a;
  m_segment.d=v_;
  m_data=0;
  m_num_segments_left=0;
}
//----

template<typename T>
void compressed_track_set::const_iterator<T>::init(const T &v_)
{
  // init iterator with infinite constant value
  m_segment_end=numeric_type<float>::range_max();
  m_segment.a.set(0.0f);
  m_segment.c=m_segment.b=m_segment.a;
  m_segment.d=v_;
  m_data=0;
  m_num_segments_left=0;
}
//----------------------------------------------------------------------------

template<typename T>
bool compressed_track_set::const_iterator<T>::find_segment(ufloat_t &seg_time_, ufloat_t time_, const compressed_track_set &set_)
{
  // find the spline segment for the given time value
  float t;
  const compressed_spline_segment<T> *segment=(const compressed_spline_segment<T>*)m_data;
  float segment_time;
  T p0=m_segment.d, p1;
  const typename track_channel_config<T>::tangent_t *prev_tan;
  do
  {
    // check for the last spline segment
    if(!m_num_segments_left)
      return false;
    --m_num_segments_left;

    // check for degenerated spline segment (spline tangent discontinuity)
    prev_tan=&segment->end_tangent;
    ++segment;
    if(!segment->segment_frames)
    {
      prev_tan=&segment->end_tangent;
      (uint8_t*&)segment+=sizeof(degenerated_compressed_spline_segment<T>);
    }

    // setup segment end time & update segment start & end positions
    segment_time=segment->segment_frames*set_.m_spf;
    m_segment_end=floor((m_segment_end+segment_time)*set_.m_fps+0.5f)*set_.m_spf;
    t=m_segment_end-time_;
    p1=p0;
    track_channel_config<T>::next_segment(p0, *segment, set_);
  } while(t<0.0f);
  m_data=segment;
  seg_time_=t;

  // extract Hermite spline segment tangents and setup the segment
  T t0, t1;
  track_channel_config<T>::dequantize_tangents(t0, t1, *prev_tan, *segment, set_);
  make_hermite_spline(m_segment, p0, p1, t0, t1);
  float segment_rtime=1.0f/segment_time, segment_rtime2=segment_rtime*segment_rtime;
  m_segment.a*=segment_rtime2*segment_rtime;
  m_segment.b*=segment_rtime2;
  m_segment.c*=segment_rtime;
  return true;
}
//----------------------------------------------------------------------------

// explicitly instantiate compressed_track_set iterators
template class compressed_track_set::const_iterator<vec3f>;
template class compressed_track_set::const_iterator<quatf>;
//----------------------------------------------------------------------------


//============================================================================
// compressed_track_set
//============================================================================
PFC_CLASS_DEF(compressed_track_set);
//----------------------------------------------------------------------------

compressed_track_set::compressed_track_set()
{
  init_members();
}
//----

compressed_track_set::compressed_track_set(const track_set &set_, const track_set_splinify_settings &settings_)
{
  init(set_, settings_);
}
//----

void compressed_track_set::init(const track_set &set_, const track_set_splinify_settings &settings_)
{
  // basic initialization
  init_members();
  m_num_tracks=set_.num_tracks();
  m_variable_track_times=set_.variable_track_times();
  m_start_frame=set_.start_frame();
  m_num_frames=set_.num_frames();
  bool has_channel_position=set_.has_channel(trackchannel_position);
  bool has_channel_rotation=set_.has_channel(trackchannel_rotation);
  unsigned num_channels=unsigned(has_channel_position)+unsigned(has_channel_rotation);

  // setup initial track channel data container
  unsigned channel_offset_writepos=0;
  unsigned channel_offset_size=m_num_tracks*num_channels*sizeof(channel_offset);
  unsigned channel_data_writepos=channel_offset_size;
  if(m_variable_track_times)
  {
    // setup track times
    unsigned track_time_size=m_num_tracks*sizeof(track_times);
    m_track_channel_data.resize(channel_offset_size+track_time_size);
    const track_info *tinfos=set_.track_infos();
    track_times *ttimes=(track_times*)(m_track_channel_data.data()+channel_offset_size);
    for(unsigned i=0; i<m_num_tracks; ++i)
    {
      PFC_ASSERT_MSG(tinfos[i].start_frame<65536, ("Track start frame (%i) must be less than 65536\r\n", tinfos[i].start_frame));
      PFC_ASSERT_MSG(tinfos[i].num_frames<65536, ("Number of track frames (%i) must be less than 65536\r\n", tinfos[i].num_frames));
      ttimes[i].start_frame=uint16_t(tinfos[i].start_frame);
      ttimes[i].num_frames=uint16_t(tinfos[i].num_frames);
    }
    channel_data_writepos+=track_time_size;
  }
  else
    m_track_channel_data.resize(channel_offset_size);

  // compress channels
  if(has_channel_position)
  {
    track_channel_config<vec3f> cfg(trackchannel_position,
                                    settings_.pos_input_curvature_tolerance_deg,
                                    settings_.pos_input_velocity_tolerance,
                                    settings_.pos_output_distance_tolerance,
                                    settings_.pos_tangent_velocity_tolerance_percent);
    compress_channel(cfg, set_, channel_offset_writepos, channel_data_writepos);
    m_pos_start_scale=cfg.dq_start_pos_scale;
    m_pos_start_bias=cfg.min_start_pos;
    m_pos_delta_scale=cfg.dq_delta_pos_scale;
    m_pos_delta_bias=cfg.min_delta_pos;
    m_pos_tangent_scale=-cfg.dq_segment_tangent_scale;
    m_pos_tangent_bias=-cfg.min_segment_tangent;
  }
  if(has_channel_rotation)
  {
    track_channel_config<quatf> cfg(trackchannel_rotation,
                                    settings_.rot_input_angular_velocity_tolerance,
                                    settings_.rot_input_curvature_tolerance_deg,
                                    settings_.rot_output_angle_tolerance_deg,
                                    settings_.rot_tangent_angular_velocity_tolerance_percent);
    compress_channel(cfg, set_, channel_offset_writepos, channel_data_writepos);
    m_rot_tangent_norm_scale=-cfg.dq_segment_tangent_norm_scale;
    m_rot_tangent_norm_bias=-cfg.min_segment_tangent_norm;
  }

  // init track set info
  m_fps=set_.fps();
  m_spf=set_.spf();
}
//----------------------------------------------------------------------------

void compressed_track_set::init_members()
{
  // initialize member variables
  m_channels.clear();
  m_num_tracks=0;
  m_fps=0.0f;
  m_spf=0.0f;
  m_start_frame=0;
  m_num_frames=0;
  m_variable_track_times=false;
  m_track_channel_data.clear();
  m_pos_start_scale.set(0.0f);
  m_pos_start_bias.set(0.0f);
  m_pos_delta_scale.set(0.0f);
  m_pos_delta_bias.set(0.0f);
  m_pos_tangent_scale.set(0.0f);
  m_pos_tangent_bias.set(0.0f);
  m_rot_tangent_norm_scale=0.0f;
  m_rot_tangent_norm_bias=0.0f;
}
//----

template<class Cfg>
void compressed_track_set::compress_channel(Cfg &cfg_, const track_set &set_, unsigned &channel_offset_writepos_, unsigned &channel_data_writepos_)
{
  // config typedefs & enums
  typedef typename Cfg::key_type key_type;
  typedef compressed_spline<key_type> compressed_spline;
  typedef compressed_const_spline<key_type> compressed_const_spline;
  typedef compressed_spline_segment<key_type> compressed_spline_segment;
  typedef degenerated_compressed_spline_segment<key_type> degenerated_compressed_spline_segment;
  enum {max_spline_segments=Cfg::max_spline_segments};
  enum {max_spline_segment_frames=Cfg::max_spline_segment_frames};

  // add new track channel
  m_channels.push_back(cfg_.channel);

  // generate Hermite splines for all tracks
  cubic_spline<key_type> spline_buf[max_spline_segments];
  unsigned spline_length_buf[max_spline_segments];
  deque<hermite_key<key_type> > hermite_keys;
  array<unsigned> num_spline_segments(m_num_tracks);
  const track_info *tinfos=set_.track_infos();
  const void *cdata=set_.channel_data();
  unsigned num_total_segments=0;
  unsigned num_total_degenerated_segments=0;
  unsigned num_const_splines=0;
  for(unsigned ti=0; ti<m_num_tracks; ++ti)
  {
    // find position channel for the track
    const track_info &tinfo=tinfos[ti];
    PFC_CHECK(tinfo.num_frames);
    const track_channel_info *cinfo=set_.find_channel_info(tinfo, cfg_.channel);
    if(!cinfo)
    {
      // add null track channel
      num_spline_segments[ti]=unsigned(-1);
      continue;
    }

    // switch to proper channel format handling
    switch(int(cinfo->format))
    {
      // constant channel format
      case trackchannelformat_constant:
      {
        // check for null track channel
        const key_type *key=(const key_type*)((const uint8_t*)cdata+cinfo->data_offset);
        if(cfg_.is_null_spline(*key))
        {
          num_spline_segments[ti]=unsigned(-1);
          break;
        }

        // store constant track channel
        num_spline_segments[ti]=0;
        hermite_key<key_type> hkey={0, false, *key};
        hermite_keys.push_back(hkey);
        cfg_.add_spline(*key);
        ++num_const_splines;
      } break;

      // sample channel format
      case trackchannelformat_sample:
      {
        // check for constant spline (all keys within the output distance threshold)
        const key_type *keys=(const key_type*)((const uint8_t*)cdata+cinfo->data_offset);
        key_type min_key=*keys, max_key=*keys;
        unsigned num_keys=tinfo.num_frames+1;
        for(unsigned i=1; i<num_keys; ++i)
        {
          min_key=min(min_key, keys[i]);
          max_key=max(max_key, keys[i]);
        }

        // check for constant spline
        if(cfg_.is_const_spline(min_key, max_key))
        {
          // check for null track channel
          key_type key_avg=(min_key+max_key)*0.5f;
          if(cfg_.is_null_spline(key_avg))
          {
            num_spline_segments[ti]=unsigned(-1);
            break;
          }

          // store constant track channel
          num_spline_segments[ti]=0;
          hermite_key<key_type> hkey={0, false, key_avg};
          hermite_keys.push_back(hkey);
          cfg_.add_spline(key_avg);
          ++num_const_splines;
          break;
        }

        // fit spline to track position channel keys
        cfg_.constraint.init_buffers(spline_buf, spline_length_buf, max_spline_segments);
        unsigned num_segments=fit_spline<key_type>(keys, num_keys, cfg_.constraint, max_spline_segment_frames);
        PFC_CHECK_MSG(num_segments, ("Input data generates too many cubic spline segments\r\n"));
        num_spline_segments[ti]=num_segments;
        num_total_segments+=num_segments;
        cfg_.add_spline(spline_buf[0].d);
        for(unsigned i=0; i<num_segments; ++i)
        {
          // setup Hermite key for the spline segment
          hermite_key<key_type> hkey;
          hkey.num_frames=spline_length_buf[i];
          hkey.merge_tangent=true;
          get_hermite_spline_keys(hkey.p0, hkey.p1, hkey.t0, hkey.t1, spline_buf[i]);

          // check for tangent discontinuity in the spline /*todo: improve tangent merging for better quality*/
          if(i && !cfg_.constraint.tangent_constraints(hermite_keys.back().t1, hkey.t0))
          {
            ++num_total_degenerated_segments;
            hkey.merge_tangent=false;
          }

          // add new Hermite key
          hermite_keys.push_back(hkey);
          cfg_.add_spline_segment(hkey);
        }
      } break;

      // Hermite spline channel
      case trackchannelformat_hermite:
      {
        // calculate spline bounds
        const key_type *start_key=(const key_type*)((const uint8_t*)cdata+cinfo->data_offset);
        const track_key_hermite<key_type> *keys=(const track_key_hermite<key_type>*)(start_key+1);
        unsigned num_spline_frames=tinfo.num_frames;
        unsigned num_input_segments=0;
        key_type spline_min, spline_max, p0=*start_key;
        for(unsigned frame_idx=0; frame_idx<num_spline_frames; frame_idx+=keys[num_input_segments++].num_frames)
        {
          // update spline bounds with the segment bounds
          const track_key_hermite<key_type> &key=keys[num_input_segments];
          key_type segment_min, segment_max;
          cubic_spline<key_type> spline;
          make_hermite_spline(spline, p0, key.p1, key.t0, key.t1);
          spline_bounds(segment_min, segment_max, spline);
          spline_min=frame_idx?min(spline_min, segment_min):segment_min;
          spline_max=frame_idx?max(spline_max, segment_max):segment_max;
        }

        // check for constant track
        if(cfg_.is_const_spline(spline_min, spline_max))
        {
          // check for null track channel
          key_type spline_avg=(spline_min+spline_max)*0.5f;
          if(cfg_.is_null_spline(spline_avg))
          {
            num_spline_segments[ti]=unsigned(-1);
            break;
          }

          // store constant track channel
          num_spline_segments[ti]=0;
          hermite_key<key_type> hkey={0, false, spline_avg};
          hermite_keys.push_back(hkey);
          cfg_.add_spline(spline_avg);
          ++num_const_splines;
          break;
        }

        // add Hermite spline segments for the track channel
        p0=*start_key;
        cfg_.add_spline(p0);
        unsigned num_total_spline_segments=0;
        for(unsigned i=0; i<num_input_segments; ++i)
        {
          // split spline segment to multiple sub-segments if longer than max spline segment length
          cubic_spline<key_type> spline;
          unsigned subsegment_start_frame=0;
          unsigned num_segment_frames=keys[i].num_frames;
          unsigned num_segment_frames_left=num_segment_frames;
          float rcp_segment_len=1.0f/num_segment_frames;
          while(num_segment_frames_left)
          {
            // setup Hermite key for the segment
            unsigned num_subsegment_frames=min(num_segment_frames_left, unsigned(max_spline_segment_frames));
            hermite_key<key_type> hkey;
            hkey.num_frames=num_subsegment_frames;
            const track_key_hermite<key_type> &key=keys[i];
            if(num_subsegment_frames==num_segment_frames)
            {
              // setup Hermite spline control values
              hkey.p0=p0;
              hkey.p1=key.p1;
              hkey.t0=key.t0;
              hkey.t1=key.t1;
              p0=key.p1;
            }
            else
            {
              // reparametrize Hermite spline for the segment
              cubic_spline<key_type> sub_spline;
              if(!i)
                make_hermite_spline(spline, p0, key.p1, key.t0, key.t1);
              reparametrize_spline(sub_spline, spline, num_subsegment_frames*rcp_segment_len, subsegment_start_frame*rcp_segment_len);
              get_hermite_spline_keys(hkey.p0, hkey.p1, hkey.t0, hkey.t1, sub_spline);
            }

            // check for tangent continuity
            hkey.merge_tangent=true;
            if(i && !subsegment_start_frame && !cfg_.constraint.tangent_constraints(hermite_keys.back().t1, hkey.t0))
            {
              ++num_total_degenerated_segments;
              hkey.merge_tangent=false;
            }

            // add new Hermite spline segment and proceed to the next spline segment
            hermite_keys.push_back(hkey);
            cfg_.add_spline_segment(hkey);
            ++num_total_spline_segments;
            num_segment_frames_left-=num_subsegment_frames;
            subsegment_start_frame+=num_subsegment_frames;
          }
        }

        // update spline segment counts
        num_spline_segments[ti]=num_total_spline_segments;
        num_total_segments+=num_total_spline_segments;
      } break;
    }
  }

  // quantize generated Hermite splines
  cfg_.init_quantization_factors(num_total_segments!=0, num_total_segments || num_const_splines);
  channel_offset *channel_offsets=(channel_offset*)(m_track_channel_data.data())+channel_offset_writepos_;
  array<uint8_t> compressed_track_data( (m_num_tracks-num_const_splines)*sizeof(compressed_spline)
                                     +num_const_splines*sizeof(compressed_const_spline)
                                     +num_total_segments*sizeof(compressed_spline_segment)
                                     +num_total_degenerated_segments*sizeof(degenerated_compressed_spline_segment));
  unsigned hcbi=0;
  compressed_spline *spline=(compressed_spline*)(compressed_track_data.data());
  for(unsigned ti=0; ti<m_num_tracks; ++ti)
  {
    // check for null track channel
    unsigned num_segments=num_spline_segments[ti];
    if(num_segments==unsigned(-1))
    {
      *channel_offsets++=channel_offset(null_channel_offset);
      continue;
    }

    // check for constant track channel
    const hermite_key<key_type> &hkey_start=hermite_keys[hcbi];
    *channel_offsets++=channel_offset((uint8_t*)spline-(uint8_t*)(compressed_track_data.data()))+channel_data_writepos_;
    spline->num_segments=uint8_t(num_segments);
    if(!num_segments)
    {
      // add constant track channel
      cfg_.add_compressed_spline((compressed_const_spline&)*spline, hkey_start.p0);
      spline=(compressed_spline*)(((compressed_const_spline*)spline)+1);
      ++hcbi;
      continue;
    }

    // add compressed spline and segments for the spline
    cfg_.add_compressed_spline(*spline, hkey_start);
    compressed_spline_segment *segment=(compressed_spline_segment*)(spline+1);
    for(unsigned i=0; i<num_segments; ++i)
    {
      const hermite_key<key_type> &hkey=hermite_keys[hcbi+i];
      if(!hkey.merge_tangent)
      {
        // add degenerated key for discontinued spline tangent
        segment->segment_frames=0;
        cfg_.add_compressed_segment((degenerated_compressed_spline_segment&)*segment, hkey);
        (uint8_t*&)segment+=sizeof(degenerated_compressed_spline_segment);
      }

      // add compressed segment for the spline segment
      segment->segment_frames=uint8_t(hkey.num_frames);
      cfg_.add_compressed_segment(*segment, hkey);
      ++segment;
    }

    // proceed to the next spline
    spline=(compressed_spline*)segment;
    hcbi+=num_segments;
  }

  // add compressed track channel data to the track set
  channel_data_writepos_+=channel_offset((uint8_t*)spline-(uint8_t*)(compressed_track_data.data()));
  channel_offset_writepos_+=m_num_tracks;
  m_track_channel_data.insert_back(compressed_track_data.size(), compressed_track_data.data());
}
//----------------------------------------------------------------------------
