#pragma once
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Graphics/Renderer/RenderTargetView.h"
#include "Framework/Graphics/Renderer/IDrawable.h"

namespace Framework {
namespace Graphics {

/**
* @class IRenderer
* @brief 描画インターフェース
*/
class IRenderer {
public:
    /**
    * @brief コンストラクタ
    * @param rtv レンダーターゲットビュー
    * @param pipeline 描画パイプライン
    */
    IRenderer(std::shared_ptr<Graphics::RenderTargetView> rtv, std::shared_ptr<Graphics::RenderState> pipeline);
    /**
    * @brief デストラクタ
    */
    virtual ~IRenderer() = default;
    /**
    * @brief 描画処理開始
    */
    virtual void begin() = 0;
    /**
    * @brief 描画処理終了
    */
    virtual void end() = 0;
    /**
    * @brief 描画処理
    * @param drawable 描画対象
    */
    virtual void render(IDrawable* drawable) = 0;
    /**
    * @brief 描画ターゲットを取得する
    */
    std::shared_ptr<Graphics::RenderTargetView> getRenderTarget() const { return mRenderTarget; }
    /**
    * @brief 描画ステートを取得する
    */
    std::shared_ptr<Graphics::RenderState> getPipeline() const { return mRenderState; }
protected:
    std::shared_ptr<Graphics::RenderTargetView> mRenderTarget;
    std::shared_ptr<Graphics::RenderState> mRenderState;
};

} //Graphics 
} //Framework 