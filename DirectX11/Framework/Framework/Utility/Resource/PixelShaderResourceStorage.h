#pragma once
#include "Framework/Define/Resource/PixelShader.h"
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Utility/Resource/AbstractResourceStorage.h"

namespace Framework {
namespace Utility {

/**
* @class PixelShaderResourceStorage
* @brief �s�N�Z���V�F�[�_�X�g���[�W
*/
class PixelShaderResourceStorage : public AbstractResourceStorage<Define::PixelShaderType, Graphics::PixelShader> {
public:
    /**
    * @brief �R���X�g���N�^
    */
    PixelShaderResourceStorage();
    /**
    * @brief �f�X�g���N�^
    */
    ~PixelShaderResourceStorage();
    /**
    * @brief ���\�[�X���C���|�[�g����
    */
    virtual void importResource(Define::PixelShaderType type) override;
};

} //Utility 
} //Framework 
