#include "OrthographicCamera.h"

namespace Framework {
namespace Graphics {
OrthographicCamera::OrthographicCamera(const Math::Vector2& size)
    :Camera(Math::Matrix4x4::createTranslate(Math::Vector3::ZERO),
        Math::Matrix4x4::createOrthographic(size)),
    mScreenSize(size),
    mPosition(Math::Vector3::ZERO) {}

OrthographicCamera::~OrthographicCamera() {}

void Framework::Graphics::OrthographicCamera::setPosition(const Math::Vector3& position) {
    mPosition = position;
    mView.setupTransform(-mPosition);
}

void OrthographicCamera::setScreenSize(const Math::Vector2& size) {
    mScreenSize = size;
    mProjection.setUpOrthographic(mScreenSize);
}

} //Graphics 
} //Framework 
