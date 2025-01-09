/**
 * @file pipeline.h
 * @brief Declaração da classe Pipeline, que coordena os cinco estágios do pipeline MIPS.
 *
 * A classe Pipeline controla o fluxo de instruções pelo pipeline e gerencia as interações entre a
 * Unidade de Controle (UC), CPU, e memória. É a classe principal para simular o pipeline.
 */

#ifndef PIPELINE_H
#define PIPELINE_H

#include "memory.h"
#include "cpu.h"
#include "uc.h"

#define DBG(x) std::cerr << #x << " = " << (x) <<std::endl;

class Pipeline {
public:
    Pipeline();                                               // Construtor padrão.
    void InstructionFetch();                                  // Busca a próxima instrução na memória.
    void InstructionDecode();                                 // Decodifica a instrução buscada, identificando o opcode e registradores.
    void Execute(string code);                                // Executa a instrução baseada no código passado.
    vector<string>tokenizar(string &instrucao);               // Separa uma instrução em tokens, retornando um vetor de strings.
    void InstructionLoop();                                              // Controla o ciclo de execução das instruções, monitorando a execução completa do conjunto de instruções.

private:
    string _instrucaoAtual;                                   // Armazena a instrução que está sendo processada.
    string _opcode;                                           // Guarda o opcode da instrução atual.
    UC _uc;
};

#endif
