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
    virtual ~PerspectiveCamera();
    /**
    * @brief カメラの視点の設定
    */
    virtual void setPosition(const Math::Vector3& position);
    /**
    * @brief カメラの視点の取得
    */
    virtual const Math::Vector3& getPosition() const;
    /**
    * @brief カメラの注視点の設定
    */
    virtual void setLookat(const Math::Vector3& lookat);
    /**
    * @brief カメラの注視点の取得
    */
    virtual const Math::Vector3& getLookat() const;
    /**
    * @brief カメラの上方向ベクトルの設定
    */
    virtual void setUpVector(const Math::Vector3& up);
    /**
    * @brief カメラの上方向ベクトルの取得
    */
    virtual const Math::Vector3& getUpVector() const;
private:
    Info mInfo; //!< カメラ情報
};

} //Graphics 
} //Framework 