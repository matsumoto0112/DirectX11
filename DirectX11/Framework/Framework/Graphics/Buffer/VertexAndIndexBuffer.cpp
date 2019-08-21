#include "VertexAndIndexBuffer.h"
#include "Framework/Graphics/Buffer/VertexBuffer.h"
#include "Framework/Graphics/Buffer/IndexBuffer.h"

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