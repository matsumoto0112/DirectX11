#pragma once
#include "Framework/Define/Resource/PixelShader.h"
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Utility/Resource/AbstractResourceStorage.h"

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
