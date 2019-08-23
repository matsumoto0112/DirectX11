#include "NormalLightingTest.h"
#include "Framework/Utility/Property.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Utility/ImGUI/FloatField.h"
#include "Framework/Utility/ImGUI/Window.h"
#include "Framework/Graphics/String/TextureString.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

using namespace Framework;

NormalLightingTest::NormalLightingTest()
    :mStr(std::make_unique<Graphics::TextureString>("Lighting Test", 14, "")),
    mPerspectiveCamera(std::make_unique<Graphics::PerspectiveCamera>(
        Graphics::PerspectiveCamera::Info{
        Math::Vector3(0.0f,10.0f,-10.0f),
        Math::Vector3(0.0f,0.0f,0.0f),
        Math::Vector3::UP,
        45.0f,
        Define::Window::getSize(),
        0.1f,1000.0f
        })),
    mOrthographicCamera(std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize())) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Wall, Define::ModelName::WALL);
    fbx->importResource(Define::ModelType::Object, Define::ModelName::OBJECT_NAME);
    fbx->importResource(Define::ModelType::Floor, Define::ModelName::FLOOR_NAME);

    mWall = fbx->getResource(Define::ModelType::Wall);

    auto vs = Utility::ResourceManager::getInstance().getVertexShader();
    vs->importResource(Define::VertexShaderType::Model_Lighting, Define::VertexShaderName::MODEL_LIGHTING);

    auto ps = Utility::ResourceManager::getInstance().getPixelShader();
    ps->importResource(Define::PixelShaderType::Model_Diffuse, Define::PixelShaderName::MODEL_DIFFUSE);
    ps->importResource(Define::PixelShaderType::Model_Diffuse_Lighting, Define::PixelShaderName::MODEL_DIFFUSE_LIGHTING);

    mWall->setVertexShader(vs->getResource(Define::VertexShaderType::Model));
    mWall->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse));

    mWallTransforms.emplace_back(
        Math::Vector3(0, 10.0f, 10.0f),
        Math::Quaternion::createRotateAboutX(-90.0f),
        Math::Vector3(10.0f, 1.0f, 10.0f));
    mWallTransforms.emplace_back(
        Math::Vector3(10.0f, 10.0f, 0.0f),
        Math::Quaternion::createRotateAboutX(-90.0f) * Math::Quaternion::createRotateAboutY(90.0f),
        Math::Vector3(10.0f, 1.0f, 10.0f));
    mWallTransforms.emplace_back(
        Math::Vector3(-10.0f, 10.0f, 0.0f),
        Math::Quaternion::createRotateAboutX(-90.0f) * Math::Quaternion::createRotateAboutY(-90.0f),
        Math::Vector3(10.0f, 1.0f, 10.0f));

    mObject.mTransform = Utility::Transform(
        Math::Vector3(0.0f, 0.5f, 0.0f),
        Math::Quaternion::IDENTITY,
        Math::Vector3(0.5f, 0.5f, 0.5f));
    mObject.mModel = fbx->getResource(Define::ModelType::Object);

    mFloor.mTransform = Utility::Transform(
        Math::Vector3(0.0f, -0.0f, 0.0f),
        Math::Quaternion::IDENTITY,
        Math::Vector3(10.0f, 1.0f, 10.0f));
    mFloor.mModel = fbx->getResource(Define::ModelType::Floor);
    mFloor.mModel->setVertexShader(vs->getResource(Define::VertexShaderType::Model_Lighting));
    mFloor.mModel->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse_Lighting));

    mDirectionalLight = Utility::getLightManager()->addDirectionalLight(Define::DirectionalLightType::Default,
        Math::Vector3(0.0f, -1.0f, 1.0f), Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));

    mUIWindow = std::make_unique<ImGUI::Window>("Directional Light");

#define ADD_LIGHT_COLOR_CHANGE_SLIDER(Name,Type) { \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#Name, 0.0f, [&](float val) { \
        Graphics::Color4 color = mDirectionalLight->getColor();\
        color. ## Type = val;\
        mDirectionalLight->setColor(color);\
        });\
    field->setMinValue(0.0f);\
    field->setMaxValue(1.0f);\
    mUIWindow->addItem(field); }

    //mDirectionalLight->getColor();
    ADD_LIGHT_COLOR_CHANGE_SLIDER(R, r);
    ADD_LIGHT_COLOR_CHANGE_SLIDER(G, g);
    ADD_LIGHT_COLOR_CHANGE_SLIDER(B, b);
}

NormalLightingTest::~NormalLightingTest() {}

void NormalLightingTest::load(Scene::Collecter& collecter) {}

void NormalLightingTest::update(float delta) {}

bool NormalLightingTest::isEndScene() const {
    return false;
}

void NormalLightingTest::draw() {
    mPerspectiveCamera->setMatrix();
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4::WHITE);
    for (auto&& transform : mWallTransforms) {
        mWall->draw(transform);
    }
    mObject.draw();
    mFloor.draw();

    mUIWindow->draw();
    mOrthographicCamera->setMatrix();
    mStr->draw();
}

void NormalLightingTest::end() {}

Define::SceneType NormalLightingTest::next() {
    return Define::SceneType();
}

void GameObject::draw() {
    mModel->draw(mTransform);
}
