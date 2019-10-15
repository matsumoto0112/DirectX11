#include "IceBlock.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Random.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Graphics/Texture/TextureLoader.h"
#include "Framework/Graphics/Particle/GPUParticle.h"
#include "Source/Utility/Shader/ShaderLoad.h"
#include "Framework/Define/Path.h"
#include "Source/Utility/ImGUI/AddField.h"

using namespace Framework;

namespace {
std::shared_ptr<ImGUI::Text> mText;
}

IceBlock::IceBlock()
    :GPUParticleBase(Graphics::ComputeShader::Info{ 32,32,1,2,2,1 }, { Math::Vector3(0,30,-30),Math::Vector3(0,0,0),Math::Vector3::UP }) {    //カメラの初期化

    mGPUParameter.center = Math::Vector3::ZERO;
    mCPUParameter.MAX_RUNNING_PARTICLE_NUM = 256;
    mCPUParameter.mCurrentRunningNum = 1;

    mEmitParameter = std::make_unique<Graphics::ConstantBuffer<GPUParameter>>(Graphics::ShaderInputType::Compute, 1);

    std::vector<float> randomTable = createRandomTable();
    auto gs = ShaderLoad::loadGS("Particle/IceBlock/GS");
    auto ps = ShaderLoad::loadPS("Particle/Output_Color_PS");
    auto vs = ShaderLoad::loadVS("Particle/IceBlock/VS");

    for (int i = 0; i < mCPUParameter.MAX_RUNNING_PARTICLE_NUM; i++) {
        auto cs = ShaderLoad::loadCS("Particle/IceBlock/CS", mInfo);

        //パーティクルのデータ作成
        std::vector<Particle> particle(mInfo.particleNum());
        cs->addUAVEnableVertexBuffer(1, particle, 0);

        cs->addSRV(0, randomTable);
        std::vector<int> randomSeed{ Utility::Random::getInstance()->range(0,RANDOM_MAX) };

        cs->addUAV(0, randomSeed);

        mGPUParticle.emplace_back(std::make_unique<Graphics::GPUParticle>(mInfo.particleNum(),
            Graphics::TextureLoader().load(Define::Path::getInstance()->texture() + "Smoke.png"),
            cs,
            vs,
            ps,
            gs));
    }

    mText = std::make_shared<ImGUI::Text>("");
    mWindow->addItem(mText);

    AddField::addFloatField(*mWindow, "X", mGPUParameter.center.x, -30.0f, 30.0f);
    AddField::addFloatField(*mWindow, "Y", mGPUParameter.center.y, -30.0f, 30.0f);
    AddField::addFloatField(*mWindow, "Z", mGPUParameter.center.z, -30.0f, 30.0f);
    AddField::addIntField(*mWindow, "NUM", mCPUParameter.mCurrentRunningNum, 0, mCPUParameter.MAX_RUNNING_PARTICLE_NUM);
}

IceBlock::~IceBlock() { }


void IceBlock::update() {
    GPUParticleBase::update();
    mEmitParameter->setBuffer(mGPUParameter);
    mEmitParameter->sendBuffer();
    for (int i = 0; i < mCPUParameter.mCurrentRunningNum; i++) {
        mGPUParticle[i]->simulate();
    }
}

void IceBlock::draw(Framework::Graphics::IRenderer* renderer) {
    GPUParticleBase::draw(renderer);
    for (int i = 0; i < mCPUParameter.mCurrentRunningNum; i++) {
        mGPUParticle[i]->draw();
    }

    mText->setText(Utility::StringBuilder("") << mCPUParameter.mCurrentRunningNum * mInfo.particleNum());
    mWindow->draw();
}

