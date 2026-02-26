
#ifndef WEBGPU_ABSL_FORMAT_H_
#define WEBGPU_ABSL_FORMAT_H_

#include "dawn/native/dawn_platform.h"
#include "dawn/native/Forward.h"

#include "absl/strings/str_format.h"

namespace dawn::native {

    //
    // Descriptors
    //

    // Only includes structures that have a 'label' member.
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const CommandBufferDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<CommandBufferDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const QuerySetDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<QuerySetDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const QueueDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<QueueDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const RenderBundleDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<RenderBundleDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const RenderBundleEncoderDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<RenderBundleEncoderDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const ResourceTableDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<ResourceTableDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const SharedBufferMemoryDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<SharedBufferMemoryDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const TexelBufferViewDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<TexelBufferViewDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const BufferDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<BufferDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const CommandEncoderDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<CommandEncoderDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const ComputePassDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<ComputePassDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const ExternalTextureDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<ExternalTextureDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const SamplerDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<SamplerDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const ShaderModuleDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<ShaderModuleDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const SharedFenceDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<SharedFenceDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const SurfaceDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<SurfaceDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const TextureDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<TextureDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const BindGroupDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<BindGroupDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const BindGroupLayoutDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<BindGroupLayoutDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const ComputePipelineDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<ComputePipelineDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const DeviceDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<DeviceDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const PipelineLayoutDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<PipelineLayoutDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const SharedTextureMemoryDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<SharedTextureMemoryDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const TextureViewDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<TextureViewDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const RenderPassDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<RenderPassDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const RenderPipelineDescriptor* value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
        AbslFormatConvert(const UnpackedPtr<RenderPipelineDescriptor>& value,
                          const absl::FormatConversionSpec& spec,
                          absl::FormatSink* s);

} // namespace dawn::native

namespace wgpu {

    //
    // Enums
    //

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(AdapterType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(AddressMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(AlphaMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(BackendType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(BlendFactor value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(BlendOperation value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(BufferBindingType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(BufferMapState value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(CallbackMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(CompareFunction value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(CompilationInfoRequestStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(CompilationMessageType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(ComponentSwizzle value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(CompositeAlphaMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(CreatePipelineAsyncStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(CullMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(DeviceLostReason value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(ErrorFilter value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(ErrorType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(ExternalTextureRotation value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(FeatureLevel value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(FeatureName value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(FilterMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(FrontFace value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(IndexFormat value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(InstanceFeatureName value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(LoadOp value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(LoggingType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(MapAsyncStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(MipmapFilterMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(OptionalBool value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(PopErrorScopeStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(PowerPreference value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(PredefinedColorSpace value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(PresentMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(PrimitiveTopology value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(QueryType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(QueueWorkDoneStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(RequestAdapterStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(RequestDeviceStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(SamplerBindingType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(SharedFenceType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(Status value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(StencilOperation value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(StorageTextureAccess value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(StoreOp value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(SType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(SubgroupMatrixComponentType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(SurfaceGetCurrentTextureStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(TexelBufferAccess value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(TextureAspect value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(TextureDimension value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(TextureFormat value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(TextureSampleType value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(TextureViewDimension value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(ToneMappingMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(VertexFormat value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(VertexStepMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(WaitStatus value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(WGSLLanguageFeatureName value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);

    //
    // Bitmasks
    //

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(BufferUsage value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(ColorWriteMask value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(HeapProperty value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(MapMode value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(ShaderStage value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
    AbslFormatConvert(TextureUsage value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s);

}  // namespace wgpu

#endif // WEBGPU_ABSL_FORMAT_H_
