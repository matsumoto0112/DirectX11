#pragma once

#include <d3d11.h>
#include <wrl/client.h>
namespace Framework {
namespace Graphics {

/**
* @struct GeometoryShaderData
* @brief �W�I���g���V�F�[�_�̐ݒ�ɕK�v�ȃf�[�^�Q
*/
struct GeometoryShaderData {
    Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGeometoryShader; //!< �W�I���g���V�F�[�_
};

} //Graphics 
} //Framework 
