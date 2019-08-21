#include "ResourceInitializer.h"
#include "Framework/Define/Resource/PixelShader.h"
#include "Framework/Define/Resource/VertexShader.h"
#include "Framework/Utility/Resource/ResourceManager.h"

namespace Framework {

namespace Utility {

ResourceInitializeOnStart::ResourceInitializeOnStart(ResourceManager& resourceManager) {
    resourceManager.getVertexShader()->importResource(Define::VertexShaderType::Default2D, Define::VertexShaderName::DEFAULT_2D);
    resourceManager.getVertexShader()->importResource(Define::VertexShaderType::OnlyPosition, Define::VertexShaderName::ONLY_POSITION);
    resourceManager.getVertexShader()->importResource(Define::VertexShaderType::Default3D, Define::VertexShaderName::DEFAULT_3D);
    resourceManager.getVertexShader()->importResource(Define::VertexShaderType::Lighting, Define::VertexShaderName::MODEL_LIGHTING);
    resourceManager.getVertexShader()->importResource(Define::VertexShaderType::Model, Define::VertexShaderName::MODEL_NOLIGHTING);

    resourceManager.getPixelShader()->importResource(Define::PixelShaderType::Default2D, Define::PixelShaderName::DEFAULT_2D);
    resourceManager.getPixelShader()->importResource(Define::PixelShaderType::OnlyPosition, Define::PixelShaderName::ONLY_POSITION);
    resourceManager.getPixelShader()->importResource(Define::PixelShaderType::Model, Define::PixelShaderName::MODEL_NOLIGHTING);
    resourceManager.getPixelShader()->importResource(Define::PixelShaderType::ModelLighting, Define::PixelShaderName::MODEL_LIGHTING);
    resourceManager.getPixelShader()->importResource(Define::PixelShaderType::Blend, Define::PixelShaderName::CAMERA_BLEND);
    resourceManager.getPixelShader()->importResource(Define::PixelShaderType::NoTextureNoLighting, Define::PixelShaderName::MODEL_NOTEXTURE_NOLIGHTING);
}
} //Utility 
} //Framework 
