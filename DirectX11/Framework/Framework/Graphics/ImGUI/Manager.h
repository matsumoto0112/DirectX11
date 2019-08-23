#pragma once
#include <vector>
#include <memory>
#include <Windows.h>
#include "Framework/Utility/ImGUI/ImGUI.h"

namespace Framework {
namespace ImGUI {

/**
* @class Manager
* @brief ImGUIの管理
*/
class Manager {
public:
    /**
    * @brief コンストラクタ
    */
    Manager();
    /**
    * @brief デストラクタ
    */
    ~Manager();
    /**
    * @brief アイテムをすべて描画する
    */
    void drawAll();
};

} //ImGUI
} //Framework 
