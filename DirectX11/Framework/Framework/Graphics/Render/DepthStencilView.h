#pragma once
#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @class DepthStencilView
* @brief �[�x�E�X�e���V���r���[
*/
class DepthStencilView {
public:
    /**
    * @brief �R���X�g���N�^
    */
    DepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc);
    /**
    * @brief �f�X�g���N�^
    */
    ~DepthStencilView();
    void clear();
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> getDepthStencilView() const { return mDepthStencil; }
private:
    Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencil;
};

} //Graphics 
} //Framework 