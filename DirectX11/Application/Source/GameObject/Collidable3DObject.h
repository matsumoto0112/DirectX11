#pragma once
#include <memory>
#include "Source/GameObject/GameObject3D.h"
#include "Source/GameObject/Collider.h"

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
protected:
    /**
    * @brief �R���C�_�[���쐬����
    */
    virtual std::unique_ptr<Collider> createCollider() = 0;
protected:
    std::unique_ptr<Collider> mCollider; //!< �R���C�_�[
};