#pragma once

#include "Math/Vector2.h"

namespace Framework {

namespace Device {
class GameDevice;
} //Device 

/**
* @class Game
* @brief �Q�[���N���X
*/
class Game {
protected:
    /**
    * @brief �R���X�g���N�^
    * @param screenSize �X�N���[���̑傫��
    * @param isFullScreen �t���X�N���[�����H
    * @param fps �t���[�����[�g
    */
    Game(const Math::Vector2& screenSize, bool isFullScreen = false, float fps = 60.0f);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Game();
public:
    /**
    * @brief ���s
    */
    int run();
    /**
    * @brief ������
    * @return ����������true��Ԃ�
    */
    virtual bool init();
    /**
    * @brief �I������
    */
    virtual void finalize();

private:
    /**
    * @brief �X�V
    * @param deltaTime 1�t���[���̎���
    */
    virtual void update(float deltaTime) = 0;
    /**
    * @brief �`��
    */
    virtual void draw() = 0;
    /**
    * @brief ���s�����H
    */
    virtual bool isRunning();
private:
    //�R�s�[�֎~
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
protected:
    Device::GameDevice& mGameDevice; //!< �Q�[���@��Ǘ�
    Math::Vector2 mScreenSize; //!< �X�N���[���̑傫��
    bool mIsFullScreen; //!< �t���X�N���[�����H
    float mFPS; //!< �t���[�����[�g
};

} //Framework 