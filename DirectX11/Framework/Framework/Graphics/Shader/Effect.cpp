#include "Effect.h"

namespace Framework {
namespace Graphics {

Effect::Effect(std::shared_ptr<VertexShader> vertexShader,
    std::shared_ptr<PixelShader> pixelShader)
    :mVertexShader(vertexShader), mPixelShader(pixelShader) {}

Effect::~Effect() {}

void Effect::set() {
    mVertexShader->set();
    mPixelShader->set();
}

} //Graphics 
} //Framework 