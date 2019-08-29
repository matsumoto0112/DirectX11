#pragma once
#include <memory>
#include "Framework/Math/Vector2.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/GraphicsDevice.h"
#include "Framework/Graphics/Light/LightManager.h"

namespace Framework {
namespace ImGUI {
class Manager;
} //ImGUI 
namespace Graphics {
class AlphaBlend;
class RenderTarget;
class Sampler;

/**
* @class RenderingManager
* @brief 描画管理
*/
class RenderingManager {
public:
    /**
    * @brief コンストラクタ
    * @param hWnd ウィンドウハンドル
    * @param screenSize スクリーンの大きさ
    * @param isFullScreen フルスクリーン機動か
    */
    RenderingManager(HWND hWnd, const Math::Vector2& screenSize, bool isFullScreen);
    /**
    * @brief デストラクタ
    */
    ~RenderingManager();
    /**
    * @brief 初期化処理
    * @details デバイスを作った後に初期化処理をしないといけないので別で呼ぶ
    */
    void initialize();
    /**
    * @brief 描画開始
    */
    void drawBegin(const Color4& clearColor);
    /**
    * @brief 描画終了
    */
    void drawEnd();
    /**
    * @brief グラフィックデバイスの取得
    */
    GraphicsDevice* getGraphicsDevice() const { return mGraphicsDevice.get(); }
    /**
    * @brief コンスタントバッファの取得
    */
    ConstantBufferManager* getConstantBufferManager() const { return mConstantBufferManager.get(); }
    /**
    * @brief ライト管理者の取得
    */
    LightManager* getLightManager() const { return mLightManager.get(); }
    /**
    * @brief ImGUI管理者の取得
    */
    ImGUI::Manager* getImGUIManager() const { return mImGUIManager.get(); }
private:
    Math::Vector2 mScreenSize;
    std::unique_ptr<GraphicsDevice> mGraphicsDevice; //!< グラフィックデバイス
    std::unique_ptr<ConstantBufferManager> mConstantBufferManager; //!< コンスタントバッファ管理
    std::unique_ptr<LightManager> mLightManager; //!< ライト管理
    std::unique_ptr<AlphaBlend> mAlphaBlend; //!< アルファブレンド
    std::unique_ptr<RenderTarget> mRenderTarget; //!< レンダーターゲット
    std::unique_ptr<Sampler> mDefaultSampler; //!< サンプラー
    std::unique_ptr<ImGUI::Manager> mImGUIManager; //!< ImGUIの管理
};

} //Graphics 
} //Framework 