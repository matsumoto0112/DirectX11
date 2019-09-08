#include "NormalEnemy.h"
#include "Source/GameObject/Player.h"
#include "Framework/Utility/Time.h"

using namespace Framework;

NormalEnemy::NormalEnemy(const Utility::Transform& transform, const Parameter& parameter, IMainSceneMediator& mediator)
    :Enemy(transform, parameter.color, mediator),
    mMoveSpeed(parameter.moveSpeed) {}

NormalEnemy::~NormalEnemy() {}

void NormalEnemy::update() {    //ƒvƒŒƒCƒ„[‚Ì•ûŒü‚ðŒü‚­
    Player* player = mMediator.getPlayer();
    mTransform.lookat(player->getTransform().getGlobalPostition());

    Math::Quaternion q(0, 0, 1, 0);
    Math::Quaternion r = Math::Quaternion::conjugate(mTransform.getRotate()) * q * mTransform.getRotate();
    Math::Vector3 v(r.x, r.y, r.z);
    v.normalize();
    Math::Vector3 newPos = mTransform.getPosition() + v * mMoveSpeed * Utility::Time::getInstance().deltaTime;
    mTransform.setPosition(newPos);
}
