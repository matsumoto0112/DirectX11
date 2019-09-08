#pragma once

#include <functional>
#include "Framework/Utility/ImGUI/IItem.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace ImGUI {

/**
* @class FloatField
* @brief 浮動小数点入力エリア
*/
class FloatField :public IItem {
private:
    using CallFunc = std::function<void(float)>;
public:
    /**
    * @brief コンストラクタ
    * @param text テキスト
    * @param defaultValue デフォルト値
    * @param callFunc 値が変更されたときに呼ばれる関数
    */
    FloatField(const std::string& text, float defaultValue, CallFunc callFunc = nullptr);
    /**
    * @brief デストラクタ
    */
    ~FloatField();
    /**
    * @brief 描画
    */
    virtual void draw() override;
private:
    PROPERTY(float, mValue, Value);
    PROPERTY(float, mMinValue, MinValue);
    PROPERTY(float, mMaxValue, MaxValue);
private:
    CallFunc mCallFunc; //!< 値が変更されたときに呼ばれる関数
};

} //ImGUI 
} //Framework 