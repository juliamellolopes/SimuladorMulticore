/**
 * @file uc.h
 * @brief Declaração da Unidade de Controle (UC) e da Unidade Lógica Aritmética (ULA).
 *
 * A UC gerencia a decodificação das instruções e delega operações aritméticas para a ULA.
 * É utilizada pelo pipeline para executar operações como ADD, SUB, MULT, e condicionais.
 */

#ifndef UC_H   
#define UC_H   

#include <iostream>

#include "cpu.h"

using namespace std;

#ifndef ULA_H   
#define ULA_H 

class ULA {
public:
    ULA() {}
    int operation(int var1, int var2, char var3);                         // Unidade Lógica Aritmética (ULA), executa operações aritméticas entre valores. 
private:
};

#endif

class UC {
public:
    UC();
    void select(int opcode);                                             // Unidade de Controle (UC), gerencia as operações aritméticas com base no opcode.

    CPU _cpu;
    MemoryRAM _memory;
private:
    ULA _ula;
};

#endif