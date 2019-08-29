#pragma once
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>

namespace Framework {
namespace Graphics {

/**
* @class MultiRenderTarget
* @brief マルチレンダーターゲット
*/
class MultiRenderTarget {
public:
    /**
    * @brief コンストラクタ
    */
    MultiRenderTarget(UINT renderTargetNum);
    /**
    * @brief デストラクタ
    */
    ~MultiRenderTarget();
private:
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView[]> mRTVs;
};

} //Graphics 
} //Framework 