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
* @brief テクスチャストレージ
*/
class TextureResourceStorage : public AbstractResourceStorage<Define::TextureType, Graphics::Texture> {
public:
    /**
    * @brief コンストラクタ
    */
    TextureResourceStorage();
    /**
    * @brief デストラクタ
    */
    ~TextureResourceStorage();
    /**
    * @brief リソースをインポートする
    */
    virtual void importResource(Define::TextureType, const std::string& filepath) override;
private:
    std::unique_ptr<Graphics::TextureLoader> mTextureLoader; //!< テクスチャ読み込み
};

} //Utility 
} //Framework 
