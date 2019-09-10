#pragma once
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Graphics/Shader/Effect.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Utility/Transform.h"

namespace Framework {
namespace Graphics {
class Model;
/**
* @class ZTexCreater
* @brief Z値を出力したテクスチャを作成する
*/
class ZTexCreater : public IRenderer {
public:
    /**
    * @brief コンストラクタ
    */
    ZTexCreater(UINT width, UINT height, std::shared_ptr<Effect> effect);
    /**
    * @brief デストラクタ
    */
    ~ZTexCreater();
    /**
    * @brief ビュー行列を設定する
    */
    void setViewMatrix(const Math::Matrix4x4& view);
    /**
    * @brief プロジェクション行列を設定する
    */
    void setProjectionMatrix(const Math::Matrix4x4& proj);
    /**
    * @brief 出力開始
    */
    void begin() override;
    /**
    * @brief 出力終了
    */
    void end() override;
    /**
    * @brief 出力処理
    * @param model 対象となるモデル
    * @param transform 対象となるモデルのトランスフォーム
    */
    void render(std::shared_ptr<Model> model, const Utility::Transform& tranform) override;
    /**
    * @brief スプライトを描画する
    * @param sprite 描画するスプライト
    * @details スプライトは対象外なので普通の描画をする
    */
    virtual void render(std::shared_ptr<Sprite2D> sprite) override;
    /**
    * @brief スプライトを描画する
    * @param sprite 描画するスプライト
    * @details スプライトは対象外なので普通の描画をする
    */
    virtual void render(std::shared_ptr<Sprite3D> sprite) override;
private:
    std::shared_ptr<Effect> mEffect;
    std::shared_ptr<Texture> mTexture;
    std::unique_ptr<RenderTarget> mRenderTarget;
};

} //Graphics 
} //Framework 