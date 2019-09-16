#pragma once
#include <memory>
#include "Framework/Graphics/Sprite/Sprite3D.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class IRenderer;

/**
* @class Particle
* @brief パーティクル1粒子管理
*/
class Particle {
public:
    /**
    * @brief コンストラクタ
    * @param 使用するスプライト
    */
    Particle(std::shared_ptr<Sprite3D> sprite);
    /**
    * @brief デストラクタ
    */
    virtual ~Particle();
    /**
    * @brief 初期化処理
    */
    virtual void init(Particle* origin);
    /**
    * @brief シミュレートする
    */
    virtual void simulate(float delta);
    /**
    * @brief 描画
    */
    virtual void draw(IRenderer* renderer);
    /**
    * @brief 複製する
    */
    std::unique_ptr<Particle> clone();
private:
    PROPERTY(bool, mIsAlive, IsAlive); //!< 生存しているか
    PROPERTY_POINTER(std::shared_ptr<Sprite3D>, mSprite, Sprite); //!< 使っているスプライト
    PROPERTY(Math::Vector3, mPosition, Position); //!< 座標
    PROPERTY(Math::Vector3, mVelocity, Velocity); //!< 速度
    PROPERTY(float, mLifeTime, LifeTime); //!< 生存時間
};

} //Graphics 
} //Framework 
