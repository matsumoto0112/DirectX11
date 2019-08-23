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
* @brief ImGUI�̃E�B���h�E�Ǘ�
*/
class Window : public IItem {
public:
    /**
    * @brief �E�B���h�E�̍쐬
    * @param name �E�B���h�E��
    */
    static std::shared_ptr<Window> create(const std::string& name);
    /**
    * @brief �f�X�g���N�^
    */
    ~Window();

    /**
    * @brief �E�B���h�E�ɃA�C�e����ǉ�����
    * @param item �ǉ�����A�C�e��
    */
    template<class T, std::enable_if_t<std::is_base_of<IItem, T>::value, std::nullptr_t> = nullptr>
    std::shared_ptr<T> addItem(std::shared_ptr<T> item);
    /**
    * @brief �`�揈��
    */
    virtual void draw() override;
protected:
    /**
    * @brief �R���X�g���N�^
    */
    Window(const std::string& name);
private:
    std::vector<std::shared_ptr<IItem>> mItems; //!< �E�B���h�E�ɂ��Ă���A�C�e��
};


template<class T, std::enable_if_t<std::is_base_of<IItem, T>::value, std::nullptr_t>>
inline std::shared_ptr<T> Window::addItem(std::shared_ptr<T> item) {
    static_assert(!std::is_same<T, Window>::value,"disallow template parameter T is ImGUI::Window");
    mItems.emplace_back(item);
    return item;
}

} //ImGUI 
} //Framework
