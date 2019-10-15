#include "AddField.h"

using namespace Framework::ImGUI;

void AddField::addFloatField(Window& window, const std::string& name, float& value, float min, float max) {
    std::shared_ptr<FloatField> field = std::make_shared<FloatField>(name, value, [&](float val) {value = val; }); \
        window.addItem(field); \
        field->setMinValue(min); \
        field->setMaxValue(max); \
}

void AddField::addIntField(Framework::ImGUI::Window & window, const std::string & name, int & value, int min, int max) {
    std::shared_ptr<IntField> field = std::make_shared<IntField>(name, value, [&](int val) {value = val; }); \
        window.addItem(field); \
        field->setMinValue(min); \
        field->setMaxValue(max); \
}
