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
    Player,
    Bullet,
    Enemy,
    Item,
};

/**
* @class ModelName
* @brief モデルのリソース名定義
*/
class ModelName {
public:
    static const std::string PLANE;
    static const std::string WALL;
    static const std::string PLAYER;
    static const std::string BULLET;
    static const std::string ENEMY;
    static const std::string ITEM;
};

} //Define 