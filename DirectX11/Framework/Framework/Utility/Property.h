#pragma once
#include <functional>

#define PROPERTY(type,typeName,funcName) \
protected: type typeName; \
public: inline void set ## funcName(const type& val) {typeName = val;} \
public: inline const type& get ## funcName() const{return (typeName);}

#define PROPERTY_READONLY(type,typeName,funcName) \
protected: type typeName; \
public: inline const type& get##funcName() const { return typeName; } \
protected:

template <class T>
class Property {
public:
    T& t;
    std::function<void(T)> set = nullptr;
    std::function<T()> get = nullptr;

    operator T() {
        return get ? this->get() : this->t;
    }

    T operator ->() {
        return get ? this->get() : this->t;
    }

    void operator =(const T v) {
        if (set) {
            this->set(v);
        }
        else {
            this->t = v;
        }
    }
};

template <class T>
class ReadonlyProperty {
public:
    T& t;
    std::function<T()> get = nullptr;

    operator T() {
        return get ? this->get() : this->t;
    }

    T operator ->() {
        return get ? this->get() : this->t;
    }
};
