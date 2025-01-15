#include "../include/memory/cache.h"

/**
 * @brief Armazena um valor em um endereço específico da memória principal.
 *
 * @param endereco Endereço de memória.
 * @param valor Valor a ser armazenado.
 */
void MemoryCache::escrever(int endereco, int valor) {
    if (_tipoExibicao) {
        cout << "      -> Guadando informação na Cache..." << endl;
    }
    _cache.push(make_pair(endereco, valor));

    if (_cache.size() >= TAM_CACHE) {
        if (_tipoExibicao) {
            cout << "      -> [Cache cheia]... Guardando o primeiro valor na memoria RAM" << endl;
        }
        memoriaCheia();
    }
}

/**
 * @brief Libera espaço na cache movendo o valor mais antigo para a memória principal.
 */
void MemoryCache::memoriaCheia() {
    auto retirar = _cache.front();

    _cache.pop();
    _memoryRAM.escrever(retirar.first, retirar.second);
}

void MemoryCache::liberarCache() {
    while (_cache.size() != 0) {
        memoriaCheia();
    }
}