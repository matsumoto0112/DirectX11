#pragma once

#include <memory>
namespace Framework {
namespace Utility {

/**
* @class Singleton
* @brief �p�������N���X���V���O���g����
*/
template <class T>
class Singleton {
public:
    /**
    * @brief �R���X�g���N�^
    */
    Singleton() {};
    /**
    : @brief �f�X�g���N�^
    */
    virtual ~Singleton() = default;
    /**
    * @brief �C���X�^���X�̎擾
    * @return �C���X�^���X
    */
    static T& getInstance() {
        struct temp : T { temp() :T() {} };
        static temp instance;
        return instance;
    }
private:
    //�R�s�[�R���X�g���N�^�֎~
    Singleton(const Singleton& t) = delete;
    //����֎~
    Singleton& operator=(const Singleton& t) = delete;
};

} // Utility
} //Framework 
