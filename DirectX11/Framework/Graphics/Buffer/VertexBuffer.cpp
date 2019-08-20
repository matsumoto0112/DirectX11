#include "VertexBuffer.h"

namespace Framework {
namespace Graphics {

VertexBuffer::~VertexBuffer() {}

void VertexBuffer::setData() {
    Utility::getContext()->IASetVertexBuffers(0, 1,
        mData->mBuffer.GetAddressOf(), &mData->mStride, &mData->mOffset);
}

} //Graphics 
} //Framework 