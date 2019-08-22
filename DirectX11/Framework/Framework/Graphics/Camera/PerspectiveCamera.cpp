#include "PerspectiveCamera.h"

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

const Math::Vector3& PerspectiveCamera::getPosision() const {
    return mInfo.position;
}

void PerspectiveCamera::setLookat(const Math::Vector3& lookat) {
    mInfo.lookat = lookat;
    mView.setUpView(mInfo.position, mInfo.lookat, mInfo.up);
}

const Math::Vector3& PerspectiveCamera::setLookat() const {
    return mInfo.lookat;
}

void PerspectiveCamera::setUpVector(const Math::Vector3& up) {
    mInfo.up = up;
    mView.setUpView(mInfo.position, mInfo.lookat, mInfo.up);
}

const Math::Vector3& PerspectiveCamera::getUpVector() const {
    return mInfo.up;
}

} //Graphics 
} //Framework 
