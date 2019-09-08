#pragma once
#include <functional>
#include <sstream>

#define PROPERTY(type,typeName,funcName) \
protected: type typeName; \
public: inline void set ## funcName(const type& val) {typeName = val;} \
public: inline const type& get ## funcName() const{return (typeName);}

#define PROPERTY_READONLY(type,typeName,funcName) \
protected: type typeName; \
public: inline const type& get##funcName() const { return typeName; } \
protected:

template <class T>
class PropertyBase {
protected:
    T& _value;
public:
    PropertyBase(T& value)
        :_value(value) {}
    PropertyBase(const PropertyBase& ref)
        :_value(ref._value) {}
    virtual ~PropertyBase() {};

    PropertyBase<T>& operator =(const PropertyBase<T>& ref) {
        this->_value = ref._value;
        return *this;
    }
};

template<class T>
struct GetterProperty {
    static const T& get(const T& value) { return value; }
};

template <class T>
struct SetterProperty {
    static void set(T& value, const T& var) { value = var; }
};

template <class T, class Getter = GetterProperty<T>, class Setter = SetterProperty<T>>
class Property : public PropertyBase<T>, private Getter, private Setter {
public:
    Property(T& value) :PropertyBase<T>(value) {};
    Property(const Property& ref) :PropertyBase<T>(ref) {};
    virtual ~Property() {};
public:
    operator const T& () const { return this->get(this->_value); }
    const T& operator ->() const { return this->get(this->_value); }

    Property<T, Getter, Setter>& operator =(const T& var) { this->set(this->_value, var); return *this; };
};