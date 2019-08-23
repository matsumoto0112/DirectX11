#pragma once
#include <memory>
#include <unordered_map>
#include "Framework/Define/Render/LightType.h"
#include "Framework/Graphics/Light/DirectionalLight.h"
#include "Framework/Graphics/Light/PointLight.h"

namespace Framework {
namespace Graphics {

/**
* @class LightManager
* @brief discription
*/
class LightManager {
private:
    using DirectionalLightPtr = std::shared_ptr<DirectionalLight>;
    using DirectionalLightMap = std::unordered_map<Define::DirectionalLightType, DirectionalLightPtr>;
    using PointLightPtr = std::shared_ptr<PointLight>;
    using PointLightMap = std::unordered_map<Define::PointLightType, PointLightPtr>;
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
    DirectionalLightPtr addDirectionalLight(
        Define::DirectionalLightType key, const Math::Vector3& direction, const Color4& color);
    /**
    * @brief ポイントライトの追加
    * @param key ライトを一意に特定するキー
    * @param position 座標
    * @param color 色
    * @param R 最大到達距離
    * @param A 減衰率
    */
    PointLightPtr addPointLight(
        Define::PointLightType key, const Math::Vector3& position, const Color4& color, float R, float A);

    void set();
private:
    DirectionalLightMap mDirectionalLights;
    PointLightMap mPointLights;
};

} //Graphics 
} //Framework 