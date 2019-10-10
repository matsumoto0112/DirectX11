#include "Shadow.h"
#include "Framework/Graphics/Render/AlphaBlendSetting.h"
#include "Framework/Graphics/Render/AlphaBlend.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/Wrap/DirectX.h"
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
#include "Framework/Graphics/Shader/ShaderResourceView.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"

using namespace Framework;

namespace {
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
Utility::Transform mTransform;
std::unique_ptr<Graphics::Model> mModel;
std::shared_ptr<Graphics::Effect> mShadowEffect;
std::shared_ptr<Graphics::Effect> mModelEffect;
std::shared_ptr<Graphics::Sprite2D> mSprite;

struct LightMatrix {
    Math::Matrix4x4 view;
    Math::Matrix4x4 proj;
};
std::unique_ptr<Graphics::ConstantBuffer<LightMatrix>> mLightMatrix;
LightMatrix mLightMatrixData;
ComPtr<ID3D11Texture2D> mRenderTargetTexture;
ComPtr<ID3D11RenderTargetView> mRenderTarget;
ComPtr<ID3D11ShaderResourceView> mRenderTargetSRV;
ComPtr<ID3D11DepthStencilView> mDepthStencil;

std::unique_ptr<Graphics::AlphaBlend> createAlphaBlend() {
    D3D11_BLEND_DESC desc;
    desc.AlphaToCoverageEnable = FALSE;
    desc.IndependentBlendEnable = FALSE;
    desc.RenderTarget[0] = Graphics::AlphaBlendSetting::getDefaultDesc();
    return std::make_unique<Graphics::AlphaBlend>(desc);
}

}
Shadow::Shadow() {
    //カメラの初期化
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance().getSize(),0.1f,1000.0f });

    m2DCamera = std::make_shared<Graphics::OrthographicCamera>(Define::Config::getInstance().getSize());
    //アルファブレンドの作成
    mAlphaBlend = createAlphaBlend();

    //ラスタライザ作成
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
    std::vector<UINT> indices(pos.size());
    for (int i = 0; i < indices.size() / 3; i++) {
        indices[i * 3 + 0] = i * 3 + 2;
        indices[i * 3 + 1] = i * 3 + 1;
        indices[i * 3 + 2] = i * 3 + 0;
    }
    auto vs = Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Only_Position);
    auto ps = Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Output_Color);

    mModel = std::make_unique<Graphics::Model>(std::make_shared<Graphics::VertexBuffer>(pos),
        std::make_shared<Graphics::IndexBuffer>(indices, Graphics::PrimitiveTopology::TriangleList),
        std::make_shared<Graphics::Effect>(vs, ps));

    mTransform = Utility::Transform(Math::Vector3::ZERO, Math::Quaternion::IDENTITY, Math::Vector3(5.0f, 5.0f, 5.0f));

    mLightMatrixData.view = m3DCamera->getView().transpose();
    mLightMatrixData.proj = m3DCamera->getProjection().transpose();
    mLightMatrix = std::make_unique<Graphics::ConstantBuffer<LightMatrix>>(Graphics::ShaderInputType::All, 7);
    mLightMatrix->setBuffer(mLightMatrixData);
    mModelEffect = mModel->getEffect();
    mModelEffect->setPixelShader(nullptr);
    mShadowEffect = std::make_shared<Graphics::Effect>(
        std::make_shared<Graphics::VertexShader>("ShadowMap/ShadowMapCreate_VS"), nullptr);

    UINT width = Define::Config::getInstance().mWidth;
    UINT height = Define::Config::getInstance().mHeight;

    //mSprite = std::make_shared<Graphics::Sprite2D>(mRenderTarget->getRenderTargetTexture());

    {
        D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{};
        rtvDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
        rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        D3D11_TEXTURE2D_DESC texDesc{};
        texDesc.Width = width;
        texDesc.Height = height;
        texDesc.MipLevels = 1;
        texDesc.ArraySize = 1;
        texDesc.Format = rtvDesc.Format;
        texDesc.SampleDesc.Count = 1;
        texDesc.SampleDesc.Quality = 0;
        texDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        texDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
        texDesc.CPUAccessFlags = 0;
        std::shared_ptr<Graphics::TextureBuffer> buffer = std::make_shared<Graphics::TextureBuffer>(texDesc);
        std::shared_ptr<Graphics::ShaderResourceView> srv = std::make_shared<Graphics::ShaderResourceView>(*buffer);
        std::shared_ptr<Graphics::Texture> tex = std::make_shared<Graphics::Texture>(buffer, srv, width, height);
        //mSprite = std::make_shared<Graphics::Sprite2D>(tex);
        Utility::getDevice()->CreateRenderTargetView(buffer->getBuffer().Get(), &rtvDesc, &mRenderTarget);
    }
    {
        D3D11_TEXTURE2D_DESC texDesc{};
        texDesc.Width = width;
        texDesc.Height = height;
        texDesc.MipLevels = 1;
        texDesc.ArraySize = 1;
        texDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R24G8_TYPELESS;
        texDesc.SampleDesc.Count = 1;
        texDesc.SampleDesc.Quality = 0;
        texDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        texDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
        texDesc.CPUAccessFlags = 0;
        std::shared_ptr<Graphics::TextureBuffer> buffer = std::make_shared<Graphics::TextureBuffer>(texDesc);

        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
        srvDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;

        std::shared_ptr<Graphics::ShaderResourceView> srv = std::make_shared<Graphics::ShaderResourceView>(*buffer, srvDesc);

        std::shared_ptr<Graphics::Texture> tex = std::make_shared<Graphics::Texture>(buffer, srv, width, height);
        mSprite = std::make_shared<Graphics::Sprite2D>(tex);

        D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
        dsvDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
        dsvDesc.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
        dsvDesc.Texture2D.MipSlice = 0;
        Utility::getDevice()->CreateDepthStencilView(buffer->getBuffer().Get(), &dsvDesc, &mDepthStencil);
    }
}

Shadow::~Shadow() { }

void Shadow::load(Framework::Scene::Collecter& collecter) { }

void Shadow::update() {
    mTransform.setRotate(mTransform.getRotate() * Math::Quaternion::createRotateAboutY(1.0f));
}

bool Shadow::isEndScene() const {
    return false;
}

void Shadow::draw(Framework::Graphics::IRenderer* renderer) {
    Utility::getContext()->RSSetState(ras.Get());
    renderer->setBackColor(Graphics::Color4(0.0f, 0.0f, 0.0f, 1.0f));
    mAlphaBlend->set();
    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);

    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f));
    mLightMatrix->sendBuffer();

    Utility::getContext()->OMSetRenderTargets(1, mRenderTarget.GetAddressOf(), mDepthStencil.Get());
    const float clear[] = { 0.0f,0.0f,0.0f,0.0f };
    Utility::getContext()->ClearRenderTargetView(mRenderTarget.Get(), clear);
    Utility::getContext()->ClearDepthStencilView(mDepthStencil.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    mModel->setEffect(mModelEffect);
    mModel->draw(mTransform);

    renderer->begin();

    Utility::getCameraManager()->setOrthographicCamera(m2DCamera);
    renderer->render(mSprite);
    //mModel->setEffect(mModelEffect);
    //mModel->draw(mTransform);
}

void Shadow::end() { }

Define::SceneType Shadow::next() {
    return Define::SceneType();
}
