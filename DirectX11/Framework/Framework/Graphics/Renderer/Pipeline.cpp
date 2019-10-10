#include "Pipeline.h"
#include "Framework/Graphics/Renderer/IDrawable.h"

namespace Framework {
namespace Graphics {

Pipeline::Pipeline(std::shared_ptr<RenderTargetView> renderTarget,
    std::shared_ptr<AlphaBlend> alphaBlend,
    const Viewport& viewport)
    :mRenderTarget(renderTarget),
    mAlphaBlend(alphaBlend),
    mViewport(viewport) { }

Pipeline::~Pipeline() { }

void Pipeline::begin() {
    mViewport.set();
    mRenderTarget->set();
    mRenderTarget->clear();
    mAlphaBlend->set();
}

void Pipeline::end() {
    mRenderTarget->end();
}

void Pipeline::render(IDrawable* drawable) { 
    drawable->draw();
}

} //Graphics 
} //Framework 
