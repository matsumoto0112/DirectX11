#pragma once
#include "Framework/Math/3DPrimitive/Primitive3D.h"
#include "Source/GameObject/Collidable3DObject.h"
#include "Source/GameObject/GameObject3D.h"

/**
* @class Wall
* @brief ��
*/
class Wall :public GameObject3D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Wall(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    ~Wall();
    /**
    * @brief �Q�[���I�u�W�F�N�g��ǂ̒��ɉ����߂�
    */
    void pushBackGameObject(Collidable3DObject& gameObject);
    virtual void draw() override;
private:
    Framework::Math::Plane mPlane;
};