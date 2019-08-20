#include "VertexAndIndexBuffer.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"

namespace Framework {
namespace Graphics {

VertexAndIndexBuffer::~VertexAndIndexBuffer() {}

void VertexAndIndexBuffer::render() {
    mVertexBuffer->setData();
    mIndexBuffer->setData();
    mIndexBuffer->drawCall();
}

} //Graphics 
} //Framework 