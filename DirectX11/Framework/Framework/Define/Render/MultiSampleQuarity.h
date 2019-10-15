#pragma once
#include "Framework/Utility/Singleton.h"

namespace Framework {
namespace Define {

/**
* @class MultiSampleQuarity
* @brief MSAA�̃N�I���e�B
*/
class MultiSampleQuarity : public Framework::Utility::Singleton<MultiSampleQuarity> {
public:
    static constexpr int Count = 1; //!< ��]����J�E���g 
public:
    void setMultiSample(int count, int quarity);
public:
    int RealCount; //!< ���ۂ̃J�E���g
    int RealQuarity; //!< ���ۂ̃N�I���e�B
};

} //Define 
} //Framework 