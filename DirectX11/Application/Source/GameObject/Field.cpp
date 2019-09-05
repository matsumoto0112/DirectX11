#include "Field.h"
#include "Source/GameObject/Wall.h"
#include "Source/GameObject/Floor.h"

using namespace Framework;

Field::Field(IMainSceneMediator& mediator) {
    mWalls[0] = std::make_unique<Wall>(Utility::Transform(
        Math::Vector3(-10.0f, 0.0f, 0.0f),
        Math::Quaternion::createRotateAboutY(90.0f),
        Math::Vector3(1.0f, 1.0f, 1.0f)),
        mediator);
    mWalls[1] = std::make_unique<Wall>(Utility::Transform(
        Math::Vector3(10.0f, 0.0f, 0.0f),
        Math::Quaternion::createRotateAboutY(-90.0f),
        Math::Vector3(1.0f, 1.0f, 1.0f)),
        mediator);

    mFloor = std::make_unique<Floor>(Utility::Transform(
        Math::Vector3(0, 0, 0),
        Math::Quaternion::IDENTITY,
        Math::Vector3(5, 1, 5)),
        mediator);
}

Field::~Field() {}

void Field::pushBackGameObject(Collider& collider) {
    for (auto&& wall : mWalls) {
        if (wall)
            wall->pushBackGameObject(collider);
    }
}

void Field::update() {}

void Field::draw() {
    mFloor->draw();
    for (auto&& wall : mWalls) {
        if (wall)
            wall->draw();
    }
    mWalls[0]->draw();
}
