#include "DepthStencilTest.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

using namespace Framework;

DepthStencilTest::DepthStencilTest()
    :mPerspectiveCamera(std::make_unique<Framework::Graphics::PerspectiveCamera>(
        Framework::Graphics::PerspectiveCamera::Info{
        Math::Vector3(0.0f,5.0f,-10.0f),
        Math::Vector3(0.0f,0.0f,0.0f),
        Math::Vector3::UP,
        45.0f,
        Define::Window::getSize(),
        0.1f,1000.0f
        })) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Object, Define::ModelName::OBJECT_NAME);
    mModel = fbx->getResource(Define::ModelType::Object);

    const int modelNum = 5;
    for (int i = 0; i < modelNum; i++) {
        mModelTransforms.emplace_back(std::make_unique<Utility::Transform>(
            Math::Vector3(i, i * 0.1f, i),
            Math::Quaternion(),
            Math::Vector3(1.0f, 1.0f, 1.0f)));
    }
}

DepthStencilTest::~DepthStencilTest() {}

void DepthStencilTest::load(Scene::Collecter& collecter) {}

void DepthStencilTest::update(float delta) {
    Math::Matrix4x4 mat = mPerspectiveCamera->getView();
}

bool DepthStencilTest::isEndScene() const {
    return false;
}

void DepthStencilTest::draw() {
    mPerspectiveCamera->setMatrix();
    Graphics::Color4 color(1.0f, 1.0f, 1.0f, 1.0f);
    for (int i = 0; i < mModelTransforms.size(); i++) {
        color.r = i * 0.2f;
        Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
        mModel->draw(*mModelTransforms[i]);
    }
    //for (int i = 5 - 1; i >= 0; i--) {
    //    color.r = i * 0.2f;
    //    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
    //    mModel->draw(*mModelTransforms[i]);
    //}
}

void DepthStencilTest::end() {}

Define::SceneType DepthStencilTest::next() {
    return Define::SceneType::Title;
}
