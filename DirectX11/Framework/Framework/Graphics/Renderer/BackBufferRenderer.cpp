//#include "BackBufferRenderer.h"
//#include "Framework/Utility/Wrap/OftenUsed.h"
//#include "Framework/Graphics/Render/RenderTarget.h"
//#include "Framework/Graphics/Desc/DepthStencilDesc.h"
//#include "Framework/Graphics/Sprite/SpriteRenderer.h"
//#include "Framework/Define/Config.h"
//
//namespace Framework {
//namespace Graphics {
//
//BackBufferRenderer::BackBufferRenderer() {
//    mRenderTarget = std::make_unique<RenderTarget>(
//        Utility::getRenderingManager()->getGraphicsDevice()->getDirectX11GraphicsDevice()->getBackBuffer(),
//        std::make_unique<Viewport>(Math::Rect(0.0f, 0.0f,
//            static_cast<float>(Define::Config::getInstance()->getWidth()), static_cast<float>(Define::Config::getInstance()->getHeight()))),
//        SRVFlag::NoUse);
//    mRenderTarget->createDepthStencilView(
//        Graphics::DepthStencilDesc::getMSAATexture2DDesc(
//            Define::Config::getInstance()->getWidth(),
//            Define::Config::getInstance()->getHeight()),
//        DepthStencilDesc::getMSAADepthStencilViewDesc());
//}
//
//BackBufferRenderer::~BackBufferRenderer() { }
//
//void BackBufferRenderer::render(std::shared_ptr<Sprite2D> sprite) {
//    SpriteRenderer::getInstance()->draw(sprite.get());
//}
//
//void BackBufferRenderer::render(std::shared_ptr<Sprite3D> sprite) {
//    SpriteRenderer::getInstance()->draw(sprite.get(), Utility::getCameraManager()->getPerspectiveCamera().get());
//}
//
//void BackBufferRenderer::render(std::shared_ptr<Model> model, const Utility::Transform& transform) {
//    model->draw(transform);
//}
//
//void BackBufferRenderer::begin() {
//    mRenderTarget->setClearColor(mBackColor);
//    mRenderTarget->set();
//    mRenderTarget->clear();
//}
//
//void BackBufferRenderer::end() { }
//
//std::shared_ptr<Texture> BackBufferRenderer::getRenderedTexture() const {
//    MY_ASSERTION(false, "BackBufferRendererクラスのgetRenderedTextureを呼ばないでください。バックバッファはテクスチャを生成できません。");
//    throw std::exception("don't call");
//}
//
//} //Graphics 
//} //Framework 
