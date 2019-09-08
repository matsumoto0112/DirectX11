#pragma once
#include <memory>
#include "Source/GameObject/GameObject3D.h"
#include "Source/GameObject/Collider.h"

class Player;
class Bullet;
class Enemy;

/**
* @class Collidable3DObject
* @brief �Փˉ\��3D�I�u�W�F�N�g
*/
class Collidable3DObject : public GameObject3D {
public:
    /**
    * @brief �R���X�g���N�^
    * @param transform �g�����X�t�H�[��
    * @param mediator ���C���V�[�������
    * @param modelType ���f���̎��
    */
    Collidable3DObject(const Framework::Utility::Transform& transform,
        IMainSceneMediator& mediator,
        Define::ModelType modelType);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Collidable3DObject();
    /**
    * @brief ������
    */
    virtual void initialize() override;
    /**
    * @brief �`��
    */
    virtual void draw() override;
    /**
    * @brief �R���C�_�[�|�C���^���擾����
    */
    Collider* getColliderPtr() const { return mCollider.get(); }

    virtual void dispatch(Collidable3DObject* other) = 0;
    virtual void hit(Player* other) {};
    virtual void hit(Bullet* other) {};
    virtual void hit(Enemy* other) {};
protected:
    /**
    * @brief �R���C�_�[���쐬����
    */
    virtual std::unique_ptr<Collider> createCollider() = 0;
protected:
    PROPERTY(bool, mIsAlive, IsAlive);
protected:
    std::unique_ptr<Collider> mCollider; //!< �R���C�_�[
};