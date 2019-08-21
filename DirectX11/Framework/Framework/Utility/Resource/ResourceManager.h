#pragma once
#include <memory>
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Resource/FBXModelResourceStorage.h"
#include "Framework/Utility/Resource/VertexShaderResourceStorage.h"
#include "Framework/Utility/Resource/PixelShaderResourceStorage.h"

namespace Framework {
namespace Utility {

class ResourceManager : public Singleton<ResourceManager> {
public:
    ~ResourceManager();
    VertexShaderResourceStorage* getVertexShader() { return mVertexShaders.get(); }
    PixelShaderResourceStorage* getPixelShader() { return mPixelShaders.get(); }
    FBXModelResourceStorage* getFBXModel() { return mFBXModel.get(); }
protected:
    ResourceManager();
private:
    std::unique_ptr<VertexShaderResourceStorage> mVertexShaders;
    std::unique_ptr<PixelShaderResourceStorage> mPixelShaders;
    std::unique_ptr<FBXModelResourceStorage> mFBXModel;
};

} //Utility 
} //Framework 
