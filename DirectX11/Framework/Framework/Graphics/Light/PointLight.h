#pragma once
#include <vector>
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Light/Light.h"
#include "Framework/Graphics/ConstantBuffer/PointLightCBufferStruct.h"
#include "Framework/Math/Vector3.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class PointLight
* @brief �|�C���g���C�g
*/
class PointLight :public Light {
public:
    /**
    * @brief �R���X�g���N�^
    */
    PointLight(const Math::Vector3& position, const Color4& color, float R, float A);
    /**
    * @brief �f�X�g���N�^
    */
    ~PointLight();
    /**
    * @brief �\���̂ɒl���Z�b�g����
    */
    void set(PointLightCBufferStruct* cbuffer);
private:
    PROPERTY(Math::Vector3, mPosition, Position);
    PROPERTY(Color4, mColor, Color);
    PROPERTY(float, mRange, Range);
    PROPERTY(float, mAttenuation, Attenuation);
};

} //Graphics 
} //Framework 