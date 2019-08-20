#pragma once

#include <d3d11.h>
#include <wrl/client.h>
namespace Framework {
namespace Graphics {

/**
* @struct PixelShaderData
* @brief �s�N�Z���V�F�[�_�̐ݒ�ɕK�v�ȃf�[�^�Q
*/
struct PixelShaderData {
    Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader; //!< �s�N�Z���V�F�[�_
};

} //Graphics 
} //Framework 
