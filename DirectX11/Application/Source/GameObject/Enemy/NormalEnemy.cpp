#include "NormalEnemy.h"
#include "Source/GameObject/Player.h"
#include "Framework/Utility/Time.h"
#include "Source/GameObject/GameObjectUtil.h"

using namespace Framework;

NormalEnemy::NormalEnemy(const Utility::Transform& transform, const Parameter& parameter, IMainSceneMediator& mediator)
    :Enemy(transform, parameter.color, mediator),
    mMoveSpeed(parameter.moveSpeed) {}

NormalEnemy::~NormalEnemy() {}

void NormalEnemy::update() {    //ƒvƒŒƒCƒ„[‚Ì•ûŒü‚ðŒü‚­
    Player* player = mMediator.getPlayer();
    mTransform.lookat(player->getTransform().getGlobalPostition());

    Math::Vector3 movement = GameObjectUtil::calcurateForwordVector(mTransform) * mMoveSpeed * Utility::Time::getInstance().getDeltaTime();
    Math::Vector3 newPos = mTransform.getPosition() + movement;
    mTransform.setPosition(newPos);
}
