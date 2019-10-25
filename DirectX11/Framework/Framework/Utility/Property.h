#pragma once
#include <functional>
#include <sstream>

/**
* @def PROPERTY
* @brief �ϐ��錾�ƃv���p�e�B��
* @details �ϐ��̃A�N�Z�X�C���q�͒��O�̂��̂��g�p�����
*/
#define PROPERTY(type, typeName,funcName) \
protected: type typeName; \
public: inline void set ## funcName(const type& val) {typeName = val;} \
public: inline const type& get ## funcName() const{ return (typeName);}

/**
* @def PROPERTY_GETREF
* @brief �ϐ��錾�ƃv���p�e�B��
* @details �ϐ��̃A�N�Z�X�C���q�͒��O�̂��̂��g�p�����
getter�͎Q�Ƃ�Ԃ�
*/
#define PROPERTY_GETREF(type,typeName,funcName) \
protected: type typeName; \
public: inline void set ## funcName(const type& val) {typeName = val;} \
public: inline type& get ## funcName() { return (typeName);}

/**
* @def PROPERTY_POINTER
* @brief �|�C���^�ϐ��錾�ƃv���p�e�B��
* @details �ϐ��̃A�N�Z�X�C���q�͒��O�̂��̂��g�p�����
*/
#define PROPERTY_POINTER(type,typeName,funcName) \
protected: type typeName; \
public: inline void set ## funcName(type val) { typeName = val; } \
public: inline type get ## funcName() const { return typeName; }

/**
* @def PROPERTY_READONLY
* @brief �ϐ��錾�ƃQ�b�^�[�̐錾
* @details �ϐ��̃A�N�Z�X�C���q�͒��O�̂��̂��g�p�����
*/
#define PROPERTY_READONLY(type,typeName,funcName) \
protected: type typeName; \
public: inline const type& get##funcName() const { return typeName; } \

/**
* @def PROPERTY_ORIGINAL_GETTER_SETTER
* @brief �ϐ��錾�ƓƎ���`�̃Q�b�^�[�E�Z�b�^�[�̐錾
* @details �ϐ��̃A�N�Z�X�C���q�͒��O�̂��̂��g�p�����
*/
#define PROPERTY_ORIGINAL_GETTER_SETTER(type,typeName,funcName,getter,setter) \
protected: type typeName; \
public: inline void set ## funcName(const type& val) { setter(val); } \
public: inline const type& get ## funcName() const{ return getter();}

/**
* @def PROPERTY_ORIGINAL_GETTER_SETTER
* @brief �ϐ��錾�ƓƎ���`�̃Q�b�^�[�E�Z�b�^�[�̐錾
* @details �ϐ��̃A�N�Z�X�C���q�͒��O�̂��̂��g�p�����
*/
#define PROPERTY_POINTER_ORIGINAL_GETTER_SETTER(type,typeName,funcName,getter,setter) \
protected: type typeName; \
public: inline void set ## funcName(type val) { setter(val); } \
public: inline type get ## funcName() const{ return getter();}


