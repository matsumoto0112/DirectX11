#pragma once
#include "Framework/Graphics/Camera/Camera.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector3.h"

#undef near
#undef far

namespace Framework {
namespace Graphics {

/**
* @class PerspectiveCamera
* @brief 透視投影カメラ
*/
class PerspectiveCamera : public Camera {
public:
    /**
    * @struct Info
    * @brief カメラの情報定義
    */
    struct Info {
        Math::Vector3 position; //!< カメラ座標
        Math::Vector3 lookat; //!< カメラ注視点
        Math::Vector3 up; //!< カメラ上方向
        float fov; //!< 視野角（度）
        Math::Vector2 screen; //!< スクリーンの大きさ
        float near; //!< 最近点
        float far; //!< 最遠点
    };
public:
    /**
    * @brief コンストラクタ
    */
    PerspectiveCamera(const Info& info);
    /**
    * @brief デストラクタ
    */
    ~PerspectiveCamera();
    virtual void setPosition(const Math::Vector3& position);
    virtual const Math::Vector3& getPosition() const;
    virtual void setLookat(const Math::Vector3& lookat);
    virtual const Math::Vector3& getLookat() const;
    virtual void setUpVector(const Math::Vector3& up);
    virtual const Math::Vector3& getUpVector() const;
    /**
    * @brief スクリーン座標からワールド座標に変換する
    * @param pos 変換したい座標
    * @param z 射影空間でのZ値
    */
    Math::Vector3 screenToWorldPosition(const Math::Vector2& pos, float z) const;
    /**
    * @brief スクリーン座標からワールド座標に変換する
    * @param pos 変換したい座標
    * @param z 射影空間でのZ値
    * @param screenSize スクリーンの大きさ
    */
    Math::Vector3 screenToWorldPosition(const Math::Vector2& pos, float z, const Math::Vector2& screenSize) const;
private:
    Info mInfo;
};

} //Graphics 
} //Framework 