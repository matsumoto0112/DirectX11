#include "Pipeline.h"
#include "Framework/Graphics/Renderer/IDrawable.h"

namespace Framework {
namespace Graphics {

RenderState::RenderState(std::shared_ptr<AlphaBlend> alphaBlend, std::shared_ptr<RasterizerState> rasterizer)
    :mAlphaBlend(alphaBlend), mRasterizer(rasterizer) { }

RenderState::~RenderState() { }

void RenderState::setPipeline() {
    mAlphaBlend->set();
    mRasterizer->set();
}

} //Graphics 
} //Framework 
