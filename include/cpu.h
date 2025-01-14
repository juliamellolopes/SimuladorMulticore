#pragma once

#include <thread>
#include <mutex>
#include <chrono>

#include "uc.h"
#include "core.h"
#include "memory/cache.h"
#include "pipeline.h"
#include "processo.h"

#define TAM_CORE 5
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

    vector<thread> _threads;
    mutex _mutexFilaPrincipal;
    mutex _mutexOrganizarFila;
    mutex _mutexProcessosAtivos;
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
    void executarProcessos();
    void atualizarFila(queue<string> &fila);
    void processamento(Processo &processo);
    void gerenciarPrioridade(Processo &processo);
    void executePipeline(const string &instrucao);
    void atualizarRegistradores(queue<pair<int, int>> &registradores);

    void inicializarThreads();
    void processarCore(int coreID);
};
