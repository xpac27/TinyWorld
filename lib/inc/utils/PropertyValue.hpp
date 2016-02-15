#pragma once

class PropertyValue
{

public:

    PropertyValue();
    PropertyValue(int payload);
    PropertyValue(float payload);
    PropertyValue(const char* payload);

    operator const int() const;
    operator const float() const;
    operator const char*() const;

private:

    int i_payload {0};
    float f_payload {0.f};
    const char* c_payload {""};
};
