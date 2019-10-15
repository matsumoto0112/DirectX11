#pragma once
#include "Framework/Utility/Singleton.h"

namespace Framework {
namespace Define {

/**
* @class MultiSampleQuarity
* @brief MSAAのクオリティ
*/
class MultiSampleQuarity : public Framework::Utility::Singleton<MultiSampleQuarity> {
public:
    static constexpr int Count = 1; //!< 希望するカウント 
public:
    void setMultiSample(int count, int quarity);
public:
    int RealCount; //!< 実際のカウント
    int RealQuarity; //!< 実際のクオリティ
};

} //Define 
} //Framework 