#pragma once
#include "Framework/Graphics/Model/Model.h"

namespace Framework {
namespace Graphics {

class Bone;
class Animation;
struct BoneMatrixCBufferStruct;

class AnimationModel : public Model {
public:
    AnimationModel(std::vector<std::unique_ptr<Mesh>> meshes,
        std::vector<std::unique_ptr<Material>> materials,
        std::vector<std::unique_ptr<Bone>> bones,
        std::unique_ptr<Animation> animation);
    ~AnimationModel();
    void update(float delta);
    virtual void draw(const Utility::Transform& transform) override;
private:
    std::vector<std::unique_ptr<Bone>> mBones;
    std::unique_ptr<Animation> mAnimation;
    std::vector<Math::Matrix4x4> mCombMatrixArray;
    BoneMatrixCBufferStruct mData;
};

} //Graphics 
} //Framework 
