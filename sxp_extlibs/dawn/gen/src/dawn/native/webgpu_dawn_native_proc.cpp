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

#include "dawn/webgpu.h"

namespace dawn::native {

// This file should be kept in sync with generator/templates/dawn/native/ProcTable.cpp

extern WGPUInstance NativeCreateInstance(WGPUInstanceDescriptor const * descriptor);
extern void NativeGetInstanceFeatures(WGPUSupportedInstanceFeatures * features);
extern WGPUStatus NativeGetInstanceLimits(WGPUInstanceLimits * limits);
extern WGPUBool NativeHasInstanceFeature(WGPUInstanceFeatureName feature);
extern WGPUProc NativeGetProcAddress(WGPUStringView procName);
extern WGPUDevice NativeAdapterCreateDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor);
extern void NativeAdapterGetFeatures(WGPUAdapter cSelf, WGPUSupportedFeatures * features);
extern WGPUStatus NativeAdapterGetFormatCapabilities(WGPUAdapter cSelf, WGPUTextureFormat format, WGPUDawnFormatCapabilities * capabilities);
extern WGPUStatus NativeAdapterGetInfo(WGPUAdapter cSelf, WGPUAdapterInfo * info);
extern WGPUInstance NativeAdapterGetInstance(WGPUAdapter cSelf);
extern WGPUStatus NativeAdapterGetLimits(WGPUAdapter cSelf, WGPULimits * limits);
extern WGPUBool NativeAdapterHasFeature(WGPUAdapter cSelf, WGPUFeatureName feature);
extern WGPUFuture NativeAdapterRequestDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallbackInfo callbackInfo);
extern void NativeAdapterAddRef(WGPUAdapter cSelf);
extern void NativeAdapterRelease(WGPUAdapter cSelf);
extern void NativeAdapterInfoFreeMembers(WGPUAdapterInfo cSelf);
extern void NativeAdapterPropertiesMemoryHeapsFreeMembers(WGPUAdapterPropertiesMemoryHeaps cSelf);
extern void NativeAdapterPropertiesSubgroupMatrixConfigsFreeMembers(WGPUAdapterPropertiesSubgroupMatrixConfigs cSelf);
extern void NativeBindGroupSetLabel(WGPUBindGroup cSelf, WGPUStringView label);
extern void NativeBindGroupAddRef(WGPUBindGroup cSelf);
extern void NativeBindGroupRelease(WGPUBindGroup cSelf);
extern void NativeBindGroupLayoutSetLabel(WGPUBindGroupLayout cSelf, WGPUStringView label);
extern void NativeBindGroupLayoutAddRef(WGPUBindGroupLayout cSelf);
extern void NativeBindGroupLayoutRelease(WGPUBindGroupLayout cSelf);
extern WGPUTexelBufferView NativeBufferCreateTexelView(WGPUBuffer cSelf, WGPUTexelBufferViewDescriptor const * descriptor);
extern void NativeBufferDestroy(WGPUBuffer cSelf);
extern void const * NativeBufferGetConstMappedRange(WGPUBuffer cSelf, size_t offset, size_t size);
extern void * NativeBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size);
extern WGPUBufferMapState NativeBufferGetMapState(WGPUBuffer cSelf);
extern uint64_t NativeBufferGetSize(WGPUBuffer cSelf);
extern WGPUBufferUsage NativeBufferGetUsage(WGPUBuffer cSelf);
extern WGPUFuture NativeBufferMapAsync(WGPUBuffer cSelf, WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo);
extern WGPUStatus NativeBufferReadMappedRange(WGPUBuffer cSelf, size_t offset, void * data, size_t size);
extern void NativeBufferSetLabel(WGPUBuffer cSelf, WGPUStringView label);
extern void NativeBufferUnmap(WGPUBuffer cSelf);
extern WGPUStatus NativeBufferWriteMappedRange(WGPUBuffer cSelf, size_t offset, void const * data, size_t size);
extern void NativeBufferAddRef(WGPUBuffer cSelf);
extern void NativeBufferRelease(WGPUBuffer cSelf);
extern void NativeCommandBufferSetLabel(WGPUCommandBuffer cSelf, WGPUStringView label);
extern void NativeCommandBufferAddRef(WGPUCommandBuffer cSelf);
extern void NativeCommandBufferRelease(WGPUCommandBuffer cSelf);
extern WGPUComputePassEncoder NativeCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor);
extern WGPURenderPassEncoder NativeCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor);
extern void NativeCommandEncoderClearBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size);
extern void NativeCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder cSelf, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size);
extern void NativeCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUTexelCopyBufferInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize);
extern void NativeCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyBufferInfo const * destination, WGPUExtent3D const * copySize);
extern void NativeCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize);
extern WGPUCommandBuffer NativeCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor);
extern void NativeCommandEncoderInjectValidationError(WGPUCommandEncoder cSelf, WGPUStringView message);
extern void NativeCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, WGPUStringView markerLabel);
extern void NativeCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf);
extern void NativeCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, WGPUStringView groupLabel);
extern void NativeCommandEncoderResolveQuerySet(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset);
extern void NativeCommandEncoderSetLabel(WGPUCommandEncoder cSelf, WGPUStringView label);
extern void NativeCommandEncoderWriteBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size);
extern void NativeCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex);
extern void NativeCommandEncoderAddRef(WGPUCommandEncoder cSelf);
extern void NativeCommandEncoderRelease(WGPUCommandEncoder cSelf);
extern void NativeComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder cSelf, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ);
extern void NativeComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
extern void NativeComputePassEncoderEnd(WGPUComputePassEncoder cSelf);
extern void NativeComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, WGPUStringView markerLabel);
extern void NativeComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf);
extern void NativeComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, WGPUStringView groupLabel);
extern void NativeComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
extern void NativeComputePassEncoderSetImmediates(WGPUComputePassEncoder cSelf, uint32_t offset, void const * data, size_t size);
extern void NativeComputePassEncoderSetLabel(WGPUComputePassEncoder cSelf, WGPUStringView label);
extern void NativeComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline);
extern void NativeComputePassEncoderSetResourceTable(WGPUComputePassEncoder cSelf, WGPUResourceTable table);
extern void NativeComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex);
extern void NativeComputePassEncoderAddRef(WGPUComputePassEncoder cSelf);
extern void NativeComputePassEncoderRelease(WGPUComputePassEncoder cSelf);
extern WGPUBindGroupLayout NativeComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex);
extern void NativeComputePipelineSetLabel(WGPUComputePipeline cSelf, WGPUStringView label);
extern void NativeComputePipelineAddRef(WGPUComputePipeline cSelf);
extern void NativeComputePipelineRelease(WGPUComputePipeline cSelf);
extern void NativeDawnDrmFormatCapabilitiesFreeMembers(WGPUDawnDrmFormatCapabilities cSelf);
extern WGPUBindGroup NativeDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor);
extern WGPUBindGroupLayout NativeDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor);
extern WGPUBuffer NativeDeviceCreateBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor);
extern WGPUCommandEncoder NativeDeviceCreateCommandEncoder(WGPUDevice cSelf, WGPUCommandEncoderDescriptor const * descriptor);
extern WGPUComputePipeline NativeDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor);
extern WGPUFuture NativeDeviceCreateComputePipelineAsync(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo);
extern WGPUBuffer NativeDeviceCreateErrorBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor);
extern WGPUExternalTexture NativeDeviceCreateErrorExternalTexture(WGPUDevice cSelf);
extern WGPUShaderModule NativeDeviceCreateErrorShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor, WGPUStringView errorMessage);
extern WGPUTexture NativeDeviceCreateErrorTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor);
extern WGPUExternalTexture NativeDeviceCreateExternalTexture(WGPUDevice cSelf, WGPUExternalTextureDescriptor const * externalTextureDescriptor);
extern WGPUPipelineLayout NativeDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor);
extern WGPUQuerySet NativeDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor);
extern WGPURenderBundleEncoder NativeDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor);
extern WGPURenderPipeline NativeDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor);
extern WGPUFuture NativeDeviceCreateRenderPipelineAsync(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo);
extern WGPUResourceTable NativeDeviceCreateResourceTable(WGPUDevice cSelf, WGPUResourceTableDescriptor const * descriptor);
extern WGPUSampler NativeDeviceCreateSampler(WGPUDevice cSelf, WGPUSamplerDescriptor const * descriptor);
extern WGPUShaderModule NativeDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor);
extern WGPUTexture NativeDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor);
extern void NativeDeviceDestroy(WGPUDevice cSelf);
extern void NativeDeviceForceLoss(WGPUDevice cSelf, WGPUDeviceLostReason type, WGPUStringView message);
extern WGPUAdapter NativeDeviceGetAdapter(WGPUDevice cSelf);
extern WGPUStatus NativeDeviceGetAdapterInfo(WGPUDevice cSelf, WGPUAdapterInfo * adapterInfo);
extern WGPUStatus NativeDeviceGetAHardwareBufferProperties(WGPUDevice cSelf, void * handle, WGPUAHardwareBufferProperties * properties);
extern void NativeDeviceGetFeatures(WGPUDevice cSelf, WGPUSupportedFeatures * features);
extern WGPUStatus NativeDeviceGetLimits(WGPUDevice cSelf, WGPULimits * limits);
extern WGPUFuture NativeDeviceGetLostFuture(WGPUDevice cSelf);
extern WGPUQueue NativeDeviceGetQueue(WGPUDevice cSelf);
extern WGPUBool NativeDeviceHasFeature(WGPUDevice cSelf, WGPUFeatureName feature);
extern WGPUSharedBufferMemory NativeDeviceImportSharedBufferMemory(WGPUDevice cSelf, WGPUSharedBufferMemoryDescriptor const * descriptor);
extern WGPUSharedFence NativeDeviceImportSharedFence(WGPUDevice cSelf, WGPUSharedFenceDescriptor const * descriptor);
extern WGPUSharedTextureMemory NativeDeviceImportSharedTextureMemory(WGPUDevice cSelf, WGPUSharedTextureMemoryDescriptor const * descriptor);
extern void NativeDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, WGPUStringView message);
extern WGPUFuture NativeDevicePopErrorScope(WGPUDevice cSelf, WGPUPopErrorScopeCallbackInfo callbackInfo);
extern void NativeDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter);
extern void NativeDeviceSetLabel(WGPUDevice cSelf, WGPUStringView label);
extern void NativeDeviceSetLoggingCallback(WGPUDevice cSelf, WGPULoggingCallbackInfo callbackInfo);
extern void NativeDeviceTick(WGPUDevice cSelf);
extern void NativeDeviceValidateTextureDescriptor(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor);
extern void NativeDeviceAddRef(WGPUDevice cSelf);
extern void NativeDeviceRelease(WGPUDevice cSelf);
extern void NativeExternalTextureDestroy(WGPUExternalTexture cSelf);
extern void NativeExternalTextureExpire(WGPUExternalTexture cSelf);
extern void NativeExternalTextureRefresh(WGPUExternalTexture cSelf);
extern void NativeExternalTextureSetLabel(WGPUExternalTexture cSelf, WGPUStringView label);
extern void NativeExternalTextureAddRef(WGPUExternalTexture cSelf);
extern void NativeExternalTextureRelease(WGPUExternalTexture cSelf);
extern WGPUSurface NativeInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor);
extern void NativeInstanceGetWGSLLanguageFeatures(WGPUInstance cSelf, WGPUSupportedWGSLLanguageFeatures * features);
extern WGPUBool NativeInstanceHasWGSLLanguageFeature(WGPUInstance cSelf, WGPUWGSLLanguageFeatureName feature);
extern void NativeInstanceProcessEvents(WGPUInstance cSelf);
extern WGPUFuture NativeInstanceRequestAdapter(WGPUInstance cSelf, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallbackInfo callbackInfo);
extern WGPUWaitStatus NativeInstanceWaitAny(WGPUInstance cSelf, size_t futureCount, WGPUFutureWaitInfo * futures, uint64_t timeoutNS);
extern void NativeInstanceAddRef(WGPUInstance cSelf);
extern void NativeInstanceRelease(WGPUInstance cSelf);
extern void NativePipelineLayoutSetLabel(WGPUPipelineLayout cSelf, WGPUStringView label);
extern void NativePipelineLayoutAddRef(WGPUPipelineLayout cSelf);
extern void NativePipelineLayoutRelease(WGPUPipelineLayout cSelf);
extern void NativeQuerySetDestroy(WGPUQuerySet cSelf);
extern uint32_t NativeQuerySetGetCount(WGPUQuerySet cSelf);
extern WGPUQueryType NativeQuerySetGetType(WGPUQuerySet cSelf);
extern void NativeQuerySetSetLabel(WGPUQuerySet cSelf, WGPUStringView label);
extern void NativeQuerySetAddRef(WGPUQuerySet cSelf);
extern void NativeQuerySetRelease(WGPUQuerySet cSelf);
extern void NativeQueueCopyExternalTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyExternalTexture const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options);
extern void NativeQueueCopyTextureForBrowser(WGPUQueue cSelf, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options);
extern WGPUFuture NativeQueueOnSubmittedWorkDone(WGPUQueue cSelf, WGPUQueueWorkDoneCallbackInfo callbackInfo);
extern void NativeQueueSetLabel(WGPUQueue cSelf, WGPUStringView label);
extern void NativeQueueSubmit(WGPUQueue cSelf, size_t commandCount, WGPUCommandBuffer const * commands);
extern void NativeQueueWriteBuffer(WGPUQueue cSelf, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size);
extern void NativeQueueWriteTexture(WGPUQueue cSelf, WGPUTexelCopyTextureInfo const * destination, void const * data, size_t dataSize, WGPUTexelCopyBufferLayout const * dataLayout, WGPUExtent3D const * writeSize);
extern void NativeQueueAddRef(WGPUQueue cSelf);
extern void NativeQueueRelease(WGPUQueue cSelf);
extern void NativeRenderBundleSetLabel(WGPURenderBundle cSelf, WGPUStringView label);
extern void NativeRenderBundleAddRef(WGPURenderBundle cSelf);
extern void NativeRenderBundleRelease(WGPURenderBundle cSelf);
extern void NativeRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
extern void NativeRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
extern void NativeRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
extern void NativeRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
extern WGPURenderBundle NativeRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor);
extern void NativeRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, WGPUStringView markerLabel);
extern void NativeRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf);
extern void NativeRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, WGPUStringView groupLabel);
extern void NativeRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
extern void NativeRenderBundleEncoderSetImmediates(WGPURenderBundleEncoder cSelf, uint32_t offset, void const * data, size_t size);
extern void NativeRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
extern void NativeRenderBundleEncoderSetLabel(WGPURenderBundleEncoder cSelf, WGPUStringView label);
extern void NativeRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline);
extern void NativeRenderBundleEncoderSetResourceTable(WGPURenderBundleEncoder cSelf, WGPUResourceTable table);
extern void NativeRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size);
extern void NativeRenderBundleEncoderAddRef(WGPURenderBundleEncoder cSelf);
extern void NativeRenderBundleEncoderRelease(WGPURenderBundleEncoder cSelf);
extern void NativeRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder cSelf, uint32_t queryIndex);
extern void NativeRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
extern void NativeRenderPassEncoderDrawIndexed(WGPURenderPassEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
extern void NativeRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
extern void NativeRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
extern void NativeRenderPassEncoderEnd(WGPURenderPassEncoder cSelf);
extern void NativeRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder cSelf);
extern void NativeRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, size_t bundleCount, WGPURenderBundle const * bundles);
extern void NativeRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, WGPUStringView markerLabel);
extern void NativeRenderPassEncoderMultiDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset);
extern void NativeRenderPassEncoderMultiDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset);
extern void NativeRenderPassEncoderPixelLocalStorageBarrier(WGPURenderPassEncoder cSelf);
extern void NativeRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf);
extern void NativeRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, WGPUStringView groupLabel);
extern void NativeRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets);
extern void NativeRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder cSelf, WGPUColor const * color);
extern void NativeRenderPassEncoderSetImmediates(WGPURenderPassEncoder cSelf, uint32_t offset, void const * data, size_t size);
extern void NativeRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
extern void NativeRenderPassEncoderSetLabel(WGPURenderPassEncoder cSelf, WGPUStringView label);
extern void NativeRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline);
extern void NativeRenderPassEncoderSetResourceTable(WGPURenderPassEncoder cSelf, WGPUResourceTable table);
extern void NativeRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
extern void NativeRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference);
extern void NativeRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size);
extern void NativeRenderPassEncoderSetViewport(WGPURenderPassEncoder cSelf, float x, float y, float width, float height, float minDepth, float maxDepth);
extern void NativeRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex);
extern void NativeRenderPassEncoderAddRef(WGPURenderPassEncoder cSelf);
extern void NativeRenderPassEncoderRelease(WGPURenderPassEncoder cSelf);
extern WGPUBindGroupLayout NativeRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex);
extern void NativeRenderPipelineSetLabel(WGPURenderPipeline cSelf, WGPUStringView label);
extern void NativeRenderPipelineAddRef(WGPURenderPipeline cSelf);
extern void NativeRenderPipelineRelease(WGPURenderPipeline cSelf);
extern void NativeResourceTableDestroy(WGPUResourceTable cSelf);
extern uint32_t NativeResourceTableGetSize(WGPUResourceTable cSelf);
extern uint32_t NativeResourceTableInsertBinding(WGPUResourceTable cSelf, WGPUBindingResource const * resource);
extern WGPUStatus NativeResourceTableRemoveBinding(WGPUResourceTable cSelf, uint32_t slot);
extern WGPUStatus NativeResourceTableUpdate(WGPUResourceTable cSelf, uint32_t slot, WGPUBindingResource const * resource);
extern void NativeResourceTableAddRef(WGPUResourceTable cSelf);
extern void NativeResourceTableRelease(WGPUResourceTable cSelf);
extern void NativeSamplerSetLabel(WGPUSampler cSelf, WGPUStringView label);
extern void NativeSamplerAddRef(WGPUSampler cSelf);
extern void NativeSamplerRelease(WGPUSampler cSelf);
extern WGPUFuture NativeShaderModuleGetCompilationInfo(WGPUShaderModule cSelf, WGPUCompilationInfoCallbackInfo callbackInfo);
extern void NativeShaderModuleSetLabel(WGPUShaderModule cSelf, WGPUStringView label);
extern void NativeShaderModuleAddRef(WGPUShaderModule cSelf);
extern void NativeShaderModuleRelease(WGPUShaderModule cSelf);
extern WGPUStatus NativeSharedBufferMemoryBeginAccess(WGPUSharedBufferMemory cSelf, WGPUBuffer buffer, WGPUSharedBufferMemoryBeginAccessDescriptor const * descriptor);
extern WGPUBuffer NativeSharedBufferMemoryCreateBuffer(WGPUSharedBufferMemory cSelf, WGPUBufferDescriptor const * descriptor);
extern WGPUStatus NativeSharedBufferMemoryEndAccess(WGPUSharedBufferMemory cSelf, WGPUBuffer buffer, WGPUSharedBufferMemoryEndAccessState * descriptor);
extern WGPUStatus NativeSharedBufferMemoryGetProperties(WGPUSharedBufferMemory cSelf, WGPUSharedBufferMemoryProperties * properties);
extern WGPUBool NativeSharedBufferMemoryIsDeviceLost(WGPUSharedBufferMemory cSelf);
extern void NativeSharedBufferMemorySetLabel(WGPUSharedBufferMemory cSelf, WGPUStringView label);
extern void NativeSharedBufferMemoryAddRef(WGPUSharedBufferMemory cSelf);
extern void NativeSharedBufferMemoryRelease(WGPUSharedBufferMemory cSelf);
extern void NativeSharedBufferMemoryEndAccessStateFreeMembers(WGPUSharedBufferMemoryEndAccessState cSelf);
extern void NativeSharedFenceExportInfo(WGPUSharedFence cSelf, WGPUSharedFenceExportInfo * info);
extern void NativeSharedFenceAddRef(WGPUSharedFence cSelf);
extern void NativeSharedFenceRelease(WGPUSharedFence cSelf);
extern WGPUStatus NativeSharedTextureMemoryBeginAccess(WGPUSharedTextureMemory cSelf, WGPUTexture texture, WGPUSharedTextureMemoryBeginAccessDescriptor const * descriptor);
extern WGPUTexture NativeSharedTextureMemoryCreateTexture(WGPUSharedTextureMemory cSelf, WGPUTextureDescriptor const * descriptor);
extern WGPUStatus NativeSharedTextureMemoryEndAccess(WGPUSharedTextureMemory cSelf, WGPUTexture texture, WGPUSharedTextureMemoryEndAccessState * descriptor);
extern WGPUStatus NativeSharedTextureMemoryGetProperties(WGPUSharedTextureMemory cSelf, WGPUSharedTextureMemoryProperties * properties);
extern WGPUBool NativeSharedTextureMemoryIsDeviceLost(WGPUSharedTextureMemory cSelf);
extern void NativeSharedTextureMemorySetLabel(WGPUSharedTextureMemory cSelf, WGPUStringView label);
extern void NativeSharedTextureMemoryAddRef(WGPUSharedTextureMemory cSelf);
extern void NativeSharedTextureMemoryRelease(WGPUSharedTextureMemory cSelf);
extern void NativeSharedTextureMemoryEndAccessStateFreeMembers(WGPUSharedTextureMemoryEndAccessState cSelf);
extern void NativeSupportedFeaturesFreeMembers(WGPUSupportedFeatures cSelf);
extern void NativeSupportedInstanceFeaturesFreeMembers(WGPUSupportedInstanceFeatures cSelf);
extern void NativeSupportedWGSLLanguageFeaturesFreeMembers(WGPUSupportedWGSLLanguageFeatures cSelf);
extern void NativeSurfaceConfigure(WGPUSurface cSelf, WGPUSurfaceConfiguration const * config);
extern WGPUStatus NativeSurfaceGetCapabilities(WGPUSurface cSelf, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities);
extern void NativeSurfaceGetCurrentTexture(WGPUSurface cSelf, WGPUSurfaceTexture * surfaceTexture);
extern WGPUStatus NativeSurfacePresent(WGPUSurface cSelf);
extern void NativeSurfaceSetLabel(WGPUSurface cSelf, WGPUStringView label);
extern void NativeSurfaceUnconfigure(WGPUSurface cSelf);
extern void NativeSurfaceAddRef(WGPUSurface cSelf);
extern void NativeSurfaceRelease(WGPUSurface cSelf);
extern void NativeSurfaceCapabilitiesFreeMembers(WGPUSurfaceCapabilities cSelf);
extern void NativeTexelBufferViewSetLabel(WGPUTexelBufferView cSelf, WGPUStringView label);
extern void NativeTexelBufferViewAddRef(WGPUTexelBufferView cSelf);
extern void NativeTexelBufferViewRelease(WGPUTexelBufferView cSelf);
extern WGPUTextureView NativeTextureCreateErrorView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor);
extern WGPUTextureView NativeTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor);
extern void NativeTextureDestroy(WGPUTexture cSelf);
extern uint32_t NativeTextureGetDepthOrArrayLayers(WGPUTexture cSelf);
extern WGPUTextureDimension NativeTextureGetDimension(WGPUTexture cSelf);
extern WGPUTextureFormat NativeTextureGetFormat(WGPUTexture cSelf);
extern uint32_t NativeTextureGetHeight(WGPUTexture cSelf);
extern uint32_t NativeTextureGetMipLevelCount(WGPUTexture cSelf);
extern uint32_t NativeTextureGetSampleCount(WGPUTexture cSelf);
extern WGPUTextureViewDimension NativeTextureGetTextureBindingViewDimension(WGPUTexture cSelf);
extern WGPUTextureUsage NativeTextureGetUsage(WGPUTexture cSelf);
extern uint32_t NativeTextureGetWidth(WGPUTexture cSelf);
extern void NativeTexturePin(WGPUTexture cSelf, WGPUTextureUsage usage);
extern void NativeTextureSetLabel(WGPUTexture cSelf, WGPUStringView label);
extern void NativeTextureSetOwnershipForMemoryDump(WGPUTexture cSelf, uint64_t ownerGuid);
extern void NativeTextureUnpin(WGPUTexture cSelf);
extern void NativeTextureAddRef(WGPUTexture cSelf);
extern void NativeTextureRelease(WGPUTexture cSelf);
extern void NativeTextureViewSetLabel(WGPUTextureView cSelf, WGPUStringView label);
extern void NativeTextureViewAddRef(WGPUTextureView cSelf);
extern void NativeTextureViewRelease(WGPUTextureView cSelf);

}

