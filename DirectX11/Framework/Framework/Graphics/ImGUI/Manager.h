#pragma once
#include <vector>
#include <memory>
#include <Windows.h>
#include "Framework/Utility/ImGUI/ImGUI.h"

namespace Framework::ImGUI {

/**
* @class Manager
* @brief ImGUI�̊Ǘ�
*/
class Manager {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Manager();
    /**
    * @brief �f�X�g���N�^
    */
    ~Manager();
    /**
    * @brief �t���[���J�n������
    */
    void beginFrame();
    /**
    * @brief �A�C�e�������ׂĕ`�悷��
    */
    void endFrame();
};

} //Framework::ImGUI
