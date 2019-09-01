#pragma once
#include <Windows.h>
#include "Framework/Math/Vector2.h"

namespace Framework {
namespace Graphics {
class DirectX11GraphicsDevice;

/**
* @class GraphicsDevice
* @brief 描画機器
*/
class GraphicsDevice {
public:
    /**
    * @brief コンストラクタ
    * @param hWnd ウィンドウハンドル
    * @param screenSize スクリーンの大きさ
    * @param isFullScreen フルスクリーンかどうか
    */
    GraphicsDevice(HWND hWnd, const Math::Vector2& screenSize, bool isFullScreen);
    /**
    * @brief デストラクタ
    */
    ~GraphicsDevice();
    /**
    * @brief 描画処理開始
    */
    void drawBegin();
    /**
    * @brief 描画処理終了
    */
    void drawEnd();
    void cleanup();

    DirectX11GraphicsDevice* getDirectX11GraphicsDevice() const { return mDirectX11Device.get(); }
private:
    std::unique_ptr<DirectX11GraphicsDevice> mDirectX11Device; //!< DirectX11用グラフィックデバイス管理
};

} //Graphics
} //Framework 