#pragma once
#include <array>

class Floor;
class IMainSceneMediator;
class Wall;
class Collider;

/**
* @class Field
* @brief ゲームのフィールド管理クラス
*/
class Field {
public:
    /**
    * @brief コンストラクタ
    */
    Field(IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    virtual ~Field();
    virtual void pushBackGameObject(Collider& collider);
    virtual void update();
    virtual void draw();
private:
    std::array<std::unique_ptr<Wall>, 4> mWalls;
    std::unique_ptr<Floor> mFloor;
};