#pragma once

#include <iostream>

#include "fcfs.h"
#include "rr.h"
#include "prioridade.h"
#include "processo.h"

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

public:
    Prioridade _prioridade;

    Escalonador(queue<string> &processosID) :
        _rr(processosID),
        _prioridade(processosID) {}
    ~Escalonador() {}

    void selecao(TipoPolitica politica, Processo &processo, int &processosAtivos);
};