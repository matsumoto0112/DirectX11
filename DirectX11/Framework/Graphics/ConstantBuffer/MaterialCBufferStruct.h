#pragma once
#include "Graphics/Color4.h"

namespace Framework {
namespace Graphics {

struct MaterialCBufferStruct {
    Color4 ambient; //!< 環境光反射
    Color4 diffuse; //!< 拡散反射
    Color4 specular; //!< 鏡面反射 
    float shininess; //!< 輝度
    float alpha; //!< アルファ値
    float tr; //発光色
    bool illumuFlag; //!< 照明モデル
};

} //Graphics 
} //Framework