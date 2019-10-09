#include "Camera.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

namespace Framework {
namespace Graphics {

Camera::Camera(const Math::Matrix4x4& view, const Math::Matrix4x4& proj)
    :mView(view), mProjection(proj) {}

Camera::~Camera() {}

void Camera::render() {
    ConstantBufferManager* cbManager = Utility::getConstantBufferManager();
    cbManager->setMatrix(ConstantBufferParameterType::View, mView);
    cbManager->setMatrix(ConstantBufferParameterType::Projection, mProjection);
}

Math::Vector3 Camera::screenToWorldPosition(const Math::Vector2& pos, float z, const Math::Vector2& screenSize) const {
    Math::Matrix4x4 invView = Math::Matrix4x4::inverse(mView);
    Math::Matrix4x4 invProj = Math::Matrix4x4::inverse(mProjection);
    Math::Matrix4x4 vp(
        screenSize.x / 2, 0, 0, 0,
        0, -screenSize.y / 2, 0, 0,
        0, 0, 1, 0,
        screenSize.x / 2, screenSize.y / 2, 0, 1);
    Math::Matrix4x4 invVP = Math::Matrix4x4::inverse(vp);
    Math::Matrix4x4 tmp = invVP * invProj * invView;
    return Math::Matrix4x4::multiplyCoord(Math::Vector3(pos.x, pos.y, z), tmp);
}

} //Graphics 
} //Framework 

