#include "Button.h"
#include "Framework/Utility/ImGUI/ImGUI.h"

namespace Framework {
namespace ImGUI {
Button::Button(const std::string& text, CallFunc callFunc)
    :IItem(text), mCallFunc(callFunc) {}

Button::~Button() {}

void Button::draw() {
    if (ImGui::Button(mName.c_str())) {
        mCallFunc();
    }
}

} //ImGUI 
} //Framework
