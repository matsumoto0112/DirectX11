#include "IndexBuffer.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Utility/Debug.h"

namespace {
//PrimitiveTopologyからD3D11_PRIMITIVE_TOPOLOGYに変換する
D3D11_PRIMITIVE_TOPOLOGY convert(Framework::Graphics::PrimitiveTopology type) {
    using Framework::Graphics::PrimitiveTopology;
    D3D11_PRIMITIVE_TOPOLOGY result;
    switch (type) {
        case PrimitiveTopology::LineList:
            result = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
            break;
        case PrimitiveTopology::TriangleList:
            result = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
            break;
        case PrimitiveTopology::TriangleStrip:
            result = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
            break;
        default:
            MY_ASSERTION(false, "未定義のプリミティブトポロジーの種類が選択されました。");
            break;
    }
    return result;
}
}

namespace Framework {
namespace Graphics {

IndexBuffer::IndexBuffer(const std::vector<UINT>& indices, PrimitiveTopology topology) {
    setBuffer(indices, topology);
}

IndexBuffer::~IndexBuffer() { }

void IndexBuffer::setBuffer(const std::vector<UINT>& indices, PrimitiveTopology topology) {
    mIndexCount = static_cast<UINT>(indices.size());

    //デスクの作成
    D3D11_BUFFER_DESC desc{};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.ByteWidth = sizeof(UINT) * mIndexCount;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    //サブリソース作成
    D3D11_SUBRESOURCE_DATA subResource{};
    subResource.pSysMem = indices.data();
    subResource.SysMemPitch = 0;
    subResource.SysMemSlicePitch = 0;

    HRESULT hr = DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, &subResource, &mBuffer);
    if (FAILED(hr)) {
        MY_ASSERTION(false, "バッファの作成に失敗しました。");
        return;
    }
    mTopology = convert(topology);
}

void IndexBuffer::setData() {
    DX11InterfaceAccessor::getContext()->IASetIndexBuffer(mBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    DX11InterfaceAccessor::getContext()->IASetPrimitiveTopology(mTopology);
}

void IndexBuffer::drawCall() {
    DX11InterfaceAccessor::getContext()->DrawIndexed(mIndexCount, 0, 0);
}

} //Graphics 
} //Framework 