#pragma once

#include <functional>
#include "Framework/Utility/ImGUI/IItem.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace ImGUI {

/**
* @class IntField
* @brief �������̓G���A
*/
class IntField :public IItem {
private:
    using CallFunc = std::function<void(int)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param text �e�L�X�g
    * @param defaultValue �f�t�H���g�l
    * @param callFunc �l���ύX���ꂽ�Ƃ��ɌĂ΂��֐�
    */
    IntField(const std::string& text, int defaultValue, CallFunc callFunc = nullptr);
    /**
    * @brief �f�X�g���N�^
    */
    ~IntField();
    /**
    * @brief �`��
    */
    virtual void draw() override;
private:
    PROPERTY(int, mValue, Value);
    PROPERTY(int, mMinValue, MinValue);
    PROPERTY(int, mMaxValue, MaxValue);
private:
    CallFunc mCallFunc; //!< �l���ύX���ꂽ�Ƃ��ɌĂ΂��֐�
};

} //ImGUI 
} //Framework 