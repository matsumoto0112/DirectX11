#pragma once
#include <list>
#include "Framework/Graphics/Particle/Particle.h"
#include "Framework/Graphics/Texture/Texture.h"

namespace Framework {
namespace Graphics {
class RenderState;

/**
* @class ParticleEmitter
* @brief �p�[�e�B�N���o�͑��u
*/
class ParticleEmitter {
public:
    /**
    * @brief �R���X�g���N�^
    * @param origin �������ƂȂ�p�[�e�B�N��
    */
    ParticleEmitter(std::shared_ptr<Particle> origin) :mOrigin(origin) { }
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~ParticleEmitter() = default;
    /**
    * @brief ����������
    */
    virtual void init() = 0;
    /**
    * @brief �V�~�����[�g����
    */
    virtual void simulate(float delta) = 0;
    /**
    * @brief �`��
    */
    virtual void draw(RenderState* pipeline) = 0;
    /**
    * @brief ���݂̃p�[�e�B�N���̐����擾
    */
    UINT getParticleNum() const { return static_cast<UINT>(mParticles.size()); }
protected:
    std::shared_ptr<Particle> mOrigin; //!< �������̃p�[�e�B�N��
    std::list<std::unique_ptr<Particle>> mParticles; //!< ���������p�[�e�B�N�����X�g
};

} //Graphics 
} //Framework 
