#pragma once

#include <string>
#include "Framework/Graphics/Shader/ShaderBase.h"
#include "Framework/Graphics/Shader/GeometoryShaderData.h"

namespace Framework {
namespace Graphics {
/**
* @class GeometoryShader
* @brief �W�I���g���V�F�[�_
*/
class GeometoryShader : public ShaderBase {
public:
    /**
    * @brief �R���X�g���N�^
    * @param filename �V�F�[�_�t�@�C����
    */
    GeometoryShader(const std::string& filename);
    /**
    * @brief �f�X�g���N�^
    */
    ~GeometoryShader();
    /**
    * @brief �V�F�[�_�̃Z�b�g
    */
    void set();
private:
    /**
    * @brief �V�F�[�_�̍쐬
    * @param name �V�F�[�_�t�@�C����
    */
    void create(const std::string& name);
private:
    std::unique_ptr<GeometoryShaderData> mShaderData; //!< �V�F�[�_�[�̃f�[�^
};

} //Graphics 
} //Framework 
