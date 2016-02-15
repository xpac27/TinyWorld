#include "../../inc/utils/PropertyValue.hpp"

PropertyValue::PropertyValue()
{
}

PropertyValue::PropertyValue(int payload) : i_payload(payload)
{
}

PropertyValue::PropertyValue(float payload) : f_payload(payload)
{
}

PropertyValue::PropertyValue(const char* payload) : c_payload(payload)
{
}

PropertyValue::operator const int() const
{
    return i_payload;
}

PropertyValue::operator const float() const
{
    return f_payload;
}

PropertyValue::operator const char*() const
{
    return c_payload;
}
