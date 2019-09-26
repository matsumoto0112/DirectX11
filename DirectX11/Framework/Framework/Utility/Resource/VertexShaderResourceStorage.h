#pragma once
#include <unordered_map>
#include "Framework/Define/Resource/VertexShader.h"
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Utility/Resource/AbstractResourceStorage.h"

namespace Framework {
namespace Utility {

/**
* @class VertexShaderResourceStorage
* @brief ���_�V�F�[�_�X�g���[�W
*/
class VertexShaderResourceStorage : public AbstractResourceStorage<Define::VertexShaderType, Graphics::VertexShader> {
public:
    /**
    * @brief �R���X�g���N�^
    */
    VertexShaderResourceStorage();
    /**
    * @brief �f�X�g���N�^
    */
    ~VertexShaderResourceStorage();
    /**
    * @brief ���\�[�X���C���|�[�g����
    */
    virtual void importResource(Define::VertexShaderType type) override;
};

} //Utility 
} //Framework 
