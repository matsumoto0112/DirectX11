#pragma once
#include "Framework/Graphics/Camera/PerspectiveCamera.h"
#include "Framework/Utility/Transform.h"

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
    virtual Framework::Graphics::PerspectiveCamera* getMainCamera() = 0;
    /**
    * @brief �e��ǉ�����
    */
    virtual void shotBullet(const Framework::Utility::Transform& transform) = 0;
};