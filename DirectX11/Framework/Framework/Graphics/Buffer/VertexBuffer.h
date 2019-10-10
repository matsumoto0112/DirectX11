#pragma once
#include <vector>
#include <d3d11.h>
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Graphics {

/**
* @class VertexBuffer
* @brief ���_�o�b�t�@�Ǘ�
*/
class VertexBuffer {
public:
    /**
    * @brief �R���X�g���N�^
    * @tparam vertices ���_�f�[�^
    */
    template<class T>
    VertexBuffer(const std::vector<T>& vertices);
    /**
    * @brief �f�X�g���N�^
    */
    ~VertexBuffer();
    /**
    * @brief ���_�f�[�^�̃Z�b�g
    */
    void setData();
private:
    /**
    * @brief ���_�o�b�t�@�̍쐬
    * @tparam vertices ���_�f�[�^
    */
    template<class T>
    void createBuffer(const std::vector<T>& vertices);
private:
    ComPtr<ID3D11Buffer> mBuffer; //!< �o�b�t�@
    UINT mStride; //!< 1���_�̃T�C�Y
    UINT mOffset; //!< ���_�z��̃I�t�Z�b�g�l
};

//�R���X�g���N�^
template<class T>
inline VertexBuffer::VertexBuffer(const std::vector<T>& vertices) {
    createBuffer(vertices);
}


//���_�o�b�t�@�̍쐬
template<class T>
inline void VertexBuffer::createBuffer(const std::vector<T>& vertices) {
    //���_�̃T�C�Y��ۑ�
    mStride = sizeof(T);
    //�I�t�Z�b�g�͊�{�g�p���Ȃ�
    mOffset = 0;

    //�o�b�t�@�f�[�^�̍쐬
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.ByteWidth = mStride * static_cast<UINT>(vertices.size());
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    //�T�u���\�[�X�̍쐬
    D3D11_SUBRESOURCE_DATA subResource;
    ZeroMemory(&subResource, sizeof(subResource));
    subResource.SysMemPitch = 0;
    subResource.SysMemSlicePitch = 0;
    subResource.pSysMem = vertices.data();
    throwIfFailed( DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, &subResource, &mBuffer));
}

} //Graphics 
} //Framework 