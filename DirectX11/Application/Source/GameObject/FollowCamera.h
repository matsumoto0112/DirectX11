#pragma once
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/Transform.h"

/**
* @class FollowCamera
* @brief プレイヤーを追尾するカメラ
*/
class FollowCamera : public Framework::Graphics::Camera {
public:
    /**
    * @brief コンストラクタ
    */
    FollowCamera(const Framework::Math::ViewInfo& viewInfo,
        const Framework::Math::ProjectionInfo& projInfo,
        Framework::Utility::Transform* targetTransform);
    /**
    * @brief デストラクタ
    */
    virtual ~FollowCamera();
    /**
    * @brief 描画準備をする
    */
    virtual void render() override;
private:
    Framework::Math::Matrix4x4 mLocalMatrix; //!<
    Framework::Utility::Transform mCameraTransform;
};