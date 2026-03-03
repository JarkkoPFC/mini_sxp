
#include "dawn/native/ValidationUtils_autogen.h"

namespace dawn::native {

    MaybeError ValidateAdapterType(wgpu::AdapterType value) {
        switch (WGPUAdapterType(value)) {
            case WGPUAdapterType_DiscreteGPU:
                return {};
            case WGPUAdapterType_IntegratedGPU:
                return {};
            case WGPUAdapterType_CPU:
                return {};
            case WGPUAdapterType_Unknown:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUAdapterType.", value);
        }
    }

    MaybeError ValidateAddressMode(wgpu::AddressMode value) {
        switch (WGPUAddressMode(value)) {
            case WGPUAddressMode_Undefined:
                return {};
            case WGPUAddressMode_ClampToEdge:
                return {};
            case WGPUAddressMode_Repeat:
                return {};
            case WGPUAddressMode_MirrorRepeat:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUAddressMode.", value);
        }
    }

    MaybeError ValidateAlphaMode(wgpu::AlphaMode value) {
        switch (WGPUAlphaMode(value)) {
            case WGPUAlphaMode_Opaque:
                return {};
            case WGPUAlphaMode_Premultiplied:
                return {};
            case WGPUAlphaMode_Unpremultiplied:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUAlphaMode.", value);
        }
    }

    MaybeError ValidateBackendType(wgpu::BackendType value) {
        switch (WGPUBackendType(value)) {
            case WGPUBackendType_Null:
                return {};
            case WGPUBackendType_WebGPU:
                return {};
            case WGPUBackendType_D3D11:
                return {};
            case WGPUBackendType_D3D12:
                return {};
            case WGPUBackendType_Metal:
                return {};
            case WGPUBackendType_Vulkan:
                return {};
            case WGPUBackendType_OpenGL:
                return {};
            case WGPUBackendType_OpenGLES:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUBackendType.", value);
        }
    }

    MaybeError ValidateBlendFactor(wgpu::BlendFactor value) {
        switch (WGPUBlendFactor(value)) {
            case WGPUBlendFactor_Undefined:
                return {};
            case WGPUBlendFactor_Zero:
                return {};
            case WGPUBlendFactor_One:
                return {};
            case WGPUBlendFactor_Src:
                return {};
            case WGPUBlendFactor_OneMinusSrc:
                return {};
            case WGPUBlendFactor_SrcAlpha:
                return {};
            case WGPUBlendFactor_OneMinusSrcAlpha:
                return {};
            case WGPUBlendFactor_Dst:
                return {};
            case WGPUBlendFactor_OneMinusDst:
                return {};
            case WGPUBlendFactor_DstAlpha:
                return {};
            case WGPUBlendFactor_OneMinusDstAlpha:
                return {};
            case WGPUBlendFactor_SrcAlphaSaturated:
                return {};
            case WGPUBlendFactor_Constant:
                return {};
            case WGPUBlendFactor_OneMinusConstant:
                return {};
            case WGPUBlendFactor_Src1:
                return {};
            case WGPUBlendFactor_OneMinusSrc1:
                return {};
            case WGPUBlendFactor_Src1Alpha:
                return {};
            case WGPUBlendFactor_OneMinusSrc1Alpha:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUBlendFactor.", value);
        }
    }

    MaybeError ValidateBlendOperation(wgpu::BlendOperation value) {
        switch (WGPUBlendOperation(value)) {
            case WGPUBlendOperation_Undefined:
                return {};
            case WGPUBlendOperation_Add:
                return {};
            case WGPUBlendOperation_Subtract:
                return {};
            case WGPUBlendOperation_ReverseSubtract:
                return {};
            case WGPUBlendOperation_Min:
                return {};
            case WGPUBlendOperation_Max:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUBlendOperation.", value);
        }
    }

    MaybeError ValidateBufferBindingType(wgpu::BufferBindingType value) {
        switch (WGPUBufferBindingType(value)) {
            case WGPUBufferBindingType_BindingNotUsed:
                return {};
            case WGPUBufferBindingType_Uniform:
                return {};
            case WGPUBufferBindingType_Storage:
                return {};
            case WGPUBufferBindingType_ReadOnlyStorage:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUBufferBindingType.", value);
        }
    }

    MaybeError ValidateBufferMapState(wgpu::BufferMapState value) {
        switch (WGPUBufferMapState(value)) {
            case WGPUBufferMapState_Unmapped:
                return {};
            case WGPUBufferMapState_Pending:
                return {};
            case WGPUBufferMapState_Mapped:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUBufferMapState.", value);
        }
    }

    MaybeError ValidateCallbackMode(wgpu::CallbackMode value) {
        switch (WGPUCallbackMode(value)) {
            case WGPUCallbackMode_WaitAnyOnly:
                return {};
            case WGPUCallbackMode_AllowProcessEvents:
                return {};
            case WGPUCallbackMode_AllowSpontaneous:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUCallbackMode.", value);
        }
    }

    MaybeError ValidateCompareFunction(wgpu::CompareFunction value) {
        switch (WGPUCompareFunction(value)) {
            case WGPUCompareFunction_Undefined:
                return {};
            case WGPUCompareFunction_Never:
                return {};
            case WGPUCompareFunction_Less:
                return {};
            case WGPUCompareFunction_Equal:
                return {};
            case WGPUCompareFunction_LessEqual:
                return {};
            case WGPUCompareFunction_Greater:
                return {};
            case WGPUCompareFunction_NotEqual:
                return {};
            case WGPUCompareFunction_GreaterEqual:
                return {};
            case WGPUCompareFunction_Always:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUCompareFunction.", value);
        }
    }

    MaybeError ValidateCompilationInfoRequestStatus(wgpu::CompilationInfoRequestStatus value) {
        switch (WGPUCompilationInfoRequestStatus(value)) {
            case WGPUCompilationInfoRequestStatus_Success:
                return {};
            case WGPUCompilationInfoRequestStatus_CallbackCancelled:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUCompilationInfoRequestStatus.", value);
        }
    }

    MaybeError ValidateCompilationMessageType(wgpu::CompilationMessageType value) {
        switch (WGPUCompilationMessageType(value)) {
            case WGPUCompilationMessageType_Error:
                return {};
            case WGPUCompilationMessageType_Warning:
                return {};
            case WGPUCompilationMessageType_Info:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUCompilationMessageType.", value);
        }
    }

    MaybeError ValidateComponentSwizzle(wgpu::ComponentSwizzle value) {
        switch (WGPUComponentSwizzle(value)) {
            case WGPUComponentSwizzle_Undefined:
                return {};
            case WGPUComponentSwizzle_Zero:
                return {};
            case WGPUComponentSwizzle_One:
                return {};
            case WGPUComponentSwizzle_R:
                return {};
            case WGPUComponentSwizzle_G:
                return {};
            case WGPUComponentSwizzle_B:
                return {};
            case WGPUComponentSwizzle_A:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUComponentSwizzle.", value);
        }
    }

