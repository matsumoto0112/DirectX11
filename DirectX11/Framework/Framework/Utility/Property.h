#pragma once
#include <functional>
#include <sstream>

/**
* @def PROPERTY
* @brief 変数宣言とプロパティ化
* @details 変数のアクセス修飾子は直前のものが使用される
*/
#define PROPERTY(type,typeName,funcName) \
type typeName; \
public: inline void set ## funcName(const type& val) {typeName = val;} \
public: inline const type& get ## funcName() const{ return (typeName);}

/**
* @def PROPERTY_POINTER
* @brief ポインタ変数宣言とプロパティ化
* @details 変数のアクセス修飾子は直前のものが使用される
*/
#define PROPERTY_POINTER(type,typeName,funcName) \
type typeName; \
public: inline void set ## funcName(type val) { typeName = val; } \
public: inline type get ## funcName() const { return typeName; }

/**
* @def PROPERTY_READONLY
* @brief 変数宣言とゲッターの宣言
* @details 変数のアクセス修飾子は直前のものが使用される
*/
#define PROPERTY_READONLY(type,typeName,funcName) \
type typeName; \
public: inline const type& get##funcName() const { return typeName; } \

/**
* @def PROPERTY_READONLY
* @brief 変数宣言と独自定義のゲッター・セッターの宣言
* @details 変数のアクセス修飾子は直前のものが使用される
*/
#define PROPERTY_ORIGINAL_GETTER_SETTER(type,typeName,funcName,getter,setter) \
type typeName; \
public: inline void set ## funcName(const type& val) { setter(val); } \
public: inline const type& get ## funcName() const{ return getter();}
