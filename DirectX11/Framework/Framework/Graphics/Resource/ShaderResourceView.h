#pragma once

#include <memory>
#include <d3d11.h>
#include "Framework/Graphics/Resource/Texture2D.h"
#include "Framework/Graphics/Shader/ShaderInputType.h"

namespace Framework {
namespace Graphics {

/**
* @class ShaderResourceView
* @brief シェーダーリソースビュー管理
*/
class ShaderResourceView {
public:
    /**
    * @brief コンストラクタ
    * @param texture リソース元のテクスチャ
    * @param srvDesc シェーダーリソースビューデスク
    */
    ShaderResourceView(std::shared_ptr<Texture2D> texture, const D3D11_SHADER_RESOURCE_VIEW_DESC* srvDesc);
    /**
    * @brief デストラクタ
    */
    ~ShaderResourceView();
    /**
    * @brief コンテキストにデータをセットする
    */
    void set(ShaderInputType inputType, UINT registerNum);
    /**;
    * @brief シェーダーリソースビューを取得する
    */
    ComPtr<ID3D11ShaderResourceView> getShaderResourceView() const { return mShaderResourceView; }
private:
    ComPtr<ID3D11ShaderResourceView> mShaderResourceView; //!< シェーダーリソースビュー
};

} //Graphics 
} //Framework 
