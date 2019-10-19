#include "IndexBuffer.h"
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
        //コンストラクタ
        IndexBuffer::IndexBuffer(ID3D11Device* device, const std::vector<UINT>& indices, PrimitiveTopology topology) {
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

            throwIfFailed(device->CreateBuffer(&desc, &subResource, &mBuffer));
            mTopology = convert(topology);
        }

        //デストラクタ
        IndexBuffer::~IndexBuffer() { }

        //コンテキストにセットする
        void IndexBuffer::set(ID3D11DeviceContext* context) {
            context->IASetIndexBuffer(mBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
            context->IASetPrimitiveTopology(mTopology);
        }

        //描画命令を送る
        void IndexBuffer::drawCall(ID3D11DeviceContext* context) {
            context->DrawIndexed(mIndexCount, 0, 0);
        }

    } //Graphics 
} //Framework 