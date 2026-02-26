// Copyright 2021 The Dawn & Tint Authors
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef DAWNNATIVE_CHAIN_UTILS_H_
#define DAWNNATIVE_CHAIN_UTILS_H_

#include <tuple>

#include "absl/strings/str_format.h"
#include "dawn/native/dawn_platform.h"
#include "dawn/native/Error.h"
#include "dawn/native/wgpu_structs_autogen.h"

namespace dawn::native {
namespace detail {

// SType for implementation details. Kept inside the detail namespace for extensibility.
template <typename T>
constexpr inline wgpu::SType STypeForImpl = wgpu::SType(0u);

// Specialize STypeFor to map from native struct types to their SType.
template <>
constexpr inline wgpu::SType STypeForImpl<ShaderSourceSPIRV> =
    wgpu::SType::ShaderSourceSPIRV;
template <>
constexpr inline wgpu::SType STypeForImpl<ShaderSourceWGSL> =
    wgpu::SType::ShaderSourceWGSL;
template <>
constexpr inline wgpu::SType STypeForImpl<RenderPassMaxDrawCount> =
    wgpu::SType::RenderPassMaxDrawCount;
template <>
constexpr inline wgpu::SType STypeForImpl<SurfaceSourceMetalLayer> =
    wgpu::SType::SurfaceSourceMetalLayer;
template <>
constexpr inline wgpu::SType STypeForImpl<SurfaceSourceWindowsHWND> =
    wgpu::SType::SurfaceSourceWindowsHWND;
template <>
constexpr inline wgpu::SType STypeForImpl<SurfaceSourceXlibWindow> =
    wgpu::SType::SurfaceSourceXlibWindow;
template <>
constexpr inline wgpu::SType STypeForImpl<SurfaceSourceWaylandSurface> =
    wgpu::SType::SurfaceSourceWaylandSurface;
template <>
constexpr inline wgpu::SType STypeForImpl<SurfaceSourceAndroidNativeWindow> =
    wgpu::SType::SurfaceSourceAndroidNativeWindow;
template <>
constexpr inline wgpu::SType STypeForImpl<SurfaceSourceXCBWindow> =
    wgpu::SType::SurfaceSourceXCBWindow;
template <>
constexpr inline wgpu::SType STypeForImpl<SurfaceColorManagement> =
    wgpu::SType::SurfaceColorManagement;
template <>
constexpr inline wgpu::SType STypeForImpl<RequestAdapterWebXROptions> =
    wgpu::SType::RequestAdapterWebXROptions;
template <>
constexpr inline wgpu::SType STypeForImpl<TextureComponentSwizzleDescriptor> =
    wgpu::SType::TextureComponentSwizzleDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<CompatibilityModeLimits> =
    wgpu::SType::CompatibilityModeLimits;
template <>
constexpr inline wgpu::SType STypeForImpl<TextureBindingViewDimensionDescriptor> =
    wgpu::SType::TextureBindingViewDimensionDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SurfaceDescriptorFromWindowsCoreWindow> =
    wgpu::SType::SurfaceDescriptorFromWindowsCoreWindow;
template <>
constexpr inline wgpu::SType STypeForImpl<ExternalTextureBindingEntry> =
    wgpu::SType::ExternalTextureBindingEntry;
template <>
constexpr inline wgpu::SType STypeForImpl<ExternalTextureBindingLayout> =
    wgpu::SType::ExternalTextureBindingLayout;
template <>
constexpr inline wgpu::SType STypeForImpl<SurfaceDescriptorFromWindowsUWPSwapChainPanel> =
    wgpu::SType::SurfaceDescriptorFromWindowsUWPSwapChainPanel;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnTextureInternalUsageDescriptor> =
    wgpu::SType::DawnTextureInternalUsageDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnEncoderInternalUsageDescriptor> =
    wgpu::SType::DawnEncoderInternalUsageDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnCacheDeviceDescriptor> =
    wgpu::SType::DawnCacheDeviceDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnAdapterPropertiesPowerPreference> =
    wgpu::SType::DawnAdapterPropertiesPowerPreference;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnBufferDescriptorErrorInfoFromWireClient> =
    wgpu::SType::DawnBufferDescriptorErrorInfoFromWireClient;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnTogglesDescriptor> =
    wgpu::SType::DawnTogglesDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnShaderModuleSPIRVOptionsDescriptor> =
    wgpu::SType::DawnShaderModuleSPIRVOptionsDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnRenderPassSampleCount> =
    wgpu::SType::DawnRenderPassSampleCount;
template <>
constexpr inline wgpu::SType STypeForImpl<RenderPassPixelLocalStorage> =
    wgpu::SType::RenderPassPixelLocalStorage;
template <>
constexpr inline wgpu::SType STypeForImpl<PipelineLayoutPixelLocalStorage> =
    wgpu::SType::PipelineLayoutPixelLocalStorage;
template <>
constexpr inline wgpu::SType STypeForImpl<BufferHostMappedPointer> =
    wgpu::SType::BufferHostMappedPointer;
template <>
constexpr inline wgpu::SType STypeForImpl<AdapterPropertiesMemoryHeaps> =
    wgpu::SType::AdapterPropertiesMemoryHeaps;
template <>
constexpr inline wgpu::SType STypeForImpl<AdapterPropertiesD3D> =
    wgpu::SType::AdapterPropertiesD3D;
template <>
constexpr inline wgpu::SType STypeForImpl<AdapterPropertiesVk> =
    wgpu::SType::AdapterPropertiesVk;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnWireWGSLControl> =
    wgpu::SType::DawnWireWGSLControl;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnWGSLBlocklist> =
    wgpu::SType::DawnWGSLBlocklist;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnDrmFormatCapabilities> =
    wgpu::SType::DawnDrmFormatCapabilities;
template <>
constexpr inline wgpu::SType STypeForImpl<ShaderModuleCompilationOptions> =
    wgpu::SType::ShaderModuleCompilationOptions;
template <>
constexpr inline wgpu::SType STypeForImpl<ColorTargetStateExpandResolveTextureDawn> =
    wgpu::SType::ColorTargetStateExpandResolveTextureDawn;
template <>
constexpr inline wgpu::SType STypeForImpl<RenderPassDescriptorExpandResolveRect> =
    wgpu::SType::RenderPassDescriptorExpandResolveRect;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryVkDedicatedAllocationDescriptor> =
    wgpu::SType::SharedTextureMemoryVkDedicatedAllocationDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryAHardwareBufferDescriptor> =
    wgpu::SType::SharedTextureMemoryAHardwareBufferDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryDmaBufDescriptor> =
    wgpu::SType::SharedTextureMemoryDmaBufDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryOpaqueFDDescriptor> =
    wgpu::SType::SharedTextureMemoryOpaqueFDDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryZirconHandleDescriptor> =
    wgpu::SType::SharedTextureMemoryZirconHandleDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryDXGISharedHandleDescriptor> =
    wgpu::SType::SharedTextureMemoryDXGISharedHandleDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryIOSurfaceDescriptor> =
    wgpu::SType::SharedTextureMemoryIOSurfaceDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryEGLImageDescriptor> =
    wgpu::SType::SharedTextureMemoryEGLImageDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryVkImageLayoutBeginState> =
    wgpu::SType::SharedTextureMemoryVkImageLayoutBeginState;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryVkImageLayoutEndState> =
    wgpu::SType::SharedTextureMemoryVkImageLayoutEndState;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryD3DSwapchainBeginState> =
    wgpu::SType::SharedTextureMemoryD3DSwapchainBeginState;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceVkSemaphoreOpaqueFDDescriptor> =
    wgpu::SType::SharedFenceVkSemaphoreOpaqueFDDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceVkSemaphoreOpaqueFDExportInfo> =
    wgpu::SType::SharedFenceVkSemaphoreOpaqueFDExportInfo;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceSyncFDDescriptor> =
    wgpu::SType::SharedFenceSyncFDDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceSyncFDExportInfo> =
    wgpu::SType::SharedFenceSyncFDExportInfo;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceVkSemaphoreZirconHandleDescriptor> =
    wgpu::SType::SharedFenceVkSemaphoreZirconHandleDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceVkSemaphoreZirconHandleExportInfo> =
    wgpu::SType::SharedFenceVkSemaphoreZirconHandleExportInfo;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceDXGISharedHandleDescriptor> =
    wgpu::SType::SharedFenceDXGISharedHandleDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceDXGISharedHandleExportInfo> =
    wgpu::SType::SharedFenceDXGISharedHandleExportInfo;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceMTLSharedEventDescriptor> =
    wgpu::SType::SharedFenceMTLSharedEventDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceMTLSharedEventExportInfo> =
    wgpu::SType::SharedFenceMTLSharedEventExportInfo;
template <>
constexpr inline wgpu::SType STypeForImpl<StaticSamplerBindingLayout> =
    wgpu::SType::StaticSamplerBindingLayout;
template <>
constexpr inline wgpu::SType STypeForImpl<YCbCrVkDescriptor> =
    wgpu::SType::YCbCrVkDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryAHardwareBufferProperties> =
    wgpu::SType::SharedTextureMemoryAHardwareBufferProperties;
template <>
constexpr inline wgpu::SType STypeForImpl<AHardwareBufferProperties> =
    wgpu::SType::AHardwareBufferProperties;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnTexelCopyBufferRowAlignmentLimits> =
    wgpu::SType::DawnTexelCopyBufferRowAlignmentLimits;
template <>
constexpr inline wgpu::SType STypeForImpl<AdapterPropertiesSubgroupMatrixConfigs> =
    wgpu::SType::AdapterPropertiesSubgroupMatrixConfigs;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceEGLSyncDescriptor> =
    wgpu::SType::SharedFenceEGLSyncDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedFenceEGLSyncExportInfo> =
    wgpu::SType::SharedFenceEGLSyncExportInfo;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnInjectedInvalidSType> =
    wgpu::SType::DawnInjectedInvalidSType;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnCompilationMessageUtf16> =
    wgpu::SType::DawnCompilationMessageUtf16;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnFakeBufferOOMForTesting> =
    wgpu::SType::DawnFakeBufferOOMForTesting;
template <>
constexpr inline wgpu::SType STypeForImpl<SurfaceDescriptorFromWindowsWinUISwapChainPanel> =
    wgpu::SType::SurfaceDescriptorFromWindowsWinUISwapChainPanel;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnDeviceAllocatorControl> =
    wgpu::SType::DawnDeviceAllocatorControl;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnHostMappedPointerLimits> =
    wgpu::SType::DawnHostMappedPointerLimits;
template <>
constexpr inline wgpu::SType STypeForImpl<RenderPassDescriptorResolveRect> =
    wgpu::SType::RenderPassDescriptorResolveRect;
template <>
constexpr inline wgpu::SType STypeForImpl<RequestAdapterWebGPUBackendOptions> =
    wgpu::SType::RequestAdapterWebGPUBackendOptions;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnFakeDeviceInitializeErrorForTesting> =
    wgpu::SType::DawnFakeDeviceInitializeErrorForTesting;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryD3D11BeginState> =
    wgpu::SType::SharedTextureMemoryD3D11BeginState;
template <>
constexpr inline wgpu::SType STypeForImpl<DawnConsumeAdapterDescriptor> =
    wgpu::SType::DawnConsumeAdapterDescriptor;
template <>
constexpr inline wgpu::SType STypeForImpl<TexelBufferBindingEntry> =
    wgpu::SType::TexelBufferBindingEntry;
template <>
constexpr inline wgpu::SType STypeForImpl<TexelBufferBindingLayout> =
    wgpu::SType::TexelBufferBindingLayout;
template <>
constexpr inline wgpu::SType STypeForImpl<SharedTextureMemoryMetalEndAccessState> =
    wgpu::SType::SharedTextureMemoryMetalEndAccessState;
template <>
constexpr inline wgpu::SType STypeForImpl<AdapterPropertiesWGPU> =
    wgpu::SType::AdapterPropertiesWGPU;
template <>
constexpr inline wgpu::SType STypeForImpl<PipelineLayoutResourceTable> =
    wgpu::SType::PipelineLayoutResourceTable;
template <>
constexpr inline wgpu::SType STypeForImpl<AdapterPropertiesExplicitComputeSubgroupSizeConfigs> =
    wgpu::SType::AdapterPropertiesExplicitComputeSubgroupSizeConfigs;

template <typename Arg, typename... Rest>
std::string STypesToString() {
    if constexpr (sizeof...(Rest)) {
        return absl::StrFormat("%s, ", STypeForImpl<Arg>) + STypesToString<Rest...>();
    } else {
        return absl::StrFormat("%s", STypeForImpl<Arg>);
    }
}

// Typelist type used to further add extensions to chain roots when they are not in the json.
template <typename... Exts>
struct AdditionalExtensionsList;

// Root specializations for adding additional extensions.
template <typename Root>
struct AdditionalExtensions {
    using List = AdditionalExtensionsList<>;
};

// Template structs to get the typing for the unpacked chains.
template <typename...>
struct UnpackedPtrChain;
template <typename... Additionals, typename... Ts>
struct UnpackedPtrChain<AdditionalExtensionsList<Additionals...>, Ts...> {
    using Type = std::tuple<Ts..., Additionals...>;
};

}  // namespace detail

template <typename T>
constexpr inline wgpu::SType STypeFor = detail::STypeForImpl<T>;
template <typename T>
constexpr inline wgpu::SType STypeFor<const T*> = detail::STypeForImpl<T>;

}  // namespace dawn::native

