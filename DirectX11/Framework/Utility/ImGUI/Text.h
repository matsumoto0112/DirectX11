#pragma once
#include "Utility/ImGUI/IItem.h"

namespace Framework {
namespace ImGUI {

/**
* @class Text
* @brief discription
*/
class Text :public IItem {
public:
    /**
    * @brief �R���X�g���N�^
    * @param text �e�L�X�g
    */
    Text(const std::string& text);
    /**
    * @brief �f�X�g���N�^
    */
    ~Text();
    void setText(const std::string& text);
    const std::string& getText() const { return getName(); }
    virtual void draw() override;
};

} //ImGUI 
} //Framework
