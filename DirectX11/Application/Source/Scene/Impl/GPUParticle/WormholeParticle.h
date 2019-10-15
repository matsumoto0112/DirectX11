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
* @class WormholeParticle
*/
class WormholeParticle : public Framework::Scene::SceneBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    WormholeParticle();
    /**
    * @brief �f�X�g���N�^
    */
    ~WormholeParticle();
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
private:
    std::shared_ptr<Framework::Graphics::OrthographicCamera> m2DCamera; //!< �J����
    std::shared_ptr<Framework::Graphics::PerspectiveCamera> m3DCamera; //!< �J����
    static constexpr int THREAD_X = 32, THREAD_Y = 32;
    static constexpr int DISPATCH_X = 1, DISPATCH_Y = 1;
    static constexpr int COUNT = THREAD_X * THREAD_Y * DISPATCH_X * DISPATCH_Y;
    static constexpr int RANDOM_MAX = 65535;

    struct Particle {
        float lifeTime;
        float speed;
        Framework::Math::Vector3 position;
        Framework::Math::Vector3 velocity;
        Framework::Graphics::Color4 color;
    };


    struct GlobalData {
        int emit;
        float time;
        float deltaTime;
        float dummy[1];
    };
    std::unique_ptr<Framework::Utility::Timer> mTimer; //!< �p�[�e�B�N���^�C�}�[
    std::unique_ptr<Framework::Graphics::ConstantBuffer<GlobalData>> mGlobalDataCB; //<! �O���[�o���f�[�^�p�R���X�^���g�o�b�t�@
    GlobalData mGlobal;
    std::shared_ptr<Framework::Graphics::RasterizerState> mPrevRasterizer; //!< �O�V�[���̃��X�^���C�U�̏��
    std::shared_ptr<Framework::Graphics::AlphaBlend> mPrevAlphaBlend; //!< �O�V�[���̃A���t�@�u�����h�̏��
};