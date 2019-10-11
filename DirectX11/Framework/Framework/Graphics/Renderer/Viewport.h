#pragma once
#include <d3d11.h>
#include "Framework/Math/Rect.h"

namespace Framework {
namespace Graphics {

/**
* @class Viewport
* @brief ビューポート
*/
class Viewport {
public:
    /**
    * @brief コンストラクタ
    * @param rect ビューポートの範囲
    */
    Viewport(const Math::Rect& rect);
    /**
    * @brief デストラクタ
    */
    ~Viewport();
    /**
    * @brief 設定する
    */
    void set();
    /**
    * @brief コンテキストの状態をクリアする
    */
    void clearState();
private:
    D3D11_VIEWPORT mViewport;
};

} //Graphics 
} //Framework 
