#pragma once

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

} //Graphics 
} //Framework 
