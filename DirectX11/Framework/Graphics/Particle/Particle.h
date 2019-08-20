#pragma once
#include <memory>
#include "Graphics/Sprite/Sprite3D.h"
#include "Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Particle
* @brief �p�[�e�B�N��1���q�Ǘ�
*/
class Particle {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Particle(std::shared_ptr<Sprite3D> sprite);
    /**
    * @brief �f�X�g���N�^
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
