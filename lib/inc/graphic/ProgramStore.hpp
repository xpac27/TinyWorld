#pragma once
#include "../../inc/graphic/ProgramType.hpp"

class Program;
class ProgramStore
{

public:

    ProgramStore();
    ~ProgramStore();

    Program* getProgram(ProgramType type);

    void reloadProgramesShaders();

private:

    Program* shadowVolume;
    Program* shadowImprint;
    Program* filling;
    Program* geometryBuffer;
    Program* deferredShading;
};
