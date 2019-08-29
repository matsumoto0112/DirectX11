#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Color4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class TextureBuffer;
/**
* @class RenderTargetView
* @brief �����_�[�^�[�Q�b�g�r���[
*/
class RenderTargetView {
private:
    using TexturePtr = std::shared_ptr<TextureBuffer>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param texture ���\�[�X�e�N�X�`��
    */
    RenderTargetView(TexturePtr texture);
    /**
    * @brief �R���X�g���N�^
    * @param texture ���\�[�X�e�N�X�`��
    * @param desc �����_�[�^�[�Q�b�g�r���[�̐ݒ�
    */
    RenderTargetView(TexturePtr texture, const D3D11_RENDER_TARGET_VIEW_DESC& desc);
    /**
    * @brief �f�X�g���N�^
    */
    ~RenderTargetView();
    /**
    * @brief �����_�[�^�[�Q�b�g�r���[���擾����
    */
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> getRenderTargetView() const { return mRenderTargetView; }
    /**
    * @brief �����_�[�^�[�Q�b�g�̃N���A
    * @param clearColor �N���A�F
    */
    void clear(const Color4& clearColor);
private:
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView; //!< �����_�[�^�[�Q�b�g�r���[
};

} //Graphics 
} //Framework 
