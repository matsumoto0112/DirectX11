#include "Joystick.h"
#include "Input/ControllerUtil.h"

namespace {

/**
* @brief ���b�Z�[�W����W���C�X�e�B�b�N�����擾�o���Ă���������
*/
bool canGetJoyInfo(MMRESULT mmResult) {
    return (mmResult == JOYERR_NOERROR);
}

/**
* @brief �W���C�X�e�B�b�N��񂩂�{�^���������Ă���������
*/
bool checkButtonDown(const JOYINFOEX& info, Framework::Input::ButtonID button) {
    using  Framework::Input::ButtonID;
    //UINT�ɕϊ������͂𒲂ׂ�
    UINT btn = static_cast<UINT>(button);

    //Button::Up�ȍ~��1<<15���傫�����l�ɂȂ��Ă���
    if (btn > (1 << 15)) {
        int pov = info.dwPOV;
        //pov��65535�̎��͓��͂��Ȃ�
        if (pov == 65535) return false;
        switch (button) {
        case ButtonID::Up:
            return pov < 9000 || pov > 27000;
        case ButtonID::Right:
            return 0 < pov && pov < 18000;
        case ButtonID::Down:
            return 9000 < pov && pov < 27000;
        case ButtonID::Left:
            return 18000 < pov && pov < 36000;
        }
    }

    //�����Ă���{�^���Ƃ̘_���ςŔ���
    return (info.dwButtons & btn) != 0;
}

}
namespace Framework {
namespace Input {

Joystick::Joystick(ID id)
    :mID(static_cast<UINT>(id)) {
    mJoyInfo.dwSize = sizeof(JOYINFOEX);
    mJoyInfo.dwFlags = JOY_RETURNALL;
    joyGetPosEx(mID, &mJoyInfo);
}

Joystick::~Joystick() {}

void Joystick::update() {
    mPrevJoyInfo = mJoyInfo;
    MMRESULT result = joyGetPosEx(mID, &mJoyInfo);
    mCanGetJoyInfo = canGetJoyInfo(result);
}

bool Joystick::isEnabled() const {
    return mCanGetJoyInfo;
}

bool Joystick::getButton(ButtonID button) const {
    return mCanGetJoyInfo && checkButtonDown(mJoyInfo, button);
}

bool Joystick::getButtonDown(ButtonID button) const {
    //�Oupdate�Ń{�^���������Ă�����
    bool prev = checkButtonDown(mPrevJoyInfo, button);
    //��update�Ń{�^���������Ă�����
    bool cur = checkButtonDown(mJoyInfo, button);

    return mCanGetJoyInfo && !prev && cur;
}

bool Joystick::getButtonUp(ButtonID button) const {
    //�Oupdate�Ń{�^���������Ă�����
    bool prev = checkButtonDown(mPrevJoyInfo, button);
    //��update�Ń{�^���������Ă�����
    bool cur = checkButtonDown(mJoyInfo, button);

    return mCanGetJoyInfo && prev && !cur;
}

float Joystick::getAxis(AxisID axis) const {
    DWORD axisInput;
    switch (axis) {
    case Input::AxisID::LeftHorizontal:
        axisInput = mJoyInfo.dwXpos;
        break;
    case Input::AxisID::LeftVertical:
        axisInput = mJoyInfo.dwYpos;
        break;
    case Input::AxisID::RightHorizontal:
        axisInput = mJoyInfo.dwUpos;
        break;
    case Input::AxisID::RightVertical:
        axisInput = mJoyInfo.dwRpos;
        break;
    case Input::AxisID::Trigger:
        axisInput = mJoyInfo.dwZpos;
        break;
    default:
        break;
    }
    return (axisInput - ControllerUtil::HALF_AXIS_MAX_POSITION) / ControllerUtil::HALF_AXIS_MAX_POSITION;
}

} //Input
} //Framework
