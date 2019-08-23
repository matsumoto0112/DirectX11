#pragma once
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Light/Light.h"
#include "Framework/Math/Vector3.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
struct DirectionalLightCBufferStruct;

/**
* @class DirectionalLight
* @brief 平行光源ライト
*/
class DirectionalLight : public Light {
public:
    /**
    * @brief コンストラクタ
    */
    DirectionalLight(const Math::Vector3& direction, const Color4& color);
    /**
    * @brief デストラクタ
    */
    ~DirectionalLight();
    void set(DirectionalLightCBufferStruct* cbuffer);
private:
    PROPERTY(Math::Vector3, mDirection, Direction);
    PROPERTY(Color4, mColor, Color);
};

} //Graphics 
} //Framework 