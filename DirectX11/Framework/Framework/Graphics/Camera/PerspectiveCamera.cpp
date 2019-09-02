#include "PerspectiveCamera.h"
#include "Framework/Define/Window.h"

namespace {
Framework::Math::Vector3 getLine(const Framework::Math::Matrix4x4& mat, int line) {
    std::array<float, 3> v;
    for (int i = 0; i < 3; i++) {
        v[i] = mat.m[line][i];
    }
    return Framework::Math::Vector3(v[0], v[1], v[2]);
}
}

namespace Framework {
namespace Graphics {
PerspectiveCamera::PerspectiveCamera(const Info& info)
    :Camera(Math::Matrix4x4::createView(info.position, info.lookat, info.up),
        Math::Matrix4x4::createProjection(info.fov, info.screen.x, info.screen.y, info.near, info.far))
    , mInfo(info) {}

PerspectiveCamera::~PerspectiveCamera() {}

void PerspectiveCamera::setPosition(const Math::Vector3& position) {
    mInfo.position = position;
    mView.setUpView(mInfo.position, mInfo.lookat, mInfo.up);
}

const Math::Vector3& PerspectiveCamera::getPosition() const {
    return mInfo.position;
}

void PerspectiveCamera::setLookat(const Math::Vector3& lookat) {
    mInfo.lookat = lookat;
    mView.setUpView(mInfo.position, mInfo.lookat, mInfo.up);
}

const Math::Vector3& PerspectiveCamera::getLookat() const {
    return mInfo.lookat;
}

void PerspectiveCamera::setUpVector(const Math::Vector3& up) {
    mInfo.up = up;
    mView.setUpView(mInfo.position, mInfo.lookat, mInfo.up);
}

const Math::Vector3& PerspectiveCamera::getUpVector() const {
    return mInfo.up;
}

Math::Vector3 PerspectiveCamera::screenToWorldPosition(const Math::Vector2 & pos, float z) const {
    return screenToWorldPosition(pos, z, Define::Window::getSize());
}

Math::Vector3 PerspectiveCamera::screenToWorldPosition(const Math::Vector2& pos, float z, const Math::Vector2& screenSize) const {
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
