#pragma once

namespace Define {

/**
* @enum TextureType
* @brief テクスチャ種類定義
*/
enum class TextureType {
    Smoke,
};

/**
* @class TextureName
* @brief テクスチャのリソース名定義
*/
class TextureName {
public:
    static const std::string SMOKE;
};

} //Define 