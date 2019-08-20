#include "Bone.h"

namespace Framework {
namespace Graphics {
Bone::Bone(int id, const Math::Matrix4x4& initMat, Math::Matrix4x4* combMatrixArray)
    :mID(id), mInitMatrix(initMat)/*, mCombMatrixArray(combMatrixArray) */ {}

Bone::Bone(int id, Math::Matrix4x4* combMatrixArray)
    : mID(id)/*, mCombMatrixArray(combMatrixArray)*/ {
    mOffsetMatrix.loadIdentity();
    mBoneMatrix.loadIdentity();
}

Bone::Bone(int id)
    : mID(id) {}

Bone::~Bone() {}

void Bone::updateBoneMatrix(const Math::Matrix4x4& def) {
    mBoneMatrix = def /** mInitMatrix*/;
}

void Bone::calcRelative(Bone* me, Math::Matrix4x4* parentMatrix) {
    if (me->mFirstChild) {
        calcRelative(me->mFirstChild, &me->mOffsetMatrix);
    }
    if (me->mSibling) {
        calcRelative(me->mSibling, parentMatrix);
    }
    if (parentMatrix) {
        me->mInitMatrix *= *parentMatrix;
    }
}

void Bone::calcUpdate(Bone* me, Math::Matrix4x4* parentMatrix) {
    me->mBoneMatrix *= *parentMatrix;
    //me->mCombMatrixArray[me->mID] = me->mOffsetMatrix * me->mBoneMatrix;
    if (me->mFirstChild) {
        calcUpdate(me->mFirstChild, &me->mBoneMatrix);
    }
    if (me->mSibling) {
        calcUpdate(me->mSibling, parentMatrix);
    }
}

void Bone::inputMatrix(Math::Matrix4x4* result) {
    //‚±‚±‚Å‰Šúp¨‚Ì‹ts—ñ‚Æ¡ƒtƒŒ[ƒ€‚Ìp¨s—ñ‚ª—~‚µ‚¢
    *result = Math::Matrix4x4::transposition(mOffsetMatrix * mBoneMatrix);
    //*result = Math::Matrix4x4::transposition(mBoneMatrix * mOffsetMatrix);

    //*result = mOffsetMatrix * mBoneMatrix;
}

} //Graphics 
} //Framework 
