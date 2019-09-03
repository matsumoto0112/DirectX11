#pragma once

#include "Framework/Graphics/Renderer/IInstance.h"

namespace Framework {
namespace Graphics {

/**
* @class OBB
* @brief 3DOBBインスタンス
*/
class Cube : public IInstance {
public:
    /**
    * @brief コンストラクタ
    */
    Cube();
    /**
    * @brief デストラクタ
    */
    ~Cube();
};

} //Graphics 
} //Framework 