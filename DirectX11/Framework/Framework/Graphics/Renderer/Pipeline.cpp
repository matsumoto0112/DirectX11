#include "Pipeline.h"

namespace Framework {
namespace Graphics {

Pipeline::Pipeline(std::shared_ptr<RenderTargetView> renderTarget, std::shared_ptr<AlphaBlend> alphaBlend)
    :mRenderTarget(renderTarget),
    mAlphaBlend(alphaBlend) { }

Pipeline::~Pipeline() { }

void Pipeline::begin() {
    mRenderTarget->set();
    mRenderTarget->clear();
    mAlphaBlend->set();
}

void Pipeline::end() { }

} //Graphics 
} //Framework 
