#pragma once

#include <string>
#include "Framework/Graphics/Shader/ShaderBase.h"
#include "Framework/Graphics/Shader/ComputeShaderData.h"

namespace Framework {
namespace Graphics {
/**
* @class PixelShader
* @brief ピクセルシェーダ
*/
class ComputeShader : public ShaderBase {
public:
    /**
    * @brief コンストラクタ
    * @param filename シェーダファイル名
    */
    ComputeShader(const std::string& filename);
    /**
    * @brief デストラクタ
    */
    ~ComputeShader();
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
public:
    std::unique_ptr<ComputeShaderData> mShaderData; //!< シェーダーのデータ
};

} //Graphics 
} //Framework 
