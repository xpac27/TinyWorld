#pragma once

class ComponentGUI
{
public:
    ComponentGUI() :id(++count - 1) {}

    unsigned int get();

private:
    unsigned int id;
    static unsigned int count;
};
