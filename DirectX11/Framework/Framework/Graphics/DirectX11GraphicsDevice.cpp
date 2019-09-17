#include "DirectX11GraphicsDevice.h"
#include "Framework/Define/Render/MultiSampleQuarity.h"
#include "Framework/Graphics/Texture/TextureBuffer.h"
#include "Framework/Utility/Debug.h"
#include "Framework/Utility/ImGUI/ImGUI.h"

namespace {
static const int MAX_MULTISAMPLE_COUNT = 8;
} // 

namespace Framework {
namespace Graphics {

DirectX11GraphicsDevice::DirectX11GraphicsDevice(HWND hWnd, UINT screenWidth, UINT screenHeight, bool isFullScreen) {
    int debugFlag;
#if defined(DEBUG) || defined(_DEBUG)
    debugFlag = D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#else
    debugFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#endif

    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        debugFlag,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &mDevice,
        nullptr,
        &mImmediateContext);

    if (FAILED(hr)) {
        MY_ERROR_WINDOW(false, "Device�쐬���s");
        return;
    }

    DXGI_SAMPLE_DESC MSAA;
    //MAX_MULTISAMPLE_COUNT����2�̗ݏ悲�Ƃɉ������Ă����Ďg�p�ł���MSAA��T��
    for (int i = Define::MultiSampleQuarity::Count; i >= 0; i /= 2) {
        UINT quarity;
        if (SUCCEEDED(mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT, i, &quarity))) {
            MSAA.Count = i;
            MSAA.Quality = quarity - 1;
            break;
        }
    }

    //�C���^�[�t�F�[�X�擾
    Microsoft::WRL::ComPtr<IDXGIDevice1> dxgi;
    hr = mDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgi);
    if (FAILED(hr)) {
        MY_ERROR_WINDOW(false, "QueryInterface���s");
        return;
    }

    //�A�_�v�^�[�擾
    Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
    hr = dxgi->GetAdapter(&adapter);
    if (FAILED(hr)) {
        MY_ERROR_WINDOW(false, "GetAdapter���s");
        return;
    }

    Microsoft::WRL::ComPtr<IDXGIFactory> factory;
    hr = adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory);
    if (FAILED(hr) || !factory) {
        MY_ERROR_WINDOW(false, "GetParent���s");
        return;
    }

    //�X���b�v�`�F�C���쐬
    DXGI_MODE_DESC modeDesc;
    ZeroMemory(&modeDesc, sizeof(modeDesc));
    modeDesc.Width = screenWidth;
    modeDesc.Height = screenHeight;
    modeDesc.RefreshRate.Numerator = 0;
    modeDesc.RefreshRate.Denominator = 1;
    modeDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;

    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BufferCount = 2;
    desc.SampleDesc = MSAA;
    desc.BufferDesc = modeDesc;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
    desc.OutputWindow = hWnd;
    desc.Windowed = !isFullScreen;
    hr = factory->CreateSwapChain(
        mDevice.Get(),
        &desc,
        &mSwapChain);

    if (FAILED(hr)) {
        MY_ERROR_WINDOW(false, "CreateSwapChain���s");
        return;
    }

    Define::MultiSampleQuarity::getInstance().setMultiSample(MSAA.Count, MSAA.Quality);
    //mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(mDebug.GetAddressOf()));
}

DirectX11GraphicsDevice::~DirectX11GraphicsDevice() {
    //// �ڍו\��
    //mDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
}

void DirectX11GraphicsDevice::present(UINT syncInterval) {
    mSwapChain->Present(0, 0);
}

std::shared_ptr<TextureBuffer> DirectX11GraphicsDevice::getBackBuffer() {
    return std::make_shared<TextureBuffer>(*this);
}

} //Graphics 
} //Framework 