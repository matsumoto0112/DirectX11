#pragma once

namespace Framework {
namespace Graphics {

/**
* @brief 有効カメラ数用構造体
*/
struct CameraNumCBufferStruct {
public:
    int cameraNum; //!< カメラの数
    int dummy[3]; //パッキング対策
};

} //Graphics 
} //Framework