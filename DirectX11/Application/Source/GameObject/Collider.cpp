#include "Collider.h"
#include "Framework/Graphics/Renderer/3D/Cube.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

using namespace Framework;

Collider::Collider(const Utility::Transform& transform)
    :mTransform(transform) {
    mCollisionRendererInstance = std::make_unique<Graphics::Cube>();
}

Collider::~Collider() {}

Math::AABB3D Collider::getAABB() const {
    Math::Matrix4x4 mat = mTransform.createSRTMatrix();
    Math::AABB3D aabb;
    aabb.setToTransformedAABB(Math::AABB3D(Math::Vector3(-0.5f, -0.5f, -0.5f), Math::Vector3(0.5f, 0.5f, 0.5f)), mat);
    return aabb;
}

Framework::Math::OBB3D Collider::getOBB() const {
    const Math::Vector3 center = mTransform.getGlobalPostition();
    Math::Matrix4x4 mat = mTransform.getGlobalRotate().toMatrix();
    Math::Vector3 x = Math::Vector3::RIGHT * mat;
    Math::Vector3 y = Math::Vector3::UP * mat;
    Math::Vector3 z = Math::Vector3::FORWORD * mat;
    x.normalize(); y.normalize(); z.normalize();
    const std::array<Math::Vector3, 3> normals = {
        x,
        y,
        z
    };
    const Math::Vector3 size = mTransform.getGlobalScale() * 0.5f;
    Math::OBB3D obb(center, normals, size);
    return obb;
}

void Collider::render() {
    Graphics::Color4 color = Graphics::Color4(1.0f, 0.0f, 0.0f, 0.2f);
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
    Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Only_Position)->set();
    Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::OutPot_Color)->set();
    mCollisionRendererInstance->render(mTransform);
    color = Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f);
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
}
