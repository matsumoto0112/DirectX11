#include "LoadResourceList.h"

namespace Framework {
namespace Utility {

using namespace Define;
#define REGISTER_LIST(type,path) { ##type , path }

const std::unordered_map<ModelType, std::string> LoadResourceList::MODEL_LIST =
{
    REGISTER_LIST(ModelType::Plane, "stage/Plane.fbx"),
    REGISTER_LIST(ModelType::Wall ,"stage/wall.fbx"),
    REGISTER_LIST(ModelType::Player , "player/player.fbx"),
    REGISTER_LIST(ModelType::Bullet , "bullet/bullet.fbx"),
    REGISTER_LIST(ModelType::Enemy , "enemy/enemy.fbx"),
    REGISTER_LIST(ModelType::Item , "item/item.fbx"),
};

const std::unordered_map<PixelShaderType, std::string> LoadResourceList::PIXEL_SHADER_LIST =
{
    REGISTER_LIST(PixelShaderType::Texture2D, "2D/Texture2D_PS"),
    REGISTER_LIST(PixelShaderType::Model, "Model/Model_PS"),
    REGISTER_LIST(PixelShaderType::Model_NoTexture, "Model/Model_NoTexture_PS"),
    REGISTER_LIST(PixelShaderType::Model_Lighting, "Model/Model_Lighting_PS"),
    REGISTER_LIST(PixelShaderType::Model_Diffuse, "Model/Model_Diffuse_PS"),
    REGISTER_LIST(PixelShaderType::Model_Diffuse_Lighting, "Model/Model_Diffuse_Lighting_PS"),
    REGISTER_LIST(PixelShaderType::Output_Z, "Model/Output_Z_PS"),
    REGISTER_LIST(PixelShaderType::Model_Diffuse_Split4Color, "Model/Model_Diffuse_Split4Color_PS"),
    REGISTER_LIST(PixelShaderType::Output_Color, "3D/Output_Color_PS"),
    REGISTER_LIST(PixelShaderType::Texture2D_Inversion, "2D/Texture2D_Inversion_PS"),
    REGISTER_LIST(PixelShaderType::Model_Shadow_Diffuse, "model/Model_Shadow_Diffuse_PS"),
    REGISTER_LIST(PixelShaderType::Model_Shadow_Color, "model/Model_Shadow_Color_PS"),
};

const std::unordered_map<TextureType, std::string> LoadResourceList::TEXTURE_LIST =
{
    REGISTER_LIST(TextureType::Smoke ,"smoke.png"),
    REGISTER_LIST(TextureType::Circle ,"circle.png"),
};

const std::unordered_map<VertexShaderType, std::string> LoadResourceList::VERTEX_SHADER_LIST =
{
    REGISTER_LIST(VertexShaderType::Texture2D ,"2D/Texture2D_VS"),
    REGISTER_LIST(VertexShaderType::Model, "Model/Model_VS"),
    REGISTER_LIST(VertexShaderType::Model_Lighting ,"Model/Model_Lighting_VS"),
    REGISTER_LIST(VertexShaderType::Output_Z ,"Model/Output_Z_VS"),
    REGISTER_LIST(VertexShaderType::Model_Shadow,"Model/Model_Shadow_VS"),
    REGISTER_LIST(VertexShaderType::Only_Position,"3D/Only_Position_VS"),
    REGISTER_LIST(VertexShaderType::Model_Shadow_Diffuse,"model/Model_Shadow_Diffuse_VS"),
};

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
