#pragma once
#include "Framework/Graphics/ConstantBuffer/ConstantBufferStruct.h"
// #include "Framework/Utility/Wrap/OftenUsed.h"

namespace Framework {
namespace Graphics {

/**
* @class MaterialProperty
* @brief �}�e���A�����
*/
template <class T>
class MaterialProperty {
public:
    /**
    * @brief �R���X�g���N�^
    * @param data �o�b�t�@�f�[�^
    */
    MaterialProperty()
        :mData() { }
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~MaterialProperty() = default;
    /**
    * @brief �o�b�t�@��]������
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