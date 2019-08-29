#pragma once
#include <d3d11.h>
#include <vector>
#include "Framework/Math/Rect.h"

namespace Framework {
namespace Graphics {

/**
* @class MultiViewport
* @brief マルチレンダーターゲットに使用するビューポート
*/
class MultiViewport {
public:
    /**
    * @brief コンストラクタ
    */
    MultiViewport(UINT viewportNum, const Math::Rect& rect);
    /**
    * @brief デストラクタ
    */
    ~MultiViewport();
    /**
    * @brief ビューポートをコンテキストにセットする
    */
    void set();
private:
    std::vector<D3D11_VIEWPORT> mViewports; //!< ビューポート配列
};

} //Graphics 
} //Framework 