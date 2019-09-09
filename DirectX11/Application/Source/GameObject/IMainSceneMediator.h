#pragma once
#include "Framework/Utility/Transform.h"
#include "Source/GameObject/FollowCamera.h"

class Player;

/**
* @class IMainSceneMediator
* @brief ���C���V�[�������
*/
class IMainSceneMediator {
public:
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~IMainSceneMediator() {};
    /**
    * @brief ���C���J�������擾����
    */
    virtual FollowCamera* getMainCamera() = 0;
    /**
    * @brief �v���C���[�|�C���^���擾����
    */
    virtual Player* getPlayer() = 0;
    /**
    * @brief �e��ǉ�����
    */
    virtual void shotBullet(const Framework::Utility::Transform& transform) = 0;
    /**
    * @brief �f�o�b�O�pImGUI�E�B���h�E��ǉ�����
    */
    virtual void addDebugUI(std::shared_ptr<Framework::ImGUI::Window> window) = 0;
};