#pragma once
#include <memory>
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class RenderTargetView;
class DepthStencilView;
class TextureBuffer;

/**
* @class RenderTarget
* @brief �����_�[�^�[�Q�b�g
*/
class RenderTarget {
private:
    using TexturePtr = std::shared_ptr<TextureBuffer>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param texture �����_�[�^�[�Q�b�g�Ɏg�p����e�N�X�`��
    */
    RenderTarget(TexturePtr texture);
    /**
    * @brief �R���X�g���N�^
    * @param texture �����_�[�^�[�Q�b�g�Ɏg�p����e�N�X�`��
    * @param rtvDesc �����_�[�^�[�Q�b�g�̃f�X�N
    */
    RenderTarget(TexturePtr texture, const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc);
    /**
    * @brief �f�X�g���N�^
    */
    ~RenderTarget();
    /**
    * @brief �[�x�E�X�e���V���r���[��ǉ�����
    */
    void bindDepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc);
    /**
    * @brief �����_�[�^�[�Q�b�g���R���e�L�X�g�ɃZ�b�g����
    */
    void set();
    /**
    * @brief �����_�[�^�[�Q�b�g���N���A����
    */
    void clear();
private:
    std::unique_ptr<RenderTargetView> mRenderTargetView; //!< �����_�[�^�[�Q�b�g
    std::unique_ptr<DepthStencilView> mDepthStencilView; //!< �[�x�E�X�e���V���r���[
    PROPERTY(Color4, mClearColor, ClearColor);
    PROPERTY(bool, mUseDepthStencil, UseDepthStencil);
};

} //Graphics 
} //Framework 