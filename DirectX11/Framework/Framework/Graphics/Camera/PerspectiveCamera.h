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
    virtual ~PerspectiveCamera();
    /**
    * @brief �J�����̎��_�̐ݒ�
    */
    virtual void setPosition(const Math::Vector3& position);
    /**
    * @brief �J�����̎��_�̎擾
    */
    virtual const Math::Vector3& getPosition() const;
    /**
    * @brief �J�����̒����_�̐ݒ�
    */
    virtual void setLookat(const Math::Vector3& lookat);
    /**
    * @brief �J�����̒����_�̎擾
    */
    virtual const Math::Vector3& getLookat() const;
    /**
    * @brief �J�����̏�����x�N�g���̐ݒ�
    */
    virtual void setUpVector(const Math::Vector3& up);
    /**
    * @brief �J�����̏�����x�N�g���̎擾
    */
    virtual const Math::Vector3& getUpVector() const;
private:
    Info mInfo; //!< �J�������
};

} //Graphics 
} //Framework 