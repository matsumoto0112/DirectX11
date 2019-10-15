#pragma once

namespace AddField {

void addFloatField(Framework::ImGUI::Window& window, const std::string& name, float& value, float min, float max);
void addFloatField(Framework::ImGUI::Window& window, const std::string& name, int& value, int min, int max);

} //AddField 