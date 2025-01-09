#ifndef CORE_H
#define CORE_H

#include <vector>

using namespace std;

#define TAM_R 8   // Número de registradores

class CORE {
public:
    CORE() {
        _registradores = vector(TAM_R, 0);
    }

    int _reg1, _reg2, _regDest;
    vector<int> _registradores;                    // Vetor de núcleos (registradores).
private:
};

#endif