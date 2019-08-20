#pragma once

#include <vector>
#include <wrl/client.h>
#include <d3d11.h>
#include "Graphics/Buffer/VertexBufferBindData.h"
#include "Graphics/DirectX11GraphicsDevice.h"
#include "Utility/Debug.h"
#include "Utility/Wrap/DirectX.h"

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
    std::unique_ptr<VertexBufferBindData> mData; //!< �f�o�C�X�]���p�f�[�^
};

//�R���X�g���N�^
template<class T>
inline VertexBuffer::VertexBuffer(const std::vector<T>& vertices)
    :mData(std::make_unique<VertexBufferBindData>()) {
    createBuffer(vertices);
}


//���_�o�b�t�@�̍쐬
template<class T>
inline void VertexBuffer::createBuffer(const std::vector<T>& vertices) {
    //���_�̃T�C�Y��ۑ�
    mData->mStride = sizeof(T);
    //�I�t�Z�b�g�͊�{�g�p���Ȃ�
    mData->mOffset = 0;

    //�o�b�t�@�f�[�^�̍쐬
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.ByteWidth = mData->mStride * vertices.size();
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    //�T�u���\�[�X�̍쐬
    D3D11_SUBRESOURCE_DATA subResource;
    ZeroMemory(&subResource, sizeof(subResource));
    subResource.SysMemPitch = 0;
    subResource.SysMemSlicePitch = 0;
    subResource.pSysMem = vertices.data();
    HRESULT hr = Utility::getDevice()->CreateBuffer(&desc, &subResource, &mData->mBuffer);
    if (FAILED(hr)) {
        MY_ASSERTION(false, "���_�o�b�t�@�쐬���s");
    }
}

} //Graphics 
} //Framework 