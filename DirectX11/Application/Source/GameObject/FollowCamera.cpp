#include "FollowCamera.h"
#include "Framework/Define/Window.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

using namespace Framework;

namespace {
Math::Matrix4x4 createViewIgnoreWorldOffset(const Math::ViewInfo& view) {
    return Math::Matrix4x4(
        view.eye.x, view.eye.y, view.eye.z, 1.0f,
        view.up.x, view.up.y, view.up.z, 0.0f,
        view.at.x, view.at.y, view.at.z, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    );
}
}

FollowCamera::FollowCamera(const Framework::Math::ViewInfo& viewInfo,
    const Framework::Math::ProjectionInfo& projInfo,
    Framework::Utility::Transform* targetTransform)
    :Camera(Math::Matrix4x4::createView(viewInfo),
        Math::Matrix4x4::createProjection(projInfo)),
    mCameraTransform(Utility::Transform()) {
    mLocalMatrix = createViewIgnoreWorldOffset(viewInfo);
    mCameraTransform.setParent(targetTransform);
}

FollowCamera::~FollowCamera() {}

void FollowCamera::render() {
    Graphics::ConstantBufferManager* cbManager = Utility::getConstantBufferManager();
    Math::Matrix4x4 camera = mLocalMatrix * Math::Matrix4x4::createTranslate(mCameraTransform.getGlobalPostition());
    Math::ViewInfo v{
        Math::Vector3(camera.m[0][0], camera.m[0][1], camera.m[0][2]),
        Math::Vector3(camera.m[2][0], camera.m[2][1], camera.m[2][2]),
        Math::Vector3(camera.m[1][0], camera.m[1][1], camera.m[1][2])
    };
    mView = Math::Matrix4x4::createView(v);
    cbManager->setMatrix(Graphics::ConstantBufferParameterType::View, mView);
    cbManager->setMatrix(Graphics::ConstantBufferParameterType::Projection, mProjection);
}
