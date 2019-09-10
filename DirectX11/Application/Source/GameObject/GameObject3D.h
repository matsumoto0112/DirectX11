#pragma once
#include "Framework/Define/Resource/Model.h"
#include "Framework/Graphics/Model/Model.h"
#include "Source/GameObject/GameObject.h"

/**
* @class GameObject3D
* @brief 3D�Q�[���I�u�W�F�N�g���N���X
*/
class GameObject3D :public GameObject {
public:
    /**
    * @brief �R���X�g���N�^
    * @param transform ������Ԃ̃g�����X�t�H�[��
    * @param modelType ���f���̎��
    */
    GameObject3D(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator, Define::ModelType modelType);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~GameObject3D();
    /**
    * @brief �`�悷��
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) override;
protected:
    std::shared_ptr<Framework::Graphics::Model> mModel; //!< ���f���f�[�^
};