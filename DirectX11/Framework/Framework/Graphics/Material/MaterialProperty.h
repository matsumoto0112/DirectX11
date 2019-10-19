#pragma once
#include "Framework/Graphics/ConstantBuffer/ConstantBufferStruct.h"
// #include "Framework/Utility/Wrap/OftenUsed.h"

namespace Framework {
namespace Graphics {

/**
* @class MaterialProperty
* @brief マテリアル情報
*/
template <class T>
class MaterialProperty {
public:
    /**
    * @brief コンストラクタ
    * @param data バッファデータ
    */
    MaterialProperty()
        :mData() { }
    /**
    * @brief デストラクタ
    */
    virtual ~MaterialProperty() = default;
    /**
    * @brief バッファを転送する
    */
    virtual void sendBuffer() = 0;
public:
    T mData;
};

class WorldMatrix3DProperty : public MaterialProperty<Math::Matrix4x4> {
public:
    virtual void sendBuffer() override;
};

class ColorProperty : public MaterialProperty<Color4> {
public:
    virtual void sendBuffer() override;
};

} //Graphics 
} //Framework 