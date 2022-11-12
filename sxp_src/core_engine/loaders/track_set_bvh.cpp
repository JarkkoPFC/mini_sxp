//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "sxp_src/core_engine/track_set.h"
using namespace pfc;
//----------------------------------------------------------------------------


#ifdef PFC_ENGINEOP_BVH
//============================================================================
// track_set_loader_bvh
//============================================================================
class track_set_loader_bvh
{
public:
  // loading
  void load(track_set&, bin_input_stream_base&);
  //--------------------------------------------------------------------------

private:
  void parse_hierarchy(text_input_stream&, char *buffer_);
  void parse_motion(text_input_stream&, char *buffer_);
  //--------------------------------------------------------------------------

  //==========================================================================
  // joint
  //==========================================================================
  enum {chl_none, chl_xpos, chl_ypos, chl_zpos, chl_xrot, chl_yrot, chl_zrot};
  struct joint
  {
    PFC_INLINE joint() {mem_zero(channels, sizeof(channels));}
    heap_str name;
    uint8_t channels[6];
  };
  //--------------------------------------------------------------------------

  enum {txt_buffer_size=1024};
  deque<joint> m_joints;
  unsigned m_num_total_channels;
};
//----------------------------------------------------------------------------
/*
bool track_set_loader_bvh::check_format(bin_input_stream_base &stream_)
{
  // check for BVH file
  auto_stream_seek<bin_input_stream_base> aseek(stream_);
  char id[9];
  stream_.read(id, 9);
  return mem_eq(id, "HIERARCHY", 9);
}
//----*/

void track_set_loader_bvh::load(track_set &tset_, bin_input_stream_base &stream_)
{
  m_num_total_channels=0;
  text_input_stream txt_stream(stream_);
  txt_stream.skip_line();
  char buf[txt_buffer_size];
  parse_hierarchy(txt_stream, buf);
  parse_motion(txt_stream, buf);
}
//----------------------------------------------------------------------------

void track_set_loader_bvh::parse_hierarchy(text_input_stream &txt_stream_, char *buffer_)
{
  while(!txt_stream_.is_eos())
  {
    // read str and switch to proper ID parsing
    unsigned str_len=(unsigned)txt_stream_.read_word(buffer_, txt_buffer_size);
    switch(str_len)
    {
      // 1 character ID
      case 1:
        if(*buffer_=='}')
          return;
      // 3 character ID
      case 3:
        if(mem_eq(buffer_, "End", 3))
        {
          // skip "End" structure
          txt_stream_.skip_to('{', true);
          txt_stream_.skip_to('}', true);
          break;
        }
        PFC_ERROR(("Unknown BVH file structure ID \"%s\"\r\n", buffer_));
      // 4 & 5 character IDs
      case 4:
      case 5:
      {
        bool is_root=false;
        if(mem_eq(buffer_, "JOINT", 5) || (is_root=mem_eq(buffer_, "ROOT", 4))==true)
        {
          // read joint name and recursively parse child joints
          txt_stream_.read_word(buffer_, txt_buffer_size);
          joint &j=m_joints.push_back();
          j.name=buffer_;
          txt_stream_.skip_to('{', true);
          parse_hierarchy(txt_stream_, buffer_);
          if(is_root)
            return;
          break;
        }
        PFC_ERROR(("Unknown BVH file structure ID \"%s\"\r\n", buffer_));
      }
      // 6 character ID
      case 6:
        if(mem_eq(buffer_, "OFFSET", 6))
        {
          txt_stream_.skip_line();
          break;
        }
        PFC_ERROR(("Unknown BVH file structure ID \"%s\"\r\n", buffer_));
      // 8 character ID
      case 8:
        if(mem_eq(buffer_, "CHANNELS", 8))
        {
          // read joint data channels
          unsigned num_chl;
          txt_stream_>>num_chl;
          joint &j=m_joints.back();
          for(unsigned i=0; i<num_chl; ++i)
          {
            txt_stream_.read_word(buffer_, txt_buffer_size);
            if(mem_eq(buffer_, "Xposition", 9))
              j.channels[i]=chl_xpos;
            else if(mem_eq(buffer_, "Yposition", 9))
              j.channels[i]=chl_ypos;
            else if(mem_eq(buffer_, "Zposition", 9))
              j.channels[i]=chl_zpos;
            else if(mem_eq(buffer_, "Xrotation", 9))
              j.channels[i]=chl_xrot;
            else if(mem_eq(buffer_, "Yrotation", 9))
              j.channels[i]=chl_yrot;
            else if(mem_eq(buffer_, "Zrotation", 9))
              j.channels[i]=chl_zrot;
            else
              PFC_ERROR(("Unknown joint channel type \"%s\"\r\n", buffer_));
            ++m_num_total_channels;
          }
          break;
        }
        PFC_ERROR(("Unknown BVH file structure ID \"%s\"\r\n", buffer_));
      default: PFC_ERROR(("Unknown BVH file structure ID \"%s\"\r\n", buffer_));
    }
  }
}
//----

void track_set_loader_bvh::parse_motion(text_input_stream &txt_stream_, char *buffer_)
{
  // skip to "MOTION" tag
  do
    txt_stream_.read_line(buffer_, txt_buffer_size);
  while(!mem_eq(buffer_, "MOTION", 6));
  
  /*todo*/
  PFC_ERROR_NOT_IMPL();
}
//----------------------------------------------------------------------------


//============================================================================
// load_track_set_bvh
//============================================================================
namespace pfc
{
  bool load_track_set_bvh(track_set &tset_, bin_input_stream_base &stream_)
  {
    // check for BVH file format
    {
      char id[9];
      stream_.read(id, 9);
      stream_.rewind(9);
      if(!mem_eq(id, "HIERARCHY", 9))
        return false;
    }

    // load track set
    track_set_loader_bvh loader;
    loader.load(tset_, stream_);
    return true;
  }
} // namespace pfc
//----------------------------------------------------------------------------

#else // PFC_ENGINEOP_BVH
namespace pfc
{
  bool load_track_set_bvh(track_set &ts_, bin_input_stream_base &stream_)
  {
    return false;
  }
} // namespace pfc
//----------------------------------------------------------------------------
#endif // !PFC_ENGINEOP_BVH
