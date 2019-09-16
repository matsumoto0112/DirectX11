#include "Timer.h"

namespace Framework {
namespace Utility {

Timer::Timer(float time)
    :Timer(time, nullptr) {}

Timer::Timer(float time, Event timerEvent)
    : mEvent(timerEvent), mLimitTime(time), mCurrentTime(mLimitTime) {}

Timer::~Timer() {}

void Timer::init() {
    mCurrentTime = mLimitTime;
}

void Timer::update(float delta) {
    if (mCurrentTime <= 0.0f)return;
    mCurrentTime -= delta;
    if (mCurrentTime <= 0.0f && mEvent) {
        mEvent();
    }
}

bool Timer::isTime() {
    return mCurrentTime <= 0.0f;
}

} //Utility 
} //Framework 
