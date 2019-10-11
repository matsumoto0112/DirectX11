#pragma once
#include "Framework/Graphics/Material/IMaterial.h"
#include "Framework/Graphics/Material/MaterialProperty.h"

namespace Framework {
namespace Graphics {

/**
* @class ModelMaterial
* @brief ���f���p�}�e���A��
*/
class ModelMaterial :public IMaterial {
public:
    /**
    * @brief �R���X�g���N�^
    */
    ModelMaterial();
    /**
    * @brief �f�X�g���N�^
    */
    ~ModelMaterial();
    virtual void set() override;
public:
    WorldMatrix3DProperty mWorldMatrix;
    ColorProperty mColor;
};

} //Graphics 
} //Framework 