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
* @brief ランダム色パーティクルテストシーン
*/
class GPUParticleBase : public Framework::Scene::SceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    GPUParticleBase(const GPUParticleInfo& info, const Framework::Math::ViewInfo& viewInfo);
    /**
    * @brief デストラクタ
    */
    ~GPUParticleBase();
    /**
    * @brief シーン読み込み処理
    */
    virtual void load(Framework::Scene::Collecter& collecter) override;
    /**
    * @brief 更新
    */
    virtual void update() override;
    /**
    * @brief シーン終了条件を満たしているか
    */
    virtual bool isEndScene() const override;
    /**
    * @brief 描画
    */
    virtual void draw(Framework::Graphics::IRenderer* pipeline) override;
    /**
    * @brief 終了処理
    */
    virtual void unload() override;
    /**
    * @brief 次のシーン
    */
    virtual Framework::Define::SceneType next() override;
protected:
    std::vector<float> createRandomTable() const;
protected:
    static constexpr int RANDOM_MAX = 65535;
    std::shared_ptr<Framework::Graphics::OrthographicCamera> m2DCamera; //!< カメラ
    std::shared_ptr<Framework::Graphics::PerspectiveCamera> m3DCamera; //!< カメラ
    GPUParticleInfo mInfo;
    std::vector<std::unique_ptr<Framework::Graphics::GPUParticle>> mGPUParticle; //!< パーティクル
    std::unique_ptr<Framework::Graphics::ConstantBuffer<GlobalData>> mGlobalDataCB; //<! グローバルデータ用コンスタントバッファ
    GlobalData mGlobal;
    std::shared_ptr<Framework::Graphics::RasterizerState> mPrevRasterizer; //!< 前シーンのラスタライザの状態
    std::shared_ptr<Framework::Graphics::AlphaBlend> mPrevAlphaBlend; //!< 前シーンのアルファブレンドの状態
    std::unique_ptr<Framework::ImGUI::Window> mWindow;
};