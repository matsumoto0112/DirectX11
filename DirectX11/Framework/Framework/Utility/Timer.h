#pragma once
#include <functional>
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Utility {

/**
* @class Timer
* @brief �^�C�}�[�N���X
*/
class Timer {
    using Event = std::function<void(void)>;
public:
    /**
    * @brief �R���X�g���N�^
    */
    Timer(float time);
    /**
    * @brief �R���X�g���N�^
    */
    Timer(float time, Event timerEvent);
    /**
    * @brief �f�X�g���N�^
    */
    ~Timer();
    /**
    * @brief ����������
    */
    void init();
    /**
    * @brief �X�V
    * @param delta ��������
    */
    void update(float delta);
    /**
    * @brief ���ԂɂȂ�����
    */
    bool isTime();
private:
    PROPERTY(float, mLimitTime, LimitTime);
    PROPERTY(float, mCurrentTime, CurrentTime);
    PROPERTY(Event, mEvent, TimeEvent);
};

} //Utility 
} //Framework 