    MaybeError ValidateCompositeAlphaMode(wgpu::CompositeAlphaMode value) {
        switch (WGPUCompositeAlphaMode(value)) {
            case WGPUCompositeAlphaMode_Auto:
                return {};
            case WGPUCompositeAlphaMode_Opaque:
                return {};
            case WGPUCompositeAlphaMode_Premultiplied:
                return {};
            case WGPUCompositeAlphaMode_Unpremultiplied:
                return {};
            case WGPUCompositeAlphaMode_Inherit:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUCompositeAlphaMode.", value);
        }
    }

    MaybeError ValidateCreatePipelineAsyncStatus(wgpu::CreatePipelineAsyncStatus value) {
        switch (WGPUCreatePipelineAsyncStatus(value)) {
            case WGPUCreatePipelineAsyncStatus_Success:
                return {};
            case WGPUCreatePipelineAsyncStatus_CallbackCancelled:
                return {};
            case WGPUCreatePipelineAsyncStatus_ValidationError:
                return {};
            case WGPUCreatePipelineAsyncStatus_InternalError:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUCreatePipelineAsyncStatus.", value);
        }
    }

    MaybeError ValidateCullMode(wgpu::CullMode value) {
        switch (WGPUCullMode(value)) {
            case WGPUCullMode_Undefined:
                return {};
            case WGPUCullMode_None:
                return {};
            case WGPUCullMode_Front:
                return {};
            case WGPUCullMode_Back:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUCullMode.", value);
        }
    }

    MaybeError ValidateDeviceLostReason(wgpu::DeviceLostReason value) {
        switch (WGPUDeviceLostReason(value)) {
            case WGPUDeviceLostReason_Unknown:
                return {};
            case WGPUDeviceLostReason_Destroyed:
                return {};
            case WGPUDeviceLostReason_CallbackCancelled:
                return {};
            case WGPUDeviceLostReason_FailedCreation:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUDeviceLostReason.", value);
        }
    }

    MaybeError ValidateErrorFilter(wgpu::ErrorFilter value) {
        switch (WGPUErrorFilter(value)) {
            case WGPUErrorFilter_Validation:
                return {};
            case WGPUErrorFilter_OutOfMemory:
                return {};
            case WGPUErrorFilter_Internal:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUErrorFilter.", value);
        }
    }

    MaybeError ValidateErrorType(wgpu::ErrorType value) {
        switch (WGPUErrorType(value)) {
            case WGPUErrorType_NoError:
                return {};
            case WGPUErrorType_Validation:
                return {};
            case WGPUErrorType_OutOfMemory:
                return {};
            case WGPUErrorType_Internal:
                return {};
            case WGPUErrorType_Unknown:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUErrorType.", value);
        }
    }

    MaybeError ValidateExternalTextureRotation(wgpu::ExternalTextureRotation value) {
        switch (WGPUExternalTextureRotation(value)) {
            case WGPUExternalTextureRotation_Rotate0Degrees:
                return {};
            case WGPUExternalTextureRotation_Rotate90Degrees:
                return {};
            case WGPUExternalTextureRotation_Rotate180Degrees:
                return {};
            case WGPUExternalTextureRotation_Rotate270Degrees:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUExternalTextureRotation.", value);
        }
    }

    MaybeError ValidateFeatureLevel(wgpu::FeatureLevel value) {
        switch (WGPUFeatureLevel(value)) {
            case WGPUFeatureLevel_Undefined:
                return {};
            case WGPUFeatureLevel_Compatibility:
                return {};
            case WGPUFeatureLevel_Core:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUFeatureLevel.", value);
        }
    }

