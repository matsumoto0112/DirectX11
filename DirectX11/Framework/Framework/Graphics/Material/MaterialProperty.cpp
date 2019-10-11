#include "MaterialProperty.h"

#define SET_CBUFFER_STRUCT_VALUE_TO_CONSTANTBUFFER(type,variableType ,value) { \
    Utility::getConstantBufferManager()->set ## variableType(type, mData.##value); \
}

#define SET_VALUE_TO_CONSTANTBUFFER(type,variableType) {\
    Utility::getConstantBufferManager()->set ## variableType(type, mData); \
}


namespace Framework {
namespace Graphics {

void WorldMatrix3DProperty::sendBuffer() {
    Utility::getConstantBufferManager()->setMatrix(ConstantBufferParameterType::World3D, mData);
}

void ColorProperty::sendBuffer() {
    SET_VALUE_TO_CONSTANTBUFFER(ConstantBufferParameterType::Color, Color);
}

} //Graphics 
} //Framework 
