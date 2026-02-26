
#ifndef DAWNNATIVE_OBJECTTPYE_AUTOGEN_H_
#define DAWNNATIVE_OBJECTTPYE_AUTOGEN_H_

#include "dawn/common/ityp_array.h"

#include <cstdint>

namespace dawn::native {

    enum class ObjectType : uint32_t {
        Adapter,
        BindGroup,
        BindGroupLayout,
        Buffer,
        CommandBuffer,
        CommandEncoder,
        ComputePipeline,
        Device,
        ExternalTexture,
        Instance,
        PipelineLayout,
        QuerySet,
        Queue,
        RenderBundle,
        RenderPipeline,
        ResourceTable,
        Sampler,
        ShaderModule,
        SharedBufferMemory,
        SharedFence,
        SharedTextureMemory,
        Surface,
        TexelBufferView,
        Texture,
        TextureView,
        ComputePassEncoder,
        RenderBundleEncoder,
        RenderPassEncoder,

        // Additional internal object types. Keep kExtraObjectTypes in sync when updating.
        BindGroupLayoutInternal,
    };

    constexpr size_t kExtraObjectTypes = 1;

    template <typename T>
    using PerObjectType = ityp::array<ObjectType, T, 28 + kExtraObjectTypes>;

    const char* ObjectTypeAsString(ObjectType type);

} // namespace dawn::native


#endif  // DAWNNATIVE_OBJECTTPYE_AUTOGEN_H_
