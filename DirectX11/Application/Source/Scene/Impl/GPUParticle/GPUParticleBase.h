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
* @brief ランダム色パーティクルテストシーン
*/
class GPUParticleBase : public Framework::Scene::SceneBase {
public:
    /**
    * @brief コンストラクタ
    */
    GPUParticleBase();
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
    std::shared_ptr<Framework::Graphics::OrthographicCamera> m2DCamera; //!< カメラ
    std::shared_ptr<Framework::Graphics::PerspectiveCamera> m3DCamera; //!< カメラ
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
    std::unique_ptr<Framework::Graphics::GPUParticle> mGPUParticle; //!< パーティクル
    std::unique_ptr<Framework::Graphics::ConstantBuffer<GlobalData>> mCB; //<! グローバルデータ用コンスタントバッファ
    std::unique_ptr<Framework::Utility::Timer> mTimer;
    GlobalData mGlobal;
    std::shared_ptr<Framework::Graphics::RasterizerState> mPrevRasterizer;
    std::shared_ptr<Framework::Graphics::AlphaBlend> mPrevAlphaBlend;
};