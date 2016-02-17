#include "../../inc/graphic/CubemapStore.hpp"
#include "Cubemap.hpp"

CubemapStore::CubemapStore()
    : stormyday(new Cubemap((const char*[]){
        "textures/environments/stormyday/cubemap/right.png",
        "textures/environments/stormyday/cubemap/left.png",
        "textures/environments/stormyday/cubemap/bottom.png",
        "textures/environments/stormyday/cubemap/top.png",
        "textures/environments/stormyday/cubemap/back.png",
        "textures/environments/stormyday/cubemap/front.png",
    }))
    , stormydayIM(new Cubemap((const char*[]){
        "textures/environments/stormyday/irradiance-map/right.png",
        "textures/environments/stormyday/irradiance-map/left.png",
        "textures/environments/stormyday/irradiance-map/bottom.png",
        "textures/environments/stormyday/irradiance-map/top.png",
        "textures/environments/stormyday/irradiance-map/back.png",
        "textures/environments/stormyday/irradiance-map/front.png",
    }))
    , archipelago(new Cubemap((const char*[]){
        "textures/environments/archipelago/cubemap/right.png",
        "textures/environments/archipelago/cubemap/left.png",
        "textures/environments/archipelago/cubemap/bottom.png",
        "textures/environments/archipelago/cubemap/top.png",
        "textures/environments/archipelago/cubemap/back.png",
        "textures/environments/archipelago/cubemap/front.png",
    }))
    , archipelagoIM(new Cubemap((const char*[]){
        "textures/environments/archipelago/irradiance-map/right.png",
        "textures/environments/archipelago/irradiance-map/left.png",
        "textures/environments/archipelago/irradiance-map/bottom.png",
        "textures/environments/archipelago/irradiance-map/top.png",
        "textures/environments/archipelago/irradiance-map/back.png",
        "textures/environments/archipelago/irradiance-map/front.png",
    }))
{
}

CubemapStore::~CubemapStore()
{
    delete stormyday;
    delete stormydayIM;
    delete archipelago;
    delete archipelagoIM;
}

Cubemap* CubemapStore::getCubemap(CubemapType type)
{
    switch (type) {
        case CubemapType::STORMYDAY: return stormyday;
        case CubemapType::STORMYDAY_IM: return stormydayIM;
        case CubemapType::ARCHIPELAGO: return archipelago;
        case CubemapType::ARCHIPELAGO_IM: return archipelagoIM;
    }
}

void CubemapStore::reloadCubemapesTextures()
{
    // TODO...
}
