#include "RandomColorParticle.h"
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

std::unique_ptr<Graphics::ComputeShader> mComputeShader; //!< �R���s���[�g�V�F�[�_
Microsoft::WRL::ComPtr<ID3D11Buffer> mComputeBufferResult; //!< �p�[�e�B�N���p�o�b�t�@
Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mComputeBufferResultUAV; //!< �p�[�e�B�N���pUAV
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB; //<! �O���[�o���f�[�^�p�R���X�^���g�o�b�t�@
Microsoft::WRL::ComPtr<ID3D11Buffer> mRandomTableBuffer; //!< �����e�[�u���o�b�t�@
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mRandomTableSRV; //!< �����e�[�u�����\�[�X
Microsoft::WRL::ComPtr<ID3D11Buffer> mRandomSeedBuffer; //!< �����V�[�h�o�b�t�@
Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mRandomSeedUAV; //!< �����V�[�hUAV
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

    HRESULT hr = Utility::getDevice()->CreateBuffer(&desc, &sub, &buffer);
    MY_ASSERTION(SUCCEEDED(hr), "���s");

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
    srvDesc.BufferEx.FirstElement = 0;
    srvDesc.Format = DXGI_FORMAT_UNKNOWN;
    srvDesc.BufferEx.NumElements = desc.ByteWidth / 4;

    hr = Utility::getDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, &srv);
    MY_ASSERTION(SUCCEEDED(hr), "���s");
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

    HRESULT hr = Utility::getDevice()->CreateBuffer(&desc, &sub, &buffer);
    MY_ASSERTION(SUCCEEDED(hr), "���s");
    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
    ZeroMemory(&uavDesc, sizeof(uavDesc));
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;
    uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
    uavDesc.Buffer.NumElements = desc.ByteWidth / 4;
    uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;

    hr = Utility::getDevice()->CreateUnorderedAccessView(buffer.Get(), &uavDesc, &uav);
    MY_ASSERTION(SUCCEEDED(hr), "���s");
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
    //�J�����̏�����
    m3DCamera = std::make_unique<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Window::getSize(),0.1f,1000.0f });

    m2DCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize());

    //�A���t�@�u�����h�̍쐬
    mAlphaBlend = createAlphaBlend();

    //�R���s���[�g�V�F�[�_�쐬
    Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
    mComputeShader = std::make_unique<Graphics::ComputeShader>("Compute/RandomParticle", info);

    //�p�[�e�B�N���̃f�[�^�쐬
    Particle particle[COUNT];
    for (int i = 0; i < COUNT; i++) {
        //particle[i] = Blackhole{ Math::Vector3::ZERO,0.0f,0.0f,Graphics::Color4::WHITE };
    }
    HRESULT hr;

    float randomTable[RANDOM_MAX];
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance().range(0.0f, 1.0f);
    }

    int randomSeed[1]{ 0 };
    createSRV(sizeof(float), RANDOM_MAX, &randomTable[0], mRandomTableBuffer, mRandomTableSRV);
    createUAV(sizeof(Particle), COUNT, &particle[0], mComputeBufferResult, mComputeBufferResultUAV);
    createUAV(sizeof(int), 1, &randomSeed[0], mRandomSeedBuffer, mRandomSeedUAV);

    //�e�N�X�`���ǂݍ���
    Utility::getResourceManager()->getTexture()->importResource(Define::TextureType::Smoke, Define::TextureName::SMOKE);
    mTexture = Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Smoke);


    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
    mGS = std::make_unique<Graphics::GeometoryShader>("SimpleParticleGS");
    mPS = std::make_unique<Graphics::PixelShader>("2D/Texture2D_Color_PS");

    const std::vector<D3D11_INPUT_ELEMENT_DESC>	layouts =
    {
        { "IN_TIME",    0, DXGI_FORMAT_R32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "POSITION",       0, DXGI_FORMAT_R32G32B32_FLOAT,          0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "IN_VELOCITY", 0, DXGI_FORMAT_R32G32B32_FLOAT,          0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,          0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    mVS = std::make_unique<Graphics::VertexShader>("2D/NoActionVS", layouts);

    //���X�^���C�U�쐬
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    Utility::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    Utility::getContext()->RSSetState(ras.Get());

    mTimer = std::make_unique<Utility::Timer>(10.0f);
    mTimer->init();

    mGlobal.emit = 1;
    mWindow = std::make_unique<ImGUI::Window>("Brackhole");
}

RandomColorParticle::~RandomColorParticle() {}

void RandomColorParticle::load(Framework::Scene::Collecter& collecter) {}

void RandomColorParticle::update() {
    mTimer->update(Utility::Time::getInstance().getDeltaTime());

    //UAV�̃Z�b�g
    UINT count = 256;
    //Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> uavs[2] = { mComputeBufferResultUAV,mRandomSeedUAV };
    //Utility::getContext()->CSSetUnorderedAccessViews(0, 2, uavs->GetAddressOf(), &count);
    Utility::getContext()->CSSetUnorderedAccessViews(1, 1, mComputeBufferResultUAV.GetAddressOf(), &count);
    Utility::getContext()->CSSetUnorderedAccessViews(0, 1, mRandomSeedUAV.GetAddressOf(), &count);
    Utility::getContext()->CSSetShaderResources(0, 1, mRandomTableSRV.GetAddressOf());

    mGlobal.deltaTime = Utility::Time::getInstance().getDeltaTime();

    //�O���[�o���f�[�^�̃Z�b�g
    mCB->setBuffer(mGlobal);
    mCB->sendBuffer();

    mGlobal.emit = 0;

    //���s
    mComputeShader->set();

    //UAV�̉��
    ID3D11UnorderedAccessView* nullUAV = nullptr;
    Utility::getContext()->CSSetUnorderedAccessViews(0, 1, &nullUAV, nullptr);
}

bool RandomColorParticle::isEndScene() const {
    return false;
}

void RandomColorParticle::draw(Framework::Graphics::IRenderer* renderer) {
    //���O����
    Utility::getContext()->RSSetState(ras.Get());
    dynamic_cast<Graphics::BackBufferRenderer*>(renderer)->getRenderTarget()->setEnableDepthStencil(false);
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mAlphaBlend->set();
    renderer->setCurrentPerspectiveCamera(m3DCamera.get());
    m3DCamera->render();
    mTexture->setData(Graphics::ShaderInputType::Pixel, 0);

    //�`�揈��
    mVS->set();
    mGS->set();
    mPS->set();
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Math::Matrix4x4 m = Math::Matrix4x4::createScale(Math::Vector3(1.0f, 1.0f, 1.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World, m);
    Utility::getConstantBufferManager()->send();

    UINT stride = sizeof(Particle);
    UINT offset = 0;
    //���_�o�b�t�@���Z�b�g����
    //�p�[�e�B�N���̃o�b�t�@�����̂܂ܓn��
    Utility::getContext()->IASetVertexBuffers(0, 1, mComputeBufferResult.GetAddressOf(), &stride, &offset);
    Utility::getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    Utility::getContext()->Draw(COUNT, 0);

    //���_�o�b�t�@���������
    ID3D11Buffer* nullBuf = nullptr;
    Utility::getContext()->IASetVertexBuffers(0, 1, &nullBuf, &stride, &offset);

    mWindow->draw();
}

void RandomColorParticle::end() {}

Define::SceneType RandomColorParticle::next() {
    return Define::SceneType();
}
