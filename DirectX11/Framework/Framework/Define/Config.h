#pragma once
#include <Windows.h>
#include "Framework/Utility/Singleton.h"

namespace Framework {
namespace Define2 {

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
    UINT mWidth;
    UINT mHeight;
};

} //Define2 
} //Framework 