#include "AlphaBlend.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace {
static constexpr UINT sampleMask = 0xffffffff;
}

namespace Framework {
namespace Graphics {

AlphaBlend::AlphaBlend(const D3D11_BLEND_DESC& blendDesc) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateBlendState(&blendDesc, &mAlphaBlend));
}

AlphaBlend::~AlphaBlend() { }

void AlphaBlend::set() {
    DX11InterfaceAccessor::getContext()->OMSetBlendState(mAlphaBlend.Get(), nullptr, sampleMask);
}

void AlphaBlend::clearState() {
    DX11InterfaceAccessor::getContext()->OMSetBlendState(nullptr, nullptr, 0);
}

D3D11_BLEND_DESC AlphaBlend::getCurrentBlendStateDesc() const {
    D3D11_BLEND_DESC res;
    mAlphaBlend->GetDesc(&res);
    return res;
}

void AlphaBlend::setBlendStateFromDesc(const D3D11_BLEND_DESC& desc) {
    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateBlendState(&desc, mAlphaBlend.ReleaseAndGetAddressOf()));
    set();
}

} //Graphics 
} //Framework 
