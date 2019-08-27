#include "AlphaBlend.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace {
static const UINT sampleMask = 0xffffffff;
}

namespace Framework {
namespace Graphics {

AlphaBlend::AlphaBlend(const D3D11_BLEND_DESC& blendDesc) {
    HRESULT hr = Utility::getDevice()->CreateBlendState(&blendDesc, &mAlphaBlend);
    MY_ASSERTION(SUCCEEDED(hr), "BlendStateçÏê¨é∏îs");
}

AlphaBlend::~AlphaBlend() {}

void AlphaBlend::set(const std::array<float, 4>& blendFactor) {
    Utility::getContext()->OMSetBlendState(mAlphaBlend.Get(), blendFactor.data(), sampleMask);
}

} //Graphics 
} //Framework 
