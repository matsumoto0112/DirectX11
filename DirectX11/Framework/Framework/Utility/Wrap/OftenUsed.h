#pragma once
#include "Framework/Graphics/RenderingManager.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Utility/Resource/ResourceManager.h"

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

/**
* @brief ライト管理者の取得
*/
Graphics::LightManager* getLightManager();

/**
* @brief 入力管理の取得
*/
Input::InputManager* getInputManager();

Utility::ResourceManager* getResourceManager();

} //Utility 
} //Framework 
