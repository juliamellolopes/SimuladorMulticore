#pragma once

#include "uc.h"
#include "core.h"
#include "memory/cache.h"
#include "pipeline.h"
#include "processo.h"

#define TAM_CORE 2
#define QUANTUM_CPU 20
class CPU : UC {
private:
    MemoryRAM _memoryRAM;
    MemoryCache _memoryCache;
    Pipeline _pipeline;

    vector<CORE> _cores;
    queue<string> _processosID;
    queue<string> _filaAuxiliarMedia;
    queue<string> _filaAuxiliarBaixa;
    queue<string> _filaAuxiliarAlta;
    int _PC;
    int _coreAtivo;
    int _processosAtivos;
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
    void incrementaPC();
    void organizarFila();
    void atualizarFila(queue<string> &fila);
    void processamento(Processo &processo);
    void gerenciarPrioridade(Processo &processo);
    void executePipeline(const string &instrucao);
    void atualizarRegistradores(queue<pair<int, int>> &registradores);

};
