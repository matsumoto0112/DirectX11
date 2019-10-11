#include "Pipeline.h"
#include "Framework/Graphics/Renderer/IDrawable.h"

namespace Framework {
namespace Graphics {

Pipeline::Pipeline(std::shared_ptr<AlphaBlend> alphaBlend, std::shared_ptr<RasterizerState> rasterizer)
    :mAlphaBlend(alphaBlend), mRasterizer(rasterizer) { }

Pipeline::~Pipeline() { }

void Pipeline::setPipeline() {
    mAlphaBlend->set();
    mRasterizer->set();
}

} //Graphics 
} //Framework 
