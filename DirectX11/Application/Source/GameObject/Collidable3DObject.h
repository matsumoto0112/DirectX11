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

    virtual std::unique_ptr<Collider> createCollider() = 0;

    Collider* getCollider() const { return mCollider.get(); }
protected:
    std::unique_ptr<Collider> mCollider; //!< �R���C�_�[
};