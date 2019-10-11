#include "IRenderer.h"

namespace Framework {
namespace Graphics {

IRenderer::IRenderer(std::shared_ptr<Graphics::RenderTargetView> rtv, std::shared_ptr<Graphics::Pipeline> pipeline)
    :mRenderTarget(rtv), mPipeline(pipeline) { }

} //Graphics 
} //Framework 
