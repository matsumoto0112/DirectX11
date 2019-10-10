#pragma once

#include <memory>
#include <d3d11.h>
#include "Framework/Graphics/Resource/Texture2D.h"
#include "Framework/Graphics/Shader/ShaderInputType.h"

namespace Framework {
namespace Graphics {

/**
* @class ShaderResourceView
* @brief �V�F�[�_�[���\�[�X�r���[�Ǘ�
*/
class ShaderResourceView {
public:
    /**
    * @brief �R���X�g���N�^
    * @param texture ���\�[�X���̃e�N�X�`��
    * @param srvDesc �V�F�[�_�[���\�[�X�r���[�f�X�N
    */
    ShaderResourceView(std::shared_ptr<Texture2D> texture, const D3D11_SHADER_RESOURCE_VIEW_DESC* srvDesc);
    /**
    * @brief �f�X�g���N�^
    */
    ~ShaderResourceView();
    /**
    * @brief �R���e�L�X�g�Ƀf�[�^���Z�b�g����
    */
    void set(ShaderInputType inputType, UINT registerNum);
    /**;
    * @brief �V�F�[�_�[���\�[�X�r���[���擾����
    */
    ComPtr<ID3D11ShaderResourceView> getShaderResourceView() const { return mShaderResourceView; }
private:
    ComPtr<ID3D11ShaderResourceView> mShaderResourceView; //!< �V�F�[�_�[���\�[�X�r���[
};

} //Graphics 
} //Framework 
