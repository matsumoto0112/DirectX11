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

    //—¼’[‚ª•½–Êã‚É‚ ‚é
    if (dotPA == 0.0f && dotPB == 0.0f) { return false; }
    //—¼’[‚ª•½–Êã‚Ì•\‚à‚µ‚­‚Í— ‘¤‚É‚ ‚é
    if ((dotPA >= 0.0f && dotPB >= 0.0f) || (dotPA <= 0.0f && dotPB <= 0.0f)) { return false; }

    Vector3 AB = line.end - line.start;

    float ratio = MathUtility::abs(dotPA) / (MathUtility::abs(dotPA) + MathUtility::abs(dotPB));
    *intersection = line.start + AB * ratio;
    return true;
}

bool Collision::obb_plane(const OBB3D& obb, const Plane& plane, float* len) {
    float r = 0.0f;
    for (int i = 0; i < 3; i++) {
        r += MathUtility::abs(Vector3::dot(obb.mNormalDirect[i] * obb.getLength(i), plane.normal));
    }
    float s = Vector3::dot((obb.mPosition - plane.p), plane.normal);
    if (len != nullptr) {
        if (s > 0) {
            *len = r - MathUtility::abs(s);
        }
        else {
            *len = r + MathUtility::abs(s);
        }
    }
    if (MathUtility::abs(s) - r < 0.0f) {
        return true;
    }
    return false;
}

} //Utility 
} //Framework 
