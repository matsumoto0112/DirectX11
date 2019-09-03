#include "Cube.h"

namespace Framework {
namespace Graphics {

Cube::Cube() {
    std::vector<OnlyPosition> vertices
    {
        {{-0.5f,   0.5f,  -0.5f,  1.0f} },
        {{0.5f,    0.5f,  -0.5f,  1.0f} },
        {{0.5f,    -0.5f,  -0.5f,  1.0f} },
        {{-0.5f,   -0.5f,  -0.5f,  1.0f} },
        {{-0.5f,    0.5f,   0.5f,  1.0f} },
        {{0.5f,     0.5f,   0.5f,  1.0f} },
        {{0.5f,    -0.5f,   0.5f,  1.0f} },
        {{-0.5f,   -0.5f,   0.5f,  1.0f} },
    };
    std::vector<WORD> indices
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

    mVIBuffer = std::make_unique<VertexAndIndexBuffer>(vertices, indices, PrimitiveTopology::TriangleList);
}

Cube::~Cube() {}

} //Graphics 
} //Framework 
