#include "RendererCommonBufferStorage.h"
#include "Utility/STLExtend/ExtendUnorderedMap.h"

namespace Framework {
namespace Graphics {

RendererCommonBufferStorage::RendererCommonBufferStorage() {}

RendererCommonBufferStorage::~RendererCommonBufferStorage() {}

void RendererCommonBufferStorage::registerBuffer(RendererInstanceType type, std::shared_ptr<VertexAndIndexBuffer> buffer) {
    if (Utility::exist(mCommonBuffers, type))return;
    mCommonBuffers.emplace(type, buffer);
}

bool RendererCommonBufferStorage::isRegistered(RendererInstanceType type) const {
    return Utility::exist(mCommonBuffers, type);
}

void RendererCommonBufferStorage::clearBuffer() {
    mCommonBuffers.clear();
}

std::shared_ptr<VertexAndIndexBuffer> RendererCommonBufferStorage::getBuffer(RendererInstanceType type) {
    MY_ASSERTION(Utility::exist(mCommonBuffers, type), "未登録のバッファが呼ばれました");
    return mCommonBuffers.at(type);
}

} //Graphics 
} //Framework