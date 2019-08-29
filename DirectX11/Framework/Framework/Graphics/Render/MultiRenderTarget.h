#pragma once
#include <memory>
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class DepthStencilView;
class TextureBuffer;

/**
* @class MultiRenderTarget
* @brief �}���`�����_�[�^�[�Q�b�g
*/
class MultiRenderTarget {
private:
    using Texture2DPtr = std::shared_ptr<TextureBuffer>;
    using RenderTargetViewPtr = Microsoft::WRL::ComPtr<ID3D11RenderTargetView>;
public:
    /**
    * @brief �R���X�g���N�^
    */
    MultiRenderTarget(UINT renderTargetNum, std::vector<Texture2DPtr> texture, const D3D11_RENDER_TARGET_VIEW_DESC& rtvDesc);
    /**
    * @brief �f�X�g���N�^
    */
    ~MultiRenderTarget();
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
    UINT mRenderTargetViewNum; //!< �����_�[�^�[�Q�b�g�r���[�̐�
    std::vector<RenderTargetViewPtr> mRTVs; //<! �����_�[�^�[�Q�b�g�r���[�z��
    std::unique_ptr<DepthStencilView> mDepthStencilView; //!< �[�x�E�X�e���V���r���[
    PROPERTY(Color4, mClearColor, ClearColor);
    PROPERTY(bool, mUseDepthStencil, UseDepthStencil);
};

} //Graphics 
} //Framework 