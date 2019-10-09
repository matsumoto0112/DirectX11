#include "PrimitiveVertex.h"

namespace Framework {
namespace Graphics {

const PrimitiveVertex::Vec4List PrimitiveVertex::quadPosition() {
    return
    {
        {0.0f,0.0f,0.0f,1.0f},
        {1.0f,0.0f,0.0f,1.0f},
        {1.0f,1.0f,0.0f,1.0f},
        {0.0f,1.0f,0.0f,1.0f},
    };
}

const PrimitiveVertex::IndexList PrimitiveVertex::quadIndex() {
    return { 0,1,2,0,2,3 };
}

const PrimitiveVertex::Vec2List PrimitiveVertex::quadUV() {
    return
    {
        {0.0f,0.0f},
        {1.0f,0.0f},
        {1.0f,1.0f},
        {0.0f,1.0f},
    };
}

const PrimitiveVertex::Vec4List PrimitiveVertex::cubePosition() {
    return
    {
        { -0.5f, 0.5f, -0.5f, 1.0f },
        { 0.5f,    0.5f,  -0.5f,  1.0f },
        { 0.5f,    -0.5f,  -0.5f,  1.0f },
        { -0.5f,   -0.5f,  -0.5f,  1.0f },
        { -0.5f,    0.5f,   0.5f,  1.0f },
        { 0.5f,     0.5f,   0.5f,  1.0f },
        { 0.5f,    -0.5f,   0.5f,  1.0f },
        { -0.5f,   -0.5f,   0.5f,  1.0f },
    };
}

const PrimitiveVertex::IndexList PrimitiveVertex::cubeIndex() {
    return
    {
        0,1,2,
        0,2,3,
        4,0,3,
        4,3,7,
        5,4,7,
        5,7,6,
        1,5,6,
        1,6,2,
        3,2,6,
        3,6,7,
        4,5,1,
        4,1,0,
    };
}

const PrimitiveVertex::Vec4List PrimitiveVertex::spherePosition(UINT u_max, UINT v_max) {
    Vec4List vertices(u_max *(v_max + 1));
    for (UINT v = 0; v <= v_max; v++) {
        for (UINT u = 0; u < u_max; u++) {
            float theta = Math::MathUtility::toRadian(180.0f * v / v_max);
            float phi = Math::MathUtility::toRadian(360.0f * u / u_max);
            float x = std::sinf(theta) * std::cosf(phi);
            float y = std::cosf(theta);
            float z = std::sinf(theta) * std::sinf(phi);
            vertices[u_max * v + u] = Math::Vector4(x, y, z, 1.0f);
        }
    }
    return vertices;
}

const PrimitiveVertex::IndexList PrimitiveVertex::sphereIndex(UINT u_max, UINT v_max) {
    IndexList indices(2 * v_max * (u_max + 1));
    int i = 0;
    for (UINT v = 0; v < v_max; v++) {
        for (UINT u = 0; u <= u_max; u++) {
            if (u == u_max) {
                indices[i++] = v * u_max;
                indices[i++] = (v + 1) * u_max;
            }
            else {
                indices[i++] = (v * u_max) + u;
                indices[i++] = indices[i - 1] + u_max;
            }
        }
    }
    return indices;
}

} //Graphics 
} //Framework 
