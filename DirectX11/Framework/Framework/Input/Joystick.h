#pragma once

#include "Framework/Input/ID.h"
#include "Framework/Input/ButtonID.h"
#pragma comment(lib,"WinMM.lib")
namespace Framework {
namespace Input {

class Joystick
{
public:
    /**
    * @brief �R���X�g���N�^
    * @param id �W���C�X�e�B�b�NID
    */
    Joystick(ID id = ID::Joystick1);
    /**
    * @brief �f�X�g���N�^
    */
    ~Joystick();
    /**
    * @brief �R���g���[�����X�V
    */
    void update();
    /**
    * @brief ���p�\��?
    */
    bool isEnabled() const;
    /**
    * @brief �{�^���������Ă��邩
    * @param button ���肷��{�^��
    * @return ��update�ŉ����Ă�����true
    ������Ă��Ȃ��A�R���g���[�������݂��Ȃ��ꍇ��false
    */
    bool getButton(ButtonID button) const;
    /**
    * @brief �{�^�������������i�g���K�[�j
    * @param button ���肷��{�^��
    * @return �Oupdate�ŉ�����Ă��Ȃ�����update�ŉ�����Ă�����true
    ����ȊO�̏ꍇ�A�R���g���[�������݂��Ȃ��ꍇ��false
    */
    bool getButtonDown(ButtonID button) const;
    /**
    * @brief �{�^���𗣂������i�g���K�[�j
    * @param button ���肷��{�^��
    * @return �Oupdate�ŉ�����Ă��Ă���update�ŗ����ꂽ��true
    ����ȊO�̏ꍇ�A�R���g���[�������݂��Ȃ��ꍇ��false
    */
    bool getButtonUp(ButtonID button) const;
    /**
    * @brief ���̓��͒l���擾
    * @axis ���肷�鎲
    * @details ���̓��͋���i�|�P�`�P�j�܂łŕԂ��B
    �g���K�[�̏ꍇ�@���g���K�[�F�O�`�P�A�E�g���K�[�O�`�|�P�̒l��Ԃ�
    */
    float getAxis(AxisID axis) const;
private:
    const UINT mID; //!< �W���C�X�e�B�b�NID
    bool mCanGetJoyInfo; //!< �W���C�X�e�B�b�N�����擾�ŗ��Ă�����
    JOYINFOEX mJoyInfo; //!< �W���C�X�e�B�b�N�����i�[����\����
    JOYINFOEX mPrevJoyInfo; //!< �Oupdate�ł̃{�^���̉������
};

} //Input 
} //Framework
