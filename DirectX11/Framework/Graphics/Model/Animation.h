#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {

class Motion;

/**
* @class Animation
* @brief アニメーション管理クラス
*/
class Animation {
public:
    /**
    * @brief コンストラクタ
    */
    Animation();
    /**
    * @brief デストラクタ
    */
    ~Animation();
    /**
    * @brief モーションの追加
    * @param id モーションID
    * @param motion 追加するモーション
    */
    void addMotion(int id, std::unique_ptr<Motion> motion);
    /**
    * @brief モーションの更新
    * @param delta 差分時間
    */
    void update(float delta);
    /**
    * @brief 再生アニメーションの変更
    * @param id 変更するアニメーションID
    */
    void changeAnimation(int id);
    /**
    * @brief 現在のモーションの行列を取得
    */
    Math::Matrix4x4 getAnimationMatrix(int bone);
private:
    float mTime; //!< アニメーション再生時間
    int mCurrentMotion; //!< 再生中のアニメーションID
    std::unordered_map<int, std::unique_ptr<Motion>> mMotions; //!< モーションリスト
};

} //Graphics
} //Framework 
