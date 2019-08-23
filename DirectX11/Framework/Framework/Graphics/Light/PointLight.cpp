#include "PointLight.h"

namespace Framework {
namespace Graphics {

PointLight::PointLight(const Math::Vector3& position,
    const Color4& color, float R, float A)
    :mPosition(position),
    mColor(color),
    mRange(R),
    mAttenuation(A) {}

PointLight::~PointLight() {}

void PointLight::set(PointLightCBufferStruct* cbuffer) {
    cbuffer->light = mPosition;
    cbuffer->color = mColor;
    cbuffer->R = mRange;
    cbuffer->A = mAttenuation;
}

} //Graphics 
} //Framework 
