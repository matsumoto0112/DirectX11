#include "DirectX11GraphicsDevice.h"
#include "Graphics/Texture/TextureBuffer.h"
#include "Utility/Debug.h"
#include "Utility/ImGUI/ImGUI.h"

namespace Framework {
namespace Graphics {

DirectX11GraphicsDevice::DirectX11GraphicsDevice(HWND hWnd, const int screenWidth, const int screenHeight, bool isFullScreen) {
    //スワップチェイン作成
    DXGI_MODE_DESC modeDesc;
    ZeroMemory(&modeDesc, sizeof(modeDesc));
    modeDesc.Width = static_cast<int>(screenWidth);
    modeDesc.Height = static_cast<int>(screenHeight);
    modeDesc.RefreshRate.Numerator = 60;
    modeDesc.RefreshRate.Denominator = 1;
    modeDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    modeDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    modeDesc.Scaling = DXGI_MODE_SCALING_CENTERED;

    DXGI_SAMPLE_DESC sampleDesc;
    ZeroMemory(&sampleDesc, sizeof(sampleDesc));
    sampleDesc.Quality = 0;
    sampleDesc.Count = 1;

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferDesc = modeDesc;
    swapChainDesc.SampleDesc = sampleDesc;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = !isFullScreen;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;
    int debugFlag;
#if defined(DEBUG) || defined(_DEBUG)
    debugFlag = D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#else
    debugFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#endif

    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        debugFlag,
        &level, 1, D3D11_SDK_VERSION, &swapChainDesc,
        &mSwapChain, &mDevice, nullptr, &mImmediateContext);

    if (FAILED(hr)) {
        MY_ASSERTION(SUCCEEDED(hr), "SwapChain作成失敗");
        return;
    }

    mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(mDebug.GetAddressOf()));
}

DirectX11GraphicsDevice::~DirectX11GraphicsDevice() {
    // 詳細表示
    //mDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
}

void DirectX11GraphicsDevice::present(UINT syncInterval) {
    mSwapChain->Present(syncInterval, 0);
}

std::shared_ptr<TextureBuffer> DirectX11GraphicsDevice::getBackBuffer() {
    return std::make_shared<TextureBuffer>(*this);
}

} //Graphics 
} //Framework 