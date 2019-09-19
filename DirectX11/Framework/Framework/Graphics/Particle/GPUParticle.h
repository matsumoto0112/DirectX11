#pragma once
#include <memory>
#include "Framework/Graphics/Shader/ComputeShader.h"
#include "Framework/Graphics/Shader/GeometoryShader.h"
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Graphics/Texture/Texture.h"
#include "Framework/Utility/Wrap/DirectX.h"

namespace Framework {
namespace Graphics {

/**
* @class GPUParticle
* @brief GPUを使用したパーティクルs
*/
class GPUParticle {
public:
    /**
    * @brief コンストラクタ
    */
    GPUParticle(UINT maxParticleNum,
        std::shared_ptr<Texture> texture,
        std::shared_ptr<ComputeShader> cs,
        std::shared_ptr<VertexShader> vs,
        std::shared_ptr<PixelShader> ps,
        std::shared_ptr<GeometoryShader> gs);
    /**
    * @brief デストラクタ
    */
    ~GPUParticle();
    void simulate();
    void draw();
private:
    UINT mMaxParticleNum;
    std::shared_ptr<Texture> mTexture;
    std::shared_ptr<ComputeShader> mComputeShader;
    std::shared_ptr<VertexShader> mVertexShader;
    std::shared_ptr<PixelShader> mPixelShader;
    std::shared_ptr<GeometoryShader> mGeometoryShader;
};

} //Graphics 
} //Framework 