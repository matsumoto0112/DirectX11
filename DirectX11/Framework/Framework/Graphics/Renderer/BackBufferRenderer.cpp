#include "BackBufferRenderer.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Graphics/Desc/BlendStateDesc.h"
#include "Framework/Graphics/Desc/RasterizerStateDesc.h"

namespace Framework {
namespace Graphics {

BackBufferRenderer::BackBufferRenderer(std::shared_ptr<Texture2D>backBufferTexture, UINT width, UINT height, const Color4& backColor)
    :IRenderer(
        std::make_shared<RenderTargetView>(
            backBufferTexture,
            nullptr,
            std::make_shared<Texture2D>(&DepthStencilDesc::getMSAATexture2DDesc(width, height), nullptr),
            &DepthStencilDesc::getMSAADepthStencilViewDesc(),
            Viewport(Math::Rect(0, 0, static_cast<float>(width), static_cast<float>(height))),
            backColor),
        std::make_shared<RenderState>(
            std::make_shared<AlphaBlend>(BlendStateDesc::BLEND_DESC(AlphaBlendType::Alignment)),
            std::make_shared<RasterizerState>(RasterizerStateDesc::getDefaultDesc(FillMode::Solid, CullMode::Back)))) { }

BackBufferRenderer::~BackBufferRenderer() { }

void BackBufferRenderer::begin() {
    mRenderTarget->clear();
    mRenderTarget->set();
    mRenderState->setPipeline();
}

void BackBufferRenderer::end() { }

void BackBufferRenderer::render(IDrawable* drawable) {
    drawable->draw();
}

} //Graphics 
} //Framework 
