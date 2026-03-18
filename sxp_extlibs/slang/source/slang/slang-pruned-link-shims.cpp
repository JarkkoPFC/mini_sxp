// slang-pruned-link-shims.cpp
#include "../core/slang-common.h"
#include "slang.h"
#include "../compiler-core/slang-glslang-compiler.h"
#include "../compiler-core/slang-llvm-compiler.h"
#include "../compiler-core/slang-metal-compiler.h"
#include "../compiler-core/slang-nvrtc-compiler.h"
#include "../compiler-core/slang-tint-compiler.h"

namespace
{
using namespace Slang;
} // namespace <anonymous>

String get_slang_cuda_prelude()
{
    return String();
}
//----

String get_slang_cpp_prelude()
{
    return String();
}
//----

String get_slang_hlsl_prelude()
{
    return String();
}
//----

String get_slang_cpp_host_prelude()
{
    return String();
}
//----

String get_slang_torch_prelude()
{
    return String();
}

namespace Slang
{
bool isDeclKeyword(const UnownedStringSlice&)
{
    SLANG_ASSERT(!"Pruned Slang shim function was called");
    return false;
}
//----

SlangResult GlslangDownstreamCompilerUtil::locateCompilers(const String&, ISlangSharedLibraryLoader*, DownstreamCompilerSet*)
{
    SLANG_ASSERT(!"Pruned Slang shim function was called");
    return SLANG_FAIL;
}
//----

SlangResult SpirvOptDownstreamCompilerUtil::locateCompilers(const String&, ISlangSharedLibraryLoader*, DownstreamCompilerSet*)
{
    SLANG_ASSERT(!"Pruned Slang shim function was called");
    return SLANG_FAIL;
}
//----

SlangResult SpirvDisDownstreamCompilerUtil::locateCompilers(const String&, ISlangSharedLibraryLoader*, DownstreamCompilerSet*)
{
    SLANG_ASSERT(!"Pruned Slang shim function was called");
    return SLANG_FAIL;
}
//----

SlangResult MetalDownstreamCompilerUtil::locateCompilers(const String&, ISlangSharedLibraryLoader*, DownstreamCompilerSet*)
{
    SLANG_ASSERT(!"Pruned Slang shim function was called");
    return SLANG_FAIL;
}
//----

SlangResult NVRTCDownstreamCompilerUtil::locateCompilers(const String&, ISlangSharedLibraryLoader*, DownstreamCompilerSet*)
{
    SLANG_ASSERT(!"Pruned Slang shim function was called");
    return SLANG_FAIL;
}
//----

SlangResult TintDownstreamCompilerUtil::locateCompilers(const String&, ISlangSharedLibraryLoader*, DownstreamCompilerSet*)
{
    SLANG_ASSERT(!"Pruned Slang shim function was called");
    return SLANG_FAIL;
}
} // namespace Slang
