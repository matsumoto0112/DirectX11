#pragma once

namespace Define {

/**
* @class LightSettings
* @brief ライティング定義
* @details コンパイル時定数でなければならないためヘッダーで定義
*/
class LightSettings {
public:
    static const int DIRECTIONALLIGHT_NUM = 4; //!< ディレクショナルライトの数
    static const int POINTLIGHT_NUM = 4; //!< ポイントライトの数
};

} //Define 