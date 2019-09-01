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
* @brief DirectX11�p�O���t�B�b�N�f�o�C�X
*/
class DirectX11GraphicsDevice {
public:
    /**
    * @brief �R���X�g���N�^
    * @param hWnd �E�B���h�E�n���h��
    */
    DirectX11GraphicsDevice(HWND hWnd, UINT screenWidth, UINT screenHeight, bool isFullScreen);
    /**
    * @brief �f�X�g���N�^
    */
    ~DirectX11GraphicsDevice();
    /**
    * @brief �f�o�C�X�̎擾
    */
    Microsoft::WRL::ComPtr<ID3D11Device> getDevice() const { return mDevice; }
    /**
    * @brief �f�o�C�X�R���e�L�X�g�̎擾
    */
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> getContext() const { return mImmediateContext; }
    /**
    * @brief �`��o�b�t�@�̐؂�ւ�
    */
    void present(UINT syncInterval = 1);
    /**
    * @brief �o�b�N�o�b�t�@�̎擾
    */
    std::shared_ptr<TextureBuffer> getBackBuffer();
    /**
    * @brief �X���b�v�`�F�C���̎擾
    */
    Microsoft::WRL::ComPtr<IDXGISwapChain> getSwapChain() const { return mSwapChain; }
private:
    Microsoft::WRL::ComPtr<ID3D11Device> mDevice; //!< �f�o�C�X
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> mImmediateContext; //!< �f�o�C�X�R���e�L�X�g 
    Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain; //!< �X���b�v�`�F�C��
    Microsoft::WRL::ComPtr<ID3D11Debug> mDebug; //!< �f�o�b�O
};

} //Graphics 
} //Framework 