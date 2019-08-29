#pragma once

namespace Framework {
namespace Graphics {

/**
* @class ShaderBase
* @brief �V�F�[�_���N���X
*/
class ShaderBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ShaderBase() {}
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ShaderBase() = default;
    /**
    * @brief �V�F�[�_���g�p����
    */
    virtual void set() = 0;
};

} //Graphics 
} //Framework 
