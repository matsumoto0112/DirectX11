#pragma once
#include <memory>
#include "Source/GameObject/GameObject.h"

namespace Framework {
namespace Graphics {
class Model;
} //Graphics 
} //Framework 

/**
* @class Player
* @brief discription
*/
class Player :public GameObject {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Player(const Framework::Utility::Transform& transform);
    /**
    * @brief �f�X�g���N�^
    */
    ~Player();
    virtual void update() override;
    virtual void draw() override;
private:
    float mMoveSpeed;
    std::shared_ptr<Framework::Graphics::Model> mModel;
};