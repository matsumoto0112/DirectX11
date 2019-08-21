#pragma once

#include <wrl/client.h>
#include <d3d11.h>

namespace Framework {
namespace Graphics {

/**
* @enum PrimitiveTopology
* @brief �v���~�e�B�u�g�|���W�[�̎��
*/
enum class PrimitiveTopology {
    LineList, //!< ���C�����X�g
    TriangleList, //!< �O�p�`���X�g
    TriangleStrip, //!< �O�p�`�X�g���b�v
    NONE,
};

/**
* @struct IndexBufferBindData
* @brief �C���f�b�N�X�o�b�t�@���f�o�C�X�Ƀo�C���h����̂ɕK�v�ȃf�[�^
*/
struct IndexBufferBindData {
    Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer; //!< �C���f�b�N�X�o�b�t�@
    D3D11_PRIMITIVE_TOPOLOGY mTopology; //!< �v���~�e�B�u�g�|���W�[�̎��
};

} //Graphics 
} //Framework 