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
    ShaderBase() { }
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ShaderBase() = default;
    /**
    * @brief �V�F�[�_���g�p����
    */
    virtual void set() = 0;
protected:
    /**
    * @brief �p�X�̍Ō�Ɋg���q���Ȃ���Βǉ�����
    */
    std::string addExtendIfNotExist(const std::string& filepath);
};

} //Graphics 
} //Framework 
