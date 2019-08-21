#pragma once
#include <vector>
#include <memory>
#include <Windows.h>
#include "Framework/Utility/ImGUI/ImGUI.h"

namespace Framework {
namespace ImGUI {

class Window;

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
    void add(Window* window);
private:
    std::vector<std::unique_ptr<Window>> mWindows; //!< GUIウィンドウのリスト
};

} //ImGUI
} //Framework 
