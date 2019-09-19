#include "GPUParticle.h"

namespace Framework {
namespace Graphics {

GPUParticle::GPUParticle(UINT maxParticleNum,
    std::shared_ptr<Texture> texture,
    std::shared_ptr<ComputeShader> cs,
    std::shared_ptr<VertexShader> vs,
    std::shared_ptr<PixelShader> ps,
    std::shared_ptr<GeometoryShader> gs)
    :mMaxParticleNum(maxParticleNum),
    mTexture(texture),
    mComputeShader(cs),
    mVertexShader(vs),
    mPixelShader(ps),
    mGeometoryShader(gs) {}


GPUParticle::~GPUParticle() {}

void GPUParticle::simulate() {
    mComputeShader->set();
}

void GPUParticle::draw() {
    mTexture->setData(Graphics::ShaderInputType::Pixel, 0);
    mComputeShader->setToVertexBuffer();
    mVertexShader->set();
    mPixelShader->set();
    mGeometoryShader->set();
    Utility::getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    Utility::getContext()->Draw(mMaxParticleNum, 0);

    mComputeShader->clearVertexBuffer();
}

} //Graphics 
} //Framework 
