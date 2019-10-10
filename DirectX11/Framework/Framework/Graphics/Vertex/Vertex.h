#pragma once

#include "Framework/Graphics/Color4.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector3.h"
#include "Framework/Math/Vector4.h"

namespace Framework {
namespace Graphics {

struct OnlyPosition {
    Math::Vector4 pos;
};

/**
* @struct BaseVertex2D
* @brief 2D用基本頂点クラス
*/
struct BaseVertex2D {
    Math::Vector4 pos; //!< 頂点座標
    Math::Vector2 uv; //!< UV座標
};

/*
* @struct TextureVertex3D
* @brief 3D頂点
*/
struct TextureVertex3D {
    Math::Vector4 pos; //!< 座標
    Math::Vector3 normal; //!< 法線
    Math::Vector2 uv; //!< UV座標
};

/**
* @struct MeshVertex
* @brief メッシュ頂点
*/
struct MeshVertex {
    Math::Vector4 pos; //!< 座標
    Math::Vector3 normal; //!< 法線
    Math::Vector2 uv; //UV座標
    Color4 color; //!< 頂点カラー
};

/**
* @struct AnimVert
* @brief アニメーション付きメッシュ頂点
*/
struct AnimVert {
    Math::Vector4 pos; //!< 頂点座標
    Math::Vector3 normal; //!< 法線
    Math::Vector2 uv; //!< UV座標
    Color4 color; //!< 頂点カラー
    unsigned int index[4]; //!< ボーン行列インデックス
    float weight[4]; //!< ボーン行列ウェイト
};

} //Graphics 
} //Framework