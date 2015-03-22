#pragma once

struct Position
{
    float x {0.0};
    float y {0.0};

    Position() {}
    Position(float init_x, float init_y)
        : x(init_x)
        , y(init_y)
    {}
};
