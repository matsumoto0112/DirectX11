#include "RenderModel.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/IO/FBXLoader.h"
#include "Framework/Define/Path.h"
#include "Framework/Define/Config.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Graphics/Desc/BlendStateDesc.h"

using namespace Framework;

namespace {
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
Utility::Transform mTransform;
std::unique_ptr<Graphics::Model> mModel;
}
RenderModel::RenderModel() {
    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,1000.0f });

    //アルファブレンドの作成
    mAlphaBlend = std::make_unique<Graphics::AlphaBlend>(Graphics::BlendStateDesc::BLEND_DESC(Graphics::AlphaBlendType::Default));

    //ラスタライザ作成
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    Graphics::DX11InterfaceAccessor::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());
    //Utility::FBXLoader loader(Define::Path::getInstance()->fbxModel() + "049d62f6-093d-4a3c-940e-b2f4fad27d9d.fbx");
    Utility::FBXLoader loader(::Define::Path::getInstance()->fbxModel() + "a2380cb0-6f46-41a7-8cde-3db2ec73e8ed.fbx");
    std::vector<Math::Vector4> pos = loader.getPosition();
    std::vector<UINT> indices(pos.size());
    for (int i = 0; i < indices.size() / 3; i++) {
        indices[i * 3 + 0] = i * 3 + 2;
        indices[i * 3 + 1] = i * 3 + 1;
        indices[i * 3 + 2] = i * 3 + 0;
    }
    auto vs = std::make_shared<Graphics::VertexShader>("3D/Only_Position_VS");
    auto ps = std::make_shared<Graphics::PixelShader>("3D/Output_Color_PS");;

    mModel = std::make_unique<Graphics::Model>(std::make_shared<Graphics::VertexBuffer>(pos),
        std::make_shared<Graphics::IndexBuffer>(indices, Graphics::PrimitiveTopology::TriangleList),
        std::make_shared<Graphics::Effect>(vs, ps));

    mTransform = Utility::Transform(Math::Vector3::ZERO, Math::Quaternion::IDENTITY, Math::Vector3(5.0f, 5.0f, 5.0f));
}

RenderModel::~RenderModel() { }

void RenderModel::load(Framework::Scene::Collecter& collecter) { }

void RenderModel::update() {
    mTransform.setRotate(mTransform.getRotate() * Math::Quaternion::createRotateAboutY(1.0f));
}

bool RenderModel::isEndScene() const {
    return false;
}

void RenderModel::draw(Framework::Graphics::Pipeline* pipeline) {
    //Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());
    //pipeline->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    //mAlphaBlend->set();
    //Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);

    //Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    //mModel->draw(mTransform);
}

void RenderModel::end() { }

Define::SceneType RenderModel::next() {
    return Define::SceneType();
}
