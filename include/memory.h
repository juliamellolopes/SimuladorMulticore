/**
 * @file memory.h
 * @brief Declaração das classes MemoryRAM e MemoryCache.
 *
 * Estas classes simulam a memória principal (RAM) e a memória cache com política de substituição FIFO.
 * São utilizadas pela CPU para operações de leitura e escrita durante a execução de instruções.
 */


#pragma once

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

#define TAM_CACHE 5
#define TAM_INSTRUCTIONS 5

using namespace std;
class MemoryRAM {
public:
    MemoryRAM() {}                             // Construtor padrão.
    MemoryRAM(string path);                    // Inicializa a memória carregando instruções a partir de um arquivo de texto.
    string getInstrucao(int endereco);         // Retorna a instrução em um endereço específico.
    size_t getSize();                          // Retorna o número total de instruções carregadas.
    void escrever(int endereco, int valor);    // Armazena um valor em um endereço específico da memória.
    size_t instrucaoAtual;

private:
    unordered_map<int, int> _memoria;          // Simula o armazenamento de valores na memória.
    vector<vector<string>>_instrucoes;                 // Armazena as instruções carregadas.
    // vector<string>_instrucoes;                 // Armazena as instruções carregadas.
};

class MemoryCache {
public:
    MemoryCache() {}                           // Construtor padrão.
    MemoryCache(MemoryRAM memoryRAM);          // Inicializa a cache com referência à memória RAM.
    void escrever(int endereco, int valor);    // Armazena um par endereço-valor na cache e chama memoriaCheia() se a cache estiver cheia.
    void memoriaCheia();                       // Move o valor mais antigo para a RAM para liberar espaço na cache.
private:
    queue<pair<int, int>> _cache;              // Que armazena pares endereço-valor.
    MemoryRAM _memoryRAM;                      // Instância da memória RAM para transferência de dados.
};