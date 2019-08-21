#pragma once
namespace Framework {
namespace Input {

/**
* @brief コントローラに関するユーティリティクラス
*/
class ControllerUtil {
public:
    static const unsigned int AXIS_MAX_POSITION; //!< 軸の最大座標
    static const float HALF_AXIS_MAX_POSITION; //!< 軸の最大座標の半分
};
} //Input 
} //Framework
