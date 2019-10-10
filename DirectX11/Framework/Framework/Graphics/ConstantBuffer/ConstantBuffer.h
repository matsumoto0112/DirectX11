#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <functional>
#include <unordered_map>
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Resource/ShaderInputType.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Graphics {

/**
* @class ConstantBuffer
* @brief �R���X�^���g�o�b�t�@
*/
template <class T>
class ConstantBuffer {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param inputType �ǂ̃V�F�[�_�ɒl��ݒ肷�邩
    * @param slotNum �V�F�[�_�̂ǂ̃X���b�g�ɒl��ݒ肷�邩
    */
    ConstantBuffer(ShaderInputType inputType, UINT slotNumber);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ConstantBuffer();
    /**
    * @brief �l�̐ݒ�
    * @param data �ݒ肷��l
    */
    void setBuffer(T data);
    /**
    * @brief �o�b�t�@�̒l��]������
    */
    void sendBuffer();
    /**
    * @brief ���݂̃R���X�^���g�o�b�t�@�̒l���擾
    */
    T getData() { return mData; }

    void clear();
private:
    T mData; //!< ���݂̃R���X�^���g�o�b�t�@�̒l
    ComPtr<ID3D11Buffer> mConstantBuffer; //!< �R���X�^���g�o�b�t�@
    ShaderInputType mInputType; //!< �ǂ̃V�F�[�_�[�Ƀf�[�^��]�����邩
    UINT mRegisterNum; //!< �V�F�[�_�[�̓o�^�ԍ�
};

template<class T>
Graphics::ConstantBuffer<T>::ConstantBuffer(ShaderInputType inputType, UINT slotNumber)
    :mInputType(inputType), mRegisterNum(slotNumber) {
    //�o�b�t�@�̍쐬
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.ByteWidth = sizeof(T);
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, nullptr, &mConstantBuffer));
}

template<class T>
inline Graphics::ConstantBuffer<T>::~ConstantBuffer() { }

template<class T>
inline void Graphics::ConstantBuffer<T>::setBuffer(T data) {
    mData = data;
}

template<class T>
inline void Graphics::ConstantBuffer<T>::sendBuffer() {
    DX11InterfaceAccessor::getContext()->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr,
        &mData, 0, 0);
    if (AND(mInputType, ShaderInputType::Vertex)) {
        DX11InterfaceAccessor::getContext()->VSSetConstantBuffers(mRegisterNum, 1, mConstantBuffer.GetAddressOf());
    }
    if (AND(mInputType, ShaderInputType::Pixel)) {
        DX11InterfaceAccessor::getContext()->PSSetConstantBuffers(mRegisterNum, 1, mConstantBuffer.GetAddressOf());
    }
    if (AND(mInputType, ShaderInputType::Geometory)) {
        DX11InterfaceAccessor::getContext()->GSSetConstantBuffers(mRegisterNum, 1, mConstantBuffer.GetAddressOf());
    }
    if (AND(mInputType, ShaderInputType::Compute)) {
        DX11InterfaceAccessor::getContext()->CSSetConstantBuffers(mRegisterNum, 1, mConstantBuffer.GetAddressOf());
    }
}

template<class T>
inline void Graphics::ConstantBuffer<T>::clear() {
    mData = T();
    sendBuffer();
}

} //Graphics 
} //Framework