#pragma once
#include <map>

class PropertyName {
public:

    static PropertyName ROOT_PATH() { return PropertyName(0); }
    static PropertyName CANVAS_WIDTH() { return PropertyName(1); }
    static PropertyName CANVAS_HEIGHT() { return PropertyName(2); }

    PropertyName() = delete;

    operator const int() const;

    bool operator <(PropertyName const& b);
    bool operator >(PropertyName const& b);

private:

    PropertyName(int type);

    int type;
};
