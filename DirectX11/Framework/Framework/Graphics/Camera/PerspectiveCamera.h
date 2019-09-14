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
    * @brief コンストラクタ
    */
    PerspectiveCamera(const Math::ViewInfo& view, const Math::ProjectionInfo& proj);
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
protected:
    Math::ViewInfo mViewInfo; //!< ビュー行列情報
    Math::ProjectionInfo mProjInfo; //!< プロジェクション行列情報
};

} //Graphics 
} //Framework 