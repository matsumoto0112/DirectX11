#include "FPS.h"
#include <Windows.h>

namespace Framework {
namespace Utility {

FPS::FPS(UINT sample) {
    setSample(sample);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&mCounter);
    mOldCounter = mCounter.QuadPart;
    mFreq = (double)freq.QuadPart;
    getFPS();
}

FPS::~FPS() {
    mDifferenceTimeList.clear();
}

double FPS::getFPS() {
    double diff = getCurrentDifferenceTime();
    //������0���ƌv�Z�ł��Ȃ�
    if (diff == 0) {
        return 0;
    }
    return updateFPS(diff);

}

void FPS::setSample(UINT sample) {
    mSample = sample;
    mDifferenceTimeList.resize(sample, 0.0f);
    mSumTimes = 0;
}

double FPS::getTime() {
    QueryPerformanceCounter(&mCounter);
    return (double)mCounter.QuadPart * 1000 / mFreq;
}

double FPS::getCurrentDifferenceTime() {
    QueryPerformanceCounter(&mCounter);
    double diff = (double)(mCounter.QuadPart - mOldCounter); //����
    mOldCounter = mCounter.QuadPart; //�l�̍X�V
    return diff * 1000 / mFreq;
}

double FPS::updateFPS(double diff) {
    //�Â��f�[�^���폜
    mDifferenceTimeList.pop_front();
    //�V�����f�[�^��ǉ�
    mDifferenceTimeList.push_back(diff);
    //���ϒl��(���ʕ����̍��v+����)/�T���v����
    double average = (mSumTimes + diff) / mSample;
    double FPS = 0;
    if (average != 0) {
        FPS = 1000.0 / average;
    }
    //���ʕ����̍X�V
    //�V�����l�𑫂��ČÂ��l������
    mSumTimes += diff - *mDifferenceTimeList.begin();
    return FPS;
}


} //Utility
} //Framework 
