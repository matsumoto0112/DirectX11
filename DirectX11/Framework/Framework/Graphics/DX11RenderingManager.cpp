#include "DX11RenderingManager.h"
#include "Framework/Define/StaticConfig.h"
#include "Framework/Graphics/Desc/RenderTargetViewDesc.h"

namespace Framework {
    namespace Graphics {
        DX11RenderingManager::DX11RenderingManager() { }

        DX11RenderingManager::~DX11RenderingManager() { }

        bool DX11RenderingManager::init(HWND hWnd, UINT width, UINT height, UINT frameCount, bool isFullScreen) {
            //デバッグフラグを立てる
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
                MY_ERROR_WINDOW(false, "Device作成失敗");
                return false;
            }

            DXGI_SAMPLE_DESC MSAA;
            //MAX_MULTISAMPLE_COUNTから2の累乗ごとに下がっていって使用できるMSAAを探す
            for (int i = Define::StaticConfig::MSAA_COUNT; i >= 0; i /= 2) {
                UINT quarity;
                if (SUCCEEDED(mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT, i, &quarity))) {
                    MSAA.Count = i;
                    MSAA.Quality = quarity - 1;
                    break;
                }
            }

            //インターフェース取得
            Microsoft::WRL::ComPtr<IDXGIDevice1> dxgi;
            hr = mDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgi);
            if (FAILED(hr)) {
                MY_ERROR_WINDOW(false, "QueryInterface失敗");
                return false;
            }

            //アダプター取得
            Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
            hr = dxgi->GetAdapter(&adapter);
            if (FAILED(hr)) {
                MY_ERROR_WINDOW(false, "GetAdapter失敗");
                return false;
            }

            Microsoft::WRL::ComPtr<IDXGIFactory> factory;
            hr = adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory);
            if (FAILED(hr) || !factory) {
                MY_ERROR_WINDOW(false, "GetParent失敗");
                return false;
            }

            //スワップチェイン作成
            DXGI_MODE_DESC modeDesc;
            ZeroMemory(&modeDesc, sizeof(modeDesc));
            modeDesc.Width = width;
            modeDesc.Height = height;
            modeDesc.RefreshRate.Numerator = 0;
            modeDesc.RefreshRate.Denominator = 1;
            modeDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;

            DXGI_SWAP_CHAIN_DESC desc;
            ZeroMemory(&desc, sizeof(desc));
            desc.BufferCount = frameCount;
            desc.SampleDesc = MSAA;
            desc.BufferDesc = modeDesc;
            desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
            desc.OutputWindow = hWnd;
            desc.Windowed = !isFullScreen;
            desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
            hr = factory->CreateSwapChain(
                mDevice.Get(),
                &desc,
                &mSwapChain);

            if (FAILED(hr)) {
                MY_ERROR_WINDOW(false, "CreateSwapChain失敗");
                return false;
            }

            mFrameCount = frameCount;

            ComPtr<ID3D11Texture2D> texture;
            throwIfFailed(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&texture));
            std::shared_ptr<Texture2D> texture2D = std::make_shared<Texture2D>(texture);
            Viewport viewport(Math::Rect(0, 0, width, height));
            mBackBuffer = std::make_shared<RenderTargetView>(mDevice.Get(), texture2D,
                nullptr, viewport, Color4(1.0f, 0.0f, 1.0f, 1.0f));
            return true;
        }

        void DX11RenderingManager::setVertexBuffer(VertexbufferPtr vertexBuffer) {
            mVertexBuffer = vertexBuffer;
        }

        void DX11RenderingManager::setIndexBuffer(IndexBufferPtr indexBuffer) {
            mIndexBuffer = indexBuffer;
        }

        void DX11RenderingManager::setVertexShader(VertexShaderPtr vertexShader) {
            mVertexShader = vertexShader;
        }

        void DX11RenderingManager::setPixelShader(PixelShaderPtr pixelShader) {
            mPixelShader = pixelShader;
        }

        void DX11RenderingManager::setRenderTarget(RenderTargetPtr renderTarget) {
            mRenderTarget = renderTarget;
        }

        void DX11RenderingManager::draw() {
            mVertexBuffer->set(mImmediateContext.Get());
            mIndexBuffer->set(mImmediateContext.Get());
            mVertexShader->set(mImmediateContext.Get());
            mPixelShader->set(mImmediateContext.Get());
            mRenderTarget->set(mImmediateContext.Get());
            mIndexBuffer->drawCall(mImmediateContext.Get());
        }

        void DX11RenderingManager::beginFrame() {
            mRenderTarget = mBackBuffer;
            mRenderTarget->clear(mImmediateContext.Get());
        }

        void DX11RenderingManager::endFrame() {
            mSwapChain->Present(0, 0);
            mImmediateContext->ClearState();
            mImmediateContext->Flush();
        }

        std::shared_ptr<IndexBuffer> DX11RenderingManager::createIndexBuffer(const std::vector<UINT>& indices, PrimitiveTopology primitiveTopology) {
            return std::make_shared<IndexBuffer>(mDevice.Get(), indices, primitiveTopology);
        }

        std::shared_ptr<VertexShader> DX11RenderingManager::createVertexShader(const std::string& filename) {
            return std::make_shared<VertexShader>(mDevice.Get(), filename);
        }

        std::shared_ptr<PixelShader> DX11RenderingManager::createPixelShader(const std::string& filename) {
            return std::make_shared<PixelShader>(mDevice.Get(), filename);
        }


    } //Graphics 
} //Framework 
