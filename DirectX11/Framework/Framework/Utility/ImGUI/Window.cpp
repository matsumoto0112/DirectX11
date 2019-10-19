#include "Window.h"
#include "Framework/Utility/ImGUI/ImGUI.h"
// #include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/ImGUI/Manager.h"

namespace Framework {
namespace ImGUI {
Window::Window(const std::string& name)
    :IItem(name) {}

Window::~Window() {}

void Window::draw() {
    ImGui::Begin(mName.c_str());

    for (auto&& item : mItems) {
        item->draw();
    }

    ImGui::End();
}

} //ImGUI 
} //Framework
