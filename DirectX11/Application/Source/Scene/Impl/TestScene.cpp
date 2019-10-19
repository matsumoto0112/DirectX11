#include "TestScene.h"
#include "Framework/Graphics/DX11RenderingManager.h"
#include "Framework/Graphics/Renderer/PrimitiveVertex.h"
#include "Framework/Define/Path.h"

using namespace Framework;
namespace {
    std::shared_ptr<Graphics::VertexBuffer> mVB;
    std::shared_ptr<Graphics::IndexBuffer> mIB;
    std::shared_ptr<Graphics::VertexShader> mVS;
    std::shared_ptr<Graphics::PixelShader> mPS;
}

TestScene::TestScene() {
    auto vertices = Graphics::PrimitiveVertex::quadPosition();
    auto indices = Graphics::PrimitiveVertex::quadIndex();
    mVB = Graphics::DX11RenderingManager::getInstance()->createVertexBuffer(vertices);
    mIB = Graphics::DX11RenderingManager::getInstance()->createIndexBuffer(indices, Graphics::PrimitiveTopology::TriangleList);
    mVS = Graphics::DX11RenderingManager::getInstance()->createVertexShader(Define::Path::getInstance()->shader() + "VertexShader");
    mPS = Graphics::DX11RenderingManager::getInstance()->createPixelShader(Define::Path::getInstance()->shader() + "PixelShader");
}

TestScene::~TestScene() { }

void TestScene::load(Scene::Collecter& collecter) { }

void TestScene::update() { }

bool TestScene::isEndScene() const {
    return false;
}

void TestScene::draw(Graphics::IRenderer* renderer) {
    Graphics::DX11RenderingManager::getInstance()->setVertexBuffer(mVB);
    Graphics::DX11RenderingManager::getInstance()->setIndexBuffer(mIB);
    Graphics::DX11RenderingManager::getInstance()->setVertexShader(mVS);
    Graphics::DX11RenderingManager::getInstance()->setPixelShader(mPS);
    Graphics::DX11RenderingManager::getInstance()->draw();
}

void TestScene::unload() { }

Define::SceneType TestScene::next() {
    return Define::SceneType();
}
