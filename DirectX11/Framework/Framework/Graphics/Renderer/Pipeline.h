#pragma once
#include <memory>
#include "Framework/Graphics/Renderer/AlphaBlend.h"
#include "Framework/Graphics/Renderer/RenderTargetView.h"
#include "Framework/Graphics/Renderer/Viewport.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class IDrawable;

/**
* @class Pipeline
* @brief 描画パイプライン管理クラス
*/
class Pipeline {
public:
    /**
    * @brief コンストラクタ
    */
    Pipeline(std::shared_ptr<RenderTargetView> renderTarget,
        std::shared_ptr<AlphaBlend> alphaBlend,
        const Viewport& viewport);
    /**
    * @brief デストラクタ
    */
    virtual ~Pipeline();
    /**
    * @brief 描画開始
    */
    virtual void begin();
    /**
    * @brief 描画終了
    */
    virtual void end();
    /**
    * @brief 描画する
    * @param drawable 描画対象
    */
    virtual void render(IDrawable* drawable);
private:
    PROPERTY_POINTER(std::shared_ptr<RenderTargetView>, mRenderTarget, RenderTargetView);
    PROPERTY_POINTER(std::shared_ptr<AlphaBlend>, mAlphaBlend, AlphaBlend);
    PROPERTY(Viewport, mViewport, Viewport);
};

} //Graphics 
} //Framework 