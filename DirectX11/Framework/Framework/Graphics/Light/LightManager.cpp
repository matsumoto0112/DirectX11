#include "LightManager.h"
#include "Framework/Define/Render/LightSettings.h"
#include "Framework/Graphics/ConstantBuffer/LightingCBufferStruct.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

namespace Framework {
namespace Graphics {
LightManager::LightManager() {}

LightManager::~LightManager() {
    mDirectionalLights.clear();
}

LightManager::DirectionalLightPtr LightManager::addDirectionalLight(Define::DirectionalLightType key,
    const Math::Vector3& direction, const Color4& color) {
    DirectionalLightPtr light = std::make_shared<DirectionalLight>(direction, color);
    mDirectionalLights.emplace(key, light);
    return light;
}

LightManager::PointLightPtr LightManager::addPointLight(Define::PointLightType key,
    const Math::Vector3& position, const Color4& color, float R, float A) {
    PointLightPtr light = std::make_shared<PointLight>(position, color, R, A);
    mPointLights.emplace(key, light);
    return light;
}

void LightManager::set() {
    LightingCBufferStruct cbuffer;
    unsigned int lightIndex = 0;
    for (auto&& light : mDirectionalLights) {
        MY_ASSERTION(lightIndex < Define::LightSettings::DIRECTIONALLIGHT_NUM,
            "ディレクショナルライトの上限に達しています");
        light.second->set(&cbuffer.dirLights[lightIndex]);
        lightIndex++;
    }

    lightIndex = 0;
    for (auto&& light : mPointLights) {
        MY_ASSERTION(lightIndex < Define::LightSettings::POINTLIGHT_NUM,
            "ポイントライトの上限に達しています");
        light.second->set(&cbuffer.pLights[lightIndex]);
        lightIndex++;
    }

    Utility::getConstantBufferManager()->setStruct(cbuffer);
}

} //Graphics 
} //Framework 
