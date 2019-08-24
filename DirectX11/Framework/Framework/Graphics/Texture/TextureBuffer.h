#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include "Framework/Math/Vector2.h"

namespace Framework {
namespace Graphics {
class DirectX11GraphicsDevice;

/**
* @class TextureBuffer
* @brief �e�N�X�`���̃o�b�t�@�Ǘ�
*/
class TextureBuffer {
    using TexPtr = Microsoft::WRL::ComPtr<ID3D11Texture2D>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param device DirectX11�p�O���t�B�b�N�f�o�C�X
    * @details �f�X�N���Ȃ���΃o�b�N�o�b�t�@���g���ăe�N�X�`�������
    */
    TextureBuffer(DirectX11GraphicsDevice& device);
    /**
    * @brief �R���X�g���N�^
    * @param desc �e�N�X�`���f�X�N
    */
    TextureBuffer(const D3D11_TEXTURE2D_DESC& desc);
    /**
    * @brief �R���X�g���N�^
    * @param desc �e�N�X�`���f�X�N
    * @param sub �T�u���\�[�X
    */
    TextureBuffer(const D3D11_TEXTURE2D_DESC& desc, const D3D11_SUBRESOURCE_DATA& sub);
    /**
    * @brief �f�X�g���N�^
    */
    ~TextureBuffer();
    /**
    * @brief �e�N�X�`���o�b�t�@�̎擾
    */
    TexPtr getBuffer() const { return mTextureBuffer; }
    /**
    * @brief �e�N�X�`���̑傫���̎擾
    */
    const Math::Vector2& getSize() const { return mSize; }
private:
    TexPtr mTextureBuffer; //!< �e�N�X�`���o�b�t�@
    Math::Vector2 mSize; //!< �e�N�X�`���̃T�C�Y
};

} //Graphics 
} //Framework 
