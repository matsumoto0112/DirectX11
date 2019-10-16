#include "DirLight.h"
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

std::unique_ptr<Graphics::Sampler> mDefaultSampler;
std::shared_ptr<Graphics::Model> mModel;
std::vector<Utility::Transform> mTransform;
std::shared_ptr<Graphics::Model> mFloor;
Utility::Transform mFloorTransform;

struct LightMatrix {
    Math::Matrix4x4 view;
    Math::Matrix4x4 proj;
};
LightMatrix mLightMatrixData;


DirLight::DirLight() {
    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
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

    {
        auto vs = ShaderLoad::loadVS("Lighting/DirLight/VS");
        auto ps = ShaderLoad::loadPS("Lighting/DirLight/PS");

        mModel = std::make_unique<Graphics::Model>(std::make_shared<Graphics::VertexBuffer>(pos),
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

    mLightMatrixData.view = Math::Matrix4x4::createView({ Math::Vector3(0,5,0),Math::Vector3(0,0,0),Math::Vector3::UP });
    mLightMatrixData.proj = m3DCamera->getProjection();

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
}

DirLight::~DirLight() { }

void DirLight::load(Framework::Scene::Collecter& collecter) {
    //このシーンで使用するステートを作成する
    auto newRasterizer = std::make_shared<Graphics::RasterizerState>(
        Graphics::RasterizerStateDesc::getDefaultDesc(Graphics::FillMode::Solid, Graphics::CullMode::Back));
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

void DirLight::update() {
    for (auto&& tr : mTransform) {
        tr.setRotate(tr.getRotate() * Math::Quaternion::createRotateAboutY(1.0f));
    }
}

bool DirLight::isEndScene() const {
    return false;
}

void DirLight::draw(Framework::Graphics::IRenderer* renderer) {
    renderer->getRenderTarget()->setBackColor(Graphics::Color4(0.3f, 0, 0, 0));
    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    Utility::getCameraManager()->setOrthographicCamera(m2DCamera);

    Graphics::ConstantBufferManager* cbManager = Utility::getConstantBufferManager();
    cbManager->setMatrix(Graphics::ConstantBufferParameterType::LightView, mLightMatrixData.view);
    cbManager->setMatrix(Graphics::ConstantBufferParameterType::LightProj, mLightMatrixData.proj);
    mDefaultSampler->setData(Graphics::ShaderInputType::Pixel, 0);

    {
        for (auto&& tr : mTransform) {
            mModel->getMaterial<Graphics::ModelMaterial>()->mWorldMatrix.mData = tr.createSRTMatrix();
            renderer->render(mModel.get());
        }
        //renderer->render(mFloor.get());
    }
}

void DirLight::unload() {
    Graphics::IRenderer* backBufferRenderer = Utility::getRenderingManager()->getRenderer();

    backBufferRenderer->getPipeline()->setRasterizerState(mPrevRasterizer);
    backBufferRenderer->getPipeline()->setAlphaBlend(mPrevAlphaBlend);
}

Define::SceneType DirLight::next() {
    return Define::SceneType();
}
