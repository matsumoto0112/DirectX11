#pragma once

#include <memory>
#include "Graphics/Shader/PixelShader.h"
#include "Graphics/Shader/VertexShader.h"

namespace Framework {
namespace Graphics {

class Effect {
public:
    Effect(std::shared_ptr<VertexShader> vertexShader,
        std::shared_ptr<PixelShader> pixelShader);
    ~Effect();
    void set();
private:
    std::shared_ptr<VertexShader> mVertexShader;
    std::shared_ptr<PixelShader> mPixelShader;
};

} //Graphics 
} //Framework 