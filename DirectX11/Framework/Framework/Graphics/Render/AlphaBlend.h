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
    AlphaBlend(const D3D11_BLEND_DESC& blendDesc);
    /**
    * @brief デストラクタ
    */
    ~AlphaBlend();
    /**
    * @brief アルファブレンドをコンテキストに設定する
    */
    void set();
private:
    Microsoft::WRL::ComPtr<ID3D11BlendState> mAlphaBlend;
};

} //Graphics 
} //Framework 