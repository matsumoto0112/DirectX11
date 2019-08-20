#pragma once
#include "Define/Resource/PixelShader.h"
#include "Graphics/Shader/PixelShader.h"
#include "Utility/Resource/AbstractResourceStorage.h"

namespace Framework {

namespace Utility {

class PixelShaderResourceStorage : public AbstractResourceStorage<Define::PixelShaderType, Graphics::PixelShader> {
public:
    PixelShaderResourceStorage();
    ~PixelShaderResourceStorage();
    virtual void importResource(Define::PixelShaderType type, const std::string& filepath) override;
};

} //Utility 
} //Framework 
