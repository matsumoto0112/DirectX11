#pragma once
#include <vector>
#include <memory>
#include <Windows.h>
#include "Framework/Utility/ImGUI/ImGUI.h"

namespace Framework {
namespace ImGUI {

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
    * @brief �A�C�e�������ׂĕ`�悷��
    */
    void drawAll();
};

} //ImGUI
} //Framework 