    MaybeError ValidateFeatureName(wgpu::FeatureName value) {
        switch (WGPUFeatureName(value)) {
            case WGPUFeatureName_CoreFeaturesAndLimits:
                return {};
            case WGPUFeatureName_DepthClipControl:
                return {};
            case WGPUFeatureName_Depth32FloatStencil8:
                return {};
            case WGPUFeatureName_TextureCompressionBC:
                return {};
            case WGPUFeatureName_TextureCompressionBCSliced3D:
                return {};
            case WGPUFeatureName_TextureCompressionETC2:
                return {};
            case WGPUFeatureName_TextureCompressionASTC:
                return {};
            case WGPUFeatureName_TextureCompressionASTCSliced3D:
                return {};
            case WGPUFeatureName_TimestampQuery:
                return {};
            case WGPUFeatureName_IndirectFirstInstance:
                return {};
            case WGPUFeatureName_ShaderF16:
                return {};
            case WGPUFeatureName_RG11B10UfloatRenderable:
                return {};
            case WGPUFeatureName_BGRA8UnormStorage:
                return {};
            case WGPUFeatureName_Float32Filterable:
                return {};
            case WGPUFeatureName_Float32Blendable:
                return {};
            case WGPUFeatureName_ClipDistances:
                return {};
            case WGPUFeatureName_DualSourceBlending:
                return {};
            case WGPUFeatureName_Subgroups:
                return {};
            case WGPUFeatureName_TextureFormatsTier1:
                return {};
            case WGPUFeatureName_TextureFormatsTier2:
                return {};
            case WGPUFeatureName_PrimitiveIndex:
                return {};
            case WGPUFeatureName_TextureComponentSwizzle:
                return {};
            case WGPUFeatureName_DawnInternalUsages:
                return {};
            case WGPUFeatureName_DawnMultiPlanarFormats:
                return {};
            case WGPUFeatureName_DawnNative:
                return {};
            case WGPUFeatureName_ChromiumExperimentalTimestampQueryInsidePasses:
                return {};
            case WGPUFeatureName_ImplicitDeviceSynchronization:
                return {};
            case WGPUFeatureName_TransientAttachments:
                return {};
            case WGPUFeatureName_MSAARenderToSingleSampled:
                return {};
            case WGPUFeatureName_D3D11MultithreadProtected:
                return {};
            case WGPUFeatureName_ANGLETextureSharing:
                return {};
            case WGPUFeatureName_PixelLocalStorageCoherent:
                return {};
            case WGPUFeatureName_PixelLocalStorageNonCoherent:
                return {};
            case WGPUFeatureName_Unorm16TextureFormats:
                return {};
            case WGPUFeatureName_MultiPlanarFormatExtendedUsages:
                return {};
            case WGPUFeatureName_MultiPlanarFormatP010:
                return {};
            case WGPUFeatureName_HostMappedPointer:
                return {};
            case WGPUFeatureName_MultiPlanarRenderTargets:
                return {};
            case WGPUFeatureName_MultiPlanarFormatNv12a:
                return {};
            case WGPUFeatureName_FramebufferFetch:
                return {};
            case WGPUFeatureName_BufferMapExtendedUsages:
                return {};
            case WGPUFeatureName_AdapterPropertiesMemoryHeaps:
                return {};
            case WGPUFeatureName_AdapterPropertiesD3D:
                return {};
            case WGPUFeatureName_AdapterPropertiesVk:
                return {};
            case WGPUFeatureName_DawnFormatCapabilities:
                return {};
            case WGPUFeatureName_DawnDrmFormatCapabilities:
                return {};
            case WGPUFeatureName_MultiPlanarFormatNv16:
                return {};
            case WGPUFeatureName_MultiPlanarFormatNv24:
                return {};
            case WGPUFeatureName_MultiPlanarFormatP210:
                return {};
            case WGPUFeatureName_MultiPlanarFormatP410:
                return {};
            case WGPUFeatureName_SharedTextureMemoryVkDedicatedAllocation:
                return {};
            case WGPUFeatureName_SharedTextureMemoryAHardwareBuffer:
                return {};
            case WGPUFeatureName_SharedTextureMemoryDmaBuf:
                return {};
            case WGPUFeatureName_SharedTextureMemoryOpaqueFD:
                return {};
            case WGPUFeatureName_SharedTextureMemoryZirconHandle:
                return {};
            case WGPUFeatureName_SharedTextureMemoryDXGISharedHandle:
                return {};
            case WGPUFeatureName_SharedTextureMemoryD3D11Texture2D:
                return {};
            case WGPUFeatureName_SharedTextureMemoryIOSurface:
                return {};
            case WGPUFeatureName_SharedTextureMemoryEGLImage:
                return {};
            case WGPUFeatureName_SharedFenceVkSemaphoreOpaqueFD:
                return {};
            case WGPUFeatureName_SharedFenceSyncFD:
                return {};
            case WGPUFeatureName_SharedFenceVkSemaphoreZirconHandle:
                return {};
            case WGPUFeatureName_SharedFenceDXGISharedHandle:
                return {};
            case WGPUFeatureName_SharedFenceMTLSharedEvent:
                return {};
            case WGPUFeatureName_SharedBufferMemoryD3D12Resource:
                return {};
            case WGPUFeatureName_StaticSamplers:
                return {};
            case WGPUFeatureName_YCbCrVulkanSamplers:
                return {};
            case WGPUFeatureName_ShaderModuleCompilationOptions:
                return {};
            case WGPUFeatureName_DawnLoadResolveTexture:
                return {};
            case WGPUFeatureName_DawnPartialLoadResolveTexture:
                return {};
            case WGPUFeatureName_MultiDrawIndirect:
                return {};
            case WGPUFeatureName_DawnTexelCopyBufferRowAlignment:
                return {};
            case WGPUFeatureName_FlexibleTextureViews:
                return {};
            case WGPUFeatureName_ChromiumExperimentalSubgroupMatrix:
                return {};
            case WGPUFeatureName_SharedFenceEGLSync:
                return {};
            case WGPUFeatureName_DawnDeviceAllocatorControl:
                return {};
            case WGPUFeatureName_AdapterPropertiesWGPU:
                return {};
            case WGPUFeatureName_SharedBufferMemoryD3D12SharedMemoryFileMappingHandle:
                return {};
            case WGPUFeatureName_SharedTextureMemoryD3D12Resource:
                return {};
            case WGPUFeatureName_ChromiumExperimentalSamplingResourceTable:
                return {};
            case WGPUFeatureName_ChromiumExperimentalSubgroupSizeControl:
                return {};
            case WGPUFeatureName_AtomicVec2uMinMax:
                return {};
            case WGPUFeatureName_Unorm16FormatsForExternalTexture:
                return {};
            case WGPUFeatureName_OpaqueYCbCrAndroidForExternalTexture:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUFeatureName.", value);
        }
    }

    MaybeError ValidateFilterMode(wgpu::FilterMode value) {
        switch (WGPUFilterMode(value)) {
            case WGPUFilterMode_Undefined:
                return {};
            case WGPUFilterMode_Nearest:
                return {};
            case WGPUFilterMode_Linear:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUFilterMode.", value);
        }
    }

    MaybeError ValidateFrontFace(wgpu::FrontFace value) {
        switch (WGPUFrontFace(value)) {
            case WGPUFrontFace_Undefined:
                return {};
            case WGPUFrontFace_CCW:
                return {};
            case WGPUFrontFace_CW:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUFrontFace.", value);
        }
    }

    MaybeError ValidateIndexFormat(wgpu::IndexFormat value) {
        switch (WGPUIndexFormat(value)) {
            case WGPUIndexFormat_Undefined:
                return {};
            case WGPUIndexFormat_Uint16:
                return {};
            case WGPUIndexFormat_Uint32:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUIndexFormat.", value);
        }
    }

    MaybeError ValidateInstanceFeatureName(wgpu::InstanceFeatureName value) {
        switch (WGPUInstanceFeatureName(value)) {
            case WGPUInstanceFeatureName_TimedWaitAny:
                return {};
            case WGPUInstanceFeatureName_ShaderSourceSPIRV:
                return {};
            case WGPUInstanceFeatureName_MultipleDevicesPerAdapter:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUInstanceFeatureName.", value);
        }
    }

    MaybeError ValidateLoadOp(wgpu::LoadOp value) {
        switch (WGPULoadOp(value)) {
            case WGPULoadOp_Undefined:
                return {};
            case WGPULoadOp_Load:
                return {};
            case WGPULoadOp_Clear:
                return {};
            case WGPULoadOp_ExpandResolveTexture:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPULoadOp.", value);
        }
    }

    MaybeError ValidateLoggingType(wgpu::LoggingType value) {
        switch (WGPULoggingType(value)) {
            case WGPULoggingType_Verbose:
                return {};
            case WGPULoggingType_Info:
                return {};
            case WGPULoggingType_Warning:
                return {};
            case WGPULoggingType_Error:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPULoggingType.", value);
        }
    }

    MaybeError ValidateMapAsyncStatus(wgpu::MapAsyncStatus value) {
        switch (WGPUMapAsyncStatus(value)) {
            case WGPUMapAsyncStatus_Success:
                return {};
            case WGPUMapAsyncStatus_CallbackCancelled:
                return {};
            case WGPUMapAsyncStatus_Error:
                return {};
            case WGPUMapAsyncStatus_Aborted:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUMapAsyncStatus.", value);
        }
    }

