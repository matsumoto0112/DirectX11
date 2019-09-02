#pragma once
#include "Source/GameObject/GameObject3D.h"

/**
* @class Floor
* @brief 床オブジェクト
*/
class Floor :public GameObject3D {
public:
    /**
    * @brief コンストラクタ
    */
    Floor(const Framework::Utility::Transform& transform);
    /**
    * @brief デストラクタ
    */
    ~Floor();
private:

};