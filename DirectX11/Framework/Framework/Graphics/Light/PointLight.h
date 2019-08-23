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
* @brief ポイントライト
*/
class PointLight :public Light {
public:
    /**
    * @brief コンストラクタ
    */
    PointLight(const Math::Vector3& position, const Color4& color, float R, float A);
    /**
    * @brief デストラクタ
    */
    ~PointLight();
    /**
    * @brief 構造体に値をセットする
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