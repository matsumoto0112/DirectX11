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
    fbx->importResource(Define::ModelType::Object, Define::ModelName::OBJECT_NAME);
    mModel = fbx->getResource(Define::ModelType::Object);
    mModel->setVertexShader(Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Model));
    mModel->setPixelShader(Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Nodel_NoTexture));

    const int modelNum = 5;
    for (int i = 0; i < modelNum; i++) {
        mModelTransforms.emplace_back(std::make_unique<Utility::Transform>(
            Math::Vector3(i, 0.1f * i, i),
            Math::Quaternion(),
            Math::Vector3(1.0f, 1.0f, 1.0f)));
    }

    std::shared_ptr<ImGUI::Window> window = ImGUI::Window::create("Camera");
    std::shared_ptr<ImGUI::FloatField> Xfield = std::make_shared<ImGUI::FloatField>("X", 0.0f, [&](float val) {
        Math::Vector3 pos = mPerspectiveCamera->getPosition();
        Math::Vector3 look = mPerspectiveCamera->getLookat();
        float sub = val - pos.x;
        pos.x = val;
        look.x += sub;
        mPerspectiveCamera->setPosition(pos);
        mPerspectiveCamera->setLookat(look);
    });
    Xfield->setMinValue(-10.0f);
    Xfield->setMaxValue(10.0f);
    window->addItem(Xfield);
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

    mOrthographicCamera->setMatrix();
    mStr->draw();

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
