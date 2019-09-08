#include "Time.h"
#include "Framework/Math/MathUtility.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Utility {

Time::Time()
    :mFPSCounter(10),
    deltaTime(mDeltaTime),
    currentFPS(mCurrentFPS) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&mCounter);
    mFreq = (double)freq.QuadPart;
}

Time::~Time() {}

void Time::init(float fps) {
    mFPS = fps;
}

void Time::startFrame() {
    QueryPerformanceCounter(&mCounter);
    double time = (double)mCounter.QuadPart * 1000.0 / mFreq;
    mDeltaTime = static_cast<float>(time - mStartTime) / 1000;
    mStartTime = time;
}

void Time::endFrame() {
    QueryPerformanceCounter(&mCounter);
    mEndTime = (double)mCounter.QuadPart * 1000 / mFreq;
    mCurrentFPS = static_cast<float>(mFPSCounter.getFPS());
}

void Time::wait() {
    double diff = mEndTime - mStartTime;
    double target = 1000.0 / mFPS;
    double wait = target - diff;

    if (wait > 0) {
        timeBeginPeriod(1);
        Sleep(wait);
        timeEndPeriod(1);
    }
}

} //Utility 
} //Framework 
