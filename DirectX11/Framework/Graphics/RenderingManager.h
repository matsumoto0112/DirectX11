#pragma once
#include <memory>
#include "Math/Vector2.h"
#include "Graphics/GraphicsDevice.h"
#include "Graphics/ConstantBuffer/ConstantBufferManager.h"

namespace Framework {
namespace ImGUI {
class Manager;
} //ImGUI 
namespace Graphics {
/**
* @class RenderingManager
* @brief 描画管理
*/
class RenderingManager {
public:
    /**
    * @brief コンストラクタ
    * @param hWnd ウィンドウハンドル
    * @param screenSize スクリーンの大きさ
    * @param isFullScreen フルスクリーン機動か
    */
    RenderingManager(HWND hWnd, const Math::Vector2& screenSize, bool isFullScreen);
    /**
    * @brief デストラクタ
    */
    ~RenderingManager();
    /**
    * @brief 初期化処理
    * @details デバイスを作った後に初期化処理をしないといけないので別で呼ぶ
    */
    void initialize();
    void drawBegin();
    void drawEnd();
    GraphicsDevice* getGraphicsDevice() const { return mGraphicsDevice.get(); }
    ConstantBufferManager* getConstantBufferManager() const { return mConstantBufferManager.get(); }
    ImGUI::Manager* getImGUIManager() const { return mImGUIManager.get(); }
private:
    Math::Vector2 mScreenSize;
    std::unique_ptr<GraphicsDevice> mGraphicsDevice; //!< グラフィックデバイス
    std::unique_ptr<ConstantBufferManager> mConstantBufferManager; //!< コンスタントバッファ管理
    std::unique_ptr<ImGUI::Manager> mImGUIManager; //!< ImGUIの管理
};

} //Graphics 
} //Framework 