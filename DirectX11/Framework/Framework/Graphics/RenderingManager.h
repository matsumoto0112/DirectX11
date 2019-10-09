#pragma once
#include <memory>
#include "Framework/Math/Vector2.h"
#include "Framework/Graphics/Camera/CameraManager.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/GraphicsDevice.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace ImGUI {
class Manager;
} //ImGUI 
namespace Graphics {
class AlphaBlend;
class RenderTarget;
class Sampler;
class IRenderer;

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
    * @param isFullScreen フルスクリーン起動か
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
    * @return バックバッファの描画デバイス
    * @details 描画時はこのレンダラーを通すと出力される
    */
    IRenderer* drawBegin();
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
    * @brief カメラ管理者の取得
    */
    CameraManager* getCameraManager() const { return mCameraManager.get(); }
    /**
    * @brief ImGUI管理者の取得
    */
    ImGUI::Manager* getImGUIManager() const { return mImGUIManager.get(); }
private:
    Math::Vector2 mScreenSize;
    std::unique_ptr<IRenderer> mBackBufferRenderer; //!< バックバッファ描画デバイス
    std::unique_ptr<GraphicsDevice> mGraphicsDevice; //!< グラフィックデバイス
    std::unique_ptr<ConstantBufferManager> mConstantBufferManager; //!< コンスタントバッファ管理
    std::unique_ptr<CameraManager> mCameraManager; //!< カメラ管理者
    std::unique_ptr<AlphaBlend> mAlphaBlend; //!< アルファブレンド
    std::unique_ptr<Sampler> mDefaultSampler; //!< サンプラー
    std::unique_ptr<ImGUI::Manager> mImGUIManager; //!< ImGUIの管理
};

} //Graphics 
} //Framework 