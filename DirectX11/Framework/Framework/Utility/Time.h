#pragma once
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Property.h"
#include "Framework/Utility/FPS.h"

namespace Framework {
namespace Utility {

/**
* @class Time
* @brief ���ԊǗ��N���X
*/
class Time :public Singleton<Time> {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Time();
    /**
    * @brief �f�X�g���N�^
    */
    ~Time();
    /**
    * @brief ����������
    * @param fps ���̃Q�[����FPS
    */
    void init(float fps);
    /**
    * @brief �t���[���J�n���ɌĂ�
    */
    void startFrame();
    /**
    * @brief �t���[���I�����ɌĂ�
    */
    void endFrame();
    /**
    * @brief ���܂���FPS���ێ����邽�߂ɑҋ@����
    */
    void wait();
private:
    double mStartTime; //!< �t���[���J�n����
    double mEndTime; //!< �t���[���I������
    double mFreq; //!< ���̎��g��
    LARGE_INTEGER mCounter; //!< �N���b�N�J�E���g��
    float mFPS; //!< ���̃Q�[���ł�FPS
    FPS mFPSCounter; //!< FPS�v��
private:
    PROPERTY_READONLY(float, mDeltaTime, DeltaTime);
    PROPERTY_READONLY(float, mCurrentFPS, CurrentFPS);
};

} //Utility 
} //Framework 