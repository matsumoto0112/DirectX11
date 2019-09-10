#include "Enemy.h"
#include "Framework/Utility/Time.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Source/GameObject/Bullet/Bullet.h"
#include "Source/GameObject/DebugMacro.h"
#include "Source/GameObject/Player.h"

using namespace Framework;

Enemy::Enemy(const Utility::Transform& transform,
    const Graphics::Color4& enemyColor,
    IMainSceneMediator& mediator)
    : Collidable3DObject(transform, mediator, Define::ModelType::Enemy),
    mColor(enemyColor) {}


Enemy::~Enemy() {}

void Enemy::initialize() {
    Collidable3DObject::initialize();
}

void Enemy::dispatch(Collidable3DObject* other) {
    other->hit(this);
}

void Enemy::hit(Player* other) {
    mIsAlive = false;
}

void Enemy::hit(Bullet* other) {
    mIsAlive = false;
}

void Enemy::draw(Graphics::IRenderer* renderer) {
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, mColor);
    Collidable3DObject::draw(renderer);
    Utility::getConstantBufferManager()->setColor(Graphics::ConstantBufferParameterType::Color, Graphics::Color4::WHITE);
}

std::unique_ptr<Collider> Enemy::createCollider() {
    const Math::Vector3 scale(1.75f, 2.0f, 1.5f);

    Utility::Transform transform(
        Math::Vector3(0.0f, 1.0f, 0.05f),
        Math::Quaternion::IDENTITY,
        scale
    );
    transform.setParent(&mTransform);
    return std::make_unique<Collider>(transform, this);
}

