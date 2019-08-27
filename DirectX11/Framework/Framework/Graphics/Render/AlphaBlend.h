#pragma once
#include <array>
#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @class AlphaBlend
* @brief �A���t�@�u�����h
*/
class AlphaBlend {
public:
    /**
    * @brief �R���X�g���N�^
    */
    AlphaBlend(const D3D11_BLEND_DESC& blendDesc);
    /**
    * @brief �f�X�g���N�^
    */
    ~AlphaBlend();
    void set(const std::array<float, 4>& blendFactor);
private:
    Microsoft::WRL::ComPtr<ID3D11BlendState> mAlphaBlend;
};

} //Graphics 
} //Framework 