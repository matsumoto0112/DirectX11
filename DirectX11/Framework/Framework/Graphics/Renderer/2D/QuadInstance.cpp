#include "QuadInstance.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/Renderer/RendererCommonBufferStorage.h"

namespace {
std::unique_ptr<Framework::Graphics::VertexAndIndexBuffer> createBuffer() {
    std::vector<Framework::Graphics::BaseVertex2D> vertices
    {
        {{0.0f,0.0f,0.0f,1.0f},{0.0f,0.0f}},
        {{1.0f,0.0f,0.0f,1.0f},{1.0f,0.0f}},
        {{1.0f,1.0f,0.0f,1.0f},{1.0f,1.0f}},
        {{0.0f,1.0f,0.0f,1.0f},{0.0f,1.0f}},
    };
    std::vector<UINT> indices{ 0,1,2,0,2,3 };
    return std::make_unique<Framework::Graphics::VertexAndIndexBuffer>(vertices, indices, Framework::Graphics::PrimitiveTopology::TriangleList);
}
}
namespace Framework {
namespace Graphics {

QuadInstance::QuadInstance()
    :mTransform(Math::Vector2::ZERO, Math::Vector2(1.0f, 1.0f), 0.0f),
    mBuffer(nullptr) {
    RendererCommonBufferStorage& storage = RendererCommonBufferStorage::getInstance();
    //�o�b�t�@�����o�^�Ȃ�쐬���ēo�^
    if (!storage.isRegistered(RendererInstanceType::Quad2D)) {
        storage.registerBuffer(RendererInstanceType::Quad2D, createBuffer());
    }
    mBuffer = storage.getBuffer(RendererInstanceType::Quad2D);
}
QuadInstance::~QuadInstance() {}

void QuadInstance::render() {
    mBuffer->render();
}

} //Graphics 
} //Framework