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
    std::shared_ptr<Graphics::ConstantBuffer> mWorldCB;
    std::shared_ptr<Graphics::ConstantBuffer> mColorCB;
}

TestScene::TestScene() {
    auto vertices = Graphics::PrimitiveVertex::quadPosition();
    auto indices = Graphics::PrimitiveVertex::quadIndex();
    mVB = Graphics::DX11RenderingManager::getInstance()->createVertexBuffer(vertices);
    mIB = Graphics::DX11RenderingManager::getInstance()->createIndexBuffer(indices, Graphics::PrimitiveTopology::TriangleList);
    mVS = Graphics::DX11RenderingManager::getInstance()->createVertexShader(Define::Path::getInstance()->shader() + "3D/Only_Position_VS");
    mPS = Graphics::DX11RenderingManager::getInstance()->createPixelShader(Define::Path::getInstance()->shader() + "3D/Output_Color_PS");
    mWorldCB = Graphics::DX11RenderingManager::getInstance()->createConstantBuffer<Graphics::MVPMatrix3DCBuffer>("MVP3D", Graphics::ShaderInputType::Vertex, 0);
    mColorCB = Graphics::DX11RenderingManager::getInstance()->createConstantBuffer<Graphics::ColorCBuffer>("Color", Graphics::ShaderInputType::Pixel, 3);
}

TestScene::~TestScene() { }

void TestScene::load(Scene::Collecter& collecter) { }

void TestScene::update() {
    Graphics::MVPMatrix3DCBuffer buffer;
    buffer.world = Math::Matrix4x4::createTranslate(Math::Vector3(0, 1, 0)).transpose();
    buffer.view = Math::Matrix4x4::createView({ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3(0,1,0) }).transpose();
    buffer.proj = Math::Matrix4x4::createProjection({ 45.0f,Define::Config::getInstance()->getSize(),0.1f,1000.0f }).transpose();
    Graphics::DX11RenderingManager::getInstance()->updateConstantBuffer(mWorldCB, (void*)&buffer);
    Graphics::ColorCBuffer color;
    color.color = Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f);
    Graphics::DX11RenderingManager::getInstance()->updateConstantBuffer(mColorCB, (void*)&color);
}

bool TestScene::isEndScene() const {
    return false;
}

void TestScene::draw(Graphics::IRenderer* renderer) {
    Graphics::DX11RenderingManager::getInstance()->setVertexBuffer(mVB);
    Graphics::DX11RenderingManager::getInstance()->setIndexBuffer(mIB);
    Graphics::DX11RenderingManager::getInstance()->setVertexShader(mVS);
    Graphics::DX11RenderingManager::getInstance()->setPixelShader(mPS);
    Graphics::DX11RenderingManager::getInstance()->setConstantBuffer("MVP3D", mWorldCB);
    Graphics::DX11RenderingManager::getInstance()->setConstantBuffer("Color", mColorCB);
    Graphics::DX11RenderingManager::getInstance()->draw();
}

void TestScene::unload() { }

Define::SceneType TestScene::next() {
    return Define::SceneType();
}
