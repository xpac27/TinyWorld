#pragma once

class PropertyValueBase {
};

template <typename T>
class PropertyValue : public PropertyValueBase
{

public:

    PropertyValue() = delete;
    PropertyValue(T value);

    operator const T() const;

private:

    T value;
};

template <typename T>
PropertyValue<T>::PropertyValue(T _value) : value(_value)
{
}

template <typename T>
PropertyValue<T>::operator const T() const
{
    return value;
}
