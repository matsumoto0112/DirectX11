#pragma once
#include <functional>
#include <sstream>

#define PROPERTY(type,typeName,funcName) \
type typeName; \
public: inline void set ## funcName(const type& val) {typeName = val;} \
public: inline const type& get ## funcName() const{ return (typeName);}

#define PROPERTY_POINTER(type,typeName,funcName) \
type* typeName; \
public: inline void set ## funcName(type* val) { typeName = val; } \
public: inline type* get ## funcName() const { return typeName; }

#define PROPERTY_READONLY(type,typeName,funcName) \
type typeName; \
public: inline const type& get##funcName() const { return typeName; } \
