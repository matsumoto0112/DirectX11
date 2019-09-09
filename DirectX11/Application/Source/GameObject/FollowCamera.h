#pragma once
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/Transform.h"

/**
* @class FollowCamera
* @brief �v���C���[��ǔ�����J����
*/
class FollowCamera : public Framework::Graphics::Camera {
public:
    /**
    * @brief �R���X�g���N�^
    */
    FollowCamera(const Framework::Graphics::PerspectiveCamera::Info& info,
        Framework::Utility::Transform* targetTransform);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~FollowCamera();
    /**
    * @brief �`�揀��������
    */
    virtual void render() override;
private:
    Framework::Math::Matrix4x4 mLocalMatrix; //!<
    Framework::Utility::Transform mCameraTransform;
};