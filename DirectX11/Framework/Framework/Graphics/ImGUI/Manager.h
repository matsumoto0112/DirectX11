#pragma once
#include <vector>
#include <memory>
#include <Windows.h>
#include "Framework/Utility/ImGUI/ImGUI.h"

namespace Framework::ImGUI {

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
    * @brief フレーム開始時処理
    */
    void beginFrame();
    /**
    * @brief アイテムをすべて描画する
    */
    void endFrame();
};

} //Framework::ImGUI
