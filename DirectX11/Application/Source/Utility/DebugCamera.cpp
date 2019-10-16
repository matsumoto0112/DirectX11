#include "DebugCamera.h"

#define ADD_FLOAT_FIELD(name,value,type,min,max) { \
    std::shared_ptr<FloatField> field = std::make_shared<FloatField>(#name, value, [&](float val) { \
        Vector3 pos = getPosition(); \
        float sub = pos.##type - val; \
        pos.##type = val; \
        setPosition(pos); \
        Vector3 look = getLookat(); \
        look.##type -= sub; \
        setLookat(look); \
        }); \
    field->setMinValue(min); \
    field->setMaxValue(max); \
    mCameraControl->addItem(field); \
}


using namespace Framework::Graphics;
using namespace Framework::Math;
using namespace Framework::ImGUI;

DebugCamera::DebugCamera(const ViewInfo& view, const ProjectionInfo& proj)
    :PerspectiveCamera(view, proj), mLength((view.eye - view.at).length()) {
    mCameraControl = std::make_unique<Framework::ImGUI::Window>("Camera_Controller");
    ADD_FLOAT_FIELD(X, view.eye.x, x, -30.0f, 30.0f);
    ADD_FLOAT_FIELD(Y, view.eye.y, y, -30.0f, 30.0f);
    ADD_FLOAT_FIELD(Z, view.eye.z, z, -30.0f, 30.0f);

    std::shared_ptr<FloatField> field = std::make_shared<FloatField>("L", mLength, [&](float val) {
        mLength = val;
        Vector3 dir = (getPosition() - getLookat()).getNormal();
        setPosition(getLookat() + dir * mLength);
    });

    field->setMinValue(0.01f);
    field->setMaxValue(100.0f);
    mCameraControl->addItem(field);
}

DebugCamera::~DebugCamera() { }

void DebugCamera::drawControlWindow() {
    mCameraControl->draw();
}
