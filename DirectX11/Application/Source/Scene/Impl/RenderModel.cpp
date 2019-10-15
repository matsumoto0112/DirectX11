#include "RenderModel.h"
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Framework/Utility/IO/FBXLoader.h"
#include "Framework/Define/Path.h"
#include "Framework/Define/Config.h"
#include "Framework/Graphics/Model/Model.h"

using namespace Framework;

namespace {
Utility::Transform mTransform;
std::unique_ptr<Graphics::Model> mModel;

}
RenderModel::RenderModel() {
    //ÉJÉÅÉâÇÃèâä˙âª
    m3DCamera = std::make_shared<Graphics::PerspectiveCamera>(
        Math::ViewInfo{ Math::Vector3(0,0,-10),Math::Vector3(0,0,0),Math::Vector3::UP },
        Math::ProjectionInfo{ 45.0f,Define::Config::getInstance()->getSize(),0.1f,1000.0f });

    Utility::FBXLoader loader(Define::Path::getInstance()->fbxModel() + "049d62f6-093d-4a3c-940e-b2f4fad27d9d.fbx");
    //Utility::FBXLoader loader(::Define::Path::getInstance()->fbxModel() + "a2380cb0-6f46-41a7-8cde-3db2ec73e8ed.fbx");
    std::vector<Math::Vector4> pos = loader.getPosition();
    std::vector<UINT> indices(pos.size());
    for (int i = 0; i < indices.size() / 3; i++) {
        indices[i * 3 + 0] = i * 3 + 2;
        indices[i * 3 + 1] = i * 3 + 1;
        indices[i * 3 + 2] = i * 3 + 0;
    }
    auto vs = std::make_shared<Graphics::VertexShader>(Define::Path::getInstance()->shader() + "3D/Only_Position_VS.cso");
    auto ps = std::make_shared<Graphics::PixelShader>(Define::Path::getInstance()->shader() + "3D/Output_Color_PS.cso");

    mModel = std::make_unique<Graphics::Model>(std::make_shared<Graphics::VertexBuffer>(pos),
        std::make_shared<Graphics::IndexBuffer>(indices, Graphics::PrimitiveTopology::TriangleList),
        std::make_shared<Graphics::Effect>(vs, ps),
        std::make_shared<Graphics::ModelMaterial>());

    mTransform = Utility::Transform(Math::Vector3::ZERO, Math::Quaternion::IDENTITY, Math::Vector3(5.0f, 5.0f, 5.0f));
}

RenderModel::~RenderModel() { }

void RenderModel::load(Framework::Scene::Collecter& collecter) { }

void RenderModel::update() {
    mTransform.setRotate(mTransform.getRotate() * Math::Quaternion::createRotateAboutY(1.0f));

    auto mat = mModel->getMaterial<Graphics::ModelMaterial>();
    mat->mWorldMatrix.mData = mTransform.createSRTMatrix();
    mat->mColor.mData = Graphics::Color4(1.0f, 0.0f, 1.0f, 1.0f);
}

bool RenderModel::isEndScene() const {
    return false;
}

void RenderModel::draw(Framework::Graphics::IRenderer* renderer) {
    Utility::getCameraManager()->setPerspectiveCamera(m3DCamera);
    renderer->render(mModel.get());
}

void RenderModel::unload() { }

Define::SceneType RenderModel::next() {
    return Define::SceneType();
}
