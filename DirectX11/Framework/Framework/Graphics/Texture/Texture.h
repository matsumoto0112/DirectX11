#pragma once

#include <memory>
#include <functional>
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Shader/ShaderInputType.h"

namespace Framework {
namespace Graphics {

class TextureBuffer;
class ShaderResourceView;

/**
* @class Texture
* @brief テクスチャ
*/
class Texture {
private:
    using Texture2DPtr = std::shared_ptr<TextureBuffer>;
    using SRVPtr = std::shared_ptr<ShaderResourceView>;
public:
    /**
    * @brief コンストラクタ
    * @param texture2D テクスチャ2D
    * @param srv シェーダーリソースビュー
    * @param width テクスチャの幅
    * @param height テクスチャの高さ
    */
    Texture(Texture2DPtr texture2D, SRVPtr srv, int width = 0, int height = 0);
    /**
    * @brief デストラクタ
    */
    virtual ~Texture();
    /**
    * @brief データのセット
    * @param inputType どのシェーダに値を代入するか
    * @param slotNum シェーダの何番にこのテクスチャデータを代入するか
    */
    void setData(ShaderInputType inputType, UINT slotNum) const;
    /**
    * @brief 幅を取得
    */
    int getWidth() const;
    /**
    * @brief 高さを取得
    */
    int getHeight() const;
private:
    Texture2DPtr mTexture2D; //!< テクスチャ2D
    SRVPtr mSRV; //!< シェーダーリソースビュー
    int mWidth; //!< 幅
    int mHeight; //!< 高さ
};

} //Graphics 
} //Framework 
