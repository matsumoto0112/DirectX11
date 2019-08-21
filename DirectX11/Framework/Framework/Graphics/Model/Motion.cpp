#include "Motion.h"
#include "Framework/Utility/Debug.h"
namespace Framework {
Graphics::Motion::Motion(int keyFrame, int bone)
    :mKeyFrameNum(keyFrame) {
    mKeyFrames.reserve(mKeyFrameNum);
    mKeyFrames.resize(keyFrame);
    for (int i = 0; i < keyFrame; i++) {
        mKeyFrames[i].resize(bone);
    }
}

Graphics::Motion::~Motion() {}

void Graphics::Motion::setKeyFrame(int frame, int bone, const Math::Matrix4x4& mat) {
    mKeyFrames[frame][bone] = mat;
}

void Graphics::Motion::addKeyFrame(const Math::Matrix4x4& mat) {
    //MY_ASSERTION(mKeyFrames.size() <= mKeyFrameNum,
    //    "最初に設定したキーフレーム数を超過しています");
    //mKeyFrames.emplace_back(mat);
}

const Math::Matrix4x4& Graphics::Motion::getKeyFrame(int frame, int bone) {
    return mKeyFrames[frame][bone];
}
} //Framework 
