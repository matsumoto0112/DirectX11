#include "FallParticle.h"
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
#include "Framework/Graphics/Particle/GPUParticle.h"
#include "Framework/Graphics/Texture/TextureLoader.h"
#include "Framework/Define/Path.h"
#include "Source/Utility/Shader/ShaderLoad.h"

using namespace Framework;

FallParticle::FallParticle()
    :GPUParticleBase(Graphics::ComputeShader::Info{ 16,16,1,8,8,1 }, { Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP }) {    //カメラの初期化
    auto cs = ShaderLoad::loadCS("Particle/Fall/CS", mInfo);

    //パーティクルのデータ作成
    std::vector<Particle> particle(mInfo.particleNum());
    cs->addUAVEnableVertexBuffer(1, particle, 0);

    cs->addSRV(0, createRandomTable());

    std::vector<int> randomSeed{ 0 };
    cs->addUAV(0, randomSeed);

    auto gs = ShaderLoad::loadGS("Particle/Geometry/Quad_GS");
    auto ps = ShaderLoad::loadPS("2D/Texture2D_Color_PS");
    auto vs = ShaderLoad::loadVS("Particle/Fall/VS");

    mGPUParticle.emplace_back(std::make_unique<Graphics::GPUParticle>(mInfo.particleNum(),
        Graphics::TextureLoader().load(Define::Path::getInstance()->texture() + "Smoke.png"),
        cs,
        vs,
        ps,
        gs));
}

FallParticle::~FallParticle() { }

void FallParticle::update() {
    GPUParticleBase::update();
    mGPUParticle[0]->simulate();
}

void FallParticle::draw(Framework::Graphics::IRenderer* pipeline) {
    GPUParticleBase::draw(pipeline);
    mGPUParticle[0]->draw();
}
