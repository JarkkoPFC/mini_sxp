// Copyright 2026 The Dawn & Tint Authors
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

#ifndef SRC_VULKAN_UTILITY_VK_STRUCT_HELPER_HPP_
#define SRC_VULKAN_UTILITY_VK_STRUCT_HELPER_HPP_

#include <type_traits>
#include <vulkan/vulkan.h>

namespace vku {

template <typename T>
constexpr VkStructureType GetSType() {
    if constexpr (std::is_same_v<T, VkDescriptorSetLayoutBindingFlagsCreateInfo>) {
        return VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
    } else if constexpr (std::is_same_v<T, VkPipelineShaderStageRequiredSubgroupSizeCreateInfoEXT>) {
        return VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO_EXT;
    } else if constexpr (std::is_same_v<T, VkPipelineRasterizationDepthClipStateCreateInfoEXT>) {
        return VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT;
    } else if constexpr (std::is_same_v<T, VkPipelineRobustnessCreateInfo>) {
        return VK_STRUCTURE_TYPE_PIPELINE_ROBUSTNESS_CREATE_INFO;
    } else if constexpr (std::is_same_v<T, VkPipelineRenderingCreateInfoKHR>) {
        return VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
    } else {
        static_assert(sizeof(T) == 0, "vku::GetSType missing specialization for this Vulkan type");
        return VK_STRUCTURE_TYPE_APPLICATION_INFO;
    }
}

}  // namespace vku

#endif  // SRC_VULKAN_UTILITY_VK_STRUCT_HELPER_HPP_
