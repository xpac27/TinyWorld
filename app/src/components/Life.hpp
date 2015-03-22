#pragma once

struct Life
{
    int amount {123};

    Life() {}
    Life(int init_amount)
        : amount(init_amount)
    {}
};
