#pragma once

#include <memory>
#include <functional>
#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Shader/ShaderInputType.h"

namespace Framework {
namespace Graphics {

class TextureBuffer;
class ShaderResourceView;

/**
* @class Texture
* @brief �e�N�X�`��
*/
class Texture {
private:
    using Texture2DPtr = std::shared_ptr<TextureBuffer>;
    using SRVPtr = std::shared_ptr<ShaderResourceView>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param texture2D �e�N�X�`��2D
    * @param srv �V�F�[�_�[���\�[�X�r���[
    * @param width �e�N�X�`���̕�
    * @param height �e�N�X�`���̍���
    */
    Texture(Texture2DPtr texture2D, SRVPtr srv, int width = 0, int height = 0);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Texture();
    /**
    * @brief �f�[�^�̃Z�b�g
    * @param inputType �ǂ̃V�F�[�_�ɒl�������邩
    * @param slotNum �V�F�[�_�̉��Ԃɂ��̃e�N�X�`���f�[�^�������邩
    */
    void setData(ShaderInputType inputType, UINT slotNum) const;
    /**
    * @brief �����擾
    */
    int getWidth() const;
    /**
    * @brief �������擾
    */
    int getHeight() const;
private:
    Texture2DPtr mTexture2D; //!< �e�N�X�`��2D
    SRVPtr mSRV; //!< �V�F�[�_�[���\�[�X�r���[
    int mWidth; //!< ��
    int mHeight; //!< ����
};

} //Graphics 
} //Framework 
