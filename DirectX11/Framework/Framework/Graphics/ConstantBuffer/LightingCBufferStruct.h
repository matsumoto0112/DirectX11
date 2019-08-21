#pragma once

#include "Framework/Define/Render/LightSettings.h"
#include "Framework/Graphics/ConstantBuffer/DirectionalLightCBufferStruct.h"
#include "Framework/Graphics/ConstantBuffer/PointLightCBufferStruct.h"

namespace Framework {
namespace Graphics {

/**
* @struct LightingCBufferStruct
* @brief ���C�e�B���O�p�R���X�^���g�o�b�t�@�\����
*/
struct LightingCBufferStruct {
public:
    DirectionalLightCBufferStruct dirLights[Define::LightSettings::DIRECTIONALLIGHT_NUM]; //!< �f�B���N�V���i�����C�g
    PointLightCBufferStruct pLights[Define::LightSettings::POINTLIGHT_NUM]; //!< �|�C���g���C�g    
};

} //Graphics 
} //Framework