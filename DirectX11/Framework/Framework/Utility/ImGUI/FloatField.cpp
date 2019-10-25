#include "FloatField.h"
#include "Framework/Utility/ImGUI/ImGUI.h"

namespace Framework {
namespace ImGUI {
FloatField::FloatField(const std::string& text, float defaultValue, CallFunc callFunc)
    :IItem(text), mCallFunc(callFunc), mValue(defaultValue), mMinValue(0.0f), mMaxValue(1.0f) {}

FloatField::FloatField(const std::string & label, float defaultValue) { }

FloatField::~FloatField() {}

void FloatField::draw() {
    if (ImGui::SliderFloat(mName.c_str(), &mValue, mMinValue, mMaxValue) && mCallFunc) {
        mCallFunc(mValue);
    }
}

} //Imgui 
} //Framework 
