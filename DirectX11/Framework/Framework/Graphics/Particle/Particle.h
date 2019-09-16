#pragma once
#include <memory>
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class IRenderer;

/**
* @class Particle
* @brief �p�[�e�B�N��1���q�Ǘ�
*/
class Particle {
public:
    /**
    * @brief �R���X�g���N�^
    * @param �g�p����X�v���C�g
    */
    Particle(std::shared_ptr<Sprite3D> sprite);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Particle();
    /**
    * @brief ����������
    */
    virtual void init(Particle* origin);
    /**
    * @brief �V�~�����[�g����
    */
    virtual void simulate(float delta);
    /**
    * @brief �`��
    */
    virtual void draw(IRenderer* renderer);
    /**
    * @brief ��������
    */
    std::unique_ptr<Particle> clone();
private:
    PROPERTY(bool, mIsAlive, IsAlive); //!< �������Ă��邩
    PROPERTY_POINTER(std::shared_ptr<Sprite3D>, mSprite, Sprite); //!< �g���Ă���X�v���C�g
    PROPERTY(Math::Vector3, mPosition, Position); //!< ���W
    PROPERTY(Math::Vector3, mVelocity, Velocity); //!< ���x
    PROPERTY(float, mLifeTime, LifeTime); //!< ��������
};

} //Graphics 
} //Framework 
