#pragma once
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Property.h"
#include "Framework/Utility/FPS.h"

namespace Framework {
namespace Utility {

/**
* @class Time
* @brief discription
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
    void update();
private:
    float mFPS; //!< ���̃Q�[���ł�FPS
    FPS mFPSCounter; //!< FPS�v��
    PROPERTY_READONLY(float, mDeltaTime, DeltaTime);
};

} //Utility 
} //Framework 