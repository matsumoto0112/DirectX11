#pragma once
#include <memory>
#include "Source/GameObject/GameObject3D.h"

namespace Framework {
namespace Graphics {
class Cube;
} //Graphics 
} //Framework 

class IMainSceneMediator;

/**
* @class Player
* @brief discription
*/
class Player :public GameObject3D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Player(const Framework::Utility::Transform& transform, IMainSceneMediator& mediator);
    /**
    * @brief �f�X�g���N�^
    */
    ~Player();
    /**
    * @brief �X�V
    */
    virtual void update() override;

    virtual void draw() override;
private:
    IMainSceneMediator& mMediator;
    float mMoveSpeed;
    std::unique_ptr<Framework::Graphics::Cube> mCube;
    Framework::Utility::Transform mCubeTransform;
};