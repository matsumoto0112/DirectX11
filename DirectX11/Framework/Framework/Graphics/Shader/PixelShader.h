#pragma once

#include <string>
#include "Framework/Graphics/Shader/ShaderBase.h"
#include "Framework/Graphics/Shader/PixelShaderData.h"

namespace Framework {
namespace Graphics {
/**
* @class PixelShader
* @brief ピクセルシェーダ
*/
class PixelShader : public ShaderBase {
public:
    /**
    * @brief コンストラクタ
    * @param filename シェーダファイル名
    */
    PixelShader(const std::string& filename);
    /**
    * @brief デストラクタ
    */
    ~PixelShader();
    /**
    * @brief ピクセルシェーダのセット
    */
    void set();
private:
    /**
    * @brief ピクセルシェーダの作成
    * @param name シェーダファイル名
    */
    void create(const std::string& name);
private:
    std::unique_ptr<PixelShaderData> mShaderData; //!< シェーダーのデータ
};

} //Graphics 
} //Framework 