// Include specializations before declaring types for ordering purposes.
#include "dawn/native/ChainUtilsImpl.inl"

namespace dawn::native {
namespace detail {

// Template type to get the unpacked chain type from the root type.
template <typename Root>
struct UnpackedPtrTypeFor;

// Template for extensible structures typing.
enum class Extensibility { In, Out };
template <typename T>
inline Extensibility ExtensibilityFor;

template <>
struct UnpackedPtrTypeFor<BindingResource> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<BindingResource>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<BindingResource> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<BufferBindingLayout> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<BufferBindingLayout>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<BufferBindingLayout> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<CommandBufferDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<CommandBufferDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<CommandBufferDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<ConstantEntry> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<ConstantEntry>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<ConstantEntry> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<CopyTextureForBrowserOptions> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<CopyTextureForBrowserOptions>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<CopyTextureForBrowserOptions> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<InstanceLimits> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<InstanceLimits>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<InstanceLimits> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<MultisampleState> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<MultisampleState>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<MultisampleState> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<PassTimestampWrites> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<PassTimestampWrites>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<PassTimestampWrites> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<PipelineLayoutStorageAttachment> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<PipelineLayoutStorageAttachment>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<PipelineLayoutStorageAttachment> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<PrimitiveState> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<PrimitiveState>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<PrimitiveState> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<QuerySetDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<QuerySetDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<QuerySetDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<QueueDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<QueueDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<QueueDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<RenderBundleDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<RenderBundleDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<RenderBundleDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<RenderBundleEncoderDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<RenderBundleEncoderDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<RenderBundleEncoderDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<RenderPassDepthStencilAttachment> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<RenderPassDepthStencilAttachment>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<RenderPassDepthStencilAttachment> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<ResourceTableDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<ResourceTableDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<ResourceTableDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SamplerBindingLayout> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SamplerBindingLayout>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SamplerBindingLayout> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SharedBufferMemoryBeginAccessDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SharedBufferMemoryBeginAccessDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SharedBufferMemoryBeginAccessDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SharedBufferMemoryDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SharedBufferMemoryDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SharedBufferMemoryDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SharedBufferMemoryEndAccessState> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SharedBufferMemoryEndAccessState>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SharedBufferMemoryEndAccessState> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<SharedBufferMemoryProperties> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SharedBufferMemoryProperties>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SharedBufferMemoryProperties> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<StorageTextureBindingLayout> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<StorageTextureBindingLayout>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<StorageTextureBindingLayout> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SurfaceCapabilities> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SurfaceCapabilities>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SurfaceCapabilities> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<SurfaceConfiguration> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SurfaceConfiguration>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SurfaceConfiguration> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SurfaceTexture> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SurfaceTexture>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SurfaceTexture> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<TexelBufferViewDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<TexelBufferViewDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<TexelBufferViewDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<TextureBindingLayout> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<TextureBindingLayout>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<TextureBindingLayout> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<VertexAttribute> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<VertexAttribute>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<VertexAttribute> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<BindGroupEntry> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<BindGroupEntry>::List
        , const ExternalTextureBindingEntry*
        , const TexelBufferBindingEntry*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<BindGroupEntry> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<BindGroupLayoutEntry> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<BindGroupLayoutEntry>::List
        , const StaticSamplerBindingLayout*
        , const ExternalTextureBindingLayout*
        , const TexelBufferBindingLayout*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<BindGroupLayoutEntry> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<BufferDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<BufferDescriptor>::List
        , const BufferHostMappedPointer*
        , const DawnFakeBufferOOMForTesting*
        , const DawnBufferDescriptorErrorInfoFromWireClient*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<BufferDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<CommandEncoderDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<CommandEncoderDescriptor>::List
        , const DawnEncoderInternalUsageDescriptor*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<CommandEncoderDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<CompilationMessage> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<CompilationMessage>::List
        , const DawnCompilationMessageUtf16*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<CompilationMessage> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<ComputePassDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<ComputePassDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<ComputePassDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<ComputeState> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<ComputeState>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<ComputeState> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<DepthStencilState> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<DepthStencilState>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<DepthStencilState> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<ExternalTextureDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<ExternalTextureDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<ExternalTextureDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<ImageCopyExternalTexture> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<ImageCopyExternalTexture>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<ImageCopyExternalTexture> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<InstanceDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<InstanceDescriptor>::List
        , const DawnTogglesDescriptor*
        , const DawnWGSLBlocklist*
        , const DawnWireWGSLControl*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<InstanceDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<Limits> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<Limits>::List
        , CompatibilityModeLimits*
        , DawnTexelCopyBufferRowAlignmentLimits*
        , DawnHostMappedPointerLimits*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<Limits> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<RenderPassColorAttachment> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<RenderPassColorAttachment>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<RenderPassColorAttachment> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<RenderPassStorageAttachment> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<RenderPassStorageAttachment>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<RenderPassStorageAttachment> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<RequestAdapterOptions> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<RequestAdapterOptions>::List
        , const RequestAdapterWebXROptions*
        , const RequestAdapterWebGPUBackendOptions*
        , const DawnTogglesDescriptor*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<RequestAdapterOptions> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SamplerDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SamplerDescriptor>::List
        , const YCbCrVkDescriptor*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SamplerDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<ShaderModuleDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<ShaderModuleDescriptor>::List
        , const ShaderSourceSPIRV*
        , const ShaderSourceWGSL*
        , const DawnShaderModuleSPIRVOptionsDescriptor*
        , const ShaderModuleCompilationOptions*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<ShaderModuleDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SharedFenceDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SharedFenceDescriptor>::List
        , const SharedFenceVkSemaphoreOpaqueFDDescriptor*
        , const SharedFenceSyncFDDescriptor*
        , const SharedFenceVkSemaphoreZirconHandleDescriptor*
        , const SharedFenceDXGISharedHandleDescriptor*
        , const SharedFenceMTLSharedEventDescriptor*
        , const SharedFenceEGLSyncDescriptor*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SharedFenceDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SharedFenceExportInfo> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SharedFenceExportInfo>::List
        , SharedFenceVkSemaphoreOpaqueFDExportInfo*
        , SharedFenceSyncFDExportInfo*
        , SharedFenceVkSemaphoreZirconHandleExportInfo*
        , SharedFenceDXGISharedHandleExportInfo*
        , SharedFenceMTLSharedEventExportInfo*
        , SharedFenceEGLSyncExportInfo*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SharedFenceExportInfo> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<SharedTextureMemoryBeginAccessDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SharedTextureMemoryBeginAccessDescriptor>::List
        , const SharedTextureMemoryVkImageLayoutBeginState*
        , const SharedTextureMemoryD3DSwapchainBeginState*
        , const SharedTextureMemoryD3D11BeginState*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SharedTextureMemoryBeginAccessDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SurfaceDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SurfaceDescriptor>::List
        , const SurfaceSourceAndroidNativeWindow*
        , const SurfaceSourceMetalLayer*
        , const SurfaceSourceWindowsHWND*
        , const SurfaceSourceXCBWindow*
        , const SurfaceSourceXlibWindow*
        , const SurfaceSourceWaylandSurface*
        , const SurfaceDescriptorFromWindowsCoreWindow*
        , const SurfaceDescriptorFromWindowsUWPSwapChainPanel*
        , const SurfaceDescriptorFromWindowsWinUISwapChainPanel*
        , const SurfaceColorManagement*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SurfaceDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<TextureDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<TextureDescriptor>::List
        , const TextureBindingViewDimensionDescriptor*
        , const DawnTextureInternalUsageDescriptor*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<TextureDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<VertexBufferLayout> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<VertexBufferLayout>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<VertexBufferLayout> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<AdapterInfo> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<AdapterInfo>::List
        , DawnAdapterPropertiesPowerPreference*
        , AdapterPropertiesMemoryHeaps*
        , AdapterPropertiesD3D*
        , AdapterPropertiesVk*
        , AdapterPropertiesWGPU*
        , AdapterPropertiesSubgroupMatrixConfigs*
        , AdapterPropertiesExplicitComputeSubgroupSizeConfigs*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<AdapterInfo> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<BindGroupDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<BindGroupDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<BindGroupDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<BindGroupLayoutDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<BindGroupLayoutDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<BindGroupLayoutDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<ColorTargetState> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<ColorTargetState>::List
        , const ColorTargetStateExpandResolveTextureDawn*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<ColorTargetState> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<CompilationInfo> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<CompilationInfo>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<CompilationInfo> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<ComputePipelineDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<ComputePipelineDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<ComputePipelineDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<DawnFormatCapabilities> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<DawnFormatCapabilities>::List
        , DawnDrmFormatCapabilities*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<DawnFormatCapabilities> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<DeviceDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<DeviceDescriptor>::List
        , const DawnConsumeAdapterDescriptor*
        , const DawnTogglesDescriptor*
        , const DawnCacheDeviceDescriptor*
        , const DawnDeviceAllocatorControl*
        , const DawnFakeDeviceInitializeErrorForTesting*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<DeviceDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<PipelineLayoutDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<PipelineLayoutDescriptor>::List
        , const PipelineLayoutResourceTable*
        , const PipelineLayoutPixelLocalStorage*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<PipelineLayoutDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SharedTextureMemoryDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SharedTextureMemoryDescriptor>::List
        , const SharedTextureMemoryVkDedicatedAllocationDescriptor*
        , const SharedTextureMemoryAHardwareBufferDescriptor*
        , const SharedTextureMemoryDmaBufDescriptor*
        , const SharedTextureMemoryOpaqueFDDescriptor*
        , const SharedTextureMemoryZirconHandleDescriptor*
        , const SharedTextureMemoryDXGISharedHandleDescriptor*
        , const SharedTextureMemoryIOSurfaceDescriptor*
        , const SharedTextureMemoryEGLImageDescriptor*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SharedTextureMemoryDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<SharedTextureMemoryEndAccessState> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SharedTextureMemoryEndAccessState>::List
        , SharedTextureMemoryMetalEndAccessState*
        , SharedTextureMemoryVkImageLayoutEndState*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SharedTextureMemoryEndAccessState> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<SharedTextureMemoryProperties> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<SharedTextureMemoryProperties>::List
        , SharedTextureMemoryAHardwareBufferProperties*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<SharedTextureMemoryProperties> = Extensibility::Out;

template <>
struct UnpackedPtrTypeFor<TextureViewDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<TextureViewDescriptor>::List
        , const TextureComponentSwizzleDescriptor*
        , const YCbCrVkDescriptor*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<TextureViewDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<VertexState> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<VertexState>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<VertexState> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<FragmentState> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<FragmentState>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<FragmentState> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<RenderPassDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<RenderPassDescriptor>::List
        , const DawnRenderPassSampleCount*
        , const RenderPassMaxDrawCount*
        , const RenderPassDescriptorExpandResolveRect*
        , const RenderPassDescriptorResolveRect*
        , const RenderPassPixelLocalStorage*
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<RenderPassDescriptor> = Extensibility::In;

template <>
struct UnpackedPtrTypeFor<RenderPipelineDescriptor> {
    using Type = UnpackedPtrChain<
        AdditionalExtensions<RenderPipelineDescriptor>::List
    >::Type;
};
template <>
constexpr inline Extensibility ExtensibilityFor<RenderPipelineDescriptor> = Extensibility::In;


}  // namespace detail

}  // namespace dawn::native

#endif  // DAWNNATIVE_CHAIN_UTILS_H_
