#pragma once

#include "Framework/Graphics/ConstantBuffer/ConstantBuffer.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferParameterType.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferStruct.h"

namespace Framework {
namespace Graphics {

template <class T>
class ConstantBufferTypeManager;

/**
* @class ConstantBufferManager
* @brief コンスタントバッファ管理者
*/
class ConstantBufferManager {
public:
    /**
    * @brief コンストラクタ
    */
    ConstantBufferManager();
    /**
    * @brief デストラクタ
    */
    ~ConstantBufferManager();
    /**
    * @brief データの転送
    */
    void send();
    /**
    * @brief 行列の設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setMatrix(ConstantBufferParameterType type, const Math::Matrix4x4& value);
    /**
    * @brief Floatの設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setFloat(ConstantBufferParameterType type, float value);
    /**
    * @brief 色の設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setColor(ConstantBufferParameterType type, const Color4& value);
    /**
    * @brief Intの設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setInt(ConstantBufferParameterType type, int value);
    /**
    * @brief Boolの設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setBool(ConstantBufferParameterType type, bool value);
    /**
    * @brief Vector4の設定
    * @param type 転送先
    * @param value 転送するデータ
    */
    void setVector4(ConstantBufferParameterType type, const Math::Vector4& value);
    /**
    * @brief 構造体の設定
    * @tparam T 転送する構造体
    * @param type 転送先
    */
    template <class T>
    void setStruct(const T& value);
    void clearBuffer();
private:
    /**
    * @brief 初期設定
    */
    void setup();
private:
    std::unique_ptr<ConstantBuffer<MVPMatrix3DCBuffer>> mMVP3DCBuffer; //!< 3DMVP行列用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<MVPMatrix2DCBuffer>> mMVP2DCBuffer; //!< 2DMVP行列用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<UVInfoCBuffer>> mUVCBuffer; //!< UV情報用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<ColorCBuffer>> mColorCBuffer; //!< 色用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<LightCBuffer>> mLightCBuffer; //!< ライト用コンスタントバッファ
    std::unique_ptr<ConstantBuffer<LightMatrixCBuffer>> mLightMatrixCBuffer; //!< ライト行列用コンスタントバッファ

    std::unique_ptr<ConstantBufferTypeManager<Math::Matrix4x4>> mMatrixBufferManager; //!< 行列用バッファ転送管理者
    std::unique_ptr<ConstantBufferTypeManager<float>> mFloatBufferManager; //!< Float用バッファ転送管理者
    std::unique_ptr<ConstantBufferTypeManager<Color4>> mColorBufferManager; //!< 色用バッファ転送管理者
    std::unique_ptr<ConstantBufferTypeManager<int>> mIntBufferManager; //!< 整数値用バッファ転送管理者
    std::unique_ptr<ConstantBufferTypeManager<Math::Vector4>> mVector4BufferManager; //!< 4次元ベクトル用バッファ転送管理者
};

template<class T>
inline void ConstantBufferManager::setStruct(const T& value) {
    static_assert(false);
}

} //Graphics 
} //Framework