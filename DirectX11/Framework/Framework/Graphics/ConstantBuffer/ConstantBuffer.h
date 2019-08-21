#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <functional>
#include <unordered_map>
#include "Framework/Graphics/Shader/ShaderInputType.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/Wrap/DirectX.h"

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
    /**
    * @brief �o�b�t�@�̓]�����Ɏg�p����֐��̍쐬
    * @param inputType �ǂ̃V�F�[�_�ɒl��ݒ肷�邩
    * @param slotNum �V�F�[�_�̂ǂ̃X���b�g�ɒl��ݒ肷�邩
    */
    std::function<void(void)> createSendBufferFunction(ShaderInputType inputType, UINT slotNumber);
private:
    T mData; //!< ���݂̃R���X�^���g�o�b�t�@�̒l
    Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer; //!< �R���X�^���g�o�b�t�@
    std::function<void(void)> mSendBufferFunction; //!< �o�b�t�@�̓]�����Ɏg�p����֐�
};

template<class T>
Graphics::ConstantBuffer<T>::ConstantBuffer(ShaderInputType inputType, UINT slotNumber) {
    //�o�b�t�@�̍쐬
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.ByteWidth = sizeof(T);
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    HRESULT hr = Utility::getDevice()->CreateBuffer(&desc, nullptr, &mConstantBuffer);
    //�쐬�Ɏ��s������E�B���h�E�\��
    if (FAILED(hr)) {
        MY_ASSERTION(false, "�R���X�^���g�o�b�t�@�쐬���s");
        return;
    }
    mSendBufferFunction = createSendBufferFunction(inputType, slotNumber);
}

template<class T>
inline Graphics::ConstantBuffer<T>::~ConstantBuffer() {}

template<class T>
inline void Graphics::ConstantBuffer<T>::setBuffer(T data) {
    mData = data;
}

template<class T>
inline void Graphics::ConstantBuffer<T>::sendBuffer() {
    Utility::getContext()->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr,
        &mData, 0, 0);
    mSendBufferFunction();
}

template<class T>
inline void Graphics::ConstantBuffer<T>::clear() {
    mData = T();
    Utility::getContext()->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr,
        &mData, 0, 0);
    mSendBufferFunction();
}

template<class T>
inline std::function<void(void)> Graphics::ConstantBuffer<T>::createSendBufferFunction(ShaderInputType inputType, UINT slotNumber) {
    //inputType�ɉ������֐��쐬
    //���_�A�s�N�Z���V�F�[�_�̂ǂ��ɓ]�����邩
    switch (inputType) {
    case ShaderInputType::Vertex:
        return [&, slotNumber]()->void {Utility::getContext()->VSSetConstantBuffers(slotNumber, 1, mConstantBuffer.GetAddressOf()); };
    case ShaderInputType::Pixel:
        return [&, slotNumber]()->void {Utility::getContext()->PSSetConstantBuffers(slotNumber, 1, mConstantBuffer.GetAddressOf()); };
    case ShaderInputType::VertexAndPixel:
        return [&, slotNumber]()->void {
            Utility::getContext()->VSSetConstantBuffers(slotNumber, 1, mConstantBuffer.GetAddressOf());
            Utility::getContext()->PSSetConstantBuffers(slotNumber, 1, mConstantBuffer.GetAddressOf());
        };
    default:
        MY_ASSERTION(false, "����`��ShaderInputType���I������܂����B");
        return NULL;
    }
}

} //Graphics 
} //Framework