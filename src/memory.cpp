#include "../include/memory.h"

// Inicializa a cache com uma referência à memória RAM.
MemoryCache::MemoryCache(MemoryRAM memoryRAM) {
    _memoryRAM = memoryRAM;
}

// Escreve um par endereço-valor na cache. Caso a cache alcance o tamanho máximo (TAM_CACHE), move o valor mais antigo para a RAM chamando a função memoriaCheia().
void MemoryCache::escrever(int endereco, int valor) {
    cout << "Guadando informação na Cache..." << endl;
    _cache.push(make_pair(endereco, valor));

    if (_cache.size() >= TAM_CACHE) {
        cout << "[Cache cheia]... Guardando o primeiro valor na memoria RAM" << endl;
        memoriaCheia();
    }
}

// Remove o valor mais antigo da cache e o armazena na RAM, liberando espaço na cache.
void MemoryCache::memoriaCheia() {
    auto retirar = _cache.front();
    _cache.pop();
    _memoryRAM.escrever(retirar.first, retirar.second);
}

// Carrega as instruções a partir de um arquivo de texto, adicionando cada linha ao vetor _instrucoes.
MemoryRAM::MemoryRAM(string path) {
    ifstream instrFile(path);
    string linha;

    if (instrFile.is_open()) {
        while (getline(instrFile, linha)) {
            _instrucoes.push_back(linha);
        }
    } else {
        cerr << "Erro ao abrir o arquivo de instruções." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Instrucoes carregadas!" << endl;
}

// Retorna a instrução armazenada em um endereço específico da memória.
string MemoryRAM::getInstrucao(int endereco) {
    return _instrucoes.at(endereco);
}

// Retorna o número de instruções carregadas na memória.
size_t MemoryRAM::getSize() {
    return _instrucoes.size();
}

// Armazena um valor em um endereço específico da memória RAM e exibe uma mensagem de confirmação.
void MemoryRAM::escrever(int endereco, int valor) {
    _memoria[endereco] = valor;
    cout << "Valor " << valor << " foi armazenado no endereco " << endereco << endl;
}