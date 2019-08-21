#pragma once
#include "Scene/SceneData/SceneDataBase.h"

namespace Scene {

/**
* @class MainData
* @brief ���C���V�[�����N���X
*/
class MainData : public SceneDataBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    MainData(unsigned int playerID) :mPlayerID(playerID) {}
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~MainData() = default;
    /**
    * @brief �v���C���[�ԍ��̎擾
    */
    unsigned int getPlayerID() const { return mPlayerID; }
    /**
    * @brief �v���C���[�ԍ��̐ݒ�
    */
    void setPlayerID(unsigned int playerID) { mPlayerID = playerID; }
private:
    unsigned int mPlayerID; //!< �v���C���[�ԍ�
};
} //Scene 