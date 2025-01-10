#pragma once

#include "memory/cache.h"
#include "uc.h"
#include "core.h"
#include "pipeline.h"


class CPU : UC {
private:
    MemoryRAM _memoryRAM;
    MemoryCache _memoryCache;
    Pipeline _pipeline;

    vector<CORE> _cores;
    int _PC;
    int _coreAtivo;
public:
    CPU() :
        _memoryRAM("instructions/"),
        _memoryCache(_memoryRAM),
        _pipeline(_memoryRAM, _memoryCache, _cores, _coreAtivo, _PC) {
        init();
    }
    ~CPU() {}

    void init();
    void inicializar();
    void InstructionLoop();
    void incrementaPC();
};
