#include "GPUParticle.h"
//#include "Framework/Graphics/DX11InterfaceAccessor.h"

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
    mGeometoryShader(gs) { }


GPUParticle::~GPUParticle() { }

void GPUParticle::simulate() {
    mComputeShader->set();
}

void GPUParticle::draw() {
    if (mTexture)
        mTexture->setData(Graphics::ShaderInputType::Pixel, 0);
    mComputeShader->setToVertexBuffer();
    mVertexShader->set();
    mPixelShader->set();
    mGeometoryShader->set();
    DX11InterfaceAccessor::getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    DX11InterfaceAccessor::getContext()->Draw(mMaxParticleNum, 0);

    mComputeShader->clearVertexBuffer();
}

} //Graphics 
} //Framework 
