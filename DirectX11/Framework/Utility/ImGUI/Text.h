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
    * @brief コンストラクタ
    * @param text テキスト
    */
    Text(const std::string& text);
    /**
    * @brief デストラクタ
    */
    ~Text();
    void setText(const std::string& text);
    const std::string& getText() const { return getName(); }
    virtual void draw() override;
};

} //ImGUI 
} //Framework
