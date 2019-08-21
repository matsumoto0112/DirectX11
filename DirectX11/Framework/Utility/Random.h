#pragma once

#include <random>
#include "Utility/Singleton.h"

namespace Framework {
namespace Utility {

/**
* @class Random
* @brief ���������N���X
*/
class Random : public Singleton<Random> {
public:
    /**
    * @brief min�ȏ�max�����̗����̐���
    */
    int range(int min, int max);
    /**
    * @brief min�ȏ�max�ȉ��̗����̐���
    */
    float range(float min, float max);
protected:
    /**
    * @brief �R���X�g���N�^
    * @details �R���X�g���N�^���O������Ă΂�Ȃ�����protected�錾
    */
    Random();
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Random();
private:
    std::random_device rnd;
    std::mt19937 mt;
    std::uniform_int_distribution<> randN;
    std::uniform_real_distribution<> randF;
};

} //Utility 
} //Framework 