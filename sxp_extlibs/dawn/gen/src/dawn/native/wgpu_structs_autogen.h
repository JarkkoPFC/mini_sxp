
#ifndef DAWNNATIVE_WGPU_STRUCTS_H_
#define DAWNNATIVE_WGPU_STRUCTS_H_

#include "absl/strings/string_view.h"
#include "dawn/webgpu_cpp.h"
#include "dawn/native/Forward.h"

#include <cmath>
#include <optional>
#include <string_view>

namespace dawn::native {


    using wgpu::ChainedStruct;
    using wgpu::ChainedStructOut;


    struct StringView {
        char const * data = nullptr;
        size_t length = WGPU_STRLEN;

        inline constexpr StringView() noexcept = default;

// NOLINTNEXTLINE(runtime/explicit) allow implicit construction
inline constexpr StringView(const std::string_view& sv) noexcept {
    this->data = sv.data();
    this->length = sv.length();
}

// NOLINTNEXTLINE(runtime/explicit) allow implicit construction
inline constexpr StringView(const char* s) {
    this->data = s;
    this->length = WGPU_STRLEN;  // use strlen
}

// NOLINTNEXTLINE(runtime/explicit) allow implicit construction
inline constexpr StringView(WGPUStringView s) {
    this->data = s.data;
    this->length = s.length;
}

inline constexpr StringView(const char* data, size_t length) {
    this->data = data;
    this->length = length;
}

// NOLINTNEXTLINE(runtime/explicit) allow implicit construction
inline constexpr StringView(std::nullptr_t) {
    this->data = nullptr;
    this->length = WGPU_STRLEN;
}

// NOLINTNEXTLINE(runtime/explicit) allow implicit construction
inline constexpr StringView(std::nullopt_t) {
    this->data = nullptr;
    this->length = WGPU_STRLEN;
}

bool IsUndefined() const {
    return this->data == nullptr && this->length == wgpu::kStrlen;
}

// NOLINTNEXTLINE(runtime/explicit) allow implicit conversion
operator std::string_view() const {
    if (this->length == wgpu::kStrlen) {
        if (IsUndefined()) {
            return {};
        }
        return {this->data};
    }
    return {this->data, this->length};
}

template <typename View,
          typename = std::enable_if_t<std::is_constructible_v<View, const char*, size_t>>>
explicit operator View() const {
    if (this->length == wgpu::kStrlen) {
        if (IsUndefined()) {
            return {};
        }
        return {this->data};
    }
    return {this->data, this->length};
}


        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const StringView& rhs) const;

