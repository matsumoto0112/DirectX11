#include "IRenderer.h"

namespace Framework {
namespace Graphics {

IRenderer::IRenderer(std::shared_ptr<Graphics::RenderTargetView> rtv, std::shared_ptr<Graphics::RenderState> state)
    :mRenderTarget(rtv), mRenderState(state) { }

} //Graphics 
} //Framework 
