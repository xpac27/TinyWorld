#pragma once

struct Life
{
    int amount {100};

    Life() {}
    Life(int init_amount)
        : amount(init_amount)
    {}
};
