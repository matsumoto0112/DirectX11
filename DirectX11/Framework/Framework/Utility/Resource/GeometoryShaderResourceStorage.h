#pragma once
#include "Framework/Define/Resource/GeometoryShader.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Utility/Resource/AbstractResourceStorage.h"

namespace Framework {
namespace Utility {

/**
* @class GeometoryShaderResourceStorage
* @brief �W�I���g���V�F�[�_�X�g���[�W
*/
class GeometoryShaderResourceStorage : public AbstractResourceStorage<Define::GeometoryShader, Graphics::GeometoryShader> {
public:
    /**
    * @brief �R���X�g���N�^
    */
    GeometoryShaderResourceStorage();
    /**
    * @brief �f�X�g���N�^
    */
    ~GeometoryShaderResourceStorage();
    /**
    * @brief ���\�[�X���C���|�[�g����
    */
    virtual void importResource(Define::GeometoryShader type) override;
};

} //Utility 
} //Framework 
