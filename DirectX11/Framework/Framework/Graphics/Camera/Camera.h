#pragma once
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Camera
* @brief �J�������N���X
*/
class Camera {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Camera(const Math::Matrix4x4& view, const Math::Matrix4x4& proj);
    /**
    * @brief �f�X�g���N�^
    */
    ~Camera();
    /**
    * @brief �`�揀��������
    */
    virtual void render();
    /**
    * @brief �X�N���[�����W���烏�[���h���W�ɕϊ�����
    * @param pos �ϊ����������W
    * @param z �ˉe��Ԃł�Z�l
    * @param screenSize �X�N���[���̑傫��
    */
    Math::Vector3 screenToWorldPosition(const Math::Vector2& pos, float z, const Math::Vector2& screenSize) const;

protected:
    PROPERTY(Math::Matrix4x4, mView, View);
    PROPERTY(Math::Matrix4x4, mProjection, Projection);
};

} //Graphics 
} //Framework 