    MaybeError ValidateMipmapFilterMode(wgpu::MipmapFilterMode value) {
        switch (WGPUMipmapFilterMode(value)) {
            case WGPUMipmapFilterMode_Undefined:
                return {};
            case WGPUMipmapFilterMode_Nearest:
                return {};
            case WGPUMipmapFilterMode_Linear:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUMipmapFilterMode.", value);
        }
    }

    MaybeError ValidateOptionalBool(wgpu::OptionalBool value) {
        switch (WGPUOptionalBool(value)) {
            case WGPUOptionalBool_False:
                return {};
            case WGPUOptionalBool_True:
                return {};
            case WGPUOptionalBool_Undefined:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUOptionalBool.", value);
        }
    }

    MaybeError ValidatePopErrorScopeStatus(wgpu::PopErrorScopeStatus value) {
        switch (WGPUPopErrorScopeStatus(value)) {
            case WGPUPopErrorScopeStatus_Success:
                return {};
            case WGPUPopErrorScopeStatus_CallbackCancelled:
                return {};
            case WGPUPopErrorScopeStatus_Error:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUPopErrorScopeStatus.", value);
        }
    }

    MaybeError ValidatePowerPreference(wgpu::PowerPreference value) {
        switch (WGPUPowerPreference(value)) {
            case WGPUPowerPreference_Undefined:
                return {};
            case WGPUPowerPreference_LowPower:
                return {};
            case WGPUPowerPreference_HighPerformance:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUPowerPreference.", value);
        }
    }

    MaybeError ValidatePredefinedColorSpace(wgpu::PredefinedColorSpace value) {
        switch (WGPUPredefinedColorSpace(value)) {
            case WGPUPredefinedColorSpace_SRGB:
                return {};
            case WGPUPredefinedColorSpace_DisplayP3:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUPredefinedColorSpace.", value);
        }
    }

    MaybeError ValidatePresentMode(wgpu::PresentMode value) {
        switch (WGPUPresentMode(value)) {
            case WGPUPresentMode_Undefined:
                return {};
            case WGPUPresentMode_Fifo:
                return {};
            case WGPUPresentMode_FifoRelaxed:
                return {};
            case WGPUPresentMode_Immediate:
                return {};
            case WGPUPresentMode_Mailbox:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUPresentMode.", value);
        }
    }

    MaybeError ValidatePrimitiveTopology(wgpu::PrimitiveTopology value) {
        switch (WGPUPrimitiveTopology(value)) {
            case WGPUPrimitiveTopology_Undefined:
                return {};
            case WGPUPrimitiveTopology_PointList:
                return {};
            case WGPUPrimitiveTopology_LineList:
                return {};
            case WGPUPrimitiveTopology_LineStrip:
                return {};
            case WGPUPrimitiveTopology_TriangleList:
                return {};
            case WGPUPrimitiveTopology_TriangleStrip:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUPrimitiveTopology.", value);
        }
    }

    MaybeError ValidateQueryType(wgpu::QueryType value) {
        switch (WGPUQueryType(value)) {
            case WGPUQueryType_Occlusion:
                return {};
            case WGPUQueryType_Timestamp:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUQueryType.", value);
        }
    }

    MaybeError ValidateQueueWorkDoneStatus(wgpu::QueueWorkDoneStatus value) {
        switch (WGPUQueueWorkDoneStatus(value)) {
            case WGPUQueueWorkDoneStatus_Success:
                return {};
            case WGPUQueueWorkDoneStatus_CallbackCancelled:
                return {};
            case WGPUQueueWorkDoneStatus_Error:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUQueueWorkDoneStatus.", value);
        }
    }

    MaybeError ValidateRequestAdapterStatus(wgpu::RequestAdapterStatus value) {
        switch (WGPURequestAdapterStatus(value)) {
            case WGPURequestAdapterStatus_Success:
                return {};
            case WGPURequestAdapterStatus_CallbackCancelled:
                return {};
            case WGPURequestAdapterStatus_Unavailable:
                return {};
            case WGPURequestAdapterStatus_Error:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPURequestAdapterStatus.", value);
        }
    }

    MaybeError ValidateRequestDeviceStatus(wgpu::RequestDeviceStatus value) {
        switch (WGPURequestDeviceStatus(value)) {
            case WGPURequestDeviceStatus_Success:
                return {};
            case WGPURequestDeviceStatus_CallbackCancelled:
                return {};
            case WGPURequestDeviceStatus_Error:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPURequestDeviceStatus.", value);
        }
    }

    MaybeError ValidateSamplerBindingType(wgpu::SamplerBindingType value) {
        switch (WGPUSamplerBindingType(value)) {
            case WGPUSamplerBindingType_BindingNotUsed:
                return {};
            case WGPUSamplerBindingType_Filtering:
                return {};
            case WGPUSamplerBindingType_NonFiltering:
                return {};
            case WGPUSamplerBindingType_Comparison:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUSamplerBindingType.", value);
        }
    }

    MaybeError ValidateSharedFenceType(wgpu::SharedFenceType value) {
        switch (WGPUSharedFenceType(value)) {
            case WGPUSharedFenceType_VkSemaphoreOpaqueFD:
                return {};
            case WGPUSharedFenceType_SyncFD:
                return {};
            case WGPUSharedFenceType_VkSemaphoreZirconHandle:
                return {};
            case WGPUSharedFenceType_DXGISharedHandle:
                return {};
            case WGPUSharedFenceType_MTLSharedEvent:
                return {};
            case WGPUSharedFenceType_EGLSync:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUSharedFenceType.", value);
        }
    }

    MaybeError ValidateStatus(wgpu::Status value) {
        switch (WGPUStatus(value)) {
            case WGPUStatus_Success:
                return {};
            case WGPUStatus_Error:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUStatus.", value);
        }
    }

    MaybeError ValidateStencilOperation(wgpu::StencilOperation value) {
        switch (WGPUStencilOperation(value)) {
            case WGPUStencilOperation_Undefined:
                return {};
            case WGPUStencilOperation_Keep:
                return {};
            case WGPUStencilOperation_Zero:
                return {};
            case WGPUStencilOperation_Replace:
                return {};
            case WGPUStencilOperation_Invert:
                return {};
            case WGPUStencilOperation_IncrementClamp:
                return {};
            case WGPUStencilOperation_DecrementClamp:
                return {};
            case WGPUStencilOperation_IncrementWrap:
                return {};
            case WGPUStencilOperation_DecrementWrap:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUStencilOperation.", value);
        }
    }

    MaybeError ValidateStorageTextureAccess(wgpu::StorageTextureAccess value) {
        switch (WGPUStorageTextureAccess(value)) {
            case WGPUStorageTextureAccess_BindingNotUsed:
                return {};
            case WGPUStorageTextureAccess_WriteOnly:
                return {};
            case WGPUStorageTextureAccess_ReadOnly:
                return {};
            case WGPUStorageTextureAccess_ReadWrite:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUStorageTextureAccess.", value);
        }
    }

