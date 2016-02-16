#include "../../inc/graphic/ProgramStore.hpp"
#include "Program.hpp"

ProgramStore::ProgramStore()
    : shadowVolume(new Program("lib/src/shaders/shadow_volume.vert", "lib/src/shaders/shadow_volume.geom", "lib/src/shaders/shadow_volume.frag"))
    , shadowImprint(new Program("lib/src/shaders/shadow_imprint.vert", "lib/src/shaders/shadow_imprint.frag"))
    , filling(new Program("lib/src/shaders/filling.vert", "lib/src/shaders/filling.frag"))
    , geometryBuffer(new Program("lib/src/shaders/geometry_buffer.vert", "lib/src/shaders/geometry_buffer.frag"))
    , deferredShading(new Program("lib/src/shaders/deferred_shading.vert", "lib/src/shaders/deferred_shading.frag"))
{
}

ProgramStore::~ProgramStore()
{
    delete shadowVolume;
    delete shadowImprint;
    delete filling;
    delete geometryBuffer;
    delete deferredShading;
}

Program* ProgramStore::getProgram(ProgramType type)
{
    switch (type) {
        case ProgramType::SHADOW_VOLUME: return shadowVolume;
        case ProgramType::SHADOW_IMPRINT: return shadowImprint;
        case ProgramType::FILLING: return filling;
        case ProgramType::GEOMETRY_BUFFER: return geometryBuffer;
        case ProgramType::DEFERRED_SHADING: return deferredShading;
    }
}

void ProgramStore::reloadProgramesShaders()
{
    // TODO...
}
