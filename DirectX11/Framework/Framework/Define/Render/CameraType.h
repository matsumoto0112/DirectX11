#pragma once

namespace Define {

/**
* @class CameraType
* @brief カメラの種類
* @details カメラの描画順もこれで制御している。上にあるものほど先に描画される。
*/
enum class CameraType {
    BackGround, //!< 背景カメラ
    ThreeD, //!< 3Dカメラ
    TwoD, //!< 2Dカメラ
    UI, //!< UIカメラ
};

} //Graphics 