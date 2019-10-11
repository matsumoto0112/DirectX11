#pragma once
#include "Framework/Graphics/Material/IMaterial.h"
#include "Framework/Graphics/Material/MaterialProperty.h"

namespace Framework {
namespace Graphics {

/**
* @class ModelMaterial
* @brief モデル用マテリアル
*/
class ModelMaterial :public IMaterial {
public:
    /**
    * @brief コンストラクタ
    */
    ModelMaterial();
    /**
    * @brief デストラクタ
    */
    ~ModelMaterial();
    virtual void set() override;
public:
    WorldMatrix3DProperty mWorldMatrix;
    ColorProperty mColor;
};

} //Graphics 
} //Framework 