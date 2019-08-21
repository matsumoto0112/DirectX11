#include "AnimationModel.h"
#include "Framework/Graphics/ConstantBuffer/BoneMatrixCBufferStruct.h"
#include "Framework/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "Framework/Graphics/Model/Animation.h"
#include "Framework/Graphics/Model/Bone.h"

namespace Framework {
namespace Graphics {

AnimationModel::AnimationModel(std::vector<std::unique_ptr<Mesh>> meshes,
    std::vector<std::unique_ptr<Material>> materials,
    std::vector<std::unique_ptr<Bone>> bones,
    std::unique_ptr<Animation> animation)
    :Model(std::move(meshes), std::move(materials)),
    mBones(std::move(bones)), mAnimation(std::move(animation)),
    mCombMatrixArray(mBones.size()) {
    mAnimation->changeAnimation(0);
}

AnimationModel::~AnimationModel() {}

void AnimationModel::update(float delta) {
    mAnimation->update(delta);
}

void AnimationModel::draw(const Utility::Transform& transform) {
    const int size = mBones.size();
    for (int i = 0; i < size; i++) {
        mBones[i]->updateBoneMatrix(mAnimation->getAnimationMatrix(i));
        mBones[i]->inputMatrix(&mData.bone[i]);
    }

    //ConstantBufferManager& cbManager = mRenderingManager.getConstantBufferManager();
    //cbManager.setStruct(mData);
    //Model::draw(transform);
}

} //Graphics 
} //Framework 
