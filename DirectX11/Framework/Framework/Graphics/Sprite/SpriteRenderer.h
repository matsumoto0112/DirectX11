#pragma once

#include <memory>
#include "Framework/Utility/Singleton.h"

namespace Framework {
namespace Graphics {
class GraphicsDeviceManager;
class Sprite2D;
class Sprite3D;
class QuadInstance;
class VertexShader;
class PixelShader;
class Sampler;

/**
* @class SpriteRenderer
* @brief スプライト描画器
*/
class SpriteRenderer : public Utility::Singleton<SpriteRenderer> {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    */
    SpriteRenderer();
    /**
    * @brief デストラクタ
    */
    ~SpriteRenderer();
    /**
    * @brief スプライトを描画する
    * @param sprite 描画するスプライト
    */
    void draw(Sprite2D* sprite);
    /**
    * @brief 3Dスプライトをビルボードで描画
    * @param sprite 描画するスプライト
    */
    void draw(Sprite3D* sprite);
private:
    std::shared_ptr<QuadInstance> mVIBuffer; //!< 頂点・インデックスバッファ
    std::shared_ptr<VertexShader> mVertexShader; //!< 頂点シェーダー
    std::shared_ptr<PixelShader> mPixelShader; //!< ピクセルシェーダー
    std::unique_ptr<Sampler> mSampler; //!< サンプラー
};

} //Graphics 
} //Framework 