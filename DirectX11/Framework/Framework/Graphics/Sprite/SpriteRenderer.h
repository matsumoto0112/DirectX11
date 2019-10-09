#pragma once

#include <memory>
#include "Framework/Utility/Singleton.h"

namespace Framework {
namespace Graphics {
class Effect;
class GraphicsDeviceManager;
class Sprite2D;
class Sprite3D;
class VertexAndIndexBuffer;
class Sampler;
class PerspectiveCamera;

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
    * @brief スプライトを独自シェーダーで描画する
    * @param sprite 描画するスプライト
    * @param effect 使用するエフェクト
    */
    void draw(Sprite2D* sprite, std::shared_ptr<Effect> effect);
    /**
    * @brief 3Dスプライトをビルボードで描画
    * @param sprite 描画するスプライト
    */
    void draw(Sprite3D* sprite, const PerspectiveCamera& camera);
private:
    std::shared_ptr<VertexAndIndexBuffer> mVIBuffer; //!< 頂点・インデックスバッファ
    std::shared_ptr<Effect> mEffect; //!< エフェクト
    std::unique_ptr<Sampler> mSampler; //!< サンプラー
};

} //Graphics 
} //Framework 