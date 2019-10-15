#include "IntField.h"
#include "Framework/Utility/ImGUI/ImGUI.h"

namespace Framework {
namespace ImGUI {
IntField::IntField(const std::string& text, int defaultValue, CallFunc callFunc)
    :IItem(text), mCallFunc(callFunc), mValue(defaultValue), mMinValue(0.0f), mMaxValue(1.0f) { }

IntField::~IntField() { }

void IntField::draw() {
    if (ImGui::SliderInt(mName.c_str(), &mValue, mMinValue, mMaxValue) && mCallFunc) {
        mCallFunc(mValue);
    }
}

} //Imgui 
} //Framework 
