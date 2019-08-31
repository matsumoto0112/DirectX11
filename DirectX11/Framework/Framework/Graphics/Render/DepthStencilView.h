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
    * @param texDesc �e�N�X�`���f�X�N
    * @param dsvDesc �[�x�E�X�e���V���f�X�N
    */
    DepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc);
    /**
    * @brief �R���X�g���N�^
    * @param width ��
    * @param height ����
    */
    DepthStencilView(UINT width, UINT height);
    /**
    * @brief �f�X�g���N�^
    */
    ~DepthStencilView();
    /**
    * @brief �N���A
    */
    void clear();
    /**
    * @brief �[�x�E�X�e���V���r���[�̎擾
    */
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> getDepthStencilView() const { return mDepthStencil; }
private:
    Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture; //!< �e�N�X�`�� 
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencil; //!< �[�x�E�X�e���V���r���[
};

} //Graphics 
} //Framework 