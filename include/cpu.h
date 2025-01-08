#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <unordered_map>

#include "memory.h"

using namespace std;

#ifndef REG_H   
#define REG_H   

#define TAM_R 8   // Número de registradores
#define TAM_C 2   // Número de núcleos

class REG {
public:
    REG();
    vector<int> _registradores;                                    // Vetor que representa os registradores de um núcleo.

private:
};

#endif
class CPU {
public:
    CPU() {}                                                         // Construtor padrão.
    CPU(MemoryRAM &memory);                                          // Inicializa a CPU com uma referência à memória RAM e configura os registradores.
    int lerRegistrador(int reg);                                     // Lê o valor de um registrador específico do núcleo ativo.
    void escreverRegistrador(int reg, int valor);                    // Escreve um valor em um registrador específico do núcleo ativo.
    void escreverNaMemoria(int endereco);                            // Escreve o valor de um registrador na memória.
    int ULA(int var1, int var2, char var3);                          // Unidade Lógica Aritmética (ULA), executa operações aritméticas entre valores.  
    void UC(int opcode);                                             // Unidade de Controle (UC), gerencia as operações aritméticas com base no opcode.
    int getPC();                                                     // Retorna o valor do contador de programa.
    void incrementaPC();                                             // Incrementa o valor do contador de programa.
    int _reg1, _reg2, _regDest;

private:
    int _coreAtivo;                                                  // Núcleo atualmente ativo na execução.
    int _PC;                                                         // Contador de programa.
    vector<REG> _cores;                                              // Vetor de núcleos (registradores).
    MemoryRAM _memoryRAM;                                            // Instância da memória principal.
    MemoryCache _memoryCache;                                        // Instância da memória cache.
};

#endif
