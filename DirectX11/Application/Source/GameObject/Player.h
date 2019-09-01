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
    * @brief コンストラクタ
    */
    Player(const Framework::Utility::Transform& transform);
    /**
    * @brief デストラクタ
    */
    ~Player();
    virtual void update() override;
    virtual void draw() override;
private:
    float mMoveSpeed;
    std::shared_ptr<Framework::Graphics::Model> mModel;
};