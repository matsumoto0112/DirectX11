#pragma once
#include <Windows.h>
#include "Framework/Math/Vector2.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"

namespace Framework {
namespace Graphics {
/**
* @class GraphicsDevice
* @brief 描画機器
*/
class GraphicsDevice {
public:
    /**
    * @brief コンストラクタ
    * @param hWnd ウィンドウハンドル
    * @param width ウィンドウ幅
    * @param height ウィンドウ高さ
    * @param isFullScreen フルスクリーンかどうか
    */
    GraphicsDevice(HWND hWnd, UINT width, UINT height, bool isFullScreen);
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