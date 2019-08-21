#pragma once

#include <d3d11.h>
#include <wrl/client.h>
#include "Framework/Graphics/Shader/ShaderInputType.h"

namespace Framework {
namespace Graphics {

class DirectX11GraphicsDevice;

/**
* @enum TextureAddressMode
* @brief テクスチャのUV座標が0～1の範囲外の時の処理方法
*/
enum class TextureAddressMode {
    Wrap, //!< 整数区切りでテクスチャの繰り返し
    Clamp, //!< 0～1にクランプ
};

/**
* @enum TextureFilterMode
* @brief サンプリング時のフィルタリング方法
*/
enum class TextureFilterMode {
    MinMagMipLinear, //!< 拡大縮小、ミップレベルに線形補間を使用
    MinMagMipPoint,
};

/**
* @brief サンプラー
* @detail サンプラーを0～1の範囲外の処理、サンプリング時のフィルタリング方法を選択して作成できます。
それ以上のことをしたい場合はシェーダファイル内で直接記述するか、作成した後のID3D11SamplerStateをコンストラクタで渡してください
*/
class Sampler {
private:
    using SamplerState = Microsoft::WRL::ComPtr<ID3D11SamplerState>;
public:
    /**
    * @brief コンストラクタ
    * @param addressMode UV座標範囲外時の処理方法
    * @param filterMode サンプリング時のフィルタリング方法
    */
    Sampler( TextureAddressMode addressMode, TextureFilterMode filterMode);
    /**
    * @brief コンストラクタ
    * @param sampler サンプラー
    */
    Sampler(const SamplerState& sampler);
    /**
    * @brief デストラクタ
    */
    ~Sampler();
    /**
    * @brief データのセット
    * @param inputType どのシェーダに値を代入するか
    * @param slotNum シェーダの何番にこのテクスチャデータを代入するか
    */
    void setData(ShaderInputType inputType, UINT slotNumber);
private:
    SamplerState mSamplerState; //!< サンプラーステート
};

} //Graphics 
} //Framework 
