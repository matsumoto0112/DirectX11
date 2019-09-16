#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @struct ComputeShaderData
* @brief �R���s���[�g�V�F�[�_�̐ݒ�ɕK�v�ȃf�[�^�Q
*/
struct ComputeShaderData {
    Microsoft::WRL::ComPtr<ID3D11ComputeShader> mComputeShader; //!< �s�N�Z���V�F�[�_
};

} //Graphics 
} //Framework 
