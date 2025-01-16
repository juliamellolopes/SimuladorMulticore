/**
 * @file rr.h
 * @brief Declaração da classe RoundRobin, que implementa o algoritmo de escalonamento Round Robin (RR).
 *
 * O algoritmo RR distribui o tempo de CPU de forma equitativa entre os processos, com base em um quantum fixo.
 * Quando o quantum de um processo expira, ele é colocado no final da fila.
 */

#pragma once

#include <iostream>
#include <queue>
#include <string>

using namespace std;

class RoundRobin {
private:
    queue<string> &_processosID;
public:
    RoundRobin(queue<string> &processosID) : _processosID(processosID) {}
    ~RoundRobin() {}

    void atualizarFila(string endereco) {
        _processosID.push(endereco);
    }
};