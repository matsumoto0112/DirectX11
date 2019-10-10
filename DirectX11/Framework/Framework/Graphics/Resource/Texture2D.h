#pragma once
#include <d3d11.h>
#include "Framework/Utility/TypeDef.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Texture2D
* @brief テクスチャ2D管理
*/
class Texture2D {
public:
    /**
    * @brief コンストラクタ
    * @param texDesc テクスチャデスク
    */
    Texture2D(const D3D11_TEXTURE2D_DESC* texDesc);
    /**
    * @brief コンストラクタ
    * @param texture テクスチャ
    */
    Texture2D(ComPtr<ID3D11Texture2D> texture);
    /**
    * @brief デストラクタ
    */
    ~Texture2D();
    /**
    * @brief テクスチャを取得する
    */
    ComPtr<ID3D11Texture2D> getTexture() const { return mTexture2D; }
private:
    ComPtr<ID3D11Texture2D> mTexture2D; //!< テクスチャ2D
};

} //Graphics 
} //Framework 