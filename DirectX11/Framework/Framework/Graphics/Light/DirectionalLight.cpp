#include "DirectionalLight.h"
#include "Framework/Graphics/ConstantBuffer/DirectionalLightCBufferStruct.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

namespace Framework {
namespace Graphics {

DirectionalLight::DirectionalLight(const Math::Vector3& direction, const Color4& color)
    :mDirection(direction), mColor(color) {}

DirectionalLight::~DirectionalLight() {}

void DirectionalLight::set(DirectionalLightCBufferStruct* cbuffer) {
    cbuffer->direction = mDirection;
    cbuffer->color = mColor;
}

} //Graphics 
} //Framework 
