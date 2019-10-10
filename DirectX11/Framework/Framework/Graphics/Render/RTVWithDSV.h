#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class RTVWithDSV
* @brief �[�x�E�X�e���V���r���[�t�������_�[�^�[�Q�b�g
*/
class RTVWithDSV {
public:
    /**
    * @brief �R���X�g���N�^
    */
    RTVWithDSV(ComPtr<ID3D11Texture2D> renderTargetTexture, const D3D11_RENDER_TARGET_VIEW_DESC* rtvDesc,
        ComPtr<ID3D11Texture2D> depthStencilTexture, const D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc);
    /**
    * @brief �f�X�g���N�^
    */
    ~RTVWithDSV();
    /**
    * @brief �����_�[�^�[�Q�b�g�E�[�x�E�X�e���V���r���[�̃N���A
    */
    void clear();
    /**
    * @brief �����_�[�^�[�Q�b�g�̃Z�b�g
    */
    void set();
private:
    ComPtr<ID3D11RenderTargetView> mRenderTargetView; //!< �����_�[�^�[�Q�b�g�r���[
    ComPtr<ID3D11DepthStencilView> mDepthStencilView; //!< �[�x�E�X�e���V���r���[
private:
    PROPERTY(Color4, mBackColor, BackColor);
};

} //Graphics 
} //Framework 