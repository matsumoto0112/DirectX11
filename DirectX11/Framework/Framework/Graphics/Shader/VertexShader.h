#pragma once

#include <vector>
#include <memory>
#include <d3d11.h>
#include "Framework/Graphics/Shader/ShaderBase.h"
#include "Framework/Graphics/Shader/VertexShaderData.h"

namespace Framework {
namespace Graphics {
class GraphicsDeviceManager;

/**
* @class VertexShader
* @brief ���_�V�F�[�_
*/
class VertexShader : public ShaderBase {
public:
    /**
    * @brief �R���X�g���N�^
    * @param filename �V�F�[�_�t�@�C����
    */
    VertexShader(const std::string& name);
    /**
    * @brief �R���X�g���N�^
    * @param filename �V�F�[�_�t�@�C����
    */
    VertexShader(const std::string& name, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputLayouts);
    /**
    * @brief �f�X�g���N�^
    */
    ~VertexShader();
    /**
    * @brief ���_�V�F�[�_�̃Z�b�g
    */
    void set() override;
private:
    /**
    * @brief ���_�V�F�[�_�̍쐬
    * @param filename �V�F�[�_�t�@�C����
    */
    void create(const std::string& name);
private:
    std::unique_ptr<VertexShaderData> mShaderData; //!< �V�F�[�_�[�̃f�[�^
};
} //Graphics 
} //Framework 
