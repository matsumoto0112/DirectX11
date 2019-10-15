#include "WormholeParticle.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Utility/Time.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Graphics/Particle/GPUParticle.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Random.h"
#include "Framework/Graphics/Texture/TextureLoader.h"
#include "Source/Utility/Shader/ShaderLoad.h"
#include "Framework/Define/Path.h"
#include "Framework/Graphics/Desc/RasterizerStateDesc.h"
#include "Framework/Graphics/Desc/BlendStateDesc.h"

using namespace Framework;

namespace {
constexpr int NUM = 128;

struct ParticleParameter {
    UINT index;
    Math::Vector3 spot;
    Math::Vector3 center;
    float radius;
};

std::unique_ptr<Graphics::ConstantBuffer<ParticleParameter>> mParameterCB; //<! パラメータ用コンスタントバッファ
ParticleParameter mParameter;
std::unique_ptr<ImGUI::Window> mWindow;
std::shared_ptr<ImGUI::Text> mText;
int mNum;
float mSpeed;
float mMaxYPosition;

}

WormholeParticle::WormholeParticle()
    :GPUParticleBase(GPUParticleInfo({ 32, 32, 1, 4, 1, 1 }),
        { Math::Vector3(0,30,-30),Math::Vector3(0,0,0),Math::Vector3::UP }) {

    mParameterCB = std::make_unique<Graphics::ConstantBuffer<ParticleParameter>>(Graphics::ShaderInputType::Compute, 1);
    auto gs = ShaderLoad::loadGS("Particle/Geometry/Cube_GS");
    auto ps = ShaderLoad::loadPS("Particle/Output_Color_PS");
    auto vs = ShaderLoad::loadVS("Particle/Wormhole/VS");

    auto randomTable = createRandomTable();
    for (int i = 0; i < NUM; i++) {
        auto cs = ShaderLoad::loadCS("Particle/Wormhole/CS", mInfo);

        //パーティクルのデータ作成
        std::vector<Particle> particle(mInfo.COUNT(), { 0 });
        cs->addUAVEnableVertexBuffer(1, particle, 0);

        cs->addSRV(0, randomTable);
        std::vector<int> randomSeed{ Utility::Random::getInstance()->range(0,RANDOM_MAX) };

        cs->addUAV(0, randomSeed);

        mGPUParticle.emplace_back(std::make_unique<Graphics::GPUParticle>(mInfo.COUNT(),
            Graphics::TextureLoader().load(Define::Path::getInstance()->texture() + "Circle.png"),
            cs,
            vs,
            ps,
            gs));
    }

    mSpeed = 30.0f;
    mParameter.index = -1;
    mParameter.spot = Math::Vector3::ZERO;
    mParameter.radius = 10.0f;
    mNum = 10;
    mMaxYPosition = 20.0f;

    mWindow = std::make_unique<ImGUI::Window>("Parameter");
    mText = std::make_shared<ImGUI::Text>("");
    mWindow->addItem(mText);

#define ADD_CHANGE_FIELD(name,var,min,max) { \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name,var,[&](float val){var = val;}); \
    mWindow->addItem(field); \
    field->setMinValue(min); \
    field->setMaxValue(max); \
    }

    ADD_CHANGE_FIELD(RADIUS, mParameter.radius, 0.0f, 30.0f);
    ADD_CHANGE_FIELD(SPEED, mSpeed, 0.0f, 100.0f);
    ADD_CHANGE_FIELD(MAX_Y, mMaxYPosition, 0.0f, 100.0f);
    ADD_CHANGE_FIELD(NUM, mNum, 0, NUM);
}

WormholeParticle::~WormholeParticle() { }

void WormholeParticle::update() {
    GPUParticleBase::update();
    mParameter.index = (mParameter.index + 1) % (mInfo.threadX * mInfo.threadY);

    mParameter.spot.y += 1.0f * mSpeed *  Utility::Time::getInstance()->getDeltaTime();
    if (mParameter.spot.y > mMaxYPosition)mParameter.spot.y -= Math::MathUtility::abs(mMaxYPosition) * 2;
    mParameter.center = mParameter.spot + Math::Vector3(0, -10, 0);
    mParameterCB->setBuffer(mParameter);
    mParameterCB->sendBuffer();

    for (int i = 0; i < mNum; i++) {
        mGPUParticle[i]->simulate();
    }
}

bool WormholeParticle::isEndScene() const {
    return false;
}

void WormholeParticle::draw(Framework::Graphics::IRenderer* pipeline) {
    GPUParticleBase::draw(pipeline);

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Math::Matrix4x4 m = Math::Matrix4x4::createTranslate(Math::Vector3(0.0f, 0.0f, 0.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World3D, m);
    Utility::getConstantBufferManager()->send();

    for (int i = 0; i < mNum; i++) {
        mGPUParticle[i]->draw();
    }

    mText->setText(Utility::StringBuilder("") << mNum * mInfo.COUNT());
    mWindow->draw();
}
