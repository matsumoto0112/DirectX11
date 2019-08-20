#pragma once
#include "Graphics/Color4.h"
#include "Graphics/Texture/Texture.h"
#include "Math/Matrix4x4.h"
#include "Math/Rect.h"

namespace Framework {
namespace Graphics {

/**
* @class Sprite3D
* @brief 3D�r���{�[�h�X�v���C�g
*/
class Sprite3D {
public:
    /**
    * @brief �R���X�g���N�^
    * @param texture �g�p����e�N�X�`��
    */
    Sprite3D(std::shared_ptr<Texture> texture);
    /**
    * @brief �f�X�g���N�^
    */
    ~Sprite3D();
    std::shared_ptr<Texture> getTexture() const { return mTexture; };
    void setTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
    /**
    * @brief ���W�̎擾
    */
    const Math::Vector3& getPosition() const { return mPosition; }
    /**
    * @brief ���W�̐ݒ�
    */
    void setPosition(const Math::Vector3& position) { mPosition = position; }
    /**
    * @brief �傫���̎擾
    */
    const Math::Vector3& getScale() const { return mScale; }
    /**
    * @brief �傫���̐ݒ�
    */
    void setScale(const Math::Vector3& scale) { mScale = scale; }
    const Color4& getColor() const { return mColor; }
    void setColor(const Color4& color) { mColor = color; }
    const Math::Rect& getSrcRect() const { return mSrcRect; }
    void setSrcRect(const Math::Rect& rect) { mSrcRect = rect; }
    /**
    * @brief �`��
    */
    void draw();

    Math::Matrix4x4 createBillboardMatrix(const Math::Matrix4x4& invView) const;
private:
    std::shared_ptr<Texture> mTexture;
    Math::Vector3 mPosition;
    Math::Vector3 mScale;
    Math::Vector2 mContentSize;
    Color4 mColor;
    Math::Rect mSrcRect;
};

} //Graphics 
} //Framework 
