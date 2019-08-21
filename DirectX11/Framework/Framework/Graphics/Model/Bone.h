#pragma once
#include <memory>
#include "Framework/Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {

class Bone {
public:
    Bone(int id, const Math::Matrix4x4& initmat, Math::Matrix4x4* combMatrixArray);
    Bone(int id, Math::Matrix4x4* combMatrixArray);
    Bone(int id);
    ~Bone();
    void setChild(Bone* child) { mFirstChild = child; }
    void setSibling(Bone* sibling) { mSibling = sibling; }
    void updateBoneMatrix(const Math::Matrix4x4& def);
    void setInitMatrix(const Math::Matrix4x4& mat) { mInitMatrix = mat; }
    void setOffsetMatrix(const Math::Matrix4x4& mat) { mOffsetMatrix = mat; }
    //‰Šúp¨‚ğe‚Ìp¨‚©‚ç‚Ì‘Š‘Îp¨‚É’¼‚·
    static void calcRelative(Bone* me, Math::Matrix4x4* parentMatrix);
    static void calcUpdate(Bone* me, Math::Matrix4x4* parentMatrix);
    void inputMatrix(Math::Matrix4x4* result);
public:
    int mID;
    Bone* mFirstChild;
    Bone* mSibling;
    Math::Matrix4x4 mOffsetMatrix;
    Math::Matrix4x4 mInitMatrix;
    Math::Matrix4x4 mBoneMatrix;
    //Math::Matrix4x4* mCombMatrixArray;
};

} //Graphics 
} //Framework 
