#pragma once

#include "Framework/Graphics/Camera/Camera.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class OrthographicCamera
* @brief ���s���e�J����
*/
class OrthographicCamera : public Camera {
public:
    /**
    * @brief �R���X�g���N�^
    * @param size ��ʃT�C�Y
    */
    OrthographicCamera(const Math::Vector2& size);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~OrthographicCamera();
    /**
    * @brief ���W�̐ݒ�
    */
    void setPosition(const Math::Vector3& position);
    void setScreenSize(const Math::Vector2& size);
private:
    PROPERTY_READONLY(Math::Vector2, mScreenSize, ScreenSize);
    PROPERTY_READONLY(Math::Vector3, mPosition, Position);
};
} //Graphics 
} //Framework 