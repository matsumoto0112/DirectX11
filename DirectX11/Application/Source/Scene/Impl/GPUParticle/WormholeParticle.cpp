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

#include "Source/Utility/ImGUI/AddField.h"
using namespace Framework;

namespace {
std::shared_ptr<ImGUI::Text> mText;
}

WormholeParticle::WormholeParticle()
    :GPUParticleBase(GPUParticleInfo({ 32, 32, 1, 4, 1, 1 }),
        { Math::Vector3(0,30,-30),Math::Vector3(0,0,0),Math::Vector3::UP }) {

    mParameterCB = std::make_unique<Graphics::ConstantBuffer<ParticleGPUParameter>>(Graphics::ShaderInputType::Compute, 1);

    //最大パーティクル粒子数はMAX_RUNS_GPUPARTICLE_NUM * スレッド数 * ディスパッチ数
    mCPUParameter.MAX_RUNS_GPUPARTICLE_NUM = 256;
    mCPUParameter.mSpeed = 30.0f;
    mCPUParameter.mCurrentRunsGPUParticleNum = 10;
    mCPUParameter.mMaxYPosition = 20.0f;
    mGPUParameter.index = -1;
    mGPUParameter.spot = Math::Vector3::ZERO;
    mGPUParameter.radius = 10.0f;
    mGPUParameter.center = Math::Vector3::ZERO;

    auto gs = ShaderLoad::loadGS("Particle/Geometry/Cube_GS");
    auto ps = ShaderLoad::loadPS("Particle/Output_Color_PS");
    auto vs = ShaderLoad::loadVS("Particle/Wormhole/VS");

    auto randomTable = createRandomTable();

    //最大実行パーティクル数までパーティクル生成
    for (int i = 0; i < mCPUParameter.MAX_RUNS_GPUPARTICLE_NUM; i++) {
        auto cs = ShaderLoad::loadCS("Particle/Wormhole/CS", mInfo);

        //パーティクルのデータ作成
        std::vector<Particle> particle(mInfo.particleNum());
        cs->addUAVEnableVertexBuffer(1, particle, 0);

        cs->addSRV(0, randomTable);
        std::vector<int> randomSeed{ Utility::Random::getInstance()->range(0,RANDOM_MAX) };

        cs->addUAV(0, randomSeed);

        mGPUParticle.emplace_back(std::make_unique<Graphics::GPUParticle>(mInfo.particleNum(),
            Graphics::TextureLoader().load(Define::Path::getInstance()->texture() + "Circle.png"),
            cs,
            vs,
            ps,
            gs));
    }


    mText = std::make_shared<ImGUI::Text>("");
    mWindow->addItem(mText);

    AddField::addFloatField(*mWindow, "RADIUS", mGPUParameter.radius, 0.0f, 30.0f);
    AddField::addFloatField(*mWindow, "SPEED", mCPUParameter.mSpeed, 0.0f, 100.0f);
    AddField::addFloatField(*mWindow, "MAX_Y", mCPUParameter.mMaxYPosition, 0.0f, 100.0f);
    AddField::addIntField(*mWindow, "RUN_NUM", mCPUParameter.mCurrentRunsGPUParticleNum, 0, mCPUParameter.MAX_RUNS_GPUPARTICLE_NUM);
}

WormholeParticle::~WormholeParticle() { }

void WormholeParticle::update() {
    GPUParticleBase::update();
    mGPUParameter.index = (mGPUParameter.index + 1) % (mInfo.threadX * mInfo.threadY);

    mGPUParameter.spot.y += 1.0f * mCPUParameter.mSpeed *  Utility::Time::getInstance()->getDeltaTime();
    if (mGPUParameter.spot.y > mCPUParameter.mMaxYPosition) mGPUParameter.spot.y -= Math::MathUtility::abs(mCPUParameter.mMaxYPosition) * 2;
    mGPUParameter.center = mGPUParameter.spot + Math::Vector3(0, -10, 0);
    mParameterCB->setBuffer(mGPUParameter);
    mParameterCB->sendBuffer();

    for (int i = 0; i < mCPUParameter.mCurrentRunsGPUParticleNum; i++) {
        mGPUParticle[i]->simulate();
    }
}

void WormholeParticle::draw(Framework::Graphics::IRenderer* pipeline) {
    GPUParticleBase::draw(pipeline);

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Math::Matrix4x4 m = Math::Matrix4x4::createTranslate(Math::Vector3(0.0f, 0.0f, 0.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World3D, m);
    Utility::getConstantBufferManager()->send();

    for (int i = 0; i < mCPUParameter.mCurrentRunsGPUParticleNum; i++) {
        mGPUParticle[i]->draw();
    }

    mText->setText(Utility::StringBuilder("") << mCPUParameter.mCurrentRunsGPUParticleNum * mInfo.particleNum());
    mWindow->draw();
}
