#include "stdafx.h"
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
#include "Framework/Graphics/Render/Viewport.h"

#include "Source/DefienClearColor.h"
using namespace Framework;

namespace {
std::unique_ptr<Graphics::Sprite2D> mSprite;
Math::Matrix4x4 lightView;
Math::Matrix4x4 lightProj;
Math::Matrix4x4 cameraView;
Math::Matrix4x4 cameraProj;
Math::Vector3 lightPos;
Math::Vector3 lightLookat;
std::shared_ptr<Graphics::VertexShader> mNormalVS;
std::shared_ptr<Graphics::PixelShader> mNormalPS;
std::shared_ptr<Graphics::VertexShader> mOutputVS;
std::shared_ptr<Graphics::PixelShader> mOutputPS;
std::shared_ptr<Graphics::VertexShader> mShadowVS;
std::shared_ptr<Graphics::PixelShader> mShadowPS;
Microsoft::WRL::ComPtr<ID3D11BlendState> mAlphaBlend;
Microsoft::WRL::ComPtr<ID3D11BlendState> mNoAlpha;
std::unique_ptr<Graphics::Viewport> mViewport;
std::shared_ptr<Graphics::Texture> mShadowMapTex;
static float f;

auto CreateDefaultBlendDesc = []() {
    D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

    RenderTarget.BlendEnable = FALSE;
    RenderTarget.SrcBlend = D3D11_BLEND_ONE;
    RenderTarget.DestBlend = D3D11_BLEND_ZERO;
    RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
    RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
    RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
    RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    return RenderTarget;
};

auto CreateAlignmentBlendDesc = []() {
    D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

    RenderTarget.BlendEnable = TRUE;
    RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    RenderTarget.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
    RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
    RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
    RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    return RenderTarget;
};

// 加算合成用ブレンド ステートのためのを設定を取得する
auto CreateAddBlendDesc = []() {
    D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

    RenderTarget.BlendEnable = TRUE;
    RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    RenderTarget.DestBlend = D3D11_BLEND_ONE;
    RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
    RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
    RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
    RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    return RenderTarget;
};

// 減算合成用ブレンド ステートのためのを設定を取得する
auto CreateSubtractBlendDesc() {
    D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

    RenderTarget.BlendEnable = TRUE;
    RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    RenderTarget.DestBlend = D3D11_BLEND_ONE;
    RenderTarget.BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
    RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
    RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
    RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    return RenderTarget;
};

// 積算合成用ブレンド ステートのためのを設定を取得する
auto CreateMultipleBlendDesc() {
    D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;

    RenderTarget.BlendEnable = TRUE;
    RenderTarget.SrcBlend = D3D11_BLEND_ZERO;
    RenderTarget.DestBlend = D3D11_BLEND_SRC_COLOR;
    RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
    RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
    RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
    RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    return RenderTarget;
};

auto CreateAddBlendDesc2 = []() {
    D3D11_RENDER_TARGET_BLEND_DESC RenderTarget;
    ZeroMemory(&RenderTarget, sizeof(RenderTarget));
    RenderTarget.BlendEnable = TRUE;
    RenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    RenderTarget.DestBlend = D3D11_BLEND_DEST_COLOR;
    RenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
    RenderTarget.SrcBlendAlpha = D3D11_BLEND_ONE;
    RenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
    RenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    RenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    return RenderTarget;
};

auto CreateTestBlendDesc = []() {
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
    return RenderTarget;
};


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
        10.0f,1000.0f
        })),
    mOrthographicCamera(std::make_unique<Graphics::OrthographicCamera>(Define::Window::getSize())) {
    auto fbx = Utility::ResourceManager::getInstance().getFBXModel();
    fbx->importResource(Define::ModelType::Wall, Define::ModelName::WALL);
    fbx->importResource(Define::ModelType::Object, Define::ModelName::OBJECT_NAME);
    fbx->importResource(Define::ModelType::Floor, Define::ModelName::FLOOR_NAME);

    mWall = fbx->getResource(Define::ModelType::Wall);

    auto vs = Utility::ResourceManager::getInstance().getVertexShader();
    vs->importResource(Define::VertexShaderType::Model_Lighting, Define::VertexShaderName::MODEL_LIGHTING);
    vs->importResource(Define::VertexShaderType::Model_Shadow, Define::VertexShaderName::MODEL_SHADOW);

    auto ps = Utility::ResourceManager::getInstance().getPixelShader();
    ps->importResource(Define::PixelShaderType::Model_Diffuse, Define::PixelShaderName::MODEL_DIFFUSE);
    ps->importResource(Define::PixelShaderType::Model_Diffuse_Lighting, Define::PixelShaderName::MODEL_DIFFUSE_LIGHTING);
    ps->importResource(Define::PixelShaderType::Model_Shadow, Define::PixelShaderName::MODEL_SHADOW);

    mWall->setVertexShader(vs->getResource(Define::VertexShaderType::Model));
    mWall->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse));

    mObject.mTransform = Utility::Transform(
        Math::Vector3(0.0f, 0.5f, 0.0f),
        Math::Quaternion::IDENTITY,
        Math::Vector3(1.0f, 1.0f, 1.0f));
    mObject.mModel = fbx->getResource(Define::ModelType::Object);
    mObject.mModel->setVertexShader(vs->getResource(Define::VertexShaderType::Model_Lighting));
    mObject.mModel->setPixelShader(ps->getResource(Define::PixelShaderType::Model_Diffuse_Lighting));

    mFloor.mTransform = Utility::Transform(
        Math::Vector3(0.0f, -60.0f, 0.0f),
        Math::Quaternion::IDENTITY,
        Math::Vector3(1.0f, 1.0f, 1.0f));
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
    texDesc.Width = 1024;
    texDesc.Height = 1024;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
    texDesc.CPUAccessFlags = 0;
    mRenderTargetTextureBuffer = std::make_shared<Graphics::TextureBuffer>(texDesc);

    D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
    ZeroMemory(&viewDesc, sizeof(viewDesc));
    viewDesc.Format = texDesc.Format;
    viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    //Z値を描画するときに使用するシェーダーリソースを作成する
    mShaderResourceView = std::make_shared<Graphics::ShaderResourceView>(*mRenderTargetTextureBuffer, nullptr);

    mRenderTargetView = std::make_unique<Graphics::RenderTargetView>(mRenderTargetTextureBuffer->getBuffer().Get(), viewDesc);

    D3D11_TEXTURE2D_DESC depthTexDesc;
    ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
    depthTexDesc.Width = texDesc.Width;
    depthTexDesc.Height = texDesc.Height;
    depthTexDesc.MipLevels = 1;
    depthTexDesc.ArraySize = 1;
    depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthTexDesc.SampleDesc.Count = 1;
    depthTexDesc.SampleDesc.Quality = 0;
    depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
    depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthTexDesc.CPUAccessFlags = 0;
    depthTexDesc.MiscFlags = 0;

    D3D11_DEPTH_STENCIL_VIEW_DESC dsd;
    ZeroMemory(&dsd, sizeof(dsd));
    dsd.Format = depthTexDesc.Format;
    dsd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsd.Texture2D.MipSlice = 0;
    mRenderTargetView->setDepthStencilView(std::make_unique<Graphics::DepthStencilView>(depthTexDesc, dsd));
    Math::Rect viewRect(0, 0, depthTexDesc.Width, depthTexDesc.Height);
    mViewport = std::make_unique<Graphics::Viewport>(viewRect);


    mShadowMapTex = std::make_shared<Graphics::Texture>(
        mRenderTargetTextureBuffer,
        mShaderResourceView,
        Define::Window::WIDTH,
        Define::Window::HEIGHT
        );
    mSprite = std::make_unique<Graphics::Sprite2D>(mShadowMapTex);
    ps->importResource(Define::PixelShaderType::Output_Z, Define::PixelShaderName::OUTPUT_Z);
    vs->importResource(Define::VertexShaderType::Output_Z, Define::VertexShaderName::OUTPUT_Z);

    const float lightScale = 1.5f;
    lightPos = Math::Vector3(lightScale * 100, lightScale * 55, lightScale * 100);
    lightLookat = Math::Vector3(0, -20.0f, 0);
    lightView = Math::Matrix4x4::createView(lightPos, lightLookat, Math::Vector3::UP);
    lightProj = Math::Matrix4x4::createProjection(40.0f, 1.0f, 1.0f, 40.0f, 300.0f);
    cameraView = Math::Matrix4x4::createView(
        Math::Vector3(0, 70, 40),
        Math::Vector3(20, -20, 020),
        Math::Vector3::UP
    );
    cameraProj = Math::Matrix4x4::createProjection(45.0f,
        Define::Window::WIDTH, Define::Window::HEIGHT, 10.0f, 1000.0f);

    mNormalVS = vs->getResource(Define::VertexShaderType::Model);
    mNormalPS = ps->getResource(Define::PixelShaderType::Model_NoTexture);
    mOutputVS = vs->getResource(Define::VertexShaderType::Output_Z);
    mOutputPS = ps->getResource(Define::PixelShaderType::Output_Z);
    mShadowVS = vs->getResource(Define::VertexShaderType::Model_Shadow);
    mShadowPS = ps->getResource(Define::PixelShaderType::Model_Shadow);

    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;
    blendDesc.RenderTarget[0] = CreateTestBlendDesc();

    Utility::getDevice()->CreateBlendState(&blendDesc, &mAlphaBlend);

    blendDesc.RenderTarget[0] = CreateDefaultBlendDesc();
    Utility::getDevice()->CreateBlendState(&blendDesc, &mNoAlpha);


    mSprite->setScale(Math::Vector2(0.25f, 0.25f));
    f = 0.0f;
}

