#pragma once
#include <functional>
#include "Framework/Utility/ImGUI/IItem.h"

namespace Framework {
namespace ImGUI {

/**
* @class Button
* @brief ImGUI�{�^���N���X
*/
class Button :public IItem {
    using CallFunc = std::function<void(void)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param text �e�L�X�g
    * @param callFunc �{�^���������ꂽ�Ƃ��ɌĂԊ֐�
    */
    Button(const std::string& text,CallFunc callFunc);
    /**
    * @brief �f�X�g���N�^
    */
    ~Button();
    /**
    * @brief �`��
    */
    virtual void draw() override;
private:
    CallFunc mCallFunc; //!< �{�^���������ꂽ�Ƃ��ɌĂԊ֐�
};

} //ImGUI 
} //Framework
