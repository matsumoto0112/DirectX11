#include "RasterizerState.h"
//#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace Framework {
namespace Graphics {

RasterizerState::RasterizerState(const D3D11_RASTERIZER_DESC& desc) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateRasterizerState(&desc, &mRasterizer));
}

RasterizerState::~RasterizerState() { }

void RasterizerState::set() {
    DX11InterfaceAccessor::getContext()->RSSetState(mRasterizer.Get());
}

void RasterizerState::clearState() {
    DX11InterfaceAccessor::getContext()->RSSetState(nullptr);
}

} //Graphics 
} //Framework 
