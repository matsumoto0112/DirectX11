#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"

namespace Framework {
namespace Graphics {
class DepthStencilView;

/**
* @class RenderTargetView
* @brief �����_�[�^�[�Q�b�g�r���[
*/
class RenderTargetView {
public:
    /**
    * @brief �R���X�g���N�^
    * @param resource ���\�[�X�e�N�X�`��
    */
    RenderTargetView(Microsoft::WRL::ComPtr<ID3D11Resource> resource);
    /**
    * @brief �R���X�g���N�^
    * @param resource ���\�[�X�e�N�X�`��
    * @param desc �����_�[�^�[�Q�b�g�r���[�̐ݒ�
    */
    RenderTargetView(Microsoft::WRL::ComPtr<ID3D11Resource> resource, const D3D11_RENDER_TARGET_VIEW_DESC& desc);
    /**
    * @brief �f�X�g���N�^
    */
    ~RenderTargetView();
    /**
    * @brief �����_�[�^�[�Q�b�g��ݒ肷��
    */
    void set();
    /**
    * @brief �����_�[�^�[�Q�b�g�r���[�̃N���A����
    */
    void clear(const Color4& clearColor);
    void setDepthStencilView(std::unique_ptr<DepthStencilView> depthStencil) { mDepthStencil = std::move(depthStencil); }
    DepthStencilView* getDepthStencilView() const { return mDepthStencil.get(); }
private:
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
    std::unique_ptr<DepthStencilView> mDepthStencil;
};

} //Graphics 
} //Framework 
