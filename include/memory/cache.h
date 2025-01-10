#pragma once

#include <queue>

#include "ram.h"

#define TAM_CACHE 5

using namespace std;

class MemoryCache {
public:
    MemoryCache(MemoryRAM &memoryRAM) : _memoryRAM(memoryRAM) {}
    void escrever(int endereco, int valor);
    void memoriaCheia();
private:
    queue<pair<int, int>> _cache;
    MemoryRAM &_memoryRAM;
};