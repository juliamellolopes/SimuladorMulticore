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