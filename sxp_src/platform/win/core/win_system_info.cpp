//============================================================================
// Mini Spin-X Library
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "sxp_src/sxp_pch.h"
#include "win_system_info.h"
#include "sxp_src/core/streams.h"
#include <dbghelp.h>
#include <comdef.h>
#include <wbemidl.h>
#include <dxdiag.h>
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// locals
//============================================================================
namespace
{
  class wmi_enumerator
  {
  public:
    // construction
    wmi_enumerator(const wchar_t *resource_=L"root\\cimv2");
    ~wmi_enumerator();
    //------------------------------------------------------------------------

    // data access
    bool access_class_object(const char *class_name_);
    bool next_object();
    template<typename T> bool get_value(T &v_, const wchar_t *value_vame_);
    template<typename T> bool get_array(array<T>&, const wchar_t *value_name_);
    //------------------------------------------------------------------------

  private:
    // helper functions
    PFC_INLINE void read_value(bool &v_, const VARIANT &var_) const            {v_=var_.boolVal==TRUE;}
    PFC_INLINE void read_value(char &v_, const VARIANT &var_) const            {v_=var_.cVal;}
    PFC_INLINE void read_value(signed char &v_, const VARIANT &var_) const     {v_=var_.cVal;}
    PFC_INLINE void read_value(unsigned char &v_, const VARIANT &var_) const   {v_=var_.bVal;}
    PFC_INLINE void read_value(short &v_, const VARIANT &var_) const           {v_=var_.iVal;}
    PFC_INLINE void read_value(unsigned short &v_, const VARIANT &var_) const  {v_=var_.uiVal;}
    PFC_INLINE void read_value(int &v_, const VARIANT &var_) const             {v_=var_.intVal;}
    PFC_INLINE void read_value(unsigned &v_, const VARIANT &var_) const        {v_=var_.uintVal;}
    PFC_INLINE void read_value(long &v_, const VARIANT &var_) const            {v_=var_.lVal;}
    PFC_INLINE void read_value(unsigned long &v_, const VARIANT &var_) const   {v_=var_.ulVal;}
    PFC_INLINE void read_value(int64_t &v_, const VARIANT &var_) const           {convert_bstr_to_value(v_, var_.bstrVal);}
    PFC_INLINE void read_value(uint64_t &v_, const VARIANT &var_) const          {convert_bstr_to_value(v_, var_.bstrVal);}
    PFC_INLINE void read_value(float &v_, const VARIANT &var_) const           {v_=var_.fltVal;}
    PFC_INLINE void read_value(double &v_, const VARIANT &var_) const          {v_=var_.dblVal;}
    PFC_INLINE void read_value(long double &v_, const VARIANT &var_) const     {v_=var_.dblVal;}
    PFC_INLINE void read_value(heap_str &v_, const VARIANT &var_) const        {v_=_bstr_t(var_.bstrVal); v_.resize(str_strip_extra_whitespace(v_.c_str()));}
    PFC_INLINE void read_value(info_date &v_, const VARIANT &var_) const       {convert_bstr_to_date(v_, var_.bstrVal);}
    bool get_variant(VARIANT&, const wchar_t *value_name_);
    template<typename T> void convert_bstr_to_value(T&, const BSTR) const;
    void convert_bstr_to_date(info_date&, const BSTR) const;
    //------------------------------------------------------------------------

    bool m_uninit_com;
    IWbemLocator *m_locator;
    IWbemServices *m_services;
    IEnumWbemClassObject *m_enumerator;
    IWbemClassObject *m_class_obj;
  };
  //--------------------------------------------------------------------------

