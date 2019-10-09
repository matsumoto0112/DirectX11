#pragma once

#include <memory>
#include "Framework/Graphics/Shader/PixelShader.h"
#include "Framework/Graphics/Shader/VertexShader.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {

/**
* @class Effect
* @brief エフェクトクラス
*/
class Effect {
public:
    /**
    * @brief コンストラクタ
    * @param vertexShader 頂点シェーダー
    * @param pixelShader ピクセルシェーダー
    */
    Effect(std::shared_ptr<VertexShader> vertexShader,
        std::shared_ptr<PixelShader> pixelShader);
    /**
    * @brief デストラクタ
    */
    ~Effect();
    /**
    * @brief シェーダーをコンテキストにセットする
    */
    void set();
private:
    PROPERTY_POINTER(std::shared_ptr<VertexShader>, mVertexShader, VertexShader); //!< 頂点シェーダー
    PROPERTY_POINTER(std::shared_ptr<PixelShader>, mPixelShader, PixelShader); //!< ピクセルシェーダー
};

} //Graphics 
} //Framework