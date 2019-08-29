#pragma once
#include <memory>
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Render/Viewport.h"
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
    using ViewportPtr = std::unique_ptr<Viewport>;
    using RenderTargetViewPtr = std::unique_ptr<RenderTargetView>;
    using DepthStencilViewPtr = std::unique_ptr<DepthStencilView>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param texture �����_�[�^�[�Q�b�g�Ɏg�p����e�N�X�`��
    */
    RenderTarget(TexturePtr texture, ViewportPtr viewport);
    /**
    * @brief �R���X�g���N�^
    * @param texture �����_�[�^�[�Q�b�g�Ɏg�p����e�N�X�`��
    * @param rtvDesc �����_�[�^�[�Q�b�g�̃f�X�N
    */
    RenderTarget(TexturePtr texture, const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc, ViewportPtr viewport);
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

private:
    RenderTargetViewPtr mRenderTargetView; //!< �����_�[�^�[�Q�b�g
    DepthStencilViewPtr mDepthStencilView; //!< �[�x�E�X�e���V���r���[
    ViewportPtr mViewport; //!< �r���[�|�[�g
    PROPERTY(Color4, mClearColor, ClearColor);
    PROPERTY(bool, mEnableDepthStencil, EnableDepthStencil);
};

} //Graphics 
} //Framework 