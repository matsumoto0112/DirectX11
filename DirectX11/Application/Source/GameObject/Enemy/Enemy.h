#pragma once

#include "Source/GameObject/Collidable3DObject.h"

/**
* @class Enemy
* @brief �G�N���X
*/
class Enemy : public Collidable3DObject {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Enemy(const Framework::Utility::Transform& transform,
        const Framework::Graphics::Color4& enemyColor,
        IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    ~Enemy();
    /**
    * @brief ����������
    */
    virtual void initialize() override;
    /**
    * @brief �f�B�X�p�b�`�֐�
    */
    virtual void dispatch(Collidable3DObject* other) override;

    virtual void hit(Player* other) override;
    /**
    * @brief �e�Ƃ̏Փˎ�����
    */
    virtual void hit(Bullet* other) override;
    /**
    * @brief �`��
    */
    virtual void draw() override;
protected:
    /**
    * @brief ���g�̃R���C�_�[���쐬����
    */
    virtual std::unique_ptr<Collider> createCollider() override;
protected:
    Framework::Graphics::Color4 mColor; //!< �F
};