#include "Random.h"

namespace Framework {
namespace Utility {

Random::Random() {
    mt = std::mt19937(rnd());
}

Random::~Random() {}

int Random::range(int min, int max) {
    randN = std::uniform_int_distribution<>(min, max - 1);
    int n = randN(mt);
    return n;
}

float Random::range(float min, float max) {
    randF = std::uniform_real_distribution<>(min, max);
    float n = (float)randF(mt);
    return n;
}
} //Utility 
} //Framework 
