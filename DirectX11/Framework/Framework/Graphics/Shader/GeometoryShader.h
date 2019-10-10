#pragma once

#include <string>
#include "Framework/Graphics/Shader/ShaderBase.h"

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
    * @param filepath �V�F�[�_�[�t�@�C���̃p�X
    */
    GeometoryShader(const std::string& filepath);
    /**
    * @brief �f�X�g���N�^
    */
    ~GeometoryShader();
    /**
    * @brief �V�F�[�_�̃Z�b�g
    */
    void set();
private:
    ComPtr<ID3D11GeometryShader> mGeometoryShader; //!< �V�F�[�_�[�̃f�[�^
};

} //Graphics 
} //Framework 
