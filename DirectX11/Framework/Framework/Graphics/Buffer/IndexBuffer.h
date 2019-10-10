#pragma once

#include <vector>
#include <d3d11.h>
#include "Framework/Graphics/Buffer/PrimitiveTopology.h"

namespace Framework {
namespace Graphics {

/**
* @class IndexBuffer
* @brief �C���f�b�N�X�o�b�t�@�Ǘ��N���X
*/
class IndexBuffer {
public:
    /**
    * @brief �R���X�g���N�^
    * @param indices �C���f�b�N�X�f�[�^
    * @param topology �v���~�e�B�u�g�|���W�[�̎��
    */
    IndexBuffer(const std::vector<UINT>& indices, PrimitiveTopology topology);
    /**
    * @brief �f�X�g���N�^
    */
    ~IndexBuffer();
    /**
    * @brief �C���f�b�N�X�f�[�^�̃Z�b�g
    */
    void setData();
    /**
    * @brief �`��w�߂𑗂�
    */
    void drawCall();
private:
    /**
    * @brief �C���f�b�N�X�f�[�^�̐ݒ�
    * @param indices �C���f�b�N�X�f�[�^
    */
    void setBuffer(const std::vector<UINT>& indices, PrimitiveTopology topology);
private:
    ComPtr<ID3D11Buffer> mBuffer; //!< �C���f�b�N�X�o�b�t�@
    D3D11_PRIMITIVE_TOPOLOGY mTopology; //!< �v���~�e�B�u�g�|���W�[�̎��
    UINT mIndexCount; //!< ���_��
};

} //Graphics 
} //Framework 