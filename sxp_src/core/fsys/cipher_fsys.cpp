//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "cipher_fsys.h"
#include "sxp_src/core/math/bit_math.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// cipher_file_system::input_stream
//============================================================================
class cipher_file_system::input_stream: public bin_input_stream_base
{
public:
  // construction
  input_stream(const cipher_file_system&, const owner_ref<bin_input_stream_base>&);
  //--------------------------------------------------------------------------

private:
  input_stream(const input_stream&); // not implemented
  void operator=(const input_stream&); // not implemented
  //--------------------------------------------------------------------------

  // implementation
  virtual usize_t update_buffer_impl(void*, usize_t num_bytes_, bool exact_);
  virtual void rewind_impl();
  virtual void rewind_impl(usize_t num_bytes_);
  virtual void skip_impl();
  virtual void seek_impl(usize_t abs_pos_);
  //--------------------------------------------------------------------------

  enum {buffer_4size=256, buffer_size=buffer_4size*4};
  enum {align_mask=3};
  owner_ref<bin_input_stream_base> m_stream;
  uint32_t m_cipher_key0[8];
  uint32_t m_cipher_key1[8];
  uint32_t m_buffer[buffer_4size];
};
//----------------------------------------------------------------------------

cipher_file_system::input_stream::input_stream(const cipher_file_system &fsys_, const owner_ref<bin_input_stream_base> &stream_)
  :m_stream(stream_)
{
  // setup stream and cipher keys
  m_is_last=m_stream.data->is_eos();
  mem_copy(m_cipher_key0, fsys_.m_cipher_key0, sizeof(m_cipher_key0));
  mem_copy(m_cipher_key1, fsys_.m_cipher_key1, sizeof(m_cipher_key1));
}
//----------------------------------------------------------------------------

usize_t cipher_file_system::input_stream::update_buffer_impl(void *p_, usize_t num_bytes_, bool exact_)
{
  // read data in batches from the stream
  usize_t num_bytes_read=0;
  while(num_bytes_)
  {
    // read encrypted data batch to buffer and decrypt the buffer
    usize_t data_align=m_begin_pos&align_mask;
    m_begin_pos+=usize_t(m_end-m_begin)-data_align;
    usize_t num_buf_bytes=m_stream.data->read_bytes(m_buffer, buffer_size, false);
    PFC_CHECK_MSG(!exact_ || num_buf_bytes==buffer_size || num_buf_bytes>=num_bytes_, ("Trying to read beyond end of the cipher stream\r\n"));
    m_data=m_begin=(const uint8_t*)m_buffer;
    m_data+=data_align;
    m_end=m_begin+num_buf_bytes;
    if(num_buf_bytes==data_align)
      break;
    const usize_t buf_4size=(num_buf_bytes+3)/4;
    usize_t pos=(m_begin_pos/4)+*m_cipher_key0;
    for(usize_t i=0; i<buf_4size; ++i)
    {
      m_buffer[i]^=to_little_endian(pos*m_cipher_key0[pos&7]+(pos/32)*m_cipher_key1[pos&7]);
      ++pos;
    }

    // copy a batch of decrypted data from the buffer to the target
    usize_t num_batch_bytes=min(num_bytes_, num_buf_bytes-data_align);
    mem_copy(p_, m_data, num_batch_bytes);
    m_data+=num_batch_bytes;
    (uint8_t*&)p_+=num_batch_bytes;
    num_bytes_-=num_batch_bytes;
    num_bytes_read+=num_batch_bytes;
  }

  // setup stream and return the number of read bytes
  m_is_first=false;
  m_is_last=m_stream.data->is_eos();
  return num_bytes_read;
}
//----

void cipher_file_system::input_stream::rewind_impl()
{
  // rewind to the beginning of the stream
  PFC_ASSERT_PEDANTIC(m_is_first==false);
  m_stream.data->rewind();
  m_is_first=true;
  m_is_last=false;
  m_begin_pos=0;
  m_begin=m_end=m_data=0;
}
//----

void cipher_file_system::input_stream::rewind_impl(usize_t num_bytes_)
{
  // rewind the stream
  PFC_ASSERT(num_bytes_);
  usize_t num_rewind_bytes=num_bytes_-usize_t(m_data-m_begin);
  PFC_ASSERT_MSG(m_begin_pos>=num_rewind_bytes, ("Trying to seek beyond beginning of the cipher stream\r\n"));
  m_begin_pos-=num_rewind_bytes;
  m_stream.data->rewind(m_stream.data->pos()-(m_begin_pos&~align_mask));
  m_is_first=m_begin_pos==0;
  m_is_last=m_stream.data->is_eos();
  m_begin=m_end=m_data=0;
}
//----

