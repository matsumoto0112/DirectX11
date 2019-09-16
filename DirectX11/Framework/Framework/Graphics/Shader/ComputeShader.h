#pragma once

#include <string>
#include "Framework/Graphics/Shader/ShaderBase.h"
#include "Framework/Graphics/Shader/ComputeShaderData.h"

namespace Framework {
namespace Graphics {
/**
* @class PixelShader
* @brief �s�N�Z���V�F�[�_
*/
class ComputeShader : public ShaderBase {
public:
    /**
    * @brief �R���X�g���N�^
    * @param filename �V�F�[�_�t�@�C����
    */
    ComputeShader(const std::string& filename);
    /**
    * @brief �f�X�g���N�^
    */
    ~ComputeShader();
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
public:
    std::unique_ptr<ComputeShaderData> mShaderData; //!< �V�F�[�_�[�̃f�[�^
};

} //Graphics 
} //Framework 
