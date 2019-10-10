#include "ComputeShader.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Random.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Define/Config.h"

using namespace Framework;

namespace {
std::unique_ptr<ImGUI::Window> mWindow;
std::shared_ptr<ImGUI::Text> mText;

static constexpr int THREAD_X = 4, THREAD_Y = 4;
static constexpr int DISPATCH_X = 4, DISPATCH_Y = 4;
static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
struct Particle {
    float lifeTime;
    Math::Vector3 position;
    Math::Vector3 velocity;
    Graphics::Color4 color;
    int seed;
};

struct GlobalData {
    //int seed;
    float deltaTime;
    int dummy;
    int dummy2;
    int dummy3;
};

std::unique_ptr<Graphics::ComputeShader> mComputeShader;
Microsoft::WRL::ComPtr<ID3D11Buffer> mComputeBufferResult;
Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mComputeBufferResultUAV;
Microsoft::WRL::ComPtr<ID3D11Buffer> mResulrBuffer;
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB;
std::shared_ptr<Graphics::Sprite3D> mSprite;
std::unique_ptr<Graphics::GeometoryShader> mGS;
std::unique_ptr<Graphics::VertexShader> mVS;
std::unique_ptr<Graphics::PixelShader> mPS;
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;

void createUAV(int elemSize, int count, Particle* particle) {
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    desc.ByteWidth = elemSize * count;
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
    desc.StructureByteStride = elemSize;

    D3D11_SUBRESOURCE_DATA sub;
    sub.pSysMem = particle;

    HRESULT hr = Graphics::DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, &sub, &mComputeBufferResult);
    MY_ASSERTION(SUCCEEDED(hr), "Ž¸”s");
    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
    ZeroMemory(&uavDesc, sizeof(uavDesc));
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;
    uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
    uavDesc.Buffer.NumElements = sizeof(Particle) * count / sizeof(int);
    uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;

    hr = Graphics::DX11InterfaceAccessor::getDevice()->CreateUnorderedAccessView(mComputeBufferResult.Get(), &uavDesc, &mComputeBufferResultUAV);
    MY_ASSERTION(SUCCEEDED(hr), "Ž¸”s");
}
}

ComputeShader::ComputeShader() {
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,1000.0f });

    m2DCamera = std::make_shared<Graphics::OrthographicCamera>(Define::Config::getInstance()->getSize());
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

    Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
    mComputeShader = std::make_unique<Graphics::ComputeShader>("Compute/SimpleParticle", info);

    Particle particle[COUNT];
    for (int i = 0; i < COUNT; i++) {
        //float life = Utility::Random::getInstance()->range(5.0f, 10.0f);
        //particle[i].lifeTime = -1;
        ////particle[i].lifeTime = 13;

        //particle[i].position = Math::Vector3(0, -2, 0);
        //float x = Utility::Random::getInstance()->range(-3.0f, 3.0f);
        //float y = Utility::Random::getInstance()->range(0.5f, 2.0f);
        //particle[i].velocity = Math::Vector3(x, y, 0);
        //par
        //particle[i].velocity = Math::Vector3(17, 19, 23);
        particle[i].seed = Utility::Random::getInstance()->range(0, (int)(INT_MAX / 2));
    }

    HRESULT hr;

    createUAV(sizeof(Particle), COUNT, &particle[0]);

    D3D11_BUFFER_DESC desc;
    mComputeBufferResult->GetDesc(&desc);
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    desc.Usage = D3D11_USAGE_STAGING;
    desc.BindFlags = 0;
    desc.MiscFlags = 0;

    hr = Graphics::DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, nullptr, &mResulrBuffer);
    MY_ASSERTION(SUCCEEDED(hr), "Ž¸”s");

    mSprite = std::make_shared<Graphics::Sprite3D>(Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Smoke));

    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);

    mGS = std::make_unique<Graphics::GeometoryShader>("SimpleParticleGS");
    mPS = std::make_unique<Graphics::PixelShader>("2D/Texture2D_Color_PS");
    mVS = std::make_unique<Graphics::VertexShader>("2D/NoActionVS");

    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    rasterizerDesc.DepthClipEnable = FALSE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    Graphics::DX11InterfaceAccessor::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());
}

ComputeShader::~ComputeShader() { }


void ComputeShader::load(Scene::Collecter& collecter) { }

void ComputeShader::update() {
    UINT count = 256;
    Graphics::DX11InterfaceAccessor::getContext()->CSSetUnorderedAccessViews(1, 1, mComputeBufferResultUAV.GetAddressOf(), &count);
    GlobalData global;
    //global.seed = Utility::Random::getInstance()->range(0, (int)(INT_MAX / 2));
    global.deltaTime = Utility::Time::getInstance()->getDeltaTime();
    mCB->setBuffer(global);
    mCB->sendBuffer();

    mComputeShader->set();

    ID3D11UnorderedAccessView* nullUAV = nullptr;
    Graphics::DX11InterfaceAccessor::getContext()->CSSetUnorderedAccessViews(1, 1, &nullUAV, nullptr);

    //mText->setText(Utility::StringBuilder("") << global.seed);
    //Graphics::DX11InterfaceAccessor::getContext()->CopyResource(mResulrBuffer.Get(), mComputeBufferResult.Get());
}

bool ComputeShader::isEndScene() const {
    return false;
}

void ComputeShader::draw(Graphics::IRenderer* renderer) {
    Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());
    dynamic_cast<Graphics::BackBufferRenderer*>(renderer)->getRenderTarget()->setEnableDepthStencil(false);
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mAlphaBlend->set();
    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    mVS->set();
    mGS->set();
    mPS->set();
    UINT stride = sizeof(Particle);
    UINT offset = 0;
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    mSprite->getTexture()->setData(Graphics::ShaderInputType::Pixel, 0);
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World3D, Math::Matrix4x4::identity());
    Utility::getConstantBufferManager()->send();
    Graphics::DX11InterfaceAccessor::getContext()->IASetVertexBuffers(0, 1, mComputeBufferResult.GetAddressOf(), &stride, &offset);
    Graphics::DX11InterfaceAccessor::getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    Graphics::DX11InterfaceAccessor::getContext()->Draw(COUNT, 0);

    ID3D11Buffer* nullBuf = nullptr;
    Graphics::DX11InterfaceAccessor::getContext()->IASetVertexBuffers(0, 1, &nullBuf, &stride, &offset);

    //D3D11_MAPPED_SUBRESOURCE mappedSub;
    //ZeroMemory(&mappedSub, sizeof(mappedSub));
    //Particle* result;
    //HRESULT hr = Graphics::DX11InterfaceAccessor::getContext()->Map(mResulrBuffer.Get(), 0, D3D11_MAP_READ, 0, &mappedSub);
    //result = reinterpret_cast<Particle*>(mappedSub.pData);
    //Graphics::DX11InterfaceAccessor::getContext()->Unmap(mResulrBuffer.Get(), 0);

    //for (int i = 0; i < COUNT; i++) {
    //    if (!result[i].alive)continue;
    //    mSprite->setPosition(result[i].position);
    //    renderer->render(mSprite);
    //}

    mWindow->draw();
}

void ComputeShader::end() { }

Define::SceneType ComputeShader::next() {
    return Define::SceneType();
}
