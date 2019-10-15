#pragma once
#include <memory>
#include "Framework/Scene/SceneBase.h"
#include "Framework/Graphics/Shader/ComputeShader.h"

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

struct GPUParticleInfo : public Framework::Graphics::ComputeShader::Info {
    GPUParticleInfo(const Framework::Graphics::ComputeShader::Info& info)
        :Framework::Graphics::ComputeShader::Info{ info }{}
public:
    UINT COUNT() {
        return threadX * threadY * threadZ * dispatchX * dispatchY * dispatchZ;
    }
};

struct GlobalData {
    int emit;
    float time;
    float deltaTime;
    float dummy[1];
};

/**
* @class RandomColorParticle
* @brief �����_���F�p�[�e�B�N���e�X�g�V�[��
*/
class GPUParticleBase : public Framework::Scene::SceneBase {
public:
    /**
    * @brief �R���X�g���N�^
    */
    GPUParticleBase(const GPUParticleInfo& info, const Framework::Math::ViewInfo& viewInfo);
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
    std::vector<float> createRandomTable() const;
protected:
    static constexpr int RANDOM_MAX = 65535;
    std::shared_ptr<Framework::Graphics::OrthographicCamera> m2DCamera; //!< �J����
    std::shared_ptr<Framework::Graphics::PerspectiveCamera> m3DCamera; //!< �J����
    GPUParticleInfo mInfo;
    std::vector<std::unique_ptr<Framework::Graphics::GPUParticle>> mGPUParticle; //!< �p�[�e�B�N��
    std::unique_ptr<Framework::Graphics::ConstantBuffer<GlobalData>> mGlobalDataCB; //<! �O���[�o���f�[�^�p�R���X�^���g�o�b�t�@
    GlobalData mGlobal;
    std::shared_ptr<Framework::Graphics::RasterizerState> mPrevRasterizer; //!< �O�V�[���̃��X�^���C�U�̏��
    std::shared_ptr<Framework::Graphics::AlphaBlend> mPrevAlphaBlend; //!< �O�V�[���̃A���t�@�u�����h�̏��
    std::unique_ptr<Framework::ImGUI::Window> mWindow;
};