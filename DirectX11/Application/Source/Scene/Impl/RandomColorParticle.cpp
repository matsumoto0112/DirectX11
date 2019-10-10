#include "RandomColorParticle.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Renderer/Pipeline.h"
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
#include "Framework/Utility/Timer.h"

using namespace Framework;

namespace {
static constexpr int THREAD_X = 16, THREAD_Y = 16;
static constexpr int DISPATCH_X = 8, DISPATCH_Y = 8;
static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
static constexpr int RANDOM_MAX = 65535;

struct Particle {
    float lifeTime;
    Math::Vector3 position;
    Math::Vector3 velocity;
    Graphics::Color4 color;
};

struct GlobalData {
    float deltaTime;
    int emit;
    float dummy[2];
};

std::unique_ptr<Graphics::ComputeShader> mComputeShader; //!< コンピュートシェーダ
Microsoft::WRL::ComPtr<ID3D11Buffer> mComputeBufferResult; //!< パーティクル用バッファ
Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mComputeBufferResultUAV; //!< パーティクル用UAV
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB; //<! グローバルデータ用コンスタントバッファ
Microsoft::WRL::ComPtr<ID3D11Buffer> mRandomTableBuffer; //!< 乱数テーブルバッファ
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mRandomTableSRV; //!< 乱数テーブルリソース
Microsoft::WRL::ComPtr<ID3D11Buffer> mRandomSeedBuffer; //!< 乱数シードバッファ
Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mRandomSeedUAV; //!< 乱数シードUAV
std::shared_ptr<Graphics::Texture> mTexture;
std::unique_ptr<Graphics::GeometoryShader> mGS;
std::unique_ptr<Graphics::VertexShader> mVS;
std::unique_ptr<Graphics::PixelShader> mPS;
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
std::unique_ptr<Utility::Timer> mTimer;
GlobalData mGlobal;
std::unique_ptr<ImGUI::Window> mWindow;

template<class T>
void createSRV(int elemSize, int count, T* tArray,
    Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer,
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& srv) {
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    desc.ByteWidth = count * elemSize;
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    desc.StructureByteStride = elemSize;

    D3D11_SUBRESOURCE_DATA sub;
    sub.pSysMem = tArray;

    HRESULT hr = Graphics::DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, &sub, &buffer);
    MY_ASSERTION(SUCCEEDED(hr), "失敗");

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
    srvDesc.BufferEx.FirstElement = 0;
    srvDesc.Format = DXGI_FORMAT_UNKNOWN;
    srvDesc.BufferEx.NumElements = desc.ByteWidth / 4;

    hr = Graphics::DX11InterfaceAccessor::getDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, &srv);
    MY_ASSERTION(SUCCEEDED(hr), "失敗");
}

template <class T>
void createUAV(int elemSize, int count, T* particle,
    Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer,
    Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>& uav) {
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
    desc.ByteWidth = elemSize * count;
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
    desc.StructureByteStride = elemSize;

    D3D11_SUBRESOURCE_DATA sub;
    sub.pSysMem = particle;

    HRESULT hr = Graphics::DX11InterfaceAccessor::getDevice()->CreateBuffer(&desc, &sub, &buffer);
    MY_ASSERTION(SUCCEEDED(hr), "失敗");
    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
    ZeroMemory(&uavDesc, sizeof(uavDesc));
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;
    uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
    uavDesc.Buffer.NumElements = desc.ByteWidth / 4;
    uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;

    hr = Graphics::DX11InterfaceAccessor::getDevice()->CreateUnorderedAccessView(buffer.Get(), &uavDesc, &uav);
    MY_ASSERTION(SUCCEEDED(hr), "失敗");
}

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAddBlendDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}
}


