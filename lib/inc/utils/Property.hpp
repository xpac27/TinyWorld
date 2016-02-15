#pragma once
#include <map>

// class Property {
// public:
//
//     static Property ROOT_PATH(const char* value) { return Property(value); }
//     static Property CANVAS_WIDTH(int value) { return Property(value); }
//     static Property CANVAS_HEIGHT(int value) { return Property(value); }
//
//     operator const int() const;
//
//     bool operator <(Property const& b);
//     bool operator >(Property const& b);
//
// private:
//
//     Property();
//     Property(int value);
//     Property(const char* value);
//
//     int type;
//
//     static int instances;
//
//     int int_value;
//     const char* char_value;
// };

class ValueBase{};

template <typename T>
class Value : public ValueBase{
};

std::map<int, ValueBase> properties;
Value<int> a;
Value<const char*> b;
properties.insert(std::pair<int, Base>(0, a));
properties.insert(std::pair<int, Base>(1, b));
