#include "Collision.h"

namespace Framework {
namespace Utility {
using namespace Math;

bool Collision::line_plane(const Line& line, const Plane& plane, Vector3* intersection) {
    Vector3 PA(plane.p - line.start);
    Vector3 PB(plane.p - line.end);

    float dotPA = Vector3::dot(plane.normal, PA);
    float dotPB = Vector3::dot(plane.normal, PB);

    if (MathUtility::abs(dotPA) < EPSILON) dotPA = 0.0f;
    if (MathUtility::abs(dotPB) < EPSILON) dotPB = 0.0f;

    //両端が平面上にある
    if (dotPA == 0.0f && dotPB == 0.0f) { return false; }
    //両端が平面上の表もしくは裏側にある
    if ((dotPA >= 0.0f && dotPB >= 0.0f) || (dotPA <= 0.0f && dotPB <= 0.0f)) { return false; }

    Vector3 AB = line.end - line.start;

    float ratio = MathUtility::abs(dotPA) / (MathUtility::abs(dotPA) + MathUtility::abs(dotPB));
    *intersection = line.start + AB * ratio;
    return true;
}

bool Collision::obb_plane(const OBB3D& obb, const Plane& plane, float* len) {
    //平面に対するOBBの射影線の長さを計算
    float r = 0.0f;
    for (int i = 0; i < 3; i++) {
        r += MathUtility::abs(Vector3::dot(obb.mNormalDirect[i] * obb.getLength(i), plane.normal));
    }

    //平面とOBBとの距離を計算
    float s = Vector3::dot((obb.mPosition - plane.p), plane.normal);

    //戻し距離を計算
    if (len != nullptr) {
        if (s > 0) {
            *len = r - MathUtility::abs(s);
        }
        else {
            *len = r + MathUtility::abs(s);
        }
    }

    //衝突判定
    if (MathUtility::abs(s) - r < 0.0f) {
        return true;
    }
    return false;
}

} //Utility 
} //Framework 
