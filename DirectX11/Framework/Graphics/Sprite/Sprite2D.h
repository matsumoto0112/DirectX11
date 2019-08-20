#pragma once

#include <memory>
#include "Math/Rect.h"
#include "Graphics/Color4.h"
#include "Math/Matrix4x4.h"

namespace Framework {
namespace Graphics {
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
class Sprite2D {
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
    virtual void draw();
    /**
    * @brief ���W�̐ݒ�
    */
    void setPosition(const Math::Vector2& position);
    /**
    * @brief ���W�̎擾
    */
    const Math::Vector2& getPosition() const;
    void setZOrder(float z);
    float getZOrder() const;
    /**
    * @brief ��]�̐ݒ�
    */
    void setRotate(float rotate);
    /**
    * @brief ��]�̎擾
    */
    float getRotate() const;
    /**
    * @brief �X�P�[�����O�̐ݒ�
    */
    void setScale(const Math::Vector2& scale);
    /**
    * @brief �X�P�[�����O�̎擾
    */
    const Math::Vector2& getScale() const;
    /**
    * @brief �R���e���c�̑傫���̐ݒ�
    */
    void setContentSize(const Math::Vector2& size);
    /**
    * @brief �R���e���c�̑傫���̎擾
    */
    const Math::Vector2& getContentSize() const;
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
    * @brief �F�̐ݒ�
    */
    void setColor(const Color4& color);
    /**
    * @brief �F�̎擾
    */
    const Color4& getColor() const;
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
    * @brief �e�N�X�`���̋�`�̐ݒ�
    * @param r ��`���
    * @detail r.left uv�̍����W(0�`1)
              r.top uv�̏���W(0�`1)
              r.width uv�̕�(0�`1)
              r.height uv�̍���(0�`1)
              ��ݒ肷��
    */
    void setSrcRect(const Rect& r);
    /**
    * @brief �e�N�X�`���̋�`�̎擾
    * @return ��`����Ԃ�
    * @detail r.left uv�̍����W(0�`1)
              r.top uv�̏���W(0�`1)
              r.width uv�̕�(0�`1)
              r.height uv�̍���(0�`1)
              ���擾����
    */
    const Rect& getSrcRect() const;
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
    void setTexture(std::shared_ptr<Texture>& texture, bool resize);
protected:
    std::shared_ptr<Texture> mTexture;
    Math::Vector2 mPosition;
    float mZOrder;
    float mRotate;
    Math::Vector2 mScale;
    Math::Vector2 mContentSize;
    Math::Vector2 mPivot;
    Color4 mColor;
    Rect mSrcRect;
};
} //Graphics 
} //Framework 
