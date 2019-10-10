#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Resource/Texture2D.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
/**
* @class RenderTargetView
* @brief �����_�[�^�[�Q�b�g�r���[
*/
class RenderTargetView {
public:
    /**
    * @brief �R���X�g���N�^
    * @param texture ���\�[�X�e�N�X�`��
    * @param desc �����_�[�^�[�Q�b�g�r���[�̐ݒ�
    */
    RenderTargetView(std::shared_ptr<Texture2D> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc, const Color4& backColor);
    /**
    * @brief �f�X�g���N�^
    */
    ~RenderTargetView();
    /**
    * @brief �����_�[�^�[�Q�b�g�r���[���擾����
    */
    ComPtr<ID3D11RenderTargetView> getRenderTargetView() const { return mRenderTargetView; }
    /**
    * @brief �����_�[�^�[�Q�b�g�̃N���A
    */
    void clear();
    /**
    * @brief �����_�[�^�[�Q�b�g���Z�b�g����
    */
    void set();
private:
    ComPtr<ID3D11RenderTargetView> mRenderTargetView; //!< �����_�[�^�[�Q�b�g�r���[
private:
    PROPERTY(Color4, mBackColor, BackColor);
};

} //Graphics 
} //Framework 
