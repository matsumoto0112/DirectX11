#include "VertexBuffer.h"

namespace Framework {
namespace Graphics {

VertexBuffer::~VertexBuffer() { }

void VertexBuffer::setData() {
    DX11InterfaceAccessor::getContext()->IASetVertexBuffers(0, 1,
        mBuffer.GetAddressOf(), &mStride, &mOffset);
}

} //Graphics 
} //Framework 