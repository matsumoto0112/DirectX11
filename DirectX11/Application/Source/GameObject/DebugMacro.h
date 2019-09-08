#pragma once
#define ADD_CHANGE_VECTOR3_PARAMETER_FIELD(name,type,getter,setter,minValue,maxValue) {\
std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name,  getter().##type,[&](float val){ \
    Math::Vector3 v = getter(); \
    v .##type = val; \
    setter(v); \
}); \
field->setMinValue(minValue); \
field->setMaxValue(maxValue); \
window->addItem(field); \
}
