#include "AlphaBlendTest.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/ImGUI/Window.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/Render/AlphaBlend.h"

using namespace Framework;

namespace {
std::unique_ptr<Graphics::AlphaBlend> mAlphaBlend;
float f;
}

AlphaBlendTest::AlphaBlendTest()
    :mPerspectiveCamera(std::make_unique<Graphics::PerspectiveCamera>(
        Graphics::PerspectiveCamera::Info{
        Math::Vector3(0,0,-10),
        Math::Vector3(0,0,0),
        Math::Vector3::UP,
        45.0f,
        Define::Window::getSize(),
        0.1f,
        1000.0f
        })) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Cube, Define::ModelName::CUBE);
    mEnemy.mModel = fbx->getResource(Define::ModelType::Cube);
    mEnemy.mModel->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model_Diffuse));
    mEnemy.mTransform = Utility::Transform(
        Math::Vector3::ZERO,
        Math::Quaternion::IDENTITY,
        Math::Vector3(1, 1, 1)
    );
    f = 0.0f;

    D3D11_BLEND_DESC bd;
    bd.AlphaToCoverageEnable = FALSE;
    bd.IndependentBlendEnable = FALSE;
    D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;
    ZeroMemory(&RenderTarget, sizeof(RenderTarget));
    RenderTarget.BlendEnable = FALSE;
    RenderTarget.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
    RenderTarget.DestBlend = D3D11_BLEND::D3D11_BLEND_DEST_COLOR;
    RenderTarget.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
    RenderTarget.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
    RenderTarget.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
    RenderTarget.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
    RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    bd.RenderTarget[0] = RenderTarget;

    mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(bd);
}

AlphaBlendTest::~AlphaBlendTest() {}

void AlphaBlendTest::load(Scene::Collecter& collecter) {}

void AlphaBlendTest::update(float delta) {
    f += 1.0f;
    Math::Quaternion rot = Math::Quaternion::createRotateAboutZ(f * 2.5) * Math::Quaternion::createRotateAboutY(f);
    mEnemy.mTransform.setRotate(rot);
}

bool AlphaBlendTest::isEndScene() const {
    return false;
}

void AlphaBlendTest::draw() {
    mAlphaBlend->set({ 0,0,0,0 });
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4::WHITE);
    mPerspectiveCamera->setMatrix();
    mEnemy.draw();
}

void AlphaBlendTest::end() {}

Define::SceneType AlphaBlendTest::next() {
    return Define::SceneType();
}

void AlphaBlendTest::GameObject::draw() {
    mModel->draw(mTransform);
}