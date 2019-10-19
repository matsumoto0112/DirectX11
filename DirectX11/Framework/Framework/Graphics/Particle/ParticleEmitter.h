#pragma once
#include <list>
#include "Framework/Graphics/Particle/Particle.h"
#include "Framework/Graphics/Texture/Texture.h"

namespace Framework {
namespace Graphics {
class RenderState;

/**
* @class ParticleEmitter
* @brief パーティクル出力装置
*/
class ParticleEmitter {
public:
    /**
    * @brief コンストラクタ
    * @param origin 複製元となるパーティクル
    */
    ParticleEmitter(std::shared_ptr<Particle> origin) :mOrigin(origin) { }
    /**
    * @brief デストラクタ
    */
    virtual ~ParticleEmitter() = default;
    /**
    * @brief 初期化処理
    */
    virtual void init() = 0;
    /**
    * @brief シミュレートする
    */
    virtual void simulate(float delta) = 0;
    /**
    * @brief 描画
    */
    virtual void draw(RenderState* pipeline) = 0;
    /**
    * @brief 現在のパーティクルの数を取得
    */
    UINT getParticleNum() const { return static_cast<UINT>(mParticles.size()); }
protected:
    std::shared_ptr<Particle> mOrigin; //!< 複製元のパーティクル
    std::list<std::unique_ptr<Particle>> mParticles; //!< 発生したパーティクルリスト
};

} //Graphics 
} //Framework 
