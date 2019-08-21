#include "Plane.h"
namespace Framework {
namespace Math {

Plane::Plane(Vector3 normal, Vector3 point) {
    mPlaneVector = Vector4(normal.x, normal.y, normal.z, Math::Vector3::dot(normal, point));
}

Plane::~Plane() {}
} //Math 
} //Framework 