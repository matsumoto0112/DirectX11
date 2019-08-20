#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include "Utility/Debug.h"
#include "Utility/ImGUI/IItem.h"

namespace Framework {
namespace ImGUI {

/**
* @class Window
* @brief ImGUI�̃E�B���h�E�Ǘ�
*/
class Window : public IItem {
public:
    /**
    * @brief �E�B���h�E�̍쐬
    * @param name �E�B���h�E��
    */
    static Window* create(const std::string& name);
    /**
    * @brief �f�X�g���N�^
    */
    ~Window();
    template<class T, std::enable_if_t<std::is_base_of<IItem, T>::value, std::nullptr_t> = nullptr>
    std::weak_ptr<T> addItem(T* item);
    virtual void draw() override;
private:
    /**
    * @brief �R���X�g���N�^
    */
    Window(const std::string& name);
private:
    std::vector<std::shared_ptr<IItem>> mItems; //!< �E�B���h�E�ɂ��Ă���A�C�e��
};


template<class T, std::enable_if_t<std::is_base_of<IItem, T>::value, std::nullptr_t>>
inline std::weak_ptr<T> Window::addItem(T* item) {
    static_assert(!std::is_same<T, Window>::value,"disallow template parameter T is ImGUI::Window");
    std::shared_ptr<T> sharedItem(item);
    mItems.emplace_back(sharedItem);
    return sharedItem;
}

} //ImGUI 
} //Framework
