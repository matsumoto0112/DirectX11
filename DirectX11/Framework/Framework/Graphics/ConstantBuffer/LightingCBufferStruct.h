#pragma once

#include "Framework/Define/Render/LightSettings.h"
#include "Framework/Graphics/ConstantBuffer/DirectionalLightCBufferStruct.h"
#include "Framework/Graphics/ConstantBuffer/PointLightCBufferStruct.h"

namespace Framework {
namespace Graphics {

/**
* @struct LightingCBufferStruct
* @brief ライティング用コンスタントバッファ構造体
*/
struct LightingCBufferStruct {
public:
    DirectionalLightCBufferStruct dirLights[Define::LightSettings::DIRECTIONALLIGHT_NUM]; //!< ディレクショナルライト
    PointLightCBufferStruct pLights[Define::LightSettings::POINTLIGHT_NUM]; //!< ポイントライト    
};

} //Graphics 
} //Framework