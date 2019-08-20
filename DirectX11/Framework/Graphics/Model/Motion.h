#pragma once
#include <vector>
#include "Math/Matrix4x4.h"
namespace Framework {
namespace Graphics {

/**
* @class Motion
* @brief モーション管理クラス
*/
class Motion {
public:
    /**
    * @brief コンストラクタ
    * @param keyFrame キーフレーム数
    */
    Motion(int keyFrame, int bone);
    /**
    * @brief デストラクタ
    */
    ~Motion();
    /**
    * @brief キーフレーム単位での行列の設定
    * @param frame 何フレーム目か
    * @param mat 行列値
    */
    void setKeyFrame(int frame, int bone, const Math::Matrix4x4& mat);
    /**
    * @brief キーフレームでの行列の追加
    * @param mat 行列値
    * @details 前に追加したキーフレームの1フレーム後の行列を設定できる
    */
    void addKeyFrame(const Math::Matrix4x4& mat);
    /**
    * @brief フレームに対する行列を返す
    */
    const Math::Matrix4x4& getKeyFrame(int frame, int bone);
    /**
    * @brief キーフレーム数を返す
    */
    int getKeyFrameNum() const { return mKeyFrameNum; }
private:
    int mKeyFrameNum; //!< キーフレーム数
    std::vector<std::vector<Math::Matrix4x4>> mKeyFrames;
    //std::vector<Math::Matrix4x4> mKeyFrames; //!< キーフレームごとの行列
};

} //Graphics 
} //Framework 
