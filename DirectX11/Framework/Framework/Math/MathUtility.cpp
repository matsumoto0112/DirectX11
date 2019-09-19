#include "MathUtility.h"
#include <cmath>
#include <stdarg.h>
#include <algorithm>

namespace Framework {
namespace Math {

float MathUtility::sin(float degree) {
    return sinf(toRadian(degree));
}

float MathUtility::cos(float degree) {
    return cosf(toRadian(degree));
}

float MathUtility::tan(float degree) {
    return tanf(toRadian(degree));
}

float MathUtility::atan2(float y, float x) {
    return toDegree(std::atan2f(y, x));
}

float MathUtility::asin(float x) {
    return toDegree(std::asin(x));
}

float MathUtility::acos(float x) {
    return toDegree(std::acos(x));
}

float MathUtility::sqrt(float a) {
    return sqrtf(a);
}

float MathUtility::cot(float degree) {
    return 1.0f / tanf(toRadian(degree));
}

float MathUtility::toRadian(float deg) {
    return deg / 180.0f * PI;
}

float MathUtility::toDegree(float rad) {
    return rad / PI * 180.0f;
}

float MathUtility::abs(float X) {
    return fabsf(X);
}
} //Math 
} //Framework 
