#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Utility {

template <class ResourceEnum, class ResourceType>
class AbstractResourceStorage {
public:
    virtual ~AbstractResourceStorage() = default;
    virtual void importResource(ResourceEnum type, const std::string& filepath) = 0;
    void removeResource(ResourceEnum type);
    std::shared_ptr<ResourceType> getResource(ResourceEnum type);
    bool exist(ResourceEnum type);
    void clear();
protected:
    std::unordered_map<ResourceEnum, std::shared_ptr<ResourceType>> mResources;
};

template<class ResourceEnum, class ResourceType>
inline void AbstractResourceStorage<ResourceEnum, ResourceType>::removeResource(ResourceEnum type) {
    MY_ASSERTION(mResources.find(type) != mResources.end(),
        "–¢“o˜^‚ÌƒŠƒ\[ƒX‚ªíœ‚³‚ê‚æ‚¤‚Æ‚µ‚Ü‚µ‚½");
    mResources.erase(type);
}

template<class ResourceEnum, class ResourceType>
inline std::shared_ptr<ResourceType> AbstractResourceStorage<ResourceEnum, ResourceType>::getResource(ResourceEnum type) {
    MY_ASSERTION(mResources.find(type) != mResources.end(),
        "–¢“o˜^‚ÌƒŠƒ\[ƒX‚ªŒÄ‚Î‚ê‚Ü‚µ‚½");
    return mResources[type];
}

template <class ResourceEnum, class ResourceType>
inline bool AbstractResourceStorage<ResourceEnum, ResourceType>::exist(ResourceEnum type) {
    return mResources.find(type) != mResources.end();
}

template<class ResourceEnum, class ResourceType>
inline void AbstractResourceStorage<ResourceEnum, ResourceType>::clear() {
    mResources.clear();
}

} //Utility 
} //Framework 