
#ifndef BACKEND_VALIDATIONUTILS_H_
#define BACKEND_VALIDATIONUTILS_H_

#include "dawn/webgpu_cpp.h"

#include "dawn/native/Error.h"

namespace dawn::native {

    // Helper functions to check the value of enums and bitmasks
    MaybeError ValidateAdapterType(wgpu::AdapterType value);
    MaybeError ValidateAddressMode(wgpu::AddressMode value);
    MaybeError ValidateAlphaMode(wgpu::AlphaMode value);
    MaybeError ValidateBackendType(wgpu::BackendType value);
    MaybeError ValidateBlendFactor(wgpu::BlendFactor value);
    MaybeError ValidateBlendOperation(wgpu::BlendOperation value);
    MaybeError ValidateBufferBindingType(wgpu::BufferBindingType value);
    MaybeError ValidateBufferMapState(wgpu::BufferMapState value);
    MaybeError ValidateCallbackMode(wgpu::CallbackMode value);
    MaybeError ValidateCompareFunction(wgpu::CompareFunction value);
    MaybeError ValidateCompilationInfoRequestStatus(wgpu::CompilationInfoRequestStatus value);
    MaybeError ValidateCompilationMessageType(wgpu::CompilationMessageType value);
    MaybeError ValidateComponentSwizzle(wgpu::ComponentSwizzle value);
    MaybeError ValidateCompositeAlphaMode(wgpu::CompositeAlphaMode value);
    MaybeError ValidateCreatePipelineAsyncStatus(wgpu::CreatePipelineAsyncStatus value);
    MaybeError ValidateCullMode(wgpu::CullMode value);
    MaybeError ValidateDeviceLostReason(wgpu::DeviceLostReason value);
    MaybeError ValidateErrorFilter(wgpu::ErrorFilter value);
    MaybeError ValidateErrorType(wgpu::ErrorType value);
    MaybeError ValidateExternalTextureRotation(wgpu::ExternalTextureRotation value);
    MaybeError ValidateFeatureLevel(wgpu::FeatureLevel value);
    MaybeError ValidateFeatureName(wgpu::FeatureName value);
    MaybeError ValidateFilterMode(wgpu::FilterMode value);
    MaybeError ValidateFrontFace(wgpu::FrontFace value);
    MaybeError ValidateIndexFormat(wgpu::IndexFormat value);
    MaybeError ValidateInstanceFeatureName(wgpu::InstanceFeatureName value);
    MaybeError ValidateLoadOp(wgpu::LoadOp value);
    MaybeError ValidateLoggingType(wgpu::LoggingType value);
    MaybeError ValidateMapAsyncStatus(wgpu::MapAsyncStatus value);
    MaybeError ValidateMipmapFilterMode(wgpu::MipmapFilterMode value);
    MaybeError ValidateOptionalBool(wgpu::OptionalBool value);
    MaybeError ValidatePopErrorScopeStatus(wgpu::PopErrorScopeStatus value);
    MaybeError ValidatePowerPreference(wgpu::PowerPreference value);
    MaybeError ValidatePredefinedColorSpace(wgpu::PredefinedColorSpace value);
    MaybeError ValidatePresentMode(wgpu::PresentMode value);
    MaybeError ValidatePrimitiveTopology(wgpu::PrimitiveTopology value);
    MaybeError ValidateQueryType(wgpu::QueryType value);
    MaybeError ValidateQueueWorkDoneStatus(wgpu::QueueWorkDoneStatus value);
    MaybeError ValidateRequestAdapterStatus(wgpu::RequestAdapterStatus value);
    MaybeError ValidateRequestDeviceStatus(wgpu::RequestDeviceStatus value);
    MaybeError ValidateSamplerBindingType(wgpu::SamplerBindingType value);
    MaybeError ValidateSharedFenceType(wgpu::SharedFenceType value);
    MaybeError ValidateStatus(wgpu::Status value);
    MaybeError ValidateStencilOperation(wgpu::StencilOperation value);
    MaybeError ValidateStorageTextureAccess(wgpu::StorageTextureAccess value);
    MaybeError ValidateStoreOp(wgpu::StoreOp value);
    MaybeError ValidateSType(wgpu::SType value);
    MaybeError ValidateSubgroupMatrixComponentType(wgpu::SubgroupMatrixComponentType value);
    MaybeError ValidateSurfaceGetCurrentTextureStatus(wgpu::SurfaceGetCurrentTextureStatus value);
    MaybeError ValidateTexelBufferAccess(wgpu::TexelBufferAccess value);
    MaybeError ValidateTextureAspect(wgpu::TextureAspect value);
    MaybeError ValidateTextureDimension(wgpu::TextureDimension value);
    MaybeError ValidateTextureFormat(wgpu::TextureFormat value);
    MaybeError ValidateTextureSampleType(wgpu::TextureSampleType value);
    MaybeError ValidateTextureViewDimension(wgpu::TextureViewDimension value);
    MaybeError ValidateToneMappingMode(wgpu::ToneMappingMode value);
    MaybeError ValidateVertexFormat(wgpu::VertexFormat value);
    MaybeError ValidateVertexStepMode(wgpu::VertexStepMode value);
    MaybeError ValidateWaitStatus(wgpu::WaitStatus value);
    MaybeError ValidateWGSLLanguageFeatureName(wgpu::WGSLLanguageFeatureName value);
    MaybeError ValidateBufferUsage(wgpu::BufferUsage value);
    MaybeError ValidateColorWriteMask(wgpu::ColorWriteMask value);
    MaybeError ValidateHeapProperty(wgpu::HeapProperty value);
    MaybeError ValidateMapMode(wgpu::MapMode value);
    MaybeError ValidateShaderStage(wgpu::ShaderStage value);
    MaybeError ValidateTextureUsage(wgpu::TextureUsage value);

} // namespace dawn::native

#endif  // BACKEND_VALIDATIONUTILS_H_
