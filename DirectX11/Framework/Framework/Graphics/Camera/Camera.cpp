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

} //Graphics 
} //Framework 