    MaybeError ValidateStoreOp(wgpu::StoreOp value) {
        switch (WGPUStoreOp(value)) {
            case WGPUStoreOp_Undefined:
                return {};
            case WGPUStoreOp_Store:
                return {};
            case WGPUStoreOp_Discard:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUStoreOp.", value);
        }
    }

    MaybeError ValidateSType(wgpu::SType value) {
        switch (WGPUSType(value)) {
            case WGPUSType_ShaderSourceSPIRV:
                return {};
            case WGPUSType_ShaderSourceWGSL:
                return {};
            case WGPUSType_RenderPassMaxDrawCount:
                return {};
            case WGPUSType_SurfaceSourceMetalLayer:
                return {};
            case WGPUSType_SurfaceSourceWindowsHWND:
                return {};
            case WGPUSType_SurfaceSourceXlibWindow:
                return {};
            case WGPUSType_SurfaceSourceWaylandSurface:
                return {};
            case WGPUSType_SurfaceSourceAndroidNativeWindow:
                return {};
            case WGPUSType_SurfaceSourceXCBWindow:
                return {};
            case WGPUSType_SurfaceColorManagement:
                return {};
            case WGPUSType_RequestAdapterWebXROptions:
                return {};
            case WGPUSType_TextureComponentSwizzleDescriptor:
                return {};
            case WGPUSType_CompatibilityModeLimits:
                return {};
            case WGPUSType_TextureBindingViewDimensionDescriptor:
                return {};
            case WGPUSType_SurfaceDescriptorFromWindowsCoreWindow:
                return {};
            case WGPUSType_ExternalTextureBindingEntry:
                return {};
            case WGPUSType_ExternalTextureBindingLayout:
                return {};
            case WGPUSType_SurfaceDescriptorFromWindowsUWPSwapChainPanel:
                return {};
            case WGPUSType_DawnTextureInternalUsageDescriptor:
                return {};
            case WGPUSType_DawnEncoderInternalUsageDescriptor:
                return {};
            case WGPUSType_DawnInstanceDescriptor:
                return {};
            case WGPUSType_DawnCacheDeviceDescriptor:
                return {};
            case WGPUSType_DawnAdapterPropertiesPowerPreference:
                return {};
            case WGPUSType_DawnBufferDescriptorErrorInfoFromWireClient:
                return {};
            case WGPUSType_DawnTogglesDescriptor:
                return {};
            case WGPUSType_DawnShaderModuleSPIRVOptionsDescriptor:
                return {};
            case WGPUSType_RequestAdapterOptionsLUID:
                return {};
            case WGPUSType_RequestAdapterOptionsGetGLProc:
                return {};
            case WGPUSType_RequestAdapterOptionsD3D11Device:
                return {};
            case WGPUSType_DawnRenderPassSampleCount:
                return {};
            case WGPUSType_RenderPassPixelLocalStorage:
                return {};
            case WGPUSType_PipelineLayoutPixelLocalStorage:
                return {};
            case WGPUSType_BufferHostMappedPointer:
                return {};
            case WGPUSType_AdapterPropertiesMemoryHeaps:
                return {};
            case WGPUSType_AdapterPropertiesD3D:
                return {};
            case WGPUSType_AdapterPropertiesVk:
                return {};
            case WGPUSType_DawnWireWGSLControl:
                return {};
            case WGPUSType_DawnWGSLBlocklist:
                return {};
            case WGPUSType_DawnDrmFormatCapabilities:
                return {};
            case WGPUSType_ShaderModuleCompilationOptions:
                return {};
            case WGPUSType_ColorTargetStateExpandResolveTextureDawn:
                return {};
            case WGPUSType_RenderPassDescriptorExpandResolveRect:
                return {};
            case WGPUSType_SharedTextureMemoryVkDedicatedAllocationDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryAHardwareBufferDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryDmaBufDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryOpaqueFDDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryZirconHandleDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryDXGISharedHandleDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryD3D11Texture2DDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryIOSurfaceDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryEGLImageDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryInitializedBeginState:
                return {};
            case WGPUSType_SharedTextureMemoryInitializedEndState:
                return {};
            case WGPUSType_SharedTextureMemoryVkImageLayoutBeginState:
                return {};
            case WGPUSType_SharedTextureMemoryVkImageLayoutEndState:
                return {};
            case WGPUSType_SharedTextureMemoryD3DSwapchainBeginState:
                return {};
            case WGPUSType_SharedFenceVkSemaphoreOpaqueFDDescriptor:
                return {};
            case WGPUSType_SharedFenceVkSemaphoreOpaqueFDExportInfo:
                return {};
            case WGPUSType_SharedFenceSyncFDDescriptor:
                return {};
            case WGPUSType_SharedFenceSyncFDExportInfo:
                return {};
            case WGPUSType_SharedFenceVkSemaphoreZirconHandleDescriptor:
                return {};
            case WGPUSType_SharedFenceVkSemaphoreZirconHandleExportInfo:
                return {};
            case WGPUSType_SharedFenceDXGISharedHandleDescriptor:
                return {};
            case WGPUSType_SharedFenceDXGISharedHandleExportInfo:
                return {};
            case WGPUSType_SharedFenceMTLSharedEventDescriptor:
                return {};
            case WGPUSType_SharedFenceMTLSharedEventExportInfo:
                return {};
            case WGPUSType_SharedBufferMemoryD3D12ResourceDescriptor:
                return {};
            case WGPUSType_StaticSamplerBindingLayout:
                return {};
            case WGPUSType_YCbCrVkDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryAHardwareBufferProperties:
                return {};
            case WGPUSType_AHardwareBufferProperties:
                return {};
            case WGPUSType_DawnTexelCopyBufferRowAlignmentLimits:
                return {};
            case WGPUSType_AdapterPropertiesSubgroupMatrixConfigs:
                return {};
            case WGPUSType_SharedFenceEGLSyncDescriptor:
                return {};
            case WGPUSType_SharedFenceEGLSyncExportInfo:
                return {};
            case WGPUSType_DawnInjectedInvalidSType:
                return {};
            case WGPUSType_DawnCompilationMessageUtf16:
                return {};
            case WGPUSType_DawnFakeBufferOOMForTesting:
                return {};
            case WGPUSType_SurfaceDescriptorFromWindowsWinUISwapChainPanel:
                return {};
            case WGPUSType_DawnDeviceAllocatorControl:
                return {};
            case WGPUSType_DawnHostMappedPointerLimits:
                return {};
            case WGPUSType_RenderPassDescriptorResolveRect:
                return {};
            case WGPUSType_RequestAdapterWebGPUBackendOptions:
                return {};
            case WGPUSType_DawnFakeDeviceInitializeErrorForTesting:
                return {};
            case WGPUSType_SharedTextureMemoryD3D11BeginState:
                return {};
            case WGPUSType_DawnConsumeAdapterDescriptor:
                return {};
            case WGPUSType_TexelBufferBindingEntry:
                return {};
            case WGPUSType_TexelBufferBindingLayout:
                return {};
            case WGPUSType_SharedTextureMemoryMetalEndAccessState:
                return {};
            case WGPUSType_AdapterPropertiesWGPU:
                return {};
            case WGPUSType_SharedBufferMemoryD3D12SharedMemoryFileMappingHandleDescriptor:
                return {};
            case WGPUSType_SharedTextureMemoryD3D12ResourceDescriptor:
                return {};
            case WGPUSType_RequestAdapterOptionsAngleVirtualizationGroup:
                return {};
            case WGPUSType_PipelineLayoutResourceTable:
                return {};
            case WGPUSType_AdapterPropertiesExplicitComputeSubgroupSizeConfigs:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUSType.", value);
        }
    }