        #ifndef ABSL_USES_STD_STRING_VIEW
        // NOLINTNEXTLINE(runtime/explicit) allow implicit conversion
        operator absl::string_view() const {
            if (this->length == wgpu::kStrlen) {
                if (IsUndefined()) {
                    return {};
                }
                return {this->data};
            }
            return {this->data, this->length};
        }
        #endif
    };

    struct AdapterPropertiesD3D : ChainedStructOut {
        AdapterPropertiesD3D() {
            sType = wgpu::SType::AdapterPropertiesD3D;
        }
        alignas(wgpu::AdapterPropertiesD3D::kFirstMemberAlignment) uint32_t shaderModel;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const AdapterPropertiesD3D& rhs) const;

    };

    struct AdapterPropertiesExplicitComputeSubgroupSizeConfigs : ChainedStructOut {
        AdapterPropertiesExplicitComputeSubgroupSizeConfigs() {
            sType = wgpu::SType::AdapterPropertiesExplicitComputeSubgroupSizeConfigs;
        }
        alignas(wgpu::AdapterPropertiesExplicitComputeSubgroupSizeConfigs::kFirstMemberAlignment) uint32_t minExplicitComputeSubgroupSize;
        uint32_t maxExplicitComputeSubgroupSize;
        uint32_t maxComputeWorkgroupSubgroups;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const AdapterPropertiesExplicitComputeSubgroupSizeConfigs& rhs) const;

    };

    struct AdapterPropertiesVk : ChainedStructOut {
        AdapterPropertiesVk() {
            sType = wgpu::SType::AdapterPropertiesVk;
        }
        alignas(wgpu::AdapterPropertiesVk::kFirstMemberAlignment) uint32_t driverVersion;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const AdapterPropertiesVk& rhs) const;

    };

    struct AdapterPropertiesWGPU : ChainedStructOut {
        AdapterPropertiesWGPU() {
            sType = wgpu::SType::AdapterPropertiesWGPU;
        }
        alignas(wgpu::AdapterPropertiesWGPU::kFirstMemberAlignment) wgpu::BackendType backendType = wgpu::BackendType::Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const AdapterPropertiesWGPU& rhs) const;

    };

    struct BindingResource {
        ChainedStruct const * nextInChain = nullptr;
        BufferBase* buffer = nullptr;
        uint64_t offset = 0;
        uint64_t size = wgpu::kWholeSize;
        SamplerBase* sampler = nullptr;
        TextureViewBase* textureView = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BindingResource& rhs) const;

    };

    struct BlendComponent {
        wgpu::BlendOperation operation = wgpu::BlendOperation::Add;
        wgpu::BlendFactor srcFactor = wgpu::BlendFactor::One;
        wgpu::BlendFactor dstFactor = wgpu::BlendFactor::Zero;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] BlendComponent WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BlendComponent& rhs) const;

    };

    struct BufferBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::BufferBindingType type = wgpu::BufferBindingType::Uniform;
        wgpu::Bool hasDynamicOffset = false;
        uint64_t minBindingSize = 0;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] BufferBindingLayout WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BufferBindingLayout& rhs) const;

    };

    struct BufferHostMappedPointer : ChainedStruct {
        BufferHostMappedPointer() {
            sType = wgpu::SType::BufferHostMappedPointer;
        }
        alignas(wgpu::BufferHostMappedPointer::kFirstMemberAlignment) void * pointer;
        WGPUCallback disposeCallback;
        void * userdata;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BufferHostMappedPointer& rhs) const;

    };

    struct Color {
        double r;
        double g;
        double b;
        double a;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Color& rhs) const;

    };

    struct ColorTargetStateExpandResolveTextureDawn : ChainedStruct {
        ColorTargetStateExpandResolveTextureDawn() {
            sType = wgpu::SType::ColorTargetStateExpandResolveTextureDawn;
        }
        alignas(wgpu::ColorTargetStateExpandResolveTextureDawn::kFirstMemberAlignment) wgpu::Bool enabled = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ColorTargetStateExpandResolveTextureDawn& rhs) const;

    };

    struct CommandBufferDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CommandBufferDescriptor& rhs) const;

    };

    struct CompatibilityModeLimits : ChainedStructOut {
        CompatibilityModeLimits() {
            sType = wgpu::SType::CompatibilityModeLimits;
        }
        alignas(wgpu::CompatibilityModeLimits::kFirstMemberAlignment) uint32_t maxStorageBuffersInVertexStage = wgpu::kLimitU32Undefined;
        uint32_t maxStorageTexturesInVertexStage = wgpu::kLimitU32Undefined;
        uint32_t maxStorageBuffersInFragmentStage = wgpu::kLimitU32Undefined;
        uint32_t maxStorageTexturesInFragmentStage = wgpu::kLimitU32Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CompatibilityModeLimits& rhs) const;

    };

    struct ConstantEntry {
        ChainedStruct const * nextInChain = nullptr;
        StringView key;
        double value;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ConstantEntry& rhs) const;

    };

    struct CopyTextureForBrowserOptions {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::Bool flipY = false;
        wgpu::Bool needsColorSpaceConversion = false;
        wgpu::AlphaMode srcAlphaMode = wgpu::AlphaMode::Unpremultiplied;
        float const * srcTransferFunctionParameters = nullptr;
        float const * conversionMatrix = nullptr;
        float const * dstTransferFunctionParameters = nullptr;
        wgpu::AlphaMode dstAlphaMode = wgpu::AlphaMode::Unpremultiplied;
        wgpu::Bool internalUsage = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CopyTextureForBrowserOptions& rhs) const;

    };

    struct DawnAdapterPropertiesPowerPreference : ChainedStructOut {
        DawnAdapterPropertiesPowerPreference() {
            sType = wgpu::SType::DawnAdapterPropertiesPowerPreference;
        }
        alignas(wgpu::DawnAdapterPropertiesPowerPreference::kFirstMemberAlignment) wgpu::PowerPreference powerPreference = wgpu::PowerPreference::Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnAdapterPropertiesPowerPreference& rhs) const;

    };

    struct DawnBufferDescriptorErrorInfoFromWireClient : ChainedStruct {
        DawnBufferDescriptorErrorInfoFromWireClient() {
            sType = wgpu::SType::DawnBufferDescriptorErrorInfoFromWireClient;
        }
        alignas(wgpu::DawnBufferDescriptorErrorInfoFromWireClient::kFirstMemberAlignment) wgpu::Bool outOfMemory = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnBufferDescriptorErrorInfoFromWireClient& rhs) const;

    };

    struct DawnCacheDeviceDescriptor : ChainedStruct {
        DawnCacheDeviceDescriptor() {
            sType = wgpu::SType::DawnCacheDeviceDescriptor;
        }
        alignas(wgpu::DawnCacheDeviceDescriptor::kFirstMemberAlignment) StringView isolationKey;
        WGPUDawnLoadCacheDataFunction loadDataFunction = nullptr;
        WGPUDawnStoreCacheDataFunction storeDataFunction = nullptr;
        void * functionUserdata = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnCacheDeviceDescriptor& rhs) const;

    };

    struct DawnCompilationMessageUtf16 : ChainedStruct {
        DawnCompilationMessageUtf16() {
            sType = wgpu::SType::DawnCompilationMessageUtf16;
        }
        alignas(wgpu::DawnCompilationMessageUtf16::kFirstMemberAlignment) uint64_t linePos;
        uint64_t offset;
        uint64_t length;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnCompilationMessageUtf16& rhs) const;

    };

    struct DawnConsumeAdapterDescriptor : ChainedStruct {
        DawnConsumeAdapterDescriptor() {
            sType = wgpu::SType::DawnConsumeAdapterDescriptor;
        }
        alignas(wgpu::DawnConsumeAdapterDescriptor::kFirstMemberAlignment) wgpu::Bool consumeAdapter = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnConsumeAdapterDescriptor& rhs) const;

    };

    struct DawnDeviceAllocatorControl : ChainedStruct {
        DawnDeviceAllocatorControl() {
            sType = wgpu::SType::DawnDeviceAllocatorControl;
        }
        alignas(wgpu::DawnDeviceAllocatorControl::kFirstMemberAlignment) size_t allocatorHeapBlockSize = 0;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnDeviceAllocatorControl& rhs) const;

    };

    struct DawnDrmFormatProperties {
        uint64_t modifier;
        uint32_t modifierPlaneCount;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnDrmFormatProperties& rhs) const;

    };

    struct DawnEncoderInternalUsageDescriptor : ChainedStruct {
        DawnEncoderInternalUsageDescriptor() {
            sType = wgpu::SType::DawnEncoderInternalUsageDescriptor;
        }
        alignas(wgpu::DawnEncoderInternalUsageDescriptor::kFirstMemberAlignment) wgpu::Bool useInternalUsages = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnEncoderInternalUsageDescriptor& rhs) const;

    };

    struct DawnFakeBufferOOMForTesting : ChainedStruct {
        DawnFakeBufferOOMForTesting() {
            sType = wgpu::SType::DawnFakeBufferOOMForTesting;
        }
        alignas(wgpu::DawnFakeBufferOOMForTesting::kFirstMemberAlignment) wgpu::Bool fakeOOMAtWireClientMap;
        wgpu::Bool fakeOOMAtNativeMap;
        wgpu::Bool fakeOOMAtDevice;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnFakeBufferOOMForTesting& rhs) const;

    };

    struct DawnFakeDeviceInitializeErrorForTesting : ChainedStruct {
        DawnFakeDeviceInitializeErrorForTesting() {
            sType = wgpu::SType::DawnFakeDeviceInitializeErrorForTesting;
        }

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnFakeDeviceInitializeErrorForTesting& rhs) const;

    };

    struct DawnHostMappedPointerLimits : ChainedStructOut {
        DawnHostMappedPointerLimits() {
            sType = wgpu::SType::DawnHostMappedPointerLimits;
        }
        alignas(wgpu::DawnHostMappedPointerLimits::kFirstMemberAlignment) uint32_t hostMappedPointerAlignment = wgpu::kLimitU32Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnHostMappedPointerLimits& rhs) const;

    };

    struct DawnInjectedInvalidSType : ChainedStruct {
        DawnInjectedInvalidSType() {
            sType = wgpu::SType::DawnInjectedInvalidSType;
        }
        alignas(wgpu::DawnInjectedInvalidSType::kFirstMemberAlignment) wgpu::SType invalidSType = {};

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnInjectedInvalidSType& rhs) const;

    };

    struct DawnRenderPassSampleCount : ChainedStruct {
        DawnRenderPassSampleCount() {
            sType = wgpu::SType::DawnRenderPassSampleCount;
        }
        alignas(wgpu::DawnRenderPassSampleCount::kFirstMemberAlignment) uint32_t sampleCount = 1;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnRenderPassSampleCount& rhs) const;

    };

    struct DawnShaderModuleSPIRVOptionsDescriptor : ChainedStruct {
        DawnShaderModuleSPIRVOptionsDescriptor() {
            sType = wgpu::SType::DawnShaderModuleSPIRVOptionsDescriptor;
        }
        alignas(wgpu::DawnShaderModuleSPIRVOptionsDescriptor::kFirstMemberAlignment) wgpu::Bool allowNonUniformDerivatives = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnShaderModuleSPIRVOptionsDescriptor& rhs) const;

    };

    struct DawnTexelCopyBufferRowAlignmentLimits : ChainedStructOut {
        DawnTexelCopyBufferRowAlignmentLimits() {
            sType = wgpu::SType::DawnTexelCopyBufferRowAlignmentLimits;
        }
        alignas(wgpu::DawnTexelCopyBufferRowAlignmentLimits::kFirstMemberAlignment) uint32_t minTexelCopyBufferRowAlignment = wgpu::kLimitU32Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnTexelCopyBufferRowAlignmentLimits& rhs) const;

    };

    struct DawnTextureInternalUsageDescriptor : ChainedStruct {
        DawnTextureInternalUsageDescriptor() {
            sType = wgpu::SType::DawnTextureInternalUsageDescriptor;
        }
        alignas(wgpu::DawnTextureInternalUsageDescriptor::kFirstMemberAlignment) wgpu::TextureUsage internalUsage = wgpu::TextureUsage::None;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnTextureInternalUsageDescriptor& rhs) const;

    };

    struct DawnTogglesDescriptor : ChainedStruct {
        DawnTogglesDescriptor() {
            sType = wgpu::SType::DawnTogglesDescriptor;
        }
        alignas(wgpu::DawnTogglesDescriptor::kFirstMemberAlignment) size_t enabledToggleCount = 0;
        const char* const * enabledToggles = nullptr;
        size_t disabledToggleCount = 0;
        const char* const * disabledToggles = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnTogglesDescriptor& rhs) const;

    };

    struct DawnWGSLBlocklist : ChainedStruct {
        DawnWGSLBlocklist() {
            sType = wgpu::SType::DawnWGSLBlocklist;
        }
        alignas(wgpu::DawnWGSLBlocklist::kFirstMemberAlignment) size_t blocklistedFeatureCount = 0;
        const char* const * blocklistedFeatures = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnWGSLBlocklist& rhs) const;

    };

    struct DawnWireWGSLControl : ChainedStruct {
        DawnWireWGSLControl() {
            sType = wgpu::SType::DawnWireWGSLControl;
        }
        alignas(wgpu::DawnWireWGSLControl::kFirstMemberAlignment) wgpu::Bool enableExperimental = false;
        wgpu::Bool enableUnsafe = false;
        wgpu::Bool enableTesting = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnWireWGSLControl& rhs) const;

    };

    struct Extent2D {
        uint32_t width;
        uint32_t height;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Extent2D& rhs) const;

    };

    struct Extent3D {
        uint32_t width;
        uint32_t height = 1;
        uint32_t depthOrArrayLayers = 1;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Extent3D& rhs) const;

    };

    struct ExternalTextureBindingEntry : ChainedStruct {
        ExternalTextureBindingEntry() {
            sType = wgpu::SType::ExternalTextureBindingEntry;
        }
        alignas(wgpu::ExternalTextureBindingEntry::kFirstMemberAlignment) ExternalTextureBase* externalTexture;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ExternalTextureBindingEntry& rhs) const;

    };

    struct ExternalTextureBindingLayout : ChainedStruct {
        ExternalTextureBindingLayout() {
            sType = wgpu::SType::ExternalTextureBindingLayout;
        }

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ExternalTextureBindingLayout& rhs) const;

    };

    struct Future {
        uint64_t id;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Future& rhs) const;

    };

    struct InstanceLimits {
        ChainedStructOut * nextInChain = nullptr;
        size_t timedWaitAnyMaxCount = 0;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const InstanceLimits& rhs) const;

    };

    struct MemoryHeapInfo {
        wgpu::HeapProperty properties = wgpu::HeapProperty::None;
        uint64_t size;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const MemoryHeapInfo& rhs) const;

    };

    struct MultisampleState {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t count = 1;
        uint32_t mask = 0xFFFFFFFF;
        wgpu::Bool alphaToCoverageEnabled = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const MultisampleState& rhs) const;

    };

    struct Origin2D {
        uint32_t x = 0;
        uint32_t y = 0;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Origin2D& rhs) const;

    };

    struct Origin3D {
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t z = 0;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Origin3D& rhs) const;

    };

    struct PassTimestampWrites {
        ChainedStruct const * nextInChain = nullptr;
        QuerySetBase* querySet;
        uint32_t beginningOfPassWriteIndex = wgpu::kQuerySetIndexUndefined;
        uint32_t endOfPassWriteIndex = wgpu::kQuerySetIndexUndefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const PassTimestampWrites& rhs) const;

    };

    struct PipelineLayoutResourceTable : ChainedStruct {
        PipelineLayoutResourceTable() {
            sType = wgpu::SType::PipelineLayoutResourceTable;
        }
        alignas(wgpu::PipelineLayoutResourceTable::kFirstMemberAlignment) wgpu::Bool usesResourceTable = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const PipelineLayoutResourceTable& rhs) const;

    };

    struct PipelineLayoutStorageAttachment {
        ChainedStruct const * nextInChain = nullptr;
        uint64_t offset = 0;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const PipelineLayoutStorageAttachment& rhs) const;

    };

    struct PrimitiveState {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::PrimitiveTopology topology = wgpu::PrimitiveTopology::TriangleList;
        wgpu::IndexFormat stripIndexFormat = wgpu::IndexFormat::Undefined;
        wgpu::FrontFace frontFace = wgpu::FrontFace::CCW;
        wgpu::CullMode cullMode = wgpu::CullMode::None;
        wgpu::Bool unclippedDepth = false;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] PrimitiveState WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const PrimitiveState& rhs) const;

    };

    struct QuerySetDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        wgpu::QueryType type = {};
        uint32_t count;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const QuerySetDescriptor& rhs) const;

    };

    struct QueueDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const QueueDescriptor& rhs) const;

    };

    struct RenderBundleDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderBundleDescriptor& rhs) const;

    };

    struct RenderBundleEncoderDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        size_t colorFormatCount;
        wgpu::TextureFormat const * colorFormats = nullptr;
        wgpu::TextureFormat depthStencilFormat = wgpu::TextureFormat::Undefined;
        uint32_t sampleCount = 1;
        wgpu::Bool depthReadOnly = false;
        wgpu::Bool stencilReadOnly = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderBundleEncoderDescriptor& rhs) const;

    };

    struct RenderPassDepthStencilAttachment {
        ChainedStruct const * nextInChain = nullptr;
        TextureViewBase* view;
        wgpu::LoadOp depthLoadOp = wgpu::LoadOp::Undefined;
        wgpu::StoreOp depthStoreOp = wgpu::StoreOp::Undefined;
        float depthClearValue = wgpu::kDepthClearValueUndefined;
        wgpu::Bool depthReadOnly = false;
        wgpu::LoadOp stencilLoadOp = wgpu::LoadOp::Undefined;
        wgpu::StoreOp stencilStoreOp = wgpu::StoreOp::Undefined;
        uint32_t stencilClearValue = 0;
        wgpu::Bool stencilReadOnly = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassDepthStencilAttachment& rhs) const;

    };

    struct RenderPassDescriptorExpandResolveRect : ChainedStruct {
        RenderPassDescriptorExpandResolveRect() {
            sType = wgpu::SType::RenderPassDescriptorExpandResolveRect;
        }
        alignas(wgpu::RenderPassDescriptorExpandResolveRect::kFirstMemberAlignment) uint32_t x;
        uint32_t y;
        uint32_t width;
        uint32_t height;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassDescriptorExpandResolveRect& rhs) const;

    };

    struct RenderPassDescriptorResolveRect : ChainedStruct {
        RenderPassDescriptorResolveRect() {
            sType = wgpu::SType::RenderPassDescriptorResolveRect;
        }
        alignas(wgpu::RenderPassDescriptorResolveRect::kFirstMemberAlignment) uint32_t colorOffsetX;
        uint32_t colorOffsetY;
        uint32_t resolveOffsetX;
        uint32_t resolveOffsetY;
        uint32_t width;
        uint32_t height;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassDescriptorResolveRect& rhs) const;

    };

    struct RenderPassMaxDrawCount : ChainedStruct {
        RenderPassMaxDrawCount() {
            sType = wgpu::SType::RenderPassMaxDrawCount;
        }
        alignas(wgpu::RenderPassMaxDrawCount::kFirstMemberAlignment) uint64_t maxDrawCount = 50000000;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassMaxDrawCount& rhs) const;

    };

    struct RequestAdapterWebGPUBackendOptions : ChainedStruct {
        RequestAdapterWebGPUBackendOptions() {
            sType = wgpu::SType::RequestAdapterWebGPUBackendOptions;
        }

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RequestAdapterWebGPUBackendOptions& rhs) const;

    };

    struct RequestAdapterWebXROptions : ChainedStruct {
        RequestAdapterWebXROptions() {
            sType = wgpu::SType::RequestAdapterWebXROptions;
        }
        alignas(wgpu::RequestAdapterWebXROptions::kFirstMemberAlignment) wgpu::Bool xrCompatible;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RequestAdapterWebXROptions& rhs) const;

    };

    struct ResourceTableDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        uint32_t size;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ResourceTableDescriptor& rhs) const;

    };

    struct SamplerBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::SamplerBindingType type = wgpu::SamplerBindingType::Filtering;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] SamplerBindingLayout WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SamplerBindingLayout& rhs) const;

    };

    struct ShaderModuleCompilationOptions : ChainedStruct {
        ShaderModuleCompilationOptions() {
            sType = wgpu::SType::ShaderModuleCompilationOptions;
        }
        alignas(wgpu::ShaderModuleCompilationOptions::kFirstMemberAlignment) wgpu::Bool strictMath;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ShaderModuleCompilationOptions& rhs) const;

    };

    struct ShaderSourceSPIRV : ChainedStruct {
        ShaderSourceSPIRV() {
            sType = wgpu::SType::ShaderSourceSPIRV;
        }
        alignas(wgpu::ShaderSourceSPIRV::kFirstMemberAlignment) uint32_t codeSize;
        uint32_t const * code = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ShaderSourceSPIRV& rhs) const;

    };

    struct ShaderSourceWGSL : ChainedStruct {
        ShaderSourceWGSL() {
            sType = wgpu::SType::ShaderSourceWGSL;
        }
        alignas(wgpu::ShaderSourceWGSL::kFirstMemberAlignment) StringView code;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ShaderSourceWGSL& rhs) const;

    };

    struct SharedBufferMemoryBeginAccessDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::Bool initialized;
        size_t fenceCount = 0;
        SharedFenceBase* const * fences = nullptr;
        uint64_t const * signaledValues = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedBufferMemoryBeginAccessDescriptor& rhs) const;

    };

    struct SharedBufferMemoryDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedBufferMemoryDescriptor& rhs) const;

    };

    struct SharedBufferMemoryEndAccessState {
        SharedBufferMemoryEndAccessState() = default;
        ~SharedBufferMemoryEndAccessState();
        SharedBufferMemoryEndAccessState(const SharedBufferMemoryEndAccessState&) = delete;
        SharedBufferMemoryEndAccessState& operator=(const SharedBufferMemoryEndAccessState&) = delete;
        SharedBufferMemoryEndAccessState(SharedBufferMemoryEndAccessState&&);
        SharedBufferMemoryEndAccessState& operator=(SharedBufferMemoryEndAccessState&&);

        ChainedStructOut * nextInChain = nullptr;
        wgpu::Bool initialized;
        size_t fenceCount = 0;
        SharedFenceBase* const * fences = nullptr;
        uint64_t const * signaledValues = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedBufferMemoryEndAccessState& rhs) const;

      private:
        inline void FreeMembers();
    };

    struct SharedBufferMemoryProperties {
        ChainedStructOut * nextInChain = nullptr;
        wgpu::BufferUsage usage = wgpu::BufferUsage::None;
        uint64_t size;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedBufferMemoryProperties& rhs) const;

    };

    struct SharedFenceDXGISharedHandleDescriptor : ChainedStruct {
        SharedFenceDXGISharedHandleDescriptor() {
            sType = wgpu::SType::SharedFenceDXGISharedHandleDescriptor;
        }
        alignas(wgpu::SharedFenceDXGISharedHandleDescriptor::kFirstMemberAlignment) void * handle;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceDXGISharedHandleDescriptor& rhs) const;

    };

    struct SharedFenceDXGISharedHandleExportInfo : ChainedStructOut {
        SharedFenceDXGISharedHandleExportInfo() {
            sType = wgpu::SType::SharedFenceDXGISharedHandleExportInfo;
        }
        alignas(wgpu::SharedFenceDXGISharedHandleExportInfo::kFirstMemberAlignment) void * handle;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceDXGISharedHandleExportInfo& rhs) const;

    };

    struct SharedFenceEGLSyncDescriptor : ChainedStruct {
        SharedFenceEGLSyncDescriptor() {
            sType = wgpu::SType::SharedFenceEGLSyncDescriptor;
        }
        alignas(wgpu::SharedFenceEGLSyncDescriptor::kFirstMemberAlignment) void * sync;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceEGLSyncDescriptor& rhs) const;

    };

    struct SharedFenceEGLSyncExportInfo : ChainedStructOut {
        SharedFenceEGLSyncExportInfo() {
            sType = wgpu::SType::SharedFenceEGLSyncExportInfo;
        }
        alignas(wgpu::SharedFenceEGLSyncExportInfo::kFirstMemberAlignment) void * sync;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceEGLSyncExportInfo& rhs) const;

    };

    struct SharedFenceMTLSharedEventDescriptor : ChainedStruct {
        SharedFenceMTLSharedEventDescriptor() {
            sType = wgpu::SType::SharedFenceMTLSharedEventDescriptor;
        }
        alignas(wgpu::SharedFenceMTLSharedEventDescriptor::kFirstMemberAlignment) void * sharedEvent;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceMTLSharedEventDescriptor& rhs) const;

    };

    struct SharedFenceMTLSharedEventExportInfo : ChainedStructOut {
        SharedFenceMTLSharedEventExportInfo() {
            sType = wgpu::SType::SharedFenceMTLSharedEventExportInfo;
        }
        alignas(wgpu::SharedFenceMTLSharedEventExportInfo::kFirstMemberAlignment) void * sharedEvent;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceMTLSharedEventExportInfo& rhs) const;

    };

    struct SharedFenceSyncFDDescriptor : ChainedStruct {
        SharedFenceSyncFDDescriptor() {
            sType = wgpu::SType::SharedFenceSyncFDDescriptor;
        }
        alignas(wgpu::SharedFenceSyncFDDescriptor::kFirstMemberAlignment) int handle;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceSyncFDDescriptor& rhs) const;

    };

    struct SharedFenceSyncFDExportInfo : ChainedStructOut {
        SharedFenceSyncFDExportInfo() {
            sType = wgpu::SType::SharedFenceSyncFDExportInfo;
        }
        alignas(wgpu::SharedFenceSyncFDExportInfo::kFirstMemberAlignment) int handle;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceSyncFDExportInfo& rhs) const;

    };

    struct SharedFenceVkSemaphoreOpaqueFDDescriptor : ChainedStruct {
        SharedFenceVkSemaphoreOpaqueFDDescriptor() {
            sType = wgpu::SType::SharedFenceVkSemaphoreOpaqueFDDescriptor;
        }
        alignas(wgpu::SharedFenceVkSemaphoreOpaqueFDDescriptor::kFirstMemberAlignment) int handle;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceVkSemaphoreOpaqueFDDescriptor& rhs) const;

    };

    struct SharedFenceVkSemaphoreOpaqueFDExportInfo : ChainedStructOut {
        SharedFenceVkSemaphoreOpaqueFDExportInfo() {
            sType = wgpu::SType::SharedFenceVkSemaphoreOpaqueFDExportInfo;
        }
        alignas(wgpu::SharedFenceVkSemaphoreOpaqueFDExportInfo::kFirstMemberAlignment) int handle;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceVkSemaphoreOpaqueFDExportInfo& rhs) const;

    };

    struct SharedFenceVkSemaphoreZirconHandleDescriptor : ChainedStruct {
        SharedFenceVkSemaphoreZirconHandleDescriptor() {
            sType = wgpu::SType::SharedFenceVkSemaphoreZirconHandleDescriptor;
        }
        alignas(wgpu::SharedFenceVkSemaphoreZirconHandleDescriptor::kFirstMemberAlignment) uint32_t handle;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceVkSemaphoreZirconHandleDescriptor& rhs) const;

    };

    struct SharedFenceVkSemaphoreZirconHandleExportInfo : ChainedStructOut {
        SharedFenceVkSemaphoreZirconHandleExportInfo() {
            sType = wgpu::SType::SharedFenceVkSemaphoreZirconHandleExportInfo;
        }
        alignas(wgpu::SharedFenceVkSemaphoreZirconHandleExportInfo::kFirstMemberAlignment) uint32_t handle;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceVkSemaphoreZirconHandleExportInfo& rhs) const;

    };

    struct SharedTextureMemoryAHardwareBufferDescriptor : ChainedStruct {
        SharedTextureMemoryAHardwareBufferDescriptor() {
            sType = wgpu::SType::SharedTextureMemoryAHardwareBufferDescriptor;
        }
        alignas(wgpu::SharedTextureMemoryAHardwareBufferDescriptor::kFirstMemberAlignment) void * handle;
        wgpu::Bool useExternalFormat;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryAHardwareBufferDescriptor& rhs) const;

    };

    struct SharedTextureMemoryD3D11BeginState : ChainedStruct {
        SharedTextureMemoryD3D11BeginState() {
            sType = wgpu::SType::SharedTextureMemoryD3D11BeginState;
        }
        alignas(wgpu::SharedTextureMemoryD3D11BeginState::kFirstMemberAlignment) wgpu::Bool requiresEndAccessFence = true;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryD3D11BeginState& rhs) const;

    };

    struct SharedTextureMemoryD3DSwapchainBeginState : ChainedStruct {
        SharedTextureMemoryD3DSwapchainBeginState() {
            sType = wgpu::SType::SharedTextureMemoryD3DSwapchainBeginState;
        }
        alignas(wgpu::SharedTextureMemoryD3DSwapchainBeginState::kFirstMemberAlignment) wgpu::Bool isSwapchain = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryD3DSwapchainBeginState& rhs) const;

    };

    struct SharedTextureMemoryDmaBufPlane {
        int fd;
        uint64_t offset;
        uint32_t stride;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryDmaBufPlane& rhs) const;

    };

    struct SharedTextureMemoryDXGISharedHandleDescriptor : ChainedStruct {
        SharedTextureMemoryDXGISharedHandleDescriptor() {
            sType = wgpu::SType::SharedTextureMemoryDXGISharedHandleDescriptor;
        }
        alignas(wgpu::SharedTextureMemoryDXGISharedHandleDescriptor::kFirstMemberAlignment) void * handle;
        wgpu::Bool useKeyedMutex;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryDXGISharedHandleDescriptor& rhs) const;

    };

    struct SharedTextureMemoryEGLImageDescriptor : ChainedStruct {
        SharedTextureMemoryEGLImageDescriptor() {
            sType = wgpu::SType::SharedTextureMemoryEGLImageDescriptor;
        }
        alignas(wgpu::SharedTextureMemoryEGLImageDescriptor::kFirstMemberAlignment) void * image;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryEGLImageDescriptor& rhs) const;

    };

    struct SharedTextureMemoryIOSurfaceDescriptor : ChainedStruct {
        SharedTextureMemoryIOSurfaceDescriptor() {
            sType = wgpu::SType::SharedTextureMemoryIOSurfaceDescriptor;
        }
        alignas(wgpu::SharedTextureMemoryIOSurfaceDescriptor::kFirstMemberAlignment) void * ioSurface;
        wgpu::Bool allowStorageBinding = true;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryIOSurfaceDescriptor& rhs) const;

    };

    struct SharedTextureMemoryOpaqueFDDescriptor : ChainedStruct {
        SharedTextureMemoryOpaqueFDDescriptor() {
            sType = wgpu::SType::SharedTextureMemoryOpaqueFDDescriptor;
        }
        alignas(wgpu::SharedTextureMemoryOpaqueFDDescriptor::kFirstMemberAlignment) void const * vkImageCreateInfo;
        int memoryFD;
        uint32_t memoryTypeIndex;
        uint64_t allocationSize;
        wgpu::Bool dedicatedAllocation;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryOpaqueFDDescriptor& rhs) const;

    };

    struct SharedTextureMemoryVkDedicatedAllocationDescriptor : ChainedStruct {
        SharedTextureMemoryVkDedicatedAllocationDescriptor() {
            sType = wgpu::SType::SharedTextureMemoryVkDedicatedAllocationDescriptor;
        }
        alignas(wgpu::SharedTextureMemoryVkDedicatedAllocationDescriptor::kFirstMemberAlignment) wgpu::Bool dedicatedAllocation;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryVkDedicatedAllocationDescriptor& rhs) const;

    };

    struct SharedTextureMemoryVkImageLayoutBeginState : ChainedStruct {
        SharedTextureMemoryVkImageLayoutBeginState() {
            sType = wgpu::SType::SharedTextureMemoryVkImageLayoutBeginState;
        }
        alignas(wgpu::SharedTextureMemoryVkImageLayoutBeginState::kFirstMemberAlignment) int32_t oldLayout;
        int32_t newLayout;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryVkImageLayoutBeginState& rhs) const;

    };

    struct SharedTextureMemoryVkImageLayoutEndState : ChainedStructOut {
        SharedTextureMemoryVkImageLayoutEndState() {
            sType = wgpu::SType::SharedTextureMemoryVkImageLayoutEndState;
        }
        alignas(wgpu::SharedTextureMemoryVkImageLayoutEndState::kFirstMemberAlignment) int32_t oldLayout;
        int32_t newLayout;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryVkImageLayoutEndState& rhs) const;

    };

    struct SharedTextureMemoryZirconHandleDescriptor : ChainedStruct {
        SharedTextureMemoryZirconHandleDescriptor() {
            sType = wgpu::SType::SharedTextureMemoryZirconHandleDescriptor;
        }
        alignas(wgpu::SharedTextureMemoryZirconHandleDescriptor::kFirstMemberAlignment) uint32_t memoryFD;
        uint64_t allocationSize;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryZirconHandleDescriptor& rhs) const;

    };

    struct StaticSamplerBindingLayout : ChainedStruct {
        StaticSamplerBindingLayout() {
            sType = wgpu::SType::StaticSamplerBindingLayout;
        }
        alignas(wgpu::StaticSamplerBindingLayout::kFirstMemberAlignment) SamplerBase* sampler;
        uint32_t sampledTextureBinding = wgpu::kLimitU32Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const StaticSamplerBindingLayout& rhs) const;

    };

    struct StencilFaceState {
        wgpu::CompareFunction compare = wgpu::CompareFunction::Always;
        wgpu::StencilOperation failOp = wgpu::StencilOperation::Keep;
        wgpu::StencilOperation depthFailOp = wgpu::StencilOperation::Keep;
        wgpu::StencilOperation passOp = wgpu::StencilOperation::Keep;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] StencilFaceState WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const StencilFaceState& rhs) const;

    };

    struct StorageTextureBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::StorageTextureAccess access = wgpu::StorageTextureAccess::WriteOnly;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
        wgpu::TextureViewDimension viewDimension = wgpu::TextureViewDimension::e2D;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] StorageTextureBindingLayout WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const StorageTextureBindingLayout& rhs) const;

    };

    struct SubgroupMatrixConfig {
        wgpu::SubgroupMatrixComponentType componentType = {};
        wgpu::SubgroupMatrixComponentType resultComponentType = {};
        uint32_t M;
        uint32_t N;
        uint32_t K;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SubgroupMatrixConfig& rhs) const;

    };

    struct SupportedFeatures {
        SupportedFeatures() = default;
        ~SupportedFeatures();
        SupportedFeatures(const SupportedFeatures&) = delete;
        SupportedFeatures& operator=(const SupportedFeatures&) = delete;
        SupportedFeatures(SupportedFeatures&&);
        SupportedFeatures& operator=(SupportedFeatures&&);

        size_t featureCount;
        wgpu::FeatureName const * features = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SupportedFeatures& rhs) const;

      private:
        inline void FreeMembers();
    };

    struct SupportedInstanceFeatures {
        SupportedInstanceFeatures() = default;
        ~SupportedInstanceFeatures();
        SupportedInstanceFeatures(const SupportedInstanceFeatures&) = delete;
        SupportedInstanceFeatures& operator=(const SupportedInstanceFeatures&) = delete;
        SupportedInstanceFeatures(SupportedInstanceFeatures&&);
        SupportedInstanceFeatures& operator=(SupportedInstanceFeatures&&);

        size_t featureCount;
        wgpu::InstanceFeatureName const * features = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SupportedInstanceFeatures& rhs) const;

      private:
        inline void FreeMembers();
    };

    struct SupportedWGSLLanguageFeatures {
        SupportedWGSLLanguageFeatures() = default;
        ~SupportedWGSLLanguageFeatures();
        SupportedWGSLLanguageFeatures(const SupportedWGSLLanguageFeatures&) = delete;
        SupportedWGSLLanguageFeatures& operator=(const SupportedWGSLLanguageFeatures&) = delete;
        SupportedWGSLLanguageFeatures(SupportedWGSLLanguageFeatures&&);
        SupportedWGSLLanguageFeatures& operator=(SupportedWGSLLanguageFeatures&&);

        size_t featureCount;
        wgpu::WGSLLanguageFeatureName const * features = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SupportedWGSLLanguageFeatures& rhs) const;

      private:
        inline void FreeMembers();
    };

    struct SurfaceCapabilities {
        SurfaceCapabilities() = default;
        ~SurfaceCapabilities();
        SurfaceCapabilities(const SurfaceCapabilities&) = delete;
        SurfaceCapabilities& operator=(const SurfaceCapabilities&) = delete;
        SurfaceCapabilities(SurfaceCapabilities&&);
        SurfaceCapabilities& operator=(SurfaceCapabilities&&);

        ChainedStructOut * nextInChain = nullptr;
        wgpu::TextureUsage usages = wgpu::TextureUsage::None;
        size_t formatCount;
        wgpu::TextureFormat const * formats = nullptr;
        size_t presentModeCount;
        wgpu::PresentMode const * presentModes = nullptr;
        size_t alphaModeCount;
        wgpu::CompositeAlphaMode const * alphaModes = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceCapabilities& rhs) const;

      private:
        inline void FreeMembers();
    };

    struct SurfaceColorManagement : ChainedStruct {
        SurfaceColorManagement() {
            sType = wgpu::SType::SurfaceColorManagement;
        }
        alignas(wgpu::SurfaceColorManagement::kFirstMemberAlignment) wgpu::PredefinedColorSpace colorSpace = {};
        wgpu::ToneMappingMode toneMappingMode = {};

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceColorManagement& rhs) const;

    };

    struct SurfaceConfiguration {
        ChainedStruct const * nextInChain = nullptr;
        DeviceBase* device;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
        wgpu::TextureUsage usage = wgpu::TextureUsage::RenderAttachment;
        uint32_t width;
        uint32_t height;
        size_t viewFormatCount = 0;
        wgpu::TextureFormat const * viewFormats = nullptr;
        wgpu::CompositeAlphaMode alphaMode = wgpu::CompositeAlphaMode::Auto;
        wgpu::PresentMode presentMode = wgpu::PresentMode::Fifo;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] SurfaceConfiguration WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceConfiguration& rhs) const;

    };

    struct SurfaceDescriptorFromWindowsCoreWindow : ChainedStruct {
        SurfaceDescriptorFromWindowsCoreWindow() {
            sType = wgpu::SType::SurfaceDescriptorFromWindowsCoreWindow;
        }
        alignas(wgpu::SurfaceDescriptorFromWindowsCoreWindow::kFirstMemberAlignment) void * coreWindow = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromWindowsCoreWindow& rhs) const;

    };

    struct SurfaceDescriptorFromWindowsUWPSwapChainPanel : ChainedStruct {
        SurfaceDescriptorFromWindowsUWPSwapChainPanel() {
            sType = wgpu::SType::SurfaceDescriptorFromWindowsUWPSwapChainPanel;
        }
        alignas(wgpu::SurfaceDescriptorFromWindowsUWPSwapChainPanel::kFirstMemberAlignment) void * swapChainPanel = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromWindowsUWPSwapChainPanel& rhs) const;

    };

    struct SurfaceDescriptorFromWindowsWinUISwapChainPanel : ChainedStruct {
        SurfaceDescriptorFromWindowsWinUISwapChainPanel() {
            sType = wgpu::SType::SurfaceDescriptorFromWindowsWinUISwapChainPanel;
        }
        alignas(wgpu::SurfaceDescriptorFromWindowsWinUISwapChainPanel::kFirstMemberAlignment) void * swapChainPanel = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptorFromWindowsWinUISwapChainPanel& rhs) const;

    };

    struct SurfaceSourceAndroidNativeWindow : ChainedStruct {
        SurfaceSourceAndroidNativeWindow() {
            sType = wgpu::SType::SurfaceSourceAndroidNativeWindow;
        }
        alignas(wgpu::SurfaceSourceAndroidNativeWindow::kFirstMemberAlignment) void * window;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceSourceAndroidNativeWindow& rhs) const;

    };

    struct SurfaceSourceMetalLayer : ChainedStruct {
        SurfaceSourceMetalLayer() {
            sType = wgpu::SType::SurfaceSourceMetalLayer;
        }
        alignas(wgpu::SurfaceSourceMetalLayer::kFirstMemberAlignment) void * layer = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceSourceMetalLayer& rhs) const;

    };

    struct SurfaceSourceWaylandSurface : ChainedStruct {
        SurfaceSourceWaylandSurface() {
            sType = wgpu::SType::SurfaceSourceWaylandSurface;
        }
        alignas(wgpu::SurfaceSourceWaylandSurface::kFirstMemberAlignment) void * display = nullptr;
        void * surface = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceSourceWaylandSurface& rhs) const;

    };

    struct SurfaceSourceWindowsHWND : ChainedStruct {
        SurfaceSourceWindowsHWND() {
            sType = wgpu::SType::SurfaceSourceWindowsHWND;
        }
        alignas(wgpu::SurfaceSourceWindowsHWND::kFirstMemberAlignment) void * hinstance = nullptr;
        void * hwnd = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceSourceWindowsHWND& rhs) const;

    };

    struct SurfaceSourceXCBWindow : ChainedStruct {
        SurfaceSourceXCBWindow() {
            sType = wgpu::SType::SurfaceSourceXCBWindow;
        }
        alignas(wgpu::SurfaceSourceXCBWindow::kFirstMemberAlignment) void * connection = nullptr;
        uint32_t window;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceSourceXCBWindow& rhs) const;

    };

    struct SurfaceSourceXlibWindow : ChainedStruct {
        SurfaceSourceXlibWindow() {
            sType = wgpu::SType::SurfaceSourceXlibWindow;
        }
        alignas(wgpu::SurfaceSourceXlibWindow::kFirstMemberAlignment) void * display = nullptr;
        uint64_t window;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceSourceXlibWindow& rhs) const;

    };

    struct SurfaceTexture {
        ChainedStructOut * nextInChain = nullptr;
        TextureBase* texture;
        wgpu::SurfaceGetCurrentTextureStatus status = {};

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceTexture& rhs) const;

    };

    struct TexelBufferBindingEntry : ChainedStruct {
        TexelBufferBindingEntry() {
            sType = wgpu::SType::TexelBufferBindingEntry;
        }
        alignas(wgpu::TexelBufferBindingEntry::kFirstMemberAlignment) TexelBufferViewBase* texelBufferView;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TexelBufferBindingEntry& rhs) const;

    };

    struct TexelBufferBindingLayout : ChainedStruct {
        TexelBufferBindingLayout() {
            sType = wgpu::SType::TexelBufferBindingLayout;
        }
        alignas(wgpu::TexelBufferBindingLayout::kFirstMemberAlignment) wgpu::TexelBufferAccess access = wgpu::TexelBufferAccess::ReadWrite;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] TexelBufferBindingLayout WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TexelBufferBindingLayout& rhs) const;

    };

    struct TexelBufferViewDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
        uint64_t offset = 0;
        uint64_t size = wgpu::kWholeSize;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TexelBufferViewDescriptor& rhs) const;

    };

    struct TexelCopyBufferLayout {
        uint64_t offset = 0;
        uint32_t bytesPerRow = wgpu::kCopyStrideUndefined;
        uint32_t rowsPerImage = wgpu::kCopyStrideUndefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TexelCopyBufferLayout& rhs) const;

    };

    struct TextureBindingLayout {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::TextureSampleType sampleType = wgpu::TextureSampleType::Float;
        wgpu::TextureViewDimension viewDimension = wgpu::TextureViewDimension::e2D;
        wgpu::Bool multisampled = false;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] TextureBindingLayout WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TextureBindingLayout& rhs) const;

    };

    struct TextureBindingViewDimensionDescriptor : ChainedStruct {
        TextureBindingViewDimensionDescriptor() {
            sType = wgpu::SType::TextureBindingViewDimensionDescriptor;
        }
        alignas(wgpu::TextureBindingViewDimensionDescriptor::kFirstMemberAlignment) wgpu::TextureViewDimension textureBindingViewDimension = wgpu::TextureViewDimension::Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TextureBindingViewDimensionDescriptor& rhs) const;

    };

    struct TextureComponentSwizzle {
        wgpu::ComponentSwizzle r = wgpu::ComponentSwizzle::R;
        wgpu::ComponentSwizzle g = wgpu::ComponentSwizzle::G;
        wgpu::ComponentSwizzle b = wgpu::ComponentSwizzle::B;
        wgpu::ComponentSwizzle a = wgpu::ComponentSwizzle::A;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] TextureComponentSwizzle WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TextureComponentSwizzle& rhs) const;

    };

    struct VertexAttribute {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::VertexFormat format = {};
        uint64_t offset;
        uint32_t shaderLocation;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const VertexAttribute& rhs) const;

    };

    struct YCbCrVkDescriptor : ChainedStruct {
        YCbCrVkDescriptor() {
            sType = wgpu::SType::YCbCrVkDescriptor;
        }
        alignas(wgpu::YCbCrVkDescriptor::kFirstMemberAlignment) uint32_t vkFormat = 0;
        uint32_t vkYCbCrModel = 0;
        uint32_t vkYCbCrRange = 0;
        uint32_t vkComponentSwizzleRed = 0;
        uint32_t vkComponentSwizzleGreen = 0;
        uint32_t vkComponentSwizzleBlue = 0;
        uint32_t vkComponentSwizzleAlpha = 0;
        uint32_t vkXChromaOffset = 0;
        uint32_t vkYChromaOffset = 0;
        wgpu::FilterMode vkChromaFilter = wgpu::FilterMode::Nearest;
        wgpu::Bool forceExplicitReconstruction = false;
        uint64_t externalFormat = 0;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] YCbCrVkDescriptor WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const YCbCrVkDescriptor& rhs) const;

    };

    struct AdapterPropertiesMemoryHeaps : ChainedStructOut {
        AdapterPropertiesMemoryHeaps() {
            sType = wgpu::SType::AdapterPropertiesMemoryHeaps;
        }
        ~AdapterPropertiesMemoryHeaps();
        AdapterPropertiesMemoryHeaps(const AdapterPropertiesMemoryHeaps&) = delete;
        AdapterPropertiesMemoryHeaps& operator=(const AdapterPropertiesMemoryHeaps&) = delete;
        AdapterPropertiesMemoryHeaps(AdapterPropertiesMemoryHeaps&&);
        AdapterPropertiesMemoryHeaps& operator=(AdapterPropertiesMemoryHeaps&&);

        alignas(wgpu::AdapterPropertiesMemoryHeaps::kFirstMemberAlignment) size_t heapCount;
        MemoryHeapInfo const * heapInfo = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const AdapterPropertiesMemoryHeaps& rhs) const;

      private:
        inline void FreeMembers();
    };

    struct AdapterPropertiesSubgroupMatrixConfigs : ChainedStructOut {
        AdapterPropertiesSubgroupMatrixConfigs() {
            sType = wgpu::SType::AdapterPropertiesSubgroupMatrixConfigs;
        }
        ~AdapterPropertiesSubgroupMatrixConfigs();
        AdapterPropertiesSubgroupMatrixConfigs(const AdapterPropertiesSubgroupMatrixConfigs&) = delete;
        AdapterPropertiesSubgroupMatrixConfigs& operator=(const AdapterPropertiesSubgroupMatrixConfigs&) = delete;
        AdapterPropertiesSubgroupMatrixConfigs(AdapterPropertiesSubgroupMatrixConfigs&&);
        AdapterPropertiesSubgroupMatrixConfigs& operator=(AdapterPropertiesSubgroupMatrixConfigs&&);

        alignas(wgpu::AdapterPropertiesSubgroupMatrixConfigs::kFirstMemberAlignment) size_t configCount;
        SubgroupMatrixConfig const * configs = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const AdapterPropertiesSubgroupMatrixConfigs& rhs) const;

      private:
        inline void FreeMembers();
    };

    struct AHardwareBufferProperties {
        YCbCrVkDescriptor yCbCrInfo;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] AHardwareBufferProperties WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const AHardwareBufferProperties& rhs) const;

    };

    struct BindGroupEntry {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t binding;
        BufferBase* buffer = nullptr;
        uint64_t offset = 0;
        uint64_t size = wgpu::kWholeSize;
        SamplerBase* sampler = nullptr;
        TextureViewBase* textureView = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BindGroupEntry& rhs) const;

    };

    struct BindGroupLayoutEntry {
        ChainedStruct const * nextInChain = nullptr;
        uint32_t binding;
        wgpu::ShaderStage visibility = wgpu::ShaderStage::None;
        uint32_t bindingArraySize = 0;
        BufferBindingLayout buffer = { nullptr, wgpu::BufferBindingType::BindingNotUsed, false, 0 };
        SamplerBindingLayout sampler = { nullptr, wgpu::SamplerBindingType::BindingNotUsed };
        TextureBindingLayout texture = { nullptr, wgpu::TextureSampleType::BindingNotUsed, wgpu::TextureViewDimension::e2D, false };
        StorageTextureBindingLayout storageTexture = { nullptr, wgpu::StorageTextureAccess::BindingNotUsed, wgpu::TextureFormat::Undefined, wgpu::TextureViewDimension::e2D };

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] BindGroupLayoutEntry WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BindGroupLayoutEntry& rhs) const;

    };

    struct BlendState {
        BlendComponent color;
        BlendComponent alpha;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] BlendState WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BlendState& rhs) const;

    };

    struct BufferDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        wgpu::BufferUsage usage = wgpu::BufferUsage::None;
        uint64_t size;
        wgpu::Bool mappedAtCreation = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BufferDescriptor& rhs) const;

    };

    struct CommandEncoderDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CommandEncoderDescriptor& rhs) const;

    };

    struct CompilationMessage {
        ChainedStruct const * nextInChain = nullptr;
        StringView message;
        wgpu::CompilationMessageType type = {};
        uint64_t lineNum;
        uint64_t linePos;
        uint64_t offset;
        uint64_t length;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CompilationMessage& rhs) const;

    };

    struct ComputePassDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        PassTimestampWrites const * timestampWrites = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ComputePassDescriptor& rhs) const;

    };

    struct ComputeState {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModuleBase* module;
        StringView entryPoint;
        size_t constantCount = 0;
        ConstantEntry const * constants = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ComputeState& rhs) const;

    };

    struct DawnDrmFormatCapabilities : ChainedStructOut {
        DawnDrmFormatCapabilities() {
            sType = wgpu::SType::DawnDrmFormatCapabilities;
        }
        ~DawnDrmFormatCapabilities();
        DawnDrmFormatCapabilities(const DawnDrmFormatCapabilities&) = delete;
        DawnDrmFormatCapabilities& operator=(const DawnDrmFormatCapabilities&) = delete;
        DawnDrmFormatCapabilities(DawnDrmFormatCapabilities&&);
        DawnDrmFormatCapabilities& operator=(DawnDrmFormatCapabilities&&);

        alignas(wgpu::DawnDrmFormatCapabilities::kFirstMemberAlignment) size_t propertiesCount;
        DawnDrmFormatProperties const * properties = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnDrmFormatCapabilities& rhs) const;

      private:
        inline void FreeMembers();
    };

    struct DepthStencilState {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
        wgpu::OptionalBool depthWriteEnabled = wgpu::OptionalBool::Undefined;
        wgpu::CompareFunction depthCompare = wgpu::CompareFunction::Undefined;
        StencilFaceState stencilFront;
        StencilFaceState stencilBack;
        uint32_t stencilReadMask = 0xFFFFFFFF;
        uint32_t stencilWriteMask = 0xFFFFFFFF;
        int32_t depthBias = 0;
        float depthBiasSlopeScale = 0.f;
        float depthBiasClamp = 0.f;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] DepthStencilState WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DepthStencilState& rhs) const;

    };

    struct ExternalTextureDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        TextureViewBase* plane0;
        TextureViewBase* plane1 = nullptr;
        Origin2D cropOrigin;
        Extent2D cropSize;
        Extent2D apparentSize;
        wgpu::Bool doYuvToRgbConversionOnly = false;
        float const * yuvToRgbConversionMatrix = nullptr;
        float const * srcTransferFunctionParameters = nullptr;
        float const * dstTransferFunctionParameters = nullptr;
        float const * gamutConversionMatrix = nullptr;
        wgpu::Bool mirrored = false;
        wgpu::ExternalTextureRotation rotation = wgpu::ExternalTextureRotation::Rotate0Degrees;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ExternalTextureDescriptor& rhs) const;

    };

    struct FutureWaitInfo {
        Future future;
        wgpu::Bool completed = false;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const FutureWaitInfo& rhs) const;

    };

    struct ImageCopyExternalTexture {
        ChainedStruct const * nextInChain = nullptr;
        ExternalTextureBase* externalTexture;
        Origin3D origin;
        Extent2D naturalSize;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ImageCopyExternalTexture& rhs) const;

    };

    struct InstanceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        size_t requiredFeatureCount = 0;
        wgpu::InstanceFeatureName const * requiredFeatures = nullptr;
        InstanceLimits const * requiredLimits = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const InstanceDescriptor& rhs) const;

    };

    struct Limits {
        ChainedStructOut * nextInChain = nullptr;
        uint32_t maxTextureDimension1D = wgpu::kLimitU32Undefined;
        uint32_t maxTextureDimension2D = wgpu::kLimitU32Undefined;
        uint32_t maxTextureDimension3D = wgpu::kLimitU32Undefined;
        uint32_t maxTextureArrayLayers = wgpu::kLimitU32Undefined;
        uint32_t maxBindGroups = wgpu::kLimitU32Undefined;
        uint32_t maxBindGroupsPlusVertexBuffers = wgpu::kLimitU32Undefined;
        uint32_t maxBindingsPerBindGroup = wgpu::kLimitU32Undefined;
        uint32_t maxDynamicUniformBuffersPerPipelineLayout = wgpu::kLimitU32Undefined;
        uint32_t maxDynamicStorageBuffersPerPipelineLayout = wgpu::kLimitU32Undefined;
        uint32_t maxSampledTexturesPerShaderStage = wgpu::kLimitU32Undefined;
        uint32_t maxSamplersPerShaderStage = wgpu::kLimitU32Undefined;
        uint32_t maxStorageBuffersPerShaderStage = wgpu::kLimitU32Undefined;
        uint32_t maxStorageTexturesPerShaderStage = wgpu::kLimitU32Undefined;
        uint32_t maxUniformBuffersPerShaderStage = wgpu::kLimitU32Undefined;
        uint64_t maxUniformBufferBindingSize = wgpu::kLimitU64Undefined;
        uint64_t maxStorageBufferBindingSize = wgpu::kLimitU64Undefined;
        uint32_t minUniformBufferOffsetAlignment = wgpu::kLimitU32Undefined;
        uint32_t minStorageBufferOffsetAlignment = wgpu::kLimitU32Undefined;
        uint32_t maxVertexBuffers = wgpu::kLimitU32Undefined;
        uint64_t maxBufferSize = wgpu::kLimitU64Undefined;
        uint32_t maxVertexAttributes = wgpu::kLimitU32Undefined;
        uint32_t maxVertexBufferArrayStride = wgpu::kLimitU32Undefined;
        uint32_t maxInterStageShaderVariables = wgpu::kLimitU32Undefined;
        uint32_t maxColorAttachments = wgpu::kLimitU32Undefined;
        uint32_t maxColorAttachmentBytesPerSample = wgpu::kLimitU32Undefined;
        uint32_t maxComputeWorkgroupStorageSize = wgpu::kLimitU32Undefined;
        uint32_t maxComputeInvocationsPerWorkgroup = wgpu::kLimitU32Undefined;
        uint32_t maxComputeWorkgroupSizeX = wgpu::kLimitU32Undefined;
        uint32_t maxComputeWorkgroupSizeY = wgpu::kLimitU32Undefined;
        uint32_t maxComputeWorkgroupSizeZ = wgpu::kLimitU32Undefined;
        uint32_t maxComputeWorkgroupsPerDimension = wgpu::kLimitU32Undefined;
        uint32_t maxImmediateSize = wgpu::kLimitU32Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const Limits& rhs) const;

    };

    struct PipelineLayoutPixelLocalStorage : ChainedStruct {
        PipelineLayoutPixelLocalStorage() {
            sType = wgpu::SType::PipelineLayoutPixelLocalStorage;
        }
        alignas(wgpu::PipelineLayoutPixelLocalStorage::kFirstMemberAlignment) uint64_t totalPixelLocalStorageSize;
        size_t storageAttachmentCount = 0;
        PipelineLayoutStorageAttachment const * storageAttachments = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const PipelineLayoutPixelLocalStorage& rhs) const;

    };

    struct RenderPassColorAttachment {
        ChainedStruct const * nextInChain = nullptr;
        TextureViewBase* view = nullptr;
        uint32_t depthSlice = wgpu::kDepthSliceUndefined;
        TextureViewBase* resolveTarget = nullptr;
        wgpu::LoadOp loadOp = wgpu::LoadOp::Undefined;
        wgpu::StoreOp storeOp = wgpu::StoreOp::Undefined;
        Color clearValue;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassColorAttachment& rhs) const;

    };

    struct RenderPassStorageAttachment {
        ChainedStruct const * nextInChain = nullptr;
        uint64_t offset = 0;
        TextureViewBase* storage;
        wgpu::LoadOp loadOp = wgpu::LoadOp::Undefined;
        wgpu::StoreOp storeOp = wgpu::StoreOp::Undefined;
        Color clearValue;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassStorageAttachment& rhs) const;

    };

    struct RequestAdapterOptions {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::FeatureLevel featureLevel = wgpu::FeatureLevel::Core;
        wgpu::PowerPreference powerPreference = wgpu::PowerPreference::Undefined;
        wgpu::Bool forceFallbackAdapter = false;
        wgpu::BackendType backendType = wgpu::BackendType::Undefined;
        SurfaceBase* compatibleSurface = nullptr;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] RequestAdapterOptions WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RequestAdapterOptions& rhs) const;

    };

    struct SamplerDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        wgpu::AddressMode addressModeU = wgpu::AddressMode::ClampToEdge;
        wgpu::AddressMode addressModeV = wgpu::AddressMode::ClampToEdge;
        wgpu::AddressMode addressModeW = wgpu::AddressMode::ClampToEdge;
        wgpu::FilterMode magFilter = wgpu::FilterMode::Nearest;
        wgpu::FilterMode minFilter = wgpu::FilterMode::Nearest;
        wgpu::MipmapFilterMode mipmapFilter = wgpu::MipmapFilterMode::Nearest;
        float lodMinClamp = 0.f;
        float lodMaxClamp = 32.f;
        wgpu::CompareFunction compare = wgpu::CompareFunction::Undefined;
        uint16_t maxAnisotropy = 1;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] SamplerDescriptor WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SamplerDescriptor& rhs) const;

    };

    struct ShaderModuleDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ShaderModuleDescriptor& rhs) const;

    };

    struct SharedFenceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceDescriptor& rhs) const;

    };

    struct SharedFenceExportInfo {
        ChainedStructOut * nextInChain = nullptr;
        wgpu::SharedFenceType type = {};

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedFenceExportInfo& rhs) const;

    };

    struct SharedTextureMemoryAHardwareBufferProperties : ChainedStructOut {
        SharedTextureMemoryAHardwareBufferProperties() {
            sType = wgpu::SType::SharedTextureMemoryAHardwareBufferProperties;
        }
        alignas(wgpu::SharedTextureMemoryAHardwareBufferProperties::kFirstMemberAlignment) YCbCrVkDescriptor yCbCrInfo;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] SharedTextureMemoryAHardwareBufferProperties WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryAHardwareBufferProperties& rhs) const;

    };

    struct SharedTextureMemoryBeginAccessDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::Bool concurrentRead;
        wgpu::Bool initialized;
        size_t fenceCount;
        SharedFenceBase* const * fences = nullptr;
        uint64_t const * signaledValues = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryBeginAccessDescriptor& rhs) const;

    };

    struct SharedTextureMemoryDmaBufDescriptor : ChainedStruct {
        SharedTextureMemoryDmaBufDescriptor() {
            sType = wgpu::SType::SharedTextureMemoryDmaBufDescriptor;
        }
        alignas(wgpu::SharedTextureMemoryDmaBufDescriptor::kFirstMemberAlignment) Extent3D size;
        uint32_t drmFormat;
        uint64_t drmModifier;
        size_t planeCount;
        SharedTextureMemoryDmaBufPlane const * planes = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryDmaBufDescriptor& rhs) const;

    };

    struct SharedTextureMemoryMetalEndAccessState : ChainedStructOut {
        SharedTextureMemoryMetalEndAccessState() {
            sType = wgpu::SType::SharedTextureMemoryMetalEndAccessState;
        }
        alignas(wgpu::SharedTextureMemoryMetalEndAccessState::kFirstMemberAlignment) Future commandsScheduledFuture;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryMetalEndAccessState& rhs) const;

    };

    struct SurfaceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SurfaceDescriptor& rhs) const;

    };

    struct TexelCopyBufferInfo {
        TexelCopyBufferLayout layout;
        BufferBase* buffer;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TexelCopyBufferInfo& rhs) const;

    };

    struct TexelCopyTextureInfo {
        TextureBase* texture;
        uint32_t mipLevel = 0;
        Origin3D origin;
        wgpu::TextureAspect aspect = wgpu::TextureAspect::All;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] TexelCopyTextureInfo WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TexelCopyTextureInfo& rhs) const;

    };

    struct TextureComponentSwizzleDescriptor : ChainedStruct {
        TextureComponentSwizzleDescriptor() {
            sType = wgpu::SType::TextureComponentSwizzleDescriptor;
        }
        alignas(wgpu::TextureComponentSwizzleDescriptor::kFirstMemberAlignment) TextureComponentSwizzle swizzle;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] TextureComponentSwizzleDescriptor WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TextureComponentSwizzleDescriptor& rhs) const;

    };

    struct TextureDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        wgpu::TextureUsage usage = wgpu::TextureUsage::None;
        wgpu::TextureDimension dimension = wgpu::TextureDimension::e2D;
        Extent3D size;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
        uint32_t mipLevelCount = 1;
        uint32_t sampleCount = 1;
        size_t viewFormatCount = 0;
        wgpu::TextureFormat const * viewFormats = nullptr;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] TextureDescriptor WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TextureDescriptor& rhs) const;

    };

    struct VertexBufferLayout {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::VertexStepMode stepMode = wgpu::VertexStepMode::Undefined;
        uint64_t arrayStride;
        size_t attributeCount;
        VertexAttribute const * attributes = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const VertexBufferLayout& rhs) const;

    };

    struct AdapterInfo {
        AdapterInfo() = default;
        ~AdapterInfo();
        AdapterInfo(const AdapterInfo&) = delete;
        AdapterInfo& operator=(const AdapterInfo&) = delete;
        AdapterInfo(AdapterInfo&&);
        AdapterInfo& operator=(AdapterInfo&&);

        ChainedStructOut * nextInChain = nullptr;
        StringView vendor;
        StringView architecture;
        StringView device;
        StringView description;
        wgpu::BackendType backendType = wgpu::BackendType::Undefined;
        wgpu::AdapterType adapterType = {};
        uint32_t vendorID;
        uint32_t deviceID;
        uint32_t subgroupMinSize;
        uint32_t subgroupMaxSize;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const AdapterInfo& rhs) const;

      private:
        inline void FreeMembers();
    };

    struct BindGroupDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        BindGroupLayoutBase* layout;
        size_t entryCount = 0;
        BindGroupEntry const * entries = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BindGroupDescriptor& rhs) const;

    };

    struct BindGroupLayoutDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        size_t entryCount = 0;
        BindGroupLayoutEntry const * entries = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const BindGroupLayoutDescriptor& rhs) const;

    };

    struct ColorTargetState {
        ChainedStruct const * nextInChain = nullptr;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
        BlendState const * blend = nullptr;
        wgpu::ColorWriteMask writeMask = wgpu::ColorWriteMask::All;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ColorTargetState& rhs) const;

    };

    struct CompilationInfo {
        ChainedStruct const * nextInChain = nullptr;
        size_t messageCount;
        CompilationMessage const * messages = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const CompilationInfo& rhs) const;

    };

    struct ComputePipelineDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        PipelineLayoutBase* layout = nullptr;
        ComputeState compute;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const ComputePipelineDescriptor& rhs) const;

    };

    struct DawnFormatCapabilities {
        ChainedStructOut * nextInChain = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DawnFormatCapabilities& rhs) const;

    };

    struct DeviceDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        size_t requiredFeatureCount = 0;
        wgpu::FeatureName const * requiredFeatures = nullptr;
        Limits const * requiredLimits = nullptr;
        QueueDescriptor defaultQueue;
        WGPUDeviceLostCallbackInfo deviceLostCallbackInfo = WGPU_DEVICE_LOST_CALLBACK_INFO_INIT;
        WGPUUncapturedErrorCallbackInfo uncapturedErrorCallbackInfo = WGPU_UNCAPTURED_ERROR_CALLBACK_INFO_INIT;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const DeviceDescriptor& rhs) const;

    };

    struct PipelineLayoutDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        size_t bindGroupLayoutCount;
        BindGroupLayoutBase* const * bindGroupLayouts = nullptr;
        uint32_t immediateSize = 0;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const PipelineLayoutDescriptor& rhs) const;

    };

    struct RenderPassPixelLocalStorage : ChainedStruct {
        RenderPassPixelLocalStorage() {
            sType = wgpu::SType::RenderPassPixelLocalStorage;
        }
        alignas(wgpu::RenderPassPixelLocalStorage::kFirstMemberAlignment) uint64_t totalPixelLocalStorageSize;
        size_t storageAttachmentCount = 0;
        RenderPassStorageAttachment const * storageAttachments = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassPixelLocalStorage& rhs) const;

    };

    struct SharedTextureMemoryDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryDescriptor& rhs) const;

    };

    struct SharedTextureMemoryEndAccessState {
        SharedTextureMemoryEndAccessState() = default;
        ~SharedTextureMemoryEndAccessState();
        SharedTextureMemoryEndAccessState(const SharedTextureMemoryEndAccessState&) = delete;
        SharedTextureMemoryEndAccessState& operator=(const SharedTextureMemoryEndAccessState&) = delete;
        SharedTextureMemoryEndAccessState(SharedTextureMemoryEndAccessState&&);
        SharedTextureMemoryEndAccessState& operator=(SharedTextureMemoryEndAccessState&&);

        ChainedStructOut * nextInChain = nullptr;
        wgpu::Bool initialized;
        size_t fenceCount;
        SharedFenceBase* const * fences = nullptr;
        uint64_t const * signaledValues = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryEndAccessState& rhs) const;

      private:
        inline void FreeMembers();
    };

    struct SharedTextureMemoryProperties {
        ChainedStructOut * nextInChain = nullptr;
        wgpu::TextureUsage usage = wgpu::TextureUsage::None;
        Extent3D size;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const SharedTextureMemoryProperties& rhs) const;

    };

    struct TextureViewDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        wgpu::TextureFormat format = wgpu::TextureFormat::Undefined;
        wgpu::TextureViewDimension dimension = wgpu::TextureViewDimension::Undefined;
        uint32_t baseMipLevel = 0;
        uint32_t mipLevelCount = wgpu::kMipLevelCountUndefined;
        uint32_t baseArrayLayer = 0;
        uint32_t arrayLayerCount = wgpu::kArrayLayerCountUndefined;
        wgpu::TextureAspect aspect = wgpu::TextureAspect::All;
        wgpu::TextureUsage usage = wgpu::TextureUsage::None;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] TextureViewDescriptor WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const TextureViewDescriptor& rhs) const;

    };

    struct VertexState {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModuleBase* module;
        StringView entryPoint;
        size_t constantCount = 0;
        ConstantEntry const * constants = nullptr;
        size_t bufferCount = 0;
        VertexBufferLayout const * buffers = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const VertexState& rhs) const;

    };

    struct FragmentState {
        ChainedStruct const * nextInChain = nullptr;
        ShaderModuleBase* module;
        StringView entryPoint;
        size_t constantCount = 0;
        ConstantEntry const * constants = nullptr;
        size_t targetCount;
        ColorTargetState const * targets = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const FragmentState& rhs) const;

    };

    struct RenderPassDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        size_t colorAttachmentCount;
        RenderPassColorAttachment const * colorAttachments = nullptr;
        RenderPassDepthStencilAttachment const * depthStencilAttachment = nullptr;
        QuerySetBase* occlusionQuerySet = nullptr;
        PassTimestampWrites const * timestampWrites = nullptr;

        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPassDescriptor& rhs) const;

    };

    struct RenderPipelineDescriptor {
        ChainedStruct const * nextInChain = nullptr;
        StringView label;
        PipelineLayoutBase* layout = nullptr;
        VertexState vertex;
        PrimitiveState primitive;
        DepthStencilState const * depthStencil = nullptr;
        MultisampleState multisample;
        FragmentState const * fragment = nullptr;

        // This method makes a copy of the struct, then, for any enum members with trivial
        // defaulting (where something like "Undefined" is replaced with a default), applies
        // all of the defaults for the struct, and recursively its by-value substructs (but
        // NOT by-pointer substructs since they are const*). It must be called in an
        // appropriate place in Dawn.
        [[nodiscard]] RenderPipelineDescriptor WithTrivialFrontendDefaults() const;
        // Equality operators, mostly for testing. Note that this tests
        // strict pointer-pointer equality if the struct contains member pointers.
        bool operator==(const RenderPipelineDescriptor& rhs) const;

    };



    // SharedBufferMemoryEndAccessState
    void APISharedBufferMemoryEndAccessStateFreeMembers(WGPUSharedBufferMemoryEndAccessState);
    // SupportedFeatures
    void APISupportedFeaturesFreeMembers(WGPUSupportedFeatures);
    // SupportedInstanceFeatures
    void APISupportedInstanceFeaturesFreeMembers(WGPUSupportedInstanceFeatures);
    // SupportedWGSLLanguageFeatures
    void APISupportedWGSLLanguageFeaturesFreeMembers(WGPUSupportedWGSLLanguageFeatures);
    // SurfaceCapabilities
    void APISurfaceCapabilitiesFreeMembers(WGPUSurfaceCapabilities);
    // AdapterPropertiesMemoryHeaps
    void APIAdapterPropertiesMemoryHeapsFreeMembers(WGPUAdapterPropertiesMemoryHeaps);
    // AdapterPropertiesSubgroupMatrixConfigs
    void APIAdapterPropertiesSubgroupMatrixConfigsFreeMembers(WGPUAdapterPropertiesSubgroupMatrixConfigs);
    // DawnDrmFormatCapabilities
    void APIDawnDrmFormatCapabilitiesFreeMembers(WGPUDawnDrmFormatCapabilities);
    // AdapterInfo
    void APIAdapterInfoFreeMembers(WGPUAdapterInfo);
    // SharedTextureMemoryEndAccessState
    void APISharedTextureMemoryEndAccessStateFreeMembers(WGPUSharedTextureMemoryEndAccessState);

} // namespace dawn::native

#endif  // DAWNNATIVE_WGPU_STRUCTS_H_
