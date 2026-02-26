
#include "dawn/native/ObjectType_autogen.h"

namespace dawn::native {

    const char* ObjectTypeAsString(ObjectType type) {
        switch (type) {
            case ObjectType::Adapter:
                return "Adapter";
            case ObjectType::BindGroup:
                return "BindGroup";
            case ObjectType::BindGroupLayout:
                return "BindGroupLayout";
            case ObjectType::Buffer:
                return "Buffer";
            case ObjectType::CommandBuffer:
                return "CommandBuffer";
            case ObjectType::CommandEncoder:
                return "CommandEncoder";
            case ObjectType::ComputePipeline:
                return "ComputePipeline";
            case ObjectType::Device:
                return "Device";
            case ObjectType::ExternalTexture:
                return "ExternalTexture";
            case ObjectType::Instance:
                return "Instance";
            case ObjectType::PipelineLayout:
                return "PipelineLayout";
            case ObjectType::QuerySet:
                return "QuerySet";
            case ObjectType::Queue:
                return "Queue";
            case ObjectType::RenderBundle:
                return "RenderBundle";
            case ObjectType::RenderPipeline:
                return "RenderPipeline";
            case ObjectType::ResourceTable:
                return "ResourceTable";
            case ObjectType::Sampler:
                return "Sampler";
            case ObjectType::ShaderModule:
                return "ShaderModule";
            case ObjectType::SharedBufferMemory:
                return "SharedBufferMemory";
            case ObjectType::SharedFence:
                return "SharedFence";
            case ObjectType::SharedTextureMemory:
                return "SharedTextureMemory";
            case ObjectType::Surface:
                return "Surface";
            case ObjectType::TexelBufferView:
                return "TexelBufferView";
            case ObjectType::Texture:
                return "Texture";
            case ObjectType::TextureView:
                return "TextureView";
            case ObjectType::ComputePassEncoder:
                return "ComputePassEncoder";
            case ObjectType::RenderBundleEncoder:
                return "RenderBundleEncoder";
            case ObjectType::RenderPassEncoder:
                return "RenderPassEncoder";
                case ObjectType::BindGroupLayoutInternal:
                    return "BindGroupLayoutInternal";
            default:
                DAWN_UNREACHABLE();
        }
    }

} // namespace dawn::native
