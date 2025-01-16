/**
 * @file uc.h
 * @brief Declaração das classes UC (Unidade de Controle) e ULA (Unidade Lógica e Aritmética).
 *
 * A classe UC gerencia a execução de operações baseadas em opcodes, enquanto a ULA realiza operações
 * aritméticas e lógicas, como somas, subtrações e comparações.
 */

#pragma once

#include <iostream>

using namespace std;

#ifndef ULA_H   
#define ULA_H 
class ULA {
public:
    ULA() {}
    int operation(int var1, int var2, char var3, const bool tipo);
private:
};

#endif
class UC {
private:
    ULA _ula;
public:
    UC() {}
    ~UC() {}

    int select(int opcode, int valor1, int valor2, const bool tipo);
};
