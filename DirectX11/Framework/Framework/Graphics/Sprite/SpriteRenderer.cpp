#include "SpriteRenderer.h"
#include <vector>
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Framework/Graphics/RenderingManager.h"
#include "Framework/Graphics/Renderer/2D/QuadInstance.h"
#include "Framework/Graphics/Shader/ShaderInputType.h"
#include "Framework/Graphics/Sprite/Sprite2D.h"
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Graphics/Texture/Sampler.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Graphics/Vertex/Vertex.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

namespace Framework {
namespace Graphics {

SpriteRenderer::SpriteRenderer() {
    mVIBuffer = std::make_unique<QuadInstance>();
    mVertexShader = std::make_unique<VertexShader>("Texture2DVS");
    mPixelShader = std::make_unique<PixelShader>("Texture2DPS");
    mSampler = std::make_unique<Sampler>(TextureAddressMode::Wrap,
        TextureFilterMode::MinMagMipLinear);
}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::draw(Sprite2D* sprite) {
    //IRenderModeChanger* renderModeChanger = Utility::getRenderingManager()->getRenderModeChanger();

    ////前回の描画設定を一時的に保存
    //CullMode preCullMode = renderModeChanger->getCullMode();
    //FillMode preFillMode = renderModeChanger->getFillMode();

    ////描画設定
    //renderModeChanger->setRenderMode(CullMode::Back, FillMode::Solid);

    //コンスタントバッファの取得
    ConstantBufferManager* cmanager = Utility::getConstantBufferManager();

    //頂点・ピクセルシェーダ
    mVertexShader->set();
    mPixelShader->set();

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

    //前の描画設定に戻す
    //renderModeChanger->setRenderMode(preCullMode, preFillMode);
}

void SpriteRenderer::draw(Sprite3D* sprite) {
    //IRenderModeChanger* renderModeChanger = Utility::getRenderingManager()->getRenderModeChanger();

    ////前回の描画設定を一時的に保存
    //CullMode preCullMode = renderModeChanger->getCullMode();
    //FillMode preFillMode = renderModeChanger->getFillMode();

    ////描画設定
    //renderModeChanger->setRenderMode(CullMode::None, FillMode::Solid);

    //コンスタントバッファの取得
    ConstantBufferManager* cmanager = Utility::getConstantBufferManager();

    //頂点・ピクセルシェーダ
    mVertexShader->set();
    mPixelShader->set();

    //テクスチャデータ
    sprite->getTexture()->setData(ShaderInputType::Pixel, 0);
    mSampler->setData(ShaderInputType::Pixel, 0);

    //PerspectiveCamera& currentCamera = Utility::getCameraManager()->getCurrentCamera<PerspectiveCamera>();

    //auto gtBillBoardMatrix = [](PerspectiveCamera& camera) {
    //    Math::Matrix4x4 mat = camera.getView();
    //    mat = Math::Matrix4x4::inverse(mat);
    //    mat.m[3][0] = 0.0f;
    //    mat.m[3][1] = 0.0f;
    //    mat.m[3][2] = 0.0f;
    //    return mat;
    //};

    //Math::Matrix4x4 mat = gtBillBoardMatrix(currentCamera);
    //cmanager->setMatrix(ConstantBufferParameterType::World, sprite->createBillboardMatrix(mat));

    //UV情報の設定
    cmanager->setRect(ConstantBufferParameterType::UV, sprite->getSrcRect());

    //色の設定
    cmanager->setColor(ConstantBufferParameterType::Color, sprite->getColor());

    cmanager->send();
    //描画
    mVIBuffer->render();

    ////前の描画設定に戻す
    //renderModeChanger->setRenderMode(preCullMode, preFillMode);
}
} //Graphics 
} //Framework 
