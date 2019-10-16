#include "Firefly.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/DX11InterfaceAccessor.h"
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Renderer/Pipeline.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Camera/OrthographicCamera.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Random.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/Renderer/BackBufferRenderer.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Graphics/Particle/GPUParticle.h"
#include "Framework/Graphics/Texture/TextureLoader.h"
#include "Framework/Define/Path.h"
#include "Source/Utility/Shader/ShaderLoad.h"
#include "Framework/Graphics/Desc/BlendStateDesc.h"
#include "Framework/Graphics/Desc/RenderTargetViewDesc.h"
#include "Framework/Graphics/Renderer/PrimitiveVertex.h"
#include "Framework/Graphics/Buffer/VertexBuffer.h"
#include "Framework/Graphics/Buffer/IndexBuffer.h"
#include "Framework/Graphics/Vertex/Vertex.h"

using namespace Framework;

namespace {
using namespace Framework::Graphics;
class MRT {
public:
    /**
    * @brief コンストラクタ
    * @param texture リソーステクスチャ
    * @param desc レンダーターゲットビューの設定
    * @param backColor 背景色
    */
    MRT(std::vector<std::shared_ptr<Texture2D>> texture, const D3D11_RENDER_TARGET_VIEW_DESC* desc,
        const D3D11_VIEWPORT& viewport, const Color4& backColor)
        :mViewport(viewport), mBackColor(backColor) {
        const UINT size = static_cast<UINT>(texture.size());
        mRenderTargetView.resize(size);
        mTexs.resize(size);

        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
        srvDesc.Format = desc->Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;

        for (UINT n = 0; n < size; n++) {
            throwIfFailed(DX11InterfaceAccessor::getDevice()->CreateRenderTargetView(texture[n]->getTexture().Get(),
                desc, &mRenderTargetView[n]));

            std::shared_ptr<Graphics::ShaderResourceView> srv = std::make_shared<Graphics::ShaderResourceView>(texture[n], &srvDesc);
            mTexs[n] = std::make_shared<Graphics::Texture>(texture[n], srv);

        }
    }
    /**
    * @brief デストラクタ
    */
    ~MRT() {
        mRenderTargetView.clear();
    }
    /**
    * @brief レンダーターゲットビューを取得する
    */
    ComPtr<ID3D11RenderTargetView> getRenderTargetView(UINT n) const {
        return mRenderTargetView[n];
    }

    std::shared_ptr<Texture> getTexture(UINT n) const {
        return mTexs[n];
    }
    /**
    * @brief レンダーターゲットのクリア
    */
    void clear() {
        for (auto&& rtv : mRenderTargetView) {
            DX11InterfaceAccessor::getContext()->ClearRenderTargetView(rtv.Get(), mBackColor.get().data());
        }
    }
    /**
    * @brief レンダーターゲットをセットする
    */
    void set() {
        DX11InterfaceAccessor::getContext()->OMSetRenderTargets(2, mRenderTargetView[0].GetAddressOf(), nullptr);
        D3D11_VIEWPORT vp[2] = { mViewport,mViewport };
        DX11InterfaceAccessor::getContext()->RSSetViewports(2, vp);
    }
    /**
    * @brief 描画終了
    */
    void end() {
        ID3D11RenderTargetView* rtv[2]{ nullptr,nullptr };
        DX11InterfaceAccessor::getContext()->OMSetRenderTargets(2, rtv, nullptr);
    }
private:
    std::vector<ComPtr<ID3D11RenderTargetView>> mRenderTargetView; //!< レンダーターゲットビュー
    D3D11_VIEWPORT mViewport; //!< ビューポート
    std::vector<std::shared_ptr<Texture>> mTexs;
private:
    PROPERTY(Color4, mBackColor, BackColor);
};

std::unique_ptr<MRT> mRTV;
std::shared_ptr<Effect> mBlendEffect;
std::unique_ptr<VertexBuffer> mVB;
std::unique_ptr<IndexBuffer> mIB;
}

