#pragma once

#include <wrl/client.h>
#include <d3d11.h>

namespace Framework {
namespace Graphics {

/**
* @struct VertexBufferBindData
* @brief ���_�o�b�t�@�̃o�C���h�ɕK�v�ȃf�[�^�Q
*/
struct VertexBufferBindData {
    Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer; //!< �o�b�t�@
    UINT mStride; //!< 1���_�̃T�C�Y
    UINT mOffset; //!< ���_�z��̃I�t�Z�b�g�l
};

} //Graphics 
} //Framework 