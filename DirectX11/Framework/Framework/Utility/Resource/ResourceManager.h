#pragma once
#include <memory>
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Resource/FBXModelResourceStorage.h"
#include "Framework/Utility/Resource/VertexShaderResourceStorage.h"
#include "Framework/Utility/Resource/PixelShaderResourceStorage.h"

namespace Framework {
namespace Utility {

/**
* @class ResourceManager
* @brief リソース管理
*/
class ResourceManager : public Singleton<ResourceManager> {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~ResourceManager();
    /**
    * @brief 頂点シェーダ管理者の取得
    */
    VertexShaderResourceStorage* getVertexShader() { return mVertexShaders.get(); }
    /**
    * @brief ピクセルシェーダ管理者の取得
    */
    PixelShaderResourceStorage* getPixelShader() { return mPixelShaders.get(); }
    /**
    * @brief FBXモデル管理者の取得
    */
    FBXModelResourceStorage* getFBXModel() { return mFBXModel.get(); }
protected:
    /**
    * @brief コンストラクタ
    */
    ResourceManager();
private:
    std::unique_ptr<VertexShaderResourceStorage> mVertexShaders;
    std::unique_ptr<PixelShaderResourceStorage> mPixelShaders;
    std::unique_ptr<FBXModelResourceStorage> mFBXModel;
};

} //Utility 
} //Framework 
