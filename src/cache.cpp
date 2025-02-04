#include "../include/memory/cache.h"

/**
 * @brief Armazena um valor em um endereço específico da memória principal.
 *
 * @param endereco Endereço de memória.
 * @param valor Valor a ser armazenado.
 */
void MemoryCache::escreverNaCache(int endereco, const variant<int, string> valor) {
    static int enderecoInstrucao = 10;
    int posicao = 0;

    if (endereco) {
        posicao = endereco;
    } else {
        posicao = enderecoInstrucao++;
    }

    _cache[posicao] = valor;

    if (_tipoExibicao) {
        cout << "      -> Valor armazenado na Cache " << endl;
    }

    if (_cache.size() >= TAM_CACHE) {
        if (_tipoExibicao) {
            cout << "      -> Cache cheia" << endl;
        }
        memoriaCheia();
    }
}

/**
 * @brief Libera espaço na cache movendo o valor mais antigo para a memória principal.
 */
void MemoryCache::memoriaCheia() {
    if (_cache.empty()) return;

    auto it = _cache.begin();
    int endereco = it->first;
    variant<int, string> valor = it->second;

    MemoryCell memCell;

    if (holds_alternative<int>(valor)) {
        memCell = static_cast<MemoryCell>(get<int>(valor));
    } else if (holds_alternative<string>(valor)) {
        memCell = static_cast<MemoryCell>(get<string>(valor));
    }

    _memoryRAM.escrever(endereco, memCell);

    _cache.erase(it);
}

/**
 * @brief Esvazia completamente a Cache.
 *
 * Executa `memoriaCheia()` até que todos os blocos da Cache tenham sido movidos para a RAM.
 * Isso garante que a Cache fique vazia, podendo ser utilizada para novas instruções.
 */
void MemoryCache::liberarCache() {
    while (_cache.size() != 0) {
        memoriaCheia();
    }
}

/**
 * @brief Retorna todos os valores armazenados na Cache.
 *
 * Esse método é utilizado para obter todas as entradas armazenadas atualmente na Cache,
 * permitindo buscas rápidas e reuso de instruções.
 *
 * @return Um unordered_map contendo os valores armazenados na Cache.
 */
unordered_map<int, variant<int, string>> MemoryCache::obterTodos() {
    return _cache;
}
