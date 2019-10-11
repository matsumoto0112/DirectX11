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
    BackBufferRenderer(std::shared_ptr<Texture2D> backBufferTexture, UINT width, UINT height, const Color4& backColor);
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
    * @brief 描画処理
    */
    virtual void render(IDrawable* drawable) override;
};

} //Graphics 
} //Framework 