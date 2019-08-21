#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include "Framework/Graphics/ConstantBuffer/ConstantBufferParameterType.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Graphics {

/**
* @class ConstantBufferTypeManager
* @brief コンスタントバッファの型の種類ごとの管理者
バッファへの転送の管理をする
* @tparam T 扱う型
*/
template <class T>
class ConstantBufferTypeManager {
private:
    using Func = std::function<void(const T&)>;
public:
    /**
    * @brief コンストラクタ
    */
    ConstantBufferTypeManager();
    /**
    * @brief デストラクタ
    */
    ~ConstantBufferTypeManager();
    /**
    * @brief 転送する関数の追加
    * @param type 転送するパラメータの種類
    * @param send 転送関数
    */
    void add(ConstantBufferParameterType type, Func send);
    /**
    * @brief バッファにデータを転送する
    * @param type 転送するパラメータの種類
    * @param value 転送するデータ
    */
    void set(ConstantBufferParameterType type, const T& value);
private:
    std::unordered_map<ConstantBufferParameterType, Func> mSendFuncs; //!< 転送関数のマップ
};

template<class T>
inline ConstantBufferTypeManager<T>::ConstantBufferTypeManager() {}

template<class T>
inline ConstantBufferTypeManager<T>::~ConstantBufferTypeManager() {
    mSendFuncs.clear();
}

template<class T>
inline void ConstantBufferTypeManager<T>::add(ConstantBufferParameterType type, Func f) {
    mSendFuncs[type] = f;
}

template<class T>
inline void ConstantBufferTypeManager<T>::set(ConstantBufferParameterType type, const T& value) {
    MY_ASSERTION(mSendFuncs.find(type) != mSendFuncs.end(),
        "未登録のSetが呼ばれました。");
    mSendFuncs[type](value);
}

} //Graphics 
} //Framework
