#include "Sphere.h"
#include "Framework/Graphics/Buffer/VertexAndIndexBuffer.h"
#include "Framework/Math/MathUtility.h"
#include "Framework/Utility/Wrap/DirectX.h"
#include "Framework/Utility/Wrap/OftenUsed.h"

namespace Framework {
namespace Graphics {
Sphere::Sphere(UINT u_max, UINT v_max) {
    std::vector<OnlyPosition> vertices(u_max *(v_max + 1));
    for (UINT v = 0; v <= v_max; v++) {
        for (UINT u = 0; u < u_max; u++) {
            float theta = Math::MathUtility::toRadian(180.0f * v / v_max);
            float phi = Math::MathUtility::toRadian(360.0f * u / u_max);
            float x = std::sinf(theta) * std::cosf(phi);
            float y = std::cosf(theta);
            float z = std::sinf(theta) * std::sinf(phi);
            vertices[u_max * v + u].pos = Math::Vector4(x, y, z, 1.0f);
        }
    }
    std::vector<UINT> indices(2 * v_max * (u_max + 1));
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

    mVIBuffer = std::make_unique<VertexAndIndexBuffer>(
        vertices,
        indices,
        PrimitiveTopology::TriangleStrip);
}

Sphere::~Sphere() {}

void Sphere::render(const Utility::Transform& transform) {
    Utility::getConstantBufferManager()->setMatrix(ConstantBufferParameterType::World, transform.createSRTMatrix());
    Utility::getConstantBufferManager()->send();
    mVIBuffer->render();
}

} //Graphics 
} //Framework 
