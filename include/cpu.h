/**
 * @file cpu.h
 * @brief Declaração da classe CPU e métodos relacionados.
 *
 * A classe CPU gerencia múltiplos núcleos e registradores, e interage com a memória principal (RAM)
 * e memória cache para execução das instruções. Utilizada pelo pipeline para processar as operações.
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <unordered_map>

#include "memory.h"
#include "core.h"

#define TAM_C 2   // Número de núcleos

class CPU {
public:
    CPU() {}                                                         // Construtor padrão.
    CPU(MemoryRAM &memory);                                          // Inicializa a CPU com uma referência à memória RAM e configura os registradores.
    int lerRegistrador(int reg);                                     // Lê o valor de um registrador específico do núcleo ativo.
    void escreverRegistrador(int reg, int valor);                    // Escreve um valor em um registrador específico do núcleo ativo.
    void escreverNaMemoria(int endereco);                            // Escreve o valor de um registrador na memória.

    int getPC();                                                     // Retorna o valor do contador de programa.
    void incrementaPC();                                             // Incrementa o valor do contador de programa.

    int _coreAtivo;                                                  // Núcleo atualmente ativo na execução.
    vector<CORE> _cores;                                              // Vetor de núcleos (registradores).
    int aux;
private:
    int _PC;                                                         // Contador de programa.
    MemoryRAM _memoryRAM;                                            // Instância da memória principal.
    MemoryCache _memoryCache;                                        // Instância da memória cache.
};

#endif
