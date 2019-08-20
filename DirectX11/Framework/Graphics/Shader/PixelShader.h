#pragma once

#include <string>
#include "Graphics/Shader/ShaderBase.h"
#include "Graphics/Shader/PixelShaderData.h"

namespace Framework {
namespace Graphics {
/**
* @class PixelShader
* @brief �s�N�Z���V�F�[�_
*/
class PixelShader : public ShaderBase {
public:
    /**
    * @brief �R���X�g���N�^
    * @param graphicsDevice �O���t�B�b�N�f�o�C�X
    * @param filename �V�F�[�_�t�@�C����
    */
    PixelShader(const std::string& filename);
    /**
    * @brief �f�X�g���N�^
    */
    ~PixelShader();
    /**
    * @brief �s�N�Z���V�F�[�_�̃Z�b�g
    */
    void set();
private:
    /**
    * @brief �s�N�Z���V�F�[�_�̍쐬
    * @param name �V�F�[�_�t�@�C����
    */
    void create(const std::string& name);
private:
    std::unique_ptr<PixelShaderData> mShaderData; //!< �V�F�[�_�[�̃f�[�^
};

} //Graphics 
} //Framework 
