#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @struct VertexShaderData
* @brief ���_�V�F�[�_�[�̐ݒ�ɕK�v�ȃf�[�^�Q
*/
struct VertexShaderData {
    Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader; //!< ���_�V�F�[�_
    Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout; //!< �C���v�b�g���C�A�E�g
};

} //Graphics 
} //Framework 
