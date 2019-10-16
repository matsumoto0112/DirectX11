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

using namespace Framework;

std::shared_ptr<Graphics::Model> mModel;
std::vector<Utility::Transform> mTransform;
std::unique_ptr<Graphics::Sampler> mDefaultSampler;

std::shared_ptr<Graphics::Sprite2D> mSprite;
std::shared_ptr<Graphics::Effect> mDepthSpriteEffect;
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

    Utility::FBXLoader loader(Define::Path::getInstance()->fbxModel() + "049d62f6-093d-4a3c-940e-b2f4fad27d9d.fbx");
    //Utility::FBXLoader loader(::Define::Path::getInstance()->fbxModel() + "a2380cb0-6f46-41a7-8cde-3db2ec73e8ed.fbx");
    std::vector<Math::Vector4> pos = loader.getPosition();
    std::vector<UINT> indices(pos.size());
    for (int i = 0; i < indices.size() / 3; i++) {
        indices[i * 3 + 0] = i * 3 + 2;
        indices[i * 3 + 1] = i * 3 + 1;
        indices[i * 3 + 2] = i * 3 + 0;
    }

    {
        auto vs = std::make_shared<Graphics::VertexShader>(Define::Path::getInstance()->shader() + "ShadowMap/ShadowMap_VS.cso");
        auto ps = std::make_shared<Graphics::PixelShader>(Define::Path::getInstance()->shader() + "ShadowMap/ShadowMap_PS.cso");

        mModel = std::make_unique<Graphics::Model>(std::make_shared<Graphics::VertexBuffer>(pos),
            std::make_shared<Graphics::IndexBuffer>(indices, Graphics::PrimitiveTopology::TriangleList),
            std::make_shared<Graphics::Effect>(vs, ps),
            std::make_shared<Graphics::ModelMaterial>());
        auto mat = mModel->getMaterial<Graphics::ModelMaterial>();
        mat->mColor.mData = Graphics::Color4(0.25f, 0.5f, 0.6f, 1.0f);
    }

    //同じモデルを使いまわすために座標だけ複数個作っておく
    for (float x = -2.0f; x < 2.0f; x += 1.0f) {
        for (float z = -2.0f; z <= 2.0f; z += 1.0f) {
            mTransform.emplace_back(Math::Vector3(x, 0, z), Math::Quaternion::IDENTITY, Math::Vector3(1.0f, 1.0f, 1.0f));
        }
    }

    mLightMatrixData.view = Math::Matrix4x4::createView({ Math::Vector3(-5,5,0),Math::Vector3(0,0,0),Math::Vector3::UP });
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

    std::string shaderPath = Define::Path::getInstance()->shader();
    mDepthSpriteEffect = std::make_shared<Graphics::Effect>(
        std::make_shared<Graphics::VertexShader>(shaderPath + "NoDelete/Texture2D_VS.cso"),
        std::make_shared<Graphics::PixelShader>(shaderPath + "ShadowMap/Depth_PS.cso"));
    mSprite->setEffect(mDepthSpriteEffect);
    mSprite->setScale(Math::Vector2(0.25f, 0.25f));
}

DirLight::~DirLight() { }

void DirLight::load(Framework::Scene::Collecter& collecter) { }

void DirLight::update() {
    for (auto&& tr : mTransform) {
        tr.setRotate(tr.getRotate() * Math::Quaternion::createRotateAboutY(1.0f));
    }
}

bool DirLight::isEndScene() const {
    return false;
}

void DirLight::draw(Framework::Graphics::IRenderer* renderer) {
    renderer->getRenderTarget()->setBackColor(Graphics::Color4(0, 0, 0, 0));
    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    Utility::getCameraManager()->setOrthographicCamera(m2DCamera);

    Graphics::ConstantBufferManager* cbManager = Utility::getConstantBufferManager();
    cbManager->setMatrix(Graphics::ConstantBufferParameterType::LightView, mLightMatrixData.view);
    cbManager->setMatrix(Graphics::ConstantBufferParameterType::LightProj, mLightMatrixData.proj);

    renderer->begin();
    mSprite->getTexture()->setData(Graphics::ShaderInputType::Pixel, 0);
    mDefaultSampler->setData(Graphics::ShaderInputType::Pixel, 0);

    {
        renderer->render(mSprite.get());
        for (auto&& tr : mTransform) {
            mModel->getMaterial<Graphics::ModelMaterial>()->mWorldMatrix.mData = tr.createSRTMatrix();
            renderer->render(mModel.get());
        }
        renderer->render(mFloor.get());
    }
}

void DirLight::unload() { }

Define::SceneType DirLight::next() {
    return Define::SceneType();
}
