#pragma once

namespace Framework {
namespace Graphics {

/**
* @class RasterizerState
* @brief ラスタライザ設定
*/
class RasterizerState {
public:
    /**
    * @brief コンストラクタ
    */
    RasterizerState(const D3D11_RASTERIZER_DESC* desc);
    /**
    * @brief デストラクタ
    */
    ~RasterizerState();
    /**
    * @brief ラスタライザをコンテキストにセットする
    */
    void set();
    /**
    * @brief コンテキストの状態をクリアする
    */
    void clearState();
private:
    ComPtr<ID3D11RasterizerState> mRasterizer;
};

} //Graphics 
} //Framework 