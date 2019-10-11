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
    IRenderer(std::shared_ptr<Graphics::RenderTargetView> rtv, std::shared_ptr<Graphics::Pipeline> pipeline);
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
    std::shared_ptr<Graphics::RenderTargetView> getRenderTarget() const { return mRenderTarget; }
protected:
    std::shared_ptr<Graphics::RenderTargetView> mRenderTarget;
    std::shared_ptr<Graphics::Pipeline> mPipeline;
};

} //Graphics 
} //Framework 