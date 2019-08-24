#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include "Framework/Math/Vector2.h"

namespace Framework {
namespace Graphics {
class DirectX11GraphicsDevice;

/**
* @class TextureBuffer
* @brief テクスチャのバッファ管理
*/
class TextureBuffer {
    using TexPtr = Microsoft::WRL::ComPtr<ID3D11Texture2D>;
public:
    /**
    * @brief コンストラクタ
    * @param device DirectX11用グラフィックデバイス
    * @details デスクがなければバックバッファを使ってテクスチャを作る
    */
    TextureBuffer(DirectX11GraphicsDevice& device);
    /**
    * @brief コンストラクタ
    * @param desc テクスチャデスク
    */
    TextureBuffer(const D3D11_TEXTURE2D_DESC& desc);
    /**
    * @brief コンストラクタ
    * @param desc テクスチャデスク
    * @param sub サブリソース
    */
    TextureBuffer(const D3D11_TEXTURE2D_DESC& desc, const D3D11_SUBRESOURCE_DATA& sub);
    /**
    * @brief デストラクタ
    */
    ~TextureBuffer();
    /**
    * @brief テクスチャバッファの取得
    */
    TexPtr getBuffer() const { return mTextureBuffer; }
    /**
    * @brief テクスチャの大きさの取得
    */
    const Math::Vector2& getSize() const { return mSize; }
private:
    TexPtr mTextureBuffer; //!< テクスチャバッファ
    Math::Vector2 mSize; //!< テクスチャのサイズ
};

} //Graphics 
} //Framework 
