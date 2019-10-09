#include "ZTexCreater.h"
#include "Framework/Graphics/Desc/RenderTargetViewDesc.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Graphics/Sprite/SpriteRenderer.h"

namespace Framework {
namespace Graphics {

ZTexCreater::ZTexCreater(UINT width, UINT height, std::shared_ptr<Effect> effect)
    :mEffect(effect) {
    std::shared_ptr<Graphics::TextureBuffer> texBuffer =
        std::make_shared<Graphics::TextureBuffer>(
            Graphics::RenderTargetViewDesc::getDefaultTexture2DDesc(width, height));
    mRenderTarget = std::make_unique<Graphics::RenderTarget>(texBuffer, Graphics::RenderTargetViewDesc::getDefaultRenderTargetViewDesc(),
        std::make_unique<Graphics::Viewport>(Math::Rect(0, 0, static_cast<float>(width), static_cast<float>(height))),
        Graphics::SRVFlag::Use);
    mRenderTarget->createDepthStencilView();
    mRenderTarget->setClearColor(Color4(0.0f, 0.0f, 0.0f, 1.0f));
}

ZTexCreater::~ZTexCreater() { }

void ZTexCreater::setViewMatrix(const Math::Matrix4x4& view) {
    Utility::getConstantBufferManager()->setMatrix(ConstantBufferParameterType::View, view);
}

void ZTexCreater::setProjectionMatrix(const Math::Matrix4x4& proj) {
    Utility::getConstantBufferManager()->setMatrix(ConstantBufferParameterType::Projection, proj);
}

void ZTexCreater::begin() {
    mRenderTarget->set();
    mRenderTarget->clear();
}

void ZTexCreater::end() {
    //mRenderTarget->reset();
}

void ZTexCreater::render(std::shared_ptr<Model> model, const Utility::Transform& tranform) {
    auto prevEffect = model->getEffect();

    model->setEffect(mEffect);

    model->draw(tranform);

    model->setEffect(prevEffect);
}

void Framework::Graphics::ZTexCreater::render(std::shared_ptr<Sprite2D> sprite) {
    sprite->draw();
}

void Framework::Graphics::ZTexCreater::render(std::shared_ptr<Sprite3D> sprite) {
    SpriteRenderer::getInstance().draw(sprite.get(), *mCurrentPerspectiveCamera);
}

std::shared_ptr<Texture> ZTexCreater::getRenderedTexture() const {
    return mRenderTarget->getRenderTargetTexture();
}


} //Graphics 
} //Framework 
