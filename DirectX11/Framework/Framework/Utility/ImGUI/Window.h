#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/ImGUI/IItem.h"

namespace Framework {
namespace ImGUI {

/**
* @class Window
* @brief ImGUIのウィンドウ管理
*/
class Window : public IItem {
public:
    /**
    * @brief ウィンドウの作成
    * @param name ウィンドウ名
    */
    static std::shared_ptr<Window> create(const std::string& name);
    /**
    * @brief デストラクタ
    */
    ~Window();

    /**
    * @brief ウィンドウにアイテムを追加する
    * @param item 追加するアイテム
    */
    template<class T, std::enable_if_t<std::is_base_of<IItem, T>::value, std::nullptr_t> = nullptr>
    std::shared_ptr<T> addItem(std::shared_ptr<T> item);
    /**
    * @brief 描画処理
    */
    virtual void draw() override;
protected:
    /**
    * @brief コンストラクタ
    */
    Window(const std::string& name);
private:
    std::vector<std::shared_ptr<IItem>> mItems; //!< ウィンドウについているアイテム
};


template<class T, std::enable_if_t<std::is_base_of<IItem, T>::value, std::nullptr_t>>
inline std::shared_ptr<T> Window::addItem(std::shared_ptr<T> item) {
    static_assert(!std::is_same<T, Window>::value,"disallow template parameter T is ImGUI::Window");
    mItems.emplace_back(item);
    return item;
}

} //ImGUI 
} //Framework
