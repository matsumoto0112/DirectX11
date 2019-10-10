#pragma once

namespace Framework {
namespace Graphics {

/**
* @enum PrimitiveTopology
* @brief プリミティブトポロジーの種類
*/
enum class PrimitiveTopology {
    LineList, //!< ラインリスト
    TriangleList, //!< 三角形リスト
    TriangleStrip, //!< 三角形ストリップ
    NONE,
};

} //Graphics 
} //Framework 
