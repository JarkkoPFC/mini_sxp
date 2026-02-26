
#include "dawn/native/CacheKey.h"
#include "dawn/native/dawn_platform.h"
#include "dawn/native/wgpu_structs_autogen.h"

#include <cstring>

namespace dawn::native {




// Custom stream operator for special bool type that doesn't have the same size as C++'s bool.
template <>
void stream::Stream<wgpu::Bool>::Write(stream::Sink* sink, const wgpu::Bool& t) {
    StreamIn(sink, static_cast<bool>(t));
}

// Custom stream operator for StringView.
template <>
void stream::Stream<StringView>::Write(stream::Sink* sink, const StringView& t) {
    bool undefined = t.IsUndefined();
    std::string_view sv = t;
    StreamIn(sink, undefined, sv);
}


template <>
void stream::Stream<AdapterInfo>::Write(stream::Sink* sink, const AdapterInfo& t) {

    StreamIn(sink, t.vendor);

    StreamIn(sink, t.architecture);

    StreamIn(sink, t.device);

    StreamIn(sink, t.description);

    StreamIn(sink, t.backendType);

    StreamIn(sink, t.adapterType);

    StreamIn(sink, t.vendorID);

    StreamIn(sink, t.deviceID);

    StreamIn(sink, t.subgroupMinSize);

    StreamIn(sink, t.subgroupMaxSize);

}

template <>
void stream::Stream<DawnCacheDeviceDescriptor>::Write(stream::Sink* sink, const DawnCacheDeviceDescriptor& t) {

    StreamIn(sink, t.isolationKey);

}

template <>
MaybeError stream::Stream<Extent3D>::Read(stream::Source* source, Extent3D* t) {

    DAWN_TRY(StreamOut(source, &t->width));

    DAWN_TRY(StreamOut(source, &t->height));

    DAWN_TRY(StreamOut(source, &t->depthOrArrayLayers));

    return {};
}
template <>
void stream::Stream<Extent3D>::Write(stream::Sink* sink, const Extent3D& t) {

    StreamIn(sink, t.width);

    StreamIn(sink, t.height);

    StreamIn(sink, t.depthOrArrayLayers);

}

template <>
MaybeError stream::Stream<SubgroupMatrixConfig>::Read(stream::Source* source, SubgroupMatrixConfig* t) {

    DAWN_TRY(StreamOut(source, &t->componentType));

    DAWN_TRY(StreamOut(source, &t->resultComponentType));

    DAWN_TRY(StreamOut(source, &t->M));

    DAWN_TRY(StreamOut(source, &t->N));

    DAWN_TRY(StreamOut(source, &t->K));

    return {};
}
template <>
void stream::Stream<SubgroupMatrixConfig>::Write(stream::Sink* sink, const SubgroupMatrixConfig& t) {

    StreamIn(sink, t.componentType);

    StreamIn(sink, t.resultComponentType);

    StreamIn(sink, t.M);

    StreamIn(sink, t.N);

    StreamIn(sink, t.K);

}

} // namespace dawn::native
