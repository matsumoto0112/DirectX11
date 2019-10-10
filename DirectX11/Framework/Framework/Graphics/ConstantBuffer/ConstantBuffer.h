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
* @brief コンスタントバッファ
*/
template <class T>
class ConstantBuffer {
public:
    /**
    * @brief コンストラクタ
    * @param graphicsDevice グラフィックデバイス
    * @param inputType どのシェーダに値を設定するか
    * @param slotNum シェーダのどのスロットに値を設定するか
    */
    ConstantBuffer(ShaderInputType inputType, UINT slotNumber);
    /**
    * @brief デストラクタ
    */
    virtual ~ConstantBuffer();
    /**
    * @brief 値の設定
    * @param data 設定する値
    */
    void setBuffer(T data);
    /**
    * @brief バッファの値を転送する
    */
    void sendBuffer();
    /**
    * @brief 現在のコンスタントバッファの値を取得
    */
    T getData() { return mData; }

    void clear();
private:
    T mData; //!< 現在のコンスタントバッファの値
    ComPtr<ID3D11Buffer> mConstantBuffer; //!< コンスタントバッファ
    ShaderInputType mInputType; //!< どのシェーダーにデータを転送するか
    UINT mRegisterNum; //!< シェーダーの登録番号
};

template<class T>
Graphics::ConstantBuffer<T>::ConstantBuffer(ShaderInputType inputType, UINT slotNumber)
    :mInputType(inputType), mRegisterNum(slotNumber) {
    //バッファの作成
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