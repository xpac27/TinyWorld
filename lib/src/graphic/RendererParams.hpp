#pragma once

// TODO use File instead of const char*
struct RendererParams
{
    unsigned int cubemapId;
    unsigned int shadowVolumeProgramId;
    unsigned int shadowImprintProgramId;
    unsigned int fillingProgramId;
    unsigned int geometryBufferProgramId;
    unsigned int deferredShadingProgramId;
};
