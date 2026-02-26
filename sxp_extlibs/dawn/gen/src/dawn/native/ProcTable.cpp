
#include "dawn/native/dawn_platform.h"
#include "dawn/native/DawnNative.h"

#include <algorithm>
#include <vector>

#include "dawn/native/Adapter.h"
#include "dawn/native/BindGroup.h"
#include "dawn/native/BindGroupLayout.h"
#include "dawn/native/Buffer.h"
#include "dawn/native/CommandBuffer.h"
#include "dawn/native/CommandEncoder.h"
#include "dawn/native/ComputePipeline.h"
#include "dawn/native/Device.h"
#include "dawn/native/ExternalTexture.h"
#include "dawn/native/Instance.h"
#include "dawn/native/PipelineLayout.h"
#include "dawn/native/QuerySet.h"
#include "dawn/native/Queue.h"
#include "dawn/native/RenderBundle.h"
#include "dawn/native/RenderPipeline.h"
#include "dawn/native/ResourceTable.h"
#include "dawn/native/Sampler.h"
#include "dawn/native/ShaderModule.h"
#include "dawn/native/SharedBufferMemory.h"
#include "dawn/native/SharedFence.h"
#include "dawn/native/SharedTextureMemory.h"
#include "dawn/native/Surface.h"
#include "dawn/native/TexelBufferView.h"
#include "dawn/native/Texture.h"
#include "dawn/native/ComputePassEncoder.h"
#include "dawn/native/RenderBundleEncoder.h"
#include "dawn/native/RenderPassEncoder.h"

namespace dawn::native {

