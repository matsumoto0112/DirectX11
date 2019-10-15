#pragma once
#include <memory>
#include "Source/Scene/Impl/GPUParticle/GPUParticleBase.h"

/**
* @class FallParticle
* @brief 落下するパーティクルテストシーン
*/
class FallParticle : public GPUParticleBase {
public:
    /**
    * @brief コンストラクタ
    */
    FallParticle();
    /**
    * @brief デストラクタ
    */
    ~FallParticle();
    /**
    * @brief 更新
    */
    virtual void update() override;
    /**
    * @brief 描画
    */
    virtual void draw(Framework::Graphics::IRenderer* pipeline) override;
private:
    struct Particle {
        float lifeTime;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 velocity;
        Framework::Graphics::Color4 color;
    };
};