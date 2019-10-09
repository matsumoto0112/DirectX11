#pragma once
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Camera
* @brief カメラ基底クラス
*/
class Camera {
public:
    /**
    * @brief コンストラクタ
    */
    Camera(const Math::Matrix4x4& view, const Math::Matrix4x4& proj);
    /**
    * @brief デストラクタ
    */
    ~Camera();
    /**
    * @brief 描画準備をする
    */
    virtual void render();
    /**
    * @brief スクリーン座標からワールド座標に変換する
    * @param pos 変換したい座標
    * @param z 射影空間でのZ値
    * @param screenSize スクリーンの大きさ
    */
    Math::Vector3 screenToWorldPosition(const Math::Vector2& pos, float z, const Math::Vector2& screenSize) const;

protected:
    PROPERTY(Math::Matrix4x4, mView, View);
    PROPERTY(Math::Matrix4x4, mProjection, Projection);
};

} //Graphics 
} //Framework 