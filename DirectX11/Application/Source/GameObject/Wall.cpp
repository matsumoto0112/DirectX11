#include "Wall.h"
#include "Framework/Graphics/Renderer/3D/Cube.h"
#include "Framework/Utility/Resource/ResourceManager.h"
#include "Framework/Utility/Wrap/OftenUsed.h"
#include "Source/GameObject/IMainSceneMediator.h"
#include "Source/GameObject/Collider.h"
#include "Framework/Utility/Collision.h"

using namespace Framework;

namespace {
static const Math::Vector3 WALL_SCALE = Math::Vector3(1.0f, 5.0f, 10.0f);
static const Math::Vector3 HALF_WALL_SCALE = WALL_SCALE * 0.5f;
}

Wall::Wall(const Utility::Transform& transform, IMainSceneMediator& mediator)
    : GameObject3D(transform, mediator, Define::ModelType::Wall),
    mPlane(transform.getGlobalPostition(),
        Math::Vector3::FORWORD *  transform.getGlobalRotate().toMatrix()) {
    const Math::Vector3 offset(
        HALF_WALL_SCALE.x * mPlane.normal.x,
        HALF_WALL_SCALE.y * mPlane.normal.y,
        HALF_WALL_SCALE.z * mPlane.normal.z);
    mPlane.p += offset;
}

Wall::~Wall() {}

void Wall::pushBackGameObject(Collider& collider) {
    float len = 0.0f;
    if (Utility::Collision::obb_plane(collider.getOBB(), mPlane, &len)) {
        Math::Vector3 pos = collider.holder->getTransform().getPosition();
        pos += len * mPlane.normal;
        collider.holder->getTransformPtr()->setPosition(pos);
    }
}

void Wall::draw() {
    GameObject3D::draw();
}
