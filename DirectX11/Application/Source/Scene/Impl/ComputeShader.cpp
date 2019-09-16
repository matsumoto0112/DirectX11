#include "ComputeShader.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/Wrap/DirectX.h"
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Random.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"

using namespace Framework;

namespace {
std::unique_ptr<ImGUI::Window> mWindow;
std::shared_ptr<ImGUI::Text> mText;

static const int COUNT = 256;
struct Particle {
    bool alive;
    float lifeTime;
    Math::Vector3 position;
    Math::Vector3 velocity;
};

struct GlobalData {
    int seed;
    float deltaTime;
    int dummy;
    int dummy2;
};

std::unique_ptr<Graphics::ComputeShader> mComputeShader;
Microsoft::WRL::ComPtr<ID3D11Buffer> mComputeBuffer;
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mComputeBufferSRV;
Microsoft::WRL::ComPtr<ID3D11Buffer> mComputeBufferResult;
Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mComputeBufferResultUAV;
Microsoft::WRL::ComPtr<ID3D11Buffer> mResulrBuffer;
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB;
std::shared_ptr<Graphics::Sprite3D> mSprite;

void createSRV(int elemSize, int count, void* particle) {
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    desc.ByteWidth = count * elemSize;
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    desc.StructureByteStride = elemSize;

    D3D11_SUBRESOURCE_DATA sub;
    sub.pSysMem = particle;

    HRESULT hr = Utility::getDevice()->CreateBuffer(&desc, &sub, &mComputeBuffer);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
    srvDesc.BufferEx.FirstElement = 0;
    srvDesc.Format = DXGI_FORMAT_UNKNOWN;
    srvDesc.BufferEx.NumElements = count;

    hr = Utility::getDevice()->CreateShaderResourceView(mComputeBuffer.Get(), &srvDesc, &mComputeBufferSRV);
}

void createUAV(int elemSize, int count) {
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    desc.ByteWidth = elemSize * count;
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    desc.StructureByteStride = elemSize;

    HRESULT hr = Utility::getDevice()->CreateBuffer(&desc, nullptr, &mComputeBufferResult);
    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
    ZeroMemory(&uavDesc, sizeof(uavDesc));
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;
    uavDesc.Format = DXGI_FORMAT_UNKNOWN;
    uavDesc.Buffer.NumElements = count;

    hr = Utility::getDevice()->CreateUnorderedAccessView(mComputeBufferResult.Get(), &uavDesc, &mComputeBufferResultUAV);
}
}

ComputeShader::ComputeShader() {
    m3DCamera = std::make_unique<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Window::getSize(),0.1f,1000.0f });

    m2DCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize());
    {
        D3D11_BLEND_DESC desc;
        desc.AlphaToCoverageEnable = FALSE;
        desc.IndependentBlendEnable = FALSE;
        desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAddBlendDesc();
        mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(desc);
    }

    mWindow = std::make_unique<ImGUI::Window>("Compute Shader Test");
    mText = std::make_shared<ImGUI::Text>("Test");
    mWindow->addItem(mText);

    mComputeShader = std::make_unique<Graphics::ComputeShader>("Compute/SimpleParticle");

    Particle particle[COUNT];
    for (int i = 0; i < COUNT; i++) {
        particle[i].alive = true;
        particle[i].lifeTime = 10.0f;
        particle[i].position = Math::Vector3(0, -2, 0);
        particle[i].velocity = Math::Vector3(0, 1.0f / 60.0f, 0);
    }

    HRESULT hr;

    createSRV(sizeof(Particle), COUNT, &particle[0]);
    createUAV(sizeof(Particle), COUNT);

    D3D11_BUFFER_DESC desc;
    mComputeBuffer->GetDesc(&desc);
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    desc.Usage = D3D11_USAGE_STAGING;
    desc.BindFlags = 0;
    desc.MiscFlags = 0;

    hr = Utility::getDevice()->CreateBuffer(&desc, nullptr, &mResulrBuffer);

    Utility::getResourceManager()->getTexture()->importResource(Define::TextureType::Smoke, Define::TextureName::SMOKE);
    mSprite = std::make_shared<Graphics::Sprite3D>(Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Smoke));

    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
}

ComputeShader::~ComputeShader() {}


void ComputeShader::load(Scene::Collecter& collecter) {}

void ComputeShader::update() {

    Utility::getContext()->CSSetShader(mComputeShader->mShaderData->mComputeShader.Get(), nullptr, 0);

    Utility::getContext()->CSSetShaderResources(0, 1, mComputeBufferSRV.GetAddressOf());

    Utility::getContext()->CSSetUnorderedAccessViews(0, 1, mComputeBufferResultUAV.GetAddressOf(), nullptr);
    GlobalData global;
    global.deltaTime = Utility::Time::getInstance().getDeltaTime();
    mCB->setBuffer(global);
    mCB->sendBuffer();
    Utility::getContext()->Dispatch(1, 1, 1);

    Utility::getContext()->CopyResource(mResulrBuffer.Get(), mComputeBufferResult.Get());
}

bool ComputeShader::isEndScene() const {
    return false;
}

void ComputeShader::draw(Graphics::IRenderer* renderer) {
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mAlphaBlend->set();
    renderer->setCurrentPerspectiveCamera(m3DCamera.get());
    m3DCamera->render();
    D3D11_MAPPED_SUBRESOURCE mappedSub;
    ZeroMemory(&mappedSub, sizeof(mappedSub));
    Particle* result;
    HRESULT hr = Utility::getContext()->Map(mResulrBuffer.Get(), 0, D3D11_MAP_READ, 0, &mappedSub);
    result = reinterpret_cast<Particle*>(mappedSub.pData);
    Utility::getContext()->Unmap(mResulrBuffer.Get(), 0);
    
    Particle p[COUNT];
    for (int i = 0; i < COUNT; i++) {
        p[i] = result[i];
    }  


    for (int i = 0; i < COUNT; i++) {
        if (!result[i].alive)continue;
        mSprite->setPosition(result[i].position);
        renderer->render(mSprite);
    }

    mWindow->draw();
}

void ComputeShader::end() {}

Define::SceneType ComputeShader::next() {
    return Define::SceneType();
}
