#pragma once
#include <memory>
#include "Framework/Define/Resource/Texture.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Utility/Resource/AbstractResourceStorage.h"

namespace Framework {
namespace Graphics {
class TextureLoader;
} //Graphics 

namespace Utility {

/**
* @class TextureResourceStorage
* @brief �e�N�X�`���X�g���[�W
*/
class TextureResourceStorage : public AbstractResourceStorage<Define::TextureType, Graphics::Texture> {
public:
    /**
    * @brief �R���X�g���N�^
    */
    TextureResourceStorage();
    /**
    * @brief �f�X�g���N�^
    */
    ~TextureResourceStorage();
    /**
    * @brief ���\�[�X���C���|�[�g����
    */
    virtual void importResource(Define::TextureType, const std::string& filepath) override;
private:
    std::unique_ptr<Graphics::TextureLoader> mTextureLoader; //!< �e�N�X�`���ǂݍ���
};

} //Utility 
} //Framework 
