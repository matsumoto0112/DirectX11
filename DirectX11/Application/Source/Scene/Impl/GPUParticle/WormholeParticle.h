#pragma once
#include <memory>
#include "Source/Scene/Impl/GPUParticle/GPUParticleBase.h"

/**
* @class WormholeParticle
*/
class WormholeParticle : public GPUParticleBase {
public:
    /**
    * @brief コンストラクタ
    */
    WormholeParticle();
    /**
    * @brief デストラクタ
    */
    ~WormholeParticle();
    /**
    * @brief 更新
    */
    virtual void update() override;
    /**
    * @brief シーン終了条件を満たしているか
    */
    virtual bool isEndScene() const override;
    /**
    * @brief 描画
    */
    virtual void draw(Framework::Graphics::IRenderer* pipeline) override;
private:
    struct Particle {
        float lifeTime;
        float speed;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 velocity;
        Framework::Graphics::Color4 color;
    };
};