  wmi_enumerator::wmi_enumerator(const wchar_t *resource_)
  {
    // init members
    m_locator=0;
    m_services=0;
    m_enumerator=0;
    m_class_obj=0;

    // initialize COM & security levels
    m_uninit_com=CoInitializeEx(0, COINIT_MULTITHREADED)>=0;
    CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

    // obtain initial locator to WMI
    const _GUID wbem_locator_clsid={0x4590f811, 0x1d3a, 0x11d0, {0x89, 0x1f, 0x00, 0xaa, 0x00, 0x4b, 0x2e, 0x24}};
    const _GUID wbem_locator_iid={0xdc12a687, 0x737f, 0x11cf, {0x88, 0x4d, 0x00, 0xaa, 0x00, 0x4b, 0x2e, 0x24}};
    HRESULT hres=CoCreateInstance(wbem_locator_clsid, 0, CLSCTX_INPROC_SERVER, wbem_locator_iid, (LPVOID*)&m_locator);
    if(hres>=0)
    {
      // connect to WMI
      hres=m_locator->ConnectServer(_bstr_t(resource_), NULL, NULL, 0, NULL, 0, 0, &m_services);
      if(m_services)
      {
        // setup proxy security levels
        hres=CoSetProxyBlanket(m_services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
        if(hres>=0)
          return;
        m_services->Release();
        m_services=0;
      }
      else
        PFC_WARN(("Failed to connect to WMI\r\n"));
      m_locator->Release();
      m_locator=0;
    }
    else
      PFC_WARN(("Failed to obtain WMI locator\r\n"));
    if(m_uninit_com)
      CoUninitialize();
  }
  //----

  wmi_enumerator::~wmi_enumerator()
  {
    if(m_services)
    {
      // release resources
      if(m_enumerator)
        m_enumerator->Release();
      if(m_class_obj)
        m_class_obj->Release();
      m_services->Release();
      m_locator->Release();
    }
    if(m_uninit_com)
      CoUninitialize();
  }
  //--------------------------------------------------------------------------

  bool wmi_enumerator::access_class_object(const char *class_name_)
  {
    // release class object and previous enumerator
    PFC_SAFE_RELEASE(m_class_obj);
    PFC_SAFE_RELEASE(m_enumerator);

    // access first class
    stack_str64 query="SELECT * FROM ";
    query+=class_name_;
    m_services->ExecQuery(bstr_t("WQL"), bstr_t(query.c_str()), WBEM_FLAG_FORWARD_ONLY|WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &m_enumerator);
    return next_object();
  }
  //----

  bool wmi_enumerator::next_object()
  {
    // get next class object
    if(!m_enumerator)
      return false;
    PFC_SAFE_RELEASE(m_class_obj);
    ULONG retval=0;
    m_enumerator->Next(WBEM_INFINITE, 1, &m_class_obj, &retval);
    return retval!=0;
  }
  //----

  template<typename T>
  bool wmi_enumerator::get_value(T &v_, const wchar_t *value_name_)
  {
    // get value for given value
    VARIANT v;
    if(!get_variant(v, value_name_) || v.vt==VT_NULL)
      return false;
    read_value(v_, v);
    VariantClear(&v);
    return true;
  }
  //----

  template<typename T>
  bool wmi_enumerator::get_array(array<T> &arr_, const wchar_t *value_name_)
  {
    // get array for given value
    VARIANT v;
    if(!get_variant(v, value_name_) || v.vt==VT_NULL)
      return false;
    LONG lb, ub;
    PFC_VERIFY(SafeArrayGetLBound(v.parray, 1, &lb)>=0);
    PFC_VERIFY(SafeArrayGetUBound(v.parray, 1, &ub)>=0);
    unsigned size=unsigned(ub-lb+1);
    arr_.resize(size);
    PFC_VERIFY(SafeArrayLock(v.parray)>=0);
    T *data=arr_.data();
    for(unsigned i=0; i<size; ++i)
      data[i]=static_cast<const T*>(v.parray->pvData)[i];
    PFC_VERIFY(SafeArrayUnlock(v.parray)>=0);
    VariantClear(&v);
    return true;
  }
  //--------------------------------------------------------------------------

  bool wmi_enumerator::get_variant(VARIANT &var_, const wchar_t *value_name_)
  {
    // get variant for the given value
    if(!m_class_obj)
      return false;
    return m_class_obj->Get(value_name_, 0, &var_, 0, 0)>=0;
  }
  //----

  template<typename T>
  void wmi_enumerator::convert_bstr_to_value(T &v_, const BSTR str_) const
  {
    // convert BSTR to given type
    _bstr_t tmp(str_);
    const char *s=tmp;
    mem_input_stream ms(s);
    text_input_stream ts(ms);
    ts>>v_;
  }
  //----

  void wmi_enumerator::convert_bstr_to_date(info_date &d_, const BSTR str_) const
  {
    // convert BSTR to date
    wchar_t y[]={str_[0], str_[1], str_[2], str_[3], 0};
    wchar_t m[]={str_[4], str_[5], 0};
    wchar_t d[]={str_[6], str_[7], 0};
    d_.year=uint16_t(_wtoi(y));
    d_.month=uint8_t(_wtoi(m));
    d_.day=uint8_t(_wtoi(d));
  }
  //--------------------------------------------------------------------------

  void get_os_info(wmi_enumerator &wmienum_, os_info &info_)
  {
    // get operating system name, architecture, version & service pack
    wmienum_.access_class_object("Win32_OperatingSystem");
    wmienum_.get_value(info_.name, L"Name");
    char *os_name_end=str_find(info_.name.c_str(), '|');
    if(os_name_end)
    {
      if(os_name_end!=info_.name.c_str() && !is_whitespace(*--os_name_end))
        ++os_name_end;
      info_.name.resize(unsigned(os_name_end-info_.name.c_str()));
    }
    heap_str osarch, build;
    if(wmienum_.get_value(osarch, L"OSArchitecture"))
    {
      info_.name+=" ";
      info_.name+=osarch;
    }
    heap_str version;
    wmienum_.get_value(version, L"Version");
    info_.name+=" (";
    info_.name+=version;
    info_.name+=")";
    wmienum_.get_value(info_.service_pack, L"CSDVersion");

    // get memory info
    wmienum_.get_value(info_.total_physical_memory, L"TotalVisibleMemorySize");
    info_.total_physical_memory*=1024;
    wmienum_.get_value(info_.free_physical_memory, L"FreePhysicalMemory");
    info_.free_physical_memory*=1024;
    wmienum_.get_value(info_.total_virtual_memory, L"TotalVirtualMemorySize");
    info_.total_virtual_memory*=1024;
    wmienum_.get_value(info_.free_virtual_memory, L"FreeVirtualMemory");
    info_.free_virtual_memory*=1024;
  }
  //----

  void get_motherboard_info(wmi_enumerator &wmienum_, motherboard_info &info_)
  {
    // get motherboard info
    wmienum_.access_class_object("Win32_BaseBoard");
    wmienum_.get_value(info_.model, L"Product");
    wmienum_.get_value(info_.manufacturer, L"Manufacturer");
    wmienum_.get_value(info_.version, L"Version");
  }
  //----

  void get_cpu_info(wmi_enumerator &wmienum_, cpu_info &info_)
  {
    // get CPU info
    wmienum_.access_class_object("Win32_Processor");
    wmienum_.get_value(info_.name, L"Name");
    wmienum_.get_value(info_.description, L"Description");
    wmienum_.get_value(info_.manufacturer, L"Manufacturer");
    uint16_t arch;
    if(wmienum_.get_value(arch, L"Architecture"))
    {
      switch(arch)
      {
        case 0: info_.architecture=cpuarch_x86; break;
        case 1: info_.architecture=cpuarch_mips; break;
        case 2: info_.architecture=cpuarch_alpha; break;
        case 3: info_.architecture=cpuarch_powerpc; break;
        case 6: info_.architecture=cpuarch_ia64; break;
        case 9: info_.architecture=cpuarch_x64; break;
      }
    }
    wmienum_.get_value(info_.num_cpu_bits, L"DataWidth");
    wmienum_.get_value(info_.num_os_bits, L"AddressWidth");
    wmienum_.get_value(info_.num_cores, L"NumberOfCores");
    wmienum_.get_value(info_.num_hw_threads, L"NumberOfLogicalProcessors");
    info_.l2_data_cache.level=2;
    wmienum_.get_value(info_.l2_data_cache.size_kb, L"L2CacheSize");
    info_.l2_data_cache.level=3;
    wmienum_.get_value(info_.l3_data_cache.size_kb, L"L3CacheSize");
    wmienum_.access_class_object("Win32_ComputerSystem");
    wmienum_.get_value(info_.num_processors, L"NumberOfProcessors");
  }
  //----

  void get_video_adapter_info(wmi_enumerator &wmienum_, array<video_adapter_info> &adapters_)
  {
    // get video adapter info
    if(wmienum_.access_class_object("Win32_VideoController"))
      do
      {
        video_adapter_info &info=adapters_.push_back();
        wmienum_.get_value(info.name, L"Name");
        wmienum_.get_value(info.memory, L"AdapterRAM");
        wmienum_.get_value(info.driver_version, L"DriverVersion");
        wmienum_.get_value(info.drivers, L"InstalledDisplayDrivers");
        wmienum_.get_value(info.driver_date, L"DriverDate");
        uint16_t mem_type;
        wmienum_.get_value(mem_type, L"VideoMemoryType");
        switch(mem_type)
        {
          case 3: info.memory_type="VRAM"; break;
          case 4: info.memory_type="DRAM"; break;
          case 5: info.memory_type="SRAM"; break;
          case 6: info.memory_type="WRAM"; break;
          case 7: info.memory_type="EDO RAM"; break;
          case 8: info.memory_type="Burst Synchronous DRAM"; break;
          case 9: info.memory_type="Pipelined Burst SRAM"; break;
          case 10: info.memory_type="CDRAM"; break;
          case 11: info.memory_type="3DRAM"; break;
          case 12: info.memory_type="SDRAM"; break;
          case 13: info.memory_type="SGRAM"; break;
        }
      } while(wmienum_.next_object());
  }
  //----

  void get_monitor_info(wmi_enumerator &wmienum_, array<monitor_info> &monitors_)
  {
    // get monitor info
    if(wmienum_.access_class_object("Win32_DesktopMonitor"))
      do
      {
        monitor_info &info=monitors_.push_back();
        wmienum_.get_value(info.description, L"Description");
        wmienum_.get_value(info.width, L"ScreenWidth");
        wmienum_.get_value(info.height, L"ScreenHeight");
      } while(wmienum_.next_object());
  }
  //----

  void get_audio_device_info(wmi_enumerator &wmienum_, array<audio_device_info> &devices_)
  {
    // get video adapter info
    if(wmienum_.access_class_object("Win32_SoundDevice"))
      do
      {
        audio_device_info &info=devices_.push_back();
        wmienum_.get_value(info.name, L"Name");
        wmienum_.get_value(info.manufacturer, L"Manufacturer");
      } while(wmienum_.next_object());
  }
  //----

  void get_software_info(software_info &software_)
  {
    // get DirectX version string
    bool uninit_com=CoInitialize(0)>=0;
    IDxDiagProvider *provider=0;
    IDxDiagContainer *diag_root=0;
    const _GUID diag_provider_clsid={0xa65b8071, 0x3bfe, 0x4213, {0x9a, 0x5b, 0x49, 0x1d, 0xa4, 0x46, 0x1c, 0xa7}};
    const _GUID diag_provider_iid={0x9c6b4cb0, 0x23f8, 0x49cc, {0xa3, 0xed, 0x45, 0xa5, 0x50, 0x00, 0xa6, 0xd2}};
    if(CoCreateInstance(diag_provider_clsid, 0, CLSCTX_INPROC_SERVER, diag_provider_iid, (LPVOID*)&provider)>=0)
    {
      DXDIAG_INIT_PARAMS params;
      mem_zero(&params, sizeof(params));
      params.dwSize=sizeof(params);
      params.dwDxDiagHeaderVersion=DXDIAG_DX9_SDK_VERSION;
      params.bAllowWHQLChecks=TRUE;
      if(provider->Initialize(&params)>=0 && provider->GetRootContainer(&diag_root)>=0)
      {
        IDxDiagContainer *sys_info=0;
        VARIANT dx_version;
        if(diag_root->GetChildContainer(L"DxDiag_SystemInfo", &sys_info)>=0
           && sys_info->GetProp(L"szDirectXVersionLongEnglish", &dx_version)>=0)
          software_.directx_ver=_bstr_t(dx_version.bstrVal);
      }
    }
    if(uninit_com)
      CoUninitialize();
  }
  //--------------------------------------------------------------------------

  const char *cpuarch_str(e_cpu_architecture arch_)
  {
    // return CPU architecture string
    switch(arch_)
    {
      case cpuarch_x86:     return "x86";
      case cpuarch_mips:    return "MIPS";
      case cpuarch_alpha:   return "Alpha";
      case cpuarch_powerpc: return "PowerPC";
      case cpuarch_ia64:    return "ia64";
      case cpuarch_x64:     return "x64";
    }
    return "N/A";
  }
} // namespace <anonymous>
//----------------------------------------------------------------------------


//============================================================================
// info_date
//============================================================================
info_date::info_date()
{
  // init members
  year=0;
  month=0;
  day=0;
}
//----------------------------------------------------------------------------


//============================================================================
// os_info
//============================================================================
os_info::os_info()
{
  // init members
  total_physical_memory=0;
  free_physical_memory=0;
  total_virtual_memory=0;
  free_virtual_memory=0;
}
//----

void os_info::log_info(const char *prefix_)
{
  PFC_LOG(("%sName: %s\r\n", prefix_, name.c_str()));
  if(service_pack.size())
    PFC_LOG(("%sService Pack: %s\r\n", prefix_, service_pack.c_str()));
  PFC_LOG(("%sTotal Physical Memory: %iMB (%iMB free)\r\n", prefix_, unsigned((total_physical_memory+1024*1024/2)/(1024*1024)), unsigned((free_physical_memory+1024*1024/2)/(1024*1024))));
  PFC_LOG(("%sTotal Virtual Memory: %iMB (%iMB free)\r\n", prefix_, unsigned((total_virtual_memory+1024*1024/2)/(1024*1024)), unsigned((free_virtual_memory+1024*1024/2)/(1024*1024))));
}
//----------------------------------------------------------------------------


//============================================================================
// motherboard_info
//============================================================================
motherboard_info::motherboard_info()
{
}
//----

void motherboard_info::log_info(const char *prefix_)
{
  PFC_LOG(("%sModel: %s (%s)\r\n", prefix_, model.c_str(), version.c_str()));
  if(manufacturer.size())
    PFC_LOG(("%sManufacturer: %s\r\n", prefix_, manufacturer.c_str()));
}
//----------------------------------------------------------------------------


//============================================================================
// cpu_cache_info
//============================================================================
cpu_cache_info::cpu_cache_info()
{
  level=0;
  size_kb=0;
  speed_ns=0;
}
//----

void cpu_cache_info::log_info(const char *prefix_)
{
  if(level && size_kb)
  {
    PFC_LOG(("%sL%i %sCache: %iKB", prefix_, level, type.c_str(), size_kb));
    if(speed_ns)
      PFC_LOG((", %ins", speed_ns));
    if(associativity.size())
      PFC_LOG((" (%s)", associativity.c_str()));
    PFC_LOG(("\r\n"));
  }
}
//----------------------------------------------------------------------------


//============================================================================
// cpu_info
//============================================================================
cpu_info::cpu_info()
{
  // init members
  architecture=cpuarch_unknown;
  num_cpu_bits=0;
  num_os_bits=0;
  num_processors=0;
  num_cores=0;
  num_hw_threads=0;
  freq_mhz=0;
  max_freq_mhz=0;
  ext_freq_mhz=0;
}
//----

void cpu_info::log_info(const char *prefix_)
{
  PFC_LOG(("%sName: %s\r\n", prefix_, name.c_str()));
  if(description.size())
    PFC_LOG(("%sDescription: %s\r\n", prefix_, description.c_str()));
  if(manufacturer.size())
    PFC_LOG(("%sManufacturer: %s\r\n", prefix_, manufacturer.c_str()));
  if(architecture)
    PFC_LOG(("%sArchitecture: %s (%i-bit) running on a %i-bit OS\r\n", prefix_, cpuarch_str(architecture), num_cpu_bits, num_os_bits));
  if(freq_mhz)
  {
    PFC_LOG(("%sCurrent Speed: %iMHz", prefix_, freq_mhz));
    if(max_freq_mhz)
      PFC_LOG((" (Max. %iMHz)", max_freq_mhz));
    PFC_LOG(("\r\n"));
    if(ext_freq_mhz)
      PFC_LOG(("%sExternal Speed: %iMHz\r\n", prefix_, ext_freq_mhz));
  }
  PFC_LOG(("%sNumber of Processors: %i (%i %s & %i HW %s)\r\n", prefix_, num_processors, num_cores, num_cores==1?"Core":"Cores", num_hw_threads, num_hw_threads==1?"Thread":"Threads"));
  l1_data_cache.log_info(prefix_);
  l1_code_cache.log_info(prefix_);
  l2_data_cache.log_info(prefix_);
  l2_code_cache.log_info(prefix_);
  l3_data_cache.log_info(prefix_);
  l3_code_cache.log_info(prefix_);
}
//----------------------------------------------------------------------------


//============================================================================
// memory_module_info
//============================================================================
memory_module_info::memory_module_info()
{
  // init members
  size_mb=0;
  total_width=0;
  freq_mhz=0;
}
//----

void memory_module_info::log_info(const char *prefix_)
{
  if(slot.size())
  {
    PFC_LOG(("%s%s: ", prefix_, slot.c_str()));
  }
  else
    PFC_LOG(("%sSLOT?: ", prefix_));
  if(size_mb)
  {
    PFC_LOG(("%iMB", size_mb));
    if(total_width || type.size())
    {
      PFC_LOG((","));
      if(total_width)
        PFC_LOG((" %i-bit", total_width));
      if(type.size())
        PFC_LOG((" %s", type.c_str()));
    }
    if(freq_mhz)
      PFC_LOG((" @ %iMHz", freq_mhz));
    PFC_LOG(("\r\n"));
  }
  else
    PFC_LOG(("<empty>\r\n"));
}
//----------------------------------------------------------------------------


//============================================================================
// video_adapter_info
//============================================================================
video_adapter_info::video_adapter_info()
{
  // init members
  memory=0;
}
//----

void video_adapter_info::log_info(const char *prefix_)
{
  PFC_LOG(("%sName: %s\r\n", prefix_, name.c_str()));
  PFC_LOG(("%sTotal Memory: %iMB", prefix_, (memory+1024*1024/2)/(1024*1024)));
  if(memory_type.size())
    PFC_LOG(("%s(%s)", prefix_, memory_type.c_str()));
  PFC_LOG(("\r\n"));
  PFC_LOG(("%sDrivers: %s\r\n", prefix_, drivers.c_str()));
  PFC_LOG(("%sDriver Version: %s (%i/%i/%i)\r\n", prefix_, driver_version.c_str(), driver_date.month, driver_date.day, driver_date.year));
}
//----------------------------------------------------------------------------


//============================================================================
// monitor_info
//============================================================================
monitor_info::monitor_info()
{
  // init members
  width=0;
  height=0;
}
//----

void monitor_info::log_info(const char *prefix_)
{
  PFC_LOG(("%sDescription: %s\r\n", prefix_, description.c_str()));
  PFC_LOG(("%sNative Resolution: %i x %i\r\n", prefix_, width, height));
}
//----------------------------------------------------------------------------


//============================================================================
// audio_device_info
//============================================================================
audio_device_info::audio_device_info()
{
}
//----

void audio_device_info::log_info(const char *prefix_)
{
  PFC_LOG(("%sName: %s\r\n", prefix_, name.c_str()));
  PFC_LOG(("%sManufacturer: %s\r\n", prefix_, manufacturer.c_str()));
}
//----------------------------------------------------------------------------


//============================================================================
// software_info
//============================================================================
software_info::software_info()
{
}
//----

void software_info::log_info(const char *prefix_)
{
  PFC_LOG(("%sDirectX Version: %s\r\n", prefix_, directx_ver.c_str()));
}
//----------------------------------------------------------------------------


//============================================================================
// system_info
//============================================================================
system_info::system_info()
{
  // get info
  get_software_info(m_software);
  wmi_enumerator wmienum;
  get_os_info(wmienum, m_os_info);
  get_motherboard_info(wmienum, m_motherboard_info);
  get_cpu_info(wmienum, m_cpu_info);
  get_video_adapter_info(wmienum, m_video_adapters);
  get_monitor_info(wmienum, m_monitors);
  get_audio_device_info(wmienum, m_audio_devices);
  get_smbios_info();
}
//----

void system_info::log_info()
{
  // print operating system info
  PFC_LOG(("Operating System Information:\r\n"));
  m_os_info.log_info("  ");

  // print motherboard and CPU info
  PFC_LOG(("Motherboard Information:\r\n"));
  m_motherboard_info.log_info("  ");
  PFC_LOG(("CPU Information:\r\n"));
  m_cpu_info.log_info("  ");

  // print memory module info
  if(m_memory_modules.size())
  {
    PFC_LOG(("Memory Module Information:\r\n"));
    for(unsigned i=0; i<m_memory_modules.size(); ++i)
      m_memory_modules[i].log_info("  ");
  }

  // print video adapter info
  if(m_video_adapters.size())
  {
    PFC_LOG(("Video Adapter Information:\r\n"));
    bool has_multiple_adapters=m_video_adapters.size()>1;
    const char *vidadapter_prefix=has_multiple_adapters?"    ":"  ";
    for(unsigned i=0; i<m_video_adapters.size(); ++i)
    {
      if(has_multiple_adapters)
        PFC_LOG(("  Adapter #%i:\r\n", i+1));
      m_video_adapters[i].log_info(vidadapter_prefix);
    }
  }

  // print monitor info
  if(m_monitors.size())
  {
    PFC_LOG(("Monitor Information:\r\n"));
    bool has_multiple_monitors=m_monitors.size()>1;
    const char *monitor_prefix=has_multiple_monitors?"    ":"  ";
    for(unsigned i=0; i<m_monitors.size(); ++i)
    {
      if(has_multiple_monitors)
        PFC_LOG(("  Monitor #%i:\r\n", i+1));
      m_monitors[i].log_info(monitor_prefix);
    }
  }

  // print audio device info
  if(m_audio_devices.size())
  {
    PFC_LOG(("Audio Device Information:\r\n"));
    bool has_multiple_devices=m_audio_devices.size()>1;
    const char *audev_prefix=has_multiple_devices?"    ":"  ";
    for(unsigned i=0; i<m_audio_devices.size(); ++i)
    {
      if(has_multiple_devices)
        PFC_LOG(("  Device #%i:\r\n", i+1));
      m_audio_devices[i].log_info(audev_prefix);
    }
  }

  // print system software info
  PFC_LOG(("System Software Info:\r\n"));
  m_software.log_info("  ");
}
//----------------------------------------------------------------------------

const os_info &system_info::os() const
{
  return m_os_info;
}
//----

const motherboard_info &system_info::motherboard() const
{
  return m_motherboard_info;
}
//----

const cpu_info &system_info::cpu() const
{
  return m_cpu_info;
}
//----

const array<memory_module_info> &system_info::memory_modules() const
{
  return m_memory_modules;
}
//----

const array<video_adapter_info> &system_info::video_adapters() const
{
  return m_video_adapters;
}
//----

const array<monitor_info> &system_info::monitors() const
{
  return m_monitors;
}
//----

const array<audio_device_info> &system_info::audio_devices() const
{
  return m_audio_devices;
}
//----

const software_info &system_info::software() const
{
  return m_software;
}
//----------------------------------------------------------------------------

void system_info::get_smbios_info()
{
  // get SMBIOS data
  wmi_enumerator wmienum(L"root\\wmi");
  if(!wmienum.access_class_object("MSSMBios_RawSMBiosTables"))
    return;
  array<uint8_t> smbios_data;
  wmienum.get_array(smbios_data, L"SMBiosData");

  // parse supplemental data from SMBIOS
  mem_input_stream mem_stream(smbios_data.data(), smbios_data.size());
  while(!mem_stream.is_eos())
  {
    // read block header
    uint8_t type, size;
    uint16_t handle;
    mem_stream>>type>>size>>handle;
    size-=4;
    {
      switch(type)
      {
        case 4: parse_smbios_cpu_info(mem_stream, size); break;
        case 7: parse_smbios_cache_info(mem_stream, size); break;
        case 17: parse_smbios_memory_device_info(mem_stream, size); break;
        // unknown type
        default:
        {
          // skip data & strings (search for double zero)
          mem_stream.skip(size);
          unsigned zero_count=0;
          do 
          {
            uint8_t c;
            mem_stream>>c;
            zero_count=c?0:zero_count+1;
          } while(zero_count<2);
        }
      }
    }
  }
}
//----

void system_info::parse_smbios_strings(bin_input_stream_base &stream_, array<heap_str> &strings_)
{
  // read strings in the block
  unsigned zero_count=0;
  heap_str *cur_str=&strings_.push_back();
  while(true) 
  {
    char c;
    stream_>>c;
    if(c)
    {
      *cur_str+=c;
      zero_count=0;
    }
    else
      if(++zero_count==1)
      {
        cur_str->resize(str_strip_extra_whitespace(cur_str->c_str()));
        cur_str=&strings_.push_back();
      }
      else
        break;
  }
  strings_.pop_back();
}
//----

void system_info::get_smbios_string(heap_str &str_, unsigned str_idx_, const array<heap_str> &strings_)
{
  if(str_idx_ && str_idx_<strings_.size())
    str_=strings_[str_idx_-1];
}
//----

void system_info::parse_smbios_cpu_info(bin_input_stream_base &stream_, unsigned size_)
{
  // 2.0+
  uint8_t socket=0, type=0, family=0, manufacturer=0;
  uint64_t id=0;
  uint8_t version=0, voltage=0;
  uint16_t clock_ext=0, max_speed=0, cur_speed=0;
  uint8_t status=0, upgrade=0;
  // 2.1+
  uint16_t l1cache=0, l2cache=0, l3cache=0;
  // 2.3+
  uint8_t serial=0, asset_tag=0, part_num=0;
  // 2.5+
  uint8_t num_cores=0, num_cores_enabled=0, num_threads=0;
  uint16_t chars=0;

  // read properties
  {
    auto_stream_seek<bin_input_stream_base> aseek(stream_, size_);
    if(size_>=22)
    {
      stream_>>socket>>type>>family>>manufacturer;
      stream_>>id;
      stream_>>version>>voltage;
      stream_>>clock_ext>>max_speed>>cur_speed;
      stream_>>status>>upgrade;
    }
    if(size_>=28)
      stream_>>l1cache>>l2cache>>l3cache;
    if(size_>=31)
      stream_>>serial>>asset_tag>>part_num;
    if(size_>=36)
    {
      stream_>>num_cores>>num_cores_enabled>>num_threads;
      stream_>>chars;
    }
  }
  array<heap_str> strings;
  parse_smbios_strings(stream_, strings);

  // map properties to the info struct
  get_smbios_string(m_cpu_info.socket, socket, strings);
  m_cpu_info.ext_freq_mhz=clock_ext;
  m_cpu_info.max_freq_mhz=max_speed;
  m_cpu_info.freq_mhz=cur_speed;
}
//----

void system_info::parse_smbios_cache_info(bin_input_stream_base &stream_, unsigned size_)
{
  // 2.0+
  uint8_t socket=0;
  uint16_t config=0;
  uint16_t max_size=0, installed_size=0;
  uint16_t supp_sram_type=0, curr_sram_type=0;
  // 2.1+
  uint8_t speed_ns=0, error_correction=0, sys_type=0, assoc=0;

  // read properties
  {
    auto_stream_seek<bin_input_stream_base> aseek(stream_, size_);
    if(size_>=11)
    {
      stream_>>socket;
      stream_>>config;
      stream_>>max_size>>installed_size;
      stream_>>supp_sram_type>>curr_sram_type;
    }
    if(size_>=15)
      stream_>>speed_ns>>error_correction>>sys_type>>assoc;
  }
  array<heap_str> strings;
  parse_smbios_strings(stream_, strings);

  // map values to cache info
  unsigned level=0;
  cpu_cache_info *cache=0;
  switch(config&7)
  {
    case 0: cache=sys_type==3?&m_cpu_info.l1_code_cache:&m_cpu_info.l1_data_cache; level=1; break;
    case 1: cache=sys_type==3?&m_cpu_info.l2_code_cache:&m_cpu_info.l2_data_cache; level=2; break;
    case 2: cache=sys_type==3?&m_cpu_info.l3_code_cache:&m_cpu_info.l3_data_cache; level=3; break;
  }
  if(cache)
  {
    cache->level=level;
    cache->size_kb=installed_size&0x8000?(installed_size&0x7fff)*64:installed_size;
    cache->speed_ns=speed_ns;
    switch(assoc)
    {
      case 0x03: cache->associativity="Direct Mapped"; break;
      case 0x04: cache->associativity="2-way Set-Associative"; break;
      case 0x05: cache->associativity="4-way Set-Associative"; break;
      case 0x06: cache->associativity="Fully Associative"; break;
      case 0x07: cache->associativity="8-way Set-Associative"; break;
      case 0x08: cache->associativity="16-way Set-Associative"; break;
      case 0x09: cache->associativity="12-way Set-Associative"; break;
      case 0x0a: cache->associativity="24-way Set-Associative"; break;
      case 0x0b: cache->associativity="32-way Set-Associative"; break;
      case 0x0c: cache->associativity="48-way Set-Associative"; break;
      case 0x0d: cache->associativity="64-way Set-Associative"; break;
    }
    switch(sys_type)
    {
      case 3: cache->type="Instruction "; break;
      case 4: cache->type="Data "; break;
    }
  }
}
//----

void system_info::parse_smbios_memory_device_info(bin_input_stream_base &stream_, unsigned size_)
{
  // 2.1+
  uint16_t phys_array_handle=0, error_info_handle=0;
  uint16_t total_width=0, data_width=0, size=0;
  uint8_t form_factor=0, device_set=0, device_locator=0, bank_locator=0;
  uint8_t memory_type=0;
  uint16_t type_detail=0;
  // 2.3+
  uint16_t speed=0;
  uint8_t manufacturer=0, serial=0, asset_tag=0, part_num=0;
  // 2.6+
  uint8_t attribs=0;
  // 2.7+
  uint32_t ext_size=0;
  uint16_t conf_clock_speed=0;

  // read parameters
  {
    auto_stream_seek<bin_input_stream_base> aseek(stream_, size_);
    if(size_>=17)
    {
      stream_>>phys_array_handle>>error_info_handle;
      stream_>>total_width>>data_width>>size;
      stream_>>form_factor>>device_set>>device_locator>>bank_locator;
      stream_>>memory_type;
      stream_>>type_detail;
    }
    if(size_>=23)
      stream_>>speed>>manufacturer>>serial>>asset_tag>>part_num;
    if(size_>=24)
      stream_>>attribs;
    if(size_>=30)
      stream_>>ext_size>>conf_clock_speed;
  }
  array<heap_str> strings;
  parse_smbios_strings(stream_, strings);

  memory_module_info &module=m_memory_modules.push_back();
  get_smbios_string(module.slot, bank_locator, strings);
  if(!module.slot.size())
    get_smbios_string(module.slot, device_locator, strings);
  module.size_mb=size;
  module.total_width=total_width;
  switch(form_factor)
  {
    case 0x03: module.type="SIMM"; break;
    case 0x04: module.type="SIP"; break;
    case 0x05: module.type="Chip"; break;
    case 0x06: module.type="DIP"; break;
    case 0x07: module.type="ZIP"; break;
    case 0x08: module.type="Proprietary Card"; break;
    case 0x09: module.type="DIMM"; break;
    case 0x0a: module.type="TSOP"; break;
    case 0x0b: module.type="Row of chips"; break;
    case 0x0c: module.type="RIMM"; break;
    case 0x0d: module.type="SODIMM"; break;
    case 0x0e: module.type="SRIMM"; break;
    case 0x0f: module.type="FB-DIMM"; break;
  }
  heap_str type_str;
  switch(memory_type)
  {
    case 0x03: type_str="DRAM"; break;
    case 0x04: type_str="EDRAM"; break;
    case 0x05: type_str="VRAM"; break;
    case 0x06: type_str="SRAM"; break;
    case 0x07: type_str="RAM"; break;
    case 0x08: type_str="ROM"; break;
    case 0x09: type_str="FLASH"; break;
    case 0x0a: type_str="EEPROM"; break;
    case 0x0b: type_str="FEPROM"; break;
    case 0x0c: type_str="EPROM"; break;
    case 0x0d: type_str="CDRAM"; break;
    case 0x0e: type_str="3DRAM"; break;
    case 0x0f: type_str="SDRAM"; break;
    case 0x10: type_str="SGRAM"; break;
    case 0x11: type_str="RDRAM"; break;
    case 0x12: type_str="DDR"; break;
    case 0x13: type_str="DDR2"; break;
    case 0x14: type_str="DDR FB-DIMM"; break;
    case 0x18: type_str="DDR3"; break;
    case 0x19: type_str="FBD2"; break;
  }
  if(type_str.size())
  {
    if(module.type.size())
      module.type+=' ';
    module.type+='(';
    module.type+=type_str;
    module.type+=')';
  }
  module.freq_mhz=speed;
}
//----------------------------------------------------------------------------


//============================================================================
// get_dll_version_str
//============================================================================
stack_str32 pfc::get_dll_version_str(const char *dll_filename_)
{
  stack_str32 version_str;
  HMODULE ver_module=LoadLibrary("version.dll");
  if(ver_module)
  {
    // get version function interfaces
    typedef DWORD(WINAPI *gfvis_t)(LPCTSTR, LPDWORD);
    typedef BOOL(WINAPI *gfvi_t)(LPCTSTR, DWORD, DWORD, LPVOID);
    typedef BOOL(WINAPI *vqv_t)(LPCVOID, LPCTSTR, LPVOID*, PUINT);
    gfvis_t gfvis=(gfvis_t)GetProcAddress(ver_module, "GetFileVersionInfoSizeA");
    gfvi_t gfvi=(gfvi_t)GetProcAddress(ver_module, "GetFileVersionInfoA");
    vqv_t vqv=(vqv_t)GetProcAddress(ver_module, "VerQueryValueA");
    if(gfvis && gfvi && vqv)
    {
      // get file version info for the dll
      DWORD dummy;
      unsigned info_size=gfvis(dll_filename_, &dummy);
      owner_data info_data=PFC_MEM_ALLOC(info_size);
      if(gfvi(dll_filename_, 0, info_size, info_data.data))
      {
        VS_FIXEDFILEINFO *ver_info=0;
        UINT info_size;
        if(vqv(info_data.data, "\\", (void**)&ver_info, &info_size))
          version_str.format("%i.%i.%i.%i", ver_info->dwFileVersionMS>>16, ver_info->dwFileVersionMS&0xffff, ver_info->dwFileVersionLS>>16, ver_info->dwFileVersionLS&0xffff);
      }
    }

    // release version.dll
    FreeLibrary(ver_module);
  }
  return version_str;
}
//----------------------------------------------------------------------------


//============================================================================
// get_call_stack
//============================================================================
void pfc::get_call_stack(heap_str &str_)
{
  // get procedure addresses & initialize symbol handler
  HMODULE module=LoadLibrary("dbghelp.dll");
  if(!module)
    return;
  typedef BOOL(WINAPI *stack_walk_64_t)(DWORD, HANDLE, HANDLE, LPSTACKFRAME64, PVOID, PREAD_PROCESS_MEMORY_ROUTINE64, PFUNCTION_TABLE_ACCESS_ROUTINE64, PGET_MODULE_BASE_ROUTINE64, PTRANSLATE_ADDRESS_ROUTINE64);
  typedef BOOL(WINAPI *sym_initialize_t)(HANDLE, PCTSTR, BOOL);
  typedef BOOL(WINAPI *sym_cleanup_t)(HANDLE);
  typedef PVOID(WINAPI *sym_function_table_access_64_t)(HANDLE, DWORD64);
  typedef DWORD64(WINAPI *sym_get_module_base_64_t)(HANDLE, DWORD64);
  typedef BOOL(WINAPI *sym_from_addr_t)(HANDLE, DWORD64 Address, PDWORD64, PSYMBOL_INFO);
  typedef BOOL(WINAPI *sym_get_line_from_addr_64_t)(HANDLE, DWORD64, PDWORD, PIMAGEHLP_LINE64);
  HANDLE process_handle=GetCurrentProcess();
  HANDLE thread_handle=GetCurrentThread();
  stack_walk_64_t sw64=(stack_walk_64_t)GetProcAddress(module, "StackWalk64");
  sym_initialize_t si=(sym_initialize_t)GetProcAddress(module, "SymInitialize");
  sym_cleanup_t sc=(sym_cleanup_t)GetProcAddress(module, "SymCleanup");
  sym_function_table_access_64_t sfta64=(sym_function_table_access_64_t)GetProcAddress(module, "SymFunctionTableAccess64");
  sym_get_module_base_64_t sgmb64=(sym_get_module_base_64_t)GetProcAddress(module, "SymGetModuleBase64");
  sym_from_addr_t sfa=(sym_from_addr_t)GetProcAddress(module, "SymFromAddr");
  sym_get_line_from_addr_64_t sglfa64=(sym_get_line_from_addr_64_t)GetProcAddress(module, "SymGetLineFromAddr64");
  if(!sw64 || !si || !sc || !sfta64 || !sgmb64 || !sfa || !(*si)(process_handle, NULL, TRUE))
  {
    FreeLibrary(module);
    return;
  }

  // get thread context & setup stack frame
  CONTEXT context_record;
  mem_zero(&context_record, sizeof(context_record));
  RtlCaptureContext(&context_record);
  STACKFRAME64 stack_frame;
  mem_zero(&stack_frame, sizeof(stack_frame));
  DWORD machine_type=0;
#ifdef PFC_PLATFORM_WIN32
  machine_type=IMAGE_FILE_MACHINE_I386;
  stack_frame.AddrPC.Offset=context_record.Eip;
  stack_frame.AddrPC.Mode=AddrModeFlat;
  stack_frame.AddrStack.Offset=context_record.Esp;
  stack_frame.AddrStack.Mode=AddrModeFlat;
  stack_frame.AddrFrame.Offset=context_record.Ebp;
  stack_frame.AddrFrame.Mode=AddrModeFlat;
#elif defined(PFC_PLATFORM_WIN64)
  machine_type=IMAGE_FILE_MACHINE_AMD64;
  stack_frame.AddrPC.Offset=context_record.Rip;
  stack_frame.AddrPC.Mode=AddrModeFlat;
  stack_frame.AddrFrame.Offset=context_record.Rsp;
  stack_frame.AddrFrame.Mode=AddrModeFlat;
  stack_frame.AddrStack.Offset=context_record.Rsp;
  stack_frame.AddrStack.Mode=AddrModeFlat;
#else
#error Unsupported platform for stack trace
#endif

  // setup symbol and line structures
  enum {max_symbol_name_len=1024};
  SYMBOL_INFO *symbol_info=(SYMBOL_INFO*)mem_alloc(sizeof(SYMBOL_INFO)+max_symbol_name_len);
  mem_zero(symbol_info, sizeof(*symbol_info));
  symbol_info->SizeOfStruct=sizeof(*symbol_info);
  symbol_info->MaxNameLen=max_symbol_name_len;
  IMAGEHLP_LINE64 line;
  mem_zero(&line, sizeof(line));
  line.SizeOfStruct=sizeof(line);

  // iterate through the call stack
  while((*sw64)(machine_type,
                process_handle,
                thread_handle,
                &stack_frame,
                &context_record,
                NULL,
                sfta64,
                sgmb64,
                NULL))
  {
    // check for infinite recursion
    if(stack_frame.AddrPC.Offset==stack_frame.AddrReturn.Offset)
    {
      /*infinite recursion*/
      str_+="Infinite recursion!\r\n";
      break;
    }

    // get function name
    DWORD64 disp_func_name=0;
    if(stack_frame.AddrPC.Offset && (*sfa)(process_handle, stack_frame.AddrPC.Offset, &disp_func_name, symbol_info))
    {
      str_+=symbol_info->Name;
      str_+="(...)";
    }
    else
      str_+="<unknown>(...)";

    // get line number
    DWORD disp_line=0;
    if(stack_frame.AddrPC.Offset && sglfa64 && (*sglfa64)(process_handle, stack_frame.AddrPC.Offset, &disp_line, &line))
    {
      str_.push_back_format(" Line %i", line.LineNumber);
      if(disp_line)
        str_.push_back_format(" + 0x%x bytes", disp_line);
    }
    str_+="\r\n";
  }

  // release resources
  mem_free(symbol_info);
  (*sc)(process_handle);
  FreeLibrary(module);
}
//----------------------------------------------------------------------------
