#include "RenderModel.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/Wrap/DirectX.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/IO/FBXLoader.h"
#include "Framework/Define/Path.h"
#include "Framework/Define/Config.h"

using namespace Framework;

namespace {
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
std::unique_ptr<Graphics::VertexAndIndexBuffer> mVIBuffer;
std::shared_ptr<Graphics::VertexShader> mVShader;
std::shared_ptr<Graphics::PixelShader> mPShader;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getDefaultDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}

}
RenderModel::RenderModel() {
    //�J�����̏�����
    m3DCamera = std::make_unique<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance().getSize(),0.1f,1000.0f });

    //�A���t�@�u�����h�̍쐬
    mAlphaBlend = createAlphaBlend();

    //���X�^���C�U�쐬
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    Utility::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    Utility::getContext()->RSSetState(ras.Get());
    //Utility::FBXLoader loader(Define::Path::getInstance().fbxModel() + "049d62f6-093d-4a3c-940e-b2f4fad27d9d.fbx");
    Utility::FBXLoader loader(::Define::Path::getInstance().fbxModel() + "a2380cb0-6f46-41a7-8cde-3db2ec73e8ed.fbx");
    std::vector<Math::Vector4> pos = loader.getPosition();
    loader.getUV();
    std::vector<UINT> indices(pos.size());
    for (int i = 0; i < indices.size() / 3; i++) {
        indices[i * 3 + 0] = i * 3 + 2;
        indices[i * 3 + 1] = i * 3 + 1;
        indices[i * 3 + 2] = i * 3 + 0;
    }
    mVIBuffer = std::make_unique<Graphics::VertexAndIndexBuffer>(pos, indices, Graphics::PrimitiveTopology::TriangleList);
    mVShader = Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Only_Position);
    mPShader = Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Output_Color);
}

RenderModel::~RenderModel() { }

void RenderModel::load(Framework::Scene::Collecter& collecter) { }

void RenderModel::update() { }

bool RenderModel::isEndScene() const {
    return false;
}

float mAngle = 0.0f;

void RenderModel::draw(Framework::Graphics::IRenderer* renderer) {
    Utility::getContext()->RSSetState(ras.Get());
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mAlphaBlend->set();
    renderer->setCurrentPerspectiveCamera(m3DCamera.get());
    m3DCamera->render();

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    Math::Vector3 scale(5.0f, 5.0f, 5.0f);
    mAngle += 1.0f;
    Math::Matrix4x4 m = Math::Matrix4x4::createScale(scale) * Math::Matrix4x4::createRotationY(mAngle);
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World, m);
    Utility::getConstantBufferManager()->send();
    mVShader->set();
    mPShader->set();
    mVIBuffer->render();
}

void RenderModel::end() { }

Define::SceneType RenderModel::next() {
    return Define::SceneType();
}