    WGPUDevice NativeAdapterCreateDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<DeviceDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateDevice(descriptor_);
        return ToAPI(result);
    }

    void NativeAdapterGetFeatures(WGPUAdapter cSelf, WGPUSupportedFeatures * features) {
        auto self = FromAPI(cSelf);

        auto features_ = reinterpret_cast<SupportedFeatures *>(features);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIGetFeatures(features_);
    }

    WGPUStatus NativeAdapterGetFormatCapabilities(WGPUAdapter cSelf, WGPUTextureFormat format, WGPUDawnFormatCapabilities * capabilities) {
        auto self = FromAPI(cSelf);

        auto format_ = static_cast<wgpu::TextureFormat>(format);
        auto capabilities_ = reinterpret_cast<DawnFormatCapabilities *>(capabilities);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetFormatCapabilities(format_, capabilities_);
        return ToAPI(result);
    }

    WGPUStatus NativeAdapterGetInfo(WGPUAdapter cSelf, WGPUAdapterInfo * info) {
        auto self = FromAPI(cSelf);

        auto info_ = reinterpret_cast<AdapterInfo *>(info);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetInfo(info_);
        return ToAPI(result);
    }

    WGPUInstance NativeAdapterGetInstance(WGPUAdapter cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetInstance();
        return ToAPI(result);
    }

    WGPUStatus NativeAdapterGetLimits(WGPUAdapter cSelf, WGPULimits * limits) {
        auto self = FromAPI(cSelf);

        auto limits_ = reinterpret_cast<Limits *>(limits);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetLimits(limits_);
        return ToAPI(result);
    }

    WGPUBool NativeAdapterHasFeature(WGPUAdapter cSelf, WGPUFeatureName feature) {
        auto self = FromAPI(cSelf);

        auto feature_ = static_cast<wgpu::FeatureName>(feature);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIHasFeature(feature_);
        return result;
    }

    WGPUFuture NativeAdapterRequestDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallbackInfo callbackInfo) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<DeviceDescriptor const *>(descriptor);
        auto callbackInfo_ = callbackInfo;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIRequestDevice(descriptor_, callbackInfo_);
        return *ToAPI(&result);
    }

    void NativeAdapterAddRef(WGPUAdapter cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeAdapterRelease(WGPUAdapter cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeAdapterInfoFreeMembers(WGPUAdapterInfo cSelf) {

        // This method is specified to not use AutoLock in json script or it returns a future.

        APIAdapterInfoFreeMembers(cSelf);
    }

    void NativeAdapterPropertiesMemoryHeapsFreeMembers(WGPUAdapterPropertiesMemoryHeaps cSelf) {

        // This method is specified to not use AutoLock in json script or it returns a future.

        APIAdapterPropertiesMemoryHeapsFreeMembers(cSelf);
    }

    void NativeAdapterPropertiesSubgroupMatrixConfigsFreeMembers(WGPUAdapterPropertiesSubgroupMatrixConfigs cSelf) {

        // This method is specified to not use AutoLock in json script or it returns a future.

        APIAdapterPropertiesSubgroupMatrixConfigsFreeMembers(cSelf);
    }

    void NativeBindGroupSetLabel(WGPUBindGroup cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeBindGroupAddRef(WGPUBindGroup cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeBindGroupRelease(WGPUBindGroup cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeBindGroupLayoutSetLabel(WGPUBindGroupLayout cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeBindGroupLayoutAddRef(WGPUBindGroupLayout cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeBindGroupLayoutRelease(WGPUBindGroupLayout cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    WGPUTexelBufferView NativeBufferCreateTexelView(WGPUBuffer cSelf, WGPUTexelBufferViewDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TexelBufferViewDescriptor const *>(descriptor);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateTexelView(descriptor_);
        return ToAPI(result);
    }

    void NativeBufferDestroy(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDestroy();
    }

    void const * NativeBufferGetConstMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        auto self = FromAPI(cSelf);

        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetConstMappedRange(offset_, size_);
        return result;
    }

    void * NativeBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        auto self = FromAPI(cSelf);

        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetMappedRange(offset_, size_);
        return result;
    }

    WGPUBufferMapState NativeBufferGetMapState(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetMapState();
        return ToAPI(result);
    }

    uint64_t NativeBufferGetSize(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetSize();
        return result;
    }

    WGPUBufferUsage NativeBufferGetUsage(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetUsage();
        return ToAPI(result);
    }

    WGPUFuture NativeBufferMapAsync(WGPUBuffer cSelf, WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo) {
        auto self = FromAPI(cSelf);

        auto mode_ = static_cast<wgpu::MapMode>(mode);
        auto offset_ = offset;
        auto size_ = size;
        auto callbackInfo_ = callbackInfo;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIMapAsync(mode_, offset_, size_, callbackInfo_);
        return *ToAPI(&result);
    }

    WGPUStatus NativeBufferReadMappedRange(WGPUBuffer cSelf, size_t offset, void * data, size_t size) {
        auto self = FromAPI(cSelf);

        auto offset_ = offset;
        auto data_ = reinterpret_cast<void *>(data);
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIReadMappedRange(offset_, data_, size_);
        return ToAPI(result);
    }

    void NativeBufferSetLabel(WGPUBuffer cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeBufferUnmap(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIUnmap();
    }

    WGPUStatus NativeBufferWriteMappedRange(WGPUBuffer cSelf, size_t offset, void const * data, size_t size) {
        auto self = FromAPI(cSelf);

        auto offset_ = offset;
        auto data_ = reinterpret_cast<void const *>(data);
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIWriteMappedRange(offset_, data_, size_);
        return ToAPI(result);
    }

    void NativeBufferAddRef(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeBufferRelease(WGPUBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeCommandBufferSetLabel(WGPUCommandBuffer cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeCommandBufferAddRef(WGPUCommandBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeCommandBufferRelease(WGPUCommandBuffer cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    WGPUComputePassEncoder NativeCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ComputePassDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIBeginComputePass(descriptor_);
        return ToAPI(result);
    }

    WGPURenderPassEncoder NativeCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<RenderPassDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIBeginRenderPass(descriptor_);
        return ToAPI(result);
    }

    void NativeCommandEncoderClearBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase*>(buffer);
        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIClearBuffer(buffer_, offset_, size_);
    }

    void NativeCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder cSelf, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<BufferBase*>(source);
        auto sourceOffset_ = sourceOffset;
        auto destination_ = reinterpret_cast<BufferBase*>(destination);
        auto destinationOffset_ = destinationOffset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APICopyBufferToBuffer(source_, sourceOffset_, destination_, destinationOffset_, size_);
    }

    void NativeCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUTexelCopyBufferInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<TexelCopyBufferInfo const *>(source);
        auto destination_ = reinterpret_cast<TexelCopyTextureInfo const *>(destination);
        auto copySize_ = reinterpret_cast<Extent3D const *>(copySize);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APICopyBufferToTexture(source_, destination_, copySize_);
    }

    void NativeCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyBufferInfo const * destination, WGPUExtent3D const * copySize) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<TexelCopyTextureInfo const *>(source);
        auto destination_ = reinterpret_cast<TexelCopyBufferInfo const *>(destination);
        auto copySize_ = reinterpret_cast<Extent3D const *>(copySize);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APICopyTextureToBuffer(source_, destination_, copySize_);
    }

    void NativeCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<TexelCopyTextureInfo const *>(source);
        auto destination_ = reinterpret_cast<TexelCopyTextureInfo const *>(destination);
        auto copySize_ = reinterpret_cast<Extent3D const *>(copySize);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APICopyTextureToTexture(source_, destination_, copySize_);
    }

    WGPUCommandBuffer NativeCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<CommandBufferDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIFinish(descriptor_);
        return ToAPI(result);
    }

    void NativeCommandEncoderInjectValidationError(WGPUCommandEncoder cSelf, WGPUStringView message) {
        auto self = FromAPI(cSelf);

        auto message_ = *reinterpret_cast<StringView*>(&message);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIInjectValidationError(message_);
    }

    void NativeCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, WGPUStringView markerLabel) {
        auto self = FromAPI(cSelf);

        auto markerLabel_ = *reinterpret_cast<StringView*>(&markerLabel);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIInsertDebugMarker(markerLabel_);
    }

    void NativeCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIPopDebugGroup();
    }

    void NativeCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, WGPUStringView groupLabel) {
        auto self = FromAPI(cSelf);

        auto groupLabel_ = *reinterpret_cast<StringView*>(&groupLabel);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIPushDebugGroup(groupLabel_);
    }

    void NativeCommandEncoderResolveQuerySet(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
        auto self = FromAPI(cSelf);

        auto querySet_ = reinterpret_cast<QuerySetBase*>(querySet);
        auto firstQuery_ = firstQuery;
        auto queryCount_ = queryCount;
        auto destination_ = reinterpret_cast<BufferBase*>(destination);
        auto destinationOffset_ = destinationOffset;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIResolveQuerySet(querySet_, firstQuery_, queryCount_, destination_, destinationOffset_);
    }

    void NativeCommandEncoderSetLabel(WGPUCommandEncoder cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetLabel(label_);
    }

    void NativeCommandEncoderWriteBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase*>(buffer);
        auto bufferOffset_ = bufferOffset;
        auto data_ = reinterpret_cast<uint8_t const *>(data);
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIWriteBuffer(buffer_, bufferOffset_, data_, size_);
    }

    void NativeCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = FromAPI(cSelf);

        auto querySet_ = reinterpret_cast<QuerySetBase*>(querySet);
        auto queryIndex_ = queryIndex;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIWriteTimestamp(querySet_, queryIndex_);
    }

    void NativeCommandEncoderAddRef(WGPUCommandEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeCommandEncoderRelease(WGPUCommandEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder cSelf, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
        auto self = FromAPI(cSelf);

        auto workgroupCountX_ = workgroupCountX;
        auto workgroupCountY_ = workgroupCountY;
        auto workgroupCountZ_ = workgroupCountZ;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDispatchWorkgroups(workgroupCountX_, workgroupCountY_, workgroupCountZ_);
    }

    void NativeComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase*>(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDispatchWorkgroupsIndirect(indirectBuffer_, indirectOffset_);
    }

    void NativeComputePassEncoderEnd(WGPUComputePassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIEnd();
    }

    void NativeComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, WGPUStringView markerLabel) {
        auto self = FromAPI(cSelf);

        auto markerLabel_ = *reinterpret_cast<StringView*>(&markerLabel);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIInsertDebugMarker(markerLabel_);
    }

    void NativeComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIPopDebugGroup();
    }

    void NativeComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, WGPUStringView groupLabel) {
        auto self = FromAPI(cSelf);

        auto groupLabel_ = *reinterpret_cast<StringView*>(&groupLabel);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIPushDebugGroup(groupLabel_);
    }

    void NativeComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = FromAPI(cSelf);

        auto groupIndex_ = groupIndex;
        auto group_ = reinterpret_cast<BindGroupBase*>(group);
        auto dynamicOffsetCount_ = dynamicOffsetCount;
        auto dynamicOffsets_ = reinterpret_cast<uint32_t const *>(dynamicOffsets);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
    }

    void NativeComputePassEncoderSetImmediates(WGPUComputePassEncoder cSelf, uint32_t offset, void const * data, size_t size) {
        auto self = FromAPI(cSelf);

        auto offset_ = offset;
        auto data_ = reinterpret_cast<void const *>(data);
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetImmediates(offset_, data_, size_);
    }

    void NativeComputePassEncoderSetLabel(WGPUComputePassEncoder cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetLabel(label_);
    }

    void NativeComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline) {
        auto self = FromAPI(cSelf);

        auto pipeline_ = reinterpret_cast<ComputePipelineBase*>(pipeline);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetPipeline(pipeline_);
    }

    void NativeComputePassEncoderSetResourceTable(WGPUComputePassEncoder cSelf, WGPUResourceTable table) {
        auto self = FromAPI(cSelf);

        auto table_ = reinterpret_cast<ResourceTableBase*>(table);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetResourceTable(table_);
    }

    void NativeComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = FromAPI(cSelf);

        auto querySet_ = reinterpret_cast<QuerySetBase*>(querySet);
        auto queryIndex_ = queryIndex;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIWriteTimestamp(querySet_, queryIndex_);
    }

    void NativeComputePassEncoderAddRef(WGPUComputePassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeComputePassEncoderRelease(WGPUComputePassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    WGPUBindGroupLayout NativeComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex) {
        auto self = FromAPI(cSelf);

        auto groupIndex_ = groupIndex;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetBindGroupLayout(groupIndex_);
        return ToAPI(result);
    }

    void NativeComputePipelineSetLabel(WGPUComputePipeline cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeComputePipelineAddRef(WGPUComputePipeline cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeComputePipelineRelease(WGPUComputePipeline cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeDawnDrmFormatCapabilitiesFreeMembers(WGPUDawnDrmFormatCapabilities cSelf) {

        // This method is specified to not use AutoLock in json script or it returns a future.

        APIDawnDrmFormatCapabilitiesFreeMembers(cSelf);
    }

    WGPUBindGroup NativeDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<BindGroupDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateBindGroup(descriptor_);
        return ToAPI(result);
    }

    WGPUBindGroupLayout NativeDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<BindGroupLayoutDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateBindGroupLayout(descriptor_);
        return ToAPI(result);
    }

    WGPUBuffer NativeDeviceCreateBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<BufferDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateBuffer(descriptor_);
        return ToAPI(result);
    }

    WGPUCommandEncoder NativeDeviceCreateCommandEncoder(WGPUDevice cSelf, WGPUCommandEncoderDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<CommandEncoderDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateCommandEncoder(descriptor_);
        return ToAPI(result);
    }

    WGPUComputePipeline NativeDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ComputePipelineDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateComputePipeline(descriptor_);
        return ToAPI(result);
    }

    WGPUFuture NativeDeviceCreateComputePipelineAsync(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ComputePipelineDescriptor const *>(descriptor);
        auto callbackInfo_ = callbackInfo;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateComputePipelineAsync(descriptor_, callbackInfo_);
        return *ToAPI(&result);
    }

    WGPUBuffer NativeDeviceCreateErrorBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<BufferDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateErrorBuffer(descriptor_);
        return ToAPI(result);
    }

    WGPUExternalTexture NativeDeviceCreateErrorExternalTexture(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateErrorExternalTexture();
        return ToAPI(result);
    }

    WGPUShaderModule NativeDeviceCreateErrorShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor, WGPUStringView errorMessage) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ShaderModuleDescriptor const *>(descriptor);
        auto errorMessage_ = *reinterpret_cast<StringView*>(&errorMessage);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateErrorShaderModule(descriptor_, errorMessage_);
        return ToAPI(result);
    }

    WGPUTexture NativeDeviceCreateErrorTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TextureDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateErrorTexture(descriptor_);
        return ToAPI(result);
    }

    WGPUExternalTexture NativeDeviceCreateExternalTexture(WGPUDevice cSelf, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
        auto self = FromAPI(cSelf);

        auto externalTextureDescriptor_ = reinterpret_cast<ExternalTextureDescriptor const *>(externalTextureDescriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateExternalTexture(externalTextureDescriptor_);
        return ToAPI(result);
    }

    WGPUPipelineLayout NativeDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<PipelineLayoutDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreatePipelineLayout(descriptor_);
        return ToAPI(result);
    }

    WGPUQuerySet NativeDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<QuerySetDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateQuerySet(descriptor_);
        return ToAPI(result);
    }

    WGPURenderBundleEncoder NativeDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<RenderBundleEncoderDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateRenderBundleEncoder(descriptor_);
        return ToAPI(result);
    }

    WGPURenderPipeline NativeDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<RenderPipelineDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateRenderPipeline(descriptor_);
        return ToAPI(result);
    }

    WGPUFuture NativeDeviceCreateRenderPipelineAsync(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<RenderPipelineDescriptor const *>(descriptor);
        auto callbackInfo_ = callbackInfo;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateRenderPipelineAsync(descriptor_, callbackInfo_);
        return *ToAPI(&result);
    }

    WGPUResourceTable NativeDeviceCreateResourceTable(WGPUDevice cSelf, WGPUResourceTableDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ResourceTableDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateResourceTable(descriptor_);
        return ToAPI(result);
    }

    WGPUSampler NativeDeviceCreateSampler(WGPUDevice cSelf, WGPUSamplerDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<SamplerDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateSampler(descriptor_);
        return ToAPI(result);
    }

    WGPUShaderModule NativeDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<ShaderModuleDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateShaderModule(descriptor_);
        return ToAPI(result);
    }

    WGPUTexture NativeDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TextureDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateTexture(descriptor_);
        return ToAPI(result);
    }

    void NativeDeviceDestroy(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self;
        auto deviceGuard = device->GetGuard();

        self->APIDestroy();
    }

    void NativeDeviceForceLoss(WGPUDevice cSelf, WGPUDeviceLostReason type, WGPUStringView message) {
        auto self = FromAPI(cSelf);

        auto type_ = static_cast<wgpu::DeviceLostReason>(type);
        auto message_ = *reinterpret_cast<StringView*>(&message);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        self->APIForceLoss(type_, message_);
    }

    WGPUAdapter NativeDeviceGetAdapter(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetAdapter();
        return ToAPI(result);
    }

    WGPUStatus NativeDeviceGetAdapterInfo(WGPUDevice cSelf, WGPUAdapterInfo * adapterInfo) {
        auto self = FromAPI(cSelf);

        auto adapterInfo_ = reinterpret_cast<AdapterInfo *>(adapterInfo);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetAdapterInfo(adapterInfo_);
        return ToAPI(result);
    }

    WGPUStatus NativeDeviceGetAHardwareBufferProperties(WGPUDevice cSelf, void * handle, WGPUAHardwareBufferProperties * properties) {
        auto self = FromAPI(cSelf);

        auto handle_ = handle;
        auto properties_ = reinterpret_cast<AHardwareBufferProperties *>(properties);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIGetAHardwareBufferProperties(handle_, properties_);
        return ToAPI(result);
    }

    void NativeDeviceGetFeatures(WGPUDevice cSelf, WGPUSupportedFeatures * features) {
        auto self = FromAPI(cSelf);

        auto features_ = reinterpret_cast<SupportedFeatures *>(features);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIGetFeatures(features_);
    }

    WGPUStatus NativeDeviceGetLimits(WGPUDevice cSelf, WGPULimits * limits) {
        auto self = FromAPI(cSelf);

        auto limits_ = reinterpret_cast<Limits *>(limits);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetLimits(limits_);
        return ToAPI(result);
    }

    WGPUFuture NativeDeviceGetLostFuture(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetLostFuture();
        return *ToAPI(&result);
    }

    WGPUQueue NativeDeviceGetQueue(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetQueue();
        return ToAPI(result);
    }

    WGPUBool NativeDeviceHasFeature(WGPUDevice cSelf, WGPUFeatureName feature) {
        auto self = FromAPI(cSelf);

        auto feature_ = static_cast<wgpu::FeatureName>(feature);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIHasFeature(feature_);
        return result;
    }

    WGPUSharedBufferMemory NativeDeviceImportSharedBufferMemory(WGPUDevice cSelf, WGPUSharedBufferMemoryDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<SharedBufferMemoryDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIImportSharedBufferMemory(descriptor_);
        return ToAPI(result);
    }

    WGPUSharedFence NativeDeviceImportSharedFence(WGPUDevice cSelf, WGPUSharedFenceDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<SharedFenceDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIImportSharedFence(descriptor_);
        return ToAPI(result);
    }

    WGPUSharedTextureMemory NativeDeviceImportSharedTextureMemory(WGPUDevice cSelf, WGPUSharedTextureMemoryDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<SharedTextureMemoryDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIImportSharedTextureMemory(descriptor_);
        return ToAPI(result);
    }

    void NativeDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, WGPUStringView message) {
        auto self = FromAPI(cSelf);

        auto type_ = static_cast<wgpu::ErrorType>(type);
        auto message_ = *reinterpret_cast<StringView*>(&message);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        self->APIInjectError(type_, message_);
    }

    WGPUFuture NativeDevicePopErrorScope(WGPUDevice cSelf, WGPUPopErrorScopeCallbackInfo callbackInfo) {
        auto self = FromAPI(cSelf);

        auto callbackInfo_ = callbackInfo;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIPopErrorScope(callbackInfo_);
        return *ToAPI(&result);
    }

    void NativeDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter) {
        auto self = FromAPI(cSelf);

        auto filter_ = static_cast<wgpu::ErrorFilter>(filter);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        self->APIPushErrorScope(filter_);
    }

    void NativeDeviceSetLabel(WGPUDevice cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeDeviceSetLoggingCallback(WGPUDevice cSelf, WGPULoggingCallbackInfo callbackInfo) {
        auto self = FromAPI(cSelf);

        auto callbackInfo_ = callbackInfo;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetLoggingCallback(callbackInfo_);
    }

    void NativeDeviceTick(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APITick();
    }

    void NativeDeviceValidateTextureDescriptor(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TextureDescriptor const *>(descriptor);
        auto device = self;
        auto deviceGuard = device->GetGuard();

        self->APIValidateTextureDescriptor(descriptor_);
    }

    void NativeDeviceAddRef(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeDeviceRelease(WGPUDevice cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeExternalTextureDestroy(WGPUExternalTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIDestroy();
    }

    void NativeExternalTextureExpire(WGPUExternalTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIExpire();
    }

    void NativeExternalTextureRefresh(WGPUExternalTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIRefresh();
    }

    void NativeExternalTextureSetLabel(WGPUExternalTexture cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeExternalTextureAddRef(WGPUExternalTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeExternalTextureRelease(WGPUExternalTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    WGPUSurface NativeInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<SurfaceDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateSurface(descriptor_);
        return ToAPI(result);
    }

    void NativeInstanceGetWGSLLanguageFeatures(WGPUInstance cSelf, WGPUSupportedWGSLLanguageFeatures * features) {
        auto self = FromAPI(cSelf);

        auto features_ = reinterpret_cast<SupportedWGSLLanguageFeatures *>(features);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIGetWGSLLanguageFeatures(features_);
    }

    WGPUBool NativeInstanceHasWGSLLanguageFeature(WGPUInstance cSelf, WGPUWGSLLanguageFeatureName feature) {
        auto self = FromAPI(cSelf);

        auto feature_ = static_cast<wgpu::WGSLLanguageFeatureName>(feature);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIHasWGSLLanguageFeature(feature_);
        return result;
    }

    void NativeInstanceProcessEvents(WGPUInstance cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIProcessEvents();
    }

    WGPUFuture NativeInstanceRequestAdapter(WGPUInstance cSelf, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallbackInfo callbackInfo) {
        auto self = FromAPI(cSelf);

        auto options_ = reinterpret_cast<RequestAdapterOptions const *>(options);
        auto callbackInfo_ = callbackInfo;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIRequestAdapter(options_, callbackInfo_);
        return *ToAPI(&result);
    }

    WGPUWaitStatus NativeInstanceWaitAny(WGPUInstance cSelf, size_t futureCount, WGPUFutureWaitInfo * futures, uint64_t timeoutNS) {
        auto self = FromAPI(cSelf);

        auto futureCount_ = futureCount;
        auto futures_ = reinterpret_cast<FutureWaitInfo *>(futures);
        auto timeoutNS_ = timeoutNS;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIWaitAny(futureCount_, futures_, timeoutNS_);
        return ToAPI(result);
    }

    void NativeInstanceAddRef(WGPUInstance cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeInstanceRelease(WGPUInstance cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativePipelineLayoutSetLabel(WGPUPipelineLayout cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativePipelineLayoutAddRef(WGPUPipelineLayout cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativePipelineLayoutRelease(WGPUPipelineLayout cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeQuerySetDestroy(WGPUQuerySet cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIDestroy();
    }

    uint32_t NativeQuerySetGetCount(WGPUQuerySet cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIGetCount();
        return result;
    }

    WGPUQueryType NativeQuerySetGetType(WGPUQuerySet cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIGetType();
        return ToAPI(result);
    }

    void NativeQuerySetSetLabel(WGPUQuerySet cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeQuerySetAddRef(WGPUQuerySet cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeQuerySetRelease(WGPUQuerySet cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeQueueCopyExternalTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyExternalTexture const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<ImageCopyExternalTexture const *>(source);
        auto destination_ = reinterpret_cast<TexelCopyTextureInfo const *>(destination);
        auto copySize_ = reinterpret_cast<Extent3D const *>(copySize);
        auto options_ = reinterpret_cast<CopyTextureForBrowserOptions const *>(options);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APICopyExternalTextureForBrowser(source_, destination_, copySize_, options_);
    }

    void NativeQueueCopyTextureForBrowser(WGPUQueue cSelf, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        auto self = FromAPI(cSelf);

        auto source_ = reinterpret_cast<TexelCopyTextureInfo const *>(source);
        auto destination_ = reinterpret_cast<TexelCopyTextureInfo const *>(destination);
        auto copySize_ = reinterpret_cast<Extent3D const *>(copySize);
        auto options_ = reinterpret_cast<CopyTextureForBrowserOptions const *>(options);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APICopyTextureForBrowser(source_, destination_, copySize_, options_);
    }

    WGPUFuture NativeQueueOnSubmittedWorkDone(WGPUQueue cSelf, WGPUQueueWorkDoneCallbackInfo callbackInfo) {
        auto self = FromAPI(cSelf);

        auto callbackInfo_ = callbackInfo;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIOnSubmittedWorkDone(callbackInfo_);
        return *ToAPI(&result);
    }

    void NativeQueueSetLabel(WGPUQueue cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeQueueSubmit(WGPUQueue cSelf, size_t commandCount, WGPUCommandBuffer const * commands) {
        auto self = FromAPI(cSelf);

        auto commandCount_ = commandCount;
        auto commands_ = reinterpret_cast<CommandBufferBase* const *>(commands);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISubmit(commandCount_, commands_);
    }

    void NativeQueueWriteBuffer(WGPUQueue cSelf, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase*>(buffer);
        auto bufferOffset_ = bufferOffset;
        auto data_ = reinterpret_cast<void const *>(data);
        auto size_ = size;
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIWriteBuffer(buffer_, bufferOffset_, data_, size_);
    }

    void NativeQueueWriteTexture(WGPUQueue cSelf, WGPUTexelCopyTextureInfo const * destination, void const * data, size_t dataSize, WGPUTexelCopyBufferLayout const * dataLayout, WGPUExtent3D const * writeSize) {
        auto self = FromAPI(cSelf);

        auto destination_ = reinterpret_cast<TexelCopyTextureInfo const *>(destination);
        auto data_ = reinterpret_cast<void const *>(data);
        auto dataSize_ = dataSize;
        auto dataLayout_ = reinterpret_cast<TexelCopyBufferLayout const *>(dataLayout);
        auto writeSize_ = reinterpret_cast<Extent3D const *>(writeSize);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIWriteTexture(destination_, data_, dataSize_, dataLayout_, writeSize_);
    }

    void NativeQueueAddRef(WGPUQueue cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeQueueRelease(WGPUQueue cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeRenderBundleSetLabel(WGPURenderBundle cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeRenderBundleAddRef(WGPURenderBundle cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeRenderBundleRelease(WGPURenderBundle cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto self = FromAPI(cSelf);

        auto vertexCount_ = vertexCount;
        auto instanceCount_ = instanceCount;
        auto firstVertex_ = firstVertex;
        auto firstInstance_ = firstInstance;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDraw(vertexCount_, instanceCount_, firstVertex_, firstInstance_);
    }

    void NativeRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        auto self = FromAPI(cSelf);

        auto indexCount_ = indexCount;
        auto instanceCount_ = instanceCount;
        auto firstIndex_ = firstIndex;
        auto baseVertex_ = baseVertex;
        auto firstInstance_ = firstInstance;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDrawIndexed(indexCount_, instanceCount_, firstIndex_, baseVertex_, firstInstance_);
    }

    void NativeRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase*>(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDrawIndexedIndirect(indirectBuffer_, indirectOffset_);
    }

    void NativeRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase*>(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDrawIndirect(indirectBuffer_, indirectOffset_);
    }

    WGPURenderBundle NativeRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<RenderBundleDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIFinish(descriptor_);
        return ToAPI(result);
    }

    void NativeRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, WGPUStringView markerLabel) {
        auto self = FromAPI(cSelf);

        auto markerLabel_ = *reinterpret_cast<StringView*>(&markerLabel);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIInsertDebugMarker(markerLabel_);
    }

    void NativeRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIPopDebugGroup();
    }

    void NativeRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, WGPUStringView groupLabel) {
        auto self = FromAPI(cSelf);

        auto groupLabel_ = *reinterpret_cast<StringView*>(&groupLabel);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIPushDebugGroup(groupLabel_);
    }

    void NativeRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = FromAPI(cSelf);

        auto groupIndex_ = groupIndex;
        auto group_ = reinterpret_cast<BindGroupBase*>(group);
        auto dynamicOffsetCount_ = dynamicOffsetCount;
        auto dynamicOffsets_ = reinterpret_cast<uint32_t const *>(dynamicOffsets);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
    }

    void NativeRenderBundleEncoderSetImmediates(WGPURenderBundleEncoder cSelf, uint32_t offset, void const * data, size_t size) {
        auto self = FromAPI(cSelf);

        auto offset_ = offset;
        auto data_ = reinterpret_cast<void const *>(data);
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetImmediates(offset_, data_, size_);
    }

    void NativeRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase*>(buffer);
        auto format_ = static_cast<wgpu::IndexFormat>(format);
        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetIndexBuffer(buffer_, format_, offset_, size_);
    }

    void NativeRenderBundleEncoderSetLabel(WGPURenderBundleEncoder cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetLabel(label_);
    }

    void NativeRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline) {
        auto self = FromAPI(cSelf);

        auto pipeline_ = reinterpret_cast<RenderPipelineBase*>(pipeline);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetPipeline(pipeline_);
    }

    void NativeRenderBundleEncoderSetResourceTable(WGPURenderBundleEncoder cSelf, WGPUResourceTable table) {
        auto self = FromAPI(cSelf);

        auto table_ = reinterpret_cast<ResourceTableBase*>(table);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetResourceTable(table_);
    }

    void NativeRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto slot_ = slot;
        auto buffer_ = reinterpret_cast<BufferBase*>(buffer);
        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetVertexBuffer(slot_, buffer_, offset_, size_);
    }

    void NativeRenderBundleEncoderAddRef(WGPURenderBundleEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeRenderBundleEncoderRelease(WGPURenderBundleEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder cSelf, uint32_t queryIndex) {
        auto self = FromAPI(cSelf);

        auto queryIndex_ = queryIndex;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIBeginOcclusionQuery(queryIndex_);
    }

    void NativeRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        auto self = FromAPI(cSelf);

        auto vertexCount_ = vertexCount;
        auto instanceCount_ = instanceCount;
        auto firstVertex_ = firstVertex;
        auto firstInstance_ = firstInstance;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDraw(vertexCount_, instanceCount_, firstVertex_, firstInstance_);
    }

    void NativeRenderPassEncoderDrawIndexed(WGPURenderPassEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        auto self = FromAPI(cSelf);

        auto indexCount_ = indexCount;
        auto instanceCount_ = instanceCount;
        auto firstIndex_ = firstIndex;
        auto baseVertex_ = baseVertex;
        auto firstInstance_ = firstInstance;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDrawIndexed(indexCount_, instanceCount_, firstIndex_, baseVertex_, firstInstance_);
    }

    void NativeRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase*>(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDrawIndexedIndirect(indirectBuffer_, indirectOffset_);
    }

    void NativeRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase*>(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIDrawIndirect(indirectBuffer_, indirectOffset_);
    }

    void NativeRenderPassEncoderEnd(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIEnd();
    }

    void NativeRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIEndOcclusionQuery();
    }

    void NativeRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, size_t bundleCount, WGPURenderBundle const * bundles) {
        auto self = FromAPI(cSelf);

        auto bundleCount_ = bundleCount;
        auto bundles_ = reinterpret_cast<RenderBundleBase* const *>(bundles);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIExecuteBundles(bundleCount_, bundles_);
    }

    void NativeRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, WGPUStringView markerLabel) {
        auto self = FromAPI(cSelf);

        auto markerLabel_ = *reinterpret_cast<StringView*>(&markerLabel);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIInsertDebugMarker(markerLabel_);
    }

    void NativeRenderPassEncoderMultiDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase*>(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        auto maxDrawCount_ = maxDrawCount;
        auto drawCountBuffer_ = reinterpret_cast<BufferBase*>(drawCountBuffer);
        auto drawCountBufferOffset_ = drawCountBufferOffset;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIMultiDrawIndexedIndirect(indirectBuffer_, indirectOffset_, maxDrawCount_, drawCountBuffer_, drawCountBufferOffset_);
    }

    void NativeRenderPassEncoderMultiDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) {
        auto self = FromAPI(cSelf);

        auto indirectBuffer_ = reinterpret_cast<BufferBase*>(indirectBuffer);
        auto indirectOffset_ = indirectOffset;
        auto maxDrawCount_ = maxDrawCount;
        auto drawCountBuffer_ = reinterpret_cast<BufferBase*>(drawCountBuffer);
        auto drawCountBufferOffset_ = drawCountBufferOffset;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIMultiDrawIndirect(indirectBuffer_, indirectOffset_, maxDrawCount_, drawCountBuffer_, drawCountBufferOffset_);
    }

    void NativeRenderPassEncoderPixelLocalStorageBarrier(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIPixelLocalStorageBarrier();
    }

    void NativeRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIPopDebugGroup();
    }

    void NativeRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, WGPUStringView groupLabel) {
        auto self = FromAPI(cSelf);

        auto groupLabel_ = *reinterpret_cast<StringView*>(&groupLabel);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIPushDebugGroup(groupLabel_);
    }

    void NativeRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        auto self = FromAPI(cSelf);

        auto groupIndex_ = groupIndex;
        auto group_ = reinterpret_cast<BindGroupBase*>(group);
        auto dynamicOffsetCount_ = dynamicOffsetCount;
        auto dynamicOffsets_ = reinterpret_cast<uint32_t const *>(dynamicOffsets);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetBindGroup(groupIndex_, group_, dynamicOffsetCount_, dynamicOffsets_);
    }

    void NativeRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder cSelf, WGPUColor const * color) {
        auto self = FromAPI(cSelf);

        auto color_ = reinterpret_cast<Color const *>(color);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetBlendConstant(color_);
    }

    void NativeRenderPassEncoderSetImmediates(WGPURenderPassEncoder cSelf, uint32_t offset, void const * data, size_t size) {
        auto self = FromAPI(cSelf);

        auto offset_ = offset;
        auto data_ = reinterpret_cast<void const *>(data);
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetImmediates(offset_, data_, size_);
    }

    void NativeRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase*>(buffer);
        auto format_ = static_cast<wgpu::IndexFormat>(format);
        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetIndexBuffer(buffer_, format_, offset_, size_);
    }

    void NativeRenderPassEncoderSetLabel(WGPURenderPassEncoder cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetLabel(label_);
    }

    void NativeRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline) {
        auto self = FromAPI(cSelf);

        auto pipeline_ = reinterpret_cast<RenderPipelineBase*>(pipeline);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetPipeline(pipeline_);
    }

    void NativeRenderPassEncoderSetResourceTable(WGPURenderPassEncoder cSelf, WGPUResourceTable table) {
        auto self = FromAPI(cSelf);

        auto table_ = reinterpret_cast<ResourceTableBase*>(table);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetResourceTable(table_);
    }

    void NativeRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        auto self = FromAPI(cSelf);

        auto x_ = x;
        auto y_ = y;
        auto width_ = width;
        auto height_ = height;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetScissorRect(x_, y_, width_, height_);
    }

    void NativeRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference) {
        auto self = FromAPI(cSelf);

        auto reference_ = reference;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetStencilReference(reference_);
    }

    void NativeRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        auto self = FromAPI(cSelf);

        auto slot_ = slot;
        auto buffer_ = reinterpret_cast<BufferBase*>(buffer);
        auto offset_ = offset;
        auto size_ = size;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetVertexBuffer(slot_, buffer_, offset_, size_);
    }

    void NativeRenderPassEncoderSetViewport(WGPURenderPassEncoder cSelf, float x, float y, float width, float height, float minDepth, float maxDepth) {
        auto self = FromAPI(cSelf);

        auto x_ = x;
        auto y_ = y;
        auto width_ = width;
        auto height_ = height;
        auto minDepth_ = minDepth;
        auto maxDepth_ = maxDepth;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetViewport(x_, y_, width_, height_, minDepth_, maxDepth_);
    }

    void NativeRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        auto self = FromAPI(cSelf);

        auto querySet_ = reinterpret_cast<QuerySetBase*>(querySet);
        auto queryIndex_ = queryIndex;
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIWriteTimestamp(querySet_, queryIndex_);
    }

    void NativeRenderPassEncoderAddRef(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeRenderPassEncoderRelease(WGPURenderPassEncoder cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    WGPUBindGroupLayout NativeRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex) {
        auto self = FromAPI(cSelf);

        auto groupIndex_ = groupIndex;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetBindGroupLayout(groupIndex_);
        return ToAPI(result);
    }

    void NativeRenderPipelineSetLabel(WGPURenderPipeline cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeRenderPipelineAddRef(WGPURenderPipeline cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeRenderPipelineRelease(WGPURenderPipeline cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeResourceTableDestroy(WGPUResourceTable cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIDestroy();
    }

    uint32_t NativeResourceTableGetSize(WGPUResourceTable cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetSize();
        return result;
    }

    uint32_t NativeResourceTableInsertBinding(WGPUResourceTable cSelf, WGPUBindingResource const * resource) {
        auto self = FromAPI(cSelf);

        auto resource_ = reinterpret_cast<BindingResource const *>(resource);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIInsertBinding(resource_);
        return result;
    }

    WGPUStatus NativeResourceTableRemoveBinding(WGPUResourceTable cSelf, uint32_t slot) {
        auto self = FromAPI(cSelf);

        auto slot_ = slot;
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIRemoveBinding(slot_);
        return ToAPI(result);
    }

    WGPUStatus NativeResourceTableUpdate(WGPUResourceTable cSelf, uint32_t slot, WGPUBindingResource const * resource) {
        auto self = FromAPI(cSelf);

        auto slot_ = slot;
        auto resource_ = reinterpret_cast<BindingResource const *>(resource);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIUpdate(slot_, resource_);
        return ToAPI(result);
    }

    void NativeResourceTableAddRef(WGPUResourceTable cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeResourceTableRelease(WGPUResourceTable cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeSamplerSetLabel(WGPUSampler cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeSamplerAddRef(WGPUSampler cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeSamplerRelease(WGPUSampler cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    WGPUFuture NativeShaderModuleGetCompilationInfo(WGPUShaderModule cSelf, WGPUCompilationInfoCallbackInfo callbackInfo) {
        auto self = FromAPI(cSelf);

        auto callbackInfo_ = callbackInfo;
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetCompilationInfo(callbackInfo_);
        return *ToAPI(&result);
    }

    void NativeShaderModuleSetLabel(WGPUShaderModule cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeShaderModuleAddRef(WGPUShaderModule cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeShaderModuleRelease(WGPUShaderModule cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    WGPUStatus NativeSharedBufferMemoryBeginAccess(WGPUSharedBufferMemory cSelf, WGPUBuffer buffer, WGPUSharedBufferMemoryBeginAccessDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase*>(buffer);
        auto descriptor_ = reinterpret_cast<SharedBufferMemoryBeginAccessDescriptor const *>(descriptor);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIBeginAccess(buffer_, descriptor_);
        return ToAPI(result);
    }

    WGPUBuffer NativeSharedBufferMemoryCreateBuffer(WGPUSharedBufferMemory cSelf, WGPUBufferDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<BufferDescriptor const *>(descriptor);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateBuffer(descriptor_);
        return ToAPI(result);
    }

    WGPUStatus NativeSharedBufferMemoryEndAccess(WGPUSharedBufferMemory cSelf, WGPUBuffer buffer, WGPUSharedBufferMemoryEndAccessState * descriptor) {
        auto self = FromAPI(cSelf);

        auto buffer_ = reinterpret_cast<BufferBase*>(buffer);
        auto descriptor_ = reinterpret_cast<SharedBufferMemoryEndAccessState *>(descriptor);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIEndAccess(buffer_, descriptor_);
        return ToAPI(result);
    }

    WGPUStatus NativeSharedBufferMemoryGetProperties(WGPUSharedBufferMemory cSelf, WGPUSharedBufferMemoryProperties * properties) {
        auto self = FromAPI(cSelf);

        auto properties_ = reinterpret_cast<SharedBufferMemoryProperties *>(properties);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIGetProperties(properties_);
        return ToAPI(result);
    }

    WGPUBool NativeSharedBufferMemoryIsDeviceLost(WGPUSharedBufferMemory cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIIsDeviceLost();
        return result;
    }

    void NativeSharedBufferMemorySetLabel(WGPUSharedBufferMemory cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeSharedBufferMemoryAddRef(WGPUSharedBufferMemory cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeSharedBufferMemoryRelease(WGPUSharedBufferMemory cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeSharedBufferMemoryEndAccessStateFreeMembers(WGPUSharedBufferMemoryEndAccessState cSelf) {

        // This method is specified to not use AutoLock in json script or it returns a future.

        APISharedBufferMemoryEndAccessStateFreeMembers(cSelf);
    }

    void NativeSharedFenceExportInfo(WGPUSharedFence cSelf, WGPUSharedFenceExportInfo * info) {
        auto self = FromAPI(cSelf);

        auto info_ = reinterpret_cast<SharedFenceExportInfo *>(info);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIExportInfo(info_);
    }

    void NativeSharedFenceAddRef(WGPUSharedFence cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeSharedFenceRelease(WGPUSharedFence cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    WGPUStatus NativeSharedTextureMemoryBeginAccess(WGPUSharedTextureMemory cSelf, WGPUTexture texture, WGPUSharedTextureMemoryBeginAccessDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto texture_ = reinterpret_cast<TextureBase*>(texture);
        auto descriptor_ = reinterpret_cast<SharedTextureMemoryBeginAccessDescriptor const *>(descriptor);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIBeginAccess(texture_, descriptor_);
        return ToAPI(result);
    }

    WGPUTexture NativeSharedTextureMemoryCreateTexture(WGPUSharedTextureMemory cSelf, WGPUTextureDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TextureDescriptor const *>(descriptor);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateTexture(descriptor_);
        return ToAPI(result);
    }

    WGPUStatus NativeSharedTextureMemoryEndAccess(WGPUSharedTextureMemory cSelf, WGPUTexture texture, WGPUSharedTextureMemoryEndAccessState * descriptor) {
        auto self = FromAPI(cSelf);

        auto texture_ = reinterpret_cast<TextureBase*>(texture);
        auto descriptor_ = reinterpret_cast<SharedTextureMemoryEndAccessState *>(descriptor);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIEndAccess(texture_, descriptor_);
        return ToAPI(result);
    }

    WGPUStatus NativeSharedTextureMemoryGetProperties(WGPUSharedTextureMemory cSelf, WGPUSharedTextureMemoryProperties * properties) {
        auto self = FromAPI(cSelf);

        auto properties_ = reinterpret_cast<SharedTextureMemoryProperties *>(properties);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIGetProperties(properties_);
        return ToAPI(result);
    }

    WGPUBool NativeSharedTextureMemoryIsDeviceLost(WGPUSharedTextureMemory cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APIIsDeviceLost();
        return result;
    }

    void NativeSharedTextureMemorySetLabel(WGPUSharedTextureMemory cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeSharedTextureMemoryAddRef(WGPUSharedTextureMemory cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeSharedTextureMemoryRelease(WGPUSharedTextureMemory cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeSharedTextureMemoryEndAccessStateFreeMembers(WGPUSharedTextureMemoryEndAccessState cSelf) {

        // This method is specified to not use AutoLock in json script or it returns a future.

        APISharedTextureMemoryEndAccessStateFreeMembers(cSelf);
    }

    void NativeSupportedFeaturesFreeMembers(WGPUSupportedFeatures cSelf) {

        // This method is specified to not use AutoLock in json script or it returns a future.

        APISupportedFeaturesFreeMembers(cSelf);
    }

    void NativeSupportedInstanceFeaturesFreeMembers(WGPUSupportedInstanceFeatures cSelf) {

        // This method is specified to not use AutoLock in json script or it returns a future.

        APISupportedInstanceFeaturesFreeMembers(cSelf);
    }

    void NativeSupportedWGSLLanguageFeaturesFreeMembers(WGPUSupportedWGSLLanguageFeatures cSelf) {

        // This method is specified to not use AutoLock in json script or it returns a future.

        APISupportedWGSLLanguageFeaturesFreeMembers(cSelf);
    }

    void NativeSurfaceConfigure(WGPUSurface cSelf, WGPUSurfaceConfiguration const * config) {
        auto self = FromAPI(cSelf);

        auto config_ = reinterpret_cast<SurfaceConfiguration const *>(config);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIConfigure(config_);
    }

    WGPUStatus NativeSurfaceGetCapabilities(WGPUSurface cSelf, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities) {
        auto self = FromAPI(cSelf);

        auto adapter_ = reinterpret_cast<AdapterBase*>(adapter);
        auto capabilities_ = reinterpret_cast<SurfaceCapabilities *>(capabilities);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetCapabilities(adapter_, capabilities_);
        return ToAPI(result);
    }

    void NativeSurfaceGetCurrentTexture(WGPUSurface cSelf, WGPUSurfaceTexture * surfaceTexture) {
        auto self = FromAPI(cSelf);

        auto surfaceTexture_ = reinterpret_cast<SurfaceTexture *>(surfaceTexture);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIGetCurrentTexture(surfaceTexture_);
    }

    WGPUStatus NativeSurfacePresent(WGPUSurface cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIPresent();
        return ToAPI(result);
    }

    void NativeSurfaceSetLabel(WGPUSurface cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APISetLabel(label_);
    }

    void NativeSurfaceUnconfigure(WGPUSurface cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIUnconfigure();
    }

    void NativeSurfaceAddRef(WGPUSurface cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeSurfaceRelease(WGPUSurface cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeSurfaceCapabilitiesFreeMembers(WGPUSurfaceCapabilities cSelf) {

        // This method is specified to not use AutoLock in json script or it returns a future.

        APISurfaceCapabilitiesFreeMembers(cSelf);
    }

    void NativeTexelBufferViewSetLabel(WGPUTexelBufferView cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeTexelBufferViewAddRef(WGPUTexelBufferView cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeTexelBufferViewRelease(WGPUTexelBufferView cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    WGPUTextureView NativeTextureCreateErrorView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TextureViewDescriptor const *>(descriptor);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        auto result =        self->APICreateErrorView(descriptor_);
        return ToAPI(result);
    }

    WGPUTextureView NativeTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
        auto self = FromAPI(cSelf);

        auto descriptor_ = reinterpret_cast<TextureViewDescriptor const *>(descriptor);
        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APICreateView(descriptor_);
        return ToAPI(result);
    }

    void NativeTextureDestroy(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIDestroy();
    }

    uint32_t NativeTextureGetDepthOrArrayLayers(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetDepthOrArrayLayers();
        return result;
    }

    WGPUTextureDimension NativeTextureGetDimension(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetDimension();
        return ToAPI(result);
    }

    WGPUTextureFormat NativeTextureGetFormat(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetFormat();
        return ToAPI(result);
    }

    uint32_t NativeTextureGetHeight(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetHeight();
        return result;
    }

    uint32_t NativeTextureGetMipLevelCount(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetMipLevelCount();
        return result;
    }

    uint32_t NativeTextureGetSampleCount(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetSampleCount();
        return result;
    }

    WGPUTextureViewDimension NativeTextureGetTextureBindingViewDimension(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetTextureBindingViewDimension();
        return ToAPI(result);
    }

    WGPUTextureUsage NativeTextureGetUsage(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetUsage();
        return ToAPI(result);
    }

    uint32_t NativeTextureGetWidth(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        auto result =        self->APIGetWidth();
        return result;
    }

    void NativeTexturePin(WGPUTexture cSelf, WGPUTextureUsage usage) {
        auto self = FromAPI(cSelf);

        auto usage_ = static_cast<wgpu::TextureUsage>(usage);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIPin(usage_);
    }

    void NativeTextureSetLabel(WGPUTexture cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeTextureSetOwnershipForMemoryDump(WGPUTexture cSelf, uint64_t ownerGuid) {
        auto self = FromAPI(cSelf);

        auto ownerGuid_ = ownerGuid;
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetOwnershipForMemoryDump(ownerGuid_);
    }

    void NativeTextureUnpin(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APIUnpin();
    }

    void NativeTextureAddRef(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeTextureRelease(WGPUTexture cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    void NativeTextureViewSetLabel(WGPUTextureView cSelf, WGPUStringView label) {
        auto self = FromAPI(cSelf);

        auto label_ = *reinterpret_cast<StringView*>(&label);
        auto device = self->GetDevice();
        auto deviceGuard = device->GetGuard();

        self->APISetLabel(label_);
    }

    void NativeTextureViewAddRef(WGPUTextureView cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIAddRef();
    }

    void NativeTextureViewRelease(WGPUTextureView cSelf) {
        auto self = FromAPI(cSelf);

        // This method is specified to not use AutoLock in json script or it returns a future.

        self->APIRelease();
    }

    WGPUInstance NativeCreateInstance(WGPUInstanceDescriptor const * descriptor) {
        auto descriptor_ = reinterpret_cast<InstanceDescriptor const *>(descriptor);
        auto result =        APICreateInstance(descriptor_);
        return ToAPI(result);
    }
    void NativeGetInstanceFeatures(WGPUSupportedInstanceFeatures * features) {
        auto features_ = reinterpret_cast<SupportedInstanceFeatures *>(features);
        APIGetInstanceFeatures(features_);
    }
    WGPUStatus NativeGetInstanceLimits(WGPUInstanceLimits * limits) {
        auto limits_ = reinterpret_cast<InstanceLimits *>(limits);
        auto result =        APIGetInstanceLimits(limits_);
        return ToAPI(result);
    }
    WGPUBool NativeHasInstanceFeature(WGPUInstanceFeatureName feature) {
        auto feature_ = static_cast<wgpu::InstanceFeatureName>(feature);
        auto result =        APIHasInstanceFeature(feature_);
        return result;
    }

    namespace {

        struct ProcEntry {
            WGPUProc proc;
            std::string_view name;
        };
        static const ProcEntry sProcMap[] = {
            { reinterpret_cast<WGPUProc>(NativeAdapterAddRef), "wgpuAdapterAddRef" },
            { reinterpret_cast<WGPUProc>(NativeAdapterCreateDevice), "wgpuAdapterCreateDevice" },
            { reinterpret_cast<WGPUProc>(NativeAdapterGetFeatures), "wgpuAdapterGetFeatures" },
            { reinterpret_cast<WGPUProc>(NativeAdapterGetFormatCapabilities), "wgpuAdapterGetFormatCapabilities" },
            { reinterpret_cast<WGPUProc>(NativeAdapterGetInfo), "wgpuAdapterGetInfo" },
            { reinterpret_cast<WGPUProc>(NativeAdapterGetInstance), "wgpuAdapterGetInstance" },
            { reinterpret_cast<WGPUProc>(NativeAdapterGetLimits), "wgpuAdapterGetLimits" },
            { reinterpret_cast<WGPUProc>(NativeAdapterHasFeature), "wgpuAdapterHasFeature" },
            { reinterpret_cast<WGPUProc>(NativeAdapterInfoFreeMembers), "wgpuAdapterInfoFreeMembers" },
            { reinterpret_cast<WGPUProc>(NativeAdapterPropertiesMemoryHeapsFreeMembers), "wgpuAdapterPropertiesMemoryHeapsFreeMembers" },
            { reinterpret_cast<WGPUProc>(NativeAdapterPropertiesSubgroupMatrixConfigsFreeMembers), "wgpuAdapterPropertiesSubgroupMatrixConfigsFreeMembers" },
            { reinterpret_cast<WGPUProc>(NativeAdapterRelease), "wgpuAdapterRelease" },
            { reinterpret_cast<WGPUProc>(NativeAdapterRequestDevice), "wgpuAdapterRequestDevice" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupAddRef), "wgpuBindGroupAddRef" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupLayoutAddRef), "wgpuBindGroupLayoutAddRef" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupLayoutRelease), "wgpuBindGroupLayoutRelease" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupLayoutSetLabel), "wgpuBindGroupLayoutSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupRelease), "wgpuBindGroupRelease" },
            { reinterpret_cast<WGPUProc>(NativeBindGroupSetLabel), "wgpuBindGroupSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeBufferAddRef), "wgpuBufferAddRef" },
            { reinterpret_cast<WGPUProc>(NativeBufferCreateTexelView), "wgpuBufferCreateTexelView" },
            { reinterpret_cast<WGPUProc>(NativeBufferDestroy), "wgpuBufferDestroy" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetConstMappedRange), "wgpuBufferGetConstMappedRange" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetMapState), "wgpuBufferGetMapState" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetMappedRange), "wgpuBufferGetMappedRange" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetSize), "wgpuBufferGetSize" },
            { reinterpret_cast<WGPUProc>(NativeBufferGetUsage), "wgpuBufferGetUsage" },
            { reinterpret_cast<WGPUProc>(NativeBufferMapAsync), "wgpuBufferMapAsync" },
            { reinterpret_cast<WGPUProc>(NativeBufferReadMappedRange), "wgpuBufferReadMappedRange" },
            { reinterpret_cast<WGPUProc>(NativeBufferRelease), "wgpuBufferRelease" },
            { reinterpret_cast<WGPUProc>(NativeBufferSetLabel), "wgpuBufferSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeBufferUnmap), "wgpuBufferUnmap" },
            { reinterpret_cast<WGPUProc>(NativeBufferWriteMappedRange), "wgpuBufferWriteMappedRange" },
            { reinterpret_cast<WGPUProc>(NativeCommandBufferAddRef), "wgpuCommandBufferAddRef" },
            { reinterpret_cast<WGPUProc>(NativeCommandBufferRelease), "wgpuCommandBufferRelease" },
            { reinterpret_cast<WGPUProc>(NativeCommandBufferSetLabel), "wgpuCommandBufferSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderAddRef), "wgpuCommandEncoderAddRef" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderBeginComputePass), "wgpuCommandEncoderBeginComputePass" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderBeginRenderPass), "wgpuCommandEncoderBeginRenderPass" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderClearBuffer), "wgpuCommandEncoderClearBuffer" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyBufferToBuffer), "wgpuCommandEncoderCopyBufferToBuffer" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyBufferToTexture), "wgpuCommandEncoderCopyBufferToTexture" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyTextureToBuffer), "wgpuCommandEncoderCopyTextureToBuffer" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderCopyTextureToTexture), "wgpuCommandEncoderCopyTextureToTexture" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderFinish), "wgpuCommandEncoderFinish" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderInjectValidationError), "wgpuCommandEncoderInjectValidationError" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderInsertDebugMarker), "wgpuCommandEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderPopDebugGroup), "wgpuCommandEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderPushDebugGroup), "wgpuCommandEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderRelease), "wgpuCommandEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderResolveQuerySet), "wgpuCommandEncoderResolveQuerySet" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderSetLabel), "wgpuCommandEncoderSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderWriteBuffer), "wgpuCommandEncoderWriteBuffer" },
            { reinterpret_cast<WGPUProc>(NativeCommandEncoderWriteTimestamp), "wgpuCommandEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderAddRef), "wgpuComputePassEncoderAddRef" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderDispatchWorkgroups), "wgpuComputePassEncoderDispatchWorkgroups" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderDispatchWorkgroupsIndirect), "wgpuComputePassEncoderDispatchWorkgroupsIndirect" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderEnd), "wgpuComputePassEncoderEnd" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderInsertDebugMarker), "wgpuComputePassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderPopDebugGroup), "wgpuComputePassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderPushDebugGroup), "wgpuComputePassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderRelease), "wgpuComputePassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetBindGroup), "wgpuComputePassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetImmediates), "wgpuComputePassEncoderSetImmediates" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetLabel), "wgpuComputePassEncoderSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetPipeline), "wgpuComputePassEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderSetResourceTable), "wgpuComputePassEncoderSetResourceTable" },
            { reinterpret_cast<WGPUProc>(NativeComputePassEncoderWriteTimestamp), "wgpuComputePassEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineAddRef), "wgpuComputePipelineAddRef" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineGetBindGroupLayout), "wgpuComputePipelineGetBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineRelease), "wgpuComputePipelineRelease" },
            { reinterpret_cast<WGPUProc>(NativeComputePipelineSetLabel), "wgpuComputePipelineSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeDawnDrmFormatCapabilitiesFreeMembers), "wgpuDawnDrmFormatCapabilitiesFreeMembers" },
            { reinterpret_cast<WGPUProc>(NativeDeviceAddRef), "wgpuDeviceAddRef" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateBindGroup), "wgpuDeviceCreateBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateBindGroupLayout), "wgpuDeviceCreateBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateBuffer), "wgpuDeviceCreateBuffer" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateCommandEncoder), "wgpuDeviceCreateCommandEncoder" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateComputePipeline), "wgpuDeviceCreateComputePipeline" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateComputePipelineAsync), "wgpuDeviceCreateComputePipelineAsync" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateErrorBuffer), "wgpuDeviceCreateErrorBuffer" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateErrorExternalTexture), "wgpuDeviceCreateErrorExternalTexture" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateErrorShaderModule), "wgpuDeviceCreateErrorShaderModule" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateErrorTexture), "wgpuDeviceCreateErrorTexture" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateExternalTexture), "wgpuDeviceCreateExternalTexture" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreatePipelineLayout), "wgpuDeviceCreatePipelineLayout" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateQuerySet), "wgpuDeviceCreateQuerySet" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateRenderBundleEncoder), "wgpuDeviceCreateRenderBundleEncoder" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateRenderPipeline), "wgpuDeviceCreateRenderPipeline" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateRenderPipelineAsync), "wgpuDeviceCreateRenderPipelineAsync" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateResourceTable), "wgpuDeviceCreateResourceTable" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateSampler), "wgpuDeviceCreateSampler" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateShaderModule), "wgpuDeviceCreateShaderModule" },
            { reinterpret_cast<WGPUProc>(NativeDeviceCreateTexture), "wgpuDeviceCreateTexture" },
            { reinterpret_cast<WGPUProc>(NativeDeviceDestroy), "wgpuDeviceDestroy" },
            { reinterpret_cast<WGPUProc>(NativeDeviceForceLoss), "wgpuDeviceForceLoss" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetAHardwareBufferProperties), "wgpuDeviceGetAHardwareBufferProperties" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetAdapter), "wgpuDeviceGetAdapter" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetAdapterInfo), "wgpuDeviceGetAdapterInfo" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetFeatures), "wgpuDeviceGetFeatures" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetLimits), "wgpuDeviceGetLimits" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetLostFuture), "wgpuDeviceGetLostFuture" },
            { reinterpret_cast<WGPUProc>(NativeDeviceGetQueue), "wgpuDeviceGetQueue" },
            { reinterpret_cast<WGPUProc>(NativeDeviceHasFeature), "wgpuDeviceHasFeature" },
            { reinterpret_cast<WGPUProc>(NativeDeviceImportSharedBufferMemory), "wgpuDeviceImportSharedBufferMemory" },
            { reinterpret_cast<WGPUProc>(NativeDeviceImportSharedFence), "wgpuDeviceImportSharedFence" },
            { reinterpret_cast<WGPUProc>(NativeDeviceImportSharedTextureMemory), "wgpuDeviceImportSharedTextureMemory" },
            { reinterpret_cast<WGPUProc>(NativeDeviceInjectError), "wgpuDeviceInjectError" },
            { reinterpret_cast<WGPUProc>(NativeDevicePopErrorScope), "wgpuDevicePopErrorScope" },
            { reinterpret_cast<WGPUProc>(NativeDevicePushErrorScope), "wgpuDevicePushErrorScope" },
            { reinterpret_cast<WGPUProc>(NativeDeviceRelease), "wgpuDeviceRelease" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetLabel), "wgpuDeviceSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeDeviceSetLoggingCallback), "wgpuDeviceSetLoggingCallback" },
            { reinterpret_cast<WGPUProc>(NativeDeviceTick), "wgpuDeviceTick" },
            { reinterpret_cast<WGPUProc>(NativeDeviceValidateTextureDescriptor), "wgpuDeviceValidateTextureDescriptor" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureAddRef), "wgpuExternalTextureAddRef" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureDestroy), "wgpuExternalTextureDestroy" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureExpire), "wgpuExternalTextureExpire" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureRefresh), "wgpuExternalTextureRefresh" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureRelease), "wgpuExternalTextureRelease" },
            { reinterpret_cast<WGPUProc>(NativeExternalTextureSetLabel), "wgpuExternalTextureSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeInstanceAddRef), "wgpuInstanceAddRef" },
            { reinterpret_cast<WGPUProc>(NativeInstanceCreateSurface), "wgpuInstanceCreateSurface" },
            { reinterpret_cast<WGPUProc>(NativeInstanceGetWGSLLanguageFeatures), "wgpuInstanceGetWGSLLanguageFeatures" },
            { reinterpret_cast<WGPUProc>(NativeInstanceHasWGSLLanguageFeature), "wgpuInstanceHasWGSLLanguageFeature" },
            { reinterpret_cast<WGPUProc>(NativeInstanceProcessEvents), "wgpuInstanceProcessEvents" },
            { reinterpret_cast<WGPUProc>(NativeInstanceRelease), "wgpuInstanceRelease" },
            { reinterpret_cast<WGPUProc>(NativeInstanceRequestAdapter), "wgpuInstanceRequestAdapter" },
            { reinterpret_cast<WGPUProc>(NativeInstanceWaitAny), "wgpuInstanceWaitAny" },
            { reinterpret_cast<WGPUProc>(NativePipelineLayoutAddRef), "wgpuPipelineLayoutAddRef" },
            { reinterpret_cast<WGPUProc>(NativePipelineLayoutRelease), "wgpuPipelineLayoutRelease" },
            { reinterpret_cast<WGPUProc>(NativePipelineLayoutSetLabel), "wgpuPipelineLayoutSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetAddRef), "wgpuQuerySetAddRef" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetDestroy), "wgpuQuerySetDestroy" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetGetCount), "wgpuQuerySetGetCount" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetGetType), "wgpuQuerySetGetType" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetRelease), "wgpuQuerySetRelease" },
            { reinterpret_cast<WGPUProc>(NativeQuerySetSetLabel), "wgpuQuerySetSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeQueueAddRef), "wgpuQueueAddRef" },
            { reinterpret_cast<WGPUProc>(NativeQueueCopyExternalTextureForBrowser), "wgpuQueueCopyExternalTextureForBrowser" },
            { reinterpret_cast<WGPUProc>(NativeQueueCopyTextureForBrowser), "wgpuQueueCopyTextureForBrowser" },
            { reinterpret_cast<WGPUProc>(NativeQueueOnSubmittedWorkDone), "wgpuQueueOnSubmittedWorkDone" },
            { reinterpret_cast<WGPUProc>(NativeQueueRelease), "wgpuQueueRelease" },
            { reinterpret_cast<WGPUProc>(NativeQueueSetLabel), "wgpuQueueSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeQueueSubmit), "wgpuQueueSubmit" },
            { reinterpret_cast<WGPUProc>(NativeQueueWriteBuffer), "wgpuQueueWriteBuffer" },
            { reinterpret_cast<WGPUProc>(NativeQueueWriteTexture), "wgpuQueueWriteTexture" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleAddRef), "wgpuRenderBundleAddRef" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderAddRef), "wgpuRenderBundleEncoderAddRef" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDraw), "wgpuRenderBundleEncoderDraw" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDrawIndexed), "wgpuRenderBundleEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDrawIndexedIndirect), "wgpuRenderBundleEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderDrawIndirect), "wgpuRenderBundleEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderFinish), "wgpuRenderBundleEncoderFinish" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderInsertDebugMarker), "wgpuRenderBundleEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderPopDebugGroup), "wgpuRenderBundleEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderPushDebugGroup), "wgpuRenderBundleEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderRelease), "wgpuRenderBundleEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetBindGroup), "wgpuRenderBundleEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetImmediates), "wgpuRenderBundleEncoderSetImmediates" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetIndexBuffer), "wgpuRenderBundleEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetLabel), "wgpuRenderBundleEncoderSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetPipeline), "wgpuRenderBundleEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetResourceTable), "wgpuRenderBundleEncoderSetResourceTable" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleEncoderSetVertexBuffer), "wgpuRenderBundleEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleRelease), "wgpuRenderBundleRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderBundleSetLabel), "wgpuRenderBundleSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderAddRef), "wgpuRenderPassEncoderAddRef" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderBeginOcclusionQuery), "wgpuRenderPassEncoderBeginOcclusionQuery" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDraw), "wgpuRenderPassEncoderDraw" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndexed), "wgpuRenderPassEncoderDrawIndexed" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndexedIndirect), "wgpuRenderPassEncoderDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderDrawIndirect), "wgpuRenderPassEncoderDrawIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderEnd), "wgpuRenderPassEncoderEnd" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderEndOcclusionQuery), "wgpuRenderPassEncoderEndOcclusionQuery" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderExecuteBundles), "wgpuRenderPassEncoderExecuteBundles" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderInsertDebugMarker), "wgpuRenderPassEncoderInsertDebugMarker" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderMultiDrawIndexedIndirect), "wgpuRenderPassEncoderMultiDrawIndexedIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderMultiDrawIndirect), "wgpuRenderPassEncoderMultiDrawIndirect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderPixelLocalStorageBarrier), "wgpuRenderPassEncoderPixelLocalStorageBarrier" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderPopDebugGroup), "wgpuRenderPassEncoderPopDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderPushDebugGroup), "wgpuRenderPassEncoderPushDebugGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderRelease), "wgpuRenderPassEncoderRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetBindGroup), "wgpuRenderPassEncoderSetBindGroup" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetBlendConstant), "wgpuRenderPassEncoderSetBlendConstant" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetImmediates), "wgpuRenderPassEncoderSetImmediates" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetIndexBuffer), "wgpuRenderPassEncoderSetIndexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetLabel), "wgpuRenderPassEncoderSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetPipeline), "wgpuRenderPassEncoderSetPipeline" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetResourceTable), "wgpuRenderPassEncoderSetResourceTable" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetScissorRect), "wgpuRenderPassEncoderSetScissorRect" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetStencilReference), "wgpuRenderPassEncoderSetStencilReference" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetVertexBuffer), "wgpuRenderPassEncoderSetVertexBuffer" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderSetViewport), "wgpuRenderPassEncoderSetViewport" },
            { reinterpret_cast<WGPUProc>(NativeRenderPassEncoderWriteTimestamp), "wgpuRenderPassEncoderWriteTimestamp" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineAddRef), "wgpuRenderPipelineAddRef" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineGetBindGroupLayout), "wgpuRenderPipelineGetBindGroupLayout" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineRelease), "wgpuRenderPipelineRelease" },
            { reinterpret_cast<WGPUProc>(NativeRenderPipelineSetLabel), "wgpuRenderPipelineSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeResourceTableAddRef), "wgpuResourceTableAddRef" },
            { reinterpret_cast<WGPUProc>(NativeResourceTableDestroy), "wgpuResourceTableDestroy" },
            { reinterpret_cast<WGPUProc>(NativeResourceTableGetSize), "wgpuResourceTableGetSize" },
            { reinterpret_cast<WGPUProc>(NativeResourceTableInsertBinding), "wgpuResourceTableInsertBinding" },
            { reinterpret_cast<WGPUProc>(NativeResourceTableRelease), "wgpuResourceTableRelease" },
            { reinterpret_cast<WGPUProc>(NativeResourceTableRemoveBinding), "wgpuResourceTableRemoveBinding" },
            { reinterpret_cast<WGPUProc>(NativeResourceTableUpdate), "wgpuResourceTableUpdate" },
            { reinterpret_cast<WGPUProc>(NativeSamplerAddRef), "wgpuSamplerAddRef" },
            { reinterpret_cast<WGPUProc>(NativeSamplerRelease), "wgpuSamplerRelease" },
            { reinterpret_cast<WGPUProc>(NativeSamplerSetLabel), "wgpuSamplerSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleAddRef), "wgpuShaderModuleAddRef" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleGetCompilationInfo), "wgpuShaderModuleGetCompilationInfo" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleRelease), "wgpuShaderModuleRelease" },
            { reinterpret_cast<WGPUProc>(NativeShaderModuleSetLabel), "wgpuShaderModuleSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeSharedBufferMemoryAddRef), "wgpuSharedBufferMemoryAddRef" },
            { reinterpret_cast<WGPUProc>(NativeSharedBufferMemoryBeginAccess), "wgpuSharedBufferMemoryBeginAccess" },
            { reinterpret_cast<WGPUProc>(NativeSharedBufferMemoryCreateBuffer), "wgpuSharedBufferMemoryCreateBuffer" },
            { reinterpret_cast<WGPUProc>(NativeSharedBufferMemoryEndAccess), "wgpuSharedBufferMemoryEndAccess" },
            { reinterpret_cast<WGPUProc>(NativeSharedBufferMemoryEndAccessStateFreeMembers), "wgpuSharedBufferMemoryEndAccessStateFreeMembers" },
            { reinterpret_cast<WGPUProc>(NativeSharedBufferMemoryGetProperties), "wgpuSharedBufferMemoryGetProperties" },
            { reinterpret_cast<WGPUProc>(NativeSharedBufferMemoryIsDeviceLost), "wgpuSharedBufferMemoryIsDeviceLost" },
            { reinterpret_cast<WGPUProc>(NativeSharedBufferMemoryRelease), "wgpuSharedBufferMemoryRelease" },
            { reinterpret_cast<WGPUProc>(NativeSharedBufferMemorySetLabel), "wgpuSharedBufferMemorySetLabel" },
            { reinterpret_cast<WGPUProc>(NativeSharedFenceAddRef), "wgpuSharedFenceAddRef" },
            { reinterpret_cast<WGPUProc>(NativeSharedFenceExportInfo), "wgpuSharedFenceExportInfo" },
            { reinterpret_cast<WGPUProc>(NativeSharedFenceRelease), "wgpuSharedFenceRelease" },
            { reinterpret_cast<WGPUProc>(NativeSharedTextureMemoryAddRef), "wgpuSharedTextureMemoryAddRef" },
            { reinterpret_cast<WGPUProc>(NativeSharedTextureMemoryBeginAccess), "wgpuSharedTextureMemoryBeginAccess" },
            { reinterpret_cast<WGPUProc>(NativeSharedTextureMemoryCreateTexture), "wgpuSharedTextureMemoryCreateTexture" },
            { reinterpret_cast<WGPUProc>(NativeSharedTextureMemoryEndAccess), "wgpuSharedTextureMemoryEndAccess" },
            { reinterpret_cast<WGPUProc>(NativeSharedTextureMemoryEndAccessStateFreeMembers), "wgpuSharedTextureMemoryEndAccessStateFreeMembers" },
            { reinterpret_cast<WGPUProc>(NativeSharedTextureMemoryGetProperties), "wgpuSharedTextureMemoryGetProperties" },
            { reinterpret_cast<WGPUProc>(NativeSharedTextureMemoryIsDeviceLost), "wgpuSharedTextureMemoryIsDeviceLost" },
            { reinterpret_cast<WGPUProc>(NativeSharedTextureMemoryRelease), "wgpuSharedTextureMemoryRelease" },
            { reinterpret_cast<WGPUProc>(NativeSharedTextureMemorySetLabel), "wgpuSharedTextureMemorySetLabel" },
            { reinterpret_cast<WGPUProc>(NativeSupportedFeaturesFreeMembers), "wgpuSupportedFeaturesFreeMembers" },
            { reinterpret_cast<WGPUProc>(NativeSupportedInstanceFeaturesFreeMembers), "wgpuSupportedInstanceFeaturesFreeMembers" },
            { reinterpret_cast<WGPUProc>(NativeSupportedWGSLLanguageFeaturesFreeMembers), "wgpuSupportedWGSLLanguageFeaturesFreeMembers" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceAddRef), "wgpuSurfaceAddRef" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceCapabilitiesFreeMembers), "wgpuSurfaceCapabilitiesFreeMembers" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceConfigure), "wgpuSurfaceConfigure" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceGetCapabilities), "wgpuSurfaceGetCapabilities" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceGetCurrentTexture), "wgpuSurfaceGetCurrentTexture" },
            { reinterpret_cast<WGPUProc>(NativeSurfacePresent), "wgpuSurfacePresent" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceRelease), "wgpuSurfaceRelease" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceSetLabel), "wgpuSurfaceSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeSurfaceUnconfigure), "wgpuSurfaceUnconfigure" },
            { reinterpret_cast<WGPUProc>(NativeTexelBufferViewAddRef), "wgpuTexelBufferViewAddRef" },
            { reinterpret_cast<WGPUProc>(NativeTexelBufferViewRelease), "wgpuTexelBufferViewRelease" },
            { reinterpret_cast<WGPUProc>(NativeTexelBufferViewSetLabel), "wgpuTexelBufferViewSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeTextureAddRef), "wgpuTextureAddRef" },
            { reinterpret_cast<WGPUProc>(NativeTextureCreateErrorView), "wgpuTextureCreateErrorView" },
            { reinterpret_cast<WGPUProc>(NativeTextureCreateView), "wgpuTextureCreateView" },
            { reinterpret_cast<WGPUProc>(NativeTextureDestroy), "wgpuTextureDestroy" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetDepthOrArrayLayers), "wgpuTextureGetDepthOrArrayLayers" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetDimension), "wgpuTextureGetDimension" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetFormat), "wgpuTextureGetFormat" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetHeight), "wgpuTextureGetHeight" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetMipLevelCount), "wgpuTextureGetMipLevelCount" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetSampleCount), "wgpuTextureGetSampleCount" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetTextureBindingViewDimension), "wgpuTextureGetTextureBindingViewDimension" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetUsage), "wgpuTextureGetUsage" },
            { reinterpret_cast<WGPUProc>(NativeTextureGetWidth), "wgpuTextureGetWidth" },
            { reinterpret_cast<WGPUProc>(NativeTexturePin), "wgpuTexturePin" },
            { reinterpret_cast<WGPUProc>(NativeTextureRelease), "wgpuTextureRelease" },
            { reinterpret_cast<WGPUProc>(NativeTextureSetLabel), "wgpuTextureSetLabel" },
            { reinterpret_cast<WGPUProc>(NativeTextureSetOwnershipForMemoryDump), "wgpuTextureSetOwnershipForMemoryDump" },
            { reinterpret_cast<WGPUProc>(NativeTextureUnpin), "wgpuTextureUnpin" },
            { reinterpret_cast<WGPUProc>(NativeTextureViewAddRef), "wgpuTextureViewAddRef" },
            { reinterpret_cast<WGPUProc>(NativeTextureViewRelease), "wgpuTextureViewRelease" },
            { reinterpret_cast<WGPUProc>(NativeTextureViewSetLabel), "wgpuTextureViewSetLabel" },
        };
        static constexpr size_t sProcMapSize = sizeof(sProcMap) / sizeof(sProcMap[0]);

    }  // anonymous namespace

    WGPUProc NativeGetProcAddress(WGPUStringView cProcName) {
        if (cProcName.data == nullptr) {
            return nullptr;
        }

        std::string_view procName(cProcName.data, cProcName.length != WGPU_STRLEN ? cProcName.length : strlen(cProcName.data));

        const ProcEntry* entry = std::lower_bound(&sProcMap[0], &sProcMap[sProcMapSize], procName,
            [](const ProcEntry &a, const std::string_view& b) -> bool {
                return a.name.compare(b) < 0;
            }
        );

        if (entry != &sProcMap[sProcMapSize] && entry->name == procName) {
            return entry->proc;
        }

        // Special case the free-standing functions of the API.
        // TODO(dawn:1238) Checking string one by one is slow, it needs to be optimized.
        if (procName == "wgpuCreateInstance") {
            return reinterpret_cast<WGPUProc>(NativeCreateInstance);
        }

        if (procName == "wgpuGetInstanceFeatures") {
            return reinterpret_cast<WGPUProc>(NativeGetInstanceFeatures);
        }

        if (procName == "wgpuGetInstanceLimits") {
            return reinterpret_cast<WGPUProc>(NativeGetInstanceLimits);
        }

        if (procName == "wgpuHasInstanceFeature") {
            return reinterpret_cast<WGPUProc>(NativeHasInstanceFeature);
        }

        if (procName == "wgpuGetProcAddress") {
            return reinterpret_cast<WGPUProc>(NativeGetProcAddress);
        }

        return nullptr;
    }

    std::vector<std::string_view> GetProcMapNamesForTestingInternal() {
        std::vector<std::string_view> result;
        result.reserve(sProcMapSize);
        for (const ProcEntry& entry : sProcMap) {
            result.push_back(entry.name);
        }
        return result;
    }

    constexpr DawnProcTable MakeProcTable() {
        DawnProcTable procs = {};
        procs.createInstance = NativeCreateInstance;
        procs.getInstanceFeatures = NativeGetInstanceFeatures;
        procs.getInstanceLimits = NativeGetInstanceLimits;
        procs.hasInstanceFeature = NativeHasInstanceFeature;
        procs.getProcAddress = NativeGetProcAddress;
        procs.adapterCreateDevice = NativeAdapterCreateDevice;
        procs.adapterGetFeatures = NativeAdapterGetFeatures;
        procs.adapterGetFormatCapabilities = NativeAdapterGetFormatCapabilities;
        procs.adapterGetInfo = NativeAdapterGetInfo;
        procs.adapterGetInstance = NativeAdapterGetInstance;
        procs.adapterGetLimits = NativeAdapterGetLimits;
        procs.adapterHasFeature = NativeAdapterHasFeature;
        procs.adapterRequestDevice = NativeAdapterRequestDevice;
        procs.adapterAddRef = NativeAdapterAddRef;
        procs.adapterRelease = NativeAdapterRelease;
        procs.adapterInfoFreeMembers = NativeAdapterInfoFreeMembers;
        procs.adapterPropertiesMemoryHeapsFreeMembers = NativeAdapterPropertiesMemoryHeapsFreeMembers;
        procs.adapterPropertiesSubgroupMatrixConfigsFreeMembers = NativeAdapterPropertiesSubgroupMatrixConfigsFreeMembers;
        procs.bindGroupSetLabel = NativeBindGroupSetLabel;
        procs.bindGroupAddRef = NativeBindGroupAddRef;
        procs.bindGroupRelease = NativeBindGroupRelease;
        procs.bindGroupLayoutSetLabel = NativeBindGroupLayoutSetLabel;
        procs.bindGroupLayoutAddRef = NativeBindGroupLayoutAddRef;
        procs.bindGroupLayoutRelease = NativeBindGroupLayoutRelease;
        procs.bufferCreateTexelView = NativeBufferCreateTexelView;
        procs.bufferDestroy = NativeBufferDestroy;
        procs.bufferGetConstMappedRange = NativeBufferGetConstMappedRange;
        procs.bufferGetMappedRange = NativeBufferGetMappedRange;
        procs.bufferGetMapState = NativeBufferGetMapState;
        procs.bufferGetSize = NativeBufferGetSize;
        procs.bufferGetUsage = NativeBufferGetUsage;
        procs.bufferMapAsync = NativeBufferMapAsync;
        procs.bufferReadMappedRange = NativeBufferReadMappedRange;
        procs.bufferSetLabel = NativeBufferSetLabel;
        procs.bufferUnmap = NativeBufferUnmap;
        procs.bufferWriteMappedRange = NativeBufferWriteMappedRange;
        procs.bufferAddRef = NativeBufferAddRef;
        procs.bufferRelease = NativeBufferRelease;
        procs.commandBufferSetLabel = NativeCommandBufferSetLabel;
        procs.commandBufferAddRef = NativeCommandBufferAddRef;
        procs.commandBufferRelease = NativeCommandBufferRelease;
        procs.commandEncoderBeginComputePass = NativeCommandEncoderBeginComputePass;
        procs.commandEncoderBeginRenderPass = NativeCommandEncoderBeginRenderPass;
        procs.commandEncoderClearBuffer = NativeCommandEncoderClearBuffer;
        procs.commandEncoderCopyBufferToBuffer = NativeCommandEncoderCopyBufferToBuffer;
        procs.commandEncoderCopyBufferToTexture = NativeCommandEncoderCopyBufferToTexture;
        procs.commandEncoderCopyTextureToBuffer = NativeCommandEncoderCopyTextureToBuffer;
        procs.commandEncoderCopyTextureToTexture = NativeCommandEncoderCopyTextureToTexture;
        procs.commandEncoderFinish = NativeCommandEncoderFinish;
        procs.commandEncoderInjectValidationError = NativeCommandEncoderInjectValidationError;
        procs.commandEncoderInsertDebugMarker = NativeCommandEncoderInsertDebugMarker;
        procs.commandEncoderPopDebugGroup = NativeCommandEncoderPopDebugGroup;
        procs.commandEncoderPushDebugGroup = NativeCommandEncoderPushDebugGroup;
        procs.commandEncoderResolveQuerySet = NativeCommandEncoderResolveQuerySet;
        procs.commandEncoderSetLabel = NativeCommandEncoderSetLabel;
        procs.commandEncoderWriteBuffer = NativeCommandEncoderWriteBuffer;
        procs.commandEncoderWriteTimestamp = NativeCommandEncoderWriteTimestamp;
        procs.commandEncoderAddRef = NativeCommandEncoderAddRef;
        procs.commandEncoderRelease = NativeCommandEncoderRelease;
        procs.computePassEncoderDispatchWorkgroups = NativeComputePassEncoderDispatchWorkgroups;
        procs.computePassEncoderDispatchWorkgroupsIndirect = NativeComputePassEncoderDispatchWorkgroupsIndirect;
        procs.computePassEncoderEnd = NativeComputePassEncoderEnd;
        procs.computePassEncoderInsertDebugMarker = NativeComputePassEncoderInsertDebugMarker;
        procs.computePassEncoderPopDebugGroup = NativeComputePassEncoderPopDebugGroup;
        procs.computePassEncoderPushDebugGroup = NativeComputePassEncoderPushDebugGroup;
        procs.computePassEncoderSetBindGroup = NativeComputePassEncoderSetBindGroup;
        procs.computePassEncoderSetImmediates = NativeComputePassEncoderSetImmediates;
        procs.computePassEncoderSetLabel = NativeComputePassEncoderSetLabel;
        procs.computePassEncoderSetPipeline = NativeComputePassEncoderSetPipeline;
        procs.computePassEncoderSetResourceTable = NativeComputePassEncoderSetResourceTable;
        procs.computePassEncoderWriteTimestamp = NativeComputePassEncoderWriteTimestamp;
        procs.computePassEncoderAddRef = NativeComputePassEncoderAddRef;
        procs.computePassEncoderRelease = NativeComputePassEncoderRelease;
        procs.computePipelineGetBindGroupLayout = NativeComputePipelineGetBindGroupLayout;
        procs.computePipelineSetLabel = NativeComputePipelineSetLabel;
        procs.computePipelineAddRef = NativeComputePipelineAddRef;
        procs.computePipelineRelease = NativeComputePipelineRelease;
        procs.dawnDrmFormatCapabilitiesFreeMembers = NativeDawnDrmFormatCapabilitiesFreeMembers;
        procs.deviceCreateBindGroup = NativeDeviceCreateBindGroup;
        procs.deviceCreateBindGroupLayout = NativeDeviceCreateBindGroupLayout;
        procs.deviceCreateBuffer = NativeDeviceCreateBuffer;
        procs.deviceCreateCommandEncoder = NativeDeviceCreateCommandEncoder;
        procs.deviceCreateComputePipeline = NativeDeviceCreateComputePipeline;
        procs.deviceCreateComputePipelineAsync = NativeDeviceCreateComputePipelineAsync;
        procs.deviceCreateErrorBuffer = NativeDeviceCreateErrorBuffer;
        procs.deviceCreateErrorExternalTexture = NativeDeviceCreateErrorExternalTexture;
        procs.deviceCreateErrorShaderModule = NativeDeviceCreateErrorShaderModule;
        procs.deviceCreateErrorTexture = NativeDeviceCreateErrorTexture;
        procs.deviceCreateExternalTexture = NativeDeviceCreateExternalTexture;
        procs.deviceCreatePipelineLayout = NativeDeviceCreatePipelineLayout;
        procs.deviceCreateQuerySet = NativeDeviceCreateQuerySet;
        procs.deviceCreateRenderBundleEncoder = NativeDeviceCreateRenderBundleEncoder;
        procs.deviceCreateRenderPipeline = NativeDeviceCreateRenderPipeline;
        procs.deviceCreateRenderPipelineAsync = NativeDeviceCreateRenderPipelineAsync;
        procs.deviceCreateResourceTable = NativeDeviceCreateResourceTable;
        procs.deviceCreateSampler = NativeDeviceCreateSampler;
        procs.deviceCreateShaderModule = NativeDeviceCreateShaderModule;
        procs.deviceCreateTexture = NativeDeviceCreateTexture;
        procs.deviceDestroy = NativeDeviceDestroy;
        procs.deviceForceLoss = NativeDeviceForceLoss;
        procs.deviceGetAdapter = NativeDeviceGetAdapter;
        procs.deviceGetAdapterInfo = NativeDeviceGetAdapterInfo;
        procs.deviceGetAHardwareBufferProperties = NativeDeviceGetAHardwareBufferProperties;
        procs.deviceGetFeatures = NativeDeviceGetFeatures;
        procs.deviceGetLimits = NativeDeviceGetLimits;
        procs.deviceGetLostFuture = NativeDeviceGetLostFuture;
        procs.deviceGetQueue = NativeDeviceGetQueue;
        procs.deviceHasFeature = NativeDeviceHasFeature;
        procs.deviceImportSharedBufferMemory = NativeDeviceImportSharedBufferMemory;
        procs.deviceImportSharedFence = NativeDeviceImportSharedFence;
        procs.deviceImportSharedTextureMemory = NativeDeviceImportSharedTextureMemory;
        procs.deviceInjectError = NativeDeviceInjectError;
        procs.devicePopErrorScope = NativeDevicePopErrorScope;
        procs.devicePushErrorScope = NativeDevicePushErrorScope;
        procs.deviceSetLabel = NativeDeviceSetLabel;
        procs.deviceSetLoggingCallback = NativeDeviceSetLoggingCallback;
        procs.deviceTick = NativeDeviceTick;
        procs.deviceValidateTextureDescriptor = NativeDeviceValidateTextureDescriptor;
        procs.deviceAddRef = NativeDeviceAddRef;
        procs.deviceRelease = NativeDeviceRelease;
        procs.externalTextureDestroy = NativeExternalTextureDestroy;
        procs.externalTextureExpire = NativeExternalTextureExpire;
        procs.externalTextureRefresh = NativeExternalTextureRefresh;
        procs.externalTextureSetLabel = NativeExternalTextureSetLabel;
        procs.externalTextureAddRef = NativeExternalTextureAddRef;
        procs.externalTextureRelease = NativeExternalTextureRelease;
        procs.instanceCreateSurface = NativeInstanceCreateSurface;
        procs.instanceGetWGSLLanguageFeatures = NativeInstanceGetWGSLLanguageFeatures;
        procs.instanceHasWGSLLanguageFeature = NativeInstanceHasWGSLLanguageFeature;
        procs.instanceProcessEvents = NativeInstanceProcessEvents;
        procs.instanceRequestAdapter = NativeInstanceRequestAdapter;
        procs.instanceWaitAny = NativeInstanceWaitAny;
        procs.instanceAddRef = NativeInstanceAddRef;
        procs.instanceRelease = NativeInstanceRelease;
        procs.pipelineLayoutSetLabel = NativePipelineLayoutSetLabel;
        procs.pipelineLayoutAddRef = NativePipelineLayoutAddRef;
        procs.pipelineLayoutRelease = NativePipelineLayoutRelease;
        procs.querySetDestroy = NativeQuerySetDestroy;
        procs.querySetGetCount = NativeQuerySetGetCount;
        procs.querySetGetType = NativeQuerySetGetType;
        procs.querySetSetLabel = NativeQuerySetSetLabel;
        procs.querySetAddRef = NativeQuerySetAddRef;
        procs.querySetRelease = NativeQuerySetRelease;
        procs.queueCopyExternalTextureForBrowser = NativeQueueCopyExternalTextureForBrowser;
        procs.queueCopyTextureForBrowser = NativeQueueCopyTextureForBrowser;
        procs.queueOnSubmittedWorkDone = NativeQueueOnSubmittedWorkDone;
        procs.queueSetLabel = NativeQueueSetLabel;
        procs.queueSubmit = NativeQueueSubmit;
        procs.queueWriteBuffer = NativeQueueWriteBuffer;
        procs.queueWriteTexture = NativeQueueWriteTexture;
        procs.queueAddRef = NativeQueueAddRef;
        procs.queueRelease = NativeQueueRelease;
        procs.renderBundleSetLabel = NativeRenderBundleSetLabel;
        procs.renderBundleAddRef = NativeRenderBundleAddRef;
        procs.renderBundleRelease = NativeRenderBundleRelease;
        procs.renderBundleEncoderDraw = NativeRenderBundleEncoderDraw;
        procs.renderBundleEncoderDrawIndexed = NativeRenderBundleEncoderDrawIndexed;
        procs.renderBundleEncoderDrawIndexedIndirect = NativeRenderBundleEncoderDrawIndexedIndirect;
        procs.renderBundleEncoderDrawIndirect = NativeRenderBundleEncoderDrawIndirect;
        procs.renderBundleEncoderFinish = NativeRenderBundleEncoderFinish;
        procs.renderBundleEncoderInsertDebugMarker = NativeRenderBundleEncoderInsertDebugMarker;
        procs.renderBundleEncoderPopDebugGroup = NativeRenderBundleEncoderPopDebugGroup;
        procs.renderBundleEncoderPushDebugGroup = NativeRenderBundleEncoderPushDebugGroup;
        procs.renderBundleEncoderSetBindGroup = NativeRenderBundleEncoderSetBindGroup;
        procs.renderBundleEncoderSetImmediates = NativeRenderBundleEncoderSetImmediates;
        procs.renderBundleEncoderSetIndexBuffer = NativeRenderBundleEncoderSetIndexBuffer;
        procs.renderBundleEncoderSetLabel = NativeRenderBundleEncoderSetLabel;
        procs.renderBundleEncoderSetPipeline = NativeRenderBundleEncoderSetPipeline;
        procs.renderBundleEncoderSetResourceTable = NativeRenderBundleEncoderSetResourceTable;
        procs.renderBundleEncoderSetVertexBuffer = NativeRenderBundleEncoderSetVertexBuffer;
        procs.renderBundleEncoderAddRef = NativeRenderBundleEncoderAddRef;
        procs.renderBundleEncoderRelease = NativeRenderBundleEncoderRelease;
        procs.renderPassEncoderBeginOcclusionQuery = NativeRenderPassEncoderBeginOcclusionQuery;
        procs.renderPassEncoderDraw = NativeRenderPassEncoderDraw;
        procs.renderPassEncoderDrawIndexed = NativeRenderPassEncoderDrawIndexed;
        procs.renderPassEncoderDrawIndexedIndirect = NativeRenderPassEncoderDrawIndexedIndirect;
        procs.renderPassEncoderDrawIndirect = NativeRenderPassEncoderDrawIndirect;
        procs.renderPassEncoderEnd = NativeRenderPassEncoderEnd;
        procs.renderPassEncoderEndOcclusionQuery = NativeRenderPassEncoderEndOcclusionQuery;
        procs.renderPassEncoderExecuteBundles = NativeRenderPassEncoderExecuteBundles;
        procs.renderPassEncoderInsertDebugMarker = NativeRenderPassEncoderInsertDebugMarker;
        procs.renderPassEncoderMultiDrawIndexedIndirect = NativeRenderPassEncoderMultiDrawIndexedIndirect;
        procs.renderPassEncoderMultiDrawIndirect = NativeRenderPassEncoderMultiDrawIndirect;
        procs.renderPassEncoderPixelLocalStorageBarrier = NativeRenderPassEncoderPixelLocalStorageBarrier;
        procs.renderPassEncoderPopDebugGroup = NativeRenderPassEncoderPopDebugGroup;
        procs.renderPassEncoderPushDebugGroup = NativeRenderPassEncoderPushDebugGroup;
        procs.renderPassEncoderSetBindGroup = NativeRenderPassEncoderSetBindGroup;
        procs.renderPassEncoderSetBlendConstant = NativeRenderPassEncoderSetBlendConstant;
        procs.renderPassEncoderSetImmediates = NativeRenderPassEncoderSetImmediates;
        procs.renderPassEncoderSetIndexBuffer = NativeRenderPassEncoderSetIndexBuffer;
        procs.renderPassEncoderSetLabel = NativeRenderPassEncoderSetLabel;
        procs.renderPassEncoderSetPipeline = NativeRenderPassEncoderSetPipeline;
        procs.renderPassEncoderSetResourceTable = NativeRenderPassEncoderSetResourceTable;
        procs.renderPassEncoderSetScissorRect = NativeRenderPassEncoderSetScissorRect;
        procs.renderPassEncoderSetStencilReference = NativeRenderPassEncoderSetStencilReference;
        procs.renderPassEncoderSetVertexBuffer = NativeRenderPassEncoderSetVertexBuffer;
        procs.renderPassEncoderSetViewport = NativeRenderPassEncoderSetViewport;
        procs.renderPassEncoderWriteTimestamp = NativeRenderPassEncoderWriteTimestamp;
        procs.renderPassEncoderAddRef = NativeRenderPassEncoderAddRef;
        procs.renderPassEncoderRelease = NativeRenderPassEncoderRelease;
        procs.renderPipelineGetBindGroupLayout = NativeRenderPipelineGetBindGroupLayout;
        procs.renderPipelineSetLabel = NativeRenderPipelineSetLabel;
        procs.renderPipelineAddRef = NativeRenderPipelineAddRef;
        procs.renderPipelineRelease = NativeRenderPipelineRelease;
        procs.resourceTableDestroy = NativeResourceTableDestroy;
        procs.resourceTableGetSize = NativeResourceTableGetSize;
        procs.resourceTableInsertBinding = NativeResourceTableInsertBinding;
        procs.resourceTableRemoveBinding = NativeResourceTableRemoveBinding;
        procs.resourceTableUpdate = NativeResourceTableUpdate;
        procs.resourceTableAddRef = NativeResourceTableAddRef;
        procs.resourceTableRelease = NativeResourceTableRelease;
        procs.samplerSetLabel = NativeSamplerSetLabel;
        procs.samplerAddRef = NativeSamplerAddRef;
        procs.samplerRelease = NativeSamplerRelease;
        procs.shaderModuleGetCompilationInfo = NativeShaderModuleGetCompilationInfo;
        procs.shaderModuleSetLabel = NativeShaderModuleSetLabel;
        procs.shaderModuleAddRef = NativeShaderModuleAddRef;
        procs.shaderModuleRelease = NativeShaderModuleRelease;
        procs.sharedBufferMemoryBeginAccess = NativeSharedBufferMemoryBeginAccess;
        procs.sharedBufferMemoryCreateBuffer = NativeSharedBufferMemoryCreateBuffer;
        procs.sharedBufferMemoryEndAccess = NativeSharedBufferMemoryEndAccess;
        procs.sharedBufferMemoryGetProperties = NativeSharedBufferMemoryGetProperties;
        procs.sharedBufferMemoryIsDeviceLost = NativeSharedBufferMemoryIsDeviceLost;
        procs.sharedBufferMemorySetLabel = NativeSharedBufferMemorySetLabel;
        procs.sharedBufferMemoryAddRef = NativeSharedBufferMemoryAddRef;
        procs.sharedBufferMemoryRelease = NativeSharedBufferMemoryRelease;
        procs.sharedBufferMemoryEndAccessStateFreeMembers = NativeSharedBufferMemoryEndAccessStateFreeMembers;
        procs.sharedFenceExportInfo = NativeSharedFenceExportInfo;
        procs.sharedFenceAddRef = NativeSharedFenceAddRef;
        procs.sharedFenceRelease = NativeSharedFenceRelease;
        procs.sharedTextureMemoryBeginAccess = NativeSharedTextureMemoryBeginAccess;
        procs.sharedTextureMemoryCreateTexture = NativeSharedTextureMemoryCreateTexture;
        procs.sharedTextureMemoryEndAccess = NativeSharedTextureMemoryEndAccess;
        procs.sharedTextureMemoryGetProperties = NativeSharedTextureMemoryGetProperties;
        procs.sharedTextureMemoryIsDeviceLost = NativeSharedTextureMemoryIsDeviceLost;
        procs.sharedTextureMemorySetLabel = NativeSharedTextureMemorySetLabel;
        procs.sharedTextureMemoryAddRef = NativeSharedTextureMemoryAddRef;
        procs.sharedTextureMemoryRelease = NativeSharedTextureMemoryRelease;
        procs.sharedTextureMemoryEndAccessStateFreeMembers = NativeSharedTextureMemoryEndAccessStateFreeMembers;
        procs.supportedFeaturesFreeMembers = NativeSupportedFeaturesFreeMembers;
        procs.supportedInstanceFeaturesFreeMembers = NativeSupportedInstanceFeaturesFreeMembers;
        procs.supportedWGSLLanguageFeaturesFreeMembers = NativeSupportedWGSLLanguageFeaturesFreeMembers;
        procs.surfaceConfigure = NativeSurfaceConfigure;
        procs.surfaceGetCapabilities = NativeSurfaceGetCapabilities;
        procs.surfaceGetCurrentTexture = NativeSurfaceGetCurrentTexture;
        procs.surfacePresent = NativeSurfacePresent;
        procs.surfaceSetLabel = NativeSurfaceSetLabel;
        procs.surfaceUnconfigure = NativeSurfaceUnconfigure;
        procs.surfaceAddRef = NativeSurfaceAddRef;
        procs.surfaceRelease = NativeSurfaceRelease;
        procs.surfaceCapabilitiesFreeMembers = NativeSurfaceCapabilitiesFreeMembers;
        procs.texelBufferViewSetLabel = NativeTexelBufferViewSetLabel;
        procs.texelBufferViewAddRef = NativeTexelBufferViewAddRef;
        procs.texelBufferViewRelease = NativeTexelBufferViewRelease;
        procs.textureCreateErrorView = NativeTextureCreateErrorView;
        procs.textureCreateView = NativeTextureCreateView;
        procs.textureDestroy = NativeTextureDestroy;
        procs.textureGetDepthOrArrayLayers = NativeTextureGetDepthOrArrayLayers;
        procs.textureGetDimension = NativeTextureGetDimension;
        procs.textureGetFormat = NativeTextureGetFormat;
        procs.textureGetHeight = NativeTextureGetHeight;
        procs.textureGetMipLevelCount = NativeTextureGetMipLevelCount;
        procs.textureGetSampleCount = NativeTextureGetSampleCount;
        procs.textureGetTextureBindingViewDimension = NativeTextureGetTextureBindingViewDimension;
        procs.textureGetUsage = NativeTextureGetUsage;
        procs.textureGetWidth = NativeTextureGetWidth;
        procs.texturePin = NativeTexturePin;
        procs.textureSetLabel = NativeTextureSetLabel;
        procs.textureSetOwnershipForMemoryDump = NativeTextureSetOwnershipForMemoryDump;
        procs.textureUnpin = NativeTextureUnpin;
        procs.textureAddRef = NativeTextureAddRef;
        procs.textureRelease = NativeTextureRelease;
        procs.textureViewSetLabel = NativeTextureViewSetLabel;
        procs.textureViewAddRef = NativeTextureViewAddRef;
        procs.textureViewRelease = NativeTextureViewRelease;
        return procs;
    }

    static DawnProcTable gProcTable = MakeProcTable();

    const DawnProcTable& GetProcsAutogen() {
        return gProcTable;
    }
}
