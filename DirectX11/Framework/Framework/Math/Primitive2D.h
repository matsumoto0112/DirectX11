#pragma once

#include <array>
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Matrix3x3.h"
#include "Framework/Math/MathUtility.h"
namespace Framework {
namespace Math {

/**
* @class Circle2D
* @brief �~
*/
class Circle2D {
public:
    /**
    * @brief �f�t�H���g�R���X�g���N�^
    */
    Circle2D() {};
    /**
    * @brief �R���X�g���N�^
    * @param center ���S���W
    * @param radius ���a
    */
    Circle2D(const Vector2& center, float radius)
        :center(center), radius(radius) {};
    /**
    * @brief �f�X�g���N�^
    */
    ~Circle2D() {};
public:
    Vector2 center; //!< ���S���W
    float radius; //!< ���a
};

/**
* @class Line2D
* @brief ����
*/
class Line2D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Line2D() {};
    /**
    * @brief �R���X�g���N�^
    * @param position �n�_
    * @param direction �����x�N�g��
    */
    Line2D(const Vector2& position, const Vector2& direction)
        :position(position), direction(direction) {};
    /**
    * @brief �f�X�g���N�^
    */
    ~Line2D() {};

    /**
    * @brief ���K�����ꂽ�����x�N�g�����擾
    */
    inline Vector2 getNormalDirection() const {
        return direction.getNormal();
    }
public:
    Vector2 position; //!< �n�_
    Vector2 direction; //!< �����x�N�g��
};

using Ray2D = Line2D;

/**
* @class Segment2D
* @brief ����
*/
class Segment2D : public Line2D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Segment2D() :Line2D() {};
    /**
    * @brief �R���X�g���N�^
    * @param position �n�_
    * @param direction �����x�N�g���i���K���j
    * @param length ����
    */
    Segment2D(const Vector2& position, const Vector2& direction, float length)
        :Line2D(position, direction), length(length) {};
    /**
    * @brief �R���X�g���N�^
    * @param start �n�_
    * @param end �I�_
    */
    Segment2D(const Vector2& start, const Vector2& end)
        :Segment2D(start, (end - start).getNormal(), (end - start).length()) {}
    /**
    * @brief �I�_�̎擾
    */
    Vector2 getEndPosition() const {
        return position + direction * length;
    };
public:
    float length; //!< �����̒���
};

/**
* @class AABB2D
* @brief ��`
*/
class AABB2D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    AABB2D() {}
    /**
    * @brief �R���X�g���N�^
    * @param position ���S���W
    * @param size ���ƍ���
    */
    AABB2D(const Vector2& position, const Vector2& size)
        :position(position), size(size) {}
    /**
    * @brief �R���X�g���N�^
    * @param left �����W(x)
    * @param top ����W(y)
    * @param right �E���W(x)
    * @param bottom �����W(y)
    */
    AABB2D(float left, float top, float right, float bottom)
        :AABB2D(Vector2((left + right) * 0.5f, (top + bottom) * 0.5f),
            Vector2(right - left, bottom - top)) {}

    /**
    * @brief ��
    */
    inline float left() const {
        return position.x - size.x * 0.5f;
    }
    /**
    * @brief �E
    */
    inline float right() const {
        return position.x + size.x * 0.5f;
    }
    /**
    * @brief ��
    */
    inline float top() const {
        return position.y - size.y * 0.5f;
    }
    /**
    * @brief ��
    */
    inline float bottom() const {
        return position.y + size.y * 0.5f;
    }
public:
    Vector2 position; //!< ���S���W
    Vector2 size; //!< ���ƍ���
};

/**
* @class OBB2D
* @brief 2D�L�����E�{�b�N�X
*/
class OBB2D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    OBB2D() {}
    /**
    * @brief �R���X�g���N�^
    * @param position ���S���W
    * @param size �e���̑傫��
    * @param rotate ��]�i�x�j
    */
    OBB2D(const Vector2& position, const Vector2& size, float rotate)
        :position(position), size(size), rotate(rotate) {}

    /**
    * @brief AABB�ɕϊ�����
    */
    static AABB2D toAABB2D(const OBB2D& obb) {
        std::array<Vector2, 4> a = obb.getVertices();
        float left = MathUtility::mymin({ a[0].x,a[1].x,a[2].x, a[3].x });
        float top = MathUtility::mymin({ a[0].y,a[1].y, a[2].y, a[3].y });
        float right = MathUtility::mymax({ a[0].x, a[1].x, a[2].x, a[3].x });
        float bottom = MathUtility::mymax({ a[0].y, a[1].y, a[2].y, a[3].y });
        return AABB2D(left, top, right, bottom);
    }

    /**
    * @brief ��]�𖳎�����AABB�ɕϊ�����
    */
    static AABB2D toAABB2DIgnoreRotate(const OBB2D& obb) {
        return AABB2D(obb.position, obb.size);
    }

    /**
    * @brief ���_�ƒ��_������4�������擾����
    */
    std::array<Vector2, 4> getVertices() const {
        const Vector2 halfSize = size * 0.5f;
        const float left = position.x - halfSize.x;
        const float right = position.x + halfSize.x;
        const float top = position.y - halfSize.y;
        const float bottom = position.y + halfSize.y;
        Matrix3x3 rotateMat = Matrix3x3::createTranslate(-position) *
            Matrix3x3::createRotate(-rotate) * Matrix3x3::createTranslate(position);
        std::array<Vector2, 4> res;
        res[0] = Vector2(left, top) * rotateMat;
        res[1] = Vector2(left, bottom) * rotateMat;
        res[2] = Vector2(right, bottom) * rotateMat;
        res[3] = Vector2(right, top) * rotateMat;
        return res;
    }
public:
    Vector2 position; //!< ���S���W
    Vector2 size; //!< ���ƍ���
    float rotate; //!< ��]
};

/**
* @class Capsule2D
* @brief �J�v�Z��
*/
class Capsule2D {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Capsule2D() {};
    /**
    * @brief �R���X�g���N�^
    * @param segment ���S����
    * @param radius ���a
    */
    Capsule2D(const Segment2D& segment, float radius)
        :segment(segment), radius(radius) {};
public:
    Segment2D segment; //!< ���S����
    float radius; //!< ���a
};

} //Math 
} //Framework 