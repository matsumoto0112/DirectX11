#pragma once
#include <memory>
#include "Source/Scene/Impl/GPUParticle/GPUParticleBase.h"

/**
* @class IceBlock
* @brief 落下して跳ね返るパーティクルテストシーン
*/
class IceBlock : public GPUParticleBase {
public:
    /**
    * @brief コンストラクタ
    */
    IceBlock();
    /**
    * @brief デストラクタ
    */
    ~IceBlock();
    /**
    * @brief 更新
    */
    virtual void update() override;
    /**
    * @brief 描画
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) override;
private:
    struct Particle {
        float lifeTime;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 velocity;
        Framework::Math::Vector3 scale;
        Framework::Math::Vector3 rotate;
        Framework::Math::Vector3 angular;
        Framework::Graphics::Color4 color;
    };

    struct CPUParameter {
        int MAX_RUNNING_PARTICLE_NUM;
        int mCurrentRunningNum;
    } mCPUParameter;

    struct GPUParameter {
        Framework::Math::Vector3 center;
        float padding[1];
    } mGPUParameter;

    std::unique_ptr<Framework::Graphics::ConstantBuffer<GPUParameter>> mEmitParameter;
};