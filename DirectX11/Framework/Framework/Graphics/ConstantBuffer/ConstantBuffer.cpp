#include "ConstantBuffer.h"

namespace {
    using  Framework::Graphics::ShaderInputType;
    void switchSet(ID3D11DeviceContext* context, ShaderInputType inputType, UINT registerNum, ID3D11Buffer** buffer) {
        //どのシェーダーにデータを送るかはマスクで入ってくる
        if (AND(inputType, ShaderInputType::Vertex)) {
            context->VSSetConstantBuffers(registerNum, 1, buffer);
        }
        if (AND(inputType, ShaderInputType::Pixel)) {
            context->PSSetConstantBuffers(registerNum, 1, buffer);
        }
        if (AND(inputType, ShaderInputType::Geometory)) {
            context->GSSetConstantBuffers(registerNum, 1, buffer);
        }
        if (AND(inputType, ShaderInputType::Compute)) {
            context->CSSetConstantBuffers(registerNum, 1, buffer);
        }
    }
}

namespace Framework {
    namespace Graphics {
        ConstantBuffer::ConstantBuffer(ID3D11Device * device, UINT size, ShaderInputType inputType, UINT slotNumber)
            :mInputType(inputType), mRegisterNum(slotNumber), mSize(size) {
            //バッファの作成
            D3D11_BUFFER_DESC desc;
            ZeroMemory(&desc, sizeof(desc));
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            desc.ByteWidth = mSize;
            desc.CPUAccessFlags = 0;
            desc.MiscFlags = 0;
            desc.StructureByteStride = 0;

            throwIfFailed(device->CreateBuffer(&desc, nullptr, &mConstantBuffer));
        }
        ConstantBuffer::~ConstantBuffer() { }

        void ConstantBuffer::updateBuffer(ID3D11DeviceContext* context, void* data) {
            context->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr,
                data, 0, 0);
        }

        void ConstantBuffer::set(ID3D11DeviceContext* context) {
            switchSet(context, mInputType, mRegisterNum, mConstantBuffer.GetAddressOf());
        }

        void ConstantBuffer::clear(ID3D11DeviceContext* context) {
            switchSet(context, mInputType, mRegisterNum, nullptr);
        }

    } //Graphics 
} //Framework 
