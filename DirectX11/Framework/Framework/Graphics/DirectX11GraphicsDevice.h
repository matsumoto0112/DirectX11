#pragma once
#include <wrl/client.h>
#include <memory>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dCompiler.lib")
#include <initguid.h>
#include <dxgidebug.h>
#include <d3d11.h>

namespace Framework {
namespace Graphics {

class TextureBuffer;

/**
* @class DirectX11GraphicsDevice
* @brief DirectX11用グラフィックデバイス
*/
class DirectX11GraphicsDevice {
public:
    /**
    * @brief コンストラクタ
    * @param hWnd ウィンドウハンドル
    */
    DirectX11GraphicsDevice(HWND hWnd, UINT screenWidth, UINT screenHeight, bool isFullScreen);
    /**
    * @brief デストラクタ
    */
    ~DirectX11GraphicsDevice();
    /**
    * @brief デバイスの取得
    */
    Microsoft::WRL::ComPtr<ID3D11Device> getDevice() const { return mDevice; }
    /**
    * @brief デバイスコンテキストの取得
    */
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> getContext() const { return mImmediateContext; }
    /**
    * @brief 描画バッファの切り替え
    */
    void present(UINT syncInterval = 1);
    /**
    * @brief バックバッファの取得
    */
    std::shared_ptr<TextureBuffer> getBackBuffer();
    /**
    * @brief スワップチェインの取得
    */
    Microsoft::WRL::ComPtr<IDXGISwapChain> getSwapChain() const { return mSwapChain; }
private:
    Microsoft::WRL::ComPtr<ID3D11Device> mDevice; //!< デバイス
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> mImmediateContext; //!< デバイスコンテキスト 
    Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain; //!< スワップチェイン
    Microsoft::WRL::ComPtr<ID3D11Debug> mDebug; //!< デバッグ
};

} //Graphics 
} //Framework 