ShadowMapTest::~ShadowMapTest() {}

void ShadowMapTest::load(Framework::Scene::Collecter & collecter) {}

void ShadowMapTest::update(float delta) {
    f += 0.2f;
}

bool ShadowMapTest::isEndScene() const {
    return false;
}

void ShadowMapTest::draw() {
    //float clear[4] = { D3D11_BLEND_ONE,D3D11_BLEND_ONE,D3D11_BLEND_ONE,D3D11_BLEND_ONE };
    float clear[4] = { 0,0,0,0 };
    Utility::getContext()->OMSetBlendState(mAlphaBlend.Get(), clear, 0xffffffff);

    Graphics::Color4 color(1.0f, 0.0f, 0.0f, 0.2f);
    Utility::getConstantBufferManager()->setColor(
        Graphics::ConstantBufferParameterType::Color,
        color);

    std::vector<Utility::Transform> objectTransforms;
    const int num = 4;
    for (int x = 0; x < num; x++) {
        for (int z = 0; z < num; z++) {
            Math::Quaternion rot =
                Math::Quaternion::createRotateAboutY(f)
                * Math::Quaternion::createRotateAboutZ(f*2.353f);
            objectTransforms.emplace_back(Utility::Transform(
                Math::Vector3(x * 20.0f, std::sinf(f / 10) * 20, z * 20.0f),
                rot,
                Math::Vector3(1.0f, 1.0f, 1.0f)
            ));
        }
    }

    auto drawObject = [&](auto s1, auto s2) {
        mObject.mModel->setVertexShader(s1);
        mObject.mModel->setPixelShader(s2);

        for (auto&& tr : objectTransforms) {
            mObject.mTransform = tr;
            mObject.draw();
        }

        mFloor.mModel->setVertexShader(s1);
        mFloor.mModel->setPixelShader(s2);

        mFloor.draw();
    };

    auto outZ = [&]() {
        ID3D11RenderTargetView* backView;
        ID3D11DepthStencilView* backDepthStencil;
        D3D11_VIEWPORT backViewport;
        UINT backViewNum = 1;

        Utility::getContext()->RSGetViewports(&backViewNum, &backViewport);
        Utility::getContext()->OMGetRenderTargets(1, &backView, &backDepthStencil);

        mViewport->set();
        mPerspectiveCamera->setMatrix();

        mRenderTargetView->set();

        mRenderTargetView->clear(ClearShadowMapColor);

        Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::View, lightView);
        Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::Projection, lightProj);

        drawObject(mOutputVS, mOutputPS);

        Utility::getContext()->OMSetRenderTargets(1, &backView, backDepthStencil);
        Utility::getContext()->RSSetViewports(backViewNum, &backViewport);
    };

    auto drawWithShadow = [&]() {
        mShadowMapTex->setData(Graphics::ShaderInputType::Pixel, 0);

        mPerspectiveCamera->setView(cameraView);
        mPerspectiveCamera->setProjection(cameraProj);
        mPerspectiveCamera->setMatrix();

        Graphics::LightMatrixCBufferStruct lm;
        lm.view = Math::Matrix4x4::transposition(lightView);
        lm.proj = Math::Matrix4x4::transposition(lightProj);
        Utility::getConstantBufferManager()->setStruct(lm);

        drawObject(mShadowVS, mShadowPS);
    };

    auto drawNormal = [&]() {
        mPerspectiveCamera->setView(cameraView);
        mPerspectiveCamera->setProjection(cameraProj);
        mPerspectiveCamera->setMatrix();

        drawObject(mNormalVS, mNormalPS);
    };

    outZ();
    Utility::getContext()->OMSetBlendState(mNoAlpha.Get(), clear, 0xffffffff);

    cameraView = Math::Matrix4x4::createView(
        Math::Vector3(40 * std::sinf(f / 10), 70, 40 * std::cosf(f / 10)),
        Math::Vector3(20, -20, 20),
        Math::Vector3::UP
    );

    drawWithShadow();

    //drawNormal();

    mOrthographicCamera->setMatrix();
    mSprite->draw();
}

void ShadowMapTest::end() {}

Define::SceneType ShadowMapTest::next() {
    return Define::SceneType();
}

void ShadowMapTest::GameObject::draw() {
    mModel->draw(mTransform);
}
