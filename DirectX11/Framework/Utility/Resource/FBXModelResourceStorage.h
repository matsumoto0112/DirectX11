#pragma once
#include <memory>
#include "Define/Resource/Model.h"
#include "Graphics/Model/Model.h"
#include "Utility/Resource/AbstractResourceStorage.h"

namespace Framework {
namespace Graphics {
class FBXLoader;
} //Graphics 

namespace Utility {

class FBXModelResourceStorage : public AbstractResourceStorage<Define::ModelType, Graphics::Model> {
public:
    FBXModelResourceStorage();
    ~FBXModelResourceStorage();
    virtual void importResource(Define::ModelType type, const std::string& filepath) override;
private:
    std::unique_ptr<Graphics::FBXLoader> mFBXLoader;
};

} //Utility 
} //Framework 
