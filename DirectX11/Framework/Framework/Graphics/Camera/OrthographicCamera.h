#pragma once

#include "Framework/Graphics/Camera/Camera.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class OrthographicCamera
* @brief 平行投影カメラ
*/
class OrthographicCamera : public Camera {
public:
    /**
    * @brief コンストラクタ
    * @param size 画面サイズ
    */
    OrthographicCamera(const Math::Vector2& size);
    /**
    * @brief デストラクタ
    */
    virtual ~OrthographicCamera();
    /**
    * @brief 座標の設定
    */
    void setPosition(const Math::Vector3& position);
    void setScreenSize(const Math::Vector2& size);
private:
    PROPERTY_READONLY(Math::Vector2, mScreenSize, ScreenSize);
    PROPERTY_READONLY(Math::Vector3, mPosition, Position);
};
} //Graphics 
} //Framework 