Firefly::Firefly()
    :GPUParticleBase(Graphics::ComputeShader::Info{ 32,32,1,1,1,1 }, { Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP }) {    //カメラの初期化
    auto cs = ShaderLoad::loadCS("Particle/Firefly/CS", mInfo);

    //パーティクルのデータ作成
    std::vector<Particle> particle(mInfo.particleNum());
    cs->addUAVEnableVertexBuffer(1, particle, 0);

    cs->addSRV(0, createRandomTable());

    std::vector<int> randomSeed{ 0 };
    cs->addUAV(0, randomSeed);

    auto gs = ShaderLoad::loadGS("Particle/Firefly/GS");
    auto ps = ShaderLoad::loadPS("Particle/Firefly/PS");
    auto vs = ShaderLoad::loadVS("Particle/Firefly/VS");

    mGPUParticle.emplace_back(std::make_unique<Graphics::GPUParticle>(mInfo.particleNum(),
        nullptr,
        cs,
        vs,
        ps,
        gs));

    std::vector<std::shared_ptr<Texture2D>> texs(2);
    UINT width = Define::Config::getInstance()->getWidth();
    UINT height = Define::Config::getInstance()->getHeight();
    D3D11_TEXTURE2D_DESC desc = RenderTargetViewDesc::getDefaultTexture2DDesc(width, height);
    D3D11_VIEWPORT vp{ 0,0,width,height,0.0f,1.0f };
    for (UINT n = 0; n < 2; n++) {
        texs[n] = std::make_shared<Texture2D>(&desc, nullptr);
    }
    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = RenderTargetViewDesc::getDefaultRenderTargetViewDesc();
    mRTV = std::make_unique<MRT>(texs, &rtvDesc, vp, Color4(0, 0, 0, 0));
    mBlendEffect = std::make_shared<Effect>(
        ShaderLoad::loadVS("NoDelete/Texture2D_VS"),
        ShaderLoad::loadPS("MRT/Blend_PS"));

    auto pos = PrimitiveVertex::quadPosition();
    auto uv = PrimitiveVertex::quadUV();
    std::vector<BaseVertex2D> vert(pos.size());
    for (int i = 0; i < vert.size(); i++) {
        vert[i] = { pos[i],uv[i] };
    }
    mVB = std::make_unique<VertexBuffer>(vert);
    auto id = PrimitiveVertex::quadIndex();
    mIB = std::make_unique<IndexBuffer>(id, PrimitiveTopology::TriangleList);
}

Firefly::~Firefly() { }

void Firefly::load(Scene::Collecter& collecter) {
    auto newBlendState = std::make_shared<Graphics::AlphaBlend>(
        Graphics::BlendStateDesc::BLEND_DESC(Graphics::AlphaBlendType::Add));

    //前の状態をコピーしておく
    //シーン終了時にもとに戻してあげる
    Graphics::IRenderer* backBufferRenderer = Utility::getRenderingManager()->getRenderer();
    backBufferRenderer->getPipeline()->setAlphaBlend(newBlendState);
}

void Firefly::update() {
    GPUParticleBase::update();
    mGPUParticle[0]->simulate();
    mGlobal.emit = -1;
}

void Firefly::draw(Framework::Graphics::IRenderer* renderer) {
    mRTV->clear();
    mRTV->set();

    GPUParticleBase::draw(renderer);
    Math::Matrix4x4 m = Math::Matrix4x4::identity();
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World3D, m);
    Utility::getConstantBufferManager()->setFloat(Graphics::ConstantBufferParameterType::UVLeft, 0.0f);
    Utility::getConstantBufferManager()->setFloat(Graphics::ConstantBufferParameterType::UVTop, 0.0f);
    Utility::getConstantBufferManager()->setFloat(Graphics::ConstantBufferParameterType::UVWidth, 1.0f);
    Utility::getConstantBufferManager()->setFloat(Graphics::ConstantBufferParameterType::UVHeight, 1.0f);
    Utility::getConstantBufferManager()->send();
    mGPUParticle[0]->draw();

    mRTV->end();

    renderer->begin();
    float width = Define::Config::getInstance()->getWidth();
    float height = Define::Config::getInstance()->getHeight();

    m = Math::Matrix4x4::createScale(Math::Vector3(width, height, 1.0f));
    Utility::getConstantBufferManager()->setMatrix(Graphics::ConstantBufferParameterType::World2D, m);
    mRTV->getTexture(0)->setData(ShaderInputType::Pixel, 0);
    mRTV->getTexture(1)->setData(ShaderInputType::Pixel, 1);
    mBlendEffect->set();
    DX11InterfaceAccessor::getContext()->GSSetShader(nullptr, nullptr, 0);
    mVB->setData();
    mIB->setData();
    mIB->drawCall();
}
