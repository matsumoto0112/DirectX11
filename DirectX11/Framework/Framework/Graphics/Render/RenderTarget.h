#pragma once
#include <memory>
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Render/SRVFlag.h"
#include "Framework/Graphics/Render/Viewport.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class DepthStencilView;
class RenderTargetView;
class Texture;
class TextureBuffer;

/**
* @class RenderTarget
* @brief �����_�[�^�[�Q�b�g
*/
class RenderTarget {
private:
    using DepthStencilViewPtr = std::unique_ptr<DepthStencilView>;
    using RenderTargetViewPtr = std::unique_ptr<RenderTargetView>;
    using TexturePtr = std::shared_ptr<Texture>;
    using TextureBufferPtr = std::shared_ptr<TextureBuffer>;
    using ViewportPtr = std::unique_ptr<Viewport>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param texture �����_�[�^�[�Q�b�g�Ɏg�p����e�N�X�`��
    * @param viewport �r���[�|�[�g
    * @param useSRV �V�F�[�_�[���\�[�X�r���[���g�p���邩
    */
    RenderTarget(TextureBufferPtr texture, ViewportPtr viewport, SRVFlag useSRV);
    /**
    * @brief �R���X�g���N�^
    * @param texture �����_�[�^�[�Q�b�g�Ɏg�p����e�N�X�`��
    * @param rtvDesc �����_�[�^�[�Q�b�g�̃f�X�N
    * @param viewport �r���[�|�[�g
    * @param useSRV �V�F�[�_�[���\�[�X�r���[���g�p���邩
    */
    RenderTarget(TextureBufferPtr texture, const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc, ViewportPtr viewport, SRVFlag useSRV);
    /**
    * @brief �f�X�g���N�^
    */
    ~RenderTarget();
    /**
    * @brief �[�x�E�X�e���V���r���[���f�t�H���g�̎d�l�ō쐬����
    */
    void createDepthStencilView();
    /**
    * @brief �[�x�E�X�e���V���r���[���쐬����
    */
    void createDepthStencilView(const D3D11_TEXTURE2D_DESC& texDesc, const D3D11_DEPTH_STENCIL_VIEW_DESC& dsvDesc);
    /**
    * @brief �����_�[�^�[�Q�b�g���R���e�L�X�g�ɃZ�b�g����
    */
    void set();
    /**
    * @brief �����_�[�^�[�Q�b�g���N���A����
    */
    void clear();
    /**
    * @brief �����_�[�^�[�Q�b�g�̃e�N�X�`�����擾����
    */
    TexturePtr getRenderTargetTexture();
private:
    RenderTargetViewPtr mRenderTargetView; //!< �����_�[�^�[�Q�b�g
    DepthStencilViewPtr mDepthStencilView; //!< �[�x�E�X�e���V���r���[
    ViewportPtr mViewport; //!< �r���[�|�[�g
    TexturePtr mTexture; //!< �����_�[�^�[�Q�b�g�̃e�N�X�`��
private:
    PROPERTY(Color4, mClearColor, ClearColor);
    PROPERTY(bool, mEnableDepthStencil, EnableDepthStencil);
};

} //Graphics 
} //Framework 