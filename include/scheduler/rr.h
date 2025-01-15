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