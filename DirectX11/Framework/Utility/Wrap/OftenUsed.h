#pragma once
#include "Graphics/RenderingManager.h"
#include "Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Input/InputManager.h"

namespace Framework {

/**
* @brief �悭�g����@�\���ȈՓI�Ɏg����悤�Ƀ��b�v�����֐�
*/
namespace Utility {
/**
* @brief ���C���E�B���h�E�̃n���h���̎擾
*/
HWND getMainHWND();

/**
* @brief ImGUI�̊Ǘ��҂̎擾
*/
ImGUI::Manager* getImGUIManager();

/**
* @brief �`��Ǘ��҂̎擾
*/
Graphics::RenderingManager* getRenderingManager();

/**
* @brief �R���X�^���g�o�b�t�@�Ǘ��҂̎擾
*/
Graphics::ConstantBufferManager* getConstantBufferManager();

Input::InputManager* getInputManager();

} //Utility 
} //Framework 
