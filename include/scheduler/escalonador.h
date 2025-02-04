/**
 * @file escalonador.h
 * @brief Declaração da classe Escalonador, que implementa políticas de escalonamento de processos.
 *
 * A classe Escalonador gerencia a execução de processos utilizando políticas como FCFS, Round Robin e Prioridade.
 * Ela organiza as filas de processos e decide qual processo será executado em seguida.
 */

#pragma once

#include <iostream>
#include <variant> 

#include "fcfs.h"
#include "rr.h"
#include "prioridade.h"
#include "processo.h"
#include "memory/cache.h"

using namespace std;

enum TipoPolitica {
    FCFS,
    RR,
    PRIORIDADE
};

class Escalonador {
private:
    FComeFServed _fcfs;
    RoundRobin _rr;
    MemoryRAM &_memoryRAM;
    MemoryCache &_memoryCache; 


public:
    Prioridade _prioridade;

    Escalonador(queue<string> &processosID, MemoryRAM &memoryRAM, MemoryCache &memoryCache) :
        _rr(processosID),
        _memoryRAM(memoryRAM),
        _memoryCache(memoryCache),
        _prioridade(processosID) {}
    ~Escalonador() {}


    bool verificarReaproveitamento(const string &operacao, int &resultado);
    void selecao(TipoPolitica politica, Processo &processo, int &processosAtivos);
};