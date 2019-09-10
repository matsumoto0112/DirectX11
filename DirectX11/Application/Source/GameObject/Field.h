#pragma once
#include <array>

class Collider;
class Collidable3DObject;
class Floor;
class IMainSceneMediator;
class Wall;

/**
* @class Field
* @brief ゲームのフィールド管理クラス
*/
class Field {
public:
    /**
    * @brief コンストラクタ
    * @param mediator メインシーン仲介者
    */
    Field(IMainSceneMediator& mediator);
    /**
    * @brief デストラクタ
    */
    virtual ~Field();
    /**
    * @brief ゲームオブジェクトをフィールド内に押し戻す
    * @param gameObject 処理するゲームオブジェクト
    */
    virtual void pushBackGameObject(Collidable3DObject& gameObject);
    /**
    * @brief ゲームオブジェクトがゲームエリアの範囲外にあるか
    */
    virtual bool isGameObjectOutOfArea(Collidable3DObject& gameObject);
    /**
    * @brief フィールドの更新
    */
    virtual void update();
    /**
    * @brief 壁の描画
    */
    virtual void drawWall();
    /**
    * @brief フィールドの描画処理
    */
    virtual void draw();
private:
    std::array<std::unique_ptr<Wall>, 4> mWalls; //!< 壁
    std::unique_ptr<Floor> mFloor; //!< 床
};