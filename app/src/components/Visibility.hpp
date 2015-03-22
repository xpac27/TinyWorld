#pragma once

struct Visibility
{
    bool active {true};

    Visibility() {}
    Visibility(bool init_active)
        : active(init_active)
    {}
};
