#include "NormalizedLambert.h"
#include "Framework/Graphics/Desc/BlendStateDesc.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/IO/FBXLoader.h"
#include "Framework/Define/Path.h"
#include "Framework/Define/Config.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Desc/RenderTargetViewDesc.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Graphics/Renderer/PrimitiveVertex.h"
#include "Framework/Graphics/Sprite/Sprite2D.h"
#include "Framework/Graphics/Desc/RasterizerStateDesc.h"
#include "Framework/Graphics/Texture/Sampler.h"
#include "Source/Utility/Shader/ShaderLoad.h"

using namespace Framework;

namespace {
std::unique_ptr<Graphics::Sampler> mDefaultSampler;
std::shared_ptr<Graphics::Model> mModel;
std::vector<Utility::Transform> mTransform;
std::shared_ptr<Graphics::Model> mFloor;
Utility::Transform mFloorTransform;

Graphics::LightCBuffer mLightData;
}


NormalizedLambert::NormalizedLambert() {
    //カメラの初期化
    m3DCamera = std::make_shared<DebugCamera>(
        Math::ViewInfo{ Math::Vector3(0,10,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,300.0f });

    m2DCamera = std::make_shared<Graphics::OrthographicCamera>(Define::Config::getInstance()->getSize());

    mDefaultSampler = std::make_unique<Graphics::Sampler>(Graphics::TextureAddressMode::Wrap, Graphics::TextureFilterMode::MinMagMipLinear);

    Utility::FBXLoader loader(Define::Path::getInstance()->fbxModel() + "pyramid.fbx");
    //Utility::FBXLoader loader(Define::Path::getInstance()->fbxModel() + "049d62f6-093d-4a3c-940e-b2f4fad27d9d.fbx");
    //Utility::FBXLoader loader(::Define::Path::getInstance()->fbxModel() + "a2380cb0-6f46-41a7-8cde-3db2ec73e8ed.fbx");
    std::vector<Math::Vector4> pos;
    std::vector<UINT> indices;
    loader.getPosition(&pos, &indices);
    std::vector<Math::Vector3> normal = loader.getNormal();
    std::vector<Graphics::NormalVertex> vert(pos.size());
    for (UINT n = 0; n < pos.size(); n++) {
        vert[n].pos = pos[n];
        vert[n].normal = normal[n];
    }

    {
        auto vs = ShaderLoad::loadVS("Lighting/NormalizedLambert_VS");
        auto ps = ShaderLoad::loadPS("Lighting/NormalizedLambert_PS");

        mModel = std::make_unique<Graphics::Model>(std::make_shared<Graphics::VertexBuffer>(vert),
            std::make_shared<Graphics::IndexBuffer>(indices, Graphics::PrimitiveTopology::TriangleList),
            std::make_shared<Graphics::Effect>(vs, ps),
            std::make_shared<Graphics::ModelMaterial>());
        auto mat = mModel->getMaterial<Graphics::ModelMaterial>();
        mat->mColor.mData = Graphics::Color4(0.25f, 0.5f, 0.6f, 1.0f);
    }

    //同じモデルを使いまわすために座標だけ複数個作っておく
    //for (float x = -2.0f; x < 2.0f; x += 1.0f) {
    //    for (float z = -2.0f; z <= 2.0f; z += 1.0f) {
    //        mTransform.emplace_back(Math::Vector3(x, 0, z), Math::Quaternion::IDENTITY, Math::Vector3(1.0f, 1.0f, 1.0f));
    //    }
    //}
    mTransform.emplace_back(Math::Vector3(0, 0, 0), Math::Quaternion::IDENTITY, Math::Vector3(10, 10, 10));

    mLightData.direction = Math::Vector4(1, 1, 0, 1);
    mLightData.color = Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f);

    UINT width = Define::Config::getInstance()->getWidth();
    UINT height = Define::Config::getInstance()->getHeight();
    {
        std::vector<Math::Vector4> pos = Graphics::PrimitiveVertex::cubePosition();
        std::vector<UINT> index = Graphics::PrimitiveVertex::cubeIndex();
        std::shared_ptr<Graphics::VertexBuffer> vb = std::make_shared<Graphics::VertexBuffer>(pos);
        std::shared_ptr<Graphics::IndexBuffer> ib = std::make_shared<Graphics::IndexBuffer>(index, Graphics::PrimitiveTopology::TriangleList);
        mFloor = std::make_shared<Graphics::Model>(vb, ib, mModel->getEffect(),
            std::make_shared<Graphics::ModelMaterial>());
        mFloorTransform.setPosition(Math::Vector3(0, -3, 0));
        mFloorTransform.setScale(Math::Vector3(10.0f, 0.1f, 10.0f));
        auto mat = mFloor->getMaterial<Graphics::ModelMaterial>();
        mat->mWorldMatrix.mData = mFloorTransform.createSRTMatrix();
        mat->mColor.mData = Graphics::Color4(0.0f, 1.0f, 1.0f, 1.0f);
    }

    mDebugWindow = std::make_unique<ImGUI::Window>("Light Parameter");
#define ADD_PARAMETE_CHANGE_FIELD(name,param,min,max) { \
    std::shared_ptr<ImGUI::FloatField> field = std::make_shared<ImGUI::FloatField>(#name, param, [&](float val) { \
        param = val; \
    }); \
    field->setMinValue(min); \
    field->setMaxValue(max); \
    mDebugWindow->addItem(field); \
    }
    ADD_PARAMETE_CHANGE_FIELD(X, mLightData.direction.x, -1.0f, 1.0f);
    ADD_PARAMETE_CHANGE_FIELD(Y, mLightData.direction.y, -1.0f, 1.0f);
    ADD_PARAMETE_CHANGE_FIELD(Z, mLightData.direction.z, -1.0f, 1.0f);
    ADD_PARAMETE_CHANGE_FIELD(R, mLightData.color.r, 0.0f, 1.0f);
    ADD_PARAMETE_CHANGE_FIELD(G, mLightData.color.g, 0.0f, 1.0f);
    ADD_PARAMETE_CHANGE_FIELD(B, mLightData.color.b, 0.0f, 1.0f);
}

