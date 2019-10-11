#pragma once
#include <array>
#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @class AlphaBlend
* @brief アルファブレンド
*/
class AlphaBlend {
public:
    /**
    * @brief コンストラクタ
    */
    AlphaBlend(const D3D11_BLEND_DESC& desc);
    /**
    * @brief デストラクタ
    */
    ~AlphaBlend();
    /**
    * @brief アルファブレンドをコンテキストに設定する
    */
    void set();
    /**
    * @brief コンテキストの状態をクリアする
    */
    void clearState();
    /**
    * @brief 現在のブレンドステートを取得する
    */
    D3D11_BLEND_DESC getCurrentBlendStateDesc() const;
    /**
    * @brief ブレンドステートを設定する
    */
    void setBlendStateFromDesc(const D3D11_BLEND_DESC& desc);
private:
    Microsoft::WRL::ComPtr<ID3D11BlendState> mAlphaBlend; //!< ブレンドステート
};

} //Graphics 
} //Framework 