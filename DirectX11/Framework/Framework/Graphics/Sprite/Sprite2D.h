#pragma once

#include <memory>
#include "Framework/Graphics/Color4.h"
#include "Framework/Graphics/Renderer/IDrawable.h"
#include "Framework/Math/Matrix4x4.h"
#include "Framework/Math/Rect.h"
#include "Framework/Utility/Property.h"

namespace Framework {
namespace Graphics {
class Effect;
class Texture;

/**
* @enum PivotBase
* @brief �s�{�b�g��ݒ肷��Ƃ��̊
*/
enum class PivotBase {
    Local, //!< ��������Ƃ����S����
    Screen, //!< �X�N���[�����W����Ƃ���
};

/**
* @class Sprite2D
* @brief 2D�X�v���C�g�`��
*/
class Sprite2D : public IDrawable {
protected:
    using Rect = Math::Rect;
protected:
    Sprite2D();
public:
    /**
    * @brief �R���X�g���N�^
    */
    Sprite2D(std::shared_ptr<Texture> texture);
    /**
    * @brief �f�X�g���N�^
    */
    virtual ~Sprite2D();
    /**
    * @brief �`�悷��
    */
    virtual void draw() override;
    /**
    * @brief �s�{�b�g�̐ݒ�
    * @param pivot �s�{�b�g�̏ꏊ
    * @param base ������ɐݒ肷�邩
    * @detail Local:pivot��0�`1�Ō��肷��B(0,0)�ŉ摜�̍���A(1,1)�ŉ摜�̉E���ɐݒ�
              Screen:�X�N���[�����W�����ƂɌ��肷��B(0,0)�ŉ�ʂ̍���A(ScreenSize)�ŉ�ʂ̉E��
    */
    void setPivot(const Math::Vector2& pivot, PivotBase base = PivotBase::Local);
    /**
    * @brief �s�{�b�g�̎擾
    * @param base �Ԃ��s�{�b�g�̊
    * @detail Local:(0,0)�ŉ摜�̍���A(1,1)�ŉ摜�̉E����\��
              Screen:(0,0)�ŉ�ʂ̍���A(ScreenSize)�ŉ�ʂ̉E��
    */
    Math::Vector2 getPivot(PivotBase base) const;
    /**
    * @brief �A���t�@�l�̐ݒ�
    * @param alpha �A���t�@�l(0.0�`1.0)
    */
    void setAlpha(float alpha);
    /**
    * @brief �A���t�@�l�̎擾
    * @return ���݂̃A���t�@�l(0.0�`1.0)
    */
    float getAlpha() const;
    /**
    * @brief ���f���ϊ��s��
    * @return ���f���ϊ��s���Ԃ�(scale * rotate * translate)
    */
    Math::Matrix4x4 getModelMatrix() const;
    /**
    * @brief �e�N�X�`���f�[�^�̎擾
    */
    Texture* getTexture() const;
    /**
    * @brief �e�N�X�`���̐ݒ�
    * @param texture �V�����e�N�X�`���f�[�^
    * @param resize �V�����摜�ɃX�v���C�g�̑傫�������킹�邩�ǂ���
    */
    void setTexture(std::shared_ptr<Texture> texture, bool resize);
protected:
    std::shared_ptr<Texture> mTexture;
protected:
    PROPERTY(Math::Vector2, mPosition, Position);
    PROPERTY(float, mZOrder, ZOrder);
    PROPERTY(float, mRotate, Rotate);
    PROPERTY(Math::Vector2, mScale, Scale);
    PROPERTY(Math::Vector2, mContentSize, ContentSize);
    PROPERTY(Color4, mColor, Color);
    PROPERTY(Rect, mSrcRect, SrcRect);
protected:
    Math::Vector2 mPivot;
};
} //Graphics 
} //Framework 
