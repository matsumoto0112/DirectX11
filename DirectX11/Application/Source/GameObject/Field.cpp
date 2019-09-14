#include "Field.h"
#include "Source/GameObject/Wall.h"
#include "Source/GameObject/Floor.h"
#include "Framework/Graphics/Renderer/ZTexCreater.h"

using namespace Framework;
namespace {
const float POS_OFFSET = 25.0f;
}

Field::Field(IMainSceneMediator& mediator) {
    for (int i = 0; i < 4; i++) {
        float rot = i * 90.0f;
        Math::Vector3 pos(0, 0, 0);
        switch (i) {
        case 0:
            pos.z = -POS_OFFSET;
            break;
        case 1:
            pos.x = -POS_OFFSET;
            break;
        case 2:
            pos.z = POS_OFFSET;
            break;
        case 3:
            pos.x = POS_OFFSET;
            break;
        }
        mWalls[i] = std::make_unique<Wall>(Utility::Transform(
            pos,
            Math::Quaternion::createRotateAboutY(rot),
            Math::Vector3(5.0f, 10.0f, 1.0f)),
            mediator);
    }

    mFloor = std::make_unique<Floor>(Utility::Transform(
        Math::Vector3(0, 0, 0),
        Math::Quaternion::IDENTITY,
        Math::Vector3(5, 1, 5)),
        mediator);

    for (auto&& wall : mWalls) {
        wall->initialize();
    }
    mFloor->initialize();
}

Field::~Field() {}

void Field::pushBackGameObject(Collidable3DObject& gameObject) {
    for (auto&& wall : mWalls) {
        wall->pushBackGameObject(gameObject);
    }
}

bool Field::isGameObjectOutOfArea(Collidable3DObject& gameObject) {
    for (auto&& wall : mWalls) {
        if (wall->isHitGameObject(gameObject)) {
            return true;
        }
    }
    return false;
}

void Field::update() {}

void Field::drawWall(Framework::Graphics::IRenderer* renderer) {
    for (auto&& wall : mWalls) {
        wall->draw(renderer);
    }
}

void Field::draw(Framework::Graphics::IRenderer* renderer) {
    //rendererがZ値を出力するレンダラーの場合、壁のみを描画する
    if (dynamic_cast<Framework::Graphics::ZTexCreater*>(renderer) != nullptr) {
        drawWall(renderer);
    }
    else {
        mFloor->draw(renderer);
        drawWall(renderer);
    }
}
