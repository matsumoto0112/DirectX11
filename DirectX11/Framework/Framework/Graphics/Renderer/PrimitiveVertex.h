#pragma once
#include <vector>
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector4.h"
#include "Framework/Graphics/Renderer/PrimitiveTopology.h"

namespace Framework {
namespace Graphics {

/**
* @class PrimitiveVertex
* @brief プリミティブ頂点定義
*/
class PrimitiveVertex {
private:
    using Vec2List = std::vector<Math::Vector2>;
    using Vec4List = std::vector<Math::Vector4>;
    using IndexList = std::vector<UINT>;
public:
    static const Vec4List quadPosition();
    static const IndexList quadIndex();
    static constexpr PrimitiveTopology QuadPrimitiveTopology = PrimitiveTopology::TriangleList;
    static const Vec2List quadUV();
    static const Vec4List cubePosition();
    static const IndexList cubeIndex();
    static constexpr PrimitiveTopology CubePrimitiveTopology = PrimitiveTopology::TriangleList;
    static const Vec4List spherePosition(UINT u_max, UINT v_max);
    static const IndexList sphereIndex(UINT u_max, UINT v_max);
    static constexpr PrimitiveTopology SpherePrimitiveTopology = PrimitiveTopology::TriangleList;
};

} //Graphics 
} //Framework 