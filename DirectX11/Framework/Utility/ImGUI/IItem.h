#pragma once
#include <string>

namespace Framework {
namespace ImGUI {

/**
* @class IItem
* @brief ImGUI�̃A�C�e���C���^�[�t�F�[�X
*/
class IItem {
public:
    /**
    * @brief �R���X�g���N�^
    * @param name �A�C�e����
    */
    IItem(const std::string& name);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IItem() = default;
    /**
    * @brief �`��
    */
    virtual void draw() = 0;
    /**
    * @brief ���O�̎擾
    */
    const std::string& getName() const { return mName; }
protected:
    std::string mName; //!< �A�C�e����
};

} //ImGUI 
} //Framework
