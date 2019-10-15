#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"

namespace Framework {
namespace Graphics {
class AlphaBlend;
class OrthographicCamera;
class PerspectiveCamera;
class GPUParticle;
class RasterizerState;
template <class T>
class ConstantBuffer;
} //Graphics 
namespace Utility {
class Timer;
} //Utility 
} //Framework 

/**
* @class RandomColorParticle
* @brief �����_���F�p�[�e�B�N���e�X�g�V�[��
*/
class GPUParticleBase : public Framework::Scene::SceneBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    GPUParticleBase();
    /**
    * @brief �f�X�g���N�^
    */
    ~GPUParticleBase();
    /**
    * @brief �V�[���ǂݍ��ݏ���
    */
    virtual void load(Framework::Scene::Collecter& collecter) override;
    /**
    * @brief �X�V
    */
    virtual void update() override;
    /**
    * @brief �V�[���I�������𖞂����Ă��邩
    */
    virtual bool isEndScene() const override;
    /**
    * @brief �`��
    */
    virtual void draw(Framework::Graphics::IRenderer* pipeline) override;
    /**
    * @brief �I������
    */
    virtual void unload() override;
    /**
    * @brief ���̃V�[��
    */
    virtual Framework::Define::SceneType next() override;
protected:
    std::shared_ptr<Framework::Graphics::OrthographicCamera> m2DCamera; //!< �J����
    std::shared_ptr<Framework::Graphics::PerspectiveCamera> m3DCamera; //!< �J����
    static constexpr int THREAD_X = 16, THREAD_Y = 4;
    static constexpr int DISPATCH_X = 1, DISPATCH_Y = 8;
    static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
    static constexpr int RANDOM_MAX = 65535;

    struct Blackhole {
        Framework::Math::Vector3 position;
        float radius;
        float theta;
        Framework::Graphics::Color4 color;
    };

    struct GlobalData {
        int emit;
        float time;
        float deltaTime;
        float dummy[1];
    };
    std::unique_ptr<Framework::Graphics::GPUParticle> mGPUParticle; //!< �p�[�e�B�N��
    std::unique_ptr<Framework::Graphics::ConstantBuffer<GlobalData>> mCB; //<! �O���[�o���f�[�^�p�R���X�^���g�o�b�t�@
    std::unique_ptr<Framework::Utility::Timer> mTimer;
    GlobalData mGlobal;
    std::shared_ptr<Framework::Graphics::RasterizerState> mPrevRasterizer;
    std::shared_ptr<Framework::Graphics::AlphaBlend> mPrevAlphaBlend;
};