NormalizedLambert::~NormalizedLambert() { }

void NormalizedLambert::load(Framework::Scene::Collecter& collecter) {
    //このシーンで使用するステートを作成する
    auto newRasterizer = std::make_shared<Graphics::RasterizerState>(
        Graphics::RasterizerStateDesc::getDefaultDesc(Graphics::FillMode::Solid, Graphics::CullMode::None));
    auto newBlendState = std::make_shared<Graphics::AlphaBlend>(
        Graphics::BlendStateDesc::BLEND_DESC(Graphics::AlphaBlendType::Alignment));

    //前の状態をコピーしておく
    //シーン終了時にもとに戻してあげる
    Graphics::IRenderer* backBufferRenderer = Utility::getRenderingManager()->getRenderer();
    mPrevRasterizer = backBufferRenderer->getPipeline()->getRasterizerState();
    mPrevAlphaBlend = backBufferRenderer->getPipeline()->getAlphaBlend();
    backBufferRenderer->getPipeline()->setRasterizerState(newRasterizer);
    backBufferRenderer->getPipeline()->setAlphaBlend(newBlendState);
}

void NormalizedLambert::update() {
    for (auto&& tr : mTransform) {
        tr.setRotate(tr.getRotate() * Math::Quaternion::createRotateAboutY(1.0f));
    }
}

bool NormalizedLambert::isEndScene() const {
    return false;
}

void NormalizedLambert::draw(Framework::Graphics::IRenderer* renderer) {
    renderer->getRenderTarget()->setBackColor(Graphics::Color4(0.0f, 0, 0, 0));
    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    Utility::getCameraManager()->setOrthographicCamera(m2DCamera);

    Graphics::ConstantBufferManager* cbManager = Utility::getConstantBufferManager();
    cbManager->setVector4(Graphics::ConstantBufferParameterType::DirectionalLightDirection, mLightData.direction);
    cbManager->setColor(Graphics::ConstantBufferParameterType::DirectionalLightColor, mLightData.color);
    mDefaultSampler->setData(Graphics::ShaderInputType::Pixel, 0);

    {
        for (auto&& tr : mTransform) {
            mModel->getMaterial<Graphics::ModelMaterial>()->mWorldMatrix.mData = tr.createSRTMatrix();
            renderer->render(mModel.get());
        }
        //renderer->render(mFloor.get());
    }

    mDebugWindow->draw();
    m3DCamera->drawControlWindow();
}

void NormalizedLambert::unload() {
    Graphics::IRenderer* backBufferRenderer = Utility::getRenderingManager()->getRenderer();

    backBufferRenderer->getPipeline()->setRasterizerState(mPrevRasterizer);
    backBufferRenderer->getPipeline()->setAlphaBlend(mPrevAlphaBlend);
}

Define::SceneType NormalizedLambert::next() {
    return Define::SceneType();
}
