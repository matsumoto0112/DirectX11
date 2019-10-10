#pragma once
#include <d3d11.h>
#include "Framework/Utility/TypeDef.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Texture2D
* @brief �e�N�X�`��2D�Ǘ�
*/
class Texture2D {
public:
    /**
    * @brief �R���X�g���N�^
    * @param texDesc �e�N�X�`���f�X�N
    */
    Texture2D(const D3D11_TEXTURE2D_DESC* texDesc);
    /**
    * @brief �R���X�g���N�^
    * @param texture �e�N�X�`��
    */
    Texture2D(ComPtr<ID3D11Texture2D> texture);
    /**
    * @brief �f�X�g���N�^
    */
    ~Texture2D();
    /**
    * @brief �e�N�X�`�����擾����
    */
    ComPtr<ID3D11Texture2D> getTexture() const { return mTexture2D; }
private:
    ComPtr<ID3D11Texture2D> mTexture2D; //!< �e�N�X�`��2D
};

} //Graphics 
} //Framework 