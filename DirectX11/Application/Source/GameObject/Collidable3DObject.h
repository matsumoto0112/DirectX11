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
    * @param collider �R���C�_�[
    */
    Collidable3DObject(const Framework::Utility::Transform& transform,
        IMainSceneMediator& mediator,
        Define::ModelType modelType,
        std::unique_ptr<Collider> collider);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Collidable3DObject();
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
    Property<bool> isAlive{ mIsAlive };
protected:
    /**
    * @brief �R���C�_�[���쐬����
    */
    virtual std::unique_ptr<Collider> createCollider() = 0;
protected:
    bool mIsAlive;
    std::unique_ptr<Collider> mCollider; //!< �R���C�_�[
};