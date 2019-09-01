#include "DepthStencilTest.h"
#include "Framework/Define/Window.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Graphics/String/TextureString.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/ImGUI/Window.h"
#include "Framework/Utility/ImGUI/FloatField.h"

using namespace Framework;

DepthStencilTest::DepthStencilTest()
    :mStr(std::make_unique<Graphics::TextureString>("Depth Stencil Test", 14, "")),
    mPerspectiveCamera(std::make_unique<Graphics::PerspectiveCamera>(
        Graphics::PerspectiveCamera::Info{
        Math::Vector3(0.0f,5.0f,-10.0f),
        Math::Vector3(0.0f,0.0f,0.0f),
        Math::Vector3::UP,
        45.0f,
        Define::Window::getSize(),
        0.1f,1000.0f
        })),
    mOrthographicCamera(std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize())) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    //fbx->importResource(Define::ModelType::Object, Define::ModelName::OBJECT_NAME);
    //mModel = fbx->getResource(Define::ModelType::Object);
    mModel->setVertexShader(Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Model));
    mModel->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Model_NoTexture));

    const int modelNum = 5;
    for (int i = 0; i < modelNum; i++) {
        mModelTransforms.emplace_back(std::make_unique<Utility::Transform>(
            Math::Vector3(i, 0.1f * i, i),
            Math::Quaternion(),
            Math::Vector3(1.0f, 1.0f, 1.0f)));
    }

//    std::shared_ptr<ImGUI::Window> window = NULL;
//#define ADD_CAMERA_MOVE_FIELD(NAME,TYPE) { \
//    float def =mPerspectiveCamera->getPosition().##TYPE; \
//    std::shared_ptr<ImGUI::FloatField> NAME##field = std::make_shared<ImGUI::FloatField>(#NAME, def, [&](float val) { \
//    Math::Vector3 pos = mPerspectiveCamera->getPosition(); \
//    Math::Vector3 look = mPerspectiveCamera->getLookat(); \
//    float sub = val - pos.##TYPE; \
//    pos.##TYPE = val; \
//    look.##TYPE += sub; \
//    mPerspectiveCamera->setPosition(pos); \
//    mPerspectiveCamera->setLookat(look); \
//    }); \
//    NAME##field->setMinValue(-50.0f); \
//    NAME##field->setMaxValue(50.0f); \
//    window->addItem(NAME##field); } 
//
//    ADD_CAMERA_MOVE_FIELD(X, x);
//    ADD_CAMERA_MOVE_FIELD(Y, y);
//    ADD_CAMERA_MOVE_FIELD(Z, z);
}

DepthStencilTest::~DepthStencilTest() {}

void DepthStencilTest::load(Scene::Collecter& collecter) {}

void DepthStencilTest::update() {
    Math::Matrix4x4 mat = mPerspectiveCamera->getView();
}

bool DepthStencilTest::isEndScene() const {
    return false;
}

void DepthStencilTest::draw() {
    mPerspectiveCamera->render();
    Graphics::Color4 color(1.0f, 1.0f, 1.0f, 1.0f);
    for (int i = 0; i < mModelTransforms.size(); i++) {
        color.r = i * 0.2f;
        Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
        mModel->draw(*mModelTransforms[i]);
    }

    mOrthographicCamera->render();
    mStr->draw();
}

void DepthStencilTest::end() {}

Define::SceneType DepthStencilTest::next() {
    return Define::SceneType::Title;
}
