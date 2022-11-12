//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#ifndef PFC_WIN_CORE_SYSTEM_INFO_H
#define PFC_WIN_CORE_SYSTEM_INFO_H
//----------------------------------------------------------------------------


//============================================================================
// interface
//============================================================================
// external
#include "sxp_src/core/containers.h"
#include "sxp_src/core/str.h"
namespace pfc
{
class bin_input_stream_base;

// new
struct info_date;
struct os_info;
struct motherboard_info;
struct cpu_cache_info;
struct cpu_info;
struct memory_module_info;
struct video_adapter_info;
struct monitor_info;
struct audio_device_info;
struct software_info;
class system_info;
stack_str32 get_dll_version_str(const char *dll_filename_);
void get_call_stack(heap_str&);
//----------------------------------------------------------------------------


//============================================================================
// e_cpu_architecture
//============================================================================
enum e_cpu_architecture
{
  cpuarch_unknown,
  cpuarch_x86,
  cpuarch_mips,
  cpuarch_alpha,
  cpuarch_powerpc,
  cpuarch_ia64,
  cpuarch_x64,
};
//----------------------------------------------------------------------------


//============================================================================
// info_date
//============================================================================
struct info_date
{
  // construction
  info_date();
  //--------------------------------------------------------------------------

  uint16_t year;
  uint8_t month, day;
};
//----------------------------------------------------------------------------


//============================================================================
// os_info
//============================================================================
struct os_info
{
  // construction and logging
  os_info();
  void log_info(const char *prefix_="");
  //--------------------------------------------------------------------------

  heap_str name;
  heap_str service_pack;
  uint64_t total_physical_memory;
  uint64_t free_physical_memory;
  uint64_t total_virtual_memory;
  uint64_t free_virtual_memory;
};
//----------------------------------------------------------------------------


//============================================================================
// motherboard_info
//============================================================================
struct motherboard_info
{
  // construction and logging
  motherboard_info();
  void log_info(const char *prefix_="");
  //--------------------------------------------------------------------------

  heap_str model;
  heap_str manufacturer;
  heap_str version;
};
//----------------------------------------------------------------------------


//============================================================================
// cpu_cache_info
//============================================================================
struct cpu_cache_info
{
  // construction and logging
  cpu_cache_info();
  void log_info(const char *prefix_="");
  //--------------------------------------------------------------------------

  unsigned level;
  unsigned size_kb;
  unsigned speed_ns;
  heap_str associativity;
  heap_str type;
};
//----------------------------------------------------------------------------


//============================================================================
// cpu_info
//============================================================================
struct cpu_info
{
  // construction and logging
  cpu_info();
  void log_info(const char *prefix_="");
  //--------------------------------------------------------------------------

  heap_str name;
  heap_str description;
  heap_str manufacturer;
  heap_str socket;
  e_cpu_architecture architecture;
  uint8_t num_cpu_bits;
  uint8_t num_os_bits;
  uint8_t num_processors;
  uint8_t num_cores;
  uint8_t num_hw_threads;
  uint32_t freq_mhz;
  uint32_t max_freq_mhz;
  uint32_t ext_freq_mhz;
  cpu_cache_info l1_data_cache, l1_code_cache;
  cpu_cache_info l2_data_cache, l2_code_cache;
  cpu_cache_info l3_data_cache, l3_code_cache;
};
//----------------------------------------------------------------------------


//============================================================================
// memory_module_info
//============================================================================
struct memory_module_info
{
  // construction and logging
  memory_module_info();
  void log_info(const char *prefix_="");
  //--------------------------------------------------------------------------

  heap_str slot;
  uint32_t size_mb;
  uint32_t total_width;
  heap_str type;
  uint32_t freq_mhz;
};
//----------------------------------------------------------------------------


//============================================================================
// video_adapter_info
//============================================================================
struct video_adapter_info
{
  // construction and logging
  video_adapter_info();
  void log_info(const char *prefix_="");
  //--------------------------------------------------------------------------

  heap_str name;
  unsigned memory;
  heap_str memory_type;
  heap_str drivers;
  heap_str driver_version;
  info_date driver_date;
};
//----------------------------------------------------------------------------


//============================================================================
// monitor_info
//============================================================================
struct monitor_info
{
  // construction and logging
  monitor_info();
  void log_info(const char *prefix_="");
  //--------------------------------------------------------------------------

  heap_str description;
  unsigned width, height;
};
//----------------------------------------------------------------------------


//============================================================================
// audio_device_info
//============================================================================
struct audio_device_info
{
  // construction and logging
  audio_device_info();
  void log_info(const char *prefix_="");
  //--------------------------------------------------------------------------

  heap_str name;
  heap_str manufacturer;
};
//----------------------------------------------------------------------------


//============================================================================
// software_info
//============================================================================
struct software_info
{
  // construction and logging
  software_info();
  void log_info(const char *prefix_="");
  //--------------------------------------------------------------------------

  heap_str directx_ver;
};
//----------------------------------------------------------------------------


//============================================================================
// system_info
//============================================================================
class system_info
{
public:
  // construction and logging
  system_info();
  void log_info();
  //--------------------------------------------------------------------------

  // accessors
  const os_info &os() const;
  const motherboard_info &motherboard() const;
  const cpu_info &cpu() const;
  const array<memory_module_info> &memory_modules() const;
  const array<video_adapter_info> &video_adapters() const;
  const array<monitor_info> &monitors() const;
  const array<audio_device_info> &audio_devices() const;
  const software_info &software() const;
  //--------------------------------------------------------------------------

private:
  // SMBIOS functions
  void get_smbios_info();
  void parse_smbios_strings(bin_input_stream_base&, array<heap_str>&);
  void get_smbios_string(heap_str&, unsigned str_idx_, const array<heap_str>&);
  void parse_smbios_cpu_info(bin_input_stream_base&, unsigned size_);
  void parse_smbios_cache_info(bin_input_stream_base&, unsigned size_);
  void parse_smbios_memory_device_info(bin_input_stream_base&, unsigned size_);
  //--------------------------------------------------------------------------

  os_info m_os_info;
  motherboard_info m_motherboard_info;
  cpu_info m_cpu_info;
  array<memory_module_info> m_memory_modules;
  array<video_adapter_info> m_video_adapters;
  array<monitor_info> m_monitors;
  array<audio_device_info> m_audio_devices;
  software_info m_software;
};
//----------------------------------------------------------------------------

//============================================================================
} // namespace pfc
#endif
