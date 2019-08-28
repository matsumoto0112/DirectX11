#include "AlphaBlend.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace {
static constexpr UINT sampleMask = 0xffffffff;
}

namespace Framework {
namespace Graphics {

AlphaBlend::AlphaBlend(const D3D11_BLEND_DESC& blendDesc) {
    HRESULT hr = Utility::getDevice()->CreateBlendState(&blendDesc, &mAlphaBlend);
    MY_ASSERTION(SUCCEEDED(hr), "BlendStateçÏê¨é∏îs");
}

AlphaBlend::~AlphaBlend() {}

void AlphaBlend::set() {
    Utility::getContext()->OMSetBlendState(mAlphaBlend.Get(), nullptr, sampleMask);
}

D3D11_BLEND_DESC AlphaBlend::getCurrentBlendStateDesc() const {
    D3D11_BLEND_DESC res;
    mAlphaBlend->GetDesc(&res);
    return res;
}

void AlphaBlend::setBlendStateFromDesc(const D3D11_BLEND_DESC& desc) {
    HRESULT hr = Utility::getDevice()->CreateBlendState(&desc, mAlphaBlend.ReleaseAndGetAddressOf());
    MY_ASSERTION(SUCCEEDED(hr), "BlendStateçÏê¨é∏îs");

    set();
}

} //Graphics 
} //Framework 
