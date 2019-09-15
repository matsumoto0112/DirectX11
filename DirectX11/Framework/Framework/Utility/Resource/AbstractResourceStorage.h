#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Utility {

/**
* @class AbstractResourceStorage
* @brief ���ۃ��\�[�X�X�g���[�W
* @tparam ResourceType ���\�[�X�̎�ނ𔻕ʂ���^
* @tparam ResourceData ���\�[�X�f�[�^�N���X
*/
template <class ResourceType, class ResourceData>
class AbstractResourceStorage {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~AbstractResourceStorage() = default;
    /**
    * @brief ���\�[�X���C���|�[�g����
    * @param type ���\�[�X�̎��
    * @param filepath �t�@�C���ւ̃p�X
    */
    virtual void importResource(ResourceType type, const std::string& filepath) = 0;
    /**
    * @brief ���\�[�X���폜����
    */
    virtual void removeResource(ResourceType type);
    /**
    * @brief ���\�[�X���擾����
    */
    virtual std::shared_ptr<ResourceData> getResource(ResourceType type) const;
    /**
    * @brief ���\�[�X�����ɑ��݂��Ă��邩
    */
    bool isExist(ResourceType type) const;
    /**
    * @brief ���\�[�X���N���A����
    */
    void clear();
protected:
    std::unordered_map<ResourceType, std::shared_ptr<ResourceData>> mResources; //!< ���\�[�X�}�b�v
};

template<class ResourceType, class ResourceData>
inline void AbstractResourceStorage<ResourceType, ResourceData>::removeResource(ResourceType type) {
    MY_ASSERTION(mResources.find(type) != mResources.end(),
        "���o�^�̃��\�[�X���폜����悤�Ƃ��܂���");
    mResources.erase(type);
}

template<class ResourceType, class ResourceData>
inline std::shared_ptr<ResourceData> AbstractResourceStorage<ResourceType, ResourceData>::getResource(ResourceType type) const {
    MY_ASSERTION(mResources.find(type) != mResources.end(),
        "���o�^�̃��\�[�X���Ă΂�܂���");
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