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

void Collider::render() {
    Graphics::Color4 color = Graphics::Color4(1.0f, 0.0f, 0.0f, 0.2f);
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
    Utility::ResourceManager::getInstance().getVertexShader()->getResource(Define::VertexShaderType::Only_Position)->set();
    Utility::ResourceManager::getInstance().getPixelShader()->getResource(Define::PixelShaderType::OutPot_Color)->set();
    mCollisionRendererInstance->render(mTransform);
    color = Graphics::Color4(1.0f, 1.0f, 1.0f, 1.0f);
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, color);
}
