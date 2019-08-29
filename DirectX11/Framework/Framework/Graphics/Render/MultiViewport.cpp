#include "MultiViewport.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

MultiViewport::MultiViewport(UINT viewportNum, const Math::Rect& rect) {
    D3D11_VIEWPORT vp;
    ZeroMemory(&vp, sizeof(vp));
    vp.TopLeftX = rect.getX();
    vp.TopLeftY = rect.getY();
    vp.Width = rect.getWidth();
    vp.Height = rect.getHeight();
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    mViewports = std::vector<D3D11_VIEWPORT>(viewportNum, vp);
}

MultiViewport::~MultiViewport() {}

void MultiViewport::set() {
    Utility::getContext()->RSSetViewports(mViewports.size(), mViewports.data());
}

} //Graphics 
} //Framework 
