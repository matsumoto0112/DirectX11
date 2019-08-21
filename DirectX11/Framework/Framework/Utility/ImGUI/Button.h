#pragma once
#include <functional>
#include "Framework/Utility/ImGUI/IItem.h"

namespace Framework {
namespace ImGUI {

/**
* @class Button
* @brief ImGUIボタンクラス
*/
class Button :public IItem {
    using CallFunc = std::function<void(void)>;
public:
    /**
    * @brief コンストラクタ
    * @param text テキスト
    * @param callFunc ボタンが押されたときに呼ぶ関数
    */
    Button(const std::string& text,CallFunc callFunc);
    /**
    * @brief デストラクタ
    */
    ~Button();
    /**
    * @brief 描画
    */
    virtual void draw() override;
private:
    CallFunc mCallFunc; //!< ボタンが押されたときに呼ぶ関数
};

} //ImGUI 
} //Framework
