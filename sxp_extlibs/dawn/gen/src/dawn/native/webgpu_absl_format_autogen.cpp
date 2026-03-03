
#include "dawn/native/webgpu_absl_format_autogen.h"

#include "dawn/native/ChainUtils.h"
#include "dawn/native/ObjectType_autogen.h"
#include "dawn/native/webgpu_absl_format.h"

namespace dawn::native {

    //
    // Descriptors
    //

    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const CommandBufferDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[CommandBufferDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<CommandBufferDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const QuerySetDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[QuerySetDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<QuerySetDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const QueueDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[QueueDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<QueueDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderBundleDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[RenderBundleDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<RenderBundleDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderBundleEncoderDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[RenderBundleEncoderDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<RenderBundleEncoderDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ResourceTableDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[ResourceTableDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<ResourceTableDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SharedBufferMemoryDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[SharedBufferMemoryDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<SharedBufferMemoryDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const TexelBufferViewDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[TexelBufferViewDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<TexelBufferViewDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const BufferDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[BufferDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<BufferDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const CommandEncoderDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[CommandEncoderDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<CommandEncoderDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ComputePassDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[ComputePassDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<ComputePassDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ExternalTextureDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[ExternalTextureDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<ExternalTextureDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SamplerDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[SamplerDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<SamplerDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ShaderModuleDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[ShaderModuleDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<ShaderModuleDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SharedFenceDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[SharedFenceDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<SharedFenceDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SurfaceDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[SurfaceDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<SurfaceDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const TextureDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[TextureDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<TextureDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const BindGroupDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[BindGroupDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<BindGroupDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const BindGroupLayoutDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[BindGroupLayoutDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<BindGroupLayoutDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const ComputePipelineDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[ComputePipelineDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<ComputePipelineDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const DeviceDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[DeviceDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<DeviceDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const PipelineLayoutDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[PipelineLayoutDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<PipelineLayoutDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const SharedTextureMemoryDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[SharedTextureMemoryDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<SharedTextureMemoryDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const TextureViewDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[TextureViewDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<TextureViewDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderPassDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[RenderPassDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<RenderPassDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const RenderPipelineDescriptor* value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        if (value == nullptr) {
            s->Append("[null]");
            return {true};
        }
        s->Append("[RenderPipelineDescriptor");
        if (value->label.data != nullptr) {
            s->Append(absl::StrFormat(" \"%s\"", value->label));
        }
        s->Append("]");
        return {true};
    }
    absl::FormatConvertResult<absl::FormatConversionCharSet::kString>
    AbslFormatConvert(const UnpackedPtr<RenderPipelineDescriptor>& value,
                      const absl::FormatConversionSpec& spec,
                      absl::FormatSink* s) {
        return AbslFormatConvert(*value, spec, s);
    }

}  // namespace dawn::native

namespace wgpu {

    //
    // Enums
    //

absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(AdapterType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("AdapterType::");
        switch (WGPUAdapterType(value)) {
        case WGPUAdapterType_DiscreteGPU:
            s->Append("DiscreteGPU");
            return {true};
        case WGPUAdapterType_IntegratedGPU:
            s->Append("IntegratedGPU");
            return {true};
        case WGPUAdapterType_CPU:
            s->Append("CPU");
            return {true};
        case WGPUAdapterType_Unknown:
            s->Append("Unknown");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUAdapterType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(AddressMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("AddressMode::");
        switch (WGPUAddressMode(value)) {
        case WGPUAddressMode_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUAddressMode_ClampToEdge:
            s->Append("ClampToEdge");
            return {true};
        case WGPUAddressMode_Repeat:
            s->Append("Repeat");
            return {true};
        case WGPUAddressMode_MirrorRepeat:
            s->Append("MirrorRepeat");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUAddressMode>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(AlphaMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("AlphaMode::");
        switch (WGPUAlphaMode(value)) {
        case WGPUAlphaMode_Opaque:
            s->Append("Opaque");
            return {true};
        case WGPUAlphaMode_Premultiplied:
            s->Append("Premultiplied");
            return {true};
        case WGPUAlphaMode_Unpremultiplied:
            s->Append("Unpremultiplied");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUAlphaMode>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(BackendType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("BackendType::");
        switch (WGPUBackendType(value)) {
        case WGPUBackendType_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUBackendType_Null:
            s->Append("Null");
            return {true};
        case WGPUBackendType_WebGPU:
            s->Append("WebGPU");
            return {true};
        case WGPUBackendType_D3D11:
            s->Append("D3D11");
            return {true};
        case WGPUBackendType_D3D12:
            s->Append("D3D12");
            return {true};
        case WGPUBackendType_Metal:
            s->Append("Metal");
            return {true};
        case WGPUBackendType_Vulkan:
            s->Append("Vulkan");
            return {true};
        case WGPUBackendType_OpenGL:
            s->Append("OpenGL");
            return {true};
        case WGPUBackendType_OpenGLES:
            s->Append("OpenGLES");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUBackendType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(BlendFactor value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("BlendFactor::");
        switch (WGPUBlendFactor(value)) {
        case WGPUBlendFactor_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUBlendFactor_Zero:
            s->Append("Zero");
            return {true};
        case WGPUBlendFactor_One:
            s->Append("One");
            return {true};
        case WGPUBlendFactor_Src:
            s->Append("Src");
            return {true};
        case WGPUBlendFactor_OneMinusSrc:
            s->Append("OneMinusSrc");
            return {true};
        case WGPUBlendFactor_SrcAlpha:
            s->Append("SrcAlpha");
            return {true};
        case WGPUBlendFactor_OneMinusSrcAlpha:
            s->Append("OneMinusSrcAlpha");
            return {true};
        case WGPUBlendFactor_Dst:
            s->Append("Dst");
            return {true};
        case WGPUBlendFactor_OneMinusDst:
            s->Append("OneMinusDst");
            return {true};
        case WGPUBlendFactor_DstAlpha:
            s->Append("DstAlpha");
            return {true};
        case WGPUBlendFactor_OneMinusDstAlpha:
            s->Append("OneMinusDstAlpha");
            return {true};
        case WGPUBlendFactor_SrcAlphaSaturated:
            s->Append("SrcAlphaSaturated");
            return {true};
        case WGPUBlendFactor_Constant:
            s->Append("Constant");
            return {true};
        case WGPUBlendFactor_OneMinusConstant:
            s->Append("OneMinusConstant");
            return {true};
        case WGPUBlendFactor_Src1:
            s->Append("Src1");
            return {true};
        case WGPUBlendFactor_OneMinusSrc1:
            s->Append("OneMinusSrc1");
            return {true};
        case WGPUBlendFactor_Src1Alpha:
            s->Append("Src1Alpha");
            return {true};
        case WGPUBlendFactor_OneMinusSrc1Alpha:
            s->Append("OneMinusSrc1Alpha");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUBlendFactor>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(BlendOperation value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("BlendOperation::");
        switch (WGPUBlendOperation(value)) {
        case WGPUBlendOperation_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUBlendOperation_Add:
            s->Append("Add");
            return {true};
        case WGPUBlendOperation_Subtract:
            s->Append("Subtract");
            return {true};
        case WGPUBlendOperation_ReverseSubtract:
            s->Append("ReverseSubtract");
            return {true};
        case WGPUBlendOperation_Min:
            s->Append("Min");
            return {true};
        case WGPUBlendOperation_Max:
            s->Append("Max");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUBlendOperation>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(BufferBindingType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("BufferBindingType::");
        switch (WGPUBufferBindingType(value)) {
        case WGPUBufferBindingType_BindingNotUsed:
            s->Append("BindingNotUsed");
            return {true};
        case WGPUBufferBindingType_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUBufferBindingType_Uniform:
            s->Append("Uniform");
            return {true};
        case WGPUBufferBindingType_Storage:
            s->Append("Storage");
            return {true};
        case WGPUBufferBindingType_ReadOnlyStorage:
            s->Append("ReadOnlyStorage");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUBufferBindingType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(BufferMapState value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("BufferMapState::");
        switch (WGPUBufferMapState(value)) {
        case WGPUBufferMapState_Unmapped:
            s->Append("Unmapped");
            return {true};
        case WGPUBufferMapState_Pending:
            s->Append("Pending");
            return {true};
        case WGPUBufferMapState_Mapped:
            s->Append("Mapped");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUBufferMapState>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(CallbackMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("CallbackMode::");
        switch (WGPUCallbackMode(value)) {
        case WGPUCallbackMode_WaitAnyOnly:
            s->Append("WaitAnyOnly");
            return {true};
        case WGPUCallbackMode_AllowProcessEvents:
            s->Append("AllowProcessEvents");
            return {true};
        case WGPUCallbackMode_AllowSpontaneous:
            s->Append("AllowSpontaneous");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUCallbackMode>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(CompareFunction value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("CompareFunction::");
        switch (WGPUCompareFunction(value)) {
        case WGPUCompareFunction_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUCompareFunction_Never:
            s->Append("Never");
            return {true};
        case WGPUCompareFunction_Less:
            s->Append("Less");
            return {true};
        case WGPUCompareFunction_Equal:
            s->Append("Equal");
            return {true};
        case WGPUCompareFunction_LessEqual:
            s->Append("LessEqual");
            return {true};
        case WGPUCompareFunction_Greater:
            s->Append("Greater");
            return {true};
        case WGPUCompareFunction_NotEqual:
            s->Append("NotEqual");
            return {true};
        case WGPUCompareFunction_GreaterEqual:
            s->Append("GreaterEqual");
            return {true};
        case WGPUCompareFunction_Always:
            s->Append("Always");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUCompareFunction>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(CompilationInfoRequestStatus value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("CompilationInfoRequestStatus::");
        switch (WGPUCompilationInfoRequestStatus(value)) {
        case WGPUCompilationInfoRequestStatus_Success:
            s->Append("Success");
            return {true};
        case WGPUCompilationInfoRequestStatus_CallbackCancelled:
            s->Append("CallbackCancelled");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUCompilationInfoRequestStatus>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(CompilationMessageType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("CompilationMessageType::");
        switch (WGPUCompilationMessageType(value)) {
        case WGPUCompilationMessageType_Error:
            s->Append("Error");
            return {true};
        case WGPUCompilationMessageType_Warning:
            s->Append("Warning");
            return {true};
        case WGPUCompilationMessageType_Info:
            s->Append("Info");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUCompilationMessageType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(ComponentSwizzle value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("ComponentSwizzle::");
        switch (WGPUComponentSwizzle(value)) {
        case WGPUComponentSwizzle_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUComponentSwizzle_Zero:
            s->Append("Zero");
            return {true};
        case WGPUComponentSwizzle_One:
            s->Append("One");
            return {true};
        case WGPUComponentSwizzle_R:
            s->Append("R");
            return {true};
        case WGPUComponentSwizzle_G:
            s->Append("G");
            return {true};
        case WGPUComponentSwizzle_B:
            s->Append("B");
            return {true};
        case WGPUComponentSwizzle_A:
            s->Append("A");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUComponentSwizzle>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(CompositeAlphaMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("CompositeAlphaMode::");
        switch (WGPUCompositeAlphaMode(value)) {
        case WGPUCompositeAlphaMode_Auto:
            s->Append("Auto");
            return {true};
        case WGPUCompositeAlphaMode_Opaque:
            s->Append("Opaque");
            return {true};
        case WGPUCompositeAlphaMode_Premultiplied:
            s->Append("Premultiplied");
            return {true};
        case WGPUCompositeAlphaMode_Unpremultiplied:
            s->Append("Unpremultiplied");
            return {true};
        case WGPUCompositeAlphaMode_Inherit:
            s->Append("Inherit");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUCompositeAlphaMode>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(CreatePipelineAsyncStatus value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("CreatePipelineAsyncStatus::");
        switch (WGPUCreatePipelineAsyncStatus(value)) {
        case WGPUCreatePipelineAsyncStatus_Success:
            s->Append("Success");
            return {true};
        case WGPUCreatePipelineAsyncStatus_CallbackCancelled:
            s->Append("CallbackCancelled");
            return {true};
        case WGPUCreatePipelineAsyncStatus_ValidationError:
            s->Append("ValidationError");
            return {true};
        case WGPUCreatePipelineAsyncStatus_InternalError:
            s->Append("InternalError");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUCreatePipelineAsyncStatus>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(CullMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("CullMode::");
        switch (WGPUCullMode(value)) {
        case WGPUCullMode_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUCullMode_None:
            s->Append("None");
            return {true};
        case WGPUCullMode_Front:
            s->Append("Front");
            return {true};
        case WGPUCullMode_Back:
            s->Append("Back");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUCullMode>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(DeviceLostReason value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("DeviceLostReason::");
        switch (WGPUDeviceLostReason(value)) {
        case WGPUDeviceLostReason_Unknown:
            s->Append("Unknown");
            return {true};
        case WGPUDeviceLostReason_Destroyed:
            s->Append("Destroyed");
            return {true};
        case WGPUDeviceLostReason_CallbackCancelled:
            s->Append("CallbackCancelled");
            return {true};
        case WGPUDeviceLostReason_FailedCreation:
            s->Append("FailedCreation");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUDeviceLostReason>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(ErrorFilter value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("ErrorFilter::");
        switch (WGPUErrorFilter(value)) {
        case WGPUErrorFilter_Validation:
            s->Append("Validation");
            return {true};
        case WGPUErrorFilter_OutOfMemory:
            s->Append("OutOfMemory");
            return {true};
        case WGPUErrorFilter_Internal:
            s->Append("Internal");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUErrorFilter>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(ErrorType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("ErrorType::");
        switch (WGPUErrorType(value)) {
        case WGPUErrorType_NoError:
            s->Append("NoError");
            return {true};
        case WGPUErrorType_Validation:
            s->Append("Validation");
            return {true};
        case WGPUErrorType_OutOfMemory:
            s->Append("OutOfMemory");
            return {true};
        case WGPUErrorType_Internal:
            s->Append("Internal");
            return {true};
        case WGPUErrorType_Unknown:
            s->Append("Unknown");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUErrorType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(ExternalTextureRotation value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("ExternalTextureRotation::");
        switch (WGPUExternalTextureRotation(value)) {
        case WGPUExternalTextureRotation_Rotate0Degrees:
            s->Append("Rotate0Degrees");
            return {true};
        case WGPUExternalTextureRotation_Rotate90Degrees:
            s->Append("Rotate90Degrees");
            return {true};
        case WGPUExternalTextureRotation_Rotate180Degrees:
            s->Append("Rotate180Degrees");
            return {true};
        case WGPUExternalTextureRotation_Rotate270Degrees:
            s->Append("Rotate270Degrees");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUExternalTextureRotation>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(FeatureLevel value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("FeatureLevel::");
        switch (WGPUFeatureLevel(value)) {
        case WGPUFeatureLevel_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUFeatureLevel_Compatibility:
            s->Append("Compatibility");
            return {true};
        case WGPUFeatureLevel_Core:
            s->Append("Core");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUFeatureLevel>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(FeatureName value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("FeatureName::");
        switch (WGPUFeatureName(value)) {
        case WGPUFeatureName_CoreFeaturesAndLimits:
            s->Append("CoreFeaturesAndLimits");
            return {true};
        case WGPUFeatureName_DepthClipControl:
            s->Append("DepthClipControl");
            return {true};
        case WGPUFeatureName_Depth32FloatStencil8:
            s->Append("Depth32FloatStencil8");
            return {true};
        case WGPUFeatureName_TextureCompressionBC:
            s->Append("TextureCompressionBC");
            return {true};
        case WGPUFeatureName_TextureCompressionBCSliced3D:
            s->Append("TextureCompressionBCSliced3D");
            return {true};
        case WGPUFeatureName_TextureCompressionETC2:
            s->Append("TextureCompressionETC2");
            return {true};
        case WGPUFeatureName_TextureCompressionASTC:
            s->Append("TextureCompressionASTC");
            return {true};
        case WGPUFeatureName_TextureCompressionASTCSliced3D:
            s->Append("TextureCompressionASTCSliced3D");
            return {true};
        case WGPUFeatureName_TimestampQuery:
            s->Append("TimestampQuery");
            return {true};
        case WGPUFeatureName_IndirectFirstInstance:
            s->Append("IndirectFirstInstance");
            return {true};
        case WGPUFeatureName_ShaderF16:
            s->Append("ShaderF16");
            return {true};
        case WGPUFeatureName_RG11B10UfloatRenderable:
            s->Append("RG11B10UfloatRenderable");
            return {true};
        case WGPUFeatureName_BGRA8UnormStorage:
            s->Append("BGRA8UnormStorage");
            return {true};
        case WGPUFeatureName_Float32Filterable:
            s->Append("Float32Filterable");
            return {true};
        case WGPUFeatureName_Float32Blendable:
            s->Append("Float32Blendable");
            return {true};
        case WGPUFeatureName_ClipDistances:
            s->Append("ClipDistances");
            return {true};
        case WGPUFeatureName_DualSourceBlending:
            s->Append("DualSourceBlending");
            return {true};
        case WGPUFeatureName_Subgroups:
            s->Append("Subgroups");
            return {true};
        case WGPUFeatureName_TextureFormatsTier1:
            s->Append("TextureFormatsTier1");
            return {true};
        case WGPUFeatureName_TextureFormatsTier2:
            s->Append("TextureFormatsTier2");
            return {true};
        case WGPUFeatureName_PrimitiveIndex:
            s->Append("PrimitiveIndex");
            return {true};
        case WGPUFeatureName_TextureComponentSwizzle:
            s->Append("TextureComponentSwizzle");
            return {true};
        case WGPUFeatureName_DawnInternalUsages:
            s->Append("DawnInternalUsages");
            return {true};
        case WGPUFeatureName_DawnMultiPlanarFormats:
            s->Append("DawnMultiPlanarFormats");
            return {true};
        case WGPUFeatureName_DawnNative:
            s->Append("DawnNative");
            return {true};
        case WGPUFeatureName_ChromiumExperimentalTimestampQueryInsidePasses:
            s->Append("ChromiumExperimentalTimestampQueryInsidePasses");
            return {true};
        case WGPUFeatureName_ImplicitDeviceSynchronization:
            s->Append("ImplicitDeviceSynchronization");
            return {true};
        case WGPUFeatureName_TransientAttachments:
            s->Append("TransientAttachments");
            return {true};
        case WGPUFeatureName_MSAARenderToSingleSampled:
            s->Append("MSAARenderToSingleSampled");
            return {true};
        case WGPUFeatureName_D3D11MultithreadProtected:
            s->Append("D3D11MultithreadProtected");
            return {true};
        case WGPUFeatureName_ANGLETextureSharing:
            s->Append("ANGLETextureSharing");
            return {true};
        case WGPUFeatureName_PixelLocalStorageCoherent:
            s->Append("PixelLocalStorageCoherent");
            return {true};
        case WGPUFeatureName_PixelLocalStorageNonCoherent:
            s->Append("PixelLocalStorageNonCoherent");
            return {true};
        case WGPUFeatureName_Unorm16TextureFormats:
            s->Append("Unorm16TextureFormats");
            return {true};
        case WGPUFeatureName_MultiPlanarFormatExtendedUsages:
            s->Append("MultiPlanarFormatExtendedUsages");
            return {true};
        case WGPUFeatureName_MultiPlanarFormatP010:
            s->Append("MultiPlanarFormatP010");
            return {true};
        case WGPUFeatureName_HostMappedPointer:
            s->Append("HostMappedPointer");
            return {true};
        case WGPUFeatureName_MultiPlanarRenderTargets:
            s->Append("MultiPlanarRenderTargets");
            return {true};
        case WGPUFeatureName_MultiPlanarFormatNv12a:
            s->Append("MultiPlanarFormatNv12a");
            return {true};
        case WGPUFeatureName_FramebufferFetch:
            s->Append("FramebufferFetch");
            return {true};
        case WGPUFeatureName_BufferMapExtendedUsages:
            s->Append("BufferMapExtendedUsages");
            return {true};
        case WGPUFeatureName_AdapterPropertiesMemoryHeaps:
            s->Append("AdapterPropertiesMemoryHeaps");
            return {true};
        case WGPUFeatureName_AdapterPropertiesD3D:
            s->Append("AdapterPropertiesD3D");
            return {true};
        case WGPUFeatureName_AdapterPropertiesVk:
            s->Append("AdapterPropertiesVk");
            return {true};
        case WGPUFeatureName_DawnFormatCapabilities:
            s->Append("DawnFormatCapabilities");
            return {true};
        case WGPUFeatureName_DawnDrmFormatCapabilities:
            s->Append("DawnDrmFormatCapabilities");
            return {true};
        case WGPUFeatureName_MultiPlanarFormatNv16:
            s->Append("MultiPlanarFormatNv16");
            return {true};
        case WGPUFeatureName_MultiPlanarFormatNv24:
            s->Append("MultiPlanarFormatNv24");
            return {true};
        case WGPUFeatureName_MultiPlanarFormatP210:
            s->Append("MultiPlanarFormatP210");
            return {true};
        case WGPUFeatureName_MultiPlanarFormatP410:
            s->Append("MultiPlanarFormatP410");
            return {true};
        case WGPUFeatureName_SharedTextureMemoryVkDedicatedAllocation:
            s->Append("SharedTextureMemoryVkDedicatedAllocation");
            return {true};
        case WGPUFeatureName_SharedTextureMemoryAHardwareBuffer:
            s->Append("SharedTextureMemoryAHardwareBuffer");
            return {true};
        case WGPUFeatureName_SharedTextureMemoryDmaBuf:
            s->Append("SharedTextureMemoryDmaBuf");
            return {true};
        case WGPUFeatureName_SharedTextureMemoryOpaqueFD:
            s->Append("SharedTextureMemoryOpaqueFD");
            return {true};
        case WGPUFeatureName_SharedTextureMemoryZirconHandle:
            s->Append("SharedTextureMemoryZirconHandle");
            return {true};
        case WGPUFeatureName_SharedTextureMemoryDXGISharedHandle:
            s->Append("SharedTextureMemoryDXGISharedHandle");
            return {true};
        case WGPUFeatureName_SharedTextureMemoryD3D11Texture2D:
            s->Append("SharedTextureMemoryD3D11Texture2D");
            return {true};
        case WGPUFeatureName_SharedTextureMemoryIOSurface:
            s->Append("SharedTextureMemoryIOSurface");
            return {true};
        case WGPUFeatureName_SharedTextureMemoryEGLImage:
            s->Append("SharedTextureMemoryEGLImage");
            return {true};
        case WGPUFeatureName_SharedFenceVkSemaphoreOpaqueFD:
            s->Append("SharedFenceVkSemaphoreOpaqueFD");
            return {true};
        case WGPUFeatureName_SharedFenceSyncFD:
            s->Append("SharedFenceSyncFD");
            return {true};
        case WGPUFeatureName_SharedFenceVkSemaphoreZirconHandle:
            s->Append("SharedFenceVkSemaphoreZirconHandle");
            return {true};
        case WGPUFeatureName_SharedFenceDXGISharedHandle:
            s->Append("SharedFenceDXGISharedHandle");
            return {true};
        case WGPUFeatureName_SharedFenceMTLSharedEvent:
            s->Append("SharedFenceMTLSharedEvent");
            return {true};
        case WGPUFeatureName_SharedBufferMemoryD3D12Resource:
            s->Append("SharedBufferMemoryD3D12Resource");
            return {true};
        case WGPUFeatureName_StaticSamplers:
            s->Append("StaticSamplers");
            return {true};
        case WGPUFeatureName_YCbCrVulkanSamplers:
            s->Append("YCbCrVulkanSamplers");
            return {true};
        case WGPUFeatureName_ShaderModuleCompilationOptions:
            s->Append("ShaderModuleCompilationOptions");
            return {true};
        case WGPUFeatureName_DawnLoadResolveTexture:
            s->Append("DawnLoadResolveTexture");
            return {true};
        case WGPUFeatureName_DawnPartialLoadResolveTexture:
            s->Append("DawnPartialLoadResolveTexture");
            return {true};
        case WGPUFeatureName_MultiDrawIndirect:
            s->Append("MultiDrawIndirect");
            return {true};
        case WGPUFeatureName_DawnTexelCopyBufferRowAlignment:
            s->Append("DawnTexelCopyBufferRowAlignment");
            return {true};
        case WGPUFeatureName_FlexibleTextureViews:
            s->Append("FlexibleTextureViews");
            return {true};
        case WGPUFeatureName_ChromiumExperimentalSubgroupMatrix:
            s->Append("ChromiumExperimentalSubgroupMatrix");
            return {true};
        case WGPUFeatureName_SharedFenceEGLSync:
            s->Append("SharedFenceEGLSync");
            return {true};
        case WGPUFeatureName_DawnDeviceAllocatorControl:
            s->Append("DawnDeviceAllocatorControl");
            return {true};
        case WGPUFeatureName_AdapterPropertiesWGPU:
            s->Append("AdapterPropertiesWGPU");
            return {true};
        case WGPUFeatureName_SharedBufferMemoryD3D12SharedMemoryFileMappingHandle:
            s->Append("SharedBufferMemoryD3D12SharedMemoryFileMappingHandle");
            return {true};
        case WGPUFeatureName_SharedTextureMemoryD3D12Resource:
            s->Append("SharedTextureMemoryD3D12Resource");
            return {true};
        case WGPUFeatureName_ChromiumExperimentalSamplingResourceTable:
            s->Append("ChromiumExperimentalSamplingResourceTable");
            return {true};
        case WGPUFeatureName_ChromiumExperimentalSubgroupSizeControl:
            s->Append("ChromiumExperimentalSubgroupSizeControl");
            return {true};
        case WGPUFeatureName_AtomicVec2uMinMax:
            s->Append("AtomicVec2uMinMax");
            return {true};
        case WGPUFeatureName_Unorm16FormatsForExternalTexture:
            s->Append("Unorm16FormatsForExternalTexture");
            return {true};
        case WGPUFeatureName_OpaqueYCbCrAndroidForExternalTexture:
            s->Append("OpaqueYCbCrAndroidForExternalTexture");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUFeatureName>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(FilterMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("FilterMode::");
        switch (WGPUFilterMode(value)) {
        case WGPUFilterMode_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUFilterMode_Nearest:
            s->Append("Nearest");
            return {true};
        case WGPUFilterMode_Linear:
            s->Append("Linear");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUFilterMode>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(FrontFace value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("FrontFace::");
        switch (WGPUFrontFace(value)) {
        case WGPUFrontFace_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUFrontFace_CCW:
            s->Append("CCW");
            return {true};
        case WGPUFrontFace_CW:
            s->Append("CW");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUFrontFace>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(IndexFormat value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("IndexFormat::");
        switch (WGPUIndexFormat(value)) {
        case WGPUIndexFormat_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUIndexFormat_Uint16:
            s->Append("Uint16");
            return {true};
        case WGPUIndexFormat_Uint32:
            s->Append("Uint32");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUIndexFormat>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(InstanceFeatureName value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("InstanceFeatureName::");
        switch (WGPUInstanceFeatureName(value)) {
        case WGPUInstanceFeatureName_TimedWaitAny:
            s->Append("TimedWaitAny");
            return {true};
        case WGPUInstanceFeatureName_ShaderSourceSPIRV:
            s->Append("ShaderSourceSPIRV");
            return {true};
        case WGPUInstanceFeatureName_MultipleDevicesPerAdapter:
            s->Append("MultipleDevicesPerAdapter");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUInstanceFeatureName>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(LoadOp value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("LoadOp::");
        switch (WGPULoadOp(value)) {
        case WGPULoadOp_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPULoadOp_Load:
            s->Append("Load");
            return {true};
        case WGPULoadOp_Clear:
            s->Append("Clear");
            return {true};
        case WGPULoadOp_ExpandResolveTexture:
            s->Append("ExpandResolveTexture");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPULoadOp>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(LoggingType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("LoggingType::");
        switch (WGPULoggingType(value)) {
        case WGPULoggingType_Verbose:
            s->Append("Verbose");
            return {true};
        case WGPULoggingType_Info:
            s->Append("Info");
            return {true};
        case WGPULoggingType_Warning:
            s->Append("Warning");
            return {true};
        case WGPULoggingType_Error:
            s->Append("Error");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPULoggingType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(MapAsyncStatus value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("MapAsyncStatus::");
        switch (WGPUMapAsyncStatus(value)) {
        case WGPUMapAsyncStatus_Success:
            s->Append("Success");
            return {true};
        case WGPUMapAsyncStatus_CallbackCancelled:
            s->Append("CallbackCancelled");
            return {true};
        case WGPUMapAsyncStatus_Error:
            s->Append("Error");
            return {true};
        case WGPUMapAsyncStatus_Aborted:
            s->Append("Aborted");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUMapAsyncStatus>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(MipmapFilterMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("MipmapFilterMode::");
        switch (WGPUMipmapFilterMode(value)) {
        case WGPUMipmapFilterMode_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUMipmapFilterMode_Nearest:
            s->Append("Nearest");
            return {true};
        case WGPUMipmapFilterMode_Linear:
            s->Append("Linear");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUMipmapFilterMode>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(OptionalBool value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("OptionalBool::");
        switch (WGPUOptionalBool(value)) {
        case WGPUOptionalBool_False:
            s->Append("False");
            return {true};
        case WGPUOptionalBool_True:
            s->Append("True");
            return {true};
        case WGPUOptionalBool_Undefined:
            s->Append("Undefined");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUOptionalBool>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(PopErrorScopeStatus value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("PopErrorScopeStatus::");
        switch (WGPUPopErrorScopeStatus(value)) {
        case WGPUPopErrorScopeStatus_Success:
            s->Append("Success");
            return {true};
        case WGPUPopErrorScopeStatus_CallbackCancelled:
            s->Append("CallbackCancelled");
            return {true};
        case WGPUPopErrorScopeStatus_Error:
            s->Append("Error");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUPopErrorScopeStatus>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(PowerPreference value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("PowerPreference::");
        switch (WGPUPowerPreference(value)) {
        case WGPUPowerPreference_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUPowerPreference_LowPower:
            s->Append("LowPower");
            return {true};
        case WGPUPowerPreference_HighPerformance:
            s->Append("HighPerformance");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUPowerPreference>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(PredefinedColorSpace value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("PredefinedColorSpace::");
        switch (WGPUPredefinedColorSpace(value)) {
        case WGPUPredefinedColorSpace_SRGB:
            s->Append("SRGB");
            return {true};
        case WGPUPredefinedColorSpace_DisplayP3:
            s->Append("DisplayP3");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUPredefinedColorSpace>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(PresentMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("PresentMode::");
        switch (WGPUPresentMode(value)) {
        case WGPUPresentMode_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUPresentMode_Fifo:
            s->Append("Fifo");
            return {true};
        case WGPUPresentMode_FifoRelaxed:
            s->Append("FifoRelaxed");
            return {true};
        case WGPUPresentMode_Immediate:
            s->Append("Immediate");
            return {true};
        case WGPUPresentMode_Mailbox:
            s->Append("Mailbox");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUPresentMode>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(PrimitiveTopology value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("PrimitiveTopology::");
        switch (WGPUPrimitiveTopology(value)) {
        case WGPUPrimitiveTopology_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUPrimitiveTopology_PointList:
            s->Append("PointList");
            return {true};
        case WGPUPrimitiveTopology_LineList:
            s->Append("LineList");
            return {true};
        case WGPUPrimitiveTopology_LineStrip:
            s->Append("LineStrip");
            return {true};
        case WGPUPrimitiveTopology_TriangleList:
            s->Append("TriangleList");
            return {true};
        case WGPUPrimitiveTopology_TriangleStrip:
            s->Append("TriangleStrip");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUPrimitiveTopology>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(QueryType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("QueryType::");
        switch (WGPUQueryType(value)) {
        case WGPUQueryType_Occlusion:
            s->Append("Occlusion");
            return {true};
        case WGPUQueryType_Timestamp:
            s->Append("Timestamp");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUQueryType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(QueueWorkDoneStatus value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("QueueWorkDoneStatus::");
        switch (WGPUQueueWorkDoneStatus(value)) {
        case WGPUQueueWorkDoneStatus_Success:
            s->Append("Success");
            return {true};
        case WGPUQueueWorkDoneStatus_CallbackCancelled:
            s->Append("CallbackCancelled");
            return {true};
        case WGPUQueueWorkDoneStatus_Error:
            s->Append("Error");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUQueueWorkDoneStatus>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(RequestAdapterStatus value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("RequestAdapterStatus::");
        switch (WGPURequestAdapterStatus(value)) {
        case WGPURequestAdapterStatus_Success:
            s->Append("Success");
            return {true};
        case WGPURequestAdapterStatus_CallbackCancelled:
            s->Append("CallbackCancelled");
            return {true};
        case WGPURequestAdapterStatus_Unavailable:
            s->Append("Unavailable");
            return {true};
        case WGPURequestAdapterStatus_Error:
            s->Append("Error");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPURequestAdapterStatus>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(RequestDeviceStatus value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("RequestDeviceStatus::");
        switch (WGPURequestDeviceStatus(value)) {
        case WGPURequestDeviceStatus_Success:
            s->Append("Success");
            return {true};
        case WGPURequestDeviceStatus_CallbackCancelled:
            s->Append("CallbackCancelled");
            return {true};
        case WGPURequestDeviceStatus_Error:
            s->Append("Error");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPURequestDeviceStatus>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(SamplerBindingType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("SamplerBindingType::");
        switch (WGPUSamplerBindingType(value)) {
        case WGPUSamplerBindingType_BindingNotUsed:
            s->Append("BindingNotUsed");
            return {true};
        case WGPUSamplerBindingType_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUSamplerBindingType_Filtering:
            s->Append("Filtering");
            return {true};
        case WGPUSamplerBindingType_NonFiltering:
            s->Append("NonFiltering");
            return {true};
        case WGPUSamplerBindingType_Comparison:
            s->Append("Comparison");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUSamplerBindingType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(SharedFenceType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("SharedFenceType::");
        switch (WGPUSharedFenceType(value)) {
        case WGPUSharedFenceType_VkSemaphoreOpaqueFD:
            s->Append("VkSemaphoreOpaqueFD");
            return {true};
        case WGPUSharedFenceType_SyncFD:
            s->Append("SyncFD");
            return {true};
        case WGPUSharedFenceType_VkSemaphoreZirconHandle:
            s->Append("VkSemaphoreZirconHandle");
            return {true};
        case WGPUSharedFenceType_DXGISharedHandle:
            s->Append("DXGISharedHandle");
            return {true};
        case WGPUSharedFenceType_MTLSharedEvent:
            s->Append("MTLSharedEvent");
            return {true};
        case WGPUSharedFenceType_EGLSync:
            s->Append("EGLSync");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUSharedFenceType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(Status value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("Status::");
        switch (WGPUStatus(value)) {
        case WGPUStatus_Success:
            s->Append("Success");
            return {true};
        case WGPUStatus_Error:
            s->Append("Error");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUStatus>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(StencilOperation value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("StencilOperation::");
        switch (WGPUStencilOperation(value)) {
        case WGPUStencilOperation_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUStencilOperation_Keep:
            s->Append("Keep");
            return {true};
        case WGPUStencilOperation_Zero:
            s->Append("Zero");
            return {true};
        case WGPUStencilOperation_Replace:
            s->Append("Replace");
            return {true};
        case WGPUStencilOperation_Invert:
            s->Append("Invert");
            return {true};
        case WGPUStencilOperation_IncrementClamp:
            s->Append("IncrementClamp");
            return {true};
        case WGPUStencilOperation_DecrementClamp:
            s->Append("DecrementClamp");
            return {true};
        case WGPUStencilOperation_IncrementWrap:
            s->Append("IncrementWrap");
            return {true};
        case WGPUStencilOperation_DecrementWrap:
            s->Append("DecrementWrap");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUStencilOperation>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(StorageTextureAccess value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("StorageTextureAccess::");
        switch (WGPUStorageTextureAccess(value)) {
        case WGPUStorageTextureAccess_BindingNotUsed:
            s->Append("BindingNotUsed");
            return {true};
        case WGPUStorageTextureAccess_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUStorageTextureAccess_WriteOnly:
            s->Append("WriteOnly");
            return {true};
        case WGPUStorageTextureAccess_ReadOnly:
            s->Append("ReadOnly");
            return {true};
        case WGPUStorageTextureAccess_ReadWrite:
            s->Append("ReadWrite");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUStorageTextureAccess>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(StoreOp value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("StoreOp::");
        switch (WGPUStoreOp(value)) {
        case WGPUStoreOp_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUStoreOp_Store:
            s->Append("Store");
            return {true};
        case WGPUStoreOp_Discard:
            s->Append("Discard");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUStoreOp>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(SType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("SType::");
        switch (WGPUSType(value)) {
        case WGPUSType_ShaderSourceSPIRV:
            s->Append("ShaderSourceSPIRV");
            return {true};
        case WGPUSType_ShaderSourceWGSL:
            s->Append("ShaderSourceWGSL");
            return {true};
        case WGPUSType_RenderPassMaxDrawCount:
            s->Append("RenderPassMaxDrawCount");
            return {true};
        case WGPUSType_SurfaceSourceMetalLayer:
            s->Append("SurfaceSourceMetalLayer");
            return {true};
        case WGPUSType_SurfaceSourceWindowsHWND:
            s->Append("SurfaceSourceWindowsHWND");
            return {true};
        case WGPUSType_SurfaceSourceXlibWindow:
            s->Append("SurfaceSourceXlibWindow");
            return {true};
        case WGPUSType_SurfaceSourceWaylandSurface:
            s->Append("SurfaceSourceWaylandSurface");
            return {true};
        case WGPUSType_SurfaceSourceAndroidNativeWindow:
            s->Append("SurfaceSourceAndroidNativeWindow");
            return {true};
        case WGPUSType_SurfaceSourceXCBWindow:
            s->Append("SurfaceSourceXCBWindow");
            return {true};
        case WGPUSType_SurfaceColorManagement:
            s->Append("SurfaceColorManagement");
            return {true};
        case WGPUSType_RequestAdapterWebXROptions:
            s->Append("RequestAdapterWebXROptions");
            return {true};
        case WGPUSType_TextureComponentSwizzleDescriptor:
            s->Append("TextureComponentSwizzleDescriptor");
            return {true};
        case WGPUSType_CompatibilityModeLimits:
            s->Append("CompatibilityModeLimits");
            return {true};
        case WGPUSType_TextureBindingViewDimensionDescriptor:
            s->Append("TextureBindingViewDimensionDescriptor");
            return {true};
        case WGPUSType_SurfaceDescriptorFromWindowsCoreWindow:
            s->Append("SurfaceDescriptorFromWindowsCoreWindow");
            return {true};
        case WGPUSType_ExternalTextureBindingEntry:
            s->Append("ExternalTextureBindingEntry");
            return {true};
        case WGPUSType_ExternalTextureBindingLayout:
            s->Append("ExternalTextureBindingLayout");
            return {true};
        case WGPUSType_SurfaceDescriptorFromWindowsUWPSwapChainPanel:
            s->Append("SurfaceDescriptorFromWindowsUWPSwapChainPanel");
            return {true};
        case WGPUSType_DawnTextureInternalUsageDescriptor:
            s->Append("DawnTextureInternalUsageDescriptor");
            return {true};
        case WGPUSType_DawnEncoderInternalUsageDescriptor:
            s->Append("DawnEncoderInternalUsageDescriptor");
            return {true};
        case WGPUSType_DawnInstanceDescriptor:
            s->Append("DawnInstanceDescriptor");
            return {true};
        case WGPUSType_DawnCacheDeviceDescriptor:
            s->Append("DawnCacheDeviceDescriptor");
            return {true};
        case WGPUSType_DawnAdapterPropertiesPowerPreference:
            s->Append("DawnAdapterPropertiesPowerPreference");
            return {true};
        case WGPUSType_DawnBufferDescriptorErrorInfoFromWireClient:
            s->Append("DawnBufferDescriptorErrorInfoFromWireClient");
            return {true};
        case WGPUSType_DawnTogglesDescriptor:
            s->Append("DawnTogglesDescriptor");
            return {true};
        case WGPUSType_DawnShaderModuleSPIRVOptionsDescriptor:
            s->Append("DawnShaderModuleSPIRVOptionsDescriptor");
            return {true};
        case WGPUSType_RequestAdapterOptionsLUID:
            s->Append("RequestAdapterOptionsLUID");
            return {true};
        case WGPUSType_RequestAdapterOptionsGetGLProc:
            s->Append("RequestAdapterOptionsGetGLProc");
            return {true};
        case WGPUSType_RequestAdapterOptionsD3D11Device:
            s->Append("RequestAdapterOptionsD3D11Device");
            return {true};
        case WGPUSType_DawnRenderPassSampleCount:
            s->Append("DawnRenderPassSampleCount");
            return {true};
        case WGPUSType_RenderPassPixelLocalStorage:
            s->Append("RenderPassPixelLocalStorage");
            return {true};
        case WGPUSType_PipelineLayoutPixelLocalStorage:
            s->Append("PipelineLayoutPixelLocalStorage");
            return {true};
        case WGPUSType_BufferHostMappedPointer:
            s->Append("BufferHostMappedPointer");
            return {true};
        case WGPUSType_AdapterPropertiesMemoryHeaps:
            s->Append("AdapterPropertiesMemoryHeaps");
            return {true};
        case WGPUSType_AdapterPropertiesD3D:
            s->Append("AdapterPropertiesD3D");
            return {true};
        case WGPUSType_AdapterPropertiesVk:
            s->Append("AdapterPropertiesVk");
            return {true};
        case WGPUSType_DawnWireWGSLControl:
            s->Append("DawnWireWGSLControl");
            return {true};
        case WGPUSType_DawnWGSLBlocklist:
            s->Append("DawnWGSLBlocklist");
            return {true};
        case WGPUSType_DawnDrmFormatCapabilities:
            s->Append("DawnDrmFormatCapabilities");
            return {true};
        case WGPUSType_ShaderModuleCompilationOptions:
            s->Append("ShaderModuleCompilationOptions");
            return {true};
        case WGPUSType_ColorTargetStateExpandResolveTextureDawn:
            s->Append("ColorTargetStateExpandResolveTextureDawn");
            return {true};
        case WGPUSType_RenderPassDescriptorExpandResolveRect:
            s->Append("RenderPassDescriptorExpandResolveRect");
            return {true};
        case WGPUSType_SharedTextureMemoryVkDedicatedAllocationDescriptor:
            s->Append("SharedTextureMemoryVkDedicatedAllocationDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryAHardwareBufferDescriptor:
            s->Append("SharedTextureMemoryAHardwareBufferDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryDmaBufDescriptor:
            s->Append("SharedTextureMemoryDmaBufDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryOpaqueFDDescriptor:
            s->Append("SharedTextureMemoryOpaqueFDDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryZirconHandleDescriptor:
            s->Append("SharedTextureMemoryZirconHandleDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryDXGISharedHandleDescriptor:
            s->Append("SharedTextureMemoryDXGISharedHandleDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryD3D11Texture2DDescriptor:
            s->Append("SharedTextureMemoryD3D11Texture2DDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryIOSurfaceDescriptor:
            s->Append("SharedTextureMemoryIOSurfaceDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryEGLImageDescriptor:
            s->Append("SharedTextureMemoryEGLImageDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryInitializedBeginState:
            s->Append("SharedTextureMemoryInitializedBeginState");
            return {true};
        case WGPUSType_SharedTextureMemoryInitializedEndState:
            s->Append("SharedTextureMemoryInitializedEndState");
            return {true};
        case WGPUSType_SharedTextureMemoryVkImageLayoutBeginState:
            s->Append("SharedTextureMemoryVkImageLayoutBeginState");
            return {true};
        case WGPUSType_SharedTextureMemoryVkImageLayoutEndState:
            s->Append("SharedTextureMemoryVkImageLayoutEndState");
            return {true};
        case WGPUSType_SharedTextureMemoryD3DSwapchainBeginState:
            s->Append("SharedTextureMemoryD3DSwapchainBeginState");
            return {true};
        case WGPUSType_SharedFenceVkSemaphoreOpaqueFDDescriptor:
            s->Append("SharedFenceVkSemaphoreOpaqueFDDescriptor");
            return {true};
        case WGPUSType_SharedFenceVkSemaphoreOpaqueFDExportInfo:
            s->Append("SharedFenceVkSemaphoreOpaqueFDExportInfo");
            return {true};
        case WGPUSType_SharedFenceSyncFDDescriptor:
            s->Append("SharedFenceSyncFDDescriptor");
            return {true};
        case WGPUSType_SharedFenceSyncFDExportInfo:
            s->Append("SharedFenceSyncFDExportInfo");
            return {true};
        case WGPUSType_SharedFenceVkSemaphoreZirconHandleDescriptor:
            s->Append("SharedFenceVkSemaphoreZirconHandleDescriptor");
            return {true};
        case WGPUSType_SharedFenceVkSemaphoreZirconHandleExportInfo:
            s->Append("SharedFenceVkSemaphoreZirconHandleExportInfo");
            return {true};
        case WGPUSType_SharedFenceDXGISharedHandleDescriptor:
            s->Append("SharedFenceDXGISharedHandleDescriptor");
            return {true};
        case WGPUSType_SharedFenceDXGISharedHandleExportInfo:
            s->Append("SharedFenceDXGISharedHandleExportInfo");
            return {true};
        case WGPUSType_SharedFenceMTLSharedEventDescriptor:
            s->Append("SharedFenceMTLSharedEventDescriptor");
            return {true};
        case WGPUSType_SharedFenceMTLSharedEventExportInfo:
            s->Append("SharedFenceMTLSharedEventExportInfo");
            return {true};
        case WGPUSType_SharedBufferMemoryD3D12ResourceDescriptor:
            s->Append("SharedBufferMemoryD3D12ResourceDescriptor");
            return {true};
        case WGPUSType_StaticSamplerBindingLayout:
            s->Append("StaticSamplerBindingLayout");
            return {true};
        case WGPUSType_YCbCrVkDescriptor:
            s->Append("YCbCrVkDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryAHardwareBufferProperties:
            s->Append("SharedTextureMemoryAHardwareBufferProperties");
            return {true};
        case WGPUSType_AHardwareBufferProperties:
            s->Append("AHardwareBufferProperties");
            return {true};
        case WGPUSType_DawnTexelCopyBufferRowAlignmentLimits:
            s->Append("DawnTexelCopyBufferRowAlignmentLimits");
            return {true};
        case WGPUSType_AdapterPropertiesSubgroupMatrixConfigs:
            s->Append("AdapterPropertiesSubgroupMatrixConfigs");
            return {true};
        case WGPUSType_SharedFenceEGLSyncDescriptor:
            s->Append("SharedFenceEGLSyncDescriptor");
            return {true};
        case WGPUSType_SharedFenceEGLSyncExportInfo:
            s->Append("SharedFenceEGLSyncExportInfo");
            return {true};
        case WGPUSType_DawnInjectedInvalidSType:
            s->Append("DawnInjectedInvalidSType");
            return {true};
        case WGPUSType_DawnCompilationMessageUtf16:
            s->Append("DawnCompilationMessageUtf16");
            return {true};
        case WGPUSType_DawnFakeBufferOOMForTesting:
            s->Append("DawnFakeBufferOOMForTesting");
            return {true};
        case WGPUSType_SurfaceDescriptorFromWindowsWinUISwapChainPanel:
            s->Append("SurfaceDescriptorFromWindowsWinUISwapChainPanel");
            return {true};
        case WGPUSType_DawnDeviceAllocatorControl:
            s->Append("DawnDeviceAllocatorControl");
            return {true};
        case WGPUSType_DawnHostMappedPointerLimits:
            s->Append("DawnHostMappedPointerLimits");
            return {true};
        case WGPUSType_RenderPassDescriptorResolveRect:
            s->Append("RenderPassDescriptorResolveRect");
            return {true};
        case WGPUSType_RequestAdapterWebGPUBackendOptions:
            s->Append("RequestAdapterWebGPUBackendOptions");
            return {true};
        case WGPUSType_DawnFakeDeviceInitializeErrorForTesting:
            s->Append("DawnFakeDeviceInitializeErrorForTesting");
            return {true};
        case WGPUSType_SharedTextureMemoryD3D11BeginState:
            s->Append("SharedTextureMemoryD3D11BeginState");
            return {true};
        case WGPUSType_DawnConsumeAdapterDescriptor:
            s->Append("DawnConsumeAdapterDescriptor");
            return {true};
        case WGPUSType_TexelBufferBindingEntry:
            s->Append("TexelBufferBindingEntry");
            return {true};
        case WGPUSType_TexelBufferBindingLayout:
            s->Append("TexelBufferBindingLayout");
            return {true};
        case WGPUSType_SharedTextureMemoryMetalEndAccessState:
            s->Append("SharedTextureMemoryMetalEndAccessState");
            return {true};
        case WGPUSType_AdapterPropertiesWGPU:
            s->Append("AdapterPropertiesWGPU");
            return {true};
        case WGPUSType_SharedBufferMemoryD3D12SharedMemoryFileMappingHandleDescriptor:
            s->Append("SharedBufferMemoryD3D12SharedMemoryFileMappingHandleDescriptor");
            return {true};
        case WGPUSType_SharedTextureMemoryD3D12ResourceDescriptor:
            s->Append("SharedTextureMemoryD3D12ResourceDescriptor");
            return {true};
        case WGPUSType_RequestAdapterOptionsAngleVirtualizationGroup:
            s->Append("RequestAdapterOptionsAngleVirtualizationGroup");
            return {true};
        case WGPUSType_PipelineLayoutResourceTable:
            s->Append("PipelineLayoutResourceTable");
            return {true};
        case WGPUSType_AdapterPropertiesExplicitComputeSubgroupSizeConfigs:
            s->Append("AdapterPropertiesExplicitComputeSubgroupSizeConfigs");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUSType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(SubgroupMatrixComponentType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("SubgroupMatrixComponentType::");
        switch (WGPUSubgroupMatrixComponentType(value)) {
        case WGPUSubgroupMatrixComponentType_F32:
            s->Append("F32");
            return {true};
        case WGPUSubgroupMatrixComponentType_F16:
            s->Append("F16");
            return {true};
        case WGPUSubgroupMatrixComponentType_U32:
            s->Append("U32");
            return {true};
        case WGPUSubgroupMatrixComponentType_I32:
            s->Append("I32");
            return {true};
        case WGPUSubgroupMatrixComponentType_U8:
            s->Append("U8");
            return {true};
        case WGPUSubgroupMatrixComponentType_I8:
            s->Append("I8");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUSubgroupMatrixComponentType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(SurfaceGetCurrentTextureStatus value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("SurfaceGetCurrentTextureStatus::");
        switch (WGPUSurfaceGetCurrentTextureStatus(value)) {
        case WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal:
            s->Append("SuccessOptimal");
            return {true};
        case WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal:
            s->Append("SuccessSuboptimal");
            return {true};
        case WGPUSurfaceGetCurrentTextureStatus_Timeout:
            s->Append("Timeout");
            return {true};
        case WGPUSurfaceGetCurrentTextureStatus_Outdated:
            s->Append("Outdated");
            return {true};
        case WGPUSurfaceGetCurrentTextureStatus_Lost:
            s->Append("Lost");
            return {true};
        case WGPUSurfaceGetCurrentTextureStatus_Error:
            s->Append("Error");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUSurfaceGetCurrentTextureStatus>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(TexelBufferAccess value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("TexelBufferAccess::");
        switch (WGPUTexelBufferAccess(value)) {
        case WGPUTexelBufferAccess_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUTexelBufferAccess_ReadOnly:
            s->Append("ReadOnly");
            return {true};
        case WGPUTexelBufferAccess_ReadWrite:
            s->Append("ReadWrite");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUTexelBufferAccess>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(TextureAspect value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("TextureAspect::");
        switch (WGPUTextureAspect(value)) {
        case WGPUTextureAspect_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUTextureAspect_All:
            s->Append("All");
            return {true};
        case WGPUTextureAspect_StencilOnly:
            s->Append("StencilOnly");
            return {true};
        case WGPUTextureAspect_DepthOnly:
            s->Append("DepthOnly");
            return {true};
        case WGPUTextureAspect_Plane0Only:
            s->Append("Plane0Only");
            return {true};
        case WGPUTextureAspect_Plane1Only:
            s->Append("Plane1Only");
            return {true};
        case WGPUTextureAspect_Plane2Only:
            s->Append("Plane2Only");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUTextureAspect>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(TextureDimension value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("TextureDimension::");
        switch (WGPUTextureDimension(value)) {
        case WGPUTextureDimension_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUTextureDimension_1D:
            s->Append("e1D");
            return {true};
        case WGPUTextureDimension_2D:
            s->Append("e2D");
            return {true};
        case WGPUTextureDimension_3D:
            s->Append("e3D");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUTextureDimension>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(TextureFormat value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("TextureFormat::");
        switch (WGPUTextureFormat(value)) {
        case WGPUTextureFormat_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUTextureFormat_R8Unorm:
            s->Append("R8Unorm");
            return {true};
        case WGPUTextureFormat_R8Snorm:
            s->Append("R8Snorm");
            return {true};
        case WGPUTextureFormat_R8Uint:
            s->Append("R8Uint");
            return {true};
        case WGPUTextureFormat_R8Sint:
            s->Append("R8Sint");
            return {true};
        case WGPUTextureFormat_R16Unorm:
            s->Append("R16Unorm");
            return {true};
        case WGPUTextureFormat_R16Snorm:
            s->Append("R16Snorm");
            return {true};
        case WGPUTextureFormat_R16Uint:
            s->Append("R16Uint");
            return {true};
        case WGPUTextureFormat_R16Sint:
            s->Append("R16Sint");
            return {true};
        case WGPUTextureFormat_R16Float:
            s->Append("R16Float");
            return {true};
        case WGPUTextureFormat_RG8Unorm:
            s->Append("RG8Unorm");
            return {true};
        case WGPUTextureFormat_RG8Snorm:
            s->Append("RG8Snorm");
            return {true};
        case WGPUTextureFormat_RG8Uint:
            s->Append("RG8Uint");
            return {true};
        case WGPUTextureFormat_RG8Sint:
            s->Append("RG8Sint");
            return {true};
        case WGPUTextureFormat_R32Float:
            s->Append("R32Float");
            return {true};
        case WGPUTextureFormat_R32Uint:
            s->Append("R32Uint");
            return {true};
        case WGPUTextureFormat_R32Sint:
            s->Append("R32Sint");
            return {true};
        case WGPUTextureFormat_RG16Unorm:
            s->Append("RG16Unorm");
            return {true};
        case WGPUTextureFormat_RG16Snorm:
            s->Append("RG16Snorm");
            return {true};
        case WGPUTextureFormat_RG16Uint:
            s->Append("RG16Uint");
            return {true};
        case WGPUTextureFormat_RG16Sint:
            s->Append("RG16Sint");
            return {true};
        case WGPUTextureFormat_RG16Float:
            s->Append("RG16Float");
            return {true};
        case WGPUTextureFormat_RGBA8Unorm:
            s->Append("RGBA8Unorm");
            return {true};
        case WGPUTextureFormat_RGBA8UnormSrgb:
            s->Append("RGBA8UnormSrgb");
            return {true};
        case WGPUTextureFormat_RGBA8Snorm:
            s->Append("RGBA8Snorm");
            return {true};
        case WGPUTextureFormat_RGBA8Uint:
            s->Append("RGBA8Uint");
            return {true};
        case WGPUTextureFormat_RGBA8Sint:
            s->Append("RGBA8Sint");
            return {true};
        case WGPUTextureFormat_BGRA8Unorm:
            s->Append("BGRA8Unorm");
            return {true};
        case WGPUTextureFormat_BGRA8UnormSrgb:
            s->Append("BGRA8UnormSrgb");
            return {true};
        case WGPUTextureFormat_RGB10A2Uint:
            s->Append("RGB10A2Uint");
            return {true};
        case WGPUTextureFormat_RGB10A2Unorm:
            s->Append("RGB10A2Unorm");
            return {true};
        case WGPUTextureFormat_RG11B10Ufloat:
            s->Append("RG11B10Ufloat");
            return {true};
        case WGPUTextureFormat_RGB9E5Ufloat:
            s->Append("RGB9E5Ufloat");
            return {true};
        case WGPUTextureFormat_RG32Float:
            s->Append("RG32Float");
            return {true};
        case WGPUTextureFormat_RG32Uint:
            s->Append("RG32Uint");
            return {true};
        case WGPUTextureFormat_RG32Sint:
            s->Append("RG32Sint");
            return {true};
        case WGPUTextureFormat_RGBA16Unorm:
            s->Append("RGBA16Unorm");
            return {true};
        case WGPUTextureFormat_RGBA16Snorm:
            s->Append("RGBA16Snorm");
            return {true};
        case WGPUTextureFormat_RGBA16Uint:
            s->Append("RGBA16Uint");
            return {true};
        case WGPUTextureFormat_RGBA16Sint:
            s->Append("RGBA16Sint");
            return {true};
        case WGPUTextureFormat_RGBA16Float:
            s->Append("RGBA16Float");
            return {true};
        case WGPUTextureFormat_RGBA32Float:
            s->Append("RGBA32Float");
            return {true};
        case WGPUTextureFormat_RGBA32Uint:
            s->Append("RGBA32Uint");
            return {true};
        case WGPUTextureFormat_RGBA32Sint:
            s->Append("RGBA32Sint");
            return {true};
        case WGPUTextureFormat_Stencil8:
            s->Append("Stencil8");
            return {true};
        case WGPUTextureFormat_Depth16Unorm:
            s->Append("Depth16Unorm");
            return {true};
        case WGPUTextureFormat_Depth24Plus:
            s->Append("Depth24Plus");
            return {true};
        case WGPUTextureFormat_Depth24PlusStencil8:
            s->Append("Depth24PlusStencil8");
            return {true};
        case WGPUTextureFormat_Depth32Float:
            s->Append("Depth32Float");
            return {true};
        case WGPUTextureFormat_Depth32FloatStencil8:
            s->Append("Depth32FloatStencil8");
            return {true};
        case WGPUTextureFormat_BC1RGBAUnorm:
            s->Append("BC1RGBAUnorm");
            return {true};
        case WGPUTextureFormat_BC1RGBAUnormSrgb:
            s->Append("BC1RGBAUnormSrgb");
            return {true};
        case WGPUTextureFormat_BC2RGBAUnorm:
            s->Append("BC2RGBAUnorm");
            return {true};
        case WGPUTextureFormat_BC2RGBAUnormSrgb:
            s->Append("BC2RGBAUnormSrgb");
            return {true};
        case WGPUTextureFormat_BC3RGBAUnorm:
            s->Append("BC3RGBAUnorm");
            return {true};
        case WGPUTextureFormat_BC3RGBAUnormSrgb:
            s->Append("BC3RGBAUnormSrgb");
            return {true};
        case WGPUTextureFormat_BC4RUnorm:
            s->Append("BC4RUnorm");
            return {true};
        case WGPUTextureFormat_BC4RSnorm:
            s->Append("BC4RSnorm");
            return {true};
        case WGPUTextureFormat_BC5RGUnorm:
            s->Append("BC5RGUnorm");
            return {true};
        case WGPUTextureFormat_BC5RGSnorm:
            s->Append("BC5RGSnorm");
            return {true};
        case WGPUTextureFormat_BC6HRGBUfloat:
            s->Append("BC6HRGBUfloat");
            return {true};
        case WGPUTextureFormat_BC6HRGBFloat:
            s->Append("BC6HRGBFloat");
            return {true};
        case WGPUTextureFormat_BC7RGBAUnorm:
            s->Append("BC7RGBAUnorm");
            return {true};
        case WGPUTextureFormat_BC7RGBAUnormSrgb:
            s->Append("BC7RGBAUnormSrgb");
            return {true};
        case WGPUTextureFormat_ETC2RGB8Unorm:
            s->Append("ETC2RGB8Unorm");
            return {true};
        case WGPUTextureFormat_ETC2RGB8UnormSrgb:
            s->Append("ETC2RGB8UnormSrgb");
            return {true};
        case WGPUTextureFormat_ETC2RGB8A1Unorm:
            s->Append("ETC2RGB8A1Unorm");
            return {true};
        case WGPUTextureFormat_ETC2RGB8A1UnormSrgb:
            s->Append("ETC2RGB8A1UnormSrgb");
            return {true};
        case WGPUTextureFormat_ETC2RGBA8Unorm:
            s->Append("ETC2RGBA8Unorm");
            return {true};
        case WGPUTextureFormat_ETC2RGBA8UnormSrgb:
            s->Append("ETC2RGBA8UnormSrgb");
            return {true};
        case WGPUTextureFormat_EACR11Unorm:
            s->Append("EACR11Unorm");
            return {true};
        case WGPUTextureFormat_EACR11Snorm:
            s->Append("EACR11Snorm");
            return {true};
        case WGPUTextureFormat_EACRG11Unorm:
            s->Append("EACRG11Unorm");
            return {true};
        case WGPUTextureFormat_EACRG11Snorm:
            s->Append("EACRG11Snorm");
            return {true};
        case WGPUTextureFormat_ASTC4x4Unorm:
            s->Append("ASTC4x4Unorm");
            return {true};
        case WGPUTextureFormat_ASTC4x4UnormSrgb:
            s->Append("ASTC4x4UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC5x4Unorm:
            s->Append("ASTC5x4Unorm");
            return {true};
        case WGPUTextureFormat_ASTC5x4UnormSrgb:
            s->Append("ASTC5x4UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC5x5Unorm:
            s->Append("ASTC5x5Unorm");
            return {true};
        case WGPUTextureFormat_ASTC5x5UnormSrgb:
            s->Append("ASTC5x5UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC6x5Unorm:
            s->Append("ASTC6x5Unorm");
            return {true};
        case WGPUTextureFormat_ASTC6x5UnormSrgb:
            s->Append("ASTC6x5UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC6x6Unorm:
            s->Append("ASTC6x6Unorm");
            return {true};
        case WGPUTextureFormat_ASTC6x6UnormSrgb:
            s->Append("ASTC6x6UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC8x5Unorm:
            s->Append("ASTC8x5Unorm");
            return {true};
        case WGPUTextureFormat_ASTC8x5UnormSrgb:
            s->Append("ASTC8x5UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC8x6Unorm:
            s->Append("ASTC8x6Unorm");
            return {true};
        case WGPUTextureFormat_ASTC8x6UnormSrgb:
            s->Append("ASTC8x6UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC8x8Unorm:
            s->Append("ASTC8x8Unorm");
            return {true};
        case WGPUTextureFormat_ASTC8x8UnormSrgb:
            s->Append("ASTC8x8UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC10x5Unorm:
            s->Append("ASTC10x5Unorm");
            return {true};
        case WGPUTextureFormat_ASTC10x5UnormSrgb:
            s->Append("ASTC10x5UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC10x6Unorm:
            s->Append("ASTC10x6Unorm");
            return {true};
        case WGPUTextureFormat_ASTC10x6UnormSrgb:
            s->Append("ASTC10x6UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC10x8Unorm:
            s->Append("ASTC10x8Unorm");
            return {true};
        case WGPUTextureFormat_ASTC10x8UnormSrgb:
            s->Append("ASTC10x8UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC10x10Unorm:
            s->Append("ASTC10x10Unorm");
            return {true};
        case WGPUTextureFormat_ASTC10x10UnormSrgb:
            s->Append("ASTC10x10UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC12x10Unorm:
            s->Append("ASTC12x10Unorm");
            return {true};
        case WGPUTextureFormat_ASTC12x10UnormSrgb:
            s->Append("ASTC12x10UnormSrgb");
            return {true};
        case WGPUTextureFormat_ASTC12x12Unorm:
            s->Append("ASTC12x12Unorm");
            return {true};
        case WGPUTextureFormat_ASTC12x12UnormSrgb:
            s->Append("ASTC12x12UnormSrgb");
            return {true};
        case WGPUTextureFormat_R8BG8Biplanar420Unorm:
            s->Append("R8BG8Biplanar420Unorm");
            return {true};
        case WGPUTextureFormat_R10X6BG10X6Biplanar420Unorm:
            s->Append("R10X6BG10X6Biplanar420Unorm");
            return {true};
        case WGPUTextureFormat_R8BG8A8Triplanar420Unorm:
            s->Append("R8BG8A8Triplanar420Unorm");
            return {true};
        case WGPUTextureFormat_R8BG8Biplanar422Unorm:
            s->Append("R8BG8Biplanar422Unorm");
            return {true};
        case WGPUTextureFormat_R8BG8Biplanar444Unorm:
            s->Append("R8BG8Biplanar444Unorm");
            return {true};
        case WGPUTextureFormat_R10X6BG10X6Biplanar422Unorm:
            s->Append("R10X6BG10X6Biplanar422Unorm");
            return {true};
        case WGPUTextureFormat_R10X6BG10X6Biplanar444Unorm:
            s->Append("R10X6BG10X6Biplanar444Unorm");
            return {true};
        case WGPUTextureFormat_OpaqueYCbCrAndroid:
            s->Append("OpaqueYCbCrAndroid");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUTextureFormat>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(TextureSampleType value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("TextureSampleType::");
        switch (WGPUTextureSampleType(value)) {
        case WGPUTextureSampleType_BindingNotUsed:
            s->Append("BindingNotUsed");
            return {true};
        case WGPUTextureSampleType_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUTextureSampleType_Float:
            s->Append("Float");
            return {true};
        case WGPUTextureSampleType_UnfilterableFloat:
            s->Append("UnfilterableFloat");
            return {true};
        case WGPUTextureSampleType_Depth:
            s->Append("Depth");
            return {true};
        case WGPUTextureSampleType_Sint:
            s->Append("Sint");
            return {true};
        case WGPUTextureSampleType_Uint:
            s->Append("Uint");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUTextureSampleType>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(TextureViewDimension value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("TextureViewDimension::");
        switch (WGPUTextureViewDimension(value)) {
        case WGPUTextureViewDimension_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUTextureViewDimension_1D:
            s->Append("e1D");
            return {true};
        case WGPUTextureViewDimension_2D:
            s->Append("e2D");
            return {true};
        case WGPUTextureViewDimension_2DArray:
            s->Append("e2DArray");
            return {true};
        case WGPUTextureViewDimension_Cube:
            s->Append("Cube");
            return {true};
        case WGPUTextureViewDimension_CubeArray:
            s->Append("CubeArray");
            return {true};
        case WGPUTextureViewDimension_3D:
            s->Append("e3D");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUTextureViewDimension>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(ToneMappingMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("ToneMappingMode::");
        switch (WGPUToneMappingMode(value)) {
        case WGPUToneMappingMode_Standard:
            s->Append("Standard");
            return {true};
        case WGPUToneMappingMode_Extended:
            s->Append("Extended");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUToneMappingMode>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(VertexFormat value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("VertexFormat::");
        switch (WGPUVertexFormat(value)) {
        case WGPUVertexFormat_Uint8:
            s->Append("Uint8");
            return {true};
        case WGPUVertexFormat_Uint8x2:
            s->Append("Uint8x2");
            return {true};
        case WGPUVertexFormat_Uint8x4:
            s->Append("Uint8x4");
            return {true};
        case WGPUVertexFormat_Sint8:
            s->Append("Sint8");
            return {true};
        case WGPUVertexFormat_Sint8x2:
            s->Append("Sint8x2");
            return {true};
        case WGPUVertexFormat_Sint8x4:
            s->Append("Sint8x4");
            return {true};
        case WGPUVertexFormat_Unorm8:
            s->Append("Unorm8");
            return {true};
        case WGPUVertexFormat_Unorm8x2:
            s->Append("Unorm8x2");
            return {true};
        case WGPUVertexFormat_Unorm8x4:
            s->Append("Unorm8x4");
            return {true};
        case WGPUVertexFormat_Snorm8:
            s->Append("Snorm8");
            return {true};
        case WGPUVertexFormat_Snorm8x2:
            s->Append("Snorm8x2");
            return {true};
        case WGPUVertexFormat_Snorm8x4:
            s->Append("Snorm8x4");
            return {true};
        case WGPUVertexFormat_Uint16:
            s->Append("Uint16");
            return {true};
        case WGPUVertexFormat_Uint16x2:
            s->Append("Uint16x2");
            return {true};
        case WGPUVertexFormat_Uint16x4:
            s->Append("Uint16x4");
            return {true};
        case WGPUVertexFormat_Sint16:
            s->Append("Sint16");
            return {true};
        case WGPUVertexFormat_Sint16x2:
            s->Append("Sint16x2");
            return {true};
        case WGPUVertexFormat_Sint16x4:
            s->Append("Sint16x4");
            return {true};
        case WGPUVertexFormat_Unorm16:
            s->Append("Unorm16");
            return {true};
        case WGPUVertexFormat_Unorm16x2:
            s->Append("Unorm16x2");
            return {true};
        case WGPUVertexFormat_Unorm16x4:
            s->Append("Unorm16x4");
            return {true};
        case WGPUVertexFormat_Snorm16:
            s->Append("Snorm16");
            return {true};
        case WGPUVertexFormat_Snorm16x2:
            s->Append("Snorm16x2");
            return {true};
        case WGPUVertexFormat_Snorm16x4:
            s->Append("Snorm16x4");
            return {true};
        case WGPUVertexFormat_Float16:
            s->Append("Float16");
            return {true};
        case WGPUVertexFormat_Float16x2:
            s->Append("Float16x2");
            return {true};
        case WGPUVertexFormat_Float16x4:
            s->Append("Float16x4");
            return {true};
        case WGPUVertexFormat_Float32:
            s->Append("Float32");
            return {true};
        case WGPUVertexFormat_Float32x2:
            s->Append("Float32x2");
            return {true};
        case WGPUVertexFormat_Float32x3:
            s->Append("Float32x3");
            return {true};
        case WGPUVertexFormat_Float32x4:
            s->Append("Float32x4");
            return {true};
        case WGPUVertexFormat_Uint32:
            s->Append("Uint32");
            return {true};
        case WGPUVertexFormat_Uint32x2:
            s->Append("Uint32x2");
            return {true};
        case WGPUVertexFormat_Uint32x3:
            s->Append("Uint32x3");
            return {true};
        case WGPUVertexFormat_Uint32x4:
            s->Append("Uint32x4");
            return {true};
        case WGPUVertexFormat_Sint32:
            s->Append("Sint32");
            return {true};
        case WGPUVertexFormat_Sint32x2:
            s->Append("Sint32x2");
            return {true};
        case WGPUVertexFormat_Sint32x3:
            s->Append("Sint32x3");
            return {true};
        case WGPUVertexFormat_Sint32x4:
            s->Append("Sint32x4");
            return {true};
        case WGPUVertexFormat_Unorm10_10_10_2:
            s->Append("Unorm10_10_10_2");
            return {true};
        case WGPUVertexFormat_Unorm8x4BGRA:
            s->Append("Unorm8x4BGRA");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUVertexFormat>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(VertexStepMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("VertexStepMode::");
        switch (WGPUVertexStepMode(value)) {
        case WGPUVertexStepMode_Undefined:
            s->Append("Undefined");
            return {true};
        case WGPUVertexStepMode_Vertex:
            s->Append("Vertex");
            return {true};
        case WGPUVertexStepMode_Instance:
            s->Append("Instance");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUVertexStepMode>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(WaitStatus value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("WaitStatus::");
        switch (WGPUWaitStatus(value)) {
        case WGPUWaitStatus_Success:
            s->Append("Success");
            return {true};
        case WGPUWaitStatus_TimedOut:
            s->Append("TimedOut");
            return {true};
        case WGPUWaitStatus_Error:
            s->Append("Error");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUWaitStatus>(value)));
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(WGSLLanguageFeatureName value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("WGSLLanguageFeatureName::");
        switch (WGPUWGSLLanguageFeatureName(value)) {
        case WGPUWGSLLanguageFeatureName_ReadonlyAndReadwriteStorageTextures:
            s->Append("ReadonlyAndReadwriteStorageTextures");
            return {true};
        case WGPUWGSLLanguageFeatureName_Packed4x8IntegerDotProduct:
            s->Append("Packed4x8IntegerDotProduct");
            return {true};
        case WGPUWGSLLanguageFeatureName_UnrestrictedPointerParameters:
            s->Append("UnrestrictedPointerParameters");
            return {true};
        case WGPUWGSLLanguageFeatureName_PointerCompositeAccess:
            s->Append("PointerCompositeAccess");
            return {true};
        case WGPUWGSLLanguageFeatureName_UniformBufferStandardLayout:
            s->Append("UniformBufferStandardLayout");
            return {true};
        case WGPUWGSLLanguageFeatureName_SubgroupId:
            s->Append("SubgroupId");
            return {true};
        case WGPUWGSLLanguageFeatureName_TextureAndSamplerLet:
            s->Append("TextureAndSamplerLet");
            return {true};
        case WGPUWGSLLanguageFeatureName_SubgroupUniformity:
            s->Append("SubgroupUniformity");
            return {true};
        case WGPUWGSLLanguageFeatureName_TextureFormatsTier1:
            s->Append("TextureFormatsTier1");
            return {true};
        case WGPUWGSLLanguageFeatureName_ChromiumTestingUnimplemented:
            s->Append("ChromiumTestingUnimplemented");
            return {true};
        case WGPUWGSLLanguageFeatureName_ChromiumTestingUnsafeExperimental:
            s->Append("ChromiumTestingUnsafeExperimental");
            return {true};
        case WGPUWGSLLanguageFeatureName_ChromiumTestingExperimental:
            s->Append("ChromiumTestingExperimental");
            return {true};
        case WGPUWGSLLanguageFeatureName_ChromiumTestingShippedWithKillswitch:
            s->Append("ChromiumTestingShippedWithKillswitch");
            return {true};
        case WGPUWGSLLanguageFeatureName_ChromiumTestingShipped:
            s->Append("ChromiumTestingShipped");
            return {true};
        case WGPUWGSLLanguageFeatureName_SizedBindingArray:
            s->Append("SizedBindingArray");
            return {true};
        case WGPUWGSLLanguageFeatureName_TexelBuffers:
            s->Append("TexelBuffers");
            return {true};
        case WGPUWGSLLanguageFeatureName_ChromiumPrint:
            s->Append("ChromiumPrint");
            return {true};
        case WGPUWGSLLanguageFeatureName_FragmentDepth:
            s->Append("FragmentDepth");
            return {true};
        case WGPUWGSLLanguageFeatureName_ImmediateAddressSpace:
            s->Append("ImmediateAddressSpace");
            return {true};
        case WGPUWGSLLanguageFeatureName_BufferView:
            s->Append("BufferView");
            return {true};
        case WGPUWGSLLanguageFeatureName_FilteringParameters:
            s->Append("FilteringParameters");
            return {true};
        case WGPUWGSLLanguageFeatureName_SwizzleAssignment:
            s->Append("SwizzleAssignment");
            return {true};
        case WGPUWGSLLanguageFeatureName_LinearIndexing:
            s->Append("LinearIndexing");
            return {true};
        default:
            break;
        }
    }
    s->Append(absl::StrFormat("%u", static_cast<WGPUWGSLLanguageFeatureName>(value)));
    return {true};
}

    //
    // Bitmasks
    //

absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(BufferUsage value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("BufferUsage::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & BufferUsage::MapRead) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("MapRead");
            value &= ~BufferUsage::MapRead;
        }
        if (value & BufferUsage::MapWrite) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("MapWrite");
            value &= ~BufferUsage::MapWrite;
        }
        if (value & BufferUsage::CopySrc) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("CopySrc");
            value &= ~BufferUsage::CopySrc;
        }
        if (value & BufferUsage::CopyDst) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("CopyDst");
            value &= ~BufferUsage::CopyDst;
        }
        if (value & BufferUsage::Index) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Index");
            value &= ~BufferUsage::Index;
        }
        if (value & BufferUsage::Vertex) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Vertex");
            value &= ~BufferUsage::Vertex;
        }
        if (value & BufferUsage::Uniform) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Uniform");
            value &= ~BufferUsage::Uniform;
        }
        if (value & BufferUsage::Storage) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Storage");
            value &= ~BufferUsage::Storage;
        }
        if (value & BufferUsage::Indirect) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Indirect");
            value &= ~BufferUsage::Indirect;
        }
        if (value & BufferUsage::QueryResolve) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("QueryResolve");
            value &= ~BufferUsage::QueryResolve;
        }
        if (value & BufferUsage::TexelBuffer) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("TexelBuffer");
            value &= ~BufferUsage::TexelBuffer;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("BufferUsage::%x", static_cast<typename std::underlying_type<BufferUsage>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }
    } else {
        s->Append(absl::StrFormat("%u", static_cast<typename std::underlying_type<BufferUsage>::type>(value)));
    }
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(ColorWriteMask value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("ColorWriteMask::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & ColorWriteMask::Red) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Red");
            value &= ~ColorWriteMask::Red;
        }
        if (value & ColorWriteMask::Green) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Green");
            value &= ~ColorWriteMask::Green;
        }
        if (value & ColorWriteMask::Blue) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Blue");
            value &= ~ColorWriteMask::Blue;
        }
        if (value & ColorWriteMask::Alpha) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Alpha");
            value &= ~ColorWriteMask::Alpha;
        }
        if (value & ColorWriteMask::All) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("All");
            value &= ~ColorWriteMask::All;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("ColorWriteMask::%x", static_cast<typename std::underlying_type<ColorWriteMask>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }
    } else {
        s->Append(absl::StrFormat("%u", static_cast<typename std::underlying_type<ColorWriteMask>::type>(value)));
    }
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(HeapProperty value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("HeapProperty::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & HeapProperty::DeviceLocal) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("DeviceLocal");
            value &= ~HeapProperty::DeviceLocal;
        }
        if (value & HeapProperty::HostVisible) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("HostVisible");
            value &= ~HeapProperty::HostVisible;
        }
        if (value & HeapProperty::HostCoherent) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("HostCoherent");
            value &= ~HeapProperty::HostCoherent;
        }
        if (value & HeapProperty::HostUncached) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("HostUncached");
            value &= ~HeapProperty::HostUncached;
        }
        if (value & HeapProperty::HostCached) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("HostCached");
            value &= ~HeapProperty::HostCached;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("HeapProperty::%x", static_cast<typename std::underlying_type<HeapProperty>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }
    } else {
        s->Append(absl::StrFormat("%u", static_cast<typename std::underlying_type<HeapProperty>::type>(value)));
    }
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(MapMode value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("MapMode::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & MapMode::Read) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Read");
            value &= ~MapMode::Read;
        }
        if (value & MapMode::Write) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Write");
            value &= ~MapMode::Write;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("MapMode::%x", static_cast<typename std::underlying_type<MapMode>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }
    } else {
        s->Append(absl::StrFormat("%u", static_cast<typename std::underlying_type<MapMode>::type>(value)));
    }
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(ShaderStage value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("ShaderStage::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & ShaderStage::Vertex) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Vertex");
            value &= ~ShaderStage::Vertex;
        }
        if (value & ShaderStage::Fragment) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Fragment");
            value &= ~ShaderStage::Fragment;
        }
        if (value & ShaderStage::Compute) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("Compute");
            value &= ~ShaderStage::Compute;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("ShaderStage::%x", static_cast<typename std::underlying_type<ShaderStage>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }
    } else {
        s->Append(absl::StrFormat("%u", static_cast<typename std::underlying_type<ShaderStage>::type>(value)));
    }
    return {true};
}
absl::FormatConvertResult<absl::FormatConversionCharSet::kString|absl::FormatConversionCharSet::kIntegral>
AbslFormatConvert(TextureUsage value,
                  const absl::FormatConversionSpec& spec,
                  absl::FormatSink* s) {
    if (spec.conversion_char() == absl::FormatConversionChar::s) {
        s->Append("TextureUsage::");
        if (!static_cast<bool>(value)) {
            // 0 is often explicitly declared as None.
            s->Append("None");
            return {true};
        }

        bool moreThanOneBit = !HasZeroOrOneBits(value);
        if (moreThanOneBit) {
            s->Append("(");
        }

        bool first = true;
        if (value & TextureUsage::CopySrc) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("CopySrc");
            value &= ~TextureUsage::CopySrc;
        }
        if (value & TextureUsage::CopyDst) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("CopyDst");
            value &= ~TextureUsage::CopyDst;
        }
        if (value & TextureUsage::TextureBinding) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("TextureBinding");
            value &= ~TextureUsage::TextureBinding;
        }
        if (value & TextureUsage::StorageBinding) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("StorageBinding");
            value &= ~TextureUsage::StorageBinding;
        }
        if (value & TextureUsage::RenderAttachment) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("RenderAttachment");
            value &= ~TextureUsage::RenderAttachment;
        }
        if (value & TextureUsage::TransientAttachment) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("TransientAttachment");
            value &= ~TextureUsage::TransientAttachment;
        }
        if (value & TextureUsage::StorageAttachment) {
            if (!first) {
                s->Append("|");
            }
            first = false;
            s->Append("StorageAttachment");
            value &= ~TextureUsage::StorageAttachment;
        }

        if (static_cast<bool>(value)) {
            if (!first) {
                s->Append("|");
            }
            s->Append(absl::StrFormat("TextureUsage::%x", static_cast<typename std::underlying_type<TextureUsage>::type>(value)));
        }

        if (moreThanOneBit) {
            s->Append(")");
        }
    } else {
        s->Append(absl::StrFormat("%u", static_cast<typename std::underlying_type<TextureUsage>::type>(value)));
    }
    return {true};
}

}  // namespace wgpu
