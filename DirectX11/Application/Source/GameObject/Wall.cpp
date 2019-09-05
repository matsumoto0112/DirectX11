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
}

Wall::Wall(const Utility::Transform& transform, IMainSceneMediator& mediator)
    : GameObject3D(transform, mediator, Define::ModelType::Wall),
    mPlane(transform.getGlobalPostition() + WALL_SCALE * 0.5f, Math::Vector3::RIGHT) {}

Wall::~Wall() {}

void Wall::pushBackGameObject(Collider& collider) {
    float len = 0.0f;
    if (Utility::Collision::obb_plane(collider.getOBB(), mPlane, &len)) {
        Math::Vector3 pos = collider.holder->getTransform().getPosition();
        pos.x += len;
        collider.holder->getTransformPtr()->setPosition(pos);
    }
}

void Wall::draw() {
    GameObject3D::draw();
}
