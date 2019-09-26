#include "LoadResourceList.h"

namespace Framework {
namespace Utility {

using namespace Define;

const std::unordered_map<GeometoryShader, std::string> LoadResourceList::GEOMETORY_SHADER_LIST =
{
    { GeometoryShader::Cube_Particle,"Particle/CubeParticle_GS" },
    { GeometoryShader::Fall_Bounce_Rotate,"Particle/Fall_Bounce_Rotate_GS"},
    { GeometoryShader::Firework,"Particle/Firework_GS"},
    { GeometoryShader::Flash,"Particle/Flash_GS"},
    { GeometoryShader::SpotInstancer,"Particle/SpotInstancer_GS"},
};

const std::unordered_map<ModelType, std::string> LoadResourceList::MODEL_LIST =
{
    {ModelType::Plane, "stage/Plane.fbx"},
    {ModelType::Wall ,"stage/wall.fbx"},
    {ModelType::Player , "player/player.fbx"},
    {ModelType::Bullet , "bullet/bullet.fbx"},
    {ModelType::Enemy , "enemy/enemy.fbx"},
    {ModelType::Item , "item/item.fbx"},
};

const std::unordered_map<PixelShaderType, std::string> LoadResourceList::PIXEL_SHADER_LIST =
{
    {PixelShaderType::Texture2D, "2D/Texture2D_PS"},
    {PixelShaderType::Model, "Model/Model_PS"},
    {PixelShaderType::Model_NoTexture, "Model/Model_NoTexture_PS"},
    {PixelShaderType::Model_Lighting, "Model/Model_Lighting_PS"},
    {PixelShaderType::Model_Diffuse, "Model/Model_Diffuse_PS"},
    {PixelShaderType::Model_Diffuse_Lighting, "Model/Model_Diffuse_Lighting_PS"},
    {PixelShaderType::Output_Z, "Model/Output_Z_PS"},
    {PixelShaderType::Model_Diffuse_Split4Color, "Model/Model_Diffuse_Split4Color_PS"},
    {PixelShaderType::Output_Color, "3D/Output_Color_PS"},
    {PixelShaderType::Texture2D_Inversion, "2D/Texture2D_Inversion_PS"},
    {PixelShaderType::Model_Shadow_Diffuse, "model/Model_Shadow_Diffuse_PS"},
    {PixelShaderType::Model_Shadow_Color, "model/Model_Shadow_Color_PS"},
    {PixelShaderType::CubeParticle, "Particle/CubeParticle_PS"},
    {PixelShaderType::Flash, "Particle/Flash_PS"},
};

const std::unordered_map<TextureType, std::string> LoadResourceList::TEXTURE_LIST =
{
    {TextureType::Smoke ,"smoke.png"},
    {TextureType::Circle ,"circle.png"},
};

const std::unordered_map<VertexShaderType, std::string> LoadResourceList::VERTEX_SHADER_LIST =
{
    {VertexShaderType::NoAction,"2D/NoActionVS" },
    {VertexShaderType::Texture2D ,"2D/Texture2D_VS"},
    {VertexShaderType::Model, "Model/Model_VS"},
    {VertexShaderType::Model_Lighting ,"Model/Model_Lighting_VS"},
    {VertexShaderType::Output_Z ,"Model/Output_Z_VS"},
    {VertexShaderType::Model_Shadow,"Model/Model_Shadow_VS"},
    {VertexShaderType::Only_Position,"3D/Only_Position_VS"},
    {VertexShaderType::Model_Shadow_Diffuse,"Model/Model_Shadow_Diffuse_VS"},
    {VertexShaderType::Blackhole,"Particle/Blackhole_VS"},
    {VertexShaderType::Fall_Bounce_Rotate,"Particle/Fall_Bounce_Rotate_VS"},
    {VertexShaderType::Fall_Bounce,"Particle/Fall_Bounce_VS"},
    {VertexShaderType::Fall,"Particle/Fall_VS"},
    {VertexShaderType::Firework,"Particle/Firework_VS"},
    {VertexShaderType::Flash,"Particle/Flash_VS"},
    {VertexShaderType::SpotInstancer,"Particle/SpotInstancer_VS"},
    {VertexShaderType::Wormhole,"Particle/Wormhole_VS"},
};

const std::string LoadResourceList::getGeometoryShaderPath(Define::GeometoryShader type) {
    MY_ASSERTION(GEOMETORY_SHADER_LIST.find(type) != GEOMETORY_SHADER_LIST.end(),
        "未登録のジオメトリシェーダが呼ばれました。");
    return GEOMETORY_SHADER_LIST.at(type);
}

const std::string LoadResourceList::getModelPath(Define::ModelType type) {
    MY_ASSERTION(MODEL_LIST.find(type) != MODEL_LIST.end(),
        "未登録のモデルが呼ばれました。");
    return MODEL_LIST.at(type);
}

const std::string LoadResourceList::getPixelShaderPath(Define::PixelShaderType type) {
    MY_ASSERTION(PIXEL_SHADER_LIST.find(type) != PIXEL_SHADER_LIST.end(),
        "未登録のピクセルシェーダが呼ばれました。");
    return PIXEL_SHADER_LIST.at(type);
}

const std::string LoadResourceList::getTexturePath(Define::TextureType type) {
    MY_ASSERTION(TEXTURE_LIST.find(type) != TEXTURE_LIST.end(),
        "未登録のテクスチャが呼ばれました。");
    return TEXTURE_LIST.at(type);
}

const std::string LoadResourceList::getVertexShaderPath(Define::VertexShaderType type) {
    MY_ASSERTION(VERTEX_SHADER_LIST.find(type) != VERTEX_SHADER_LIST.end(),
        "未登録の頂点シェーダが呼ばれました。");
    return VERTEX_SHADER_LIST.at(type);
}

} //Utility 
} //Framework 
