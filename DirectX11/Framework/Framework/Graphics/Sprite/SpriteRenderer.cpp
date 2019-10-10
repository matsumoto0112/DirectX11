#include "SpriteRenderer.h"
#include <vector>
#include <d3d11.h>
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Framework/Graphics/RenderingManager.h"
#include "Framework/Graphics/Shader/Effect.h"
#include "Framework/Graphics/Shader/ShaderInputType.h"
#include "Framework/Graphics/Sprite/Sprite2D.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Texture/Sampler.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Graphics/Renderer/PrimitiveVertex.h"

namespace {
Microsoft::WRL::ComPtr<ID3D11RasterizerState> ras;
}

namespace Framework {
namespace Graphics {

SpriteRenderer::SpriteRenderer() {
    std::vector<BaseVertex2D> vertices(4);
    auto positions = PrimitiveVertex::quadPosition();
    auto uvs = PrimitiveVertex::quadUV();
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i].pos = positions[i];
        vertices[i].uv = uvs[i];
    }
    mVIBuffer = std::make_unique<VertexAndIndexBuffer>(vertices, PrimitiveVertex::quadIndex(), PrimitiveVertex::QuadPrimitiveTopology);
    mEffect = std::make_shared<Effect>(
        Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Texture2D),
        Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::Texture2D));
    mSampler = std::make_unique<Sampler>(TextureAddressMode::Wrap,
        TextureFilterMode::MinMagMipLinear);

    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
    rasterizerDesc.DepthClipEnable = FALSE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    Utility::getDevice()->CreateRasterizerState(&rasterizerDesc, &ras);
    Utility::getContext()->RSSetState(ras.Get());
}

SpriteRenderer::~SpriteRenderer() { }

void SpriteRenderer::draw(Sprite2D* sprite) {
    draw(sprite, mEffect);
}

void SpriteRenderer::draw(Sprite2D* sprite, std::shared_ptr<Effect> effect) {
    //コンスタントバッファの取得
    ConstantBufferManager* cmanager = Utility::getConstantBufferManager();

    //エフェクト
    effect->set();

    //テクスチャデータ
    sprite->getTexture()->setData(ShaderInputType::Pixel, 0);
    mSampler->setData(ShaderInputType::Pixel, 0);

    //モデル・プロジェクション行列の設定
    cmanager->setMatrix(ConstantBufferParameterType::World, sprite->getModelMatrix());

    //UV情報の設定
    cmanager->setRect(ConstantBufferParameterType::UV, sprite->getSrcRect());

    //色の設定
    cmanager->setColor(ConstantBufferParameterType::Color, sprite->getColor());

    cmanager->send();
    //描画
    mVIBuffer->render();
}

void SpriteRenderer::draw(Sprite3D* sprite, const PerspectiveCamera* camera) {
    Utility::getContext()->RSSetState(ras.Get());
    //コンスタントバッファの取得
    ConstantBufferManager* cmanager = Utility::getConstantBufferManager();

    //エフェクト
    mEffect->set();

    //テクスチャデータ
    sprite->getTexture()->setData(ShaderInputType::Pixel, 0);
    mSampler->setData(ShaderInputType::Pixel, 0);

    auto bill = [](const Math::Vector3& billPos, const Math::Vector3& targetPos, const Math::Vector3& up) {
        Math::Matrix4x4 mat = Math::Matrix4x4::createView({ targetPos,billPos,up });
        mat = Math::Matrix4x4::inverse(mat);
        mat.m[3][0] = 0;
        mat.m[3][1] = 0;
        mat.m[3][2] = 0;
        return mat;
    };

    Math::Matrix4x4 billboardRotation = bill(
        sprite->getPosition(),
        camera->getPosition(),
        camera->getUpVector());
    Math::Matrix4x4 world = billboardRotation;
    world.m[3][0] = sprite->getPosition().x;
    world.m[3][1] = sprite->getPosition().y;
    world.m[3][2] = sprite->getPosition().z;
    cmanager->setMatrix(ConstantBufferParameterType::World, world);

    //UV情報の設定
    cmanager->setRect(ConstantBufferParameterType::UV, sprite->getSrcRect());

    //色の設定
    cmanager->setColor(ConstantBufferParameterType::Color, sprite->getColor());

    cmanager->send();
    //描画
    mVIBuffer->render();
}

} //Graphics 
} //Framework 
