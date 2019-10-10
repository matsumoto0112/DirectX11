#include "AlphaBlend.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"

namespace {
static constexpr UINT sampleMask = 0xffffffff;
}

namespace Framework {
namespace Graphics {

AlphaBlend::AlphaBlend(const D3D11_BLEND_DESC& blendDesc) {
    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateBlendState(&blendDesc, &mAlphaBlend);
    MY_ASSERTION(SUCCEEDED(hr), "BlendStateçÏê¨é∏îs");
}

AlphaBlend::~AlphaBlend() {}

void AlphaBlend::set() {
    DX11InterfaceAccessor::getContext()->OMSetBlendState(mAlphaBlend.Get(), nullptr, sampleMask);
}

D3D11_BLEND_DESC AlphaBlend::getCurrentBlendStateDesc() const {
    D3D11_BLEND_DESC res;
    mAlphaBlend->GetDesc(&res);
    return res;
}

void AlphaBlend::setBlendStateFromDesc(const D3D11_BLEND_DESC& desc) {
    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateBlendState(&desc, mAlphaBlend.ReleaseAndGetAddressOf());
    MY_ASSERTION(SUCCEEDED(hr), "BlendStateçÏê¨é∏îs");

    set();
}

} //Graphics 
} //Framework 
