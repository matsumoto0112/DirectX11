#pragma once
#include "Graphics/RenderingManager.h"
#include "Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Input/InputManager.h"

namespace Framework {

/**
* @brief よく使われる機能を簡易的に使えるようにラップした関数
*/
namespace Utility {
/**
* @brief メインウィンドウのハンドルの取得
*/
HWND getMainHWND();

/**
* @brief ImGUIの管理者の取得
*/
ImGUI::Manager* getImGUIManager();

/**
* @brief 描画管理者の取得
*/
Graphics::RenderingManager* getRenderingManager();

/**
* @brief コンスタントバッファ管理者の取得
*/
Graphics::ConstantBufferManager* getConstantBufferManager();

Input::InputManager* getInputManager();

} //Utility 
} //Framework 
