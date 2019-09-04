#pragma once
#include <memory>
#include "Framework/Utility/Transform.h"
#include "Framework/Utility/Property.h"
#include "Source/GameObject/IMainSceneMediator.h"

/**
* @class GameObject
* @brief �Q�[���I�u�W�F�N�g���N���X
*/
class GameObject {
public:
    /**
    * @brief �R���X�g���N�^
    */
    GameObject(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator)
        :mMediator(mediator), mTransform(transform) {};
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~GameObject() = default;
    virtual void update() {};
    virtual void draw() {};

    ReadonlyProperty<Framework::Utility::Transform> transform{ mTransform };
protected:
    IMainSceneMediator& mMediator; //!< ���C���V�[�������
    Framework::Utility::Transform mTransform;
};