#include "FallBounceParticle.h"
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
static constexpr int THREAD_X = 16, THREAD_Y = 16;
static constexpr int DISPATCH_X = 8, DISPATCH_Y = 8;
static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
static constexpr int RANDOM_MAX = 65535;
const int NUM = 12;

struct Particle {
    float lifeTime;
    Math::Vector3 position;
    Math::Vector3 velocity;
    Math::Vector3 scale;
    Graphics::Color4 color;
};

struct GlobalData {
    float deltaTime;
    float gravity;
    float d[2];
    Math::Vector3 center;
    float dummy[1];
};

std::vector<std::unique_ptr<Graphics::GPUParticle>> mGPUParticle; //!< �p�[�e�B�N��
std::unique_ptr<Graphics::ConstantBuffer<GlobalData>> mCB; //<! �O���[�o���f�[�^�p�R���X�^���g�o�b�t�@
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
std::unique_ptr<Utility::Timer> mTimer;
GlobalData mGlobal;
std::unique_ptr<ImGUI::Window> mWindow;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getAlignmentBlendDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}
}

FallBounceParticle::FallBounceParticle() {    //�J�����̏�����
    m3DCamera = std::make_unique<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,30,-30),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Window::getSize(),0.1f,1000.0f });

    m2DCamera = std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize());

    //�A���t�@�u�����h�̍쐬
    mAlphaBlend = createAlphaBlend();



    std::vector<float> randomTable(RANDOM_MAX);
    for (int i = 0; i < RANDOM_MAX; i++) {
        randomTable[i] = Utility::Random::getInstance().range(0.0f, 1.0f);
    }



    //�e�N�X�`���ǂݍ���
    Utility::getResourceManager()->getTexture()->importResource(Define::TextureType::Smoke, Define::TextureName::SMOKE);

    mCB = std::make_unique<Graphics::ConstantBuffer<GlobalData>>(Graphics::ShaderInputType::Compute, 0);
    auto gs = std::make_shared<Graphics::GeometoryShader>("Particle/CubeParticle_GS");
    auto ps = std::make_shared<Graphics::PixelShader>("Particle/CubeParticle_PS");

    const std::vector<D3D11_INPUT_ELEMENT_DESC>	layouts =
    {
        { "IN_LIFETIME",0, DXGI_FORMAT_R32_FLOAT,          0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "IN_VELOCITY",0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "IN_SCALE",0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR",      0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    auto vs = std::make_shared<Graphics::VertexShader>("Particle/Fall_Bounce_VS", layouts);

    for (int i = 0; i < NUM; i++) {
        //�R���s���[�g�V�F�[�_�쐬
        Graphics::ComputeShader::Info info{ DISPATCH_X,DISPATCH_Y,1,THREAD_X,THREAD_Y,1 };
        auto cs = std::make_shared<Graphics::ComputeShader>("Particle/Fall_Bounce_CS", info);

        //�p�[�e�B�N���̃f�[�^�쐬
        std::vector<Particle> particle(COUNT);
        for (int i = 0; i < COUNT; i++) {
            particle[i] = Particle{ -1.0f,Math::Vector3::ZERO,Math::Vector3::ZERO,Math::Vector3::ZERO, Graphics::Color4::WHITE };
        }
        cs->addUAVEnableVertexBuffer(1, particle, 0);

        cs->addSRV(0, randomTable);
        std::vector<int> randomSeed{ Utility::Random::getInstance().range(0,RANDOM_MAX) };

        cs->addUAV(0, randomSeed);

        mGPUParticle.emplace_back(std::make_unique<Graphics::GPUParticle>(COUNT,
            Utility::getResourceManager()->getTexture()->getResource(Define::TextureType::Smoke),
            cs,
            vs,
            ps,
            gs));
    }


    //���X�^���C�U�쐬
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    Utility::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    Utility::getContext()->RSSetState(ras.Get());

    mTimer = std::make_unique<Utility::Timer>(10.0f);
    mTimer->init();

    mWindow = std::make_unique<ImGUI::Window>("Parameter");
#define ADD_CHANGE_CENTER_FIELD(name,type) {\
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name,0.0f,[&](float val){mGlobal.center.##type = val;});\
        mWindow->addItem(field); \
        field->setMinValue(-10.0f); \
        field->setMaxValue(10.0f); \
    }
    ADD_CHANGE_CENTER_FIELD(X, x);
    ADD_CHANGE_CENTER_FIELD(Y, y);
    ADD_CHANGE_CENTER_FIELD(Z, z);
}

FallBounceParticle::~FallBounceParticle() {}

void FallBounceParticle::load(Framework::Scene::Collecter& collecter) {}

void FallBounceParticle::update() {
    mTimer->update(Utility::Time::getInstance().getDeltaTime());

    mGlobal.deltaTime = Utility::Time::getInstance().getDeltaTime();
    mGlobal.gravity = 9.8f;

    //�O���[�o���f�[�^�̃Z�b�g
    mCB->setBuffer(mGlobal);
    mCB->sendBuffer();

    for (int i = 0; i < mGPUParticle.size(); i++) {
        mGPUParticle[i]->simulate();
    }
}

bool FallBounceParticle::isEndScene() const {
    return false;
}

void FallBounceParticle::draw(Framework::Graphics::IRenderer* renderer) {
    Utility::getContext()->RSSetState(ras.Get());
    dynamic_cast<Graphics::BackBufferRenderer*>(renderer)->getRenderTarget()->setEnableDepthStencil(false);
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mAlphaBlend->set();
    renderer->setCurrentPerspectiveCamera(m3DCamera.get());
    m3DCamera->render();

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Math::Matrix4x4 m = Math::Matrix4x4::createScale(Math::Vector3(1.0f, 1.0f, 1.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World, m);
    Utility::getConstantBufferManager()->send();

    for (int i = 0; i < mGPUParticle.size(); i++) {
        mGPUParticle[i]->draw();
    }

    mWindow->draw();
}

void FallBounceParticle::end() {}

Define::SceneType FallBounceParticle::next() {
    return Define::SceneType();
}