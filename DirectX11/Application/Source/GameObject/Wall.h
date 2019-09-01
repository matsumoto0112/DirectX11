#pragma once
#include "Source/GameObject/GameObject.h"

namespace Framework {
namespace Graphics {
class Model;
} //Graphics 
} //Framework 

/**
* @class Wall
* @brief 壁
*/
class Wall :public GameObject {
public:
    /**
    * @brief コンストラクタ
    */
    Wall(const Framework::Utility::Transform& transform);
    /**
    * @brief デストラクタ
    */
    ~Wall();
    virtual void update();
    virtual void draw();
private:
    std::shared_ptr<Framework::Graphics::Model> mModel;
};