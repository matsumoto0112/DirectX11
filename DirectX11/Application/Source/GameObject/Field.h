#pragma once
#include <array>

class Floor;
class IMainSceneMediator;
class Wall;
class Collider;

/**
* @class Field
* @brief �Q�[���̃t�B�[���h�Ǘ��N���X
*/
class Field {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Field(IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Field();
    virtual void pushBackGameObject(Collider& collider);
    virtual void update();
    virtual void draw();
private:
    std::array<std::unique_ptr<Wall>, 4> mWalls;
    std::unique_ptr<Floor> mFloor;
};