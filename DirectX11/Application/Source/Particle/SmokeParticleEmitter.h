#pragma once
#include "Framework/Graphics/Particle/ParticleEmitter.h"
#include "Framework/Utility/Property.h"
#include "Framework/Utility/Range.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Transform.h"

/**
* @class SmokeParticleEmitter
* @brief 煙のパーティクルのエミッター
*/
class SmokeParticleEmitter : public Framework::Graphics::ParticleEmitter {
public:
    /**
    * @brief コンストラクタ
    */
    SmokeParticleEmitter(std::shared_ptr<Framework::Graphics::Particle> particle);
    /**
    * @brief デストラクタ
    */
    virtual ~SmokeParticleEmitter();
    /**
    * @brief 初期化処理
    */
    virtual void init() override;
    /**
    * @brief シミュレートする
    */
    virtual void simulate(float delta) override;
    /**
    * @brief 描画
    */
    virtual void draw(Framework::Graphics::IRenderer* renderer) override;
private:
    virtual void emit(int num);
private:
    PROPERTY_GETREF(Framework::Utility::Transform, mTransform, Transform);
    PROPERTY_GETREF(Framework::Utility::Timer, mLimitTime, LimitTimer);
    PROPERTY_GETREF(Framework::Utility::Timer, mEmitTimer, EmitTimer);
    PROPERTY_GETREF(Framework::Utility::Range<Framework::Math::Vector3>, mVelocity, VelocityRange);
    PROPERTY(int, mOnceEmitNum, OnceEmitNum);
    PROPERTY(int, mMaxParticleNum, MaxParticleNum);
};