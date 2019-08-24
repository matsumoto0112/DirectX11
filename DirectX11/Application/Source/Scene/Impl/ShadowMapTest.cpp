#include "ShadowMapTest.h"
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

#include "Framework/Graphics/Sprite/Sprite2D.h"
#include "Framework/Graphics/Shader/ShaderResourceView.h"
#include "Framework/Graphics/Render/RenderTargetView.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"

using namespace Framework;

namespace {
Graphics::Sprite2D* spr;
}

ShadowMapTest::ShadowMapTest()
    : mStr(std::make_unique<Graphics::TextureString>("ShadowMap Test", 14, "")),
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

    //mWallTransforms.emplace_back(
    //    Math::Vector3(0, 10.0f, 10.0f),
    //    Math::Quaternion::createRotateAboutX(-90.0f),
    //    Math::Vector3(10.0f, 1.0f, 10.0f));
    //mWallTransforms.emplace_back(
    //    Math::Vector3(10.0f, 10.0f, 0.0f),
    //    Math::Quaternion::createRotateAboutX(-90.0f) * Math::Quaternion::createRotateAboutY(90.0f),
    //    Math::Vector3(10.0f, 1.0f, 10.0f));
    //mWallTransforms.emplace_back(
    //    Math::Vector3(-10.0f, 10.0f, 0.0f),
    //    Math::Quaternion::createRotateAboutX(-90.0f) * Math::Quaternion::createRotateAboutY(-90.0f),
    //    Math::Vector3(10.0f, 1.0f, 10.0f));

    mObject.mTransform = Utility::Transform(
        Math::Vector3(0.0f, 0.5f, 0.0f),
        Math::Quaternion::IDENTITY,
        Math::Vector3(0.5f, 0.5f, 0.5f));
    mObject.mModel = fbx->getResource(Define::ModelType::Object);
    mObject.mModel->setVertexShader(vs->getResource(Define::VertexShaderType::Model_Lighting));
    mObject.mModel->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse_Lighting));

    mFloor.mTransform = Utility::Transform(
        Math::Vector3(0.0f, -0.0f, 0.0f),
        Math::Quaternion::IDENTITY,
        Math::Vector3(10.0f, 1.0f, 10.0f));
    mFloor.mModel = fbx->getResource(Define::ModelType::Floor);
    mFloor.mModel->setVertexShader(vs->getResource(Define::VertexShaderType::Model_Lighting));
    mFloor.mModel->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse_Lighting));

    mDirectionalLight = Utility::getLightManager()->addDirectionalLight(Define::DirectionalLightType::Default,
        Math::Vector3(0.0f, -1.0f, 1.0f), Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mPointLight = Utility::getLightManager()->addPointLight(Define::PointLightType::LeftTopFloor,
        Math::Vector3(0.0f, 0.0f, 0.0),
        Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f),
        5.0f,
        0.0f);

    //    mUIWindow = std::make_unique<ImGUI::Window>("Point Light");
    //
    //#define ADD_LIGHT_COLOR_CHANGE_SLIDER(Name,Type) { \
    //    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#Name, 0.0f, [&](float val) { \
    //        Graphics::Color4 color = mPointLight->getColor();\
    //        color. ## Type = val;\
    //        mPointLight->setColor(color);\
    //        });\
    //    field->setMinValue(0.0f);\
    //    field->setMaxValue(1.0f);\
    //    mUIWindow->addItem(field); }
    //#define ADD_LIGHT_POSITION_CHANGE_SLIDER(Name,Type) { \
    //    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#Name, 0.0f, [&](float val) { \
    //        Math::Vector3 pos = mPointLight->getPosition();\
    //        pos. ## Type = val;\
    //        mPointLight->setPosition(pos);\
    //        });\
    //    field->setMinValue(-10.0f);\
    //    field->setMaxValue(10.0f);\
    //    mUIWindow->addItem(field); }
    //
    //    //    //mDirectionalLight->getColor();
    //    ADD_LIGHT_COLOR_CHANGE_SLIDER(R, r);
    //    ADD_LIGHT_COLOR_CHANGE_SLIDER(G, g);
    //    ADD_LIGHT_COLOR_CHANGE_SLIDER(B, b);
    //    ADD_LIGHT_POSITION_CHANGE_SLIDER(X, x);
    //    ADD_LIGHT_POSITION_CHANGE_SLIDER(Y, y);
    //    ADD_LIGHT_POSITION_CHANGE_SLIDER(Z, z);

    //Z値を格納するテクスチャを作成する
    D3D11_TEXTURE2D_DESC texDesc;
    ZeroMemory(&texDesc, sizeof(texDesc));
    texDesc.Width = Define::Window::WIDTH;
    texDesc.Height = Define::Window::HEIGHT;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_TYPELESS;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
    texDesc.CPUAccessFlags = 0;
    mRenderTargetTextureBuffer = std::make_shared<Graphics::TextureBuffer>(texDesc);

    D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
    ZeroMemory(&viewDesc, sizeof(viewDesc));
    viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    //Z値を描画するときに使用するシェーダーリソースを作成する
    mShaderResourceView = std::make_shared<Graphics::ShaderResourceView>(*mRenderTargetTextureBuffer);

    mRenderTargetView = std::make_unique<Graphics::RenderTargetView>(mRenderTargetTextureBuffer->getBuffer().Get(), viewDesc);

    std::shared_ptr<Graphics::Texture> texture = std::make_shared<Graphics::Texture>(
        mRenderTargetTextureBuffer,
        mShaderResourceView,
        Define::Window::WIDTH,
        Define::Window::HEIGHT
        );
    spr = new Graphics::Sprite2D(texture);
    ps->importResource(Define::PixelShaderType::Output_Z, Define::PixelShaderName::OUTPUT_Z);
    vs->importResource(Define::VertexShaderType::Output_Z, Define::VertexShaderName::OUTPUT_Z);
    mObject.mModel->setVertexShader(vs->getResource(Define::VertexShaderType::Output_Z));
    mObject.mModel->setPixelShader(ps->getResource(Define::PixelShaderType::Output_Z));

}

