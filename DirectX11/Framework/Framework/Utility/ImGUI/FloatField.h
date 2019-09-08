#pragma once

#include <functional>
#include "Framework/Utility/ImGUI/IItem.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace ImGUI {

/**
* @class FloatField
* @brief ���������_���̓G���A
*/
class FloatField :public IItem {
private:
    using CallFunc = std::function<void(float)>;
public:
    /**
    * @brief �R���X�g���N�^
    * @param text �e�L�X�g
    * @param defaultValue �f�t�H���g�l
    * @param callFunc �l���ύX���ꂽ�Ƃ��ɌĂ΂��֐�
    */
    FloatField(const std::string& text, float defaultValue, CallFunc callFunc = nullptr);
    /**
    * @brief �f�X�g���N�^
    */
    ~FloatField();
    /**
    * @brief �`��
    */
    virtual void draw() override;
private:
    PROPERTY(float, mValue, Value);
    PROPERTY(float, mMinValue, MinValue);
    PROPERTY(float, mMaxValue, MaxValue);
private:
    CallFunc mCallFunc; //!< �l���ύX���ꂽ�Ƃ��ɌĂ΂��֐�
};

} //ImGUI 
} //Framework 