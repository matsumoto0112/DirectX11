#pragma once

#include <vector>
#include <d3d11.h>
#include "Framework/Graphics/Shader/ShaderBase.h"

namespace Framework {
namespace Graphics {

/**
* @class VertexShader
* @brief 頂点シェーダ
*/
class VertexShader : public ShaderBase {
public:
    /**
    * @brief コンストラクタ
    * @param filepath シェーダファイル名
    */
    VertexShader(const std::string& filepath);
    /**
    * @brief デストラクタ
    */
    ~VertexShader();
    /**
    * @brief 頂点シェーダのセット
    */
    void set() override;
private:
    ComPtr<ID3D11VertexShader> mVertexShader; //!< 頂点シェーダ
    ComPtr<ID3D11InputLayout> mInputLayout; //!< インプットレイアウト
};
} //Graphics 
} //Framework 