RandomColorParticle::RandomColorParticle() {
    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,1000.0f });

    m2DCamera = std::make_shared<Graphics::OrthographicCamera>(Define::Config::getInstance()->getSize());

    //アルファブレンドの作成
    mAlphaBlend = createAlphaBlend();

    //コンピュートシェーダ作成
    Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
    mComputeShader = std::make_unique<Graphics::ComputeShader>("Compute/RandomParticle", info);

    //パーティクルのデータ作成
    Particle particle[COUNT];
    for (int i = 0; i < COUNT; i++) {
        //particle[i] = Blackhole{ Math::Vector3::ZERO,0.0f,0.0f,Graphics::Color4::WHITE };
    }

    float randomTable[RANDOM_MAX];
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance()->range(0.0f, 1.0f);
    }

    int randomSeed[1]{ 0 };
    createSRV(sizeof(float), RANDOM_MAX, &randomTable[0], mRandomTableBuffer, mRandomTableSRV);
    createUAV(sizeof(Particle), COUNT, &particle[0], mComputeBufferResult, mComputeBufferResultUAV);
    createUAV(sizeof(int), 1, &randomSeed[0], mRandomSeedBuffer, mRandomSeedUAV);

    //テクスチャ読み込み
    mTexture = Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Smoke);

    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
    mGS = std::make_unique<Graphics::GeometoryShader>("SimpleParticleGS");
    mPS = std::make_unique<Graphics::PixelShader>("2D/Texture2D_Color_PS");
    mVS = std::make_unique<Graphics::VertexShader>("2D/NoActionVS");

    //ラスタライザ作成
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    Graphics::DX11InterfaceAccessor::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());

    mTimer = std::make_unique<Utility::Timer>(10.0f);
    mTimer->init();

    mGlobal.emit = 1;
    mWindow = std::make_unique<ImGUI::Window>("Brackhole");
}

RandomColorParticle::~RandomColorParticle() {}

void RandomColorParticle::load(Framework::Scene::Collecter& collecter) {}

void RandomColorParticle::update() {
    mTimer->update(Utility::Time::getInstance()->getDeltaTime());

    //UAVのセット
    UINT count = 256;
    //Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> uavs[2] = { mComputeBufferResultUAV,mRandomSeedUAV };
    //Graphics::DX11InterfaceAccessor::getContext()->CSSetUnorderedAccessViews(0, 2, uavs->GetAddressOf(), &count);
    Graphics::DX11InterfaceAccessor::getContext()->CSSetUnorderedAccessViews(1, 1, mComputeBufferResultUAV.GetAddressOf(), &count);
    Graphics::DX11InterfaceAccessor::getContext()->CSSetUnorderedAccessViews(0, 1, mRandomSeedUAV.GetAddressOf(), &count);
    Graphics::DX11InterfaceAccessor::getContext()->CSSetShaderResources(0, 1, mRandomTableSRV.GetAddressOf());

    mGlobal.deltaTime = Utility::Time::getInstance()->getDeltaTime();

    //グローバルデータのセット
    mCB->setBuffer(mGlobal);
    mCB->sendBuffer();

    mGlobal.emit = 0;

    //実行
    mComputeShader->set();

    //UAVの解放
    ID3D11UnorderedAccessView* nullUAV = nullptr;
    Graphics::DX11InterfaceAccessor::getContext()->CSSetUnorderedAccessViews(0, 1, &nullUAV, nullptr);
}

bool RandomColorParticle::isEndScene() const {
    return false;
}

void RandomColorParticle::draw(Framework::Graphics::Pipeline* pipeline) {
    ////事前準備
    //Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());
    //dynamic_cast<Graphics::BackBufferRenderer*>(pipeline)->getRenderTarget()->setEnableDepthStencil(false);
    //pipeline->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    //mAlphaBlend->set();
    //Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    //Utility::getCameraManager()->setOrthographicCamera(m2DCamera);
    //mTexture->setData(Graphics::ShaderInputType::Pixel, 0);

    ////描画処理
    //mVS->set();
    //mGS->set();
    //mPS->set();
    //Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    //Math::Matrix4x4 m = Math::Matrix4x4::createScale(Math::Vector3(1.0f, 1.0f, 1.0f));
    //Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World3D, m);
    //Utility::getConstantBufferManager()->send();

    //UINT stride = sizeof(Particle);
    //UINT offset = 0;
    ////頂点バッファをセットする
    ////パーティクルのバッファをそのまま渡す
    //Graphics::DX11InterfaceAccessor::getContext()->IASetVertexBuffers(0, 1, mComputeBufferResult.GetAddressOf(), &stride, &offset);
    //Graphics::DX11InterfaceAccessor::getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    //Graphics::DX11InterfaceAccessor::getContext()->Draw(COUNT, 0);

    ////頂点バッファを解放する
    //ID3D11Buffer* nullBuf = nullptr;
    //Graphics::DX11InterfaceAccessor::getContext()->IASetVertexBuffers(0, 1, &nullBuf, &stride, &offset);

    //mWindow->draw();
}

void RandomColorParticle::end() {}

Define::SceneType RandomColorParticle::next() {
    return Define::SceneType();
}
