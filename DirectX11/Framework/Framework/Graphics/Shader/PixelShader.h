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
    * @param filepath シェーダファイル名
    */
    PixelShader(const std::string& filepath);
    /**
    * @brief デストラクタ
    */
    ~PixelShader();
    /**
    * @brief ピクセルシェーダのセット
    */
    void set();
private:
    ComPtr<ID3D11PixelShader> mPixelShader; //!< ピクセルシェーダ
};

} //Graphics 
} //Framework 
