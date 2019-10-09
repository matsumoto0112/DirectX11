#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class RenderTarget;

/**
* @class BackBufferRenderer
* @brief バックバッファに向けて描画するデバイス
*/
class BackBufferRenderer : public IRenderer {
public:
    /**
    * @brief コンストラクタ
    */
    BackBufferRenderer();
    /**
    * @brief デストラクタ
    */
    ~BackBufferRenderer();
    /**
    * @brief 描画開始
    */
    virtual void begin() override;
    /**
    * @brief 描画終了
    */
    virtual void end() override;
    /**
    * @brief スプライトを描画する
    * @param sprite 描画するスプライト
    */
    virtual void render(std::shared_ptr<Sprite2D> sprite) override;
    /**
    * @brief スプライトを描画する
    * @param sprite 描画するスプライト
    */
    virtual void render(std::shared_ptr<Sprite3D> sprite) override;
    ///**
    //* @brief モデルを描画する
    //* @param model 描画するモデル
    //* @param transform 描画するモデルのトランスフォーム
    //*/
    //virtual void render(std::shared_ptr<Model> model, const Utility::Transform& transform) override;
    /**
    * @brief 描画したターゲットのテクスチャを取得する
    * @details バックバッファのテクスチャは取得できないのでエラーとなる
    */
    virtual std::shared_ptr<Texture> getRenderedTexture() const override;
    /**
    * @brief レンダーターゲットを取得する
    */
    RenderTarget* getRenderTarget() const { return mRenderTarget.get(); }
private:
    std::unique_ptr<RenderTarget> mRenderTarget; //!< レンダーターゲット
};

} //Graphics 
} //Framework 