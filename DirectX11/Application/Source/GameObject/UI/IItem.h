#pragma once
#include "Framework/Utility/Property.h"
#include "Framework/Utility/Transform2D.h"

namespace UI {

/**
* @class IItem
* @brief UIアイテムインターフェース
*/
class IItem {
public:
    /**
    * @brief コンストラクタ
    */
    IItem(const Framework::Utility::Transform2D& transform) :
        mTransform(transform) {}
    /**
    * @brief デストラクタ
    */
    virtual ~IItem() = default;
    /**
    * @brief 描画処理
    */
    virtual void render() = 0;
protected:
    PROPERTY(Framework::Utility::Transform2D, mTransform, Transform);
};

} //UI 