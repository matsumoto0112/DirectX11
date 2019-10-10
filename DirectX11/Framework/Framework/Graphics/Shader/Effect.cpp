#include "Effect.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
namespace Framework {
namespace Graphics {

Effect::Effect(std::shared_ptr<VertexShader> vertexShader,
    std::shared_ptr<PixelShader> pixelShader)
    :mVertexShader(vertexShader), mPixelShader(pixelShader) { }

Effect::~Effect() { }

void Effect::set() {
    mVertexShader->set();
    if (mPixelShader)
        mPixelShader->set();
    else DX11InterfaceAccessor::getContext()->PSSetShader(nullptr, nullptr, 0);
}

} //Graphics 
} //Framework 