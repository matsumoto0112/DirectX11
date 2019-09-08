#include "SingleShotWeapon.h"

using namespace Framework;

SingleShotWeapon::SingleShotWeapon(const Utility::Transform& transform, IMainSceneMediator& mediator)
    :PlayerWeapon(transform, mediator) {}

SingleShotWeapon::~SingleShotWeapon() {}

void SingleShotWeapon::pullTrigger() {
    mCounter++;
    if (mCounter % 5 == 0) {
        Utility::Transform tr(
            mTransform.getGlobalPostition(),
            mTransform.getGlobalRotate(),
            mTransform.getGlobalScale());
        mMediator.shotBullet(tr);
    }
}
