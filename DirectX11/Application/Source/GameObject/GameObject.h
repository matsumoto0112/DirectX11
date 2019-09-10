#pragma once
#include <memory>
#include "Framework/Graphics/Renderer/IRenderer.h"
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
    /**
    * @brief ����������
    */
    virtual void initialize() {};
    /**
    * @brief �X�V
    */
    virtual void update() {};
    /**
    * @brief �`�悷��
    * @param renderer �g�p����`��C���^�[�t�F�[�X
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) {};
    /**
    * @brief �g�����X�t�H�[���̃|�C���^���擾����
    */
    Framework::Utility::Transform* getTransformPtr() { return &mTransform; }
protected:
    IMainSceneMediator& mMediator; //!< ���C���V�[�������
protected:
    PROPERTY(Framework::Utility::Transform, mTransform, Transform);
};