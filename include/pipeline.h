#ifndef PIPELINE_H
#define PIPELINE_H

#include "memory.h"
#include "cpu.h"

#define DBG(x) std::cerr << #x << " = " << (x) <<std::endl;

class Pipeline {
public:
    Pipeline() {}                                             // Construtor padrão.
    Pipeline(MemoryRAM &memory, CPU &cpu);                    // Inicializa o pipeline com referências para a memória e CPU.
    void InstructionFetch();                                  // Busca a próxima instrução na memória.
    void InstructionDecode();                                 // Decodifica a instrução buscada, identificando o opcode e registradores.
    void Execute(string code);                                // Executa a instrução baseada no código passado.
    vector<string>tokenizar(string &instrucao);               // Separa uma instrução em tokens, retornando um vetor de strings.
    void loop();                                              // Controla o ciclo de execução das instruções, monitorando a execução completa do conjunto de instruções.

private:
    string _instrucaoAtual;                                   // Armazena a instrução que está sendo processada.
    string _opcode;                                           // Guarda o opcode da instrução atual.
    MemoryRAM _memoryRAM;                                     // Referência à memória RAM.
    CPU _cpu;                                                 // Referência à CPU.
};

#endif
