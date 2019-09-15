#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Utility {

/**
* @class AbstractResourceStorage
* @brief 抽象リソースストレージ
* @tparam ResourceType リソースの種類を判別する型
* @tparam ResourceData リソースデータクラス
*/
template <class ResourceType, class ResourceData>
class AbstractResourceStorage {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~AbstractResourceStorage() = default;
    /**
    * @brief リソースをインポートする
    * @param type リソースの種類
    * @param filepath ファイルへのパス
    */
    virtual void importResource(ResourceType type, const std::string& filepath) = 0;
    /**
    * @brief リソースを削除する
    */
    virtual void removeResource(ResourceType type);
    /**
    * @brief リソースを取得する
    */
    virtual std::shared_ptr<ResourceData> getResource(ResourceType type) const;
    /**
    * @brief リソースが既に存在しているか
    */
    bool isExist(ResourceType type) const;
    /**
    * @brief リソースをクリアする
    */
    void clear();
protected:
    std::unordered_map<ResourceType, std::shared_ptr<ResourceData>> mResources; //!< リソースマップ
};

template<class ResourceType, class ResourceData>
inline void AbstractResourceStorage<ResourceType, ResourceData>::removeResource(ResourceType type) {
    MY_ASSERTION(mResources.find(type) != mResources.end(),
        "未登録のリソースが削除されようとしました");
    mResources.erase(type);
}

template<class ResourceType, class ResourceData>
inline std::shared_ptr<ResourceData> AbstractResourceStorage<ResourceType, ResourceData>::getResource(ResourceType type) const {
    MY_ASSERTION(mResources.find(type) != mResources.end(),
        "未登録のリソースが呼ばれました");
    return mResources.at(type);
}

template <class ResourceType, class ResourceData>
inline bool AbstractResourceStorage<ResourceType, ResourceData>::isExist(ResourceType type) const {
    return mResources.find(type) != mResources.end();
}

template<class ResourceType, class ResourceData>
inline void AbstractResourceStorage<ResourceType, ResourceData>::clear() {
    mResources.clear();
}

} //Utility 
} //Framework 