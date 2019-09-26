#include "stdafx.h"
#include "Source/Scene/Impl/Main.h"
#include "Source/GameObject/GameObjectManager.h"
#include "Source/GameObject/Player.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Define/Window.h"
#include "Source/GameObject/Bullet/Bullet.h"
#include "Source/GameObject/Enemy/NormalEnemy.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

#include "Framework/Graphics/Renderer/3D/Cube.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Source/GameObject/Field.h"
#include "Framework/Utility/Random.h"
#include "Source/GameObject/FollowCamera.h"
#include "Source/GameObject/Item/Item.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Graphics/Sprite/Sprite2D.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Graphics/Texture/TextureLoader.h"
#include "Framework/Define/Path.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Desc/RenderTargetViewDesc.h"
#include "Framework/Graphics/Shader/Effect.h"
#include "Framework/Graphics/Renderer/ZTexCreater.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Graphics/Texture/Sampler.h"
#include "Framework/Utility/Time.h"
#include "Framework/Graphics/Particle/SimpleParticleEmitter.h"

#include "Framework/Graphics/Sprite/SpriteRenderer.h"

using namespace Framework;

namespace {
std::unique_ptr<Graphics::SimpleParticleEmitter> mParticleEmitter;
std::shared_ptr<Graphics::Sprite3D> spr;
}

Main::Main() {
    std::unique_ptr<Player> player = std::make_unique<Player>(Utility::Transform(), *this);
    std::unique_ptr<Field> field = std::make_unique<Field>(*this);
    mManager = std::make_unique<GameObjectManager>(*this, std::move(player), std::move(field));

    Math::ViewInfo v{
        Math::Vector3(0,10,-10),
        Math::Vector3::ZERO,
        Math::Vector3::UP
    };
    Math::ProjectionInfo p{
        45.0f,
        Define::Window::getSize(),
        0.1f,
        1000.0f
    };
    mCamera = std::make_unique<FollowCamera>(v, p,
        getPlayer()->getTransformPtr());

    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.AlphaToCoverageEnable = TRUE;
    bd.IndependentBlendEnable = FALSE;
    bd.RenderTarget[0] = Graphics::AlphaBlendSetting::getAlignmentBlendDesc();
    mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(bd);

    std::shared_ptr<ImGUI::Window> mUIWindow = std::make_shared<ImGUI::Window>("Light");

    addDebugUI(mUIWindow);

    spr = std::make_shared<Graphics::Sprite3D>(
        Graphics::TextureLoader().load(Define::Path::getInstance().texture() + "smoke.png"));
    std::shared_ptr<Graphics::Particle> particle = std::make_unique<Graphics::Particle>(spr);
    mParticleEmitter = std::make_unique<Graphics::SimpleParticleEmitter>(particle);
    mParticleEmitter->setDuration(100.0f);
    mParticleEmitter->init();
}

Main::~Main() {}

void Main::load(Scene::Collecter& collecter) {}


void Main::update() {
    mManager->update();
    mParticleEmitter->simulate(Utility::Time::getInstance().getDeltaTime());
    //    int num = 0;
    //    const int NUM = 36;
    //    const float ANGLE = 360.0f / NUM;
    //    float x = Math::MathUtility::cos(ANGLE * num) * 5;
    //    float z = Math::MathUtility::sin(ANGLE * num) * 5;
    //    float s = 1.0f;
    //    Utility::Transform tr(
    //        Math::Vector3(x, 0.0f, z),
    //        Math::Quaternion::IDENTITY,
    //        Math::Vector3(s, s, s)
    //    );
    //    tr.lookat(Math::Vector3(0.0f, 0.0f, 0.0f));
    //    NormalEnemy::Parameter parameter;
    //    parameter.color = Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f);
    //    parameter.moveSpeed = 3.0f;
    //    mManager->addEnemy(std::make_unique<NormalEnemy>(tr, parameter, *this));
    //}
}

bool Main::isEndScene() const {
    return false;
}

void Main::draw(Graphics::IRenderer* renderer) {
    renderer->setBackColor(Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    renderer->setCurrentPerspectiveCamera(mCamera.get());
    mAlphaBlend->set();
    mCamera->render();
    mManager->draw(renderer);
    mParticleEmitter->draw(renderer);
    //Graphics::Sprite2D sprite(
    //    Graphics::TextureLoader().load(Define::Path::getInstance().texture() + "smoke.png"));
    //Graphics::OrthographicCamera o(Math::Vector2(Define::Window::WIDTH, Define::Window::HEIGHT));
    //o.render();
    //Graphics::SpriteRenderer::getInstance().draw(&sprite);

    //mCamera->render();
    //renderer->render(spr);
    renderer->end();

    //UIウィンドウ
    for (auto&& window : mDebugUIs) {
        window->draw();
    }
}

void Main::end() {}

Define::SceneType Main::next() {
    return Define::SceneType();
}

FollowCamera* Main::getMainCamera() {
    return mCamera.get();
}

void Main::shotBullet(const Utility::Transform& transform) {
    mManager->addBullet(std::make_unique<Bullet>(transform, *this));
}

void Main::addDebugUI(std::shared_ptr<ImGUI::Window> window) {
    mDebugUIs.emplace_back(window);
}

Player* Main::getPlayer() {
    return mManager->getPlayer();
}
