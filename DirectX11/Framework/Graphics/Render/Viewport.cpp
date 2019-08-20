#include "Viewport.h"
#include "Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

Viewport::Viewport(const Math::Rect& rect) {
    mViewport.TopLeftX = rect.getX();
    mViewport.TopLeftY = rect.getY();
    mViewport.Width = rect.getWidth();
    mViewport.Height = rect.getHeight();
    mViewport.MinDepth = 0.0f;
    mViewport.MaxDepth = 1.0f;
}

Viewport::~Viewport() {}

void Viewport::set() {
    Utility::getContext()->RSSetViewports(1, &mViewport);
}

} //Graphics 
} //Framework 
