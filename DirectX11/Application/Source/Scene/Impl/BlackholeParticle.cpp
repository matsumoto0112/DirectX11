#include "BlackholeParticle.h"
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
#include "Framework/Graphics/Particle/GPUParticle.h"

using namespace Framework;

namespace {
static constexpr int THREAD_X = 4, THREAD_Y = 4;
static constexpr int DISPATCH_X = 4, DISPATCH_Y = 4;
static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
static constexpr int RANDOM_MAX = 65535;

struct Blackhole {
    Math::Vector3 position;
    float radius;
    float theta;
    Graphics::Color4 color;
};

struct GlobalData {
    int emit;
    float time;
    float deltaTime;
    float dummy[1];
};

std::unique_ptr<Graphics::GPUParticle<Blackhole>> mGPUParticle; //!< �p�[�e�B�N��
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB; //<! �O���[�o���f�[�^�p�R���X�^���g�o�b�t�@
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
std::unique_ptr<Utility::Timer> mTimer;
GlobalData mGlobal;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAddBlendDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}
}

BlackholeParticle::BlackholeParticle() {
    //�J�����̏�����
    m3DCamera = std::make_unique<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Window::getSize(),0.1f,1000.0f });

    m2DCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize());

    //�A���t�@�u�����h�̍쐬
    mAlphaBlend = createAlphaBlend();


    //�R���s���[�g�V�F�[�_�쐬
    Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
    auto cs = std::make_shared<Graphics::ComputeShader>("Particle/Blackhole_CS", info);

    //�p�[�e�B�N���̃f�[�^�쐬
    std::vector<Blackhole> particle(COUNT);
    for (int i = 0; i < COUNT; i++) {
        particle[i] = Blackhole{ Math::Vector3::ZERO,0.0f,0.0f,Graphics::Color4::WHITE };
    }
    cs->addUAVEnableVertexBuffer(0, particle, 0);

    std::vector<float> randomTable(RANDOM_MAX);
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance().range(0.0f, 1.0f);
    }
    cs->addSRV(0, randomTable);

    std::vector<int> randomSeed{ 0 };
    cs->addUAV(1, randomSeed);


    //�e�N�X�`���ǂݍ���
    Utility::getResourceManager()->getTexture()->importResource(Define::TextureType::Smoke, Define::TextureName::SMOKE);

    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
    auto gs = std::make_shared<Graphics::GeometoryShader>("SimpleParticleGS");
    auto ps = std::make_shared<Graphics::PixelShader>("2D/Texture2D_Color_PS");

    const std::vector<D3D11_INPUT_ELEMENT_DESC>	layouts =
    {
        { "POSITION",       0, DXGI_FORMAT_R32G32B32_FLOAT,          0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "IN_RADIUS",       0, DXGI_FORMAT_R32_FLOAT,          0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "IN_THETA",       0, DXGI_FORMAT_R32_FLOAT,          0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,          0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    auto vs = std::make_shared<Graphics::VertexShader>("Particle/Blackhole_VS", layouts);

    mGPUParticle = std::make_unique<Graphics::GPUParticle<Blackhole>>(COUNT,
        Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Smoke),
        cs,
        vs,
        ps,
        gs);


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
}

BlackholeParticle::~BlackholeParticle() {}

void BlackholeParticle::load(Framework::Scene::Collecter & collecter) {}

void BlackholeParticle::update() {
    mTimer->update(Utility::Time::getInstance().getDeltaTime());

    mGlobal.time = Utility::Time::getInstance().getTime();
    mGlobal.deltaTime = Utility::Time::getInstance().getDeltaTime();

    //�O���[�o���f�[�^�̃Z�b�g
    mCB->setBuffer(mGlobal);
    mCB->sendBuffer();

    mGlobal.emit = 0;

    mGPUParticle->simulate();
}

bool BlackholeParticle::isEndScene() const {
    return false;
}

void BlackholeParticle::draw(Framework::Graphics::IRenderer* renderer) {    //���O����
    Utility::getContext()->RSSetState(ras.Get());
    dynamic_cast<Graphics::BackBufferRenderer*>(renderer)->getRenderTarget()->setEnableDepthStencil(false);
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mAlphaBlend->set();
    renderer->setCurrentPerspectiveCamera(m3DCamera.get());
    m3DCamera->render();

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Math::Matrix4x4 m = Math::Matrix4x4::createScale(Math::Vector3(0.1f, 0.1f, 1.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World, m);
    Utility::getConstantBufferManager()->send();

    mGPUParticle->draw();
}

void BlackholeParticle::end() {}

Define::SceneType BlackholeParticle::next() {
    return Define::SceneType();
}