#pragma once
#include <string>
namespace Define {

/**
* @enum ModelTYpe
* @brief モデルの種類定義
*/
enum class ModelType {
    Plane,
    Wall,
    Red,
    Green,
    Blue,
    Player,
};

/**
* @class ModelName
* @brief モデルのリソース名定義
*/
class ModelName {
public:
    static const std::string PLANE;
    static const std::string WALL;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string BLUE;
    static const std::string PLAYER;
};

} //Define 