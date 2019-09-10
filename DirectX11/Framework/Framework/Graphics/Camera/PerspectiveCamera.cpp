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
PerspectiveCamera::PerspectiveCamera(const Math::ViewInfo& view, const Math::ProjectionInfo& proj)
    :Camera(Math::Matrix4x4::createView(view),
        Math::Matrix4x4::createProjection(proj))
    , mViewInfo(view), mProjInfo(proj) {}

PerspectiveCamera::~PerspectiveCamera() {}

void PerspectiveCamera::setPosition(const Math::Vector3& position) {
    mViewInfo.eye = position;
    mView.setUpView(mViewInfo);
}

const Math::Vector3& PerspectiveCamera::getPosition() const {
    return mViewInfo.eye;
}

void PerspectiveCamera::setLookat(const Math::Vector3& lookat) {
    mViewInfo.at = lookat;
    mView.setUpView(mViewInfo);
}

const Math::Vector3& PerspectiveCamera::getLookat() const {
    return mViewInfo.at;
}

void PerspectiveCamera::setUpVector(const Math::Vector3& up) {
    mViewInfo.up = up;
    mView.setUpView(mViewInfo);
}

const Math::Vector3& PerspectiveCamera::getUpVector() const {
    return mViewInfo.up;
}

} //Graphics 
} //Framework 