ShadowMapTest::~ShadowMapTest() {}

void ShadowMapTest::load(Framework::Scene::Collecter & collecter) {}

void ShadowMapTest::update(float delta) {}

bool ShadowMapTest::isEndScene() const {
    return false;
}

void ShadowMapTest::draw() {
    //mPerspectiveCamera->setMatrix();
    //Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4::WHITE);
    //for (auto&& transform : mWallTransforms) {
    //    mWall->draw(transform);
    //}
    //mObject.draw();
    //mFloor.draw();

    ////mUIWindow->draw();
    //mOrthographicCamera->setMatrix();
    //mStr->draw();
    ID3D11RenderTargetView* backView;
    ID3D11DepthStencilView* backDepthStencil;
    Utility::getContext()->OMGetRenderTargets(1, &backView, &backDepthStencil);

    Utility::Transform tr(Math::Vector3::ZERO, Math::Quaternion::IDENTITY, Math::Vector3(1.0f, 1.0f, 1.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World, tr.createSRTMatrix());
    mPerspectiveCamera->setMatrix();
    mRenderTargetView->set();
    mRenderTargetView->clear(Graphics::Color4::BLACK);
    const int num = 1;
    for (int z = 0; z < num; z++) {
        for (int x = 0; x < num; x++) {
            mObject.mTransform.setPosition(Math::Vector3((x - num / 2)*2.0f, 0.0f, (z - num / 2) * 2.0f));
            mObject.draw();
        }
    }

    mOrthographicCamera->setMatrix();
    Utility::getContext()->OMSetRenderTargets(1, &backView, backDepthStencil);
    spr->draw();
}

void ShadowMapTest::end() {}

Define::SceneType ShadowMapTest::next() {
    return Define::SceneType();
}

void ShadowMapTest::GameObject::draw() {
    mModel->draw(mTransform);
}
