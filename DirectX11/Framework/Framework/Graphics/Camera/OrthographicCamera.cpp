#include "OrthographicCamera.h"
// #include "Framework/Utility/Wrap/OftenUsed.h"

namespace Framework {
namespace Graphics {
OrthographicCamera::OrthographicCamera(const Math::Vector2& size)
    :Camera(Math::Matrix4x4::createTranslate(Math::Vector3::ZERO),
        Math::Matrix4x4::createOrthographic(size)),
    mScreenSize(size),
    mPosition(Math::Vector3::ZERO) {}

OrthographicCamera::~OrthographicCamera() {}

void OrthographicCamera::render() {
    ConstantBufferManager* cbManager = Utility::getConstantBufferManager();
    cbManager->setMatrix(ConstantBufferParameterType::View2D, mView);
    cbManager->setMatrix(ConstantBufferParameterType::Projection2D, mProjection);
}

void OrthographicCamera::setPosition(const Math::Vector3& position) {
    mPosition = position;
    mView.setupTransform(-mPosition);
}

void OrthographicCamera::setScreenSize(const Math::Vector2& size) {
    mScreenSize = size;
    mProjection.setUpOrthographic(mScreenSize);
}

} //Graphics 
} //Framework 
