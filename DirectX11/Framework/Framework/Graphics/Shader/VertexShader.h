#pragma once

#include <vector>
#include <memory>
#include <d3d11.h>
#include "Framework/Graphics/Shader/ShaderBase.h"
#include "Framework/Graphics/Shader/VertexShaderData.h"

namespace Framework {
namespace Graphics {
class GraphicsDeviceManager;

/**
* @class VertexShader
* @brief 頂点シェーダ
*/
class VertexShader : public ShaderBase {
public:
    /**
    * @brief コンストラクタ
    * @param filename シェーダファイル名
    */
    VertexShader(const std::string& name);
    /**
    * @brief コンストラクタ
    * @param filename シェーダファイル名
    */
    VertexShader(const std::string& name, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputLayouts);
    /**
    * @brief デストラクタ
    */
    ~VertexShader();
    /**
    * @brief 頂点シェーダのセット
    */
    void set() override;
private:
    /**
    * @brief 頂点シェーダの作成
    * @param filename シェーダファイル名
    */
    void create(const std::string& name);
private:
    std::unique_ptr<VertexShaderData> mShaderData; //!< シェーダーのデータ
};
} //Graphics 
} //Framework 