void cipher_file_system::input_stream::skip_impl()
{
  // advance the stream
  m_begin_pos+=usize_t(m_data-m_begin);
  m_stream.data->skip((m_begin_pos&~align_mask)-m_stream.data->pos());
  m_is_first=false;
  m_is_last=m_stream.data->is_eos();
  m_begin=m_end=m_data=0;
}
//----

void cipher_file_system::input_stream::seek_impl(usize_t abs_pos_)
{
  // seek to the given position in the stream
  m_stream.data->seek(abs_pos_&~align_mask);
  m_is_first=abs_pos_==0;
  m_is_last=m_stream.data->is_eos();
  m_begin_pos=abs_pos_;
  m_begin=m_end=m_data=0;
}
//----------------------------------------------------------------------------


//============================================================================
// cipher_file_system::output_stream
//============================================================================
class cipher_file_system::output_stream: public bin_output_stream_base
{
public:
  // construction
  output_stream(const cipher_file_system&, const owner_ref<bin_output_stream_base>&);
  virtual ~output_stream();
  //--------------------------------------------------------------------------

private:
  output_stream(const output_stream&); // not implemented
  void operator=(const output_stream&); // not implemented
  //--------------------------------------------------------------------------

  // implementation
  virtual void flush_buffer_impl(const void*, usize_t num_bytes_);
  void encrypt_write_buffer(usize_t num_bytes_);
  //--------------------------------------------------------------------------

  enum {buffer_4size=1024, buffer_size=buffer_4size*4};
  owner_ref<bin_output_stream_base> m_stream;
  uint32_t m_cipher_key0[8];
  uint32_t m_cipher_key1[8];
  uint32_t m_buffer[buffer_4size];
};
//----------------------------------------------------------------------------

cipher_file_system::output_stream::output_stream(const cipher_file_system &fsys_, const owner_ref<bin_output_stream_base> &stream_)
  :m_stream(stream_)
{
  // setup stream and cipher keys
  m_begin=(uint8_t*)m_buffer;
  m_end=(uint8_t*)m_buffer+buffer_size;
  m_data=m_begin;
  mem_copy(m_cipher_key0, fsys_.m_cipher_key0, sizeof(m_cipher_key0));
  mem_copy(m_cipher_key1, fsys_.m_cipher_key1, sizeof(m_cipher_key1));
}
//----

cipher_file_system::output_stream::~output_stream()
{
  // encrypt the buffer and write remaining data
  encrypt_write_buffer(usize_t(m_data-m_begin));
}
//----------------------------------------------------------------------------

void cipher_file_system::output_stream::flush_buffer_impl(const void *p_, usize_t num_bytes_)
{
  // write data in batches to the stream
  usize_t num_buffer_bytes=usize_t(m_data-m_begin);
  while(true)
  {
    // fill the buffer with data
    const usize_t num_bytes_to_copy=min(num_bytes_, buffer_size-num_buffer_bytes);
    mem_copy(m_data, p_, num_bytes_to_copy);
    if(num_buffer_bytes+num_bytes_to_copy<buffer_size)
    {
      (uint8_t*&)m_data+=num_bytes_to_copy;
      break;
    }

    // encrypt & write buffer to the stream and proceed to the next data batch
    encrypt_write_buffer(buffer_size);
    m_begin_pos+=buffer_size;
    m_data=(uint8_t*)m_buffer;
    num_buffer_bytes=0;
    num_bytes_-=num_bytes_to_copy;
    (const uint8_t*&)p_+=num_bytes_to_copy;
  }
}
//----

void cipher_file_system::output_stream::encrypt_write_buffer(usize_t num_bytes_)
{
  // encrypt buffer and write it to the stream
  const usize_t buf_4size=(num_bytes_+3)/4;
  usize_t pos=(m_begin_pos/4)+*m_cipher_key0;
  for(usize_t i=0; i<buf_4size; ++i)
  {
    m_buffer[i]^=pos*m_cipher_key0[pos&7]+(pos/32)*m_cipher_key1[pos&7];
    ++pos;
  }
  m_stream.data->write_bytes(m_buffer, num_bytes_);
}
//----------------------------------------------------------------------------


