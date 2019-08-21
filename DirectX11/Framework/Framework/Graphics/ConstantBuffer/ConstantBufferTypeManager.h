#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include "Framework/Graphics/ConstantBuffer/ConstantBufferParameterType.h"
#include "Framework/Utility/Debug.h"

namespace Framework {
namespace Graphics {

/**
* @class ConstantBufferTypeManager
* @brief �R���X�^���g�o�b�t�@�̌^�̎�ނ��Ƃ̊Ǘ���
�o�b�t�@�ւ̓]���̊Ǘ�������
* @tparam T �����^
*/
template <class T>
class ConstantBufferTypeManager {
private:
    using Func = std::function<void(const T&)>;
public:
    /**
    * @brief �R���X�g���N�^
    */
    ConstantBufferTypeManager();
    /**
    * @brief �f�X�g���N�^
    */
    ~ConstantBufferTypeManager();
    /**
    * @brief �]������֐��̒ǉ�
    * @param type �]������p�����[�^�̎��
    * @param send �]���֐�
    */
    void add(ConstantBufferParameterType type, Func send);
    /**
    * @brief �o�b�t�@�Ƀf�[�^��]������
    * @param type �]������p�����[�^�̎��
    * @param value �]������f�[�^
    */
    void set(ConstantBufferParameterType type, const T& value);
private:
    std::unordered_map<ConstantBufferParameterType, Func> mSendFuncs; //!< �]���֐��̃}�b�v
};

template<class T>
inline ConstantBufferTypeManager<T>::ConstantBufferTypeManager() {}

template<class T>
inline ConstantBufferTypeManager<T>::~ConstantBufferTypeManager() {
    mSendFuncs.clear();
}

template<class T>
inline void ConstantBufferTypeManager<T>::add(ConstantBufferParameterType type, Func f) {
    mSendFuncs[type] = f;
}

template<class T>
inline void ConstantBufferTypeManager<T>::set(ConstantBufferParameterType type, const T& value) {
    MY_ASSERTION(mSendFuncs.find(type) != mSendFuncs.end(),
        "���o�^��Set���Ă΂�܂����B");
    mSendFuncs[type](value);
}

} //Graphics 
} //Framework
