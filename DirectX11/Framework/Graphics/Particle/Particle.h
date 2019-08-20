#pragma once
#include <memory>
#include "Graphics/Sprite/Sprite3D.h"
#include "Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Particle
* @brief パーティクル1粒子管理
*/
class Particle {
public:
    /**
    * @brief コンストラクタ
    */
    Particle(std::shared_ptr<Sprite3D> sprite);
    /**
    * @brief デストラクタ
    */
    virtual ~Particle();
    virtual void simulate(float delta);
    virtual void draw();
    std::unique_ptr<Particle> clone();
private:
    std::shared_ptr<Sprite3D> mSprite;
private:
    PROPERTY(bool, mIsAlive, Alive);
    PROPERTY(Math::Vector3, mPosition, Position);
    PROPERTY(Math::Vector3, mVelocity, Velocity);
    PROPERTY(float, mLifeTime, LifeTime);
};

} //Graphics 
} //Framework 
