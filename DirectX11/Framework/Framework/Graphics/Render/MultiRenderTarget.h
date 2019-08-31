#pragma once
#include <memory>
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Render/MultiViewport.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class DepthStencilView;
class TextureBuffer;
class Texture;

/**
* @class MultiRenderTarget
* @brief �}���`�����_�[�^�[�Q�b�g
*/
class MultiRenderTarget {
private:
    using Texture2DPtr = std::shared_ptr<TextureBuffer>;
    using RenderTargetViewPtr = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>;
    using MultiViewportPtr = std::unique_ptr<MultiViewport>;
    using TexturePtr = std::shared_ptr<Texture>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param renderTargetNum �����_�[�^�[�Q�b�g��
    * @param textures �g�p����e�N�X�`���o�b�t�@�z��
    * @param rtvDesc �����_�[�^�[�Q�b�g�f�X�N
    * @param rect �����_�[�^�[�Q�b�g�͈̔�
    */
    MultiRenderTarget(UINT renderTargetNum,
        std::vector<Texture2DPtr> textures,
        const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc,
        const Math::Rect& rect);
    /**
    * @brief �R���X�g���N�^
    * @param renderTargetNum �����_�[�^�[�Q�b�g��
    * @param rect �����_�[�^�[�Q�b�g�͈̔�
    * @details �f�t�H���g�̃����_�[�^�[�Q�b�g�̎d�l�ō쐬����
    */
    MultiRenderTarget(UINT renderTargetNum,
        const Math::Rect& rect);
    /**
    * @brief �f�X�g���N�^
    */
    ~MultiRenderTarget();
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
    * @param num �z��̃C���f�b�N�X
    */
    TexturePtr getRenderTargetTexture(UINT index);
private:
    std::vector<RenderTargetViewPtr> mRTVs; //<! �����_�[�^�[�Q�b�g�r���[�z��
    std::unique_ptr<DepthStencilView> mDepthStencilView; //!< �[�x�E�X�e���V���r���[
    MultiViewportPtr mViewport; //!< �r���[�|�[�g
    std::vector<TexturePtr> mRenderTargetTextures; //!< �����_�[�^�[�Q�b�g�̃e�N�X�`���z��
    PROPERTY(Color4, mClearColor, ClearColor);
    PROPERTY(bool, mUseDepthStencil, UseDepthStencil);
};

} //Graphics 
} //Framework 