#pragma once
#include <array>

namespace Framework {
namespace Graphics {
class IRenderer;
class ZTexCreater;
} //Graphics
} //Framework 

class Collider;
class Collidable3DObject;
class Floor;
class IMainSceneMediator;
class Wall;

/**
* @class Field
* @brief �Q�[���̃t�B�[���h�Ǘ��N���X
*/
class Field {
public:
    /**
    * @brief �R���X�g���N�^
    * @param mediator ���C���V�[�������
    */
    Field(IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Field();
    /**
    * @brief �Q�[���I�u�W�F�N�g���t�B�[���h���ɉ����߂�
    * @param gameObject ��������Q�[���I�u�W�F�N�g
    */
    virtual void pushBackGameObject(Collidable3DObject& gameObject);
    /**
    * @brief �Q�[���I�u�W�F�N�g���Q�[���G���A�͈̔͊O�ɂ��邩
    */
    virtual bool isGameObjectOutOfArea(Collidable3DObject& gameObject);
    /**
    * @brief �t�B�[���h�̍X�V
    */
    virtual void update();
    /**
    * @brief �ǂ̕`��
    */
    virtual void drawWall(Framework::Graphics::IRenderer* renderer);
    /**
    * @brief �t�B�[���h�̕`�揈��
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer);
    /**
    * @brief �t�B�[���h�̕`�揈��
    */
    virtual void draw(Framework::Graphics::ZTexCreater* renderer);
private:
    std::array<std::unique_ptr<Wall>, 4> mWalls; //!< ��
    std::unique_ptr<Floor> mFloor; //!< ��
};