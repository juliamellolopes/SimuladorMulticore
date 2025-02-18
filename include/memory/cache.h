/**
 * @file cache.h
 * @brief Declaração da classe MemoryCache, que implementa uma memória cache simulada.
 *
 * A classe MemoryCache gerencia a escrita de valores em um cache de tamanho fixo.
 * Quando a cache está cheia, os dados mais antigos são movidos para a memória principal (RAM).
 */

#pragma once

#include <queue>
#include <variant>
#include <unordered_map>

#include "ram.h"

#define TAM_CACHE 1

using namespace std;

class MemoryCache {
private:
    unordered_map<int, variant<int, string>> _cache;
    MemoryRAM &_memoryRAM;
    bool _tipoExibicao;

public:
    MemoryCache(MemoryRAM &memoryRAM, bool tipo) :
        _memoryRAM(memoryRAM),
        _tipoExibicao(tipo) {}

    void escreverNaCache(int endereco, const variant<int, string> valor);
    void memoriaCheia();
    void liberarCache();

    unordered_map<int, variant<int, string>> obterTodos();
};