    MaybeError ValidateSubgroupMatrixComponentType(wgpu::SubgroupMatrixComponentType value) {
        switch (WGPUSubgroupMatrixComponentType(value)) {
            case WGPUSubgroupMatrixComponentType_F32:
                return {};
            case WGPUSubgroupMatrixComponentType_F16:
                return {};
            case WGPUSubgroupMatrixComponentType_U32:
                return {};
            case WGPUSubgroupMatrixComponentType_I32:
                return {};
            case WGPUSubgroupMatrixComponentType_U8:
                return {};
            case WGPUSubgroupMatrixComponentType_I8:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUSubgroupMatrixComponentType.", value);
        }
    }

    MaybeError ValidateSurfaceGetCurrentTextureStatus(wgpu::SurfaceGetCurrentTextureStatus value) {
        switch (WGPUSurfaceGetCurrentTextureStatus(value)) {
            case WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal:
                return {};
            case WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal:
                return {};
            case WGPUSurfaceGetCurrentTextureStatus_Timeout:
                return {};
            case WGPUSurfaceGetCurrentTextureStatus_Outdated:
                return {};
            case WGPUSurfaceGetCurrentTextureStatus_Lost:
                return {};
            case WGPUSurfaceGetCurrentTextureStatus_Error:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUSurfaceGetCurrentTextureStatus.", value);
        }
    }

    MaybeError ValidateTexelBufferAccess(wgpu::TexelBufferAccess value) {
        switch (WGPUTexelBufferAccess(value)) {
            case WGPUTexelBufferAccess_ReadOnly:
                return {};
            case WGPUTexelBufferAccess_ReadWrite:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUTexelBufferAccess.", value);
        }
    }

    MaybeError ValidateTextureAspect(wgpu::TextureAspect value) {
        switch (WGPUTextureAspect(value)) {
            case WGPUTextureAspect_Undefined:
                return {};
            case WGPUTextureAspect_All:
                return {};
            case WGPUTextureAspect_StencilOnly:
                return {};
            case WGPUTextureAspect_DepthOnly:
                return {};
            case WGPUTextureAspect_Plane0Only:
                return {};
            case WGPUTextureAspect_Plane1Only:
                return {};
            case WGPUTextureAspect_Plane2Only:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUTextureAspect.", value);
        }
    }

    MaybeError ValidateTextureDimension(wgpu::TextureDimension value) {
        switch (WGPUTextureDimension(value)) {
            case WGPUTextureDimension_Undefined:
                return {};
            case WGPUTextureDimension_1D:
                return {};
            case WGPUTextureDimension_2D:
                return {};
            case WGPUTextureDimension_3D:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUTextureDimension.", value);
        }
    }

