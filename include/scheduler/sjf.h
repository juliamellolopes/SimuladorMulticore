/**
 * @file sjf.h
 * @brief Declaração da classe SJF, que implementa o algoritmo de escalonamento Shortest Job First (SJF).
 *
 * O algoritmo SJF organiza os processos em ordem crescente de tempo de execução.
 */

#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#include "processo.h"
#include "memory/cache.h"

using namespace std;

class SJF {
private:
    queue<string> &_processosID;
    vector<Processo> _filaOrdenada;

public:
    SJF(queue<string> &processosID) :
        _processosID(processosID) {}
    ~SJF() {}

    void organizarFila(vector<Processo> &processos) {
        _filaOrdenada.clear();

        for (auto &proc : processos) {
            if (!proc._pcb.checkEstadoFinalizado()) {
                _filaOrdenada.push_back(proc);
            }
        }

        sort(_filaOrdenada.begin(), _filaOrdenada.end(), [](const Processo &a, const Processo &b) {
            return a._pcb.getTempoAtual() < b._pcb.getTempoAtual();
        });

        for (auto &proc : _filaOrdenada) {
            _processosID.push(proc._pcb.getEnderecoBase());
        }
    }
};
