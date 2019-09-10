#include "BackBufferRenderer.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"

namespace Framework {
namespace Graphics {

BackBufferRenderer::BackBufferRenderer() {
    mRenderTarget = std::make_unique<RenderTarget>(
        Utility::getRenderingManager()->getGraphicsDevice()->getDirectX11GraphicsDevice()->getBackBuffer(),
        std::make_unique<Viewport>(Math::Rect(0.0f, 0.0f, Define::Window::WIDTH, Define::Window::HEIGHT)),
        SRVFlag::NoUse);
    mRenderTarget->createDepthStencilView(
        Graphics::DepthStencilDesc::getDefaultTexture2DDesc(
            Define::Window::WIDTH,
            Define::Window::HEIGHT),
        DepthStencilDesc::getDefaultDepthStencilViewDesc());
}

BackBufferRenderer::~BackBufferRenderer() {}

void BackBufferRenderer::render(std::shared_ptr<Sprite2D> sprite) {
    sprite->draw();
}

void BackBufferRenderer::render(std::shared_ptr<Sprite3D> sprite) {
    sprite->draw();
}

void BackBufferRenderer::render(std::shared_ptr<Model> model, const Utility::Transform& transform) {
    model->draw(transform);
}
void BackBufferRenderer::begin() {
    mRenderTarget->setClearColor(mBackColor);
    mRenderTarget->set();
    mRenderTarget->clear();
}

void BackBufferRenderer::end() {}

} //Graphics 
} //Framework 
