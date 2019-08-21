#pragma once

#define PROPERTY(type,typeName,funcName) protected: \
type typeName; \
public: \
inline void set ## funcName(const type& val) {typeName = val;} \
inline const type& get ## funcName() const{return (typeName);}
