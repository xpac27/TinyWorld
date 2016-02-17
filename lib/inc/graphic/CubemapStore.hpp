#pragma once
#include "../../inc/graphic/CubemapType.hpp"

class Cubemap;
class CubemapStore
{

public:

    CubemapStore();
    ~CubemapStore();

    Cubemap* getCubemap(CubemapType type);

    void reloadCubemapesTextures();

private:

    Cubemap* stormyday;
    Cubemap* stormydayIM;
    Cubemap* archipelago;
    Cubemap* archipelagoIM;
};
