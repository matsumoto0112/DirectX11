#pragma once
#include <memory>
#include "Source/Scene/Impl/GPUParticle/GPUParticleBase.h"

/**
* @class Firefly
* @brief 落下するパーティクルテストシーン
*/
class Firefly : public GPUParticleBase {
public:
    /**
    * @brief コンストラクタ
    */
    Firefly();
    /**
    * @brief デストラクタ
    */
    ~Firefly();

    virtual void load(Framework::Scene::Collecter& collecter) override;
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
        float moveTime;
        float nextRotateTime;
        float angle;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 scale;
        Framework::Graphics::Color4 color;
    };
};