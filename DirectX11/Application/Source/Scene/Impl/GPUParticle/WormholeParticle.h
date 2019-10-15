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
    * @brief 描画
    */
    virtual void draw(Framework::Graphics::IRenderer* pipeline) override;
private:
    /**
    * @brief パーティクル構造体
    */
    struct Particle {
        float lifeTime;
        float speed;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 velocity;
        Framework::Graphics::Color4 color;
    };
    /**
    * @brief GPUで利用するパーティクルのエミットパラメータ
    */
    struct ParticleGPUParameter {
        UINT index;
        Framework::Math::Vector3 spot;
        Framework::Math::Vector3 center;
        float radius;
    };
    /**
    * @brief CPUで利用するパーティクルのエミットパラメータ
    */
    struct ParticleCPUParameter {
        UINT MAX_RUNS_GPUPARTICLE_NUM; //!< 最大で利用するパーティクルの実行数
        int mCurrentRunsGPUParticleNum; //!< 現在のパーティクル実行数
        float mSpeed; //!< パーティクルの生成地点の移動速度
        float mMaxYPosition; //!< 最大Y座標値
    };
    std::unique_ptr<Framework::Graphics::ConstantBuffer<ParticleGPUParameter>> mParameterCB; //<! パラメータ用コンスタントバッファ
    ParticleGPUParameter mGPUParameter;
    ParticleCPUParameter mCPUParameter;
};