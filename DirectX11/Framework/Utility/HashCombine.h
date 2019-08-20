#pragma once

#include <functional>

//�Q�l�T�C�g https://suzulang.com/cpp-unordered_map-my-type/
namespace Framework {
namespace Utility {

/**
* @brief �n�b�V���l�𓝍�����
* @param seed �����̃n�b�V���l
* @param v �V���Ƀn�b�V���l���쐬����l
* @return ����seed��v����쐬�����n�b�V���l�𓝍������l
*/
template<typename T>
static size_t combineHash(size_t seed, const T& v) {
    //��{�^�Ɋւ���n�b�V�������͕W�����C�u�������񋟂��Ă���
    std::hash<T> primitive_type_hash;

    //���������n�b�V������������B���̃R�[�h��boost���̂��g�p����
    seed ^= primitive_type_hash(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}

} //Utility 
} //Framework 
