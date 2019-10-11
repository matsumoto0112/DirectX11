#include "ModelMaterial.h"

namespace Framework {
namespace Graphics {
ModelMaterial::ModelMaterial()
    :mWorldMatrix(), mColor() { }

ModelMaterial::~ModelMaterial() { }

void ModelMaterial::set() {
    mWorldMatrix.sendBuffer();
    mColor.sendBuffer();
    Utility::getConstantBufferManager()->send();
}

} //Graphics 
} //Framework 
