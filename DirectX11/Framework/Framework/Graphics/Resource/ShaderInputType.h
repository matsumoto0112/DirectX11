#pragma once
namespace Framework {
namespace Graphics {

/**
* @enum ShaderInputType
* @brief �V�F�[�_�ɒl��������ۂǂ̃V�F�[�_�ɑ�����邩
*/
enum class ShaderInputType {
    Vertex = 1 << 0,
    Pixel = 1 << 1,
    Geometory = 1 << 2,
    Compute = 1 << 3,
};

inline ShaderInputType operator|(ShaderInputType L, ShaderInputType R) {
    return static_cast<ShaderInputType>(static_cast<uint64_t>(L) | static_cast<uint64_t>(R));
}

inline ShaderInputType operator&(ShaderInputType L, ShaderInputType R) {
    return static_cast<ShaderInputType>(static_cast<uint64_t>(L) & static_cast<uint64_t>(R));
}

inline bool AND(ShaderInputType L, ShaderInputType R) {
    return (L & R) == R;
}

} //Graphics 
} //Framework 
