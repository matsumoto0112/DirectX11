#pragma once
namespace Framework {
namespace Utility {

class ResourceManager;

/**
* @brief ���\�[�X�X�g���[�W�̏���������
*/
class ResourceInitializeOnStart {
public:
    /**
    * @brief �R���X�g���N�^
    * @param resourceManager ���\�[�X�Ǘ���
    */
    ResourceInitializeOnStart(ResourceManager& resourceManager);
};

} //Utility 
} //Framework 
