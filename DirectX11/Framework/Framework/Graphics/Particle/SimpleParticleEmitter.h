#pragma once
#include "Framework/Graphics/Particle/ParticleEmitter.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class SimpleParticleEmitter
* @brief シンプルパーティクル生成
*/
class SimpleParticleEmitter : public ParticleEmitter {
public:
    /**
    * @brief コンストラクタ
    */
    SimpleParticleEmitter(std::shared_ptr<Particle> origin);
    /**
    * @brief デストラクタ
    */
    virtual ~SimpleParticleEmitter();
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
    virtual void draw(IRenderer* renderer) override;
private:
    PROPERTY(bool, mIsAlive, IsAlive); //!< 生存しているか
    PROPERTY(float, mDuration, Duration); //!< 生存時間
    PROPERTY(float, mEmitInterval, EmitInterval); //!< 発生間隔
    PROPERTY(float, mIntervalTimer, IntervalTimer); //!< パーティクルタイマー
    PROPERTY(int, mOnceEmitNum, OnceEmitNum); //!< 一回で発生する量
    PROPERTY(float, mRemainingTime, RemainingTime); //!< パーティクルの残り生存時間
};

} //Graphics 
} //Framework 