extern "C" {
    using namespace dawn::native;

    WGPUInstance wgpuCreateInstance (WGPUInstanceDescriptor const * descriptor) {
        return NativeCreateInstance(descriptor);
    }
    void wgpuGetInstanceFeatures (WGPUSupportedInstanceFeatures * features) {
        return NativeGetInstanceFeatures(features);
    }
    WGPUStatus wgpuGetInstanceLimits (WGPUInstanceLimits * limits) {
        return NativeGetInstanceLimits(limits);
    }
    WGPUBool wgpuHasInstanceFeature (WGPUInstanceFeatureName feature) {
        return NativeHasInstanceFeature(feature);
    }
    WGPUProc wgpuGetProcAddress (WGPUStringView procName) {
        return NativeGetProcAddress(procName);
    }

    WGPUDevice wgpuAdapterCreateDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor) {
        return NativeAdapterCreateDevice(
            cSelf, descriptor);
    }
    void wgpuAdapterGetFeatures(WGPUAdapter cSelf, WGPUSupportedFeatures * features) {
        return NativeAdapterGetFeatures(
            cSelf, features);
    }
    WGPUStatus wgpuAdapterGetFormatCapabilities(WGPUAdapter cSelf, WGPUTextureFormat format, WGPUDawnFormatCapabilities * capabilities) {
        return NativeAdapterGetFormatCapabilities(
            cSelf, format, capabilities);
    }
    WGPUStatus wgpuAdapterGetInfo(WGPUAdapter cSelf, WGPUAdapterInfo * info) {
        return NativeAdapterGetInfo(
            cSelf, info);
    }
    WGPUInstance wgpuAdapterGetInstance(WGPUAdapter cSelf) {
        return NativeAdapterGetInstance(
            cSelf);
    }
    WGPUStatus wgpuAdapterGetLimits(WGPUAdapter cSelf, WGPULimits * limits) {
        return NativeAdapterGetLimits(
            cSelf, limits);
    }
    WGPUBool wgpuAdapterHasFeature(WGPUAdapter cSelf, WGPUFeatureName feature) {
        return NativeAdapterHasFeature(
            cSelf, feature);
    }
    WGPUFuture wgpuAdapterRequestDevice(WGPUAdapter cSelf, WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallbackInfo callbackInfo) {
        return NativeAdapterRequestDevice(
            cSelf, descriptor, callbackInfo);
    }
    void wgpuAdapterAddRef(WGPUAdapter cSelf) {
        return NativeAdapterAddRef(
            cSelf);
    }
    void wgpuAdapterRelease(WGPUAdapter cSelf) {
        return NativeAdapterRelease(
            cSelf);
    }
    void wgpuAdapterInfoFreeMembers(WGPUAdapterInfo cSelf) {
        return NativeAdapterInfoFreeMembers(
            cSelf);
    }
    void wgpuAdapterPropertiesMemoryHeapsFreeMembers(WGPUAdapterPropertiesMemoryHeaps cSelf) {
        return NativeAdapterPropertiesMemoryHeapsFreeMembers(
            cSelf);
    }
    void wgpuAdapterPropertiesSubgroupMatrixConfigsFreeMembers(WGPUAdapterPropertiesSubgroupMatrixConfigs cSelf) {
        return NativeAdapterPropertiesSubgroupMatrixConfigsFreeMembers(
            cSelf);
    }
    void wgpuBindGroupSetLabel(WGPUBindGroup cSelf, WGPUStringView label) {
        return NativeBindGroupSetLabel(
            cSelf, label);
    }
    void wgpuBindGroupAddRef(WGPUBindGroup cSelf) {
        return NativeBindGroupAddRef(
            cSelf);
    }
    void wgpuBindGroupRelease(WGPUBindGroup cSelf) {
        return NativeBindGroupRelease(
            cSelf);
    }
    void wgpuBindGroupLayoutSetLabel(WGPUBindGroupLayout cSelf, WGPUStringView label) {
        return NativeBindGroupLayoutSetLabel(
            cSelf, label);
    }
    void wgpuBindGroupLayoutAddRef(WGPUBindGroupLayout cSelf) {
        return NativeBindGroupLayoutAddRef(
            cSelf);
    }
    void wgpuBindGroupLayoutRelease(WGPUBindGroupLayout cSelf) {
        return NativeBindGroupLayoutRelease(
            cSelf);
    }
    WGPUTexelBufferView wgpuBufferCreateTexelView(WGPUBuffer cSelf, WGPUTexelBufferViewDescriptor const * descriptor) {
        return NativeBufferCreateTexelView(
            cSelf, descriptor);
    }
    void wgpuBufferDestroy(WGPUBuffer cSelf) {
        return NativeBufferDestroy(
            cSelf);
    }
    void const * wgpuBufferGetConstMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        return NativeBufferGetConstMappedRange(
            cSelf, offset, size);
    }
    void * wgpuBufferGetMappedRange(WGPUBuffer cSelf, size_t offset, size_t size) {
        return NativeBufferGetMappedRange(
            cSelf, offset, size);
    }
    WGPUBufferMapState wgpuBufferGetMapState(WGPUBuffer cSelf) {
        return NativeBufferGetMapState(
            cSelf);
    }
    uint64_t wgpuBufferGetSize(WGPUBuffer cSelf) {
        return NativeBufferGetSize(
            cSelf);
    }
    WGPUBufferUsage wgpuBufferGetUsage(WGPUBuffer cSelf) {
        return NativeBufferGetUsage(
            cSelf);
    }
    WGPUFuture wgpuBufferMapAsync(WGPUBuffer cSelf, WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo) {
        return NativeBufferMapAsync(
            cSelf, mode, offset, size, callbackInfo);
    }
    WGPUStatus wgpuBufferReadMappedRange(WGPUBuffer cSelf, size_t offset, void * data, size_t size) {
        return NativeBufferReadMappedRange(
            cSelf, offset, data, size);
    }
    void wgpuBufferSetLabel(WGPUBuffer cSelf, WGPUStringView label) {
        return NativeBufferSetLabel(
            cSelf, label);
    }
    void wgpuBufferUnmap(WGPUBuffer cSelf) {
        return NativeBufferUnmap(
            cSelf);
    }
    WGPUStatus wgpuBufferWriteMappedRange(WGPUBuffer cSelf, size_t offset, void const * data, size_t size) {
        return NativeBufferWriteMappedRange(
            cSelf, offset, data, size);
    }
    void wgpuBufferAddRef(WGPUBuffer cSelf) {
        return NativeBufferAddRef(
            cSelf);
    }
    void wgpuBufferRelease(WGPUBuffer cSelf) {
        return NativeBufferRelease(
            cSelf);
    }
    void wgpuCommandBufferSetLabel(WGPUCommandBuffer cSelf, WGPUStringView label) {
        return NativeCommandBufferSetLabel(
            cSelf, label);
    }
    void wgpuCommandBufferAddRef(WGPUCommandBuffer cSelf) {
        return NativeCommandBufferAddRef(
            cSelf);
    }
    void wgpuCommandBufferRelease(WGPUCommandBuffer cSelf) {
        return NativeCommandBufferRelease(
            cSelf);
    }
    WGPUComputePassEncoder wgpuCommandEncoderBeginComputePass(WGPUCommandEncoder cSelf, WGPUComputePassDescriptor const * descriptor) {
        return NativeCommandEncoderBeginComputePass(
            cSelf, descriptor);
    }
    WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass(WGPUCommandEncoder cSelf, WGPURenderPassDescriptor const * descriptor) {
        return NativeCommandEncoderBeginRenderPass(
            cSelf, descriptor);
    }
    void wgpuCommandEncoderClearBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        return NativeCommandEncoderClearBuffer(
            cSelf, buffer, offset, size);
    }
    void wgpuCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder cSelf, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
        return NativeCommandEncoderCopyBufferToBuffer(
            cSelf, source, sourceOffset, destination, destinationOffset, size);
    }
    void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder cSelf, WGPUTexelCopyBufferInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) {
        return NativeCommandEncoderCopyBufferToTexture(
            cSelf, source, destination, copySize);
    }
    void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder cSelf, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyBufferInfo const * destination, WGPUExtent3D const * copySize) {
        return NativeCommandEncoderCopyTextureToBuffer(
            cSelf, source, destination, copySize);
    }
    void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder cSelf, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) {
        return NativeCommandEncoderCopyTextureToTexture(
            cSelf, source, destination, copySize);
    }
    WGPUCommandBuffer wgpuCommandEncoderFinish(WGPUCommandEncoder cSelf, WGPUCommandBufferDescriptor const * descriptor) {
        return NativeCommandEncoderFinish(
            cSelf, descriptor);
    }
    void wgpuCommandEncoderInjectValidationError(WGPUCommandEncoder cSelf, WGPUStringView message) {
        return NativeCommandEncoderInjectValidationError(
            cSelf, message);
    }
    void wgpuCommandEncoderInsertDebugMarker(WGPUCommandEncoder cSelf, WGPUStringView markerLabel) {
        return NativeCommandEncoderInsertDebugMarker(
            cSelf, markerLabel);
    }
    void wgpuCommandEncoderPopDebugGroup(WGPUCommandEncoder cSelf) {
        return NativeCommandEncoderPopDebugGroup(
            cSelf);
    }
    void wgpuCommandEncoderPushDebugGroup(WGPUCommandEncoder cSelf, WGPUStringView groupLabel) {
        return NativeCommandEncoderPushDebugGroup(
            cSelf, groupLabel);
    }
    void wgpuCommandEncoderResolveQuerySet(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
        return NativeCommandEncoderResolveQuerySet(
            cSelf, querySet, firstQuery, queryCount, destination, destinationOffset);
    }
    void wgpuCommandEncoderSetLabel(WGPUCommandEncoder cSelf, WGPUStringView label) {
        return NativeCommandEncoderSetLabel(
            cSelf, label);
    }
    void wgpuCommandEncoderWriteBuffer(WGPUCommandEncoder cSelf, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
        return NativeCommandEncoderWriteBuffer(
            cSelf, buffer, bufferOffset, data, size);
    }
    void wgpuCommandEncoderWriteTimestamp(WGPUCommandEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        return NativeCommandEncoderWriteTimestamp(
            cSelf, querySet, queryIndex);
    }
    void wgpuCommandEncoderAddRef(WGPUCommandEncoder cSelf) {
        return NativeCommandEncoderAddRef(
            cSelf);
    }
    void wgpuCommandEncoderRelease(WGPUCommandEncoder cSelf) {
        return NativeCommandEncoderRelease(
            cSelf);
    }
    void wgpuComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder cSelf, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
        return NativeComputePassEncoderDispatchWorkgroups(
            cSelf, workgroupCountX, workgroupCountY, workgroupCountZ);
    }
    void wgpuComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        return NativeComputePassEncoderDispatchWorkgroupsIndirect(
            cSelf, indirectBuffer, indirectOffset);
    }
    void wgpuComputePassEncoderEnd(WGPUComputePassEncoder cSelf) {
        return NativeComputePassEncoderEnd(
            cSelf);
    }
    void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder cSelf, WGPUStringView markerLabel) {
        return NativeComputePassEncoderInsertDebugMarker(
            cSelf, markerLabel);
    }
    void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder cSelf) {
        return NativeComputePassEncoderPopDebugGroup(
            cSelf);
    }
    void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder cSelf, WGPUStringView groupLabel) {
        return NativeComputePassEncoderPushDebugGroup(
            cSelf, groupLabel);
    }
    void wgpuComputePassEncoderSetBindGroup(WGPUComputePassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        return NativeComputePassEncoderSetBindGroup(
            cSelf, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void wgpuComputePassEncoderSetImmediates(WGPUComputePassEncoder cSelf, uint32_t offset, void const * data, size_t size) {
        return NativeComputePassEncoderSetImmediates(
            cSelf, offset, data, size);
    }
    void wgpuComputePassEncoderSetLabel(WGPUComputePassEncoder cSelf, WGPUStringView label) {
        return NativeComputePassEncoderSetLabel(
            cSelf, label);
    }
    void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder cSelf, WGPUComputePipeline pipeline) {
        return NativeComputePassEncoderSetPipeline(
            cSelf, pipeline);
    }
    void wgpuComputePassEncoderSetResourceTable(WGPUComputePassEncoder cSelf, WGPUResourceTable table) {
        return NativeComputePassEncoderSetResourceTable(
            cSelf, table);
    }
    void wgpuComputePassEncoderWriteTimestamp(WGPUComputePassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        return NativeComputePassEncoderWriteTimestamp(
            cSelf, querySet, queryIndex);
    }
    void wgpuComputePassEncoderAddRef(WGPUComputePassEncoder cSelf) {
        return NativeComputePassEncoderAddRef(
            cSelf);
    }
    void wgpuComputePassEncoderRelease(WGPUComputePassEncoder cSelf) {
        return NativeComputePassEncoderRelease(
            cSelf);
    }
    WGPUBindGroupLayout wgpuComputePipelineGetBindGroupLayout(WGPUComputePipeline cSelf, uint32_t groupIndex) {
        return NativeComputePipelineGetBindGroupLayout(
            cSelf, groupIndex);
    }
    void wgpuComputePipelineSetLabel(WGPUComputePipeline cSelf, WGPUStringView label) {
        return NativeComputePipelineSetLabel(
            cSelf, label);
    }
    void wgpuComputePipelineAddRef(WGPUComputePipeline cSelf) {
        return NativeComputePipelineAddRef(
            cSelf);
    }
    void wgpuComputePipelineRelease(WGPUComputePipeline cSelf) {
        return NativeComputePipelineRelease(
            cSelf);
    }
    void wgpuDawnDrmFormatCapabilitiesFreeMembers(WGPUDawnDrmFormatCapabilities cSelf) {
        return NativeDawnDrmFormatCapabilitiesFreeMembers(
            cSelf);
    }
    WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice cSelf, WGPUBindGroupDescriptor const * descriptor) {
        return NativeDeviceCreateBindGroup(
            cSelf, descriptor);
    }
    WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice cSelf, WGPUBindGroupLayoutDescriptor const * descriptor) {
        return NativeDeviceCreateBindGroupLayout(
            cSelf, descriptor);
    }
    WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        return NativeDeviceCreateBuffer(
            cSelf, descriptor);
    }
    WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice cSelf, WGPUCommandEncoderDescriptor const * descriptor) {
        return NativeDeviceCreateCommandEncoder(
            cSelf, descriptor);
    }
    WGPUComputePipeline wgpuDeviceCreateComputePipeline(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor) {
        return NativeDeviceCreateComputePipeline(
            cSelf, descriptor);
    }
    WGPUFuture wgpuDeviceCreateComputePipelineAsync(WGPUDevice cSelf, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo) {
        return NativeDeviceCreateComputePipelineAsync(
            cSelf, descriptor, callbackInfo);
    }
    WGPUBuffer wgpuDeviceCreateErrorBuffer(WGPUDevice cSelf, WGPUBufferDescriptor const * descriptor) {
        return NativeDeviceCreateErrorBuffer(
            cSelf, descriptor);
    }
    WGPUExternalTexture wgpuDeviceCreateErrorExternalTexture(WGPUDevice cSelf) {
        return NativeDeviceCreateErrorExternalTexture(
            cSelf);
    }
    WGPUShaderModule wgpuDeviceCreateErrorShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor, WGPUStringView errorMessage) {
        return NativeDeviceCreateErrorShaderModule(
            cSelf, descriptor, errorMessage);
    }
    WGPUTexture wgpuDeviceCreateErrorTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        return NativeDeviceCreateErrorTexture(
            cSelf, descriptor);
    }
    WGPUExternalTexture wgpuDeviceCreateExternalTexture(WGPUDevice cSelf, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
        return NativeDeviceCreateExternalTexture(
            cSelf, externalTextureDescriptor);
    }
    WGPUPipelineLayout wgpuDeviceCreatePipelineLayout(WGPUDevice cSelf, WGPUPipelineLayoutDescriptor const * descriptor) {
        return NativeDeviceCreatePipelineLayout(
            cSelf, descriptor);
    }
    WGPUQuerySet wgpuDeviceCreateQuerySet(WGPUDevice cSelf, WGPUQuerySetDescriptor const * descriptor) {
        return NativeDeviceCreateQuerySet(
            cSelf, descriptor);
    }
    WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice cSelf, WGPURenderBundleEncoderDescriptor const * descriptor) {
        return NativeDeviceCreateRenderBundleEncoder(
            cSelf, descriptor);
    }
    WGPURenderPipeline wgpuDeviceCreateRenderPipeline(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor) {
        return NativeDeviceCreateRenderPipeline(
            cSelf, descriptor);
    }
    WGPUFuture wgpuDeviceCreateRenderPipelineAsync(WGPUDevice cSelf, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo) {
        return NativeDeviceCreateRenderPipelineAsync(
            cSelf, descriptor, callbackInfo);
    }
    WGPUResourceTable wgpuDeviceCreateResourceTable(WGPUDevice cSelf, WGPUResourceTableDescriptor const * descriptor) {
        return NativeDeviceCreateResourceTable(
            cSelf, descriptor);
    }
    WGPUSampler wgpuDeviceCreateSampler(WGPUDevice cSelf, WGPUSamplerDescriptor const * descriptor) {
        return NativeDeviceCreateSampler(
            cSelf, descriptor);
    }
    WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice cSelf, WGPUShaderModuleDescriptor const * descriptor) {
        return NativeDeviceCreateShaderModule(
            cSelf, descriptor);
    }
    WGPUTexture wgpuDeviceCreateTexture(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        return NativeDeviceCreateTexture(
            cSelf, descriptor);
    }
    void wgpuDeviceDestroy(WGPUDevice cSelf) {
        return NativeDeviceDestroy(
            cSelf);
    }
    void wgpuDeviceForceLoss(WGPUDevice cSelf, WGPUDeviceLostReason type, WGPUStringView message) {
        return NativeDeviceForceLoss(
            cSelf, type, message);
    }
    WGPUAdapter wgpuDeviceGetAdapter(WGPUDevice cSelf) {
        return NativeDeviceGetAdapter(
            cSelf);
    }
    WGPUStatus wgpuDeviceGetAdapterInfo(WGPUDevice cSelf, WGPUAdapterInfo * adapterInfo) {
        return NativeDeviceGetAdapterInfo(
            cSelf, adapterInfo);
    }
    WGPUStatus wgpuDeviceGetAHardwareBufferProperties(WGPUDevice cSelf, void * handle, WGPUAHardwareBufferProperties * properties) {
        return NativeDeviceGetAHardwareBufferProperties(
            cSelf, handle, properties);
    }
    void wgpuDeviceGetFeatures(WGPUDevice cSelf, WGPUSupportedFeatures * features) {
        return NativeDeviceGetFeatures(
            cSelf, features);
    }
    WGPUStatus wgpuDeviceGetLimits(WGPUDevice cSelf, WGPULimits * limits) {
        return NativeDeviceGetLimits(
            cSelf, limits);
    }
    WGPUFuture wgpuDeviceGetLostFuture(WGPUDevice cSelf) {
        return NativeDeviceGetLostFuture(
            cSelf);
    }
    WGPUQueue wgpuDeviceGetQueue(WGPUDevice cSelf) {
        return NativeDeviceGetQueue(
            cSelf);
    }
    WGPUBool wgpuDeviceHasFeature(WGPUDevice cSelf, WGPUFeatureName feature) {
        return NativeDeviceHasFeature(
            cSelf, feature);
    }
    WGPUSharedBufferMemory wgpuDeviceImportSharedBufferMemory(WGPUDevice cSelf, WGPUSharedBufferMemoryDescriptor const * descriptor) {
        return NativeDeviceImportSharedBufferMemory(
            cSelf, descriptor);
    }
    WGPUSharedFence wgpuDeviceImportSharedFence(WGPUDevice cSelf, WGPUSharedFenceDescriptor const * descriptor) {
        return NativeDeviceImportSharedFence(
            cSelf, descriptor);
    }
    WGPUSharedTextureMemory wgpuDeviceImportSharedTextureMemory(WGPUDevice cSelf, WGPUSharedTextureMemoryDescriptor const * descriptor) {
        return NativeDeviceImportSharedTextureMemory(
            cSelf, descriptor);
    }
    void wgpuDeviceInjectError(WGPUDevice cSelf, WGPUErrorType type, WGPUStringView message) {
        return NativeDeviceInjectError(
            cSelf, type, message);
    }
    WGPUFuture wgpuDevicePopErrorScope(WGPUDevice cSelf, WGPUPopErrorScopeCallbackInfo callbackInfo) {
        return NativeDevicePopErrorScope(
            cSelf, callbackInfo);
    }
    void wgpuDevicePushErrorScope(WGPUDevice cSelf, WGPUErrorFilter filter) {
        return NativeDevicePushErrorScope(
            cSelf, filter);
    }
    void wgpuDeviceSetLabel(WGPUDevice cSelf, WGPUStringView label) {
        return NativeDeviceSetLabel(
            cSelf, label);
    }
    void wgpuDeviceSetLoggingCallback(WGPUDevice cSelf, WGPULoggingCallbackInfo callbackInfo) {
        return NativeDeviceSetLoggingCallback(
            cSelf, callbackInfo);
    }
    void wgpuDeviceTick(WGPUDevice cSelf) {
        return NativeDeviceTick(
            cSelf);
    }
    void wgpuDeviceValidateTextureDescriptor(WGPUDevice cSelf, WGPUTextureDescriptor const * descriptor) {
        return NativeDeviceValidateTextureDescriptor(
            cSelf, descriptor);
    }
    void wgpuDeviceAddRef(WGPUDevice cSelf) {
        return NativeDeviceAddRef(
            cSelf);
    }
    void wgpuDeviceRelease(WGPUDevice cSelf) {
        return NativeDeviceRelease(
            cSelf);
    }
    void wgpuExternalTextureDestroy(WGPUExternalTexture cSelf) {
        return NativeExternalTextureDestroy(
            cSelf);
    }
    void wgpuExternalTextureExpire(WGPUExternalTexture cSelf) {
        return NativeExternalTextureExpire(
            cSelf);
    }
    void wgpuExternalTextureRefresh(WGPUExternalTexture cSelf) {
        return NativeExternalTextureRefresh(
            cSelf);
    }
    void wgpuExternalTextureSetLabel(WGPUExternalTexture cSelf, WGPUStringView label) {
        return NativeExternalTextureSetLabel(
            cSelf, label);
    }
    void wgpuExternalTextureAddRef(WGPUExternalTexture cSelf) {
        return NativeExternalTextureAddRef(
            cSelf);
    }
    void wgpuExternalTextureRelease(WGPUExternalTexture cSelf) {
        return NativeExternalTextureRelease(
            cSelf);
    }
    WGPUSurface wgpuInstanceCreateSurface(WGPUInstance cSelf, WGPUSurfaceDescriptor const * descriptor) {
        return NativeInstanceCreateSurface(
            cSelf, descriptor);
    }
    void wgpuInstanceGetWGSLLanguageFeatures(WGPUInstance cSelf, WGPUSupportedWGSLLanguageFeatures * features) {
        return NativeInstanceGetWGSLLanguageFeatures(
            cSelf, features);
    }
    WGPUBool wgpuInstanceHasWGSLLanguageFeature(WGPUInstance cSelf, WGPUWGSLLanguageFeatureName feature) {
        return NativeInstanceHasWGSLLanguageFeature(
            cSelf, feature);
    }
    void wgpuInstanceProcessEvents(WGPUInstance cSelf) {
        return NativeInstanceProcessEvents(
            cSelf);
    }
    WGPUFuture wgpuInstanceRequestAdapter(WGPUInstance cSelf, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallbackInfo callbackInfo) {
        return NativeInstanceRequestAdapter(
            cSelf, options, callbackInfo);
    }
    WGPUWaitStatus wgpuInstanceWaitAny(WGPUInstance cSelf, size_t futureCount, WGPUFutureWaitInfo * futures, uint64_t timeoutNS) {
        return NativeInstanceWaitAny(
            cSelf, futureCount, futures, timeoutNS);
    }
    void wgpuInstanceAddRef(WGPUInstance cSelf) {
        return NativeInstanceAddRef(
            cSelf);
    }
    void wgpuInstanceRelease(WGPUInstance cSelf) {
        return NativeInstanceRelease(
            cSelf);
    }
    void wgpuPipelineLayoutSetLabel(WGPUPipelineLayout cSelf, WGPUStringView label) {
        return NativePipelineLayoutSetLabel(
            cSelf, label);
    }
    void wgpuPipelineLayoutAddRef(WGPUPipelineLayout cSelf) {
        return NativePipelineLayoutAddRef(
            cSelf);
    }
    void wgpuPipelineLayoutRelease(WGPUPipelineLayout cSelf) {
        return NativePipelineLayoutRelease(
            cSelf);
    }
    void wgpuQuerySetDestroy(WGPUQuerySet cSelf) {
        return NativeQuerySetDestroy(
            cSelf);
    }
    uint32_t wgpuQuerySetGetCount(WGPUQuerySet cSelf) {
        return NativeQuerySetGetCount(
            cSelf);
    }
    WGPUQueryType wgpuQuerySetGetType(WGPUQuerySet cSelf) {
        return NativeQuerySetGetType(
            cSelf);
    }
    void wgpuQuerySetSetLabel(WGPUQuerySet cSelf, WGPUStringView label) {
        return NativeQuerySetSetLabel(
            cSelf, label);
    }
    void wgpuQuerySetAddRef(WGPUQuerySet cSelf) {
        return NativeQuerySetAddRef(
            cSelf);
    }
    void wgpuQuerySetRelease(WGPUQuerySet cSelf) {
        return NativeQuerySetRelease(
            cSelf);
    }
    void wgpuQueueCopyExternalTextureForBrowser(WGPUQueue cSelf, WGPUImageCopyExternalTexture const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        return NativeQueueCopyExternalTextureForBrowser(
            cSelf, source, destination, copySize, options);
    }
    void wgpuQueueCopyTextureForBrowser(WGPUQueue cSelf, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
        return NativeQueueCopyTextureForBrowser(
            cSelf, source, destination, copySize, options);
    }
    WGPUFuture wgpuQueueOnSubmittedWorkDone(WGPUQueue cSelf, WGPUQueueWorkDoneCallbackInfo callbackInfo) {
        return NativeQueueOnSubmittedWorkDone(
            cSelf, callbackInfo);
    }
    void wgpuQueueSetLabel(WGPUQueue cSelf, WGPUStringView label) {
        return NativeQueueSetLabel(
            cSelf, label);
    }
    void wgpuQueueSubmit(WGPUQueue cSelf, size_t commandCount, WGPUCommandBuffer const * commands) {
        return NativeQueueSubmit(
            cSelf, commandCount, commands);
    }
    void wgpuQueueWriteBuffer(WGPUQueue cSelf, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
        return NativeQueueWriteBuffer(
            cSelf, buffer, bufferOffset, data, size);
    }
    void wgpuQueueWriteTexture(WGPUQueue cSelf, WGPUTexelCopyTextureInfo const * destination, void const * data, size_t dataSize, WGPUTexelCopyBufferLayout const * dataLayout, WGPUExtent3D const * writeSize) {
        return NativeQueueWriteTexture(
            cSelf, destination, data, dataSize, dataLayout, writeSize);
    }
    void wgpuQueueAddRef(WGPUQueue cSelf) {
        return NativeQueueAddRef(
            cSelf);
    }
    void wgpuQueueRelease(WGPUQueue cSelf) {
        return NativeQueueRelease(
            cSelf);
    }
    void wgpuRenderBundleSetLabel(WGPURenderBundle cSelf, WGPUStringView label) {
        return NativeRenderBundleSetLabel(
            cSelf, label);
    }
    void wgpuRenderBundleAddRef(WGPURenderBundle cSelf) {
        return NativeRenderBundleAddRef(
            cSelf);
    }
    void wgpuRenderBundleRelease(WGPURenderBundle cSelf) {
        return NativeRenderBundleRelease(
            cSelf);
    }
    void wgpuRenderBundleEncoderDraw(WGPURenderBundleEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        return NativeRenderBundleEncoderDraw(
            cSelf, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    void wgpuRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        return NativeRenderBundleEncoderDrawIndexed(
            cSelf, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
    }
    void wgpuRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        return NativeRenderBundleEncoderDrawIndexedIndirect(
            cSelf, indirectBuffer, indirectOffset);
    }
    void wgpuRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        return NativeRenderBundleEncoderDrawIndirect(
            cSelf, indirectBuffer, indirectOffset);
    }
    WGPURenderBundle wgpuRenderBundleEncoderFinish(WGPURenderBundleEncoder cSelf, WGPURenderBundleDescriptor const * descriptor) {
        return NativeRenderBundleEncoderFinish(
            cSelf, descriptor);
    }
    void wgpuRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder cSelf, WGPUStringView markerLabel) {
        return NativeRenderBundleEncoderInsertDebugMarker(
            cSelf, markerLabel);
    }
    void wgpuRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder cSelf) {
        return NativeRenderBundleEncoderPopDebugGroup(
            cSelf);
    }
    void wgpuRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder cSelf, WGPUStringView groupLabel) {
        return NativeRenderBundleEncoderPushDebugGroup(
            cSelf, groupLabel);
    }
    void wgpuRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        return NativeRenderBundleEncoderSetBindGroup(
            cSelf, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void wgpuRenderBundleEncoderSetImmediates(WGPURenderBundleEncoder cSelf, uint32_t offset, void const * data, size_t size) {
        return NativeRenderBundleEncoderSetImmediates(
            cSelf, offset, data, size);
    }
    void wgpuRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        return NativeRenderBundleEncoderSetIndexBuffer(
            cSelf, buffer, format, offset, size);
    }
    void wgpuRenderBundleEncoderSetLabel(WGPURenderBundleEncoder cSelf, WGPUStringView label) {
        return NativeRenderBundleEncoderSetLabel(
            cSelf, label);
    }
    void wgpuRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder cSelf, WGPURenderPipeline pipeline) {
        return NativeRenderBundleEncoderSetPipeline(
            cSelf, pipeline);
    }
    void wgpuRenderBundleEncoderSetResourceTable(WGPURenderBundleEncoder cSelf, WGPUResourceTable table) {
        return NativeRenderBundleEncoderSetResourceTable(
            cSelf, table);
    }
    void wgpuRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        return NativeRenderBundleEncoderSetVertexBuffer(
            cSelf, slot, buffer, offset, size);
    }
    void wgpuRenderBundleEncoderAddRef(WGPURenderBundleEncoder cSelf) {
        return NativeRenderBundleEncoderAddRef(
            cSelf);
    }
    void wgpuRenderBundleEncoderRelease(WGPURenderBundleEncoder cSelf) {
        return NativeRenderBundleEncoderRelease(
            cSelf);
    }
    void wgpuRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder cSelf, uint32_t queryIndex) {
        return NativeRenderPassEncoderBeginOcclusionQuery(
            cSelf, queryIndex);
    }
    void wgpuRenderPassEncoderDraw(WGPURenderPassEncoder cSelf, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
        return NativeRenderPassEncoderDraw(
            cSelf, vertexCount, instanceCount, firstVertex, firstInstance);
    }
    void wgpuRenderPassEncoderDrawIndexed(WGPURenderPassEncoder cSelf, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
        return NativeRenderPassEncoderDrawIndexed(
            cSelf, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
    }
    void wgpuRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        return NativeRenderPassEncoderDrawIndexedIndirect(
            cSelf, indirectBuffer, indirectOffset);
    }
    void wgpuRenderPassEncoderDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
        return NativeRenderPassEncoderDrawIndirect(
            cSelf, indirectBuffer, indirectOffset);
    }
    void wgpuRenderPassEncoderEnd(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderEnd(
            cSelf);
    }
    void wgpuRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderEndOcclusionQuery(
            cSelf);
    }
    void wgpuRenderPassEncoderExecuteBundles(WGPURenderPassEncoder cSelf, size_t bundleCount, WGPURenderBundle const * bundles) {
        return NativeRenderPassEncoderExecuteBundles(
            cSelf, bundleCount, bundles);
    }
    void wgpuRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder cSelf, WGPUStringView markerLabel) {
        return NativeRenderPassEncoderInsertDebugMarker(
            cSelf, markerLabel);
    }
    void wgpuRenderPassEncoderMultiDrawIndexedIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) {
        return NativeRenderPassEncoderMultiDrawIndexedIndirect(
            cSelf, indirectBuffer, indirectOffset, maxDrawCount, drawCountBuffer, drawCountBufferOffset);
    }
    void wgpuRenderPassEncoderMultiDrawIndirect(WGPURenderPassEncoder cSelf, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) {
        return NativeRenderPassEncoderMultiDrawIndirect(
            cSelf, indirectBuffer, indirectOffset, maxDrawCount, drawCountBuffer, drawCountBufferOffset);
    }
    void wgpuRenderPassEncoderPixelLocalStorageBarrier(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderPixelLocalStorageBarrier(
            cSelf);
    }
    void wgpuRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderPopDebugGroup(
            cSelf);
    }
    void wgpuRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder cSelf, WGPUStringView groupLabel) {
        return NativeRenderPassEncoderPushDebugGroup(
            cSelf, groupLabel);
    }
    void wgpuRenderPassEncoderSetBindGroup(WGPURenderPassEncoder cSelf, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
        return NativeRenderPassEncoderSetBindGroup(
            cSelf, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
    }
    void wgpuRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder cSelf, WGPUColor const * color) {
        return NativeRenderPassEncoderSetBlendConstant(
            cSelf, color);
    }
    void wgpuRenderPassEncoderSetImmediates(WGPURenderPassEncoder cSelf, uint32_t offset, void const * data, size_t size) {
        return NativeRenderPassEncoderSetImmediates(
            cSelf, offset, data, size);
    }
    void wgpuRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder cSelf, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
        return NativeRenderPassEncoderSetIndexBuffer(
            cSelf, buffer, format, offset, size);
    }
    void wgpuRenderPassEncoderSetLabel(WGPURenderPassEncoder cSelf, WGPUStringView label) {
        return NativeRenderPassEncoderSetLabel(
            cSelf, label);
    }
    void wgpuRenderPassEncoderSetPipeline(WGPURenderPassEncoder cSelf, WGPURenderPipeline pipeline) {
        return NativeRenderPassEncoderSetPipeline(
            cSelf, pipeline);
    }
    void wgpuRenderPassEncoderSetResourceTable(WGPURenderPassEncoder cSelf, WGPUResourceTable table) {
        return NativeRenderPassEncoderSetResourceTable(
            cSelf, table);
    }
    void wgpuRenderPassEncoderSetScissorRect(WGPURenderPassEncoder cSelf, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        return NativeRenderPassEncoderSetScissorRect(
            cSelf, x, y, width, height);
    }
    void wgpuRenderPassEncoderSetStencilReference(WGPURenderPassEncoder cSelf, uint32_t reference) {
        return NativeRenderPassEncoderSetStencilReference(
            cSelf, reference);
    }
    void wgpuRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder cSelf, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
        return NativeRenderPassEncoderSetVertexBuffer(
            cSelf, slot, buffer, offset, size);
    }
    void wgpuRenderPassEncoderSetViewport(WGPURenderPassEncoder cSelf, float x, float y, float width, float height, float minDepth, float maxDepth) {
        return NativeRenderPassEncoderSetViewport(
            cSelf, x, y, width, height, minDepth, maxDepth);
    }
    void wgpuRenderPassEncoderWriteTimestamp(WGPURenderPassEncoder cSelf, WGPUQuerySet querySet, uint32_t queryIndex) {
        return NativeRenderPassEncoderWriteTimestamp(
            cSelf, querySet, queryIndex);
    }
    void wgpuRenderPassEncoderAddRef(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderAddRef(
            cSelf);
    }
    void wgpuRenderPassEncoderRelease(WGPURenderPassEncoder cSelf) {
        return NativeRenderPassEncoderRelease(
            cSelf);
    }
    WGPUBindGroupLayout wgpuRenderPipelineGetBindGroupLayout(WGPURenderPipeline cSelf, uint32_t groupIndex) {
        return NativeRenderPipelineGetBindGroupLayout(
            cSelf, groupIndex);
    }
    void wgpuRenderPipelineSetLabel(WGPURenderPipeline cSelf, WGPUStringView label) {
        return NativeRenderPipelineSetLabel(
            cSelf, label);
    }
    void wgpuRenderPipelineAddRef(WGPURenderPipeline cSelf) {
        return NativeRenderPipelineAddRef(
            cSelf);
    }
    void wgpuRenderPipelineRelease(WGPURenderPipeline cSelf) {
        return NativeRenderPipelineRelease(
            cSelf);
    }
    void wgpuResourceTableDestroy(WGPUResourceTable cSelf) {
        return NativeResourceTableDestroy(
            cSelf);
    }
    uint32_t wgpuResourceTableGetSize(WGPUResourceTable cSelf) {
        return NativeResourceTableGetSize(
            cSelf);
    }
    uint32_t wgpuResourceTableInsertBinding(WGPUResourceTable cSelf, WGPUBindingResource const * resource) {
        return NativeResourceTableInsertBinding(
            cSelf, resource);
    }
    WGPUStatus wgpuResourceTableRemoveBinding(WGPUResourceTable cSelf, uint32_t slot) {
        return NativeResourceTableRemoveBinding(
            cSelf, slot);
    }
    WGPUStatus wgpuResourceTableUpdate(WGPUResourceTable cSelf, uint32_t slot, WGPUBindingResource const * resource) {
        return NativeResourceTableUpdate(
            cSelf, slot, resource);
    }
    void wgpuResourceTableAddRef(WGPUResourceTable cSelf) {
        return NativeResourceTableAddRef(
            cSelf);
    }
    void wgpuResourceTableRelease(WGPUResourceTable cSelf) {
        return NativeResourceTableRelease(
            cSelf);
    }
    void wgpuSamplerSetLabel(WGPUSampler cSelf, WGPUStringView label) {
        return NativeSamplerSetLabel(
            cSelf, label);
    }
    void wgpuSamplerAddRef(WGPUSampler cSelf) {
        return NativeSamplerAddRef(
            cSelf);
    }
    void wgpuSamplerRelease(WGPUSampler cSelf) {
        return NativeSamplerRelease(
            cSelf);
    }
    WGPUFuture wgpuShaderModuleGetCompilationInfo(WGPUShaderModule cSelf, WGPUCompilationInfoCallbackInfo callbackInfo) {
        return NativeShaderModuleGetCompilationInfo(
            cSelf, callbackInfo);
    }
    void wgpuShaderModuleSetLabel(WGPUShaderModule cSelf, WGPUStringView label) {
        return NativeShaderModuleSetLabel(
            cSelf, label);
    }
    void wgpuShaderModuleAddRef(WGPUShaderModule cSelf) {
        return NativeShaderModuleAddRef(
            cSelf);
    }
    void wgpuShaderModuleRelease(WGPUShaderModule cSelf) {
        return NativeShaderModuleRelease(
            cSelf);
    }
    WGPUStatus wgpuSharedBufferMemoryBeginAccess(WGPUSharedBufferMemory cSelf, WGPUBuffer buffer, WGPUSharedBufferMemoryBeginAccessDescriptor const * descriptor) {
        return NativeSharedBufferMemoryBeginAccess(
            cSelf, buffer, descriptor);
    }
    WGPUBuffer wgpuSharedBufferMemoryCreateBuffer(WGPUSharedBufferMemory cSelf, WGPUBufferDescriptor const * descriptor) {
        return NativeSharedBufferMemoryCreateBuffer(
            cSelf, descriptor);
    }
    WGPUStatus wgpuSharedBufferMemoryEndAccess(WGPUSharedBufferMemory cSelf, WGPUBuffer buffer, WGPUSharedBufferMemoryEndAccessState * descriptor) {
        return NativeSharedBufferMemoryEndAccess(
            cSelf, buffer, descriptor);
    }
    WGPUStatus wgpuSharedBufferMemoryGetProperties(WGPUSharedBufferMemory cSelf, WGPUSharedBufferMemoryProperties * properties) {
        return NativeSharedBufferMemoryGetProperties(
            cSelf, properties);
    }
    WGPUBool wgpuSharedBufferMemoryIsDeviceLost(WGPUSharedBufferMemory cSelf) {
        return NativeSharedBufferMemoryIsDeviceLost(
            cSelf);
    }
    void wgpuSharedBufferMemorySetLabel(WGPUSharedBufferMemory cSelf, WGPUStringView label) {
        return NativeSharedBufferMemorySetLabel(
            cSelf, label);
    }
    void wgpuSharedBufferMemoryAddRef(WGPUSharedBufferMemory cSelf) {
        return NativeSharedBufferMemoryAddRef(
            cSelf);
    }
    void wgpuSharedBufferMemoryRelease(WGPUSharedBufferMemory cSelf) {
        return NativeSharedBufferMemoryRelease(
            cSelf);
    }
    void wgpuSharedBufferMemoryEndAccessStateFreeMembers(WGPUSharedBufferMemoryEndAccessState cSelf) {
        return NativeSharedBufferMemoryEndAccessStateFreeMembers(
            cSelf);
    }
    void wgpuSharedFenceExportInfo(WGPUSharedFence cSelf, WGPUSharedFenceExportInfo * info) {
        return NativeSharedFenceExportInfo(
            cSelf, info);
    }
    void wgpuSharedFenceAddRef(WGPUSharedFence cSelf) {
        return NativeSharedFenceAddRef(
            cSelf);
    }
    void wgpuSharedFenceRelease(WGPUSharedFence cSelf) {
        return NativeSharedFenceRelease(
            cSelf);
    }
    WGPUStatus wgpuSharedTextureMemoryBeginAccess(WGPUSharedTextureMemory cSelf, WGPUTexture texture, WGPUSharedTextureMemoryBeginAccessDescriptor const * descriptor) {
        return NativeSharedTextureMemoryBeginAccess(
            cSelf, texture, descriptor);
    }
    WGPUTexture wgpuSharedTextureMemoryCreateTexture(WGPUSharedTextureMemory cSelf, WGPUTextureDescriptor const * descriptor) {
        return NativeSharedTextureMemoryCreateTexture(
            cSelf, descriptor);
    }
    WGPUStatus wgpuSharedTextureMemoryEndAccess(WGPUSharedTextureMemory cSelf, WGPUTexture texture, WGPUSharedTextureMemoryEndAccessState * descriptor) {
        return NativeSharedTextureMemoryEndAccess(
            cSelf, texture, descriptor);
    }
    WGPUStatus wgpuSharedTextureMemoryGetProperties(WGPUSharedTextureMemory cSelf, WGPUSharedTextureMemoryProperties * properties) {
        return NativeSharedTextureMemoryGetProperties(
            cSelf, properties);
    }
    WGPUBool wgpuSharedTextureMemoryIsDeviceLost(WGPUSharedTextureMemory cSelf) {
        return NativeSharedTextureMemoryIsDeviceLost(
            cSelf);
    }
    void wgpuSharedTextureMemorySetLabel(WGPUSharedTextureMemory cSelf, WGPUStringView label) {
        return NativeSharedTextureMemorySetLabel(
            cSelf, label);
    }
    void wgpuSharedTextureMemoryAddRef(WGPUSharedTextureMemory cSelf) {
        return NativeSharedTextureMemoryAddRef(
            cSelf);
    }
    void wgpuSharedTextureMemoryRelease(WGPUSharedTextureMemory cSelf) {
        return NativeSharedTextureMemoryRelease(
            cSelf);
    }
    void wgpuSharedTextureMemoryEndAccessStateFreeMembers(WGPUSharedTextureMemoryEndAccessState cSelf) {
        return NativeSharedTextureMemoryEndAccessStateFreeMembers(
            cSelf);
    }
    void wgpuSupportedFeaturesFreeMembers(WGPUSupportedFeatures cSelf) {
        return NativeSupportedFeaturesFreeMembers(
            cSelf);
    }
    void wgpuSupportedInstanceFeaturesFreeMembers(WGPUSupportedInstanceFeatures cSelf) {
        return NativeSupportedInstanceFeaturesFreeMembers(
            cSelf);
    }
    void wgpuSupportedWGSLLanguageFeaturesFreeMembers(WGPUSupportedWGSLLanguageFeatures cSelf) {
        return NativeSupportedWGSLLanguageFeaturesFreeMembers(
            cSelf);
    }
    void wgpuSurfaceConfigure(WGPUSurface cSelf, WGPUSurfaceConfiguration const * config) {
        return NativeSurfaceConfigure(
            cSelf, config);
    }
    WGPUStatus wgpuSurfaceGetCapabilities(WGPUSurface cSelf, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities) {
        return NativeSurfaceGetCapabilities(
            cSelf, adapter, capabilities);
    }
    void wgpuSurfaceGetCurrentTexture(WGPUSurface cSelf, WGPUSurfaceTexture * surfaceTexture) {
        return NativeSurfaceGetCurrentTexture(
            cSelf, surfaceTexture);
    }
    WGPUStatus wgpuSurfacePresent(WGPUSurface cSelf) {
        return NativeSurfacePresent(
            cSelf);
    }
    void wgpuSurfaceSetLabel(WGPUSurface cSelf, WGPUStringView label) {
        return NativeSurfaceSetLabel(
            cSelf, label);
    }
    void wgpuSurfaceUnconfigure(WGPUSurface cSelf) {
        return NativeSurfaceUnconfigure(
            cSelf);
    }
    void wgpuSurfaceAddRef(WGPUSurface cSelf) {
        return NativeSurfaceAddRef(
            cSelf);
    }
    void wgpuSurfaceRelease(WGPUSurface cSelf) {
        return NativeSurfaceRelease(
            cSelf);
    }
    void wgpuSurfaceCapabilitiesFreeMembers(WGPUSurfaceCapabilities cSelf) {
        return NativeSurfaceCapabilitiesFreeMembers(
            cSelf);
    }
    void wgpuTexelBufferViewSetLabel(WGPUTexelBufferView cSelf, WGPUStringView label) {
        return NativeTexelBufferViewSetLabel(
            cSelf, label);
    }
    void wgpuTexelBufferViewAddRef(WGPUTexelBufferView cSelf) {
        return NativeTexelBufferViewAddRef(
            cSelf);
    }
    void wgpuTexelBufferViewRelease(WGPUTexelBufferView cSelf) {
        return NativeTexelBufferViewRelease(
            cSelf);
    }
    WGPUTextureView wgpuTextureCreateErrorView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
        return NativeTextureCreateErrorView(
            cSelf, descriptor);
    }
    WGPUTextureView wgpuTextureCreateView(WGPUTexture cSelf, WGPUTextureViewDescriptor const * descriptor) {
        return NativeTextureCreateView(
            cSelf, descriptor);
    }
    void wgpuTextureDestroy(WGPUTexture cSelf) {
        return NativeTextureDestroy(
            cSelf);
    }
    uint32_t wgpuTextureGetDepthOrArrayLayers(WGPUTexture cSelf) {
        return NativeTextureGetDepthOrArrayLayers(
            cSelf);
    }
    WGPUTextureDimension wgpuTextureGetDimension(WGPUTexture cSelf) {
        return NativeTextureGetDimension(
            cSelf);
    }
    WGPUTextureFormat wgpuTextureGetFormat(WGPUTexture cSelf) {
        return NativeTextureGetFormat(
            cSelf);
    }
    uint32_t wgpuTextureGetHeight(WGPUTexture cSelf) {
        return NativeTextureGetHeight(
            cSelf);
    }
    uint32_t wgpuTextureGetMipLevelCount(WGPUTexture cSelf) {
        return NativeTextureGetMipLevelCount(
            cSelf);
    }
    uint32_t wgpuTextureGetSampleCount(WGPUTexture cSelf) {
        return NativeTextureGetSampleCount(
            cSelf);
    }
    WGPUTextureViewDimension wgpuTextureGetTextureBindingViewDimension(WGPUTexture cSelf) {
        return NativeTextureGetTextureBindingViewDimension(
            cSelf);
    }
    WGPUTextureUsage wgpuTextureGetUsage(WGPUTexture cSelf) {
        return NativeTextureGetUsage(
            cSelf);
    }
    uint32_t wgpuTextureGetWidth(WGPUTexture cSelf) {
        return NativeTextureGetWidth(
            cSelf);
    }
    void wgpuTexturePin(WGPUTexture cSelf, WGPUTextureUsage usage) {
        return NativeTexturePin(
            cSelf, usage);
    }
    void wgpuTextureSetLabel(WGPUTexture cSelf, WGPUStringView label) {
        return NativeTextureSetLabel(
            cSelf, label);
    }
    void wgpuTextureSetOwnershipForMemoryDump(WGPUTexture cSelf, uint64_t ownerGuid) {
        return NativeTextureSetOwnershipForMemoryDump(
            cSelf, ownerGuid);
    }
    void wgpuTextureUnpin(WGPUTexture cSelf) {
        return NativeTextureUnpin(
            cSelf);
    }
    void wgpuTextureAddRef(WGPUTexture cSelf) {
        return NativeTextureAddRef(
            cSelf);
    }
    void wgpuTextureRelease(WGPUTexture cSelf) {
        return NativeTextureRelease(
            cSelf);
    }
    void wgpuTextureViewSetLabel(WGPUTextureView cSelf, WGPUStringView label) {
        return NativeTextureViewSetLabel(
            cSelf, label);
    }
    void wgpuTextureViewAddRef(WGPUTextureView cSelf) {
        return NativeTextureViewAddRef(
            cSelf);
    }
    void wgpuTextureViewRelease(WGPUTextureView cSelf) {
        return NativeTextureViewRelease(
            cSelf);
    }
}
