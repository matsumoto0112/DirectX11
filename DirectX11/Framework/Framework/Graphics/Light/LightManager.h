#pragma once
#include <memory>
#include <unordered_map>
#include "Framework/Define/Render/LightType.h"
#include "Framework/Graphics/Light/DirectionalLight.h"

namespace Framework {
namespace Graphics {

/**
* @class LightManager
* @brief discription
*/
class LightManager {
private:
    using DirectionalLightPtr = std::shared_ptr<DirectionalLight>;
    using DirectionalLightMap = std::unordered_map<Define::DirectionalLightType, DirectionalLightPtr >;
public:
    /**
    * @brief コンストラクタ
    */
    LightManager();
    /**
    * @brief デストラクタ
    */
    ~LightManager();
    /**
    * @brief ディレクショナルライトの追加
    * @param key ライトを一意に特定するキー
    * @param direction 方向
    * @param color 色
    */
    DirectionalLightPtr addDirectionalLight(Define::DirectionalLightType key, const Math::Vector3& direction, const Color4& color);
    void set();
private:
    DirectionalLightMap mDirectionalLights;
};

} //Graphics 
} //Framework 