//============================================================================
// cipher_file_system
//============================================================================
cipher_file_system::cipher_file_system(file_system_base &fsys_, const char *key_, bool set_active_)
  :file_system_base(set_active_)
  ,m_fsys(fsys_)
{
  // generate cipher keys from the key
  PFC_ASSERT(key_);
  m_cipher_key0[0]=crc32(key_, 0x15fa4e18);
  m_cipher_key0[1]=crc32(key_, 0x7c3f03ae);
  m_cipher_key0[2]=crc32(key_, 0xa538e29a);
  m_cipher_key0[3]=crc32(key_, 0x57c2eaa1);
  m_cipher_key0[4]=crc32(key_, 0xd37888a8);
  m_cipher_key0[5]=crc32(key_, 0x38f1c245);
  m_cipher_key0[6]=crc32(key_, 0xe27a7f21);
  m_cipher_key0[7]=crc32(key_, 0xc37e172c);
  m_cipher_key1[0]=crc32(key_, 0x7487e88a);
  m_cipher_key1[1]=crc32(key_, 0x7825c38d);
  m_cipher_key1[2]=crc32(key_, 0xb7c4ead8);
  m_cipher_key1[3]=crc32(key_, 0x430486a8);
  m_cipher_key1[4]=crc32(key_, 0x3b39c7a5);
  m_cipher_key1[5]=crc32(key_, 0x4c93a501);
  m_cipher_key1[6]=crc32(key_, 0x90a39ef2);
  m_cipher_key1[7]=crc32(key_, 0xf51a7a8c);
}
//----------------------------------------------------------------------------

file_system_base::iterator cipher_file_system::find_first(e_fsys_find fsys_find_, const char *dirname_, const char *path_) const
{
  return m_fsys.find_first(fsys_find_, dirname_, path_);
}
//----------------------------------------------------------------------------

bool cipher_file_system::exists(const char *filename_, const char *path_) const
{
  return m_fsys.exists(filename_, path_);
}
//----

usize_t cipher_file_system::file_size(const char *filename_, const char *path_) const
{
  return m_fsys.file_size(filename_, path_);
}
//----

bool cipher_file_system::is_writable(const char *filename_, const char *path_) const
{
  return m_fsys.is_writable(filename_, path_);
}
//----

file_time cipher_file_system::mod_time(const char *filename_, const char *path_) const
{
  return m_fsys.mod_time(filename_, path_);
}
//----

owner_ptr<bin_input_stream_base> cipher_file_system::open_read(const char *filename_, const char *path_, e_file_open_check fopen_check_) const
{
  return PFC_NEW(input_stream)(*this, m_fsys.open_read(filename_, path_, fopen_check_));
}
//----

owner_ptr<bin_output_stream_base> cipher_file_system::open_write(const char *filename_, const char *path_, e_file_open_write_mode mode_, uint64_t fpos_, bool makedir_, e_file_open_check fopen_check_)
{
  return PFC_NEW(output_stream)(*this, m_fsys.open_write(filename_, path_, mode_, fpos_, makedir_, fopen_check_));
}
//----

bool cipher_file_system::delete_file(const char *filename_, const char *path_)
{
  return m_fsys.delete_file(filename_, path_);
}
//----

bool cipher_file_system::rename_file(const char *filename_, const char *new_filename_, const char *path_, bool overwrite_existing_)
{
  return m_fsys.rename_file(filename_, new_filename_, path_, overwrite_existing_);
}
//----

void cipher_file_system::touch_file(const char *filename_, const char *path_)
{
  m_fsys.touch_file(filename_, path_);
}
//----------------------------------------------------------------------------

void cipher_file_system::set_directory(const char *dirname_)
{
  m_fsys.set_directory(dirname_);
}
//----

bool cipher_file_system::make_directory(const char *dirname_, const char *path_)
{
  return m_fsys.make_directory(dirname_, path_);
}
//----

bool cipher_file_system::delete_directory(const char *dirname_, const char *path_, bool delete_content_)
{
  return m_fsys.delete_directory(dirname_, path_, delete_content_);
}
//----

bool cipher_file_system::rename_directory(const char *dirname_, const char *new_dirname_, const char *path_)
{
  return m_fsys.rename_directory(dirname_, new_dirname_, path_);
}
//----

owner_ptr<directory_monitor_base> cipher_file_system::create_directory_monitor(const char *dirname_, bool notify_subdirs_) const
{
  return m_fsys.create_directory_monitor(dirname_, notify_subdirs_);
}
//----------------------------------------------------------------------------
