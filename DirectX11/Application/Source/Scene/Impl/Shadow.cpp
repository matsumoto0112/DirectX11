#include "Shadow.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Renderer/IRenderer.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/IO/FBXLoader.h"
#include "Framework/Define/Path.h"
#include "Framework/Define/Config.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Render/RenderTarget.h"
#include "Framework/Graphics/Render/DepthStencilView.h"
#include "Framework/Graphics/Desc/RenderTargetViewDesc.h"
#include "Framework/Graphics/Desc/DepthStencilDesc.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Graphics/Renderer/PrimitiveVertex.h"

using namespace Framework;

namespace {
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
std::vector<Utility::Transform> mTransform;
std::shared_ptr<Graphics::Model> mModel;
std::shared_ptr<Graphics::Effect> mShadowEffect;
std::shared_ptr<Graphics::Effect> mModelEffect;
std::shared_ptr<Graphics::Effect> mDrawDepth;
std::shared_ptr<Graphics::Sprite2D> mSprite;
std::shared_ptr<Graphics::Model> mFloor;
Utility::Transform mFloorTransform;
std::shared_ptr<Graphics::Effect> mFloorEffect;

struct LightMatrix {
    Math::Matrix4x4 view;
    Math::Matrix4x4 proj;
};
LightMatrix mLightMatrixData;
ComPtr<ID3D11Texture2D> mRenderTargetTexture;
ComPtr<ID3D11RenderTargetView> mRenderTarget;
ComPtr<ID3D11ShaderResourceView> mRenderTargetSRV;
ComPtr<ID3D11DepthStencilView> mDepthStencil;
float mTheta;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getDefaultDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}

}
Shadow::Shadow() {
    ////カメラの初期化
    //m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
    //    Math::ViewInfo{ Math::Vector3(0,10,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
    //    Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,300.0f });

    //m2DCamera = std::make_shared<Graphics::OrthographicCamera>(Define::Config::getInstance()->getSize());
    ////アルファブレンドの作成
    //mAlphaBlend = createAlphaBlend();

    ////ラスタライザ作成
    //D3D11_RASTERIZER_DESC rasterizerDesc;
    //ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    //rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    //rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    //rasterizerDesc.DepthClipEnable = TRUE;
    //rasterizerDesc.MultisampleEnable = FALSE;
    //rasterizerDesc.DepthBiasClamp = 0;
    //rasterizerDesc.SlopeScaledDepthBias = 0;
    //Graphics::DX11InterfaceAccessor::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    //Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());
    ////Utility::FBXLoader loader(Define::Path::getInstance()->fbxModel() + "049d62f6-093d-4a3c-940e-b2f4fad27d9d.fbx");
    //Utility::FBXLoader loader(::Define::Path::getInstance()->fbxModel() + "a2380cb0-6f46-41a7-8cde-3db2ec73e8ed.fbx");
    //std::vector<Math::Vector4> pos = loader.getPosition();
    //std::vector<UINT> indices(pos.size());
    //for (int i = 0; i < indices.size() / 3; i++) {
    //    indices[i * 3 + 0] = i * 3 + 2;
    //    indices[i * 3 + 1] = i * 3 + 1;
    //    indices[i * 3 + 2] = i * 3 + 0;
    //}

    //auto vs = Utility::ResourceManager::getInstance()->getVertexShader()->getResource(Define::VertexShaderType::Only_Position);
    //auto ps = Utility::ResourceManager::getInstance()->getPixelShader()->getResource(Define::PixelShaderType::Output_Color);

    //mModel = std::make_unique<Graphics::Model>(std::make_shared<Graphics::VertexBuffer>(pos),
    //    std::make_shared<Graphics::IndexBuffer>(indices, Graphics::PrimitiveTopology::TriangleList),
    //    std::make_shared<Graphics::Effect>(vs, ps));

    ////for (int x = -2; x < 2; x++) {
    ////    for (int z = -2; z < 2; z++) {
    ////        mTransform.emplace_back(Math::Vector3(x, 0, z), Math::Quaternion::IDENTITY, Math::Vector3(1.0f, 1.0f, 1.0f));
    ////    }
    ////}
    //mTransform.emplace_back(Math::Vector3(0, 0, 0), Math::Quaternion::IDENTITY, Math::Vector3(1, 1, 1));

    //mLightMatrixData.proj = m3DCamera->getProjection();
    //mModelEffect = mModel->getEffect();
    //mShadowEffect = std::make_shared<Graphics::Effect>(
    //    std::make_shared<Graphics::VertexShader>("ShadowMap/ShadowMapCreate_VS"), nullptr);

    //mDrawDepth = std::make_shared<Graphics::Effect>(
    //    std::make_shared<Graphics::VertexShader>("2D/Texture2D_VS"),
    //    std::make_shared<Graphics::PixelShader>("ShadowMap/Depth_PS"));

    //UINT width = Define::Config::getInstance()->getWidth();
    //UINT height = Define::Config::getInstance()->getHeight();

    //{
    //    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{};
    //    rtvDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
    //    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    //    D3D11_TEXTURE2D_DESC texDesc{};
    //    texDesc.Width = width;
    //    texDesc.Height = height;
    //    texDesc.MipLevels = 1;
    //    texDesc.ArraySize = 1;
    //    texDesc.Format = rtvDesc.Format;
    //    texDesc.SampleDesc.Count = 1;
    //    texDesc.SampleDesc.Quality = 0;
    //    texDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    //    texDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
    //    texDesc.CPUAccessFlags = 0;
    //    std::shared_ptr<Graphics::TextureBuffer> buffer = std::make_shared<Graphics::TextureBuffer>(texDesc);
    //    std::shared_ptr<Graphics::ShaderResourceView> srv = std::make_shared<Graphics::ShaderResourceView>(*buffer);
    //    std::shared_ptr<Graphics::Texture> tex = std::make_shared<Graphics::Texture>(buffer, srv, width, height);
    //    Graphics::DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(buffer->getBuffer().Get(), &rtvDesc, &mRenderTarget);
    //}
    //{
    //    D3D11_TEXTURE2D_DESC texDesc{};
    //    texDesc.Width = width;
    //    texDesc.Height = height;
    //    texDesc.MipLevels = 1;
    //    texDesc.ArraySize = 1;
    //    texDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R24G8_TYPELESS;
    //    texDesc.SampleDesc.Count = 1;
    //    texDesc.SampleDesc.Quality = 0;
    //    texDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    //    texDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
    //    texDesc.CPUAccessFlags = 0;
    //    std::shared_ptr<Graphics::TextureBuffer> buffer = std::make_shared<Graphics::TextureBuffer>(texDesc);

    //    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
    //    srvDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    //    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    //    srvDesc.Texture2D.MipLevels = 1;

    //    std::shared_ptr<Graphics::ShaderResourceView> srv = std::make_shared<Graphics::ShaderResourceView>(*buffer, srvDesc);

    //    std::shared_ptr<Graphics::Texture> tex = std::make_shared<Graphics::Texture>(buffer, srv, width, height);
    //    mSprite = std::make_shared<Graphics::Sprite2D>(tex);


    //    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
    //    dsvDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
    //    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
    //    dsvDesc.Texture2D.MipSlice = 0;
    //    Graphics::DX11InterfaceAccessor::getDevice()->CreateDepthStencilView(buffer->getBuffer().Get(), &dsvDesc, &mDepthStencil);
    //    mSprite->setScale(Math::Vector2(0.25f, 0.25f));

    //}
    //{

    //    std::vector<Math::Vector4> pos = Graphics::PrimitiveVertex::cubePosition();
    //    std::vector<UINT> index = Graphics::PrimitiveVertex::cubeIndex();
    //    std::shared_ptr<Graphics::VertexBuffer> vb = std::make_shared<Graphics::VertexBuffer>(pos);
    //    std::shared_ptr<Graphics::IndexBuffer> ib = std::make_shared<Graphics::IndexBuffer>(index, Graphics::PrimitiveTopology::TriangleList);
    //    mFloorEffect = std::make_shared<Graphics::Effect>(
    //        std::make_shared<Graphics::VertexShader>("ShadowMap/ShadowMap_VS"),
    //        std::make_shared<Graphics::PixelShader>("ShadowMap/ShadowMap_PS"));
    //    mFloor = std::make_shared<Graphics::Model>(vb, ib, mFloorEffect);
    //    mFloorTransform.setPosition(Math::Vector3(0, -3, 0));
    //    mFloorTransform.setScale(Math::Vector3(10.0f, 0.1f, 10.0f));
    //}

    mTheta = 0.0f;
}

