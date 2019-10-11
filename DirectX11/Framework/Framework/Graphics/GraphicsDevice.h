#pragma once
#include <Windows.h>
#include "Framework/Math/Vector2.h"
#include "Framework/Graphics/DirectX11GraphicsDevice.h"

namespace Framework {
namespace Graphics {
/**
* @class GraphicsDevice
* @brief �`��@��
*/
class GraphicsDevice {
public:
    /**
    * @brief �R���X�g���N�^
    * @param hWnd �E�B���h�E�n���h��
    * @param width �E�B���h�E��
    * @param height �E�B���h�E����
    * @param isFullScreen �t���X�N���[�����ǂ���
    */
    GraphicsDevice(HWND hWnd, UINT width, UINT height, bool isFullScreen);
    /**
    * @brief �f�X�g���N�^
    */
    ~GraphicsDevice();
    /**
    * @brief �`�揈���J�n
    */
    void drawBegin();
    /**
    * @brief �`�揈���I��
    */
    void drawEnd();
    void cleanup();

    DirectX11GraphicsDevice* getDirectX11GraphicsDevice() const { return mDirectX11Device.get(); }
private:
    std::unique_ptr<DirectX11GraphicsDevice> mDirectX11Device; //!< DirectX11�p�O���t�B�b�N�f�o�C�X�Ǘ�
};

} //Graphics
} //Framework 