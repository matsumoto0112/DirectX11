#pragma once
#include <vector>
#include <d3d11.h>
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Graphics {

/**
* @class VertexBuffer
* @brief 頂点バッファ管理
*/
class VertexBuffer {
public:
    /**
    * @brief コンストラクタ
    * @tparam vertices 頂点データ
    */
    template<class T>
    VertexBuffer(const std::vector<T>& vertices);
    /**
    * @brief デストラクタ
    */
    ~VertexBuffer();
    /**
    * @brief 頂点データのセット
    */
    void setData();
private:
    /**
    * @brief 頂点バッファの作成
    * @tparam vertices 頂点データ
    */
    template<class T>
    void createBuffer(const std::vector<T>& vertices);
private:
    ComPtr<ID3D11Buffer> mBuffer; //!< バッファ
    UINT mStride; //!< 1頂点のサイズ
    UINT mOffset; //!< 頂点配列のオフセット値
};

//コンストラクタ
template<class T>
inline VertexBuffer::VertexBuffer(const std::vector<T>& vertices) {
    createBuffer(vertices);
}


//頂点バッファの作成
template<class T>
inline void VertexBuffer::createBuffer(const std::vector<T>& vertices) {
    //頂点のサイズを保存
    mStride = sizeof(T);
    //オフセットは基本使用しない
    mOffset = 0;

    //バッファデータの作成
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.ByteWidth = mStride * static_cast<UINT>(vertices.size());
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    //サブリソースの作成
    D3D11_SUBRESOURCE_DATA subResource;
    ZeroMemory(&subResource, sizeof(subResource));
    subResource.SysMemPitch = 0;
    subResource.SysMemSlicePitch = 0;
    subResource.pSysMem = vertices.data();
    throwIfFailed( DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, &subResource, &mBuffer));
}

} //Graphics 
} //Framework 