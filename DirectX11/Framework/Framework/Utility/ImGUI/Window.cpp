#include "Window.h"
#include "Framework/Utility/ImGUI/ImGUI.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/ImGUI/Manager.h"

namespace Framework {
namespace ImGUI {
Window::Window(const std::string& name)
    :IItem(name) {}

std::shared_ptr<Window> Window::create(const std::string& name) {
    class temp : public Window {
    public:
        temp(const std::string& name)
            :Window(name) {}
    };
    std::shared_ptr<Window> window = std::make_shared<temp>(name);
    Utility::getImGUIManager()->add(window);
    return window;
}

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
