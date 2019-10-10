#pragma once

namespace Framework {
namespace Graphics {

/**
* @class IDrawable
* @brief 描画可能オブジェクト
*/
class IDrawable {
public:
    /**
    * @brief デストラクタ
    */
    virtual ~IDrawable() = default;
    /**
    * @brief 描画処理
    */
    virtual void draw() = 0;
};

} //Graphics 
} //Framework 