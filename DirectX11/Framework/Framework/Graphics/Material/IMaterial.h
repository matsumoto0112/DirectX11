#pragma once
#include <vector>
#include "Framework/Graphics/Material/MaterialProperty.h"

namespace Framework {
namespace Graphics {

/**
* @class IMaterial
* @brief discription
*/
class IMaterial {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IMaterial() = default;

    virtual void set() = 0;
};

} //Graphics 
} //Framework 