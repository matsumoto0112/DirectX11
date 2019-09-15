#pragma once
#include <memory>
#include "Framework/Define/Resource/Model.h"
#include "Framework/Graphics/Model/Model.h"
#include "Framework/Utility/Resource/AbstractResourceStorage.h"

namespace Framework {
namespace Graphics {
class FBXLoader;
} //Graphics 

namespace Utility {

/**
* @class FBXModelResourceStorage
* @brief FBX���f���X�g���[�W
*/
class FBXModelResourceStorage : public AbstractResourceStorage<Define::ModelType, Graphics::Model> {
public:
    /**
    * @brief �R���X�g���N�^
    */
    FBXModelResourceStorage();
    /**
    * @brief �f�X�g���N�^
    */
    ~FBXModelResourceStorage();
    /**
    * @brief ���\�[�X���C���|�[�g����
    */
    virtual void importResource(Define::ModelType type, const std::string& filepath) override;
private:
    std::unique_ptr<Graphics::FBXLoader> mFBXLoader; //!< FBX�ǂݍ���
};

} //Utility 
} //Framework 
