#include "Wall.h"
#include "Framework/Graphics/Renderer/3D/Cube.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Source/GameObject/IMainSceneMediator.h"
#include "Source/GameObject/Collider.h"
#include "Framework/Utility/Collision.h"

using namespace Framework;

namespace {
static const float WALL_HALF_WIDTH = 0.5f;
}

Wall::Wall(const Utility::Transform& transform, IMainSceneMediator& mediator)
    : GameObject3D(transform, mediator, Define::ModelType::Wall),
    mPlane(transform.getGlobalPostition(),
        Math::Vector3::FORWORD *  transform.getGlobalRotate().toMatrix()) {
    //•Ç•½–Ê‚ÌˆÊ’u‚ð“à‘¤‚É‚¸‚ç‚·
    const Math::Vector3 offset(
        WALL_HALF_WIDTH * mPlane.normal.x,
        WALL_HALF_WIDTH * mPlane.normal.y,
        WALL_HALF_WIDTH * mPlane.normal.z);
    mPlane.p += offset;
}

Wall::~Wall() {}

void Wall::pushBackGameObject(Collidable3DObject& gameObject) {
    float len = 0.0f;
    if (Utility::Collision::obb_plane(gameObject.getColliderPtr()->getOBB(), mPlane, &len)) {
        Math::Vector3 pos = gameObject.getTransform().getPosition();
        pos += len * mPlane.normal;
        gameObject.getTransformPtr()->setPosition(pos);
    }
}

bool Wall::isHitGameObject(Collidable3DObject& gameObject) {
    return Utility::Collision::obb_plane(gameObject.getColliderPtr()->getOBB(), mPlane, nullptr);
}

void Wall::draw() {
    GameObject3D::draw();
}
