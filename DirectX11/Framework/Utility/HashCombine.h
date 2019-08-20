#pragma once

#include <functional>

//参考サイト https://suzulang.com/cpp-unordered_map-my-type/
namespace Framework {
namespace Utility {

/**
* @brief ハッシュ値を統合する
* @param seed 既存のハッシュ値
* @param v 新たにハッシュ値を作成する値
* @return 元のseedとvから作成したハッシュ値を統合した値
*/
template<typename T>
static size_t combineHash(size_t seed, const T& v) {
    //基本型に関するハッシュ生成は標準ライブラリが提供している
    std::hash<T> primitive_type_hash;

    //生成したハッシュを合成する。このコードはboostものを使用する
    seed ^= primitive_type_hash(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}

} //Utility 
} //Framework 
