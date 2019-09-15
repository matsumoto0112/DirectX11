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
* @brief FBXモデルストレージ
*/
class FBXModelResourceStorage : public AbstractResourceStorage<Define::ModelType, Graphics::Model> {
public:
    /**
    * @brief コンストラクタ
    */
    FBXModelResourceStorage();
    /**
    * @brief デストラクタ
    */
    ~FBXModelResourceStorage();
    /**
    * @brief リソースをインポートする
    */
    virtual void importResource(Define::ModelType type, const std::string& filepath) override;
private:
    std::unique_ptr<Graphics::FBXLoader> mFBXLoader; //!< FBX読み込み
};

} //Utility 
} //Framework 
