#pragma once
#include <string>

namespace Framework {
namespace ImGUI {

/**
* @class IItem
* @brief ImGUIのアイテムインターフェース
*/
class IItem {
public:
    /**
    * @brief コンストラクタ
    * @param name アイテム名
    */
    IItem(const std::string& name);
    /**
    * @brief デストラクタ
    */
    virtual ~IItem() = default;
    /**
    * @brief 描画
    */
    virtual void draw() = 0;
    /**
    * @brief 名前の取得
    */
    const std::string& getName() const { return mName; }
protected:
    std::string mName; //!< アイテム名
};

} //ImGUI 
} //Framework
