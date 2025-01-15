/**
 * @file core.h
 * @brief Define a estrutura básica de registradores utilizada pela CPU.
 *
 * Este arquivo contém a definição da classe CORE, que representa um conjunto de registradores (núcleos).
 * É utilizada pela classe CPU para gerenciar os registradores durante a execução de instruções.
 */

#pragma once

#include <vector>

using namespace std;

#define TAM_R 8   // Número de registradores

class CORE {
private:
public:
    CORE() {
        _registradores = vector(TAM_R, 0);
    }

    int _reg1, _reg2, _regDest;
    vector<int> _registradores;
};