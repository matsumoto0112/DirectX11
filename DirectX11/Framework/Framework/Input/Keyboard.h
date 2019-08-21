#pragma once

#include <array>
#include <wrl/client.h>
#include <Windows.h>
#include "Framework/Input/KeyCode.h"

namespace Framework {
namespace Input {

/**
* @class Keyboard
* @brief �L�[�{�[�h���͊Ǘ��N���X
*/
class Keyboard {
public:
    /**
    * @brief �R���X�g���N�^
    * @param hWnd �E�B���h�E�n���h��
    */
    Keyboard(HWND hWnd);
    /**
    * @brief �f�X�g���N�^
    */
    ~Keyboard();
    /**
    * @brief �X�V
    */
    void update();
    /**
    * @brief �L�[�������Ă��邩
    * @param key ���肷��L�[
    * @return ��update�ŉ����Ă�����true
    ������Ă��Ȃ��A�R���g���[�������݂��Ȃ��ꍇ��false
    */
    bool getKey(KeyCode key) const;
    /**
    * @brief �L�[�����������i�g���K�[�j
    * @param key ���肷��L�[
    * @return �Oupdate�ŉ�����Ă��Ȃ�����update�ŉ�����Ă�����true
    ����ȊO�̏ꍇ��false
    */
    bool getKeyDown(KeyCode key) const;
    /**
    * @brief �L�[�𗣂������i�g���K�[�j
    * @param key ���肷��L�[
    * @return �Oupdate�ŉ�����Ă��Ă���update�ŗ����ꂽ��true
    ����ȊO�̏ꍇ��false
    */
    bool getKeyUp(KeyCode key) const;
private:
    static const int KEY_MAX = 256; //!< �L�[�ő吔
    using KeyInfo = std::array<BYTE, KEY_MAX>;
    HRESULT mResult; //!<  �L�[���擾���̃��b�Z�[�W
    KeyInfo mCurrentKeys; //!< ��update�Ŏ擾�����L�[���
    KeyInfo mPrevKeys; //!< �Oupdate�Ŏ擾�����L�[���
private:
    /**
    * @brief �L�[�������Ă��邩
    * @param keys ����Ɏg���L�[�z��
    * @param key ���肷��L�[
    */
    bool checkKeyDown(const KeyInfo& keys, KeyCode key) const;
};

} //Input 
} //Framework
