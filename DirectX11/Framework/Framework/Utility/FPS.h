#pragma once

#include <list>
#include <Windows.h>

namespace Framework {
namespace Utility {

/**
* @class FPS
* @brief FPS�v���N���X
* @detail �Q�l:http://marupeke296.com/DXCLSSmp_FPSCounter.html
*/
class FPS {
public:
    /**
    * @brief �R���X�g���N�^
    * @param sample �T���v����(�����قǑS�̂̕��ς����܂邪�������𑽂��g��)
    */
    FPS(UINT sample = 10);
    /**
    * @brief �f�X�g���N�^
    */
    ~FPS();
    /**
    * @brief FPS�v��
    * @return FPS(�~���b)
    */
    double getFPS();
    /**
    * @brief �T���v�����̐ݒ�
    * @param sample �T���v����(�����قǑS�̂̕��ς����܂邪�������𑽂��g��)
    */
    void setSample(UINT sample);

    double getTime();
private:
    /**
    * @brief ���݂̍������ԁi�~���b�j
    */
    double getCurrentDifferenceTime();
    /**
    * @brief FPS�̍X�V
    * @param diff ��������
    */
    double updateFPS(double diff);
private:
    double mFreq; //!< ���̎��g��
    LARGE_INTEGER mCounter; //!< �N���b�N�J�E���g��
    LONGLONG mOldCounter; //!< �ȑO�̃N���b�N�J�E���g��
    double mSumTimes; //!< ���ʕ����̕��ϒl
    UINT mSample; //!< �T���v����
    std::list<double> mDifferenceTimeList; //!< �o�ߎ��Ԃ̃��X�g
};

} //FPS
} //Framework 
