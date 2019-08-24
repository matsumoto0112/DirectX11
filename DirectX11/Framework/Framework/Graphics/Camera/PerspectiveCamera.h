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
* @brief �������e�J����
*/
class PerspectiveCamera : public Camera {
public:
    /**
    * @struct Info
    * @brief �J�����̏���`
    */
    struct Info {
        Math::Vector3 position; //!< �J�������W
        Math::Vector3 lookat; //!< �J���������_
        Math::Vector3 up; //!< �J���������
        float fov; //!< ����p�i�x�j
        Math::Vector2 screen; //!< �X�N���[���̑傫��
        float near; //!< �ŋߓ_
        float far; //!< �ŉ��_
    };
public:
    /**
    * @brief �R���X�g���N�^
    */
    PerspectiveCamera(const Info& info);
    /**
    * @brief �f�X�g���N�^
    */
    ~PerspectiveCamera();
    virtual void setPosition(const Math::Vector3& position);
    virtual const Math::Vector3& getPosition() const;
    virtual void setLookat(const Math::Vector3& lookat);
    virtual const Math::Vector3& getLookat() const;
    virtual void setUpVector(const Math::Vector3& up);
    virtual const Math::Vector3& getUpVector() const;
private:
    Info mInfo;
};

} //Graphics 
} //Framework 