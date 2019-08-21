#pragma once
#include <list>
#include "Framework/Graphics/Particle/Particle.h"
#include "Framework/Graphics/Texture/Texture.h"

namespace Framework {
namespace Graphics {


/**
* @class ParticleEmitter
* @brief パーティクル出力装置
*/
class ParticleEmitter {
public:
    /**
    * @brief コンストラクタ
    */
    ParticleEmitter(std::shared_ptr<Particle> origin) :mOrigin(origin) {}
    /**
    * @brief デストラクタ
    */
    virtual ~ParticleEmitter() = default;
    virtual void simulate(float delta) = 0;
    virtual void draw() = 0;
protected:
    std::shared_ptr<Particle> mOrigin;
    std::list<std::unique_ptr<Particle>> mParticles;
};

} //Graphics 
} //Framework 
