#include "Window.h"
#include "Framework/Utility/ImGUI/ImGUI.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/ImGUI/Manager.h"

namespace Framework {
namespace ImGUI {
Window::Window(const std::string& name)
    :IItem(name) {}

Window* Window::create(const std::string& name) {
    Window* window = new Window(name);
    Utility::getImGUIManager()->add(window);
    return window;
}

Window::~Window() {}
//
//std::weak_ptr<IItem> Window::addItem(IItem* item) {
//    std::shared_ptr<IItem> sharedItem(item);
//    mItems.emplace_back(sharedItem);
//    return sharedItem;
//}

void Window::draw() {
    ImGui::Begin(mName.c_str());

    for (auto&& item : mItems) {
        item->draw();
    }

    ImGui::End();
}

} //ImGUI 
} //Framework
