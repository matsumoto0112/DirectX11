#include "QuadInstance.h"
#include "Device/GameDevice.h"
#include "Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Graphics/Renderer/RendererCommonBufferStorage.h"

namespace {
std::unique_ptr<Framework::Graphics::VertexAndIndexBuffer> createBuffer() {
    std::vector<Framework::Graphics::BaseVertex2D> vertices
    {
        {{0.0f,0.0f,0.0f,1.0f},{0.0f,0.0f}},
        {{1.0f,0.0f,0.0f,1.0f},{1.0f,0.0f}},
        {{1.0f,1.0f,0.0f,1.0f},{1.0f,1.0f}},
        {{0.0f,1.0f,0.0f,1.0f},{0.0f,1.0f}},
    };
    std::vector<WORD> indices{ 0,1,2,0,2,3 };
    return std::make_unique<Framework::Graphics::VertexAndIndexBuffer>(vertices, indices, Framework::Graphics::PrimitiveTopology::TriangleList);
}
}
namespace Framework {
namespace Graphics {

QuadInstance::QuadInstance()
    :mTransform(Math::Vector2::ZERO, Math::Vector2(1.0f, 1.0f), 0.0f),
    mBuffer(nullptr) {
    RendererCommonBufferStorage& storage = RendererCommonBufferStorage::getInstance();
    //ƒoƒbƒtƒ@‚ª–¢“o˜^‚È‚çì¬‚µ‚Ä“o˜^
    if (!storage.isRegistered(RendererInstanceType::Quad2D)) {
        storage.registerBuffer(RendererInstanceType::Quad2D, createBuffer());
    }
    mBuffer = storage.getBuffer(RendererInstanceType::Quad2D);
}
QuadInstance::~QuadInstance() {}

void QuadInstance::render() {
    //Device::GameDevice::getInstance().getGraphicsDevice().getConstantBufferManager().setMatrix(
    //    ConstantBufferParameterType::World, mTransform.createSRTMatrix());
    mBuffer->render();
}

} //Graphics 
} //Framework