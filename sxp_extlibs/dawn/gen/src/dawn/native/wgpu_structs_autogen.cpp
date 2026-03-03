
#include "dawn/native/wgpu_structs_autogen.h"

#include <cstring>
#include <tuple>

#include "dawn/common/Assert.h"

#if defined(__GNUC__) || defined(__clang__)
// error: 'offsetof' within non-standard-layout type 'wgpu::XXX' is conditionally-supported
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#endif

namespace dawn::native {

    static_assert(sizeof(ChainedStruct) == sizeof(WGPUChainedStruct),
            "sizeof mismatch for ChainedStruct");
    static_assert(alignof(ChainedStruct) == alignof(WGPUChainedStruct),
            "alignof mismatch for ChainedStruct");
    static_assert(offsetof(ChainedStruct, nextInChain) == offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for ChainedStruct::nextInChain");
    static_assert(offsetof(ChainedStruct, sType) == offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for ChainedStruct::sType");


    bool StringView::operator==(const StringView& rhs) const {
        return data == rhs.data && length == rhs.length;
    }


    static_assert(sizeof(AdapterPropertiesD3D) == sizeof(WGPUAdapterPropertiesD3D), "sizeof mismatch for AdapterPropertiesD3D");
    static_assert(alignof(AdapterPropertiesD3D) == alignof(WGPUAdapterPropertiesD3D), "alignof mismatch for AdapterPropertiesD3D");

    static_assert(offsetof(AdapterPropertiesD3D, nextInChain) == offsetof(WGPUAdapterPropertiesD3D, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for AdapterPropertiesD3D::nextInChain");
    static_assert(offsetof(AdapterPropertiesD3D, sType) == offsetof(WGPUAdapterPropertiesD3D, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for AdapterPropertiesD3D::sType");
    static_assert(offsetof(AdapterPropertiesD3D, shaderModel) == offsetof(WGPUAdapterPropertiesD3D, shaderModel),
                 "offsetof mismatch for AdapterPropertiesD3D::shaderModel");

    bool AdapterPropertiesD3D::operator==(const AdapterPropertiesD3D& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            shaderModel
        ) == std::tie(
            rhs.shaderModel
        );
    }


    static_assert(sizeof(AdapterPropertiesExplicitComputeSubgroupSizeConfigs) == sizeof(WGPUAdapterPropertiesExplicitComputeSubgroupSizeConfigs), "sizeof mismatch for AdapterPropertiesExplicitComputeSubgroupSizeConfigs");
    static_assert(alignof(AdapterPropertiesExplicitComputeSubgroupSizeConfigs) == alignof(WGPUAdapterPropertiesExplicitComputeSubgroupSizeConfigs), "alignof mismatch for AdapterPropertiesExplicitComputeSubgroupSizeConfigs");

    static_assert(offsetof(AdapterPropertiesExplicitComputeSubgroupSizeConfigs, nextInChain) == offsetof(WGPUAdapterPropertiesExplicitComputeSubgroupSizeConfigs, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for AdapterPropertiesExplicitComputeSubgroupSizeConfigs::nextInChain");
    static_assert(offsetof(AdapterPropertiesExplicitComputeSubgroupSizeConfigs, sType) == offsetof(WGPUAdapterPropertiesExplicitComputeSubgroupSizeConfigs, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for AdapterPropertiesExplicitComputeSubgroupSizeConfigs::sType");
    static_assert(offsetof(AdapterPropertiesExplicitComputeSubgroupSizeConfigs, minExplicitComputeSubgroupSize) == offsetof(WGPUAdapterPropertiesExplicitComputeSubgroupSizeConfigs, minExplicitComputeSubgroupSize),
                 "offsetof mismatch for AdapterPropertiesExplicitComputeSubgroupSizeConfigs::minExplicitComputeSubgroupSize");
    static_assert(offsetof(AdapterPropertiesExplicitComputeSubgroupSizeConfigs, maxExplicitComputeSubgroupSize) == offsetof(WGPUAdapterPropertiesExplicitComputeSubgroupSizeConfigs, maxExplicitComputeSubgroupSize),
                 "offsetof mismatch for AdapterPropertiesExplicitComputeSubgroupSizeConfigs::maxExplicitComputeSubgroupSize");
    static_assert(offsetof(AdapterPropertiesExplicitComputeSubgroupSizeConfigs, maxComputeWorkgroupSubgroups) == offsetof(WGPUAdapterPropertiesExplicitComputeSubgroupSizeConfigs, maxComputeWorkgroupSubgroups),
                 "offsetof mismatch for AdapterPropertiesExplicitComputeSubgroupSizeConfigs::maxComputeWorkgroupSubgroups");

    bool AdapterPropertiesExplicitComputeSubgroupSizeConfigs::operator==(const AdapterPropertiesExplicitComputeSubgroupSizeConfigs& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            minExplicitComputeSubgroupSize,
            maxExplicitComputeSubgroupSize,
            maxComputeWorkgroupSubgroups
        ) == std::tie(
            rhs.minExplicitComputeSubgroupSize,
            rhs.maxExplicitComputeSubgroupSize,
            rhs.maxComputeWorkgroupSubgroups
        );
    }


    static_assert(sizeof(AdapterPropertiesVk) == sizeof(WGPUAdapterPropertiesVk), "sizeof mismatch for AdapterPropertiesVk");
    static_assert(alignof(AdapterPropertiesVk) == alignof(WGPUAdapterPropertiesVk), "alignof mismatch for AdapterPropertiesVk");

    static_assert(offsetof(AdapterPropertiesVk, nextInChain) == offsetof(WGPUAdapterPropertiesVk, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for AdapterPropertiesVk::nextInChain");
    static_assert(offsetof(AdapterPropertiesVk, sType) == offsetof(WGPUAdapterPropertiesVk, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for AdapterPropertiesVk::sType");
    static_assert(offsetof(AdapterPropertiesVk, driverVersion) == offsetof(WGPUAdapterPropertiesVk, driverVersion),
                 "offsetof mismatch for AdapterPropertiesVk::driverVersion");

    bool AdapterPropertiesVk::operator==(const AdapterPropertiesVk& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            driverVersion
        ) == std::tie(
            rhs.driverVersion
        );
    }


    static_assert(sizeof(AdapterPropertiesWGPU) == sizeof(WGPUAdapterPropertiesWGPU), "sizeof mismatch for AdapterPropertiesWGPU");
    static_assert(alignof(AdapterPropertiesWGPU) == alignof(WGPUAdapterPropertiesWGPU), "alignof mismatch for AdapterPropertiesWGPU");

    static_assert(offsetof(AdapterPropertiesWGPU, nextInChain) == offsetof(WGPUAdapterPropertiesWGPU, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for AdapterPropertiesWGPU::nextInChain");
    static_assert(offsetof(AdapterPropertiesWGPU, sType) == offsetof(WGPUAdapterPropertiesWGPU, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for AdapterPropertiesWGPU::sType");
    static_assert(offsetof(AdapterPropertiesWGPU, backendType) == offsetof(WGPUAdapterPropertiesWGPU, backendType),
                 "offsetof mismatch for AdapterPropertiesWGPU::backendType");

    bool AdapterPropertiesWGPU::operator==(const AdapterPropertiesWGPU& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            backendType
        ) == std::tie(
            rhs.backendType
        );
    }


    static_assert(sizeof(BindingResource) == sizeof(WGPUBindingResource), "sizeof mismatch for BindingResource");
    static_assert(alignof(BindingResource) == alignof(WGPUBindingResource), "alignof mismatch for BindingResource");

    static_assert(offsetof(BindingResource, nextInChain) == offsetof(WGPUBindingResource, nextInChain),
            "offsetof mismatch for BindingResource::nextInChain");
    static_assert(offsetof(BindingResource, buffer) == offsetof(WGPUBindingResource, buffer),
                 "offsetof mismatch for BindingResource::buffer");
    static_assert(offsetof(BindingResource, offset) == offsetof(WGPUBindingResource, offset),
                 "offsetof mismatch for BindingResource::offset");
    static_assert(offsetof(BindingResource, size) == offsetof(WGPUBindingResource, size),
                 "offsetof mismatch for BindingResource::size");
    static_assert(offsetof(BindingResource, sampler) == offsetof(WGPUBindingResource, sampler),
                 "offsetof mismatch for BindingResource::sampler");
    static_assert(offsetof(BindingResource, textureView) == offsetof(WGPUBindingResource, textureView),
                 "offsetof mismatch for BindingResource::textureView");

    bool BindingResource::operator==(const BindingResource& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            buffer,
            offset,
            size,
            sampler,
            textureView
        ) == std::tie(
            rhs.buffer,
            rhs.offset,
            rhs.size,
            rhs.sampler,
            rhs.textureView
        );
    }


    static_assert(sizeof(BlendComponent) == sizeof(WGPUBlendComponent), "sizeof mismatch for BlendComponent");
    static_assert(alignof(BlendComponent) == alignof(WGPUBlendComponent), "alignof mismatch for BlendComponent");

    static_assert(offsetof(BlendComponent, operation) == offsetof(WGPUBlendComponent, operation),
                 "offsetof mismatch for BlendComponent::operation");
    static_assert(offsetof(BlendComponent, srcFactor) == offsetof(WGPUBlendComponent, srcFactor),
                 "offsetof mismatch for BlendComponent::srcFactor");
    static_assert(offsetof(BlendComponent, dstFactor) == offsetof(WGPUBlendComponent, dstFactor),
                 "offsetof mismatch for BlendComponent::dstFactor");

    BlendComponent BlendComponent::WithTrivialFrontendDefaults() const {
        BlendComponent copy;
        copy.operation = (operation == wgpu::BlendOperation::Undefined)
            ? wgpu::BlendOperation::Add
            : operation;
        copy.srcFactor = (srcFactor == wgpu::BlendFactor::Undefined)
            ? wgpu::BlendFactor::One
            : srcFactor;
        copy.dstFactor = (dstFactor == wgpu::BlendFactor::Undefined)
            ? wgpu::BlendFactor::Zero
            : dstFactor;
        return copy;
    }
    bool BlendComponent::operator==(const BlendComponent& rhs) const {
        return  std::tie(
            operation,
            srcFactor,
            dstFactor
        ) == std::tie(
            rhs.operation,
            rhs.srcFactor,
            rhs.dstFactor
        );
    }


    static_assert(sizeof(BufferBindingLayout) == sizeof(WGPUBufferBindingLayout), "sizeof mismatch for BufferBindingLayout");
    static_assert(alignof(BufferBindingLayout) == alignof(WGPUBufferBindingLayout), "alignof mismatch for BufferBindingLayout");

    static_assert(offsetof(BufferBindingLayout, nextInChain) == offsetof(WGPUBufferBindingLayout, nextInChain),
            "offsetof mismatch for BufferBindingLayout::nextInChain");
    static_assert(offsetof(BufferBindingLayout, type) == offsetof(WGPUBufferBindingLayout, type),
                 "offsetof mismatch for BufferBindingLayout::type");
    static_assert(offsetof(BufferBindingLayout, hasDynamicOffset) == offsetof(WGPUBufferBindingLayout, hasDynamicOffset),
                 "offsetof mismatch for BufferBindingLayout::hasDynamicOffset");
    static_assert(offsetof(BufferBindingLayout, minBindingSize) == offsetof(WGPUBufferBindingLayout, minBindingSize),
                 "offsetof mismatch for BufferBindingLayout::minBindingSize");

    BufferBindingLayout BufferBindingLayout::WithTrivialFrontendDefaults() const {
        BufferBindingLayout copy;
        copy.nextInChain = nextInChain;
        copy.type = (type == wgpu::BufferBindingType::Undefined)
            ? wgpu::BufferBindingType::Uniform
            : type;
        copy.hasDynamicOffset = hasDynamicOffset;
        copy.minBindingSize = minBindingSize;
        return copy;
    }
    bool BufferBindingLayout::operator==(const BufferBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            type,
            hasDynamicOffset,
            minBindingSize
        ) == std::tie(
            rhs.type,
            rhs.hasDynamicOffset,
            rhs.minBindingSize
        );
    }


    static_assert(sizeof(BufferHostMappedPointer) == sizeof(WGPUBufferHostMappedPointer), "sizeof mismatch for BufferHostMappedPointer");
    static_assert(alignof(BufferHostMappedPointer) == alignof(WGPUBufferHostMappedPointer), "alignof mismatch for BufferHostMappedPointer");

    static_assert(offsetof(BufferHostMappedPointer, nextInChain) == offsetof(WGPUBufferHostMappedPointer, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for BufferHostMappedPointer::nextInChain");
    static_assert(offsetof(BufferHostMappedPointer, sType) == offsetof(WGPUBufferHostMappedPointer, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for BufferHostMappedPointer::sType");
    static_assert(offsetof(BufferHostMappedPointer, pointer) == offsetof(WGPUBufferHostMappedPointer, pointer),
                 "offsetof mismatch for BufferHostMappedPointer::pointer");
    static_assert(offsetof(BufferHostMappedPointer, disposeCallback) == offsetof(WGPUBufferHostMappedPointer, disposeCallback),
                 "offsetof mismatch for BufferHostMappedPointer::disposeCallback");
    static_assert(offsetof(BufferHostMappedPointer, userdata) == offsetof(WGPUBufferHostMappedPointer, userdata),
                 "offsetof mismatch for BufferHostMappedPointer::userdata");

    bool BufferHostMappedPointer::operator==(const BufferHostMappedPointer& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            pointer,
            disposeCallback,
            userdata
        ) == std::tie(
            rhs.pointer,
            rhs.disposeCallback,
            rhs.userdata
        );
    }


    static_assert(sizeof(Color) == sizeof(WGPUColor), "sizeof mismatch for Color");
    static_assert(alignof(Color) == alignof(WGPUColor), "alignof mismatch for Color");

    static_assert(offsetof(Color, r) == offsetof(WGPUColor, r),
                 "offsetof mismatch for Color::r");
    static_assert(offsetof(Color, g) == offsetof(WGPUColor, g),
                 "offsetof mismatch for Color::g");
    static_assert(offsetof(Color, b) == offsetof(WGPUColor, b),
                 "offsetof mismatch for Color::b");
    static_assert(offsetof(Color, a) == offsetof(WGPUColor, a),
                 "offsetof mismatch for Color::a");

    bool Color::operator==(const Color& rhs) const {
        return  std::tie(
            r,
            g,
            b,
            a
        ) == std::tie(
            rhs.r,
            rhs.g,
            rhs.b,
            rhs.a
        );
    }


    static_assert(sizeof(ColorTargetStateExpandResolveTextureDawn) == sizeof(WGPUColorTargetStateExpandResolveTextureDawn), "sizeof mismatch for ColorTargetStateExpandResolveTextureDawn");
    static_assert(alignof(ColorTargetStateExpandResolveTextureDawn) == alignof(WGPUColorTargetStateExpandResolveTextureDawn), "alignof mismatch for ColorTargetStateExpandResolveTextureDawn");

    static_assert(offsetof(ColorTargetStateExpandResolveTextureDawn, nextInChain) == offsetof(WGPUColorTargetStateExpandResolveTextureDawn, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for ColorTargetStateExpandResolveTextureDawn::nextInChain");
    static_assert(offsetof(ColorTargetStateExpandResolveTextureDawn, sType) == offsetof(WGPUColorTargetStateExpandResolveTextureDawn, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for ColorTargetStateExpandResolveTextureDawn::sType");
    static_assert(offsetof(ColorTargetStateExpandResolveTextureDawn, enabled) == offsetof(WGPUColorTargetStateExpandResolveTextureDawn, enabled),
                 "offsetof mismatch for ColorTargetStateExpandResolveTextureDawn::enabled");

    bool ColorTargetStateExpandResolveTextureDawn::operator==(const ColorTargetStateExpandResolveTextureDawn& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            enabled
        ) == std::tie(
            rhs.enabled
        );
    }


    static_assert(sizeof(CommandBufferDescriptor) == sizeof(WGPUCommandBufferDescriptor), "sizeof mismatch for CommandBufferDescriptor");
    static_assert(alignof(CommandBufferDescriptor) == alignof(WGPUCommandBufferDescriptor), "alignof mismatch for CommandBufferDescriptor");

    static_assert(offsetof(CommandBufferDescriptor, nextInChain) == offsetof(WGPUCommandBufferDescriptor, nextInChain),
            "offsetof mismatch for CommandBufferDescriptor::nextInChain");
    static_assert(offsetof(CommandBufferDescriptor, label) == offsetof(WGPUCommandBufferDescriptor, label),
                 "offsetof mismatch for CommandBufferDescriptor::label");

    bool CommandBufferDescriptor::operator==(const CommandBufferDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(CompatibilityModeLimits) == sizeof(WGPUCompatibilityModeLimits), "sizeof mismatch for CompatibilityModeLimits");
    static_assert(alignof(CompatibilityModeLimits) == alignof(WGPUCompatibilityModeLimits), "alignof mismatch for CompatibilityModeLimits");

    static_assert(offsetof(CompatibilityModeLimits, nextInChain) == offsetof(WGPUCompatibilityModeLimits, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for CompatibilityModeLimits::nextInChain");
    static_assert(offsetof(CompatibilityModeLimits, sType) == offsetof(WGPUCompatibilityModeLimits, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for CompatibilityModeLimits::sType");
    static_assert(offsetof(CompatibilityModeLimits, maxStorageBuffersInVertexStage) == offsetof(WGPUCompatibilityModeLimits, maxStorageBuffersInVertexStage),
                 "offsetof mismatch for CompatibilityModeLimits::maxStorageBuffersInVertexStage");
    static_assert(offsetof(CompatibilityModeLimits, maxStorageTexturesInVertexStage) == offsetof(WGPUCompatibilityModeLimits, maxStorageTexturesInVertexStage),
                 "offsetof mismatch for CompatibilityModeLimits::maxStorageTexturesInVertexStage");
    static_assert(offsetof(CompatibilityModeLimits, maxStorageBuffersInFragmentStage) == offsetof(WGPUCompatibilityModeLimits, maxStorageBuffersInFragmentStage),
                 "offsetof mismatch for CompatibilityModeLimits::maxStorageBuffersInFragmentStage");
    static_assert(offsetof(CompatibilityModeLimits, maxStorageTexturesInFragmentStage) == offsetof(WGPUCompatibilityModeLimits, maxStorageTexturesInFragmentStage),
                 "offsetof mismatch for CompatibilityModeLimits::maxStorageTexturesInFragmentStage");

    bool CompatibilityModeLimits::operator==(const CompatibilityModeLimits& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            maxStorageBuffersInVertexStage,
            maxStorageTexturesInVertexStage,
            maxStorageBuffersInFragmentStage,
            maxStorageTexturesInFragmentStage
        ) == std::tie(
            rhs.maxStorageBuffersInVertexStage,
            rhs.maxStorageTexturesInVertexStage,
            rhs.maxStorageBuffersInFragmentStage,
            rhs.maxStorageTexturesInFragmentStage
        );
    }


    static_assert(sizeof(ConstantEntry) == sizeof(WGPUConstantEntry), "sizeof mismatch for ConstantEntry");
    static_assert(alignof(ConstantEntry) == alignof(WGPUConstantEntry), "alignof mismatch for ConstantEntry");

    static_assert(offsetof(ConstantEntry, nextInChain) == offsetof(WGPUConstantEntry, nextInChain),
            "offsetof mismatch for ConstantEntry::nextInChain");
    static_assert(offsetof(ConstantEntry, key) == offsetof(WGPUConstantEntry, key),
                 "offsetof mismatch for ConstantEntry::key");
    static_assert(offsetof(ConstantEntry, value) == offsetof(WGPUConstantEntry, value),
                 "offsetof mismatch for ConstantEntry::value");

    bool ConstantEntry::operator==(const ConstantEntry& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            key,
            value
        ) == std::tie(
            rhs.key,
            rhs.value
        );
    }


    static_assert(sizeof(CopyTextureForBrowserOptions) == sizeof(WGPUCopyTextureForBrowserOptions), "sizeof mismatch for CopyTextureForBrowserOptions");
    static_assert(alignof(CopyTextureForBrowserOptions) == alignof(WGPUCopyTextureForBrowserOptions), "alignof mismatch for CopyTextureForBrowserOptions");

    static_assert(offsetof(CopyTextureForBrowserOptions, nextInChain) == offsetof(WGPUCopyTextureForBrowserOptions, nextInChain),
            "offsetof mismatch for CopyTextureForBrowserOptions::nextInChain");
    static_assert(offsetof(CopyTextureForBrowserOptions, flipY) == offsetof(WGPUCopyTextureForBrowserOptions, flipY),
                 "offsetof mismatch for CopyTextureForBrowserOptions::flipY");
    static_assert(offsetof(CopyTextureForBrowserOptions, needsColorSpaceConversion) == offsetof(WGPUCopyTextureForBrowserOptions, needsColorSpaceConversion),
                 "offsetof mismatch for CopyTextureForBrowserOptions::needsColorSpaceConversion");
    static_assert(offsetof(CopyTextureForBrowserOptions, srcAlphaMode) == offsetof(WGPUCopyTextureForBrowserOptions, srcAlphaMode),
                 "offsetof mismatch for CopyTextureForBrowserOptions::srcAlphaMode");
    static_assert(offsetof(CopyTextureForBrowserOptions, srcTransferFunctionParameters) == offsetof(WGPUCopyTextureForBrowserOptions, srcTransferFunctionParameters),
                 "offsetof mismatch for CopyTextureForBrowserOptions::srcTransferFunctionParameters");
    static_assert(offsetof(CopyTextureForBrowserOptions, conversionMatrix) == offsetof(WGPUCopyTextureForBrowserOptions, conversionMatrix),
                 "offsetof mismatch for CopyTextureForBrowserOptions::conversionMatrix");
    static_assert(offsetof(CopyTextureForBrowserOptions, dstTransferFunctionParameters) == offsetof(WGPUCopyTextureForBrowserOptions, dstTransferFunctionParameters),
                 "offsetof mismatch for CopyTextureForBrowserOptions::dstTransferFunctionParameters");
    static_assert(offsetof(CopyTextureForBrowserOptions, dstAlphaMode) == offsetof(WGPUCopyTextureForBrowserOptions, dstAlphaMode),
                 "offsetof mismatch for CopyTextureForBrowserOptions::dstAlphaMode");
    static_assert(offsetof(CopyTextureForBrowserOptions, internalUsage) == offsetof(WGPUCopyTextureForBrowserOptions, internalUsage),
                 "offsetof mismatch for CopyTextureForBrowserOptions::internalUsage");

    bool CopyTextureForBrowserOptions::operator==(const CopyTextureForBrowserOptions& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            flipY,
            needsColorSpaceConversion,
            srcAlphaMode,
            srcTransferFunctionParameters,
            conversionMatrix,
            dstTransferFunctionParameters,
            dstAlphaMode,
            internalUsage
        ) == std::tie(
            rhs.flipY,
            rhs.needsColorSpaceConversion,
            rhs.srcAlphaMode,
            rhs.srcTransferFunctionParameters,
            rhs.conversionMatrix,
            rhs.dstTransferFunctionParameters,
            rhs.dstAlphaMode,
            rhs.internalUsage
        );
    }


    static_assert(sizeof(DawnAdapterPropertiesPowerPreference) == sizeof(WGPUDawnAdapterPropertiesPowerPreference), "sizeof mismatch for DawnAdapterPropertiesPowerPreference");
    static_assert(alignof(DawnAdapterPropertiesPowerPreference) == alignof(WGPUDawnAdapterPropertiesPowerPreference), "alignof mismatch for DawnAdapterPropertiesPowerPreference");

    static_assert(offsetof(DawnAdapterPropertiesPowerPreference, nextInChain) == offsetof(WGPUDawnAdapterPropertiesPowerPreference, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnAdapterPropertiesPowerPreference::nextInChain");
    static_assert(offsetof(DawnAdapterPropertiesPowerPreference, sType) == offsetof(WGPUDawnAdapterPropertiesPowerPreference, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnAdapterPropertiesPowerPreference::sType");
    static_assert(offsetof(DawnAdapterPropertiesPowerPreference, powerPreference) == offsetof(WGPUDawnAdapterPropertiesPowerPreference, powerPreference),
                 "offsetof mismatch for DawnAdapterPropertiesPowerPreference::powerPreference");

    bool DawnAdapterPropertiesPowerPreference::operator==(const DawnAdapterPropertiesPowerPreference& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            powerPreference
        ) == std::tie(
            rhs.powerPreference
        );
    }


    static_assert(sizeof(DawnBufferDescriptorErrorInfoFromWireClient) == sizeof(WGPUDawnBufferDescriptorErrorInfoFromWireClient), "sizeof mismatch for DawnBufferDescriptorErrorInfoFromWireClient");
    static_assert(alignof(DawnBufferDescriptorErrorInfoFromWireClient) == alignof(WGPUDawnBufferDescriptorErrorInfoFromWireClient), "alignof mismatch for DawnBufferDescriptorErrorInfoFromWireClient");

    static_assert(offsetof(DawnBufferDescriptorErrorInfoFromWireClient, nextInChain) == offsetof(WGPUDawnBufferDescriptorErrorInfoFromWireClient, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnBufferDescriptorErrorInfoFromWireClient::nextInChain");
    static_assert(offsetof(DawnBufferDescriptorErrorInfoFromWireClient, sType) == offsetof(WGPUDawnBufferDescriptorErrorInfoFromWireClient, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnBufferDescriptorErrorInfoFromWireClient::sType");
    static_assert(offsetof(DawnBufferDescriptorErrorInfoFromWireClient, outOfMemory) == offsetof(WGPUDawnBufferDescriptorErrorInfoFromWireClient, outOfMemory),
                 "offsetof mismatch for DawnBufferDescriptorErrorInfoFromWireClient::outOfMemory");

    bool DawnBufferDescriptorErrorInfoFromWireClient::operator==(const DawnBufferDescriptorErrorInfoFromWireClient& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            outOfMemory
        ) == std::tie(
            rhs.outOfMemory
        );
    }


    static_assert(sizeof(DawnCacheDeviceDescriptor) == sizeof(WGPUDawnCacheDeviceDescriptor), "sizeof mismatch for DawnCacheDeviceDescriptor");
    static_assert(alignof(DawnCacheDeviceDescriptor) == alignof(WGPUDawnCacheDeviceDescriptor), "alignof mismatch for DawnCacheDeviceDescriptor");

    static_assert(offsetof(DawnCacheDeviceDescriptor, nextInChain) == offsetof(WGPUDawnCacheDeviceDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnCacheDeviceDescriptor::nextInChain");
    static_assert(offsetof(DawnCacheDeviceDescriptor, sType) == offsetof(WGPUDawnCacheDeviceDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnCacheDeviceDescriptor::sType");
    static_assert(offsetof(DawnCacheDeviceDescriptor, isolationKey) == offsetof(WGPUDawnCacheDeviceDescriptor, isolationKey),
                 "offsetof mismatch for DawnCacheDeviceDescriptor::isolationKey");
    static_assert(offsetof(DawnCacheDeviceDescriptor, loadDataFunction) == offsetof(WGPUDawnCacheDeviceDescriptor, loadDataFunction),
                 "offsetof mismatch for DawnCacheDeviceDescriptor::loadDataFunction");
    static_assert(offsetof(DawnCacheDeviceDescriptor, storeDataFunction) == offsetof(WGPUDawnCacheDeviceDescriptor, storeDataFunction),
                 "offsetof mismatch for DawnCacheDeviceDescriptor::storeDataFunction");
    static_assert(offsetof(DawnCacheDeviceDescriptor, functionUserdata) == offsetof(WGPUDawnCacheDeviceDescriptor, functionUserdata),
                 "offsetof mismatch for DawnCacheDeviceDescriptor::functionUserdata");

    bool DawnCacheDeviceDescriptor::operator==(const DawnCacheDeviceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            isolationKey,
            loadDataFunction,
            storeDataFunction,
            functionUserdata
        ) == std::tie(
            rhs.isolationKey,
            rhs.loadDataFunction,
            rhs.storeDataFunction,
            rhs.functionUserdata
        );
    }


    static_assert(sizeof(DawnCompilationMessageUtf16) == sizeof(WGPUDawnCompilationMessageUtf16), "sizeof mismatch for DawnCompilationMessageUtf16");
    static_assert(alignof(DawnCompilationMessageUtf16) == alignof(WGPUDawnCompilationMessageUtf16), "alignof mismatch for DawnCompilationMessageUtf16");

    static_assert(offsetof(DawnCompilationMessageUtf16, nextInChain) == offsetof(WGPUDawnCompilationMessageUtf16, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnCompilationMessageUtf16::nextInChain");
    static_assert(offsetof(DawnCompilationMessageUtf16, sType) == offsetof(WGPUDawnCompilationMessageUtf16, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnCompilationMessageUtf16::sType");
    static_assert(offsetof(DawnCompilationMessageUtf16, linePos) == offsetof(WGPUDawnCompilationMessageUtf16, linePos),
                 "offsetof mismatch for DawnCompilationMessageUtf16::linePos");
    static_assert(offsetof(DawnCompilationMessageUtf16, offset) == offsetof(WGPUDawnCompilationMessageUtf16, offset),
                 "offsetof mismatch for DawnCompilationMessageUtf16::offset");
    static_assert(offsetof(DawnCompilationMessageUtf16, length) == offsetof(WGPUDawnCompilationMessageUtf16, length),
                 "offsetof mismatch for DawnCompilationMessageUtf16::length");

    bool DawnCompilationMessageUtf16::operator==(const DawnCompilationMessageUtf16& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            linePos,
            offset,
            length
        ) == std::tie(
            rhs.linePos,
            rhs.offset,
            rhs.length
        );
    }


    static_assert(sizeof(DawnConsumeAdapterDescriptor) == sizeof(WGPUDawnConsumeAdapterDescriptor), "sizeof mismatch for DawnConsumeAdapterDescriptor");
    static_assert(alignof(DawnConsumeAdapterDescriptor) == alignof(WGPUDawnConsumeAdapterDescriptor), "alignof mismatch for DawnConsumeAdapterDescriptor");

    static_assert(offsetof(DawnConsumeAdapterDescriptor, nextInChain) == offsetof(WGPUDawnConsumeAdapterDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnConsumeAdapterDescriptor::nextInChain");
    static_assert(offsetof(DawnConsumeAdapterDescriptor, sType) == offsetof(WGPUDawnConsumeAdapterDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnConsumeAdapterDescriptor::sType");
    static_assert(offsetof(DawnConsumeAdapterDescriptor, consumeAdapter) == offsetof(WGPUDawnConsumeAdapterDescriptor, consumeAdapter),
                 "offsetof mismatch for DawnConsumeAdapterDescriptor::consumeAdapter");

    bool DawnConsumeAdapterDescriptor::operator==(const DawnConsumeAdapterDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            consumeAdapter
        ) == std::tie(
            rhs.consumeAdapter
        );
    }


    static_assert(sizeof(DawnDeviceAllocatorControl) == sizeof(WGPUDawnDeviceAllocatorControl), "sizeof mismatch for DawnDeviceAllocatorControl");
    static_assert(alignof(DawnDeviceAllocatorControl) == alignof(WGPUDawnDeviceAllocatorControl), "alignof mismatch for DawnDeviceAllocatorControl");

    static_assert(offsetof(DawnDeviceAllocatorControl, nextInChain) == offsetof(WGPUDawnDeviceAllocatorControl, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnDeviceAllocatorControl::nextInChain");
    static_assert(offsetof(DawnDeviceAllocatorControl, sType) == offsetof(WGPUDawnDeviceAllocatorControl, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnDeviceAllocatorControl::sType");
    static_assert(offsetof(DawnDeviceAllocatorControl, allocatorHeapBlockSize) == offsetof(WGPUDawnDeviceAllocatorControl, allocatorHeapBlockSize),
                 "offsetof mismatch for DawnDeviceAllocatorControl::allocatorHeapBlockSize");

    bool DawnDeviceAllocatorControl::operator==(const DawnDeviceAllocatorControl& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            allocatorHeapBlockSize
        ) == std::tie(
            rhs.allocatorHeapBlockSize
        );
    }


    static_assert(sizeof(DawnDrmFormatProperties) == sizeof(WGPUDawnDrmFormatProperties), "sizeof mismatch for DawnDrmFormatProperties");
    static_assert(alignof(DawnDrmFormatProperties) == alignof(WGPUDawnDrmFormatProperties), "alignof mismatch for DawnDrmFormatProperties");

    static_assert(offsetof(DawnDrmFormatProperties, modifier) == offsetof(WGPUDawnDrmFormatProperties, modifier),
                 "offsetof mismatch for DawnDrmFormatProperties::modifier");
    static_assert(offsetof(DawnDrmFormatProperties, modifierPlaneCount) == offsetof(WGPUDawnDrmFormatProperties, modifierPlaneCount),
                 "offsetof mismatch for DawnDrmFormatProperties::modifierPlaneCount");

    bool DawnDrmFormatProperties::operator==(const DawnDrmFormatProperties& rhs) const {
        return  std::tie(
            modifier,
            modifierPlaneCount
        ) == std::tie(
            rhs.modifier,
            rhs.modifierPlaneCount
        );
    }


    static_assert(sizeof(DawnEncoderInternalUsageDescriptor) == sizeof(WGPUDawnEncoderInternalUsageDescriptor), "sizeof mismatch for DawnEncoderInternalUsageDescriptor");
    static_assert(alignof(DawnEncoderInternalUsageDescriptor) == alignof(WGPUDawnEncoderInternalUsageDescriptor), "alignof mismatch for DawnEncoderInternalUsageDescriptor");

    static_assert(offsetof(DawnEncoderInternalUsageDescriptor, nextInChain) == offsetof(WGPUDawnEncoderInternalUsageDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnEncoderInternalUsageDescriptor::nextInChain");
    static_assert(offsetof(DawnEncoderInternalUsageDescriptor, sType) == offsetof(WGPUDawnEncoderInternalUsageDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnEncoderInternalUsageDescriptor::sType");
    static_assert(offsetof(DawnEncoderInternalUsageDescriptor, useInternalUsages) == offsetof(WGPUDawnEncoderInternalUsageDescriptor, useInternalUsages),
                 "offsetof mismatch for DawnEncoderInternalUsageDescriptor::useInternalUsages");

    bool DawnEncoderInternalUsageDescriptor::operator==(const DawnEncoderInternalUsageDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            useInternalUsages
        ) == std::tie(
            rhs.useInternalUsages
        );
    }


    static_assert(sizeof(DawnFakeBufferOOMForTesting) == sizeof(WGPUDawnFakeBufferOOMForTesting), "sizeof mismatch for DawnFakeBufferOOMForTesting");
    static_assert(alignof(DawnFakeBufferOOMForTesting) == alignof(WGPUDawnFakeBufferOOMForTesting), "alignof mismatch for DawnFakeBufferOOMForTesting");

    static_assert(offsetof(DawnFakeBufferOOMForTesting, nextInChain) == offsetof(WGPUDawnFakeBufferOOMForTesting, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnFakeBufferOOMForTesting::nextInChain");
    static_assert(offsetof(DawnFakeBufferOOMForTesting, sType) == offsetof(WGPUDawnFakeBufferOOMForTesting, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnFakeBufferOOMForTesting::sType");
    static_assert(offsetof(DawnFakeBufferOOMForTesting, fakeOOMAtWireClientMap) == offsetof(WGPUDawnFakeBufferOOMForTesting, fakeOOMAtWireClientMap),
                 "offsetof mismatch for DawnFakeBufferOOMForTesting::fakeOOMAtWireClientMap");
    static_assert(offsetof(DawnFakeBufferOOMForTesting, fakeOOMAtNativeMap) == offsetof(WGPUDawnFakeBufferOOMForTesting, fakeOOMAtNativeMap),
                 "offsetof mismatch for DawnFakeBufferOOMForTesting::fakeOOMAtNativeMap");
    static_assert(offsetof(DawnFakeBufferOOMForTesting, fakeOOMAtDevice) == offsetof(WGPUDawnFakeBufferOOMForTesting, fakeOOMAtDevice),
                 "offsetof mismatch for DawnFakeBufferOOMForTesting::fakeOOMAtDevice");

    bool DawnFakeBufferOOMForTesting::operator==(const DawnFakeBufferOOMForTesting& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            fakeOOMAtWireClientMap,
            fakeOOMAtNativeMap,
            fakeOOMAtDevice
        ) == std::tie(
            rhs.fakeOOMAtWireClientMap,
            rhs.fakeOOMAtNativeMap,
            rhs.fakeOOMAtDevice
        );
    }


    static_assert(sizeof(DawnFakeDeviceInitializeErrorForTesting) == sizeof(WGPUDawnFakeDeviceInitializeErrorForTesting), "sizeof mismatch for DawnFakeDeviceInitializeErrorForTesting");
    static_assert(alignof(DawnFakeDeviceInitializeErrorForTesting) == alignof(WGPUDawnFakeDeviceInitializeErrorForTesting), "alignof mismatch for DawnFakeDeviceInitializeErrorForTesting");

    static_assert(offsetof(DawnFakeDeviceInitializeErrorForTesting, nextInChain) == offsetof(WGPUDawnFakeDeviceInitializeErrorForTesting, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnFakeDeviceInitializeErrorForTesting::nextInChain");
    static_assert(offsetof(DawnFakeDeviceInitializeErrorForTesting, sType) == offsetof(WGPUDawnFakeDeviceInitializeErrorForTesting, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnFakeDeviceInitializeErrorForTesting::sType");

    bool DawnFakeDeviceInitializeErrorForTesting::operator==(const DawnFakeDeviceInitializeErrorForTesting& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
        ) == std::tie(
        );
    }


    static_assert(sizeof(DawnHostMappedPointerLimits) == sizeof(WGPUDawnHostMappedPointerLimits), "sizeof mismatch for DawnHostMappedPointerLimits");
    static_assert(alignof(DawnHostMappedPointerLimits) == alignof(WGPUDawnHostMappedPointerLimits), "alignof mismatch for DawnHostMappedPointerLimits");

    static_assert(offsetof(DawnHostMappedPointerLimits, nextInChain) == offsetof(WGPUDawnHostMappedPointerLimits, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnHostMappedPointerLimits::nextInChain");
    static_assert(offsetof(DawnHostMappedPointerLimits, sType) == offsetof(WGPUDawnHostMappedPointerLimits, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnHostMappedPointerLimits::sType");
    static_assert(offsetof(DawnHostMappedPointerLimits, hostMappedPointerAlignment) == offsetof(WGPUDawnHostMappedPointerLimits, hostMappedPointerAlignment),
                 "offsetof mismatch for DawnHostMappedPointerLimits::hostMappedPointerAlignment");

    bool DawnHostMappedPointerLimits::operator==(const DawnHostMappedPointerLimits& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            hostMappedPointerAlignment
        ) == std::tie(
            rhs.hostMappedPointerAlignment
        );
    }


    static_assert(sizeof(DawnInjectedInvalidSType) == sizeof(WGPUDawnInjectedInvalidSType), "sizeof mismatch for DawnInjectedInvalidSType");
    static_assert(alignof(DawnInjectedInvalidSType) == alignof(WGPUDawnInjectedInvalidSType), "alignof mismatch for DawnInjectedInvalidSType");

    static_assert(offsetof(DawnInjectedInvalidSType, nextInChain) == offsetof(WGPUDawnInjectedInvalidSType, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnInjectedInvalidSType::nextInChain");
    static_assert(offsetof(DawnInjectedInvalidSType, sType) == offsetof(WGPUDawnInjectedInvalidSType, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnInjectedInvalidSType::sType");
    static_assert(offsetof(DawnInjectedInvalidSType, invalidSType) == offsetof(WGPUDawnInjectedInvalidSType, invalidSType),
                 "offsetof mismatch for DawnInjectedInvalidSType::invalidSType");

    bool DawnInjectedInvalidSType::operator==(const DawnInjectedInvalidSType& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            invalidSType
        ) == std::tie(
            rhs.invalidSType
        );
    }


    static_assert(sizeof(DawnRenderPassSampleCount) == sizeof(WGPUDawnRenderPassSampleCount), "sizeof mismatch for DawnRenderPassSampleCount");
    static_assert(alignof(DawnRenderPassSampleCount) == alignof(WGPUDawnRenderPassSampleCount), "alignof mismatch for DawnRenderPassSampleCount");

    static_assert(offsetof(DawnRenderPassSampleCount, nextInChain) == offsetof(WGPUDawnRenderPassSampleCount, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnRenderPassSampleCount::nextInChain");
    static_assert(offsetof(DawnRenderPassSampleCount, sType) == offsetof(WGPUDawnRenderPassSampleCount, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnRenderPassSampleCount::sType");
    static_assert(offsetof(DawnRenderPassSampleCount, sampleCount) == offsetof(WGPUDawnRenderPassSampleCount, sampleCount),
                 "offsetof mismatch for DawnRenderPassSampleCount::sampleCount");

    bool DawnRenderPassSampleCount::operator==(const DawnRenderPassSampleCount& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            sampleCount
        ) == std::tie(
            rhs.sampleCount
        );
    }


    static_assert(sizeof(DawnShaderModuleSPIRVOptionsDescriptor) == sizeof(WGPUDawnShaderModuleSPIRVOptionsDescriptor), "sizeof mismatch for DawnShaderModuleSPIRVOptionsDescriptor");
    static_assert(alignof(DawnShaderModuleSPIRVOptionsDescriptor) == alignof(WGPUDawnShaderModuleSPIRVOptionsDescriptor), "alignof mismatch for DawnShaderModuleSPIRVOptionsDescriptor");

    static_assert(offsetof(DawnShaderModuleSPIRVOptionsDescriptor, nextInChain) == offsetof(WGPUDawnShaderModuleSPIRVOptionsDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnShaderModuleSPIRVOptionsDescriptor::nextInChain");
    static_assert(offsetof(DawnShaderModuleSPIRVOptionsDescriptor, sType) == offsetof(WGPUDawnShaderModuleSPIRVOptionsDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnShaderModuleSPIRVOptionsDescriptor::sType");
    static_assert(offsetof(DawnShaderModuleSPIRVOptionsDescriptor, allowNonUniformDerivatives) == offsetof(WGPUDawnShaderModuleSPIRVOptionsDescriptor, allowNonUniformDerivatives),
                 "offsetof mismatch for DawnShaderModuleSPIRVOptionsDescriptor::allowNonUniformDerivatives");

    bool DawnShaderModuleSPIRVOptionsDescriptor::operator==(const DawnShaderModuleSPIRVOptionsDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            allowNonUniformDerivatives
        ) == std::tie(
            rhs.allowNonUniformDerivatives
        );
    }


    static_assert(sizeof(DawnTexelCopyBufferRowAlignmentLimits) == sizeof(WGPUDawnTexelCopyBufferRowAlignmentLimits), "sizeof mismatch for DawnTexelCopyBufferRowAlignmentLimits");
    static_assert(alignof(DawnTexelCopyBufferRowAlignmentLimits) == alignof(WGPUDawnTexelCopyBufferRowAlignmentLimits), "alignof mismatch for DawnTexelCopyBufferRowAlignmentLimits");

    static_assert(offsetof(DawnTexelCopyBufferRowAlignmentLimits, nextInChain) == offsetof(WGPUDawnTexelCopyBufferRowAlignmentLimits, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnTexelCopyBufferRowAlignmentLimits::nextInChain");
    static_assert(offsetof(DawnTexelCopyBufferRowAlignmentLimits, sType) == offsetof(WGPUDawnTexelCopyBufferRowAlignmentLimits, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnTexelCopyBufferRowAlignmentLimits::sType");
    static_assert(offsetof(DawnTexelCopyBufferRowAlignmentLimits, minTexelCopyBufferRowAlignment) == offsetof(WGPUDawnTexelCopyBufferRowAlignmentLimits, minTexelCopyBufferRowAlignment),
                 "offsetof mismatch for DawnTexelCopyBufferRowAlignmentLimits::minTexelCopyBufferRowAlignment");

    bool DawnTexelCopyBufferRowAlignmentLimits::operator==(const DawnTexelCopyBufferRowAlignmentLimits& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            minTexelCopyBufferRowAlignment
        ) == std::tie(
            rhs.minTexelCopyBufferRowAlignment
        );
    }


    static_assert(sizeof(DawnTextureInternalUsageDescriptor) == sizeof(WGPUDawnTextureInternalUsageDescriptor), "sizeof mismatch for DawnTextureInternalUsageDescriptor");
    static_assert(alignof(DawnTextureInternalUsageDescriptor) == alignof(WGPUDawnTextureInternalUsageDescriptor), "alignof mismatch for DawnTextureInternalUsageDescriptor");

    static_assert(offsetof(DawnTextureInternalUsageDescriptor, nextInChain) == offsetof(WGPUDawnTextureInternalUsageDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnTextureInternalUsageDescriptor::nextInChain");
    static_assert(offsetof(DawnTextureInternalUsageDescriptor, sType) == offsetof(WGPUDawnTextureInternalUsageDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnTextureInternalUsageDescriptor::sType");
    static_assert(offsetof(DawnTextureInternalUsageDescriptor, internalUsage) == offsetof(WGPUDawnTextureInternalUsageDescriptor, internalUsage),
                 "offsetof mismatch for DawnTextureInternalUsageDescriptor::internalUsage");

    bool DawnTextureInternalUsageDescriptor::operator==(const DawnTextureInternalUsageDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            internalUsage
        ) == std::tie(
            rhs.internalUsage
        );
    }


    static_assert(sizeof(DawnTogglesDescriptor) == sizeof(WGPUDawnTogglesDescriptor), "sizeof mismatch for DawnTogglesDescriptor");
    static_assert(alignof(DawnTogglesDescriptor) == alignof(WGPUDawnTogglesDescriptor), "alignof mismatch for DawnTogglesDescriptor");

    static_assert(offsetof(DawnTogglesDescriptor, nextInChain) == offsetof(WGPUDawnTogglesDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnTogglesDescriptor::nextInChain");
    static_assert(offsetof(DawnTogglesDescriptor, sType) == offsetof(WGPUDawnTogglesDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnTogglesDescriptor::sType");
    static_assert(offsetof(DawnTogglesDescriptor, enabledToggleCount) == offsetof(WGPUDawnTogglesDescriptor, enabledToggleCount),
                 "offsetof mismatch for DawnTogglesDescriptor::enabledToggleCount");
    static_assert(offsetof(DawnTogglesDescriptor, enabledToggles) == offsetof(WGPUDawnTogglesDescriptor, enabledToggles),
                 "offsetof mismatch for DawnTogglesDescriptor::enabledToggles");
    static_assert(offsetof(DawnTogglesDescriptor, disabledToggleCount) == offsetof(WGPUDawnTogglesDescriptor, disabledToggleCount),
                 "offsetof mismatch for DawnTogglesDescriptor::disabledToggleCount");
    static_assert(offsetof(DawnTogglesDescriptor, disabledToggles) == offsetof(WGPUDawnTogglesDescriptor, disabledToggles),
                 "offsetof mismatch for DawnTogglesDescriptor::disabledToggles");

    bool DawnTogglesDescriptor::operator==(const DawnTogglesDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            enabledToggleCount,
            enabledToggles,
            disabledToggleCount,
            disabledToggles
        ) == std::tie(
            rhs.enabledToggleCount,
            rhs.enabledToggles,
            rhs.disabledToggleCount,
            rhs.disabledToggles
        );
    }


    static_assert(sizeof(DawnWGSLBlocklist) == sizeof(WGPUDawnWGSLBlocklist), "sizeof mismatch for DawnWGSLBlocklist");
    static_assert(alignof(DawnWGSLBlocklist) == alignof(WGPUDawnWGSLBlocklist), "alignof mismatch for DawnWGSLBlocklist");

    static_assert(offsetof(DawnWGSLBlocklist, nextInChain) == offsetof(WGPUDawnWGSLBlocklist, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnWGSLBlocklist::nextInChain");
    static_assert(offsetof(DawnWGSLBlocklist, sType) == offsetof(WGPUDawnWGSLBlocklist, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnWGSLBlocklist::sType");
    static_assert(offsetof(DawnWGSLBlocklist, blocklistedFeatureCount) == offsetof(WGPUDawnWGSLBlocklist, blocklistedFeatureCount),
                 "offsetof mismatch for DawnWGSLBlocklist::blocklistedFeatureCount");
    static_assert(offsetof(DawnWGSLBlocklist, blocklistedFeatures) == offsetof(WGPUDawnWGSLBlocklist, blocklistedFeatures),
                 "offsetof mismatch for DawnWGSLBlocklist::blocklistedFeatures");

    bool DawnWGSLBlocklist::operator==(const DawnWGSLBlocklist& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            blocklistedFeatureCount,
            blocklistedFeatures
        ) == std::tie(
            rhs.blocklistedFeatureCount,
            rhs.blocklistedFeatures
        );
    }


    static_assert(sizeof(DawnWireWGSLControl) == sizeof(WGPUDawnWireWGSLControl), "sizeof mismatch for DawnWireWGSLControl");
    static_assert(alignof(DawnWireWGSLControl) == alignof(WGPUDawnWireWGSLControl), "alignof mismatch for DawnWireWGSLControl");

    static_assert(offsetof(DawnWireWGSLControl, nextInChain) == offsetof(WGPUDawnWireWGSLControl, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnWireWGSLControl::nextInChain");
    static_assert(offsetof(DawnWireWGSLControl, sType) == offsetof(WGPUDawnWireWGSLControl, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnWireWGSLControl::sType");
    static_assert(offsetof(DawnWireWGSLControl, enableExperimental) == offsetof(WGPUDawnWireWGSLControl, enableExperimental),
                 "offsetof mismatch for DawnWireWGSLControl::enableExperimental");
    static_assert(offsetof(DawnWireWGSLControl, enableUnsafe) == offsetof(WGPUDawnWireWGSLControl, enableUnsafe),
                 "offsetof mismatch for DawnWireWGSLControl::enableUnsafe");
    static_assert(offsetof(DawnWireWGSLControl, enableTesting) == offsetof(WGPUDawnWireWGSLControl, enableTesting),
                 "offsetof mismatch for DawnWireWGSLControl::enableTesting");

    bool DawnWireWGSLControl::operator==(const DawnWireWGSLControl& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            enableExperimental,
            enableUnsafe,
            enableTesting
        ) == std::tie(
            rhs.enableExperimental,
            rhs.enableUnsafe,
            rhs.enableTesting
        );
    }


    static_assert(sizeof(Extent2D) == sizeof(WGPUExtent2D), "sizeof mismatch for Extent2D");
    static_assert(alignof(Extent2D) == alignof(WGPUExtent2D), "alignof mismatch for Extent2D");

    static_assert(offsetof(Extent2D, width) == offsetof(WGPUExtent2D, width),
                 "offsetof mismatch for Extent2D::width");
    static_assert(offsetof(Extent2D, height) == offsetof(WGPUExtent2D, height),
                 "offsetof mismatch for Extent2D::height");

    bool Extent2D::operator==(const Extent2D& rhs) const {
        return  std::tie(
            width,
            height
        ) == std::tie(
            rhs.width,
            rhs.height
        );
    }


    static_assert(sizeof(Extent3D) == sizeof(WGPUExtent3D), "sizeof mismatch for Extent3D");
    static_assert(alignof(Extent3D) == alignof(WGPUExtent3D), "alignof mismatch for Extent3D");

    static_assert(offsetof(Extent3D, width) == offsetof(WGPUExtent3D, width),
                 "offsetof mismatch for Extent3D::width");
    static_assert(offsetof(Extent3D, height) == offsetof(WGPUExtent3D, height),
                 "offsetof mismatch for Extent3D::height");
    static_assert(offsetof(Extent3D, depthOrArrayLayers) == offsetof(WGPUExtent3D, depthOrArrayLayers),
                 "offsetof mismatch for Extent3D::depthOrArrayLayers");

    bool Extent3D::operator==(const Extent3D& rhs) const {
        return  std::tie(
            width,
            height,
            depthOrArrayLayers
        ) == std::tie(
            rhs.width,
            rhs.height,
            rhs.depthOrArrayLayers
        );
    }


    static_assert(sizeof(ExternalTextureBindingEntry) == sizeof(WGPUExternalTextureBindingEntry), "sizeof mismatch for ExternalTextureBindingEntry");
    static_assert(alignof(ExternalTextureBindingEntry) == alignof(WGPUExternalTextureBindingEntry), "alignof mismatch for ExternalTextureBindingEntry");

    static_assert(offsetof(ExternalTextureBindingEntry, nextInChain) == offsetof(WGPUExternalTextureBindingEntry, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for ExternalTextureBindingEntry::nextInChain");
    static_assert(offsetof(ExternalTextureBindingEntry, sType) == offsetof(WGPUExternalTextureBindingEntry, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for ExternalTextureBindingEntry::sType");
    static_assert(offsetof(ExternalTextureBindingEntry, externalTexture) == offsetof(WGPUExternalTextureBindingEntry, externalTexture),
                 "offsetof mismatch for ExternalTextureBindingEntry::externalTexture");

    bool ExternalTextureBindingEntry::operator==(const ExternalTextureBindingEntry& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            externalTexture
        ) == std::tie(
            rhs.externalTexture
        );
    }


    static_assert(sizeof(ExternalTextureBindingLayout) == sizeof(WGPUExternalTextureBindingLayout), "sizeof mismatch for ExternalTextureBindingLayout");
    static_assert(alignof(ExternalTextureBindingLayout) == alignof(WGPUExternalTextureBindingLayout), "alignof mismatch for ExternalTextureBindingLayout");

    static_assert(offsetof(ExternalTextureBindingLayout, nextInChain) == offsetof(WGPUExternalTextureBindingLayout, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for ExternalTextureBindingLayout::nextInChain");
    static_assert(offsetof(ExternalTextureBindingLayout, sType) == offsetof(WGPUExternalTextureBindingLayout, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for ExternalTextureBindingLayout::sType");

    bool ExternalTextureBindingLayout::operator==(const ExternalTextureBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
        ) == std::tie(
        );
    }


    static_assert(sizeof(Future) == sizeof(WGPUFuture), "sizeof mismatch for Future");
    static_assert(alignof(Future) == alignof(WGPUFuture), "alignof mismatch for Future");

    static_assert(offsetof(Future, id) == offsetof(WGPUFuture, id),
                 "offsetof mismatch for Future::id");

    bool Future::operator==(const Future& rhs) const {
        return  std::tie(
            id
        ) == std::tie(
            rhs.id
        );
    }


    static_assert(sizeof(InstanceLimits) == sizeof(WGPUInstanceLimits), "sizeof mismatch for InstanceLimits");
    static_assert(alignof(InstanceLimits) == alignof(WGPUInstanceLimits), "alignof mismatch for InstanceLimits");

    static_assert(offsetof(InstanceLimits, nextInChain) == offsetof(WGPUInstanceLimits, nextInChain),
            "offsetof mismatch for InstanceLimits::nextInChain");
    static_assert(offsetof(InstanceLimits, timedWaitAnyMaxCount) == offsetof(WGPUInstanceLimits, timedWaitAnyMaxCount),
                 "offsetof mismatch for InstanceLimits::timedWaitAnyMaxCount");

    bool InstanceLimits::operator==(const InstanceLimits& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            timedWaitAnyMaxCount
        ) == std::tie(
            rhs.timedWaitAnyMaxCount
        );
    }


    static_assert(sizeof(MemoryHeapInfo) == sizeof(WGPUMemoryHeapInfo), "sizeof mismatch for MemoryHeapInfo");
    static_assert(alignof(MemoryHeapInfo) == alignof(WGPUMemoryHeapInfo), "alignof mismatch for MemoryHeapInfo");

    static_assert(offsetof(MemoryHeapInfo, properties) == offsetof(WGPUMemoryHeapInfo, properties),
                 "offsetof mismatch for MemoryHeapInfo::properties");
    static_assert(offsetof(MemoryHeapInfo, size) == offsetof(WGPUMemoryHeapInfo, size),
                 "offsetof mismatch for MemoryHeapInfo::size");

    bool MemoryHeapInfo::operator==(const MemoryHeapInfo& rhs) const {
        return  std::tie(
            properties,
            size
        ) == std::tie(
            rhs.properties,
            rhs.size
        );
    }


    static_assert(sizeof(MultisampleState) == sizeof(WGPUMultisampleState), "sizeof mismatch for MultisampleState");
    static_assert(alignof(MultisampleState) == alignof(WGPUMultisampleState), "alignof mismatch for MultisampleState");

    static_assert(offsetof(MultisampleState, nextInChain) == offsetof(WGPUMultisampleState, nextInChain),
            "offsetof mismatch for MultisampleState::nextInChain");
    static_assert(offsetof(MultisampleState, count) == offsetof(WGPUMultisampleState, count),
                 "offsetof mismatch for MultisampleState::count");
    static_assert(offsetof(MultisampleState, mask) == offsetof(WGPUMultisampleState, mask),
                 "offsetof mismatch for MultisampleState::mask");
    static_assert(offsetof(MultisampleState, alphaToCoverageEnabled) == offsetof(WGPUMultisampleState, alphaToCoverageEnabled),
                 "offsetof mismatch for MultisampleState::alphaToCoverageEnabled");

    bool MultisampleState::operator==(const MultisampleState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            count,
            mask,
            alphaToCoverageEnabled
        ) == std::tie(
            rhs.count,
            rhs.mask,
            rhs.alphaToCoverageEnabled
        );
    }


    static_assert(sizeof(Origin2D) == sizeof(WGPUOrigin2D), "sizeof mismatch for Origin2D");
    static_assert(alignof(Origin2D) == alignof(WGPUOrigin2D), "alignof mismatch for Origin2D");

    static_assert(offsetof(Origin2D, x) == offsetof(WGPUOrigin2D, x),
                 "offsetof mismatch for Origin2D::x");
    static_assert(offsetof(Origin2D, y) == offsetof(WGPUOrigin2D, y),
                 "offsetof mismatch for Origin2D::y");

    bool Origin2D::operator==(const Origin2D& rhs) const {
        return  std::tie(
            x,
            y
        ) == std::tie(
            rhs.x,
            rhs.y
        );
    }


    static_assert(sizeof(Origin3D) == sizeof(WGPUOrigin3D), "sizeof mismatch for Origin3D");
    static_assert(alignof(Origin3D) == alignof(WGPUOrigin3D), "alignof mismatch for Origin3D");

    static_assert(offsetof(Origin3D, x) == offsetof(WGPUOrigin3D, x),
                 "offsetof mismatch for Origin3D::x");
    static_assert(offsetof(Origin3D, y) == offsetof(WGPUOrigin3D, y),
                 "offsetof mismatch for Origin3D::y");
    static_assert(offsetof(Origin3D, z) == offsetof(WGPUOrigin3D, z),
                 "offsetof mismatch for Origin3D::z");

    bool Origin3D::operator==(const Origin3D& rhs) const {
        return  std::tie(
            x,
            y,
            z
        ) == std::tie(
            rhs.x,
            rhs.y,
            rhs.z
        );
    }


    static_assert(sizeof(PassTimestampWrites) == sizeof(WGPUPassTimestampWrites), "sizeof mismatch for PassTimestampWrites");
    static_assert(alignof(PassTimestampWrites) == alignof(WGPUPassTimestampWrites), "alignof mismatch for PassTimestampWrites");

    static_assert(offsetof(PassTimestampWrites, nextInChain) == offsetof(WGPUPassTimestampWrites, nextInChain),
            "offsetof mismatch for PassTimestampWrites::nextInChain");
    static_assert(offsetof(PassTimestampWrites, querySet) == offsetof(WGPUPassTimestampWrites, querySet),
                 "offsetof mismatch for PassTimestampWrites::querySet");
    static_assert(offsetof(PassTimestampWrites, beginningOfPassWriteIndex) == offsetof(WGPUPassTimestampWrites, beginningOfPassWriteIndex),
                 "offsetof mismatch for PassTimestampWrites::beginningOfPassWriteIndex");
    static_assert(offsetof(PassTimestampWrites, endOfPassWriteIndex) == offsetof(WGPUPassTimestampWrites, endOfPassWriteIndex),
                 "offsetof mismatch for PassTimestampWrites::endOfPassWriteIndex");

    bool PassTimestampWrites::operator==(const PassTimestampWrites& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            querySet,
            beginningOfPassWriteIndex,
            endOfPassWriteIndex
        ) == std::tie(
            rhs.querySet,
            rhs.beginningOfPassWriteIndex,
            rhs.endOfPassWriteIndex
        );
    }


    static_assert(sizeof(PipelineLayoutResourceTable) == sizeof(WGPUPipelineLayoutResourceTable), "sizeof mismatch for PipelineLayoutResourceTable");
    static_assert(alignof(PipelineLayoutResourceTable) == alignof(WGPUPipelineLayoutResourceTable), "alignof mismatch for PipelineLayoutResourceTable");

    static_assert(offsetof(PipelineLayoutResourceTable, nextInChain) == offsetof(WGPUPipelineLayoutResourceTable, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for PipelineLayoutResourceTable::nextInChain");
    static_assert(offsetof(PipelineLayoutResourceTable, sType) == offsetof(WGPUPipelineLayoutResourceTable, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for PipelineLayoutResourceTable::sType");
    static_assert(offsetof(PipelineLayoutResourceTable, usesResourceTable) == offsetof(WGPUPipelineLayoutResourceTable, usesResourceTable),
                 "offsetof mismatch for PipelineLayoutResourceTable::usesResourceTable");

    bool PipelineLayoutResourceTable::operator==(const PipelineLayoutResourceTable& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            usesResourceTable
        ) == std::tie(
            rhs.usesResourceTable
        );
    }


    static_assert(sizeof(PipelineLayoutStorageAttachment) == sizeof(WGPUPipelineLayoutStorageAttachment), "sizeof mismatch for PipelineLayoutStorageAttachment");
    static_assert(alignof(PipelineLayoutStorageAttachment) == alignof(WGPUPipelineLayoutStorageAttachment), "alignof mismatch for PipelineLayoutStorageAttachment");

    static_assert(offsetof(PipelineLayoutStorageAttachment, nextInChain) == offsetof(WGPUPipelineLayoutStorageAttachment, nextInChain),
            "offsetof mismatch for PipelineLayoutStorageAttachment::nextInChain");
    static_assert(offsetof(PipelineLayoutStorageAttachment, offset) == offsetof(WGPUPipelineLayoutStorageAttachment, offset),
                 "offsetof mismatch for PipelineLayoutStorageAttachment::offset");
    static_assert(offsetof(PipelineLayoutStorageAttachment, format) == offsetof(WGPUPipelineLayoutStorageAttachment, format),
                 "offsetof mismatch for PipelineLayoutStorageAttachment::format");

    bool PipelineLayoutStorageAttachment::operator==(const PipelineLayoutStorageAttachment& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            offset,
            format
        ) == std::tie(
            rhs.offset,
            rhs.format
        );
    }


    static_assert(sizeof(PrimitiveState) == sizeof(WGPUPrimitiveState), "sizeof mismatch for PrimitiveState");
    static_assert(alignof(PrimitiveState) == alignof(WGPUPrimitiveState), "alignof mismatch for PrimitiveState");

    static_assert(offsetof(PrimitiveState, nextInChain) == offsetof(WGPUPrimitiveState, nextInChain),
            "offsetof mismatch for PrimitiveState::nextInChain");
    static_assert(offsetof(PrimitiveState, topology) == offsetof(WGPUPrimitiveState, topology),
                 "offsetof mismatch for PrimitiveState::topology");
    static_assert(offsetof(PrimitiveState, stripIndexFormat) == offsetof(WGPUPrimitiveState, stripIndexFormat),
                 "offsetof mismatch for PrimitiveState::stripIndexFormat");
    static_assert(offsetof(PrimitiveState, frontFace) == offsetof(WGPUPrimitiveState, frontFace),
                 "offsetof mismatch for PrimitiveState::frontFace");
    static_assert(offsetof(PrimitiveState, cullMode) == offsetof(WGPUPrimitiveState, cullMode),
                 "offsetof mismatch for PrimitiveState::cullMode");
    static_assert(offsetof(PrimitiveState, unclippedDepth) == offsetof(WGPUPrimitiveState, unclippedDepth),
                 "offsetof mismatch for PrimitiveState::unclippedDepth");

    PrimitiveState PrimitiveState::WithTrivialFrontendDefaults() const {
        PrimitiveState copy;
        copy.nextInChain = nextInChain;
        copy.topology = (topology == wgpu::PrimitiveTopology::Undefined)
            ? wgpu::PrimitiveTopology::TriangleList
            : topology;
        copy.stripIndexFormat = stripIndexFormat;
        copy.frontFace = (frontFace == wgpu::FrontFace::Undefined)
            ? wgpu::FrontFace::CCW
            : frontFace;
        copy.cullMode = (cullMode == wgpu::CullMode::Undefined)
            ? wgpu::CullMode::None
            : cullMode;
        copy.unclippedDepth = unclippedDepth;
        return copy;
    }
    bool PrimitiveState::operator==(const PrimitiveState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            topology,
            stripIndexFormat,
            frontFace,
            cullMode,
            unclippedDepth
        ) == std::tie(
            rhs.topology,
            rhs.stripIndexFormat,
            rhs.frontFace,
            rhs.cullMode,
            rhs.unclippedDepth
        );
    }


    static_assert(sizeof(QuerySetDescriptor) == sizeof(WGPUQuerySetDescriptor), "sizeof mismatch for QuerySetDescriptor");
    static_assert(alignof(QuerySetDescriptor) == alignof(WGPUQuerySetDescriptor), "alignof mismatch for QuerySetDescriptor");

    static_assert(offsetof(QuerySetDescriptor, nextInChain) == offsetof(WGPUQuerySetDescriptor, nextInChain),
            "offsetof mismatch for QuerySetDescriptor::nextInChain");
    static_assert(offsetof(QuerySetDescriptor, label) == offsetof(WGPUQuerySetDescriptor, label),
                 "offsetof mismatch for QuerySetDescriptor::label");
    static_assert(offsetof(QuerySetDescriptor, type) == offsetof(WGPUQuerySetDescriptor, type),
                 "offsetof mismatch for QuerySetDescriptor::type");
    static_assert(offsetof(QuerySetDescriptor, count) == offsetof(WGPUQuerySetDescriptor, count),
                 "offsetof mismatch for QuerySetDescriptor::count");

    bool QuerySetDescriptor::operator==(const QuerySetDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            type,
            count
        ) == std::tie(
            rhs.label,
            rhs.type,
            rhs.count
        );
    }


    static_assert(sizeof(QueueDescriptor) == sizeof(WGPUQueueDescriptor), "sizeof mismatch for QueueDescriptor");
    static_assert(alignof(QueueDescriptor) == alignof(WGPUQueueDescriptor), "alignof mismatch for QueueDescriptor");

    static_assert(offsetof(QueueDescriptor, nextInChain) == offsetof(WGPUQueueDescriptor, nextInChain),
            "offsetof mismatch for QueueDescriptor::nextInChain");
    static_assert(offsetof(QueueDescriptor, label) == offsetof(WGPUQueueDescriptor, label),
                 "offsetof mismatch for QueueDescriptor::label");

    bool QueueDescriptor::operator==(const QueueDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(RenderBundleDescriptor) == sizeof(WGPURenderBundleDescriptor), "sizeof mismatch for RenderBundleDescriptor");
    static_assert(alignof(RenderBundleDescriptor) == alignof(WGPURenderBundleDescriptor), "alignof mismatch for RenderBundleDescriptor");

    static_assert(offsetof(RenderBundleDescriptor, nextInChain) == offsetof(WGPURenderBundleDescriptor, nextInChain),
            "offsetof mismatch for RenderBundleDescriptor::nextInChain");
    static_assert(offsetof(RenderBundleDescriptor, label) == offsetof(WGPURenderBundleDescriptor, label),
                 "offsetof mismatch for RenderBundleDescriptor::label");

    bool RenderBundleDescriptor::operator==(const RenderBundleDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(RenderBundleEncoderDescriptor) == sizeof(WGPURenderBundleEncoderDescriptor), "sizeof mismatch for RenderBundleEncoderDescriptor");
    static_assert(alignof(RenderBundleEncoderDescriptor) == alignof(WGPURenderBundleEncoderDescriptor), "alignof mismatch for RenderBundleEncoderDescriptor");

    static_assert(offsetof(RenderBundleEncoderDescriptor, nextInChain) == offsetof(WGPURenderBundleEncoderDescriptor, nextInChain),
            "offsetof mismatch for RenderBundleEncoderDescriptor::nextInChain");
    static_assert(offsetof(RenderBundleEncoderDescriptor, label) == offsetof(WGPURenderBundleEncoderDescriptor, label),
                 "offsetof mismatch for RenderBundleEncoderDescriptor::label");
    static_assert(offsetof(RenderBundleEncoderDescriptor, colorFormatCount) == offsetof(WGPURenderBundleEncoderDescriptor, colorFormatCount),
                 "offsetof mismatch for RenderBundleEncoderDescriptor::colorFormatCount");
    static_assert(offsetof(RenderBundleEncoderDescriptor, colorFormats) == offsetof(WGPURenderBundleEncoderDescriptor, colorFormats),
                 "offsetof mismatch for RenderBundleEncoderDescriptor::colorFormats");
    static_assert(offsetof(RenderBundleEncoderDescriptor, depthStencilFormat) == offsetof(WGPURenderBundleEncoderDescriptor, depthStencilFormat),
                 "offsetof mismatch for RenderBundleEncoderDescriptor::depthStencilFormat");
    static_assert(offsetof(RenderBundleEncoderDescriptor, sampleCount) == offsetof(WGPURenderBundleEncoderDescriptor, sampleCount),
                 "offsetof mismatch for RenderBundleEncoderDescriptor::sampleCount");
    static_assert(offsetof(RenderBundleEncoderDescriptor, depthReadOnly) == offsetof(WGPURenderBundleEncoderDescriptor, depthReadOnly),
                 "offsetof mismatch for RenderBundleEncoderDescriptor::depthReadOnly");
    static_assert(offsetof(RenderBundleEncoderDescriptor, stencilReadOnly) == offsetof(WGPURenderBundleEncoderDescriptor, stencilReadOnly),
                 "offsetof mismatch for RenderBundleEncoderDescriptor::stencilReadOnly");

    bool RenderBundleEncoderDescriptor::operator==(const RenderBundleEncoderDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            colorFormatCount,
            colorFormats,
            depthStencilFormat,
            sampleCount,
            depthReadOnly,
            stencilReadOnly
        ) == std::tie(
            rhs.label,
            rhs.colorFormatCount,
            rhs.colorFormats,
            rhs.depthStencilFormat,
            rhs.sampleCount,
            rhs.depthReadOnly,
            rhs.stencilReadOnly
        );
    }


    static_assert(sizeof(RenderPassDepthStencilAttachment) == sizeof(WGPURenderPassDepthStencilAttachment), "sizeof mismatch for RenderPassDepthStencilAttachment");
    static_assert(alignof(RenderPassDepthStencilAttachment) == alignof(WGPURenderPassDepthStencilAttachment), "alignof mismatch for RenderPassDepthStencilAttachment");

    static_assert(offsetof(RenderPassDepthStencilAttachment, nextInChain) == offsetof(WGPURenderPassDepthStencilAttachment, nextInChain),
            "offsetof mismatch for RenderPassDepthStencilAttachment::nextInChain");
    static_assert(offsetof(RenderPassDepthStencilAttachment, view) == offsetof(WGPURenderPassDepthStencilAttachment, view),
                 "offsetof mismatch for RenderPassDepthStencilAttachment::view");
    static_assert(offsetof(RenderPassDepthStencilAttachment, depthLoadOp) == offsetof(WGPURenderPassDepthStencilAttachment, depthLoadOp),
                 "offsetof mismatch for RenderPassDepthStencilAttachment::depthLoadOp");
    static_assert(offsetof(RenderPassDepthStencilAttachment, depthStoreOp) == offsetof(WGPURenderPassDepthStencilAttachment, depthStoreOp),
                 "offsetof mismatch for RenderPassDepthStencilAttachment::depthStoreOp");
    static_assert(offsetof(RenderPassDepthStencilAttachment, depthClearValue) == offsetof(WGPURenderPassDepthStencilAttachment, depthClearValue),
                 "offsetof mismatch for RenderPassDepthStencilAttachment::depthClearValue");
    static_assert(offsetof(RenderPassDepthStencilAttachment, depthReadOnly) == offsetof(WGPURenderPassDepthStencilAttachment, depthReadOnly),
                 "offsetof mismatch for RenderPassDepthStencilAttachment::depthReadOnly");
    static_assert(offsetof(RenderPassDepthStencilAttachment, stencilLoadOp) == offsetof(WGPURenderPassDepthStencilAttachment, stencilLoadOp),
                 "offsetof mismatch for RenderPassDepthStencilAttachment::stencilLoadOp");
    static_assert(offsetof(RenderPassDepthStencilAttachment, stencilStoreOp) == offsetof(WGPURenderPassDepthStencilAttachment, stencilStoreOp),
                 "offsetof mismatch for RenderPassDepthStencilAttachment::stencilStoreOp");
    static_assert(offsetof(RenderPassDepthStencilAttachment, stencilClearValue) == offsetof(WGPURenderPassDepthStencilAttachment, stencilClearValue),
                 "offsetof mismatch for RenderPassDepthStencilAttachment::stencilClearValue");
    static_assert(offsetof(RenderPassDepthStencilAttachment, stencilReadOnly) == offsetof(WGPURenderPassDepthStencilAttachment, stencilReadOnly),
                 "offsetof mismatch for RenderPassDepthStencilAttachment::stencilReadOnly");

    bool RenderPassDepthStencilAttachment::operator==(const RenderPassDepthStencilAttachment& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            view,
            depthLoadOp,
            depthStoreOp,
            depthClearValue,
            depthReadOnly,
            stencilLoadOp,
            stencilStoreOp,
            stencilClearValue,
            stencilReadOnly
        ) == std::tie(
            rhs.view,
            rhs.depthLoadOp,
            rhs.depthStoreOp,
            rhs.depthClearValue,
            rhs.depthReadOnly,
            rhs.stencilLoadOp,
            rhs.stencilStoreOp,
            rhs.stencilClearValue,
            rhs.stencilReadOnly
        );
    }


    static_assert(sizeof(RenderPassDescriptorExpandResolveRect) == sizeof(WGPURenderPassDescriptorExpandResolveRect), "sizeof mismatch for RenderPassDescriptorExpandResolveRect");
    static_assert(alignof(RenderPassDescriptorExpandResolveRect) == alignof(WGPURenderPassDescriptorExpandResolveRect), "alignof mismatch for RenderPassDescriptorExpandResolveRect");

    static_assert(offsetof(RenderPassDescriptorExpandResolveRect, nextInChain) == offsetof(WGPURenderPassDescriptorExpandResolveRect, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for RenderPassDescriptorExpandResolveRect::nextInChain");
    static_assert(offsetof(RenderPassDescriptorExpandResolveRect, sType) == offsetof(WGPURenderPassDescriptorExpandResolveRect, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for RenderPassDescriptorExpandResolveRect::sType");
    static_assert(offsetof(RenderPassDescriptorExpandResolveRect, x) == offsetof(WGPURenderPassDescriptorExpandResolveRect, x),
                 "offsetof mismatch for RenderPassDescriptorExpandResolveRect::x");
    static_assert(offsetof(RenderPassDescriptorExpandResolveRect, y) == offsetof(WGPURenderPassDescriptorExpandResolveRect, y),
                 "offsetof mismatch for RenderPassDescriptorExpandResolveRect::y");
    static_assert(offsetof(RenderPassDescriptorExpandResolveRect, width) == offsetof(WGPURenderPassDescriptorExpandResolveRect, width),
                 "offsetof mismatch for RenderPassDescriptorExpandResolveRect::width");
    static_assert(offsetof(RenderPassDescriptorExpandResolveRect, height) == offsetof(WGPURenderPassDescriptorExpandResolveRect, height),
                 "offsetof mismatch for RenderPassDescriptorExpandResolveRect::height");

    bool RenderPassDescriptorExpandResolveRect::operator==(const RenderPassDescriptorExpandResolveRect& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            x,
            y,
            width,
            height
        ) == std::tie(
            rhs.x,
            rhs.y,
            rhs.width,
            rhs.height
        );
    }


    static_assert(sizeof(RenderPassDescriptorResolveRect) == sizeof(WGPURenderPassDescriptorResolveRect), "sizeof mismatch for RenderPassDescriptorResolveRect");
    static_assert(alignof(RenderPassDescriptorResolveRect) == alignof(WGPURenderPassDescriptorResolveRect), "alignof mismatch for RenderPassDescriptorResolveRect");

    static_assert(offsetof(RenderPassDescriptorResolveRect, nextInChain) == offsetof(WGPURenderPassDescriptorResolveRect, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for RenderPassDescriptorResolveRect::nextInChain");
    static_assert(offsetof(RenderPassDescriptorResolveRect, sType) == offsetof(WGPURenderPassDescriptorResolveRect, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for RenderPassDescriptorResolveRect::sType");
    static_assert(offsetof(RenderPassDescriptorResolveRect, colorOffsetX) == offsetof(WGPURenderPassDescriptorResolveRect, colorOffsetX),
                 "offsetof mismatch for RenderPassDescriptorResolveRect::colorOffsetX");
    static_assert(offsetof(RenderPassDescriptorResolveRect, colorOffsetY) == offsetof(WGPURenderPassDescriptorResolveRect, colorOffsetY),
                 "offsetof mismatch for RenderPassDescriptorResolveRect::colorOffsetY");
    static_assert(offsetof(RenderPassDescriptorResolveRect, resolveOffsetX) == offsetof(WGPURenderPassDescriptorResolveRect, resolveOffsetX),
                 "offsetof mismatch for RenderPassDescriptorResolveRect::resolveOffsetX");
    static_assert(offsetof(RenderPassDescriptorResolveRect, resolveOffsetY) == offsetof(WGPURenderPassDescriptorResolveRect, resolveOffsetY),
                 "offsetof mismatch for RenderPassDescriptorResolveRect::resolveOffsetY");
    static_assert(offsetof(RenderPassDescriptorResolveRect, width) == offsetof(WGPURenderPassDescriptorResolveRect, width),
                 "offsetof mismatch for RenderPassDescriptorResolveRect::width");
    static_assert(offsetof(RenderPassDescriptorResolveRect, height) == offsetof(WGPURenderPassDescriptorResolveRect, height),
                 "offsetof mismatch for RenderPassDescriptorResolveRect::height");

    bool RenderPassDescriptorResolveRect::operator==(const RenderPassDescriptorResolveRect& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            colorOffsetX,
            colorOffsetY,
            resolveOffsetX,
            resolveOffsetY,
            width,
            height
        ) == std::tie(
            rhs.colorOffsetX,
            rhs.colorOffsetY,
            rhs.resolveOffsetX,
            rhs.resolveOffsetY,
            rhs.width,
            rhs.height
        );
    }


    static_assert(sizeof(RenderPassMaxDrawCount) == sizeof(WGPURenderPassMaxDrawCount), "sizeof mismatch for RenderPassMaxDrawCount");
    static_assert(alignof(RenderPassMaxDrawCount) == alignof(WGPURenderPassMaxDrawCount), "alignof mismatch for RenderPassMaxDrawCount");

    static_assert(offsetof(RenderPassMaxDrawCount, nextInChain) == offsetof(WGPURenderPassMaxDrawCount, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for RenderPassMaxDrawCount::nextInChain");
    static_assert(offsetof(RenderPassMaxDrawCount, sType) == offsetof(WGPURenderPassMaxDrawCount, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for RenderPassMaxDrawCount::sType");
    static_assert(offsetof(RenderPassMaxDrawCount, maxDrawCount) == offsetof(WGPURenderPassMaxDrawCount, maxDrawCount),
                 "offsetof mismatch for RenderPassMaxDrawCount::maxDrawCount");

    bool RenderPassMaxDrawCount::operator==(const RenderPassMaxDrawCount& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            maxDrawCount
        ) == std::tie(
            rhs.maxDrawCount
        );
    }


    static_assert(sizeof(RequestAdapterWebGPUBackendOptions) == sizeof(WGPURequestAdapterWebGPUBackendOptions), "sizeof mismatch for RequestAdapterWebGPUBackendOptions");
    static_assert(alignof(RequestAdapterWebGPUBackendOptions) == alignof(WGPURequestAdapterWebGPUBackendOptions), "alignof mismatch for RequestAdapterWebGPUBackendOptions");

    static_assert(offsetof(RequestAdapterWebGPUBackendOptions, nextInChain) == offsetof(WGPURequestAdapterWebGPUBackendOptions, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for RequestAdapterWebGPUBackendOptions::nextInChain");
    static_assert(offsetof(RequestAdapterWebGPUBackendOptions, sType) == offsetof(WGPURequestAdapterWebGPUBackendOptions, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for RequestAdapterWebGPUBackendOptions::sType");

    bool RequestAdapterWebGPUBackendOptions::operator==(const RequestAdapterWebGPUBackendOptions& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
        ) == std::tie(
        );
    }


    static_assert(sizeof(RequestAdapterWebXROptions) == sizeof(WGPURequestAdapterWebXROptions), "sizeof mismatch for RequestAdapterWebXROptions");
    static_assert(alignof(RequestAdapterWebXROptions) == alignof(WGPURequestAdapterWebXROptions), "alignof mismatch for RequestAdapterWebXROptions");

    static_assert(offsetof(RequestAdapterWebXROptions, nextInChain) == offsetof(WGPURequestAdapterWebXROptions, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for RequestAdapterWebXROptions::nextInChain");
    static_assert(offsetof(RequestAdapterWebXROptions, sType) == offsetof(WGPURequestAdapterWebXROptions, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for RequestAdapterWebXROptions::sType");
    static_assert(offsetof(RequestAdapterWebXROptions, xrCompatible) == offsetof(WGPURequestAdapterWebXROptions, xrCompatible),
                 "offsetof mismatch for RequestAdapterWebXROptions::xrCompatible");

    bool RequestAdapterWebXROptions::operator==(const RequestAdapterWebXROptions& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            xrCompatible
        ) == std::tie(
            rhs.xrCompatible
        );
    }


    static_assert(sizeof(ResourceTableDescriptor) == sizeof(WGPUResourceTableDescriptor), "sizeof mismatch for ResourceTableDescriptor");
    static_assert(alignof(ResourceTableDescriptor) == alignof(WGPUResourceTableDescriptor), "alignof mismatch for ResourceTableDescriptor");

    static_assert(offsetof(ResourceTableDescriptor, nextInChain) == offsetof(WGPUResourceTableDescriptor, nextInChain),
            "offsetof mismatch for ResourceTableDescriptor::nextInChain");
    static_assert(offsetof(ResourceTableDescriptor, label) == offsetof(WGPUResourceTableDescriptor, label),
                 "offsetof mismatch for ResourceTableDescriptor::label");
    static_assert(offsetof(ResourceTableDescriptor, size) == offsetof(WGPUResourceTableDescriptor, size),
                 "offsetof mismatch for ResourceTableDescriptor::size");

    bool ResourceTableDescriptor::operator==(const ResourceTableDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            size
        ) == std::tie(
            rhs.label,
            rhs.size
        );
    }


    static_assert(sizeof(SamplerBindingLayout) == sizeof(WGPUSamplerBindingLayout), "sizeof mismatch for SamplerBindingLayout");
    static_assert(alignof(SamplerBindingLayout) == alignof(WGPUSamplerBindingLayout), "alignof mismatch for SamplerBindingLayout");

    static_assert(offsetof(SamplerBindingLayout, nextInChain) == offsetof(WGPUSamplerBindingLayout, nextInChain),
            "offsetof mismatch for SamplerBindingLayout::nextInChain");
    static_assert(offsetof(SamplerBindingLayout, type) == offsetof(WGPUSamplerBindingLayout, type),
                 "offsetof mismatch for SamplerBindingLayout::type");

    SamplerBindingLayout SamplerBindingLayout::WithTrivialFrontendDefaults() const {
        SamplerBindingLayout copy;
        copy.nextInChain = nextInChain;
        copy.type = (type == wgpu::SamplerBindingType::Undefined)
            ? wgpu::SamplerBindingType::Filtering
            : type;
        return copy;
    }
    bool SamplerBindingLayout::operator==(const SamplerBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            type
        ) == std::tie(
            rhs.type
        );
    }


    static_assert(sizeof(ShaderModuleCompilationOptions) == sizeof(WGPUShaderModuleCompilationOptions), "sizeof mismatch for ShaderModuleCompilationOptions");
    static_assert(alignof(ShaderModuleCompilationOptions) == alignof(WGPUShaderModuleCompilationOptions), "alignof mismatch for ShaderModuleCompilationOptions");

    static_assert(offsetof(ShaderModuleCompilationOptions, nextInChain) == offsetof(WGPUShaderModuleCompilationOptions, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for ShaderModuleCompilationOptions::nextInChain");
    static_assert(offsetof(ShaderModuleCompilationOptions, sType) == offsetof(WGPUShaderModuleCompilationOptions, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for ShaderModuleCompilationOptions::sType");
    static_assert(offsetof(ShaderModuleCompilationOptions, strictMath) == offsetof(WGPUShaderModuleCompilationOptions, strictMath),
                 "offsetof mismatch for ShaderModuleCompilationOptions::strictMath");

    bool ShaderModuleCompilationOptions::operator==(const ShaderModuleCompilationOptions& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            strictMath
        ) == std::tie(
            rhs.strictMath
        );
    }


    static_assert(sizeof(ShaderSourceSPIRV) == sizeof(WGPUShaderSourceSPIRV), "sizeof mismatch for ShaderSourceSPIRV");
    static_assert(alignof(ShaderSourceSPIRV) == alignof(WGPUShaderSourceSPIRV), "alignof mismatch for ShaderSourceSPIRV");

    static_assert(offsetof(ShaderSourceSPIRV, nextInChain) == offsetof(WGPUShaderSourceSPIRV, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for ShaderSourceSPIRV::nextInChain");
    static_assert(offsetof(ShaderSourceSPIRV, sType) == offsetof(WGPUShaderSourceSPIRV, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for ShaderSourceSPIRV::sType");
    static_assert(offsetof(ShaderSourceSPIRV, codeSize) == offsetof(WGPUShaderSourceSPIRV, codeSize),
                 "offsetof mismatch for ShaderSourceSPIRV::codeSize");
    static_assert(offsetof(ShaderSourceSPIRV, code) == offsetof(WGPUShaderSourceSPIRV, code),
                 "offsetof mismatch for ShaderSourceSPIRV::code");

    bool ShaderSourceSPIRV::operator==(const ShaderSourceSPIRV& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            codeSize,
            code
        ) == std::tie(
            rhs.codeSize,
            rhs.code
        );
    }


    static_assert(sizeof(ShaderSourceWGSL) == sizeof(WGPUShaderSourceWGSL), "sizeof mismatch for ShaderSourceWGSL");
    static_assert(alignof(ShaderSourceWGSL) == alignof(WGPUShaderSourceWGSL), "alignof mismatch for ShaderSourceWGSL");

    static_assert(offsetof(ShaderSourceWGSL, nextInChain) == offsetof(WGPUShaderSourceWGSL, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for ShaderSourceWGSL::nextInChain");
    static_assert(offsetof(ShaderSourceWGSL, sType) == offsetof(WGPUShaderSourceWGSL, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for ShaderSourceWGSL::sType");
    static_assert(offsetof(ShaderSourceWGSL, code) == offsetof(WGPUShaderSourceWGSL, code),
                 "offsetof mismatch for ShaderSourceWGSL::code");

    bool ShaderSourceWGSL::operator==(const ShaderSourceWGSL& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            code
        ) == std::tie(
            rhs.code
        );
    }


    static_assert(sizeof(SharedBufferMemoryBeginAccessDescriptor) == sizeof(WGPUSharedBufferMemoryBeginAccessDescriptor), "sizeof mismatch for SharedBufferMemoryBeginAccessDescriptor");
    static_assert(alignof(SharedBufferMemoryBeginAccessDescriptor) == alignof(WGPUSharedBufferMemoryBeginAccessDescriptor), "alignof mismatch for SharedBufferMemoryBeginAccessDescriptor");

    static_assert(offsetof(SharedBufferMemoryBeginAccessDescriptor, nextInChain) == offsetof(WGPUSharedBufferMemoryBeginAccessDescriptor, nextInChain),
            "offsetof mismatch for SharedBufferMemoryBeginAccessDescriptor::nextInChain");
    static_assert(offsetof(SharedBufferMemoryBeginAccessDescriptor, initialized) == offsetof(WGPUSharedBufferMemoryBeginAccessDescriptor, initialized),
                 "offsetof mismatch for SharedBufferMemoryBeginAccessDescriptor::initialized");
    static_assert(offsetof(SharedBufferMemoryBeginAccessDescriptor, fenceCount) == offsetof(WGPUSharedBufferMemoryBeginAccessDescriptor, fenceCount),
                 "offsetof mismatch for SharedBufferMemoryBeginAccessDescriptor::fenceCount");
    static_assert(offsetof(SharedBufferMemoryBeginAccessDescriptor, fences) == offsetof(WGPUSharedBufferMemoryBeginAccessDescriptor, fences),
                 "offsetof mismatch for SharedBufferMemoryBeginAccessDescriptor::fences");
    static_assert(offsetof(SharedBufferMemoryBeginAccessDescriptor, signaledValues) == offsetof(WGPUSharedBufferMemoryBeginAccessDescriptor, signaledValues),
                 "offsetof mismatch for SharedBufferMemoryBeginAccessDescriptor::signaledValues");

    bool SharedBufferMemoryBeginAccessDescriptor::operator==(const SharedBufferMemoryBeginAccessDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            initialized,
            fenceCount,
            fences,
            signaledValues
        ) == std::tie(
            rhs.initialized,
            rhs.fenceCount,
            rhs.fences,
            rhs.signaledValues
        );
    }


    static_assert(sizeof(SharedBufferMemoryDescriptor) == sizeof(WGPUSharedBufferMemoryDescriptor), "sizeof mismatch for SharedBufferMemoryDescriptor");
    static_assert(alignof(SharedBufferMemoryDescriptor) == alignof(WGPUSharedBufferMemoryDescriptor), "alignof mismatch for SharedBufferMemoryDescriptor");

    static_assert(offsetof(SharedBufferMemoryDescriptor, nextInChain) == offsetof(WGPUSharedBufferMemoryDescriptor, nextInChain),
            "offsetof mismatch for SharedBufferMemoryDescriptor::nextInChain");
    static_assert(offsetof(SharedBufferMemoryDescriptor, label) == offsetof(WGPUSharedBufferMemoryDescriptor, label),
                 "offsetof mismatch for SharedBufferMemoryDescriptor::label");

    bool SharedBufferMemoryDescriptor::operator==(const SharedBufferMemoryDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(SharedBufferMemoryEndAccessState) == sizeof(WGPUSharedBufferMemoryEndAccessState), "sizeof mismatch for SharedBufferMemoryEndAccessState");
    static_assert(alignof(SharedBufferMemoryEndAccessState) == alignof(WGPUSharedBufferMemoryEndAccessState), "alignof mismatch for SharedBufferMemoryEndAccessState");

    static_assert(offsetof(SharedBufferMemoryEndAccessState, nextInChain) == offsetof(WGPUSharedBufferMemoryEndAccessState, nextInChain),
            "offsetof mismatch for SharedBufferMemoryEndAccessState::nextInChain");
    static_assert(offsetof(SharedBufferMemoryEndAccessState, initialized) == offsetof(WGPUSharedBufferMemoryEndAccessState, initialized),
                 "offsetof mismatch for SharedBufferMemoryEndAccessState::initialized");
    static_assert(offsetof(SharedBufferMemoryEndAccessState, fenceCount) == offsetof(WGPUSharedBufferMemoryEndAccessState, fenceCount),
                 "offsetof mismatch for SharedBufferMemoryEndAccessState::fenceCount");
    static_assert(offsetof(SharedBufferMemoryEndAccessState, fences) == offsetof(WGPUSharedBufferMemoryEndAccessState, fences),
                 "offsetof mismatch for SharedBufferMemoryEndAccessState::fences");
    static_assert(offsetof(SharedBufferMemoryEndAccessState, signaledValues) == offsetof(WGPUSharedBufferMemoryEndAccessState, signaledValues),
                 "offsetof mismatch for SharedBufferMemoryEndAccessState::signaledValues");

    bool SharedBufferMemoryEndAccessState::operator==(const SharedBufferMemoryEndAccessState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            initialized,
            fenceCount,
            fences,
            signaledValues
        ) == std::tie(
            rhs.initialized,
            rhs.fenceCount,
            rhs.fences,
            rhs.signaledValues
        );
    }


    static_assert(sizeof(SharedBufferMemoryProperties) == sizeof(WGPUSharedBufferMemoryProperties), "sizeof mismatch for SharedBufferMemoryProperties");
    static_assert(alignof(SharedBufferMemoryProperties) == alignof(WGPUSharedBufferMemoryProperties), "alignof mismatch for SharedBufferMemoryProperties");

    static_assert(offsetof(SharedBufferMemoryProperties, nextInChain) == offsetof(WGPUSharedBufferMemoryProperties, nextInChain),
            "offsetof mismatch for SharedBufferMemoryProperties::nextInChain");
    static_assert(offsetof(SharedBufferMemoryProperties, usage) == offsetof(WGPUSharedBufferMemoryProperties, usage),
                 "offsetof mismatch for SharedBufferMemoryProperties::usage");
    static_assert(offsetof(SharedBufferMemoryProperties, size) == offsetof(WGPUSharedBufferMemoryProperties, size),
                 "offsetof mismatch for SharedBufferMemoryProperties::size");

    bool SharedBufferMemoryProperties::operator==(const SharedBufferMemoryProperties& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            usage,
            size
        ) == std::tie(
            rhs.usage,
            rhs.size
        );
    }


    static_assert(sizeof(SharedFenceDXGISharedHandleDescriptor) == sizeof(WGPUSharedFenceDXGISharedHandleDescriptor), "sizeof mismatch for SharedFenceDXGISharedHandleDescriptor");
    static_assert(alignof(SharedFenceDXGISharedHandleDescriptor) == alignof(WGPUSharedFenceDXGISharedHandleDescriptor), "alignof mismatch for SharedFenceDXGISharedHandleDescriptor");

    static_assert(offsetof(SharedFenceDXGISharedHandleDescriptor, nextInChain) == offsetof(WGPUSharedFenceDXGISharedHandleDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceDXGISharedHandleDescriptor::nextInChain");
    static_assert(offsetof(SharedFenceDXGISharedHandleDescriptor, sType) == offsetof(WGPUSharedFenceDXGISharedHandleDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceDXGISharedHandleDescriptor::sType");
    static_assert(offsetof(SharedFenceDXGISharedHandleDescriptor, handle) == offsetof(WGPUSharedFenceDXGISharedHandleDescriptor, handle),
                 "offsetof mismatch for SharedFenceDXGISharedHandleDescriptor::handle");

    bool SharedFenceDXGISharedHandleDescriptor::operator==(const SharedFenceDXGISharedHandleDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            handle
        ) == std::tie(
            rhs.handle
        );
    }


    static_assert(sizeof(SharedFenceDXGISharedHandleExportInfo) == sizeof(WGPUSharedFenceDXGISharedHandleExportInfo), "sizeof mismatch for SharedFenceDXGISharedHandleExportInfo");
    static_assert(alignof(SharedFenceDXGISharedHandleExportInfo) == alignof(WGPUSharedFenceDXGISharedHandleExportInfo), "alignof mismatch for SharedFenceDXGISharedHandleExportInfo");

    static_assert(offsetof(SharedFenceDXGISharedHandleExportInfo, nextInChain) == offsetof(WGPUSharedFenceDXGISharedHandleExportInfo, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceDXGISharedHandleExportInfo::nextInChain");
    static_assert(offsetof(SharedFenceDXGISharedHandleExportInfo, sType) == offsetof(WGPUSharedFenceDXGISharedHandleExportInfo, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceDXGISharedHandleExportInfo::sType");
    static_assert(offsetof(SharedFenceDXGISharedHandleExportInfo, handle) == offsetof(WGPUSharedFenceDXGISharedHandleExportInfo, handle),
                 "offsetof mismatch for SharedFenceDXGISharedHandleExportInfo::handle");

    bool SharedFenceDXGISharedHandleExportInfo::operator==(const SharedFenceDXGISharedHandleExportInfo& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            handle
        ) == std::tie(
            rhs.handle
        );
    }


    static_assert(sizeof(SharedFenceEGLSyncDescriptor) == sizeof(WGPUSharedFenceEGLSyncDescriptor), "sizeof mismatch for SharedFenceEGLSyncDescriptor");
    static_assert(alignof(SharedFenceEGLSyncDescriptor) == alignof(WGPUSharedFenceEGLSyncDescriptor), "alignof mismatch for SharedFenceEGLSyncDescriptor");

    static_assert(offsetof(SharedFenceEGLSyncDescriptor, nextInChain) == offsetof(WGPUSharedFenceEGLSyncDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceEGLSyncDescriptor::nextInChain");
    static_assert(offsetof(SharedFenceEGLSyncDescriptor, sType) == offsetof(WGPUSharedFenceEGLSyncDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceEGLSyncDescriptor::sType");
    static_assert(offsetof(SharedFenceEGLSyncDescriptor, sync) == offsetof(WGPUSharedFenceEGLSyncDescriptor, sync),
                 "offsetof mismatch for SharedFenceEGLSyncDescriptor::sync");

    bool SharedFenceEGLSyncDescriptor::operator==(const SharedFenceEGLSyncDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            sync
        ) == std::tie(
            rhs.sync
        );
    }


    static_assert(sizeof(SharedFenceEGLSyncExportInfo) == sizeof(WGPUSharedFenceEGLSyncExportInfo), "sizeof mismatch for SharedFenceEGLSyncExportInfo");
    static_assert(alignof(SharedFenceEGLSyncExportInfo) == alignof(WGPUSharedFenceEGLSyncExportInfo), "alignof mismatch for SharedFenceEGLSyncExportInfo");

    static_assert(offsetof(SharedFenceEGLSyncExportInfo, nextInChain) == offsetof(WGPUSharedFenceEGLSyncExportInfo, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceEGLSyncExportInfo::nextInChain");
    static_assert(offsetof(SharedFenceEGLSyncExportInfo, sType) == offsetof(WGPUSharedFenceEGLSyncExportInfo, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceEGLSyncExportInfo::sType");
    static_assert(offsetof(SharedFenceEGLSyncExportInfo, sync) == offsetof(WGPUSharedFenceEGLSyncExportInfo, sync),
                 "offsetof mismatch for SharedFenceEGLSyncExportInfo::sync");

    bool SharedFenceEGLSyncExportInfo::operator==(const SharedFenceEGLSyncExportInfo& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            sync
        ) == std::tie(
            rhs.sync
        );
    }


    static_assert(sizeof(SharedFenceMTLSharedEventDescriptor) == sizeof(WGPUSharedFenceMTLSharedEventDescriptor), "sizeof mismatch for SharedFenceMTLSharedEventDescriptor");
    static_assert(alignof(SharedFenceMTLSharedEventDescriptor) == alignof(WGPUSharedFenceMTLSharedEventDescriptor), "alignof mismatch for SharedFenceMTLSharedEventDescriptor");

    static_assert(offsetof(SharedFenceMTLSharedEventDescriptor, nextInChain) == offsetof(WGPUSharedFenceMTLSharedEventDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceMTLSharedEventDescriptor::nextInChain");
    static_assert(offsetof(SharedFenceMTLSharedEventDescriptor, sType) == offsetof(WGPUSharedFenceMTLSharedEventDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceMTLSharedEventDescriptor::sType");
    static_assert(offsetof(SharedFenceMTLSharedEventDescriptor, sharedEvent) == offsetof(WGPUSharedFenceMTLSharedEventDescriptor, sharedEvent),
                 "offsetof mismatch for SharedFenceMTLSharedEventDescriptor::sharedEvent");

    bool SharedFenceMTLSharedEventDescriptor::operator==(const SharedFenceMTLSharedEventDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            sharedEvent
        ) == std::tie(
            rhs.sharedEvent
        );
    }


    static_assert(sizeof(SharedFenceMTLSharedEventExportInfo) == sizeof(WGPUSharedFenceMTLSharedEventExportInfo), "sizeof mismatch for SharedFenceMTLSharedEventExportInfo");
    static_assert(alignof(SharedFenceMTLSharedEventExportInfo) == alignof(WGPUSharedFenceMTLSharedEventExportInfo), "alignof mismatch for SharedFenceMTLSharedEventExportInfo");

    static_assert(offsetof(SharedFenceMTLSharedEventExportInfo, nextInChain) == offsetof(WGPUSharedFenceMTLSharedEventExportInfo, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceMTLSharedEventExportInfo::nextInChain");
    static_assert(offsetof(SharedFenceMTLSharedEventExportInfo, sType) == offsetof(WGPUSharedFenceMTLSharedEventExportInfo, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceMTLSharedEventExportInfo::sType");
    static_assert(offsetof(SharedFenceMTLSharedEventExportInfo, sharedEvent) == offsetof(WGPUSharedFenceMTLSharedEventExportInfo, sharedEvent),
                 "offsetof mismatch for SharedFenceMTLSharedEventExportInfo::sharedEvent");

    bool SharedFenceMTLSharedEventExportInfo::operator==(const SharedFenceMTLSharedEventExportInfo& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            sharedEvent
        ) == std::tie(
            rhs.sharedEvent
        );
    }


    static_assert(sizeof(SharedFenceSyncFDDescriptor) == sizeof(WGPUSharedFenceSyncFDDescriptor), "sizeof mismatch for SharedFenceSyncFDDescriptor");
    static_assert(alignof(SharedFenceSyncFDDescriptor) == alignof(WGPUSharedFenceSyncFDDescriptor), "alignof mismatch for SharedFenceSyncFDDescriptor");

    static_assert(offsetof(SharedFenceSyncFDDescriptor, nextInChain) == offsetof(WGPUSharedFenceSyncFDDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceSyncFDDescriptor::nextInChain");
    static_assert(offsetof(SharedFenceSyncFDDescriptor, sType) == offsetof(WGPUSharedFenceSyncFDDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceSyncFDDescriptor::sType");
    static_assert(offsetof(SharedFenceSyncFDDescriptor, handle) == offsetof(WGPUSharedFenceSyncFDDescriptor, handle),
                 "offsetof mismatch for SharedFenceSyncFDDescriptor::handle");

    bool SharedFenceSyncFDDescriptor::operator==(const SharedFenceSyncFDDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            handle
        ) == std::tie(
            rhs.handle
        );
    }


    static_assert(sizeof(SharedFenceSyncFDExportInfo) == sizeof(WGPUSharedFenceSyncFDExportInfo), "sizeof mismatch for SharedFenceSyncFDExportInfo");
    static_assert(alignof(SharedFenceSyncFDExportInfo) == alignof(WGPUSharedFenceSyncFDExportInfo), "alignof mismatch for SharedFenceSyncFDExportInfo");

    static_assert(offsetof(SharedFenceSyncFDExportInfo, nextInChain) == offsetof(WGPUSharedFenceSyncFDExportInfo, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceSyncFDExportInfo::nextInChain");
    static_assert(offsetof(SharedFenceSyncFDExportInfo, sType) == offsetof(WGPUSharedFenceSyncFDExportInfo, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceSyncFDExportInfo::sType");
    static_assert(offsetof(SharedFenceSyncFDExportInfo, handle) == offsetof(WGPUSharedFenceSyncFDExportInfo, handle),
                 "offsetof mismatch for SharedFenceSyncFDExportInfo::handle");

    bool SharedFenceSyncFDExportInfo::operator==(const SharedFenceSyncFDExportInfo& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            handle
        ) == std::tie(
            rhs.handle
        );
    }


    static_assert(sizeof(SharedFenceVkSemaphoreOpaqueFDDescriptor) == sizeof(WGPUSharedFenceVkSemaphoreOpaqueFDDescriptor), "sizeof mismatch for SharedFenceVkSemaphoreOpaqueFDDescriptor");
    static_assert(alignof(SharedFenceVkSemaphoreOpaqueFDDescriptor) == alignof(WGPUSharedFenceVkSemaphoreOpaqueFDDescriptor), "alignof mismatch for SharedFenceVkSemaphoreOpaqueFDDescriptor");

    static_assert(offsetof(SharedFenceVkSemaphoreOpaqueFDDescriptor, nextInChain) == offsetof(WGPUSharedFenceVkSemaphoreOpaqueFDDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceVkSemaphoreOpaqueFDDescriptor::nextInChain");
    static_assert(offsetof(SharedFenceVkSemaphoreOpaqueFDDescriptor, sType) == offsetof(WGPUSharedFenceVkSemaphoreOpaqueFDDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceVkSemaphoreOpaqueFDDescriptor::sType");
    static_assert(offsetof(SharedFenceVkSemaphoreOpaqueFDDescriptor, handle) == offsetof(WGPUSharedFenceVkSemaphoreOpaqueFDDescriptor, handle),
                 "offsetof mismatch for SharedFenceVkSemaphoreOpaqueFDDescriptor::handle");

    bool SharedFenceVkSemaphoreOpaqueFDDescriptor::operator==(const SharedFenceVkSemaphoreOpaqueFDDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            handle
        ) == std::tie(
            rhs.handle
        );
    }


    static_assert(sizeof(SharedFenceVkSemaphoreOpaqueFDExportInfo) == sizeof(WGPUSharedFenceVkSemaphoreOpaqueFDExportInfo), "sizeof mismatch for SharedFenceVkSemaphoreOpaqueFDExportInfo");
    static_assert(alignof(SharedFenceVkSemaphoreOpaqueFDExportInfo) == alignof(WGPUSharedFenceVkSemaphoreOpaqueFDExportInfo), "alignof mismatch for SharedFenceVkSemaphoreOpaqueFDExportInfo");

    static_assert(offsetof(SharedFenceVkSemaphoreOpaqueFDExportInfo, nextInChain) == offsetof(WGPUSharedFenceVkSemaphoreOpaqueFDExportInfo, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceVkSemaphoreOpaqueFDExportInfo::nextInChain");
    static_assert(offsetof(SharedFenceVkSemaphoreOpaqueFDExportInfo, sType) == offsetof(WGPUSharedFenceVkSemaphoreOpaqueFDExportInfo, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceVkSemaphoreOpaqueFDExportInfo::sType");
    static_assert(offsetof(SharedFenceVkSemaphoreOpaqueFDExportInfo, handle) == offsetof(WGPUSharedFenceVkSemaphoreOpaqueFDExportInfo, handle),
                 "offsetof mismatch for SharedFenceVkSemaphoreOpaqueFDExportInfo::handle");

    bool SharedFenceVkSemaphoreOpaqueFDExportInfo::operator==(const SharedFenceVkSemaphoreOpaqueFDExportInfo& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            handle
        ) == std::tie(
            rhs.handle
        );
    }


    static_assert(sizeof(SharedFenceVkSemaphoreZirconHandleDescriptor) == sizeof(WGPUSharedFenceVkSemaphoreZirconHandleDescriptor), "sizeof mismatch for SharedFenceVkSemaphoreZirconHandleDescriptor");
    static_assert(alignof(SharedFenceVkSemaphoreZirconHandleDescriptor) == alignof(WGPUSharedFenceVkSemaphoreZirconHandleDescriptor), "alignof mismatch for SharedFenceVkSemaphoreZirconHandleDescriptor");

    static_assert(offsetof(SharedFenceVkSemaphoreZirconHandleDescriptor, nextInChain) == offsetof(WGPUSharedFenceVkSemaphoreZirconHandleDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceVkSemaphoreZirconHandleDescriptor::nextInChain");
    static_assert(offsetof(SharedFenceVkSemaphoreZirconHandleDescriptor, sType) == offsetof(WGPUSharedFenceVkSemaphoreZirconHandleDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceVkSemaphoreZirconHandleDescriptor::sType");
    static_assert(offsetof(SharedFenceVkSemaphoreZirconHandleDescriptor, handle) == offsetof(WGPUSharedFenceVkSemaphoreZirconHandleDescriptor, handle),
                 "offsetof mismatch for SharedFenceVkSemaphoreZirconHandleDescriptor::handle");

    bool SharedFenceVkSemaphoreZirconHandleDescriptor::operator==(const SharedFenceVkSemaphoreZirconHandleDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            handle
        ) == std::tie(
            rhs.handle
        );
    }


    static_assert(sizeof(SharedFenceVkSemaphoreZirconHandleExportInfo) == sizeof(WGPUSharedFenceVkSemaphoreZirconHandleExportInfo), "sizeof mismatch for SharedFenceVkSemaphoreZirconHandleExportInfo");
    static_assert(alignof(SharedFenceVkSemaphoreZirconHandleExportInfo) == alignof(WGPUSharedFenceVkSemaphoreZirconHandleExportInfo), "alignof mismatch for SharedFenceVkSemaphoreZirconHandleExportInfo");

    static_assert(offsetof(SharedFenceVkSemaphoreZirconHandleExportInfo, nextInChain) == offsetof(WGPUSharedFenceVkSemaphoreZirconHandleExportInfo, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedFenceVkSemaphoreZirconHandleExportInfo::nextInChain");
    static_assert(offsetof(SharedFenceVkSemaphoreZirconHandleExportInfo, sType) == offsetof(WGPUSharedFenceVkSemaphoreZirconHandleExportInfo, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedFenceVkSemaphoreZirconHandleExportInfo::sType");
    static_assert(offsetof(SharedFenceVkSemaphoreZirconHandleExportInfo, handle) == offsetof(WGPUSharedFenceVkSemaphoreZirconHandleExportInfo, handle),
                 "offsetof mismatch for SharedFenceVkSemaphoreZirconHandleExportInfo::handle");

    bool SharedFenceVkSemaphoreZirconHandleExportInfo::operator==(const SharedFenceVkSemaphoreZirconHandleExportInfo& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            handle
        ) == std::tie(
            rhs.handle
        );
    }


    static_assert(sizeof(SharedTextureMemoryAHardwareBufferDescriptor) == sizeof(WGPUSharedTextureMemoryAHardwareBufferDescriptor), "sizeof mismatch for SharedTextureMemoryAHardwareBufferDescriptor");
    static_assert(alignof(SharedTextureMemoryAHardwareBufferDescriptor) == alignof(WGPUSharedTextureMemoryAHardwareBufferDescriptor), "alignof mismatch for SharedTextureMemoryAHardwareBufferDescriptor");

    static_assert(offsetof(SharedTextureMemoryAHardwareBufferDescriptor, nextInChain) == offsetof(WGPUSharedTextureMemoryAHardwareBufferDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryAHardwareBufferDescriptor::nextInChain");
    static_assert(offsetof(SharedTextureMemoryAHardwareBufferDescriptor, sType) == offsetof(WGPUSharedTextureMemoryAHardwareBufferDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryAHardwareBufferDescriptor::sType");
    static_assert(offsetof(SharedTextureMemoryAHardwareBufferDescriptor, handle) == offsetof(WGPUSharedTextureMemoryAHardwareBufferDescriptor, handle),
                 "offsetof mismatch for SharedTextureMemoryAHardwareBufferDescriptor::handle");

    bool SharedTextureMemoryAHardwareBufferDescriptor::operator==(const SharedTextureMemoryAHardwareBufferDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            handle
        ) == std::tie(
            rhs.handle
        );
    }


    static_assert(sizeof(SharedTextureMemoryD3D11BeginState) == sizeof(WGPUSharedTextureMemoryD3D11BeginState), "sizeof mismatch for SharedTextureMemoryD3D11BeginState");
    static_assert(alignof(SharedTextureMemoryD3D11BeginState) == alignof(WGPUSharedTextureMemoryD3D11BeginState), "alignof mismatch for SharedTextureMemoryD3D11BeginState");

    static_assert(offsetof(SharedTextureMemoryD3D11BeginState, nextInChain) == offsetof(WGPUSharedTextureMemoryD3D11BeginState, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryD3D11BeginState::nextInChain");
    static_assert(offsetof(SharedTextureMemoryD3D11BeginState, sType) == offsetof(WGPUSharedTextureMemoryD3D11BeginState, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryD3D11BeginState::sType");
    static_assert(offsetof(SharedTextureMemoryD3D11BeginState, requiresEndAccessFence) == offsetof(WGPUSharedTextureMemoryD3D11BeginState, requiresEndAccessFence),
                 "offsetof mismatch for SharedTextureMemoryD3D11BeginState::requiresEndAccessFence");

    bool SharedTextureMemoryD3D11BeginState::operator==(const SharedTextureMemoryD3D11BeginState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            requiresEndAccessFence
        ) == std::tie(
            rhs.requiresEndAccessFence
        );
    }


    static_assert(sizeof(SharedTextureMemoryD3DSwapchainBeginState) == sizeof(WGPUSharedTextureMemoryD3DSwapchainBeginState), "sizeof mismatch for SharedTextureMemoryD3DSwapchainBeginState");
    static_assert(alignof(SharedTextureMemoryD3DSwapchainBeginState) == alignof(WGPUSharedTextureMemoryD3DSwapchainBeginState), "alignof mismatch for SharedTextureMemoryD3DSwapchainBeginState");

    static_assert(offsetof(SharedTextureMemoryD3DSwapchainBeginState, nextInChain) == offsetof(WGPUSharedTextureMemoryD3DSwapchainBeginState, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryD3DSwapchainBeginState::nextInChain");
    static_assert(offsetof(SharedTextureMemoryD3DSwapchainBeginState, sType) == offsetof(WGPUSharedTextureMemoryD3DSwapchainBeginState, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryD3DSwapchainBeginState::sType");
    static_assert(offsetof(SharedTextureMemoryD3DSwapchainBeginState, isSwapchain) == offsetof(WGPUSharedTextureMemoryD3DSwapchainBeginState, isSwapchain),
                 "offsetof mismatch for SharedTextureMemoryD3DSwapchainBeginState::isSwapchain");

    bool SharedTextureMemoryD3DSwapchainBeginState::operator==(const SharedTextureMemoryD3DSwapchainBeginState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            isSwapchain
        ) == std::tie(
            rhs.isSwapchain
        );
    }


    static_assert(sizeof(SharedTextureMemoryDmaBufPlane) == sizeof(WGPUSharedTextureMemoryDmaBufPlane), "sizeof mismatch for SharedTextureMemoryDmaBufPlane");
    static_assert(alignof(SharedTextureMemoryDmaBufPlane) == alignof(WGPUSharedTextureMemoryDmaBufPlane), "alignof mismatch for SharedTextureMemoryDmaBufPlane");

    static_assert(offsetof(SharedTextureMemoryDmaBufPlane, fd) == offsetof(WGPUSharedTextureMemoryDmaBufPlane, fd),
                 "offsetof mismatch for SharedTextureMemoryDmaBufPlane::fd");
    static_assert(offsetof(SharedTextureMemoryDmaBufPlane, offset) == offsetof(WGPUSharedTextureMemoryDmaBufPlane, offset),
                 "offsetof mismatch for SharedTextureMemoryDmaBufPlane::offset");
    static_assert(offsetof(SharedTextureMemoryDmaBufPlane, stride) == offsetof(WGPUSharedTextureMemoryDmaBufPlane, stride),
                 "offsetof mismatch for SharedTextureMemoryDmaBufPlane::stride");

    bool SharedTextureMemoryDmaBufPlane::operator==(const SharedTextureMemoryDmaBufPlane& rhs) const {
        return  std::tie(
            fd,
            offset,
            stride
        ) == std::tie(
            rhs.fd,
            rhs.offset,
            rhs.stride
        );
    }


    static_assert(sizeof(SharedTextureMemoryDXGISharedHandleDescriptor) == sizeof(WGPUSharedTextureMemoryDXGISharedHandleDescriptor), "sizeof mismatch for SharedTextureMemoryDXGISharedHandleDescriptor");
    static_assert(alignof(SharedTextureMemoryDXGISharedHandleDescriptor) == alignof(WGPUSharedTextureMemoryDXGISharedHandleDescriptor), "alignof mismatch for SharedTextureMemoryDXGISharedHandleDescriptor");

    static_assert(offsetof(SharedTextureMemoryDXGISharedHandleDescriptor, nextInChain) == offsetof(WGPUSharedTextureMemoryDXGISharedHandleDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryDXGISharedHandleDescriptor::nextInChain");
    static_assert(offsetof(SharedTextureMemoryDXGISharedHandleDescriptor, sType) == offsetof(WGPUSharedTextureMemoryDXGISharedHandleDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryDXGISharedHandleDescriptor::sType");
    static_assert(offsetof(SharedTextureMemoryDXGISharedHandleDescriptor, handle) == offsetof(WGPUSharedTextureMemoryDXGISharedHandleDescriptor, handle),
                 "offsetof mismatch for SharedTextureMemoryDXGISharedHandleDescriptor::handle");
    static_assert(offsetof(SharedTextureMemoryDXGISharedHandleDescriptor, useKeyedMutex) == offsetof(WGPUSharedTextureMemoryDXGISharedHandleDescriptor, useKeyedMutex),
                 "offsetof mismatch for SharedTextureMemoryDXGISharedHandleDescriptor::useKeyedMutex");

    bool SharedTextureMemoryDXGISharedHandleDescriptor::operator==(const SharedTextureMemoryDXGISharedHandleDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            handle,
            useKeyedMutex
        ) == std::tie(
            rhs.handle,
            rhs.useKeyedMutex
        );
    }


    static_assert(sizeof(SharedTextureMemoryEGLImageDescriptor) == sizeof(WGPUSharedTextureMemoryEGLImageDescriptor), "sizeof mismatch for SharedTextureMemoryEGLImageDescriptor");
    static_assert(alignof(SharedTextureMemoryEGLImageDescriptor) == alignof(WGPUSharedTextureMemoryEGLImageDescriptor), "alignof mismatch for SharedTextureMemoryEGLImageDescriptor");

    static_assert(offsetof(SharedTextureMemoryEGLImageDescriptor, nextInChain) == offsetof(WGPUSharedTextureMemoryEGLImageDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryEGLImageDescriptor::nextInChain");
    static_assert(offsetof(SharedTextureMemoryEGLImageDescriptor, sType) == offsetof(WGPUSharedTextureMemoryEGLImageDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryEGLImageDescriptor::sType");
    static_assert(offsetof(SharedTextureMemoryEGLImageDescriptor, image) == offsetof(WGPUSharedTextureMemoryEGLImageDescriptor, image),
                 "offsetof mismatch for SharedTextureMemoryEGLImageDescriptor::image");

    bool SharedTextureMemoryEGLImageDescriptor::operator==(const SharedTextureMemoryEGLImageDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            image
        ) == std::tie(
            rhs.image
        );
    }


    static_assert(sizeof(SharedTextureMemoryIOSurfaceDescriptor) == sizeof(WGPUSharedTextureMemoryIOSurfaceDescriptor), "sizeof mismatch for SharedTextureMemoryIOSurfaceDescriptor");
    static_assert(alignof(SharedTextureMemoryIOSurfaceDescriptor) == alignof(WGPUSharedTextureMemoryIOSurfaceDescriptor), "alignof mismatch for SharedTextureMemoryIOSurfaceDescriptor");

    static_assert(offsetof(SharedTextureMemoryIOSurfaceDescriptor, nextInChain) == offsetof(WGPUSharedTextureMemoryIOSurfaceDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryIOSurfaceDescriptor::nextInChain");
    static_assert(offsetof(SharedTextureMemoryIOSurfaceDescriptor, sType) == offsetof(WGPUSharedTextureMemoryIOSurfaceDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryIOSurfaceDescriptor::sType");
    static_assert(offsetof(SharedTextureMemoryIOSurfaceDescriptor, ioSurface) == offsetof(WGPUSharedTextureMemoryIOSurfaceDescriptor, ioSurface),
                 "offsetof mismatch for SharedTextureMemoryIOSurfaceDescriptor::ioSurface");
    static_assert(offsetof(SharedTextureMemoryIOSurfaceDescriptor, allowStorageBinding) == offsetof(WGPUSharedTextureMemoryIOSurfaceDescriptor, allowStorageBinding),
                 "offsetof mismatch for SharedTextureMemoryIOSurfaceDescriptor::allowStorageBinding");

    bool SharedTextureMemoryIOSurfaceDescriptor::operator==(const SharedTextureMemoryIOSurfaceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            ioSurface,
            allowStorageBinding
        ) == std::tie(
            rhs.ioSurface,
            rhs.allowStorageBinding
        );
    }


    static_assert(sizeof(SharedTextureMemoryOpaqueFDDescriptor) == sizeof(WGPUSharedTextureMemoryOpaqueFDDescriptor), "sizeof mismatch for SharedTextureMemoryOpaqueFDDescriptor");
    static_assert(alignof(SharedTextureMemoryOpaqueFDDescriptor) == alignof(WGPUSharedTextureMemoryOpaqueFDDescriptor), "alignof mismatch for SharedTextureMemoryOpaqueFDDescriptor");

    static_assert(offsetof(SharedTextureMemoryOpaqueFDDescriptor, nextInChain) == offsetof(WGPUSharedTextureMemoryOpaqueFDDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryOpaqueFDDescriptor::nextInChain");
    static_assert(offsetof(SharedTextureMemoryOpaqueFDDescriptor, sType) == offsetof(WGPUSharedTextureMemoryOpaqueFDDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryOpaqueFDDescriptor::sType");
    static_assert(offsetof(SharedTextureMemoryOpaqueFDDescriptor, vkImageCreateInfo) == offsetof(WGPUSharedTextureMemoryOpaqueFDDescriptor, vkImageCreateInfo),
                 "offsetof mismatch for SharedTextureMemoryOpaqueFDDescriptor::vkImageCreateInfo");
    static_assert(offsetof(SharedTextureMemoryOpaqueFDDescriptor, memoryFD) == offsetof(WGPUSharedTextureMemoryOpaqueFDDescriptor, memoryFD),
                 "offsetof mismatch for SharedTextureMemoryOpaqueFDDescriptor::memoryFD");
    static_assert(offsetof(SharedTextureMemoryOpaqueFDDescriptor, memoryTypeIndex) == offsetof(WGPUSharedTextureMemoryOpaqueFDDescriptor, memoryTypeIndex),
                 "offsetof mismatch for SharedTextureMemoryOpaqueFDDescriptor::memoryTypeIndex");
    static_assert(offsetof(SharedTextureMemoryOpaqueFDDescriptor, allocationSize) == offsetof(WGPUSharedTextureMemoryOpaqueFDDescriptor, allocationSize),
                 "offsetof mismatch for SharedTextureMemoryOpaqueFDDescriptor::allocationSize");
    static_assert(offsetof(SharedTextureMemoryOpaqueFDDescriptor, dedicatedAllocation) == offsetof(WGPUSharedTextureMemoryOpaqueFDDescriptor, dedicatedAllocation),
                 "offsetof mismatch for SharedTextureMemoryOpaqueFDDescriptor::dedicatedAllocation");

    bool SharedTextureMemoryOpaqueFDDescriptor::operator==(const SharedTextureMemoryOpaqueFDDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            vkImageCreateInfo,
            memoryFD,
            memoryTypeIndex,
            allocationSize,
            dedicatedAllocation
        ) == std::tie(
            rhs.vkImageCreateInfo,
            rhs.memoryFD,
            rhs.memoryTypeIndex,
            rhs.allocationSize,
            rhs.dedicatedAllocation
        );
    }


    static_assert(sizeof(SharedTextureMemoryVkDedicatedAllocationDescriptor) == sizeof(WGPUSharedTextureMemoryVkDedicatedAllocationDescriptor), "sizeof mismatch for SharedTextureMemoryVkDedicatedAllocationDescriptor");
    static_assert(alignof(SharedTextureMemoryVkDedicatedAllocationDescriptor) == alignof(WGPUSharedTextureMemoryVkDedicatedAllocationDescriptor), "alignof mismatch for SharedTextureMemoryVkDedicatedAllocationDescriptor");

    static_assert(offsetof(SharedTextureMemoryVkDedicatedAllocationDescriptor, nextInChain) == offsetof(WGPUSharedTextureMemoryVkDedicatedAllocationDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryVkDedicatedAllocationDescriptor::nextInChain");
    static_assert(offsetof(SharedTextureMemoryVkDedicatedAllocationDescriptor, sType) == offsetof(WGPUSharedTextureMemoryVkDedicatedAllocationDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryVkDedicatedAllocationDescriptor::sType");
    static_assert(offsetof(SharedTextureMemoryVkDedicatedAllocationDescriptor, dedicatedAllocation) == offsetof(WGPUSharedTextureMemoryVkDedicatedAllocationDescriptor, dedicatedAllocation),
                 "offsetof mismatch for SharedTextureMemoryVkDedicatedAllocationDescriptor::dedicatedAllocation");

    bool SharedTextureMemoryVkDedicatedAllocationDescriptor::operator==(const SharedTextureMemoryVkDedicatedAllocationDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            dedicatedAllocation
        ) == std::tie(
            rhs.dedicatedAllocation
        );
    }


    static_assert(sizeof(SharedTextureMemoryVkImageLayoutBeginState) == sizeof(WGPUSharedTextureMemoryVkImageLayoutBeginState), "sizeof mismatch for SharedTextureMemoryVkImageLayoutBeginState");
    static_assert(alignof(SharedTextureMemoryVkImageLayoutBeginState) == alignof(WGPUSharedTextureMemoryVkImageLayoutBeginState), "alignof mismatch for SharedTextureMemoryVkImageLayoutBeginState");

    static_assert(offsetof(SharedTextureMemoryVkImageLayoutBeginState, nextInChain) == offsetof(WGPUSharedTextureMemoryVkImageLayoutBeginState, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryVkImageLayoutBeginState::nextInChain");
    static_assert(offsetof(SharedTextureMemoryVkImageLayoutBeginState, sType) == offsetof(WGPUSharedTextureMemoryVkImageLayoutBeginState, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryVkImageLayoutBeginState::sType");
    static_assert(offsetof(SharedTextureMemoryVkImageLayoutBeginState, oldLayout) == offsetof(WGPUSharedTextureMemoryVkImageLayoutBeginState, oldLayout),
                 "offsetof mismatch for SharedTextureMemoryVkImageLayoutBeginState::oldLayout");
    static_assert(offsetof(SharedTextureMemoryVkImageLayoutBeginState, newLayout) == offsetof(WGPUSharedTextureMemoryVkImageLayoutBeginState, newLayout),
                 "offsetof mismatch for SharedTextureMemoryVkImageLayoutBeginState::newLayout");

    bool SharedTextureMemoryVkImageLayoutBeginState::operator==(const SharedTextureMemoryVkImageLayoutBeginState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            oldLayout,
            newLayout
        ) == std::tie(
            rhs.oldLayout,
            rhs.newLayout
        );
    }


    static_assert(sizeof(SharedTextureMemoryVkImageLayoutEndState) == sizeof(WGPUSharedTextureMemoryVkImageLayoutEndState), "sizeof mismatch for SharedTextureMemoryVkImageLayoutEndState");
    static_assert(alignof(SharedTextureMemoryVkImageLayoutEndState) == alignof(WGPUSharedTextureMemoryVkImageLayoutEndState), "alignof mismatch for SharedTextureMemoryVkImageLayoutEndState");

    static_assert(offsetof(SharedTextureMemoryVkImageLayoutEndState, nextInChain) == offsetof(WGPUSharedTextureMemoryVkImageLayoutEndState, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryVkImageLayoutEndState::nextInChain");
    static_assert(offsetof(SharedTextureMemoryVkImageLayoutEndState, sType) == offsetof(WGPUSharedTextureMemoryVkImageLayoutEndState, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryVkImageLayoutEndState::sType");
    static_assert(offsetof(SharedTextureMemoryVkImageLayoutEndState, oldLayout) == offsetof(WGPUSharedTextureMemoryVkImageLayoutEndState, oldLayout),
                 "offsetof mismatch for SharedTextureMemoryVkImageLayoutEndState::oldLayout");
    static_assert(offsetof(SharedTextureMemoryVkImageLayoutEndState, newLayout) == offsetof(WGPUSharedTextureMemoryVkImageLayoutEndState, newLayout),
                 "offsetof mismatch for SharedTextureMemoryVkImageLayoutEndState::newLayout");

    bool SharedTextureMemoryVkImageLayoutEndState::operator==(const SharedTextureMemoryVkImageLayoutEndState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            oldLayout,
            newLayout
        ) == std::tie(
            rhs.oldLayout,
            rhs.newLayout
        );
    }


    static_assert(sizeof(SharedTextureMemoryZirconHandleDescriptor) == sizeof(WGPUSharedTextureMemoryZirconHandleDescriptor), "sizeof mismatch for SharedTextureMemoryZirconHandleDescriptor");
    static_assert(alignof(SharedTextureMemoryZirconHandleDescriptor) == alignof(WGPUSharedTextureMemoryZirconHandleDescriptor), "alignof mismatch for SharedTextureMemoryZirconHandleDescriptor");

    static_assert(offsetof(SharedTextureMemoryZirconHandleDescriptor, nextInChain) == offsetof(WGPUSharedTextureMemoryZirconHandleDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryZirconHandleDescriptor::nextInChain");
    static_assert(offsetof(SharedTextureMemoryZirconHandleDescriptor, sType) == offsetof(WGPUSharedTextureMemoryZirconHandleDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryZirconHandleDescriptor::sType");
    static_assert(offsetof(SharedTextureMemoryZirconHandleDescriptor, memoryFD) == offsetof(WGPUSharedTextureMemoryZirconHandleDescriptor, memoryFD),
                 "offsetof mismatch for SharedTextureMemoryZirconHandleDescriptor::memoryFD");
    static_assert(offsetof(SharedTextureMemoryZirconHandleDescriptor, allocationSize) == offsetof(WGPUSharedTextureMemoryZirconHandleDescriptor, allocationSize),
                 "offsetof mismatch for SharedTextureMemoryZirconHandleDescriptor::allocationSize");

    bool SharedTextureMemoryZirconHandleDescriptor::operator==(const SharedTextureMemoryZirconHandleDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            memoryFD,
            allocationSize
        ) == std::tie(
            rhs.memoryFD,
            rhs.allocationSize
        );
    }


    static_assert(sizeof(StaticSamplerBindingLayout) == sizeof(WGPUStaticSamplerBindingLayout), "sizeof mismatch for StaticSamplerBindingLayout");
    static_assert(alignof(StaticSamplerBindingLayout) == alignof(WGPUStaticSamplerBindingLayout), "alignof mismatch for StaticSamplerBindingLayout");

    static_assert(offsetof(StaticSamplerBindingLayout, nextInChain) == offsetof(WGPUStaticSamplerBindingLayout, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for StaticSamplerBindingLayout::nextInChain");
    static_assert(offsetof(StaticSamplerBindingLayout, sType) == offsetof(WGPUStaticSamplerBindingLayout, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for StaticSamplerBindingLayout::sType");
    static_assert(offsetof(StaticSamplerBindingLayout, sampler) == offsetof(WGPUStaticSamplerBindingLayout, sampler),
                 "offsetof mismatch for StaticSamplerBindingLayout::sampler");
    static_assert(offsetof(StaticSamplerBindingLayout, sampledTextureBinding) == offsetof(WGPUStaticSamplerBindingLayout, sampledTextureBinding),
                 "offsetof mismatch for StaticSamplerBindingLayout::sampledTextureBinding");

    bool StaticSamplerBindingLayout::operator==(const StaticSamplerBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            sampler,
            sampledTextureBinding
        ) == std::tie(
            rhs.sampler,
            rhs.sampledTextureBinding
        );
    }


    static_assert(sizeof(StencilFaceState) == sizeof(WGPUStencilFaceState), "sizeof mismatch for StencilFaceState");
    static_assert(alignof(StencilFaceState) == alignof(WGPUStencilFaceState), "alignof mismatch for StencilFaceState");

    static_assert(offsetof(StencilFaceState, compare) == offsetof(WGPUStencilFaceState, compare),
                 "offsetof mismatch for StencilFaceState::compare");
    static_assert(offsetof(StencilFaceState, failOp) == offsetof(WGPUStencilFaceState, failOp),
                 "offsetof mismatch for StencilFaceState::failOp");
    static_assert(offsetof(StencilFaceState, depthFailOp) == offsetof(WGPUStencilFaceState, depthFailOp),
                 "offsetof mismatch for StencilFaceState::depthFailOp");
    static_assert(offsetof(StencilFaceState, passOp) == offsetof(WGPUStencilFaceState, passOp),
                 "offsetof mismatch for StencilFaceState::passOp");

    StencilFaceState StencilFaceState::WithTrivialFrontendDefaults() const {
        StencilFaceState copy;
        copy.compare = (compare == wgpu::CompareFunction::Undefined)
            ? wgpu::CompareFunction::Always
            : compare;
        copy.failOp = (failOp == wgpu::StencilOperation::Undefined)
            ? wgpu::StencilOperation::Keep
            : failOp;
        copy.depthFailOp = (depthFailOp == wgpu::StencilOperation::Undefined)
            ? wgpu::StencilOperation::Keep
            : depthFailOp;
        copy.passOp = (passOp == wgpu::StencilOperation::Undefined)
            ? wgpu::StencilOperation::Keep
            : passOp;
        return copy;
    }
    bool StencilFaceState::operator==(const StencilFaceState& rhs) const {
        return  std::tie(
            compare,
            failOp,
            depthFailOp,
            passOp
        ) == std::tie(
            rhs.compare,
            rhs.failOp,
            rhs.depthFailOp,
            rhs.passOp
        );
    }


    static_assert(sizeof(StorageTextureBindingLayout) == sizeof(WGPUStorageTextureBindingLayout), "sizeof mismatch for StorageTextureBindingLayout");
    static_assert(alignof(StorageTextureBindingLayout) == alignof(WGPUStorageTextureBindingLayout), "alignof mismatch for StorageTextureBindingLayout");

    static_assert(offsetof(StorageTextureBindingLayout, nextInChain) == offsetof(WGPUStorageTextureBindingLayout, nextInChain),
            "offsetof mismatch for StorageTextureBindingLayout::nextInChain");
    static_assert(offsetof(StorageTextureBindingLayout, access) == offsetof(WGPUStorageTextureBindingLayout, access),
                 "offsetof mismatch for StorageTextureBindingLayout::access");
    static_assert(offsetof(StorageTextureBindingLayout, format) == offsetof(WGPUStorageTextureBindingLayout, format),
                 "offsetof mismatch for StorageTextureBindingLayout::format");
    static_assert(offsetof(StorageTextureBindingLayout, viewDimension) == offsetof(WGPUStorageTextureBindingLayout, viewDimension),
                 "offsetof mismatch for StorageTextureBindingLayout::viewDimension");

    StorageTextureBindingLayout StorageTextureBindingLayout::WithTrivialFrontendDefaults() const {
        StorageTextureBindingLayout copy;
        copy.nextInChain = nextInChain;
        copy.access = (access == wgpu::StorageTextureAccess::Undefined)
            ? wgpu::StorageTextureAccess::WriteOnly
            : access;
        copy.format = format;
        copy.viewDimension = (viewDimension == wgpu::TextureViewDimension::Undefined)
            ? wgpu::TextureViewDimension::e2D
            : viewDimension;
        return copy;
    }
    bool StorageTextureBindingLayout::operator==(const StorageTextureBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            access,
            format,
            viewDimension
        ) == std::tie(
            rhs.access,
            rhs.format,
            rhs.viewDimension
        );
    }


    static_assert(sizeof(SubgroupMatrixConfig) == sizeof(WGPUSubgroupMatrixConfig), "sizeof mismatch for SubgroupMatrixConfig");
    static_assert(alignof(SubgroupMatrixConfig) == alignof(WGPUSubgroupMatrixConfig), "alignof mismatch for SubgroupMatrixConfig");

    static_assert(offsetof(SubgroupMatrixConfig, componentType) == offsetof(WGPUSubgroupMatrixConfig, componentType),
                 "offsetof mismatch for SubgroupMatrixConfig::componentType");
    static_assert(offsetof(SubgroupMatrixConfig, resultComponentType) == offsetof(WGPUSubgroupMatrixConfig, resultComponentType),
                 "offsetof mismatch for SubgroupMatrixConfig::resultComponentType");
    static_assert(offsetof(SubgroupMatrixConfig, M) == offsetof(WGPUSubgroupMatrixConfig, M),
                 "offsetof mismatch for SubgroupMatrixConfig::M");
    static_assert(offsetof(SubgroupMatrixConfig, N) == offsetof(WGPUSubgroupMatrixConfig, N),
                 "offsetof mismatch for SubgroupMatrixConfig::N");
    static_assert(offsetof(SubgroupMatrixConfig, K) == offsetof(WGPUSubgroupMatrixConfig, K),
                 "offsetof mismatch for SubgroupMatrixConfig::K");

    bool SubgroupMatrixConfig::operator==(const SubgroupMatrixConfig& rhs) const {
        return  std::tie(
            componentType,
            resultComponentType,
            M,
            N,
            K
        ) == std::tie(
            rhs.componentType,
            rhs.resultComponentType,
            rhs.M,
            rhs.N,
            rhs.K
        );
    }


    static_assert(sizeof(SupportedFeatures) == sizeof(WGPUSupportedFeatures), "sizeof mismatch for SupportedFeatures");
    static_assert(alignof(SupportedFeatures) == alignof(WGPUSupportedFeatures), "alignof mismatch for SupportedFeatures");

    static_assert(offsetof(SupportedFeatures, featureCount) == offsetof(WGPUSupportedFeatures, featureCount),
                 "offsetof mismatch for SupportedFeatures::featureCount");
    static_assert(offsetof(SupportedFeatures, features) == offsetof(WGPUSupportedFeatures, features),
                 "offsetof mismatch for SupportedFeatures::features");

    bool SupportedFeatures::operator==(const SupportedFeatures& rhs) const {
        return  std::tie(
            featureCount,
            features
        ) == std::tie(
            rhs.featureCount,
            rhs.features
        );
    }


    static_assert(sizeof(SupportedInstanceFeatures) == sizeof(WGPUSupportedInstanceFeatures), "sizeof mismatch for SupportedInstanceFeatures");
    static_assert(alignof(SupportedInstanceFeatures) == alignof(WGPUSupportedInstanceFeatures), "alignof mismatch for SupportedInstanceFeatures");

    static_assert(offsetof(SupportedInstanceFeatures, featureCount) == offsetof(WGPUSupportedInstanceFeatures, featureCount),
                 "offsetof mismatch for SupportedInstanceFeatures::featureCount");
    static_assert(offsetof(SupportedInstanceFeatures, features) == offsetof(WGPUSupportedInstanceFeatures, features),
                 "offsetof mismatch for SupportedInstanceFeatures::features");

    bool SupportedInstanceFeatures::operator==(const SupportedInstanceFeatures& rhs) const {
        return  std::tie(
            featureCount,
            features
        ) == std::tie(
            rhs.featureCount,
            rhs.features
        );
    }


    static_assert(sizeof(SupportedWGSLLanguageFeatures) == sizeof(WGPUSupportedWGSLLanguageFeatures), "sizeof mismatch for SupportedWGSLLanguageFeatures");
    static_assert(alignof(SupportedWGSLLanguageFeatures) == alignof(WGPUSupportedWGSLLanguageFeatures), "alignof mismatch for SupportedWGSLLanguageFeatures");

    static_assert(offsetof(SupportedWGSLLanguageFeatures, featureCount) == offsetof(WGPUSupportedWGSLLanguageFeatures, featureCount),
                 "offsetof mismatch for SupportedWGSLLanguageFeatures::featureCount");
    static_assert(offsetof(SupportedWGSLLanguageFeatures, features) == offsetof(WGPUSupportedWGSLLanguageFeatures, features),
                 "offsetof mismatch for SupportedWGSLLanguageFeatures::features");

    bool SupportedWGSLLanguageFeatures::operator==(const SupportedWGSLLanguageFeatures& rhs) const {
        return  std::tie(
            featureCount,
            features
        ) == std::tie(
            rhs.featureCount,
            rhs.features
        );
    }


    static_assert(sizeof(SurfaceCapabilities) == sizeof(WGPUSurfaceCapabilities), "sizeof mismatch for SurfaceCapabilities");
    static_assert(alignof(SurfaceCapabilities) == alignof(WGPUSurfaceCapabilities), "alignof mismatch for SurfaceCapabilities");

    static_assert(offsetof(SurfaceCapabilities, nextInChain) == offsetof(WGPUSurfaceCapabilities, nextInChain),
            "offsetof mismatch for SurfaceCapabilities::nextInChain");
    static_assert(offsetof(SurfaceCapabilities, usages) == offsetof(WGPUSurfaceCapabilities, usages),
                 "offsetof mismatch for SurfaceCapabilities::usages");
    static_assert(offsetof(SurfaceCapabilities, formatCount) == offsetof(WGPUSurfaceCapabilities, formatCount),
                 "offsetof mismatch for SurfaceCapabilities::formatCount");
    static_assert(offsetof(SurfaceCapabilities, formats) == offsetof(WGPUSurfaceCapabilities, formats),
                 "offsetof mismatch for SurfaceCapabilities::formats");
    static_assert(offsetof(SurfaceCapabilities, presentModeCount) == offsetof(WGPUSurfaceCapabilities, presentModeCount),
                 "offsetof mismatch for SurfaceCapabilities::presentModeCount");
    static_assert(offsetof(SurfaceCapabilities, presentModes) == offsetof(WGPUSurfaceCapabilities, presentModes),
                 "offsetof mismatch for SurfaceCapabilities::presentModes");
    static_assert(offsetof(SurfaceCapabilities, alphaModeCount) == offsetof(WGPUSurfaceCapabilities, alphaModeCount),
                 "offsetof mismatch for SurfaceCapabilities::alphaModeCount");
    static_assert(offsetof(SurfaceCapabilities, alphaModes) == offsetof(WGPUSurfaceCapabilities, alphaModes),
                 "offsetof mismatch for SurfaceCapabilities::alphaModes");

    bool SurfaceCapabilities::operator==(const SurfaceCapabilities& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            usages,
            formatCount,
            formats,
            presentModeCount,
            presentModes,
            alphaModeCount,
            alphaModes
        ) == std::tie(
            rhs.usages,
            rhs.formatCount,
            rhs.formats,
            rhs.presentModeCount,
            rhs.presentModes,
            rhs.alphaModeCount,
            rhs.alphaModes
        );
    }


    static_assert(sizeof(SurfaceColorManagement) == sizeof(WGPUSurfaceColorManagement), "sizeof mismatch for SurfaceColorManagement");
    static_assert(alignof(SurfaceColorManagement) == alignof(WGPUSurfaceColorManagement), "alignof mismatch for SurfaceColorManagement");

    static_assert(offsetof(SurfaceColorManagement, nextInChain) == offsetof(WGPUSurfaceColorManagement, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SurfaceColorManagement::nextInChain");
    static_assert(offsetof(SurfaceColorManagement, sType) == offsetof(WGPUSurfaceColorManagement, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SurfaceColorManagement::sType");
    static_assert(offsetof(SurfaceColorManagement, colorSpace) == offsetof(WGPUSurfaceColorManagement, colorSpace),
                 "offsetof mismatch for SurfaceColorManagement::colorSpace");
    static_assert(offsetof(SurfaceColorManagement, toneMappingMode) == offsetof(WGPUSurfaceColorManagement, toneMappingMode),
                 "offsetof mismatch for SurfaceColorManagement::toneMappingMode");

    bool SurfaceColorManagement::operator==(const SurfaceColorManagement& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            colorSpace,
            toneMappingMode
        ) == std::tie(
            rhs.colorSpace,
            rhs.toneMappingMode
        );
    }


    static_assert(sizeof(SurfaceConfiguration) == sizeof(WGPUSurfaceConfiguration), "sizeof mismatch for SurfaceConfiguration");
    static_assert(alignof(SurfaceConfiguration) == alignof(WGPUSurfaceConfiguration), "alignof mismatch for SurfaceConfiguration");

    static_assert(offsetof(SurfaceConfiguration, nextInChain) == offsetof(WGPUSurfaceConfiguration, nextInChain),
            "offsetof mismatch for SurfaceConfiguration::nextInChain");
    static_assert(offsetof(SurfaceConfiguration, device) == offsetof(WGPUSurfaceConfiguration, device),
                 "offsetof mismatch for SurfaceConfiguration::device");
    static_assert(offsetof(SurfaceConfiguration, format) == offsetof(WGPUSurfaceConfiguration, format),
                 "offsetof mismatch for SurfaceConfiguration::format");
    static_assert(offsetof(SurfaceConfiguration, usage) == offsetof(WGPUSurfaceConfiguration, usage),
                 "offsetof mismatch for SurfaceConfiguration::usage");
    static_assert(offsetof(SurfaceConfiguration, width) == offsetof(WGPUSurfaceConfiguration, width),
                 "offsetof mismatch for SurfaceConfiguration::width");
    static_assert(offsetof(SurfaceConfiguration, height) == offsetof(WGPUSurfaceConfiguration, height),
                 "offsetof mismatch for SurfaceConfiguration::height");
    static_assert(offsetof(SurfaceConfiguration, viewFormatCount) == offsetof(WGPUSurfaceConfiguration, viewFormatCount),
                 "offsetof mismatch for SurfaceConfiguration::viewFormatCount");
    static_assert(offsetof(SurfaceConfiguration, viewFormats) == offsetof(WGPUSurfaceConfiguration, viewFormats),
                 "offsetof mismatch for SurfaceConfiguration::viewFormats");
    static_assert(offsetof(SurfaceConfiguration, alphaMode) == offsetof(WGPUSurfaceConfiguration, alphaMode),
                 "offsetof mismatch for SurfaceConfiguration::alphaMode");
    static_assert(offsetof(SurfaceConfiguration, presentMode) == offsetof(WGPUSurfaceConfiguration, presentMode),
                 "offsetof mismatch for SurfaceConfiguration::presentMode");

    SurfaceConfiguration SurfaceConfiguration::WithTrivialFrontendDefaults() const {
        SurfaceConfiguration copy;
        copy.nextInChain = nextInChain;
        copy.device = device;
        copy.format = format;
        copy.usage = usage;
        copy.width = width;
        copy.height = height;
        copy.viewFormatCount = viewFormatCount;
        copy.viewFormats = viewFormats;
        copy.alphaMode = alphaMode;
        copy.presentMode = (presentMode == wgpu::PresentMode::Undefined)
            ? wgpu::PresentMode::Fifo
            : presentMode;
        return copy;
    }
    bool SurfaceConfiguration::operator==(const SurfaceConfiguration& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            device,
            format,
            usage,
            width,
            height,
            viewFormatCount,
            viewFormats,
            alphaMode,
            presentMode
        ) == std::tie(
            rhs.device,
            rhs.format,
            rhs.usage,
            rhs.width,
            rhs.height,
            rhs.viewFormatCount,
            rhs.viewFormats,
            rhs.alphaMode,
            rhs.presentMode
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromWindowsCoreWindow) == sizeof(WGPUSurfaceDescriptorFromWindowsCoreWindow), "sizeof mismatch for SurfaceDescriptorFromWindowsCoreWindow");
    static_assert(alignof(SurfaceDescriptorFromWindowsCoreWindow) == alignof(WGPUSurfaceDescriptorFromWindowsCoreWindow), "alignof mismatch for SurfaceDescriptorFromWindowsCoreWindow");

    static_assert(offsetof(SurfaceDescriptorFromWindowsCoreWindow, nextInChain) == offsetof(WGPUSurfaceDescriptorFromWindowsCoreWindow, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SurfaceDescriptorFromWindowsCoreWindow::nextInChain");
    static_assert(offsetof(SurfaceDescriptorFromWindowsCoreWindow, sType) == offsetof(WGPUSurfaceDescriptorFromWindowsCoreWindow, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SurfaceDescriptorFromWindowsCoreWindow::sType");
    static_assert(offsetof(SurfaceDescriptorFromWindowsCoreWindow, coreWindow) == offsetof(WGPUSurfaceDescriptorFromWindowsCoreWindow, coreWindow),
                 "offsetof mismatch for SurfaceDescriptorFromWindowsCoreWindow::coreWindow");

    bool SurfaceDescriptorFromWindowsCoreWindow::operator==(const SurfaceDescriptorFromWindowsCoreWindow& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            coreWindow
        ) == std::tie(
            rhs.coreWindow
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromWindowsUWPSwapChainPanel) == sizeof(WGPUSurfaceDescriptorFromWindowsUWPSwapChainPanel), "sizeof mismatch for SurfaceDescriptorFromWindowsUWPSwapChainPanel");
    static_assert(alignof(SurfaceDescriptorFromWindowsUWPSwapChainPanel) == alignof(WGPUSurfaceDescriptorFromWindowsUWPSwapChainPanel), "alignof mismatch for SurfaceDescriptorFromWindowsUWPSwapChainPanel");

    static_assert(offsetof(SurfaceDescriptorFromWindowsUWPSwapChainPanel, nextInChain) == offsetof(WGPUSurfaceDescriptorFromWindowsUWPSwapChainPanel, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SurfaceDescriptorFromWindowsUWPSwapChainPanel::nextInChain");
    static_assert(offsetof(SurfaceDescriptorFromWindowsUWPSwapChainPanel, sType) == offsetof(WGPUSurfaceDescriptorFromWindowsUWPSwapChainPanel, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SurfaceDescriptorFromWindowsUWPSwapChainPanel::sType");
    static_assert(offsetof(SurfaceDescriptorFromWindowsUWPSwapChainPanel, swapChainPanel) == offsetof(WGPUSurfaceDescriptorFromWindowsUWPSwapChainPanel, swapChainPanel),
                 "offsetof mismatch for SurfaceDescriptorFromWindowsUWPSwapChainPanel::swapChainPanel");

    bool SurfaceDescriptorFromWindowsUWPSwapChainPanel::operator==(const SurfaceDescriptorFromWindowsUWPSwapChainPanel& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            swapChainPanel
        ) == std::tie(
            rhs.swapChainPanel
        );
    }


    static_assert(sizeof(SurfaceDescriptorFromWindowsWinUISwapChainPanel) == sizeof(WGPUSurfaceDescriptorFromWindowsWinUISwapChainPanel), "sizeof mismatch for SurfaceDescriptorFromWindowsWinUISwapChainPanel");
    static_assert(alignof(SurfaceDescriptorFromWindowsWinUISwapChainPanel) == alignof(WGPUSurfaceDescriptorFromWindowsWinUISwapChainPanel), "alignof mismatch for SurfaceDescriptorFromWindowsWinUISwapChainPanel");

    static_assert(offsetof(SurfaceDescriptorFromWindowsWinUISwapChainPanel, nextInChain) == offsetof(WGPUSurfaceDescriptorFromWindowsWinUISwapChainPanel, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SurfaceDescriptorFromWindowsWinUISwapChainPanel::nextInChain");
    static_assert(offsetof(SurfaceDescriptorFromWindowsWinUISwapChainPanel, sType) == offsetof(WGPUSurfaceDescriptorFromWindowsWinUISwapChainPanel, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SurfaceDescriptorFromWindowsWinUISwapChainPanel::sType");
    static_assert(offsetof(SurfaceDescriptorFromWindowsWinUISwapChainPanel, swapChainPanel) == offsetof(WGPUSurfaceDescriptorFromWindowsWinUISwapChainPanel, swapChainPanel),
                 "offsetof mismatch for SurfaceDescriptorFromWindowsWinUISwapChainPanel::swapChainPanel");

    bool SurfaceDescriptorFromWindowsWinUISwapChainPanel::operator==(const SurfaceDescriptorFromWindowsWinUISwapChainPanel& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            swapChainPanel
        ) == std::tie(
            rhs.swapChainPanel
        );
    }


    static_assert(sizeof(SurfaceSourceAndroidNativeWindow) == sizeof(WGPUSurfaceSourceAndroidNativeWindow), "sizeof mismatch for SurfaceSourceAndroidNativeWindow");
    static_assert(alignof(SurfaceSourceAndroidNativeWindow) == alignof(WGPUSurfaceSourceAndroidNativeWindow), "alignof mismatch for SurfaceSourceAndroidNativeWindow");

    static_assert(offsetof(SurfaceSourceAndroidNativeWindow, nextInChain) == offsetof(WGPUSurfaceSourceAndroidNativeWindow, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SurfaceSourceAndroidNativeWindow::nextInChain");
    static_assert(offsetof(SurfaceSourceAndroidNativeWindow, sType) == offsetof(WGPUSurfaceSourceAndroidNativeWindow, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SurfaceSourceAndroidNativeWindow::sType");
    static_assert(offsetof(SurfaceSourceAndroidNativeWindow, window) == offsetof(WGPUSurfaceSourceAndroidNativeWindow, window),
                 "offsetof mismatch for SurfaceSourceAndroidNativeWindow::window");

    bool SurfaceSourceAndroidNativeWindow::operator==(const SurfaceSourceAndroidNativeWindow& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            window
        ) == std::tie(
            rhs.window
        );
    }


    static_assert(sizeof(SurfaceSourceMetalLayer) == sizeof(WGPUSurfaceSourceMetalLayer), "sizeof mismatch for SurfaceSourceMetalLayer");
    static_assert(alignof(SurfaceSourceMetalLayer) == alignof(WGPUSurfaceSourceMetalLayer), "alignof mismatch for SurfaceSourceMetalLayer");

    static_assert(offsetof(SurfaceSourceMetalLayer, nextInChain) == offsetof(WGPUSurfaceSourceMetalLayer, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SurfaceSourceMetalLayer::nextInChain");
    static_assert(offsetof(SurfaceSourceMetalLayer, sType) == offsetof(WGPUSurfaceSourceMetalLayer, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SurfaceSourceMetalLayer::sType");
    static_assert(offsetof(SurfaceSourceMetalLayer, layer) == offsetof(WGPUSurfaceSourceMetalLayer, layer),
                 "offsetof mismatch for SurfaceSourceMetalLayer::layer");

    bool SurfaceSourceMetalLayer::operator==(const SurfaceSourceMetalLayer& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            layer
        ) == std::tie(
            rhs.layer
        );
    }


    static_assert(sizeof(SurfaceSourceWaylandSurface) == sizeof(WGPUSurfaceSourceWaylandSurface), "sizeof mismatch for SurfaceSourceWaylandSurface");
    static_assert(alignof(SurfaceSourceWaylandSurface) == alignof(WGPUSurfaceSourceWaylandSurface), "alignof mismatch for SurfaceSourceWaylandSurface");

    static_assert(offsetof(SurfaceSourceWaylandSurface, nextInChain) == offsetof(WGPUSurfaceSourceWaylandSurface, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SurfaceSourceWaylandSurface::nextInChain");
    static_assert(offsetof(SurfaceSourceWaylandSurface, sType) == offsetof(WGPUSurfaceSourceWaylandSurface, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SurfaceSourceWaylandSurface::sType");
    static_assert(offsetof(SurfaceSourceWaylandSurface, display) == offsetof(WGPUSurfaceSourceWaylandSurface, display),
                 "offsetof mismatch for SurfaceSourceWaylandSurface::display");
    static_assert(offsetof(SurfaceSourceWaylandSurface, surface) == offsetof(WGPUSurfaceSourceWaylandSurface, surface),
                 "offsetof mismatch for SurfaceSourceWaylandSurface::surface");

    bool SurfaceSourceWaylandSurface::operator==(const SurfaceSourceWaylandSurface& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            display,
            surface
        ) == std::tie(
            rhs.display,
            rhs.surface
        );
    }


    static_assert(sizeof(SurfaceSourceWindowsHWND) == sizeof(WGPUSurfaceSourceWindowsHWND), "sizeof mismatch for SurfaceSourceWindowsHWND");
    static_assert(alignof(SurfaceSourceWindowsHWND) == alignof(WGPUSurfaceSourceWindowsHWND), "alignof mismatch for SurfaceSourceWindowsHWND");

    static_assert(offsetof(SurfaceSourceWindowsHWND, nextInChain) == offsetof(WGPUSurfaceSourceWindowsHWND, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SurfaceSourceWindowsHWND::nextInChain");
    static_assert(offsetof(SurfaceSourceWindowsHWND, sType) == offsetof(WGPUSurfaceSourceWindowsHWND, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SurfaceSourceWindowsHWND::sType");
    static_assert(offsetof(SurfaceSourceWindowsHWND, hinstance) == offsetof(WGPUSurfaceSourceWindowsHWND, hinstance),
                 "offsetof mismatch for SurfaceSourceWindowsHWND::hinstance");
    static_assert(offsetof(SurfaceSourceWindowsHWND, hwnd) == offsetof(WGPUSurfaceSourceWindowsHWND, hwnd),
                 "offsetof mismatch for SurfaceSourceWindowsHWND::hwnd");

    bool SurfaceSourceWindowsHWND::operator==(const SurfaceSourceWindowsHWND& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            hinstance,
            hwnd
        ) == std::tie(
            rhs.hinstance,
            rhs.hwnd
        );
    }


    static_assert(sizeof(SurfaceSourceXCBWindow) == sizeof(WGPUSurfaceSourceXCBWindow), "sizeof mismatch for SurfaceSourceXCBWindow");
    static_assert(alignof(SurfaceSourceXCBWindow) == alignof(WGPUSurfaceSourceXCBWindow), "alignof mismatch for SurfaceSourceXCBWindow");

    static_assert(offsetof(SurfaceSourceXCBWindow, nextInChain) == offsetof(WGPUSurfaceSourceXCBWindow, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SurfaceSourceXCBWindow::nextInChain");
    static_assert(offsetof(SurfaceSourceXCBWindow, sType) == offsetof(WGPUSurfaceSourceXCBWindow, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SurfaceSourceXCBWindow::sType");
    static_assert(offsetof(SurfaceSourceXCBWindow, connection) == offsetof(WGPUSurfaceSourceXCBWindow, connection),
                 "offsetof mismatch for SurfaceSourceXCBWindow::connection");
    static_assert(offsetof(SurfaceSourceXCBWindow, window) == offsetof(WGPUSurfaceSourceXCBWindow, window),
                 "offsetof mismatch for SurfaceSourceXCBWindow::window");

    bool SurfaceSourceXCBWindow::operator==(const SurfaceSourceXCBWindow& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            connection,
            window
        ) == std::tie(
            rhs.connection,
            rhs.window
        );
    }


    static_assert(sizeof(SurfaceSourceXlibWindow) == sizeof(WGPUSurfaceSourceXlibWindow), "sizeof mismatch for SurfaceSourceXlibWindow");
    static_assert(alignof(SurfaceSourceXlibWindow) == alignof(WGPUSurfaceSourceXlibWindow), "alignof mismatch for SurfaceSourceXlibWindow");

    static_assert(offsetof(SurfaceSourceXlibWindow, nextInChain) == offsetof(WGPUSurfaceSourceXlibWindow, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SurfaceSourceXlibWindow::nextInChain");
    static_assert(offsetof(SurfaceSourceXlibWindow, sType) == offsetof(WGPUSurfaceSourceXlibWindow, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SurfaceSourceXlibWindow::sType");
    static_assert(offsetof(SurfaceSourceXlibWindow, display) == offsetof(WGPUSurfaceSourceXlibWindow, display),
                 "offsetof mismatch for SurfaceSourceXlibWindow::display");
    static_assert(offsetof(SurfaceSourceXlibWindow, window) == offsetof(WGPUSurfaceSourceXlibWindow, window),
                 "offsetof mismatch for SurfaceSourceXlibWindow::window");

    bool SurfaceSourceXlibWindow::operator==(const SurfaceSourceXlibWindow& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            display,
            window
        ) == std::tie(
            rhs.display,
            rhs.window
        );
    }


    static_assert(sizeof(SurfaceTexture) == sizeof(WGPUSurfaceTexture), "sizeof mismatch for SurfaceTexture");
    static_assert(alignof(SurfaceTexture) == alignof(WGPUSurfaceTexture), "alignof mismatch for SurfaceTexture");

    static_assert(offsetof(SurfaceTexture, nextInChain) == offsetof(WGPUSurfaceTexture, nextInChain),
            "offsetof mismatch for SurfaceTexture::nextInChain");
    static_assert(offsetof(SurfaceTexture, texture) == offsetof(WGPUSurfaceTexture, texture),
                 "offsetof mismatch for SurfaceTexture::texture");
    static_assert(offsetof(SurfaceTexture, status) == offsetof(WGPUSurfaceTexture, status),
                 "offsetof mismatch for SurfaceTexture::status");

    bool SurfaceTexture::operator==(const SurfaceTexture& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            texture,
            status
        ) == std::tie(
            rhs.texture,
            rhs.status
        );
    }


    static_assert(sizeof(TexelBufferBindingEntry) == sizeof(WGPUTexelBufferBindingEntry), "sizeof mismatch for TexelBufferBindingEntry");
    static_assert(alignof(TexelBufferBindingEntry) == alignof(WGPUTexelBufferBindingEntry), "alignof mismatch for TexelBufferBindingEntry");

    static_assert(offsetof(TexelBufferBindingEntry, nextInChain) == offsetof(WGPUTexelBufferBindingEntry, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for TexelBufferBindingEntry::nextInChain");
    static_assert(offsetof(TexelBufferBindingEntry, sType) == offsetof(WGPUTexelBufferBindingEntry, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for TexelBufferBindingEntry::sType");
    static_assert(offsetof(TexelBufferBindingEntry, texelBufferView) == offsetof(WGPUTexelBufferBindingEntry, texelBufferView),
                 "offsetof mismatch for TexelBufferBindingEntry::texelBufferView");

    bool TexelBufferBindingEntry::operator==(const TexelBufferBindingEntry& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            texelBufferView
        ) == std::tie(
            rhs.texelBufferView
        );
    }


    static_assert(sizeof(TexelBufferBindingLayout) == sizeof(WGPUTexelBufferBindingLayout), "sizeof mismatch for TexelBufferBindingLayout");
    static_assert(alignof(TexelBufferBindingLayout) == alignof(WGPUTexelBufferBindingLayout), "alignof mismatch for TexelBufferBindingLayout");

    static_assert(offsetof(TexelBufferBindingLayout, nextInChain) == offsetof(WGPUTexelBufferBindingLayout, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for TexelBufferBindingLayout::nextInChain");
    static_assert(offsetof(TexelBufferBindingLayout, sType) == offsetof(WGPUTexelBufferBindingLayout, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for TexelBufferBindingLayout::sType");
    static_assert(offsetof(TexelBufferBindingLayout, access) == offsetof(WGPUTexelBufferBindingLayout, access),
                 "offsetof mismatch for TexelBufferBindingLayout::access");
    static_assert(offsetof(TexelBufferBindingLayout, format) == offsetof(WGPUTexelBufferBindingLayout, format),
                 "offsetof mismatch for TexelBufferBindingLayout::format");

    TexelBufferBindingLayout TexelBufferBindingLayout::WithTrivialFrontendDefaults() const {
        TexelBufferBindingLayout copy;
        copy.nextInChain = nextInChain;
        copy.sType = sType;
        copy.access = (access == wgpu::TexelBufferAccess::Undefined)
            ? wgpu::TexelBufferAccess::ReadWrite
            : access;
        copy.format = format;
        return copy;
    }
    bool TexelBufferBindingLayout::operator==(const TexelBufferBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            access,
            format
        ) == std::tie(
            rhs.access,
            rhs.format
        );
    }


    static_assert(sizeof(TexelBufferViewDescriptor) == sizeof(WGPUTexelBufferViewDescriptor), "sizeof mismatch for TexelBufferViewDescriptor");
    static_assert(alignof(TexelBufferViewDescriptor) == alignof(WGPUTexelBufferViewDescriptor), "alignof mismatch for TexelBufferViewDescriptor");

    static_assert(offsetof(TexelBufferViewDescriptor, nextInChain) == offsetof(WGPUTexelBufferViewDescriptor, nextInChain),
            "offsetof mismatch for TexelBufferViewDescriptor::nextInChain");
    static_assert(offsetof(TexelBufferViewDescriptor, label) == offsetof(WGPUTexelBufferViewDescriptor, label),
                 "offsetof mismatch for TexelBufferViewDescriptor::label");
    static_assert(offsetof(TexelBufferViewDescriptor, format) == offsetof(WGPUTexelBufferViewDescriptor, format),
                 "offsetof mismatch for TexelBufferViewDescriptor::format");
    static_assert(offsetof(TexelBufferViewDescriptor, offset) == offsetof(WGPUTexelBufferViewDescriptor, offset),
                 "offsetof mismatch for TexelBufferViewDescriptor::offset");
    static_assert(offsetof(TexelBufferViewDescriptor, size) == offsetof(WGPUTexelBufferViewDescriptor, size),
                 "offsetof mismatch for TexelBufferViewDescriptor::size");

    bool TexelBufferViewDescriptor::operator==(const TexelBufferViewDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            format,
            offset,
            size
        ) == std::tie(
            rhs.label,
            rhs.format,
            rhs.offset,
            rhs.size
        );
    }


    static_assert(sizeof(TexelCopyBufferLayout) == sizeof(WGPUTexelCopyBufferLayout), "sizeof mismatch for TexelCopyBufferLayout");
    static_assert(alignof(TexelCopyBufferLayout) == alignof(WGPUTexelCopyBufferLayout), "alignof mismatch for TexelCopyBufferLayout");

    static_assert(offsetof(TexelCopyBufferLayout, offset) == offsetof(WGPUTexelCopyBufferLayout, offset),
                 "offsetof mismatch for TexelCopyBufferLayout::offset");
    static_assert(offsetof(TexelCopyBufferLayout, bytesPerRow) == offsetof(WGPUTexelCopyBufferLayout, bytesPerRow),
                 "offsetof mismatch for TexelCopyBufferLayout::bytesPerRow");
    static_assert(offsetof(TexelCopyBufferLayout, rowsPerImage) == offsetof(WGPUTexelCopyBufferLayout, rowsPerImage),
                 "offsetof mismatch for TexelCopyBufferLayout::rowsPerImage");

    bool TexelCopyBufferLayout::operator==(const TexelCopyBufferLayout& rhs) const {
        return  std::tie(
            offset,
            bytesPerRow,
            rowsPerImage
        ) == std::tie(
            rhs.offset,
            rhs.bytesPerRow,
            rhs.rowsPerImage
        );
    }


    static_assert(sizeof(TextureBindingLayout) == sizeof(WGPUTextureBindingLayout), "sizeof mismatch for TextureBindingLayout");
    static_assert(alignof(TextureBindingLayout) == alignof(WGPUTextureBindingLayout), "alignof mismatch for TextureBindingLayout");

    static_assert(offsetof(TextureBindingLayout, nextInChain) == offsetof(WGPUTextureBindingLayout, nextInChain),
            "offsetof mismatch for TextureBindingLayout::nextInChain");
    static_assert(offsetof(TextureBindingLayout, sampleType) == offsetof(WGPUTextureBindingLayout, sampleType),
                 "offsetof mismatch for TextureBindingLayout::sampleType");
    static_assert(offsetof(TextureBindingLayout, viewDimension) == offsetof(WGPUTextureBindingLayout, viewDimension),
                 "offsetof mismatch for TextureBindingLayout::viewDimension");
    static_assert(offsetof(TextureBindingLayout, multisampled) == offsetof(WGPUTextureBindingLayout, multisampled),
                 "offsetof mismatch for TextureBindingLayout::multisampled");

    TextureBindingLayout TextureBindingLayout::WithTrivialFrontendDefaults() const {
        TextureBindingLayout copy;
        copy.nextInChain = nextInChain;
        copy.sampleType = (sampleType == wgpu::TextureSampleType::Undefined)
            ? wgpu::TextureSampleType::Float
            : sampleType;
        copy.viewDimension = (viewDimension == wgpu::TextureViewDimension::Undefined)
            ? wgpu::TextureViewDimension::e2D
            : viewDimension;
        copy.multisampled = multisampled;
        return copy;
    }
    bool TextureBindingLayout::operator==(const TextureBindingLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            sampleType,
            viewDimension,
            multisampled
        ) == std::tie(
            rhs.sampleType,
            rhs.viewDimension,
            rhs.multisampled
        );
    }


    static_assert(sizeof(TextureBindingViewDimensionDescriptor) == sizeof(WGPUTextureBindingViewDimensionDescriptor), "sizeof mismatch for TextureBindingViewDimensionDescriptor");
    static_assert(alignof(TextureBindingViewDimensionDescriptor) == alignof(WGPUTextureBindingViewDimensionDescriptor), "alignof mismatch for TextureBindingViewDimensionDescriptor");

    static_assert(offsetof(TextureBindingViewDimensionDescriptor, nextInChain) == offsetof(WGPUTextureBindingViewDimensionDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for TextureBindingViewDimensionDescriptor::nextInChain");
    static_assert(offsetof(TextureBindingViewDimensionDescriptor, sType) == offsetof(WGPUTextureBindingViewDimensionDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for TextureBindingViewDimensionDescriptor::sType");
    static_assert(offsetof(TextureBindingViewDimensionDescriptor, textureBindingViewDimension) == offsetof(WGPUTextureBindingViewDimensionDescriptor, textureBindingViewDimension),
                 "offsetof mismatch for TextureBindingViewDimensionDescriptor::textureBindingViewDimension");

    bool TextureBindingViewDimensionDescriptor::operator==(const TextureBindingViewDimensionDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            textureBindingViewDimension
        ) == std::tie(
            rhs.textureBindingViewDimension
        );
    }


    static_assert(sizeof(TextureComponentSwizzle) == sizeof(WGPUTextureComponentSwizzle), "sizeof mismatch for TextureComponentSwizzle");
    static_assert(alignof(TextureComponentSwizzle) == alignof(WGPUTextureComponentSwizzle), "alignof mismatch for TextureComponentSwizzle");

    static_assert(offsetof(TextureComponentSwizzle, r) == offsetof(WGPUTextureComponentSwizzle, r),
                 "offsetof mismatch for TextureComponentSwizzle::r");
    static_assert(offsetof(TextureComponentSwizzle, g) == offsetof(WGPUTextureComponentSwizzle, g),
                 "offsetof mismatch for TextureComponentSwizzle::g");
    static_assert(offsetof(TextureComponentSwizzle, b) == offsetof(WGPUTextureComponentSwizzle, b),
                 "offsetof mismatch for TextureComponentSwizzle::b");
    static_assert(offsetof(TextureComponentSwizzle, a) == offsetof(WGPUTextureComponentSwizzle, a),
                 "offsetof mismatch for TextureComponentSwizzle::a");

    TextureComponentSwizzle TextureComponentSwizzle::WithTrivialFrontendDefaults() const {
        TextureComponentSwizzle copy;
        copy.r = (r == wgpu::ComponentSwizzle::Undefined)
            ? wgpu::ComponentSwizzle::R
            : r;
        copy.g = (g == wgpu::ComponentSwizzle::Undefined)
            ? wgpu::ComponentSwizzle::G
            : g;
        copy.b = (b == wgpu::ComponentSwizzle::Undefined)
            ? wgpu::ComponentSwizzle::B
            : b;
        copy.a = (a == wgpu::ComponentSwizzle::Undefined)
            ? wgpu::ComponentSwizzle::A
            : a;
        return copy;
    }
    bool TextureComponentSwizzle::operator==(const TextureComponentSwizzle& rhs) const {
        return  std::tie(
            r,
            g,
            b,
            a
        ) == std::tie(
            rhs.r,
            rhs.g,
            rhs.b,
            rhs.a
        );
    }


    static_assert(sizeof(VertexAttribute) == sizeof(WGPUVertexAttribute), "sizeof mismatch for VertexAttribute");
    static_assert(alignof(VertexAttribute) == alignof(WGPUVertexAttribute), "alignof mismatch for VertexAttribute");

    static_assert(offsetof(VertexAttribute, nextInChain) == offsetof(WGPUVertexAttribute, nextInChain),
            "offsetof mismatch for VertexAttribute::nextInChain");
    static_assert(offsetof(VertexAttribute, format) == offsetof(WGPUVertexAttribute, format),
                 "offsetof mismatch for VertexAttribute::format");
    static_assert(offsetof(VertexAttribute, offset) == offsetof(WGPUVertexAttribute, offset),
                 "offsetof mismatch for VertexAttribute::offset");
    static_assert(offsetof(VertexAttribute, shaderLocation) == offsetof(WGPUVertexAttribute, shaderLocation),
                 "offsetof mismatch for VertexAttribute::shaderLocation");

    bool VertexAttribute::operator==(const VertexAttribute& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            format,
            offset,
            shaderLocation
        ) == std::tie(
            rhs.format,
            rhs.offset,
            rhs.shaderLocation
        );
    }


    static_assert(sizeof(YCbCrVkDescriptor) == sizeof(WGPUYCbCrVkDescriptor), "sizeof mismatch for YCbCrVkDescriptor");
    static_assert(alignof(YCbCrVkDescriptor) == alignof(WGPUYCbCrVkDescriptor), "alignof mismatch for YCbCrVkDescriptor");

    static_assert(offsetof(YCbCrVkDescriptor, nextInChain) == offsetof(WGPUYCbCrVkDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for YCbCrVkDescriptor::nextInChain");
    static_assert(offsetof(YCbCrVkDescriptor, sType) == offsetof(WGPUYCbCrVkDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for YCbCrVkDescriptor::sType");
    static_assert(offsetof(YCbCrVkDescriptor, vkFormat) == offsetof(WGPUYCbCrVkDescriptor, vkFormat),
                 "offsetof mismatch for YCbCrVkDescriptor::vkFormat");
    static_assert(offsetof(YCbCrVkDescriptor, vkYCbCrModel) == offsetof(WGPUYCbCrVkDescriptor, vkYCbCrModel),
                 "offsetof mismatch for YCbCrVkDescriptor::vkYCbCrModel");
    static_assert(offsetof(YCbCrVkDescriptor, vkYCbCrRange) == offsetof(WGPUYCbCrVkDescriptor, vkYCbCrRange),
                 "offsetof mismatch for YCbCrVkDescriptor::vkYCbCrRange");
    static_assert(offsetof(YCbCrVkDescriptor, vkComponentSwizzleRed) == offsetof(WGPUYCbCrVkDescriptor, vkComponentSwizzleRed),
                 "offsetof mismatch for YCbCrVkDescriptor::vkComponentSwizzleRed");
    static_assert(offsetof(YCbCrVkDescriptor, vkComponentSwizzleGreen) == offsetof(WGPUYCbCrVkDescriptor, vkComponentSwizzleGreen),
                 "offsetof mismatch for YCbCrVkDescriptor::vkComponentSwizzleGreen");
    static_assert(offsetof(YCbCrVkDescriptor, vkComponentSwizzleBlue) == offsetof(WGPUYCbCrVkDescriptor, vkComponentSwizzleBlue),
                 "offsetof mismatch for YCbCrVkDescriptor::vkComponentSwizzleBlue");
    static_assert(offsetof(YCbCrVkDescriptor, vkComponentSwizzleAlpha) == offsetof(WGPUYCbCrVkDescriptor, vkComponentSwizzleAlpha),
                 "offsetof mismatch for YCbCrVkDescriptor::vkComponentSwizzleAlpha");
    static_assert(offsetof(YCbCrVkDescriptor, vkXChromaOffset) == offsetof(WGPUYCbCrVkDescriptor, vkXChromaOffset),
                 "offsetof mismatch for YCbCrVkDescriptor::vkXChromaOffset");
    static_assert(offsetof(YCbCrVkDescriptor, vkYChromaOffset) == offsetof(WGPUYCbCrVkDescriptor, vkYChromaOffset),
                 "offsetof mismatch for YCbCrVkDescriptor::vkYChromaOffset");
    static_assert(offsetof(YCbCrVkDescriptor, vkChromaFilter) == offsetof(WGPUYCbCrVkDescriptor, vkChromaFilter),
                 "offsetof mismatch for YCbCrVkDescriptor::vkChromaFilter");
    static_assert(offsetof(YCbCrVkDescriptor, forceExplicitReconstruction) == offsetof(WGPUYCbCrVkDescriptor, forceExplicitReconstruction),
                 "offsetof mismatch for YCbCrVkDescriptor::forceExplicitReconstruction");
    static_assert(offsetof(YCbCrVkDescriptor, externalFormat) == offsetof(WGPUYCbCrVkDescriptor, externalFormat),
                 "offsetof mismatch for YCbCrVkDescriptor::externalFormat");

    YCbCrVkDescriptor YCbCrVkDescriptor::WithTrivialFrontendDefaults() const {
        YCbCrVkDescriptor copy;
        copy.nextInChain = nextInChain;
        copy.sType = sType;
        copy.vkFormat = vkFormat;
        copy.vkYCbCrModel = vkYCbCrModel;
        copy.vkYCbCrRange = vkYCbCrRange;
        copy.vkComponentSwizzleRed = vkComponentSwizzleRed;
        copy.vkComponentSwizzleGreen = vkComponentSwizzleGreen;
        copy.vkComponentSwizzleBlue = vkComponentSwizzleBlue;
        copy.vkComponentSwizzleAlpha = vkComponentSwizzleAlpha;
        copy.vkXChromaOffset = vkXChromaOffset;
        copy.vkYChromaOffset = vkYChromaOffset;
        copy.vkChromaFilter = (vkChromaFilter == wgpu::FilterMode::Undefined)
            ? wgpu::FilterMode::Nearest
            : vkChromaFilter;
        copy.forceExplicitReconstruction = forceExplicitReconstruction;
        copy.externalFormat = externalFormat;
        return copy;
    }
    bool YCbCrVkDescriptor::operator==(const YCbCrVkDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            vkFormat,
            vkYCbCrModel,
            vkYCbCrRange,
            vkComponentSwizzleRed,
            vkComponentSwizzleGreen,
            vkComponentSwizzleBlue,
            vkComponentSwizzleAlpha,
            vkXChromaOffset,
            vkYChromaOffset,
            vkChromaFilter,
            forceExplicitReconstruction,
            externalFormat
        ) == std::tie(
            rhs.vkFormat,
            rhs.vkYCbCrModel,
            rhs.vkYCbCrRange,
            rhs.vkComponentSwizzleRed,
            rhs.vkComponentSwizzleGreen,
            rhs.vkComponentSwizzleBlue,
            rhs.vkComponentSwizzleAlpha,
            rhs.vkXChromaOffset,
            rhs.vkYChromaOffset,
            rhs.vkChromaFilter,
            rhs.forceExplicitReconstruction,
            rhs.externalFormat
        );
    }


    static_assert(sizeof(AdapterPropertiesMemoryHeaps) == sizeof(WGPUAdapterPropertiesMemoryHeaps), "sizeof mismatch for AdapterPropertiesMemoryHeaps");
    static_assert(alignof(AdapterPropertiesMemoryHeaps) == alignof(WGPUAdapterPropertiesMemoryHeaps), "alignof mismatch for AdapterPropertiesMemoryHeaps");

    static_assert(offsetof(AdapterPropertiesMemoryHeaps, nextInChain) == offsetof(WGPUAdapterPropertiesMemoryHeaps, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for AdapterPropertiesMemoryHeaps::nextInChain");
    static_assert(offsetof(AdapterPropertiesMemoryHeaps, sType) == offsetof(WGPUAdapterPropertiesMemoryHeaps, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for AdapterPropertiesMemoryHeaps::sType");
    static_assert(offsetof(AdapterPropertiesMemoryHeaps, heapCount) == offsetof(WGPUAdapterPropertiesMemoryHeaps, heapCount),
                 "offsetof mismatch for AdapterPropertiesMemoryHeaps::heapCount");
    static_assert(offsetof(AdapterPropertiesMemoryHeaps, heapInfo) == offsetof(WGPUAdapterPropertiesMemoryHeaps, heapInfo),
                 "offsetof mismatch for AdapterPropertiesMemoryHeaps::heapInfo");

    bool AdapterPropertiesMemoryHeaps::operator==(const AdapterPropertiesMemoryHeaps& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            heapCount,
            heapInfo
        ) == std::tie(
            rhs.heapCount,
            rhs.heapInfo
        );
    }


    static_assert(sizeof(AdapterPropertiesSubgroupMatrixConfigs) == sizeof(WGPUAdapterPropertiesSubgroupMatrixConfigs), "sizeof mismatch for AdapterPropertiesSubgroupMatrixConfigs");
    static_assert(alignof(AdapterPropertiesSubgroupMatrixConfigs) == alignof(WGPUAdapterPropertiesSubgroupMatrixConfigs), "alignof mismatch for AdapterPropertiesSubgroupMatrixConfigs");

    static_assert(offsetof(AdapterPropertiesSubgroupMatrixConfigs, nextInChain) == offsetof(WGPUAdapterPropertiesSubgroupMatrixConfigs, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for AdapterPropertiesSubgroupMatrixConfigs::nextInChain");
    static_assert(offsetof(AdapterPropertiesSubgroupMatrixConfigs, sType) == offsetof(WGPUAdapterPropertiesSubgroupMatrixConfigs, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for AdapterPropertiesSubgroupMatrixConfigs::sType");
    static_assert(offsetof(AdapterPropertiesSubgroupMatrixConfigs, configCount) == offsetof(WGPUAdapterPropertiesSubgroupMatrixConfigs, configCount),
                 "offsetof mismatch for AdapterPropertiesSubgroupMatrixConfigs::configCount");
    static_assert(offsetof(AdapterPropertiesSubgroupMatrixConfigs, configs) == offsetof(WGPUAdapterPropertiesSubgroupMatrixConfigs, configs),
                 "offsetof mismatch for AdapterPropertiesSubgroupMatrixConfigs::configs");

    bool AdapterPropertiesSubgroupMatrixConfigs::operator==(const AdapterPropertiesSubgroupMatrixConfigs& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            configCount,
            configs
        ) == std::tie(
            rhs.configCount,
            rhs.configs
        );
    }


    static_assert(sizeof(AHardwareBufferProperties) == sizeof(WGPUAHardwareBufferProperties), "sizeof mismatch for AHardwareBufferProperties");
    static_assert(alignof(AHardwareBufferProperties) == alignof(WGPUAHardwareBufferProperties), "alignof mismatch for AHardwareBufferProperties");

    static_assert(offsetof(AHardwareBufferProperties, yCbCrInfo) == offsetof(WGPUAHardwareBufferProperties, yCbCrInfo),
                 "offsetof mismatch for AHardwareBufferProperties::yCbCrInfo");

    AHardwareBufferProperties AHardwareBufferProperties::WithTrivialFrontendDefaults() const {
        AHardwareBufferProperties copy;
        copy.yCbCrInfo = yCbCrInfo.WithTrivialFrontendDefaults();
        return copy;
    }
    bool AHardwareBufferProperties::operator==(const AHardwareBufferProperties& rhs) const {
        return  std::tie(
            yCbCrInfo
        ) == std::tie(
            rhs.yCbCrInfo
        );
    }


    static_assert(sizeof(BindGroupEntry) == sizeof(WGPUBindGroupEntry), "sizeof mismatch for BindGroupEntry");
    static_assert(alignof(BindGroupEntry) == alignof(WGPUBindGroupEntry), "alignof mismatch for BindGroupEntry");

    static_assert(offsetof(BindGroupEntry, nextInChain) == offsetof(WGPUBindGroupEntry, nextInChain),
            "offsetof mismatch for BindGroupEntry::nextInChain");
    static_assert(offsetof(BindGroupEntry, binding) == offsetof(WGPUBindGroupEntry, binding),
                 "offsetof mismatch for BindGroupEntry::binding");
    static_assert(offsetof(BindGroupEntry, buffer) == offsetof(WGPUBindGroupEntry, buffer),
                 "offsetof mismatch for BindGroupEntry::buffer");
    static_assert(offsetof(BindGroupEntry, offset) == offsetof(WGPUBindGroupEntry, offset),
                 "offsetof mismatch for BindGroupEntry::offset");
    static_assert(offsetof(BindGroupEntry, size) == offsetof(WGPUBindGroupEntry, size),
                 "offsetof mismatch for BindGroupEntry::size");
    static_assert(offsetof(BindGroupEntry, sampler) == offsetof(WGPUBindGroupEntry, sampler),
                 "offsetof mismatch for BindGroupEntry::sampler");
    static_assert(offsetof(BindGroupEntry, textureView) == offsetof(WGPUBindGroupEntry, textureView),
                 "offsetof mismatch for BindGroupEntry::textureView");

    bool BindGroupEntry::operator==(const BindGroupEntry& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            binding,
            buffer,
            offset,
            size,
            sampler,
            textureView
        ) == std::tie(
            rhs.binding,
            rhs.buffer,
            rhs.offset,
            rhs.size,
            rhs.sampler,
            rhs.textureView
        );
    }


    static_assert(sizeof(BindGroupLayoutEntry) == sizeof(WGPUBindGroupLayoutEntry), "sizeof mismatch for BindGroupLayoutEntry");
    static_assert(alignof(BindGroupLayoutEntry) == alignof(WGPUBindGroupLayoutEntry), "alignof mismatch for BindGroupLayoutEntry");

    static_assert(offsetof(BindGroupLayoutEntry, nextInChain) == offsetof(WGPUBindGroupLayoutEntry, nextInChain),
            "offsetof mismatch for BindGroupLayoutEntry::nextInChain");
    static_assert(offsetof(BindGroupLayoutEntry, binding) == offsetof(WGPUBindGroupLayoutEntry, binding),
                 "offsetof mismatch for BindGroupLayoutEntry::binding");
    static_assert(offsetof(BindGroupLayoutEntry, visibility) == offsetof(WGPUBindGroupLayoutEntry, visibility),
                 "offsetof mismatch for BindGroupLayoutEntry::visibility");
    static_assert(offsetof(BindGroupLayoutEntry, bindingArraySize) == offsetof(WGPUBindGroupLayoutEntry, bindingArraySize),
                 "offsetof mismatch for BindGroupLayoutEntry::bindingArraySize");
    static_assert(offsetof(BindGroupLayoutEntry, buffer) == offsetof(WGPUBindGroupLayoutEntry, buffer),
                 "offsetof mismatch for BindGroupLayoutEntry::buffer");
    static_assert(offsetof(BindGroupLayoutEntry, sampler) == offsetof(WGPUBindGroupLayoutEntry, sampler),
                 "offsetof mismatch for BindGroupLayoutEntry::sampler");
    static_assert(offsetof(BindGroupLayoutEntry, texture) == offsetof(WGPUBindGroupLayoutEntry, texture),
                 "offsetof mismatch for BindGroupLayoutEntry::texture");
    static_assert(offsetof(BindGroupLayoutEntry, storageTexture) == offsetof(WGPUBindGroupLayoutEntry, storageTexture),
                 "offsetof mismatch for BindGroupLayoutEntry::storageTexture");

    BindGroupLayoutEntry BindGroupLayoutEntry::WithTrivialFrontendDefaults() const {
        BindGroupLayoutEntry copy;
        copy.nextInChain = nextInChain;
        copy.binding = binding;
        copy.visibility = visibility;
        copy.bindingArraySize = bindingArraySize;
        copy.buffer = buffer.WithTrivialFrontendDefaults();
        copy.sampler = sampler.WithTrivialFrontendDefaults();
        copy.texture = texture.WithTrivialFrontendDefaults();
        copy.storageTexture = storageTexture.WithTrivialFrontendDefaults();
        return copy;
    }
    bool BindGroupLayoutEntry::operator==(const BindGroupLayoutEntry& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            binding,
            visibility,
            bindingArraySize,
            buffer,
            sampler,
            texture,
            storageTexture
        ) == std::tie(
            rhs.binding,
            rhs.visibility,
            rhs.bindingArraySize,
            rhs.buffer,
            rhs.sampler,
            rhs.texture,
            rhs.storageTexture
        );
    }


    static_assert(sizeof(BlendState) == sizeof(WGPUBlendState), "sizeof mismatch for BlendState");
    static_assert(alignof(BlendState) == alignof(WGPUBlendState), "alignof mismatch for BlendState");

    static_assert(offsetof(BlendState, color) == offsetof(WGPUBlendState, color),
                 "offsetof mismatch for BlendState::color");
    static_assert(offsetof(BlendState, alpha) == offsetof(WGPUBlendState, alpha),
                 "offsetof mismatch for BlendState::alpha");

    BlendState BlendState::WithTrivialFrontendDefaults() const {
        BlendState copy;
        copy.color = color.WithTrivialFrontendDefaults();
        copy.alpha = alpha.WithTrivialFrontendDefaults();
        return copy;
    }
    bool BlendState::operator==(const BlendState& rhs) const {
        return  std::tie(
            color,
            alpha
        ) == std::tie(
            rhs.color,
            rhs.alpha
        );
    }


    static_assert(sizeof(BufferDescriptor) == sizeof(WGPUBufferDescriptor), "sizeof mismatch for BufferDescriptor");
    static_assert(alignof(BufferDescriptor) == alignof(WGPUBufferDescriptor), "alignof mismatch for BufferDescriptor");

    static_assert(offsetof(BufferDescriptor, nextInChain) == offsetof(WGPUBufferDescriptor, nextInChain),
            "offsetof mismatch for BufferDescriptor::nextInChain");
    static_assert(offsetof(BufferDescriptor, label) == offsetof(WGPUBufferDescriptor, label),
                 "offsetof mismatch for BufferDescriptor::label");
    static_assert(offsetof(BufferDescriptor, usage) == offsetof(WGPUBufferDescriptor, usage),
                 "offsetof mismatch for BufferDescriptor::usage");
    static_assert(offsetof(BufferDescriptor, size) == offsetof(WGPUBufferDescriptor, size),
                 "offsetof mismatch for BufferDescriptor::size");
    static_assert(offsetof(BufferDescriptor, mappedAtCreation) == offsetof(WGPUBufferDescriptor, mappedAtCreation),
                 "offsetof mismatch for BufferDescriptor::mappedAtCreation");

    bool BufferDescriptor::operator==(const BufferDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            usage,
            size,
            mappedAtCreation
        ) == std::tie(
            rhs.label,
            rhs.usage,
            rhs.size,
            rhs.mappedAtCreation
        );
    }


    static_assert(sizeof(CommandEncoderDescriptor) == sizeof(WGPUCommandEncoderDescriptor), "sizeof mismatch for CommandEncoderDescriptor");
    static_assert(alignof(CommandEncoderDescriptor) == alignof(WGPUCommandEncoderDescriptor), "alignof mismatch for CommandEncoderDescriptor");

    static_assert(offsetof(CommandEncoderDescriptor, nextInChain) == offsetof(WGPUCommandEncoderDescriptor, nextInChain),
            "offsetof mismatch for CommandEncoderDescriptor::nextInChain");
    static_assert(offsetof(CommandEncoderDescriptor, label) == offsetof(WGPUCommandEncoderDescriptor, label),
                 "offsetof mismatch for CommandEncoderDescriptor::label");

    bool CommandEncoderDescriptor::operator==(const CommandEncoderDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(CompilationMessage) == sizeof(WGPUCompilationMessage), "sizeof mismatch for CompilationMessage");
    static_assert(alignof(CompilationMessage) == alignof(WGPUCompilationMessage), "alignof mismatch for CompilationMessage");

    static_assert(offsetof(CompilationMessage, nextInChain) == offsetof(WGPUCompilationMessage, nextInChain),
            "offsetof mismatch for CompilationMessage::nextInChain");
    static_assert(offsetof(CompilationMessage, message) == offsetof(WGPUCompilationMessage, message),
                 "offsetof mismatch for CompilationMessage::message");
    static_assert(offsetof(CompilationMessage, type) == offsetof(WGPUCompilationMessage, type),
                 "offsetof mismatch for CompilationMessage::type");
    static_assert(offsetof(CompilationMessage, lineNum) == offsetof(WGPUCompilationMessage, lineNum),
                 "offsetof mismatch for CompilationMessage::lineNum");
    static_assert(offsetof(CompilationMessage, linePos) == offsetof(WGPUCompilationMessage, linePos),
                 "offsetof mismatch for CompilationMessage::linePos");
    static_assert(offsetof(CompilationMessage, offset) == offsetof(WGPUCompilationMessage, offset),
                 "offsetof mismatch for CompilationMessage::offset");
    static_assert(offsetof(CompilationMessage, length) == offsetof(WGPUCompilationMessage, length),
                 "offsetof mismatch for CompilationMessage::length");

    bool CompilationMessage::operator==(const CompilationMessage& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            message,
            type,
            lineNum,
            linePos,
            offset,
            length
        ) == std::tie(
            rhs.message,
            rhs.type,
            rhs.lineNum,
            rhs.linePos,
            rhs.offset,
            rhs.length
        );
    }


    static_assert(sizeof(ComputePassDescriptor) == sizeof(WGPUComputePassDescriptor), "sizeof mismatch for ComputePassDescriptor");
    static_assert(alignof(ComputePassDescriptor) == alignof(WGPUComputePassDescriptor), "alignof mismatch for ComputePassDescriptor");

    static_assert(offsetof(ComputePassDescriptor, nextInChain) == offsetof(WGPUComputePassDescriptor, nextInChain),
            "offsetof mismatch for ComputePassDescriptor::nextInChain");
    static_assert(offsetof(ComputePassDescriptor, label) == offsetof(WGPUComputePassDescriptor, label),
                 "offsetof mismatch for ComputePassDescriptor::label");
    static_assert(offsetof(ComputePassDescriptor, timestampWrites) == offsetof(WGPUComputePassDescriptor, timestampWrites),
                 "offsetof mismatch for ComputePassDescriptor::timestampWrites");

    bool ComputePassDescriptor::operator==(const ComputePassDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            timestampWrites
        ) == std::tie(
            rhs.label,
            rhs.timestampWrites
        );
    }


    static_assert(sizeof(ComputeState) == sizeof(WGPUComputeState), "sizeof mismatch for ComputeState");
    static_assert(alignof(ComputeState) == alignof(WGPUComputeState), "alignof mismatch for ComputeState");

    static_assert(offsetof(ComputeState, nextInChain) == offsetof(WGPUComputeState, nextInChain),
            "offsetof mismatch for ComputeState::nextInChain");
    static_assert(offsetof(ComputeState, module) == offsetof(WGPUComputeState, module),
                 "offsetof mismatch for ComputeState::module");
    static_assert(offsetof(ComputeState, entryPoint) == offsetof(WGPUComputeState, entryPoint),
                 "offsetof mismatch for ComputeState::entryPoint");
    static_assert(offsetof(ComputeState, constantCount) == offsetof(WGPUComputeState, constantCount),
                 "offsetof mismatch for ComputeState::constantCount");
    static_assert(offsetof(ComputeState, constants) == offsetof(WGPUComputeState, constants),
                 "offsetof mismatch for ComputeState::constants");

    bool ComputeState::operator==(const ComputeState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            module,
            entryPoint,
            constantCount,
            constants
        ) == std::tie(
            rhs.module,
            rhs.entryPoint,
            rhs.constantCount,
            rhs.constants
        );
    }


    static_assert(sizeof(DawnDrmFormatCapabilities) == sizeof(WGPUDawnDrmFormatCapabilities), "sizeof mismatch for DawnDrmFormatCapabilities");
    static_assert(alignof(DawnDrmFormatCapabilities) == alignof(WGPUDawnDrmFormatCapabilities), "alignof mismatch for DawnDrmFormatCapabilities");

    static_assert(offsetof(DawnDrmFormatCapabilities, nextInChain) == offsetof(WGPUDawnDrmFormatCapabilities, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for DawnDrmFormatCapabilities::nextInChain");
    static_assert(offsetof(DawnDrmFormatCapabilities, sType) == offsetof(WGPUDawnDrmFormatCapabilities, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for DawnDrmFormatCapabilities::sType");
    static_assert(offsetof(DawnDrmFormatCapabilities, propertiesCount) == offsetof(WGPUDawnDrmFormatCapabilities, propertiesCount),
                 "offsetof mismatch for DawnDrmFormatCapabilities::propertiesCount");
    static_assert(offsetof(DawnDrmFormatCapabilities, properties) == offsetof(WGPUDawnDrmFormatCapabilities, properties),
                 "offsetof mismatch for DawnDrmFormatCapabilities::properties");

    bool DawnDrmFormatCapabilities::operator==(const DawnDrmFormatCapabilities& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            propertiesCount,
            properties
        ) == std::tie(
            rhs.propertiesCount,
            rhs.properties
        );
    }


    static_assert(sizeof(DepthStencilState) == sizeof(WGPUDepthStencilState), "sizeof mismatch for DepthStencilState");
    static_assert(alignof(DepthStencilState) == alignof(WGPUDepthStencilState), "alignof mismatch for DepthStencilState");

    static_assert(offsetof(DepthStencilState, nextInChain) == offsetof(WGPUDepthStencilState, nextInChain),
            "offsetof mismatch for DepthStencilState::nextInChain");
    static_assert(offsetof(DepthStencilState, format) == offsetof(WGPUDepthStencilState, format),
                 "offsetof mismatch for DepthStencilState::format");
    static_assert(offsetof(DepthStencilState, depthWriteEnabled) == offsetof(WGPUDepthStencilState, depthWriteEnabled),
                 "offsetof mismatch for DepthStencilState::depthWriteEnabled");
    static_assert(offsetof(DepthStencilState, depthCompare) == offsetof(WGPUDepthStencilState, depthCompare),
                 "offsetof mismatch for DepthStencilState::depthCompare");
    static_assert(offsetof(DepthStencilState, stencilFront) == offsetof(WGPUDepthStencilState, stencilFront),
                 "offsetof mismatch for DepthStencilState::stencilFront");
    static_assert(offsetof(DepthStencilState, stencilBack) == offsetof(WGPUDepthStencilState, stencilBack),
                 "offsetof mismatch for DepthStencilState::stencilBack");
    static_assert(offsetof(DepthStencilState, stencilReadMask) == offsetof(WGPUDepthStencilState, stencilReadMask),
                 "offsetof mismatch for DepthStencilState::stencilReadMask");
    static_assert(offsetof(DepthStencilState, stencilWriteMask) == offsetof(WGPUDepthStencilState, stencilWriteMask),
                 "offsetof mismatch for DepthStencilState::stencilWriteMask");
    static_assert(offsetof(DepthStencilState, depthBias) == offsetof(WGPUDepthStencilState, depthBias),
                 "offsetof mismatch for DepthStencilState::depthBias");
    static_assert(offsetof(DepthStencilState, depthBiasSlopeScale) == offsetof(WGPUDepthStencilState, depthBiasSlopeScale),
                 "offsetof mismatch for DepthStencilState::depthBiasSlopeScale");
    static_assert(offsetof(DepthStencilState, depthBiasClamp) == offsetof(WGPUDepthStencilState, depthBiasClamp),
                 "offsetof mismatch for DepthStencilState::depthBiasClamp");

    DepthStencilState DepthStencilState::WithTrivialFrontendDefaults() const {
        DepthStencilState copy;
        copy.nextInChain = nextInChain;
        copy.format = format;
        copy.depthWriteEnabled = depthWriteEnabled;
        copy.depthCompare = depthCompare;
        copy.stencilFront = stencilFront.WithTrivialFrontendDefaults();
        copy.stencilBack = stencilBack.WithTrivialFrontendDefaults();
        copy.stencilReadMask = stencilReadMask;
        copy.stencilWriteMask = stencilWriteMask;
        copy.depthBias = depthBias;
        copy.depthBiasSlopeScale = depthBiasSlopeScale;
        copy.depthBiasClamp = depthBiasClamp;
        return copy;
    }
    bool DepthStencilState::operator==(const DepthStencilState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            format,
            depthWriteEnabled,
            depthCompare,
            stencilFront,
            stencilBack,
            stencilReadMask,
            stencilWriteMask,
            depthBias,
            depthBiasSlopeScale,
            depthBiasClamp
        ) == std::tie(
            rhs.format,
            rhs.depthWriteEnabled,
            rhs.depthCompare,
            rhs.stencilFront,
            rhs.stencilBack,
            rhs.stencilReadMask,
            rhs.stencilWriteMask,
            rhs.depthBias,
            rhs.depthBiasSlopeScale,
            rhs.depthBiasClamp
        );
    }


    static_assert(sizeof(ExternalTextureDescriptor) == sizeof(WGPUExternalTextureDescriptor), "sizeof mismatch for ExternalTextureDescriptor");
    static_assert(alignof(ExternalTextureDescriptor) == alignof(WGPUExternalTextureDescriptor), "alignof mismatch for ExternalTextureDescriptor");

    static_assert(offsetof(ExternalTextureDescriptor, nextInChain) == offsetof(WGPUExternalTextureDescriptor, nextInChain),
            "offsetof mismatch for ExternalTextureDescriptor::nextInChain");
    static_assert(offsetof(ExternalTextureDescriptor, label) == offsetof(WGPUExternalTextureDescriptor, label),
                 "offsetof mismatch for ExternalTextureDescriptor::label");
    static_assert(offsetof(ExternalTextureDescriptor, plane0) == offsetof(WGPUExternalTextureDescriptor, plane0),
                 "offsetof mismatch for ExternalTextureDescriptor::plane0");
    static_assert(offsetof(ExternalTextureDescriptor, plane1) == offsetof(WGPUExternalTextureDescriptor, plane1),
                 "offsetof mismatch for ExternalTextureDescriptor::plane1");
    static_assert(offsetof(ExternalTextureDescriptor, cropOrigin) == offsetof(WGPUExternalTextureDescriptor, cropOrigin),
                 "offsetof mismatch for ExternalTextureDescriptor::cropOrigin");
    static_assert(offsetof(ExternalTextureDescriptor, cropSize) == offsetof(WGPUExternalTextureDescriptor, cropSize),
                 "offsetof mismatch for ExternalTextureDescriptor::cropSize");
    static_assert(offsetof(ExternalTextureDescriptor, apparentSize) == offsetof(WGPUExternalTextureDescriptor, apparentSize),
                 "offsetof mismatch for ExternalTextureDescriptor::apparentSize");
    static_assert(offsetof(ExternalTextureDescriptor, doYuvToRgbConversionOnly) == offsetof(WGPUExternalTextureDescriptor, doYuvToRgbConversionOnly),
                 "offsetof mismatch for ExternalTextureDescriptor::doYuvToRgbConversionOnly");
    static_assert(offsetof(ExternalTextureDescriptor, yuvToRgbConversionMatrix) == offsetof(WGPUExternalTextureDescriptor, yuvToRgbConversionMatrix),
                 "offsetof mismatch for ExternalTextureDescriptor::yuvToRgbConversionMatrix");
    static_assert(offsetof(ExternalTextureDescriptor, srcTransferFunctionParameters) == offsetof(WGPUExternalTextureDescriptor, srcTransferFunctionParameters),
                 "offsetof mismatch for ExternalTextureDescriptor::srcTransferFunctionParameters");
    static_assert(offsetof(ExternalTextureDescriptor, dstTransferFunctionParameters) == offsetof(WGPUExternalTextureDescriptor, dstTransferFunctionParameters),
                 "offsetof mismatch for ExternalTextureDescriptor::dstTransferFunctionParameters");
    static_assert(offsetof(ExternalTextureDescriptor, gamutConversionMatrix) == offsetof(WGPUExternalTextureDescriptor, gamutConversionMatrix),
                 "offsetof mismatch for ExternalTextureDescriptor::gamutConversionMatrix");
    static_assert(offsetof(ExternalTextureDescriptor, mirrored) == offsetof(WGPUExternalTextureDescriptor, mirrored),
                 "offsetof mismatch for ExternalTextureDescriptor::mirrored");
    static_assert(offsetof(ExternalTextureDescriptor, rotation) == offsetof(WGPUExternalTextureDescriptor, rotation),
                 "offsetof mismatch for ExternalTextureDescriptor::rotation");

    bool ExternalTextureDescriptor::operator==(const ExternalTextureDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            plane0,
            plane1,
            cropOrigin,
            cropSize,
            apparentSize,
            doYuvToRgbConversionOnly,
            yuvToRgbConversionMatrix,
            srcTransferFunctionParameters,
            dstTransferFunctionParameters,
            gamutConversionMatrix,
            mirrored,
            rotation
        ) == std::tie(
            rhs.label,
            rhs.plane0,
            rhs.plane1,
            rhs.cropOrigin,
            rhs.cropSize,
            rhs.apparentSize,
            rhs.doYuvToRgbConversionOnly,
            rhs.yuvToRgbConversionMatrix,
            rhs.srcTransferFunctionParameters,
            rhs.dstTransferFunctionParameters,
            rhs.gamutConversionMatrix,
            rhs.mirrored,
            rhs.rotation
        );
    }


    static_assert(sizeof(FutureWaitInfo) == sizeof(WGPUFutureWaitInfo), "sizeof mismatch for FutureWaitInfo");
    static_assert(alignof(FutureWaitInfo) == alignof(WGPUFutureWaitInfo), "alignof mismatch for FutureWaitInfo");

    static_assert(offsetof(FutureWaitInfo, future) == offsetof(WGPUFutureWaitInfo, future),
                 "offsetof mismatch for FutureWaitInfo::future");
    static_assert(offsetof(FutureWaitInfo, completed) == offsetof(WGPUFutureWaitInfo, completed),
                 "offsetof mismatch for FutureWaitInfo::completed");

    bool FutureWaitInfo::operator==(const FutureWaitInfo& rhs) const {
        return  std::tie(
            future,
            completed
        ) == std::tie(
            rhs.future,
            rhs.completed
        );
    }


    static_assert(sizeof(ImageCopyExternalTexture) == sizeof(WGPUImageCopyExternalTexture), "sizeof mismatch for ImageCopyExternalTexture");
    static_assert(alignof(ImageCopyExternalTexture) == alignof(WGPUImageCopyExternalTexture), "alignof mismatch for ImageCopyExternalTexture");

    static_assert(offsetof(ImageCopyExternalTexture, nextInChain) == offsetof(WGPUImageCopyExternalTexture, nextInChain),
            "offsetof mismatch for ImageCopyExternalTexture::nextInChain");
    static_assert(offsetof(ImageCopyExternalTexture, externalTexture) == offsetof(WGPUImageCopyExternalTexture, externalTexture),
                 "offsetof mismatch for ImageCopyExternalTexture::externalTexture");
    static_assert(offsetof(ImageCopyExternalTexture, origin) == offsetof(WGPUImageCopyExternalTexture, origin),
                 "offsetof mismatch for ImageCopyExternalTexture::origin");
    static_assert(offsetof(ImageCopyExternalTexture, naturalSize) == offsetof(WGPUImageCopyExternalTexture, naturalSize),
                 "offsetof mismatch for ImageCopyExternalTexture::naturalSize");

    bool ImageCopyExternalTexture::operator==(const ImageCopyExternalTexture& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            externalTexture,
            origin,
            naturalSize
        ) == std::tie(
            rhs.externalTexture,
            rhs.origin,
            rhs.naturalSize
        );
    }


    static_assert(sizeof(InstanceDescriptor) == sizeof(WGPUInstanceDescriptor), "sizeof mismatch for InstanceDescriptor");
    static_assert(alignof(InstanceDescriptor) == alignof(WGPUInstanceDescriptor), "alignof mismatch for InstanceDescriptor");

    static_assert(offsetof(InstanceDescriptor, nextInChain) == offsetof(WGPUInstanceDescriptor, nextInChain),
            "offsetof mismatch for InstanceDescriptor::nextInChain");
    static_assert(offsetof(InstanceDescriptor, requiredFeatureCount) == offsetof(WGPUInstanceDescriptor, requiredFeatureCount),
                 "offsetof mismatch for InstanceDescriptor::requiredFeatureCount");
    static_assert(offsetof(InstanceDescriptor, requiredFeatures) == offsetof(WGPUInstanceDescriptor, requiredFeatures),
                 "offsetof mismatch for InstanceDescriptor::requiredFeatures");
    static_assert(offsetof(InstanceDescriptor, requiredLimits) == offsetof(WGPUInstanceDescriptor, requiredLimits),
                 "offsetof mismatch for InstanceDescriptor::requiredLimits");

    bool InstanceDescriptor::operator==(const InstanceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            requiredFeatureCount,
            requiredFeatures,
            requiredLimits
        ) == std::tie(
            rhs.requiredFeatureCount,
            rhs.requiredFeatures,
            rhs.requiredLimits
        );
    }


    static_assert(sizeof(Limits) == sizeof(WGPULimits), "sizeof mismatch for Limits");
    static_assert(alignof(Limits) == alignof(WGPULimits), "alignof mismatch for Limits");

    static_assert(offsetof(Limits, nextInChain) == offsetof(WGPULimits, nextInChain),
            "offsetof mismatch for Limits::nextInChain");
    static_assert(offsetof(Limits, maxTextureDimension1D) == offsetof(WGPULimits, maxTextureDimension1D),
                 "offsetof mismatch for Limits::maxTextureDimension1D");
    static_assert(offsetof(Limits, maxTextureDimension2D) == offsetof(WGPULimits, maxTextureDimension2D),
                 "offsetof mismatch for Limits::maxTextureDimension2D");
    static_assert(offsetof(Limits, maxTextureDimension3D) == offsetof(WGPULimits, maxTextureDimension3D),
                 "offsetof mismatch for Limits::maxTextureDimension3D");
    static_assert(offsetof(Limits, maxTextureArrayLayers) == offsetof(WGPULimits, maxTextureArrayLayers),
                 "offsetof mismatch for Limits::maxTextureArrayLayers");
    static_assert(offsetof(Limits, maxBindGroups) == offsetof(WGPULimits, maxBindGroups),
                 "offsetof mismatch for Limits::maxBindGroups");
    static_assert(offsetof(Limits, maxBindGroupsPlusVertexBuffers) == offsetof(WGPULimits, maxBindGroupsPlusVertexBuffers),
                 "offsetof mismatch for Limits::maxBindGroupsPlusVertexBuffers");
    static_assert(offsetof(Limits, maxBindingsPerBindGroup) == offsetof(WGPULimits, maxBindingsPerBindGroup),
                 "offsetof mismatch for Limits::maxBindingsPerBindGroup");
    static_assert(offsetof(Limits, maxDynamicUniformBuffersPerPipelineLayout) == offsetof(WGPULimits, maxDynamicUniformBuffersPerPipelineLayout),
                 "offsetof mismatch for Limits::maxDynamicUniformBuffersPerPipelineLayout");
    static_assert(offsetof(Limits, maxDynamicStorageBuffersPerPipelineLayout) == offsetof(WGPULimits, maxDynamicStorageBuffersPerPipelineLayout),
                 "offsetof mismatch for Limits::maxDynamicStorageBuffersPerPipelineLayout");
    static_assert(offsetof(Limits, maxSampledTexturesPerShaderStage) == offsetof(WGPULimits, maxSampledTexturesPerShaderStage),
                 "offsetof mismatch for Limits::maxSampledTexturesPerShaderStage");
    static_assert(offsetof(Limits, maxSamplersPerShaderStage) == offsetof(WGPULimits, maxSamplersPerShaderStage),
                 "offsetof mismatch for Limits::maxSamplersPerShaderStage");
    static_assert(offsetof(Limits, maxStorageBuffersPerShaderStage) == offsetof(WGPULimits, maxStorageBuffersPerShaderStage),
                 "offsetof mismatch for Limits::maxStorageBuffersPerShaderStage");
    static_assert(offsetof(Limits, maxStorageTexturesPerShaderStage) == offsetof(WGPULimits, maxStorageTexturesPerShaderStage),
                 "offsetof mismatch for Limits::maxStorageTexturesPerShaderStage");
    static_assert(offsetof(Limits, maxUniformBuffersPerShaderStage) == offsetof(WGPULimits, maxUniformBuffersPerShaderStage),
                 "offsetof mismatch for Limits::maxUniformBuffersPerShaderStage");
    static_assert(offsetof(Limits, maxUniformBufferBindingSize) == offsetof(WGPULimits, maxUniformBufferBindingSize),
                 "offsetof mismatch for Limits::maxUniformBufferBindingSize");
    static_assert(offsetof(Limits, maxStorageBufferBindingSize) == offsetof(WGPULimits, maxStorageBufferBindingSize),
                 "offsetof mismatch for Limits::maxStorageBufferBindingSize");
    static_assert(offsetof(Limits, minUniformBufferOffsetAlignment) == offsetof(WGPULimits, minUniformBufferOffsetAlignment),
                 "offsetof mismatch for Limits::minUniformBufferOffsetAlignment");
    static_assert(offsetof(Limits, minStorageBufferOffsetAlignment) == offsetof(WGPULimits, minStorageBufferOffsetAlignment),
                 "offsetof mismatch for Limits::minStorageBufferOffsetAlignment");
    static_assert(offsetof(Limits, maxVertexBuffers) == offsetof(WGPULimits, maxVertexBuffers),
                 "offsetof mismatch for Limits::maxVertexBuffers");
    static_assert(offsetof(Limits, maxBufferSize) == offsetof(WGPULimits, maxBufferSize),
                 "offsetof mismatch for Limits::maxBufferSize");
    static_assert(offsetof(Limits, maxVertexAttributes) == offsetof(WGPULimits, maxVertexAttributes),
                 "offsetof mismatch for Limits::maxVertexAttributes");
    static_assert(offsetof(Limits, maxVertexBufferArrayStride) == offsetof(WGPULimits, maxVertexBufferArrayStride),
                 "offsetof mismatch for Limits::maxVertexBufferArrayStride");
    static_assert(offsetof(Limits, maxInterStageShaderVariables) == offsetof(WGPULimits, maxInterStageShaderVariables),
                 "offsetof mismatch for Limits::maxInterStageShaderVariables");
    static_assert(offsetof(Limits, maxColorAttachments) == offsetof(WGPULimits, maxColorAttachments),
                 "offsetof mismatch for Limits::maxColorAttachments");
    static_assert(offsetof(Limits, maxColorAttachmentBytesPerSample) == offsetof(WGPULimits, maxColorAttachmentBytesPerSample),
                 "offsetof mismatch for Limits::maxColorAttachmentBytesPerSample");
    static_assert(offsetof(Limits, maxComputeWorkgroupStorageSize) == offsetof(WGPULimits, maxComputeWorkgroupStorageSize),
                 "offsetof mismatch for Limits::maxComputeWorkgroupStorageSize");
    static_assert(offsetof(Limits, maxComputeInvocationsPerWorkgroup) == offsetof(WGPULimits, maxComputeInvocationsPerWorkgroup),
                 "offsetof mismatch for Limits::maxComputeInvocationsPerWorkgroup");
    static_assert(offsetof(Limits, maxComputeWorkgroupSizeX) == offsetof(WGPULimits, maxComputeWorkgroupSizeX),
                 "offsetof mismatch for Limits::maxComputeWorkgroupSizeX");
    static_assert(offsetof(Limits, maxComputeWorkgroupSizeY) == offsetof(WGPULimits, maxComputeWorkgroupSizeY),
                 "offsetof mismatch for Limits::maxComputeWorkgroupSizeY");
    static_assert(offsetof(Limits, maxComputeWorkgroupSizeZ) == offsetof(WGPULimits, maxComputeWorkgroupSizeZ),
                 "offsetof mismatch for Limits::maxComputeWorkgroupSizeZ");
    static_assert(offsetof(Limits, maxComputeWorkgroupsPerDimension) == offsetof(WGPULimits, maxComputeWorkgroupsPerDimension),
                 "offsetof mismatch for Limits::maxComputeWorkgroupsPerDimension");
    static_assert(offsetof(Limits, maxImmediateSize) == offsetof(WGPULimits, maxImmediateSize),
                 "offsetof mismatch for Limits::maxImmediateSize");

    bool Limits::operator==(const Limits& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            maxTextureDimension1D,
            maxTextureDimension2D,
            maxTextureDimension3D,
            maxTextureArrayLayers,
            maxBindGroups,
            maxBindGroupsPlusVertexBuffers,
            maxBindingsPerBindGroup,
            maxDynamicUniformBuffersPerPipelineLayout,
            maxDynamicStorageBuffersPerPipelineLayout,
            maxSampledTexturesPerShaderStage,
            maxSamplersPerShaderStage,
            maxStorageBuffersPerShaderStage,
            maxStorageTexturesPerShaderStage,
            maxUniformBuffersPerShaderStage,
            maxUniformBufferBindingSize,
            maxStorageBufferBindingSize,
            minUniformBufferOffsetAlignment,
            minStorageBufferOffsetAlignment,
            maxVertexBuffers,
            maxBufferSize,
            maxVertexAttributes,
            maxVertexBufferArrayStride,
            maxInterStageShaderVariables,
            maxColorAttachments,
            maxColorAttachmentBytesPerSample,
            maxComputeWorkgroupStorageSize,
            maxComputeInvocationsPerWorkgroup,
            maxComputeWorkgroupSizeX,
            maxComputeWorkgroupSizeY,
            maxComputeWorkgroupSizeZ,
            maxComputeWorkgroupsPerDimension,
            maxImmediateSize
        ) == std::tie(
            rhs.maxTextureDimension1D,
            rhs.maxTextureDimension2D,
            rhs.maxTextureDimension3D,
            rhs.maxTextureArrayLayers,
            rhs.maxBindGroups,
            rhs.maxBindGroupsPlusVertexBuffers,
            rhs.maxBindingsPerBindGroup,
            rhs.maxDynamicUniformBuffersPerPipelineLayout,
            rhs.maxDynamicStorageBuffersPerPipelineLayout,
            rhs.maxSampledTexturesPerShaderStage,
            rhs.maxSamplersPerShaderStage,
            rhs.maxStorageBuffersPerShaderStage,
            rhs.maxStorageTexturesPerShaderStage,
            rhs.maxUniformBuffersPerShaderStage,
            rhs.maxUniformBufferBindingSize,
            rhs.maxStorageBufferBindingSize,
            rhs.minUniformBufferOffsetAlignment,
            rhs.minStorageBufferOffsetAlignment,
            rhs.maxVertexBuffers,
            rhs.maxBufferSize,
            rhs.maxVertexAttributes,
            rhs.maxVertexBufferArrayStride,
            rhs.maxInterStageShaderVariables,
            rhs.maxColorAttachments,
            rhs.maxColorAttachmentBytesPerSample,
            rhs.maxComputeWorkgroupStorageSize,
            rhs.maxComputeInvocationsPerWorkgroup,
            rhs.maxComputeWorkgroupSizeX,
            rhs.maxComputeWorkgroupSizeY,
            rhs.maxComputeWorkgroupSizeZ,
            rhs.maxComputeWorkgroupsPerDimension,
            rhs.maxImmediateSize
        );
    }


    static_assert(sizeof(PipelineLayoutPixelLocalStorage) == sizeof(WGPUPipelineLayoutPixelLocalStorage), "sizeof mismatch for PipelineLayoutPixelLocalStorage");
    static_assert(alignof(PipelineLayoutPixelLocalStorage) == alignof(WGPUPipelineLayoutPixelLocalStorage), "alignof mismatch for PipelineLayoutPixelLocalStorage");

    static_assert(offsetof(PipelineLayoutPixelLocalStorage, nextInChain) == offsetof(WGPUPipelineLayoutPixelLocalStorage, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for PipelineLayoutPixelLocalStorage::nextInChain");
    static_assert(offsetof(PipelineLayoutPixelLocalStorage, sType) == offsetof(WGPUPipelineLayoutPixelLocalStorage, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for PipelineLayoutPixelLocalStorage::sType");
    static_assert(offsetof(PipelineLayoutPixelLocalStorage, totalPixelLocalStorageSize) == offsetof(WGPUPipelineLayoutPixelLocalStorage, totalPixelLocalStorageSize),
                 "offsetof mismatch for PipelineLayoutPixelLocalStorage::totalPixelLocalStorageSize");
    static_assert(offsetof(PipelineLayoutPixelLocalStorage, storageAttachmentCount) == offsetof(WGPUPipelineLayoutPixelLocalStorage, storageAttachmentCount),
                 "offsetof mismatch for PipelineLayoutPixelLocalStorage::storageAttachmentCount");
    static_assert(offsetof(PipelineLayoutPixelLocalStorage, storageAttachments) == offsetof(WGPUPipelineLayoutPixelLocalStorage, storageAttachments),
                 "offsetof mismatch for PipelineLayoutPixelLocalStorage::storageAttachments");

    bool PipelineLayoutPixelLocalStorage::operator==(const PipelineLayoutPixelLocalStorage& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            totalPixelLocalStorageSize,
            storageAttachmentCount,
            storageAttachments
        ) == std::tie(
            rhs.totalPixelLocalStorageSize,
            rhs.storageAttachmentCount,
            rhs.storageAttachments
        );
    }


    static_assert(sizeof(RenderPassColorAttachment) == sizeof(WGPURenderPassColorAttachment), "sizeof mismatch for RenderPassColorAttachment");
    static_assert(alignof(RenderPassColorAttachment) == alignof(WGPURenderPassColorAttachment), "alignof mismatch for RenderPassColorAttachment");

    static_assert(offsetof(RenderPassColorAttachment, nextInChain) == offsetof(WGPURenderPassColorAttachment, nextInChain),
            "offsetof mismatch for RenderPassColorAttachment::nextInChain");
    static_assert(offsetof(RenderPassColorAttachment, view) == offsetof(WGPURenderPassColorAttachment, view),
                 "offsetof mismatch for RenderPassColorAttachment::view");
    static_assert(offsetof(RenderPassColorAttachment, depthSlice) == offsetof(WGPURenderPassColorAttachment, depthSlice),
                 "offsetof mismatch for RenderPassColorAttachment::depthSlice");
    static_assert(offsetof(RenderPassColorAttachment, resolveTarget) == offsetof(WGPURenderPassColorAttachment, resolveTarget),
                 "offsetof mismatch for RenderPassColorAttachment::resolveTarget");
    static_assert(offsetof(RenderPassColorAttachment, loadOp) == offsetof(WGPURenderPassColorAttachment, loadOp),
                 "offsetof mismatch for RenderPassColorAttachment::loadOp");
    static_assert(offsetof(RenderPassColorAttachment, storeOp) == offsetof(WGPURenderPassColorAttachment, storeOp),
                 "offsetof mismatch for RenderPassColorAttachment::storeOp");
    static_assert(offsetof(RenderPassColorAttachment, clearValue) == offsetof(WGPURenderPassColorAttachment, clearValue),
                 "offsetof mismatch for RenderPassColorAttachment::clearValue");

    bool RenderPassColorAttachment::operator==(const RenderPassColorAttachment& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            view,
            depthSlice,
            resolveTarget,
            loadOp,
            storeOp,
            clearValue
        ) == std::tie(
            rhs.view,
            rhs.depthSlice,
            rhs.resolveTarget,
            rhs.loadOp,
            rhs.storeOp,
            rhs.clearValue
        );
    }


    static_assert(sizeof(RenderPassStorageAttachment) == sizeof(WGPURenderPassStorageAttachment), "sizeof mismatch for RenderPassStorageAttachment");
    static_assert(alignof(RenderPassStorageAttachment) == alignof(WGPURenderPassStorageAttachment), "alignof mismatch for RenderPassStorageAttachment");

    static_assert(offsetof(RenderPassStorageAttachment, nextInChain) == offsetof(WGPURenderPassStorageAttachment, nextInChain),
            "offsetof mismatch for RenderPassStorageAttachment::nextInChain");
    static_assert(offsetof(RenderPassStorageAttachment, offset) == offsetof(WGPURenderPassStorageAttachment, offset),
                 "offsetof mismatch for RenderPassStorageAttachment::offset");
    static_assert(offsetof(RenderPassStorageAttachment, storage) == offsetof(WGPURenderPassStorageAttachment, storage),
                 "offsetof mismatch for RenderPassStorageAttachment::storage");
    static_assert(offsetof(RenderPassStorageAttachment, loadOp) == offsetof(WGPURenderPassStorageAttachment, loadOp),
                 "offsetof mismatch for RenderPassStorageAttachment::loadOp");
    static_assert(offsetof(RenderPassStorageAttachment, storeOp) == offsetof(WGPURenderPassStorageAttachment, storeOp),
                 "offsetof mismatch for RenderPassStorageAttachment::storeOp");
    static_assert(offsetof(RenderPassStorageAttachment, clearValue) == offsetof(WGPURenderPassStorageAttachment, clearValue),
                 "offsetof mismatch for RenderPassStorageAttachment::clearValue");

    bool RenderPassStorageAttachment::operator==(const RenderPassStorageAttachment& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            offset,
            storage,
            loadOp,
            storeOp,
            clearValue
        ) == std::tie(
            rhs.offset,
            rhs.storage,
            rhs.loadOp,
            rhs.storeOp,
            rhs.clearValue
        );
    }


    static_assert(sizeof(RequestAdapterOptions) == sizeof(WGPURequestAdapterOptions), "sizeof mismatch for RequestAdapterOptions");
    static_assert(alignof(RequestAdapterOptions) == alignof(WGPURequestAdapterOptions), "alignof mismatch for RequestAdapterOptions");

    static_assert(offsetof(RequestAdapterOptions, nextInChain) == offsetof(WGPURequestAdapterOptions, nextInChain),
            "offsetof mismatch for RequestAdapterOptions::nextInChain");
    static_assert(offsetof(RequestAdapterOptions, featureLevel) == offsetof(WGPURequestAdapterOptions, featureLevel),
                 "offsetof mismatch for RequestAdapterOptions::featureLevel");
    static_assert(offsetof(RequestAdapterOptions, powerPreference) == offsetof(WGPURequestAdapterOptions, powerPreference),
                 "offsetof mismatch for RequestAdapterOptions::powerPreference");
    static_assert(offsetof(RequestAdapterOptions, forceFallbackAdapter) == offsetof(WGPURequestAdapterOptions, forceFallbackAdapter),
                 "offsetof mismatch for RequestAdapterOptions::forceFallbackAdapter");
    static_assert(offsetof(RequestAdapterOptions, backendType) == offsetof(WGPURequestAdapterOptions, backendType),
                 "offsetof mismatch for RequestAdapterOptions::backendType");
    static_assert(offsetof(RequestAdapterOptions, compatibleSurface) == offsetof(WGPURequestAdapterOptions, compatibleSurface),
                 "offsetof mismatch for RequestAdapterOptions::compatibleSurface");

    RequestAdapterOptions RequestAdapterOptions::WithTrivialFrontendDefaults() const {
        RequestAdapterOptions copy;
        copy.nextInChain = nextInChain;
        copy.featureLevel = (featureLevel == wgpu::FeatureLevel::Undefined)
            ? wgpu::FeatureLevel::Core
            : featureLevel;
        copy.powerPreference = powerPreference;
        copy.forceFallbackAdapter = forceFallbackAdapter;
        copy.backendType = backendType;
        copy.compatibleSurface = compatibleSurface;
        return copy;
    }
    bool RequestAdapterOptions::operator==(const RequestAdapterOptions& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            featureLevel,
            powerPreference,
            forceFallbackAdapter,
            backendType,
            compatibleSurface
        ) == std::tie(
            rhs.featureLevel,
            rhs.powerPreference,
            rhs.forceFallbackAdapter,
            rhs.backendType,
            rhs.compatibleSurface
        );
    }


    static_assert(sizeof(SamplerDescriptor) == sizeof(WGPUSamplerDescriptor), "sizeof mismatch for SamplerDescriptor");
    static_assert(alignof(SamplerDescriptor) == alignof(WGPUSamplerDescriptor), "alignof mismatch for SamplerDescriptor");

    static_assert(offsetof(SamplerDescriptor, nextInChain) == offsetof(WGPUSamplerDescriptor, nextInChain),
            "offsetof mismatch for SamplerDescriptor::nextInChain");
    static_assert(offsetof(SamplerDescriptor, label) == offsetof(WGPUSamplerDescriptor, label),
                 "offsetof mismatch for SamplerDescriptor::label");
    static_assert(offsetof(SamplerDescriptor, addressModeU) == offsetof(WGPUSamplerDescriptor, addressModeU),
                 "offsetof mismatch for SamplerDescriptor::addressModeU");
    static_assert(offsetof(SamplerDescriptor, addressModeV) == offsetof(WGPUSamplerDescriptor, addressModeV),
                 "offsetof mismatch for SamplerDescriptor::addressModeV");
    static_assert(offsetof(SamplerDescriptor, addressModeW) == offsetof(WGPUSamplerDescriptor, addressModeW),
                 "offsetof mismatch for SamplerDescriptor::addressModeW");
    static_assert(offsetof(SamplerDescriptor, magFilter) == offsetof(WGPUSamplerDescriptor, magFilter),
                 "offsetof mismatch for SamplerDescriptor::magFilter");
    static_assert(offsetof(SamplerDescriptor, minFilter) == offsetof(WGPUSamplerDescriptor, minFilter),
                 "offsetof mismatch for SamplerDescriptor::minFilter");
    static_assert(offsetof(SamplerDescriptor, mipmapFilter) == offsetof(WGPUSamplerDescriptor, mipmapFilter),
                 "offsetof mismatch for SamplerDescriptor::mipmapFilter");
    static_assert(offsetof(SamplerDescriptor, lodMinClamp) == offsetof(WGPUSamplerDescriptor, lodMinClamp),
                 "offsetof mismatch for SamplerDescriptor::lodMinClamp");
    static_assert(offsetof(SamplerDescriptor, lodMaxClamp) == offsetof(WGPUSamplerDescriptor, lodMaxClamp),
                 "offsetof mismatch for SamplerDescriptor::lodMaxClamp");
    static_assert(offsetof(SamplerDescriptor, compare) == offsetof(WGPUSamplerDescriptor, compare),
                 "offsetof mismatch for SamplerDescriptor::compare");
    static_assert(offsetof(SamplerDescriptor, maxAnisotropy) == offsetof(WGPUSamplerDescriptor, maxAnisotropy),
                 "offsetof mismatch for SamplerDescriptor::maxAnisotropy");

    SamplerDescriptor SamplerDescriptor::WithTrivialFrontendDefaults() const {
        SamplerDescriptor copy;
        copy.nextInChain = nextInChain;
        copy.label = label;
        copy.addressModeU = (addressModeU == wgpu::AddressMode::Undefined)
            ? wgpu::AddressMode::ClampToEdge
            : addressModeU;
        copy.addressModeV = (addressModeV == wgpu::AddressMode::Undefined)
            ? wgpu::AddressMode::ClampToEdge
            : addressModeV;
        copy.addressModeW = (addressModeW == wgpu::AddressMode::Undefined)
            ? wgpu::AddressMode::ClampToEdge
            : addressModeW;
        copy.magFilter = (magFilter == wgpu::FilterMode::Undefined)
            ? wgpu::FilterMode::Nearest
            : magFilter;
        copy.minFilter = (minFilter == wgpu::FilterMode::Undefined)
            ? wgpu::FilterMode::Nearest
            : minFilter;
        copy.mipmapFilter = (mipmapFilter == wgpu::MipmapFilterMode::Undefined)
            ? wgpu::MipmapFilterMode::Nearest
            : mipmapFilter;
        copy.lodMinClamp = lodMinClamp;
        copy.lodMaxClamp = lodMaxClamp;
        copy.compare = compare;
        copy.maxAnisotropy = maxAnisotropy;
        return copy;
    }
    bool SamplerDescriptor::operator==(const SamplerDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            addressModeU,
            addressModeV,
            addressModeW,
            magFilter,
            minFilter,
            mipmapFilter,
            lodMinClamp,
            lodMaxClamp,
            compare,
            maxAnisotropy
        ) == std::tie(
            rhs.label,
            rhs.addressModeU,
            rhs.addressModeV,
            rhs.addressModeW,
            rhs.magFilter,
            rhs.minFilter,
            rhs.mipmapFilter,
            rhs.lodMinClamp,
            rhs.lodMaxClamp,
            rhs.compare,
            rhs.maxAnisotropy
        );
    }


    static_assert(sizeof(ShaderModuleDescriptor) == sizeof(WGPUShaderModuleDescriptor), "sizeof mismatch for ShaderModuleDescriptor");
    static_assert(alignof(ShaderModuleDescriptor) == alignof(WGPUShaderModuleDescriptor), "alignof mismatch for ShaderModuleDescriptor");

    static_assert(offsetof(ShaderModuleDescriptor, nextInChain) == offsetof(WGPUShaderModuleDescriptor, nextInChain),
            "offsetof mismatch for ShaderModuleDescriptor::nextInChain");
    static_assert(offsetof(ShaderModuleDescriptor, label) == offsetof(WGPUShaderModuleDescriptor, label),
                 "offsetof mismatch for ShaderModuleDescriptor::label");

    bool ShaderModuleDescriptor::operator==(const ShaderModuleDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(SharedFenceDescriptor) == sizeof(WGPUSharedFenceDescriptor), "sizeof mismatch for SharedFenceDescriptor");
    static_assert(alignof(SharedFenceDescriptor) == alignof(WGPUSharedFenceDescriptor), "alignof mismatch for SharedFenceDescriptor");

    static_assert(offsetof(SharedFenceDescriptor, nextInChain) == offsetof(WGPUSharedFenceDescriptor, nextInChain),
            "offsetof mismatch for SharedFenceDescriptor::nextInChain");
    static_assert(offsetof(SharedFenceDescriptor, label) == offsetof(WGPUSharedFenceDescriptor, label),
                 "offsetof mismatch for SharedFenceDescriptor::label");

    bool SharedFenceDescriptor::operator==(const SharedFenceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(SharedFenceExportInfo) == sizeof(WGPUSharedFenceExportInfo), "sizeof mismatch for SharedFenceExportInfo");
    static_assert(alignof(SharedFenceExportInfo) == alignof(WGPUSharedFenceExportInfo), "alignof mismatch for SharedFenceExportInfo");

    static_assert(offsetof(SharedFenceExportInfo, nextInChain) == offsetof(WGPUSharedFenceExportInfo, nextInChain),
            "offsetof mismatch for SharedFenceExportInfo::nextInChain");
    static_assert(offsetof(SharedFenceExportInfo, type) == offsetof(WGPUSharedFenceExportInfo, type),
                 "offsetof mismatch for SharedFenceExportInfo::type");

    bool SharedFenceExportInfo::operator==(const SharedFenceExportInfo& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            type
        ) == std::tie(
            rhs.type
        );
    }


    static_assert(sizeof(SharedTextureMemoryAHardwareBufferProperties) == sizeof(WGPUSharedTextureMemoryAHardwareBufferProperties), "sizeof mismatch for SharedTextureMemoryAHardwareBufferProperties");
    static_assert(alignof(SharedTextureMemoryAHardwareBufferProperties) == alignof(WGPUSharedTextureMemoryAHardwareBufferProperties), "alignof mismatch for SharedTextureMemoryAHardwareBufferProperties");

    static_assert(offsetof(SharedTextureMemoryAHardwareBufferProperties, nextInChain) == offsetof(WGPUSharedTextureMemoryAHardwareBufferProperties, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryAHardwareBufferProperties::nextInChain");
    static_assert(offsetof(SharedTextureMemoryAHardwareBufferProperties, sType) == offsetof(WGPUSharedTextureMemoryAHardwareBufferProperties, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryAHardwareBufferProperties::sType");
    static_assert(offsetof(SharedTextureMemoryAHardwareBufferProperties, yCbCrInfo) == offsetof(WGPUSharedTextureMemoryAHardwareBufferProperties, yCbCrInfo),
                 "offsetof mismatch for SharedTextureMemoryAHardwareBufferProperties::yCbCrInfo");

    SharedTextureMemoryAHardwareBufferProperties SharedTextureMemoryAHardwareBufferProperties::WithTrivialFrontendDefaults() const {
        SharedTextureMemoryAHardwareBufferProperties copy;
        copy.nextInChain = nextInChain;
        copy.sType = sType;
        copy.yCbCrInfo = yCbCrInfo.WithTrivialFrontendDefaults();
        return copy;
    }
    bool SharedTextureMemoryAHardwareBufferProperties::operator==(const SharedTextureMemoryAHardwareBufferProperties& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            yCbCrInfo
        ) == std::tie(
            rhs.yCbCrInfo
        );
    }


    static_assert(sizeof(SharedTextureMemoryBeginAccessDescriptor) == sizeof(WGPUSharedTextureMemoryBeginAccessDescriptor), "sizeof mismatch for SharedTextureMemoryBeginAccessDescriptor");
    static_assert(alignof(SharedTextureMemoryBeginAccessDescriptor) == alignof(WGPUSharedTextureMemoryBeginAccessDescriptor), "alignof mismatch for SharedTextureMemoryBeginAccessDescriptor");

    static_assert(offsetof(SharedTextureMemoryBeginAccessDescriptor, nextInChain) == offsetof(WGPUSharedTextureMemoryBeginAccessDescriptor, nextInChain),
            "offsetof mismatch for SharedTextureMemoryBeginAccessDescriptor::nextInChain");
    static_assert(offsetof(SharedTextureMemoryBeginAccessDescriptor, concurrentRead) == offsetof(WGPUSharedTextureMemoryBeginAccessDescriptor, concurrentRead),
                 "offsetof mismatch for SharedTextureMemoryBeginAccessDescriptor::concurrentRead");
    static_assert(offsetof(SharedTextureMemoryBeginAccessDescriptor, initialized) == offsetof(WGPUSharedTextureMemoryBeginAccessDescriptor, initialized),
                 "offsetof mismatch for SharedTextureMemoryBeginAccessDescriptor::initialized");
    static_assert(offsetof(SharedTextureMemoryBeginAccessDescriptor, fenceCount) == offsetof(WGPUSharedTextureMemoryBeginAccessDescriptor, fenceCount),
                 "offsetof mismatch for SharedTextureMemoryBeginAccessDescriptor::fenceCount");
    static_assert(offsetof(SharedTextureMemoryBeginAccessDescriptor, fences) == offsetof(WGPUSharedTextureMemoryBeginAccessDescriptor, fences),
                 "offsetof mismatch for SharedTextureMemoryBeginAccessDescriptor::fences");
    static_assert(offsetof(SharedTextureMemoryBeginAccessDescriptor, signaledValues) == offsetof(WGPUSharedTextureMemoryBeginAccessDescriptor, signaledValues),
                 "offsetof mismatch for SharedTextureMemoryBeginAccessDescriptor::signaledValues");

    bool SharedTextureMemoryBeginAccessDescriptor::operator==(const SharedTextureMemoryBeginAccessDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            concurrentRead,
            initialized,
            fenceCount,
            fences,
            signaledValues
        ) == std::tie(
            rhs.concurrentRead,
            rhs.initialized,
            rhs.fenceCount,
            rhs.fences,
            rhs.signaledValues
        );
    }


    static_assert(sizeof(SharedTextureMemoryDmaBufDescriptor) == sizeof(WGPUSharedTextureMemoryDmaBufDescriptor), "sizeof mismatch for SharedTextureMemoryDmaBufDescriptor");
    static_assert(alignof(SharedTextureMemoryDmaBufDescriptor) == alignof(WGPUSharedTextureMemoryDmaBufDescriptor), "alignof mismatch for SharedTextureMemoryDmaBufDescriptor");

    static_assert(offsetof(SharedTextureMemoryDmaBufDescriptor, nextInChain) == offsetof(WGPUSharedTextureMemoryDmaBufDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryDmaBufDescriptor::nextInChain");
    static_assert(offsetof(SharedTextureMemoryDmaBufDescriptor, sType) == offsetof(WGPUSharedTextureMemoryDmaBufDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryDmaBufDescriptor::sType");
    static_assert(offsetof(SharedTextureMemoryDmaBufDescriptor, size) == offsetof(WGPUSharedTextureMemoryDmaBufDescriptor, size),
                 "offsetof mismatch for SharedTextureMemoryDmaBufDescriptor::size");
    static_assert(offsetof(SharedTextureMemoryDmaBufDescriptor, drmFormat) == offsetof(WGPUSharedTextureMemoryDmaBufDescriptor, drmFormat),
                 "offsetof mismatch for SharedTextureMemoryDmaBufDescriptor::drmFormat");
    static_assert(offsetof(SharedTextureMemoryDmaBufDescriptor, drmModifier) == offsetof(WGPUSharedTextureMemoryDmaBufDescriptor, drmModifier),
                 "offsetof mismatch for SharedTextureMemoryDmaBufDescriptor::drmModifier");
    static_assert(offsetof(SharedTextureMemoryDmaBufDescriptor, planeCount) == offsetof(WGPUSharedTextureMemoryDmaBufDescriptor, planeCount),
                 "offsetof mismatch for SharedTextureMemoryDmaBufDescriptor::planeCount");
    static_assert(offsetof(SharedTextureMemoryDmaBufDescriptor, planes) == offsetof(WGPUSharedTextureMemoryDmaBufDescriptor, planes),
                 "offsetof mismatch for SharedTextureMemoryDmaBufDescriptor::planes");

    bool SharedTextureMemoryDmaBufDescriptor::operator==(const SharedTextureMemoryDmaBufDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            size,
            drmFormat,
            drmModifier,
            planeCount,
            planes
        ) == std::tie(
            rhs.size,
            rhs.drmFormat,
            rhs.drmModifier,
            rhs.planeCount,
            rhs.planes
        );
    }


    static_assert(sizeof(SharedTextureMemoryMetalEndAccessState) == sizeof(WGPUSharedTextureMemoryMetalEndAccessState), "sizeof mismatch for SharedTextureMemoryMetalEndAccessState");
    static_assert(alignof(SharedTextureMemoryMetalEndAccessState) == alignof(WGPUSharedTextureMemoryMetalEndAccessState), "alignof mismatch for SharedTextureMemoryMetalEndAccessState");

    static_assert(offsetof(SharedTextureMemoryMetalEndAccessState, nextInChain) == offsetof(WGPUSharedTextureMemoryMetalEndAccessState, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for SharedTextureMemoryMetalEndAccessState::nextInChain");
    static_assert(offsetof(SharedTextureMemoryMetalEndAccessState, sType) == offsetof(WGPUSharedTextureMemoryMetalEndAccessState, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for SharedTextureMemoryMetalEndAccessState::sType");
    static_assert(offsetof(SharedTextureMemoryMetalEndAccessState, commandsScheduledFuture) == offsetof(WGPUSharedTextureMemoryMetalEndAccessState, commandsScheduledFuture),
                 "offsetof mismatch for SharedTextureMemoryMetalEndAccessState::commandsScheduledFuture");

    bool SharedTextureMemoryMetalEndAccessState::operator==(const SharedTextureMemoryMetalEndAccessState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            commandsScheduledFuture
        ) == std::tie(
            rhs.commandsScheduledFuture
        );
    }


    static_assert(sizeof(SurfaceDescriptor) == sizeof(WGPUSurfaceDescriptor), "sizeof mismatch for SurfaceDescriptor");
    static_assert(alignof(SurfaceDescriptor) == alignof(WGPUSurfaceDescriptor), "alignof mismatch for SurfaceDescriptor");

    static_assert(offsetof(SurfaceDescriptor, nextInChain) == offsetof(WGPUSurfaceDescriptor, nextInChain),
            "offsetof mismatch for SurfaceDescriptor::nextInChain");
    static_assert(offsetof(SurfaceDescriptor, label) == offsetof(WGPUSurfaceDescriptor, label),
                 "offsetof mismatch for SurfaceDescriptor::label");

    bool SurfaceDescriptor::operator==(const SurfaceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(TexelCopyBufferInfo) == sizeof(WGPUTexelCopyBufferInfo), "sizeof mismatch for TexelCopyBufferInfo");
    static_assert(alignof(TexelCopyBufferInfo) == alignof(WGPUTexelCopyBufferInfo), "alignof mismatch for TexelCopyBufferInfo");

    static_assert(offsetof(TexelCopyBufferInfo, layout) == offsetof(WGPUTexelCopyBufferInfo, layout),
                 "offsetof mismatch for TexelCopyBufferInfo::layout");
    static_assert(offsetof(TexelCopyBufferInfo, buffer) == offsetof(WGPUTexelCopyBufferInfo, buffer),
                 "offsetof mismatch for TexelCopyBufferInfo::buffer");

    bool TexelCopyBufferInfo::operator==(const TexelCopyBufferInfo& rhs) const {
        return  std::tie(
            layout,
            buffer
        ) == std::tie(
            rhs.layout,
            rhs.buffer
        );
    }


    static_assert(sizeof(TexelCopyTextureInfo) == sizeof(WGPUTexelCopyTextureInfo), "sizeof mismatch for TexelCopyTextureInfo");
    static_assert(alignof(TexelCopyTextureInfo) == alignof(WGPUTexelCopyTextureInfo), "alignof mismatch for TexelCopyTextureInfo");

    static_assert(offsetof(TexelCopyTextureInfo, texture) == offsetof(WGPUTexelCopyTextureInfo, texture),
                 "offsetof mismatch for TexelCopyTextureInfo::texture");
    static_assert(offsetof(TexelCopyTextureInfo, mipLevel) == offsetof(WGPUTexelCopyTextureInfo, mipLevel),
                 "offsetof mismatch for TexelCopyTextureInfo::mipLevel");
    static_assert(offsetof(TexelCopyTextureInfo, origin) == offsetof(WGPUTexelCopyTextureInfo, origin),
                 "offsetof mismatch for TexelCopyTextureInfo::origin");
    static_assert(offsetof(TexelCopyTextureInfo, aspect) == offsetof(WGPUTexelCopyTextureInfo, aspect),
                 "offsetof mismatch for TexelCopyTextureInfo::aspect");

    TexelCopyTextureInfo TexelCopyTextureInfo::WithTrivialFrontendDefaults() const {
        TexelCopyTextureInfo copy;
        copy.texture = texture;
        copy.mipLevel = mipLevel;
        copy.origin = origin;
        copy.aspect = (aspect == wgpu::TextureAspect::Undefined)
            ? wgpu::TextureAspect::All
            : aspect;
        return copy;
    }
    bool TexelCopyTextureInfo::operator==(const TexelCopyTextureInfo& rhs) const {
        return  std::tie(
            texture,
            mipLevel,
            origin,
            aspect
        ) == std::tie(
            rhs.texture,
            rhs.mipLevel,
            rhs.origin,
            rhs.aspect
        );
    }


    static_assert(sizeof(TextureComponentSwizzleDescriptor) == sizeof(WGPUTextureComponentSwizzleDescriptor), "sizeof mismatch for TextureComponentSwizzleDescriptor");
    static_assert(alignof(TextureComponentSwizzleDescriptor) == alignof(WGPUTextureComponentSwizzleDescriptor), "alignof mismatch for TextureComponentSwizzleDescriptor");

    static_assert(offsetof(TextureComponentSwizzleDescriptor, nextInChain) == offsetof(WGPUTextureComponentSwizzleDescriptor, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for TextureComponentSwizzleDescriptor::nextInChain");
    static_assert(offsetof(TextureComponentSwizzleDescriptor, sType) == offsetof(WGPUTextureComponentSwizzleDescriptor, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for TextureComponentSwizzleDescriptor::sType");
    static_assert(offsetof(TextureComponentSwizzleDescriptor, swizzle) == offsetof(WGPUTextureComponentSwizzleDescriptor, swizzle),
                 "offsetof mismatch for TextureComponentSwizzleDescriptor::swizzle");

    TextureComponentSwizzleDescriptor TextureComponentSwizzleDescriptor::WithTrivialFrontendDefaults() const {
        TextureComponentSwizzleDescriptor copy;
        copy.nextInChain = nextInChain;
        copy.sType = sType;
        copy.swizzle = swizzle.WithTrivialFrontendDefaults();
        return copy;
    }
    bool TextureComponentSwizzleDescriptor::operator==(const TextureComponentSwizzleDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            swizzle
        ) == std::tie(
            rhs.swizzle
        );
    }


    static_assert(sizeof(TextureDescriptor) == sizeof(WGPUTextureDescriptor), "sizeof mismatch for TextureDescriptor");
    static_assert(alignof(TextureDescriptor) == alignof(WGPUTextureDescriptor), "alignof mismatch for TextureDescriptor");

    static_assert(offsetof(TextureDescriptor, nextInChain) == offsetof(WGPUTextureDescriptor, nextInChain),
            "offsetof mismatch for TextureDescriptor::nextInChain");
    static_assert(offsetof(TextureDescriptor, label) == offsetof(WGPUTextureDescriptor, label),
                 "offsetof mismatch for TextureDescriptor::label");
    static_assert(offsetof(TextureDescriptor, usage) == offsetof(WGPUTextureDescriptor, usage),
                 "offsetof mismatch for TextureDescriptor::usage");
    static_assert(offsetof(TextureDescriptor, dimension) == offsetof(WGPUTextureDescriptor, dimension),
                 "offsetof mismatch for TextureDescriptor::dimension");
    static_assert(offsetof(TextureDescriptor, size) == offsetof(WGPUTextureDescriptor, size),
                 "offsetof mismatch for TextureDescriptor::size");
    static_assert(offsetof(TextureDescriptor, format) == offsetof(WGPUTextureDescriptor, format),
                 "offsetof mismatch for TextureDescriptor::format");
    static_assert(offsetof(TextureDescriptor, mipLevelCount) == offsetof(WGPUTextureDescriptor, mipLevelCount),
                 "offsetof mismatch for TextureDescriptor::mipLevelCount");
    static_assert(offsetof(TextureDescriptor, sampleCount) == offsetof(WGPUTextureDescriptor, sampleCount),
                 "offsetof mismatch for TextureDescriptor::sampleCount");
    static_assert(offsetof(TextureDescriptor, viewFormatCount) == offsetof(WGPUTextureDescriptor, viewFormatCount),
                 "offsetof mismatch for TextureDescriptor::viewFormatCount");
    static_assert(offsetof(TextureDescriptor, viewFormats) == offsetof(WGPUTextureDescriptor, viewFormats),
                 "offsetof mismatch for TextureDescriptor::viewFormats");

    TextureDescriptor TextureDescriptor::WithTrivialFrontendDefaults() const {
        TextureDescriptor copy;
        copy.nextInChain = nextInChain;
        copy.label = label;
        copy.usage = usage;
        copy.dimension = (dimension == wgpu::TextureDimension::Undefined)
            ? wgpu::TextureDimension::e2D
            : dimension;
        copy.size = size;
        copy.format = format;
        copy.mipLevelCount = mipLevelCount;
        copy.sampleCount = sampleCount;
        copy.viewFormatCount = viewFormatCount;
        copy.viewFormats = viewFormats;
        return copy;
    }
    bool TextureDescriptor::operator==(const TextureDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            usage,
            dimension,
            size,
            format,
            mipLevelCount,
            sampleCount,
            viewFormatCount,
            viewFormats
        ) == std::tie(
            rhs.label,
            rhs.usage,
            rhs.dimension,
            rhs.size,
            rhs.format,
            rhs.mipLevelCount,
            rhs.sampleCount,
            rhs.viewFormatCount,
            rhs.viewFormats
        );
    }


    static_assert(sizeof(VertexBufferLayout) == sizeof(WGPUVertexBufferLayout), "sizeof mismatch for VertexBufferLayout");
    static_assert(alignof(VertexBufferLayout) == alignof(WGPUVertexBufferLayout), "alignof mismatch for VertexBufferLayout");

    static_assert(offsetof(VertexBufferLayout, nextInChain) == offsetof(WGPUVertexBufferLayout, nextInChain),
            "offsetof mismatch for VertexBufferLayout::nextInChain");
    static_assert(offsetof(VertexBufferLayout, stepMode) == offsetof(WGPUVertexBufferLayout, stepMode),
                 "offsetof mismatch for VertexBufferLayout::stepMode");
    static_assert(offsetof(VertexBufferLayout, arrayStride) == offsetof(WGPUVertexBufferLayout, arrayStride),
                 "offsetof mismatch for VertexBufferLayout::arrayStride");
    static_assert(offsetof(VertexBufferLayout, attributeCount) == offsetof(WGPUVertexBufferLayout, attributeCount),
                 "offsetof mismatch for VertexBufferLayout::attributeCount");
    static_assert(offsetof(VertexBufferLayout, attributes) == offsetof(WGPUVertexBufferLayout, attributes),
                 "offsetof mismatch for VertexBufferLayout::attributes");

    bool VertexBufferLayout::operator==(const VertexBufferLayout& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            stepMode,
            arrayStride,
            attributeCount,
            attributes
        ) == std::tie(
            rhs.stepMode,
            rhs.arrayStride,
            rhs.attributeCount,
            rhs.attributes
        );
    }


    static_assert(sizeof(AdapterInfo) == sizeof(WGPUAdapterInfo), "sizeof mismatch for AdapterInfo");
    static_assert(alignof(AdapterInfo) == alignof(WGPUAdapterInfo), "alignof mismatch for AdapterInfo");

    static_assert(offsetof(AdapterInfo, nextInChain) == offsetof(WGPUAdapterInfo, nextInChain),
            "offsetof mismatch for AdapterInfo::nextInChain");
    static_assert(offsetof(AdapterInfo, vendor) == offsetof(WGPUAdapterInfo, vendor),
                 "offsetof mismatch for AdapterInfo::vendor");
    static_assert(offsetof(AdapterInfo, architecture) == offsetof(WGPUAdapterInfo, architecture),
                 "offsetof mismatch for AdapterInfo::architecture");
    static_assert(offsetof(AdapterInfo, device) == offsetof(WGPUAdapterInfo, device),
                 "offsetof mismatch for AdapterInfo::device");
    static_assert(offsetof(AdapterInfo, description) == offsetof(WGPUAdapterInfo, description),
                 "offsetof mismatch for AdapterInfo::description");
    static_assert(offsetof(AdapterInfo, backendType) == offsetof(WGPUAdapterInfo, backendType),
                 "offsetof mismatch for AdapterInfo::backendType");
    static_assert(offsetof(AdapterInfo, adapterType) == offsetof(WGPUAdapterInfo, adapterType),
                 "offsetof mismatch for AdapterInfo::adapterType");
    static_assert(offsetof(AdapterInfo, vendorID) == offsetof(WGPUAdapterInfo, vendorID),
                 "offsetof mismatch for AdapterInfo::vendorID");
    static_assert(offsetof(AdapterInfo, deviceID) == offsetof(WGPUAdapterInfo, deviceID),
                 "offsetof mismatch for AdapterInfo::deviceID");
    static_assert(offsetof(AdapterInfo, subgroupMinSize) == offsetof(WGPUAdapterInfo, subgroupMinSize),
                 "offsetof mismatch for AdapterInfo::subgroupMinSize");
    static_assert(offsetof(AdapterInfo, subgroupMaxSize) == offsetof(WGPUAdapterInfo, subgroupMaxSize),
                 "offsetof mismatch for AdapterInfo::subgroupMaxSize");

    bool AdapterInfo::operator==(const AdapterInfo& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            vendor,
            architecture,
            device,
            description,
            backendType,
            adapterType,
            vendorID,
            deviceID,
            subgroupMinSize,
            subgroupMaxSize
        ) == std::tie(
            rhs.vendor,
            rhs.architecture,
            rhs.device,
            rhs.description,
            rhs.backendType,
            rhs.adapterType,
            rhs.vendorID,
            rhs.deviceID,
            rhs.subgroupMinSize,
            rhs.subgroupMaxSize
        );
    }


    static_assert(sizeof(BindGroupDescriptor) == sizeof(WGPUBindGroupDescriptor), "sizeof mismatch for BindGroupDescriptor");
    static_assert(alignof(BindGroupDescriptor) == alignof(WGPUBindGroupDescriptor), "alignof mismatch for BindGroupDescriptor");

    static_assert(offsetof(BindGroupDescriptor, nextInChain) == offsetof(WGPUBindGroupDescriptor, nextInChain),
            "offsetof mismatch for BindGroupDescriptor::nextInChain");
    static_assert(offsetof(BindGroupDescriptor, label) == offsetof(WGPUBindGroupDescriptor, label),
                 "offsetof mismatch for BindGroupDescriptor::label");
    static_assert(offsetof(BindGroupDescriptor, layout) == offsetof(WGPUBindGroupDescriptor, layout),
                 "offsetof mismatch for BindGroupDescriptor::layout");
    static_assert(offsetof(BindGroupDescriptor, entryCount) == offsetof(WGPUBindGroupDescriptor, entryCount),
                 "offsetof mismatch for BindGroupDescriptor::entryCount");
    static_assert(offsetof(BindGroupDescriptor, entries) == offsetof(WGPUBindGroupDescriptor, entries),
                 "offsetof mismatch for BindGroupDescriptor::entries");

    bool BindGroupDescriptor::operator==(const BindGroupDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            layout,
            entryCount,
            entries
        ) == std::tie(
            rhs.label,
            rhs.layout,
            rhs.entryCount,
            rhs.entries
        );
    }


    static_assert(sizeof(BindGroupLayoutDescriptor) == sizeof(WGPUBindGroupLayoutDescriptor), "sizeof mismatch for BindGroupLayoutDescriptor");
    static_assert(alignof(BindGroupLayoutDescriptor) == alignof(WGPUBindGroupLayoutDescriptor), "alignof mismatch for BindGroupLayoutDescriptor");

    static_assert(offsetof(BindGroupLayoutDescriptor, nextInChain) == offsetof(WGPUBindGroupLayoutDescriptor, nextInChain),
            "offsetof mismatch for BindGroupLayoutDescriptor::nextInChain");
    static_assert(offsetof(BindGroupLayoutDescriptor, label) == offsetof(WGPUBindGroupLayoutDescriptor, label),
                 "offsetof mismatch for BindGroupLayoutDescriptor::label");
    static_assert(offsetof(BindGroupLayoutDescriptor, entryCount) == offsetof(WGPUBindGroupLayoutDescriptor, entryCount),
                 "offsetof mismatch for BindGroupLayoutDescriptor::entryCount");
    static_assert(offsetof(BindGroupLayoutDescriptor, entries) == offsetof(WGPUBindGroupLayoutDescriptor, entries),
                 "offsetof mismatch for BindGroupLayoutDescriptor::entries");

    bool BindGroupLayoutDescriptor::operator==(const BindGroupLayoutDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            entryCount,
            entries
        ) == std::tie(
            rhs.label,
            rhs.entryCount,
            rhs.entries
        );
    }


    static_assert(sizeof(ColorTargetState) == sizeof(WGPUColorTargetState), "sizeof mismatch for ColorTargetState");
    static_assert(alignof(ColorTargetState) == alignof(WGPUColorTargetState), "alignof mismatch for ColorTargetState");

    static_assert(offsetof(ColorTargetState, nextInChain) == offsetof(WGPUColorTargetState, nextInChain),
            "offsetof mismatch for ColorTargetState::nextInChain");
    static_assert(offsetof(ColorTargetState, format) == offsetof(WGPUColorTargetState, format),
                 "offsetof mismatch for ColorTargetState::format");
    static_assert(offsetof(ColorTargetState, blend) == offsetof(WGPUColorTargetState, blend),
                 "offsetof mismatch for ColorTargetState::blend");
    static_assert(offsetof(ColorTargetState, writeMask) == offsetof(WGPUColorTargetState, writeMask),
                 "offsetof mismatch for ColorTargetState::writeMask");

    bool ColorTargetState::operator==(const ColorTargetState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            format,
            blend,
            writeMask
        ) == std::tie(
            rhs.format,
            rhs.blend,
            rhs.writeMask
        );
    }


    static_assert(sizeof(CompilationInfo) == sizeof(WGPUCompilationInfo), "sizeof mismatch for CompilationInfo");
    static_assert(alignof(CompilationInfo) == alignof(WGPUCompilationInfo), "alignof mismatch for CompilationInfo");

    static_assert(offsetof(CompilationInfo, nextInChain) == offsetof(WGPUCompilationInfo, nextInChain),
            "offsetof mismatch for CompilationInfo::nextInChain");
    static_assert(offsetof(CompilationInfo, messageCount) == offsetof(WGPUCompilationInfo, messageCount),
                 "offsetof mismatch for CompilationInfo::messageCount");
    static_assert(offsetof(CompilationInfo, messages) == offsetof(WGPUCompilationInfo, messages),
                 "offsetof mismatch for CompilationInfo::messages");

    bool CompilationInfo::operator==(const CompilationInfo& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            messageCount,
            messages
        ) == std::tie(
            rhs.messageCount,
            rhs.messages
        );
    }


    static_assert(sizeof(ComputePipelineDescriptor) == sizeof(WGPUComputePipelineDescriptor), "sizeof mismatch for ComputePipelineDescriptor");
    static_assert(alignof(ComputePipelineDescriptor) == alignof(WGPUComputePipelineDescriptor), "alignof mismatch for ComputePipelineDescriptor");

    static_assert(offsetof(ComputePipelineDescriptor, nextInChain) == offsetof(WGPUComputePipelineDescriptor, nextInChain),
            "offsetof mismatch for ComputePipelineDescriptor::nextInChain");
    static_assert(offsetof(ComputePipelineDescriptor, label) == offsetof(WGPUComputePipelineDescriptor, label),
                 "offsetof mismatch for ComputePipelineDescriptor::label");
    static_assert(offsetof(ComputePipelineDescriptor, layout) == offsetof(WGPUComputePipelineDescriptor, layout),
                 "offsetof mismatch for ComputePipelineDescriptor::layout");
    static_assert(offsetof(ComputePipelineDescriptor, compute) == offsetof(WGPUComputePipelineDescriptor, compute),
                 "offsetof mismatch for ComputePipelineDescriptor::compute");

    bool ComputePipelineDescriptor::operator==(const ComputePipelineDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            layout,
            compute
        ) == std::tie(
            rhs.label,
            rhs.layout,
            rhs.compute
        );
    }


    static_assert(sizeof(DawnFormatCapabilities) == sizeof(WGPUDawnFormatCapabilities), "sizeof mismatch for DawnFormatCapabilities");
    static_assert(alignof(DawnFormatCapabilities) == alignof(WGPUDawnFormatCapabilities), "alignof mismatch for DawnFormatCapabilities");

    static_assert(offsetof(DawnFormatCapabilities, nextInChain) == offsetof(WGPUDawnFormatCapabilities, nextInChain),
            "offsetof mismatch for DawnFormatCapabilities::nextInChain");

    bool DawnFormatCapabilities::operator==(const DawnFormatCapabilities& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
        ) == std::tie(
        );
    }


    static_assert(sizeof(DeviceDescriptor) == sizeof(WGPUDeviceDescriptor), "sizeof mismatch for DeviceDescriptor");
    static_assert(alignof(DeviceDescriptor) == alignof(WGPUDeviceDescriptor), "alignof mismatch for DeviceDescriptor");

    static_assert(offsetof(DeviceDescriptor, nextInChain) == offsetof(WGPUDeviceDescriptor, nextInChain),
            "offsetof mismatch for DeviceDescriptor::nextInChain");
    static_assert(offsetof(DeviceDescriptor, label) == offsetof(WGPUDeviceDescriptor, label),
                 "offsetof mismatch for DeviceDescriptor::label");
    static_assert(offsetof(DeviceDescriptor, requiredFeatureCount) == offsetof(WGPUDeviceDescriptor, requiredFeatureCount),
                 "offsetof mismatch for DeviceDescriptor::requiredFeatureCount");
    static_assert(offsetof(DeviceDescriptor, requiredFeatures) == offsetof(WGPUDeviceDescriptor, requiredFeatures),
                 "offsetof mismatch for DeviceDescriptor::requiredFeatures");
    static_assert(offsetof(DeviceDescriptor, requiredLimits) == offsetof(WGPUDeviceDescriptor, requiredLimits),
                 "offsetof mismatch for DeviceDescriptor::requiredLimits");
    static_assert(offsetof(DeviceDescriptor, defaultQueue) == offsetof(WGPUDeviceDescriptor, defaultQueue),
                 "offsetof mismatch for DeviceDescriptor::defaultQueue");
    static_assert(offsetof(DeviceDescriptor, deviceLostCallbackInfo) == offsetof(WGPUDeviceDescriptor, deviceLostCallbackInfo),
                 "offsetof mismatch for DeviceDescriptor::deviceLostCallbackInfo");
    static_assert(offsetof(DeviceDescriptor, uncapturedErrorCallbackInfo) == offsetof(WGPUDeviceDescriptor, uncapturedErrorCallbackInfo),
                 "offsetof mismatch for DeviceDescriptor::uncapturedErrorCallbackInfo");

    bool DeviceDescriptor::operator==(const DeviceDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            requiredFeatureCount,
            requiredFeatures,
            requiredLimits,
            defaultQueue
        ) == std::tie(
            rhs.label,
            rhs.requiredFeatureCount,
            rhs.requiredFeatures,
            rhs.requiredLimits,
            rhs.defaultQueue
        );
    }


    static_assert(sizeof(PipelineLayoutDescriptor) == sizeof(WGPUPipelineLayoutDescriptor), "sizeof mismatch for PipelineLayoutDescriptor");
    static_assert(alignof(PipelineLayoutDescriptor) == alignof(WGPUPipelineLayoutDescriptor), "alignof mismatch for PipelineLayoutDescriptor");

    static_assert(offsetof(PipelineLayoutDescriptor, nextInChain) == offsetof(WGPUPipelineLayoutDescriptor, nextInChain),
            "offsetof mismatch for PipelineLayoutDescriptor::nextInChain");
    static_assert(offsetof(PipelineLayoutDescriptor, label) == offsetof(WGPUPipelineLayoutDescriptor, label),
                 "offsetof mismatch for PipelineLayoutDescriptor::label");
    static_assert(offsetof(PipelineLayoutDescriptor, bindGroupLayoutCount) == offsetof(WGPUPipelineLayoutDescriptor, bindGroupLayoutCount),
                 "offsetof mismatch for PipelineLayoutDescriptor::bindGroupLayoutCount");
    static_assert(offsetof(PipelineLayoutDescriptor, bindGroupLayouts) == offsetof(WGPUPipelineLayoutDescriptor, bindGroupLayouts),
                 "offsetof mismatch for PipelineLayoutDescriptor::bindGroupLayouts");
    static_assert(offsetof(PipelineLayoutDescriptor, immediateSize) == offsetof(WGPUPipelineLayoutDescriptor, immediateSize),
                 "offsetof mismatch for PipelineLayoutDescriptor::immediateSize");

    bool PipelineLayoutDescriptor::operator==(const PipelineLayoutDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            bindGroupLayoutCount,
            bindGroupLayouts,
            immediateSize
        ) == std::tie(
            rhs.label,
            rhs.bindGroupLayoutCount,
            rhs.bindGroupLayouts,
            rhs.immediateSize
        );
    }


    static_assert(sizeof(RenderPassPixelLocalStorage) == sizeof(WGPURenderPassPixelLocalStorage), "sizeof mismatch for RenderPassPixelLocalStorage");
    static_assert(alignof(RenderPassPixelLocalStorage) == alignof(WGPURenderPassPixelLocalStorage), "alignof mismatch for RenderPassPixelLocalStorage");

    static_assert(offsetof(RenderPassPixelLocalStorage, nextInChain) == offsetof(WGPURenderPassPixelLocalStorage, chain) + offsetof(WGPUChainedStruct, next),
            "offsetof mismatch for RenderPassPixelLocalStorage::nextInChain");
    static_assert(offsetof(RenderPassPixelLocalStorage, sType) == offsetof(WGPURenderPassPixelLocalStorage, chain) + offsetof(WGPUChainedStruct, sType),
            "offsetof mismatch for RenderPassPixelLocalStorage::sType");
    static_assert(offsetof(RenderPassPixelLocalStorage, totalPixelLocalStorageSize) == offsetof(WGPURenderPassPixelLocalStorage, totalPixelLocalStorageSize),
                 "offsetof mismatch for RenderPassPixelLocalStorage::totalPixelLocalStorageSize");
    static_assert(offsetof(RenderPassPixelLocalStorage, storageAttachmentCount) == offsetof(WGPURenderPassPixelLocalStorage, storageAttachmentCount),
                 "offsetof mismatch for RenderPassPixelLocalStorage::storageAttachmentCount");
    static_assert(offsetof(RenderPassPixelLocalStorage, storageAttachments) == offsetof(WGPURenderPassPixelLocalStorage, storageAttachments),
                 "offsetof mismatch for RenderPassPixelLocalStorage::storageAttachments");

    bool RenderPassPixelLocalStorage::operator==(const RenderPassPixelLocalStorage& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            totalPixelLocalStorageSize,
            storageAttachmentCount,
            storageAttachments
        ) == std::tie(
            rhs.totalPixelLocalStorageSize,
            rhs.storageAttachmentCount,
            rhs.storageAttachments
        );
    }


    static_assert(sizeof(SharedTextureMemoryDescriptor) == sizeof(WGPUSharedTextureMemoryDescriptor), "sizeof mismatch for SharedTextureMemoryDescriptor");
    static_assert(alignof(SharedTextureMemoryDescriptor) == alignof(WGPUSharedTextureMemoryDescriptor), "alignof mismatch for SharedTextureMemoryDescriptor");

    static_assert(offsetof(SharedTextureMemoryDescriptor, nextInChain) == offsetof(WGPUSharedTextureMemoryDescriptor, nextInChain),
            "offsetof mismatch for SharedTextureMemoryDescriptor::nextInChain");
    static_assert(offsetof(SharedTextureMemoryDescriptor, label) == offsetof(WGPUSharedTextureMemoryDescriptor, label),
                 "offsetof mismatch for SharedTextureMemoryDescriptor::label");

    bool SharedTextureMemoryDescriptor::operator==(const SharedTextureMemoryDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label
        ) == std::tie(
            rhs.label
        );
    }


    static_assert(sizeof(SharedTextureMemoryEndAccessState) == sizeof(WGPUSharedTextureMemoryEndAccessState), "sizeof mismatch for SharedTextureMemoryEndAccessState");
    static_assert(alignof(SharedTextureMemoryEndAccessState) == alignof(WGPUSharedTextureMemoryEndAccessState), "alignof mismatch for SharedTextureMemoryEndAccessState");

    static_assert(offsetof(SharedTextureMemoryEndAccessState, nextInChain) == offsetof(WGPUSharedTextureMemoryEndAccessState, nextInChain),
            "offsetof mismatch for SharedTextureMemoryEndAccessState::nextInChain");
    static_assert(offsetof(SharedTextureMemoryEndAccessState, initialized) == offsetof(WGPUSharedTextureMemoryEndAccessState, initialized),
                 "offsetof mismatch for SharedTextureMemoryEndAccessState::initialized");
    static_assert(offsetof(SharedTextureMemoryEndAccessState, fenceCount) == offsetof(WGPUSharedTextureMemoryEndAccessState, fenceCount),
                 "offsetof mismatch for SharedTextureMemoryEndAccessState::fenceCount");
    static_assert(offsetof(SharedTextureMemoryEndAccessState, fences) == offsetof(WGPUSharedTextureMemoryEndAccessState, fences),
                 "offsetof mismatch for SharedTextureMemoryEndAccessState::fences");
    static_assert(offsetof(SharedTextureMemoryEndAccessState, signaledValues) == offsetof(WGPUSharedTextureMemoryEndAccessState, signaledValues),
                 "offsetof mismatch for SharedTextureMemoryEndAccessState::signaledValues");

    bool SharedTextureMemoryEndAccessState::operator==(const SharedTextureMemoryEndAccessState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            initialized,
            fenceCount,
            fences,
            signaledValues
        ) == std::tie(
            rhs.initialized,
            rhs.fenceCount,
            rhs.fences,
            rhs.signaledValues
        );
    }


    static_assert(sizeof(SharedTextureMemoryProperties) == sizeof(WGPUSharedTextureMemoryProperties), "sizeof mismatch for SharedTextureMemoryProperties");
    static_assert(alignof(SharedTextureMemoryProperties) == alignof(WGPUSharedTextureMemoryProperties), "alignof mismatch for SharedTextureMemoryProperties");

    static_assert(offsetof(SharedTextureMemoryProperties, nextInChain) == offsetof(WGPUSharedTextureMemoryProperties, nextInChain),
            "offsetof mismatch for SharedTextureMemoryProperties::nextInChain");
    static_assert(offsetof(SharedTextureMemoryProperties, usage) == offsetof(WGPUSharedTextureMemoryProperties, usage),
                 "offsetof mismatch for SharedTextureMemoryProperties::usage");
    static_assert(offsetof(SharedTextureMemoryProperties, size) == offsetof(WGPUSharedTextureMemoryProperties, size),
                 "offsetof mismatch for SharedTextureMemoryProperties::size");
    static_assert(offsetof(SharedTextureMemoryProperties, format) == offsetof(WGPUSharedTextureMemoryProperties, format),
                 "offsetof mismatch for SharedTextureMemoryProperties::format");

    bool SharedTextureMemoryProperties::operator==(const SharedTextureMemoryProperties& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            usage,
            size,
            format
        ) == std::tie(
            rhs.usage,
            rhs.size,
            rhs.format
        );
    }


    static_assert(sizeof(TextureViewDescriptor) == sizeof(WGPUTextureViewDescriptor), "sizeof mismatch for TextureViewDescriptor");
    static_assert(alignof(TextureViewDescriptor) == alignof(WGPUTextureViewDescriptor), "alignof mismatch for TextureViewDescriptor");

    static_assert(offsetof(TextureViewDescriptor, nextInChain) == offsetof(WGPUTextureViewDescriptor, nextInChain),
            "offsetof mismatch for TextureViewDescriptor::nextInChain");
    static_assert(offsetof(TextureViewDescriptor, label) == offsetof(WGPUTextureViewDescriptor, label),
                 "offsetof mismatch for TextureViewDescriptor::label");
    static_assert(offsetof(TextureViewDescriptor, format) == offsetof(WGPUTextureViewDescriptor, format),
                 "offsetof mismatch for TextureViewDescriptor::format");
    static_assert(offsetof(TextureViewDescriptor, dimension) == offsetof(WGPUTextureViewDescriptor, dimension),
                 "offsetof mismatch for TextureViewDescriptor::dimension");
    static_assert(offsetof(TextureViewDescriptor, baseMipLevel) == offsetof(WGPUTextureViewDescriptor, baseMipLevel),
                 "offsetof mismatch for TextureViewDescriptor::baseMipLevel");
    static_assert(offsetof(TextureViewDescriptor, mipLevelCount) == offsetof(WGPUTextureViewDescriptor, mipLevelCount),
                 "offsetof mismatch for TextureViewDescriptor::mipLevelCount");
    static_assert(offsetof(TextureViewDescriptor, baseArrayLayer) == offsetof(WGPUTextureViewDescriptor, baseArrayLayer),
                 "offsetof mismatch for TextureViewDescriptor::baseArrayLayer");
    static_assert(offsetof(TextureViewDescriptor, arrayLayerCount) == offsetof(WGPUTextureViewDescriptor, arrayLayerCount),
                 "offsetof mismatch for TextureViewDescriptor::arrayLayerCount");
    static_assert(offsetof(TextureViewDescriptor, aspect) == offsetof(WGPUTextureViewDescriptor, aspect),
                 "offsetof mismatch for TextureViewDescriptor::aspect");
    static_assert(offsetof(TextureViewDescriptor, usage) == offsetof(WGPUTextureViewDescriptor, usage),
                 "offsetof mismatch for TextureViewDescriptor::usage");

    TextureViewDescriptor TextureViewDescriptor::WithTrivialFrontendDefaults() const {
        TextureViewDescriptor copy;
        copy.nextInChain = nextInChain;
        copy.label = label;
        copy.format = format;
        copy.dimension = dimension;
        copy.baseMipLevel = baseMipLevel;
        copy.mipLevelCount = mipLevelCount;
        copy.baseArrayLayer = baseArrayLayer;
        copy.arrayLayerCount = arrayLayerCount;
        copy.aspect = (aspect == wgpu::TextureAspect::Undefined)
            ? wgpu::TextureAspect::All
            : aspect;
        copy.usage = usage;
        return copy;
    }
    bool TextureViewDescriptor::operator==(const TextureViewDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            format,
            dimension,
            baseMipLevel,
            mipLevelCount,
            baseArrayLayer,
            arrayLayerCount,
            aspect,
            usage
        ) == std::tie(
            rhs.label,
            rhs.format,
            rhs.dimension,
            rhs.baseMipLevel,
            rhs.mipLevelCount,
            rhs.baseArrayLayer,
            rhs.arrayLayerCount,
            rhs.aspect,
            rhs.usage
        );
    }


    static_assert(sizeof(VertexState) == sizeof(WGPUVertexState), "sizeof mismatch for VertexState");
    static_assert(alignof(VertexState) == alignof(WGPUVertexState), "alignof mismatch for VertexState");

    static_assert(offsetof(VertexState, nextInChain) == offsetof(WGPUVertexState, nextInChain),
            "offsetof mismatch for VertexState::nextInChain");
    static_assert(offsetof(VertexState, module) == offsetof(WGPUVertexState, module),
                 "offsetof mismatch for VertexState::module");
    static_assert(offsetof(VertexState, entryPoint) == offsetof(WGPUVertexState, entryPoint),
                 "offsetof mismatch for VertexState::entryPoint");
    static_assert(offsetof(VertexState, constantCount) == offsetof(WGPUVertexState, constantCount),
                 "offsetof mismatch for VertexState::constantCount");
    static_assert(offsetof(VertexState, constants) == offsetof(WGPUVertexState, constants),
                 "offsetof mismatch for VertexState::constants");
    static_assert(offsetof(VertexState, bufferCount) == offsetof(WGPUVertexState, bufferCount),
                 "offsetof mismatch for VertexState::bufferCount");
    static_assert(offsetof(VertexState, buffers) == offsetof(WGPUVertexState, buffers),
                 "offsetof mismatch for VertexState::buffers");

    bool VertexState::operator==(const VertexState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            module,
            entryPoint,
            constantCount,
            constants,
            bufferCount,
            buffers
        ) == std::tie(
            rhs.module,
            rhs.entryPoint,
            rhs.constantCount,
            rhs.constants,
            rhs.bufferCount,
            rhs.buffers
        );
    }


    static_assert(sizeof(FragmentState) == sizeof(WGPUFragmentState), "sizeof mismatch for FragmentState");
    static_assert(alignof(FragmentState) == alignof(WGPUFragmentState), "alignof mismatch for FragmentState");

    static_assert(offsetof(FragmentState, nextInChain) == offsetof(WGPUFragmentState, nextInChain),
            "offsetof mismatch for FragmentState::nextInChain");
    static_assert(offsetof(FragmentState, module) == offsetof(WGPUFragmentState, module),
                 "offsetof mismatch for FragmentState::module");
    static_assert(offsetof(FragmentState, entryPoint) == offsetof(WGPUFragmentState, entryPoint),
                 "offsetof mismatch for FragmentState::entryPoint");
    static_assert(offsetof(FragmentState, constantCount) == offsetof(WGPUFragmentState, constantCount),
                 "offsetof mismatch for FragmentState::constantCount");
    static_assert(offsetof(FragmentState, constants) == offsetof(WGPUFragmentState, constants),
                 "offsetof mismatch for FragmentState::constants");
    static_assert(offsetof(FragmentState, targetCount) == offsetof(WGPUFragmentState, targetCount),
                 "offsetof mismatch for FragmentState::targetCount");
    static_assert(offsetof(FragmentState, targets) == offsetof(WGPUFragmentState, targets),
                 "offsetof mismatch for FragmentState::targets");

    bool FragmentState::operator==(const FragmentState& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            module,
            entryPoint,
            constantCount,
            constants,
            targetCount,
            targets
        ) == std::tie(
            rhs.module,
            rhs.entryPoint,
            rhs.constantCount,
            rhs.constants,
            rhs.targetCount,
            rhs.targets
        );
    }


    static_assert(sizeof(RenderPassDescriptor) == sizeof(WGPURenderPassDescriptor), "sizeof mismatch for RenderPassDescriptor");
    static_assert(alignof(RenderPassDescriptor) == alignof(WGPURenderPassDescriptor), "alignof mismatch for RenderPassDescriptor");

    static_assert(offsetof(RenderPassDescriptor, nextInChain) == offsetof(WGPURenderPassDescriptor, nextInChain),
            "offsetof mismatch for RenderPassDescriptor::nextInChain");
    static_assert(offsetof(RenderPassDescriptor, label) == offsetof(WGPURenderPassDescriptor, label),
                 "offsetof mismatch for RenderPassDescriptor::label");
    static_assert(offsetof(RenderPassDescriptor, colorAttachmentCount) == offsetof(WGPURenderPassDescriptor, colorAttachmentCount),
                 "offsetof mismatch for RenderPassDescriptor::colorAttachmentCount");
    static_assert(offsetof(RenderPassDescriptor, colorAttachments) == offsetof(WGPURenderPassDescriptor, colorAttachments),
                 "offsetof mismatch for RenderPassDescriptor::colorAttachments");
    static_assert(offsetof(RenderPassDescriptor, depthStencilAttachment) == offsetof(WGPURenderPassDescriptor, depthStencilAttachment),
                 "offsetof mismatch for RenderPassDescriptor::depthStencilAttachment");
    static_assert(offsetof(RenderPassDescriptor, occlusionQuerySet) == offsetof(WGPURenderPassDescriptor, occlusionQuerySet),
                 "offsetof mismatch for RenderPassDescriptor::occlusionQuerySet");
    static_assert(offsetof(RenderPassDescriptor, timestampWrites) == offsetof(WGPURenderPassDescriptor, timestampWrites),
                 "offsetof mismatch for RenderPassDescriptor::timestampWrites");

    bool RenderPassDescriptor::operator==(const RenderPassDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            colorAttachmentCount,
            colorAttachments,
            depthStencilAttachment,
            occlusionQuerySet,
            timestampWrites
        ) == std::tie(
            rhs.label,
            rhs.colorAttachmentCount,
            rhs.colorAttachments,
            rhs.depthStencilAttachment,
            rhs.occlusionQuerySet,
            rhs.timestampWrites
        );
    }


    static_assert(sizeof(RenderPipelineDescriptor) == sizeof(WGPURenderPipelineDescriptor), "sizeof mismatch for RenderPipelineDescriptor");
    static_assert(alignof(RenderPipelineDescriptor) == alignof(WGPURenderPipelineDescriptor), "alignof mismatch for RenderPipelineDescriptor");

    static_assert(offsetof(RenderPipelineDescriptor, nextInChain) == offsetof(WGPURenderPipelineDescriptor, nextInChain),
            "offsetof mismatch for RenderPipelineDescriptor::nextInChain");
    static_assert(offsetof(RenderPipelineDescriptor, label) == offsetof(WGPURenderPipelineDescriptor, label),
                 "offsetof mismatch for RenderPipelineDescriptor::label");
    static_assert(offsetof(RenderPipelineDescriptor, layout) == offsetof(WGPURenderPipelineDescriptor, layout),
                 "offsetof mismatch for RenderPipelineDescriptor::layout");
    static_assert(offsetof(RenderPipelineDescriptor, vertex) == offsetof(WGPURenderPipelineDescriptor, vertex),
                 "offsetof mismatch for RenderPipelineDescriptor::vertex");
    static_assert(offsetof(RenderPipelineDescriptor, primitive) == offsetof(WGPURenderPipelineDescriptor, primitive),
                 "offsetof mismatch for RenderPipelineDescriptor::primitive");
    static_assert(offsetof(RenderPipelineDescriptor, depthStencil) == offsetof(WGPURenderPipelineDescriptor, depthStencil),
                 "offsetof mismatch for RenderPipelineDescriptor::depthStencil");
    static_assert(offsetof(RenderPipelineDescriptor, multisample) == offsetof(WGPURenderPipelineDescriptor, multisample),
                 "offsetof mismatch for RenderPipelineDescriptor::multisample");
    static_assert(offsetof(RenderPipelineDescriptor, fragment) == offsetof(WGPURenderPipelineDescriptor, fragment),
                 "offsetof mismatch for RenderPipelineDescriptor::fragment");

    RenderPipelineDescriptor RenderPipelineDescriptor::WithTrivialFrontendDefaults() const {
        RenderPipelineDescriptor copy;
        copy.nextInChain = nextInChain;
        copy.label = label;
        copy.layout = layout;
        copy.vertex = vertex;
        copy.primitive = primitive.WithTrivialFrontendDefaults();
        copy.depthStencil = depthStencil;
        copy.multisample = multisample;
        copy.fragment = fragment;
        return copy;
    }
    bool RenderPipelineDescriptor::operator==(const RenderPipelineDescriptor& rhs) const {
        return (nextInChain == rhs.nextInChain) && std::tie(
            label,
            layout,
            vertex,
            primitive,
            depthStencil,
            multisample,
            fragment
        ) == std::tie(
            rhs.label,
            rhs.layout,
            rhs.vertex,
            rhs.primitive,
            rhs.depthStencil,
            rhs.multisample,
            rhs.fragment
        );
    }


    // SharedBufferMemoryEndAccessState
    SharedBufferMemoryEndAccessState::~SharedBufferMemoryEndAccessState() {
        FreeMembers();
    }

    SharedBufferMemoryEndAccessState::SharedBufferMemoryEndAccessState(SharedBufferMemoryEndAccessState&& rhs)
    : initialized(rhs.initialized),
      fenceCount(rhs.fenceCount),
      fences(rhs.fences),
      signaledValues(rhs.signaledValues){
        rhs.initialized = {};
        rhs.fenceCount = {};
        rhs.fences = {};
        rhs.signaledValues = {};
    }

    SharedBufferMemoryEndAccessState& SharedBufferMemoryEndAccessState::operator=(SharedBufferMemoryEndAccessState&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        FreeMembers();
        this->initialized = std::move(rhs.initialized);
        this->fenceCount = std::move(rhs.fenceCount);
        this->fences = std::move(rhs.fences);
        this->signaledValues = std::move(rhs.signaledValues);
        rhs.initialized = {};
        rhs.fenceCount = {};
        rhs.fences = {};
        rhs.signaledValues = {};
        return *this;
    }

    void SharedBufferMemoryEndAccessState::FreeMembers() {
        bool needsFreeing = false;        if (this->fences != nullptr) { needsFreeing = true; }        if (this->signaledValues != nullptr) { needsFreeing = true; }if (needsFreeing) {
            APISharedBufferMemoryEndAccessStateFreeMembers(*reinterpret_cast<WGPUSharedBufferMemoryEndAccessState*>(this));
        }
    }

    // SupportedFeatures
    SupportedFeatures::~SupportedFeatures() {
        FreeMembers();
    }

    SupportedFeatures::SupportedFeatures(SupportedFeatures&& rhs)
    : featureCount(rhs.featureCount),
      features(rhs.features){
        rhs.featureCount = {};
        rhs.features = {};
    }

    SupportedFeatures& SupportedFeatures::operator=(SupportedFeatures&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        FreeMembers();
        this->featureCount = std::move(rhs.featureCount);
        this->features = std::move(rhs.features);
        rhs.featureCount = {};
        rhs.features = {};
        return *this;
    }

    void SupportedFeatures::FreeMembers() {
        bool needsFreeing = false;        if (this->features != nullptr) { needsFreeing = true; }if (needsFreeing) {
            APISupportedFeaturesFreeMembers(*reinterpret_cast<WGPUSupportedFeatures*>(this));
        }
    }

    // SupportedInstanceFeatures
    SupportedInstanceFeatures::~SupportedInstanceFeatures() {
        FreeMembers();
    }

    SupportedInstanceFeatures::SupportedInstanceFeatures(SupportedInstanceFeatures&& rhs)
    : featureCount(rhs.featureCount),
      features(rhs.features){
        rhs.featureCount = {};
        rhs.features = {};
    }

    SupportedInstanceFeatures& SupportedInstanceFeatures::operator=(SupportedInstanceFeatures&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        FreeMembers();
        this->featureCount = std::move(rhs.featureCount);
        this->features = std::move(rhs.features);
        rhs.featureCount = {};
        rhs.features = {};
        return *this;
    }

    void SupportedInstanceFeatures::FreeMembers() {
        bool needsFreeing = false;        if (this->features != nullptr) { needsFreeing = true; }if (needsFreeing) {
            APISupportedInstanceFeaturesFreeMembers(*reinterpret_cast<WGPUSupportedInstanceFeatures*>(this));
        }
    }

    // SupportedWGSLLanguageFeatures
    SupportedWGSLLanguageFeatures::~SupportedWGSLLanguageFeatures() {
        FreeMembers();
    }

    SupportedWGSLLanguageFeatures::SupportedWGSLLanguageFeatures(SupportedWGSLLanguageFeatures&& rhs)
    : featureCount(rhs.featureCount),
      features(rhs.features){
        rhs.featureCount = {};
        rhs.features = {};
    }

    SupportedWGSLLanguageFeatures& SupportedWGSLLanguageFeatures::operator=(SupportedWGSLLanguageFeatures&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        FreeMembers();
        this->featureCount = std::move(rhs.featureCount);
        this->features = std::move(rhs.features);
        rhs.featureCount = {};
        rhs.features = {};
        return *this;
    }

    void SupportedWGSLLanguageFeatures::FreeMembers() {
        bool needsFreeing = false;        if (this->features != nullptr) { needsFreeing = true; }if (needsFreeing) {
            APISupportedWGSLLanguageFeaturesFreeMembers(*reinterpret_cast<WGPUSupportedWGSLLanguageFeatures*>(this));
        }
    }

    // SurfaceCapabilities
    SurfaceCapabilities::~SurfaceCapabilities() {
        FreeMembers();
    }

    SurfaceCapabilities::SurfaceCapabilities(SurfaceCapabilities&& rhs)
    : usages(rhs.usages),
      formatCount(rhs.formatCount),
      formats(rhs.formats),
      presentModeCount(rhs.presentModeCount),
      presentModes(rhs.presentModes),
      alphaModeCount(rhs.alphaModeCount),
      alphaModes(rhs.alphaModes){
        rhs.usages = {};
        rhs.formatCount = {};
        rhs.formats = {};
        rhs.presentModeCount = {};
        rhs.presentModes = {};
        rhs.alphaModeCount = {};
        rhs.alphaModes = {};
    }

    SurfaceCapabilities& SurfaceCapabilities::operator=(SurfaceCapabilities&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        FreeMembers();
        this->usages = std::move(rhs.usages);
        this->formatCount = std::move(rhs.formatCount);
        this->formats = std::move(rhs.formats);
        this->presentModeCount = std::move(rhs.presentModeCount);
        this->presentModes = std::move(rhs.presentModes);
        this->alphaModeCount = std::move(rhs.alphaModeCount);
        this->alphaModes = std::move(rhs.alphaModes);
        rhs.usages = {};
        rhs.formatCount = {};
        rhs.formats = {};
        rhs.presentModeCount = {};
        rhs.presentModes = {};
        rhs.alphaModeCount = {};
        rhs.alphaModes = {};
        return *this;
    }

    void SurfaceCapabilities::FreeMembers() {
        bool needsFreeing = false;        if (this->formats != nullptr) { needsFreeing = true; }        if (this->presentModes != nullptr) { needsFreeing = true; }        if (this->alphaModes != nullptr) { needsFreeing = true; }if (needsFreeing) {
            APISurfaceCapabilitiesFreeMembers(*reinterpret_cast<WGPUSurfaceCapabilities*>(this));
        }
    }

    // AdapterPropertiesMemoryHeaps
    AdapterPropertiesMemoryHeaps::~AdapterPropertiesMemoryHeaps() {
        FreeMembers();
    }

    AdapterPropertiesMemoryHeaps::AdapterPropertiesMemoryHeaps(AdapterPropertiesMemoryHeaps&& rhs)
    : heapCount(rhs.heapCount),
      heapInfo(rhs.heapInfo){
        rhs.heapCount = {};
        rhs.heapInfo = {};
    }

    AdapterPropertiesMemoryHeaps& AdapterPropertiesMemoryHeaps::operator=(AdapterPropertiesMemoryHeaps&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        FreeMembers();
        this->heapCount = std::move(rhs.heapCount);
        this->heapInfo = std::move(rhs.heapInfo);
        rhs.heapCount = {};
        rhs.heapInfo = {};
        return *this;
    }

    void AdapterPropertiesMemoryHeaps::FreeMembers() {
        bool needsFreeing = false;        if (this->heapInfo != nullptr) { needsFreeing = true; }if (needsFreeing) {
            APIAdapterPropertiesMemoryHeapsFreeMembers(*reinterpret_cast<WGPUAdapterPropertiesMemoryHeaps*>(this));
        }
    }

    // AdapterPropertiesSubgroupMatrixConfigs
    AdapterPropertiesSubgroupMatrixConfigs::~AdapterPropertiesSubgroupMatrixConfigs() {
        FreeMembers();
    }

    AdapterPropertiesSubgroupMatrixConfigs::AdapterPropertiesSubgroupMatrixConfigs(AdapterPropertiesSubgroupMatrixConfigs&& rhs)
    : configCount(rhs.configCount),
      configs(rhs.configs){
        rhs.configCount = {};
        rhs.configs = {};
    }

    AdapterPropertiesSubgroupMatrixConfigs& AdapterPropertiesSubgroupMatrixConfigs::operator=(AdapterPropertiesSubgroupMatrixConfigs&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        FreeMembers();
        this->configCount = std::move(rhs.configCount);
        this->configs = std::move(rhs.configs);
        rhs.configCount = {};
        rhs.configs = {};
        return *this;
    }

    void AdapterPropertiesSubgroupMatrixConfigs::FreeMembers() {
        bool needsFreeing = false;        if (this->configs != nullptr) { needsFreeing = true; }if (needsFreeing) {
            APIAdapterPropertiesSubgroupMatrixConfigsFreeMembers(*reinterpret_cast<WGPUAdapterPropertiesSubgroupMatrixConfigs*>(this));
        }
    }

    // DawnDrmFormatCapabilities
    DawnDrmFormatCapabilities::~DawnDrmFormatCapabilities() {
        FreeMembers();
    }

    DawnDrmFormatCapabilities::DawnDrmFormatCapabilities(DawnDrmFormatCapabilities&& rhs)
    : propertiesCount(rhs.propertiesCount),
      properties(rhs.properties){
        rhs.propertiesCount = {};
        rhs.properties = {};
    }

    DawnDrmFormatCapabilities& DawnDrmFormatCapabilities::operator=(DawnDrmFormatCapabilities&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        FreeMembers();
        this->propertiesCount = std::move(rhs.propertiesCount);
        this->properties = std::move(rhs.properties);
        rhs.propertiesCount = {};
        rhs.properties = {};
        return *this;
    }

    void DawnDrmFormatCapabilities::FreeMembers() {
        bool needsFreeing = false;        if (this->properties != nullptr) { needsFreeing = true; }if (needsFreeing) {
            APIDawnDrmFormatCapabilitiesFreeMembers(*reinterpret_cast<WGPUDawnDrmFormatCapabilities*>(this));
        }
    }

    // AdapterInfo
    AdapterInfo::~AdapterInfo() {
        FreeMembers();
    }

    AdapterInfo::AdapterInfo(AdapterInfo&& rhs)
    : vendor(rhs.vendor),
      architecture(rhs.architecture),
      device(rhs.device),
      description(rhs.description),
      backendType(rhs.backendType),
      adapterType(rhs.adapterType),
      vendorID(rhs.vendorID),
      deviceID(rhs.deviceID),
      subgroupMinSize(rhs.subgroupMinSize),
      subgroupMaxSize(rhs.subgroupMaxSize){
        rhs.vendor = {};
        rhs.architecture = {};
        rhs.device = {};
        rhs.description = {};
        rhs.backendType = {};
        rhs.adapterType = {};
        rhs.vendorID = {};
        rhs.deviceID = {};
        rhs.subgroupMinSize = {};
        rhs.subgroupMaxSize = {};
    }

    AdapterInfo& AdapterInfo::operator=(AdapterInfo&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        FreeMembers();
        this->vendor = std::move(rhs.vendor);
        this->architecture = std::move(rhs.architecture);
        this->device = std::move(rhs.device);
        this->description = std::move(rhs.description);
        this->backendType = std::move(rhs.backendType);
        this->adapterType = std::move(rhs.adapterType);
        this->vendorID = std::move(rhs.vendorID);
        this->deviceID = std::move(rhs.deviceID);
        this->subgroupMinSize = std::move(rhs.subgroupMinSize);
        this->subgroupMaxSize = std::move(rhs.subgroupMaxSize);
        rhs.vendor = {};
        rhs.architecture = {};
        rhs.device = {};
        rhs.description = {};
        rhs.backendType = {};
        rhs.adapterType = {};
        rhs.vendorID = {};
        rhs.deviceID = {};
        rhs.subgroupMinSize = {};
        rhs.subgroupMaxSize = {};
        return *this;
    }

    void AdapterInfo::FreeMembers() {
        bool needsFreeing = false;        if (this->vendor.data != nullptr) { needsFreeing = true; }        if (this->architecture.data != nullptr) { needsFreeing = true; }        if (this->device.data != nullptr) { needsFreeing = true; }        if (this->description.data != nullptr) { needsFreeing = true; }if (needsFreeing) {
            APIAdapterInfoFreeMembers(*reinterpret_cast<WGPUAdapterInfo*>(this));
        }
    }

    // SharedTextureMemoryEndAccessState
    SharedTextureMemoryEndAccessState::~SharedTextureMemoryEndAccessState() {
        FreeMembers();
    }

    SharedTextureMemoryEndAccessState::SharedTextureMemoryEndAccessState(SharedTextureMemoryEndAccessState&& rhs)
    : initialized(rhs.initialized),
      fenceCount(rhs.fenceCount),
      fences(rhs.fences),
      signaledValues(rhs.signaledValues){
        rhs.initialized = {};
        rhs.fenceCount = {};
        rhs.fences = {};
        rhs.signaledValues = {};
    }

    SharedTextureMemoryEndAccessState& SharedTextureMemoryEndAccessState::operator=(SharedTextureMemoryEndAccessState&& rhs) {
        if (&rhs == this) {
            return *this;
        }
        FreeMembers();
        this->initialized = std::move(rhs.initialized);
        this->fenceCount = std::move(rhs.fenceCount);
        this->fences = std::move(rhs.fences);
        this->signaledValues = std::move(rhs.signaledValues);
        rhs.initialized = {};
        rhs.fenceCount = {};
        rhs.fences = {};
        rhs.signaledValues = {};
        return *this;
    }

    void SharedTextureMemoryEndAccessState::FreeMembers() {
        bool needsFreeing = false;        if (this->fences != nullptr) { needsFreeing = true; }        if (this->signaledValues != nullptr) { needsFreeing = true; }if (needsFreeing) {
            APISharedTextureMemoryEndAccessStateFreeMembers(*reinterpret_cast<WGPUSharedTextureMemoryEndAccessState*>(this));
        }
    }


} // namespace dawn::native
