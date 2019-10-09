#pragma once
#include <Windows.h>
#include "Framework/Utility/Singleton.h"
#include "Framework/Math/Vector2.h"

namespace Framework {
namespace Define {

/**
* @class Config
* @brief 外部ファイル依存設定管理クラス
*/
class Config : public Utility::Singleton<Config> {
public:

protected:
    /**
    * @brief コンストラクタ
    */
    Config();
    /**
    * @brief デストラクタ
    */
    ~Config();
    //private:
public:
    const Math::Vector2 getSize() const { return Math::Vector2(mWidth, mHeight); };
public:
    UINT mWidth;
    UINT mHeight;
};

} //Define 
} //Framework 