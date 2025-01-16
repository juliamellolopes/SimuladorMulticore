/**
 * @file cache.h
 * @brief Declaração da classe MemoryCache, que implementa uma memória cache simulada.
 *
 * A classe MemoryCache gerencia a escrita de valores em um cache de tamanho fixo.
 * Quando a cache está cheia, os dados mais antigos são movidos para a memória principal (RAM).
 */

#pragma once

#include <queue>

#include "ram.h"

#define TAM_CACHE 5

using namespace std;

class MemoryCache {
private:
    queue<pair<int, int>> _cache;
    MemoryRAM &_memoryRAM;
    bool _tipoExibicao;

public:
    MemoryCache(MemoryRAM &memoryRAM, bool tipo) :
        _memoryRAM(memoryRAM),
        _tipoExibicao(tipo) {}
    void escrever(int endereco, int valor);
    void memoriaCheia();
    void liberarCache();
};