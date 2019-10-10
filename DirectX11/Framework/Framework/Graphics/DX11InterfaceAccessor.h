#pragma once
#include <d3d11.h>
#include "Framework/Utility/TypeDef.h"

namespace Framework {
namespace Graphics {

/**
* @class DX11InterfaceAccessor
* @brief DirectX11�C���^�[�t�F�[�X�A�N�Z�T
*/
class DX11InterfaceAccessor {
public:
    /**
    * @brief �f�o�C�X�̎擾
    */
    static ComPtr<ID3D11Device> getDevice();
    /**
    * @brief �R���e�L�X�g�̎擾
    */
    static ComPtr<ID3D11DeviceContext> getContext();
};

} //Graphics 
} //Framework 