Shadow::~Shadow() { }

void Shadow::load(Framework::Scene::Collecter& collecter) { }

void Shadow::update() {
    for (auto&& tr : mTransform) {
        //tr.setRotate(tr.getRotate() * Math::Quaternion::createRotateAboutY(1.0f));
    }
    //mTransform.setPosition(mTransform.getPosition() + Math::Vector3(0, 0, 1));
}

bool Shadow::isEndScene() const {
    return false;
}

void Shadow::draw(Framework::Graphics::IRenderer* renderer) {
    //Graphics::DX11InterfaceAccessor::getContext()->RSSetState(ras.Get());
    //renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 0.0f));
    //mAlphaBlend->set();
    //Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);

    //mTheta += 0.1f;
    //float x = Math::MathUtility::sin(mTheta) * 1;
    //float z = Math::MathUtility::cos(mTheta * 0.5f) * 1;
    //mLightMatrixData.view = Math::Matrix4x4::createView({ Math::Vector3(x,5,z),Math::Vector3(0,0,0),Math::Vector3::UP });
    //Graphics::ConstantBufferManager* cbManager = Utility::getConstantBufferManager();
    //cbManager->setMatrix(Graphics::ConstantBufferParameterType::LightView, mLightMatrixData.view);
    //cbManager->setMatrix(Graphics::ConstantBufferParameterType::LightProj, mLightMatrixData.proj);
    //cbManager->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f));
    //cbManager->send();

    //Graphics::DX11InterfaceAccessor::getContext()->OMSetRenderTargets(1, mRenderTarget.GetAddressOf(), mDepthStencil.Get());
    //const float clear[] = { 0.0f,0.0f,0.0f,1.0f };
    //Graphics::DX11InterfaceAccessor::getContext()->ClearRenderTargetView(mRenderTarget.Get(), clear);
    //Graphics::DX11InterfaceAccessor::getContext()->ClearDepthStencilView(mDepthStencil.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    //mModel->setEffect(mShadowEffect);
    //for (auto&& tr : mTransform) {
    //    mModel->draw(tr);
    //}

    //mFloor->setEffect(mShadowEffect);
    //mFloor->draw(mFloorTransform);

    //renderer->begin();
    //Utility::getCameraManager()->setOrthographicCamera(m2DCamera);
    //mSprite->draw(mDrawDepth);

    //Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    //mModel->setEffect(mFloorEffect);
    //for (auto&& tr : mTransform) {
    //    mModel->draw(tr);
    //}

    //Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f));
    //Utility::getConstantBufferManager()->send();
    //mFloor->setEffect(mFloorEffect);
    //mFloor->draw(mFloorTransform);
}

void Shadow::end() { }

Define::SceneType Shadow::next() {
    return Define::SceneType();
}
