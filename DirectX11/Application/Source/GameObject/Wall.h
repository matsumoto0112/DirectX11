#pragma once
#include "Source/GameObject/GameObject3D.h"

/**
* @class Wall
* @brief 壁
*/
class Wall :public GameObject3D {
public:
    /**
    * @brief コンストラクタ
    */
    Wall(const Framework::Utility::Transform& transform);
    /**
    * @brief デストラクタ
    */
    ~Wall();
private:
};