#include "ComputeShader.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/Wrap/DirectX.h"
#include "Framework/Graphics/Shader/ComputeShader.h"

using namespace Framework;

namespace {
std::unique_ptr<ImGUI::Window> mWindow;
std::shared_ptr<ImGUI::Text> mText;

struct InputBuffer {
    int i;
};

struct OutputBuffer {
    int i;
};

std::unique_ptr<Graphics::ComputeShader> mComputeShader;
Microsoft::WRL::ComPtr<ID3D11Buffer> mComputeBuffer;
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mComputeBufferSRV;
Microsoft::WRL::ComPtr<ID3D11Buffer> mComputeBuffer2;
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mComputeBufferSRV2;
Microsoft::WRL::ComPtr<ID3D11Buffer> mComputeBufferResult;
Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mComputeBufferResultUAV;
}

ComputeShader::ComputeShader() {
    mWindow = std::make_unique<ImGUI::Window>("Compute Shader Test");
    mText = std::make_shared<ImGUI::Text>("Test");
    mWindow->addItem(mText);

    mComputeShader = std::make_unique<Graphics::ComputeShader>("Compute/TestCompute");

    const int ELEM_SIZE = 16 * 16;
    InputBuffer inputBuffer[ELEM_SIZE], inputBuffer2[ELEM_SIZE];
    for (int i = 0; i < ELEM_SIZE; i++) {
        inputBuffer[i].i = i;
        inputBuffer2[i].i = ELEM_SIZE - i * 2;
    }
    HRESULT hr;

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    desc.ByteWidth = sizeof(InputBuffer) * ELEM_SIZE;
    desc.StructureByteStride = sizeof(InputBuffer);

    D3D11_SUBRESOURCE_DATA sub;
    ZeroMemory(&sub, sizeof(sub));
    sub.pSysMem = inputBuffer;

    hr = Utility::getDevice()->CreateBuffer(&desc, &sub, &mComputeBuffer);

    sub.pSysMem = inputBuffer2;
    hr = Utility::getDevice()->CreateBuffer(&desc, &sub, &mComputeBuffer2);

    hr = Utility::getDevice()->CreateBuffer(&desc, nullptr, &mComputeBufferResult);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
    srvDesc.BufferEx.FirstElement = 0;

    if (desc.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) {
        srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        srvDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
        srvDesc.BufferEx.NumElements = desc.ByteWidth / 4;
    }
    else if (desc.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) {
        srvDesc.Format = DXGI_FORMAT_UNKNOWN;
        srvDesc.BufferEx.NumElements = desc.ByteWidth / desc.StructureByteStride;
    }

    hr = Utility::getDevice()->CreateShaderResourceView(mComputeBuffer.Get(), &srvDesc, &mComputeBufferSRV);
    hr = Utility::getDevice()->CreateShaderResourceView(mComputeBuffer2.Get(), &srvDesc, &mComputeBufferSRV2);

    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
    ZeroMemory(&uavDesc, sizeof(uavDesc));
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;

    if (desc.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS) {
        uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
        uavDesc.Buffer.NumElements = desc.ByteWidth / 4;
    }
    else if (desc.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED) {
        uavDesc.Format = DXGI_FORMAT_UNKNOWN;
        uavDesc.Buffer.NumElements = desc.ByteWidth / desc.StructureByteStride;
    }

    hr = Utility::getDevice()->CreateUnorderedAccessView(mComputeBufferResult.Get(), &uavDesc, &mComputeBufferResultUAV);

    Utility::getContext()->CSSetShader(mComputeShader->mShaderData->mComputeShader.Get(), nullptr, 0);

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srvs[2]{ mComputeBufferSRV,mComputeBufferSRV2 };
    Utility::getContext()->CSSetShaderResources(0, 2, srvs[0].GetAddressOf());

    Utility::getContext()->CSSetUnorderedAccessViews(0, 1, mComputeBufferResultUAV.GetAddressOf(), nullptr);

    Utility::getContext()->Dispatch(1, 1, 1);

    Microsoft::WRL::ComPtr<ID3D11Buffer> resultBuffer;
    mComputeBuffer->GetDesc(&desc);
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    desc.Usage = D3D11_USAGE_STAGING;
    desc.BindFlags = 0;
    desc.MiscFlags = 0;

    hr = Utility::getDevice()->CreateBuffer(&desc, nullptr, &resultBuffer);
    Utility::getContext()->CopyResource(resultBuffer.Get(), mComputeBufferResult.Get());

    D3D11_MAPPED_SUBRESOURCE mappedSub;
    ZeroMemory(&mappedSub, sizeof(mappedSub));

    OutputBuffer* result;

    hr = Utility::getContext()->Map(resultBuffer.Get(), 0, D3D11_MAP_READ, 0, &mappedSub);
    result = static_cast<OutputBuffer*>(mappedSub.pData);
    Utility::getContext()->Unmap(resultBuffer.Get(), 0);
    Utility::StringBuilder sb("");
    for (int i = 0; i < 16; i++) {
        sb << result[i].i << "\n";
    }
    mText->setText(sb);
}

ComputeShader::~ComputeShader() {}


void ComputeShader::load(Scene::Collecter& collecter) {}

void ComputeShader::update() {}

bool ComputeShader::isEndScene() const {
    return false;
}

void ComputeShader::draw(Graphics::IRenderer* renderer) {
    mWindow->draw();
}

void ComputeShader::end() {}

Define::SceneType ComputeShader::next() {
    return Define::SceneType();
}