    MaybeError ValidateTextureFormat(wgpu::TextureFormat value) {
        switch (WGPUTextureFormat(value)) {
            case WGPUTextureFormat_R8Unorm:
                return {};
            case WGPUTextureFormat_R8Snorm:
                return {};
            case WGPUTextureFormat_R8Uint:
                return {};
            case WGPUTextureFormat_R8Sint:
                return {};
            case WGPUTextureFormat_R16Unorm:
                return {};
            case WGPUTextureFormat_R16Snorm:
                return {};
            case WGPUTextureFormat_R16Uint:
                return {};
            case WGPUTextureFormat_R16Sint:
                return {};
            case WGPUTextureFormat_R16Float:
                return {};
            case WGPUTextureFormat_RG8Unorm:
                return {};
            case WGPUTextureFormat_RG8Snorm:
                return {};
            case WGPUTextureFormat_RG8Uint:
                return {};
            case WGPUTextureFormat_RG8Sint:
                return {};
            case WGPUTextureFormat_R32Float:
                return {};
            case WGPUTextureFormat_R32Uint:
                return {};
            case WGPUTextureFormat_R32Sint:
                return {};
            case WGPUTextureFormat_RG16Unorm:
                return {};
            case WGPUTextureFormat_RG16Snorm:
                return {};
            case WGPUTextureFormat_RG16Uint:
                return {};
            case WGPUTextureFormat_RG16Sint:
                return {};
            case WGPUTextureFormat_RG16Float:
                return {};
            case WGPUTextureFormat_RGBA8Unorm:
                return {};
            case WGPUTextureFormat_RGBA8UnormSrgb:
                return {};
            case WGPUTextureFormat_RGBA8Snorm:
                return {};
            case WGPUTextureFormat_RGBA8Uint:
                return {};
            case WGPUTextureFormat_RGBA8Sint:
                return {};
            case WGPUTextureFormat_BGRA8Unorm:
                return {};
            case WGPUTextureFormat_BGRA8UnormSrgb:
                return {};
            case WGPUTextureFormat_RGB10A2Uint:
                return {};
            case WGPUTextureFormat_RGB10A2Unorm:
                return {};
            case WGPUTextureFormat_RG11B10Ufloat:
                return {};
            case WGPUTextureFormat_RGB9E5Ufloat:
                return {};
            case WGPUTextureFormat_RG32Float:
                return {};
            case WGPUTextureFormat_RG32Uint:
                return {};
            case WGPUTextureFormat_RG32Sint:
                return {};
            case WGPUTextureFormat_RGBA16Unorm:
                return {};
            case WGPUTextureFormat_RGBA16Snorm:
                return {};
            case WGPUTextureFormat_RGBA16Uint:
                return {};
            case WGPUTextureFormat_RGBA16Sint:
                return {};
            case WGPUTextureFormat_RGBA16Float:
                return {};
            case WGPUTextureFormat_RGBA32Float:
                return {};
            case WGPUTextureFormat_RGBA32Uint:
                return {};
            case WGPUTextureFormat_RGBA32Sint:
                return {};
            case WGPUTextureFormat_Stencil8:
                return {};
            case WGPUTextureFormat_Depth16Unorm:
                return {};
            case WGPUTextureFormat_Depth24Plus:
                return {};
            case WGPUTextureFormat_Depth24PlusStencil8:
                return {};
            case WGPUTextureFormat_Depth32Float:
                return {};
            case WGPUTextureFormat_Depth32FloatStencil8:
                return {};
            case WGPUTextureFormat_BC1RGBAUnorm:
                return {};
            case WGPUTextureFormat_BC1RGBAUnormSrgb:
                return {};
            case WGPUTextureFormat_BC2RGBAUnorm:
                return {};
            case WGPUTextureFormat_BC2RGBAUnormSrgb:
                return {};
            case WGPUTextureFormat_BC3RGBAUnorm:
                return {};
            case WGPUTextureFormat_BC3RGBAUnormSrgb:
                return {};
            case WGPUTextureFormat_BC4RUnorm:
                return {};
            case WGPUTextureFormat_BC4RSnorm:
                return {};
            case WGPUTextureFormat_BC5RGUnorm:
                return {};
            case WGPUTextureFormat_BC5RGSnorm:
                return {};
            case WGPUTextureFormat_BC6HRGBUfloat:
                return {};
            case WGPUTextureFormat_BC6HRGBFloat:
                return {};
            case WGPUTextureFormat_BC7RGBAUnorm:
                return {};
            case WGPUTextureFormat_BC7RGBAUnormSrgb:
                return {};
            case WGPUTextureFormat_ETC2RGB8Unorm:
                return {};
            case WGPUTextureFormat_ETC2RGB8UnormSrgb:
                return {};
            case WGPUTextureFormat_ETC2RGB8A1Unorm:
                return {};
            case WGPUTextureFormat_ETC2RGB8A1UnormSrgb:
                return {};
            case WGPUTextureFormat_ETC2RGBA8Unorm:
                return {};
            case WGPUTextureFormat_ETC2RGBA8UnormSrgb:
                return {};
            case WGPUTextureFormat_EACR11Unorm:
                return {};
            case WGPUTextureFormat_EACR11Snorm:
                return {};
            case WGPUTextureFormat_EACRG11Unorm:
                return {};
            case WGPUTextureFormat_EACRG11Snorm:
                return {};
            case WGPUTextureFormat_ASTC4x4Unorm:
                return {};
            case WGPUTextureFormat_ASTC4x4UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC5x4Unorm:
                return {};
            case WGPUTextureFormat_ASTC5x4UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC5x5Unorm:
                return {};
            case WGPUTextureFormat_ASTC5x5UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC6x5Unorm:
                return {};
            case WGPUTextureFormat_ASTC6x5UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC6x6Unorm:
                return {};
            case WGPUTextureFormat_ASTC6x6UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC8x5Unorm:
                return {};
            case WGPUTextureFormat_ASTC8x5UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC8x6Unorm:
                return {};
            case WGPUTextureFormat_ASTC8x6UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC8x8Unorm:
                return {};
            case WGPUTextureFormat_ASTC8x8UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC10x5Unorm:
                return {};
            case WGPUTextureFormat_ASTC10x5UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC10x6Unorm:
                return {};
            case WGPUTextureFormat_ASTC10x6UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC10x8Unorm:
                return {};
            case WGPUTextureFormat_ASTC10x8UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC10x10Unorm:
                return {};
            case WGPUTextureFormat_ASTC10x10UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC12x10Unorm:
                return {};
            case WGPUTextureFormat_ASTC12x10UnormSrgb:
                return {};
            case WGPUTextureFormat_ASTC12x12Unorm:
                return {};
            case WGPUTextureFormat_ASTC12x12UnormSrgb:
                return {};
            case WGPUTextureFormat_R8BG8Biplanar420Unorm:
                return {};
            case WGPUTextureFormat_R10X6BG10X6Biplanar420Unorm:
                return {};
            case WGPUTextureFormat_R8BG8A8Triplanar420Unorm:
                return {};
            case WGPUTextureFormat_R8BG8Biplanar422Unorm:
                return {};
            case WGPUTextureFormat_R8BG8Biplanar444Unorm:
                return {};
            case WGPUTextureFormat_R10X6BG10X6Biplanar422Unorm:
                return {};
            case WGPUTextureFormat_R10X6BG10X6Biplanar444Unorm:
                return {};
            case WGPUTextureFormat_OpaqueYCbCrAndroid:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUTextureFormat.", value);
        }
    }

    MaybeError ValidateTextureSampleType(wgpu::TextureSampleType value) {
        switch (WGPUTextureSampleType(value)) {
            case WGPUTextureSampleType_BindingNotUsed:
                return {};
            case WGPUTextureSampleType_Float:
                return {};
            case WGPUTextureSampleType_UnfilterableFloat:
                return {};
            case WGPUTextureSampleType_Depth:
                return {};
            case WGPUTextureSampleType_Sint:
                return {};
            case WGPUTextureSampleType_Uint:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUTextureSampleType.", value);
        }
    }

    MaybeError ValidateTextureViewDimension(wgpu::TextureViewDimension value) {
        switch (WGPUTextureViewDimension(value)) {
            case WGPUTextureViewDimension_Undefined:
                return {};
            case WGPUTextureViewDimension_1D:
                return {};
            case WGPUTextureViewDimension_2D:
                return {};
            case WGPUTextureViewDimension_2DArray:
                return {};
            case WGPUTextureViewDimension_Cube:
                return {};
            case WGPUTextureViewDimension_CubeArray:
                return {};
            case WGPUTextureViewDimension_3D:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUTextureViewDimension.", value);
        }
    }

    MaybeError ValidateToneMappingMode(wgpu::ToneMappingMode value) {
        switch (WGPUToneMappingMode(value)) {
            case WGPUToneMappingMode_Standard:
                return {};
            case WGPUToneMappingMode_Extended:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUToneMappingMode.", value);
        }
    }

