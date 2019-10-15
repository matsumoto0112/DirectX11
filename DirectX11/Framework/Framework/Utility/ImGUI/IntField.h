#pragma once

#include <functional>
#include "Framework/Utility/ImGUI/IItem.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace ImGUI {

/**
* @class IntField
* @brief 整数入力エリア
*/
class IntField :public IItem {
private:
    using CallFunc = std::function<void(int)>;
public:
    /**
    * @brief コンストラクタ
    * @param text テキスト
    * @param defaultValue デフォルト値
    * @param callFunc 値が変更されたときに呼ばれる関数
    */
    IntField(const std::string& text, int defaultValue, CallFunc callFunc = nullptr);
    /**
    * @brief デストラクタ
    */
    ~IntField();
    /**
    * @brief 描画
    */
    virtual void draw() override;
private:
    PROPERTY(int, mValue, Value);
    PROPERTY(int, mMinValue, MinValue);
    PROPERTY(int, mMaxValue, MaxValue);
private:
    CallFunc mCallFunc; //!< 値が変更されたときに呼ばれる関数
};

} //ImGUI 
} //Framework 