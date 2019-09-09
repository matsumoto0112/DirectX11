#pragma once
#include "Source/GameObject/Collidable3DObject.h"

/**
* @class Item
* @brief �A�C�e�����N���X
*/
class Item :public Collidable3DObject {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Item(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    ~Item();
    /**
    * @brief �X�V
    */
    virtual void update() override;
    /**
    * @brief �f�B�X�p�b�`�֐�
    */
    virtual void dispatch(Collidable3DObject* other) override;
    /**
    * @brief �v���C���[�Ƃ̏Փˎ�����
    */
    virtual void hit(Player* other) override;
    /**
    * @brief �R���C�_�[���쐬����
    */
    virtual std::unique_ptr<Collider> createCollider() override;
private:
};