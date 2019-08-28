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
    MY_ASSERTION(SUCCEEDED(hr), "BlendStateì¬Ž¸”s");
}

AlphaBlend::~AlphaBlend() {}

void AlphaBlend::set() {
    Utility::getContext()->OMSetBlendState(mAlphaBlend.Get(), nullptr, sampleMask);
}

} //Graphics 
} //Framework 
