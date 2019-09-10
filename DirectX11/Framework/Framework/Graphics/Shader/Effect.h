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
public:
    /**
    * @brief 頂点シェーダーを取得する
    */
    std::shared_ptr<VertexShader> getVertexShader() const { return mVertexShader; }
    /**
    * @brief 頂点シェーダーを設定する
    */
    void setVertexShader(std::shared_ptr<VertexShader> vshader) { mVertexShader = vshader; }
    /**
    * @brief ピクセルシェーダーを取得する
    */
    std::shared_ptr<PixelShader> getPixelShader() const { return mPixelShader; }
    /**
    * @brief ピクセルシェーダーを設定する
    */
    void setPixelShader(std::shared_ptr<PixelShader> pshader) { mPixelShader = pshader; }
private:
    std::shared_ptr<VertexShader> mVertexShader; //!< 頂点シェーダー
    std::shared_ptr<PixelShader> mPixelShader; //!< ピクセルシェーダー
};

} //Graphics 
} //Framework