#pragma once

#include <memory>
#include "Framework/Utility/Singleton.h"

namespace Framework {
namespace Graphics {
class Effect;
class GraphicsDeviceManager;
class IndexBuffer;
class PerspectiveCamera;
class Sampler;
class Sprite2D;
class Sprite3D;
class VertexBuffer;
class RenderState;

/**
* @class SpriteRenderer
* @brief スプライト描画器
*/
class SpriteRenderer : public Utility::Singleton<SpriteRenderer> {
public:
    /**
    * @brief コンストラクタ
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
    * @param camera 描画するカメラ
    */
    void draw(Sprite3D* sprite);
    /**
    * @brief スプライト描画に使用するデフォルトのエフェクトを取得する
    */
    Effect* getDefaultSpriteEffect() const { return mEffect.get(); }
private:
    std::shared_ptr<VertexBuffer> mVertexBuffer; //!< 頂点・インデックスバッファ
    std::shared_ptr<IndexBuffer> mIndexBuffer; //!< 頂点・インデックスバッファ
    std::shared_ptr<RenderState> mRenderState; //!< 描画設定
    std::shared_ptr<Effect> mEffect; //!< エフェクト
    std::unique_ptr<Sampler> mSampler; //!< サンプラー
};

} //Graphics 
} //Framework 