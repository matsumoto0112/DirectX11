#include "Effect.h"
#include "Framework/Utility/Wrap/DirectX.h"
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
    else Utility::getContext()->PSSetShader(nullptr, nullptr, 0);
}

} //Graphics 
} //Framework 