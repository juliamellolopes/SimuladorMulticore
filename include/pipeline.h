/**
 * @file pipeline.h
 * @brief Declaração da classe Pipeline, que coordena os cinco estágios do pipeline MIPS.
 *
 * A classe Pipeline controla o fluxo de instruções pelo pipeline e gerencia as interações entre a
 * Unidade de Controle (UC), CPU, e memória. É a classe principal para simular o pipeline.
 */

#pragma once

#include "memory/cache.h"
#include "core.h"

class Pipeline {
public:
    Pipeline(MemoryRAM &memoryRAM, MemoryCache &memoryCache, vector<CORE> &cores, int &coreAtivo, int &PC) :
        _memoryRAM(memoryRAM),
        _memoryCache(memoryCache),
        _cores(cores),
        _coreAtivo(coreAtivo),
        _PC(PC) {}

    int lerRegistrador(int reg);
    void escreverRegistrador(int reg, int valor);
    void escreverNaMemoria(int endereco);

    void InstructionFetch(string instrucao);
    string InstructionDecode();
    vector<int> Execute(string code);

private:
    string _instrucaoAtual;
    string _opcode;

    MemoryRAM &_memoryRAM;
    MemoryCache &_memoryCache;
    vector<CORE> &_cores;
    int &_coreAtivo;
    int &_PC;

    vector<string>tokenizar(string &instrucao);
};
