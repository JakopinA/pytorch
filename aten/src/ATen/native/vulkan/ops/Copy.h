#pragma once

#ifdef USE_VULKAN_API

#include <ATen/native/vulkan/ops/Common.h>

namespace at {
namespace native {
namespace vulkan {
namespace ops {

void transfer_cpu_to_vulkan(const Tensor&, vTensor&);

void transfer_vulkan_to_cpu(vTensor&, Tensor&);

void pack_cpu_to_vulkan(const Tensor& src, vTensor& dst);

void pack_vulkan_to_cpu(vTensor& src, Tensor& dst);

Tensor& copy_(Tensor& dst, const Tensor& src);

ops::vTensor to_vulkan(
    at::Tensor& src,
    const api::StorageType storage_type = api::StorageType::TEXTURE_3D);

at::Tensor from_vulkan(ops::vTensor& v_src);

//
// Utility functions for memcpy
//

template <typename T>
void memcpy_to_mapping_impl(const Tensor& src, api::MemoryMap& dst_mapping) {
  T* data_ptr = dst_mapping.template data<T>();
  memcpy(
      data_ptr,
      src.data_ptr<T>(),
      std::min(src.nbytes(), dst_mapping.nbytes()));
}

template <typename T>
void memcpy_from_mapping_impl(api::MemoryMap& src_mapping, Tensor& dst) {
  T* data_ptr = src_mapping.template data<T>();
  memcpy(
      dst.data_ptr<T>(),
      data_ptr,
      std::min(src_mapping.nbytes(), dst.nbytes()));
}

void memcpy_to_mapping(const Tensor& src, api::MemoryMap& dst_mapping);

void memcpy_from_mapping(api::MemoryMap& src_mapping, Tensor& dst);

} // namespace ops
} // namespace vulkan
} // namespace native
} // namespace at

#endif /* USE_VULKAN_API */
