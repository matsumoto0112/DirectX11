#include "Text.h"
#include "Utility/ImGUI/ImGUI.h"

namespace Framework {
namespace ImGUI {
Text::Text(const std::string& text)
    :IItem(text) {}

Text::~Text() {}

void Text::setText(const std::string& text) {
    mName = text;
}

void Text::draw() {
    ImGui::Text(mName.c_str());
}

} //ImGUI 
} //Framework
