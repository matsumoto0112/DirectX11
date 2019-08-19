#pragma once

#include "Math/Vector2.h"
namespace Framework {
namespace Math {

/**
* @class Rect
* @brief ��`�N���X
*/
class Rect {
public:
    /**
    * @brief �f�t�H���g�R���X�g���N�^
    */
    Rect();
    /**
    * @brief �R���X�g���N�^
    * @param x x���W
    * @param y y���W
    * @param width ��
    * @param height ����
    */
    Rect(float x, float y, float width, float height);
    /**
    * @brief �R���X�g���N�^
    * @param center ���S���W
    * @param size �傫��
    */
    Rect(const Vector2& center, const Vector2& size);
    /**
    * @brief �f�X�g���N�^
    */
    ~Rect();
    /**
    * @brief x���W���擾
    */
    float getX() const;
    /**
    * @brief x���W��ݒ�
    */
    void setX(float x);
    /**
    * @brief y���W���擾
    */
    float getY() const;
    /**
    * @brief y���W��ݒ�
    */
    void setY(float y);
    /**
    * @brief ���W���擾
    */
    Vector2 getPosition() const;
    /**
    * @brief ���W��ݒ�
    */
    void setPosition(const Vector2& position);
    /**
    * @brief ���W��ݒ�
    */
    void setPosition(float x, float y);
    /**
    * @brief �����擾
    */
    float getWidth() const;
    /**
    * @brief ����ݒ�
    */
    void setWidth(float width);
    /**
    * @brief �������擾
    */
    float getHeight() const;
    /**
    * @brief ������ݒ�
    */
    void setHeight(float height);
    /**
    * @brief ���ƍ������擾
    */
    Vector2 getSize() const;
    /**
    * @brief ���ƍ�����ݒ�
    */
    void setSize(const Vector2& size);
    /**
    * @brief ���ƍ�����ݒ�
    */
    void setSize(float width, float height);
    /**
    * @brief �ŏ�x���W���擾
    */
    float getXMin() const;
    /**
    * @brief �ŏ�x���W��ݒ�
    */
    void setXMin(float xmin);
    /**
    * @brief �ő�x���W���擾
    */
    float getXMax() const;
    /**
    * @brief �ő�x���W��ݒ�
    */
    void setXMax(float xmax);
    /**
    * @brief �ŏ�y���W���擾
    */
    float getYMin() const;
    /**
    * @brief �ŏ�y���W��ݒ�
    */
    void setYMin(float ymin);
    /**
    * @brief �ő�y���W���擾
    */
    float getYMax() const;
    /**
    * @brief �ő�y���W��ݒ�
    */
    void setYMax(float ymax);
    /**
    * @brief �ŏ����W���擾
    */
    Vector2 getMin() const;
    /**
    * @brief �ŏ����W��ݒ�
    */
    void setMin(const Vector2& min);
    /**
    * @brief �ŏ����W��ݒ�
    */
    void setMin(float xmin, float ymin);
    /**
    * @brief �ő���W���擾
    */
    Vector2 getMax() const;
    /**
    * @brief �ő���W��ݒ�
    */
    void setMax(const Vector2& max);
    /**
    * @brief �ő���W��ݒ�
    */
    void setMax(float xmax, float ymax);
    /**
    * @brief ���S���W���擾
    */
    Vector2 getCenter() const;
    /**
    * @brief �_���܂�ł��邩
    * @param point �_�̍��W
    * @return �܂�ł�����true
    */
    bool contains(const Vector2& point) const;
    /**
    * @brief �ʂ̋�`�Əd�Ȃ��Ă��邩
    * @param rect ���ׂ��`
    * @return �d�Ȃ��Ă�����true
    */
    bool intersects(const Rect& rect) const;
private:
    float x; //!< x���W
    float y; //!< y���W
    float width; //!< ��
    float height; //!< ����
};

} //Math 
} //Framework 