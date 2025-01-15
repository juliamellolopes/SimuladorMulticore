#pragma once

#include <thread>
#include <mutex>
#include <chrono>

#include "uc.h"
#include "core.h"
#include "scheduler/escalonador.h"
#include "pipeline.h"
#include "memory/cache.h"
#include "processo.h"

#define TAM_CORE 3
#define QUANTUM_CPU 20
class CPU : UC {
private:
    bool _tipoExibicao; // true -> completa | false -> resumida

    MemoryRAM _memoryRAM;
    MemoryCache _memoryCache;
    Pipeline _pipeline;
    queue<string> _processosID;
    Escalonador _escalonador;
    TipoPolitica _politica;

    vector<CORE> _cores;
    queue<string> _filaAuxiliarMedia;
    queue<string> _filaAuxiliarBaixa;
    queue<string> _filaAuxiliarAlta;
    int _PC;
    int _coreAtivo;
    int _processosAtivos;

    vector<thread> _threads;
    mutex _mutexFilaPrincipal;
public:
    CPU(const bool tipo) :
        _tipoExibicao(tipo),
        _memoryRAM("instructions/", _tipoExibicao),
        _memoryCache(_memoryRAM, _tipoExibicao),
        _pipeline(_memoryRAM, _memoryCache, _cores, _coreAtivo, _PC, _tipoExibicao),
        _escalonador(_processosID) {
        init();
    }
    ~CPU() {}

    void init();
    void inicializar();
    void incrementaPC();
    void processamento(Processo &processo);
    void executePipeline(const string &instrucao);
    void atualizarRegistradores(queue<pair<int, int>> &registradores);

    void inicializarThreads();
    void processarCore(int coreID);

    void setPolitica(TipoPolitica politica);
    TipoPolitica getPolitica();

    void setTipoExibicao(bool tipo);
    bool getTipoExibicao();
};
