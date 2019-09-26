#pragma once
#include <memory>
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Resource/FBXModelResourceStorage.h"
#include "Framework/Utility/Resource/GeometoryShaderResourceStorage.h"
#include "Framework/Utility/Resource/PixelShaderResourceStorage.h"
#include "Framework/Utility/Resource/TextureResourceStorage.h"
#include "Framework/Utility/Resource/VertexShaderResourceStorage.h"

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
    VertexShaderResourceStorage* getVertexShader() const { return mVertexShaders.get(); }
    /**
    * @brief ジオメトリシェーダ管理者の取得
    */
    GeometoryShaderResourceStorage* getGeometoryShader() const { return mGeometoryShaders.get(); }
    /**
    * @brief ピクセルシェーダ管理者の取得
    */
    PixelShaderResourceStorage* getPixelShader() const { return mPixelShaders.get(); }
    /**
    * @brief FBXモデル管理者の取得
    */
    FBXModelResourceStorage* getFBXModel() const { return mFBXModel.get(); }
    /**
    * @brief テクスチャ管理者の取得
    */
    TextureResourceStorage* getTexture() const { return mTexture.get(); }
protected:
    /**
    * @brief コンストラクタ
    */
    ResourceManager();
private:
    std::unique_ptr<VertexShaderResourceStorage> mVertexShaders;
    std::unique_ptr<GeometoryShaderResourceStorage> mGeometoryShaders;
    std::unique_ptr<PixelShaderResourceStorage> mPixelShaders;
    std::unique_ptr<FBXModelResourceStorage> mFBXModel;
    std::unique_ptr<TextureResourceStorage> mTexture;
};

} //Utility 
} //Framework 
