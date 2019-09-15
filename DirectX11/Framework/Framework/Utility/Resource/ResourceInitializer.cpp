#include "ResourceInitializer.h"
#include "Framework/Define/Resource/PixelShader.h"
#include "Framework/Define/Resource/VertexShader.h"
#include "Framework/Utility/Resource/ResourceManager.h"

namespace Framework {
namespace Utility {

ResourceInitializeOnStart::ResourceInitializeOnStart(ResourceManager& resourceManager) {
#define LOAD_VS(TYPE,NAME) resourceManager.getVertexShader()->importResource((TYPE), (NAME))
#define LOAD_PS(TYPE,NAME) resourceManager.getPixelShader()->importResource((TYPE), (NAME))

    LOAD_VS(Define::VertexShaderType::Texture2D, Define::VertexShaderName::TEXTURE2D);
    LOAD_VS(Define::VertexShaderType::Model_Lighting, Define::VertexShaderName::MODEL_LIGHTING);
    LOAD_VS(Define::VertexShaderType::Model, Define::VertexShaderName::MODEL);
    LOAD_VS(Define::VertexShaderType::Only_Position, Define::VertexShaderName::ONLY_POSITION);

    LOAD_PS(Define::PixelShaderType::Texture2D, Define::PixelShaderName::TEXTURE2D);
    LOAD_PS(Define::PixelShaderType::Model, Define::PixelShaderName::MODEL);
    LOAD_PS(Define::PixelShaderType::Model_NoTexture, Define::PixelShaderName::MODEL_NOTEXTURE);
    LOAD_PS(Define::PixelShaderType::Model_Lighting, Define::PixelShaderName::MODEL_LIGHTING);
    LOAD_PS(Define::PixelShaderType::OutPot_Color, Define::PixelShaderName::OUTPUT_COLOR);
}
} //Utility 
} //Framework 