    MaybeError ValidateVertexFormat(wgpu::VertexFormat value) {
        switch (WGPUVertexFormat(value)) {
            case WGPUVertexFormat_Uint8:
                return {};
            case WGPUVertexFormat_Uint8x2:
                return {};
            case WGPUVertexFormat_Uint8x4:
                return {};
            case WGPUVertexFormat_Sint8:
                return {};
            case WGPUVertexFormat_Sint8x2:
                return {};
            case WGPUVertexFormat_Sint8x4:
                return {};
            case WGPUVertexFormat_Unorm8:
                return {};
            case WGPUVertexFormat_Unorm8x2:
                return {};
            case WGPUVertexFormat_Unorm8x4:
                return {};
            case WGPUVertexFormat_Snorm8:
                return {};
            case WGPUVertexFormat_Snorm8x2:
                return {};
            case WGPUVertexFormat_Snorm8x4:
                return {};
            case WGPUVertexFormat_Uint16:
                return {};
            case WGPUVertexFormat_Uint16x2:
                return {};
            case WGPUVertexFormat_Uint16x4:
                return {};
            case WGPUVertexFormat_Sint16:
                return {};
            case WGPUVertexFormat_Sint16x2:
                return {};
            case WGPUVertexFormat_Sint16x4:
                return {};
            case WGPUVertexFormat_Unorm16:
                return {};
            case WGPUVertexFormat_Unorm16x2:
                return {};
            case WGPUVertexFormat_Unorm16x4:
                return {};
            case WGPUVertexFormat_Snorm16:
                return {};
            case WGPUVertexFormat_Snorm16x2:
                return {};
            case WGPUVertexFormat_Snorm16x4:
                return {};
            case WGPUVertexFormat_Float16:
                return {};
            case WGPUVertexFormat_Float16x2:
                return {};
            case WGPUVertexFormat_Float16x4:
                return {};
            case WGPUVertexFormat_Float32:
                return {};
            case WGPUVertexFormat_Float32x2:
                return {};
            case WGPUVertexFormat_Float32x3:
                return {};
            case WGPUVertexFormat_Float32x4:
                return {};
            case WGPUVertexFormat_Uint32:
                return {};
            case WGPUVertexFormat_Uint32x2:
                return {};
            case WGPUVertexFormat_Uint32x3:
                return {};
            case WGPUVertexFormat_Uint32x4:
                return {};
            case WGPUVertexFormat_Sint32:
                return {};
            case WGPUVertexFormat_Sint32x2:
                return {};
            case WGPUVertexFormat_Sint32x3:
                return {};
            case WGPUVertexFormat_Sint32x4:
                return {};
            case WGPUVertexFormat_Unorm10_10_10_2:
                return {};
            case WGPUVertexFormat_Unorm8x4BGRA:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUVertexFormat.", value);
        }
    }

    MaybeError ValidateVertexStepMode(wgpu::VertexStepMode value) {
        switch (WGPUVertexStepMode(value)) {
            case WGPUVertexStepMode_Undefined:
                return {};
            case WGPUVertexStepMode_Vertex:
                return {};
            case WGPUVertexStepMode_Instance:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUVertexStepMode.", value);
        }
    }

    MaybeError ValidateWaitStatus(wgpu::WaitStatus value) {
        switch (WGPUWaitStatus(value)) {
            case WGPUWaitStatus_Success:
                return {};
            case WGPUWaitStatus_TimedOut:
                return {};
            case WGPUWaitStatus_Error:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUWaitStatus.", value);
        }
    }

    MaybeError ValidateWGSLLanguageFeatureName(wgpu::WGSLLanguageFeatureName value) {
        switch (WGPUWGSLLanguageFeatureName(value)) {
            case WGPUWGSLLanguageFeatureName_ReadonlyAndReadwriteStorageTextures:
                return {};
            case WGPUWGSLLanguageFeatureName_Packed4x8IntegerDotProduct:
                return {};
            case WGPUWGSLLanguageFeatureName_UnrestrictedPointerParameters:
                return {};
            case WGPUWGSLLanguageFeatureName_PointerCompositeAccess:
                return {};
            case WGPUWGSLLanguageFeatureName_UniformBufferStandardLayout:
                return {};
            case WGPUWGSLLanguageFeatureName_SubgroupId:
                return {};
            case WGPUWGSLLanguageFeatureName_TextureAndSamplerLet:
                return {};
            case WGPUWGSLLanguageFeatureName_SubgroupUniformity:
                return {};
            case WGPUWGSLLanguageFeatureName_TextureFormatsTier1:
                return {};
            case WGPUWGSLLanguageFeatureName_ChromiumTestingUnimplemented:
                return {};
            case WGPUWGSLLanguageFeatureName_ChromiumTestingUnsafeExperimental:
                return {};
            case WGPUWGSLLanguageFeatureName_ChromiumTestingExperimental:
                return {};
            case WGPUWGSLLanguageFeatureName_ChromiumTestingShippedWithKillswitch:
                return {};
            case WGPUWGSLLanguageFeatureName_ChromiumTestingShipped:
                return {};
            case WGPUWGSLLanguageFeatureName_SizedBindingArray:
                return {};
            case WGPUWGSLLanguageFeatureName_TexelBuffers:
                return {};
            case WGPUWGSLLanguageFeatureName_ChromiumPrint:
                return {};
            case WGPUWGSLLanguageFeatureName_FragmentDepth:
                return {};
            case WGPUWGSLLanguageFeatureName_ImmediateAddressSpace:
                return {};
            case WGPUWGSLLanguageFeatureName_BufferView:
                return {};
            case WGPUWGSLLanguageFeatureName_FilteringParameters:
                return {};
            case WGPUWGSLLanguageFeatureName_SwizzleAssignment:
                return {};
            case WGPUWGSLLanguageFeatureName_LinearIndexing:
                return {};
            default:
                return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUWGSLLanguageFeatureName.", value);
        }
    }


    MaybeError ValidateBufferUsage(wgpu::BufferUsage value) {
        if ((value & static_cast<wgpu::BufferUsage>(~2047)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUBufferUsage.", value);
    }

    MaybeError ValidateColorWriteMask(wgpu::ColorWriteMask value) {
        if ((value & static_cast<wgpu::ColorWriteMask>(~15)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUColorWriteMask.", value);
    }

    MaybeError ValidateHeapProperty(wgpu::HeapProperty value) {
        if ((value & static_cast<wgpu::HeapProperty>(~31)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUHeapProperty.", value);
    }

    MaybeError ValidateMapMode(wgpu::MapMode value) {
        if ((value & static_cast<wgpu::MapMode>(~3)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUMapMode.", value);
    }

    MaybeError ValidateShaderStage(wgpu::ShaderStage value) {
        if ((value & static_cast<wgpu::ShaderStage>(~7)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUShaderStage.", value);
    }

    MaybeError ValidateTextureUsage(wgpu::TextureUsage value) {
        if ((value & static_cast<wgpu::TextureUsage>(~127)) == 0) {
            return {};
        }
        return DAWN_VALIDATION_ERROR("Value %i is invalid for WGPUTextureUsage.", value);
    }


} // namespace dawn::native
