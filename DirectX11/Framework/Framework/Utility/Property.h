#pragma once
#include <functional>
#include <sstream>

/**
* @def PROPERTY
* @brief 変数宣言とプロパティ化
* @details 変数のアクセス修飾子は直前のものが使用される
*/
#define PROPERTY(type, typeName,funcName) \
protected: type typeName; \
public: inline void set ## funcName(const type& val) {typeName = val;} \
public: inline const type& get ## funcName() const{ return (typeName);}

/**
* @def PROPERTY_GETREF
* @brief 変数宣言とプロパティ化
* @details 変数のアクセス修飾子は直前のものが使用される
getterは参照を返す
*/
#define PROPERTY_GETREF(type,typeName,funcName) \
protected: type typeName; \
public: inline void set ## funcName(const type& val) {typeName = val;} \
public: inline type& get ## funcName() { return (typeName);}

/**
* @def PROPERTY_POINTER
* @brief ポインタ変数宣言とプロパティ化
* @details 変数のアクセス修飾子は直前のものが使用される
*/
#define PROPERTY_POINTER(type,typeName,funcName) \
protected: type typeName; \
public: inline void set ## funcName(type val) { typeName = val; } \
public: inline type get ## funcName() const { return typeName; }

/**
* @def PROPERTY_READONLY
* @brief 変数宣言とゲッターの宣言
* @details 変数のアクセス修飾子は直前のものが使用される
*/
#define PROPERTY_READONLY(type,typeName,funcName) \
protected: type typeName; \
public: inline const type& get##funcName() const { return typeName; } \

/**
* @def PROPERTY_ORIGINAL_GETTER_SETTER
* @brief 変数宣言と独自定義のゲッター・セッターの宣言
* @details 変数のアクセス修飾子は直前のものが使用される
*/
#define PROPERTY_ORIGINAL_GETTER_SETTER(type,typeName,funcName,getter,setter) \
protected: type typeName; \
public: inline void set ## funcName(const type& val) { setter(val); } \
public: inline const type& get ## funcName() const{ return getter();}

/**
* @def PROPERTY_ORIGINAL_GETTER_SETTER
* @brief 変数宣言と独自定義のゲッター・セッターの宣言
* @details 変数のアクセス修飾子は直前のものが使用される
*/
#define PROPERTY_POINTER_ORIGINAL_GETTER_SETTER(type,typeName,funcName,getter,setter) \
protected: type typeName; \
public: inline void set ## funcName(type val) { setter(val); } \
public: inline type get ## funcName() const{ return getter();}


