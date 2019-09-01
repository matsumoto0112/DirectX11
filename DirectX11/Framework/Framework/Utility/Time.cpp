#include "Time.h"
#include "Framework/Math/MathUtility.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Utility {

Time::Time()
    :mFPSCounter(10) {}

Time::~Time() {}

void Time::init(float fps) {
    mFPS = fps;
}

void Time::update() {
    //����̃��[�v���FPS���v��
    float fps = mFPSCounter.getFPS();
    MY_DEBUG_LOG(StringBuilder("FPS:") << fps);
}

} //Utility 
} //Framework 
